//---------------------------------------------------------------------------

#ifndef NTFSFileSystemH
#define NTFSFileSystemH
//---------------------------------------------------------------------------
#endif
typedef struct
{
  BYTE padding_1[3];
  BYTE signature[8];
  SHORT bytes_per_sector;
  BYTE sector_factor;
  BYTE padding_2[6];
  BYTE device_type;
  BYTE padding_3[18];
  ULONGLONG sectors_by_volume;
  ULONGLONG mft_lcn;
  ULONGLONG mft_lcn_copy;
  BYTE clusters_per_mft;
  BYTE padding_3[3];
  BYTE clusters_per_index;
  BYTE padding_4[3];
  ULONGLONG volume_serial_number;
  BYTE padding_5;
  BYTE boot_code[426];
  SHORT end_of_bootrecord;

} NTFS_BootRecord;

class NTFSFileSystem
{
	private:
        DWORD TotalClusters;
		BYTE ClusterFactor;
		DWORD BytesPerCluster;
	public:
		NTFSFileSystem();
		int Open(WCHAR *path);
		int ReadClusters(ULONGLONG startCluster, DWORD numberOfClusters, BYTE *outBuffer);
		DWORD TotalClusterNumber();
        DWORD GetBytesPerCluster();
};

