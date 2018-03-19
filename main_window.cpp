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
	sqlite_signature = "SQLite format 3";
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
		NTFSFileSystem device(file_handle, &error_code);
		DWORD result;
        BYTE buffer[4096];
		result = device.ReadClusters(file_handle, (ULONGLONG)0, (DWORD)1, buffer);
		bool found = this->SearchBySignature(sqlite_signature, buffer);
		if (found)
			lblStatusBar->Caption = "FOUND!";
		else
			lblStatusBar->Caption = sizeof(sqlite_signature)/sizeof(*sqlite_signature);
		
	}
    CloseHandle(file_handle);
}
//---------------------------------------------------------------------------
bool TMainWindow::SearchBySignature(BYTE *sig, BYTE *cluster_data)
{
	unsigned int sig_length = sizeof(sig)/sizeof(*sig);
	unsigned int cluster_length = sizeof(cluster_data)/sizeof(*cluster_data);
	if (sig_length > cluster_length)
	{
        return false;
	}
	for (unsigned int iter = 0; iter < sig_length; iter++)
	{
		if (sig[iter] == cluster_data[iter])
		{
            continue;
		}
		else
			return false;
	}
	return true;
}


