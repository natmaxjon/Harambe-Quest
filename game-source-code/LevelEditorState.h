#ifndef LEVEL_EDITOR_STATE_H
#define LEVEL_EDITOR_STATE_H

/// \file LevelEditorState.h
/// \brief Contains the class definition for the "LevelEditorState" class

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "Configuration.h"
#include "AssetManager.h"

#include "State.h"
#include "GameLoop.h"
#include "Button.h"

#include <vector>

namespace sf
{
/// Overloading the < operator so that sf::Vector2f can be used in std::maps
extern bool operator<(const Vector2f& left, const Vector2f& right);

/// Overloading the < operator so that sf::Vector2i can be used in std::maps
extern bool operator<(const Vector2i& left, const Vector2i& right);
}

/// \class LevelEditorState
/// \brief The state that coordinates the user input, internal logic and rendering required for a user to design, build and save their own custom maze.
///
/// The editor is presented as a GUI containing the maze grid, and several buttons and key inputs that allow the user to choose the following settings of the maze: tile type and arrangemnt of tiles, the rotation of each tile, the linkage between keys and doors, the start positions of the characters and the name of the maze. The user can then save the maze, which writes their design to text files to be loaded later in the EndlessLevelState

class LevelEditorState: public State
{
public:
    
    /// \enum possible selections for the build buttons
    enum class BuildSelection
    {
        NOTHING,
        WALL,
        CORNER,
        GATE,
        KEY,
        FRUIT,
        POWER_PELLET,
        SUPER_PELLET,
        ERASER,
        TEXTBOX,
        LINK_KEYS,
        PLAYER,
        BLINKY,
        INKY,
        PINKY,
        CLYDE
    };

    /// \enum possible selections for the bottom buttons
    enum class BottomSelection {EXIT, SAVE, CLEAR, HELP};
    
    /// Constructor.
    /// @param game a shared pointer to a structure containing the game's state machine, asset manager, input manager and display window
    LevelEditorState(gamePtr game);

    /// Load the buttons, grid and textbox using the asset manager.
    void initialise() override;
    
    /// Process the user input using the input manager.
    ///
    /// The following input events are monitored: exit request, mouse button clicks (selecting buttons and textbox), text entered event (for entering the maze name), key pressed events for 'R' (rotate), 'C' (clear), BACKSPACE (delete maze name) and ENTER (confirm maze name)
    void processInput() override;
    
    /// Update the state of the grid and its contents, the selection and rotation of the buttons and the textbox letters.
    /// @param dt the elapsed time in milliseconds
    void update(float dt) override;
    
    /// Render the grid and its contents, the buttons and the textbox to the screen.
    /// @param dt the elapsed time in milliseconds
    void draw(float dt) override;

private:
    const sf::FloatRect gridBounds_{GRID_POSITION, GRID_SIZE};

    gamePtr game_;

    // Buttons
    map<BottomSelection, Button> bottomButtons_;
    map<BuildSelection, Button> buildButtons_;
    BuildSelection currentSelection_ = BuildSelection::NOTHING;
    BuildSelection previousSelection_ = BuildSelection::NOTHING;

    // Grid
    vector<sf::Vertex> gridLines_;
    vector<sf::Text> gridNumbers_;
    sf::RectangleShape highlightSquare_;
    map<pair<float, float>, sf::Sprite> gridSprites_;
    sf::Texture bgTexture_;
    sf::Sprite background_;

    // Textbox
    string mazeName_;
    sf::Text displayName_;
    sf::Text helpText_;
    string helpString_;
    int maxNameLength_ = 10;

    // Key link
    bool isKeySelected_ = false;
    sf::Vector2f selectedKeyPos_;
    sf::Vector2i selectedKeyIndex_;
    map<sf::Vector2f,vector<sf::Vector2f>> keyMapPos_;
    map<sf::Vector2i,vector<sf::Vector2i>> keyMapIndices_;
    sf::RectangleShape linkLine_;

    // Maze data
    vector<string> layout_{NUM_ROWS, string(NUM_COLS,'E')};
    vector<string> rotationMap_{NUM_ROWS, string(NUM_COLS,'0')};

    /*------------- Private helper functions -------------*/

    // Loading data
    void loadButtons(AssetManager& assetManager);
    void loadBottomButtons(AssetManager& assetManager);
    void loadBuildButtons(AssetManager& assetManager);
    void loadGrid();
    void loadGridLines();
    void loadGridNumbers();
    void loadHighlightSquare();
    void loadKeyLinkLine();
    void loadTextBox();

    // Handling input
    void deselectKey();
    void handleButtonInput();
    bool saveSuccessful();
    bool mazeHasNoEdibles();
    void clear();
    void selectBuildButton();
    void applyRadioStyle();

    void handleKeyLinkEvent();
    bool isKeyBlock();
    bool isGateBlock();
    void selectKey();
    void addGate();
    void rotateSelectedSprite();

    // Updating state elements
    void updateButtons();
    void updateGrid();
    bool isMousePressed();
    bool gridContainsMouse();
    void removeGridSprite(sf::Vector2f position);
    void addGridSprite(sf::Vector2f position);
    void updateKeyMap(sf::Vector2f position, sf::Vector2i index);
    sf::Vector2f map2GridPosition(sf::Vector2i position);
    sf::Vector2f map2GridPosition(sf::Vector2f position);
    sf::Vector2i map2GridIndex(sf::Vector2f position);
    sf::Sprite createGridSprite(sf::Vector2f position);
    char getLayoutChar();
    char getAngleChar();
    void updateCharacters();
    void updateNameText();
    bool textIsValid(uint32_t unicode);

    // Rendering state elements
    void drawButtons();
    void drawGrid();
    void drawGridNumbers();
    void drawHighlightSquare();
    void drawGridSprites();
    void drawLinkLines();
    void drawDanglingLink();
    void drawExistingLinks();
};

#endif
