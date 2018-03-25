//---------------------------------------------------------------------------

#ifndef ReadingThreadH
#define ReadingThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "main_window.h"
#include "SearchingThread.h"
//---------------------------------------------------------------------------
class ReadingThread : public TThread
{
private:
	NTFSFileSystem *drive;
	int error_code;
protected:
	void __fastcall Execute();
public:
	ReadingThread(WCHAR *path, bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif