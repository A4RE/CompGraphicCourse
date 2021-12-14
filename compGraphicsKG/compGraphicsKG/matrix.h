#pragma once
#include <math.h>
#include "graphics.h"
#include "Point3D.h"

enum class Axises {X, Y, Z};

void mulMat(double* cor, double** matr, int size);
void delmatr(double** matr, int size);
double** matrixTransfer(double dx, double dy, double dz);
double** matrixScale(double sx, double sy, double sz);
double** matrixRotation(double fiVec, Axises axis);
double** matrProjection();
double** matrShadow(Point3D& l, int maxY);