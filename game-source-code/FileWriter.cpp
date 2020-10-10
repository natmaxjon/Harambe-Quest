#include "FileWriter.h"

void FileWriter::writeFile(string& mazeName, const string& pathToFile)
{
    file_.open(pathToFile, ofstream::app);

    file_ << mazeName << "\n";

    file_.close();
}

void FileWriter::writeFile(vector<string>& layout, const string& pathToFile)
{
    file_.open(pathToFile, ofstream::out | ofstream::trunc);

    for (auto row : layout)
    {
        file_ << row << "\n";
    }

    file_.close();
}

void FileWriter::writeFile(map<sf::Vector2i,vector<sf::Vector2i>>& keyMapIndices, const string& pathToFile)
{
    file_.open(pathToFile, ofstream::out | ofstream::trunc);

    for (auto [keyIndex, gateIndices] : keyMapIndices)
    {
        file_ << keyIndex.x << " " << keyIndex.y << "\n";

        for (auto gateIndex : gateIndices)
            file_ << gateIndex.x << " " << gateIndex.y << " ";

        file_ << "\n";
    }

    file_.close();
}

void FileWriter::writeFile(vector<sf::Vector2i>& startPos, const string& pathToFile)
{
    file_.open(pathToFile, ofstream::out | ofstream::trunc);

    for (auto pos : startPos)
    {
        file_ << pos.x << " " << pos.y << "\n";
    }

    file_.close();
}

void FileWriter::writeFile(vector<pair<string,int>>& highScores, const string& pathToFile)
{

    file_.open(pathToFile, ofstream::out | ofstream::trunc);

    for (auto entry : highScores)
    {
        file_ << entry.first << " " << entry.second << "\n";
    }

    file_.close();
}


