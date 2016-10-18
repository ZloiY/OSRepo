#include "stdafx.h"
#include "Point.h"

using namespace std;

Point::Point()
{
	x = 0.0;
	y = 0.0;
	time_calc = 0;
	time_write = 0;
}

void Point::setX(double x) {
	this->x = x;
}

void Point::setY(double y) {
	this->y = y;
}

void Point::setTimeCalc(long long time) {
	this->time_calc = time;
}

void Point::setTimeWrite(long long time) {
	this->time_write = time;
}

double Point::getX() {
	return x;
}

double Point::getY() {
	return y;
}

long long Point::getTimeCalc() {
	return time_calc;
}

long long Point::getTimeWrite() {
	return time_write;
}

Point::~Point()
{
}
