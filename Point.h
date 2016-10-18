#pragma once
class Point
{
private:
	double x;
	double y;
	long long time_calc;
	long long time_write;
public:
	Point();
	void setX(double x);
	void setY(double y);
	void setTimeCalc(long long time);
	void setTimeWrite(long long time);
	double getX();
	double getY();
	long long getTimeCalc();
	long long getTimeWrite();
	~Point();
};