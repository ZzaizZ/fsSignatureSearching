//---------------------------------------------------------------------------

#pragma hdrstop

#include "NTFSFileSystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

NTFSFileSystem::NTFSFileSystem(HANDLE file_handle, DWORD *error_code)
{
	BYTE data_buffer[512];
	*error_code = this->ReadBootRecord(file_handle, data_buffer);
	mbr = (NTFS_BootRecord*)data_buffer;
	int bytes_per_sector = (0x01 << mbr->bytes_per_sector);
	int sector_per_cluster = (0x01 << mbr->sector_per_cluster);
	bytes_per_cluster = bytes_per_sector * sector_per_cluster;
	bool is_NTFS = this->CheckNTFS();
}

NTFSFileSystem::~NTFSFileSystem()
{
}

DWORD NTFSFileSystem::ReadBootRecord(HANDLE file_handle, BYTE *data_buffer)
{
	ULONGLONG start_offset = 0;
	LARGE_INTEGER sector_offset;
	sector_offset.QuadPart = start_offset;
	unsigned long current_position = SetFilePointer(
			file_handle,
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
	bool read_result = ReadFile(file_handle, data_buffer, bytes_to_read, &bytes_read, NULL);
	if(!read_result || bytes_read != bytes_to_read)
	{
		return GetLastError() + 10;
	}

	return GetLastError();
}

// ----> testing method
ULONGLONG NTFSFileSystem::GetFSSignature()
{
	 if (this->CheckNTFS())
		return (0x01 << mbr->signature);
	 else
        return 1234;
}
// <------- testing method

int NTFSFileSystem::ReadClusters(HANDLE file_handle, ULONGLONG start_cluster, DWORD number_of_clusters, BYTE *data_buffer)
{
	ULONGLONG start_offset = start_cluster*bytes_per_cluster;
	LARGE_INTEGER sector_offset;
	sector_offset.QuadPart = start_offset;
	unsigned long currentPosition = SetFilePointer(file_handle,
			sector_offset.LowPart,
			&sector_offset.HighPart,
			FILE_BEGIN
		);
	if(currentPosition != sector_offset.LowPart)
	{
		return GetLastError()+2000;
	}
	DWORD bytes_to_read = number_of_clusters*bytes_per_cluster;
	DWORD bytes_read;
	bool read_result = ReadFile(file_handle, data_buffer, bytes_to_read, &bytes_read, NULL);
	if(!read_result || bytes_read != bytes_to_read)
	{
		return GetLastError()+20;
	}

	return GetLastError();
}

bool NTFSFileSystem::CheckNTFS()
{
    if( mbr->signature != 0x202020205346544E )
		return FALSE;
	else
        return TRUE;
}
