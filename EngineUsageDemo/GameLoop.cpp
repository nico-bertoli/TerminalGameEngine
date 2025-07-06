#include "GameLoop.h"
#include "Config.h"
#include "EndlessRunnerLevel.h"
#include "PuzzleLevel.h"
#include "Terminal.h"
#include "CollisionsTestLevel.h"
#include "PongLevel.h"
#include "InputUtils.h"
#include "AudioManager.h"
#include "Simulation.h"
#include "SpaceInvadersLevel.h"
#include "SortingLayerTestLevel.h"

using namespace std;
using namespace Engine;
using namespace Engine::InputUtils;

GameLoop::GameLoop()
{
    bool returnToMainMenu = false;

    while (true)
    {
        AudioManager::Instance().StopMusic();
        std::shared_ptr<Level> level = ShowLevelSelection();
        while (true)
        {
            returnToMainMenu = LoopSimulation(level);
            if (returnToMainMenu)
                break;
        }
    }
}

bool GameLoop::LoopSimulation(std::shared_ptr<Level> level)
{
    Simulation::Instance().LoadLevel(level);
    while (level->IsTerminated() == false)
    {
        Simulation::Instance().Step();
        if (IsKeyPressed(Key::ESC))
            return true;
    }
    return false;
}

std::shared_ptr<Level> GameLoop::ShowLevelSelection()
{
    Terminal::Instance().Clear();

    Terminal::Instance().SetColor(Terminal::WHITE);
    cout << "==========================" << endl;
    cout << "   Terminal Game Engine   " << endl;
    cout << "==========================" << endl << endl;

    cout << "Select a demo game:" << endl;
    Terminal::Instance().SetColor(Terminal::RED);
    cout << "1 -> space invaders" << endl;
    Terminal::Instance().SetColor(Terminal::GREEN);
    cout << "2 -> endless runner" << endl;
    Terminal::Instance().SetColor(Terminal::CYAN_DARK);
    cout << "3 -> puzzle game" << endl;
    Terminal::Instance().SetColor(Terminal::YELLOW);
    cout << "4 -> pong (local multiplayer)" << endl;

    Terminal::Instance().SetColor(Terminal::WHITE);
#if DEBUG_MODE
    cout << "5 -> collisions test" << endl;
    cout << "6 -> sorting layer test" << endl;
#endif;
    cout << "esc -> return to main menu" << endl;

    cout << endl << endl << endl;
    cout << "--------------------------- Controls:" << endl;

    cout << "Space invaders:" << endl;
    cout << "wasd: move, space bar: shoot" << endl << endl;

    cout << "Platformers:" << endl;
    cout << "wasd: move, spacebar: jump" << endl << endl;

    cout << "Pong:" << endl;
    cout << "a/d: Player 1 move, left/right arrow: Player 2 move" << endl;

    cout << endl << endl << endl;
    cout << "--------------------------- Credits:" << endl;

    cout << "Music by 'Cody O'Quinn'" << endl;

    while (true)
    {
        if (IsKeyPressed(Key::NUM_1))
        {
            return std::make_unique<SpaceInvaders::SpaceInvadersLevel>();
            break;
        }
        else if (IsKeyPressed(Key::NUM_2))
        {
            return std::make_unique<Platformer::EndlessRunnerLevel>();
            break;
        }
        else if (IsKeyPressed(Key::NUM_3))
        {
            return std::make_unique<Platformer::PuzzleLevel>();
            break;
        }
        else if (IsKeyPressed(Key::NUM_4))
        {
            return std::make_unique<Pong::PongLevel>();
            break;
        }
#if DEBUG_MODE
        else if (IsKeyPressed(Key::NUM_5))
        {
            return std::make_unique<Platformer::CollisionsTestLevel>();
            break;
        }
        else if (IsKeyPressed(Key::NUM_6))
        {
            return std::make_unique<Platformer::SortingLayerTestLevel>();
            break;
        }
#endif
    }
}
