#include "stdafx.h"
#include "Point.h"

using namespace std;

Point::Point()
{
	x = 0;
	y = 0;
	time_calc = 0;
	time_write = 0;
}

void Point::setX(int x) {
	this->x = x;
}

void Point::setY(int y) {
	this->y = y;
}

void Point::setTimeCalc(long long time) {
	this->time_calc = time;
}

void Point::setTimeWrite(long long time) {
	this->time_write = time;
}

int Point::getX() {
	return x;
}

int Point::getY() {
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
