#pragma once

#include <vector>
#include <functional>

template <typename... Args>
class Event
{
    
//---------------------------------------------------------- Fields
private:
    std::vector< std::function<void(Args...)>> handlers;

//---------------------------------------------------------- Methods
public:
    void Subscribe(std::function<void(Args...)> handler)
    { 
        handlers.push_back(handler);
    }

    void Notify(Args... args)
    {
        for (auto& handler : handlers)
            handler(args...);
    }

    void Clear() 
    { 
        handlers.clear();
    }
};