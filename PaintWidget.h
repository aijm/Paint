#ifndef  PAINTWIDGET_H
#define  PAINTWIDGET_H
#include <vector>
#include <QWidget>
#include <Figure.h>
using namespace std;
enum PaintMode { CLINE, CRECT, CELLIPSE, CPOLYGON, CFREEHAND }; //图形选项
class PaintWidget :public QWidget
{
	Q_OBJECT
public:
	PaintWidget(QWidget *parent = 0);
	~PaintWidget();
	void setPaintMode(PaintMode paintmode)
	{
		m_paintmode = paintmode;
	}
	void setPaintStyle(paintstyle style)
	{
		m_paintstyle = style;
	}
	
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	
private:
	QPixmap *m_pixmap;
	CFigure *m_currentfig;
	CPolygon *m_polygon;
	vector<CFigure*> m_FigrueArray; //保存图形指针
	vector<QPoint> vertex;
	QPoint m_lastPos;
	paintstyle m_paintstyle;
	PaintMode m_paintmode = CELLIPSE; //默认为椭圆
	bool m_leftpressed = false;
};


#endif // ! PAINTWIDGET_H
