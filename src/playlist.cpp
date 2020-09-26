#include "playlist.h"

PlayList::PlayList()
{
	tracks = new QList<Track>();
}

PlayList::~PlayList(){
	delete tracks;
}

QList<Track>* PlayList::getTracks()
{
	return tracks;
}

void PlayList::addTrack(Track value)
{
	tracks->append(value);
}

void PlayList::delTrack(Track value)
{
	tracks->removeOne(value);
}

QString PlayList::getName()
{
	return name;
}

void PlayList::setName(QString &value)
{
	name = value;
}

QString PlayList::getImgUrl()
{
	return imgUrl;
}

void PlayList::setImgUrl(QString &value)
{
	imgUrl = value;
}
