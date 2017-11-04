#ifndef  FIGURE_H
#define  FIGURE_H


#include <QWidget>
#include <vector>
#include <iostream>

using namespace std;

//多边形边类，用于扫描转换
class LineNode
{
public:
	
	bool operator<( const LineNode& b) const
	{
		return x < b.x;
	}
	void print()
	{
		cout << "x=" << x << ", dx=" << dx << ", ymin=" << ymin << ", ymax=" << ymax << endl;
	}
	double x;  //ymin对应的x坐标
	double upx; //每条线ymax的顶点对应的x坐标
	double dx;  //y增加1时，对应的x增量
	double ymin; //边端点y坐标最小值
	double ymax; //边端点y坐标最大值
};


//画图的颜色、线宽
class paintstyle
{
public:
	paintstyle(int r=0,int g=0,int b=0,int width=1)
		:m_red(r),m_green(g),m_blue(b),m_width(width){}
	paintstyle(const paintstyle& style)
	{
		m_red = style.m_red;
		m_green = style.m_green;
		m_blue = style.m_blue;
		m_width = style.m_width;
	}
	int r() { return m_red; }
	int g() { return m_green; }
	int b() { return m_blue; }
	int w() { return m_width; }
private:
	int m_red, m_green, m_blue;
	int m_width;
};

//图形类
class CFigure
{
public:
	virtual void Draw(QPixmap &pixmap) {}  
	void setPaintStyle(paintstyle m_style)
	{
		style = m_style;
	}
	//是否开启反走样
	void setAntialiasing(bool TrueorFalse)
	{
		antialiasing = TrueorFalse;
	}
	paintstyle style;
	bool antialiasing = true;
};

//线类(继承CFigure)
class CLine:public CFigure
{
public:
	virtual void Draw(QPixmap &pixmap);
	//构造函数初始化列表
	CLine(int x1,int y1,int x2,int y2):
		m_x1(x1),m_y1(y1),m_x2(x2),m_y2(y2){}
	//拷贝构造函数
	CLine(const CLine& line)
	{
		this->m_x1 = line.m_x1;
		this->m_x2 = line.m_x2;
		this->m_y1 = line.m_y1;
		this->m_y2 = line.m_y2;   
	}
	//赋值构造函数
	CLine& CLine::operator=(const CLine& line)
	{
		this->m_x1 = line.m_x1;
		this->m_x2 = line.m_x2;
		this->m_y1 = line.m_y1;
		this->m_y2 = line.m_y2;
		return *this;
	}

private:
	int m_x1;
	int m_x2;
	int m_y1;
	int m_y2;
	
};

//矩形类(继承CFigure)
class CRect :public CFigure
{
public:
	virtual void Draw(QPixmap &pixmap);
	//构造函数初始化列表
	CRect(int left, int up, int right, int down) :
		m_left(left), m_up(up), m_right(right), m_down(down) {}
	//拷贝构造函数
	CRect(const CRect& Rect)
	{
		this->m_left = Rect.m_left;
		this->m_up = Rect.m_up;
		this->m_right = Rect.m_right;
		this->m_down = Rect.m_down;
	}
	//赋值构造函数
	CRect& CRect::operator=(const CRect& Rect)
	{
		this->m_left = Rect.m_left;
		this->m_up = Rect.m_up;
		this->m_right = Rect.m_right;
		this->m_down = Rect.m_down;
		return *this;
	}

private:
	int m_left;
	int m_up;
	int m_right;
	int m_down;
	
};

//椭圆类(继承CFigure)
class CEllipse :public CFigure
{
public:
	virtual void Draw(QPixmap &pixmap);
	//构造函数初始化列表
	CEllipse(int left, int up, int right, int down) :
		m_left(left), m_up(up), m_right(right), m_down(down) {}
	//拷贝构造函数
	CEllipse(const CEllipse& Ellipse)
	{
		this->m_left = Ellipse.m_left;
		this->m_up = Ellipse.m_up;
		this->m_right = Ellipse.m_right;
		this->m_down = Ellipse.m_down;
	}
	//赋值构造函数
	CEllipse& CEllipse::operator=(const CEllipse& Ellipse)
	{
		this->m_left = Ellipse.m_left;
		this->m_up = Ellipse.m_up;
		this->m_right = Ellipse.m_right;
		this->m_down = Ellipse.m_down;
		return *this;
	}

private:
	int m_left;
	int m_up;
	int m_right;
	int m_down;
};

class CPolygon :public CFigure
{

public:
	CPolygon() {}
	bool isclosed = false;
	CPolygon(vector<QPoint> vertex) :m_vertex(vertex){}
	virtual void Draw(QPixmap &pixmap);

	CPolygon(const CPolygon& polygon)
	{
		m_vertex = polygon.m_vertex;
	}
	CPolygon& operator=(const CPolygon& polygon)
	{
		m_vertex = polygon.m_vertex;
		return *this;
	}

	void addVertex(const QPoint& vertex)
	{
		m_vertex.push_back(vertex);
	}
	void addVertex(int x,int y)
	{
		QPoint vertex(x, y);
		m_vertex.push_back(vertex);
	}


private:
	vector<QPoint> m_vertex;

};

//class CFreehand:public CFigure
//{
//public:
//	virtual void Draw(QPixmap &pixmap);
//	CFreehand(vector<QPoint> vertex) :m_vertex(vertex) {}
//	CFreehand(const CFreehand& freehand)
//	{
//		m_vertex = freehand.m_vertex;
//	}
//	CFreehand& operator=(const CFreehand& freehand)
//	{
//		m_vertex = freehand.m_vertex;
//		return *this;
//	}
//
//	void addVertex(const QPoint& vertex)
//	{
//		m_vertex.push_back(vertex);
//	}
//	void addVertex(int x, int y)
//	{
//		QPoint vertex(x, y);
//		m_vertex.push_back(vertex);
//	}
//
//private:
//	vector<QPoint> m_vertex;
//
//};
#endif // ! FIGURE_H