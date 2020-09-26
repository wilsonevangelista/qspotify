#ifndef SPOTIFYAPI_H
#define SPOTIFYAPI_H

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QList>

#include "secrets.h"
#include "track.h"


class SpotifyAPI: public QObject
{
	Q_OBJECT
public:
	SpotifyAPI();
	~SpotifyAPI();

	void searchMusic(QString );

private:
	QNetworkAccessManager qnam;
	QNetworkReply *reply;
	QString accessToken, tokenType;
	QTimer expireTimer;
	int total;


	QUrl nextUrl = QUrl();
	QUrl tokenUrl = QUrl("https://accounts.spotify.com/api/token"); //-H "Authorization: Basic <base64 encoded spotifyapi>"
	QUrl searchTrackUrl = QUrl("https://api.spotify.com/v1/search");

	void searchMusicWithUrl(QUrl );
	void searchNext();
	void getToken();

private slots:
	void getTokenFinished();
	void searchTrackFinished();
signals:
	void tokenOK(QString);
	void searchReturn(QList<Track> &);

};

#endif // SPOTIFYAPI_H
