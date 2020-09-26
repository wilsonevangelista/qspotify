#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>

#include <QDesktopServices>
#include <QInputDialog>
#include <QMessageBox>

#include <QJsonDocument>
#include <QMap>
#include <QList>

#include "spotifyapi.h"
#include "playlist.h"
#include "track.h"
#include "playlistmanagerdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	PlayList *selectedPlaylist = nullptr;
	SpotifyAPI spotify;

private slots:
	void on_btnAddPlaylist_pressed();
	void on_cmbPlaylist_currentIndexChanged(int index);

	void on_btnDelPlaylist_pressed();

	void on_pushButton_pressed();

	void updateSelectedPlaylist();

private:
	Ui::MainWindow *ui;
	QString configLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
	QMap<QUuid, PlayList> playlists;
};

#endif // MAINWINDOW_H
