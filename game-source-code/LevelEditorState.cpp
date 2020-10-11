#include "LevelEditorState.h"
#include "MainMenuState.h"
#include "MazeEditorHelp.h"

#include <cmath>
#include <string>
#include <iostream>


bool sf::operator<(const Vector2f& left, const Vector2f& right)
{
    return left.x < right.x || (left.x == right.x && left.y < right.y);
}

bool sf::operator<(const Vector2i& left, const Vector2i& right)
{
    return left.x < right.x || (left.x == right.x && left.y < right.y);
}

LevelEditorState::LevelEditorState(gamePtr game): game_{game}
{
    // error checking
}

void LevelEditorState::initialise()
{
    loadButtons(game_->assetManager);
    loadGrid();
    loadTextBox();
}

void LevelEditorState::processInput()
{
    sf::Event event;

    while (game_->window.pollEvent(event))
    {
        if (game_->inputManager.isExitRequest(event))
            game_->window.close();
        
        if (event.type == sf::Event::Resized)
        {
            game_->view = game_->inputManager.getLetterboxView(game_->view, event.size.width, event.size.height);
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                isKeySelected_ = false;
                handleButtonInput();
            }

            if (event.mouseButton.button == sf::Mouse::Right)
                handleKeyLinkEvent();
        }

        if (event.type == sf::Event::TextEntered && currentSelection_ == BuildSelection::TEXTBOX)
        {
            if (textIsValid(event.text.unicode))
            {
                if (mazeName_.size() < maxNameLength_)
                    mazeName_+= static_cast<char>(event.text.unicode);
            }
        }

        if (event.type == sf::Event::KeyPressed && currentSelection_ == BuildSelection::TEXTBOX)
        {
            if (event.key.code == sf::Keyboard::BackSpace)
            {
                if (mazeName_.size() > 0)
                    mazeName_.erase(mazeName_.size() - 1);
            }

            if (event.key.code == sf::Keyboard::Enter)
            {
                buildButtons_[BuildSelection::TEXTBOX].deselect();
                currentSelection_ = BuildSelection::NOTHING;
            }
        }

        if (currentSelection_ != BuildSelection::TEXTBOX)
        {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
                rotateSelectedSprite();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
                clear();
        }
    }
}

void LevelEditorState::update(float dt)
{
    updateButtons();
    updateGrid();
    updateNameText();
}

void LevelEditorState::draw(float dt)
{
    game_->window.clear(sf::Color{26,26,26});
    game_->window.setView(game_->view);

    game_->window.draw(background_);
    drawGrid();
    game_->window.draw(displayName_);
    drawButtons();

    game_->window.display();
}

/*------------- Private helper functions -------------*/

/*----- Loading data -----*/

void LevelEditorState::loadButtons(AssetManager& assetManager)
{
    loadBottomButtons(assetManager);
    loadBuildButtons(assetManager);
}

void LevelEditorState::loadBottomButtons(AssetManager& assetManager)
{
    vector<string> name{"EXIT", "SAVE", "CLEAR"};
    vector<BottomSelection> selection{BottomSelection::EXIT, BottomSelection::SAVE, BottomSelection::CLEAR};

    Button button{assetManager.getTexture("menu button"), assetManager.getFont("coarse 8-bit")};
    button.setSpriteScale(0.4, 0.4);
    button.setTextScale(0.5, 0.5);

    for (auto i = 0; i < selection.size(); i++)
    {
        button.setString(name[i]);
        button.setPosition(GRID_POSITION.x + (i+1)*GRID_SIZE.x/4.f, GRID_POSITION.y + GRID_SIZE.y + 65);
        bottomButtons_[selection[i]] = button;
    }

    button = Button{assetManager.getTexture("question mark")};
    button.setPosition(GAME_WIDTH-50,GAME_HEIGHT-50);
    button.setSpriteScale(0.7f,0.7f);
    button.setHoverColour(sf::Color::Yellow);

    bottomButtons_[BottomSelection::HELP] = button;

}

void LevelEditorState::loadBuildButtons(AssetManager& assetManager)
{
    vector<BuildSelection> selection
    {
        BuildSelection::WALL,
        BuildSelection::CORNER,
        BuildSelection::GATE,
        BuildSelection::KEY,
        BuildSelection::FRUIT,
        BuildSelection::POWER_PELLET,
        BuildSelection::SUPER_PELLET,
        BuildSelection::ERASER
    };

    vector<string> textureString{"wall","corner","gate","key","fruit","power pellet","super pellet","eraser"};

    Button button;

    for (auto i = 0; i < selection.size(); i++)
    {
        button = Button{assetManager.getTexture(textureString[i])};
        button.setPosition((GRID_POSITION.x + GRID_SIZE.x + GAME_WIDTH)/2.f, GRID_POSITION.y + (i+1)*GRID_SIZE.y/9.f);
        button.setSpriteColour(sf::Color::White, sf::Color::White, sf::Color::White);

        switch (selection[i])
        {
            case BuildSelection::GATE:
                button.setSpriteScale(17.f/15.f,17.f/15.f); // 17.f/15.f, 17.f/15.f
                break;
            default:
                button.setSpriteScale(1.7f, 1.7f);
                break;
        }

        button.setOutline(4.f);
        buildButtons_[selection[i]] = button;
    }

    button = Button{assetManager.getTexture("blank-button")};
    button.setPosition(GRID_POSITION.x + GRID_SIZE.x/2, GRID_POSITION.y - 20);
    buildButtons_[BuildSelection::TEXTBOX] = button;

    // Clear button is unique
    buildButtons_[BuildSelection::ERASER].setSpriteScale(1.f, 1.f);
    buildButtons_[BuildSelection::ERASER].setOutline(0.f);
    buildButtons_[BuildSelection::ERASER].setSpriteColour(sf::Color::White,sf::Color::Yellow,sf::Color::Green);

    // Player
    button = Button(assetManager.getTexture("harambe head"));
    button.setSpriteScale(1.5f, 1.5f);
    button.setSpriteColour(sf::Color::White, sf::Color::White, sf::Color::White);
    button.setOutlineColour(sf::Color::Transparent, sf::Color::Yellow, sf::Color::Transparent);
    button.setOutline(2.f);
    button.setPosition(390.f, 570.f);
    buildButtons_[BuildSelection::PLAYER] = button;

    textureString = vector<string>
    {
        "red head",
        "purple head",
        "green head",
        "brown head"
    };

    selection = vector<BuildSelection>
    {
        BuildSelection::BLINKY,
        BuildSelection::INKY,
        BuildSelection::PINKY,
        BuildSelection::CLYDE
    };

    for (auto i = 0; i < selection.size(); i++)
    {
        button = Button(assetManager.getTexture(textureString[i]));
        button.setPosition(300.f + i*60, 300.f);
        button.setSpriteScale(10.f/7.f, 10.f/7.f);
        button.setSpriteColour(sf::Color::White, sf::Color::White, sf::Color::White);
        button.setOutlineColour(sf::Color::Transparent, sf::Color::Yellow, sf::Color::Transparent);
        button.setOutline(2.f);
        buildButtons_[selection[i]] = button;
    }
}

void LevelEditorState::loadGrid()
{
    loadGridLines();
    loadGridNumbers();
    loadHighlightSquare();
    loadKeyLinkLine();

    // grass

    bgTexture_ = *game_->assetManager.getTexture("grass");
    bgTexture_.setRepeated(true);
    background_.setTexture(bgTexture_);
    background_.setPosition(GRID_POSITION.x, GRID_POSITION.y);
    background_.setTextureRect(sf::IntRect(GRID_POSITION.x, GRID_POSITION.y, GRID_SIZE.x, GRID_SIZE.y));
}

void LevelEditorState::loadGridLines()
{
    auto pos1 = sf::Vector2f{0,0};
    auto pos2 = sf::Vector2f{0,0};

    // Horizontal lines
    for (auto row = 0; row < NUM_ROWS + 1; row++)
    {
        pos1 = sf::Vector2f{GRID_POSITION.x, GRID_POSITION.y + row * GRID_SPACING};
        pos2 = sf::Vector2f{GRID_POSITION.x + (NUM_COLS) * GRID_SPACING, GRID_POSITION.y + row * GRID_SPACING};

        gridLines_.push_back(sf::Vertex(pos1, sf::Color::Black));
        gridLines_.push_back(sf::Vertex(pos2, sf::Color::Black));
    }

    // Vertical lines
    for (auto col = 0; col < NUM_COLS + 1; col++)
    {
        pos1 = sf::Vector2f{GRID_POSITION.x + col * GRID_SPACING, GRID_POSITION.y};
        pos2 = sf::Vector2f{GRID_POSITION.x + col * GRID_SPACING, GRID_POSITION.y + (NUM_ROWS) * GRID_SPACING};

        gridLines_.push_back(sf::Vertex(pos1, sf::Color::Black));
        gridLines_.push_back(sf::Vertex(pos2, sf::Color::Black));
    }
}

void LevelEditorState::loadGridNumbers()
{
    sf::Text num;
    num.setFont(*game_->assetManager.getFont("pressStart 8-bit"));

    gridNumbers_.push_back(num);

    for (int i = 0; i < 25; i++)
    {
        num.setString(to_string(i));
        num.setOrigin(num.getLocalBounds().width/2, num.getLocalBounds().height/2);
        num.setPosition(GRID_POSITION.x/2.f, GRID_POSITION.y + i * GRID_SPACING + GRID_SPACING/2.f);
        num.setScale(0.45, 0.45);
        gridNumbers_.push_back(num);
    }

    for (int i = 0; i < 23; i++)
    {
        num.setString(to_string(i));
        num.setOrigin(num.getLocalBounds().width/2, num.getLocalBounds().height/2);
        num.setPosition(GRID_POSITION.x + i * GRID_SPACING + GRID_SPACING/2.f, GRID_POSITION.y + GRID_SIZE.y + 15);

        if (i < 10)
            num.setScale(0.45, 0.45);
        else
            num.setScale(0.39, 0.39);

        gridNumbers_.push_back(num);
    }
}

void LevelEditorState::loadHighlightSquare()
{
    highlightSquare_.setSize(sf::Vector2f{GRID_SPACING, GRID_SPACING});
    highlightSquare_.setFillColor(sf::Color{255,255,255,100});
    highlightSquare_.setOrigin(highlightSquare_.getGlobalBounds().width/2.f,
                               highlightSquare_.getGlobalBounds().height/2.f);
}

void LevelEditorState::loadKeyLinkLine()
{
    linkLine_.setSize(sf::Vector2f{0.f, LINK_LINE_THICKNESS});
    linkLine_.setOrigin(0.f, linkLine_.getGlobalBounds().height/2.f);
    linkLine_.setFillColor(sf::Color{231,169,70});
}

void LevelEditorState::loadTextBox()
{
    displayName_.setFont(*game_->assetManager.getFont("pressStart 8-bit"));
    displayName_.setString("Enter Maze Name");
    displayName_.setOrigin(displayName_.getGlobalBounds().width/2, displayName_.getGlobalBounds().height/2);
    displayName_.setPosition(GRID_POSITION.x + GRID_SIZE.x/2, GRID_POSITION.y - 20);
    displayName_.setScale(0.7, 0.7);

    mazeName_ = "";

}

/*----- Handling input -----*/

void LevelEditorState::handleButtonInput()
{
    if (bottomButtons_[BottomSelection::EXIT].isHover(game_->window))
    {
        game_->assetManager.playSound("button click");
        game_->stateMachine.addState(make_unique<MainMenuState>(game_));
    }

    if (bottomButtons_[BottomSelection::SAVE].isHover(game_->window))
    {
        if (saveSuccessful())
            game_->stateMachine.addState(make_unique<MainMenuState>(game_));
    }

    if (bottomButtons_[BottomSelection::CLEAR].isHover(game_->window))
    {
        game_->assetManager.playSound("button click");
        clear();
    }

    if (bottomButtons_[BottomSelection::HELP].isHover(game_->window))
    {
        game_->assetManager.playSound("button click");
        game_->stateMachine.addState(make_unique<MazeEditorHelp>(game_));
    }

    selectBuildButton();
}

bool LevelEditorState::saveSuccessful()
{
    if (mazeName_.size() == 0)
    {
        game_->assetManager.playSound("error");
        displayName_.setFillColor(sf::Color::Red);
        return false;
    }

    if (mazeHasNoEdibles())
    {
        game_->assetManager.playSound("error");
        return false;
    }

    game_->assetManager.playSound("button click");

    auto& assetMan = game_->assetManager;

    assetMan.addMazeName(mazeName_);

    assetMan.writeLayout(layout_, mazeName_);
    assetMan.writeRotationMap(rotationMap_, mazeName_);
    assetMan.writeKeyMap(keyMapIndices_, mazeName_);

    auto startPos = vector<sf::Vector2i>{};
    startPos.push_back(map2GridIndex(buildButtons_[BuildSelection::PLAYER].getPosition()));
    startPos.push_back(map2GridIndex(buildButtons_[BuildSelection::BLINKY].getPosition()));
    startPos.push_back(map2GridIndex(buildButtons_[BuildSelection::INKY].getPosition()));
    startPos.push_back(map2GridIndex(buildButtons_[BuildSelection::PINKY].getPosition()));
    startPos.push_back(map2GridIndex(buildButtons_[BuildSelection::CLYDE].getPosition()));
    assetMan.writeStartPos(startPos, mazeName_);

    auto highScores = vector<pair<string,int>>(5, make_pair("-----", 0));
    assetMan.writeHighScores(highScores, mazeName_);

    return true;
}

bool LevelEditorState::mazeHasNoEdibles()
{
    auto numEdibles = 0;

    for (auto row : layout_)
        for (auto col : row)
            if (col == 'F' || col == 'S' || col == 'P')
                numEdibles++;

    if (numEdibles == 0)
        return true;

    return false;
}

void LevelEditorState::clear()
{
    gridSprites_.clear();
    keyMapPos_.clear();
    keyMapIndices_.clear();
    currentSelection_ = BuildSelection::NOTHING;

    isKeySelected_ = false;

    buildButtons_[BuildSelection::PLAYER].setPosition(390.f, 570.f);
    buildButtons_[BuildSelection::BLINKY].setPosition(300.f, 300.f);
    buildButtons_[BuildSelection::PINKY].setPosition(360.f, 300.f);
    buildButtons_[BuildSelection::INKY].setPosition(420.f, 300.f);
    buildButtons_[BuildSelection::CLYDE].setPosition(480.f, 300.f);

    for (auto& [selection, button] : buildButtons_)
    {
        button.deselect();
        button.setRotation(0.f);
    }

    layout_ = vector<string>{NUM_ROWS, string(NUM_COLS,'E')};
    rotationMap_ = vector<string>{NUM_ROWS, string(NUM_COLS,'0')};

    mazeName_ = "";
}

void LevelEditorState::selectBuildButton()
{
    for (auto [selection, button] : buildButtons_)
    {
        if (button.isHover(game_->window))
        {
            if (selection == previousSelection_)
            {
                button.deselect();
                currentSelection_ = BuildSelection::NOTHING;
            }
            else
            {
                game_->assetManager.playSound("select button");
                currentSelection_ = selection;
            }
        }
    }

    previousSelection_ = currentSelection_;

    applyRadioStyle();
}

void LevelEditorState::applyRadioStyle()
{
    // "Radio" because only one can be selected at a time
    for (auto& [selection, button] : buildButtons_)
    {
        if (selection == currentSelection_)
            button.select();
        else
            button.deselect();
    }
}

bool LevelEditorState::textIsValid(uint32_t unicode)
{
    if (unicode < 48 && unicode != 32)
        return false;

    if (unicode > 122)
        return false;

    if (unicode > 90 && unicode < 97)
        return false;

    if (unicode > 57 && unicode < 65)
        return false;

    return true;
}

void LevelEditorState::updateNameText()
{
    std::string displayText;

    if (mazeName_.size() == 0 && currentSelection_ != BuildSelection::TEXTBOX)
        displayText = "Enter Maze Name";
    else if (mazeName_.size() > 0 && currentSelection_ != BuildSelection::TEXTBOX)
        displayText = mazeName_;
    else
    {
        displayText = mazeName_;

        for (auto i = displayText.size(); i < maxNameLength_; i++)
            displayText += '_';
    }

    displayName_.setString(displayText);
    displayName_.setOrigin(displayName_.getGlobalBounds().width/2.0f,
                            displayName_.getGlobalBounds().height/2.0f);
    displayName_.setPosition(GRID_POSITION.x + GRID_SIZE.x/2-30, GRID_POSITION.y - 30);
    displayName_.setScale(0.7, 0.7);

    if (currentSelection_ == BuildSelection::TEXTBOX)
        displayName_.setFillColor(sf::Color::Yellow);
    else
        displayName_.setFillColor(sf::Color::White);
}

void LevelEditorState::handleKeyLinkEvent()
{
    if (gridContainsMouse())
    {
        if (isKeyBlock())
            selectKey();

        if (isGateBlock() && isKeySelected_)
            addGate();
    }
}

bool LevelEditorState::isKeyBlock()
{
    auto pos = map2GridPosition(game_->window.mapPixelToCoords(sf::Mouse::getPosition(game_->window)));
    auto index = map2GridIndex(pos);
    auto layoutChar = layout_[index.y].at(index.x);

    if (layoutChar == 'K')
        return true;

    return false;
}

bool LevelEditorState::isGateBlock()
{
    auto pos = map2GridPosition(game_->window.mapPixelToCoords(sf::Mouse::getPosition(game_->window)));
    auto index = map2GridIndex(pos);
    auto layoutChar = layout_[index.y].at(index.x);

    if (layoutChar == 'G')
        return true;

    return false;
}

void LevelEditorState::selectKey()
{
    game_->assetManager.playSound("key");
    isKeySelected_ = true;
    currentSelection_ = BuildSelection::NOTHING;
    applyRadioStyle();

    auto pos = map2GridPosition(game_->window.mapPixelToCoords(sf::Mouse::getPosition(game_->window)));
    selectedKeyPos_ = pos;
    selectedKeyIndex_ = map2GridIndex(pos);
}

void LevelEditorState::addGate()
{
    game_->assetManager.playSound("gate link");
    auto pos = map2GridPosition(game_->window.mapPixelToCoords(sf::Mouse::getPosition(game_->window)));

    keyMapPos_[selectedKeyPos_].push_back(pos);
    keyMapIndices_[selectedKeyIndex_].push_back(map2GridIndex(pos));
}

void LevelEditorState::rotateSelectedSprite()
{
    if (currentSelection_ == BuildSelection::ERASER)
        return;

    auto angle = (int)buildButtons_[currentSelection_].getRotation();
    angle = (angle + 90) % 360;
    buildButtons_[currentSelection_].setRotation(angle);
}

/*----- Updating state elements -----*/

void LevelEditorState::updateButtons()
{
    for(auto& [selection, button] : bottomButtons_)
        button.update(game_->window);

    for (auto& [selection, button] : buildButtons_)
        button.update(game_->window);
}

void LevelEditorState::updateGrid()
{
    updateCharacters();

    if (currentSelection_ == BuildSelection::NOTHING)
        return;

    auto mousePos = map2GridPosition(game_->window.mapPixelToCoords(sf::Mouse::getPosition(game_->window)));

    if (isMousePressed() && gridContainsMouse())
    {
        if (currentSelection_ == BuildSelection::ERASER)
            removeGridSprite(mousePos);
        else
            addGridSprite(mousePos);
    }
}

bool LevelEditorState::isMousePressed()
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool LevelEditorState::gridContainsMouse()
{
    return gridBounds_.contains(game_->window.mapPixelToCoords(sf::Mouse::getPosition(game_->window)));
}

void LevelEditorState::removeGridSprite(sf::Vector2f position)
{

    auto index = map2GridIndex(position);

    if (gridSprites_.find({position.x,position.y}) != gridSprites_.end())

    {
        gridSprites_.erase({position.x,position.y});
        layout_[index.y].at(index.x) = 'E';
        rotationMap_[index.y].at(index.x) = '0';
        updateKeyMap(position, index);
    }
}

void LevelEditorState::addGridSprite(sf::Vector2f position)
{
    gridSprites_[{position.x,position.y}] = createGridSprite(position);

    auto index = map2GridIndex(position);
    layout_[index.y].at(index.x) = getLayoutChar();
    rotationMap_[index.y].at(index.x) = getAngleChar();
    updateKeyMap(position, index);
}

void LevelEditorState::updateKeyMap(sf::Vector2f position, sf::Vector2i index)
{
    // Erase keys and their corresponding doors
    keyMapPos_.erase(position);
    keyMapIndices_.erase(index);

    // Erase specific door from every key
    auto deletedPos = vector<sf::Vector2f>{};
    auto deletedIdx = vector<sf::Vector2i>{};

    for (auto& [keyPos, gatePos] : keyMapPos_)
    {
        gatePos.erase(remove(gatePos.begin(), gatePos.end(), position), gatePos.end());

        if (gatePos.empty())
            deletedPos.push_back(keyPos);
    }

    for (auto& [keyIndex, gateIndices] : keyMapIndices_)
    {
        gateIndices.erase(remove(gateIndices.begin(), gateIndices.end(), index), gateIndices.end());

        if (gateIndices.empty())
            deletedIdx.push_back(keyIndex);
    }

    // Erase keys with no doors
    for (auto pos : deletedPos)
        keyMapPos_.erase(pos);

    for (auto pos : deletedIdx)
        keyMapIndices_.erase(pos);
}

sf::Vector2f LevelEditorState::map2GridPosition(sf::Vector2f position)
{
    auto yPos = GRID_POSITION.y + floor((position.y - GRID_POSITION.y)/GRID_SPACING) * GRID_SPACING + GRID_SPACING/2.f;
    auto xPos = GRID_POSITION.x + floor((position.x - GRID_POSITION.x)/GRID_SPACING) * GRID_SPACING + GRID_SPACING/2.f;
    
    return sf::Vector2f{xPos,yPos};
}

sf::Vector2i LevelEditorState::map2GridIndex(sf::Vector2f position)
{
    auto yIndex = (int)((position.y - GRID_POSITION.y)/GRID_SPACING);
    auto xIndex = (int)((position.x - GRID_POSITION.x)/GRID_SPACING);

    return sf::Vector2i{xIndex,yIndex};
}

sf::Sprite LevelEditorState::createGridSprite(sf::Vector2f position)
{
    sf::Sprite sprite;

    switch (currentSelection_)
    {
        case BuildSelection::WALL:
            sprite.setTexture(*game_->assetManager.getTexture("wall"));
            break;
        case BuildSelection::CORNER:
            sprite.setTexture(*game_->assetManager.getTexture("corner"));
            break;
        case BuildSelection::GATE:
            sprite.setTexture(*game_->assetManager.getTexture("gate"));
            break;
        case BuildSelection::KEY:
            sprite.setTexture(*game_->assetManager.getTexture("key"));
            break;
        case BuildSelection::FRUIT:
            sprite.setTexture(*game_->assetManager.getTexture("fruit"));
            break;
        case BuildSelection::POWER_PELLET:
            sprite.setTexture(*game_->assetManager.getTexture("power pellet"));
            break;
        case BuildSelection::SUPER_PELLET:
            sprite.setTexture(*game_->assetManager.getTexture("super pellet"));
            break;

        default:
            break;
    }

    sprite.setOrigin(sprite.getGlobalBounds().width/2.f, sprite.getGlobalBounds().height/2.f);
    sprite.setScale(15.f/17.f, 15.f/17.f);
    sprite.setRotation(buildButtons_[currentSelection_].getRotation());
    sprite.setPosition(position);
    return sprite;
}

char LevelEditorState::getLayoutChar()
{
    switch (currentSelection_)
    {
        case BuildSelection::WALL:
            return 'W';
        case BuildSelection::CORNER:
            return 'C';
        case BuildSelection::GATE:
            return 'G';
        case BuildSelection::KEY:
            return 'K';
        case BuildSelection::FRUIT:
            return 'F';
        case BuildSelection::POWER_PELLET:
            return 'P';
        case BuildSelection::SUPER_PELLET:
            return 'S';

        default:
            return 'E';
    }
}

char LevelEditorState::getAngleChar()
{
    switch ((int)buildButtons_[currentSelection_].getRotation())
    {
        case 0:
            return '0';
        case 90:
            return '1';
        case 180:
            return '2';
        case 270:
            return '3';

        default:
            return '0';
    }
}

void LevelEditorState::updateCharacters()
{
    vector<BuildSelection> characters
    {
        BuildSelection::PLAYER,
        BuildSelection::BLINKY,
        BuildSelection::PINKY,
        BuildSelection::INKY,
        BuildSelection::CLYDE,
    };

    for (auto i = 0; i < characters.size(); i++)
    {
        if (currentSelection_ != characters[i])
        {
            removeGridSprite(buildButtons_[characters[i]].getPosition());
        }
        else if (gridContainsMouse())
        {
            auto mousePos = game_->window.mapPixelToCoords(sf::Mouse::getPosition(game_->window));
            buildButtons_[characters[i]].setPosition(map2GridPosition(mousePos));
        }
    }
}

/*----- Rendering state elements -----*/

void LevelEditorState::drawButtons()
{
    for (auto& [selection, button] : bottomButtons_)
        game_->window.draw(button);

    for (auto& [selection, button] : buildButtons_)
        game_->window.draw(button);
}

void LevelEditorState::drawGrid()
{
    game_->window.draw(&gridLines_[0], gridLines_.size(), sf::Lines);
    drawGridNumbers();
    drawHighlightSquare();
    drawGridSprites();
    drawLinkLines();
}

void LevelEditorState::drawGridNumbers()
{
    for (auto num : gridNumbers_)
        game_->window.draw(num);
}

void LevelEditorState::drawHighlightSquare()
{
    auto mousePos = map2GridPosition(game_->window.mapPixelToCoords(sf::Mouse::getPosition(game_->window)));

    if (gridContainsMouse())
    {
        highlightSquare_.setPosition(mousePos);
        game_->window.draw(highlightSquare_);
    }
}

void LevelEditorState::drawGridSprites()
{
    vector<sf::Sprite> walls;
    sf::Vector2i index;

    for (auto const& [pos, sprite] : gridSprites_)
    {
        index = map2GridIndex(sf::Vector2f{pos.first,pos.second});

        if (layout_[index.y].at(index.x) == 'W' || layout_[index.y].at(index.x) == 'C')
            walls.push_back(sprite);
        else
            game_->window.draw(sprite);
    }

    // Draw walls last
    for (auto& wall : walls)
        game_->window.draw(wall);
}

void LevelEditorState::drawLinkLines()
{
    drawExistingLinks();

    if (gridContainsMouse())
        drawDanglingLink();
}

void LevelEditorState::drawDanglingLink()
{
    if (!isKeySelected_)
        return;

    auto mousePos = game_->window.mapPixelToCoords(sf::Mouse::getPosition(game_->window));

    auto length = sqrtf(pow(selectedKeyPos_.x - mousePos.x,2) + pow(selectedKeyPos_.y - mousePos.y,2));
    auto radians = atan2(selectedKeyPos_.y - mousePos.y, selectedKeyPos_.x - mousePos.x);
    auto angle = radians*180/PI + 180;

    linkLine_.setPosition(selectedKeyPos_);
    linkLine_.setSize(sf::Vector2f{length, LINK_LINE_THICKNESS});
    linkLine_.setRotation(angle);
    game_->window.draw(linkLine_);
}

void LevelEditorState::drawExistingLinks()
{
    auto length = 0.f;
    auto radians = 0.f;
    auto angle = 0.f;

    for (const auto& [keyPos, gatePos] : keyMapPos_)
    {
        for (const auto& pos : gatePos)
        {
            length = sqrtf(pow(keyPos.x - pos.x,2) + pow(keyPos.y - pos.y,2));
            radians = atan2(keyPos.y - pos.y, keyPos.x - pos.x);
            angle = radians*180/PI + 180;

            linkLine_.setPosition(keyPos);
            linkLine_.setSize(sf::Vector2f{length, LINK_LINE_THICKNESS});
            linkLine_.setRotation(angle);
            game_->window.draw(linkLine_);
        }
    }
}
