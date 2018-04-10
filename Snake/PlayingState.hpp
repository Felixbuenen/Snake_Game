//
//  PlayingState.hpp
//  Snake
//
//  Created by Apple on 04-04-18.
//  Copyright © 2018 FelixBuenen. All rights reserved.
//

#ifndef PlayingState_hpp
#define PlayingState_hpp

#include "GameState.h"
#include "MenuState.hpp"
#include "Snake.hpp"
#include <iostream>
#include <stdlib.h>

struct Food
{
public:
    int x;
    int y;
    std::unique_ptr<sf::CircleShape> foodshape { new sf::CircleShape };
};

class PlayingState : public GameState
{
public:
    void Init();
    void CleanUp();
    
    // used when state needs to proceed at other time
    void Pause();
    void Resume();
    
    void HandleInput(Game*, sf::Event&);
    void Update     (Game*);
    void Draw       (Game*);
    
    //static PlayingState* Instance()
    //{
    //    return &m_PlayingState;
    //}
    
//protected:
    PlayingState(int speed);
    
private:
    //static PlayingState m_PlayingState;
    
    int cellSize;
    int gridWidth, gridHeight;
    int num_food;
    bool paused = false;
    sf::RectangleShape leftWall, rightWall, upperWall, lowerWall;
    Food foodPiece;
    sf::Vector2f gridPos;
    sf::Clock snakeClock;
    sf::Clock timer;
    sf::Text timer_text;
    sf::Text food_text;
    sf::Text title_text;
    Snake snake;
    
    void DrawWalls(Game*);
    void DrawSnake(Game*);
    void DrawGUI(Game*);
    void UpdateTime();
    bool CheckCollision();
    void SetFoodPosition();
};

#endif /* PlayingState_hpp */
