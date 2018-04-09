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
    t_snake.setString("S N A K E");
    t_snake.setStyle(sf::Text::Bold);
    t_snake.setCharacterSize(100);
    t_snake.setFont(font);
    t_snake.setFillColor(sf::Color::White);
    sf::Vector2f textBounds(t_snake.getLocalBounds().left + t_snake.getLocalBounds().width,
                            t_snake.getLocalBounds().top  + t_snake.getLocalBounds().height);
    t_snake.setOrigin(textBounds.x / 2.f, textBounds.y / 2.f);
    t_snake.setPosition(sf::Vector2f(1500.f/2.f, 150.f)); // FIX USE OF CONSTANT!
    
    // setup information text
    t_inform.setString("Select level and press Space to start a new game!");
    t_inform.setStyle(sf::Text::Bold);
    t_inform.setCharacterSize(60);
    t_inform.setFont(font);
    t_inform.setFillColor(sf::Color::White);
    textBounds.x = t_inform.getLocalBounds().left + t_inform.getLocalBounds().width;
    textBounds.y = t_inform.getLocalBounds().top  + t_inform.getLocalBounds().height;
    t_inform.setOrigin(textBounds.x / 2.f, textBounds.y / 2.f);
    t_inform.setPosition(sf::Vector2f(1500.f/2.f, 500.f)); // FIX USE OF CONSTANT!
    
    // fill level vector
    //std::fill(levels.begin(), levels.end(), std::unique_ptr<sf::Text>(new sf::Text()));
    levels.push_back(std::unique_ptr<sf::Text>(new sf::Text()));
    levels.push_back(std::unique_ptr<sf::Text>(new sf::Text()));
    levels.push_back(std::unique_ptr<sf::Text>(new sf::Text()));
    
    // setup level texts
    levels[(int)_EASY]->setString("EASY");
    levels[(int)_EASY]->setStyle(sf::Text::Regular);
    levels[(int)_EASY]->setCharacterSize(30);
    levels[(int)_EASY]->setFont(font);
    levels[(int)_EASY]->setFillColor(sf::Color::White);
    textBounds.x = levels[(int)_EASY]->getLocalBounds().left + levels[(int)_EASY]->getLocalBounds().width;
    textBounds.y = levels[(int)_EASY]->getLocalBounds().top  + levels[(int)_EASY]->getLocalBounds().height;
    levels[(int)_EASY]->setOrigin(textBounds.x / 2.f, textBounds.y / 2.f);
    levels[(int)_EASY]->setPosition(sf::Vector2f(1500.f/4.f, 850.f)); // FIX USE OF CONSTANT!
    
    levels[(int)_MEDIUM]->setString("MEDIUM");
    levels[(int)_MEDIUM]->setStyle(sf::Text::Bold | sf::Text::Underlined);
    levels[(int)_MEDIUM]->setCharacterSize(50);
    levels[(int)_MEDIUM]->setFont(font);
    levels[(int)_MEDIUM]->setFillColor(sf::Color::White);
    textBounds.x = levels[(int)_MEDIUM]->getLocalBounds().left + levels[(int)_MEDIUM]->getLocalBounds().width;
    textBounds.y = levels[(int)_MEDIUM]->getLocalBounds().top  + levels[(int)_MEDIUM]->getLocalBounds().height;
    levels[(int)_MEDIUM]->setOrigin(textBounds.x / 2.f, textBounds.y / 2.f);
    levels[(int)_MEDIUM]->setPosition(sf::Vector2f(1500.f/2.f, 850.f)); // FIX USE OF CONSTANT!
    
    levels[(int)_HARD]->setString("HARD");
    levels[(int)_HARD]->setStyle(sf::Text::Regular);
    levels[(int)_HARD]->setCharacterSize(30);
    levels[(int)_HARD]->setFont(font);
    levels[(int)_HARD]->setFillColor(sf::Color::White);
    textBounds.x = levels[(int)_HARD]->getLocalBounds().left + levels[(int)_HARD]->getLocalBounds().width;
    textBounds.y = levels[(int)_HARD]->getLocalBounds().top  + levels[(int)_HARD]->getLocalBounds().height;
    levels[(int)_HARD]->setOrigin(textBounds.x / 2.f, textBounds.y / 2.f);
    levels[(int)_HARD]->setPosition(sf::Vector2f(1500.f/2.f + 1500.f/4.f, 850.f)); // FIX USE OF CONSTANT!

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












