#ifndef SPOTIFYAPI_H
#define SPOTIFYAPI_H

#include <QDebug>
#include <QMetaEnum>
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
	void searchNext();
	void searchPrevious();
	int total, offset;

private:
	QNetworkAccessManager qnam;
	QNetworkReply *reply;
	QString accessToken, tokenType;
	QTimer expireTimer;
	bool netError;


	QUrl nextUrl = QUrl();
	QUrl previousUrl = QUrl();
	QUrl tokenUrl = QUrl("https://accounts.spotify.com/api/token"); //-H "Authorization: Basic <base64 encoded spotifyapi>"
	QUrl searchTrackUrl = QUrl("https://api.spotify.com/v1/search");

	void searchMusicWithUrl(QUrl );
	void getToken();
	void networkError(QNetworkReply::NetworkError err);

private slots:
	void getTokenFinished();
	void searchTrackFinished();
signals:
	void tokenOK(QString);
	void searchReturn(QList<Track>);
	void error(QString, bool);

};

#endif // SPOTIFYAPI_H
