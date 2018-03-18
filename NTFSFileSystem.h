//---------------------------------------------------------------------------

#ifndef NTFSFileSystemH
#define NTFSFileSystemH
//---------------------------------------------------------------------------
#endif
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

