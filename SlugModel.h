#ifndef SLUGMODEL_H
#define SLUGMODEL_H

#include <QString>
#include <QList>

#include "libjson/libjson.h"

#include "BaseModel.h"

class SlugModel : public BaseModel
{
public:
    SlugModel();
    SlugModel(const char* data);

    QString *Get(int index);
    int GetSize();

    QList<QString> &GetSlugs() {return slugs;}

    void Print();

    virtual void ProcessJson(JSONNODE *node);

private:
    QList<QString> slugs;
};

#endif // SLUGMODEL_H
