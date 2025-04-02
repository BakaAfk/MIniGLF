//
// Created by Baka-tannn on 21/2/2025.
//

#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <SDL.h>
#include <string>
#include <map>

class TextureLoader {
private:
    static std::map<std::string, SDL_Texture*> textureCache;
public:
    static SDL_Texture *loadTexture(const char *fileName);
    static void Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dist);
    static void clearCache();
};
#endif //TEXTURELOADER_H
