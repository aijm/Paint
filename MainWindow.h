#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <PaintWidget.h>
#include <QActionGroup>
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	void CreateActions();

	private slots:
	void on_freehandtriggered();
	void on_linetriggered();
	void on_recttriggered();
	void on_ellipsetriggered();
	void on_polygontriggered();
	void on_selectcolorAct();

private:
	PaintWidget *m_paintwidget;
	QActionGroup *paintmodeGroup;
	QAction *FreehandAct;
	QAction *LineAct;
	QAction *RectAct;
	QAction *EllipseAct;
	QAction *PolygonAct;
	

	QAction *selectcolorAct;
	QMenu *paintmodeMenu;
	QToolBar *paintmodeBar;

	QToolBar *colorBar;
	
	paintstyle m_paintstyle=paintstyle(0, 0, 0, 1);

};

#endif // MAINWINDOW_H
