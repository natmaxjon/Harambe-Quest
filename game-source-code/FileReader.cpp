#include "FileReader.h"
#include <iostream>
void FileReader::readFile(vector<string>& layout, const string& pathToFile)
{
    openFile(pathToFile);

    auto row = ""s;

	while (getline(file_, row))
        layout.push_back(row);

    file_.close();
}

void FileReader::readFile(map<tuple<int,int>, vector<tuple<int,int>>>& keyMap, const string& pathToFile)
{
    openFile(pathToFile);

    auto keyString = ""s;
    auto gateString = ""s;

    stringstream keyStream(keyString);
    stringstream gateStream(gateString);

    auto keyPosX = 0;
    auto keyPosY = 0;

    auto gatePosX = 0;
    auto gatePosY = 0;

    vector<tuple<int,int>> gatePairs = {};

    while (getline(file_, keyString) && getline(file_, gateString))
    {
        keyStream = stringstream(keyString);
        gateStream = stringstream(gateString);

        keyStream >> keyPosX >> keyPosY;

        while (gateStream >> gatePosX && gateStream >> gatePosY)
            gatePairs.push_back(make_tuple(gatePosX, gatePosY));

        keyMap.insert({make_tuple(keyPosX, keyPosY), gatePairs});

        gatePairs = {};
    }

    file_.close();
}

void FileReader::readFile(vector<sf::Vector2f>& startPos, const string& pathToFile)
{
    openFile(pathToFile);

    auto posString = ""s;

    stringstream posStream(posString);

    auto posX = 0.f;
    auto posY = 0.f;

    while (getline(file_, posString))
    {
        posStream = stringstream(posString);

        posStream >> posX >> posY;

        startPos.push_back(sf::Vector2f{posX,posY});
    }

    file_.close();
}

void FileReader::readFile(vector<pair<string,int>>& highScores,  const string& pathToFile)
{
    openFile(pathToFile);

    highScores.clear();

    auto scoreLine = ""s;
    stringstream scoreStream(scoreLine);
    auto name = ""s;
    auto score = ""s;

    while (getline(file_, scoreLine))
    {
        scoreStream = stringstream(scoreLine);
        scoreStream >> name >> score;
        highScores.push_back(make_pair(name, stoi(score)));
    }

    file_.close();
}

void FileReader::openFile(const string& pathToFile)
{
    file_.open(pathToFile);

    if (!file_.is_open())
        cout << "FILE FAILED TO OPEN" << endl;
}

