//---------------------------------------------------------------------------

#ifndef ThreadSearchH
#define ThreadSearchH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <vector>
//---------------------------------------------------------------------------
using namespace std;
typedef struct
{
	__int64 cluster_number;
    BYTE *signature;
} SearchCoincidence;
class SearchingThread : public TThread
{
private:
	BYTE *cluster_data;
    DWORD cluster_size;
    vector<BYTE> data_buffer;
	void CopyData();
	void SearchData();
	void __fastcall AddMatch();
	void __fastcall CompleteSearch();
    ULONGLONG current_cluster;
protected:
	void __fastcall Execute();
public:
	__fastcall SearchingThread(BYTE *data, DWORD cluster_size, bool CreateSuspended);
	TEvent *BufferReadyEvent;
	TEvent *BufferCopiedEvent;
    void SetCurrentCluster(ULONGLONG cluster);
};
//---------------------------------------------------------------------------
#endif
