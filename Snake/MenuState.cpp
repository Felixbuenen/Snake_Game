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
    t_inform.setString("Press Space to start a new game!");
    t_inform.setStyle(sf::Text::Bold);
    t_inform.setCharacterSize(60);
    t_inform.setFont(font);
    t_inform.setFillColor(sf::Color::White);
    sf::Vector2f textBoundsInform(t_inform.getLocalBounds().left + t_inform.getLocalBounds().width,
                            t_inform.getLocalBounds().top  + t_inform.getLocalBounds().height);
    t_inform.setOrigin(textBoundsInform.x / 2.f, textBoundsInform.y / 2.f);
    t_inform.setPosition(sf::Vector2f(1500.f/2.f, 500.f)); // FIX USE OF CONSTANT!
}

void MenuState::CleanUp()
{
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
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
    {
        // ...switch to game.
        //game->ChangeState(PlayingState::Instance());
        game->ChangeState(new PlayingState());
    }
}

void MenuState::Update(Game* game)
{
    
}

void MenuState::Draw(Game* game)
{
    game->GetWindow()->draw(t_snake);
    game->GetWindow()->draw(t_inform);
}