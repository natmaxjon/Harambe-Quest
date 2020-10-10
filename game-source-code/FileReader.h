#ifndef FILE_READER_H
#define FILE_READER_H
/** \file FileReader.h
 *  \brief Contains the class definition of the FileReader Class
 */
#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <utility>

using namespace std;

/** \class FileReader
 *  \brief An object which is capable of reading files from the external system and sending them
 *  to the rest of the program
 *
 *  Acts as a single point of entry of files coming from the system.
 */
class FileReader
{
public:

    /** \brief Overloaded function to read a file
     *
     *  Reads the file stored in the given path, and stores it line by line in the vector given
     *
     *  \param layout, a reference to a vector of strings
     *  \param pathToFile, the path to the file which needs to be read
     */
	void readFile(vector<string>& layout, const string& pathToFile);

	 /** \brief Overloaded function to read a file
     *
     *  Reads the file stored in the given path, two lines at a time, and separates each line
     *  into a tuple corresponding to a key position, and a vector of tuples corresponding to
     *  the gates the key links to.
     *
     *  \param keyMap, a reference to a map, linking the tuple with the vector of tuples
     *  \param pathToFile, the path to the file which needs to be read
     */
    void readFile(map<tuple<int,int>, vector<tuple<int,int>>>& keyMap, const string& pathToFile); // Change to sf::Vector2f

    /** \brief Overloaded function to read a file
     *
     *  Reads the file stored in the given path, and stores the two components of each line in a
     *  sf::Vector2f, and each sf::Vector2f in a vector.
     *
     *  \param startPos, a reference to a vector of sf::Vector2
     *  \param pathToFile, the path to the file which needs to be read
     */
    void readFile(vector<sf::Vector2f>& startPos, const string& pathToFile);

    /** \brief Overloaded function to read a file
     *
     *  Reads the file stored in the given path, with each line read as a pair of string and integer,
     *  consisting of a name and the corresponding high score. All the pairs are contained in a vector.
     *
     *  \param highScores, a reference to a vector of pair<string, int>
     *  \param pathToFile, the path to the file which needs to be read
     */
    void readFile(vector<pair<string,int>>& highScores,  const string& pathToFile) ;



private:
	ifstream file_;

    // Private helper functions
    void openFile(const string& pathToFile);

};

#endif

