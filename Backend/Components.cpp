//
// Created by conta on 02-02-2024.
//
# include "Components.h"

CSprite::CSprite(const std::string &FILE, Vector2D &SIZE): textureAddress(FILE), size(SIZE)
{
    texture.loadFromFile(textureAddress , sf::IntRect(0, 0, SIZE.x, SIZE.y));
    texture.setSmooth(true);
    texture.setRepeated(false);
    sprite.setTexture(texture);
    sprite.setOrigin(SIZE.x / 2, SIZE.y / 2);
    sprite.setScale(1, 1);
}

CSprite::CSprite(const std::string &FILE)
{
    texture.loadFromFile(textureAddress);
    texture.setSmooth(true);
    texture.setRepeated(false);
    sprite.setTexture(texture);
}