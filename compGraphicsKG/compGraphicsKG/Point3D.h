#pragma once

class Point3D
{
private:
	double x, y, z;
public:
	Point3D() : x(0), y(0), z(0) {}
	Point3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

	void setX(double _x) { x = _x; }
	double getX() { return x; }

	void setY(double _y) { y = _y; }
	double getY() { return y; }

	void setZ(double _z) { z = _z; }
	double getZ() { return z; }
};

