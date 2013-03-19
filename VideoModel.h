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

    unsigned int GetId();
    QString *GetDescription();
    QString *GetTitle();
    QString *GetVideoManifestUrl();
    QString *GetVideoResourceUrl();

    void Print();

    virtual void ProcessJson(JSONNODE *node);

private:
    unsigned int id;
    QString description;
    QString title;
    QString videoManifestUrl;
    QString videoResourceUrl;
};

#endif // VIDEOMODEL_H
