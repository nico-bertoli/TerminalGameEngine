#pragma once
#include "Terminal.h"

namespace Engine
{
	class Printer
	{
		//---------------------------------------------------------- Margins
	public:
		static const size_t LEFT_MARGIN_SIZE = 1;
		static const size_t TOP_MARGIN_SIZE = 2;
		static const size_t BOTTOM_MARGIN_SIZE = 1;

		//---------------------------------------------------------- Fields
	protected:
		size_t screenSizeX;
		size_t screenSizeY;
		size_t padding;

		Terminal& terminal = Terminal::Instance();

		//---------------------------------------------------------- Methods
	public:
		Printer
		(
			size_t screenSizeX,
			size_t screenSizeY,
			size_t screenPadding
		) :
			screenSizeX(screenSizeX),
			screenSizeY(screenSizeY),
			padding(screenPadding)
		{
		}

		size_t GetMaxTerminalX() const { return screenSizeX + LEFT_MARGIN_SIZE; }
		size_t GetMaxTerminalY() const { return screenSizeY + TOP_MARGIN_SIZE; }

	protected:
		int ConvertWorldPosToScreenPos(int worldPos) const { return worldPos - static_cast<int>(padding); }
	};
}