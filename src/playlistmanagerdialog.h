#ifndef SEARCHTRACKDIALOG_H
#define SEARCHTRACKDIALOG_H

#include <QDialog>

#include "mainwindow.h"
#include "playlist.h"
#include "track.h"
#include "spotifyapi.h"

namespace Ui {
class PlayListManagerDialog;
}

class PlayListManagerDialog : public QDialog
{
	Q_OBJECT

public:
	explicit PlayListManagerDialog(QWidget *parent = nullptr);
	~PlayListManagerDialog();

private slots:
	void on_btnSearch_pressed();

	void on_btnClose_pressed();

	void on_btnNext_pressed();

	void on_btnPrev_pressed();

	void on_btnAdd_pressed();

	void on_btnDelTrack_pressed();

	void on_btnSave_pressed();

private:
	Ui::PlayListManagerDialog *ui;
	PlayList *playlist;
	SpotifyAPI *spotify;
};

#endif // SEARCHTRACKDIALOG_H
