#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QImageReader>
#include <QMessageBox>
#include <QTime>
#include "mc920.h"






//global variable to mainwindow
MedicalImage *image3D;
MedicalImage *labelImage;
QImage *imageZ;
QImage *imageY;
QImage *imageX;
QImage *imageXYZ;
ViewDisplay *viewZ;
ViewDisplay *viewY;
ViewDisplay *viewX;
int defaultMaxValue = 4095;
int NegativeType = 4;
bool negativeActive = false;
int NormalizationType = 5;
bool NormalizationActive = false;
bool startDrawXYZImage = false;







void init(){
    image3D = NULL;
    labelImage = NULL;
    imageZ = NULL;
    imageY = NULL;
    imageX = NULL;

    //xy plan
    viewZ = (ViewDisplay *)calloc(1,sizeof(ViewDisplay));
    viewZ->horizontalAxis = 'x';
    viewZ->verticalAxis = 'y';
    viewZ->referenceAxis = 'z';
    viewZ->verticalDirection = 1;
    viewZ->horizontalDirection = 1;
    viewZ->slice = 0;
    viewZ->rgbColorTable = NULL;
    viewZ->type = 1;
    updateContrastBrightParameters(viewZ,0,defaultMaxValue,0,defaultMaxValue);


    //zx plan
    viewY = (ViewDisplay *)calloc(1,sizeof(ViewDisplay));
    viewY->horizontalAxis = 'x';
    viewY->verticalAxis = 'z';
    viewY->referenceAxis = 'y';
    viewY->verticalDirection = -1;
    viewY->horizontalDirection = 1;
    viewY->slice = 0;
    viewY->rgbColorTable = NULL;
    viewY->type = 1;
    updateContrastBrightParameters(viewY,0,defaultMaxValue,0,defaultMaxValue);


    //zy plan
    viewX = (ViewDisplay *)calloc(1,sizeof(ViewDisplay));
    viewX->horizontalAxis = 'y';
    viewX->verticalAxis = 'z';
    viewX->referenceAxis = 'x';
    viewX->verticalDirection = -1;
    viewX->horizontalDirection = -1;
    viewX->slice = 0;
    viewX->rgbColorTable = NULL;
    viewX->type = 1;
    updateContrastBrightParameters(viewX,0,defaultMaxValue,0,defaultMaxValue);

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action3D_Image_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Text Files (*.scn);;C++ Files (*.cpp *.h)"));
    if (!fileName.isEmpty()) {

        if(image3D != NULL){
            DestroyMedicalImage(&image3D);
            DestroyMedicalImage(&labelImage);
            delete imageZ;
            delete imageY;
            delete imageX;
            imageZ = NULL;
            imageY = NULL;
            imageX = NULL;
        }

        image3D = ReadMedicalImage(fileName.toLatin1().data());//reading 3d image


        viewZ->slice = image3D->nz/2;
        viewZ->type = 1;
        viewZ->k2 = image3D->maxValue;
        updateContrastBrightParameters(viewZ,image3D->maxValue/2.0,image3D->maxValue);

        viewY->slice = image3D->ny/2;
        viewY->type = 1;
        viewY->k2 = image3D->maxValue;
        updateContrastBrightParameters(viewY,image3D->maxValue/2.0,image3D->maxValue);


        viewX->slice = image3D->nx/2;
        viewX->type = 1;
        viewX->k2 = image3D->maxValue;
        updateContrastBrightParameters(viewX,image3D->maxValue/2.0,image3D->maxValue);


        ui->spinBoxImageZ->setMaximum(image3D->nz-1);
        ui->spinBoxImageZ->setValue(viewZ->slice);

        ui->spinBoxImageY->setMaximum(image3D->ny-1);
        ui->spinBoxImageY->setValue(viewY->slice);

        ui->spinBoxImageX->setMaximum(image3D->nx-1);
        ui->spinBoxImageX->setValue(viewX->slice);


        //solution1: comprimi 12 bits em 8 bits (desolcamento de 4 bits para a direita)
        //solution2: salva uma imagem png como 16 bits e depois le ela
        int solution = 1;
        if(solution == 1){

            getQImageFromView(viewZ,image3D,labelImage,&imageZ);
            getQImageFromView(viewY,image3D,labelImage,&imageY);
            getQImageFromView(viewX,image3D,labelImage,&imageX);

            displayImageOnLabel(imageZ,ui->labelFigureZ);
            displayImageOnLabel(imageY,ui->labelFigureY);
            displayImageOnLabel(imageX,ui->labelFigureX);
        }

    }
    else{
        QMessageBox messageBox;
        messageBox.critical(0,"Error","File is empty");
        messageBox.setFixedSize(500,200);
    }

    ui->SpinBoxPointX->setValue(image3D->nx/2);
    ui->SpinBoxPointY->setValue(image3D->ny/2);
    startDrawXYZImage = true;
    ui->SpinBoxPointZ->setValue(image3D->nz/2);
}

void MainWindow::on_spinBoxImageZ_valueChanged(int newValue)
{
    try{
        if(imageZ != NULL && image3D != NULL){
            viewZ->slice = newValue;
            getQImageFromView(viewZ,image3D,labelImage,&imageZ);
            displayImageOnLabel(imageZ,ui->labelFigureZ);
        }
    }catch(int e){
        fprintf(stderr,"Nao consegui converter\n");
    }

}

void MainWindow::on_spinBoxImageY_valueChanged(int newValue)
{
    try{
        if(imageY != NULL && image3D != NULL){
            viewY->slice = newValue;
            getQImageFromView(viewY,image3D,labelImage,&imageY);
            displayImageOnLabel(imageY,ui->labelFigureY);
        }
    }catch(int e){
        fprintf(stderr,"Nao consegui converter\n");
    }
}

void MainWindow::on_spinBoxImageX_valueChanged(int newValue)
{
    try{
        if(imageX != NULL && image3D != NULL){
            viewX->slice = newValue;
            getQImageFromView(viewX,image3D,labelImage,&imageX);
            displayImageOnLabel(imageX,ui->labelFigureX);
        }
    }catch(int e){
        fprintf(stderr,"Nao consegui converter\n");
    }
}


void MainWindow::on_mirrorZ_clicked()
{
    if(imageZ != NULL && image3D != NULL){
        mirrorAlongVerticalAxis(viewZ);
        getQImageFromView(viewZ,image3D,labelImage,&imageZ);
        displayImageOnLabel(imageZ,ui->labelFigureZ);
    }
}



void MainWindow::on_rotateZ_90AntiClockwise_clicked()
{
    if(imageZ != NULL && image3D != NULL){
        rotationAntiClockWiseZ(viewZ);
        getQImageFromView(viewZ,image3D,labelImage,&imageZ);
        displayImageOnLabel(imageZ,ui->labelFigureZ);
    }
}

void MainWindow::on_rotateY_90Anticlockwise_clicked()
{
    if(imageY != NULL && image3D != NULL){
        rotationAntiClockWiseY(viewY);
        getQImageFromView(viewY,image3D,labelImage,&imageY);
        displayImageOnLabel(imageY,ui->labelFigureY);
    }
}

void MainWindow::on_rotateY_90Anticlockwise_2_clicked()
{
    if(imageX != NULL && image3D != NULL){
        rotationAntiClockWiseY(viewX);
        getQImageFromView(viewX,image3D,labelImage,&imageX);
        displayImageOnLabel(imageX,ui->labelFigureX);
    }
}

void MainWindow::on_actionLabel_map_triggered()
{
    if(image3D != NULL){

        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                        tr("Text Files (*.scn)"));

        if (!fileName.isEmpty()) {

            if(labelImage != NULL){
                DestroyMedicalImage(&labelImage);
                destroyRGBColorMap(&viewZ->rgbColorTable);
                destroyRGBColorMap(&viewY->rgbColorTable);
                destroyRGBColorMap(&viewX->rgbColorTable);
                destroyYCgCoColorMap(&viewZ->yCgCoColorTable);
                destroyYCgCoColorMap(&viewY->yCgCoColorTable);
                destroyYCgCoColorMap(&viewX->yCgCoColorTable);
            }
            labelImage = ReadMedicalImage(fileName.toLatin1().data());

            //TODO: checar se as dimensoes sao iguais labelImage-3Dimage
            viewZ->rgbColorTable = generateRGBColorMap(labelImage,4095);
            copyColorMap(viewZ->rgbColorTable,&viewY->rgbColorTable);
            copyColorMap(viewZ->rgbColorTable,&viewX->rgbColorTable);

            //            for(int i=0; i<viewZ->rgbColorTable->numberRows; i++){
            //                for(int j=0; j<viewZ->rgbColorTable->numberColumns; j++){
            //                    fprintf(stderr,"%d ",viewZ->rgbColorTable->table[i][j]);
            //                }
            //                fprintf(stderr,"\n");
            //            }
            //            fprintf(stderr,"\n");



            convertRGBColorMap2YCgCoColorMap(viewZ->rgbColorTable,&viewZ->yCgCoColorTable, 4095);
            convertRGBColorMap2YCgCoColorMap(viewY->rgbColorTable,&viewY->yCgCoColorTable, 4095);
            convertRGBColorMap2YCgCoColorMap(viewX->rgbColorTable,&viewX->yCgCoColorTable, 4095);

            //            for(int i=0; i<viewZ->rgbColorTable->numberRows; i++){
            //                for(int j=0; j<viewZ->rgbColorTable->numberColumns; j++){
            //                    fprintf(stderr,"%f ",viewZ->yCgCoColorTable->table[i][j]);
            //                }
            //                fprintf(stderr,"\n");
            //            }
            //            fprintf(stderr,"\n");

            viewZ->type = 3;
            viewY->type = 3;
            viewX->type = 3;

            getQImageFromView(viewZ,image3D,labelImage,&imageZ);
            getQImageFromView(viewY,image3D,labelImage,&imageY);
            getQImageFromView(viewX,image3D,labelImage,&imageX);

            displayImageOnLabel(imageZ,ui->labelFigureZ);
            displayImageOnLabel(imageY,ui->labelFigureY);
            displayImageOnLabel(imageX,ui->labelFigureX);


        }else{
            QMessageBox messageBox;
            messageBox.critical(0,"Error","File is empty");
            messageBox.setFixedSize(500,200);
        }


    }else{
        QMessageBox messageBox;
        messageBox.critical(0,"Error","You must load an image");
        messageBox.setFixedSize(500,200);
    }
}


void MainWindow::on_labelFigureZ_customContextMenuRequested(const QPoint &pos)
{
    const QPoint globalMousePosition(pos.x() + ui->labelFigureZ->geometry().topLeft().x(), pos.y() + ui->labelFigureZ->geometry().topLeft().y());
    int selectedOption = createContextMenuForLabelImage(image3D,labelImage,globalMousePosition,this);
    if(viewZ->type != selectedOption && selectedOption > 0){
        viewZ->type = selectedOption;
        getQImageFromView(viewZ,image3D,labelImage,&imageZ);
        displayImageOnLabel(imageZ,ui->labelFigureZ);
    }
}


void MainWindow::on_labelFigureY_customContextMenuRequested(const QPoint &pos)
{
    const QPoint globalMousePosition(pos.x() + ui->labelFigureY->geometry().topLeft().x(), pos.y() + ui->labelFigureY->geometry().topLeft().y());
    int selectedOption = createContextMenuForLabelImage(image3D,labelImage,globalMousePosition,this);
    if(viewY->type != selectedOption && selectedOption > 0){
        viewY->type = selectedOption;
        getQImageFromView(viewY,image3D,labelImage,&imageY);
        displayImageOnLabel(imageY,ui->labelFigureY);
    }
}

void MainWindow::on_labelFigureX_customContextMenuRequested(const QPoint &pos)
{
    const QPoint globalMousePosition(pos.x() + ui->labelFigureX->geometry().topLeft().x(), pos.y() + ui->labelFigureX->geometry().topLeft().y());
    int selectedOption = createContextMenuForLabelImage(image3D,labelImage,globalMousePosition,this);
    if(viewX->type != selectedOption && selectedOption > 0){
        viewX->type = selectedOption;
        getQImageFromView(viewX,image3D,labelImage,&imageX);
        displayImageOnLabel(imageX,ui->labelFigureX);
    }
}



void MainWindow::on_pushButton_clicked()
{

    if(image3D != NULL){
        brightContrastDialogForm = new BrightContrastDialog(this,viewZ->bright,viewZ->contrast,image3D->maxValue,negativeActive, NormalizationActive);
        brightContrastDialogForm->setAttribute( Qt::WA_DeleteOnClose );
        brightContrastDialogForm->show();
        connect(brightContrastDialogForm,SIGNAL(brightSignal(float)),this,SLOT(updateImagesNewBrightContrast()));
        connect(brightContrastDialogForm,SIGNAL(contrastSignal(float)),this,SLOT(updateImagesNewBrightContrast()));
        connect(brightContrastDialogForm,SIGNAL(negativeSignal(bool)),this,SLOT(displayNegativeImage()));
        connect(brightContrastDialogForm,SIGNAL(normalizationSignal(bool)),this,SLOT(displayNormalizedImage()));
    }else{
        brightContrastDialogForm = new BrightContrastDialog(this,viewZ->bright,viewZ->contrast,defaultMaxValue, negativeActive,NormalizationActive);
        brightContrastDialogForm->setAttribute( Qt::WA_DeleteOnClose );
        brightContrastDialogForm->show();
        connect(brightContrastDialogForm,SIGNAL(brightSignal(float)),this,SLOT(updateImagesNewBrightContrast()));
        connect(brightContrastDialogForm,SIGNAL(contrastSignal(float)),this,SLOT(updateImagesNewBrightContrast()));
        connect(brightContrastDialogForm,SIGNAL(negativeSignal(bool)),this,SLOT(displayNegativeImage()));
        connect(brightContrastDialogForm,SIGNAL(normalizationSignal(bool)),this,SLOT(displayNormalizedImage()));
    }
}

void MainWindow::updateImagesNewBrightContrast(){
    viewZ->bright = brightContrastDialogForm->brightValue;
    viewZ->contrast = brightContrastDialogForm->contrastValue;

    viewZ->I1 = viewZ->bright - (viewZ->contrast/2);
    viewZ->I2 = viewZ->contrast - viewZ->I1;

    viewY->bright = viewZ->bright;
    viewY->contrast = viewZ->contrast;
    viewY->I1 = viewZ->I1;
    viewY->I2 = viewZ->I2;

    viewX->bright = viewZ->bright;
    viewX->contrast = viewZ->contrast;
    viewX->I1 = viewZ->I1;
    viewX->I2 = viewZ->I2;
    getQImageFromView(viewZ,image3D,labelImage,&imageZ);
    displayImageOnLabel(imageZ,ui->labelFigureZ);

    getQImageFromView(viewY,image3D,labelImage,&imageY);
    displayImageOnLabel(imageY,ui->labelFigureY);

    getQImageFromView(viewX,image3D,labelImage,&imageX);
    displayImageOnLabel(imageX,ui->labelFigureX);
}

void MainWindow::displayNegativeImage(){
    negativeActive = brightContrastDialogForm->negative;
    viewZ->type = NegativeType + viewZ->type;
    NegativeType = viewZ->type - NegativeType;
    viewZ->type = viewZ->type - NegativeType;
    viewY->type = viewZ->type;
    viewX->type = viewZ->type;

    if(image3D != NULL){
        getQImageFromView(viewZ,image3D,labelImage,&imageZ);
        displayImageOnLabel(imageZ,ui->labelFigureZ);

        getQImageFromView(viewY,image3D,labelImage,&imageY);
        displayImageOnLabel(imageY,ui->labelFigureY);

        getQImageFromView(viewX,image3D,labelImage,&imageX);
        displayImageOnLabel(imageX,ui->labelFigureX);
    }
}

void MainWindow::displayNormalizedImage(){
    NormalizationActive = brightContrastDialogForm->normalization;
    viewZ->type = NormalizationType + viewZ->type;
    NormalizationType = viewZ->type - NormalizationType;
    viewZ->type = viewZ->type - NormalizationType;
    viewY->type = viewZ->type;
    viewX->type = viewZ->type;

    if(image3D != NULL){
        getQImageFromView(viewZ,image3D,labelImage,&imageZ);
        displayImageOnLabel(imageZ,ui->labelFigureZ);

        getQImageFromView(viewY,image3D,labelImage,&imageY);
        displayImageOnLabel(imageY,ui->labelFigureY);

        getQImageFromView(viewX,image3D,labelImage,&imageX);
        displayImageOnLabel(imageX,ui->labelFigureX);
    }
}



void MainWindow::on_pushButton_2_clicked()
{
    iftMatrix<float> *vec = createMatrix(1,4,(float)0);

    vec->elements[0] = 1;
    vec->elements[1] = 1;
    vec->elements[2] = 1;
    vec->elements[3] = 0;

    iftMatrix<float> *p = createMatrix(1,4,(float)0);

    p->elements[0] = 157/2.;
    p->elements[1] = 255/2.;
    p->elements[2] = 255/2.;
    p->elements[3] = 1;


    iftMatrix<float> *p2 = createMatrix(1,4,(float)0);
    p2->elements[0] = 157;
    p2->elements[1] = 255;
    p2->elements[2] = 255;
    p2->elements[3] = 1;



    QTime myTimer;
    int nMilliseconds;
    MedicalImage* image3D_aux = ReadMedicalImage("brain.scn");

    myTimer.start();
    MedicalImage* out = refactoreScene(p,p2,vec,image3D_aux,100);
    WriteMedicalImage(out,"teste.scn");
    nMilliseconds = myTimer.elapsed();
    fprintf(stderr,"took %d mseconds to execute \n", nMilliseconds);
//    myTimer.start();
//    getPlanarSlice(p,vec,image3D_aux);
//    nMilliseconds = myTimer.elapsed();
//    fprintf(stderr,"took %d mseconds to execute \n", nMilliseconds);

    //    myTimer.start();
    //    refactoreImage(image3D,image3D->dx/2.,image3D->dy/2.,image3D->dz/2.);
    //    nMilliseconds = myTimer.elapsed();
    //    fprintf(stderr,"took %d mseconds to execute \n", nMilliseconds);


//    myTimer.start();
//    refactoreImage2(image3D_aux,image3D_aux->dx/2.,image3D_aux->dy/2.,image3D_aux->dz/2.);
//    nMilliseconds = myTimer.elapsed();
//    fprintf(stderr,"took %d mseconds to execute \n", nMilliseconds);
}

void MainWindow::on_actionRefactor_triggered()
{
    if(image3D != NULL){
        refactFormDialog = new RefactFormDialog(this,image3D->dx,image3D->dy,image3D->dz);
        refactFormDialog->setAttribute( Qt::WA_DeleteOnClose );
        refactFormDialog->show();
        connect(refactFormDialog,SIGNAL(okSignal(float,float,float)),this,SLOT(refactScene()));
    }
}

void MainWindow::refactScene(){

    MedicalImage* refactoredImage = refactoreImage2(image3D,refactFormDialog->dx,refactFormDialog->dy,refactFormDialog->dz);

    if(image3D != NULL){
        DestroyMedicalImage(&image3D);
        DestroyMedicalImage(&labelImage);
        delete imageZ;
        delete imageY;
        delete imageX;
        imageZ = NULL;
        imageY = NULL;
        imageX = NULL;
    }
    image3D = refactoredImage;

    viewZ->slice = image3D->nz/2;
    viewZ->type = 1;
    viewZ->k2 = image3D->maxValue;
    updateContrastBrightParameters(viewZ,image3D->maxValue/2.0,image3D->maxValue);

    viewY->slice = image3D->ny/2;
    viewY->type = 1;
    viewY->k2 = image3D->maxValue;
    updateContrastBrightParameters(viewY,image3D->maxValue/2.0,image3D->maxValue);


    viewX->slice = image3D->nx/2;
    viewX->type = 1;
    viewX->k2 = image3D->maxValue;
    updateContrastBrightParameters(viewX,image3D->maxValue/2.0,image3D->maxValue);



    ui->spinBoxImageZ->setMaximum(image3D->nz-1);
    ui->spinBoxImageZ->setValue(viewZ->slice);

    ui->spinBoxImageY->setMaximum(image3D->ny-1);
    ui->spinBoxImageY->setValue(viewY->slice);

    ui->spinBoxImageX->setMaximum(image3D->nx-1);
    ui->spinBoxImageX->setValue(viewX->slice);

    getQImageFromView(viewZ,image3D,labelImage,&imageZ);
    getQImageFromView(viewY,image3D,labelImage,&imageY);
    getQImageFromView(viewX,image3D,labelImage,&imageX);

    displayImageOnLabel(imageZ,ui->labelFigureZ);
    displayImageOnLabel(imageY,ui->labelFigureY);
    displayImageOnLabel(imageX,ui->labelFigureX);
}



void MainWindow::on_SpinBoxPointX_valueChanged(double p_x)
{
    ui->SpinBoxPointX->setValue(p_x);
    if(image3D != NULL){
        iftMatrix<float> *vec = createMatrix(1,4,(float)0);
        iftMatrix<float> *p = createMatrix(1,4,(float)0);
        p->elements[0] = ui->SpinBoxPointX->value();
        p->elements[1] = ui->SpinBoxPointY->value();
        p->elements[2] = ui->SpinBoxPointZ->value();
        p->elements[3] = 1;

        vec->elements[0] = ui->SpinBoxVectorX->value();
        vec->elements[1] = ui->SpinBoxVectorY->value();
        vec->elements[2] = ui->SpinBoxVectorZ->value();
        vec->elements[3] = 0;

        GrayImage *sliceXYZ = getPlanarSlice(p,vec,image3D,true);
        ViewDisplay *viewXYZ = (ViewDisplay *)calloc(1,sizeof(ViewDisplay));
        viewXYZ->k1 = 0;
        viewXYZ->k2 = image3D->maxValue;
        //WidthLevelGrayImage(slice, view->bright, view->contrast,image3D->maxValue);
        //updateContrastBrightParameters(viewXYZ,image3D->maxValue/2.0,image3D->maxValue);
        //WidthLevelGrayImage(slice, viewXYZ->bright, viewXYZ->contrast,image3D->maxValue);

        if(image3D->nbits > 8){
            imageXYZ = createGrayImage2LabelArea(sliceXYZ,image3D->maxValue);
        }else{
            imageXYZ = create8bitsGrayImage2LabelArea(sliceXYZ);
        }

        displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
        DestroyGrayImage(&sliceXYZ);
    }
}

void MainWindow::on_SpinBoxPointY_valueChanged(double p_y)
{
    ui->SpinBoxPointY->setValue(p_y);
    if(image3D != NULL ){
        iftMatrix<float> *vec = createMatrix(1,4,(float)0);
        iftMatrix<float> *p = createMatrix(1,4,(float)0);
        p->elements[0] = ui->SpinBoxPointX->value();
        p->elements[1] = ui->SpinBoxPointY->value();
        p->elements[2] = ui->SpinBoxPointZ->value();
        p->elements[3] = 1;

        vec->elements[0] = ui->SpinBoxVectorX->value();
        vec->elements[1] = ui->SpinBoxVectorY->value();
        vec->elements[2] = ui->SpinBoxVectorZ->value();
        vec->elements[3] = 0;

        GrayImage *slice = getPlanarSlice(p,vec,image3D,true);
        ViewDisplay *viewXYZ = (ViewDisplay *)calloc(1,sizeof(ViewDisplay));
        viewXYZ->k1 = 0;
        viewXYZ->k2 = image3D->maxValue;
        //WidthLevelGrayImage(slice, view->bright, view->contrast,image3D->maxValue);
        updateContrastBrightParameters(viewXYZ,image3D->maxValue/2.0,image3D->maxValue);
        WidthLevelGrayImage(slice, viewXYZ->bright, viewXYZ->contrast,image3D->maxValue);

        if(image3D->nbits > 8){
            imageXYZ = createGrayImage2LabelArea(slice,image3D->maxValue);
        }else{
            imageXYZ = create8bitsGrayImage2LabelArea(slice);
        }

        displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
        DestroyGrayImage(&slice);
    }
}

void MainWindow::on_SpinBoxPointZ_valueChanged(double p_z)
{
    ui->SpinBoxPointZ->setValue(p_z);
    if(image3D != NULL){
        iftMatrix<float> *vec = createMatrix(1,4,(float)0);
        iftMatrix<float> *p = createMatrix(1,4,(float)0);
        p->elements[0] = ui->SpinBoxPointX->value();
        p->elements[1] = ui->SpinBoxPointY->value();
        p->elements[2] = ui->SpinBoxPointZ->value();
        p->elements[3] = 1;

        vec->elements[0] = ui->SpinBoxVectorX->value();
        vec->elements[1] = ui->SpinBoxVectorY->value();
        vec->elements[2] = ui->SpinBoxVectorZ->value();
        vec->elements[3] = 0;

        GrayImage *slice = getPlanarSlice(p,vec,image3D,true);
        ViewDisplay *viewXYZ = (ViewDisplay *)calloc(1,sizeof(ViewDisplay));
        viewXYZ->k1 = 0;
        viewXYZ->k2 = image3D->maxValue;
        //WidthLevelGrayImage(slice, view->bright, view->contrast,image3D->maxValue);
        updateContrastBrightParameters(viewXYZ,image3D->maxValue/2.0,image3D->maxValue);
        WidthLevelGrayImage(slice, viewXYZ->bright, viewXYZ->contrast,image3D->maxValue);

        if(image3D->nbits > 8){
            imageXYZ = createGrayImage2LabelArea(slice,image3D->maxValue);
        }else{
            imageXYZ = create8bitsGrayImage2LabelArea(slice);
        }

        displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
        DestroyGrayImage(&slice);
    }
}

void MainWindow::on_SpinBoxVectorX_valueChanged(double v_x)
{
    ui->SpinBoxVectorX->setValue(v_x);
    if(image3D != NULL){
        iftMatrix<float> *vec = createMatrix(1,4,(float)0);
        iftMatrix<float> *p = createMatrix(1,4,(float)0);
        p->elements[0] = ui->SpinBoxPointX->value();
        p->elements[1] = ui->SpinBoxPointY->value();
        p->elements[2] = ui->SpinBoxPointZ->value();
        p->elements[3] = 1;

        vec->elements[0] = ui->SpinBoxVectorX->value();
        vec->elements[1] = ui->SpinBoxVectorY->value();
        vec->elements[2] = ui->SpinBoxVectorZ->value();
        vec->elements[3] = 0;

        GrayImage *sliceXYZ = getPlanarSlice(p,vec,image3D,true);
        ViewDisplay *viewXYZ = (ViewDisplay *)calloc(1,sizeof(ViewDisplay));
        viewXYZ->k1 = 0;
        viewXYZ->k2 = image3D->maxValue;
        //WidthLevelGrayImage(slice, view->bright, view->contrast,image3D->maxValue);
        updateContrastBrightParameters(viewXYZ,image3D->maxValue/2.0,image3D->maxValue);
        WidthLevelGrayImage(sliceXYZ, viewXYZ->bright, viewXYZ->contrast,image3D->maxValue);

        if(image3D->nbits > 8){
            imageXYZ = createGrayImage2LabelArea(sliceXYZ,image3D->maxValue);
        }else{
            imageXYZ = create8bitsGrayImage2LabelArea(sliceXYZ);
        }

        displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
        DestroyGrayImage(&sliceXYZ);
    }
}

void MainWindow::on_SpinBoxVectorY_valueChanged(double v_y)
{
    ui->SpinBoxVectorY->setValue(v_y);
    if(image3D != NULL){
        iftMatrix<float> *vec = createMatrix(1,4,(float)0);
        iftMatrix<float> *p = createMatrix(1,4,(float)0);
        p->elements[0] = ui->SpinBoxPointX->value();
        p->elements[1] = ui->SpinBoxPointY->value();
        p->elements[2] = ui->SpinBoxPointZ->value();
        p->elements[3] = 1;

        vec->elements[0] = ui->SpinBoxVectorX->value();
        vec->elements[1] = ui->SpinBoxVectorY->value();
        vec->elements[2] = ui->SpinBoxVectorZ->value();
        vec->elements[3] = 0;

        GrayImage *sliceXYZ = getPlanarSlice(p,vec,image3D,true);
        ViewDisplay *viewXYZ = (ViewDisplay *)calloc(1,sizeof(ViewDisplay));
        viewXYZ->k1 = 0;
        viewXYZ->k2 = image3D->maxValue;
        //WidthLevelGrayImage(slice, view->bright, view->contrast,image3D->maxValue);
        updateContrastBrightParameters(viewXYZ,image3D->maxValue/2.0,image3D->maxValue);
        WidthLevelGrayImage(sliceXYZ, viewXYZ->bright, viewXYZ->contrast,image3D->maxValue);

        if(image3D->nbits > 8){
            imageXYZ = createGrayImage2LabelArea(sliceXYZ,image3D->maxValue);
        }else{
            imageXYZ = create8bitsGrayImage2LabelArea(sliceXYZ);
        }

        displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
        DestroyGrayImage(&sliceXYZ);
    }
}

void MainWindow::on_SpinBoxVectorZ_valueChanged(double v_z)
{
    ui->SpinBoxVectorZ->setValue(v_z);
    if(image3D != NULL){
        iftMatrix<float> *vec = createMatrix(1,4,(float)0);
        iftMatrix<float> *p = createMatrix(1,4,(float)0);
        p->elements[0] = ui->SpinBoxPointX->value();
        p->elements[1] = ui->SpinBoxPointY->value();
        p->elements[2] = ui->SpinBoxPointZ->value();
        p->elements[3] = 1;

        vec->elements[0] = ui->SpinBoxVectorX->value();
        vec->elements[1] = ui->SpinBoxVectorY->value();
        vec->elements[2] = ui->SpinBoxVectorZ->value();
        vec->elements[3] = 0;

        GrayImage *sliceXYZ = getPlanarSlice(p,vec,image3D,true);
        ViewDisplay *viewXYZ = (ViewDisplay *)calloc(1,sizeof(ViewDisplay));
        viewXYZ->k1 = 0;
        viewXYZ->k2 = image3D->maxValue;
        //WidthLevelGrayImage(slice, view->bright, view->contrast,image3D->maxValue);
        updateContrastBrightParameters(viewXYZ,image3D->maxValue/2.0,image3D->maxValue);
        WidthLevelGrayImage(sliceXYZ, viewXYZ->bright, viewXYZ->contrast,image3D->maxValue);

        if(image3D->nbits > 8){
            imageXYZ = createGrayImage2LabelArea(sliceXYZ,image3D->maxValue);
        }else{
            imageXYZ = create8bitsGrayImage2LabelArea(sliceXYZ);
        }

        displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
        DestroyGrayImage(&sliceXYZ);
    }
}

void MainWindow::on_actionGenerate_New_Volume_triggered()
{
    if(image3D != NULL){
\
    }
}
