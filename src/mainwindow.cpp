#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secrets.h"

MainWindow::MainWindow(QWidget *parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	statusBar()->showMessage("Obtendo token aguarde...");

	connect(&spotify, &SpotifyAPI::tokenOK, this, [=](QString token){
		statusBar()->showMessage("Token obtido!");
		spotify.searchMusic("Fear of the dark");
	});


	connect(&spotify, &SpotifyAPI::searchReturn, this, [=](QList<Track> &tracks){
		foreach (auto track, tracks) {
			qDebug() << track.toJSON();
		}
	});
}

MainWindow::~MainWindow()
{
	delete ui;
}


