#pragma once
#include "Config.h"
#include "Core/Frame.h"
#include "Terminal/Terminal.h"
#include "Printers/Printer.h"
#include <list>
#include <string>
#include <memory>

namespace Engine
{
	class GameObject;
	class Frame;

	class SimulationPrinter : public Printer
	{
		//---------------------------------------------------------- Fields
	private:
		TerminalColor bg_chars_color_;
		Frame background_;
		//---------------------------------------------------------- Methods
	public:
		SimulationPrinter
		(
			size_t screen_size_x,
			size_t screen_size_y,
			size_t screen_padding,
			TerminalColor bg_chars_color,
			const char* background_file_name = ""
		);

		void PrintObject(std::shared_ptr<GameObject> obj);
		void ClearObject(std::shared_ptr<GameObject> obj);
		void ClearArea(int world_x_pos, int world_y_pos, size_t x_size, size_t y_size);

	private:
		void PrintInternal(int world_x_pos, int world_y_pos, size_t x_size, size_t y_size, std::shared_ptr<GameObject> go);
		void InitBackground(const char* background_file_name);
		void PrintBackground();
	};
}