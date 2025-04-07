//
// Created by Baka-tannn on 21/2/2025.
//

#ifndef AUDIO_H
#define AUDIO_H
#include <SDL_mixer.h>

class Audio {
private:
    Mix_Music *audio; // BGM
public:
    Audio(const char* fileName, int loop, int volume);
    static void PauseAudio();
    static void ResumeAudio();
    static void PlaySFX(const char* fileName, int volume);
};
#endif //AUDIO_H
