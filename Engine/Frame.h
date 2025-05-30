#pragma once
#include "Config.h"
#include "Vector2D.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <cassert>
#include <string>

namespace Engine
{
    class Frame
    {
    public:
        Vector2D<char> chars;

    public:
        size_t GetSizeY() const { return chars.GetSizeY(); }
        size_t GetSizeX() const { return chars.GetSizeX(); }

        void ReadFromFile(const char* fileName);
        void WriteString(const std::string& writenString, char writeOverChar);
        bool IsSetup() { return GetSizeY() > 0; }

        void RemoveNotAllowedChars(std::string& str);
    };
}

