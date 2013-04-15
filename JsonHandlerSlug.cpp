#include "JsonHandlerSlug.h"

#include <stdio.h>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariantList>
#include <QVariant>
#include <QList>


JsonHandlerSlug::JsonHandlerSlug() : JsonHandlerBase() { }

void JsonHandlerSlug::processJsonArray(const QJsonArray &node) {

    qDebug("DEBUG: processJsonArray() >>\n");

    foreach (QVariant item, node.toVariantList()) {
        //qDebug("DEBUG:      item.type()=%d, %s\n",(int)item.type(), item.typeName());
        if (item.canConvert(QMetaType::QVariantMap)) {
            QJsonObject jObj = QJsonObject::fromVariantMap(item.toMap());
            //qDebug("DEBUG:      jObj.count()=%d\n",(int)jObj.count());

            slugs.push_back(jObj.value("slug").toString());
            //qDebug("DEBUG:      jObj.value(slug)=%s\n",qPrintable(slug->slug));
            titles.push_back(jObj.value("title").toString());
            //qDebug("DEBUG:      jObj.value(title)=%s\n",qPrintable(slug->title));
        }
    }
}

void JsonHandlerSlug::print() {
    qDebug("DEBUG:      slug count: %d\n", titles.size());
    foreach (QString title, titles) {
        qDebug("DEBUG:      slug: %s\n",qPrintable(title));
    }
}

QList<QString> &JsonHandlerSlug::getSlugs() {
    return slugs;
}

QList<QString> &JsonHandlerSlug::getTitles() {
    return titles;
}

const QString &JsonHandlerSlug::getSlugAt(int index) {
    if (index < (int)slugs.size()) {
        return (slugs.at(index));
    } else {
        return 0;
    }
}

const QString &JsonHandlerSlug::getTitleAt(int index) {
    if (index < (int)titles.size()) {
        return (titles.at(index));
    } else {
        return 0;
    }
}

