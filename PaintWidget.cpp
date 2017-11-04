#include <PaintWidget.h>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include <assert.h>
using namespace std;
PaintWidget::PaintWidget(QWidget *parent)
	:QWidget(parent)
{
	setMinimumSize(800, 600);     //���û�ͼ���������С��С
	setAutoFillBackground(true);    //�Զ��趨������ɫ

	setPalette(QPalette(QColor(200,200,200)));      //���õ�ɫ�����ɫΪ��ɫ

	m_pixmap = new QPixmap(this->size());    //���pixmap������������׼�����Ƶ��ռ������

	m_pixmap->fill(Qt::white);     //������ͼƬ�ı����ǰ�ɫ
	//cout << "pixmapsize" << m_pixmap->width() << ", " << m_pixmap->height() << endl;
	

	m_currentfig = NULL;
	m_polygon = NULL;
	
}
PaintWidget::~PaintWidget()
{
	//����ʱ���ͷ�vector��ÿ��ͼ��
	for(auto it=m_FigrueArray.begin();it!=m_FigrueArray.end();++it)
	{
		delete *it;
	}

}

void PaintWidget::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	m_pixmap->fill(Qt::white);
	//cout <<"������ "<< m_FigrueArray.size() << endl;
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
	//m_pixmap->save("pixmap.jpg");
	QPainter painter(this);
	painter.drawPixmap(QPoint(0, 0), *m_pixmap);
	
	//cout << "2" << endl;
}
void PaintWidget::mousePressEvent(QMouseEvent *event)
{
	//cout << "mousepress" << endl;
    if(event->button()==Qt::LeftButton)
	{
		/*m_leftpressed = true;*/
		m_lastPos = event->pos();
		if(m_paintmode==CFREEHAND)
		{
			vertex.push_back(m_lastPos);
		}
		else{}
		
		
		if(m_paintmode==CPOLYGON)
		{
			m_leftpressed = false;
			//vertex.push_back(m_lastPos);

			if(m_polygon==NULL)
			{
				//cout << "m_polygon is NULL" << endl;
				m_polygon = new CPolygon();
			}
			assert(m_polygon != NULL);

			
			m_polygon->isclosed = false;
			
			m_polygon->addVertex(m_lastPos);
			m_currentfig = m_polygon;
		
			m_currentfig->setPaintStyle(m_paintstyle);
	
			update();

		}
		else{
			m_leftpressed = true;
		}
	}
	if(event->button() == Qt::RightButton)
	{
		if(m_paintmode==CPOLYGON)
		{
			m_polygon->isclosed = true;
			m_currentfig = m_polygon;
			m_currentfig->setPaintStyle(m_paintstyle);
			m_FigrueArray.push_back(m_currentfig);
			m_currentfig = NULL;
			m_polygon = NULL;
		}
		update();
	}
}
void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
	
	if(m_leftpressed)
	{

		//cout << "mousemove" << endl;
		
		if(m_currentfig)
		{
			delete m_currentfig;
			m_currentfig = NULL;
		}
		
		
		switch (m_paintmode)
		{
		case CLINE:    m_currentfig = new CLine(m_lastPos.x(), m_lastPos.y(), event->pos().x(), event->pos().y());
			break;
		case CRECT:    m_currentfig = new CRect(m_lastPos.x(), m_lastPos.y(), event->pos().x(), event->pos().y());
			break;
		case CELLIPSE:  m_currentfig = new CEllipse(m_lastPos.x(), m_lastPos.y(), event->pos().x(), event->pos().y());
			break;
		case CFREEHAND: vertex.push_back(event->pos()); m_currentfig = new CPolygon(vertex);
		case CPOLYGON: break;
			
		default:
			break;
			
		}
		m_currentfig->setPaintStyle(m_paintstyle);
		update();
	}
}
void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
	
	if (event->button() == Qt::LeftButton&&m_leftpressed)
	{
		//����ͷ�ʱ������ǰ���Ƶ�ͼ�μ��뵽vector��
	    if(m_currentfig != NULL)
		{
			m_FigrueArray.push_back(m_currentfig);
			m_currentfig = NULL;
			vertex.clear();
			//cout << m_FigrueArray.size() << endl;
		}
		m_leftpressed = false;
	}
	update();
}

