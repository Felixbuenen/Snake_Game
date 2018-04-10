//
//  MenuState.cpp
//  Snake
//
//  Created by Apple on 02-04-18.
//  Copyright © 2018 FelixBuenen. All rights reserved.
//

#include "MenuState.hpp"

//MenuState MenuState::m_MenuState;

void MenuState::Init()
{
    // load font
    font.loadFromFile(resourcePath() + "sansation.ttf");
    
    // setup snake title text
    /*t_snake.setString("S N A K E");
    t_snake.setStyle(sf::Text::Bold);
    t_snake.setCharacterSize(100);
    t_snake.setFont(font);
    t_snake.setFillColor(sf::Color::White);
    sf::Vector2f textBounds(t_snake.getLocalBounds().left + t_snake.getLocalBounds().width,
                            t_snake.getLocalBounds().top  + t_snake.getLocalBounds().height);
    t_snake.setOrigin(textBounds.x / 2.f, textBounds.y / 2.f);
    t_snake.setPosition(sf::Vector2f(1500.f/2.f, 150.f)); // FIX USE OF CONSTANT!*/
    int x = 750;
    int y = 150;
    ResourceManager::GetInstance()->SetupText(t_snake, "S N A K E", sf::Text::Bold,
                                              100, x, y, sf::Color::White);
    
    // setup information text
    /*t_inform.setString("Select level and press Space to start a new game!");
    t_inform.setStyle(sf::Text::Bold);
    t_inform.setCharacterSize(60);
    t_inform.setFont(font);
    t_inform.setFillColor(sf::Color::White);
    textBounds.x = t_inform.getLocalBounds().left + t_inform.getLocalBounds().width;
    textBounds.y = t_inform.getLocalBounds().top  + t_inform.getLocalBounds().height;
    t_inform.setOrigin(textBounds.x / 2.f, textBounds.y / 2.f);
    t_inform.setPosition(sf::Vector2f(1500.f/2.f, 500.f)); // FIX USE OF CONSTANT!*/
    x = 750;
    y = 500;
    ResourceManager::GetInstance()->SetupText(t_inform, "Select level and press Space to start a new game!", sf::Text::Bold,
                                              60, x, y, sf::Color::White);
    
    // fill level vector
    //std::fill(levels.begin(), levels.end(), std::unique_ptr<sf::Text>(new sf::Text()));
    levels.push_back(std::unique_ptr<sf::Text>(new sf::Text()));
    levels.push_back(std::unique_ptr<sf::Text>(new sf::Text()));
    levels.push_back(std::unique_ptr<sf::Text>(new sf::Text()));
    
    // setup level texts
    x = 1500 / 4;
    y = 850;
    ResourceManager::GetInstance()->SetupText(*levels[(int)_EASY], "EASY", sf::Text::Regular,
                                              30, x, y, sf::Color::White);
    
    x = 1500 / 2;
    y = 850;
    ResourceManager::GetInstance()->SetupText(*levels[(int)_MEDIUM], "MEDIUM",
                                              (sf::Text::Style)(sf::Text::Regular | sf::Text::Underlined),
                                              50, x, y, sf::Color::White);
    
    x = 1500/2 + 1500/4;
    y = 850;
    ResourceManager::GetInstance()->SetupText(*levels[(int)_HARD], "HARD", sf::Text::Regular,
                                              30, x, y, sf::Color::White);

    currentLevel = Levels::_MEDIUM;
}

void MenuState::CleanUp()
{
    // delete levels vector
    levels.clear();
}

void MenuState::Pause()
{
}

void MenuState::Resume()
{
}

void MenuState::HandleInput(Game* game, sf::Event& event)
{
    // if user presses space...
    if(event.type == sf::Event::KeyPressed)
    {
        // ...switch to game.
        //game->ChangeState(PlayingState::Instance());
        if (event.key.code == sf::Keyboard::Space)
        {
            int speed = 34358;
            
            switch (currentLevel)
            {
                case Levels::_EASY:
                    speed = N_EASY;
                    break;
                case Levels::_MEDIUM:
                    speed = N_MEDIUM;
                    break;
                case Levels::_HARD:
                    speed = N_HARD;
                    break;
                default:
                    break;
            }
            
            game->ChangeState(new PlayingState(speed));
        }
        if (event.key.code == sf::Keyboard::Left ) ChangeLevel(-1);
        if (event.key.code == sf::Keyboard::Right) ChangeLevel(1);
    }
}

void MenuState::Update(Game* game)
{
    
}

void MenuState::Draw(Game* game)
{
    game->GetWindow()->draw(t_snake);
    game->GetWindow()->draw(t_inform);
    game->GetWindow()->draw(*levels[(int)_EASY]);
    game->GetWindow()->draw(*levels[(int)_MEDIUM]);
    game->GetWindow()->draw(*levels[(int)_HARD]);
}

void MenuState::ChangeLevel(int dir)
{
    int newLevel = (int)currentLevel + dir;
    newLevel = newLevel < 0 ? 0 : newLevel;
    newLevel = newLevel > 2 ? 2 : newLevel;
    
    // set old current level to smaller text
    levels[(int)currentLevel]->setStyle(sf::Text::Regular);
    levels[(int)currentLevel]->setCharacterSize(30);
    
    currentLevel = (Levels)newLevel;
    levels[(int)currentLevel]->setStyle(sf::Text::Underlined | sf::Text::Bold);
    levels[(int)currentLevel]->setCharacterSize(50);
}

// position text void












