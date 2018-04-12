//---------------------------------------------------------------------------

#ifndef ThreadSearchH
#define ThreadSearchH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <vector>
#include <list>
#include <string>
using namespace std;
//---------------------------------------------------------------------------
typedef struct
{
	int id;
	string signature;
	string name;
} SignDataEntry;
//---------------------------------------------------------------------------
typedef vector<BYTE> Cluster;
//---------------------------------------------------------------------------
typedef struct
{
	__int64 cluster_number;
    const char* signature;
} SearchCoincidence;
//---------------------------------------------------------------------------
class SearchingThread : public TThread
{
private:
	Cluster *cluster_data;
    DWORD cluster_size;
	Cluster data_buffer;
	vector<SignDataEntry>::iterator current_sig;
	vector<SignDataEntry> signatures_db;
	void CopyData();
	void SearchData();
	void __fastcall AddMatch();
	void __fastcall CompleteSearch();
    ULONGLONG current_cluster;
protected:
	void __fastcall Execute();
public:
	__fastcall SearchingThread(Cluster *data, DWORD cluster_size,  bool CreateSuspended);
	TEvent *BufferReadyEvent;
	TEvent *BufferCopiedEvent;
    void SetCurrentCluster(ULONGLONG cluster);
};
//---------------------------------------------------------------------------
#endif
