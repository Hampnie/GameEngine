#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "common.h"

#include <string>
#include <map>

class ResourceManager
{
public:
    static ResourceManager& Instance()
    {
        static ResourceManager theSingleInstance;
        return theSingleInstance;
    }
    GLuint loadTexture(const char* pathToFile);
    void releaseAllResources();
private:
    ResourceManager() {}
    ResourceManager(const ResourceManager& root) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    std::map<std::string, GLuint> all_paths;
};

#endif
