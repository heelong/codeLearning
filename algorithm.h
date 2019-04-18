// (1) ��ɺ���Distance�������_P���߶�_L֮��ľ���
//        ��������1�� p = [0, 0], l = [[1, 0], [0, 1]]
//        ��������2�� p = [0, 0], l = [[1, 1], [2, 1]]
// (2) ��ɺ���DouglasPeucker��ʵ������㴮�ĳ�ϡ


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

	//�������������С��0Ϊ�۽ǣ�����0Ϊ���
	/*�����ĵ�����ֽ� ��� / �ڻ� / ������ /����a��b=|a||b|��cos��
	�������壺����a������b�����ϵ�ͶӰ������b��ģ�ĳ�
	���깫ʽ��A.x*B.x+A.y*B.y;   */
	inline double Dot(const Point& A, const Point& B)
	{
		return A.mX*B.mX + A.mY*B.mY;
	}

	//������������
	inline double Length(const Point& A)
	{
		return sqrt(Dot(A, A));
	}

	/*�����Ĳ�����ֽ� ʸ�� / ��� / ������ /����a��b=|a||b|��sin��
	�������壺��ֱa��b���ڣ�����a,b���ɵ�ƽ���ı��ε����
	���깫ʽ�� A.x*B.y-B.x*A.y   */
	//�����������,�����ųɵ�ƽ���ı��ε����
	inline double Cross(const Point& A, const Point& B)
	{
		return A.mX*B.mY - B.mX*A.mY;
	}

	/*������ת  ��ʽ x=x'*cos(rad)-y'*sin(rad)  
	 *				 y=x'*sin(rad)+y'*cos(rad) 
	 *				 radΪҪ��ת�ĽǶȣ���λΪ���ȣ�*/
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

		//����
		double foot_x = k*d_x + _P.mX;
		double foot_y = k*d_x + _P.mX;

		const Vector v_P1_P2 = _L.mP2 - _L.mP1;//�߶�����
		const Vector v_L1_P = _P - _L.mP1;//�˵�P1����P������
		const Vector v_L2_P = _P - _L.mP2;//�˵�P2����P������

		if (dcmp(Dot(v_P1_P2, v_L1_P))<0)
		{
			//���� v_P1_P2 �� v_L1_P �ĵ��Ϊ����,
			//������v_P1_P2��v_L1_P�ļн���90~270֮��
			//��P���߶��⣬�˵�L1�����
			return Length(v_L1_P);
		}
		else if (dcmp(Dot(v_P1_P2, v_L2_P))>0)
		{
			//���� v_P1_P2 �� v_L2_P �ĵ��Ϊ����,
			//������v_P1_P2��v_L2_P�ļн���0~90��270~360֮��
			//��P���߶��⣬�˵�L2�����
			return Length(v_L2_P);
		}
		//else
		//{
		//	//�������߶��ڣ����ص㵽����ľ���
		//	d_x = _P.mX - foot_x;
		//	d_y = _P.mY - foot_y;
		//	dis = sqrt(d_x*d_x + d_y*d_y);
		//}
		else
		{
			//������Եױ߳���Ϊ��
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
