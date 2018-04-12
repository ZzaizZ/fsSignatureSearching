//
// Created by zzaizz on 11.04.18.
//

#include "NTFSFileSystem.h"
#include <cwchar>
#include <iostream>

using namespace std;

FileSystem::FileSystem(const WCHAR *p, int *error_code)
{
    file_handle = 0;
    file_handle = CreateFile(p, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file_handle == INVALID_HANDLE_VALUE)
        *error_code = 1;
}

//------------------------------------
//          FsNTFS
//----------------------------------
NtfsFS::NtfsFS(const WCHAR *p, int *error_code)
    :FileSystem(p, error_code)
{
    HANDLE file_handle = FsHandle();
	if (file_handle != INVALID_HANDLE_VALUE)
	{
        ReadBootRecord(data_buffer);
        mbr = (NTFS_BootRecord*)data_buffer;
        cout << data_buffer[3] << endl;
        cout << mbr->signature;
		SHORT bytes_per_sector = ( mbr->bytes_per_sector );
        BYTE sector_per_cluster = (mbr->sector_per_cluster);
        bytes_per_cluster = bytes_per_sector * sector_per_cluster;
        is_NTFS = CheckNTFS();
        if (is_NTFS) { //// ÇÀÌÅÍÈÒÜ ÍÀ ÍÅ!!!!!!!!!!!!!!!
            *error_code = 200;
        }
        else
            *error_code = 0;
    }
}

DWORD NtfsFS::ReadBootRecord(BYTE *data_buffer)
{
    ULONGLONG start_offset = 0;
    LARGE_INTEGER sector_offset;
    sector_offset.QuadPart = start_offset;
    unsigned long current_position = SetFilePointer(
            FsHandle(),
            sector_offset.LowPart,
            &sector_offset.HighPart,
            FILE_BEGIN
    );
    if(current_position != sector_offset.LowPart)
    {
        return GetLastError() + 1000;
    }
    DWORD bytes_to_read = 512;
    DWORD bytes_read;
    bool read_result = (bool)ReadFile(FsHandle(), data_buffer, bytes_to_read, &bytes_read, NULL);
    if(!read_result || bytes_read != bytes_to_read)
    {
        return GetLastError() + 10;
    }

    return GetLastError();
}

bool NtfsFS::CheckNTFS()
{
    if( mbr->signature == 0x4e54465320202020 )
        return TRUE;
    else
        return FALSE;
}

ULONGLONG NtfsFS::GetClustersCount()
{
	ULONGLONG sbv = mbr->sectors_by_volume;
	BYTE spc = mbr->sector_per_cluster;
	ULONGLONG res = sbv/spc;
	return res;
}

Cluster NtfsFS::ReadClusters(ULONGLONG start_cluster, DWORD number_of_clusters, int *error_code)
{
    Cluster read_clusters;
    ULONGLONG start_offset = start_cluster*bytes_per_cluster;
    LARGE_INTEGER sector_offset;
    sector_offset.QuadPart = start_offset;
    unsigned long currentPosition = SetFilePointer(FsHandle(),
                                                   sector_offset.LowPart,
                                                   &sector_offset.HighPart,
                                                   FILE_BEGIN);
    if(currentPosition != sector_offset.LowPart)
        *error_code = (int)GetLastError()+2000;
    else
    {
        DWORD bytes_to_read = number_of_clusters * bytes_per_cluster;
        DWORD bytes_read;
        read_clusters.resize(bytes_to_read);
        bool read_result = (bool)ReadFile(FsHandle(), &read_clusters[0], bytes_to_read, &bytes_read, NULL);
        if (!read_result || bytes_read != bytes_to_read)
            *error_code = (int)GetLastError() + 20;
    }
    *error_code = (int)GetLastError();
    return read_clusters;
}

Cluster NtfsFS::ReadClusters(ULONGLONG start_cluster, DWORD number_of_clusters)
{
    Cluster read_clusters;
    ULONGLONG start_offset = start_cluster*bytes_per_cluster;
    LARGE_INTEGER sector_offset;
    sector_offset.QuadPart = start_offset;
    unsigned long currentPosition = SetFilePointer(FsHandle(),
                                                   sector_offset.LowPart,
                                                   &sector_offset.HighPart,
                                                   FILE_BEGIN);
    if(currentPosition != sector_offset.LowPart)
        return read_clusters;
    else
    {
        DWORD bytes_to_read = number_of_clusters * bytes_per_cluster;
        DWORD bytes_read;
        read_clusters.resize(bytes_to_read);
        bool read_result = (bool)ReadFile(FsHandle(), &read_clusters[0], bytes_to_read, &bytes_read, NULL);
        if (!read_result || bytes_read != bytes_to_read)
            return read_clusters;
    }
    return read_clusters;
}

