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
		//spotify.searchMusic("Fear of the dark");
	});

	connect(&spotify, &SpotifyAPI::searchReturn, this, [=](QList<Track> &tracks){
		foreach (auto track, tracks) {
			qDebug() << QJsonDocument::fromJson(track.toJSON());
		}
	});
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_btnAddPlaylist_pressed()
{
	bool ok;
	QString nomePlaylist = QInputDialog::getText(this, "Nova Playlist", "Nome da playlist:", QLineEdit::Normal,"", &ok);
	if (ok && !nomePlaylist.isEmpty())
	{
		PlayList pl(nomePlaylist);
		playlists.insert(pl.getUuid(), pl);
		ui->cmbPlaylist->addItem(nomePlaylist, pl.getUuid());

		int index = ui->cmbPlaylist->findData(pl.getUuid());
		ui->cmbPlaylist->setCurrentIndex(index);
	}
}

void MainWindow::on_cmbPlaylist_currentIndexChanged(int index)
{
	if(ui->cmbPlaylist->itemData(index).isNull()) return;

	QUuid uuid = ui->cmbPlaylist->itemData(index).toUuid();
	statusBar()->showMessage("Selecionado: " + ui->cmbPlaylist->itemText(index));

	PlayList pl = playlists.find(uuid).value();
	QList<Track> tracks = pl.getTracks();

	foreach (auto track, tracks) {
		qDebug() << QJsonDocument::fromJson(track.toJSON());
	}
}

void MainWindow::on_btnDelPlaylist_pressed()
{
	auto idx = ui->cmbPlaylist->currentIndex();
	if (idx < 0) return;

	QMessageBox msgBox;
	QString plName = ui->cmbPlaylist->itemText(idx);

	msgBox.setText("Confirmação");
	msgBox.setInformativeText(QString("Deseja remover a playlist <b>\"").append(plName).append("\"</b>?"));
	msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
	msgBox.setDefaultButton(QMessageBox::Yes);
	int ret = msgBox.exec();
	if(ret == QMessageBox::Yes) {
		ui->cmbPlaylist->removeItem(idx);
		ui->cmbPlaylist->setCurrentIndex(idx - 1);
		statusBar()->showMessage(plName + " removida!", 5000);
	}
}
