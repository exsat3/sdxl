// MyDialog.cpp: 实现文件
//

#include "pch.h"
#include "sdxl.h"
#include "MyDialog.h"
#include "afxdialogex.h"
#include "../Detours-master/include/detours.h"

#pragma comment(lib,"../Detours-master/lib.X64/detours.lib")

// MyDialog 对话框

IMPLEMENT_DYNAMIC(MyDialog, CDialog)

MyDialog::MyDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

MyDialog* MyDlg = nullptr;
BOOL MyDialog::OnInitDialog()
{	
	DetourTransactionBegin();
	MyDlg = this;
	return TRUE;
}

MyDialog::~MyDialog()
{
}

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MyDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &MyDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &MyDialog::OnBnClickedButton2)
END_MESSAGE_MAP()


// MyDialog 消息处理程序
void test()    //类外调用
{
	CString str = L"修改";
	//MyDlg->GetDlgItem(IDC_EDIT1)->SetWindowTextW(str);
	//MessageBox(nullptr,str, 0, MB_OK);
	CButton* cb = (CButton*)MyDlg->GetDlgItem(IDC_BUTTON1);
	cb->SetWindowTextW(str);
}



void MyDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(str);
	MessageBox(str,0,MB_OK);

}


void MyDialog::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	test();
}
