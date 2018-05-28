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
    virtual void First() = 0;
    virtual void Next() { current_cluster++; }
    virtual bool IsDone();
    Cluster CurrentItem() = 0;
    virtual ULONGLONG CurrentIndex() = 0;
protected:
    IndexedIterator() : Iterator<Cluster>() {};
	ULONGLONG container_size;
	ULONGLONG current_cluster;
};

class NtfsClusterIterator : public IndexedIterator
{
public:
    void First() { current_cluster = 0; }
    Cluster CurrentItem();
    ULONGLONG CurrentIndex() { return current_cluster; }
	NtfsClusterIterator(FileSystem *drive);
private:
    FileSystem *drive;

};

class Fat32ClusterIterator : public IndexedIterator
{
public:
    void First() { current_cluster = 1; }
    Cluster CurrentItem();
    ULONGLONG CurrentIndex() { return current_cluster; }
    Fat32ClusterIterator(FileSystem *drive);
private:
    FileSystem *drive;
};

class Ext4ClusterIterator : public IndexedIterator
{
public:
    void First() { current_cluster = 2; }
    Cluster CurrentItem();
    ULONGLONG CurrentIndex() { return current_cluster; }
    Ext4ClusterIterator(FileSystem *drive);
private:
    FileSystem *drive;
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

