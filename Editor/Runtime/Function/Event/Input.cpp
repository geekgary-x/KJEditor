#include "Function/Event/Input.h"

namespace Soarscape
{
	Input::Input()
	{
		keyMap["Left_Mouse_Down"] = KeyCode::Left_Mouse_Down;
		keyMap["Left_Mouse_Release"] = KeyCode::Left_Mouse_Release;
	}
}