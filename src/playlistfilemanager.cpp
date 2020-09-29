#include "playlistfilemanager.h"

PlaylistFileManager::PlaylistFileManager()
{

}

void PlaylistFileManager::savePlaylists(QString filename, QMap<QUuid, PlayList> playlists)
{
	QFile file(filename);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;
	QTextStream out(&file);
	QString data = "[";

	foreach (auto playlist, playlists) {
		data.append(playlist.toJSON());
		if (playlist.getUuid() != playlists.lastKey()) data.append(",");
	}

	data.append("]");

	out << data;
	file.close();

}

QMap<QUuid, PlayList> *PlaylistFileManager::loadPlaylists(QString filename)
{
	QFile file(filename);
	auto playlists = new QMap<QUuid, PlayList> ();

	if (file.exists())
	{
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			return nullptr;
		}

		QTextStream in(&file);

		auto data = in.readAll().toUtf8();

		auto doc = QJsonDocument::fromJson(data);
		auto items = doc.array();


		for (int i = 0; i < items.size() ; i++ )
		{
			PlayList pl(items[i].toObject().value("name").toString(),
						items[i].toObject().value("uuid").toString());
			auto tracks = items[i].toObject().value("tracks").toArray();

			for (auto t: tracks){
				auto to = t.toObject();
				pl.addTrack( Track(to.value("id").toString(),
								   to.value("name").toString(),
								   to.value("album").toString(),
								   to.value("artist").toString(),
								   to.value("preview_url").toString()));
			}

			playlists->insert(pl.getUuid(), pl);
		}
		file.close();
	}
	return playlists;
}
