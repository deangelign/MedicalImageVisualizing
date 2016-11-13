#ifndef MATRIXFEIA_H
#define MATRIXFEIA_H

#include <cblas.h>
#include <cstdio>
#include <typeinfo>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <image.h>

enum ConverstionTypes { INT2FLOAT=0, FLOAT2INT=1 };
enum primitiveDataTypesId { INT=0, LONG=1, FLOAT=2, DOUBLE=3, LONG_DOUBLE=4  };


extern "C" {
// LU decomoposition of a general matrix
void sgetrf_(int* M, int *N, float* A, int* lda, int* IPIV, int* INFO);

// generate inverse of a matrix given its LU decomposition
void sgetri_(int* N, float* A, int* lda, int* IPIV, float* WORK, int* lwork, int* INFO);
}

template <typename T>
struct iftMatrix{
    T* elements;
    int numberRows;//magnitudeSquared
    int numberCols;
    int dataTypeId;
    int* shifts;
} ;

int getDataTypeId(const char* dataType){
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


iftMatrix<float>* createIdentityMatrix(int numberRows, int numberCols, int dataTypeId){
    iftMatrix<float> *matrix = NULL;
    //matrix = allocateMatrixPointer(10,10,(float)0.0);
    //matrix = allocateAppropriatetMatrixPointer(10,10,0);
    matrix =  allocateMatrixPointer(numberRows, numberCols, (float)0);
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

    free((*matrix)->shifts);
    free((*matrix)->elements);
    free(*matrix);
    *matrix = NULL;
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

template <typename T>
void matrixAddition(iftMatrix<T> *A,iftMatrix<T> *B){
    int k=0;
    for (int i = 0; i < A->numberRows; ++i) {
        for (int j = 0; j < A->numberCols; ++j) {
            A->elements[k] = A->elements[k] + B->elements[k];
            ++k;
        }
    }
}

iftMatrix<float>* matrixSubtraction(iftMatrix<float> *A,iftMatrix<float> *B){

    iftMatrix<float>* C = createMatrix(A->numberRows,A->numberCols,(float) 0);
    int k=0;
    for (int i = 0; i < A->numberRows; ++i) {
        for (int j = 0; j < A->numberCols; ++j) {
            C->elements[k] = A->elements[k] - B->elements[k];
            ++k;
        }
    }
    return C;
}

template <typename T>
void matrixSubtractionInPlace(iftMatrix<T> *A,iftMatrix<T> *B){

    int k=0;
    for (int i = 0; i < A->numberRows; ++i) {
        for (int j = 0; j < A->numberCols; ++j) {
            A->elements[k] = A->elements[k] - B->elements[k];
            ++k;
        }
    }
}

template <typename T>
void matrixSubtractVector(iftMatrix<T> *A,iftMatrix<T> *vec){

    int k=0;
    for (int i = 0; i < A->numberRows; ++i) {
        for (int j = 0; j < A->numberCols; ++j) {
            A->elements[k] = A->elements[k] - vec->elements[j];
            ++k;
        }
    }
}

template <typename T>
void matrixSubtractVector2(iftMatrix<T> *A,iftMatrix<T> *vec){

    int k=0;
    for (int i = 0; i < A->numberRows; ++i) {
        for (int j = 0; j < A->numberCols; ++j) {
            A->elements[k] = vec->elements[j] - A->elements[k];
            ++k;
        }
    }
}

iftMatrix<float>* matrixMultiplicationF(iftMatrix<float> *A,iftMatrix<float> *B, float alpha, float beta,
                                        CBLAS_TRANSPOSE transposeA, CBLAS_TRANSPOSE transposeB){



    //    if(A->numberCols != B->numberRows){
    //        fprintf(stderr,"Could not perform matrix multiplication");
    //        return NULL;
    //    }
    int dataTypeId = (A->dataTypeId>=B->dataTypeId) ? A->dataTypeId : B->dataTypeId;
    iftMatrix<float>* C = NULL;

    if(transposeA == CblasNoTrans && transposeB == CblasNoTrans){
        C = allocateMatrixPointer(A->numberRows, B->numberCols,(float)0);
    }else if(transposeA == CblasTrans && transposeB == CblasNoTrans){
        C = allocateMatrixPointer(A->numberCols, B->numberCols,(float)0);
    }else if(transposeA == CblasNoTrans && transposeB == CblasTrans){
        C = allocateMatrixPointer(A->numberRows, B->numberRows,(float)0);
    }else if(transposeA == CblasTrans && transposeB == CblasTrans){
        C = allocateMatrixPointer(A->numberCols, B->numberRows,(float)0);
    }


    if(dataTypeId == INT || dataTypeId == LONG || dataTypeId == FLOAT){
        cblas_sgemm(CblasRowMajor,transposeA,transposeB,A->numberRows,B->numberCols,A->numberCols,alpha,
                    A->elements,A->numberCols,B->elements,B->numberCols,beta,C->elements,B->numberCols);
    }
    return C;
}

iftMatrix<float>* matrixMultiplicationF_inPlace(iftMatrix<float> *A,iftMatrix<float> *B, iftMatrix<float> *C,float alpha, float beta,
                                        CBLAS_TRANSPOSE transposeA, CBLAS_TRANSPOSE transposeB){



    //    if(A->numberCols != B->numberRows){
    //        fprintf(stderr,"Could not perform matrix multiplication");
    //        return NULL;
    //    }
    int dataTypeId = (A->dataTypeId>=B->dataTypeId) ? A->dataTypeId : B->dataTypeId;

    if(dataTypeId == INT || dataTypeId == LONG || dataTypeId == FLOAT){
        cblas_sgemm(CblasRowMajor,transposeA,transposeB,A->numberRows,B->numberCols,A->numberCols,alpha,
                    A->elements,A->numberCols,B->elements,B->numberCols,beta,C->elements,B->numberCols);
    }
    return C;
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
iftMatrix<Type1>* matrixMultiplication(iftMatrix<Type1> *A,iftMatrix<Type1> *B){
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

iftMatrix<float>* matrixMultiplicationF(iftMatrix<float> *A,iftMatrix<float> *B){
    if(A->numberCols != B->numberRows){
        fprintf(stderr,"Could not perform matrix multiplication");
        return NULL;
    }
    int dataTypeId = (A->dataTypeId>=B->dataTypeId) ? A->dataTypeId : B->dataTypeId;
    iftMatrix<float>* C = NULL;
    C = allocateMatrixPointer(A->numberRows, B->numberCols,(float)0);

    if(dataTypeId == INT || dataTypeId == LONG || dataTypeId == FLOAT){
        cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,A->numberRows,B->numberCols,A->numberCols,1.0,
                    A->elements,A->numberCols,B->elements,B->numberCols,0.0,C->elements,B->numberCols);
    }
    return C;
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

    sgetrf_(&n, &n, matrix->elements, &n, ipiv, &info);
    sgetri_(&n, matrix->elements, &n, ipiv, work, &lwork, &info);
}

template <typename Type1>
void copyMatrixInplace(iftMatrix<Type1> *matrixSource, iftMatrix<Type1> *matrixTarget){
    int n = matrixSource->numberCols*matrixSource->numberRows;
    for (int k = 0; k < n; ++k) {
        matrixTarget->elements[k] = matrixSource->elements[k];
    }
}

template <typename Type1>
iftMatrix<Type1>* copyMatrix(iftMatrix<Type1> *matrixSource){
    iftMatrix<Type1> *matrixTarget = allocateMatrixPointer(matrixSource->numberRows,matrixSource->numberCols,(float)0);
    int n = matrixSource->numberCols*matrixSource->numberRows;
    for (int k = 0; k < n; ++k) {
        matrixTarget->elements[k] = matrixSource->elements[k];
    }
    return matrixTarget;
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

template <typename Type1>
iftMatrix<Type1>* createRotationMatrixInX(Type1 angle_rad){
    iftMatrix<Type1>* rotationX = createIdentityMatrix(4,4,FLOAT);
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
iftMatrix<Type1>* createRotationMatrixInY(Type1 angle_rad){
    iftMatrix<Type1>* rotationY = createIdentityMatrix(4,4,FLOAT);
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
iftMatrix<Type1>* createRotationMatrixInZ(Type1 angle_rad){
    iftMatrix<Type1>* rotationZ = createIdentityMatrix(4,4,FLOAT);
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
iftMatrix<Type>* createRotationMatrix(Type angle_rad,char axes){
    iftMatrix<Type>* rotationMatrix = NULL;
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

void alignVectorWithZF(float x, float y,float z, float *thetaX, float *thetaY){
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



template <typename Type>
void printMatrix(iftMatrix<Type> *matrix){
    int k = 0;

    switch (matrix->dataTypeId) {
    case INT:
        for (int row = 0; row < matrix->numberRows; ++row) {
            for (int col = 0; col < matrix->numberCols; ++col) {
                fprintf(stderr,"%d ",matrix->elements[k]);
                ++k;
            }
            fprintf(stderr,"\n");
        }
        fprintf(stderr,"\n");
        break;
    case LONG:
        for (int row = 0; row < matrix->numberRows; ++row) {
            for (int col = 0; col < matrix->numberCols; ++col) {
                fprintf(stderr,"%ld ",matrix->elements[k]);
                ++k;
            }
            fprintf(stderr,"\n");
        }
        fprintf(stderr,"\n");
        break;
    case FLOAT:
        for (int row = 0; row < matrix->numberRows; ++row) {
            for (int col = 0; col < matrix->numberCols; ++col) {
                fprintf(stderr,"%4.5f ",matrix->elements[k]);
                ++k;
            }
            fprintf(stderr,"\n");
        }
        fprintf(stderr,"\n");
        break;
    case DOUBLE:
        for (int row = 0; row < matrix->numberRows; ++row) {
            for (int col = 0; col < matrix->numberCols; ++col) {
                fprintf(stderr,"%4.5lf ",matrix->elements[k]);
                ++k;
            }
        }
        fprintf(stderr,"\n");
        break;
    case LONG_DOUBLE:
        for (int row = 0; row < matrix->numberRows; ++row) {
            for (int col = 0; col < matrix->numberCols; ++col) {
                fprintf(stderr,"%4.5lf ",matrix->elements[k]);
                ++k;
            }
            fprintf(stderr,"\n");
        }
        fprintf(stderr,"\n");
        break;
    default:
        break;
    }
}


float bilinearInterpolation(float x,float y,int fixedz, MedicalImage *image3D){

    int xfloor = x;//implicit casting faster than explicit casting
    //int xfloor = floor(x);
    int xceil = xfloor+1;
    int yfloor = y;//implicit casting faster than explicit casting
    //int yfloor = floor(y);
    int yceil = yfloor+1;

    float p12, p34, p;
    p12 = (x-(float)xfloor)*image3D->val[fixedz][yfloor][xceil];
    p12 += ((float)xceil-x)*image3D->val[fixedz][yfloor][xfloor];

    p34 = (x-(float)xfloor)*image3D->val[fixedz][yceil][xceil];
    p34 += ((float)xceil-x)*image3D->val[fixedz][yceil][xfloor];

    p = ((y-yfloor)*p34) + ((yceil-y)*p12);
    return p;
}


float TrilinearInterpolation(float x,float y,float z, MedicalImage *image3D){

    int zfloor = z;//implicit casting faster than explicit casting
    //int zfloor = floor(z);
    int zceil = zfloor+1;
    float Ip=-1;


    float zFloorBright = bilinearInterpolation(x,y,zfloor,image3D);
    float zCeilBright = bilinearInterpolation(x,y,zceil,image3D);
    Ip = ((z-zfloor)*zCeilBright)+((zceil-z)*zFloorBright);

    return Ip;
}



float computeDiogonal(float nx, float ny, float nz){
    return sqrt((nx*nx) + (ny*ny) + (nz*nz));
}

void myDDAVersion(float x1, float y1, float x2, float y2, GrayImage* grayImage,
                  int value){
    float eplison = 0.0001;
    if(fabs(x2-x1) < eplison){
        x1 += eplison;
    }
    if(fabs(y2-y1) < eplison){
        y1 += eplison;
    }
    float slope = (y2-y1)/(x2-x1);
    float b = y1 - (slope*x1);
    if(fabs(x2-x1) > fabs(y2-y1)){
        //eq y = ax + b
        int x_int;
        int xFinal_int;
        if(x1<x2){
            x_int = (int)x1;
            xFinal_int = (int)x2;
        }else{
            x_int = (int)x2;
            xFinal_int = (int)x1;
        }

        int y_int;
        for (; x_int < xFinal_int; x_int++) {
            y_int = (slope*x_int)+b;
            if(y_int < grayImage->ny && x_int < grayImage->nx){
                if(y_int >= 0 && x_int > 0){
                    grayImage->val[y_int][x_int] = value;
                }
            }
        }
    }else{
        //eq (y-b)/a = x
        int y_int;
        int yFinal_int;
        if(y1 < y2){
            y_int = (int)y1;
            yFinal_int = (int)y2;
        }else{
            y_int = (int)y2;
            yFinal_int = (int)y1;
        }

        int x_int;
        for (; y_int < yFinal_int; y_int++) {
            x_int = (y_int-b)/slope;
            if(y_int < grayImage->ny && x_int < grayImage->nx){
                if(y_int >= 0 && x_int > 0){
                    grayImage->val[y_int][x_int] = value;
                }
            }
        }
    }
}


void drawInterWireFrame(iftMatrix<float> *transformationMatrix, GrayImage* grayImage, MedicalImage* image3D,
                        float zFront,float zBack,float yFront,float yBack,float xFront,float xBack, int value){
    iftMatrix<float>*viewVectors = createMatrix(6,4,(float)0);
    iftMatrix<float>*normalViewPlaneVector = createMatrix(4,1,(float)0);
    //x view
    viewVectors->elements[0] = 1;
    viewVectors->elements[4] = -1;
    //y view
    viewVectors->elements[9] = 1;
    viewVectors->elements[13] = -1;
    //z view
    viewVectors->elements[18] = 1;
    viewVectors->elements[22] = -1;

    //view plane
    normalViewPlaneVector->elements[2] = -1;

    iftMatrix<float>* rotateViews = matrixMultiplicationF(viewVectors,transformationMatrix, 1.0, 0.0, CblasNoTrans, CblasTrans);
    iftMatrix<float>* innerProductsMatrix = matrixMultiplicationF(rotateViews,normalViewPlaneVector);
    //-z is visible
    if(innerProductsMatrix->elements[5] > 0){
        iftMatrix<float>* facesPoints = createMatrix(4,4,(float)0);
        //(0,0,0,1)
        facesPoints->elements[0] = 0;
        facesPoints->elements[1] = 0;
        facesPoints->elements[2] = zFront;
        facesPoints->elements[3] = 1;
        //(nx,0,0,1)
        facesPoints->elements[4] = image3D->nx;
        facesPoints->elements[5] = 0;
        facesPoints->elements[6] = zFront;
        facesPoints->elements[7] = 1;
        //(0,ny,0,1)
        facesPoints->elements[8] = 0;
        facesPoints->elements[9] = image3D->ny;
        facesPoints->elements[10] = zFront;
        facesPoints->elements[11] = 1;

        //(nx,ny,0,1)
        facesPoints->elements[12] = image3D->nx;
        facesPoints->elements[13] = image3D->ny;
        facesPoints->elements[14] = zFront;
        facesPoints->elements[15] = 1;

        iftMatrix<float>*facesPointsMZOnViewPlane = matrixMultiplicationF(facesPoints,transformationMatrix, 1.0, 0.0, CblasNoTrans, CblasTrans);
        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5], grayImage, value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        destroyMatrix(&facesPointsMZOnViewPlane);
        destroyMatrix(&facesPoints);

    }

    //z is visible
    if(innerProductsMatrix->elements[4] > 0){
        iftMatrix<float>* facesPoints = createMatrix(4,4,(float)0);
        //(0,0,nz,1)
        facesPoints->elements[0] = 0;
        facesPoints->elements[1] = 0;
        facesPoints->elements[2] = zBack;
        facesPoints->elements[3] = 1;
        //(nx,0,nz,1)
        facesPoints->elements[4] = image3D->nx;
        facesPoints->elements[5] = 0;
        facesPoints->elements[6] = zBack;
        facesPoints->elements[7] = 1;
        //(0,ny,nz,1)
        facesPoints->elements[8] = 0;
        facesPoints->elements[9] = image3D->ny;
        facesPoints->elements[10] = zBack;
        facesPoints->elements[11] = 1;
        //(nx,ny,nz,1)
        facesPoints->elements[12] = image3D->nx;
        facesPoints->elements[13] = image3D->ny;
        facesPoints->elements[14] = zBack;
        facesPoints->elements[15] = 1;

        iftMatrix<float>*facesPointsMZOnViewPlane = matrixMultiplicationF(facesPoints,transformationMatrix, 1.0, 0.0, CblasNoTrans, CblasTrans);
        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        destroyMatrix(&facesPointsMZOnViewPlane);
        destroyMatrix(&facesPoints);
    }

    //-y is visible
    if(innerProductsMatrix->elements[3]>0){
        iftMatrix<float>* facesPoints = createMatrix(4,4,(float)0);
        //(0,0,0,1)
        facesPoints->elements[0] = 0;
        facesPoints->elements[1] = yFront;
        facesPoints->elements[2] = 0;
        facesPoints->elements[3] = 1;
        //(nx,0,0,1)
        facesPoints->elements[4] = image3D->nx;
        facesPoints->elements[5] = yFront;
        facesPoints->elements[6] = 0;
        facesPoints->elements[7] = 1;
        //(0,0,nz,1)
        facesPoints->elements[8] = 0;
        facesPoints->elements[9] = yFront;
        facesPoints->elements[10] = image3D->nz;
        facesPoints->elements[11] = 1;

        //(nx,0,nz,1)
        facesPoints->elements[12] = image3D->nx;
        facesPoints->elements[13] = yFront;
        facesPoints->elements[14] = image3D->nz;
        facesPoints->elements[15] = 1;

        iftMatrix<float>*facesPointsMZOnViewPlane = matrixMultiplicationF(facesPoints,transformationMatrix, 1.0, 0.0, CblasNoTrans, CblasTrans);
        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        destroyMatrix(&facesPointsMZOnViewPlane);
        destroyMatrix(&facesPoints);
    }

    //y is visible
    if(innerProductsMatrix->elements[2]>0){
        iftMatrix<float>* facesPoints = createMatrix(4,4,(float)0);
        //(0,ny,0,1)
        facesPoints->elements[0] = 0;
        facesPoints->elements[1] = yBack;
        facesPoints->elements[2] = 0;
        facesPoints->elements[3] = 1;
        //(nx,ny,0,1)
        facesPoints->elements[4] = image3D->nx;
        facesPoints->elements[5] = yBack;
        facesPoints->elements[6] = 0;
        facesPoints->elements[7] = 1;
        //(0,ny,nz,1)
        facesPoints->elements[8] = 0;
        facesPoints->elements[9] = yBack;
        facesPoints->elements[10] = image3D->nz;
        facesPoints->elements[11] = 1;

        //(nx,ny,nz,1)
        facesPoints->elements[12] = image3D->nx;
        facesPoints->elements[13] = yBack;
        facesPoints->elements[14] = image3D->nz;
        facesPoints->elements[15] = 1;

        iftMatrix<float>*facesPointsMZOnViewPlane = matrixMultiplicationF(facesPoints,transformationMatrix, 1.0, 0.0, CblasNoTrans, CblasTrans);
        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        destroyMatrix(&facesPointsMZOnViewPlane);
        destroyMatrix(&facesPoints);
    }

    //-x is visible
    if(innerProductsMatrix->elements[1]>0){
        iftMatrix<float>* facesPoints = createMatrix(4,4,(float)0);
        //(0,0,0,1)
        facesPoints->elements[0] = xFront;
        facesPoints->elements[1] = 0;
        facesPoints->elements[2] = 0;
        facesPoints->elements[3] = 1;
        //(0,ny,0,1)
        facesPoints->elements[4] = xFront;
        facesPoints->elements[5] = image3D->ny;
        facesPoints->elements[6] = 0;
        facesPoints->elements[7] = 1;
        //(0,0,nz,1)
        facesPoints->elements[8] = xFront;
        facesPoints->elements[9] = 0;
        facesPoints->elements[10] = image3D->nz;
        facesPoints->elements[11] = 1;

        //(0,ny,nz,1)
        facesPoints->elements[12] = xFront;
        facesPoints->elements[13] = image3D->ny;
        facesPoints->elements[14] = image3D->nz;
        facesPoints->elements[15] = 1;

        iftMatrix<float>*facesPointsMZOnViewPlane = matrixMultiplicationF(facesPoints,transformationMatrix, 1.0, 0.0, CblasNoTrans, CblasTrans);
        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        destroyMatrix(&facesPointsMZOnViewPlane);
        destroyMatrix(&facesPoints);
    }

    //x is visible
    if(innerProductsMatrix->elements[0]>0){
        iftMatrix<float>* facesPoints = createMatrix(4,4,(float)0);
        //(nx,ny,0,1)
        facesPoints->elements[0] = xBack;
        facesPoints->elements[1] = 0;
        facesPoints->elements[2] = 0;
        facesPoints->elements[3] = 1;
        //(nx,ny,0,1)
        facesPoints->elements[4] = xBack;
        facesPoints->elements[5] = image3D->ny;
        facesPoints->elements[6] = 0;
        facesPoints->elements[7] = 1;
        //(nx,0,nz,1)
        facesPoints->elements[8] = xBack;
        facesPoints->elements[9] = 0;
        facesPoints->elements[10] = image3D->nz;
        facesPoints->elements[11] = 1;

        //(nx,ny,nz,1)
        facesPoints->elements[12] = xBack;
        facesPoints->elements[13] = image3D->ny;
        facesPoints->elements[14] = image3D->nz;
        facesPoints->elements[15] = 1;

        iftMatrix<float>*facesPointsMZOnViewPlane = matrixMultiplicationF(facesPoints,transformationMatrix, 1.0, 0.0, CblasNoTrans, CblasTrans);
        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        destroyMatrix(&facesPointsMZOnViewPlane);
        destroyMatrix(&facesPoints);
    }



    destroyMatrix(&viewVectors);
    destroyMatrix(&normalViewPlaneVector);
    destroyMatrix(&rotateViews);
    destroyMatrix(&innerProductsMatrix);

}

void drawWireFrame(iftMatrix<float> *transformationMatrix, GrayImage* grayImage, MedicalImage* image3D,
                   int value){
    iftMatrix<float>*viewVectors = createMatrix(6,4,(float)0);
    iftMatrix<float>*normalViewPlaneVector = createMatrix(4,1,(float)0);
    //x view
    viewVectors->elements[0] = 1;
    viewVectors->elements[4] = -1;
    //y view
    viewVectors->elements[9] = 1;
    viewVectors->elements[13] = -1;
    //z view
    viewVectors->elements[18] = 1;
    viewVectors->elements[22] = -1;

    //view plane
    normalViewPlaneVector->elements[2] = -1;

    iftMatrix<float>* rotateViews = matrixMultiplicationF(viewVectors,transformationMatrix, 1.0, 0.0, CblasNoTrans, CblasTrans);
    iftMatrix<float>* innerProductsMatrix = matrixMultiplicationF(rotateViews,normalViewPlaneVector);
    //-z is visible
    if(innerProductsMatrix->elements[5] > 0){
        iftMatrix<float>* facesPoints = createMatrix(4,4,(float)0);
        //(0,0,0,1)
        facesPoints->elements[0] = 0;
        facesPoints->elements[1] = 0;
        facesPoints->elements[2] = 0;
        facesPoints->elements[3] = 1;
        //(nx,0,0,1)
        facesPoints->elements[4] = image3D->nx;
        facesPoints->elements[5] = 0;
        facesPoints->elements[6] = 0;
        facesPoints->elements[7] = 1;
        //(0,ny,0,1)
        facesPoints->elements[8] = 0;
        facesPoints->elements[9] = image3D->ny;
        facesPoints->elements[10] = 0;
        facesPoints->elements[11] = 1;

        //(nx,ny,0,1)
        facesPoints->elements[12] = image3D->nx;
        facesPoints->elements[13] = image3D->ny;
        facesPoints->elements[14] = 0;
        facesPoints->elements[15] = 1;

        iftMatrix<float>*facesPointsMZOnViewPlane = matrixMultiplicationF(facesPoints,transformationMatrix, 1.0, 0.0, CblasNoTrans, CblasTrans);
        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        destroyMatrix(&facesPointsMZOnViewPlane);
        destroyMatrix(&facesPoints);

    }

    //z is visible
    if(innerProductsMatrix->elements[4] > 0){
        iftMatrix<float>* facesPoints = createMatrix(4,4,(float)0);
        //(0,0,nz,1)
        facesPoints->elements[0] = 0;
        facesPoints->elements[1] = 0;
        facesPoints->elements[2] = image3D->nz;
        facesPoints->elements[3] = 1;
        //(nx,0,nz,1)
        facesPoints->elements[4] = image3D->nx;
        facesPoints->elements[5] = 0;
        facesPoints->elements[6] = image3D->nz;
        facesPoints->elements[7] = 1;
        //(0,ny,nz,1)
        facesPoints->elements[8] = 0;
        facesPoints->elements[9] = image3D->ny;
        facesPoints->elements[10] = image3D->nz;
        facesPoints->elements[11] = 1;
        //(nx,ny,nz,1)
        facesPoints->elements[12] = image3D->nx;
        facesPoints->elements[13] = image3D->ny;
        facesPoints->elements[14] = image3D->nz;
        facesPoints->elements[15] = 1;

        iftMatrix<float>*facesPointsMZOnViewPlane = matrixMultiplicationF(facesPoints,transformationMatrix, 1.0, 0.0, CblasNoTrans, CblasTrans);
        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        destroyMatrix(&facesPointsMZOnViewPlane);
        destroyMatrix(&facesPoints);
    }

    //-y is visible
    if(innerProductsMatrix->elements[3]>0){
        iftMatrix<float>* facesPoints = createMatrix(4,4,(float)0);
        //(0,0,0,1)
        facesPoints->elements[0] = 0;
        facesPoints->elements[1] = 0;
        facesPoints->elements[2] = 0;
        facesPoints->elements[3] = 1;
        //(nx,0,0,1)
        facesPoints->elements[4] = image3D->nx;
        facesPoints->elements[5] = 0;
        facesPoints->elements[6] = 0;
        facesPoints->elements[7] = 1;
        //(0,0,nz,1)
        facesPoints->elements[8] = 0;
        facesPoints->elements[9] = 0;
        facesPoints->elements[10] = image3D->nz;
        facesPoints->elements[11] = 1;

        //(nx,0,nz,1)
        facesPoints->elements[12] = image3D->nx;
        facesPoints->elements[13] = 0;
        facesPoints->elements[14] = image3D->nz;
        facesPoints->elements[15] = 1;

        iftMatrix<float>*facesPointsMZOnViewPlane = matrixMultiplicationF(facesPoints,transformationMatrix, 1.0, 0.0, CblasNoTrans, CblasTrans);
        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        destroyMatrix(&facesPointsMZOnViewPlane);
        destroyMatrix(&facesPoints);
    }

    //y is visible
    if(innerProductsMatrix->elements[2]>0){
        iftMatrix<float>* facesPoints = createMatrix(4,4,(float)0);
        //(0,ny,0,1)
        facesPoints->elements[0] = 0;
        facesPoints->elements[1] = image3D->ny;
        facesPoints->elements[2] = 0;
        facesPoints->elements[3] = 1;
        //(nx,ny,0,1)
        facesPoints->elements[4] = image3D->nx;
        facesPoints->elements[5] = image3D->ny;
        facesPoints->elements[6] = 0;
        facesPoints->elements[7] = 1;
        //(0,ny,nz,1)
        facesPoints->elements[8] = 0;
        facesPoints->elements[9] = image3D->ny;
        facesPoints->elements[10] = image3D->nz;
        facesPoints->elements[11] = 1;

        //(nx,ny,nz,1)
        facesPoints->elements[12] = image3D->nx;
        facesPoints->elements[13] = image3D->ny;
        facesPoints->elements[14] = image3D->nz;
        facesPoints->elements[15] = 1;

        iftMatrix<float>*facesPointsMZOnViewPlane = matrixMultiplicationF(facesPoints,transformationMatrix, 1.0, 0.0, CblasNoTrans, CblasTrans);
        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        destroyMatrix(&facesPointsMZOnViewPlane);
        destroyMatrix(&facesPoints);
    }

    //-x is visible
    if(innerProductsMatrix->elements[1]>0){
        iftMatrix<float>* facesPoints = createMatrix(4,4,(float)0);
        //(0,0,0,1)
        facesPoints->elements[0] = 0;
        facesPoints->elements[1] = 0;
        facesPoints->elements[2] = 0;
        facesPoints->elements[3] = 1;
        //(0,ny,0,1)
        facesPoints->elements[4] = 0;
        facesPoints->elements[5] = image3D->ny;
        facesPoints->elements[6] = 0;
        facesPoints->elements[7] = 1;
        //(0,0,nz,1)
        facesPoints->elements[8] = 0;
        facesPoints->elements[9] = 0;
        facesPoints->elements[10] = image3D->nz;
        facesPoints->elements[11] = 1;

        //(0,ny,nz,1)
        facesPoints->elements[12] = 0;
        facesPoints->elements[13] = image3D->ny;
        facesPoints->elements[14] = image3D->nz;
        facesPoints->elements[15] = 1;

        iftMatrix<float>*facesPointsMZOnViewPlane = matrixMultiplicationF(facesPoints,transformationMatrix, 1.0, 0.0, CblasNoTrans, CblasTrans);
        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        destroyMatrix(&facesPointsMZOnViewPlane);
        destroyMatrix(&facesPoints);
    }

    //x is visible
    if(innerProductsMatrix->elements[0]>0){
        iftMatrix<float>* facesPoints = createMatrix(4,4,(float)0);
        //(nx,ny,0,1)
        facesPoints->elements[0] = image3D->nx;
        facesPoints->elements[1] = 0;
        facesPoints->elements[2] = 0;
        facesPoints->elements[3] = 1;
        //(nx,ny,0,1)
        facesPoints->elements[4] = image3D->nx;
        facesPoints->elements[5] = image3D->ny;
        facesPoints->elements[6] = 0;
        facesPoints->elements[7] = 1;
        //(nx,0,nz,1)
        facesPoints->elements[8] = image3D->nx;
        facesPoints->elements[9] = 0;
        facesPoints->elements[10] = image3D->nz;
        facesPoints->elements[11] = 1;

        //(nx,ny,nz,1)
        facesPoints->elements[12] = image3D->nx;
        facesPoints->elements[13] = image3D->ny;
        facesPoints->elements[14] = image3D->nz;
        facesPoints->elements[15] = 1;

        iftMatrix<float>*facesPointsMZOnViewPlane = matrixMultiplicationF(facesPoints,transformationMatrix, 1.0, 0.0, CblasNoTrans, CblasTrans);
        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[0],
                facesPointsMZOnViewPlane->elements[1],
                facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[4],
                facesPointsMZOnViewPlane->elements[5],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        myDDAVersion(facesPointsMZOnViewPlane->elements[8],
                facesPointsMZOnViewPlane->elements[9],
                facesPointsMZOnViewPlane->elements[12],
                facesPointsMZOnViewPlane->elements[13], grayImage,value);

        destroyMatrix(&facesPointsMZOnViewPlane);
        destroyMatrix(&facesPoints);
    }



    destroyMatrix(&viewVectors);
    destroyMatrix(&normalViewPlaneVector);
    destroyMatrix(&rotateViews);
    destroyMatrix(&innerProductsMatrix);
}

template <typename Type>
GrayImage* getPlanarSlice(iftMatrix<Type> *point, iftMatrix<Type> *vector,
                          MedicalImage *image3D, bool drawFrame){
    float thetaX;
    float thetaY;
    float nx,ny,nz;
    float diagonal;
    nx = image3D->nx;
    ny = image3D->ny;
    nz= image3D->nz;
    diagonal = computeDiogonal(nx,ny,nz);
    iftMatrix<float>* rotationX;
    iftMatrix<float>* rotationY;
    iftMatrix<float>* p_translation = createIdentityMatrix(4,4,FLOAT);
    iftMatrix<float>* qc_translation = createIdentityMatrix(4,4,FLOAT);

    p_translation->elements[3] = -point->elements[0];
    p_translation->elements[7] = -point->elements[1];
    p_translation->elements[11] = -point->elements[2];

    qc_translation->elements[3] = diagonal/2;
    qc_translation->elements[7] = diagonal/2;
    qc_translation->elements[11] = -diagonal/2;

    alignVectorWithZF(vector->elements[0],vector->elements[1],vector->elements[2],&thetaX,&thetaY);
    rotationX = createRotationMatrix(thetaX,'x');
    rotationY = createRotationMatrix(thetaY,'y');
    //R = matrixMultiplicationF(rotationY,rotationX);


    iftMatrix<float> *aux = matrixMultiplicationF(rotationX,p_translation);
    iftMatrix<float> *aux2 = matrixMultiplicationF(rotationY,aux);
    iftMatrix<float> *T = matrixMultiplicationF(qc_translation,aux2);
    iftMatrix<float> *T_inv = copyMatrix(T);
    invertMatrix(T_inv);

    int h = (int)diagonal;
    iftMatrix<float> *planCoord = createMatrix(h*h,4,(float)0);

    int k=0;
    for (int v = 0; v < h; ++v) {
        for (int u = 0; u < h; ++u) {
            planCoord->elements[k] = u;
            ++k;
            planCoord->elements[k] = v;
            ++k;
            planCoord->elements[k] = -diagonal/2;
            ++k;
            planCoord->elements[k]= 1;
            ++k;
        }
    }
    iftMatrix<float> *voxelsCoord = matrixMultiplicationF(planCoord,T_inv, 1.0, 0.0, CblasNoTrans, CblasTrans);
    GrayImage *outputImage = CreateGrayImage(h,h);

    k=0;
    //int width = 1;
    for (int v = 0; v < h; ++v) {
        for (int u = 0; u < h; ++u) {
            outputImage->val[v][u] = 0;
            //printf("%f %f %f %f",);
            if(voxelsCoord->elements[k] >= 0 && voxelsCoord->elements[k] < nx-1){
                if(voxelsCoord->elements[k+1] >= 0 && voxelsCoord->elements[k+1] < ny-1){
                    if(voxelsCoord->elements[k+2] >= 0 && voxelsCoord->elements[k+2] < nz-1){
                        outputImage->val[v][u] = (int)TrilinearInterpolation(voxelsCoord->elements[k],voxelsCoord->elements[k+1],
                                voxelsCoord->elements[k+2],image3D);

                    }
                }
            }

            k += 4;
            //fprintf(stderr,"x:%d y:%d : %d\n",u,v,outputImage->val[v][u]);
        }
    }

    if(drawFrame){
        //drawInterWireFrame(T,outputImage, image3D,point->elements[2],image3D->nz,point->elements[1],image3D->ny, point->elements[0],image3D->nx, 2048);
        drawWireFrame(T,outputImage, image3D,4095);
    }
    //WriteGrayImage(outputImage,"bujao.pgm");

    destroyMatrix(&rotationX);
    destroyMatrix(&rotationY);
    destroyMatrix(&p_translation);
    destroyMatrix(&qc_translation);
    destroyMatrix(&aux);
    destroyMatrix(&aux2);
    destroyMatrix(&T);
    destroyMatrix(&T_inv);
    destroyMatrix(&planCoord);
    destroyMatrix(&voxelsCoord);

    return outputImage;
}




void refactoreImage(MedicalImage *image3D, float newDx, float newDy,float newDz){
    float scaleX = image3D->dx/newDx;
    float scaleY = image3D->dy/newDy;
    float scaleZ = image3D->dz/newDz;

    int newNx = (int)scaleX*image3D->nx;
    int newNy = (int)scaleY*image3D->ny;
    int newNz = (int)scaleZ*image3D->nz;

    MedicalImage *refactoredImage3DX = CreateMedicalImage(newNx,image3D->ny,image3D->nz);

    refactoredImage3DX->dx = newDx;
    refactoredImage3DX->dy = image3D->dy;
    refactoredImage3DX->dz = image3D->dz;

    float Ip;
    int xfloor,xceil;
    int yfloor,yceil;
    int zfloor,zceil;
    float dx,dy,dz;
    float xf,yf,zf;

    int lastx = (int)(((float)(image3D->nx-1)*image3D->dx)/newDx);

    for (int z = 0; z < image3D->nz; ++z) {
        for (int y = 0; y < image3D->ny; ++y) {
            dx = 0;
            for (int x = 0; x < lastx; ++x) {
                xf = dx/image3D->dx;
                xfloor = (int)xf;
                xceil = xfloor+1;
                Ip = (xf-xfloor)*image3D->val[z][y][xceil];
                Ip += (xceil-xf)*image3D->val[z][y][xfloor];
                refactoredImage3DX->val[z][y][x] = Ip;
                dx += newDx;
            }
        }
    }
    MedicalImage *refactoredImage3DXY = CreateMedicalImage(newNx,newNy,image3D->nz);
    refactoredImage3DXY->dx = newDx;
    refactoredImage3DXY->dy = newDy;
    refactoredImage3DXY->dz = image3D->dz;
    int lasty = (int)(((float)(image3D->ny-1)*image3D->dy)/newDy);
    for (int z = 0; z < image3D->nz; ++z) {
        for (int x = 0; x < refactoredImage3DXY->nx; ++x) {
            dy = 0;
            for (int y = 0; y < lasty; ++y) {
                yf = dy/image3D->dy;
                yfloor = (int)yf;
                yceil = yfloor+1;
                Ip = (yf-yfloor)*refactoredImage3DX->val[z][yceil][x];
                Ip += (yceil-yf)*refactoredImage3DX->val[z][yfloor][x];
                refactoredImage3DXY->val[z][y][x] = Ip;
                dy += newDy;
            }
        }
    }
    MedicalImage *refactoredImage3DXYZ = CreateMedicalImage(newNx,newNy,newNz);
    refactoredImage3DXYZ->dx = newDx;
    refactoredImage3DXYZ->dy = newDy;
    refactoredImage3DXYZ->dz = newDz;
    int lastz = (int)(((float)(image3D->nz-1)*image3D->dz)/newDz);
    for (int y = 0; y < refactoredImage3DXYZ->ny; ++y) {
        for (int x = 0; x < refactoredImage3DXYZ->nx; ++x) {
            dz = 0;
            for (int z = 0; z < lastz; ++z) {
                zf = dz/image3D->dz;
                zfloor = (int)zf;
                zceil = zfloor+1;
                Ip = (zf-zfloor)*refactoredImage3DXY->val[zceil][y][x];
                Ip += (zceil-zf)*refactoredImage3DXY->val[zfloor][y][x];
                refactoredImage3DXYZ->val[z][y][x] = Ip;
                dz += newDz;
            }
        }
    }
    WriteMedicalImage(refactoredImage3DXYZ,"XYZ.scn");
    DestroyMedicalImage(&refactoredImage3DX);
    DestroyMedicalImage(&refactoredImage3DXY);
    DestroyMedicalImage(&refactoredImage3DXYZ);
}

MedicalImage* refactoreImage2(MedicalImage *image3D, float newDx, float newDy,float newDz){
    float scaleX = image3D->dx/newDx;
    float scaleY = image3D->dy/newDy;
    float scaleZ = image3D->dz/newDz;

    int newNx = scaleX*image3D->nx;
    int newNy = scaleY*image3D->ny;
    int newNz = scaleZ*image3D->nz;

    int lastx = (int)(((float)(image3D->nx-1)*image3D->dx)/newDx);
    int lasty = (int)(((float)(image3D->ny-1)*image3D->dy)/newDy);
    int lastz = (int)(((float)(image3D->nz-1)*image3D->dz)/newDz);

    float Ip;
    float dx,dy,dz;
    float xf,yf,zf;
    float stepSizeX = 1/image3D->dx;
    float stepSizeY = 1/image3D->dy;
    float stepSizeZ = 1/image3D->dz;



    MedicalImage *refactoredImage3DXYZ = CreateMedicalImage(newNx,newNy,newNz);
    refactoredImage3DXYZ->dx = newDx;
    refactoredImage3DXYZ->dy = newDy;
    refactoredImage3DXYZ->dz = newDz;
    refactoredImage3DXYZ->maxValue = image3D->maxValue;
    refactoredImage3DXYZ->nbits = image3D->nbits;
    for (int i = 0; i < 10; ++i) {
        refactoredImage3DXYZ->unid[i] =  image3D->unid[i];
    }


    dz = 0;
    for (int z = 0; z < lastz; ++z) {
        dy = 0;
        for (int y = 0; y < lasty; ++y) {
            dx = 0;
            for (int x = 0; x < lastx; ++x) {
                xf = dx*stepSizeX;
                yf = dy*stepSizeY;
                zf = dz*stepSizeZ;
                Ip = TrilinearInterpolation(xf,yf,zf,image3D);
                refactoredImage3DXYZ->val[z][y][x] = Ip;//implicit casting faster than explicit casting
                dx += newDx;
            }
            dy += newDy;
        }
        dz += newDz;
    }
    WriteMedicalImage(refactoredImage3DXYZ,"XYZ2.scn");
    //DestroyMedicalImage(&refactoredImage3DXYZ);
    return refactoredImage3DXYZ;
}

void insertSliceInScene(MedicalImage* image3D,GrayImage* grayImage,int z){
    for (int y = 0; y < image3D->ny; ++y) {
        for (int x = 0; x < image3D->nx; ++x) {
            image3D->val[z][y][x] = grayImage->val[y][x];
        }
    }
}

MedicalImage* refactoreScene(iftMatrix<float> *point1, iftMatrix<float> *point2,
                             MedicalImage *image3D, int n){
    iftMatrix<float>* stepSize = matrixSubtraction(point2,point1);
    divideMatrixByScalar(stepSize, n);
    iftMatrix<float>* pk = copyMatrix(point1);
    int h = (int)computeDiogonal(image3D->nx,image3D->ny,image3D->nz);
    MedicalImage *outputScene = CreateMedicalImage(h,h,n);
    outputScene->maxValue = image3D->maxValue;
    outputScene->nbits = image3D->nbits;
    for (int i = 0; i < 10; ++i) {
        outputScene->unid[i] = image3D->unid[i];
    }
    GrayImage *currentSlice;
    for (int i = 0; i < n; ++i) {
        currentSlice = getPlanarSlice(pk,stepSize,image3D,false);
        insertSliceInScene(outputScene,currentSlice,i);
        matrixAddition(pk,stepSize);
        DestroyGrayImage(&currentSlice);
    }
    destroyMatrix(&stepSize);
    destroyMatrix(&pk);
    return outputScene;

}

MedicalImage* refactoreScene(iftMatrix<float> *points, MedicalImage *image3D, int n){

    int lastIndex = points->numberRows*points->numberCols;
    int k=4;
    iftMatrix<float>*p1 = createMatrix(1,points->numberCols,(float)0);
    iftMatrix<float>*p2 = createMatrix(1,points->numberCols,(float)0);
    int h = (int)computeDiogonal(image3D->nx,image3D->ny,image3D->nz);

    MedicalImage *outputScene = CreateMedicalImage(h,h,n*(points->numberRows-1));
    outputScene->maxValue = image3D->maxValue;
    outputScene->nbits = image3D->nbits;
    for (int i = 0; i < 10; ++i) {
        outputScene->unid[i] = image3D->unid[i];
    }
    GrayImage *currentSlice = NULL;

    while(k < lastIndex){
        p1->elements[0] = points->elements[k-4];
        p1->elements[1] = points->elements[k+1-4];
        p1->elements[2] = points->elements[k+2-4];
        p1->elements[3] = points->elements[k+3-4];
        p2->elements[0] = points->elements[k];
        p2->elements[1] = points->elements[k+1];
        p2->elements[2] = points->elements[k+2];
        p2->elements[3] = points->elements[k+3];
        iftMatrix<float>* stepSize = matrixSubtraction(p2,p1);
        divideMatrixByScalar(stepSize, n);
        iftMatrix<float>* pk = copyMatrix(p1);
        int shift = (k/4)-1;
        int stride = (shift*n);
        for (int i = 0; i < n; ++i) {
            currentSlice = getPlanarSlice(pk,stepSize,image3D,false);
            insertSliceInScene(outputScene,currentSlice,i + stride);
            matrixAddition(pk,stepSize);
            DestroyGrayImage(&currentSlice);
        }
        k += 4;
        destroyMatrix(&stepSize);
        destroyMatrix(&pk);
    }
    destroyMatrix(&p1);
    destroyMatrix(&p2);
    return outputScene;

}

template<typename type1>
void computeInnerProducts(iftMatrix<type1> *A, iftMatrix<type1> *B,
                          iftMatrix<type1> *C){
    int k=0;
    for(int i=0; i<A->numberRows; i++){
        C->elements[i] = A->elements[k]*B->elements[k];
        C->elements[i] += A->elements[k+1]*B->elements[k+1];
        C->elements[i] += A->elements[k+2]*B->elements[k+2];
        k += 4;
    }
}

template<typename type1>
void computeInnerProductsGivenVector(iftMatrix<type1> *A, iftMatrix<type1> *vec,
                          iftMatrix<type1> *C){
    int k=0;
    int l=0;
    for(int i=0; i<A->numberRows; i++){
        C->elements[i] = A->elements[k]*vec->elements[l];
        C->elements[i] += A->elements[k+1]*vec->elements[l+1];
        C->elements[i] += A->elements[k+2]*vec->elements[l+2];
        k += 4;
    }
}

void computeLambdasInplace(iftMatrix<float>*inners1,iftMatrix<float>*inners2,iftMatrix<float>*lambdas){
    for (int i = 0; i < inners2->numberRows; ++i) {
        if(fabs(inners2->elements[i]) < 0.00001){
            inners2->elements[i] = 0.00001;
        }
        lambdas->elements[i] = inners1->elements[i]/inners2->elements[i];
    }
}

void findPoints(iftMatrix<float>* lambdas, iftMatrix<float>* inners2, iftMatrix<float>*p0,
                iftMatrix<float>*n_t, iftMatrix<float>* p1, iftMatrix<float>* pn){
    float HighLambda = -9999999;
    float lowLambda = 9999999;
    int indexLow = -1;
    int indexHigh = -1;

    for (int i = 0; i < lambdas->numberRows; ++i) {
        if(fabs(inners2->elements[i]) > 0.0001 ){

            if(lambdas->elements[i] < lowLambda){
                lowLambda = lambdas->elements[i];
                indexLow = i;
            }
            if(lambdas->elements[i] > HighLambda){
                HighLambda = lambdas->elements[i];
                indexHigh = i;
            }
        }
    }

    p1->elements[0] = (int)(p0->elements[0] + lowLambda*n_t->elements[0]);
    p1->elements[1] = (int)(p0->elements[1] + lowLambda*n_t->elements[1]);
    p1->elements[2] = (int)(p0->elements[2] + lowLambda*n_t->elements[2]);
    p1->elements[3] = 1;

    pn->elements[0] = (int)(p0->elements[0] + HighLambda*n_t->elements[0]);
    pn->elements[1] = (int)(p0->elements[1] + HighLambda*n_t->elements[1]);
    pn->elements[2] = (int)(p0->elements[2] + HighLambda*n_t->elements[2]);
    pn->elements[3] = 1;
}


float getMaximumIntensityOnLine(iftMatrix<float> *p0,iftMatrix<float>*pn,MedicalImage *image3D){
    float x,y,z;
    x = p0->elements[0];
    y = p0->elements[1];
    z = p0->elements[2];
    iftMatrix<float>* delta = matrixSubtraction(pn,p0);
    float diagonal = computeDiogonal(delta->elements[0],delta->elements[1],delta->elements[2]);
    float diagonalD = computeDiogonal(image3D->dx,image3D->dy,image3D->dz);
    int n = diagonal/diagonalD;
    divideMatrixByScalar(delta,n);
    float dx,dy,dz;
    float maximumValue = 0;
    float value;
    for (int i = 0; i < n; ++i) {
        if(x < image3D->nx-1){
            if(y < image3D->ny-1){
                if(z < image3D->nz-1){

                    value = TrilinearInterpolation(x,y,z,image3D);
                    if(value > maximumValue){
                        maximumValue = value;
                    }

                }
            }
        }

        x += delta->elements[0];
        y += delta->elements[1];
        z += delta->elements[2];
    }
    return maximumValue;
}


void maximumIntensityProjection(MedicalImage *image3D, float thetax_degree, float thetay_degree){
    //convert degree to rads
    float thetay_rad = thetay_degree*(M_PI)/180.;
    float thetax_rad = thetax_degree*(M_PI)/180.;
    iftMatrix<float> *Ry = createRotationMatrix(-thetay_rad,'y');
    iftMatrix<float> *Rx = createRotationMatrix(-thetax_rad,'x');
    float diagonal = computeDiogonal(image3D->nx,image3D->ny,image3D->nz);

    iftMatrix<float>* pc_dash = createIdentityMatrix(4,4,FLOAT);
    iftMatrix<float>* pc = createIdentityMatrix(4,4,FLOAT);

    pc_dash->elements[3] = -diagonal/2.;
    pc_dash->elements[7] = -diagonal/2.;
    pc_dash->elements[11] = -diagonal/2.;

    pc->elements[3] = image3D->nx/2.;
    pc->elements[7] = image3D->ny/2.;
    pc->elements[11] = image3D->nz/2.;

    iftMatrix<float> *aux = matrixMultiplicationF(Ry,pc_dash);
    iftMatrix<float> *aux2 = matrixMultiplicationF(Rx,aux);
    iftMatrix<float> *T_inv = matrixMultiplicationF(pc,aux2);
    int h = (int)diagonal;
    GrayImage *image = CreateGrayImage(h,h);

    iftMatrix<float> *nj = createMatrix(6,4,(float)0);
    iftMatrix<float> *cj = createMatrix(6,4,(float)0);
    iftMatrix<float> *n = createMatrix(1,4,(float)0);


    //-z normal
    nj->elements[0] = 0;
    nj->elements[1] = 0;
    nj->elements[2] = -1;
    nj->elements[3] = 0;
    //z normal
    nj->elements[4] = 0;
    nj->elements[5] = 0;
    nj->elements[6] = 1;
    nj->elements[7] = 0;
    //-y normal
    nj->elements[8] = 0;
    nj->elements[9] = -1;
    nj->elements[10] = 0;
    nj->elements[11] = 0;
    //y normal
    nj->elements[12] = 0;
    nj->elements[13] = 1;
    nj->elements[14] = 0;
    nj->elements[15] = 0;
    //-x normal
    nj->elements[16] = -1;
    nj->elements[17] = 0;
    nj->elements[18] = 0;
    nj->elements[19] = 0;
    //x normal
    nj->elements[20] = -1;
    nj->elements[21] = 0;
    nj->elements[22] = 0;
    nj->elements[23] = 0;
    //-z normal
    cj->elements[0] = image3D->nx/2.;
    cj->elements[1] = image3D->ny/2.;
    cj->elements[2] = 0;
    cj->elements[3] = 1;
    //z normal
    cj->elements[4] = image3D->nx/2.;
    cj->elements[5] = image3D->ny/2.;
    cj->elements[6] = image3D->nz;
    cj->elements[7] = 1;
    //-y normal
    cj->elements[8] = image3D->nx/2.;
    cj->elements[9] = 0;
    cj->elements[10] = image3D->nz/2.;
    cj->elements[11] = 1;
    //y normal
    cj->elements[12] = image3D->nx/2.;
    cj->elements[13] = image3D->ny;
    cj->elements[14] = image3D->nz/2.;
    cj->elements[15] = 1;
    //-x normal
    cj->elements[16] = 0.;
    cj->elements[17] = image3D->ny/2.;
    cj->elements[18] = image3D->nz/2.;
    cj->elements[19] = 1;
    //x normal
    cj->elements[20] = image3D->nx;
    cj->elements[21] = image3D->ny/2.;
    cj->elements[22] = image3D->nz/2.;
    cj->elements[23] = 1;

    n->elements[0] = 0;
    n->elements[1] = 0;
    n->elements[2] = 1;
    n->elements[3] = 0;
    iftMatrix<float>* inners1 = createMatrix(6,1,(float)0);
    iftMatrix<float>* inners2 = createMatrix(6,1,(float)0);
    iftMatrix<float>* lambdas = createMatrix(6,1,(float)0);
    iftMatrix<float>* p0 = createMatrix(1,4,(float)0);
    iftMatrix<float>* p0_t = createMatrix(1,4,(float)0);
    iftMatrix<float>* p1 = createMatrix(1,4,(float)0);
    iftMatrix<float>* pn = createMatrix(1,4,(float)0);
    iftMatrix<float>* n_t = createMatrix(1,4,(float)0);
    iftMatrix<float> *cj_copy = createMatrix(6,4,(float)0);



    for (int v = 0; v < image->ny; ++v) {
        for (int u = 0; u < image->nx; ++u) {

            p0->elements[0] = 231;
            p0->elements[1] = 71;
            p0->elements[2] = -diagonal/2.;
            p0->elements[3] = 1;
            matrixMultiplicationF_inPlace(p0,T_inv,p0_t,1.0,0.0,CblasNoTrans, CblasTrans);
            matrixMultiplicationF_inPlace(n,T_inv,n_t,1.0, 0.0, CblasNoTrans, CblasTrans);
            copyMatrixInplace(cj,cj_copy);
            matrixSubtractVector(cj_copy,p0_t);
            computeInnerProducts(cj_copy,nj,inners1);
            computeInnerProductsGivenVector(nj,n_t,inners2);
            computeLambdasInplace(inners1,inners2,lambdas);


            findPoints(lambdas,inners2, p0_t, n_t, p1, pn);

            printMatrix(p1);
            printMatrix(pn);
            if(p1->elements[0] >= 0 && p1->elements[1] >= 0 && p1->elements[2] >= 0){
                if(p1->elements[0] <= image3D->nx && p1->elements[1] <= image3D->ny && p1->elements[2] <= image3D->nz){
                    if(pn->elements[0] >= 0 && pn->elements[1] >= 0 && pn->elements[2] >= 0){
                        if(pn->elements[0] <= image3D->nx && pn->elements[1] <= image3D->ny && pn->elements[2] <= image3D->nz){
                            image->val[v][u] = getMaximumIntensityOnLine(p1,pn,image3D);
                        }
                    }
                }
            }

        }
    }
    destroyMatrix(&T_inv);
    destroyMatrix(&cj);
    destroyMatrix(&cj_copy);
    destroyMatrix(&nj);
    destroyMatrix(&inners1);
    destroyMatrix(&inners2);
    destroyMatrix(&lambdas);
    printMatrix(p1);
    printMatrix(pn);
    printMatrix(p0);
    WriteGrayImage(image,"maximum.pgm");
}


#endif // MATRIXFEIA_H
