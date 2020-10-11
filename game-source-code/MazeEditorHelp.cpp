#include "MazeEditorHelp.h"
#include "LevelEditorState.h"

#include "Configuration.h"

#include <string>

MazeEditorHelp::MazeEditorHelp(gamePtr game): game_{game}
{
    // error checking
}

void MazeEditorHelp::initialise()
{
    loadTitle(game_->assetManager);
    loadText(game_->assetManager);
    loadButtons(game_->assetManager);
    loadPageProgress(game_->assetManager);
}

void MazeEditorHelp::processInput()
{
    sf::Event event;

    while (game_->window.pollEvent(event))
    {
        if (game_->inputManager.isExitRequest(event))
            game_->window.close();
        
        if (event.type == sf::Event::Resized)
            game_->view = game_->inputManager.getLetterboxView(game_->view, event.size.width, event.size.height);

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (exitButton_.isHover(game_->window))
            {
                game_->assetManager.playSound("button click");
                game_->stateMachine.addState(make_unique<LevelEditorState>(game_));
            }
            
            if (rightButton_.isHover(game_->window))
                nextPage();

            if (leftButton_.isHover(game_->window))
                previousPage();
        }
    }
}

void MazeEditorHelp::update(float dt)
{
    exitButton_.update(game_->window);
    leftButton_.update(game_->window);
    rightButton_.update(game_->window);
}

void MazeEditorHelp::draw(float dt)
{
    game_->window.clear();
    game_->window.setView(game_->view);

    game_->window.draw(bg);
    game_->window.draw(title_);

    for (const auto& line : pages_[pageNum_])
            game_->window.draw(line);
    
    game_->window.draw(pageDisplay_);

    game_->window.draw(exitButton_);
    game_->window.draw(leftButton_);
    game_->window.draw(rightButton_);

    game_->window.display();
}

/*------------- Private helper functions -------------*/

void MazeEditorHelp::loadTitle(AssetManager& assetManager)
{
    title_.setFont(*assetManager.getFont("pressStart 8-bit"));

    title_.setString("MAZE EDITOR GUIDE");
    title_.setOrigin(title_.getGlobalBounds().width/2, title_.getGlobalBounds().height/2);
    title_.setPosition(GAME_WIDTH/2, 50);
    title_.setFillColor(sf::Color{21, 244, 238});
    
    // background
    
    bg.setTexture(*assetManager.getTexture("aux background"));
}

void MazeEditorHelp::loadText(AssetManager& assetManager)
{
    sf::Text line;
    vector<sf::Text> paragraph;

    line.setFont(*assetManager.getFont("fine 8-bit"));
    
    line.setString("Welcome to the Maze Editor! Here, you can create your own");
    paragraph.push_back(line);
    
    line.setString("custom mazes to play in. This is how it works:\n");
    paragraph.push_back(line);
    
    line.setString("- Select one of the 7 tile types on the right hand side of");
    paragraph.push_back(line);
    
    line.setString("  the screen using the left mouse button\n");
    paragraph.push_back(line);
    
    line.setString("- To insert the selected tile type, click on the desired");
    paragraph.push_back(line);

    line.setString("  position in the grid. You can hold down and drag to insert\n");
    paragraph.push_back(line);

    line.setString("  multiple tiles quickly\n");
    paragraph.push_back(line);

    line.setString("- To remove tiles, select the eraser button and click on");
    paragraph.push_back(line);

    line.setString("  the tile you wish to remove. Hold down and drag to erase\n");
    paragraph.push_back(line);

    line.setString("  multiple tiles quickly\n");
    paragraph.push_back(line);

    line.setString("- Press 'R' to rotate the tile that is currently selected\n");
    paragraph.push_back(line);

    line.setString("- To link a key to a specific gate, RIGHT-CLICK on the key\n");
    paragraph.push_back(line);
    
    line.setString("  you wish to link within the grid. A line will be drawn between\n");
    paragraph.push_back(line);
    
    line.setString("  this key and your mouse, indicating that you are in\n");
    paragraph.push_back(line);
    
    line.setString("  \"link-mode\"\n");
    paragraph.push_back(line);
    
    line.setString("- While in link-mode, RIGHT-CLICK on a gate within the grid \n");
    paragraph.push_back(line);
    
    line.setString("  to add it to the list of gates that the selected key opens\n");
    paragraph.push_back(line);

    for (int i = 0; i< paragraph.size(); i++)
    {
        paragraph[i].setScale(0.7,0.7);
        paragraph[i].setOrigin(0.f, paragraph[i].getGlobalBounds().height/2);
        paragraph[i].setPosition(25 ,125.f + i*40.f);
    }
    
    pages_.push_back(paragraph);
    
    paragraph.clear();
    
    line.setString("- Repeat the above step to link multiple gates to the\n");
    paragraph.push_back(line);
    
    line.setString("  same key\n");
    paragraph.push_back(line);

    line.setString("- To exit link-mode, LEFT-CLICK anywhere in the screen\n");
    paragraph.push_back(line);
    
    line.setString("- To set the starting position of a particular character,\n");
    paragraph.push_back(line);
    
    line.setString("  click on its head and place it in the desired position\n");
    paragraph.push_back(line);
    
    line.setString("  within the grid\n");
    paragraph.push_back(line);
    
    line.setString("- To name your maze, click on \"Enter Maze Name\" and enter\n");
    paragraph.push_back(line);
    
    line.setString("  a maximum of 10 characters. Press ENTER when you are\n");
    paragraph.push_back(line);
    
    line.setString("  done. Note that this is required in order to save the maze\n");
    paragraph.push_back(line);
    
    line.setString("- In addition, your maze must have at least one fruit, \n");
    paragraph.push_back(line);
    
    line.setString("  power pellet or super pellet in order to save\n");
    paragraph.push_back(line);

    line.setString("- To reset everything in the maze, click the CLEAR button\n");
    paragraph.push_back(line);
    
    line.setString("- Once you are done, click SAVE. Your maze should now be\n");
    paragraph.push_back(line);
    
    line.setString("  available as a choice in the Maze Select screen after\n");
    paragraph.push_back(line);
    
    line.setString("  pressing PLAY in the Main Menu. You can navigate to it\n");
    paragraph.push_back(line);
    
    line.setString("  using the left and right arrow buttons\n");
    paragraph.push_back(line);
    
    line.setString("- To go back to the Main Menu without saving, click the\n");
    paragraph.push_back(line);
    
    line.setString("  EXIT button\n");
    paragraph.push_back(line);
    
    for (int i = 0; i< paragraph.size(); i++)
    {
        paragraph[i].setScale(0.7,0.7);
        paragraph[i].setOrigin(0.f, paragraph[i].getGlobalBounds().height/2);
        paragraph[i].setPosition(25 ,125.f + i*40.f);
    }
    
    pages_.push_back(paragraph);
}

void MazeEditorHelp::loadButtons(AssetManager& assetManager)
{
    auto font = assetManager.getFont("coarse 8-bit");
    auto texture = assetManager.getTexture("menu button");
    
    exitButton_ = Button{assetManager.getTexture("exit button")};
    exitButton_.setPosition(sf::Vector2f{800,32});  // hard-coded for now
    exitButton_.setHoverColour(sf::Color::Red);
    
    leftButton_ = Button{assetManager.getTexture("left triangle")};
    leftButton_.setPosition(GAME_WIDTH/2 - 90.f, 850);
    leftButton_.setSpriteScale(0.4f,0.4f);

    rightButton_ = Button{assetManager.getTexture("right triangle")};
    rightButton_.setPosition(GAME_WIDTH/2 + 95.f, 850);
    rightButton_.setSpriteScale(0.4f,0.4f);
}

void MazeEditorHelp::loadPageProgress(AssetManager& assetManager)
{
    pageDisplay_.setFont(*assetManager.getFont("pressStart 8-bit"));
    pageDisplay_.setString(to_string(pageNum_ + 1) + "/" + to_string(pages_.size()));
    pageDisplay_.setOrigin(pageDisplay_.getGlobalBounds().width/2, pageDisplay_.getGlobalBounds().height/2);
    pageDisplay_.setScale(0.8, 0.8);
    pageDisplay_.setPosition(GAME_WIDTH/2, 850);
}

void MazeEditorHelp::nextPage()
{
    if (pageNum_ == pages_.size() - 1)
    {
        game_->assetManager.playSound("error");
    }
    else
    {
        game_->assetManager.playSound("button click");
        
        pageNum_++;
        pageDisplay_.setString(to_string(pageNum_ + 1) + "/" + to_string(pages_.size()));
        pageDisplay_.setOrigin(pageDisplay_.getGlobalBounds().width/2, pageDisplay_.getGlobalBounds().height/2);
    }
}

void MazeEditorHelp::previousPage()
{
    if (pageNum_ == 0)
    {
        game_->assetManager.playSound("error");
    }
    else
    {
        game_->assetManager.playSound("button click");
        
        pageNum_--;
        pageDisplay_.setString(to_string(pageNum_ + 1) + "/" + to_string(pages_.size()));
        pageDisplay_.setOrigin(pageDisplay_.getGlobalBounds().width/2, pageDisplay_.getGlobalBounds().height/2);
    }
}
