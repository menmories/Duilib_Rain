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
		//CButtonUI* Button = FindControlByName<CButtonUI>(TEXT("myname"));
		//Button->OnNotify += MakeDelegate(this, &CMainWindow::OnDestroy);
	}

	virtual LPCTSTR GetWindowClassName()const
	{
		return TEXT("MAINWINDOW");
	}

	virtual CDuiString GetSkinFile()
	{
		return CDuiString(TEXT("XML\\MainWindow.xml"));
	}

	virtual void OnDestroy()
	{
		CWindowImplBase::OnDestroy();
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

