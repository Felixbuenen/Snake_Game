//
//  PlayingState.cpp
//  Snake
//
//  Created by Apple on 04-04-18.
//  Copyright © 2018 FelixBuenen. All rights reserved.
//

#include "PlayingState.hpp"

//PlayingState PlayingState::m_PlayingState;

PlayingState::PlayingState(int speed)
{
    snake.speed = speed;
}

void PlayingState::Init()
{
    cellSize   = 20;
    gridHeight = 25;
    gridWidth  = 25;
    
    num_food = 0;
    
    int centerX = (gridWidth*cellSize)/2;
    gridPos.x = 1500.f/2.f - centerX;
    gridPos.y = 400;
    
    // setup snake
    int startX = gridWidth/2;
    int startY = gridHeight/2;
    
    snake.Init(5, cellSize, startX, startY);
    
    // setup food
    foodPiece.foodshape->setFillColor(sf::Color::Red);
    SetFoodPosition();
    foodPiece.foodshape->setRadius(cellSize/2);
    
    snakeClock.restart();
    timer.restart();
    
    // FIX USE OF CONSTANTS
    // setup snake title text
    int x = 750;
    int y = 100;
    ResourceManager::GetInstance()->SetupText(title_text, "S N A K E", sf::Text::Bold, 75, x, y, sf::Color::White);
    
    // setup timer text
    x = gridPos.x;
    y = 250;
    ResourceManager::GetInstance()->SetupText(timer_text, "0:00", sf::Text::Bold, 75, x, y, sf::Color::Black);
    
    // setup food text
    x = gridPos.x + gridWidth*cellSize - food_text.getLocalBounds().width;
    y = 250;
    ResourceManager::GetInstance()->SetupText(food_text, "Food: 0", sf::Text::Bold, 75, x, y, sf::Color::Black);
}

void PlayingState::CleanUp()
{
}

// used when state needs to proceed at other time
void PlayingState::Pause()
{
    
}

void PlayingState::Resume()
{
    
}

void PlayingState::HandleInput(Game* game, sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::P)
        {
            paused = !paused;
        }
        
        // player moves up
        if(event.key.code == sf::Keyboard::Up && snake.prevVy != 1)
        {
            snake.vy = -1;
            snake.vx = 0;
            return;
        }
        
        // player moves down
        if(event.key.code == sf::Keyboard::Down && snake.prevVy != -1)
        {
            snake.vy = 1;
            snake.vx = 0;
            return;
        }
        
        // player moves left
        if(event.key.code == sf::Keyboard::Left && snake.prevVx != 1)
        {
            snake.vy = 0;
            snake.vx = -1;
            return;
        }
        
        // player moves right
        if(event.key.code == sf::Keyboard::Right && snake.prevVx != -1)
        {
            snake.vy = 0;
            snake.vx = 1;
            return;
        }
    }
}

void PlayingState::Update(Game* game)
{
    if (paused) return;
    
    UpdateTime();
    
    // only move snake -speed- times per second
    sf::Time currentTime = snakeClock.getElapsedTime();
    if (currentTime.asMilliseconds() > (1000 / snake.speed))
    {
        snakeClock.restart();
        
        if (CheckCollision())
            game->ChangeState(new MenuState);
        
        snake.Move();
    }
}

bool PlayingState::CheckCollision()
{
    int nextX = snake.headX + snake.vx;
    int nextY = snake.headY + snake.vy;
    
    // check snake collision
    std::list<SnakePiece>::iterator it;
    for (it = std::next(snake.GetSnake()->begin()); it != snake.GetSnake()->end(); ++it)
    {
        if ((nextX == it->x) & (nextY == it->y)) return true;
    }
    
    // check walls
    if (nextX == -1)         return true;
    if (nextX == gridWidth)  return true;
    if (nextY == -1)         return true;
    if (nextY == gridHeight) return true;
    
    // check food
    if (nextX == foodPiece.x & nextY == foodPiece.y)
    {
        // increase number of food
        num_food++;
        food_text.setString("Food: " + std::to_string(num_food));
        
        // add snake piece
        snake.AddPiece();
        
        // update snake position
        SetFoodPosition();
    }
    
    return false;
}

void PlayingState::SetFoodPosition()
{
    bool inSnake;
    int x, y;
    
    do
    {
        inSnake = false;
        x = rand() % gridWidth;
        y = rand() % gridHeight;
        
        std::list<SnakePiece>::iterator it;
        for (it = snake.GetSnake()->begin(); it != snake.GetSnake()->end(); ++it)
        {
            if ((x == it->x) & (y == it->y))
            {
                inSnake = true;
                break;
            }
        }
    }
    while (inSnake);
    
    foodPiece.x = x;
    foodPiece.y = y;
    foodPiece.foodshape->setPosition(gridPos.x + x * cellSize, gridPos.y + y * cellSize);
}

void PlayingState::Draw(Game* game)
{
    DrawWalls(game);
    DrawSnake(game);
    DrawGUI  (game);
    game->GetWindow()->draw(*foodPiece.foodshape);
}


void PlayingState::DrawWalls(Game* game)
{
    // setup left wall
    leftWall.setSize(sf::Vector2f(cellSize, (gridHeight+2)*cellSize));
    leftWall.setPosition(gridPos.x - cellSize, gridPos.y - cellSize);
    leftWall.setFillColor(sf::Color::Black);
    
    // setup right wall
    rightWall.setSize(sf::Vector2f(cellSize, (gridHeight+2)*cellSize));
    rightWall.setPosition(gridPos.x + gridWidth*cellSize, gridPos.y - cellSize);
    rightWall.setFillColor(sf::Color::Black);
    
    // setup upper wall
    upperWall.setSize(sf::Vector2f(gridWidth*cellSize,cellSize));
    upperWall.setPosition(gridPos.x, gridPos.y - cellSize);
    upperWall.setFillColor(sf::Color::Black);
    
    // setup lower wall
    lowerWall.setSize(sf::Vector2f(gridWidth*cellSize,cellSize));
    lowerWall.setPosition(gridPos.x, gridPos.y + gridHeight*cellSize);
    lowerWall.setFillColor(sf::Color::Black);
    
    // draw walls
    game->GetWindow()->draw(leftWall);
    game->GetWindow()->draw(rightWall);
    game->GetWindow()->draw(upperWall);
    game->GetWindow()->draw(lowerWall);
}

void PlayingState::DrawSnake(Game* game)
{    
    // draw snake
    std::list<SnakePiece>::iterator it;
    for (it = snake.GetSnake()->begin(); it != snake.GetSnake()->end(); ++it)
    {
        snake.pieceShape->setPosition(gridPos.x + it->x * cellSize , gridPos.y + it->y * cellSize);
        game->GetWindow()->draw(*snake.pieceShape);
    }
}

void PlayingState::DrawGUI(Game* game)
{
    game->GetWindow()->draw(title_text);
    game->GetWindow()->draw(timer_text);
    game->GetWindow()->draw(food_text);
}

void PlayingState::UpdateTime()
{
    sf::Time time = timer.getElapsedTime();
    
    int second = time.asSeconds();
    int rest = (time.asMilliseconds() - second*1000)/100;
    std::string s_second  = std::to_string(second);
    std::string s_rest    = std::to_string(rest);
    std::string time_text = s_second + ":" + s_rest;
    
    timer_text.setString("" + time_text);
}







