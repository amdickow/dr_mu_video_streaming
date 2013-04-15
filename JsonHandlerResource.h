#ifndef RESOURCEMODEL_H
#define RESOURCEMODEL_H

#include <QList>
#include <QJsonArray>
#include <QString>
#include <vector>



#include "JsonHandlerBase.h"

struct ResourceEntry {
    QString uri;
    int bitRate;
};

class ResourceEntries
{
public:
    QList<int> &getBitrates();
    const QString &getUriAt(int index);

    void add(ResourceEntry *entry);

    void print();

private:
    QList<QString> uris;
    QList<int> bitRates;
};

class JsonHandlerResource : public JsonHandlerBase
{
public:
    JsonHandlerResource();

    unsigned int getResourceId();
    const QString &getName();
    const QString &getDownloadUri(int index);

    void print();

    virtual void processJsonArray(const QJsonArray &node);

private:
    void processLinks(const QJsonArray &node);

    unsigned int resId;
    QString name;
    ResourceEntries entries;
};

#endif // RESOURCEMODEL_H
