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

class Fat32ClusterIterator : public IndexedIterator
{
public:
    void First() { current_cluster = 1; }
    void Next() { current_cluster++; }
    bool IsDone() { return (current_cluster >= container_size); }
    Cluster CurrentItem();
    ULONGLONG CurrentIndex() { return current_cluster; }
    Fat32ClusterIterator(FileSystem *drive);
private:
    FileSystem *drive;
    ULONGLONG container_size;
    ULONGLONG current_cluster;
};

class IndexedIteratorDecorator : public IndexedIterator
{
protected:
    IndexedIterator *it;
    IndexedIteratorDecorator() {};
    IndexedIteratorDecorator(IndexedIterator *it) { this->it = it; };
public:
    void First() { it->First(); }
    void Next() { it->Next(); }
    bool IsDone() { return it->IsDone(); }
    Cluster CurrentItem() { return it->CurrentItem(); }
    ULONGLONG CurrentIndex() { return it->CurrentIndex(); }
};

class RangeClustersDec : public IndexedIteratorDecorator
{
private:
    ULONGLONG start_cluster;
    ULONGLONG stop_cluster;
public:
    RangeClustersDec(ULONGLONG start_cluster, ULONGLONG stop_cluster, IndexedIterator *it);
    void First();
    void Next() { it->Next(); }
    bool IsDone() {return (it->CurrentIndex() > stop_cluster || it->IsDone()); }
    Cluster GetCurrent() { return it->CurrentItem(); }
    ULONGLONG GetCurrentIndex()  { return  it->CurrentIndex(); }
};

#endif //FILESYSTEM_ITERATOR_H

