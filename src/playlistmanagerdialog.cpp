#include "playlistmanagerdialog.h"
#include "ui_playlistmanagerdialog.h"

PlayListManagerDialog::PlayListManagerDialog(QWidget *parent):
	QDialog(parent),
	ui(new Ui::PlayListManagerDialog)
{	
	spotify = &((MainWindow *)parent)->spotify;
	playlist = ((MainWindow *)parent)->selectedPlaylist;
	ui->setupUi(this);
	setModal(true);
	setWindowTitle(playlist->getName());


	ui->lstPlaylist->clear();
	foreach (auto track, playlist->getTracks()) {
		auto item = new QListWidgetItem(track.toString());
		item->setData(Qt::UserRole, QVariant::fromValue<Track>(track));
		ui->lstPlaylist->addItem(item);
	}

	connect(spotify, &SpotifyAPI::searchReturn, this, [=](QList<Track> &tracks){
		ui->lstSearch->clear();
		ui->labelTotal->setText("Mostrando do " + QString::number(spotify->offset) + " até  "
								+ QString::number(20 + spotify->offset) + " de " + QString::number(spotify->total));

		foreach (auto track, tracks) {
			auto item = new QListWidgetItem(track.toString());
			item->setData(Qt::UserRole, QVariant::fromValue<Track>(track));
			ui->lstSearch->addItem(item);
		}

	});
}

PlayListManagerDialog::~PlayListManagerDialog()
{
	delete ui;
}

void PlayListManagerDialog::on_btnSearch_pressed()
{
	spotify->searchMusic(ui->leQuery->text());
}

void PlayListManagerDialog::on_btnClose_pressed()
{
	close();
}

void PlayListManagerDialog::on_btnNext_pressed()
{
	spotify->searchNext();
}

void PlayListManagerDialog::on_btnPrev_pressed()
{
	spotify->searchPrevious();
}

void PlayListManagerDialog::on_btnAdd_pressed()
{
	auto selected = ui->lstSearch->currentItem();
	if(selected != nullptr){
		ui->lstPlaylist->addItem(selected->clone());
		delete selected;
		ui->lstPlaylist->update();
		//qDebug() << selected->data(Qt::UserRole).value<Track>().toString();
	}
}

void PlayListManagerDialog::on_btnDelTrack_pressed()
{
	auto selected = ui->lstPlaylist->currentItem();
	if(selected != nullptr){
		delete selected;
	}
}

void PlayListManagerDialog::on_btnSave_pressed()
{
	ui->lstPlaylist->setSelectionMode(QListWidget::SelectionMode::MultiSelection);
	ui->lstPlaylist->selectAll();
	auto items = ui->lstPlaylist->selectedItems();

	playlist->clearTracks();
	foreach (auto item, items) {
		playlist->addTrack(item->data(Qt::UserRole).value<Track>());
	}
	close();
}
