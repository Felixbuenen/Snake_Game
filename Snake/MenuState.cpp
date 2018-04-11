//
//  MenuState.cpp
//  Snake
//
//  Created by Apple on 02-04-18.
//  Copyright © 2018 FelixBuenen. All rights reserved.
//

#include "MenuState.hpp"

void MenuState::Init()
{
    // load font
    font.loadFromFile(resourcePath() + "sansation.ttf");
    
    // setup snake title text
    int x = 750;
    int y = 150;
    ResourceManager::GetInstance()->SetupText(t_snake, "S N A K E", sf::Text::Bold,
                                              100, x, y, sf::Color::White);
    
    // setup information text
    x = 750;
    y = 500;
    ResourceManager::GetInstance()->SetupText(t_inform, "Select level and press Space to start a new game!", sf::Text::Bold,
                                              60, x, y, sf::Color::White);
    
    // fill level vector
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
        if (event.key.code == sf::Keyboard::Space)
        {
            int speed;
            
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
        
        // switch menu selection
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
    // determine new current level
    int newLevel = (int)currentLevel + dir;
    newLevel = newLevel < 0 ? 0 : newLevel;
    newLevel = newLevel > 2 ? 2 : newLevel;
    
    // scale old selected text down
    levels[(int)currentLevel]->setStyle(sf::Text::Regular);
    ResourceManager::GetInstance()->ScaleText(*levels[(int)currentLevel], 30);
    
    // scale new selected text up
    currentLevel = (Levels)newLevel;
    levels[(int)currentLevel]->setStyle(sf::Text::Underlined | sf::Text::Bold);
    ResourceManager::GetInstance()->ScaleText(*levels[(int)currentLevel], 50);
}












