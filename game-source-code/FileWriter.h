#ifndef FILE_WRITER_H
#define FILE_WRITER_H
/** \file FileWriter.h
 *  \brief Contains the class definition of the FileWriter Class
 */
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <utility>

using namespace std;

/** \class FileWriter
 *  \brief An object which is capable of writing files to the external system
 *
 *  Acts as a single point of outputting files to the system
 */

class FileWriter
{
public:

    /** \brief Overloaded function to write to a file
     *
     *  Writes to the file stored in the given path, writing the vector given line by line.
     *
     *  \param layout, a reference to a vector of strings
     *  \param pathToFile, the path to the file which needs to be written to
     */
	void writeFile(vector<string>& layout, const string& pathToFile);

	/** \brief Overloaded function to write to a file
     *
     *  Writes the key for each element on a line followed by all the components of the second element on the next,
     *  for the whole map.
     *
     *  \param keyMap, a reference to a map
     *  \param pathToFile, the path to the file which needs to be written to
     */
    void writeFile(map<sf::Vector2i,vector<sf::Vector2i>>& keyMap, const string& pathToFile);

    /** \brief Overloaded function to write to a file
     *
     *  Writes each component sf::Vector2i on a single line, for the whole vector
     *
     *  \param startPos, a reference to the vector of sf::Vector2i
     *  \param pathToFile, the path to the file which needs to be written to
     */
    void writeFile(vector<sf::Vector2i>& startPos, const string& pathToFile);

    /** \brief Overloaded function to write to a file
     *
     *  Adds the string passed in to the end of the file
     *
     *  \param mazeName, which needs to be added
     *  \param pathToFile, the path to the file which needs to be written to
     */
    void writeFile(string& mazeName, const string& pathToFile);

    /** \brief Overloaded function to write to a file
     *
     *  Writes each high score pair on a new line, with the name followed by the score
     *
     *  \param highScores, a reference to a vector of pair<string, int>
     *  \param pathToFile, the path to the file which needs to be written to
     */
    void writeFile(vector<pair<string,int>>& highScores,  const string& pathToFile) ;


private:
	ofstream file_;

    // Private helper functions
    void openFile(const string& pathToFile);

};

#endif

