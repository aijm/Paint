#include <Figure.h>
#include <QPainter>
#include <iostream>
using namespace std;
void CLine::Draw(QPixmap &pixmap)
{
	QPen pen;
	pen.setColor(QColor(style.r(), style.g(), style.b()));
	pen.setWidth(style.w());

	QPainter painter(&pixmap);
	painter.setPen(pen);
	painter.drawLine(m_x1, m_y1, m_x2, m_y2);
}

void CRect::Draw(QPixmap &pixmap)
{
	QPen pen;
	pen.setColor(QColor(style.r(), style.g(), style.b()));
	pen.setWidth(style.w());

	QPainter painter(&pixmap);
	painter.setPen(pen);
	painter.drawRect(m_left, m_up, m_right - m_left + 1, m_down - m_up + 1);
	
}

void CEllipse::Draw(QPixmap &pixmap)
{
	QPen pen;
	pen.setColor(QColor(style.r(), style.g(), style.b()));
	pen.setWidth(style.w());

	QPainter painter(&pixmap);
	painter.setPen(pen);
	painter.drawEllipse(m_left, m_up, m_right - m_left + 1, m_down - m_up + 1);
	
}