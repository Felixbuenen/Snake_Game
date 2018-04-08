//
//  GameState.h
//  Snake
//
//  Created by Apple on 02-04-18.
//  Copyright © 2018 FelixBuenen. All rights reserved.
//

#ifndef GameState_h
#define GameState_h

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

#include "Game.hpp"

class GameState
{
public:
    virtual void Init() = 0;
    virtual void CleanUp() = 0;
    
    // used when state needs to proceed at other time
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    
    virtual void HandleInput(Game* game, sf::Event&) = 0;
    virtual void Update(Game* game) = 0;
    virtual void Draw(Game* game) = 0;

//protected:
    GameState(){}
};

#endif /* GameState_h */
