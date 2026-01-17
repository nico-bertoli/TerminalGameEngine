#include <terme/Core/Frame.h>
#include <terme/Utils/StringUtils.h>
#include <cassert>

using std::string;

namespace Engine
{
    void Frame::ReadFromFile(const char* file_name)
    {
        if (file_name[0] == '\0')
            return;

        std::ifstream file(file_name, std::ios::binary);
        if (!file)
        {
            std::cerr << "Error opening frame file: " << file_name << std::endl;
            return;
        }

        string line = "";
        int y = 0;

        while (std::getline(file, line))
        {
            RemoveNotAllowedChars(line);

            if (y == 0)
                chars.Resize(line.size(), 0);

            assert(line.size() == chars.GetSizeX());

            chars.IncreaseSizeY();
            for (int x = 0; x < line.length(); ++x)
                chars.Get(x, y) = line[x];

            line = "";
            ++y;
        }

        return;
    }

    void Frame::RemoveNotAllowedChars(string& str)
    {
        StringUtils::RemoveInstancesOfChar(str, '\n');
        StringUtils::RemoveInstancesOfChar(str, '\r');
        StringUtils::RemoveInstancesOfChar(str, '\t');
        StringUtils::RemoveInstancesOfChar(str, '\0');
    }

    void Frame::WriteString(const string& written_string, char write_over_char)
    {
        for (size_t y = 0; y < GetSizeY(); ++y)
        {
            for (size_t x = 0; x < GetSizeX(); ++x)
            {
                char c = chars.Get(x, y);

                // insert score message
                if (c == write_over_char)
                {
                    for (int insert_it = 0; insert_it < written_string.size(); ++insert_it)
                        chars.Get(x + insert_it, y) = written_string[insert_it];

                    x += written_string.size() - 1;
                }
            }
        }
    }


}