#ifndef  FIGURE_H
#define  FIGURE_H


#include <QWidget>

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


class CFigure
{
public:
	virtual void Draw(QPixmap &pixmap) {}
	void setPaintStyle(paintstyle m_style)
	{
		style = m_style;
	}
	paintstyle style;
};

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


#endif // ! FIGURE_H