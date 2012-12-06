enum EmuFileType
{
    FILETYPE_ERROR = -1,
    FILETYPE_PSP_PBP,
	FILETYPE_PSP_INTERNAL_ELF,
    FILETYPE_PSP_ELF,
    FILETYPE_PSP_ISO,
    FILETYPE_UNKNOWN,
    FILETYPE_ENCRYPTED,
    FILETYPE_NO_FILE,
};

namespace loaders
{
    EmuFileType IdentifyFile(QString const &filename);    
    EmuFileType LoadFile(QString const &filename);
    EmuFileType LoadPBP(QString const &filename);
    EmuFileType LoadISO(QString const &filename);
    EmuFileType LoadELF(QString const &filename);
	EmuFileType LoadInternalELF(QString const &filename);
    QString getDiscID();
    void UnloadFile();
    void UnloadImage();
	std::string getBootPath();
	void setBootPath(char const* path);
	std::string getEbootPath();
	void setEbootPath(char const* path);
	void setIsoName(std::string path);
	std::string getIsoName();
}
