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
	NTFSFileSystem *drive;
    BYTE *cluster_data;
	int error_code;
    ULONGLONG clusters_count;
protected:
	void __fastcall Execute();
public:
	ReadingThread(WCHAR *path, bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
