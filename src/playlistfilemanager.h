#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "playlist.h"
#include "track.h"

class PlaylistFileManager
{
public:
	PlaylistFileManager();

	static void savePlaylists(QString filename, QMap<QUuid, PlayList> playlists);
	static QMap<QUuid, PlayList> *loadPlaylists(QString filename);
};

#endif // FILEMANAGER_H
