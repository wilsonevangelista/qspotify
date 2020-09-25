#ifndef SPOTIFYAPI_H
#define SPOTIFYAPI_H

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>

#include "secrets.h"


class SpotifyAPI: public QObject
{
	Q_OBJECT
public:
	SpotifyAPI();
	~SpotifyAPI();

	void searchMusic(QString);

private:
	QNetworkAccessManager qnam;
	QNetworkReply *reply;
	QString accessToken, tokenType;
	QTimer expireTimer;

	QUrl tokenUrl = QUrl("https://accounts.spotify.com/api/token"); //-H "Authorization: Basic <base64 encoded spotifyapi>"
	QUrl trackUrl = QUrl("https://api.spotify.com/v1/tracks/"); //{id}
	QUrl searchTrackUrl = QUrl("https://api.spotify.com/v1/search\?type=track&q=");

	void getToken();

public slots:
	void getTokenFinished();
signals:
	void tokenOK(QString);

};

#endif // SPOTIFYAPI_H
