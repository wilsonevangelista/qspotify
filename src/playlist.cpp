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

QUuid PlayList::getUuid() const
{
	return uuid;
}

QByteArray PlayList::toJSON()
{
	auto ret = new QString("{ \"name\" : \"" + name +
						   "\", \"uuid\": \"" + uuid.toString() +
						   "\", \"tracks\" : [");

	for (int i = 0; i < tracks.length(); i++) {
		ret->append(tracks[i].toJSON());
		if (i < tracks.length() - 1) ret->append(",");
	}
	ret->append("]}");
	return ret->toUtf8();
}




