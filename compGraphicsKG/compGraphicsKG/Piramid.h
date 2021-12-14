#pragma once
#include "Triangle.h"

class Piramid
{
private:
	vector<Triangle> triangles;
	Point3D center;
	int maxX = 0, maxY = 0;
	void centerTask();
public:
	Piramid() {}
	Piramid(vector<Triangle> _triangles);
	Piramid(Point3D _point1, Point3D _point2, Point3D _point3, Point3D _point4, 
		COLORREF _color1, COLORREF _color2, COLORREF _color3, COLORREF _color4);

	void print();
	void transfer(double dx, double dy, double dz, bool isBorder = true);
	void scale(double sx, double sy, double sz, bool isBorder = true);
	void rotation(double angle, Axises axis, bool isBorder = true);
	void projection();
	void painting();
	void setMax(int _maxX, int _maxY);
	void parintShadow(Point3D l);

	vector<Triangle> getTriandles() { return triangles; }
};

