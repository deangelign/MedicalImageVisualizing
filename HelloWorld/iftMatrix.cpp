#include "iftMatrix.h"


/*int getDataTypeId(const char* dataType){
    if( !strcmp(dataType,"i") ){
        return INT;
    }else if( !strcmp(dataType,"l") ){
        return LONG;
    }else if( !strcmp(dataType,"f") ){
        return FLOAT;
    }else if( !strcmp(dataType,"d") ){
        return DOUBLE;
    }else if( !strcmp(dataType,"e") ){
        return LONG_DOUBLE;
    }else{
        return -1;
    }
}

template <typename type1, typename type2>
int getAproprieteDataType(iftMatrix<type1>* matrix, type2 scalar){
    int scalarDataTypeId = getDataTypeId(typeid(scalar).name());
    return (scalarDataTypeId >= matrix->dataTypeId) ? scalarDataTypeId : matrix->dataTypeId;
}

template <typename type1, typename type2>
int getAproprieteDataType(type1  scalar1, type2 scalar2){
    int scalarDataTypeId1 = getDataTypeId(typeid(scalar1).name());
    int scalarDataTypeId2 = getDataTypeId(typeid(scalar2).name());
    return (scalarDataTypeId1 >= scalarDataTypeId2) ? scalarDataTypeId1 : scalarDataTypeId2;
}

template <typename type>
int getAproprieteDataType(int  dataTypeId, type scalar){
    int scalarDataTypeId = getDataTypeId(typeid(scalar).name());
    return (scalarDataTypeId >= dataTypeId) ? scalarDataTypeId : dataTypeId;
}

template <typename T>
iftMatrix<T>* allocateMatrixPointer(int numberRows, int numberCols, T initialValue){
    iftMatrix<T> *matrix = (iftMatrix<T> *)calloc(1,sizeof(iftMatrix<T>));
    matrix->elements = (T*)calloc(numberCols*numberRows,sizeof(T));
    matrix->shifts = (int *)calloc(numberRows,sizeof(int));
    matrix->numberCols = numberCols;
    matrix->numberRows = numberRows;
    matrix->dataTypeId = getDataTypeId(typeid(initialValue).name());
    return matrix;
}

template <typename T>
iftMatrix<T>* allocateAppropriatetMatrixPointer(int numberRows, int numberCols, int dataTypeId){
    iftMatrix<T> *matrix = NULL;
    switch (dataTypeId) {
    case INT:
        matrix = allocateMatrixPointer(numberRows, numberCols, (int)0);
        break;
    case LONG:
        matrix = allocateMatrixPointer(numberRows, numberCols, (long)0);
        break;
    case FLOAT:
        matrix = allocateMatrixPointer(numberRows, numberCols, (float)0);
        break;
    case DOUBLE:
        matrix = allocateMatrixPointer(numberRows, numberCols, (double)0);
        break;
    case LONG_DOUBLE:
        matrix = allocateMatrixPointer(numberRows, numberCols, (long double)0);
        break;
    default:
        break;
    }
    return matrix;

}

template <typename T>
iftMatrix<T>* createMatrix(int numberRows, int numberCols, T initialValue){
    iftMatrix<T> *matrix = allocateMatrixPointer(numberRows,numberCols,initialValue);

    int k=0;
    for (int i = 0; i < numberRows; ++i) {
        matrix->shifts[i] = k;
        for (int j = 0; j < numberCols; ++j) {
            matrix->elements[k] = initialValue;
            ++k;
        }
    }
    return matrix;
}

template <typename T>
iftMatrix<float>* createIdentityMatrix(int numberRows, int numberCols, int dataTypeId){
    iftMatrix<float> *matrix = NULL;
    matrix = allocateMatrixPointer(10,10,(float)0.0);
    //matrix = allocateAppropriatetMatrixPointer(10,10,0);
    //iftMatrix<T> *matrix =  allocateAppropriatetMatrixPointer(numberRows, numberCols, dataTypeId);
    //allocateAppropriatetMatrixPointer(numberRows,numberCols,0);
    int k=0;
    for (int i = 0; i < numberRows; ++i) {
        matrix->shifts[i] = k;
        for (int j = 0; j < numberCols; ++j) {
            matrix->elements[k] = (i == j) ? 1 : 0;
            ++k;
        }
    }
    return matrix;
}

template <typename T, typename P>
iftMatrix<P>* convertMatrixTypes(int converstionType, iftMatrix<T>* matrixSource){
    int numberElements;
    numberElements = matrixSource->numberRows*matrixSource->numberCols;
    iftMatrix<P> *matrixTarget = NULL;
    switch (converstionType){

    case INT2FLOAT:
        matrixTarget = allocateMatrixPointer(matrixSource->numberRows, matrixSource->numberCols, (float)0);
        for (int k=0; k<numberElements; k++) {
            matrixTarget->elements[k] = (float)matrixSource->elements[k];
        }
        break;

    case FLOAT2INT:
        matrixTarget = allocateMatrixPointer(matrixSource->numberRows, matrixSource->numberCols, (int)0);
        for (int k=0; k<numberElements; k++) {
            matrixTarget->elements[k] = (int)matrixSource->elements[k];
        }
        break;

    default:
        break;
    }
    return matrixTarget;
}

template <typename T>
void destroyMatrix(iftMatrix<T>**matrix){
    free((*matrix)->dataType);
    free((*matrix)->shifts);
    free((*matrix)->elements);
    free(matrix);
}

template <typename T,typename P>
void multiplyMatrixByScalar(iftMatrix<T>*matrix, P scalar){
    int n = matrix->numberCols*matrix->numberRows;
    for (int k = 0; k < n; ++k) {
        matrix->elements[k] *= scalar;
    }
}

template <typename Type1,typename Type2, typename Type3>
iftMatrix<Type3>* multiplyMatrixByScalar(iftMatrix<Type1>*matrix, Type2 scalar){
    int dataTypeId = getAproprieteDataType(matrix,scalar);
    int n = matrix->numberCols*matrix->numberRows;
    iftMatrix<Type3>* outputMatrix = NULL;
    outputMatrix = allocateAppropriatetMatrixPointer(matrix->numberRows, matrix->numberCols,dataTypeId);

    for (int k = 0; k < n; ++k) {
        outputMatrix->elements[k] = matrix->elements[k]*scalar;
    }
    return outputMatrix;
}

template <typename T,typename P>
void addMatrixByScalar(iftMatrix<T>*matrix, P scalar){
    int n = matrix->numberCols*matrix->numberRows;
    for (int k = 0; k < n; ++k) {
        matrix->elements[k] += scalar;
    }
}

template <typename T,typename P>
void subtractMatrixByScalar(iftMatrix<T>*matrix, P scalar){
    int n = matrix->numberCols*matrix->numberRows;
    for (int k = 0; k < n; ++k) {
        matrix->elements[k] -= scalar;
    }
}


template <typename T,typename P>
void divideMatrixByScalar(iftMatrix<T>*matrix, P scalar){
    int n = matrix->numberCols*matrix->numberRows;
    for (int k = 0; k < n; ++k) {
        matrix->elements[k] /= scalar;
    }
}

template <typename Type1,typename Type2,typename Type3, typename Type4>
iftMatrix<Type4>* matrixMultiplication(iftMatrix<Type1> *A,iftMatrix<Type2> *B, Type3 alpha, Type3 beta,
                                       int transposeA, int transposeB){
    if(A->numberCols != B->numberRows){
        fprintf(stderr,"Could not perform matrix multiplication");
        return NULL;
    }
    int dataTypeId = (A->dataTypeId>=B->dataTypeId) ? A->dataTypeId : B->dataTypeId;
    dataTypeId = getAproprieteDataType(dataTypeId, alpha);
    iftMatrix<Type3>* C = NULL;
    C = allocateAppropriatetMatrixPointer(A->numberRows, B->numberCols,dataTypeId);

    if(dataTypeId == INT || dataTypeId == LONG || dataTypeId == FLOAT){
        cblas_sgemm(CblasRowMajor,transposeA,transposeB,A->numberRows,B->numberCols,A->numberCols,alpha,
                    A->values,A->numberCols,B->values,B->numberCols,beta,C->elements,B->numberCols);
    }else if(dataTypeId == DOUBLE || dataTypeId == LONG_DOUBLE){
        cblas_dgemm(CblasRowMajor,transposeA,transposeB,A->numberRows,B->numberCols,A->numberCols,alpha,
                    A->values,A->numberCols,B->values,B->numberCols,beta,C->elements,B->numberCols);
    }
}

template <typename Type1,typename Type2,typename Type3, typename Type4>
void matrixMultiplication(iftMatrix<Type1> *A,iftMatrix<Type2> *B, iftMatrix<Type3> *C, Type4 alpha, Type4 beta,
                                       int transposeA, int transposeB){
    if(A->numberCols != B->numberRows){
        fprintf(stderr,"Could not perform matrix multiplication");
        return NULL;
    }
    if(C->dataTypeId == INT || C->dataTypeId == LONG || C->dataTypeId == FLOAT){
        cblas_sgemm(CblasRowMajor,transposeA,transposeB,A->numberRows,B->numberCols,A->numberCols,alpha,
                    A->values,A->numberCols,B->values,B->numberCols,beta,C->elements,B->numberCols);
    }else if(C->dataTypeId == DOUBLE || C->dataTypeId == LONG_DOUBLE){
        cblas_dgemm(CblasRowMajor,transposeA,transposeB,A->numberRows,B->numberCols,A->numberCols,alpha,
                    A->values,A->numberCols,B->values,B->numberCols,beta,C->elements,B->numberCols);
    }
}

template <typename Type1,typename Type2,typename Type3>
void matrixMultiplication(iftMatrix<Type1> *A,iftMatrix<Type2> *B, iftMatrix<Type3> *C){
    if(A->numberCols != B->numberRows){
        fprintf(stderr,"Could not perform matrix multiplication");
        return NULL;
    }
    if(C->dataTypeId == INT || C->dataTypeId == LONG || C->dataTypeId == FLOAT){
        cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,A->numberRows,B->numberCols,A->numberCols,1.0,
                    A->values,A->numberCols,B->values,B->numberCols,0.0,C->elements,B->numberCols);
    }else if(C->dataTypeId == DOUBLE || C->dataTypeId == LONG_DOUBLE){
        cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,A->numberRows,B->numberCols,A->numberCols,1.0,
                    A->values,A->numberCols,B->values,B->numberCols,0.0,C->elements,B->numberCols);
    }
}

template <typename Type1,typename Type2,typename Type3>
iftMatrix<Type3>* matrixMultiplication(iftMatrix<Type1> *A,iftMatrix<Type2> *B){
    if(A->numberCols != B->numberRows){
        fprintf(stderr,"Could not perform matrix multiplication");
        return NULL;
    }
    int dataTypeId = (A->dataTypeId>=B->dataTypeId) ? A->dataTypeId : B->dataTypeId;
    iftMatrix<Type3>* C = NULL;
    C = allocateAppropriatetMatrixPointer(A->numberRows, B->numberCols,dataTypeId);

    if(dataTypeId == INT || dataTypeId == LONG || dataTypeId == FLOAT){
        cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,A->numberRows,B->numberCols,A->numberCols,1.0,
                    A->values,A->numberCols,B->values,B->numberCols,0.0,C->elements,B->numberCols);
    }else if(dataTypeId == DOUBLE || dataTypeId == LONG_DOUBLE){
        cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,A->numberRows,B->numberCols,A->numberCols,1.0,
                    A->values,A->numberCols,B->values,B->numberCols,0.0,C->elements,B->numberCols);
    }
}


template <typename Type1>
void invertMatrix(iftMatrix<Type1> *matrix){
    if(matrix->numberCols != matrix->numberRows){
        fprintf(stderr,"Could not perform matrix inversion");
    }

    int n = matrix->numberRows;
    int *ipiv = (int *)calloc(n+1,sizeof(int));
    int lwork = n * n;
    float *work = (float *)calloc(lwork,sizeof(float));
    int info;

    sgetrf_(&n, &n, matrix->values, &n, ipiv, &info);
    sgetri_(&n, matrix->values, &n, ipiv, work, &lwork, &info);
}

template <typename Type1>
void copyMatrix(iftMatrix<Type1> *matrixSource, iftMatrix<Type1> *matrixTarget){
    int n = matrixSource->numberCols*matrixSource->numberRows;
    for (int k = 0; k < n; ++k) {
        matrixTarget->elements[k] = matrixSource->elements[k];
    }
}


template <typename Type>
iftMatrix<Type> *getSubMatrix(iftMatrix<Type> *matrix, int startRow, int endRow, int startCol, int endCol){
    if(endRow < startRow || endCol < startCol){
        fprintf(stderr,"could not get subMatrix");
        return NULL;
    }
    iftMatrix<Type> *subMatrix = allocateAppropriatetMatrixPointer(endRow-startRow,endCol-startCol,matrix->dataTypeId);
    int k=0;
    int l = matrix->shifts[startRow]+startCol;
    for (int row = startRow; row <= endRow; ++row) {
        for (int col = startCol; col < endCol; ++col) {
            subMatrix->elements[k] = matrix->elements[l];
            ++l;
        }
        l = matrix->shifts[row]+startCol;
    }
    return subMatrix;
}

template <typename Type>
void getPlanarSlice(iftMatrix<Type> *point, iftMatrix<Type> *vector){
    float thetaX;
    float thetaY;
    iftMatrix<Type>* rotationX;
    iftMatrix<Type>* rotationY;
    iftMatrix<Type>* R;

    alignVectorWithZ(vector->elements[0],vector->elements[1],vector->elements[2],&thetaX,&thetaY);
    rotationX = createRotationMatrix(thetaX,'x');
    rotationY = createRotationMatrix(thetaY,'y');
    R = matrixMultiplication(rotationY,rotationX);
    printMatrix(R);
}

template <typename Type1,typename Type2>
void alignVectorWithZ(Type1 x, Type1 y,Type1 z, Type2 *thetaX, Type2 *thetaY){
    if(fabs(z) < 0.0000001 ){
        z = 0.0000001;
    }
    *thetaX = atan(y/z);
    if(z < 0){
        *thetaX += M_PI;
    }
    float z_dash = z/cos(*thetaX);
    *thetaY = -atan(x/z_dash);
}

template <typename Type1>
iftMatrix<Type1>* createRotationMatrix(Type1 angle_rad,char axes){
    iftMatrix<Type1>* rotationMatrix = NULL;
    if(axes == 'x'){
        rotationMatrix = createRotationMatrixInX(angle_rad);
    }else if(axes == 'y'){
        rotationMatrix = createRotationMatrixInY(angle_rad);
    }else if(axes == 'z'){
        rotationMatrix = createRotationMatrixInZ(angle_rad);
    }else{
        //TODO
    }
    return rotationMatrix;
}

template <typename Type1>
iftMatrix<float>* createRotationMatrixInX(Type1 angle_rad){
    iftMatrix<float>* rotationX = createIdentityMatrix(4,4,FLOAT);
    //first row
    rotationX->elements[0] = 1;
    rotationX->elements[1] = 0;
    rotationX->elements[2] = 0;
    rotationX->elements[3] = 0;
    //second row
    rotationX->elements[4] = 0;
    rotationX->elements[5] = cos(angle_rad);
    rotationX->elements[6] = -sin(angle_rad);
    rotationX->elements[7] = 0;
    //third row
    rotationX->elements[8] = 0;
    rotationX->elements[9] = sin(angle_rad);
    rotationX->elements[10] = cos(angle_rad);
    rotationX->elements[11] = 0;
    //fourth row
    rotationX->elements[12] = 0;
    rotationX->elements[13] = 0;
    rotationX->elements[14] = 0;
    rotationX->elements[15] = 1;
    return rotationX;
}

template <typename Type1>
iftMatrix<float>* createRotationMatrixInY(Type1 angle_rad){
    iftMatrix<float>* rotationY = createIdentityMatrix(4,4,FLOAT);
    //first row
    rotationY->elements[0] = cos(angle_rad);
    rotationY->elements[1] = 0;
    rotationY->elements[2] = sin(angle_rad);
    rotationY->elements[3] = 0;
    //second row
    rotationY->elements[4] = 0;
    rotationY->elements[5] = 1;
    rotationY->elements[6] = 0;
    rotationY->elements[7] = 0;
    //third row
    rotationY->elements[8] = -sin(angle_rad);
    rotationY->elements[9] = 0;
    rotationY->elements[10] = cos(angle_rad);
    rotationY->elements[11] = 0;
    //fourth row
    rotationY->elements[12] = 0;
    rotationY->elements[13] = 0;
    rotationY->elements[14] = 0;
    rotationY->elements[15] = 1;
    return rotationY;
}

template <typename Type1>
iftMatrix<float>* createRotationMatrixInZ(Type1 angle_rad){
    iftMatrix<float>* rotationZ = createIdentityMatrix(4,4,FLOAT);
    //first row
    rotationZ->elements[0] = cos(angle_rad);
    rotationZ->elements[1] = -sin(angle_rad);
    rotationZ->elements[2] = 0;
    rotationZ->elements[3] = 0;
    //second row
    rotationZ->elements[4] = sin(angle_rad);
    rotationZ->elements[5] = cos(angle_rad);
    rotationZ->elements[6] = 0;
    rotationZ->elements[7] = 0;
    //third row
    rotationZ->elements[8] = 0;
    rotationZ->elements[9] = 0;
    rotationZ->elements[10] = 1;
    rotationZ->elements[11] = 0;
    //fourth row
    rotationZ->elements[12] = 0;
    rotationZ->elements[13] = 0;
    rotationZ->elements[14] = 0;
    rotationZ->elements[15] = 1;
    return rotationZ;
}

template <typename Type>
void printMatrix(iftMatrix<Type> *matrix){
    int k = 0;
    switch (matrix->dataTypeId) {
    case INT:
        for (int row = 0; row < matrix->numberRows; ++row) {
            for (int col = 0; col < matrix->numberCols; ++col) {
                printf("%d ",matrix->elements[k]);
                ++k;
            }
        }
        break;
    case LONG:
        for (int row = 0; row < matrix->numberRows; ++row) {
            for (int col = 0; col < matrix->numberCols; ++col) {
                printf("%ld ",matrix->elements[k]);
                ++k;
            }
        }
        break;
    case FLOAT:
        for (int row = 0; row < matrix->numberRows; ++row) {
            for (int col = 0; col < matrix->numberCols; ++col) {
                printf("%4.5f ",matrix->elements[k]);
                ++k;
            }
        }
        break;
    case DOUBLE:
        for (int row = 0; row < matrix->numberRows; ++row) {
            for (int col = 0; col < matrix->numberCols; ++col) {
                printf("%4.5lf ",matrix->elements[k]);
                ++k;
            }
        }
        break;
    case LONG_DOUBLE:
        for (int row = 0; row < matrix->numberRows; ++row) {
            for (int col = 0; col < matrix->numberCols; ++col) {
                printf("%4.5lf ",matrix->elements[k]);
                ++k;
            }
        }
        break;
    default:
        break;
    }
}



/*void MatrixMultiplication(Matrix *A,Matrix *B,Matrix *C,char At, char Bt){
    if(At == 'n' && Bt == 'n'){
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,A->numberRows,B->numberCols,A->numberCols,
                    1.0,A->values,A->numberCols,B->values,B->numberCols,0.0,C->values,B->numberCols);
    }else if(At == 's' && Bt == 'n'){
        cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans,A->numberRows,B->numberCols,A->numberCols,
                    1.0,A->values,A->numberCols,B->values,B->numberCols,0.0,C->values,B->numberCols);
    }else if(At == 'n' && Bt == 's'){
        cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans,A->numberRows,B->numberCols,A->numberCols,
                    1.0,A->values,A->numberCols,B->values,B->numberCols,0.0,C->values,B->numberCols);
    }else if(At == 's' && Bt == 's'){
        cblas_sgemm(CblasRowMajor, CblasTrans, CblasTrans,A->numberRows,B->numberCols,A->numberCols,
                    1.0,A->values,A->numberCols,B->values,B->numberCols,0.0,C->values,B->numberCols);
    }

}*/





/*Matrix* createRotationMatrix(float angle_rad,char axes){
    Matrix *rotationMatrix = NULL;


    if(axes == 'x'){

        rotationMatrix = createMatrix(4, 4);

        //first row
        rotationMatrix->values[0] = 1;
        rotationMatrix->values[1] = 0;
        rotationMatrix->values[2] = 0;
        rotationMatrix->values[3] = 0;

        //second row
        rotationMatrix->values[4] = 0;
        rotationMatrix->values[5] = cos(angle_rad);
        rotationMatrix->values[6] = -sin(angle_rad);
        rotationMatrix->values[7] = 0;

        //third row
        rotationMatrix->values[8] = 0;
        rotationMatrix->values[9] = sin(angle_rad);
        rotationMatrix->values[10] = cos(angle_rad);
        rotationMatrix->values[11] = 0;

        //fourth row
        rotationMatrix->values[12] = 0;
        rotationMatrix->values[13] = 0;
        rotationMatrix->values[14] = 0;
        rotationMatrix->values[15] = 1;


    }else if(axes == 'y'){

        rotationMatrix = createMatrix(4, 4);

        //first row
        rotationMatrix->values[0] = cos(angle_rad);
        rotationMatrix->values[1] = 0;
        rotationMatrix->values[2] = sin(angle_rad);
        rotationMatrix->values[3] = 0;

        //second row
        rotationMatrix->values[4] = 0;
        rotationMatrix->values[5] = 1;
        rotationMatrix->values[6] = 0;
        rotationMatrix->values[7] = 0;

        //third row
        rotationMatrix->values[8] = -sin(angle_rad);
        rotationMatrix->values[9] = 0;
        rotationMatrix->values[10] = cos(angle_rad);
        rotationMatrix->values[11] = 0;

        //fourth row
        rotationMatrix->values[12] = 0;
        rotationMatrix->values[13] = 0;
        rotationMatrix->values[14] = 0;
        rotationMatrix->values[15] = 1;

    }else if(axes == 'z'){

        rotationMatrix = createMatrix(4, 4);

        //first row
        rotationMatrix->values[0] = cos(angle_rad);
        rotationMatrix->values[1] = -sin(angle_rad);
        rotationMatrix->values[2] = 0;
        rotationMatrix->values[3] = 0;

        //second row
        rotationMatrix->values[4] = sin(angle_rad);
        rotationMatrix->values[5] = cos(angle_rad);
        rotationMatrix->values[6] = 0;
        rotationMatrix->values[7] = 0;

        //third row
        rotationMatrix->values[8] = 0;
        rotationMatrix->values[9] = 0;
        rotationMatrix->values[10] = 1;
        rotationMatrix->values[11] = 0;

        //fourth row
        rotationMatrix->values[12] = 0;
        rotationMatrix->values[13] = 0;
        rotationMatrix->values[14] = 0;
        rotationMatrix->values[15] = 1;

    }else{
        fprintf(stderr,"Invalid Axes %c in createRotationMatrice function\n",axes);
    }

    return rotationMatrix;

}

void applyTranslation(float x,float y, float z,Matrix *matrix){
    matrix->values[3] += x;
    matrix->values[7] += y;
    matrix->values[11] += z;
}



void MatrixAndVectorMultiplication(Matrix *A,Matrix *B,Matrix *C){
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,A->numberRows,B->numberCols,A->numberCols,
                1,A->values,A->numberCols,B->values,B->numberCols,0,C->values,B->numberCols);
}

void printMatrix(Matrix *matrix){
    int k=0;
    for(int i=0; i<matrix->numberRows; i++){
        for(int j=0; j<matrix->numberCols; j++){
            fprintf(stderr, "%6.3f ",matrix->values[k]);
            k++;
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");
}

void invertMatrix(Matrix *matrix){
    if(matrix->numberCols != matrix->numberRows){
        fprintf(stderr,"Could not perform matrix inversion");
    }

    int n = matrix->numberRows;
    int *ipiv = (int *)calloc(n+1,sizeof(int));
    int lwork = n * n;
    float *work = (float *)calloc(lwork,sizeof(float));
    int info;

    sgetrf_(&n, &n, matrix->values, &n, ipiv, &info);
    sgetri_(&n, matrix->values, &n, ipiv, work, &lwork, &info);
}

void copyMatrix(Matrix *A, Matrix **B){
    if((*B) == NULL){
        (*B) = createMatrix(A->numberRows,A->numberCols);
    }
    if(A->numberCols != (*B)->numberCols || A->numberRows != (*B)->numberRows){
        destroyMatrix(B);
        (*B) = createMatrix(A->numberRows,A->numberCols);
    }
    int k=0;
    for(int i=0; i<A->numberRows; i++){
        for(int j=0; j<A->numberCols; j++){
            (*B)->values[k] = A->values[k];
            k++;
        }
    }
}

void destroyMatrix(Matrix **matrix){
    free((*matrix)->values);
    free(matrix);
}*/



