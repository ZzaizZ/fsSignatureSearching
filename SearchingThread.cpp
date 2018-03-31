//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
#include "main_window.h"
#include "SearchingThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SearchingThread::SearchingThread(BYTE *data, DWORD cluster_size,  bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	cluster_data = data;
	this->cluster_size = cluster_size;
	data_buffer.resize(cluster_size);
	BufferReadyEvent  = new TEvent(NULL, true, false,"",false);
	BufferCopiedEvent = new TEvent(NULL, true, false,"",false);

	BYTE *sig;
	// SQLite format 3
	sig = "\x53\x51\x4C\x69\x74\x65\x20\x66\x6F\x72\x6D\x61\x74\x20\x33\x00";
	signatures.push_back(sig);
	// mp3
	sig = "\x49\x44\x33";
	signatures.push_back(sig);
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
    Synchronize(&CompleteSearch);
}
void SearchingThread::SetCurrentCluster(ULONGLONG cluster)
{
    current_cluster = cluster;
}
//---------------------------------------------------------------------------
void SearchingThread::CopyData()
{
	memcpy(&data_buffer[0], cluster_data, cluster_size);
}
//---------------------------------------------------------------------------
void SearchingThread::SearchData()
{
	for (current_sig = signatures.begin(); current_sig != signatures.end(); current_sig++) {
		bool matchFound = false;
		unsigned int sig_length = sizeof(*current_sig)/sizeof(**current_sig);
		if (sig_length > cluster_size)
		{
			matchFound = false;
			continue;
		}
		else
		{
			unsigned int flag = 0;
			for (unsigned int iter = 0; iter < sig_length; iter++)
			{
				if ((*current_sig)[iter] == data_buffer[iter])
					flag++;
				else{

                    break;
				}
			}
			if (flag == sig_length)
				matchFound = true;
		}
		if(matchFound)
		{
			Synchronize(&AddMatch);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall SearchingThread::AddMatch()
{
    PVirtualNode new_node = MainWindow->vstFindingSectors->AddChild(MainWindow->vstFindingSectors->RootNode);
	SearchCoincidence *node_data = (SearchCoincidence*)MainWindow->vstFindingSectors->GetNodeData(new_node);
	node_data->cluster_number = current_cluster;
	node_data->signature = *current_sig;
}
//---------------------------------------------------------------------------
void __fastcall SearchingThread::CompleteSearch()
{
	Application->MessageBoxW(L"Поиск окончен", L"Событие", MB_OK);
    MainWindow->lblStatusBar->Caption = L"Поиск окончен";
}
//---------------------------------------------------------------------------
