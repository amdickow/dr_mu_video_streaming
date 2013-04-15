#include "JsonHandlerBase.h"

#include <stdio.h>
#include <QJsonArray>

JsonHandlerBase::JsonHandlerBase() {}

JsonHandlerBase::~JsonHandlerBase() {}

void JsonHandlerBase::kill() {
    delete this;
}

bool JsonHandlerBase::create(QByteArray *data) {
    doc = QJsonDocument::fromJson(*data);
    return !doc.isNull();
}

void JsonHandlerBase::process() {
    qDebug("DEBUG: JsonHandlerBase::process() >> \n");

    if (!doc.isNull()) {
        if (doc.isArray()) {
            qDebug("DEBUG:      array size=%d\n",(int)doc.array().size());
            this->processJsonArray(doc.array());
        } else {
            // isObject then?
            // this case should be handled but is irrellevant for DR
        }

    } else  {
        qDebug("DEBUG:      Parsing failed!\n");
    }
}
