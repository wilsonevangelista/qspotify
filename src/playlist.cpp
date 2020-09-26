#include "playlist.h"

PlayList::PlayList(QString name):
	name(name), uuid(QUuid::createUuid())
{
}

PlayList::~PlayList(){
}

QList<Track> PlayList::getTracks()
{
	return tracks;
}

void PlayList::clearTracks(){
	tracks.clear();
}

void PlayList::addTrack(Track value)
{
	tracks.append(value);
}

void PlayList::delTrack(Track value)
{
	tracks.removeOne(value);
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

QUuid PlayList::getUuid() const
{
	return uuid;
}




