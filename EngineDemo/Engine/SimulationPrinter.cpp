#include "SimulationPrinter.h"

#include "Collider.h"
#include "GameObject.h"
#include "Simulation.h"
#include "Config.h"
#include "Level.h"
#include "TimeHelper.h"
#include "Terminal.h"
#include "DebugManager.h"

#include <Windows.h>
#include <cassert>
#include <algorithm>

using std::shared_ptr;
using std::string;

namespace Engine
{
    SimulationPrinter::SimulationPrinter
    (
        size_t screenSizeX,
        size_t screenSizeY,
        size_t screenPadding,
        int backgroundColor,
        const char* backgroundFileName
    ) : Printer(screenSizeX, screenSizeY, screenPadding), backgroundColor(backgroundColor)
    {
        InitBackground(backgroundFileName);
    }

    void SimulationPrinter::PrintObject(shared_ptr<GameObject> go)
    {
        Model model = go->GetModel();
        assert(model.GetSizeX() > 0 && model.GetSizeY() > 0);
        terminal.SetColor(go->GetColor());
        PrintInternal(go->GetPosX(), go->GetPosY(), go->GetModelWidth(), go->GetModelHeight(), go);
    }

    void SimulationPrinter::ClearObject(shared_ptr<GameObject> obj)
    {
        PrintInternal(obj->GetPosX(), obj->GetPosY(), obj->GetModelWidth(), obj->GetModelHeight(), nullptr);
    }

    void SimulationPrinter::ClearArea(int worldXPos, int worldYPos, size_t xSize, size_t ySize)
    {
        PrintInternal(worldXPos, worldYPos, xSize, ySize, nullptr);
    }

    void SimulationPrinter::PrintInternal(int worldXPos, int worldYPos, size_t xSize, size_t ySize, shared_ptr<GameObject> go)
    {
        terminal.SetColor(go == nullptr ? backgroundColor : go->GetColor());
        for (int yScreen = ConvertWorldPosToScreenPos(worldYPos), yModel = 0; yModel < ySize && yScreen < screenSizeY; ++yScreen, ++yModel)
        {
            if (yScreen + TOP_MARGIN_SIZE < TOP_MARGIN_SIZE) continue;
            int lineTerminalPosX = ConvertWorldPosToScreenPos(worldXPos) + LEFT_MARGIN_SIZE;
            string line = "";

            for (int xScreen = ConvertWorldPosToScreenPos(worldXPos), xModel = 0; xModel < xSize && xScreen < screenSizeX; ++xScreen, ++xModel)
            {
                if (xScreen + LEFT_MARGIN_SIZE < LEFT_MARGIN_SIZE)continue;

                if (go == nullptr)
                    line += background.IsSetup() ? background.chars.Get(xScreen, screenSizeY - yScreen - 1) : ' ';
                else
                    line += go->GetModel().Get(xModel, go->GetModelHeight() - 1 - yModel);
            }
            if (lineTerminalPosX < LEFT_MARGIN_SIZE)
                lineTerminalPosX = LEFT_MARGIN_SIZE;
            terminal.SetCursorPosition(lineTerminalPosX, screenSizeY - yScreen + BOTTOM_MARGIN_SIZE);
            terminal.Cout(line);
        }
    }

    void SimulationPrinter::PrintBackground()
    {
        if (!background.IsSetup())
            return;

        terminal.SetColor(backgroundColor);

        string line = "";


        for (int y = 0; y < screenSizeY; ++y)
        {
            for (int x = 0; x < screenSizeX; ++x)
            {
                //reversing y order
                char charToPrint = background.chars.Get(x, y);
                line += charToPrint;
            }
            terminal.SetCursorPosition(LEFT_MARGIN_SIZE, y + TOP_MARGIN_SIZE);
            terminal.Cout(line);
            line.clear();
        }
    }

    void SimulationPrinter::InitBackground(const char* backgroundFileName)
    {
        if (backgroundFileName == "")
            return;

        background.ReadFromFile(backgroundFileName);
        PrintBackground();
    }
}