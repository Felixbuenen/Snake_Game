//
//  Game.hpp
//  Snake
//
//  Created by Apple on 02-04-18.
//  Copyright © 2018 FelixBuenen. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

class GameState; // inform compiler existence of GameState class.

class Game
{
public:
    Game(int, int, const char*);
    ~Game();
    sf::Vector2u windowSize;
    void RunGame();
    
    void ChangeState(GameState*);
    void PushState(GameState*);
    void PopState();
    
    sf::RenderWindow* GetWindow()
    {
        return &window;
    };

private:
    // stack of states
    std::vector<GameState*> states;
    sf::RenderWindow window;

    void HandleInput();
    void Update();
    void Draw();
};

#endif /* Game_hpp */
