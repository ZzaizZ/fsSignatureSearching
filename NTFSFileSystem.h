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

#endif //FILESYSTEM_FILESYSTEM_H

