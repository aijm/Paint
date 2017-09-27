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
	LineAct = new QAction(paintmodeGroup);
	LineAct->setIcon(QIcon(":/images/line.png"));
	connect(LineAct,SIGNAL(triggered()),this,SLOT(on_linetriggered()));

	RectAct = new QAction(paintmodeGroup);
	RectAct->setIcon(QIcon(":/images/rect.png"));
	connect(RectAct, SIGNAL(triggered()), this, SLOT(on_recttriggered()));

	EllipseAct = new QAction(paintmodeGroup);
	EllipseAct->setIcon(QIcon(":/images/ellipse.png"));
	connect(EllipseAct, SIGNAL(triggered()), this, SLOT(on_ellipsetriggered()));
	
	LineAct->setChecked(true);

	selectcolorAct = new QAction(QStringLiteral("颜色"), this);
	connect(selectcolorAct, SIGNAL(triggered()), this, SLOT(on_selectcolorAct()));

	/*paintmodeGroup->addAction(LineAct);
	paintmodeGroup->addAction(RectAct);
	paintmodeGroup->addAction(EllipseAct);*/

	paintmodeMenu = new QMenu(QStringLiteral("形状"),this);
	paintmodeMenu->addAction(LineAct);
	paintmodeMenu->addAction(RectAct);
	paintmodeMenu->addAction(EllipseAct);

	menuBar()->addMenu(paintmodeMenu);

	paintmodeBar = addToolBar(QStringLiteral("形状"));
	paintmodeBar->addAction(LineAct);
	paintmodeBar->addAction(RectAct);
	paintmodeBar->addAction(EllipseAct);

	colorBar = addToolBar(QStringLiteral("颜色"));
	colorBar->addAction(selectcolorAct);
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

void MainWindow::on_selectcolorAct()
{
	QColor color = QColorDialog::getColor(Qt::red, this, QStringLiteral("选择颜色"));
	m_paintstyle = paintstyle(color.red(), color.green(), color.blue(), m_paintstyle.w());
	m_paintwidget->setPaintStyle(m_paintstyle);
}

