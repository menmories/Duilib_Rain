#ifndef __UICHILDLAYOUT_H__
#define __UICHILDLAYOUT_H__

#pragma once

namespace Duilib
{
	class DUILIB_API CChildLayoutUI : public CContainerUI
	{
	public:
		CChildLayoutUI();

		void Init();
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void SetChildLayoutXML(CDuiString pXML);
		Duilib::CDuiString GetChildLayoutXML();
		virtual LPVOID GetInterface(LPCTSTR pstrName);
		virtual LPCTSTR GetClass() const;

	private:
		Duilib::CDuiString m_pstrXMLFile;
	};
} // namespace Duilib
#endif // __UICHILDLAYOUT_H__
