#ifndef TRACK_H
#define TRACK_H

#include <QString>

class Track
{
public:
	Track(QString id, QString name, QString album, QString artist, QString previewUrl);
	bool operator==(const Track& rhs){ return id == rhs.id; };

	QString toString();
	QByteArray toJSON();
private:
	QString id;
	QString name;
	QString album;
	QString artist;
	QString previewUrl;
};

#endif // TRACK_H
