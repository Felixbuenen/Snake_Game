//
//  MenuState.hpp
//  Snake
//
//  Created by Apple on 02-04-18.
//  Copyright © 2018 FelixBuenen. All rights reserved.
//

#ifndef MenuState_hpp
#define MenuState_hpp

#define N_EASY   3
#define N_MEDIUM 10
#define N_HARD   20

#include "GameState.h"
#include "PlayingState.hpp"
#include <algorithm>

enum Levels {_EASY, _MEDIUM, _HARD};

class MenuState : public GameState
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
    
    MenuState(){}
    
private:
    void ChangeLevel(int dir);
    Levels currentLevel;
    
    sf::Font font;
    sf::Text t_snake;
    sf::Text t_inform;
    
    std::vector<std::unique_ptr<sf::Text>> levels;
};

#endif /* MenuState_hpp */
