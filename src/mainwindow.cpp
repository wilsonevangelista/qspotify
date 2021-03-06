#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secrets.h"

MainWindow::MainWindow(QWidget *parent):
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	player(new QMediaPlayer),
	mediaPlaylist(new QMediaPlaylist())
{
	ui->setupUi(this);
	auto pls = PlaylistFileManager::loadPlaylists(filename);

	if (pls == nullptr) {
		QMessageBox::warning(this,"Atenção!", "Erro ao ler " + filename, QMessageBox::Ok);
	}

	playlists = *pls;

	foreach(auto pl, playlists)
		ui->cmbPlaylist->addItem(pl.getName(), pl.getUuid());

	statusBar()->showMessage("Obtendo token aguarde...");

	player->setVolume(100);

	connect(mediaPlaylist, &QMediaPlaylist::currentIndexChanged, this, [=](int idx){
		ui->playlistWidget->setCurrentRow(idx);
		ui->playlistWidget->update();

		if(idx == 0)
			ui->btnPrev->setEnabled(false);
		else
			ui->btnPrev->setEnabled(true);

		if(idx == mediaPlaylist->mediaCount() - 1)
			ui->btnNext->setEnabled(false);
		else
			ui->btnNext->setEnabled(true);

	});

	connect(&spotify, &SpotifyAPI::error, this, [=](QString msg, bool isNetworkError){
		QMessageBox::warning(this,"Atenção!", msg, QMessageBox::Ok);
		if(isNetworkError){
			ui->btnPlay->setEnabled(false);
			ui->playlistWidget->setEnabled(false);
		}

		statusBar()->showMessage("Erro!");
		ui->pushButton->setEnabled(false);
	});

	connect(&spotify, &SpotifyAPI::tokenOK, this, [=](QString token){
		statusBar()->showMessage("Token obtido!");
	});

}

MainWindow::~MainWindow()
{
	delete ui;
	delete player;
	delete mediaPlaylist;
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
		PlaylistFileManager::savePlaylists(filename, playlists);
	}
}

void MainWindow::on_cmbPlaylist_currentIndexChanged(int idx)
{
	if(ui->cmbPlaylist->itemData(idx).isNull()) return;

	QUuid uuid = ui->cmbPlaylist->itemData(idx).toUuid();
	selectedPlaylist = &playlists.find(uuid).value();

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
		QUuid uuid = ui->cmbPlaylist->itemData(idx).toUuid();

		ui->playlistWidget->clear();
		ui->cmbPlaylist->removeItem(idx);
		playlists.remove(uuid);
		ui->cmbPlaylist->setCurrentIndex( idx > 0 ? idx - 1 : 0);

		//selectedPlaylist = nullptr;
		statusBar()->showMessage(plName + " removida!", 5000);
		PlaylistFileManager::savePlaylists(filename, playlists);
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
		PlaylistFileManager::savePlaylists(filename, playlists);
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
	on_btnStop_pressed();
}

void MainWindow::on_btnPlay_pressed()
{
	mediaPlaylist->clear();
	foreach (auto track, selectedPlaylist->getTracks()) {
		mediaPlaylist->addMedia(QUrl(track.getPreviewUrl()));
	}

	player->setPlaylist(mediaPlaylist);
	player->play();
	ui->btnStop->setEnabled(true);
	ui->btnPlay->setEnabled(false);
	ui->btnNext->setEnabled(true);
	ui->btnPrev->setEnabled(false);
}

void MainWindow::on_btnStop_pressed()
{
	player->stop();
	ui->btnStop->setEnabled(false);
	ui->btnNext->setEnabled(false);
	ui->btnPrev->setEnabled(false);

	if(selectedPlaylist->getTracks().count() > 0){
		ui->btnPlay->setEnabled(true);
	}
}

void MainWindow::on_btnNext_pressed()
{
	mediaPlaylist->next();
}

void MainWindow::on_btnPrev_pressed()
{
	mediaPlaylist->previous();
}

void MainWindow::on_playlistWidget_itemClicked(QListWidgetItem *item)
{
	mediaPlaylist->setCurrentIndex( ui->playlistWidget->currentRow() );
}
