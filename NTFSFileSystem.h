#ifndef FILESYSTEM_FILESYSTEM_H
#define FILESYSTEM_FILESYSTEM_H
//---------------------------------------------------------------------------
#include <windows.h>
#include <vector>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
typedef vector<BYTE> Cluster;
//---------------------------------------------------------------------------
class FileSystem
{
private:
    HANDLE file_handle;
protected:
    HANDLE FsHandle() { return file_handle; }
    ULONGLONG total_clusters;
    DWORD bytes_per_cluster;
public:
    virtual ULONGLONG GetClustersCount() = 0;
    virtual DWORD GetBytesPerCluster() { return bytes_per_cluster; }
    virtual Cluster ReadClusters(ULONGLONG start_cluster, DWORD number_of_clusters, int *error_code) = 0;
    virtual Cluster ReadClusters(ULONGLONG start_cluster, DWORD number_of_clusters) = 0;
    FileSystem(const WCHAR *p, int *error_code);
};
//------------------------------------
//          FsNTFS
//------------------------------------
#pragma pack(push, 1)
typedef struct
{
    BYTE padding_1[3];
    ULONGLONG signature;
    SHORT bytes_per_sector;
    BYTE sector_per_cluster;
    BYTE padding_2[7];
    BYTE device_type;
    BYTE padding_3[18];
    ULONGLONG sectors_by_volume;
    ULONGLONG mft_lcn;
    ULONGLONG mft_lcn_copy;
    BYTE clusters_per_mft;
    BYTE padding_4[3];
    BYTE clusters_per_index;
    BYTE padding_5[3];
    ULONGLONG volume_serial_number;
    BYTE padding_6;
    BYTE boot_code[426];
    SHORT end_of_bootrecord;

} NTFS_BootRecord;
#pragma pack(pop)

class NtfsFS : public FileSystem
{
public:
    NtfsFS(const WCHAR *p, int *error_code);
    Cluster ReadClusters(ULONGLONG start_cluster, DWORD number_of_clusters, int *error_code);
    Cluster ReadClusters(ULONGLONG start_cluster, DWORD number_of_clusters);
	ULONGLONG GetClustersCount();
    ~NtfsFS() {};
private:
	BYTE data_buffer[512];
    bool is_NTFS;
    DWORD ReadBootRecord(BYTE *data_buffer);
    bool CheckNTFS();
    NTFS_BootRecord *mbr;
};
//------------------------------------
//          FsFAT32
//------------------------------------
#pragma pack(push, 1)
typedef struct
{
    BYTE jmp[3];
    ULONGLONG oem_name;
    SHORT bytes_per_sector;
    BYTE sectors_per_cluster;
    SHORT reserved_sectors;
    BYTE numbers_of_copies_fat;
    BYTE padding_1[2];
    BYTE padding_2[2];
    BYTE media_descriptor;
    BYTE padding_3[2];
    SHORT sectors_per_track;
    SHORT number_of_heads;
    DWORD number_of_hidden_sectors;
    DWORD sectors_in_partition;
    DWORD sectors_per_fat;
    BYTE padding_4[42];
    ULONGLONG fat_name;
    BYTE exec_code[420];
    SHORT boot_record_signature;
} FAT32_BootRecord;
#pragma pack(pop)

class Fat32FS : public FileSystem
{
public:
    Fat32FS(const WCHAR *p, int *error_code);
    Cluster ReadClusters(ULONGLONG start_cluster, DWORD number_of_clusters, int *error_code);
    Cluster ReadClusters(ULONGLONG start_cluster, DWORD number_of_clusters);
    ULONGLONG GetClustersCount();
    ~Fat32FS() {};
private:
    BYTE data_buffer[512];
    bool is_FAT32;
    DWORD ReadBootRecord(BYTE *data_buffer);
    bool CheckFAT32();
    FAT32_BootRecord *mbr;
};

#endif //FILESYSTEM_FILESYSTEM_H

