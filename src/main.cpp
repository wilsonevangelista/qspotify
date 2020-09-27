#include "mainwindow.h"
#include <QStyle>
#include <QScreen>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	qRegisterMetaType<Track>();
	qRegisterMetaType<PlayList>();

	w.setGeometry(
		QStyle::alignedRect(
			Qt::LeftToRight,
			Qt::AlignCenter,
			w.size(),
			a.primaryScreen()->geometry()
		)
	);
	return a.exec();	
}
