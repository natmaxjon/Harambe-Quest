#include "Scoreboard.h"
#include <iostream>
#include <cmath>

/*--------Static----------*/
int Scoreboard::endScore = 0;

void Scoreboard::endGame()
{
    endScore = current_score_;
}

int Scoreboard::getEndScore()
{
    return endScore;
}
/*-----------------------*/

Scoreboard::Scoreboard(vector<pair<string,int> > highscores) :
    highscores_(highscores)
{
    current_score_ = endScore;
}

void Scoreboard::increaseScore(const int amount)
{
    current_score_ += amount;
}

void Scoreboard::EatMultiplier(const int mult)
{
    n = mult;
}

void Scoreboard::updateHighScores(string name)
{
    if (name.size() > 0 && endScore > getFifthScore())
        {
            for (int i = 0; i < 5; i++)
            {
                if (endScore > highscores_[i].second)
                {
                    highscores_.insert(highscores_.begin()+i, make_pair(name, getEndScore()));
                    break;
                }
            }

            highscores_.erase(highscores_.begin()+5);
        }

    endScore = 0;
}

void Scoreboard::onNotify(Event event)
{
    switch (event)
    {
        case Observer::Event::POWER_PELLET_EATEN:
            ghost_counter_ = 0;
        case Observer::Event::SUPER_PELLET_EATEN:
            increaseScore(PELLET_SCORE*n);
            break;
        case Observer::Event::FRUIT_EATEN:
            increaseScore(FRUIT_SCORE*n);
            break;
        case Observer::Event::GHOST_EATEN:
            {
                increaseScore(GHOST_SCORE*pow(2,ghost_counter_));
                ghost_counter_++;
                if (ghost_counter_ == 4)
                {
                    ghost_counter_ = 0;
                    increaseScore(GHOST_SCORE*pow(2,4));
                }
            }
        default:
            break;
    }
}
