#include "Piramid.h"

Piramid::Piramid(vector<Triangle> _triangles) {
    triangles = _triangles;
}
//задание точек и цвета для построения пирамиды путем соединения треугольников
Piramid::Piramid(Point3D _point1, Point3D _point2, Point3D _point3, Point3D _point4, 
    COLORREF _color1, COLORREF _color2, COLORREF _color3, COLORREF _color4) {
	triangles.push_back(Triangle(_point1, _point2, _point3, _color1));
	triangles.push_back(Triangle(_point1, _point2, _point4, _color2));
	triangles.push_back(Triangle(_point1, _point3, _point4, _color3));
	triangles.push_back(Triangle(_point2, _point3, _point4, _color4));
}
//Построение пирамиды
void Piramid::print() {
    for (int i = 0; i < triangles.size(); i++)
        triangles[i].print();
}
//Перемещение
void Piramid::transfer(double dx, double dy, double dz, bool isBorder) {
    bool isNanBorder = false;
    for (int i = 0; i < triangles.size(); i++) {
        triangles[i].transfer(dx, dy, dz);
        if (triangles[i].getIsNanBorder())
            isNanBorder = true;
    }
    if (isNanBorder && isBorder)
        for (int i = 0; i < triangles.size(); i++)
            triangles[i].transfer(-dx, -dy, -dz);
}
//масштабируемость
void Piramid::scale(double sx, double sy, double sz, bool isBorder) {
    centerTask();
    bool isNanBorder = false;
    for (int i = 0; i < triangles.size(); i++) {
        triangles[i].scale(center, sx, sy, sz);
        if (triangles[i].getIsNanBorder())
            isNanBorder = true;
    }
    if (isNanBorder && isBorder)
        for (int i = 0; i < triangles.size(); i++)
            triangles[i].scale(center, 1.0 / sx, 1.0 / sy, 1.0 / sz);
}

//вращение по осям
void Piramid::rotation(double angle, Axises axis, bool isBorder) {
    centerTask();
    bool isNanBorder = false;
    for (int i = 0; i < triangles.size(); i++) {
        triangles[i].rotation(center, angle, axis);
        if (triangles[i].getIsNanBorder())
            isNanBorder = true;
    }
    if (isNanBorder && isBorder)
        for (int i = 0; i < triangles.size(); i++)
            triangles[i].rotation(center, -angle, axis);
}
//Границы
void Piramid::setMax(int _maxX, int _maxY) {
    maxX = _maxX;
    maxY = _maxY;
    for (int i = 0; i < triangles.size(); i++)
        triangles[i].setMax(maxX, maxY);
}
//построение тени
void Piramid::parintShadow(Point3D l) {
    vector<Triangle> shadowTriangles;
    for (int i = 0; i < triangles.size(); i++)
        shadowTriangles.push_back(triangles[i].getShadowTriangle(l));
    Piramid shadowPiramid(shadowTriangles);
    shadowPiramid.setMax(maxX, maxY);
    shadowPiramid.centerTask();
    shadowPiramid.rotation(20, Axises::X, false);
    shadowPiramid.projection();
    shadowPiramid.print();
    shadowPiramid.painting();
}
//нахождение центра
void Piramid::centerTask() {

    double minX = INT32_MAX, minY = INT32_MAX, minZ = INT32_MAX, maxX = INT32_MIN, maxY = INT32_MIN, maxZ = INT32_MIN;
    
    //нахождения крайних точек  
    for (int i = 0; i < triangles.size(); i++)
    {
        triangles[i].centerTask();
        if (triangles[i].getCenterX() < minX)
            minX = triangles[i].getCenterX();
        if (triangles[i].getCenterX() > maxX)
            maxX = triangles[i].getCenterX();

        if (triangles[i].getCenterY() < minY)
            minY = triangles[i].getCenterY();
        if (triangles[i].getCenterY() > maxY)
            maxY = triangles[i].getCenterY();

        if (triangles[i].getCenterZ() < minZ)
            minZ = triangles[i].getCenterZ();
        if (triangles[i].getCenterZ() > maxZ)
            maxZ = triangles[i].getCenterZ();
    }
    //вычисление центра
    center.setX((minX + maxX) / 2.0);
    center.setY((minY + maxY) / 2.0);
    center.setZ((minZ + maxZ) / 2.0);
}
//проекция
void Piramid::projection() {
    centerTask();
    for (int i = 0; i < triangles.size(); i++)
        triangles[i].projection(center);
}
//закраска
void Piramid::painting() {
    for (int i = 0; i < triangles.size(); i++)
        triangles[i].painting();
}