#ifndef __Duilib_APPLICATION_H__
#define __Duilib_APPLICATION_H__

#pragma once

namespace Duilib
{
	class DUILIB_API CApplication
	{
	public:
		static CApplication* Get();

		bool Init();

		int Run();
	private:

		void Destroy();

		CApplication();
		~CApplication();

	};
}
#endif // UITimer_h__
