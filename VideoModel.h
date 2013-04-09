#ifndef VIDEOMODEL_H
#define VIDEOMODEL_H

#include <QString>

#include "libjson/libjson.h"

#include "BaseModel.h"

class VideoModel : public BaseModel
{
public:
    VideoModel();
    VideoModel(const char* data);

    struct VideoEntry {
        unsigned int id;
        QString title;
        QString description;
        QString videoManifestUrl;
        QString videoResourceUrl;
    };

    unsigned int GetId();
    QString *GetDescription();
    QString *GetTitle();
    QString *GetVideoManifestUrl();
    QString *GetVideoResourceUrl();

    VideoEntry* GetVideoEntry(int index);
    QList<VideoEntry*> GetVideoEntries();

    void Print();

    virtual void ProcessJson(JSONNODE *node);

private:
    unsigned int id;
    QList<VideoModel::VideoEntry*> videoEntries;
};

#endif // VIDEOMODEL_H
