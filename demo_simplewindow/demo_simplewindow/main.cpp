// demo_simplewindow.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <Duilib.h>

using namespace Duilib;

class CMainWindow : public CWindowImplBase
{
public:


protected:
	virtual void InitWindow()
	{

	}

	virtual LPCTSTR GetWindowClassName()const
	{
		return TEXT("MAINWINDOW");
	}

	virtual CDuiString GetSkinFile()
	{
		return CDuiString(TEXT("XML\\MainWindow.xml"));
	}

	virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CWindowImplBase::OnDestroy(uMsg, wParam, lParam, bHandled);
		::PostQuitMessage(0);
		bHandled = TRUE;
		return FALSE;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	CApplication* app = CApplication::Get();
	if (!app->Init())
	{
		return -1;
	}

	CMainWindow mainWindow;
	HWND hWnd = mainWindow.Create(NULL, TEXT("MAINWINDOW_BENJAMIN"), UI_WNDSTYLE_FRAME, 0L);
	mainWindow.CenterWindow();
	mainWindow.Show();
	return app->Run();
}

