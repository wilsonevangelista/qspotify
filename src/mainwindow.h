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
#include <QListWidgetItem>

#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <QFile>

#include "spotifyapi.h"
#include "playlist.h"
#include "track.h"
#include "playlistmanagerdialog.h"
#include "playlistfilemanager.h"

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

	void on_btnPlay_pressed();

	void on_btnStop_pressed();

	void on_btnNext_pressed();

	void on_btnPrev_pressed();

	void on_playlistWidget_itemClicked(QListWidgetItem *item);

private:
	Ui::MainWindow *ui;
	QMediaPlayer *player;
	QMediaPlaylist *mediaPlaylist;
	//QString configLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
	QString filename = "playlists.json";
	QMap<QUuid, PlayList> playlists;
};

#endif // MAINWINDOW_H
