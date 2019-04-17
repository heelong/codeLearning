// (1) 完成函数Distance，计算点_P到线段_L之间的距离
//        测试数据1： p = [0, 0], l = [[1, 0], [0, 1]]
//        测试数据2： p = [0, 0], l = [[1, 1], [2, 1]]
// (2) 完成函数DouglasPeucker，实现坐标点串的抽稀


#include <iostream>
#include <vector>  
#include <math.h>
#include <algorithm>
using namespace std;
struct Point
{
	Point(double _x, double _y)
		: mX(_x), mY(_y)
	{
	}
	double mX, mY;
};

struct Line
{
	Line(double _x1, double _y1, double _x2, double _y2)
		: mP1(Point(_x1, _y1)), mP2(Point(_x2, _y2))
	{}
	Point mP1;
	Point mP2;
};

typedef std::vector<Point> Polyline;

double Distance(const Point& _P, const Line& _L)
{
	double dis = 0.0;

	double d_x = _L.mP1.mX - _L.mP2.mX;
	double d_y = _L.mP1.mY - _L.mP2.mY;
	double dis_2 = d_x*d_x + d_y*d_y;
	double k = -((_L.mP1.mX - _P.mX)*d_x + (_L.mP1.mY - _P.mY)*d_y) / dis_2;

	//垂足
	double foot_x = k*d_x + _P.mX;
	double foot_y = k*d_x + _P.mX;

	if (foot_x>max(_L.mP1.mX, _L.mP2.mX) || foot_x<min(_L.mP1.mX, _L.mP2.mX) ||
		foot_y>max(_L.mP1.mY, _L.mP2.mY) || foot_y<min(_L.mP1.mY, _L.mP2.mY))
	{
		//垂足在线段以外，返回与线段端点距离较近的点的距离
		d_x = _P.mX - _L.mP1.mX;
		d_y = _P.mY - _L.mP1.mY;
		double dis_P_Lp1 = sqrt(d_x*d_x + d_y*d_y);

		d_x = _P.mX - _L.mP2.mX;
		d_y = _P.mY - _L.mP2.mY;
		double dis_P_Lp2 = sqrt(d_x*d_x + d_y*d_y);
		dis = min(dis_P_Lp1, dis_P_Lp2);
	}
	else
	{
		//垂足在线段内，返回点到垂足的距离
		d_x = _P.mX - foot_x;
		d_y = _P.mY - foot_y;
		dis = sqrt(d_x*d_x + d_y*d_y);
	}
	return dis;
};

Polyline DouglasPeucker(const Polyline& _Line, double _Threshold)
{
}

void DistanceTest()
{
	Point p(0, 0);
	Line l(1, 0, 0, 1);
	std::cout << Distance(p, l) << std::endl;
	std::cout << Distance(Point(0, 0), Line(1, 1, 2, 1)) << std::endl;
}

//int main() {
//	/*  Testing data:
//	polyline coordinates: [[0, 0], [1, -1], [2.5, -2], [4, -0.3], [5, 2], [3.5, 4]]
//	threshold: 1.0
//	*/
//	DistanceTest();
//
//	return 0;
//}