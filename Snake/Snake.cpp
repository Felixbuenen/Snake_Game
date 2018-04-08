//
//  Snake.cpp
//  Snake
//
//  Created by Apple on 04-04-18.
//  Copyright © 2018 FelixBuenen. All rights reserved.
//

#include "Snake.hpp"
#include <thread>

Snake::~Snake()
{
    m_snake.clear();
}

void Snake::Init(int n, int size, int x, int y)
{
    headX = x;
    headY = y;
    
    // fill list
    for(int i = 0; i < 7; i++)
    {
        SnakePiece s = {i + x, y};
        m_snake.push_back(s);
    }
    
    // setup drawable snake piece
    pieceShape->setSize(sf::Vector2f((float)size, (float)size));
    pieceShape->setFillColor(sf::Color::Black);
}

void Snake::Move()
{
    prevVx = vx;
    prevVy = vy;
    headX = m_snake.front().x + vx;
    headY = m_snake.front().y + vy;
    
    m_snake.pop_back();
    SnakePiece s = {headX, headY};
    m_snake.push_front(s);
}

void Snake::AddPiece()
{
    SnakePiece s = *m_snake.end();
    m_snake.push_back(s);
}
