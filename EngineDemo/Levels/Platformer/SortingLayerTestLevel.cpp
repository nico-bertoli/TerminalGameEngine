#include "SortingLayerTestLevel.h"
#include "Level.h"
#include "Simulation.h"
#include "Bunny.h"
#include "SortingLayerTestObject.h"

using std::shared_ptr;

namespace Platformer
{
    void SortingLayerTestLevel::LoadInSimulation()
    {
        Level::LoadInSimulation();
        Engine::Simulation& simulation = Engine::Simulation::Instance();

        //----------------- bunny setup
        shared_ptr<Bunny> bunny = std::make_shared<Bunny>(9,5);
        bunny->OnObstacleHit.Subscribe([this]() { OnGameOver(); });
        simulation.TryAddEntity(bunny);

        //----------------- front object
        auto sortingLayerTestObjFront = std::make_shared<SortingLayerTestObject>
        (
            10,     //posx
            1,      //posy
            30,     //sizex
            5,      //sizey
            -37,    //char
            Engine::Terminal::RED,
            200     //sorting layer
        );
        simulation.TryAddEntity(sortingLayerTestObjFront);

        //----------------- back object
        auto sortingLayerTestObjBack = std::make_shared<SortingLayerTestObject>
        (
            60,     //posx
            1,      //posy
            30,      //sizex
            5,      //sizey
            -37,     //char
            Engine::Terminal::BLUE,
            0       //sorting layer
        );
        simulation.TryAddEntity(sortingLayerTestObjBack);
    }
}