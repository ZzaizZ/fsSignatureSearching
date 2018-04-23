#include "Iterator.h"
#include <iostream>


NtfsClusterIterator::NtfsClusterIterator(FileSystem *drive)
{
	this->drive = drive;
	container_size = drive->GetClustersCount();
}

Cluster NtfsClusterIterator::CurrentItem()
{
    return drive->ReadClusters(current_cluster, (DWORD)1);
}

bool NtfsClusterIterator::IsDone()
{
	if (current_cluster >= container_size)
		return true;
	else
		return false;
}

Fat32ClusterIterator::Fat32ClusterIterator(FileSystem *drive)
{
    this->drive = drive;
	container_size = drive->GetClustersCount()-1;
}

Cluster Fat32ClusterIterator::CurrentItem()
{
    return drive->ReadClusters(current_cluster+1, (DWORD)1);
}

Ext4ClusterIterator::Ext4ClusterIterator(FileSystem *drive)
{
    this->drive = drive;
	container_size = drive->GetClustersCount();
}

Cluster Ext4ClusterIterator::CurrentItem()
{
	return drive->ReadClusters(current_cluster+1, (DWORD)1);
}

RangeClustersDec::RangeClustersDec(ULONGLONG start_cluster, ULONGLONG stop_cluster, IndexedIterator *it)
	:IndexedIteratorDecorator(it)
{
    this->start_cluster = start_cluster;
    this->stop_cluster = stop_cluster;
}

void RangeClustersDec::First()
{
    for (it->First(); !it->IsDone(); it->Next())
        if (it->CurrentIndex() == start_cluster)
            break;
}

