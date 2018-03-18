//---------------------------------------------------------------------------

#pragma hdrstop

#include "NTFSFileSystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

NTFSFileSystem::NTFSFileSystem(HANDLE file_handle)
{
	BYTE *data_buffer[512];
	this->ReadSectors(file_handle, 0, 1, *data_buffer);
    mbr = (NTFS_BootRecord*)data_buffer;
}

NTFSFileSystem::~NTFSFileSystem()
{
}

int NTFSFileSystem::ReadSectors(HANDLE file_handle, ULONGLONG sector_position, DWORD number_of_sectors, BYTE *data_buffer)
{
	ULONGLONG start_offset = sector_position;
	LARGE_INTEGER sector_offset;
	sector_offset.QuadPart = start_offset;
	unsigned long currentPosition = SetFilePointer(file_handle,
			sector_offset.LowPart, &sector_offset.HighPart,
			FILE_BEGIN
		);
	if(currentPosition != sector_offset.LowPart)
	{
		return -2; // код ошибки неправильного задани€ позиции
	}
	DWORD bytes_to_read = 512*number_of_sectors;
	DWORD bytes_read;
	bool read_result = ReadFile(file_handle, data_buffer, bytes_to_read, &bytes_read, NULL);
	if(!read_result || bytes_read != bytes_to_read)
	{
		return -3; //код ошибки чтени€
	}

	return 0; //код успешного завершени€ чтени€
}

int NTFSFileSystem::ReadClusters(HANDLE file_handle, ULONGLONG start_cluster, DWORD number_of_clusters, BYTE *data_buffer)
{
}
