//
//  ResourceManager.hpp
//  Snake
//
//  Created by Apple on 10-04-18.
//  Copyright © 2018 FelixBuenen. All rights reserved.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <SFML/Graphics.hpp>

class ResourceManager
{
public:
    static ResourceManager* GetInstance() { return &resourceManager; }
    
    void SetupText(sf::Text&, const std::string&, const sf::Text::Style&, int charSize, int x, int y, const sf::Color&);
    sf::Font* GetFont() { return &sans_font; }
    
private:
    static ResourceManager resourceManager;
    sf::Font sans_font;
    
protected:
    ResourceManager();
};

#endif /* ResourceManager_hpp */
