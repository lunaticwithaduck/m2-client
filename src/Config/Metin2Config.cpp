#include "MainDialog.h"
#include "resource.h"

#include <wtl/atlapp.h>

#include <locale.h>

#pragma comment(lib, "d3d9.lib")

CAppModule _Module;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	::InitCommonControls();

	_Module.Init(NULL, hInstance);

	CMainDialog cDialog;
	int nRet = (int) cDialog.DoModal();

	_Module.Term();
	return nRet;
}
