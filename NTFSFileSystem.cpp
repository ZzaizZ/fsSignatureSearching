//---------------------------------------------------------------------------

#pragma hdrstop

#include "NTFSFileSystem.h"
#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
NTFSFileSystem::NTFSFileSystem(WCHAR *drive_path, int *error_code)
{
	this->file_handle = 0;
	is_NTFS = false;
	file_handle = CreateFile(L"\\\\.\\J:", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file_handle == INVALID_HANDLE_VALUE)
	{
//		swprintf_s (error_message, 100, L"Ошибка при открытии файла. Код ошибки: %x", GetLastError());
		*error_code = 1; // код ошибки открытия файла
	}
	else
	{
		BYTE data_buffer[512];
		ReadBootRecord(data_buffer);
		mbr = (NTFS_BootRecord*)data_buffer;
		int bytes_per_sector = ( mbr->bytes_per_sector);
		int sector_per_cluster = (mbr->sector_per_cluster);
		bytes_per_cluster = bytes_per_sector * sector_per_cluster;
		is_NTFS = CheckNTFS();
		if (is_NTFS) {
			//swprintf_s(error_message, 100,L"На указанном диске не обранужено ФС NTFS");
			*error_code = 1; // код ошибки неправильной ФС
		}
		else
//			swprintf_s(error_message, 100,L"Открыт диск с системой NTFS");
			*error_code = 0; // код удачного открытия системы NTFS
	}

}
//---------------------------------------------------------------------------
NTFSFileSystem::~NTFSFileSystem()
{
    CloseHandle(file_handle);
    delete file_handle;
}
//---------------------------------------------------------------------------
DWORD NTFSFileSystem::ReadBootRecord(BYTE *data_buffer)
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
ULONGLONG NTFSFileSystem::GetClustersCount()
{
	return mbr->sectors_by_volume/mbr->sector_per_cluster;
}
// <------- testing method
DWORD NTFSFileSystem::GetBytesPerCluster()
{
	return bytes_per_cluster;
}
int NTFSFileSystem::ReadClusters(ULONGLONG start_cluster, DWORD number_of_clusters, BYTE *data_buffer)
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
//---------------------------------------------------------------------------
bool NTFSFileSystem::CheckNTFS()
{
	//0x202020205346544E
	if( mbr->signature == 0x4e544653202020 )
		return TRUE;
	else
        return FALSE;
}
