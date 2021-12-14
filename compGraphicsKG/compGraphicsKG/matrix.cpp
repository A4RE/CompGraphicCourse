#include "matrix.h"

const double pi = 3.1415926535;

//умножение матрицы на матрицу
void mulMat(double* cor, double** matr, int size)
{
    //массив для результата умножения
    double* newCor = new double[size];

    for (int i = 0; i < size; i++)
    {
        double a = 0;
        for (int j = 0; j < size; j++)
            a += cor[j] * matr[j][i];
        newCor[i] = a;
    }
    //запись навых координат в изначальный массив
    for (int i = 0; i < size; i++)
        cor[i] = newCor[i];
    delete[] newCor;
}
//освобождение динамической памяти, выделенной под матрицы преобразования
void delmatr(double** matr, int size)
{
    for (int i = 0; i < size; i++)
        delete[] matr[i];
    delete[] matr;
}
//создание матрицы перемещения
double** matrixTransfer(double dx, double dy, double dz)
{
    double** matr = new double* [4];  
    for (int i = 0; i < 4; i++) {
        matr[i] = new double[4];
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
                matr[i][j] = 1;
            else
                matr[i][j] = 0;
        }
    }

    matr[3][0] = dx;
    matr[3][1] = dy;
    matr[3][2] = dz;

    return matr;
}
//создание матрицы маштабирования
double** matrixScale(double sx, double sy, double sz)
{
    double** matr = new double* [4];
    for (int i = 0; i < 4; i++) {
        matr[i] = new double[4];
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
                matr[i][j] = 1;
            else
                matr[i][j] = 0;
        }
    }
        
    matr[0][0] = sx;
    matr[1][1] = sy;
    matr[2][2] = sz;
    return matr;
}
//создание матрицы поворота
double** matrixRotation(double fiVec, Axises axis)
{
    fiVec *= pi / 180.0;
    double** matr = new double* [4]; 
    for (int i = 0; i < 4; i++) {
        matr[i] = new double[4];
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
                matr[i][j] = 1;
            else
                matr[i][j] = 0;
        }
    }
        
    if (axis == Axises::Z)
    {
        matr[0][0] = cos(fiVec);
        matr[0][1] = sin(fiVec);
        matr[1][0] = -sin(fiVec);
        matr[1][1] = cos(fiVec);
    }
    else if (axis == Axises::X)
    {
        matr[1][1] = cos(fiVec);
        matr[1][2] = sin(fiVec);
        matr[2][1] = -sin(fiVec);
        matr[2][2] = cos(fiVec);
    }
    else if (axis == Axises::Y)
    {
        matr[0][0] = cos(fiVec);
        matr[0][2] = -sin(fiVec);
        matr[2][0] = sin(fiVec);
        matr[2][2] = cos(fiVec);
    }        
    return matr;
}
//создание матрицы проецирования
double** matrProjection()
{
    double** matr = new double* [4];
    for (int i = 0; i < 4; i++) {
        matr[i] = new double[4];
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
                matr[i][j] = 1;
            else
                matr[i][j] = 0;
        }
    }
        
    matr[2][3] = 1.0/500.0;
    return matr;
}
// создание матрицы тени
double** matrShadow(Point3D& l, int maxY) {
    double ys = maxY;
    double** matr = new double* [4];
    for (int i = 0; i < 4; i++) {
        matr[i] = new double[4];
        for (int j = 0; j < 4; j++)
            matr[i][j] = 0;
    }    
    
    matr[0][0] = ys-l.getY();
    matr[1][0] = l.getX();
    matr[1][1] = ys;
    matr[1][2] = l.getZ();
    matr[1][3] = 1;
    matr[2][2] = ys-l.getY();
    matr[3][0] = -ys*l.getX();
    matr[3][1] = -ys*l.getY();
    matr[3][2] = -ys*l.getZ();
    matr[3][3] = -l.getY();

    return matr;
}