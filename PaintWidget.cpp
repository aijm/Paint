#include <PaintWidget.h>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
using namespace std;
PaintWidget::PaintWidget(QWidget *parent)
	:QWidget(parent)
{
	setMinimumSize(600, 400);     //设置绘图区域窗体的最小大小
	setAutoFillBackground(true);    //自动设定背景颜色

	setPalette(QPalette(QColor(200,200,200)));      //设置调色板的颜色为白色

	m_pixmap = new QPixmap(this->size());    //这个pixmap对象用来接受准备绘制到空间的内容

	m_pixmap->fill(Qt::white);     //填充这个图片的背景是白色
	cout << "pixmapsize" << m_pixmap->width() << ", " << m_pixmap->height() << endl;
	

	m_currentfig = NULL;
}
PaintWidget::~PaintWidget()
{
	for(auto it=m_FigrueArray.begin();it!=m_FigrueArray.end();++it)
	{
		delete *it;
	}

}

void PaintWidget::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	m_pixmap->fill(Qt::white);
	cout <<"数量： "<< m_FigrueArray.size() << endl;
	//cout << "1" << endl;
	
	for(auto it=m_FigrueArray.begin();it!=m_FigrueArray.end();++it)
	{
		
		(*it)->Draw(*m_pixmap);
	}
	
	if(m_currentfig != NULL)
	{
		
		m_currentfig->Draw(*m_pixmap);
		//cout << "paintcurrent" << endl;
		
	}
	m_pixmap->save("pixmap.jpg");
	QPainter painter(this);
	painter.drawPixmap(QPoint(0, 0), *m_pixmap);
	
	//cout << "2" << endl;
}
void PaintWidget::mousePressEvent(QMouseEvent *event)
{
	cout << "mousepress" << endl;
    if(event->button()==Qt::LeftButton)
	{
		m_leftpressed = true;
		m_lastPos = event->pos();
	}
}
void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
	
	if(m_leftpressed)
	{
		//cout << "mousemove" << endl;
		m_currentfig = NULL;
		
		switch (m_paintmode)
		{
		case CLINE:   /*cout << "cline" << endl;*/ m_currentfig = new CLine(m_lastPos.x(), m_lastPos.y(), event->pos().x(), event->pos().y());
			break;
		case CRECT:   cout << "crect" << endl;  m_currentfig = new CRect(m_lastPos.x(), m_lastPos.y(), event->pos().x(), event->pos().y());
			break;
		case CELLIPSE:  cout << "cellipse" << endl; m_currentfig = new CEllipse(m_lastPos.x(), m_lastPos.y(), event->pos().x(), event->pos().y());
			break;
		default:
			break;
			
		}
		m_currentfig->setPaintStyle(m_paintstyle);
		update();
	}
}
void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
	
	if (event->button() == Qt::LeftButton)
	{
		//cout << "鼠标左键释放" << endl;
	    if(m_currentfig != NULL)
		{
			m_FigrueArray.push_back(m_currentfig);
			//cout << m_FigrueArray.size() << endl;
		}
		m_leftpressed = false;
	}
	update();
}

