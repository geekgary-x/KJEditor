#pragma once
#include <cstdint>
namespace Soarscape
{
	enum class MouseKey
	{
		Left = 0,
		Middle,
		Right
	};
	struct MouseInput
	{
		MouseInput(MouseKey key)
			: key(key)
		{}
		MouseKey key;
	};
}