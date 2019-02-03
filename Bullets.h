//
// Created by george on 24.05.18.
//

#ifndef GAME_BULLETS_H
#define GAME_BULLETS_H


#include "ControlFunctions.h"

class Bullets : public Character {
protected:


    const float bullet_size = 40;
public:
    explicit Bullets(sf::Texture &texture, Engine *engine, sf::Vector2f start, sf::Vector2f dest, int spec);

    void logic() override;

    void draw() override;

    void move() override;

    void Orientation();

};

Bullets::Bullets(sf::Texture &texture, Engine *engine, sf::Vector2f start, sf::Vector2f distance, int spec) : Character(texture) {
    type = -spec;
    hp = -1;
    mass = 0;

    vMax = 40;
    coord = start;
    //v = distance;
    a.x = a.y = 0;
    collisionRad = 10;
    collisional = false;
    v.x = (distance.x / length(distance)) * vMax;
    v.y = (distance.y / length(distance)) * vMax;
    sprite_.setScale(bullet_size / width, bullet_size / height);
    Orientation();
    std::cout << "\n\n*****************bullet was created\n\n" << std::endl;
    std::cout <<"\n\n======== MOUSE SPEED ========  " << length(v) << std::endl;
    engine_ = engine;
    engine_->GetNewCharacter(this);



}

void Bullets::logic() {
    Gde;
    std::cout << "\n\n\n\n\n\n\n\n---------logic was created\n\n\n\n\n" << std::endl;
}

void Bullets::draw() {
    Character::draw();
}

void Bullets::move() {
    Character::move();
}

void Bullets::Orientation() {
    sprite_.setRotation(180 + atan2f(v.y, v.x) * 180 / PI);
}
#endif //GAME_BULLETS_H
