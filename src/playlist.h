#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QList>
#include <QUuid>
#include "track.h"

class PlayList
{
public:
	explicit PlayList(QString name, QUuid uuid = nullptr);

	PlayList() = default;
	PlayList(const PlayList &) = default;;
	~PlayList() = default;

	QList<Track> getTracks();
	void clearTracks();
	void addTrack(Track );
	void delTrack(Track );

	QString getName();
	void setName(QString &value);

	QUuid getUuid() const;
	QByteArray toJSON();

private:
	QString name;
	QList<Track> tracks;
	QUuid uuid;

};

Q_DECLARE_METATYPE(PlayList);

#endif // PLAYLIST_H
