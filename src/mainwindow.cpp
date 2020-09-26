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

		int idx = ui->cmbPlaylist->findData(pl.getUuid());
		ui->cmbPlaylist->setCurrentIndex(idx);
	}
}

void MainWindow::on_cmbPlaylist_currentIndexChanged(int idx)
{
	if(ui->cmbPlaylist->itemData(idx).isNull()) return;

	QUuid uuid = ui->cmbPlaylist->itemData(idx).toUuid();
	selectedPlaylist = &playlists.find(uuid).value();
	QList<Track> tracks = selectedPlaylist->getTracks();

	statusBar()->showMessage("Selecionado: " + ui->cmbPlaylist->itemText(idx));

	updateSelectedPlaylist();
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
		ui->playlistWidget->clear();
		ui->cmbPlaylist->removeItem(idx);
		ui->cmbPlaylist->setCurrentIndex( idx > 0 ? idx - 1 : 0);
		selectedPlaylist = nullptr;
		statusBar()->showMessage(plName + " removida!", 5000);
	}
}

void MainWindow::on_pushButton_pressed()
{
	if (selectedPlaylist == nullptr){
		QMessageBox::warning(this,"Atenção!", "Selecione uma Playlist", QMessageBox::Ok);
	} else {
		auto search = new PlayListManagerDialog(this);
		search->exec();
		delete search;
		updateSelectedPlaylist();
	}
}

void MainWindow::updateSelectedPlaylist()
{
	ui->playlistWidget->clear();
	foreach (auto track, selectedPlaylist->getTracks()) {
		auto item = new QListWidgetItem(track.toString());
		item->setData(Qt::UserRole, QVariant::fromValue<Track>(track));
		ui->playlistWidget->addItem(item);
	}
}
