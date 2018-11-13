#include <SOIL/SOIL.h>
#include "resourceManager.h"

#include <utility>

GLuint ResourceManager::loadTexture(const char *pathToFile)
{
    if( all_paths.find(pathToFile) == all_paths.end())
    {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // Set our texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Set texture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Load, create texture and generate mipmaps
        int width, height;
        unsigned char* image = SOIL_load_image(pathToFile, &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        //glGenerateMipmap(GL_TEXTURE_2D);
        SOIL_free_image_data(image);
        glBindTexture(GL_TEXTURE_2D, 0);

        all_paths.insert(std::pair<std::string, GLuint>(pathToFile, texture));

        return texture;
    } 
    else 
    {
        std::map<std::string,GLuint>::iterator it;
        it = all_paths.find(pathToFile);

        return it->second;
    }    
}

void ResourceManager::releaseAllResources()
{
    
}
