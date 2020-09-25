#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secrets.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	statusBar()->showMessage("Obtendo token aguarde...");
	connect(&spotify, &SpotifyAPI::tokenOK, this, [=](QString token){
		statusBar()->showMessage("Token obtido!");
	});
}

MainWindow::~MainWindow()
{
	delete ui;
}


