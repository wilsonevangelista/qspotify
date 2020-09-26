#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QList>
#include "track.h"

class PlayList
{
public:
	explicit PlayList();
	~PlayList();

	QList<Track> *getTracks();
	void addTrack(Track );
	void delTrack(Track );

	QString getName();
	void setName(QString &value);

	QString getImgUrl();
	void setImgUrl(QString &value);

private:
	QString name;
	QList<Track> *tracks;
	QString imgUrl;

};

#endif // PLAYLIST_H
