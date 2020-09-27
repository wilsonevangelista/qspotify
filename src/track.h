#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QVariant>

class Track
{
public:
	Track(QString id, QString name, QString album, QString artist, QString previewUrl);

	Track() = default;
	Track(const Track &) = default;
	~Track() = default;

	bool operator==(const Track& rhs){ return id == rhs.id; };

	QString toString();
	QByteArray toJSON();
	QString getPreviewUrl() const;

private:
	QString id;
	QString name;
	QString album;
	QString artist;
	QString previewUrl;
};

Q_DECLARE_METATYPE(Track);

#endif // TRACK_H
