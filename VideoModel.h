#ifndef VIDEOMODEL_H
#define VIDEOMODEL_H

#include <QJsonArray>
#include <QString>
#include <QList>

#include "JsonHandlerBase.h"

struct VideoEntry {
    unsigned int id;
    QString title;
    QString description;
    QString videoManifestUrl;
    QString videoResourceUrl;
};

class VideoEntries {
public:
    QList<QString> &getTitles();
    const QString &getVideoResUrlAt(int index);

    void add(VideoEntry *video);

    void print();

private:
    QList<int> ids;
    QList<QString> titles;
    QList<QString> videoResourceUrls;
};

class VideoModel : public JsonHandlerBase
{
public:
    VideoModel();

    unsigned int getId();
    QString *getDescription();
    const QString &getVideoResourceUrlAt(int index);

    QList<QString> &getTitles();

    void print();

    virtual void processJsonArray(const QJsonArray &node);

private:
    unsigned int id;
    VideoEntries videoEntries;
};

#endif // VIDEOMODEL_H
