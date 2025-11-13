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
}