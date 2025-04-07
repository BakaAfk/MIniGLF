//
// Created by Baka-tannn on 21/2/2025.
//
#include <SDL_mixer.h>
#include "audio.h"
#include <SDL_messagebox.h>

Audio::Audio(const char * fileName, int loop, int volume) // Load and play BGM
{
    audio = Mix_LoadMUS(fileName);
    if (audio == NULL) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Khong the load bgm", NULL);
    }
    Mix_PlayMusic(audio, loop);
    Mix_VolumeMusic(volume);
}

void Audio::PauseAudio() // Pause BGM
{
    Mix_PauseMusic();
}

void Audio::ResumeAudio() // Unpause BGM
{
    Mix_ResumeMusic();
}

void Audio::PlaySFX(const char * fileName, int volume) // Load and play SFX
{
    Mix_Chunk * sfx = Mix_LoadWAV(fileName);
    Mix_PlayChannel(-1, sfx, 0);
    Mix_VolumeChunk(sfx, volume);
}