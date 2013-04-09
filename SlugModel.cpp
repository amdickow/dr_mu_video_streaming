#include "SlugModel.h"

#include <stdio.h>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariantList>
#include <QVariant>
#include <QList>


SlugModel::SlugModel() : JsonHandlerBase() { }

void SlugModel::processJsonArray(const QJsonArray &node) {

    printf("DEBUG: processJsonArray() >>\n");

    foreach (QVariant item, node.toVariantList()) {
        //printf("DEBUG:      item.type()=%d, %s\n",(int)item.type(), item.typeName());
        if (item.canConvert(QMetaType::QVariantMap)) {
            QJsonObject jObj = QJsonObject::fromVariantMap(item.toMap());
            //printf("DEBUG:      jObj.count()=%d\n",(int)jObj.count());

            slugs.push_back(jObj.value("slug").toString());
            //printf("DEBUG:      jObj.value(slug)=%s\n",qPrintable(slug->slug));
            titles.push_back(jObj.value("title").toString());
            //printf("DEBUG:      jObj.value(title)=%s\n",qPrintable(slug->title));
        }
    }
}

void SlugModel::print() {
    printf("DEBUG:      slug count: %d\n", titles.size());
    foreach (QString title, titles) {
        printf("DEBUG:      slug: %s\n",qPrintable(title));
    }
}

QList<QString> &SlugModel::getSlugs() {
    return slugs;
}

QList<QString> &SlugModel::getTitles() {
    return titles;
}

const QString &SlugModel::getSlugAt(int index) {
    if (index < (int)slugs.size()) {
        return (slugs.at(index));
    } else {
        return 0;
    }
}

const QString &SlugModel::getTitleAt(int index) {
    if (index < (int)titles.size()) {
        return (titles.at(index));
    } else {
        return 0;
    }
}

