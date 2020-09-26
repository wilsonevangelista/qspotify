#include "spotifyapi.h"

SpotifyAPI::SpotifyAPI()
{
	getToken();
	connect(&expireTimer, &QTimer::timeout, this, [=](){ getToken(); });
}

SpotifyAPI::~SpotifyAPI(){

}

void SpotifyAPI::searchMusic(QString query)
{
	if (accessToken.isEmpty()) return;

	searchTrackUrl.setQuery("type=track&q=" + query);
	searchMusicWithUrl(searchTrackUrl);
}

void SpotifyAPI::searchMusicWithUrl(QUrl url)
{
	auto req = QNetworkRequest(url);
	req.setRawHeader("Authorization", QString(tokenType + " " + accessToken).toUtf8());
	reply = qnam.get(req);
	connect(reply, &QNetworkReply::finished, this, &SpotifyAPI::searchTrackFinished);
}

void SpotifyAPI::getToken(){
	auto req = QNetworkRequest(tokenUrl);
	QByteArray body;
	body.append("grant_type=client_credentials");
	req.setRawHeader("Authorization", QString("Basic ").append(SPOTIFY_B64ENC_IDKEY).toUtf8());
	req.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, "application/x-www-form-urlencoded");

	reply = qnam.post(req, body);
	connect(reply, &QNetworkReply::finished, this, &SpotifyAPI::getTokenFinished);
}

void SpotifyAPI::getTokenFinished()
{
	const auto data = reply->readAll();
	reply->deleteLater();
	reply = nullptr;

	const auto document = QJsonDocument::fromJson(data);
	const auto root = document.object();

	accessToken = root.value("access_token").toString();
	tokenType = root.value("token_type").toString();

	int expires_in = root.value("expires_in").toInt();
	if (expires_in > 0)
		expireTimer.start(expires_in * 1000);
	emit tokenOK(accessToken);
}

void SpotifyAPI::searchTrackFinished()
{
	auto tracks = QList<Track>();
	const auto data = reply->readAll();
	reply->deleteLater();
	reply = nullptr;

	auto document = QJsonDocument::fromJson(data);
	auto root = document.object();

	auto trackResult = root.value("tracks").toObject();
	auto total = trackResult.value("total").toInt();
	auto items = trackResult.value("items").toArray();

	//auto nextUrl = trackResult.value("next");

	for (int i = 0; i < items.size() ; i++) {
		auto track = Track(
					items[i].toObject().value("id").toString(),
					items[i].toObject().value("name").toString(),
					items[i].toObject().value("album").toObject().value("name").toString(),
					items[i].toObject().value("artists").toArray().at(0).toObject().value("name").toString(),
					items[i].toObject().value("preview_url").toString()
					);
		tracks.append(track);
	}

	emit searchReturn(tracks);
}
