//
// Created by Baka-tannn on 21/2/2025.
//

#ifndef AUDIO_H
#define AUDIO_H
#pragma once
#include <SDL_mixer.h>

class Audio {
private:
    Mix_Music *audio;
public:
    Audio(const char* fileName, int loop, int volume);
    void StopAudio();
    void PauseAudio();
    void ResumeAudio();
    static void PlaySFX(const char* fileName, int volume);
};
#endif //AUDIO_H
