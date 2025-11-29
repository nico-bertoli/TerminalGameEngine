#include <cassert>
#include "BaseTerminal.h"
#include "Managers/DebugManager.h"

namespace Engine
{
    void BaseTerminal::Cout(std::string_view s) const
    {
        std::cout << s;
#if DEBUG_MODE && SHOW_COUT_CALLS
        DebugManager::Instance().IncrementCoutCalls();
#endif
    }

    void BaseTerminal::Cout(char c) const
    {
        std::cout << c;
#if DEBUG_MODE && SHOW_COUT_CALLS
        DebugManager::Instance().IncrementCoutCalls();
#endif
    }

    void BaseTerminal::SetColor(const char* frontColor, const char* backColor)
    {
        if(frontColor == nullptr)
            frontColor = defaultFrontColor;
        if(backColor == nullptr)
            backColor = defaultBackColor;

        if(this->frontColor != frontColor)
        {
             std::cout<<frontColor;
             this->frontColor = frontColor;
        }
        if(this->backColor != backColor)
        {
            std::cout<<backColor;
            this->backColor = backColor;
        }
    }

    void BaseTerminal::SetDefaultColors(const char* frontColor, const char* backColor)
    {
        assert(frontColor != nullptr);
        assert(backColor != nullptr);

        defaultFrontColor = frontColor;
        defaultBackColor = backColor;

        SetColor(defaultFrontColor, defaultBackColor);
    }
}