#pragma once
#include <unordered_map>
#include "Core/Base/PublicSingleton.h"
namespace Soarscape
{
	struct MousePos
	{
		MousePos(float x, float y)
			: x(x), y(y)
		{}
		float x;
		float y;
	};
	class Input : public PublicSingleton<Input>
	{
	public:
		Input();
		enum class KeyCode
		{
			Left_Mouse_Down = 0,
			Left_Mouse_Release,
		};
		std::unordered_map<std::string, KeyCode> keyMap;
	};
}