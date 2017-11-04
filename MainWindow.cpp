#include <MainWindow.h>
#include <QAction>
#include <QActionGroup>
#include <QMenu>
#include <QToolBar>
#include <QMenuBar>
#include <QDialog>
#include <QColorDialog>
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowIcon(QIcon(":/images/paint.png"));
	CreateActions();
	m_paintwidget = new PaintWidget(this);
	setCentralWidget(m_paintwidget);
}

MainWindow::~MainWindow()
{
	
}

void MainWindow::CreateActions()
{
	paintmodeGroup = new QActionGroup(this);
	
	paintmodeGroup->setExclusive(true);

	FreehandAct = new QAction(paintmodeGroup);
	FreehandAct->setIcon(QIcon(":/images/freehand.png"));
	connect(FreehandAct, SIGNAL(triggered()), this, SLOT(on_freehandtriggered()));

	LineAct = new QAction(paintmodeGroup);
	LineAct->setIcon(QIcon(":/images/line2.png"));
	connect(LineAct,SIGNAL(triggered()),this,SLOT(on_linetriggered()));

	RectAct = new QAction(paintmodeGroup);
	RectAct->setIcon(QIcon(":/images/rect1.png"));
	connect(RectAct, SIGNAL(triggered()), this, SLOT(on_recttriggered()));

	EllipseAct = new QAction(paintmodeGroup);
	EllipseAct->setIcon(QIcon(":/images/ellipse1.png"));
	connect(EllipseAct, SIGNAL(triggered()), this, SLOT(on_ellipsetriggered()));
	
	PolygonAct = new QAction(paintmodeGroup);
	PolygonAct->setIcon(QIcon(":/images/polygon1.png"));
	connect(PolygonAct, SIGNAL(triggered()), this, SLOT(on_polygontriggered()));

	LineAct->setChecked(true);

	selectcolorAct = new QAction(this);
	selectcolorAct->setIcon(QIcon(":/images/color2.png"));
	connect(selectcolorAct, SIGNAL(triggered()), this, SLOT(on_selectcolorAct()));

	/*paintmodeGroup->addAction(LineAct);
	paintmodeGroup->addAction(RectAct);
	paintmodeGroup->addAction(EllipseAct);*/

	paintmodeMenu = new QMenu(QStringLiteral("形状"),this);
	paintmodeMenu->addAction(FreehandAct);
	paintmodeMenu->addAction(LineAct);
	paintmodeMenu->addAction(RectAct);
	paintmodeMenu->addAction(EllipseAct);
	paintmodeMenu->addAction(PolygonAct);

	menuBar()->addMenu(paintmodeMenu);

	paintmodeBar = addToolBar(QStringLiteral("形状"));
	paintmodeBar->addAction(FreehandAct);
	paintmodeBar->addAction(LineAct);
	paintmodeBar->addAction(RectAct);
	paintmodeBar->addAction(EllipseAct);
	paintmodeBar->addAction(PolygonAct);

	colorBar = addToolBar(QStringLiteral("颜色"));
	colorBar->addAction(selectcolorAct);
}


void MainWindow::on_freehandtriggered()
{
	m_paintwidget->setPaintMode(CFREEHAND);
}
void MainWindow::on_linetriggered()
{
	m_paintwidget->setPaintMode(CLINE);
}
void MainWindow::on_recttriggered()
{
	m_paintwidget->setPaintMode(CRECT);
}
void MainWindow::on_ellipsetriggered()
{
	m_paintwidget->setPaintMode(CELLIPSE);
}

void MainWindow::on_polygontriggered()
{
	m_paintwidget->setPaintMode(CPOLYGON);
}

void MainWindow::on_selectcolorAct()
{
	QColor color = QColorDialog::getColor(Qt::red, this, QStringLiteral("选择颜色"));
	m_paintstyle = paintstyle(color.red(), color.green(), color.blue(), m_paintstyle.w());
	m_paintwidget->setPaintStyle(m_paintstyle);
}

