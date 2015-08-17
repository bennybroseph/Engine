#include "Sound.h"

/////////////////////////////////////////////////////////////////////////
//Namespace Sound
/////////////////////////////////////////////////////////////////////////

namespace Sound
{
    Mix_Music* bg_music;

    void Init()
    {
        Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
        Mix_AllocateChannels(16);

        bg_music = NULL;
    }

    void Load(std::string filename)
    {
        bg_music = Mix_LoadMUS(filename.c_str());
    }

    void Play(int loop)
    {
        Mix_PlayMusic(bg_music, loop);
    }

    void Quit()
    {
        Mix_FreeMusic(bg_music);
    }
}

/////////////////////////////////////////////////////////////////////////
//Class SFX
/////////////////////////////////////////////////////////////////////////

SFX::SFX()
{
}

SFX::SFX(std::string filename)
{
    //Must be called because the object is created before Sound is Inited
    //Not good, but can't think of fix for it
    //Could get bad later, when objects are created and killed on the fly
    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);

    this->chunk = Mix_LoadWAV(filename.c_str());
}

SFX::~SFX()
{
    Mix_FreeChunk(this->chunk);
}

void SFX::Load(std::string filename)
{
    this->chunk = Mix_LoadWAV(filename.c_str());
}

void SFX::Play()
{
    //Mix_PlayChannel(channel num (-1 for next channel), chunk, loop times)
    Mix_PlayChannel(-1, this->chunk, 0);
}
