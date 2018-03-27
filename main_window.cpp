//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main_window.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
typedef struct
{
    __int64 cluster_number;
} EntryStruct;

TMainWindow *MainWindow;
//---------------------------------------------------------------------------
__fastcall TMainWindow::TMainWindow(TComponent* Owner)
	: TForm(Owner)
{
	sqlite_signature = "SQLite format 3";
	pbSearchingStatus->Max = 100;
    pbSearchingStatus->Position = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainWindow::btnSearchClick(TObject *Sender)
{
	//WCHAR *drive_path = tedName->Text.c_str();
	//int error_code;
	//lblStatusBar->Caption = drive_path;
	reading_thread = new ReadingThread(tedName->Text.c_str(), false);
}
//---------------------------------------------------------------------------
void __fastcall TMainWindow::vstFindingSectorsGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
	if (!Node) return;
	SearchCoincidence *node_data = (SearchCoincidence*)Sender->GetNodeData(Node);
	switch (Column)
	{
		case 0: CellText = node_data->cluster_number; break;
		case 1: CellText = (char *)node_data->signature; break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainWindow::btnStopClick(TObject *Sender)
{
    reading_thread->Terminate();
}
//---------------------------------------------------------------------------

