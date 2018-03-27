//---------------------------------------------------------------------------

#ifndef ReadingThreadH
#define ReadingThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>

#include "SearchingThread.h"
//---------------------------------------------------------------------------
class ReadingThread : public TThread
{
private:
	NTFSFileSystem *drive;
    BYTE *cluster_data;
	int error_code;
protected:
	void __fastcall Execute();
public:
	ReadingThread(WCHAR *path, bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
