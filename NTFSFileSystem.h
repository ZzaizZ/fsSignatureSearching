//---------------------------------------------------------------------------

#ifndef NTFSFileSystemH
#define NTFSFileSystemH
#endif
//---------------------------------------------------------------------------
#include <windows.h>
//---------------------------------------------------------------------------
#pragma pack(push, 1)
typedef struct
{
  BYTE padding_1[3];
  ULONGLONG signature;
  SHORT bytes_per_sector;
  BYTE sector_per_cluster;
  BYTE padding_2[6];
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
//---------------------------------------------------------------------------
class NTFSFileSystem
{
	private:
		NTFS_BootRecord *mbr;
		DWORD total_clusters;
		DWORD bytes_per_cluster;
		DWORD ReadBootRecord(HANDLE file_handle, BYTE *data_buffer);
		bool CheckNTFS();
        bool is_NTFS;
	public:
		NTFSFileSystem(HANDLE file_handle, DWORD *error_code);
		~NTFSFileSystem();
        ULONGLONG GetFSSignature();
		int ReadClusters(HANDLE file_handle, ULONGLONG start_cluster, DWORD number_of_clusters, BYTE *data_buffer);
};

