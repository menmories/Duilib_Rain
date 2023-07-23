#ifndef DUILIB_OPENFILEDIALOG_H
#define DUILIB_OPENFILEDIALOG_H

#include "stdafx.h"


namespace Duilib
{
	class DUILIB_API COpenFileDialogUI
	{
	public:
		COpenFileDialogUI(HWND hParent);
		~COpenFileDialogUI();

		void SetFileFilter(const CDuiString& filter);

		void SetTitle(const CDuiString& title);

		virtual bool Open();

		TCHAR* GetFileName()const;
	protected:
		TCHAR* m_szFileName;
		TCHAR* m_szTitle;
		HWND m_hWndParent;
		CDuiString m_fileFilter;
	};


	class DUILIB_API CSaveFileDialogUI : public COpenFileDialogUI
	{
	public:
		CSaveFileDialogUI(HWND hParent);
		~CSaveFileDialogUI();
		virtual bool Open();
	};
}

#endif // DUILIB_OPENFILEDIALOG_H__
