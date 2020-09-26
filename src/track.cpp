#include "track.h"

Track::Track(QString id, QString name, QString album, QString artist, QString previewUrl):
id(id), name(name), album(album), artist(artist), previewUrl(previewUrl)
{

}

QString Track::toString(){
	return name + " - " + artist + " - " + album;
}

QByteArray Track::toJSON(){
	return QString("{ \"id\": \"" + id +"\", \"name\": \"" + name + "\", \"artist\": \"" + artist + "\", \"album\": \"" + album + "\", \"preview_url\": \"" + previewUrl + "\"}").toUtf8();
}
