//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

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

__fastcall SearchingThread::SearchingThread(BYTE *data, DWORD cluster_size, bool CreateSuspended)
	: TThread(CreateSuspended)
{
	cluster_data = data;
	this->cluster_size = cluster_size;
	databuffer = new BYTE[clusterSize];
    FreeOnTerminate = true;
	BufferReadyEvent  = new TEvent(NULL, true, false,"",false);
	BufferCopiedEvent = new TEvent(NULL, true, false,"",false);
}
//---------------------------------------------------------------------------
void __fastcall SearchingThread::Execute()
{
	while (1){
		if(BufferReadyEvent->WaitFor(WaitDelayMs) == wrSignaled)
		{
			CopyData();

			BufferReadyEvent->ResetEvent();
			BufferCopiedEvent->SetEvent();

			SearchData();
		}
        if(Terminated) break;
	}
	delete BufferReadyEvent;
	delete BufferCopiedEvent;
	delete[] data_buffer;
    Synchronize(&CompleteSearch);
}
//---------------------------------------------------------------------------
void SearchThread::CopyData()
{
	memcpy(data_buffer, cluster_buffer, cluster_size);
}
//---------------------------------------------------------------------------
void SearchThread::SearchData()
{
	bool matchFound = false;
    BYTE *sig = 0x53514C69746520666F726D6174203300;
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
				flag++:
			else
				matchFound = false;
		}
		if (flag == sig_length) 
			matchFound = false;
	}
	// memcmp


	if(matchFound)
	{
		Synchronize(&AddMatch);
	}
}
//---------------------------------------------------------------------------
void __fastcall SearchThread::AddMatch()
{
	PVirtualNode newNode = MainWindow->vstFindingSectors->AddChild(MainWindow->ResultTree->RootNode);
}
//---------------------------------------------------------------------------
void __fastcall SearchThread::CompleteSearch()
{
	Application->MessageBoxW(L"����� �������", L"�������", MB_OK);
}
//---------------------------------------------------------------------------
