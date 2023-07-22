// demo_simplewindow.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include <Duilib.h>

using namespace Duilib;



class CMainWindow : public CWindowImplBase
{
public:
	CMainWindow()
		: m_btn_close(NULL)
		, m_btn_min(NULL)
		, m_btn_max(NULL)
	{
		
	}

protected:
	CButtonUI* m_btn_close;
	CButtonUI* m_btn_min;
	CButtonUI* m_btn_max;

	virtual void InitWindow()
	{
		//CButtonUI* Button = FindControlByName<CButtonUI>(TEXT("myname"));
		//Button->OnNotify += MakeDelegate(this, &CMainWindow::OnDestroy);
		m_btn_close = FindControlByName<CButtonUI>(TEXT("btn_close"));
		m_btn_min = FindControlByName<CButtonUI>(TEXT("btn_min"));
		m_btn_max = FindControlByName<CButtonUI>(TEXT("btn_max"));

		m_btn_min->OnNotify += MakeDelegate(this, &CMainWindow::OnBtnMinClicked, _T("click"));
		m_btn_max->OnNotify += MakeDelegate(this, &CMainWindow::OnBtnMaxClicked, _T("click"));
		m_btn_close->OnNotify += MakeDelegate(this, &CMainWindow::OnBtnCloseClicked, _T("click"));

		CMusicPlayer* musicPlayer = CMusicPlayer::Get();
		string filename1 = "山崎惠理——《Starlight》（昴宿七星 ED） - 1.202206031532_x264(Av639680153,P1).mp3";
		musicPlayer->AddNewSound(filename1.c_str());
		musicPlayer->Play2D(filename1.c_str());
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

private:

	bool CMainWindow::OnBtnMinClicked(TNotifyUI* pTNotifyUI, LPARAM lParam, WPARAM wParam)
	{
		ShowMinimized();
		return true;
	}

	bool CMainWindow::OnBtnMaxClicked(TNotifyUI* pTNotifyUI, LPARAM lParam, WPARAM wParam)
	{
		if (IsMaximized())
		{
			Show();
		}
		else
		{
			ShowMaximized();
		}
		return true;
	}

	bool CMainWindow::OnBtnCloseClicked(TNotifyUI* pTNotifyUI, LPARAM lParam, WPARAM wParam)
	{
		Close();
		return true;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	CApplication* app = CApplication::Get();
	if (!app->Init())
	{
		printf("Application init failed!\n");
		return -1;
	}

	CMainWindow mainWindow;
	if (!mainWindow.Create(NULL, TEXT("MAINWINDOW_MUSICPLAYER")))
	{
		printf("Create window failed!\n");
		return -2;
	}
	mainWindow.CenterWindow();
	mainWindow.Show();
	return app->Run();
}

