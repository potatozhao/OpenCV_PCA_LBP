
// opencvMFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "opencvMFC.h"
#include "opencvMFCDlg.h"
#include "afxdialogex.h"
#include "CheckFace.h"
#include "LBP.h"
#include "PCA.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
CString GetDirectory();
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CopencvMFCDlg 对话框




CopencvMFCDlg::CopencvMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CopencvMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	imagepath1 = _T("");
	imagepath2 = _T("");
	lastnum = _T("");
}

void CopencvMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, imagepath1);
	DDX_Text(pDX, IDC_EDIT2, imagepath2);
	//  DDX_Control(pDX, IDC_EDIT3, lastnum);
	DDX_Text(pDX, IDC_EDIT3, lastnum);
}

BEGIN_MESSAGE_MAP(CopencvMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CopencvMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CopencvMFCDlg::OnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CopencvMFCDlg::OnClickedButton3)
END_MESSAGE_MAP()


// CopencvMFCDlg 消息处理程序

BOOL CopencvMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CopencvMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CopencvMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CopencvMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CopencvMFCDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat ImgFirst1;
	Mat ImgFirst2;
	Mat img;
	Mat ImgLast1;
	Mat ImgLast2;
	img = imread("111.bmp",0);
	//imagepath1 = "E:\\01.png";
	//imagepath2 = "E:\\05.png";
	PhotoCup(ImgFirst1,imagepath1);
	PhotoCup(ImgFirst2,imagepath2);
	ImageMain(img,ImgFirst1,ImgFirst2,ImgLast1,ImgLast2);
	lastnum = test(ImgLast1,ImgLast2).c_str();
	GetDlgItem(IDC_EDIT3)->SetWindowText(lastnum);
	//SetDlgItemText(hWinMain, IDC_EDIT3, lastnum);
}


void CopencvMFCDlg::OnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	imagepath1 = GetDirectory();
	UpdateData(false);
}


void CopencvMFCDlg::OnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	imagepath2 = GetDirectory();
	UpdateData(false);
}
CString GetDirectory()
{
	BROWSEINFO bi;
	char name[MAX_PATH];
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
	bi.pszDisplayName = name;
	bi.lpszTitle = "选择文件夹目录";
	bi.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_USENEWUI | BIF_BROWSEINCLUDEFILES | BIF_EDITBOX ;
	bi.lpfn = NULL;
	bi.lParam = NULL;
	bi.iImage = NULL;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if(idl == NULL)
		return "";
	CString strDirectoryPath;
	SHGetPathFromIDList(idl, strDirectoryPath.GetBuffer(MAX_PATH));
	strDirectoryPath.ReleaseBuffer();
	if(strDirectoryPath.IsEmpty())
		return "";
	//if(strDirectoryPath.Right(1)!="\\")
	//	strDirectoryPath+="\\";
	
	return strDirectoryPath;
}

