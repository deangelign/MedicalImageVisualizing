#include "image.h"

Image *CreateImage(int ncols, int nrows)
{
    Image *img=NULL;
    int i;

    img = (Image *) calloc(1,sizeof(Image));
    if (img == NULL){
        Error(MSG1,"CreateImage");
    }

    img->val   = AllocIntArray(nrows*ncols);
    img->tbrow = AllocIntArray(nrows);

    img->tbrow[0]=0;
    for (i=1; i < nrows; i++)
        img->tbrow[i]=img->tbrow[i-1]+ncols;
    img->ncols = ncols;
    img->nrows = nrows;

    return(img);
}

void DestroyImage(Image **img)
{
    Image *aux;

    aux = *img;
    if(aux != NULL){
        if (aux->val != NULL)   free(aux->val);
        if (aux->tbrow != NULL) free(aux->tbrow);
        free(aux);
        *img = NULL;
    }
}

Image *ReadImage(char *filename)
{
    FILE *fp=NULL;
    unsigned char *value=NULL;
    char type[10];
    int  i,ncols,nrows,n;
    Image *img=NULL;
    char z[256];

    fp = fopen(filename,"rb");
    if (fp == NULL){
        fprintf(stderr,"Cannot open %s\n",filename);
        exit(-1);
    }
    fscanf(fp,"%s\n",type);
    if((strcmp(type,"P5")==0)){
        NCFgets(z,255,fp);
        sscanf(z,"%d %d\n",&ncols,&nrows);
        n = ncols*nrows;
        NCFgets(z,255,fp);
        sscanf(z,"%d\n",&i);
        fgetc(fp);
        value = (unsigned char *)calloc(n,sizeof(unsigned char));
        if (value != NULL){
            fread(value,sizeof(unsigned char),n,fp);
        }else{
            fprintf(stderr,"Insufficient memory in ReadImage\n");
            exit(-1);
        }
        fclose(fp);
        img = CreateImage(ncols,nrows);
        for (i=0; i < n; i++)
            img->val[i]=(int)value[i];
        free(value);
    }else{
        if((strcmp(type,"P2")==0)){
            NCFgets(z,255,fp);
            sscanf(z,"%d %d\n",&ncols,&nrows);
            n = ncols*nrows;
            NCFgets(z,255,fp);
            sscanf(z,"%d\n",&i);
            img = CreateImage(ncols,nrows);
            for (i=0; i < n; i++)
                fscanf(fp,"%d",&img->val[i]);
            fclose(fp);
        }else{
            fprintf(stderr,"Input image must be P2 or P5\n");
            exit(-1);
        }
    }

    return(img);
}

void WriteImage(Image *img,char *filename)
{
    FILE *fp;
    int i, n, Imax,Imin;

    fp = fopen(filename,"wb");
    if (fp == NULL){
        fprintf(stderr,"Cannot open %s\n",filename);
        exit(-1);
    }
    n    = img->ncols*img->nrows;
    Imax = INT_MIN; Imin = INT_MAX;
    for (i=0; i < n; i++) {
        if (img->val[i] > Imax)
            Imax = img->val[i];
        if (img->val[i] < Imin)
            Imin = img->val[i];
    }

    fprintf(fp,"P2\n");
    fprintf(fp,"%d %d\n",img->ncols,img->nrows);
    fprintf(fp,"%d\n",Imax-Imin);

    for (i=0; i < n; i++) {
        fprintf(fp,"%d ",img->val[i]-Imin);
        if (((i+1)%17) == 0)
            fprintf(fp,"\n");
    }

    fclose(fp);
}


Image *MakeImage(char *data)
{
    Image *img;
    int ncols,nrows,i,n;

    sscanf(data,"%d",&ncols);
    data=strchr(data,',')+1;
    sscanf(data,"%d",&nrows);
    data=strchr(data,',')+1;

    img = CreateImage(ncols,nrows);
    n   = ncols*nrows;
    for (i=0; i < n; i++) {
        sscanf(data,"%d",&img->val[i]);
        data=strchr(data,',')+1;
    }
    return(img);
}

Image  *AddZeros(Image *img, int ncols, int nrows)
{
    Image *eimg; /* expanded image with zeros to the left and to the
                  bottom of the input image */
    int i,j,x,y;

    eimg = CreateImage(img->ncols+ncols,img->nrows+nrows);

    j = 0;
    for (y=0; y < img->nrows; y++)
        for (x=0; x < img->ncols; x++) {
            i = x + eimg->tbrow[y];
            eimg->val[i]=img->val[j];
            j++;
        }
    return(eimg);
}

Image *CreateCos(int ncols, int nrows, float wx, float wy, float phix, float phiy)
{
    int x, y, p;
    Image *cosimg = NULL;

    cosimg = CreateImage(ncols, nrows);

    /* We are adding a DC level of 127 to the amplitude of the
       sine. This will create an extra impulse at the center of the
       magnitude spectrum. */

    for (x = 0; x < ncols; x++)
        for ( y = 0; y < nrows; y++) {
            p = x + cosimg->tbrow[y];
            cosimg->val[p] = (int) (127.0*(cos(2*PI*wx*(float)(x - phix)/ncols + 2*PI*wy*(float)(y - phiy)/nrows))+127.0+0.5);
        }

    return cosimg;
}

Image *Abs(Image *img)
{
    Image *absimg=NULL;
    int p,n;

    n = img->ncols*img->nrows;
    absimg = CreateImage(img->ncols,img->nrows);
    for (p=0; p < n; p++)
        absimg->val[p] = abs(img->val[p]);
    return(absimg);
}

Image  *ImageMagnitude(Image *imgx, Image *imgy)
{
    Image *mag=CreateImage(imgx->ncols,imgx->nrows);
    int p,n=imgx->ncols*imgx->nrows;

    for (p=0; p < n; p++)
        mag->val[p] = (int)sqrt(imgx->val[p]*imgx->val[p] + imgy->val[p]*imgy->val[p]);

    return(mag);
}

DImage *CreateDImage(int ncols, int nrows)
{
    DImage *dimg=NULL;
    int i;

    dimg = (DImage *) calloc(1,sizeof(DImage));
    if (dimg == NULL){
        Error(MSG1,"CreateDImage");
    }

    dimg->val   = AllocDoubleArray(nrows*ncols);
    dimg->tbrow = AllocIntArray(nrows);

    dimg->tbrow[0]=0;
    for (i=1; i < nrows; i++)
        dimg->tbrow[i]=dimg->tbrow[i-1]+ncols;
    dimg->ncols = ncols;
    dimg->nrows = nrows;

    return(dimg);
}

void DestroyDImage(DImage **dimg)
{
    DImage *aux;

    aux = *dimg;
    if(aux != NULL){
        if (aux->val != NULL)   free(aux->val);
        if (aux->tbrow != NULL) free(aux->tbrow);
        free(aux);
        *dimg = NULL;
    }
}

GrayImage *CreateGrayImage(int nx, int ny)
{
    GrayImage *I=(GrayImage *)calloc(1,sizeof(GrayImage));
    int y;

    I->nx = nx;
    I->ny = ny;
    I->dx = 1.0;
    I->dy = 1.0;
    sprintf(I->unid,"mm");

    I->val = (int **)calloc(ny,sizeof(int *));
    if (I->val == NULL)
        Error(MSG1,"CreateGrayImage");
    else{
        for (y=0; y < I->ny; y++){
            I->val[y] = (int *)calloc(nx,sizeof(int));
            if (I->val[y] == NULL)
                Error(MSG1,"CreateGrayImage");
        }
    }
    return(I);
}

void DestroyGrayImage(GrayImage **I)
{
    int y;

    if ((*I) != NULL) {
        for (y=0; y < (*I)->ny; y++)
            free((*I)->val[y]);
        free((*I)->val);
        free(*I);
        *I = NULL;
    }
}

GrayImage *ReadGrayImage(char *filename)
{
    FILE *fp=NULL;
    char type[10];
    uchar *data=NULL;
    int  x,y,nx,ny,Imax;
    GrayImage *I=NULL;
    char remarks[256];

    fp = fopen(filename,"r");
    if (fp != NULL) {
        fscanf(fp,"%s",type);
        NCFgets(remarks,255,fp);

        if ((strcmp(type,"P2")==0)||
                (strcmp(type,"P5")==0)){
            fscanf(fp,"%d",&nx);
            fscanf(fp,"%d\n",&ny);

            I = CreateGrayImage(nx,ny);
            fscanf(fp,"%d\n",&Imax);

            if (strcmp(type,"P2")==0){
                for (y=0; y < ny; y++)
                    for (x=0; x < nx; x++)
                        fscanf(fp,"%d",&I->val[y][x]);
            }else{
                if (strcmp(type,"P5")==0){
                    data = AllocUCharArray(nx*ny);
                    fread(data,sizeof(uchar),nx*ny,fp);
                    for (y=0; y < ny; y++)
                        for (x=0; x < nx; x++)
                            I->val[y][x] = data[x+y*nx];
                    free(data);
                }
            }
        }else{
            Error("Image type invalid","ReadGrayImage");
        }
        fclose(fp);
    }else{
        Error(MSG2,"ReadGrayImage");
    }

    return(I);
}

void WriteGrayImage(GrayImage *I, char *filename)
{
    FILE *fp=NULL;
    uchar *data=NULL;
    int  x,y,Imax,Imin;

    Imax = INT_MIN; Imin = INT_MAX;
    for (y=0; y < I->ny; y++)
        for (x=0; x < I->nx; x++){
            if (I->val[y][x] > Imax)
                Imax = I->val[y][x];
            if (I->val[y][x] < Imin)
                Imin = I->val[y][x];
        }

    fp = fopen(filename,"w");
    if (fp != NULL) {

        if (((Imax-Imin) >= 0)&&((Imax-Imin) < 256)){
            fprintf(fp,"P5\n");
            fprintf(fp,"%d %d\n",I->nx,I->ny);
            fprintf(fp,"%d\n",Imax);

            data = AllocUCharArray(I->nx*I->ny);
            for (y=0; y < I->ny; y++)
                for (x=0; x < I->nx; x++)
                    data[x+y*I->nx] = (uchar) I->val[y][x]-Imin;

            fwrite(data,sizeof(uchar),I->nx*I->ny,fp);
            free(data);
        }else{
            fprintf(fp,"P2\n");
            fprintf(fp,"%d %d\n",I->nx,I->ny);
            fprintf(fp,"%d\n",Imax-Imin);

            for (y=0; y < I->ny; y++){
                for (x=0; x < I->nx; x++)
                    fprintf(fp,"%d ",I->val[y][x]-Imin);
                fprintf(fp,"\n");
            }
        }
        fclose(fp);

    }else{
        Error(MSG2,"WriteGrayImage");
    }
}

ColorImage *CreateColorImage(int nx, int ny)
{
    ColorImage *I=(ColorImage *)calloc(1,sizeof(ColorImage));
    int y;

    I->nx = nx;
    I->ny = ny;
    I->dx = 1.0;
    I->dy = 1.0;
    sprintf(I->unid,"mm");

    I->cor = (Cor **)calloc(ny,sizeof(Cor *));
    if (I->cor == NULL)
        Error(MSG1,"CreateColorImage");
    else{
        for (y=0; y < I->ny; y++){
            I->cor[y] = (Cor *)calloc(nx,sizeof(Cor));
            if (I->cor[y] == NULL)
                Error(MSG1,"CreateColorImage");
        }
    }
    return(I);
}

ColorImage *ReadColorImage(char *filename)
{
    FILE *fp=NULL;
    char type[10];
    int  x,y,nx,ny,Imax;
    ColorImage *I=NULL;
    char remarks[256];

    fp = fopen(filename,"r");
    if (fp != NULL) {
        fscanf(fp,"%s",type);
        NCFgets(remarks,255,fp);

        if (strcmp(type,"P6")==0){
            fscanf(fp,"%d",&nx);
            fscanf(fp,"%d\n",&ny);
            I = CreateColorImage(nx,ny);
            fscanf(fp,"%d\n",&Imax);
            fgetc(fp);
            for (y=0; y < ny; y++)
                for (x=0; x < nx; x++){
                    I->cor[y][x].val[RED]=(int)fgetc(fp);
                    I->cor[y][x].val[GREEN]=(int)fgetc(fp);
                    I->cor[y][x].val[BLUE]=(int)fgetc(fp);
                }
        }else{
            Error("Image type invalid","ReadColormage");
        }

        fclose(fp);
    }else{
        Error(MSG2,"ReadColorImage");
    }

    return(I);
}

void WriteColorImage(ColorImage *I, char *filename)
{
    FILE *fp=NULL;
    int  x,y;

    fp = fopen(filename,"w");
    if (fp != NULL) {
        fprintf(fp,"P6\n");
        fprintf(fp,"%d %d\n",I->nx,I->ny);
        fprintf(fp,"255\n");

        for (y=0; y < I->ny; y++)
            for (x=0; x < I->nx; x++){
                fputc((uchar)I->cor[y][x].val[RED],fp);
                fputc((uchar)I->cor[y][x].val[GREEN],fp);
                fputc((uchar)I->cor[y][x].val[BLUE],fp);
            }
        fclose(fp);
    }else{
        Error(MSG2,"WriteColorImage");
    }

}

void DestroyColorImage(ColorImage **I)
{
    int y;

    if ((*I) != NULL) {
        for (y=0; y < (*I)->ny; y++)
            free((*I)->cor[y]);
        free((*I)->cor);
        free(*I);
        *I = NULL;
    }
}

MedicalImage *CreateMedicalImage(int nx, int ny, int nz)
{
    MedicalImage *I=(MedicalImage *)calloc(1,sizeof(MedicalImage));
    int y,z;

    I->nx = nx;
    I->ny = ny;
    I->nz = nz;
    I->dx = 1.0;
    I->dy = 1.0;
    I->dz = 1.0;
    sprintf(I->unid,"mm");

    I->val = (int ***)calloc(nz,sizeof(int **));
    if (I->val == NULL)
        Error(MSG1,"CreateMedicalImage");
    else{
        for (z=0; z < I->nz; z++){
            I->val[z] = (int **)calloc(ny,sizeof(int *));
            if (I->val[z] == NULL){
                Error(MSG1,"CreateMedicalImage");
            }
        }
        for (z=0; z < I->nz; z++)
            for (y=0; y < I->ny; y++){
                I->val[z][y] = (int *)calloc(nx,sizeof(int));
                if (I->val[z][y] == NULL)
                    Error(MSG1,"CreateMedicalImage");
            }
    }

    return(I);
}

void DestroyMedicalImage(MedicalImage **I)
{
    int y,z;

    if ((*I) != NULL) {
        for (z=0; z < (*I)->nz; z++) {
            for (y=0; y < (*I)->ny; y++)
                free((*I)->val[z][y]);
            free((*I)->val[z]);
        }
        free(*I);
        *I = NULL;
    }
}

MedicalImage *ReadMedicalImage(char *filename)
{
    FILE *fp=NULL;
    char type[10];
    uchar *data8=NULL;
    ushort *data16=NULL;
    int  x,y,z,nx,ny,nz,nbits;
    float dx,dy,dz;
    dx = dy = dz = 0;
    nx = ny = nz = 0;
    nbits = 0;
    MedicalImage *I=NULL;
    char remarks[256];

    fp = fopen(filename,"rb");
    if (fp != NULL) {
        fscanf(fp,"%s",type);
        NCFgets(remarks,255,fp);

        if (strcmp(type,"SCN")==0){
            fscanf(fp,"%d",&nx);
            fscanf(fp,"%d",&ny);
            fscanf(fp,"%d\n",&nz);

            I = CreateMedicalImage(nx,ny,nz);
            fscanf(fp,"%f",&I->dx);
            fscanf(fp,"%f",&I->dy);
            fscanf(fp,"%f\n",&I->dz);
            fscanf(fp,"%d\n",&nbits); // 8 ou 16 bits

            //fprintf(stderr,"%s\n %d %d %d\n %f %f %f\n %d\n",filename,I->nx,I->ny,I->nz,I->dx,I->dy,I->dz,nbits);



            switch(nbits) {

            case 8:
                data8 = AllocUCharArray(nx*ny*nz);
                fread(data8,sizeof(uchar),nx*ny*nz,fp);
                I->maxValue = 0;
                for (z=0; z < nz; z++)
                    for (y=0; y < ny; y++)
                        for (x=0; x < nx; x++){
                            I->val[z][y][x] = (int) data8[x+y*nx+z*nx*ny];
                            if(I->maxValue < I->val[z][y][x]){
                                I->maxValue = I->val[z][y][x];
                            }
                        }

                free(data8);
                I->nbits = 8;
                break;

            case 16:

                data16 = AllocUShortArray(nx*ny*nz);
                fread(data16,sizeof(ushort),nx*ny*nz,fp);
                I->maxValue = 0;
                for (z=0; z < nz; z++)
                    for (y=0; y < ny; y++)
                        for (x=0; x < nx; x++){
                            I->val[z][y][x] = (int) data16[x+y*nx+z*nx*ny];
                            if(I->maxValue < I->val[z][y][x]){
                                I->maxValue = I->val[z][y][x];
                            }
                        }
                if(I->maxValue > 32767){
                    I->nbits = 16;
                }else if(I->maxValue > 16383){
                    I->nbits = 15;
                }else if(I->maxValue > 8191){
                    I->nbits = 14;
                }else if(I->maxValue > 4095){
                    I->nbits = 13;
                }else if(I->maxValue > 2047){
                    I->nbits = 12;
                }else if(I->maxValue > 1023){
                    I->nbits = 11;
                }else if(I->maxValue > 511){
                    I->nbits = 10;
                }else if(I->maxValue > 255){
                    I->nbits = 9;
                }else{
                    I->nbits = 8;
                }

                free(data16);
                break;

            default:
                Error("Invalid number of bits","ReadMedicalImage");
            }
            fclose(fp);
        }else{
            Error("Invalid image type","ReadMedicalImage");
        }
    }else{
        Error(MSG2,"ReadMedicalImage");
    }



    return(I);
}

void WriteMedicalImage(MedicalImage *I, char *filename)
{
    FILE *fp=NULL;
    uchar *data8=NULL;
    ushort *data16=NULL;
    int  x,y,z,Imax;

    Imax = INT_MIN;
    for (z=0; z < I->nz; z++)
        for (y=0; y < I->ny; y++)
            for (x=0; x < I->nx; x++)
                if (I->val[z][y][x] > Imax)
                    Imax = I->val[z][y][x];

    fp = fopen(filename,"w");
    if (fp != NULL) {
        fprintf(fp,"SCN\n");
        fprintf(fp,"%d %d %d\n",I->nx,I->ny,I->nz);
        fprintf(fp,"%f %f %f\n",I->dx,I->dy,I->dz);
        if (Imax < 256){
            fprintf(fp,"8\n");
            data8 = AllocUCharArray(I->nx*I->ny*I->nz);
            for (z=0; z < I->nz; z++)
                for (y=0; y < I->ny; y++)
                    for (x=0; x < I->nx; x++)
                        data8[x+y*I->nx+z*I->nx*I->ny] = (uchar) I->val[z][y][x];

            fwrite(data8,sizeof(uchar),I->nx*I->ny*I->nz,fp);
            free(data8);
        }else{
            fprintf(fp,"16\n");
            data16 = AllocUShortArray(I->nx*I->ny*I->nz);
            for (z=0; z < I->nz; z++)
                for (y=0; y < I->ny; y++)
                    for (x=0; x < I->nx; x++)
                        data16[x+y*I->nx+z*I->nx*I->ny] = (ushort) I->val[z][y][x];

            fwrite(data16,sizeof(ushort),I->nx*I->ny*I->nz,fp);
            free(data16);
        }
        fclose(fp);
    }else{
        Error(MSG2,"WriteMedicalImage");
    }

}

//void writeGrayImagePng(GrayImage *grayImage,int nbits, char *file_name){
//    int width = grayImage->nx;
//    int height = grayImage->ny;


//    png_bytep *row_pointers;
//    if(nbits != 8 && nbits != 16){
//        Error("Invalid number of bits","writePngImage");
//    }
//    int bytesColorSpace = 1;
//    int byteshift = nbits/8;

//    size_t pixel_size = (bytesColorSpace) * byteshift;
//    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
//    for (int y=0; y<height; y++){
//        row_pointers[y] = (png_byte*) malloc(pixel_size*width);
//    }


//    for (int y = 0; y < height; ++y) {
//        png_byte *row = row_pointers[y];
//        for (int x=0; x<width; x++) {

//            png_byte* ptr = &(row[x*byteshift]);
//            ptr[0*byteshift] = grayImage->val[y][x] & 0xFF;//get first byte

//            if(nbits==16) {//in 16bit image, we should store as big endian
//                ptr[1] = ptr[0];
//                ptr[0] = (grayImage->val[y][x]>>8) & 0xFF;//get second byte
//            }
//        }
//    }


//    /* create file */
//    FILE *fp = fopen(file_name, "wb");
//    if (!fp)
//        Error("Internal Error: File %s could not be opened for writing", "writeColorImagePng");

//    /* initialize stuff */
//    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

//    if (!png_ptr)
//        Error("Internal Error: png_create_write_struct failed", "writeColorImagePng");

//    png_infop info_ptr = png_create_info_struct(png_ptr);
//    if (!info_ptr)
//        Error("Internal Error: png_create_info_struct failed", "writeColorImagePng");

//    if (setjmp(png_jmpbuf(png_ptr)))
//        Error("Internal Error: Error during init_io", "writeColorImagePng");

//    png_init_io(png_ptr, fp);


//    /* write header */
//    if (setjmp(png_jmpbuf(png_ptr)))
//        Error("Internal Error: Error during writing header", "writeColorImagePng");


//    png_set_IHDR(png_ptr, info_ptr, width, height,
//                 nbits, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
//                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

//    png_write_info(png_ptr, info_ptr);


//    /* write bytes */
//    if (setjmp(png_jmpbuf(png_ptr)))
//        Error("Internal Error: Error during writing bytes", "writeColorImagePng");

//    png_write_image(png_ptr, row_pointers);


//    /* end write */
//    if (setjmp(png_jmpbuf(png_ptr)))
//        Error("Internal Error: Error during end of write", "writeColorImagePng");

//    png_write_end(png_ptr, NULL);

//    png_destroy_write_struct(&png_ptr, &info_ptr);

//    /* cleanup heap allocation */
//    for (int y=0; y<height; y++)
//        free(row_pointers[y]);
//    free(row_pointers);

//    fclose(fp);
//}


//void writeColorImagePng(ColorImage *colorImage,int nbits, char *file_name){

//    int width = colorImage->nx;
//    int height = colorImage->ny;


//    png_bytep *row_pointers;
//    if(nbits != 8 && nbits != 16){
//        Error("Invalid number of bits","writePngImage");
//    }
//    int bytesColorSpace = 3;
//    int byteshift = nbits/8;

//    size_t pixel_size = (bytesColorSpace) * byteshift;
//    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
//    for (int y=0; y<height; y++){
//        row_pointers[y] = (png_byte*) malloc(pixel_size*width);
//    }


//    for (int y = 0; y < height; ++y) {
//        png_byte *row = row_pointers[y];
//        for (int x=0; x<width; x++) {

//            png_byte* ptr = &(row[x*3*byteshift]);
//            ptr[0*byteshift] = colorImage->cor[y][x].val[0] & 0xFF;//get first byte
//            ptr[1*byteshift] = colorImage->cor[y][x].val[1] & 0xFF;
//            ptr[2*byteshift] = colorImage->cor[y][x].val[2] & 0xFF;

//            if(nbits==16) {//in 16bit image, we should store as big endian
//                ptr[0*byteshift+1] = ptr[0*byteshift];
//                ptr[1*byteshift+1] = ptr[1*byteshift];
//                ptr[2*byteshift+1] = ptr[2*byteshift];

//                ptr[0*byteshift] = ((colorImage->cor[y][x].val[0]>>8) & 0xFF);//get second byte
//                ptr[1*byteshift] = ((colorImage->cor[y][x].val[1]>>8) & 0xFF);
//                ptr[2*byteshift] = ((colorImage->cor[y][x].val[2]>>8) & 0xFF);
//            }
//        }
//    }


//    /* create file */
//    FILE *fp = fopen(file_name, "wb");
//    if (!fp)
//        Error("Internal Error: File %s could not be opened for writing", "writeColorImagePng");

//    /* initialize stuff */
//    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

//    if (!png_ptr)
//        Error("Internal Error: png_create_write_struct failed", "writeColorImagePng");

//    png_infop info_ptr = png_create_info_struct(png_ptr);
//    if (!info_ptr)
//        Error("Internal Error: png_create_info_struct failed", "writeColorImagePng");

//    if (setjmp(png_jmpbuf(png_ptr)))
//        Error("Internal Error: Error during init_io", "writeColorImagePng");

//    png_init_io(png_ptr, fp);


//    /* write header */
//    if (setjmp(png_jmpbuf(png_ptr)))
//        Error("Internal Error: Error during writing header", "writeColorImagePng");


//    png_set_IHDR(png_ptr, info_ptr, width, height,
//                 nbits, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
//                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

//    png_write_info(png_ptr, info_ptr);


//    /* write bytes */
//    if (setjmp(png_jmpbuf(png_ptr))){
//        Error("Internal Error: Error during writing bytes", "writeColorImagePng");
//    }

//    png_write_image(png_ptr, row_pointers);


//    /* end write */
//    if (setjmp(png_jmpbuf(png_ptr)))
//        Error("Internal Error: Error during end of write", "writeColorImagePng");

//    png_write_end(png_ptr, NULL);

//    png_destroy_write_struct(&png_ptr, &info_ptr);

//    /* cleanup heap allocation */
//    for (int y=0; y<height; y++)
//        free(row_pointers[y]);
//    free(row_pointers);

//    fclose(fp);
//}

MyImage *createMyImage(int nx, int ny, int nz){
    MyImage *myImage= (MyImage *)calloc(1,sizeof(MyImage));

    myImage->nx = nx;
    myImage->ny = ny;
    myImage->nz = nz;
    myImage->dx = 1.0;
    myImage->dy = 1.0;
    myImage->dz = 1.0;
    sprintf(myImage->unid,"mm");
    myImage->Pixel = NULL;
    return myImage;
}




