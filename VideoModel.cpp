#include "VideoModel.h"

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
}

QList<QString> &VideoEntries::getTitles() {
    return titles;
}

void VideoEntries::print() {
    printf("DEBUG print() >>\n");
    int size = ids.size();
    for (int i = 0; i < size; i++) {
        if(ids.at(i)) {
            printf("    id                  : %d \n", ids.at(i));
        }
        if (!titles.at(i).isEmpty()) {
            printf("    title               : %s \n", qPrintable(titles.at(i)));
        }
        if (!videoResourceUrls.at(i).isEmpty()) {
            printf("    video-resource-url  : %s \n", qPrintable(videoResourceUrls.at(i)));
        }
    }
}

VideoModel::VideoModel() : JsonHandlerBase(), id(0) { }

void VideoModel::processJsonArray(const QJsonArray &node) {

    printf("DEBUG: processJsonArray() >>\n");

    foreach (QVariant item, node.toVariantList()) {
        //printf("DEBUG:      item.type()=%d, %s\n",(int)item.type(), item.typeName());
        if (item.canConvert(QMetaType::QVariantMap)) {
            QJsonObject jObj = QJsonObject::fromVariantMap(item.toMap());
            //printf("DEBUG:      jObj.count()=%d\n",(int)jObj.count());

            VideoEntry *video = new VideoEntry();
            video->id = (int)jObj.value("id").toDouble();
            printf("DEBUG:      jObj.value(id)=%d\n",video->id);
            video->title.append(jObj.value("title").toString());
            printf("DEBUG:      jObj.value(title)=%s\n",qPrintable(video->title));
            video->videoResourceUrl.append(jObj.value("videoResourceUrl").toString());
            printf("DEBUG:      jObj.value(videoResourceUrl)=%s\n",qPrintable(video->videoResourceUrl));
            videoEntries.add(video);
        }
    }
}

unsigned int VideoModel::getId() {
    return id;
}

QString *VideoModel::getDescription() {
    return 0; //&description;
}

QList<QString> &VideoModel::getTitles() {
    return videoEntries.getTitles();
}


QString *VideoModel::getVideoResourceUrl() {
    return 0; //&videoResourceUrl;
}

void VideoModel::print() {
    videoEntries.print();
}


