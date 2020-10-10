#include "Soundboard.h"
#include <random>
#include <chrono>
using namespace std;

#include <chrono>

Soundboard::Soundboard(gamePtr game) : game_(game)
{
    numSongs_ = playList_.size();
    for (int i = 0; i< numSongs_; i++)
    {
        if (game_->assetManager.getStatus(playList_[i]) == sf::SoundSource::Status::Playing)
        {
            currentSong_ = i;
        }
    }
}

Soundboard::Soundboard(gamePtr game, bool highScore) : game_(game)
{
    if (highScore)
        song_ = "xue hua piao";
    else
        song_ = "coffin dance";


    game_->assetManager.playSong(song_);
    game_->assetManager.setLoop(song_, true);
}

Soundboard::~Soundboard()
{
    //dtor
}

void Soundboard::gotoMenu()
{
    for (auto song : playList_)
    {
        if (game_->assetManager.getStatus(song) == sf::SoundSource::Status::Playing)
        {
           game_->assetManager.stopSong(song);
        }
    }

    if (game_->assetManager.getStatus(song_) == sf::SoundSource::Status::Playing)
    {
        game_->assetManager.stopSong(song_);
    }
}

void Soundboard::restart()
{
    gotoMenu();

    shufflePlaylist();

    game_->assetManager.playSong(playList_[0]);
}


void Soundboard::checkSong()
{
    if (game_->assetManager.getStatus(playList_[currentSong_]) != sf::SoundSource::Status::Playing)
    {
        currentSong_++;
        if (currentSong_ == numSongs_)
            currentSong_ = 0;

        game_->assetManager.playSong(playList_[currentSong_]);

    }
}

void Soundboard::nextSong()
{
    game_->assetManager.stopSong(playList_[currentSong_]);

    currentSong_++;
    if (currentSong_ == numSongs_)
        currentSong_ = 0;

    game_->assetManager.playSong(playList_[currentSong_]);
}

void Soundboard::prevSong()
{
    game_->assetManager.stopSong(playList_[currentSong_]);

    currentSong_--;
    if (currentSong_ == -1)
        currentSong_ = numSongs_-1;

    game_->assetManager.playSong(playList_[currentSong_]);
}

void Soundboard::lastLife()
{
    game_->assetManager.stopSong(playList_[currentSong_]);
    if (game_->assetManager.getStatus("damaged coda") != sf::SoundSource::Status::Playing)
    {
        game_->assetManager.playSong("damaged coda");
    }
}

void Soundboard::gameOver()
{
    if (game_->assetManager.getStatus("damaged coda") == sf::SoundSource::Status::Playing)
        game_->assetManager.stopSong("damaged coda");
    else
        game_->assetManager.stopSong(playList_[currentSong_]);
}

void Soundboard::nextLevel()
{
    if (game_->assetManager.getStatus("damaged coda") == sf::SoundSource::Status::Playing)
            game_->assetManager.stopSong("damaged coda");

    if (game_->assetManager.getStatus(playList_[currentSong_]) != sf::SoundSource::Status::Playing)
        game_->assetManager.playSong(playList_[currentSong_+1]);
}

void Soundboard::onNotify(Event event)
{
    auto& assetManager = game_->assetManager;
    switch (event)
    {
        case Observer::Event::POWER_PELLET_EATEN:
            assetManager.playSound("power pellet");
            break;
        case Observer::Event::SUPER_PELLET_EATEN:
            assetManager.playSound("super pellet");
            break;
        case Observer::Event::FRUIT_EATEN:
            break;
        case Observer::Event::GHOST_EATEN:
            assetManager.playSound("eat ghost");
            break;
        case Observer::Event::KEY_EATEN:
            assetManager.playSound("key");
            break;
        case Observer::Event::GATE_BROKEN:
            assetManager.playSound("gate break");
            break;
        case Observer::Event::LIFE_LOST:
            assetManager.playSound("player die");
            break;
        default:
            break;
    }
}

/*-------------- Static Playlist -------------------*/
vector<string> Soundboard::playList_ = PLAYLIST;
default_random_engine Soundboard::engine_;

void Soundboard::seedRandom()
{
   default_random_engine new_engine;
   engine_ = new_engine;
   engine_.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

void Soundboard::shufflePlaylist()
{
   std::shuffle(playList_.begin(), playList_.end(), engine_);
}

vector<string> Soundboard::getPlaylist()
{
    return playList_;
}
