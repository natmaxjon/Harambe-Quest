#ifndef SOUNDBOARD_H
#define SOUNDBOARD_H

#include <ctime>
#include <random>
#include <algorithm>
#include <vector>
#include <string>

/** \file Soundboard.h
 *  \brief Contains the definition of the Scoreboard class
 */

#include "Configuration.h"
#include "Observer.h"
#include "AssetManager.h"
#include "GameLoop.h"

using namespace std;

/** \class Soundboard
 *
 *  Soundboard inherits from Observer, and is an observer of maze objects
 *  and characters. This class plays music as well as sound effects
 *  linked to different events.
 */

class Soundboard : public Observer
{
    public:

        /** \brief Default Soundboard constructor */
        Soundboard() {}

        /** \brief Overloaded Soundboard constructor
         *
         *  Initialises a game pointer, as well as determines
         *  if any song in the playlist is currently playing.
         *
         *  \param game, a pointer to the game struct
         */
        Soundboard(gamePtr game);

         /** \brief Overloaded Soundboard constructor
         *
         *  Initialises a game pointer, as well as plays one of two songs
         *  depending on the boolean value of highScore.
         *
         *  \param game, a pointer to the game struct
         *  \param highScore, a boolean value indicating whether or not the user achieved a high score
         */
        Soundboard(gamePtr game, bool highScore);

        /** \brief Destructor */
        virtual ~Soundboard();

        /** \brief Performs an action upon notification of event by subjects
         *
         *  This will play a specific sound effect linked to the event which is passed in.
         *
         * \param event, an enum defined by the Observer class
         */
        void onNotify(Event event) override;

        /** \brief Checks which song in the playlist is currently playing
            and sets it to the current song number */
        void checkSong();

        /** \brief Suspends all playing of songs */
        void gotoMenu();

        /** \brief Shuffles the playlist and plays a song */
        void restart();

        /** \brief Continues the current song if the player had more than one life,
            otherwise changes the song from the "Last Life" song */
        void nextLevel();

        /** \brief Plays the next song in the playlist */
        void nextSong();

        /** \brief Plays the previous song in the playlist */
        void prevSong();

        /** \brief Stops playing the current song */
        void gameOver();

        /** \brief Plays the "Last Life" song */
        void lastLife();

        /** \brief Seeds the default_random_engine */
        static void seedRandom();

        /** \brief Shuffles the playlist using the STL shuffle function and a default_random_engine */
        static void shufflePlaylist();

        /** \brief Returns the current playlist
         *  \returns a vector<string> containing the names of the songs and order of the currrent playlist
         */
        static vector<string> getPlaylist();

    protected:

    private:
        gamePtr game_;

        int numSongs_;
        int currentSong_;
        string song_;
        static vector<string> playList_;
        static default_random_engine engine_;
};

#endif // SOUNDBOARD_H
