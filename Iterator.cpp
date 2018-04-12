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


