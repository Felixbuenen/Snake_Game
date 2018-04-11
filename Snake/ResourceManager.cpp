//
//  ResourceManager.cpp
//  Snake
//
//  Created by Apple on 10-04-18.
//  Copyright © 2018 FelixBuenen. All rights reserved.
//

#include "ResourceManager.hpp"
#include "ResourcePath.hpp"

ResourceManager ResourceManager::resourceManager;

ResourceManager::ResourceManager()
{
    // load font
    sans_font.loadFromFile(resourcePath() + "sansation.ttf");
}

// automatically sets up all properties of text object
void ResourceManager::SetupText(sf::Text& text, const std::string& content,
                           const sf::Text::Style& style, int charSize, int x,
                           int y, const sf::Color& col)
{
    text.setString(content);
    text.setStyle(style);
    text.setCharacterSize(charSize);
    text.setFont(sans_font);
    text.setFillColor(col);
    
    sf::Vector2f textBounds(text.getLocalBounds().left + text.getLocalBounds().width,
                            text.getLocalBounds().top  + text.getLocalBounds().height);
    
    text.setOrigin(textBounds.x / 2.f, textBounds.y / 2.f);
    text.setPosition(sf::Vector2f(x, y));
}

// automatically scales text centered
void ResourceManager::ScaleText(sf::Text& text, int charSize)
{
    text.setCharacterSize(charSize);
    
    sf::Vector2f textBounds(text.getLocalBounds().left + text.getLocalBounds().width,
                            text.getLocalBounds().top  + text.getLocalBounds().height);
    
    text.setOrigin(textBounds.x / 2, textBounds.y / 2);
    text.setPosition(text.getPosition());
}