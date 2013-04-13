#include "ResourceModel.h"

#include <stdio.h>
#include <string.h>




using namespace std;

ResourceModel::ResourceModel() : JsonHandlerBase(), resId(0) { }

void ResourceModel::processJsonArray(const QJsonArray &node) {

    qDebug("DEBUG: processJsonArray() >>\n");
#if 0
    while(begin != end) {
// this should not be needed
        if (json_type(*begin) == JSON_ARRAY ||
            json_type(*begin) == JSON_NODE) {
            processJsonArray(*begin);
        }


        json_char *name = json_name(*begin);

        if (strcmp(name, "resourceId") == 0) {
            json_int_t value = json_as_int(*begin);
            resId = value;
            qDebug("DEBUG: processJsonArray() found resourceId, value=%d\n", (int) value);
        }

        if (strcmp(name, "name") == 0) {
            json_char *value = json_as_string(*begin);
            this->name.append(value);
            qDebug("DEBUG: processJsonArray() found name, value=%s\n", (const char*) value);
            json_free(value);
        }

        if (strcmp(name, "links") == 0) {
            qDebug("    json_type() type=%d size=%d\n", json_type(*begin), json_size(*begin));
            if (json_type(*begin) == JSON_ARRAY ||
                json_type(*begin) == JSON_NODE) {
                qDebug("DEBUG: processJsonArray() found links!\n");
                ProcessLinks(*begin);
            }
        }

        json_free(name);
        ++begin;
    }
    //json_free(begin);
    //json_free(end);
    #endif
}

void ResourceModel::processLinks(QJsonObject *node) {
#if 0

    qDebug("DEBUG: ProcessLinks() >> node type=%d\n", json_type(*begin));

    while(begin != end) {
        if (json_type(*begin) == JSON_ARRAY ||
            json_type(*begin) == JSON_NODE) {
            ProcessLinks(*begin);
        }
        json_char *name = json_name(*begin);
        if (strcmp(name, "uri") == 0) {
            json_char *value = json_as_string(*begin);
            downloadUri.push_back(string(value));
            qDebug("DEBUG: processJsonArray() found uri, value=%s\n", (const char*) value);
            json_free(value);
        }
        json_free(name);
        ++begin;
    }
#endif
}


unsigned int ResourceModel::getResourceId() {
    return resId;
}

std::string *ResourceModel::getName() {
    return &name;
}

std::string *ResourceModel::getDownloadUri(int index) {
    return &(downloadUri.at(index));
}


void ResourceModel::print() {
    qDebug("DEBUG: print() >>\n");

    if(resId) {
        qDebug("    resource-id         : %d \n", resId);
    }
    if (!name.empty()) {
        qDebug("    name                : %s \n", name.c_str());
    }

    for (int i = 0; i < downloadUri.size(); i++) {
        if (!(downloadUri.at(i)).empty()) {
            qDebug("    uri[%d]         : %s \n", i, (downloadUri.at(i)).c_str());
        }
    }

}

