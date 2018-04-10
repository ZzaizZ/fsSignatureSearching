//---------------------------------------------------------------------------

#ifndef IteratorH
#define IteratorH
#include "SearchingThread.h"
//---------------------------------------------------------------------------
#include <windows.h>
#include "NTFSFileSystem.h"
using namespace std;
//---------------------------------------------------------------------------
template <class Item>
class Iterator
{
	public:
		virtual void First() = 0;
		virtual void Next() = 0;
		virtual bool IsDone() = 0;
		virtual Item CurrentItem() = 0;
	protected:
		Iterator() {};
};class IndexedIterator : public Iterator<BYTE*>{    public:
		virtual void First() = 0;
		virtual void Next() = 0;
		virtual bool IsDone() = 0;
		virtual BYTE* CurrentItem() { return NULL; }
		virtual __int64 CurrentIndex() {};
	protected:
		IndexedIterator() {};
};class ClusterIterator : public IndexedIterator{	public:
		void First();
		void Next();
		bool IsDone();
		BYTE* CurrentItem(BYTE *data_buffer);
		ClusterIterator(NTFSFileSystem *drive);
		__int64 CurrentIndex() { return current_cluster; }
	private:
    	NTFSFileSystem *drive;
		__int64 container_size;
		__int64 current_cluster;

};#endif
