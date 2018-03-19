//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main_window.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TMainWindow *MainWindow;
//---------------------------------------------------------------------------
__fastcall TMainWindow::TMainWindow(TComponent* Owner)
	: TForm(Owner)
{
	sqlite_signature = 0x53514C69746520666F726D6174203300;
}
//---------------------------------------------------------------------------
void __fastcall TMainWindow::btnSearchClick(TObject *Sender)
{
	WCHAR *path = tedName->Text.c_str();
	lblStatusBar->Caption = path;
	HANDLE file_handle;
	file_handle = CreateFileW(path,
					GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
					NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
					);
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		WCHAR buf[50];
		swprintf(buf, 50, L"Ошибка при открытии файла. Код ошибки: %x", GetLastError());
		lblStatusBar->Caption = buf;
	}
	else
	{
		lblStatusBar->Caption = "OK";
		DWORD error_code;
		NTFSFileSystem device(path, &error_code);
        lblStatusBar->Caption = error_code;
	}
    CloseHandle(file_handle);
}
//---------------------------------------------------------------------------

