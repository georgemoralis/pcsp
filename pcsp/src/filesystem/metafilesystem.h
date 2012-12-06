


class fs_MetaFileSystem : public fs_GenericHandleAllocator, fs_AbstractFileSystem
{
    struct System
    {
        std::string prefix;
        fs_AbstractFileSystem *system;
    };

    u32                 current;
	std::vector<System> fileSystems;
	std::string         currentDirectory;
	

public:
    fs_MetaFileSystem() : current(0) {}

	void                   Mount(std::string prefix, fs_AbstractFileSystem *system);
	void                   Unmount(fs_AbstractFileSystem *system);
	void                   UnmountAll();
	fs_AbstractFileSystem *GetHandleOwner(u32 handle);
	bool                   MapFilePath(std::string inpath, std::string* outpath, fs_AbstractFileSystem **system);
	u32                    RequestHandle() { return ++current; }
    void                   ReleaseHandle(u32 UNUSED(handle)) {}
	std::vector<FileInfo>  GetDirListing(std::string path);
	u32                    OpenFile(std::string filename, FileAccess access);
	void                   CloseFile(u32 handle);
	u32                    ReadFile(u32 handle, u8 *pointer, s64 size);
	u32                    WriteFile(u32 handle, const u8 *pointer, s64 size);
	u32                    SeekFile(u32 handle, s64 position, FileMove type);
	void                   StatFile(u32 structaddress, FileInfo &info);
    virtual void           ChangeDirectory(std::string dir);
    bool                   OwnsHandle(u32 UNUSED(handle)) { return false; }
	FileInfo               GetFileInfo(std::string filename);
};


