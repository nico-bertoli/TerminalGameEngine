#pragma once

//todo move this and event to separate library

template <typename T>
class Singleton
{
//---------------------------------------------------------- Fields
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }

//---------------------------------------------------------- Fields
public:
    //prevent copy
    Singleton(const Singleton&) = delete;
    Singleton& operator = (const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator = (const Singleton&&) = delete;

protected:
    // prevent direct instantiation
    Singleton() = default;
    virtual ~Singleton() = default;
};