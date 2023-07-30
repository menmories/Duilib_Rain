#ifndef __UI_TABLE_H__
#define __UI_TABLE_H__


namespace Duilib
{
	class ITableHeader
	{
		virtual void AddItem() = 0;
	};

	class ITableView
	{
		virtual void AddItem() = 0;
	};




}	//namespace Duilib

#endif	//__UI_TABLE_H__

