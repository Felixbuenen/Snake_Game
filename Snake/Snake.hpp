//
//  Snake.hpp
//  Snake
//
//  Created by Apple on 04-04-18.
//  Copyright © 2018 FelixBuenen. All rights reserved.
//

#ifndef Snake_hpp
#define Snake_hpp

#include <list>
#include <SFML/Graphics.hpp>

struct SnakePiece
{
    int x;
    int y;
};

class Snake
{
public:
    Snake(){};
    ~Snake();
    
    void Init(int n, int size, int x = 0, int y = 0);
    void Move();
    void AddPiece();
    
    int vx = -1;
    int vy = 0;
    int prevVx = vx;
    int prevVy = vy;
    int headX;
    int headY;
    int speed; // steps per second
    
    std::unique_ptr<sf::RectangleShape> pieceShape { new sf::RectangleShape() };
    
    std::list<SnakePiece>* GetSnake()
    {
        return &m_snake;
    }
    
private:
    std::list<SnakePiece> m_snake;
    
};

#endif /* Snake_hpp */
