#include "ResourceModel.h"

#include <stdio.h>
#include <string.h>


#include "libjson/libjson.h"

using namespace std;

ResourceModel::ResourceModel() : BaseModel(0), resId(0) { }

ResourceModel::ResourceModel(const char* data) : BaseModel(data), resId(0) { }

void ResourceModel::ProcessJson(JSONNODE *node) {
    JSONNODE_ITERATOR begin = json_begin(node);
    JSONNODE_ITERATOR end   = json_end(node);

    printf("DEBUG: ProcessJson() >>\n");

    while(begin != end) {
#if 0 // this should not be needed
        if (json_type(*begin) == JSON_ARRAY ||
            json_type(*begin) == JSON_NODE) {
            ProcessJson(*begin);
        }
#endif

        json_char *name = json_name(*begin);

        if (strcmp(name, "resourceId") == 0) {
            json_int_t value = json_as_int(*begin);
            resId = value;
            printf("DEBUG: ProcessJson() found resourceId, value=%d\n", (int) value);
        }

        if (strcmp(name, "name") == 0) {
            json_char *value = json_as_string(*begin);
            this->name.append(value);
            printf("DEBUG: ProcessJson() found name, value=%s\n", (const char*) value);
            json_free(value);
        }

        if (strcmp(name, "links") == 0) {
            printf("    json_type() type=%d size=%d\n", json_type(*begin), json_size(*begin));
            if (json_type(*begin) == JSON_ARRAY ||
                json_type(*begin) == JSON_NODE) {
                printf("DEBUG: ProcessJson() found links!\n");
                ProcessLinks(*begin);
            }
        }

        json_free(name);
        ++begin;
    }
    //json_free(begin);
    //json_free(end);
}

void ResourceModel::ProcessLinks(JSONNODE *node) {
    JSONNODE_ITERATOR begin = json_begin(node);
    JSONNODE_ITERATOR end   = json_end(node);

    printf("DEBUG: ProcessLinks() >> node type=%d\n", json_type(*begin));

    while(begin != end) {
        if (json_type(*begin) == JSON_ARRAY ||
            json_type(*begin) == JSON_NODE) {
            ProcessLinks(*begin);
        }
        json_char *name = json_name(*begin);
        if (strcmp(name, "uri") == 0) {
            json_char *value = json_as_string(*begin);
            downloadUri.push_back(string(value));
            printf("DEBUG: ProcessJson() found uri, value=%s\n", (const char*) value);
            json_free(value);
        }
        json_free(name);
        ++begin;
    }
}


unsigned int ResourceModel::GetResourceId() {
    return resId;
}

std::string *ResourceModel::GetName() {
    return &name;
}

std::string *ResourceModel::GetDownloadUri(int index) {
    return &(downloadUri.at(index));
}


void ResourceModel::Print() {
    printf("DEBUG: Print() >>\n");

    if(resId) {
        printf("    resource-id         : %d \n", resId);
    }
    if (!name.empty()) {
        printf("    name                : %s \n", name.c_str());
    }

    for (int i = 0; i < downloadUri.size(); i++) {
        if (!(downloadUri.at(i)).empty()) {
            printf("    uri[%d]         : %s \n", i, (downloadUri.at(i)).c_str());
        }
    }

}

