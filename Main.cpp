#include <Windows.h>
#include <iostream>
#include "Graphics.h"
#include "WindowHelper.h"
#include "debug.h"

/* End of File */
//what to do
//projection Transformation


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	const UINT WIDTH = 1080;
	const UINT HEIGHT = 920;
	HWND wnd;

	std::cout << "hello" << std::endl;
	RedirectIOToConsole();
	printf("hello");

	if (!SetupWindow(hInstance, WIDTH, HEIGHT, nCmdShow, wnd)) {
		std::cerr << "failed" << std::endl;
		return -1;
	}

	Graphics gfx(WIDTH, HEIGHT, wnd);

	MSG msg = {};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		gfx.Render();
	}
	
	return 0;
}