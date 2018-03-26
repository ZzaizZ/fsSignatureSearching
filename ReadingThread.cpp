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
ReadingThread::ReadingThread(WCHAR *path, bool CreateSuspended)
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
    SearchingThread *searching;
	if (error_code == 0) {
		DWORD bytes_per_cluster = drive->GetBytesPerCluster();
		ULONGLONG clusters_count = drive->GetClustersCount();
		MainWindow->lblTotalClustersCount->Caption = clusters_count;
		cluster_data = new BYTE[bytes_per_cluster];
        searching = new SearchingThread(cluster_data, bytes_per_cluster, false);
		for (__int64 cluster = 0; cluster < clusters_count; cluster++) {

			drive->ReadClusters(cluster, 1, cluster_data);
			searching->BufferReadyEvent->SetEvent();

			while(searching->BufferCopiedEvent->WaitFor(2000) != wrSignaled){}

			MainWindow->lblCurrentClusterNumber->Caption = cluster;
			MainWindow->pbSearchingStatus->Position = 100*cluster/clusters_count;
			searching->SetCurrentCluster(cluster);

			searching->BufferCopiedEvent->ResetEvent();

			if (Terminated)
				break;
		}
		searching->Terminate();
		delete [] cluster_data;
	}
}
//---------------------------------------------------------------------------
