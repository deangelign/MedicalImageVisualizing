#ifndef IFTMATRIX_H
#define IFTMATRIX_H


#include <cblas.h>
#include <cstdio>
#include <typeinfo>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h>


/*enum ConverstionTypes { INT2FLOAT=0, FLOAT2INT=1 };
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



int getDataTypeId(const char* dataType);

template <typename type1, typename type2>
int getAproprieteDataType(iftMatrix<type1>* matrix, type2 scalar);

template <typename type1, typename type2>
int getAproprieteDataType(type1  scalar1, type2 scalar2);

template <typename type>
int getAproprieteDataType(int  dataTypeId, type scalar);

template <typename T>
iftMatrix<T>* createMatrix(int numberRows, int numberCols, T initialValue);

template <typename T>
iftMatrix<T>* allocateMatrixPointer(int numberRows, int numberCols, T initialValue);

template <typename T>
iftMatrix<T>* allocateAppropriatetMatrixPointer(int numberRows, int numberCols, int dataTypeId);

iftMatrix<float>* createIdentityMatrix(int numberRows, int numberCols, int dataTypeId);

template <typename T, typename P>
iftMatrix<P>* convertMatrixTypes(int converstionType, iftMatrix<T>* matrixSource);

template <typename T>
void destroyMatrix(iftMatrix<T>**matrix);

template <typename T,typename P>
void addMatrixByScalar(iftMatrix<T>*matrix, P scalar);

template <typename T,typename P>
void subtractMatrixByScalar(iftMatrix<T>*matrix, P scalar);

template <typename T,typename P>
void multiplyMatrixByScalar(iftMatrix<T>*matrix, P scalar);

template <typename Type1,typename Type2, typename Type3>
iftMatrix<Type3>* multiplyMatrixByScalar(iftMatrix<Type1>*matrix, Type2 scalar);

template <typename T,typename P>
void divideMatrixByScalar(iftMatrix<T>*matrix, P scalar);

template <typename Type1,typename Type2,typename Type3, typename Type4>
iftMatrix<Type4>* matrixMultiplication(iftMatrix<Type1> *A,iftMatrix<Type2> *B, Type3 alpha, Type3 beta,
                                       int transposeA, int transposeB);

template <typename Type1,typename Type2,typename Type3, typename Type4>
void matrixMultiplication(iftMatrix<Type1> *A,iftMatrix<Type2> *B, iftMatrix<Type3> *C, Type4 alpha, Type4 beta,
                                       int transposeA, int transposeB);

template <typename Type1,typename Type2,typename Type3>
void matrixMultiplication(iftMatrix<Type1> *A,iftMatrix<Type2> *B, iftMatrix<Type3> *C);

template <typename Type1,typename Type2,typename Type3>
iftMatrix<Type3>* matrixMultiplication(iftMatrix<Type1> *A,iftMatrix<Type2> *B);

template <typename Type1>
void invertMatrix(iftMatrix<Type1> *matrix);

template <typename Type>
void printMatrix(iftMatrix<Type> *matrix);

template <typename Type>
iftMatrix<Type> *getSubMatrix(iftMatrix<Type> *matrix, int startRow, int endRow, int startCol, int endCol);

template <typename Type1,typename Type2>
void alignVectorWithZ(Type1 x, Type1 y,Type1 z, Type2 *thetaX, Type2 *thetaY);

template <typename Type1>
iftMatrix<float>* createRotationMatrixInX(Type1 angle_rad);

template <typename Type1>
iftMatrix<float>* createRotationMatrixInY(Type1 angle_rad);

template <typename Type1>
iftMatrix<float>* createRotationMatrixInZ(Type1 angle_rad);

template <typename Type1>
iftMatrix<Type1>* createRotationMatrix(Type1 angle_rad,char axes);

template <typename Type>
void getPlanarSlice(iftMatrix<Type> *point, iftMatrix<Type> *vector);



/*typedef struct {

    float *values;
    int numberRows;
    int numberCols;

} Matrix;



Matrix* createMatrix(int numberRows, int numberCols);
Matrix* createIdentityMatrix(int size);
void alignVectorWithZ(float x, float y,float z, float *thetaX, float *thetaY);
Matrix* createRotationMatrix(float angle_rad,char axes);
void applyTranslation(float x,float y, float z,Matrix *matrix);
void MatrixMultiplication(Matrix *A,Matrix *B,Matrix *C,char At, char Bt);
void printMatrix(Matrix *matrix);
void invertMatrix(Matrix *matrix);
void destroyMatrix(Matrix **matrix);
void copyMatrix(Matrix *A, Matrix **B);*/

#endif // IFTMATRIX_H
