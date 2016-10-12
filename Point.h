#pragma once
class Point
{
private:
	int x;
	int y;
	long long time_calc;
	long long time_write;
public:
	Point();
	void setX(int x);
	void setY(int y);
	void setTimeCalc(long long time);
	void setTimeWrite(long long time);
	int getX();
	int getY();
	long long getTimeCalc();
	long long getTimeWrite();
	~Point();
};