#pragma once
#include <iostream>

namespace shu
{
	struct KeyStatus
	{
		bool isPress = false;	// �Ƿ���
		bool isHold = false;	// �Ƿ���
		bool isRelease = false;	// �Ƿ��ͷ�
	};

	// ������Ӧ�ļ��룬���飺https://learn.microsoft.com/zh-cn/windows/win32/inputdev/virtual-key-codes
	enum class Key : uint32_t
	{
		LBUTTON = 0x01,
		RBUTTON,
		CANCEL,
		MBUTTON,
		SBUTTON1,
		SBUTTON2,
		BACK = 0x08,
		TAB,
		CLEAR = 0x0C,
		RETURN,
		SHIFT = 0x10,
		CONTROL,
		ESCAPE = 0x1B,
		// VK_MENU ...
		SPACE = 0x20,
		LEFT = 0x25,
		UP, RIGHT, DOWN,
		A = 0x41,
		B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
	};

	class InputKey
	{
	public:
		InputKey();
		~InputKey();

		static void UpdataKeyStatus(uint32_t key, bool status);
		static void Updata();
		static KeyStatus& GetKeyStatus(Key key);
		// �Ƿ�������һ��������
		static bool IsAnyKeyPress();

	private:
		static InputKey* ptr;

		// ������״̬
		bool m_KeyNewState[256] = { 0 };
		bool m_KeyOldState[256] = { 0 };
		KeyStatus m_KeyboardState[256];

		bool m_IsAnyKeyPress = false;
	};
}

