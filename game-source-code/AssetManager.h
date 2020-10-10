#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

/// \file AssetManager.h
/// \brief Contains the class definition for the "AssetManager" class

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "FileReader.h"
#include "FileWriter.h"
#include "Maze.h"

#include <map>

using namespace std;

/// \class AssetManager
/// \brief This class manages the access to the resources required by the game during runtime
///
/// It provides methods for loading resources into memory, writing to files from memeory, and providing access to textures, fonts, sounds, music, and other data saved by the user at runtime.

class AssetManager
{
public:
    typedef shared_ptr<sf::Texture> texturePtr; /**\typedef a shared pointer to a sf::Texture, to improve readability */
    typedef shared_ptr<sf::Font> fontPtr; /**\typedef a shared pointer to a sf::Font, to improve readability */
    typedef shared_ptr<sf::SoundBuffer> bufferPtr; /**\typedef a shared pointer to a sf::SoundBuffer, to improve readability */
    typedef unique_ptr<sf::Music> music_ptr; /**\typedef a unique pointer to a sf::Music object, to improve readability */

    /// Load a texture into memory
    /// @param name texture name
    /// @param filePath relative path to texture
    void loadTexture(const string& name, const string& filePath);
    
    /// Get texture corresponding to the texture name given
    /// @param name texture name
    /// \return shared pointer to the requested texture
    texturePtr getTexture(const string& name);
    
    /// Load a font into memory
    /// @param name font name
    /// @param filePath relative path to font
    void loadFont(const string& name, const string& filePath);
    
    /// Get font corresponding to the font name given
    /// @param name font name
    /// \return shared pointer to the requested font
    fontPtr getFont(const string& name);
    
    /// Load a sound buffer into memory
    /// @param name sound buffer name
    /// @param filePath relative path to sound buffer
    void loadSoundBuffer(const string& name, const string& filePath);
    
    /// Plays the sound corresponding to the sound buffer name given
    /// @param name sound buffer name
    void playSound(const string& name);
    
    /// Load a pointer to a music file into memory
    /// @param name song name
    /// @param filePath relative path to music file
    void loadMusic(const string& name, const string& filePath);
    
    /// Plays the song corresponding to the song name given
    /// @param name song name
    void playSong(const string& name);
    
    /// Pauses the song corresponding to the song name given
    /// @param name song name
    void pauseSong(const string& name);
    
    /// Stops the song corresponding to the song name given
    /// @param name song name
    void stopSong(const string& name);
    
    /// Sets the song corresponding to the song name given to loop continuously
    /// @param name song name
    /// @param isLoop boolean that is true if the song should loop continuously, and false if it should not
    void setLoop(const string& name, bool isLoop);
    
    /// Get the playing status of the song corresponding to the song name given
    /// @param name song name
    /// \return an enum representing the playing status of the song (Stopped, Paused or Playing)
    sf::SoundSource::Status getStatus(const string& name);
    
    /// Load the list of mazes into memory
    void loadMazeList();
    
    /// Get maze list
    /// \return a vector of strings where each string represents a maze on the list
    vector<string>& getMazeList();
    
    /// Load a maze layout into memory corresponding to the name given
    /// @param name layout name
    /// @param mazeName the name of the maze
    void loadLayout(const string& name, const string& mazeName);
    
    /// Get the maze layout corresponding to the name given
    ///
    /// Note that each string in the vector returned represents a row in the maze where each character corresponds to a tile type (E - empty; W - wall; C - corner; G - gate; K - key; F - fruit; P - power pellet; S - super pellet)
    /// @param name name of the layout
    /// \return a reference to a vector of strings where each string represents a row in the maze
    vector<string>& getLayout(const string& name);
    
    /// Load a maze rotation map into memory corresponding to the name given
    /// @param name rotation map name
    /// @param mazeName the name of the maze
    void loadRotationMap(const string& name, const string& mazeName);
    
    /// Get the maze rotation map corresponding to the name given
    ///
    /// Note that each string in the vector returned represents a row in the maze where each character corresponds to a tile rotation ('0' - 0 degrees; '1' - 90 degrees; '2' - 180 degrees; '3'- 270 degrees)
    /// @param name name of the rotation map
    /// \return a reference to a vector of strings where each string represents a row in the maze
    vector<string>& getRotationMap(const string& name);
    
    /// Load a key map into memory corresponding to the name given
    /// @param name key map name
    /// @param mazeName the name of the maze
    void loadKeyMap(const string& name, const string& mazeName);
    
    /// Get the maze key map corresponding to the name given
    ///
    /// @param name key map name
    /// \return a reference to a map relating a tuple of two ints (the key indices) to a vector of tuples of two ints (the gate indices)
    Maze::posKeyMap& getKeyMap(const string& name);
    
    /// Load the character start positions into memory corresponding to the name given
    /// @param name character start positions file name
    /// @param mazeName the name of the maze
    void loadStartPos(const string& name, const string& mazeName);
    
    /// Get the character start positions corresponding to the name given
    ///
    /// Note that each sf::Vector2f corresponds to a character position, with the first position being for the player, and the following positions for the enemies
    /// @param name character start positions file name
    /// \return a reference to a vector of sf::Vector2f positions representing the starting maze indices for the characters
    vector<sf::Vector2f>& getStartPos(const string& name);
    
    /// Load all the highscores related to the maze specifed by the maze name
    /// @param mazeName the name of the maze
    void loadHighScores(const string& mazeName);
    
    /// Get all the highscores
    /// This returns the highscores corresponding to the current maze name selected
    /// \return a reference to a vector of pairs relating the player names to their scores
    vector<pair<string,int>>& getHighScores();
    
    /// Load the credits for the game
    void loadCredits();
    /// Get the credits for the game
    vector<string>& getCredits();


    /*----------------------- Writing to Files--------------------------------*/
    
    /// Add a maze name to the maze list
    /// @param mazeName name of the maze
    void addMazeName(string& mazeName);
    
    /// Write a layout file linked to the given maze name
    /// @param layout layout file name
    /// @param mazeName name of the maze
    void writeLayout(vector<string>& layout, const string& mazeName);
    
    /// Write a rotation map file linked to the given maze name
    /// @param layout rotation map file name
    /// @param mazeName name of the maze
    void writeRotationMap(vector<string>& layout, const string& mazeName);
    
    /// Write a key map file linked to the given maze name
    /// @param keyMapIndices key map file name
    /// @param mazeName name of the maze
    void writeKeyMap(map<sf::Vector2i,vector<sf::Vector2i>>& keyMapIndices, const string& mazeName);
    
    /// Write a start positions file file linked to the given maze name
    /// @param startPos start positions file name
    /// @param mazeName name of the maze
    void writeStartPos(vector<sf::Vector2i>& startPos, const string& mazeName);
    
    void deleteMazeData(string& mazeName);
    
    /// Write a highscores file linked to the given maze name
    /// @param highScores highscores file name
    /// @param mazeName name of the maze
    void writeHighScores(vector<pair<string,int>> highScores, const string& mazeName);

private:
    vector<string> mazeList_;
    vector<string> credits_;

    map<string,texturePtr> textures_;
    map<string,fontPtr> fonts_;

    map<string,bufferPtr> buffers_;
    map<string,sf::Sound> sounds_;

    map<string,music_ptr> music_;

    map<string,vector<string>> layouts_;
    map<string,vector<string>> rotationMaps_;
    map<string,Maze::posKeyMap> keyMaps_;
    map<string,vector<sf::Vector2f>> startPos_;
    vector<pair<string,int>> highScores_;

    FileReader fileReader_;
    FileWriter fileWriter_;
};

#endif
