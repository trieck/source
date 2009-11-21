
#define WIN32_LEAN_AND_MEAN
#define INITGUID

#include <windows.h>
#include <ddraw.h>

/*
 * main entry point
 */
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPSTR lpCmdLine, int nShowCmd)
{
	HRESULT hr;
	LPDIRECTDRAW pdd;

	hr = DirectDrawCreate(NULL, &pdd, NULL);
	if (FAILED(hr))
		return 1;

	pdd->Release();

	return 0;
}
