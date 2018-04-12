#ifndef FILESYSTEM_ITERATOR_H
#define FILESYSTEM_ITERATOR_H
//---------------------------------------------------------------------------
#include <windows.h>
#include <vector>
#include "NTFSFileSystem.h"
//---------------------------------------------------------------------------
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
};


class IndexedIterator : public Iterator<Cluster>
{
public:
    void First() = 0;
    void Next() = 0;
    bool IsDone() = 0;
    Cluster CurrentItem() = 0;
    virtual ULONGLONG CurrentIndex() = 0;
protected:
    IndexedIterator() : Iterator<Cluster>() {};
};

class NtfsClusterIterator : public IndexedIterator
{
public:
    void First() { current_cluster = 0; }
    void Next() { current_cluster++; }
    bool IsDone();
    Cluster CurrentItem();
    ULONGLONG CurrentIndex() { return current_cluster; }
	NtfsClusterIterator(FileSystem *drive);
private:
    FileSystem *drive;
    ULONGLONG container_size;
    ULONGLONG current_cluster;
};

#endif //FILESYSTEM_ITERATOR_H

