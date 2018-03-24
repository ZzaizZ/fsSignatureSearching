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
	WCHAR *drive_path = tedName->Text.c_str();
//    WCHAR error_message[100];
	int error_code;
	lblStatusBar->Caption = drive_path;
	NTFSFileSystem *drive = new NTFSFileSystem(drive_path, &error_code);
	lblStatusBar->Caption = error_code;
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
//---------------------------------------------------------------------------

