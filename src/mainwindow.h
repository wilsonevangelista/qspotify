#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>

#include <QDesktopServices>

#include "spotifyapi.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void getUserInformation();
	void getOnlinePlaylists();

private:
	Ui::MainWindow *ui;
	QString configLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

	SpotifyAPI spotify;
};

#endif // MAINWINDOW_H
