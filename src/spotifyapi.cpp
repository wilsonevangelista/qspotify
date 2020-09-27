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

void SpotifyAPI::searchNext()
{
	if (nextUrl.isEmpty()) return;
	searchMusicWithUrl(nextUrl);
}

void SpotifyAPI::searchPrevious()
{
	if (previousUrl.isEmpty()) return;
	searchMusicWithUrl(previousUrl);
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
	connect(reply, &QNetworkReply::errorOccurred, this, &SpotifyAPI::networkError);
}

void SpotifyAPI::networkError(QNetworkReply::NetworkError err){
	if (err == QNetworkReply::ProtocolInvalidOperationError) return;
	netError = true;
	emit error("Erro na conexão: " +
			   QString(QMetaEnum::fromType<QNetworkReply::NetworkError>().valueToKey(err)), true);
}

void SpotifyAPI::getTokenFinished()
{
	if (netError) return;
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
	if (accessToken.isEmpty()){
		QString msg = "Não conseguiu obter token!\n";
		if (!root.value("error").toString().isEmpty()){
			msg.append("Samples salvos podem ser executados, mas gerenciar playlist será desabilitado.\n");
			msg.append("Erro: " + root.value("error").toString());
		}
		emit error(msg, false);
	} else {
		emit tokenOK(accessToken);
	}
}

void SpotifyAPI::searchTrackFinished()
{
	if (netError) return;
	auto tracks = QList<Track>();
	const auto data = reply->readAll();
	reply->deleteLater();
	reply = nullptr;

	auto document = QJsonDocument::fromJson(data);
	auto root = document.object();

	auto trackResult = root.value("tracks").toObject();
	auto items = trackResult.value("items").toArray();

	total = trackResult.value("total").toInt();
	offset = trackResult.value("offset").toInt();

	nextUrl.clear();
	if (!trackResult.value("next").isNull())
		nextUrl.setUrl(trackResult.value("next").toString());
	if (!trackResult.value("previous").isNull())
		previousUrl.setUrl(trackResult.value("previous").toString());

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
