#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QList>
#include <QUuid>
#include "track.h"

class PlayList
{
public:
	explicit PlayList(QString name);
	~PlayList();

	QList<Track> getTracks();
	void addTrack(Track );
	void delTrack(Track );

	QString getName();
	void setName(QString &value);

	QString getImgUrl();
	void setImgUrl(QString &value);

	QUuid getUuid() const;

private:
	QString name;
	QList<Track> tracks;
	QString imgUrl;
	QUuid uuid;

};

#endif // PLAYLIST_H
