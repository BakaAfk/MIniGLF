//
// Created by Baka-tannn on 21/2/2025.
//
#include <SDL_mixer.h>
#include "audio.h"
#include <iostream>
#include <SDL_messagebox.h>

Audio::Audio(const char* fileName, int loop, int volume)
{
    audio = Mix_LoadMUS(fileName);
    if (audio == NULL)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"Error", "Can't load audio",NULL);
    }
    Mix_PlayMusic(audio, loop);
    Mix_VolumeMusic(volume);
}

void Audio::StopAudio()
{
    Mix_HaltMusic();
}

void Audio::PauseAudio()
{
    Mix_PauseMusic();
}

void Audio::ResumeAudio()
{
    Mix_ResumeMusic();
}




