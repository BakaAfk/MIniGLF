//
// Created by Baka-tannn on 23/3/2025.
//

#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class TextRenderer {
public:
    TextRenderer();
    ~TextRenderer();

    void renderText(SDL_Renderer *renderer, const std::string& text, int x, int y, int size, SDL_Color color);
    void renderTextCenter(SDL_Renderer *renderer, const std::string& text, int x, int y, int size, SDL_Color color);
private:
    TTF_Font *font;
};

#endif //TEXTRENDERER_H
