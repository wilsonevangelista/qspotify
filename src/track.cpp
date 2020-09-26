#include "track.h"

Track::Track(QString id, QString name, QString album, QString artist, QString previewUrl):
id(id), name(name), album(album), artist(artist), previewUrl(previewUrl)
{

}

QString Track::toString(){
	return name + " - " + artist + " - " + album;
}

QString Track::toJSON(){
	return "{ id: " + id +", name: " + name + ", artist: " + artist + ", album: " + album + ", preview_url: " + previewUrl + "}";
}
