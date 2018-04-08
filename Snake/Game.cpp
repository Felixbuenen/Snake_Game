//
//  Game.cpp
//  Snake
//
//  Created by Apple on 02-04-18.
//  Copyright © 2018 FelixBuenen. All rights reserved.
//

#include "Game.hpp"
#include "MenuState.hpp"

Game::Game(int w, int h, const char* title)
{
    window.create(sf::VideoMode(w, h), title);
    window.setTitle(title);
    
    // initialize menu state
    ChangeState(new MenuState());
}

Game::~Game()
{
    states.clear();
}

void Game::RunGame()
{
    // Start the game loop
    while (window.isOpen())
    {
        HandleInput();
        Draw();
        Update();
    }
}

// used to replace current state
void Game::ChangeState(GameState* state)
{
    // cleanup and remove current state
    if(!states.empty())
    {
        states.back()->CleanUp();
        states.pop_back();
    }
    
    // add new current state and initialize it
    states.push_back(state);
    states.back()->Init();
}

// used to add a new current state, pausing the previous state
void Game::PushState(GameState* state)
{
    // pause current state
    if(!states.empty())
    {
        states.back()->Pause();
    }
    
    // add new current state and initialize it
    states.push_back(state);
    states.back()->Init();
}

void Game::PopState()
{
    // remove current state
    if(!states.empty())
    {
        states.back()->CleanUp();
        states.pop_back();
    }
    
    // resume previous state
    if(!states.empty())
    {
        states.back()->Resume();
    }
}

void Game::HandleInput()
{
    // Process events
    sf::Event event;
    while (window.pollEvent(event))
    {
        // Close window: exit
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        // Escape pressed: exit
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            window.close();
        }
        
        states.back()->HandleInput(this, event);
    }
}

void Game::Draw()
{
    // Clear screen
    window.clear(sf::Color(30, 110, 30));
    states.back()->Draw(this);
    window.display();
}

void Game::Update()
{
    states.back()->Update(this);
}
















