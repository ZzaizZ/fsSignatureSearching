﻿//---------------------------------------------------------------------------
#include <System.hpp>
#pragma hdrstop
#include "main_window.h"
#include "ReadingThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace std;
ReadingThread::ReadingThread(WCHAR *path, bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	error_code = 0;
	drive = new NtfsFS(path, &error_code);
	if (error_code != 0) {
		WCHAR error_message[100];
		swprintf_s(error_message, 100, L"Ошибка при открытии файловой системы: (%i)", error_code);
		MessageBoxW(NULL, error_message, L"Ошибка!", MB_OK );
        this->Terminate();
	}
	else
	{
        clusters_count = drive->GetClustersCount();
    	MainWindow->lblStatusBar->Caption = clusters_count;
    }

}
//---------------------------------------------------------------------------
IndexedIterator* ReadingThread::ChoiseIterator()
{
	if (MainWindow->radAll->Checked)
		return new NtfsClusterIterator(drive);
	else if (MainWindow->radRange->Checked)
		return new RangeClustersDec(StrToInt64(MainWindow->tedStartCluster->Text),
		StrToInt64(MainWindow->tedStopCluster->Text),
		new NtfsClusterIterator(drive));
}
//---------------------------------------------------------------------------
void __fastcall ReadingThread::Execute()
{
	SearchingThread *searching;
    MainWindow->pbSearchingStatus->Position = 0;
	if (error_code == 0) {
		DWORD bytes_per_cluster = drive->GetBytesPerCluster();
        MainWindow->lblStatusBar->Caption = L"Идёт поиск...";
		MainWindow->lblTotalClustersCount->Caption = clusters_count - 1;
		searching = new SearchingThread(&cluster_data, bytes_per_cluster, false);
		__int64 last_cluster = 0;

		IndexedIterator *it = ChoiseIterator();

		for (it->First(); !it->IsDone(); it->Next())
        {
			__int64 cluster = it->CurrentIndex();
			cluster_data = it->CurrentItem();
			searching->BufferReadyEvent->SetEvent();
			if (cluster % 1000 == 0) {
				MainWindow->lblCurrentClusterNumber->Caption = cluster;
				MainWindow->pbSearchingStatus->Position = 100 * cluster / (clusters_count - 1);
			}
			while(searching->BufferCopiedEvent->WaitFor(2000) != wrSignaled){}
			searching->SetCurrentCluster(cluster);

			searching->BufferCopiedEvent->ResetEvent();
//
			if (Terminated)
				break;
			last_cluster = cluster;
            bool tmp = it->IsDone();
		}
		MainWindow->lblCurrentClusterNumber->Caption = last_cluster;
		MainWindow->pbSearchingStatus->Position = 100 * last_cluster / (clusters_count - 1);
		searching->Terminate();
        delete it;
	}
}
//---------------------------------------------------------------------------
