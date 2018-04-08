//
//  MenuState.hpp
//  Snake
//
//  Created by Apple on 02-04-18.
//  Copyright © 2018 FelixBuenen. All rights reserved.
//

#ifndef MenuState_hpp
#define MenuState_hpp

#include "GameState.h"
#include "PlayingState.hpp"

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
    
    //static MenuState* Instance()
    //{
    //    return &m_MenuState;
    //}
    
//protected:
    MenuState(){}
    
private:
    //static MenuState m_MenuState;
    
    sf::Font font;
    sf::Text t_snake;
    sf::Text t_inform;

};

#endif /* MenuState_hpp */
