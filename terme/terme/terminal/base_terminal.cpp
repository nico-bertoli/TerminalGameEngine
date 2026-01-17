#include <cassert>
#include <terme/terminal/base_terminal.h>
#include <terme/managers/debug_manager.h>

namespace terme
{
    void base_terminal::Cout(std::string_view s) const
    {
        std::cout << s;
#if DEBUG_MODE && SHOW_COUT_CALLS
        debug_manager::Instance().IncrementCoutCalls();
#endif
    }

    void base_terminal::Cout(char c) const
    {
        std::cout << c;
#if DEBUG_MODE && SHOW_COUT_CALLS
        debug_manager::Instance().IncrementCoutCalls();
#endif
    }

    void base_terminal::SetColor(const char* front_color, const char* back_color)
    {
        if(front_color == nullptr)
            front_color = default_front_color_;
        if(back_color == nullptr)
            back_color = default_back_color_;

        if(this->front_color_ != front_color)
        {
             std::cout<<front_color;
             this->front_color_ = front_color;
        }
        if(this->back_color_ != back_color)
        {
            std::cout<<back_color;
            this->back_color_ = back_color;
        }
    }

    void base_terminal::SetDefaultColors(const char* front_color, const char* back_color)
    {
        assert(front_color != nullptr);
        assert(back_color != nullptr);

        default_front_color_ = front_color;
        default_back_color_ = back_color;

        SetColor(default_front_color_, default_back_color_);
    }
}