#pragma once
#include <terme/config.h>
#include <terme/core/frame.h>
#include <terme/terminal/terminal.h>
#include <terme/printers/printer.h>
#include <list>
#include <string>
#include <memory>

namespace terme
{
	class game_object;
	class Frame;

	class simulation_printer : public Printer
	{
		//---------------------------------------------------------- Fields
	private:
		TerminalColor bg_chars_color_;
		Frame background_;
		//---------------------------------------------------------- Methods
	public:
		simulation_printer
		(
			size_t screen_size_x,
			size_t screen_size_y,
			size_t screen_padding,
			TerminalColor bg_chars_color,
			const char* background_file_name = ""
		);

		void PrintObject(std::shared_ptr<game_object> obj);
		void ClearObject(std::shared_ptr<game_object> obj);
		void ClearArea(int world_x_pos, int world_y_pos, size_t x_size, size_t y_size);

	private:
		void PrintInternal(int world_x_pos, int world_y_pos, size_t x_size, size_t y_size, std::shared_ptr<game_object> go);
		void InitBackground(const char* background_file_name);
		void PrintBackground();
	};
}