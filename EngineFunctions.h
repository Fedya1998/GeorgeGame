//
// Created by andrew on 24.05.18.
//

#ifndef GAME_ENGINEFUNCTIONS_H
#define GAME_ENGINEFUNCTIONS_H

#include "ControlFunctions.h"
#include "Lifebar.h"

void Engine::GetNewCharacter(Controllable *that) {
    objects[quantity] = that;
    Increment();
}

void Engine::Increment() {
    quantity++;

}

Engine::Engine() :
        window_(sf::VideoMode(WIN_X, WIN_Y), "Play, BITCH!"),
        gameView_(sf::FloatRect(0.0f, 0.0f, WIN_X, WIN_Y)) {

    Gde;
    window_.setView(gameView_);
}


void Engine::DeleteCharacter(Controllable *that) {
    Controllable * temp = this->objects[quantity - 1];
    this->objects[quantity - 1] = that;
    that = temp;
    quantity--;
}


void Engine::run() {
    std::cout<<"quantaty is " << quantity;
    sf::Texture map;
    map.loadFromFile("space.jpg");
    //map.setSmooth(true);
    background_.setTexture(map);
    int k = 1;
    sf::Event event{};
    while (window_.isOpen()) {
        window_.clear();
        window_.setFramerateLimit(60);
        dtime_ = clock_.getElapsedTime().asMicroseconds() / 50000.f;
        clock_.restart();

        window_.draw(background_);

        while (window_.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window_.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window_.close();

        sf::Vector2f center = dynamic_cast<Spacecraft *>(objects[0])->FindViewCenter(background_, gameView_);
        gameView_.setCenter(sf::Vector2f(center.x, center.y));
        window_.setView(gameView_);


        if (objects) {

            for (int i = 0; i < quantity; i++) {
                std::cout << "Pizda  " << i << "\n";
                auto object = dynamic_cast <Character *> (objects[i]);

                object->logic();
                for (int j = 1; j < quantity; ++j) {
                    if ((j != i) && (object->colide(objects[j])) && (object->id != objects[j]->id)) {

                        std::cout << "INTERSECTION WITH " << j << ", SOOOQA\n";
                        object->colisionResponse(dynamic_cast<Character *>(objects[j]));

                        Gde;
                    }
                }

                object->move();
                object->draw();
            }

        }
        lifeBar_.draw(window_);
        lifeBar_.update(10);
        window_.display();
    }
    std::cout<<"quantaty is " << quantity;
//        for (; clock.getElapsedTime().asMicroseconds() - time < 5e4;) {}
}

#endif //GAME_ENGINEFUNCTIONS_H
