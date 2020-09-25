#include "spotifyapi.h"

SpotifyAPI::SpotifyAPI()
{
	getToken();
	connect(&expireTimer, &QTimer::timeout, this, [=](){ getToken(); });
}

SpotifyAPI::~SpotifyAPI(){

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
	expireTimer.start(expires_in * 1000);
	emit tokenOK(accessToken);
}
