// (1) 完成函数Distance，计算点_P到线段_L之间的距离
//        测试数据1： p = [0, 0], l = [[1, 0], [0, 1]]
//        测试数据2： p = [0, 0], l = [[1, 1], [2, 1]]
// (2) 完成函数DouglasPeucker，实现坐标点串的抽稀


#include <iostream>
#include <vector>  
#include <math.h>
#include <algorithm>
using namespace std;
namespace GeometricAlgorithm
{
	const double eps = 1e-10;

	struct Point
	{
		Point(double _x, double _y)
			: mX(_x), mY(_y)
		{
		}
		double mX, mY;
	};
	typedef Point Vector;

	inline Point operator + (const Point& A, const Point& B){ return Point(A.mX + B.mX, A.mY + B.mY); }
	inline Point operator - (const Point& A, const Point& B){ return Point(A.mX - B.mX, A.mY - B.mY); }
	inline Point operator * (const Point& A, double B){ return Point(A.mX*B, A.mY*B); }
	inline Point operator / (const Point& A, double B){ return Point(A.mX / B, A.mY / B); }

	inline int dcmp(const double& x)
	{
		if (fabs(x) < eps)
			return 0;
		return (x > 0) ? 1 : -1;
	}


	inline bool operator == (const Point& A, const Point& B){
		return dcmp(A.mX - B.mX) == 0 && dcmp(A.mY - B.mY) == 0;
	}

	//计算向量点积，小于0为钝角，大于0为锐角
	/*向量的点积（又叫 标积 / 内积 / 数量积 /），a·b=|a||b|·cosθ
	几何意义：向量a在向量b方向上的投影与向量b的模的乘
	坐标公式：A.x*B.x+A.y*B.y;   */
	inline double Dot(const Point& A, const Point& B)
	{
		return A.mX*B.mX + A.mY*B.mY;
	}

	//计算向量长度
	inline double Length(const Point& A)
	{
		return sqrt(Dot(A, A));
	}

	/*向量的叉积（又叫 矢积 / 外积 / 向量积 /），a×b=|a||b|·sinθ
	几何意义：垂直a、b所在，向量a,b构成的平行四边形的面积
	坐标公式： A.x*B.y-B.x*A.y   */
	//计算向量叉积,向量张成的平行四边形的面积
	inline double Cross(const Point& A, const Point& B)
	{
		return A.mX*B.mY - B.mX*A.mY;
	}

	/*向量旋转  公式 x=x'*cos(rad)-y'*sin(rad)  
	 *				 y=x'*sin(rad)+y'*cos(rad) 
	 *				 rad为要旋转的角度（单位为弧度）*/
	Vector Rotate(Vector A, double rad){
		return Vector(A.mX*cos(rad) - A.mY*sin(rad), A.mX*sin(rad) + A.mY*cos(rad));
	}

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

		const double d_x = _L.mP1.mX - _L.mP2.mX;
		const double d_y = _L.mP1.mY - _L.mP2.mY;
		const double dis_2 = d_x*d_x + d_y*d_y;
		const double k = -((_L.mP1.mX - _P.mX)*d_x + (_L.mP1.mY - _P.mY)*d_y) / dis_2;

		//垂足
		double foot_x = k*d_x + _P.mX;
		double foot_y = k*d_x + _P.mX;

		const Vector v_P1_P2 = _L.mP2 - _L.mP1;//线段向量
		const Vector v_L1_P = _P - _L.mP1;//端点P1到点P的向量
		const Vector v_L2_P = _P - _L.mP2;//端点P2到点P的向量

		if (dcmp(Dot(v_P1_P2, v_L1_P))<0)
		{
			//向量 v_P1_P2 与 v_L1_P 的点积为负数,
			//则向量v_P1_P2与v_L1_P的夹角在90~270之间
			//点P在线段外，端点L1的外侧
			return Length(v_L1_P);
		}
		else if (dcmp(Dot(v_P1_P2, v_L2_P))>0)
		{
			//向量 v_P1_P2 与 v_L2_P 的点积为正数,
			//则向量v_P1_P2与v_L2_P的夹角在0~90或270~360之间
			//点P在线段外，端点L2的外侧
			return Length(v_L2_P);
		}
		//else
		//{
		//	//垂足在线段内，返回点到垂足的距离
		//	d_x = _P.mX - foot_x;
		//	d_y = _P.mY - foot_y;
		//	dis = sqrt(d_x*d_x + d_y*d_y);
		//}
		else
		{
			//面积除以底边长度为高
			return fabs(Cross(v_P1_P2, v_L1_P)) / Length(v_P1_P2);
		}

		return dis;
	};

	Polyline DouglasPeucker(const Polyline& _Line, double _Threshold)
	{
		Polyline cur;
		return cur;
	}

	void DistanceTest()
	{
		Point p(0, 0);
		Line l(1, 0, 0, 1);
		std::cout << Distance(p, l) << std::endl;
		std::cout << Distance(Point(0, 0), Line(1, 1, 2, 1)) << std::endl;
	}

	int GeometricAlgorithmTest() {
		/*  Testing data:
		polyline coordinates: [[0, 0], [1, -1], [2.5, -2], [4, -0.3], [5, 2], [3.5, 4]]
		threshold: 1.0
		*/
		DistanceTest();
	
		return 0;
	}	
}
