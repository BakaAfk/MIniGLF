//
// Created by Baka-tannn on 23/3/2025.
//

#include "textRenderer.h"
#include "globalVar.h"

TTF_Font *TextRenderer::font = nullptr;

TextRenderer::TextRenderer() { // Constructor
    if (TTF_Init() == -1) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to initialize TTF", nullptr);
    }
    font = TTF_OpenFont("resources/font/font.ttf", DEFAULT_FONT_SIZE);
    if (!font) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to load font", nullptr);
    }
}

TextRenderer::~TextRenderer() { // Destructor
    if (font) {
        TTF_CloseFont(font);
    }
}

void TextRenderer::renderText(SDL_Renderer *renderer, const std::string& text, int x, int y, int size, SDL_Color color) { // Render text
    if (size != DEFAULT_FONT_SIZE) { // Default = 24
        TTF_Font *tempfont = TTF_OpenFont("resources/font/font.ttf", size); // Open temp font with custom size
        if (!tempfont) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Loi khi load font", nullptr);
        }
        SDL_Surface *surface = TTF_RenderText_Solid(tempfont, text.c_str(), color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        // Calculate the position
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = surface->w; // Width of the text
        rect.h = surface->h; // Height of the text

        SDL_RenderCopy(renderer, texture, nullptr, &rect);

        // Free resources
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        TTF_CloseFont(tempfont); // Close temp font
    } else {
        SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = surface->w;
        rect.h = surface->h;

        SDL_RenderCopy(renderer, texture, nullptr, &rect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

}

void TextRenderer::renderTextCenter(SDL_Renderer *renderer, const std::string& text, int x, int y, int size, SDL_Color color) { // Render middle text
    if (size != DEFAULT_FONT_SIZE) { // Default = 24
        TTF_Font *tempfont = TTF_OpenFont("resources/font/font.ttf", size); // Open temp font with custom size
        if (!tempfont) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Loi khi load font", nullptr);
        }
        SDL_Surface *surface = TTF_RenderText_Solid(tempfont, text.c_str(), color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        // Calculate the position
        SDL_Rect rect;
        rect.x = x - surface->w / 2; // Center the text
        rect.y = y;
        rect.w = surface->w;
        rect.h = surface->h;

        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        // Free resources
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        TTF_CloseFont(tempfont);
    } else {
        SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect rect;
        rect.x = x - surface->w / 2;
        rect.y = y;
        rect.w = surface->w;
        rect.h = surface->h;

        SDL_RenderCopy(renderer, texture, nullptr, &rect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}