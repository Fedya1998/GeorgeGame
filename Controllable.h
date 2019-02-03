//
// Created by george on 18.04.18.
//

#ifndef GAME_BASE_H
#define GAME_BASE_H

#include <SFML/Graphics.hpp>
#include <cstring>
#include <cmath>
#include <utility>
#include <iostream>
#include "dlc.h"
#include "Lifebar_h.h"

static int quantity = 0;

class Controllable;

class Engine {
public:
    sf::Sprite background_;
    std::string pathfile = "back.png";

    sf::RenderWindow window_;

    sf::View gameView_;

    sf::Clock clock_;

    LifeBar lifeBar_ ;
    float dtime_;

    void GetNewCharacter(Controllable *that);

    void DeleteCharacter(Controllable *that);

    void Increment();

    Controllable **objects = (Controllable **) calloc(sizeof(Controllable *), 100);

    Engine();

    void run();

    ~Engine() {
        Gde;
        delete (objects);
        std::cout << "Engine Deleted";
    }
};

#endif //GAME_ENGINE_H


class Controllable {
protected:
    sf::Vector2f coord;
    float height = 0;
    float width = 0;
    Engine *engine_;
    float collisionRad = 0;
    sf::Sprite sprite_;
    bool collisional = true;
    float mass = INF_MASS;

    int type = 0;
    int hp = -1;

public:
    int id = -1;
    explicit Controllable(sf::Texture &texture);

    void dump();

    bool colide(Controllable *that);

    virtual void draw();

    void hit ();

    void accident ();

    virtual ~Controllable() = default;

    bool operator==(const Controllable &that);

    bool operator!=(const Controllable &that);

    void setEngine(Engine *engine);

    sf::Vector2f collDistance(Controllable &that);

    sf::Vector2f getCoord();

    double getSize();

};


class Character : public Controllable {
protected:
    sf::Vector2f v;
    int vMax = 0;
    int vMin = 0;

    sf::Clock clock_shot{};
    sf::Clock collisionClock;

    sf::Texture bulletTexture;
    sf::Vector2f a {};
    sf::Vector2f dest;

    float stamina;
    float health;
    float dmg;

    float cooldown;

public:

    virtual void move();

    void draw() override;

    virtual void attack(sf::Vector2f distance);

    virtual void Shot(sf::Vector2f distance);

    void collapse(Controllable &Obj);

    void colisionResponse(Character *that);

    explicit Character(sf::Texture &texture);

    void ControlBounds(double x, double y);

    ~Character() override = default;

    virtual void logic() pure;

};


class Spacecraft : public Character {
public:
    explicit Spacecraft(sf::Texture &texture, Engine *engine);

    void MouseOrientation();

    void move() override;

    void draw() override;

    void attack(sf::Vector2f distance) override;

    void Shot(sf::Vector2f distance) override;

    void logic() override;

    sf::Vector2f FindViewCenter(const sf::Sprite &background, sf::View &gameView);
};


//#endif //GAME_BASE_H
