//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "ReadingThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ReadingThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
using namespace std;
__fastcall ReadingThread::ReadingThread(WCHAR *path, bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	error_code = 0;
	drive = new NTFSFileSystem(path, &error_code);
	if (error_code != 0) {
		WCHAR error_message[100];
		swprintf_s(error_message, 100, L"Ошибка открытия файловой системы (%i)", error_code);
		MessageBoxW(NULL, error_message, L"Ошибка!", MB_OK );
	}
}
//---------------------------------------------------------------------------
void __fastcall ReadingThread::Execute()
{
	//---- Place thread code here ----
	if (error_code == 0) {
		DWORD bytes_per_cluster = drive->GetBytesPerCluster();
		ULONGLONG clusters_count = drive->GetClustersCount();
		BYTE *cluster_data = new BYTE[bytes_per_cluster];
        searching_thread = new SearchingThread(cluster_data, bytes_per_cluster, false);
		for (__int64 cluster = 0; cluster < clusters_count; cluster++) {

			drive->ReadClusters(cluster, 1, cluster_data);
            MainWindow->lblCurrentClusterNumber->Caption = cluster;
			searching_thread->BufferReadyEvent->SetEvent();
			while(searching_thread->BufferCopiedEvent->WaitFor(WaitDelayMs) != wrSignaled){}
			searching_thread->

			if (Terminated)
				break;
            delete cluster_data;
		}
	}
	searching_thread->Terminate();
}
//---------------------------------------------------------------------------
