// MyDialog.cpp: 实现文件
//

#include "pch.h"
#include "sdxl.h"
#include "MyDialog.h"
#include "afxdialogex.h"
#include<WinSock2.h>
#include "../Detours-master/include/detours.h"

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"../Detours-master/lib.X64/detours.lib")

// MyDialog 对话框
IMPLEMENT_DYNAMIC(MyDialog, CDialog)

MyDialog::MyDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

int (WINAPI* Oldsend)(
	_In_ SOCKET s,
	_In_reads_bytes_(len) const char FAR* buf,
	_In_ int len,
	_In_ int flags
	) = send;

int (WINAPI* Oldrecv)(
	_In_ SOCKET s,
	_Out_writes_bytes_to_(len, return) __out_data_source(NETWORK) char FAR* buf,
	_In_ int len,
	_In_ int flags
	) = recv;

int MySend(int s,char* buf,int len,int flags)
{	
	//我们需要处理封包的代码
	return Oldsend(s, buf, len, flags);
}

int MyRecv(int s, char* buf, int len, int flags)
{
	//我们需要处理封包的代码
	return Oldrecv(s, buf, len, flags);
}

MyDialog* MyDlg = nullptr;
BOOL MyDialog::OnInitDialog()
{	
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)Oldsend, MySend);
	DetourAttach(&(PVOID&)Oldrecv, MyRecv);
	DetourTransactionCommit();
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
