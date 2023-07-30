// demo_simplewindow.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include <Duilib.h>
#include <atlbase.h>
#include <atlstr.h>
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
	CButtonUI* m_btn_openFile;
	CListUI* m_list_selectButon;
	CTabLayoutUI* m_tab_main;
	CListUI* m_list_localmusic;

	void AddMusic(const CDuiString& title, const CDuiString& songer, const CDuiString& album, const CDuiString& time)
	{
		RECT padding = { 5, 0, 0, 0 };
		CListTextElementUI* listItem = new CListTextElementUI();
		m_list_localmusic->Add(listItem);
		listItem->SetPadding(padding);
		CString str;
		str.Format(TEXT("%d"), m_list_localmusic->GetCount());
		listItem->SetText(0, str);
		listItem->SetText(1, title);
		listItem->SetText(2, songer);
		listItem->SetText(3, album);
		listItem->SetText(4, time);
		
	}

	virtual void InitWindow()
	{
		//CButtonUI* Button = FindControlByName<CButtonUI>(TEXT("myname"));
		//Button->OnNotify += MakeDelegate(this, &CMainWindow::OnDestroy);
		m_btn_close = FindControlByName<CButtonUI>(TEXT("btn_close"));
		m_btn_min = FindControlByName<CButtonUI>(TEXT("btn_min"));
		m_btn_max = FindControlByName<CButtonUI>(TEXT("btn_max"));
		m_btn_openFile = FindControlByName<CButtonUI>(TEXT("btn_openaudiofile"));
		m_list_selectButon = FindControlByName<CListUI>(TEXT("list_selectButton"));
		m_tab_main = FindControlByName<CTabLayoutUI>(TEXT("tab_main"));
		m_list_localmusic = FindControlByName<CListUI>(TEXT("list_localmusic"));

		//RECT padding = { 5, 0, 0, 0 };
		////m_list_localmusic->SetItemTextPadding(padding);
		////m_list_localmusic->SetItemTextColor(0xffffffff);
		//for (int i = 0; i < 10; i++)
		//{
		//	CListTextElementUI* listItem = new CListTextElementUI();
		//	m_list_localmusic->Add(listItem);
		//	listItem->SetPadding(padding);
		//	listItem->SetText(0, TEXT("可爱1"));
		//	listItem->SetText(1, TEXT("可爱2"));
		//	listItem->SetText(2, TEXT("可爱3"));
		//	listItem->SetText(3, TEXT("可爱4"));
		//	listItem->SetText(4, TEXT("可爱5"));
		//}
		

		m_btn_min->OnNotify += MakeDelegate(this, &CMainWindow::OnBtnMinClicked, _T("click"));
		m_btn_max->OnNotify += MakeDelegate(this, &CMainWindow::OnBtnMaxClicked, _T("click"));
		m_btn_close->OnNotify += MakeDelegate(this, &CMainWindow::OnBtnCloseClicked, _T("click"));
		m_btn_openFile->OnNotify += MakeDelegate(this, &CMainWindow::OnBtnOpenFileClicked, _T("click"));

		/*CMusicPlayer* musicPlayer = CMusicPlayer::Get();
		string filename1 = "山崎惠理——《Starlight》（昴宿七星 ED） - 1.202206031532_x264(Av639680153,P1).mp3";
		musicPlayer->AddNewSound(filename1.c_str());
		musicPlayer->Play2D(filename1.c_str());*/
	}

	virtual LPCTSTR GetWindowClassName()const
	{
		return TEXT("MAINWINDOW");
	}

	virtual CDuiString GetSkinFile()
	{
		return CDuiString(TEXT("XML\\MainWindow.xml"));
	}

	virtual void Notify(TNotifyUI& msg)
	{
		if (msg.sType == DUI_MSGTYPE_ITEMSELECT)
		{
			if (msg.pSender->GetName() == TEXT("list_selectButton"))
			{
				CListUI* pList = (CListUI*)msg.pSender;
				int item = pList->GetCurSel();
				if (item > -1)
				{
					m_tab_main->SelectItem(item);
				}
			}
		}
		else if (msg.sType == DUI_MSGTYPE_ITEMSELECT)
		{
			if (msg.pSender == m_list_localmusic)
			{
				int curSel = m_list_localmusic->GetCurSel();
				CListTextElementUI* item = (CListTextElementUI*)m_list_localmusic->GetItemAt(curSel);
				if (item)
				{
					CStringA fileName = item->GetText(1);
					CMusicPlayer* musicPlayer = CMusicPlayer::Get();
					musicPlayer->Stop();
					musicPlayer->Play2D(fileName.GetString());
				}
			}
		}
	}

	virtual void OnDestroy()
	{
		CWindowImplBase::OnDestroy();
	}

private:
	bool OnBtnOpenFileClicked(TNotifyUI* pTNotifyUI, LPARAM lParam, WPARAM wParam)
	{
		COpenFileDialogUI fileDialog(m_hWnd);
		fileDialog.SetTitle(TEXT("打开音乐"));
		fileDialog.SetFileFilter(TEXT("All File\0*.*\0"));
		if (fileDialog.Open())
		{
			CMusicPlayer* musicPlayer = CMusicPlayer::Get();
			CStringA fileName = fileDialog.GetFileName();
			musicPlayer->AddNewSound(fileName.GetString());
			musicPlayer->Stop();
			musicPlayer->Play2D(fileName.GetString());
			AddMusic(fileDialog.GetFileName(), TEXT(""), TEXT(""), TEXT("00:00"));
		}
		return true;
	}

	bool CMainWindow::OnBtnMinClicked(TNotifyUI* pTNotifyUI, LPARAM lParam, WPARAM wParam)
	{
		ShowMinimized();
		return true;
	}

	bool CMainWindow::OnBtnMaxClicked(TNotifyUI* pTNotifyUI, LPARAM lParam, WPARAM wParam)
	{
		//normalimage="XML\btn_caption_max_normal.png" hotimage="XML\btn_caption_max_hot.png" pushedimage="XML\btn_caption_max_pushed.png"
		if (IsMaximized())
		{
			Show();
			m_btn_max->SetNormalImage(TEXT("XML\\btn_caption_max_normal.png"));
			m_btn_max->SetHotImage(TEXT("XML\\btn_caption_max_hot.png"));
			m_btn_max->SetPushedImage(TEXT("XML\\btn_caption_max_pushed.png"));
			
		}
		else
		{
			ShowMaximized();
			m_btn_max->SetNormalImage(TEXT("XML\\btn_caption_max2_normal.png"));
			m_btn_max->SetHotImage(TEXT("XML\\btn_caption_max2_hot.png"));
			m_btn_max->SetPushedImage(TEXT("XML\\btn_caption_max2_pushed.png"));
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

