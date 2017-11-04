#include <Figure.h>
#include <QPainter>
#include <iostream>
#include <assert.h>
#include <list>
typedef list<LineNode> LINEList;
using namespace std;
void CLine::Draw(QPixmap &pixmap)
{
	QPen pen;
	pen.setColor(QColor(style.r(), style.g(), style.b()));
	//cout << style.r() << ", " << style.g() << ", " << style.b() << endl;
	pen.setWidth(style.w());

	QPainter painter(&pixmap);
	painter.setPen(pen);
 
	if(antialiasing)
	{
	    //直线反走样，每一步通过直线上下两端像素点与直线的距离，计算颜色，距离近的颜色深
		//cout << "antialiasing" << endl;
		int x = m_x1;
		int y = m_y1;

		int dx = abs(m_x2 - m_x1);  //x间距
		int dy = abs(m_y2 - m_y1);  //y间距


		int sx = (m_x2 > m_x1) ? 1 : -1; //x方向步进
		int sy = (m_y2 > m_y1) ? 1 : -1; //y方向步进

		bool xychanged = (dy > dx) ? true : false; //x、y方向是否交换
												   //斜率绝对值大于1时，交换x,y
		if (dy>dx)
		{
			int temp = dx;
			dx = dy;
			dy = temp;
		}
		int e = 2 * dy - dx;  //初始误差


		painter.drawPoint(x, y);
		
		for (int i = 0; i<dx; ++i)
		{
			double ratio = 1.0*(dx + e) / 2 / dx;
			
			
			//将RGB转换到HSV,以便通过饱和度改变颜色深浅实现反走样
			QColor hsv = QColor(style.r(), style.g(), style.b()).toHsv();
			
			//根据到直线的距离调整饱和度
			if(ratio!=0)
			{
				//黑色无法通过改变饱和度，需要通过亮度调节
				if (style.r() == 0 && style.g() == 0 && style.b() == 0)
					hsv.setHsv(0, 0, static_cast<int>((1 - ratio) * 255));
				else
					hsv.setHsv(hsv.hsvHue(), static_cast<int>(hsv.saturation()*ratio), hsv.value());
				pen.setColor(hsv.toRgb());
				painter.setPen(pen);
				painter.drawPoint(x + sx, y + sy);
			}
			
			if(ratio!=1)
			{
				hsv = QColor(style.r(), style.g(), style.b()).toHsv();
				if (style.r() == 0 && style.g() == 0 && style.b() == 0)
					hsv.setHsv(0, 0, static_cast<int>((ratio) * 255));
				else
					hsv.setHsv(hsv.hsvHue(), static_cast<int>(hsv.saturation()*(1 - ratio)), hsv.value());
				pen.setColor(hsv.toRgb());
				painter.setPen(pen);
				if (xychanged)	painter.drawPoint(x, y + sy);
				else painter.drawPoint(x + sx, y);
			}
			
				
			if(e+2*dy<dx)
			{
				if (xychanged) y += sy;
				else x += sx;
				e += 2 * dy;
			}
			else
			{
				x += sx;
				y += sy;
				e += 2 * (dy - dx);
			}
			
		}
		pen.setColor(QColor(style.r(), style.g(), style.b()));
		painter.setPen(pen);
		painter.drawPoint(m_x2, m_y2);
	}
	else
	{
		int x = m_x1;
		int y = m_y1;

		int dx = abs(m_x2 - m_x1);  //x间距
		int dy = abs(m_y2 - m_y1);  //y间距


		int sx = (m_x2 > m_x1) ? 1 : -1; //x方向步进
		int sy = (m_y2 > m_y1) ? 1 : -1; //y方向步进

		bool xychanged = (dy > dx) ? true : false; //x、y方向是否交换
												   //斜率绝对值大于1时，交换x,y
		if (dy>dx)
		{
			int temp = dx;
			dx = dy;
			dy = temp;
		}
		int e = 2 * dy - dx;  //初始误差


		painter.drawPoint(x, y);
		for (int i = 0; i<dx; ++i)
		{

			if (e >= 0)
			{
				x += sx;
				y += sy;
				e += 2 * (dy - dx);
			}
			else {
				if (xychanged) y += sy;
				else x += sx;

				e += 2 * dy;
			}
			painter.drawPoint(x, y);
		}
	}
	


	//painter.drawLine(m_x1, m_y1, m_x2, m_y2);
}

void CRect::Draw(QPixmap &pixmap)
{

	CLine lineleft(m_left, m_up, m_left, m_down);
	CLine lineright(m_right, m_up, m_right, m_down);
	CLine lineup(m_left, m_up, m_right, m_up);
	CLine linedown(m_left, m_down, m_right, m_down);
	lineleft.setPaintStyle(style);
	lineright.setPaintStyle(style);
	lineup.setPaintStyle(style);
	linedown.setPaintStyle(style);
	lineleft.setAntialiasing(antialiasing);
	lineright.setAntialiasing(antialiasing);
	lineup.setAntialiasing(antialiasing);
	linedown.setAntialiasing(antialiasing);

	lineleft.Draw(pixmap);
	lineright.Draw(pixmap);
	lineup.Draw(pixmap);
	linedown.Draw(pixmap);
	//painter.drawRect(m_left, m_up, m_right - m_left + 1, m_down - m_up + 1);
	
}

void CEllipse::Draw(QPixmap &pixmap)
{
	QPen pen;
	pen.setColor(QColor(style.r(), style.g(), style.b()));
	pen.setWidth(style.w());

	QPainter painter(&pixmap);
	painter.setPen(pen);
	//painter.drawEllipse(m_left, m_up, m_right - m_left + 1, m_down - m_up + 1);

	int xc = (m_left + m_right) / 2;
	int yc = (m_up + m_down) / 2;

	int a = abs(m_left - m_right)/2;
	int b = abs(m_up - m_down) / 2;
	/*if(a==b)
	{
		int radius = a;

		int x = 0, y = radius, d = 2 - 3 * radius;

		while (x <= y)
		{
			painter.drawPoint(QPoint(x, y) + QPoint(xc, yc));
			painter.drawPoint(QPoint(x, -y) + QPoint(xc, yc));
			painter.drawPoint(QPoint(-x, y) + QPoint(xc, yc));
			painter.drawPoint(QPoint(-x, -y) + QPoint(xc, yc));
			painter.drawPoint(QPoint(y, x) + QPoint(xc, yc));
			painter.drawPoint(QPoint(y, -x) + QPoint(xc, yc));
			painter.drawPoint(QPoint(-y, x) + QPoint(xc, yc));
			painter.drawPoint(QPoint(-y, -x) + QPoint(xc, yc));

			if (d < 0)
			{

				d += 4 * x + 6;
				x++;
			}
			else {
				d += 4 * (x - y) + 10;
				x++;
				y--;

			}
		}
	}*/

	int sa = a*a;
	int sb = b*b;

	int x = 0, y = b, d = 4 * sb + (1 - 4 * b)*sa;
    //椭圆反走样
	if(antialiasing)
	{
		painter.drawPoint(QPoint(x, y) + QPoint(xc, yc));
		painter.drawPoint(QPoint(x, -y) + QPoint(xc, yc));
		painter.drawPoint(QPoint(-x, y) + QPoint(xc, yc));
		painter.drawPoint(QPoint(-x, -y) + QPoint(xc, yc));
		//斜率绝对值小于1的部分
		while(sb*(x+1)<sa*(y+1))
		{
			++x;
			double ycross = sqrt(sb*(1 - 1.0*x*x / sa));
			
			double ratio = 1.0*y - ycross;
			ratio = ratio < 1 ? ratio : 0.8;
			ratio = ratio > 0 ? ratio : 0.2;
			
			//将RGB转换到HSV,以便通过饱和度改变颜色深浅实现反走样
			QColor hsv = QColor(style.r(), style.g(), style.b()).toHsv();

			//根据到椭圆的距离调整饱和度
			if (ratio != 0)
			{
				//黑色无法通过改变饱和度，需要通过亮度调节
				if (style.r() == 0 && style.g() == 0 && style.b() == 0)
					hsv.setHsv(0, 0, static_cast<int>((1 - ratio) * 255));
				else
					hsv.setHsv(hsv.hsvHue(), static_cast<int>(hsv.saturation()*ratio), hsv.value());
				pen.setColor(hsv.toRgb());
				painter.setPen(pen);
				painter.drawPoint(QPoint(x, y - 1)+QPoint(xc,yc));
				painter.drawPoint(QPoint(-x, y - 1) + QPoint(xc, yc));
				painter.drawPoint(QPoint(x, 1-y) + QPoint(xc, yc));
				painter.drawPoint(QPoint(-x, 1-y) + QPoint(xc, yc));
				
			}

			if (ratio != 1)
			{
				hsv = QColor(style.r(), style.g(), style.b()).toHsv();
				if (style.r() == 0 && style.g() == 0 && style.b() == 0)
					hsv.setHsv(0, 0, static_cast<int>((ratio) * 255));
				else
					hsv.setHsv(hsv.hsvHue(), static_cast<int>(hsv.saturation()*(1 - ratio)), hsv.value());
				pen.setColor(hsv.toRgb());
				painter.setPen(pen);
				painter.drawPoint(QPoint(x, y) + QPoint(xc, yc));
				painter.drawPoint(QPoint(x, -y) + QPoint(xc, yc));
				painter.drawPoint(QPoint(-x, y) + QPoint(xc, yc));
				painter.drawPoint(QPoint(-x, -y) + QPoint(xc, yc));
				
			}
			if(sb*(x+1)*(x+1)+sa*(y-1)*(y-1)-sa*sb>=0)
			{
				--y;
			}

		}
	    //斜率绝对值大于1的一段
		while(y>1)
		{
			--y;
			double xcross = sqrt(sa*(1 - 1.0*y*y / sb));
			double ratio =  1.0*x + 1 - xcross;
			ratio = ratio < 1 ? ratio : 0.8;
			ratio = ratio > 0 ? ratio : 0.2;
			//将RGB转换到HSV,以便通过饱和度改变颜色深浅实现反走样
			QColor hsv = QColor(style.r(), style.g(), style.b()).toHsv();

			//根据到椭圆的距离调整饱和度
			if (ratio != 0)
			{
				//黑色无法通过改变饱和度，需要通过亮度调节
				if (style.r() == 0 && style.g() == 0 && style.b() == 0)
					hsv.setHsv(0, 0, static_cast<int>((1 - ratio) * 255));
				else
					hsv.setHsv(hsv.hsvHue(), static_cast<int>(hsv.saturation()*ratio), hsv.value());
				pen.setColor(hsv.toRgb());
				painter.setPen(pen);
				painter.drawPoint(QPoint(x, y) + QPoint(xc, yc));
				painter.drawPoint(QPoint(x, -y) + QPoint(xc, yc));
				painter.drawPoint(QPoint(-x, y) + QPoint(xc, yc));
				painter.drawPoint(QPoint(-x, -y) + QPoint(xc, yc));

			}

			if (ratio != 1)
			{
				hsv = QColor(style.r(), style.g(), style.b()).toHsv();
				if (style.r() == 0 && style.g() == 0 && style.b() == 0)
					hsv.setHsv(0, 0, static_cast<int>((ratio) * 255));
				else
					hsv.setHsv(hsv.hsvHue(), static_cast<int>(hsv.saturation()*(1 - ratio)), hsv.value());
				pen.setColor(hsv.toRgb());
				painter.setPen(pen);
				painter.drawPoint(QPoint(x+1, y) + QPoint(xc, yc));
				painter.drawPoint(QPoint(x+1, -y) + QPoint(xc, yc));
				painter.drawPoint(QPoint(-x-1, y) + QPoint(xc, yc));
				painter.drawPoint(QPoint(-x-1, -y) + QPoint(xc, yc));

			}
			if (sb*(x + 1)*(x + 1) + sa*(y - 1)*(y - 1) - sa*sb <= 0)
			{
				++x;
			}
		}
		painter.drawPoint(QPoint(a, 0) + QPoint(xc, yc));
		painter.drawPoint(QPoint(-a, 0) + QPoint(xc, yc));

	}

	else
	{
		//斜率绝对值<1的一段
		while (2 * sb*(x + 1)<sa*(2 * y - 1))
		{
			//cout << "x:" << x + xc << ", y:" << y + yc << endl;
			painter.drawPoint(QPoint(x, y) + QPoint(xc, yc));
			painter.drawPoint(QPoint(x, -y) + QPoint(xc, yc));
			painter.drawPoint(QPoint(-x, y) + QPoint(xc, yc));
			painter.drawPoint(QPoint(-x, -y) + QPoint(xc, yc));

			if (d<0)
			{
				d += 4 * sb*(2 * x + 3);
				x++;
			}
			else {
				d += 4 * (sb*(2 * x + 3) + sa*(2 - 2 * y));
				x++;
				y--;
			}

		}
		d = sb*(4 * x*x + 4 * x + 1) + 4 * sa*(y - 1)*(y - 1) - 4 * sa*sb;
		//斜率绝对值大于1的一段
		while (y>0)
		{
			painter.drawPoint(QPoint(x, y) + QPoint(xc, yc));
			painter.drawPoint(QPoint(x, -y) + QPoint(xc, yc));
			painter.drawPoint(QPoint(-x, y) + QPoint(xc, yc));
			painter.drawPoint(QPoint(-x, -y) + QPoint(xc, yc));

			if (d<0)
			{
				d += 4 * sb*(2 * x + 2) + 4 * sa*(3 - 2 * y);
				x++;
				y--;
			}
			else
			{
				d += 4 * sa*(3 - 2 * y);
				y--;
			}
		}
		painter.drawPoint(QPoint(a, 0) + QPoint(xc, yc));
		painter.drawPoint(QPoint(-a, 0) + QPoint(xc, yc));
	}
	
	
	
	
}

void CPolygon::Draw(QPixmap &pixmap)
{
	//cout << "点个数：" << m_vertex.size() - 1 << endl;
	if (m_vertex.size() < 2) return;
	LINEList linelist;
	int i = 0;
	for (i = 0; i < m_vertex.size() - 1; ++i)
	{
		CLine line(m_vertex[i].x(), m_vertex[i].y(), m_vertex[i + 1].x(), m_vertex[i + 1].y());
		line.setPaintStyle(style);
		line.setAntialiasing(antialiasing);
		line.Draw(pixmap);

		
		LineNode linenode; //边的x,ymax,ymin,upx信息
		if (m_vertex[i].y() < m_vertex[i + 1].y())
		{
			linenode.ymax = m_vertex[i + 1].y(); //ymax
			linenode.ymin = m_vertex[i].y();   //ymin
			linenode.x = m_vertex[i].x();
			linenode.upx = m_vertex[i + 1].x();
			linenode.dx = 1.0*(m_vertex[i].x() - m_vertex[i + 1].x()) / (m_vertex[i].y() - m_vertex[i + 1].y());
		}
		else if (m_vertex[i].y() == m_vertex[i + 1].y())
		{
			linenode.ymax = m_vertex[i].y();
			linenode.ymin = m_vertex[i].y();   //ymin
			linenode.dx = 0;
			linenode.upx = m_vertex[i].x();
			linenode.x = m_vertex[i].x() < m_vertex[i + 1].x() ? m_vertex[i].x() : m_vertex[i + 1].x();
		}
		else
		{
			linenode.ymax = m_vertex[i].y();
			linenode.ymin = m_vertex[i + 1].y();   //ymin
			linenode.x = m_vertex[i + 1].x();
			linenode.upx = m_vertex[i].x();
			linenode.dx = 1.0*(m_vertex[i].x() - m_vertex[i + 1].x()) / (m_vertex[i].y() - m_vertex[i + 1].y());
		}

		linelist.push_back(linenode);
	}
	if (isclosed)
	{
		CLine line(m_vertex[0].x(), m_vertex[0].y(), m_vertex[i].x(), m_vertex[i].y());
		line.setPaintStyle(style);
		line.setAntialiasing(antialiasing);
		line.Draw(pixmap);

		LineNode linenode;
		if (m_vertex[i].y() < m_vertex[0].y())
		{
			linenode.ymax = m_vertex[0].y();
			linenode.ymin = m_vertex[i].y();   //ymin
			linenode.x = m_vertex[i].x();
			linenode.upx = m_vertex[0].x();
			linenode.dx = 1.0*(m_vertex[i].x() - m_vertex[0].x()) / (m_vertex[i].y() - m_vertex[0].y());
		}
		else if (m_vertex[i].y() == m_vertex[0].y())
		{
			linenode.ymax = m_vertex[i].y();
			linenode.ymin = m_vertex[i].y();   //ymin
			linenode.dx = 0;
			linenode.upx = m_vertex[i].x();
			linenode.x = m_vertex[i].x() < m_vertex[0].x() ? m_vertex[i].x() : m_vertex[0].x();
		}
		else
		{
			linenode.ymax = m_vertex[i].y();
			linenode.ymin = m_vertex[0].y();   //ymin
			linenode.x = m_vertex[0].x();
			linenode.upx = m_vertex[i].x();
			linenode.dx = 1.0*(m_vertex[i].x() - m_vertex[0].x()) / (m_vertex[i].y() - m_vertex[0].y());
		}

		linelist.push_back(linenode);
		
	}
	//多边形扫描转换
	if(isclosed)
	{
		
		//cout << "start polygon brush" << endl;
		QPen pen;
		pen.setColor(QColor(style.r(), style.g(), style.b()));
		
		pen.setWidth(style.w());

		QPainter painter(&pixmap);
		painter.setPen(pen);

		int ymin = (*(linelist.begin())).ymin;
		int ymax= (*(linelist.begin())).ymax;
		
	    for(auto linenode:linelist)
		{
			if (linenode.ymin < ymin) ymin = linenode.ymin;
			else{}
			if (linenode.ymax > ymax) ymax = linenode.ymax;
			else{}
		}
		//cout << "边数目"<<linelist.size() << endl;
		
		vector<LINEList> NET(ymax - ymin + 1);
		//创建新边表，将ymin=扫描线y值的边加入对应的扫描线作为新边
		for(int i=0;i<NET.size();++i)
		{
			for(auto linenode:linelist)
			{
				if (linenode.ymin == i + ymin) NET[i].push_back(linenode);
			}
		}
		
		
		LINEList AET; //活动边表
		
		for(int i=0;i<NET.size();++i)
		{
			//将扫描线对应新边表插入活动边表
			for (auto linenode : NET[i]) AET.push_back(linenode);
		    //按x值递增排序
			AET.sort();

			
			vector<double> xvalue;
		    //遍历活动边表，若已达到某条边ymax，则将其x置为upx
			//(因为dx是double型，不这样做的话，无法判断x相同的两条边)
			for (auto& temp : AET)  //需要用引用，否则无法改变值
				if (temp.ymax == i + ymin) temp.x = temp.upx;
			for(auto it=AET.begin();it!=AET.end();++it)
			{
				auto temp = it;
				++temp;
				
				if((*it).x==(*temp).x)
				{
					//如果有x值相同的情形，按情况取舍
					if (((*it).ymax <= i + ymin) && ((*temp).ymax <= i + ymin));
					else if (((*it).ymax > i + ymin) && ((*temp).ymax > i + ymin));
					else xvalue.push_back((*it).x);
					++it;
				}
				else
				{
					xvalue.push_back((*it).x);
				}
			}
			
			assert(xvalue.size() % 2 == 0);
			//每两点画线,例如0,1; 2,3;...
			if(xvalue.size())
			{
				for (int k = 0; k<xvalue.size() - 1; k+=2)
				{
					
					for (int j = xvalue[k]; j<xvalue[k + 1]; ++j)
					{
						painter.drawPoint(j, i + ymin);
					}
				}
			}
			
			//遍历活动边表，若某条边的ymax与当前扫描线y值相等，则删除；否则，将x递增
			for(auto it=AET.begin();it!=AET.end();++it)
			{
				if ((*it).ymax == i + ymin) AET.erase(it);
				else (*it).x += (*it).dx;
			}
		
		}


	}
	
	
}


//void CFreehand::Draw(QPixmap & pixmap)
//{
//	QPen pen;
//	pen.setColor(QColor(style.r(), style.g(), style.b()));
//	pen.setWidth(style.w());
//
//	QPainter painter(&pixmap);
//	painter.setPen(pen);
//
//	for(auto vertex:m_vertex)
//	{
//		painter.drawPoint(vertex.x(), vertex.y());
//	}
//}
