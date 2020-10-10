#include "AssetManager.h"
#include <iostream>
#include <string>

void AssetManager::loadTexture(const string& name, const string& filePath)
{
    auto texture = make_shared<sf::Texture>();

    if(!texture->loadFromFile(filePath))
    {
        // throw exception
    }

    textures_[name] = texture;
}

AssetManager::texturePtr AssetManager::getTexture(const string& name)
{
    return textures_[name];
}

void AssetManager::loadFont(const string& name, const string& filePath)
{
    auto font = make_shared<sf::Font>();

    if(!font->loadFromFile(filePath))
    {
        // throw exception
    }

    fonts_[name] = font;
}

AssetManager::fontPtr AssetManager::getFont(const string& name)
{
    return fonts_[name];
}

void AssetManager::loadSoundBuffer(const string& name, const string& filePath)
{
    auto buffer = make_shared<sf::SoundBuffer>();

    if(!buffer->loadFromFile(filePath))
    {
        // throw exception
    }

    buffers_[name] = buffer;
    sounds_[name].setBuffer(*buffers_[name]);
}

void AssetManager::playSound(const string& name)
{
    sounds_[name].play();
}

void AssetManager::loadMusic(const string& name, const string& filePath)
{
    auto music_pointer = make_unique<sf::Music>();

    if(!music_pointer->openFromFile(filePath))
    {
        // throw exception
    }

    music_[name] = move(music_pointer);   // this might not work... I'm just guessing
}

void AssetManager::playSong(const string& name)
{
    music_[name]->play();
}

void AssetManager::pauseSong(const string& name)
{
    music_[name]->pause();
}

void AssetManager::stopSong(const string& name)
{
    music_[name]->stop();
}

void AssetManager::setLoop(const string& name, bool isLoop)
{
    music_[name]->setLoop(isLoop);
}

sf::SoundSource::Status AssetManager::getStatus(const string& name)
{
    return music_[name]->getStatus();
}


void AssetManager::loadMazeList()
{
    mazeList_.clear();

    auto filePath = MAZE_LIST_FILEPATH;

    fileReader_.readFile(mazeList_, filePath);
}

vector<string>& AssetManager::getMazeList()
{
    return mazeList_;
}


void AssetManager::loadLayout(const string& name, const string& mazeName)
{
    auto filePath = MAZE_DIRECTORY + mazeName + "_layout.txt";
    vector<string> layout;
    fileReader_.readFile(layout, filePath);
    layouts_[name] = layout;
}

void AssetManager::loadCredits()
{
    auto filePath = CREDITS_FILEPATH;
    fileReader_.readFile(credits_, filePath);
}

vector<string>& AssetManager::getCredits()
{
    return credits_;
}

vector<string>& AssetManager::getLayout(const string& name)
{
    return layouts_[name];
}

void AssetManager::loadRotationMap(const string& name, const string& mazeName)
{
    auto filePath = MAZE_DIRECTORY + mazeName + "_orientations.txt";
    vector<string> rotationMap;
    fileReader_.readFile(rotationMap, filePath);
    rotationMaps_[name] = rotationMap;
}

vector<string>& AssetManager::getRotationMap(const string& name)
{
    return rotationMaps_[name];
}

void AssetManager::loadKeyMap(const string& name, const string& mazeName)
{
    auto filePath = MAZE_DIRECTORY + mazeName + "_keymap.txt";
    Maze::posKeyMap keyMap;
    fileReader_.readFile(keyMap, filePath);
    keyMaps_[name] = keyMap;
}

Maze::posKeyMap& AssetManager::getKeyMap(const string& name)
{
    return keyMaps_[name];
}

void AssetManager::loadStartPos(const string& name, const string& mazeName)
{
    auto filePath = MAZE_DIRECTORY + mazeName + "_startpositions.txt";
    vector<sf::Vector2f> startPos;
    fileReader_.readFile(startPos, filePath);
    startPos_[name] = startPos;
}

vector<sf::Vector2f>& AssetManager::getStartPos(const string& name)
{
    return startPos_[name];
}

void AssetManager::loadHighScores(const string& mazeName)
{
    auto filePath = HIGH_SCORE_DIRECTORY + mazeName + ".txt";
    fileReader_.readFile(highScores_, filePath);
}

vector<pair<string,int>>& AssetManager::getHighScores()
{
    return highScores_;
}

/*---------------------- Writing -----------------------*/
void AssetManager::addMazeName(string& mazeName)
{
    auto filePath = MAZE_LIST_FILEPATH;

    mazeList_.clear();

    loadMazeList();

    if (find(mazeList_.begin(), mazeList_.end(), mazeName) == mazeList_.end())
        fileWriter_.writeFile(mazeName, filePath);
}

void AssetManager::writeLayout(vector<string>& layout, const string& mazeName)
{
    auto filePath = MAZE_DIRECTORY + mazeName + "_layout.txt";

    fileWriter_.writeFile(layout, filePath);
}

void AssetManager::writeRotationMap(vector<string>& rotations, const string& mazeName)
{
    auto filePath = MAZE_DIRECTORY + mazeName + "_orientations.txt";

    fileWriter_.writeFile(rotations, filePath);
}

void AssetManager::writeKeyMap(map<sf::Vector2i,vector<sf::Vector2i>>& keyMapIndices, const string& mazeName)
{
    auto filePath = MAZE_DIRECTORY + mazeName + "_keymap.txt";

    fileWriter_.writeFile(keyMapIndices, filePath);
}

void AssetManager::writeStartPos(vector<sf::Vector2i>& startPos, const string& mazeName)
{
    auto filePath = MAZE_DIRECTORY + mazeName + "_startpositions.txt";

    fileWriter_.writeFile(startPos, filePath);
}

void AssetManager::deleteMazeData(string& mazeName)
{
    // Get old maze from list
    auto mazeList = getMazeList();
    
    // Remove name
    mazeList.erase(remove(mazeList.begin(), mazeList.end(), mazeName), mazeList.end());
    
    // Clear old file
    ofstream file;
    file.open(MAZE_LIST_FILEPATH);
    file.close();
    
    // Add adjusted list
    for (auto& mazeName : mazeList)
        addMazeName(mazeName);
    
    auto str = MAZE_DIRECTORY + mazeName + "";
    auto n = str.length();
    
    vector<string> fileSuffixes{"_layout.txt", "_orientations.txt", "_keymap.txt", "_startpositions.txt"};
    
    for (auto suffix : fileSuffixes)
    {
        str = MAZE_DIRECTORY + mazeName + suffix;
        
        n = str.length();
        
        char filePath[n + 1];
        
        strcpy(filePath, str.c_str());
        
        if (remove(filePath) != 0)
            cout << "FILE NOT DELETED" << endl;
    }
    
    str = HIGH_SCORE_DIRECTORY + mazeName + ".txt";
    n = str.length();
    char filePath[n + 1];
    strcpy(filePath, str.c_str());
    
    if (remove(filePath) != 0)
        cout << "FILE NOT DELETED" << endl;
}

void AssetManager::writeHighScores(vector<pair<string, int>> highScores, const string& mazeName)
{
    auto filePath = HIGH_SCORE_DIRECTORY + mazeName + ".txt";

    fileWriter_.writeFile(highScores, filePath);
}


