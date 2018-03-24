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
    SearchingThread *searching_thread;
	int error_code;
protected:
	void __fastcall Execute();
public:
	__fastcall ReadingThread(WCHAR *path, bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
