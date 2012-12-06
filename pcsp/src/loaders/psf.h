class psf_loader
{

public:

	u8 size;

	bool sizeDirty;
	bool tablesDirty;
	u32 indexCount;
	psf_loader();
	~psf_loader();
	static const int PSF_IDENT = 0x46535000;
	static const int PSF_DATA_TYPE_BINARY = 0;
	static const int PSF_DATA_TYPE_STRING = 2;
	static const int PSF_DATA_TYPE_INT32 = 4;
	void read(u8 *fileptr);
	void write(const char *filepath);
	void calculateSize();
	void calculateTables();
	void printpsf();
	QString getString(QString Key);
	u32 getInteger(QString Key);
	QString getPrintableString(QString Key);
	void putString(QString Key, QString Data, int rawlen);
	void putInteger(QString Key, int Data);

    
	struct Psf_header
    {
      u32    magic;
      u32    version;
      u32    keyTableOffset;
      u32    valueTableOffset;
      u32    indexEntryCount;
    };
	struct Psf_section
    {
      u16   keyOffset;
      u8    padding;
      u8    dataType; /* string=2, integer=4, binary=0 */
      u32   dataSize;
      u32   dataSizePadded;
      u32   valueOffset;
    };
	struct Psf_header   *psfheader;
	struct Psf_section  *psfsections, *sect;
public:
   class PSFKeyValuePair
   {
   public:
      struct Psf_section *section;
	  // key table info
	  QString key;

	  // data table info
	  QString data;

	  PSFKeyValuePair() {}
	  PSFKeyValuePair(QString k, int type, int size, int paddedSize, QString d) {
		  section = (struct Psf_section *)malloc(sizeof(struct Psf_section));
		  section->padding = 4;
		  section->dataType = type;
		  section->dataSize = size;
		  section->dataSizePadded = paddedSize;
		  key = k;
		  data = d;
	  }
	  void read(struct Psf_section *sect) 
	  {
		  section=sect;
	  }
   };
   QLinkedList<PSFKeyValuePair*> pairList;
};

