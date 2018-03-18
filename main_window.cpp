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
}
//---------------------------------------------------------------------------
void __fastcall TMainWindow::btnSearchClick(TObject *Sender)
{
	WCHAR *path = tedName->Text.c_str();
	lblStatusBar->Caption = path;
	HANDLE file_handle = CreateFileW(path,
					GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE,
					NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
					);
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		lblStatusBar->Caption = "Ошибка при открытии файла"; // код ошибки открытия файла
	}
	else
	{
        lblStatusBar->Caption = "OK";
		NTFSFileSystem device(path);
	}
    CloseHandle(file_handle);
}
//---------------------------------------------------------------------------

