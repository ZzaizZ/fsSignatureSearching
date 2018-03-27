//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
#include "main_window.h"
#include "SearchingThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall SearchingThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall SearchingThread::SearchingThread(BYTE *data, DWORD cluster_size,  bool CreateSuspended)
	: TThread(CreateSuspended)
{
    FreeOnTerminate = true;

	cluster_data = data;
	this->cluster_size = cluster_size;
	data_buffer = new BYTE[cluster_size];

	BufferReadyEvent  = new TEvent(NULL, true, false,"",false);
	BufferCopiedEvent = new TEvent(NULL, true, false,"",false);
}
//---------------------------------------------------------------------------
void __fastcall SearchingThread::Execute()
{
	while (1){
		if(BufferReadyEvent->WaitFor(2000) == wrSignaled)
		{
			CopyData();

			BufferReadyEvent->ResetEvent();
			BufferCopiedEvent->SetEvent();

			SearchData();
		}
        if(Terminated) break;
	}
    MainWindow->lblStatusBar->Caption = L"Очистка памяти";
	delete BufferReadyEvent;
	delete BufferCopiedEvent;
	delete [] data_buffer;
    Synchronize(&CompleteSearch);
}
void SearchingThread::SetCurrentCluster(ULONGLONG cluster)
{
    current_cluster = cluster;
}
//---------------------------------------------------------------------------
void SearchingThread::CopyData()
{
	memcpy(data_buffer, cluster_data, cluster_size);
}
//---------------------------------------------------------------------------
void SearchingThread::SearchData()
{
	bool matchFound = false;
	BYTE *sig = "SQLite format 3";
	unsigned int sig_length = sizeof(sig)/sizeof(*sig);
	if (sig_length > cluster_size)
	{
		matchFound = false;
	}
	else
	{
        unsigned int flag = 0;
		for (unsigned int iter = 0; iter < sig_length; iter++)
		{
			if (sig[iter] == data_buffer[iter])
				flag++;
			else
				matchFound = false;
		}
		if (flag == sig_length)
			matchFound = true;
	}
	if(matchFound)
	{
		Synchronize(&AddMatch);
	}
}
//---------------------------------------------------------------------------
void __fastcall SearchingThread::AddMatch()
{
	PVirtualNode new_node = MainWindow->vstFindingSectors->AddChild(MainWindow->vstFindingSectors->RootNode);
	SearchCoincidence *node_data = (SearchCoincidence*)MainWindow->vstFindingSectors->GetNodeData(new_node);
	node_data->cluster_number = current_cluster;
	node_data->signature = "SQlite format 3";
}
//---------------------------------------------------------------------------
void __fastcall SearchingThread::CompleteSearch()
{
	Application->MessageBoxW(L"Поиск окончен", L"Событие", MB_OK);
    MainWindow->lblStatusBar->Caption = L"Поиск окончен";
}
//---------------------------------------------------------------------------
