//---------------------------------------------------------------------------

#ifndef ReadingThreadH
#define ReadingThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>

#include "SearchingThread.h"
#include "Iterator.h"
//---------------------------------------------------------------------------
class ReadingThread : public TThread
{
private:
	FileSystem *drive;
    Cluster cluster_data;
	int error_code;
	ULONGLONG clusters_count;
	IndexedIterator* ChoiseIterator();
	FileSystem* ChoiseDriveFS(WCHAR *path, int *error_code);
protected:
	void __fastcall Execute();
public:
	ReadingThread(WCHAR *path, bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
