#include <QtTest>
#include <QtCore/QCoreApplication>

#include "track.h"
#include "playlist.h"
#include "spotifyapi.h"
#include "playlistfilemanager.h"

// add necessary includes here

class QSpotifyTest : public QObject
{
	Q_OBJECT

public:
	QSpotifyTest();
	~QSpotifyTest();

private:
	Track *t;
	PlayList *p;
	SpotifyAPI *s;
	QUuid uuid;



private slots:
	void initTestCase();
	void cleanupTestCase();

	void spotify_token();
	void spotify_search();

	void track_json();
	void track_string();
	void track_url();

	void playlist_json();
	void playlist_json_track();
	void playlist_name();

	void playlistfile_test();

};

QSpotifyTest::QSpotifyTest()
{
	qRegisterMetaType<Track>();
	qRegisterMetaType<PlayList>();
}

QSpotifyTest::~QSpotifyTest()
{

}

void QSpotifyTest::spotify_token()
{
	QSignalSpy spy(s, SIGNAL(tokenOK(QString)));
	QVERIFY(spy.wait());
	QList<QVariant> arguments = spy.takeFirst();
	QVERIFY(!arguments.at(0).toString().isEmpty());
}

void QSpotifyTest::spotify_search()
{
	QSignalSpy spy(s, SIGNAL(searchReturn(QList<Track>)));
	s->searchMusic("Fear of the dark");
	QVERIFY(spy.wait(20000));
	QList<QVariant> arguments = spy.takeFirst();
	QList<Track> tracks = qvariant_cast<QList<Track>>(arguments.at(0));
	QVERIFY(!tracks.isEmpty());
}

void QSpotifyTest::initTestCase()
{
	t = new Track("id", "name", "album", "artist", "preview_url");
	uuid = QUuid::createUuid();
	p = new PlayList("teste", uuid);
	s = new SpotifyAPI();
}

void QSpotifyTest::cleanupTestCase()
{
	delete t;
	delete p;
	delete s;
}

void QSpotifyTest::track_json()
{
	QVERIFY(t->toJSON() == "{ \"id\": \"id\", \"name\": \"name\", \"artist\": \"artist\", \"album\": \"album\", \"preview_url\": \"preview_url\"}");
}

void QSpotifyTest::track_string()
{
	QVERIFY(t->toString() == ("name - artist - album"));
}

void QSpotifyTest::track_url()
{
	QVERIFY(t->getPreviewUrl() == "preview_url");
}

void QSpotifyTest::playlist_json()
{
	QVERIFY(p->toJSON() == "{ \"name\" : \"teste\", \"uuid\": \"" + uuid.toString() + "\", \"tracks\" : []}");
}

void QSpotifyTest::playlist_json_track()
{
	Track track("id", "name", "album", "artist", "preview_url");
	p->addTrack(track);
	QVERIFY(p->toJSON() == "{ \"name\" : \"teste\", \"uuid\": \"" + uuid.toString() + "\", \"tracks\" : ["+ track.toJSON() +"]}");
}

void QSpotifyTest::playlist_name()
{
	QVERIFY(p->getName() == ("teste"));
}

void QSpotifyTest::playlistfile_test()
{
	QString filename = "testesalvar.json";
	QMap<QUuid, PlayList> pls;
	pls.insert(uuid, *p);
	PlaylistFileManager::savePlaylists(filename, pls);
	auto plsptr = PlaylistFileManager::loadPlaylists(filename);
	QVERIFY(plsptr != nullptr);
	pls = *plsptr;
	QVERIFY(pls.count(uuid) == 1);


}

QTEST_MAIN(QSpotifyTest)

#include "tst_qspotifytest.moc"
