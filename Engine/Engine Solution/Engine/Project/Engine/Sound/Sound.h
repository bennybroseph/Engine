#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

/////////////////////////////////////////////////////////////////////////
//Namespace Sound
/////////////////////////////////////////////////////////////////////////
//Used mostly for playing and loading the background music
//Not nearly finished, needs bells and whistles
/////////////////////////////////////////////////////////////////////////

namespace Sound
{
    ////////Functions////////

    //Initializes SDL_Mixer and Sound
    void Init();

    //Loads the given file into bg_music
    void Load(std::string);

    //Plays bg_music the specified amount of times, -1 is infinite
    void Play(int);

    //Frees memory, called upon program exit
    void Quit();


    ////////Member Variables////////

    //Stores the sound file and is used to play it
    extern Mix_Music *bg_music;
}


/////////////////////////////////////////////////////////////////////////
//Class SFX
/////////////////////////////////////////////////////////////////////////
//Each object stores a sound file, and can be played via Play()
//Each object (character, item, etc.) will have a SFX object
//Open for improvement
/////////////////////////////////////////////////////////////////////////

class SFX
{
    public:

        ////////Constructor - Destructor////////


        SFX();

        //Allows for loading a sound file upon construction
        SFX(std::string);

        ~SFX();

        ////////Functions////////

        //Load the given sound file onto chunk
        void Load(std::string);

        //Play chunk
        void Play();

    private:

        ////////Member Variables////////

        //Stores a sound file which is played via Play()
        Mix_Chunk* chunk;
};

#endif // SOUND_H_INCLUDED
