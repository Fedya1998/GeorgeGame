//
// Created by andrew on 23.05.18.
//

#ifndef GAME_CONTROLFUNCTIONS_H
#define GAME_CONTROLFUNCTIONS_H

#include "Controllable.h"
#include "EngineFunctions.h"
#include "Bullets.h"


Controllable::Controllable(sf::Texture &texture) {
    std::cout << "I am controllable, and I'm ok\n";

    sprite_.setTexture(texture);
    width = sprite_.getTexture()->getSize().x;
    height = sprite_.getTexture()->getSize().y;
    id = quantity;


    sprite_.setOrigin(width / 2, height / 2);

    mass = SUP_MASS;
    std::cout << "I am end of controllable, and I'm ok\n";

}


void Controllable::dump() {
    engine_->window_.draw(sprite_);
    std::cout << sprite_.getPosition().x << sprite_.getPosition().y << "\n";
    std::cout << coord.x << coord.y << "\n\n";
}

void Controllable::draw() {
    sprite_.setPosition(coord);
    engine_->window_.draw(sprite_);
}

bool Controllable::operator!=(const Controllable &that) {
    return !(*this == that);
}

bool Controllable::operator==(const Controllable &that) {
    return coord.x == that.coord.x && that.coord.y == coord.y;
}

void Controllable::setEngine(Engine *engine) { this->engine_ = engine; }

sf::Vector2f Controllable::getCoord() { return coord; }

sf::Vector2f Controllable::collDistance(Controllable &that) { return that.getCoord() - coord; }

bool colide(Controllable &member) {
    return false;
}


void Character::move() {

    if (sqrt(pow(v.x + a.x, 2) + pow(v.y + a.y, 2)) < vMax) {
        v.x += a.x * engine_->dtime_;
        v.y += a.y * engine_->dtime_;
    }

    if (sqrt(pow(v.x, 2) + pow(v.y, 2)) > vMax) {
        v.y /= sqrt(vMax);
        v.x /= sqrt(vMax);
    }
    coord.x += v.x * engine_->dtime_;
    coord.y += v.y * engine_->dtime_;
//    engine_->clock_.restart();

    std::cout << "coordinates: " << coord.x << " " << coord.y << " pidoras ";

    std::cout << "Velocity " << v.x << " " << v.y << "\n\n\n";

}


Character::Character(sf::Texture &texture) : Controllable(texture) {
    std::cout << "I am movable, and I'm ok\n";

}

void Character::draw() {
    Controllable::draw();
}

void Character::colisionResponse(Character *that) {
    std::cout << "collision detected\n";

    if ((!that->collisional) && (this->collisional)) {
        if (-(that->type) != this->type) {
            this->hit();
            engine_->DeleteCharacter(that);
        }


    } else if ((!this->collisional) && (that->collisional)) {
        if (-(that->type) != this->type) {
            that->hit();
            engine_->DeleteCharacter(this);
        }

    } else {
        collisionClock.restart();
        that->collisionClock.restart();


        float deltaP = dot(this->v - that->v, this->collDistance(*that));
        std::cout << "Velocity DIRECTION :" << dot(this->v, that->v) << "\n";

        deltaP *= (2 * this->mass * that->mass) / ((this->mass + that->mass) * length(this->collDistance(*that)));

        std::cout << "deltaP = " << deltaP << "\n";

        sf::Vector2f dp = this->collDistance(*that) * (deltaP / 100.f);

        std::cout << "Spacecraft  " << (dp / this->mass).x << "   " << (dp / this->mass).y << "\n";
        std::cout << " Metheor" << (dp / that->mass).x << "   " << (dp / that->mass).y << "\n";
        std::cout << "Mass1 = " << this->mass << "  Mass2 = " << that->mass << "\n";

        v -= dp / this->mass;
        that->v -= dp / that->mass;

        if (this->type != that->type) {
            this->accident();
            that->accident();
        }
    }


}

void Controllable::hit() {
    if (type >= ALIVE) {
        if (hp - BOT_DMG > 0)
            hp -= BOT_DMG;
        else
            hp = 0;
    }
}

void Controllable::accident() {
    if (type >= ALIVE) {
        if (hp - COL_DMG > 0)
            hp -= COL_DMG;
        else
            hp = 0;
    }
}

bool Controllable::colide(Controllable *that) {


    double length1 = length(this->collDistance(*that));
    double size1 = this->collisionRad;
    double size2 = that->collisionRad;
    auto size = size1 + size2;




//    std::cout << "Coordinats1: " << that->getCoord().x << "  " << that->getCoord().y << " \n";
//    std::cout << "Coordinats2: " << coord.x << "  " << coord.y << "\n";
//    std::cout << "COOLLIDE:: " << size1 << " + " << size2 << " = " << size << "    " << length1 << "\n";

    return length1 < size;
}


void Character::ControlBounds(double x, double y) {

    if (((coord.x > BACK_X - x) && (v.x > 0)) ||
        ((coord.x < x) && (v.x < 0))) {

        sprite_.setPosition(check(coord.x, x, BACK_X), coord.y);
        v.x *= (-1);
    } else if (((coord.y > BACK_Y - y) && (v.y > 0)) ||
               ((coord.y < y) && (v.y < 0))) {

        sprite_.setPosition(coord.x, check(coord.y, y, BACK_Y));
        v.y *= (-1);
    }
}

void Character::attack(sf::Vector2f distance) {
    std::cout << "/////////////    attack time is " << clock_shot.getElapsedTime().asSeconds() << "/////" << std::endl;
    if (clock_shot.getElapsedTime().asSeconds() > cooldown) {
        this->Shot(distance);
        Gde;
        clock_shot.restart();

    }
}

void Character::Shot(sf::Vector2f distance) {
    auto *bullet_ptr = new Bullets(bulletTexture, engine_, coord, distance, type);
}


double Controllable::getSize() { return (width + height) / 3.3; }

Spacecraft::Spacecraft(sf::Texture &texture, Engine *engine) : Character(texture) {
    std::cout << "Im at the start of Spacecraft\n";

    cooldown = 1;
    hp = SUP_HEALTH;
    type = SPACECRAFT;
    mass = SUP_MASS;

    vMax = 100;

    bulletTexture.loadFromFile("ship_bullet.png");

    engine_ = engine;
    engine_->GetNewCharacter(this);

    coord.x = BACK_X / 2;
    coord.y = BACK_Y / 2;

    sprite_.setScale((TEXT_SIZE / width), (TEXT_SIZE / height));

    width = TEXT_SIZE;
    height = TEXT_SIZE;

    collisionRad = BOT_SIZE / 2.f;

    std::cout << "Im at the end of Spacecraft\n";
}


void Spacecraft::move() { Character::move(); }

void Spacecraft::draw() { Controllable::draw(); }

void Spacecraft::logic() {
    const float accel = 2;
    const float slowdown = 0.01;

    const float EPSILON = 0.0001;
    if (collisionClock.getElapsedTime().asMilliseconds() > 1000) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            a.y = -accel;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            a.x = -accel;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            a.y = accel;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            a.x = accel;

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            a.x = 0;

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            a.y = 0;

        if (fabs(pow(pow(v.x, 2) + pow(v.y, 2), 0.5)) > EPSILON) {/* which means that we're moving*/
            a.x += -sgn(v.x) * slowdown * v.x * v.x;
            a.y += -sgn(v.y) * slowdown * v.y * v.y;
        } else {
            v.x = 0;
            v.y = 0;
        }
    } else a.x = a.y = 0;
/* putting brims of map */
    if (coord.x < WIN_X / 2) {
        v.x = 0;
        a.x = 0;
        coord.x = WIN_X / 2;
    }

    if (coord.x > BACK_X - WIN_X / 2) {
        v.x = 0;
        a.x = 0;
        coord.x = BACK_X - WIN_X / 2;
    }
    if (coord.y < WIN_Y / 2) {
        v.y = 0;
        a.y = 0;
        coord.y = WIN_Y / 2;
    }
    if (coord.y > BACK_Y - WIN_Y / 2) {
        v.y = 0;
        a.y = 0;
        coord.y = BACK_Y - WIN_Y / 2;
    }
    MouseOrientation();

//    for (int j = 1; j < quantity; ++j) {
//        if (this->colide(engine_->objects[j])) {
//
//            std::cout << "INTERSECTION WITH " << j << ", SOOOQA\n";
//            this->colisionResponse(dynamic_cast<Character *>(engine_->objects[j]));
//            Gde;
//        }
//    }

    if (sf::Mouse::isButtonPressed((sf::Mouse::Left))) {
        sf::Vector2i mouse = sf::Mouse::getPosition(engine_->window_);
        mouse.x += coord.x - WIN_X / 2;
        mouse.y += coord.y - WIN_Y / 2;
        dest = sf::Vector2f(mouse.x, mouse.y) - coord;


        attack(dest);
    }

    if ((hp == 0) && (type >= ALIVE))
        engine_->DeleteCharacter(this);

}

void Spacecraft::MouseOrientation() {

    sf::Vector2i mouse = sf::Mouse::getPosition(engine_->window_);
    sf::Vector2f center = sprite_.getPosition();

    mouse.x += center.x - WIN_X / 2;
    mouse.y += center.y - WIN_Y / 2;

    sf::Vector2f ptr = sf::Vector2f(mouse.x, mouse.y) - center;
    sprite_.setRotation(270 + atan2f(ptr.y, ptr.x) * 180 / PI);


}

sf::Vector2f Spacecraft::FindViewCenter(const sf::Sprite &background, sf::View &gameView) {
    sf::Vector2f center = sf::Vector2f(sprite_.getPosition().x, sprite_.getPosition().y);

    center.x = std::max(center.x, gameView.getSize().x / 2);
    center.y = std::max(center.y, gameView.getSize().y / 2);

    center.x = std::min(center.x, background.getTexture()->getSize().x - gameView.getSize().x / 2);
    center.y = std::min(center.y, background.getTexture()->getSize().y - gameView.getSize().y / 2);
    return center;
}

void Spacecraft::attack(sf::Vector2f distance) { Character::attack(distance); }

void Spacecraft::Shot(sf::Vector2f distance) { Character::Shot(distance); }

#endif //GAME_CONTROLFUNCTIONS_H
