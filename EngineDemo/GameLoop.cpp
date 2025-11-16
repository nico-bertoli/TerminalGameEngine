#include "GameLoop.h"
#include "Config.h"
#include "EndlessRunnerLevel.h"
#include "PuzzleLevel.h"
#include "Terminal/Terminal.h"
#include "CollisionsTestLevel.h"
#include "PongLevel.h"
#include "InputManager/InputManager.h"
#include "Managers/AudioManager.h"
#include "Core/Simulation.h"
#include "SpaceInvadersLevel.h"
#include "SortingLayerTestLevel.h"

using namespace std;
using namespace Engine;

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
        if (InputManager::Instance().IsKeyPressed(Key::ESC))
            return true;
    }
    return false;
}

std::shared_ptr<Level> GameLoop::ShowLevelSelection()
{
    Terminal::Instance().Clear();

    Terminal::Instance().SetColor(Color::WHITE);
    cout << "==========================\n";
    cout << "   Terminal Game Engine   \n";
    cout << "==========================\n\n";

    cout << "Select a demo game:\n";
    Terminal::Instance().SetColor(Color::RED);
    cout << "1 -> space invaders\n";
    Terminal::Instance().SetColor(Color::GREEN);
    cout << "2 -> endless runner\n";
    Terminal::Instance().SetColor(Color::CYAN_DARK);
    cout << "3 -> puzzle game\n";
    Terminal::Instance().SetColor(Color::YELLOW);
    cout << "4 -> pong (local multiplayer)\n";

    Terminal::Instance().SetColor(Color::WHITE);
#if DEBUG_MODE
    cout << "5 -> collisions test\n";
    cout << "6 -> sorting layer test\n";
#endif
    cout << "esc -> return to main menu\n\n";

    cout << "--------------------------- Controls:\n";

    cout << "Space invaders:\n";
    cout << "wasd: move, space bar: shoot\n\n";

    cout << "Platformers:\n";
    cout << "wasd: move, spacebar: jump\n\n";

    cout << "Pong:\n";
    cout << "a/d: Player 1 move, left/right arrow: Player 2 move\n\n";

    cout << "--------------------------- Credits:\n";

    cout << "Music by 'Cody O'Quinn'\n";

    while (true)
    {
        if (InputManager::Instance().IsKeyPressed(Key::NUM_1))
        {
            return std::make_unique<SpaceInvaders::SpaceInvadersLevel>();
            break;
        }
        else if (InputManager::Instance().IsKeyPressed(Key::NUM_2))
        {
            return std::make_unique<Platformer::EndlessRunnerLevel>();
            break;
        }
        else if (InputManager::Instance().IsKeyPressed(Key::NUM_3))
        {
            return std::make_unique<Platformer::PuzzleLevel>();
            break;
        }
        else if (InputManager::Instance().IsKeyPressed(Key::NUM_4))
        {
            return std::make_unique<Pong::PongLevel>();
            break;
        }
#if DEBUG_MODE
        else if (InputManager::Instance().IsKeyPressed(Key::NUM_5))
        {
            return std::make_unique<Platformer::CollisionsTestLevel>();
            break;
        }
        else if (InputManager::Instance().IsKeyPressed(Key::NUM_6))
        {
            return std::make_unique<Platformer::SortingLayerTestLevel>();
            break;
        }
#endif
    }
}
