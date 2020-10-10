#ifndef SCOREBOARD_H
#define SCOREBOARD_H

/** \file Scoreboard.h
 *  \brief Contains the definition of the Scoreboard class
 */

#include "Observer.h"
#include "Configuration.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

/** \class Scoreboard
 *
 *  Scoreboard is an observer of maze objects and characters,
 *  and maintains both the current score in a game and the high scores
 */
class Scoreboard : public Observer
{
    public:
        /** \brief Default constructor */
        Scoreboard(){}

        /** \brief Constructs Scoreboard object with initialisation list
         *
         *  Initialises the high scores and sets the current score to the last
         *  end score (a static variable). If in the beginning of a game, this will
         *  set the score to 0 but carry the score at the end of a previous game through
         *  to the next.
         *
         * \param highscores, a vector<pair<string,int>> of the high score list for the current maze.
         */
        Scoreboard(vector<pair<string,int> > highscores);

        virtual ~Scoreboard() {}

        /** \brief Performs an action upon notification of event by subjects
         *
         *  This will increase the score by a certain amount depending on the event type.
         *
         * \param event, an enum defined by the Observer class
         */
        void onNotify(Event event) override;

        /** \brief Increase the score multiplier
         *  This will increase the amount that the score gets incremented by each time
         *
         * \param mult, an integer multiplier value
         */
        void EatMultiplier(const int mult);

        /** \brief Updates the high score list
         *
         *  The name passed in along with the current score is inserted
         *  into the high score list in the correct position
         *
         *  \param name, a string of the name to be entered
         */
        void updateHighScores(string name);

        /** \brief returns the highest score in the list
            \returns an integer, the highest score for the current maze*/
        int getHighestScore() const { return highscores_.front().second;};

         /** \brief returns the fifth highest score in the list
            \returns an integer, the fifth highest score for the current maze*/
        int getFifthScore() const { return highscores_.back().second;};

         /** \brief returns the current player score
            \returns an integer, the current player score */
        int getCurrentScore() const { return current_score_; };

         /** \brief returns the list of high scores
            \returns a vector<pair<string,int>> containing the list of names and high scores
            */
        vector<pair<string,int>> getHighScores() const { return highscores_; };

        /** \brief Sets the static end score to the current score */
        void endGame();

        /** \brief returns the static end score variable which was the score at the end of the
                    previous game
            \returns an integer, the static end score variable */
        static int getEndScore();

    protected:

    private:
        int current_score_;
        int ghost_counter_ = 0;
        int n = 1;

        static int endScore;

        vector<pair<string,int>> highscores_;
        std::string text_ = "";

        void increaseScore(const int amount);


};

#endif // SCOREBOARD_H
