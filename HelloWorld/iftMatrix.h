//#ifndef iftMatrix_H
//#define iftMatrix_H


//#include <cblas.h>
//#include <cstdio>
//#include <typeinfo>
//#include <string.h>
//#include <stdlib.h>
//#include <math.h>
//#include <iostream>
//#include "mc920.h"


//enum ConverstionTypes { INT2FLOAT=0, FLOAT2INT=1 };
//enum primitiveDataTypesId { INT=0, LONG=1, FLOAT=2, DOUBLE=3, LONG_DOUBLE=4  };


//extern "C" {
//    // LU decomoposition of a general matrix
//    void sgetrf_(int* M, int *N, float* A, int* lda, int* IPIV, int* INFO);

//    // generate inverse of a matrix given its LU decomposition
//    void sgetri_(int* N, float* A, int* lda, int* IPIV, float* WORK, int* lwork, int* INFO);
//}

//template <typename T>
//struct iftMatrix{
//    T* elements;
//    int numberRows;//magnitudeSquared
//    int numberCols;
//    int dataTypeId;
//    int* shifts;
//} ;



//int getDataTypeId(const char* dataType);

//template <typename type1, typename type2>
//int getAproprieteDataType(iftMatrix<type1>* matrix, type2 scalar);

//template <typename type1, typename type2>
//int getAproprieteDataType(type1  scalar1, type2 scalar2);

//template <typename type>
//int getAproprieteDataType(int  dataTypeId, type scalar);

//template <typename T>
//iftMatrix<T>* allocateMatrixPointer(int numberRows, int numberCols, T initialValue);

//template <typename T>
//iftMatrix<T>* allocateAppropriatetMatrixPointer(int numberRows, int numberCols, int dataTypeId);

//template <typename T>
//iftMatrix<T>* createMatrix(int numberRows, int numberCols, T initialValue);


//iftMatrix<float>* createIdentityMatrix(int numberRows, int numberCols, int dataTypeId);

//template <typename T, typename P>
//iftMatrix<P>* convertMatrixTypes(int converstionType, iftMatrix<T>* matrixSource);

//template <typename T>
//void destroyMatrix(iftMatrix<T>**matrix);

//template <typename T,typename P>
//void multiplyMatrixByScalar(iftMatrix<T>*matrix, P scalar);

//template <typename Type1,typename Type2, typename Type3>
//iftMatrix<Type3>* multiplyMatrixByScalar(iftMatrix<Type1>*matrix, Type2 scalar);

//template <typename T,typename P>
//void addMatrixByScalar(iftMatrix<T>*matrix, P scalar);

//template <typename T,typename P>
//void subtractMatrixByScalar(iftMatrix<T>*matrix, P scalar);


//template <typename T,typename P>
//void divideMatrixByScalar(iftMatrix<T>*matrix, P scalar);

//template <typename T>
//void matrixAddition(iftMatrix<T> *A,iftMatrix<T> *B);

//iftMatrix<float>* matrixSubtraction(iftMatrix<float> *A,iftMatrix<float> *B);

//template <typename T>
//void matrixSubtractionInPlace(iftMatrix<T> *A,iftMatrix<T> *B);

//template <typename T>
//void matrixSubtractVector(iftMatrix<T> *A,iftMatrix<T> *vec);

//template <typename T>
//void matrixSubtractVector2(iftMatrix<T> *A,iftMatrix<T> *vec);

//iftMatrix<float>* matrixMultiplicationF(iftMatrix<float> *A,iftMatrix<float> *B, float alpha, float beta,
//                                        CBLAS_TRANSPOSE transposeA, CBLAS_TRANSPOSE transposeB);

//iftMatrix<float>* matrixMultiplicationF_inPlace(iftMatrix<float> *A,iftMatrix<float> *B, iftMatrix<float> *C,float alpha, float beta,
//                                        CBLAS_TRANSPOSE transposeA, CBLAS_TRANSPOSE transposeB);

//template <typename Type1,typename Type2,typename Type3, typename Type4>
//iftMatrix<Type4>* matrixMultiplication(iftMatrix<Type1> *A,iftMatrix<Type2> *B, Type3 alpha, Type3 beta,
//                                       int transposeA, int transposeB);

//template <typename Type1,typename Type2,typename Type3, typename Type4>
//void matrixMultiplication(iftMatrix<Type1> *A,iftMatrix<Type2> *B, iftMatrix<Type3> *C, Type4 alpha, Type4 beta,
//                          int transposeA, int transposeB);

//template <typename Type1,typename Type2,typename Type3>
//void matrixMultiplication(iftMatrix<Type1> *A,iftMatrix<Type2> *B, iftMatrix<Type3> *C);

//template <typename Type1,typename Type2,typename Type3>
//iftMatrix<Type1>* matrixMultiplication(iftMatrix<Type1> *A,iftMatrix<Type1> *B);

//iftMatrix<float>* matrixMultiplicationF(iftMatrix<float> *A,iftMatrix<float> *B);

//template <typename Type1>
//void invertMatrix(iftMatrix<Type1> *matrix);

//template <typename Type1>
//void copyMatrixInplace(iftMatrix<Type1> *matrixSource, iftMatrix<Type1> *matrixTarget);

//template <typename Type1>
//iftMatrix<Type1>* copyMatrix(iftMatrix<Type1> *matrixSource);


//template <typename Type>
//iftMatrix<Type> *getSubMatrix(iftMatrix<Type> *matrix, int startRow, int endRow, int startCol, int endCol);

//template <typename Type1>
//iftMatrix<Type1>* createRotationMatrixInX(Type1 angle_rad);

//template <typename Type1>
//iftMatrix<Type1>* createRotationMatrixInY(Type1 angle_rad);

//template <typename Type1>
//iftMatrix<Type1>* createRotationMatrixInZ(Type1 angle_rad);

//template <typename Type>
//iftMatrix<Type>* createRotationMatrix(Type angle_rad,char axes);




//template <typename Type1,typename Type2>
//void alignVectorWithZ(Type1 x, Type1 y,Type1 z, Type2 *thetaX, Type2 *thetaY);

//void alignVectorWithZF(float x, float y,float z, float *thetaX, float *thetaY);



//template <typename Type>
//void printMatrix(iftMatrix<Type> *matrix);


//float bilinearInterpolation(float x,float y,int fixedz, MedicalImage *image3D);



//float computeDiogonal(float nx, float ny, float nz){
//    return sqrt((nx*nx) + (ny*ny) + (nz*nz));
//}

//void myDDAVersion(float x1, float y1, float x2, float y2, GrayImage* grayImage,
//                  int value);

//void drawInterWireFrame(iftMatrix<float> *transformationMatrix, GrayImage* grayImage, MedicalImage* image3D,
//                        float zFront,float zBack,float yFront,float yBack,float xFront,float xBack, int value);

//void drawWireFrame(iftMatrix<float> *transformationMatrix, GrayImage* grayImage, MedicalImage* image3D,
//                   int value);

//template <typename Type>
//GrayImage* getPlanarSlice(iftMatrix<Type> *point, iftMatrix<Type> *vector,
//                          MedicalImage *image3D, bool drawFrame);

//void refactoreImage(MedicalImage *image3D, float newDx, float newDy,float newDz);

//MedicalImage* refactoreImage2(MedicalImage *image3D, float newDx, float newDy,float newDz);

//void insertSliceInScene(MedicalImage* image3D,GrayImage* grayImage,int z);

//MedicalImage* refactoreScene(iftMatrix<float> *point1, iftMatrix<float> *point2,
//                             MedicalImage *image3D, int n);

//MedicalImage* refactoreScene(iftMatrix<float> *points, MedicalImage *image3D, int n){}

//template<typename type1>
//void computeInnerProducts(iftMatrix<type1> *A, iftMatrix<type1> *B,
//                          iftMatrix<type1> *C);

//template<typename type1>
//void computeInnerProductsGivenVector(iftMatrix<type1> *A, iftMatrix<type1> *vec,
//                          iftMatrix<type1> *C);

//float getMaximumIntensityOnLine(iftMatrix<float> *p0,iftMatrix<float>*pn,MedicalImage *image3D);
//GrayImage* maximumIntensityProjection(MedicalImage *image3D, float thetax_degree, float thetay_degree);

//#endif // iftMatrix_H
