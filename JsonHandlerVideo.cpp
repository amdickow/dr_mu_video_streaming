#include "JsonHandlerVideo.h"

#include <stdio.h>
#include <string.h>
#include <vector>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariantList>
#include <QVariant>
#include <QList>

using namespace std;

void VideoEntries::add(VideoEntry *video) {
    ids.push_back(video->id);
    titles.push_back(video->title);
    videoResourceUrls.push_back(video->videoResourceUrl);
    delete video;
}

QList<QString> &VideoEntries::getTitles() {
    return titles;
}

const QString &VideoEntries::getVideoResUrlAt(int index) {
    if (index < videoResourceUrls.size()) {
        return videoResourceUrls.at(index);
    }
    return 0;
}

void VideoEntries::print() {
    int size = ids.size();
    for (int i = 0; i < size; i++) {
        if(ids.at(i)) {
            qDebug("    id                  : %d \n", ids.at(i));
        }
        if (!titles.at(i).isEmpty()) {
            qDebug("    title               : %s \n", qPrintable(titles.at(i)));
        }
        if (!videoResourceUrls.at(i).isEmpty()) {
            qDebug("    video-resource-url  : %s \n", qPrintable(videoResourceUrls.at(i)));
        }
    }
}

JsonHandlerVideo::JsonHandlerVideo() : JsonHandlerBase(), id(0) { }

void JsonHandlerVideo::processJsonArray(const QJsonArray &node) {

    qDebug("DEBUG: processJsonArray() >>\n");

    foreach (QVariant item, node.toVariantList()) {
        //qDebug("DEBUG:      item.type()=%d, %s\n",(int)item.type(), item.typeName());
        if (item.canConvert(QMetaType::QVariantMap)) {
            QJsonObject jObj = QJsonObject::fromVariantMap(item.toMap());
            //qDebug("DEBUG:      jObj.count()=%d\n",(int)jObj.count());

            VideoEntry *video = new VideoEntry();
            video->id = (int)jObj.value("id").toDouble();
            qDebug("DEBUG:      jObj.value(id)=%d\n",video->id);
            video->title.append(jObj.value("title").toString());
            qDebug("DEBUG:      jObj.value(title)=%s\n",qPrintable(video->title));
            video->videoResourceUrl.append(jObj.value("videoResourceUrl").toString());
            qDebug("DEBUG:      jObj.value(videoResourceUrl)=%s\n",qPrintable(video->videoResourceUrl));
            videoEntries.add(video);
        }
    }
}

unsigned int JsonHandlerVideo::getId() {
    return id;
}

QString *JsonHandlerVideo::getDescription() {
    return 0; //&description;
}

QList<QString> &JsonHandlerVideo::getTitles() {
    return videoEntries.getTitles();
}


const QString &JsonHandlerVideo::getVideoResourceUrlAt(int index) {
    return videoEntries.getVideoResUrlAt(index);
}

void JsonHandlerVideo::print() {
    qDebug("DEBUG print() >>\n");
    videoEntries.print();
}


