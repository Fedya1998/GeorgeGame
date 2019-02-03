#include "EngineFunctions.h"
#include "Metheors.h"
#include "Enemy.h"


int main() {
    Engine engine;
    int i;

    auto *super_list = (Controllable *) calloc(sizeof(Controllable), 20);

    sf::Texture ironMan;
    ironMan.loadFromFile("Red-Chin-Iron-Man-128.png");
    Gde;
    sf::Sprite sprite(ironMan);

    sf::Texture metheor;
    metheor.loadFromFile("metheor.png");

    sf::Texture bots;
    bots.loadFromFile("friend.png");


    Spacecraft djordj(ironMan, &engine);
//    djordj.setEngine(&engine);

    Metheors metheors(metheor, &engine);
//    metheors.setEngine(&engine);

    for (i = 0; i < BOT_AMOUNT; i++){
        auto* bullet_ptr = new Enemy(bots, &engine);
    }

    for (i = 0; i < MET_AM; i++){
        auto* bullet_ptr = new Metheors(metheor, &engine);
    }



    Gde;


    Gde;
//    super_list[0] = djordj;
//    engine.GetNewCharacter(&djordj);
    Gde;
    engine.run();
    Gde;

    return 0;
}






