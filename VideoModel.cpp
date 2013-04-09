#include "VideoModel.h"

#include <stdio.h>
#include <string.h>
#include <vector>

#include "libjson/libjson.h"

using namespace std;

VideoModel::VideoModel() : BaseModel(0), id(0) { }

VideoModel::VideoModel(const char* data) : BaseModel(data), id(0) { }

void VideoModel::ProcessJson(JSONNODE *node) {
    JSONNODE_ITERATOR begin = json_begin(node);
    JSONNODE_ITERATOR end   = json_end(node);

    printf("DEBUG: ProcessJson() >>\n");

    while(begin != end) {
        if (json_type(*begin) == JSON_ARRAY ||
            json_type(*begin) == JSON_NODE) {
            ProcessJson(*begin);
        }

        json_char *name = json_name(*begin);

        if (strcmp(name, "id") == 0) {
            json_int_t value = json_as_int(*begin);
            id = value;
            printf("DEBUG: ProcessJson() found id, value=%d\n", (int) value);
        }

        if (strcmp(name, "description") == 0) {
            json_char *value = json_as_string(*begin);
            description.append(value);
            printf("DEBUG: ProcessJson() found description, value=%s\n", (const char*) value);
            json_free(value);
        }

        if (strcmp(name, "title") == 0) {
            json_char *value = json_as_string(*begin);
            title.append(value);
            printf("DEBUG: ProcessJson() found title, value=%s\n", (const char*) value);
            json_free(value);
        }

        if (strcmp(name, "videoManifestUrl") == 0) {
            json_char *value = json_as_string(*begin);
            videoManifestUrl.append(value);
            printf("DEBUG: ProcessJson() found videoManifestUrl, value=%s\n", (const char*) value);
            json_free(value);
        }

        if (strcmp(name, "videoResourceUrl") == 0) {
            json_char *value = json_as_string(*begin);
            videoResourceUrl.append(value);
            printf("DEBUG: ProcessJson() found videoResourceUrl, value=%s\n", (const char*) value);
            json_free(value);
        }
        json_free(name);
        ++begin;
    }
    //json_free(begin);
    //json_free(end);
}


unsigned int VideoModel::GetId() {
    return id;
}

QString *VideoModel::GetDescription() {
    return &description;
}

QString *VideoModel::GetTitle() {
    return &title;
}

QString *VideoModel::GetVideoManifestUrl() {
    return &videoManifestUrl;
}

QString *VideoModel::GetVideoResourceUrl() {
    return &videoResourceUrl;
}

VideoModel::VideoEntry* VideoModel::GetVideoEntry(int index)
{

}

QList<VideoModel::VideoEntry*> VideoModel::GetVideoEntries()
{

}


void VideoModel::Print() {
    printf("DEBUG Print() >>\n");

    if(id) {
        printf("    id                  : %d \n", id);
    }
    if (!title.isEmpty()) {
        printf("    title               : %s \n", qPrintable(title));
    }
    if (!description.isEmpty()) {
        printf("    description         : %s \n", qPrintable(description));
    }
    if (!videoManifestUrl.isEmpty()) {
        printf("    video-manifest-url  : %s \n", qPrintable(videoManifestUrl));
    }
    if (!videoResourceUrl.isEmpty()) {
        printf("    video-resource-url  : %s \n", qPrintable(videoResourceUrl));
    }
}

