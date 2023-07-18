# Duilib_Rain


基于Duilib修改的Dui库

文档位于docs目录下
库位于Duilib_Rain目录下




## 如何使用
1、编译Duilib_Rain
将编译出来的Dll和lib包含到自己的工程目录下


2、新建类CMainWindow，产生头文件MainWindow.h和源文件MainWindow.cpp

头文件MainWindow.h声明如下：

#pragma once
#include <Duilib.h>
using namespace Duilib;
class CMainWindow : public CWindowImplBase
{
public:
	CMainWindow();
	~CMainWindow();

	virtual CDuiString GetSkinFile();

	virtual LPCTSTR GetWindowClassName()const;

    //在这里对控件进行初始化，比如添加事件
	virtual void InitWindow();

    //窗口销毁时触发该函数
	virtual LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL& bHandled);
};

源文件MainWindow.cpp声明如下

#include "stdafx.h"
#include "MainWindow.h"

Duilib::CDuiString CMainWindow::GetSkinFile()
{
	return TEXT("xml\\MainWindow.xml");         //返回路径
}

CMainWindow::CMainWindow()
{
}

CMainWindow::~CMainWindow()
{
}

void CMainWindow::InitWindow()
{

}

LRESULT CMainWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	if (uMsg == WM_DESTROY)
	{
		::PostQuitMessage(0);
		return 0;
	}
	
	return 0;
}

3、在main函数添加以下代码：

#include "MainWindow.h"
int main(int argc, char** argv)
{
	DuiLib::CApplication* app = DuiLib::CApplication::Get();
	if (!app->Init())
	{
		return -1;
	}
	CMainWindow mainWindow;
	mainWindow.Create(NULL, TEXT(""), UI_WNDSTYLE_FRAME, 0L, 0, 0, 1320, 780);
	mainWindow.CenterWindow();
	mainWindow.ShowWindow();
	return app->Run();
}


4、在程序目录下创建一个xml文件夹，并在下面创建一个文件叫MainWindow.xml，加入如下代码：

<?xml version="1.0" encoding="UTF-8"?>
<Window size="1300,760" caption="0,0,0,30" sizebox="6,6,6,6">
    <VerticalLayout bkimage="me.jpg">
    </VerticalLayout>
</Window>


5、编译代码，然后打开，会发现窗口显示了出来，并在中间绘制了me.jpg这张图片
这里的xml其实就是用来描述窗口属性及其下面的控件的，XML内必须使用<Window>标签
来作为Root标签，可以在中间增加窗口属性，比如size就是窗口的大小，我要设置窗口大小
为1300&*760的大小，那么就size="1300,760"

Window中间的标签则是控件了，关于控件的属性可以查看docs下的属性列表
而标签就是控件，比如按钮控件：
<Button width="120" height="30"/>



