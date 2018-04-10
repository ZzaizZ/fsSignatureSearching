//---------------------------------------------------------------------------
#ifndef ThreadSearchH
#define ThreadSearchH
#pragma hdrstop

#include "Iterator.h"
#include <string>
//---------------------------------------------------------------------------
#pragma package(smart_init)

ClusterIterator::ClusterIterator(NTFSFileSystem *drive)
{
	container_size = drive->GetClustersCount();
	this->drive = drive;
}

void ClusterIterator::First()
{
    current_cluster = 0;
}

void ClusterIterator::Next()
{
    current_cluster++;
}

bool ClusterIterator::IsDone()
{
	return (current_cluster >= container_size);
}

BYTE* ClusterIterator::CurrentItem(BYTE *data_buffer)
{
	drive->ReadClusters(current_cluster, 1, data_buffer);
    return data_buffer;
}
#endif
