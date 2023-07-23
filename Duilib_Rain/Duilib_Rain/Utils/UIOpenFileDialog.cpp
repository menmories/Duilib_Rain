#include "stdafx.h"
#include "UIOpenFileDialog.h"

#define OFN_MAX_PATH 1024

Duilib::COpenFileDialogUI::COpenFileDialogUI(HWND hParent)
	: m_hWndParent(hParent)
{
	assert(hParent);
	m_szFileName = new WCHAR[OFN_MAX_PATH + 1];
	m_szTitle = new WCHAR[OFN_MAX_PATH + 1];
	_tcscpy(m_szTitle, TEXT("打开文件"));
	m_fileFilter = TEXT("All File\0*.*\0");
}

Duilib::COpenFileDialogUI::~COpenFileDialogUI()
{
	delete[] m_szFileName;
	delete[] m_szTitle;
}

void Duilib::COpenFileDialogUI::SetFileFilter(const CDuiString& filter)
{
	m_fileFilter = filter;
}

void Duilib::COpenFileDialogUI::SetTitle(const CDuiString& title)
{
	_tcscpy(m_szTitle, title.GetData());
}

bool Duilib::COpenFileDialogUI::Open()
{
	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof(OPENFILENAME));
	memset(m_szFileName, 0, sizeof(TCHAR) * (OFN_MAX_PATH + 1));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = m_hWndParent;
	ofn.hInstance = CPaintManagerUI::GetInstance();
	ofn.lpstrFilter = m_fileFilter.GetData();
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = m_szFileName;
	ofn.nMaxFile = OFN_MAX_PATH;
	ofn.lpstrFileTitle = m_szTitle;
	ofn.nMaxFileTitle = OFN_MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_EXPLORER;
	// 按下确定按钮
	return ::GetOpenFileName(&ofn) ? true : false;
}

TCHAR* Duilib::COpenFileDialogUI::GetFileName() const
{
	return m_szFileName;
}

Duilib::CSaveFileDialogUI::CSaveFileDialogUI(HWND hParent)
	: COpenFileDialogUI(hParent)
{
}

Duilib::CSaveFileDialogUI::~CSaveFileDialogUI()
{

}

bool Duilib::CSaveFileDialogUI::Open()
{
	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof(OPENFILENAME));
	memset(m_szFileName, 0, sizeof(TCHAR) * (OFN_MAX_PATH + 1));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = m_hWndParent;
	ofn.hInstance = CPaintManagerUI::GetInstance();
	ofn.lpstrFilter = m_fileFilter.GetData();
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = m_szFileName;
	ofn.nMaxFile = OFN_MAX_PATH;
	ofn.lpstrFileTitle = m_szTitle;
	ofn.nMaxFileTitle = OFN_MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_EXPLORER;
	// 按下确定按钮
	return ::GetSaveFileName(&ofn) ? true : false;
}
