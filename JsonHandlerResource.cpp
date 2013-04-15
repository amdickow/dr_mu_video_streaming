#include "JsonHandlerResource.h"

#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariantList>
#include <QVariant>
#include <QList>
#include <stdio.h>
#include <string.h>




using namespace std;

void ResourceEntries::add(ResourceEntry *entry) {
    uris.push_back(entry->uri);
    bitRates.push_back(entry->bitRate);
    delete entry;
}

QList<int> &ResourceEntries::getBitrates() {
    return bitRates;
}

const QString &ResourceEntries::getUriAt(int index) {
    if (index < uris.size()) {
        return uris.at(index);
    }
    return 0;
}

void ResourceEntries::print() {
    int size = uris.size();
    for (int i = 0; i < size; i++) {
        if (!uris.at(i).isEmpty()) {
            qDebug("    uri               : %s \n", qPrintable(uris.at(i)));
        }
        if(bitRates.at(i)) {
            qDebug("    bitrate(Kbps)     : %d \n", bitRates.at(i));
        }
    }
}

JsonHandlerResource::JsonHandlerResource() : JsonHandlerBase(), resId(0) { }

void JsonHandlerResource::processJsonArray(const QJsonArray &node) {

    qDebug("DEBUG: processJsonArray() >>\n");

    foreach (QVariant item, node.toVariantList()) {
        //qDebug("DEBUG:      item.type()=%d, %s\n",(int)item.type(), item.typeName());
        if (item.canConvert(QMetaType::QVariantMap)) {
            QJsonObject jObj = QJsonObject::fromVariantMap(item.toMap());
            //qDebug("DEBUG:      jObj.count()=%d\n",(int)jObj.count());

            name.append(jObj.value("name").toString());
            qDebug("DEBUG:      jObj.value(title)=%s\n",qPrintable(name));

            if (jObj.value("links").isArray()) {
                processLinks(jObj.value("links").toArray());
            }
        }
    }
}

void JsonHandlerResource::processLinks(const QJsonArray &node) {
    qDebug("DEBUG: processLinks() >>\n");

    foreach (QVariant item, node.toVariantList()) {
        //qDebug("DEBUG:      item.type()=%d, %s\n",(int)item.type(), item.typeName());
        if (item.canConvert(QMetaType::QVariantMap)) {
            QJsonObject jObj = QJsonObject::fromVariantMap(item.toMap());
            //qDebug("DEBUG:      jObj.count()=%d\n",(int)jObj.count());

            ResourceEntry *resource = new ResourceEntry();
            resource->uri.append(jObj.value("uri").toString());
            qDebug("DEBUG:      jObj.value(videoResourceUrl)=%s\n",qPrintable(resource->uri));

            resource->bitRate = (int)jObj.value("bitrateKbps").toDouble();

            entries.add(resource);
        }
    }
}


unsigned int JsonHandlerResource::getResourceId() {
    return resId;
}

const QString &JsonHandlerResource::getName() {
    return name;
}

const QString &JsonHandlerResource::getDownloadUri(int index) {
    return entries.getUriAt(index);
}


void JsonHandlerResource::print() {
    qDebug("DEBUG: print() >>\n");

    if (!name.isEmpty()) {
        qDebug("    name                : %s \n", qPrintable(name));
    }

    entries.print();
}

