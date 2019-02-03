//
// Created by george on 22.05.18.
//

#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H

#include "ControlFunctions.h"
#include "Bullets.h"

class Enemy : public Character {
protected:
    double viewRange;
    double atackRange;


public:
    explicit Enemy(sf::Texture &texture, Engine *engine);

    void logic() override;

    void freeFlight();

    void Orientation() {
        sprite_.setRotation(90 + atan2f(v.y, v.x) * 180 / PI);
    }

    void chasing(sf::Vector2f distance);

    void Shot(sf::Vector2f distance) override;

    void move() override;

    void attack(sf::Vector2f distance) override;

    void draw() override;;
};

Enemy::Enemy(sf::Texture &texture, Engine *engine) : Character(texture) {


    vMin = 2;
    type = BOT;
    vMax = 10;
    mass = 1500;
    cooldown = BOT_CD;
    viewRange = BOT_VI;
    atackRange = BOT_AT;
    hp = BOT_HP;
    stamina = BOT_ST;
    dmg = BOT_DMG;
    sprite_.setScale(BOT_SIZE / width, BOT_SIZE / height);

    bulletTexture.loadFromFile("bot_bullet.png");

    height = BOT_SIZE;
    width = BOT_SIZE;

    coord.x = WIN_X / 2;
    coord.y = BACK_Y / 2 + quantity * sgn(rand() - RAND_MAX/2) * 100;

    v.x = vMin + rand() % (vMax - vMin);
    v.y = sgn(rand() - RAND_MAX / 2) * rand() % (vMax);

    collisionRad = BOT_SIZE / 2.f;

    engine_ = engine;
    engine_->GetNewCharacter(this);

}

void Enemy::draw() {
    Controllable::draw();
}

void Enemy::logic() {

    Controllable *ship = engine_->objects[0];
    sf::Vector2f distance = ship->getCoord() - coord;
    if (collisionClock.getElapsedTime().asMilliseconds() > 1000) {
        if (length(distance) < BOT_VI)
            chasing(distance);
        if (length(distance) < BOT_AT) {
            chasing(distance);
            attack(distance);
        }
        if (length(distance) >= BOT_VI)
            freeFlight();
    }
    ControlBounds(WIN_X / 2, WIN_Y / 2);
    Orientation();



    if ((hp == 0) && (type >= ALIVE))
        engine_->DeleteCharacter(this);
}

void Enemy::chasing(sf::Vector2f distance) {

    v = distance;
    v.x /= length(distance) / vMax;
    v.y /= length(distance) / vMax;

}

void Enemy::freeFlight() {
    float angle;
    if (v.x == 0)
        angle = 180;
    else
        angle = atanf(v.y / v.x) + 90;

    a.x = (rand() % ACCEL_MAX) * sgn(rand() - RAND_MAX / 2) * cosf(angle);
    a.y = (rand() % ACCEL_MAX) * sgn(rand() - RAND_MAX / 2) * sinf(angle);

}

void Enemy::attack(sf::Vector2f distance) {Character::attack(distance);}

void Enemy::Shot(sf::Vector2f distance) {
    Character::Shot(distance);
//    auto * bullet_ptr = new Bullets (bulletTexture, engine_, coord, distance) ;
}

void Enemy::move() {Character::move();}


#endif //GAME_ENEMY_H
