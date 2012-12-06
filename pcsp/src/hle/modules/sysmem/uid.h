
#define UID_ROOTNAME          "Root"
#define UID_METAROOTNAME      "MetaRoot"
#define UID_BASICNAME         "Basic"
#define UID_METABASICNAME     "MetaBasic"

#define UID_INFO(type, uid, uidtype) ((type *)((int)uid + (uidtype)->Size * sizeof(int)))
#define UIDCB_FROM_INFO(info, type) ((uidControlBlock *)((info) - (type)->Size * sizeof(int)))

struct UidMemoryInfo
{
	UidControlBlock *uidRoot;
	UidControlBlock *uidMetaRoot;
	UidControlBlock *uidBasicType;
	int uid_count;
};

struct BasicInfo
{
	int unk_0;
};

Memory::Ptr< UidControlBlock > uidPartitionType;
Memory::Ptr< UidControlBlock > uidHeapType;
Memory::Ptr< UidControlBlock > uidBasicType;
Memory::Ptr< UidControlBlock > uidUidMgmtHeap;

u32 uidmgmt_heap_uid;
UidMemoryInfo uid_info;

int _CreateUID(Memory::Ptr< UidControlBlock > uidType, char *name, short attr, Memory::Ptr< UidControlBlock > &block)
{
	// int state = __suspend_intc ();

#if 0
	if (parent < 1 || name < 1)
	{
		//5b04
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_ERROR;
	}

	*block = 0;

	UidControlBlock *tmp = malloc(uidType->unk * 4);

	if (tmp == 0)
	{
		//5af0
		// __resume_intc (state);

		return SCE_KERNEL_ERROR_NO_MEMORY;
	}

	char *uidname = sub_00004D24(name, var_BA58);
	if (uidname == 0)
	{
		//5ae4
		free4(tmp);

		// __resume_intc (state);
		return SCE_KERNEL_ERROR_NO_MEMORY;
	}

	*block = tmp;

	int result = InitUIDFromType(uidType, tmp, uidname, attr);
#else
	int result = 0;
#endif
	// __resume_intc (state);

	return result;
}

void _DeleteUID(u32 uid)
{
	// sceKernelCallUIDFunction(uid, UIDFUNC_DELETE);
}


#if 0
//46d0
void _InitUid()
{
	UidControlBlock *uidRoot;
	UidControlBlock *uidMetaRoot;
	UidControlBlock *uidBasic;
	UidControlBlock *uidMetaBasic;

	char *strRoot, *strMetaRoot, *strBasic, *strMetaBasic;
	
	void *heapptr;
	
	HeapInfo *heapinfo;
	
	int ret;

	int intr = sceKernelCpuSuspendIntr();

	fp = 0x10000;

	uidUidMgmtHeap = 0;
	uidmgmt_heap_uid = 0;

	PartitionInfo *partition = PartitionInfo::get_partition(1);

	_CreateHeap(partition, 0x2000, 0x1, &heapptr);

	_SetBlockDeleted(partition, heapptr);

	main_heap.size = 0x2000;
	main_heap.partition = 0x1;
	main_heap.addr = heapptr;

	uidRoot      = (UidControlBlock *)_AllocHeapMemory(&main_heap, sizeof(UidControlBlock), 0);
	uidMetaRoot  = (UidControlBlock *)_AllocHeapMemory(&main_heap, sizeof(UidControlBlock), 0);
	uidBasic     = (UidControlBlock *)_AllocHeapMemory(&main_heap, sizeof(UidControlBlock), 0);
	uidMetaBasic = (UidControlBlock *)_AllocHeapMemory(&main_heap, sizeof(UidControlBlock), 0);

	::memset(uidRoot,      0, sizeof(UidControlBlock));
	::memset(uidMetaRoot,  0, sizeof(UidControlBlock));
	::memset(uidBasic,     0, sizeof(UidControlBlock));
	::memset(uidMetaBasic, 0, sizeof(UidControlBlock));


	strRoot      = (char *)_AllocHeapMemory(&main_heap, sizeof(UID_ROOTNAME)      + 1, 0);
	strMetaRoot  = (char *)_AllocHeapMemory(&main_heap, sizeof(UID_METAROOTNAME)  + 1, 0);
	strBasic     = (char *)_AllocHeapMemory(&main_heap, sizeof(UID_BASICNAME)     + 1, 0);
	strMetaBasic = (char *)_AllocHeapMemory(&main_heap, sizeof(UID_METABASICNAME) + 1, 0);

	_InitBasicUIDType(uidRoot, strRoot, uidMetaRoot, strRoot, uidBasic, strBasic, uidMetaBasic, strMetaBasic);

	_HeapInit();

	ret = sceKernelCreateUID(uidHeapType, "Heap for UID management", 0, &uidUidMgmtHeap);

	heapinfo = UID_INFO(HeapInfo, uidUidMgmtHeap, uidHeapType);
	heapinfo->size      = main_heap.size;
	heapinfo->partition = main_heap.partition;
	heapinfo->addr      = main_heap.addr;

	uidmgmt_heap_uid = uidUidMgmtHeap->UID;

	sceKernelCpuResumeIntr(intr);
}

//4c30
void *malloc_uid()
{
	void *buf;

	buf = _AllocHeapMemory(&main_heap, sizeof(uidControlBlock), 0);

	if(buf != 0)
	{
		memclear(buf, sizeof(uidControlBlock));
	}

	return buf;
}

//4c7c
int free5(void *unk_a0)
{
	_FreeHeapMemory(&main_heap, unk_a0);

	return 0;
}

//4ca4
void *malloc(SceSize size)
{
	void *buf = _AllocHeapMemory(&main_heap, size, 0);

	if(buf != 0)
	{
		memclear(buf, size);
	}

	return buf;
}

//4cfc
int free4(void *unk_a0)
{
	_FreeHeapMemory(&main_heap, unk_a0);

	return 0;
}

//4d24
char *sub_00004D24(char *unk_a0, char *unk_a1)
{
	int len_a0 = strlenmax(unk_a0, 0x1F);

	int len_a1 = strlenmax(unk_a1, 0x1F);

	if(len_a0 + len_a1 > 0x1F)
	{
		return 0;
	}

	char *s0 = _AllocHeapMemory(&main_heap, len_a0 + len_a1 + 1, 0);
	if(s0 == 0)
	{
		return 0;
	}

	strncpy(s0, unk_a0, len_a0);

	strncpy(s0 + len_a0, unk_a1, len_a1);

	*(s0 + len_a0 + len_a1) = 0;

	return s0;
}

//4df0
int free(void *unk_a0)
{
	_FreeHeapMemory(&main_heap, unk_a0);

	return 0;
}

//4e18
void *malloc_partition()
{
	void *buf = _AllocHeapMemory(&main_heap, sizeof(PartitionInfo), 0);

	if(buf != 0)
	{
		memclear(buf, sizeof(PartitionInfo));
	}

	return buf;
}

//4e64
int FreeUidControlBlock(void *unk_a0)
{
	_FreeHeapMemory(&main_heap, unk_a0);

	return 0;
}

//4e8c
void *malloc_partition2()
{
	void *buf = _AllocHeapMemory(&main_heap, sizeof(PartitionInfo), 0);

	if(buf != 0)
	{
		memclear(buf, sizeof(PartitionInfo));
	}

	return buf;
}

//4ed8
int free3(void *unk_a0)
{
	_FreeHeapMemory(&main_heap, unk_a0);

	return 0;
}

//4f00
void memclear(void *buf, SceSize size)
{
	if(size <= 0)
	{
		return;
	}

	for(; size > 0; size--, buf += sizeof(int))
	{
		*((int *)buf) = 0;
	}
}

//4f24
void strncpy(char *dest, char *src, int len)
{
	int i;

	for(i = 0; i < len && *src; i++, src++, dest++)
	{
		*dest = *src;
	}
}

//4f68
int strlenmax(char *str, int maxlen)
{
	int len;

	if(*str == 0 || maxlen <= 0)
	{
		return 0;
	}

	str++;

	for(len = 0; *str && len < maxlen; len++, str++);

	return len;
}

//4fa4
int sceKernelCallUIDFunction(SceUID uid, int funcid, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6)
{
	int ret;
	int intr = sceKernelCpuSuspendIntr();
	void *args[6] = { arg1, arg2, arg3, arg4, arg5, arg6 };
	int (*func)(uidControlBlock *cb, uidControlBlock *type, int funcid, void *args);
	uidControlBlock *cb2;

	uidControlBlock *cb = UIDCB_FROM_UID(uid);
	if(uid < 0 || cb->UID != uid)
	{
		//5010
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_UNKNOWN_UID;
	}

	sceKernelLookupUIDFunction(cb->type, funcid, &func, &cb2);

	if(func != 0)
	{
		ret = func(cb, cb2, funcid, args);
	}
	else
	{
		//5080
		ret = sceKernelCallUIDObjFunction(cb, 0xB9970352, funcid, args);
	}

	//5070
	sceKernelCpuResumeIntr(intr);

	return ret;
}

//5090
int sceKernelCallUIDObjFunction(uidControlBlock *cb, int funcid, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6)
{
	int ret;
	void *args[6] = { arg1, arg2, arg3, arg4, arg5, arg6 };
	int (*func)(uidControlBlock *cb, uidControlBlock *type, int funcid, void *args) = 0;
	uidControlBlock *cb2;

	int intr = sceKernelCpuSuspendIntr();

	sceKernelLookupUIDFunction(cb->type, funcid, &func, &cb2);

	if(func != 0)
	{
		ret = func(cb, cb2, funcid, args);
	}
	else
	{
		ret = sceKernelCallUIDObjFunction(cb, 0xB9970352, funcid, args);
	}

	sceKernelCpuResumeIntr(intr);

	return ret;
}

//5140
int SysMemForKernel_CE05CCB7(uidControlBlock *cb, uidControlBlock *cb1, int funcid, void *args)
{
	int ret;
	void *args[6] = { arg1, arg2, arg3, arg4, arg5, arg6 };
	int (*func)(uidControlBlock *cb, uidControlBlock *type, int funcid, void *args) = 0;
	uidControlBlock *cb2;

	int intr = sceKernelCpuSuspendIntr();

	sceKernelLookupUIDFunction(cb1->inherited, funcid, &func, &cb2);

	if(func != 0)
	{
		ret = func(cb, cb2, funcid, args);
	}
	else
	{
		ret = sceKernelCallUIDObjFunction(cb, 0xB9970352, funcid, args);
	}

	sceKernelCpuResumeIntr(intr);

	return ret;
}

//51e8
int sceKernelLookupUIDFunction(uidControlBlock *cb, int funcid, int (**func)(uidControlBlock *cb, uidControlBlock *type, int funcid, void *args), unk_a3)
{
	int i, intr = sceKernelCpuSuspendIntr();

	*func = 0;
	if(cb != 0)
	{
		v0 = cb->func_table;

		//5224
		uidControlBlock *tmp;
		for(tmp = cb; tmp; tmp = tmp->inherited)
		{
			v0 = cb->func_table;
			if(cb->func_table[0].funcid == 0 || cb->func_table[0].func == 0)
			{
				continue;
			}

			//5240
			for(i = 0; tmp->func_table[i].func; i++)
			{
				if(tmp->func_table[i].funcid == funcid)
				{
					//5290
					*unk_a3 = tmp;
					*func = tmp->func_table[i].func

						sceKernelCpuResumeIntr(intr);

					return 0;
				}
			}
		}
	}

	//5264
	sceKernelCpuResumeIntr(intr);

	return SCE_KERNEL_ERROR_NOT_FOUND_UIDFUNC;
}

UidLookupFunction RootUidFuncTable[] =
{
	{ UIDFUNC_CREATE, DummyUIDFunc },
	{ 0x973A5367, DummyUIDFunc },
	{ 0x285422D4, DummyUIDFunc },
	{ UIDFUNC_DELETE, RootDeleteUID },
	{ 0x86D94883, DummyUIDFunc },
	{ UIDFUNC_GETNAME, loc_00005f48 },
	{ UIDFUNC_GETTYPEUID, loc_00005f98 },
	{ UIDFUNC_EQUALS, loc_00005fa4 },
	{ UIDFUNC_ISTYPE, loc_0000600c },
	{ 0xB9970352, sub_00006048 },
	{ 0, 0 }
};

UidLookupFunction MetaRootUidFuncTable[] =
{
	{ UIDFUNC_DELETE, DummyUIDFunc },
	{ 0, 0 }
};

//52a4
void InitRootUID(uidControlBlock *uidRoot, char *strRoot, uidControlBlock *uidMetaRoot, char *strMetaRoot)
{
	int intr = sceKernelCpuSuspendIntr();

	uid_info.uidRoot = uidRoot;
	uid_info.uidMetaRoot = uidMetaRoot;
	uid_info.uid_count = 1;

	strcpy(name1, "Root");

	uidRoot->parent = uidRoot;
	uidRoot->nextChild = uidRoot;
	uidRoot->type = uidMetaRoot;
	uidRoot->UID = ((int)uid_info->uidRoot << 5) | 0x3;
	uidRoot->name = name1;
	uidRoot->unk = 0x6; //b
	uidRoot->size = 0;
	uidRoot->nextEntry = uid_info->uidRoot;
	uidRoot->inherited = 0;
	uidRoot->func_table = RootUidFuncTable;

	uid_info->uid_count++;

	strcpy(name2, "MetaRoot");

	uidMetaRoot->parent = uidMetaRoot;
	uidMetaRoot->nextChild = uidMetaRoot;
	uidMetaRoot->type = uid_info->uidMetaRoot;
	uidMetaRoot->UID = ((int)uid_info->uidMetaRoot << 5) | ((uid_info->uid_count & 0x3F) << 1) | 0x1;
	uidMetaRoot->name = name2;
	uidMetaRoot->unk = 0x6; //b
	uidMetaRoot->size = 0;
	uidMetaRoot->nextEntry = 0;
	uidMetaRoot->inherited = uid_info->uidRoot;
	uidMetaRoot->func_table = MetaRootUidFuncTable;

	uid_info->uid_count++;

	sceKernelCpuResumeIntr(intr);
}

//5418
void InitUIDType(uidControlBlock *uidInheritedType, uidControlBlock *uidType, uidControlBlock *uidMeta, char *strType, char *strMeta,
				 int size, UidLookupFunction *func_table, UidLookupFunction *func_table2, uidControlBlock **block)
{
	(type.8).18++;

	uidType->parent = uidType;
	uidType->nextChild = uidType;
	uidType->type = uidMeta;
	uidType->UID = ((int)uidType << 5) | ((uid_info->uid_count & 0x3F) << 1) | 0x1;
	uidType->name = strType;
	uidType->unk = uidInheritedType->unk + ((size + 3) / 4);
	uidType->size = uidInheritedType->unk;
	uidType->nextEntry = uid_info->uidRoot->nextEntry;
	uidType->inherited = uidInheritedType;
	uidType->func_table = func_table;

	uid_info->uid_count++;

	uidMeta->parent = uidMeta;
	uidMeta->nextChild = uidMeta;
	uidMeta->type = uid_info->uidMetaRoot;
	uidMeta->UID = ((int)uidMeta << 5) | ((uid_info->uid_count) & 0x3F) << 1) | 0x1;
	uidMeta->name = strMeta;
	uidMeta->unk = 0x6;
	uidMeta->size = 0;
	uidMeta->nextEntry = 0;
	uidMeta->inherited = uidInheritedType->type;
	uidMeta->func_table = func_table2;

	uid_info->uid_count++;

	uid_info->uidRoot->nextEntry = uidType;

	*block = uidType;
}

//5504
int sceKernelCreateUIDtypeInherit(char *inherited_name, char *name, int a2, int a3, int t0, UidControlBlock **block)
{
	int intr = sceKernelCpuSuspendIntr();

	if (inherited_name < 1 || name < 1)
	{
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_ERROR;
	}

	// make sure a UID with the same name does not already exist
	if (sub_00005E20(name) != 0)
	{
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_IDTYPE_EXIST;
	}

	//make sure a UID for the type exists
	s5 = sub_00005E20(inherited_name);
	
	if (s5 == 0)
	{
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_IDTYPE_NOT_EXIST;
	}

	UidControlBlock *s2 = malloc_uid();

	UidControlBlock *s3 = malloc_uid();

	char *s1 = sub_00004D24(name, var_BA58);

	char *s0 = sub_00004D24("Meta", name);

	if(s0 < 1 || s1 < 1 || s2 < 1 || s3 < 1)
	{
		if(s2 != 0)
		{
			free5(s2);
		}

		if(s3 != 0)
		{
			free5(s3);
		}

		if(s1 != 0)
		{
			free5(s1);
		}

		if(s0 != 0)
		{
			free5(s0);
		}

		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_NO_MEMORY;
	}

	s0 = InitUIDType(s5, s2, s3, s1, s0, unk_a2, unk_a3, unk_t0, block);

	sceKernelCpuResumeIntr(intr);

	return s0;
}

//56dc
uidControlBlock *sceKernelCreateUIDtype(unk_a0, unk_a1, unk_a2, unk_a3, unk_t0)
{
	return sceKernelCreateUIDtypeInherit("Basic", unk_a0, unk_a1, unk_a2, unk_a3, unk_t0);
}

//5720
int sceKernelDeleteUIDtype(uidControlBlock *uid)
{
	int intr = sceKernelCpuSuspendIntr();

	if(uid->parent != uid)
	{
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_IDTYPE_NOT_EMPTY;
	}

	if(uid->type->nextEntry != 0)
	{
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_IDTYPE_NOT_EMPTY;
	}

	uidControlBlock *prev = uid_info->uidRoot, *tmp;
	for(tmp = uid_info->uidRoot->nextEntry; tmp != uid; tmp = tmp->nextEntry)
	{
		prev = tmp;
	}

	prev->nextEntry = tmp->nextEntry;

	free(uid->name);

	free(uid->type->name);

	FreeUidControlBlock(uid->type);

	FreeUidControlBlock(uid);

	sceKernelCpuResumeIntr(intr);

	return 0;
}

//57dc
int sceKernelGetUIDname(SceUID uid, int bufsize, char *buf)
{
	char *s, *d;

	int intr = sceKernelCpuSuspendIntr();

	if(uid <= 0)
	{
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_UNKNOWN_UID;
	}

	uidControlBlock *cb = UIDCB_FROM_UID(uid);

	if(cb->UID != uid)
	{
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_UNKNOWN_UID;
	}

	for(s = cb->name, d = buf; bufsize > 1 && *s; s++, d++, bufsize--)
	{
		*d = *s;
	}

	*d = 0;

	sceKernelCpuResumeIntr(intr);

	return 0;
}

//5890
int sceKernelRenameUID(SceUID uid, char *name)
{
	int intr = sceKernelCpuSuspendIntr();

	uidControlBlock *cb = UIDCB_FROM_UID(uid);
	if(uid < 0 || cb->UID != uid)
	{
		//sce bug here: need to call sceKernelCpuResumeIntr here!
		return SCE_KERNEL_ERROR_UNKNOWN_UID;
	}

	free(cb->name);

	char *uidname = sub_00004D24(name, var_BA58);
	if(uidname == 0)
	{
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_NO_MEMORY;
	}

	cb->name = uidname;

	sceKernelCpuResumeIntr(intr);

	return 0;
}

//5948
int sceKernelGetUIDtype(SceUID uid)
{
	int ret = SCE_KERNEL_ERROR_UNKNOWN_UID;

	uidControlBlock *cb = UIDCB_FROM_UID(uid);
	if(uid <= 0 || cb->uid != UID)
	{
		return SCE_KERNEL_ERROR_UNKNOWN_UID;
	}

	return cb->type->UID;
}

//5980
int InitUIDFromType(uidControlBlock *uidType, uidControlBlock *uid, char *name, short attr)
{
	uid->parent = uidType;
	uid->nextChild = uidType->nextChild;
	uid->type = uidType;
	uid->UID = ((int)uid << 5) | ((uid_info->uid_count & 0x3F) << 1) | 0x1;
	uid->name = name;
	uid->unk = uidType->unk;
	uid->size = uidType->size;
	uid->attribute = attr;

	uidType->nextChild = child;

	uid->nextChild->parent = uid;

	uid_info->uid_count++;

	sceKernelCallUIDObjFunction(uid, UIDFUNC_CREATE);

	return 0;
}

//5a14
int sceKernelCreateUID(uidControlBlock *uidType, char *name, short attr, uidControlBlock **block)
{
	int intr = sceKernelCpuSuspendIntr();

	if(parent < 1 || name < 1)
	{
		//5b04
		sceKernelCpuResumeIntr(intr);
		return SCE_KERNEL_ERROR_ERROR;
	}

	*block = 0;
	uidControlBlock *tmp = malloc(uidType->unk * 4);
	if(tmp == 0)
	{
		//5af0
		sceKernelCpuResumeIntr(intr);
		return SCE_KERNEL_ERROR_NO_MEMORY;
	}

	char *uidname = sub_00004D24(name, var_BA58);
	if(uidname == 0)
	{
		//5ae4
		free4(tmp);

		sceKernelCpuResumeIntr(intr);
		return SCE_KERNEL_ERROR_NO_MEMORY;
	}

	*block = tmp;

	int ret = InitUIDFromType(uidType, tmp, uidname, attr);

	sceKernelCpuResumeIntr(intr);

	return ret;
}

//5b18
void sceKernelDeleteUID(SceUID uid)
{
	sceKernelCallUIDFunction(uid, UIDFUNC_DELETE);
}

//5b38
int sceKernelSearchUIDbyName(char *name, int uid)
{
	uidControlBlock *tmp, *parent, *cb;
	int ret;

	if(name == 0)
	{
		return SCE_KERNEL_ERROR_ERROR;
	}

	int intr = sceKernelCpuSuspendIntr();

	if(uid == 0)
	{
		tmp = uid_info->uidRoot;
		do
		{
			if((cb = sub_00005E84(name, uid_info->uidRoot)) != 0)
			{
				break;
			}

			tmp = tmp->nextEntry;
		} while(tmp != uid_info->uidRoot);

		sceKernelCpuResumeIntr(intr);

		if(cb == 0)
		{
			return SCE_KERNEL_ERROR_ID_NOT_EXIST;
		}

		return cb->UID;
	}

	cb = UIDCB_FROM_UID(uid);
	if(uid > 0 && cb->UID == uid)
	{
		//5bc8
		if(cb->type->type == uid_info->uidMetaRoot)
		{
			//5bf4
			if(cb->type == uid_info->uidRoot)
			{
				sceKernelCpuResumeIntr(intr);

				return SCE_KERNEL_ERROR_IDTYPE_NOT_EXIST;
			}

			cb = sub_00005E84(name, cb);

			sceKernelCpuResumeIntr(intr);

			if(cb == 0)
			{
				return SCE_KERNEL_ERROR_ID_NOT_EXIST;
			}

			return cb->UID;
		}
	}

	//5b98
	sceKernelCpuResumeIntr(intr);

	return SCE_KERNEL_ERROR_UNKNOWN_UID;
}

//5c5c
int sceKernelGetUIDcontrolBlock(SceUID uid, uidControlBlock **block)
{
	uidControlBlock *cb;

	if(uid == 0)
	{
		return SCE_KERNEL_ERROR_UNKNOWN_UID;
	}

	if(((int)uid & 0x80000001) == 0x1)
	{
		//5c8c
		cb = UIDCB_FROM_UID(uid);
		if(cb->UID == uid)
		{
			*block = cb;

			return 0;
		}
	}

	return SCE_KERNEL_ERROR_UNKNOWN_UID;
}

//5cb8
int sceKernelGetUIDcontrolBlockWithType(SceUID uid, uidControlBlock *type, uidControlBlock **block)
{
	uidControlBlock *cb;

	int intr = sceKernelCpuSuspendIntr();

	if(uid == 0)
	{
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_UNKNOWN_UID;
	}

	if((uid & 0x80000001) == 1)
	{
		cb = UIDCB_FROM_UID(uid);
		if(uid <= 0 || cb->UID != uid)
		{
			sceKernelCpuResumeIntr(intr);

			return SCE_KERNEL_ERROR_UNKNOWN_UID;
		}

		if(cb->type != type)
		{
			sceKernelCpuResumeIntr(intr);

			return SCE_KERNEL_ERROR_UNMATCH_UID_TYPE;
		}

		*block = cb;

		sceKernelCpuResumeIntr(intr);

		return 0;
	}

	sceKernelCpuResumeIntr(intr);

	return SCE_KERNEL_ERROR_UNKNOWN_UID;
}

//5d7c
int SysMemForKernel_82D3CEE3(uidControlBlock *uid, uidControlBlock *type)
{
	uidControlBlock *tmp;

	for(tmp = uid->type; tmp && tmp != type; tmp = tmp->inherited);

	//5db4
	return (tmp == type);
}

//5dbc
int strcmp(char *s1, char *s2)
{
	if(s1 == s2)
	{
		return 1;
	}

	if(s1 < 1 || s2 < 1)
	{
		return 0;
	}

	while(*s1 == *s2++)
	{
		if(*s1++ == 0)
		{
			return 1;
		}
	}

	return 0;
}

//5e20
uidControlBlock *sub_00005E20(char *name)
{
	uidControlBlock *block = uid_info->uidRoot;

	while(1 == 1)
	{
		if(strcmp(name, block->name))
		{
			return block;
		}

		block = block->nextEntry;
		if(block == uid_info->uidRoot)
		{
			return 0;
		}
	}
}

//5e84
uidControlBlock *sub_00005E84(char *name, uidControlBlock *block)
{
	uidControlBlock *tmp, *parent = block->parent;

	for(tmp = block; tmp != parent; tmp = tmp->parent)
	{
		if(strcmp(name, parent->name) != 0)
		{
			return parent;
		}
	}

	return 0;
}

int DummyUIDFunc(uidControlBlock *cb, uidControlBlock *type, int funcid, void *args)
{
	return cb->UID;
}

//5ef0
int RootDeleteUID(uidControlBlock *cb, uidControlBlock *type, int funcid, void *args)
{
	cb->type = 0;

	cb->parent->nextChild = cb->nextChild;
	cb->parent = cb;

	cb->nextChild->parent = cb->parent;
	cb->nextChild = cb;

	cb->UID = 0;

	free(cb->name);

	free4(cb);

	return 0;
}

//5f48
int loc_00005f48(uidControlBlock *cb, uidControlBlock *type, int funcid, void *args)
{
	char *s, *d = (char *)args[1];
	int bufsize = (int)args[0];

	if(bufsize > 1)
	{
		for(s = cb->name; bufsize > 1 && *s; s++, d++, bufsize--)
		{
			*d = *s;
		}
	}

	*d = 0;

	return 0;
}

//5f98
int loc_00005f98(uidControlBlock *cb, uidControlBlock *type, int funcid, void *args)
{
	return cb->type->UID;
}

//5fa4
int loc_00005fa4(uidControlBlock *cb, uidControlBlock *type, int funcid, void *args)
{
	int uid = (int)args[0];
	uidControlBlock *cb2, *tmp;

	cb2 = UIDCB_FROM_UID(uid);
	if(uid <= 0 || cb2->UID != uid)
	{
		return 0;
	}

	//5fd0
	for(tmp = cb->type; tmp && ((int)tmp ^ (int)cb2);  tmp = tmp->inherited);

	return (((int)tmp ^ (int)cb2) < 1);
}

//600c
int loc_0000600c(uidControlBlock *cb, uidControlBlock *type, int funcid, void *args)
{
	int uid = (int)args[0];
	uidControlBlock *cb2;

	cb2 = UIDCB_FROM_UID(uid);
	if(uid > 0)
	{
		if(cb2->UID == uid)
		{
			return (cb->type == cb2);
		}
		else
		{
			return cb->UID;
		}
	}

	return 0;
}

//6048
int sub_00006048(uidControlBlock *cb, uidControlBlock *type, int funcid, void *args)
{
	Kprintf("WARNING: %s of %s not support 0x%x key\n", cb->name, cb->type->name, (int)args[0]);

	return SCE_KERNEL_ERROR_NOT_FOUND_UIDFUNC;
}

//6080
void strcpy(char *dest, char *src)
{
	for(; *src; dest++, src++)
	{
		*dest = *src;
	}

	//60a0
	*dest = '\0';
}

UidLookupFunction BasicUidFuncTable[] =
{
	{ UIDFUNC_CREATE, BasicCreateUID },
	{ UIDFUNC_DELETE, BasicDeleteUID },
	{ 0, 0 }
};

//60a8
void _InitBasicUIDType(uidControlBlock *uidRoot, char *strRoot, uidControlBlock *uidMetaRoot, char *strMetaRoot,
					  uidControlBlock *uidBasic, char *strBasic, uidControlBlock *uidMetaBasic, char *strMetaBasic)
{
	int intr = sceKernelCpuSuspendIntr();

	InitRootUID(uidRoot, strRoot, uidMetaRoot, strMetaRoot);

	strcpy2(strBasic, "Basic");

	strcpy2(strMetaBasic, "MetaBasic");

	InitUIDType(uid_info->uidRoot, uidBasic, uidMetaBasic, strBasic, strMetaBasic, 0x4, BasicUidFuncTable, 0, &uid_info->uidBasicType);

	sceKernelCpuResumeIntr(intr);
}

//61a0
int sceKernelIsHold(uidControlBlock *unk_a0, uidControlBlock *unk_a1)
{
	s2 = unk_a0;
	s1 = unk_a1;

	int intr = sceKernelCpuSuspendIntr();

	if(SysMemForKernel_82D3CEE3(unk_a1, uid_info.uidBasicType) == 0 || SysMemForKernel_82D3CEE3(unk_a0, uid_info.uidBasicType) == 0)
	{
		sceKernelCpuResumeIntr(intr);

		return 0;
	}

	v1 = uid_info.uidBasicType;
	v0 = v1.15;
	v0 = v0 << 2;
	a0 = v0 + s1;
	v0 = v0 + s2;
	a1 = 0x0(v0);
	a0 = 0x0(a0);
	v1 = 0x10(a1);
	v0 = 0x14(a0);
	v0 = v0 < v1;
	if(v0 == 0)
	{
		v1 = 0x0(a1);
		//6288
		if(v1 == a1)
		{
			sceKernelCpuResumeIntr(intr);

			return 0;
		}

		v0 = 0x10(v1);

		//6294
		while(1 == 1)
		{
			if(v0 == s1)
			{
				sceKernelCpuResumeIntr(intr);

				return 1;
			}

			v1 = 0x0(v1);
			if(v1 == a1)
			{
				break;
			}

			v0 = 0x10(v1);
		}

		sceKernelCpuResumeIntr(intr);

		return 0;
	}

	v1 = 0x8(a0);
	a0 += 0x8;
	if(v1 == a0)
	{
		sceKernelCpuResumeIntr(intr);

		return 0;
	}

	v0 = 0xC(v1);
	//623c
	while(1 == 1)
	{
		if(v0 == s2)
		{
			//6278
			sceKernelCpuResumeIntr(intr);

			return 1;
		}

		v1 = 0x0(v1);
		if(v1 == a0)
		{
			break;
		}

		v0 = 0xC(v1);
	}

	sceKernelCpuResumeIntr(intr);

	return 0;
}

//62b0
//wtf is this meant to do??? sceKernelReleaseUID below is identical, neither resume
//interrupts, and they both always return SCE_KERNEL_ERROR_NOT_FOUND_UIDFUNC
int sceKernelHoldUID(SceUID unk_a0, SceUID unk_a1)
{
	int intr = sceKernelCpuSuspendIntr();

	if(unk_a0 <= 0 || unk_a1 <= 0)
	{
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_UNKNOWN_UID;
	}

	uidControlBlock *cb_a0 = UIDCB_FROM_UID(unk_a0);
	uidControlBlock *cb_a1 = UIDCB_FROM_UID(unk_a1);

	if(cb_a0->UID != unk_a0 || cb_a1->UID != unk_a1)
	{
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_UNKNOWN_UID;
	}

	if(SysMemForKernel_82D3CEE3(cb_a0, uid_info.uidBasicType) == 0 || SysMemForKernel_82D3CEE3(cb_a1, uid_info.uidBasicType) == 0)
	{
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_NOT_FOUND_UIDFUNC;
	}

	return SCE_KERNEL_ERROR_NOT_FOUND_UIDFUNC;
}

//6384
int sceKernelReleaseUID(SceUID unk_a0, SceUID unk_a1)
{
	s1 = unk_a0;
	s0 = unk_a1;

	int intr = sceKernelCpuSuspendIntr();

	a0 = v0;
	a2 = s0 >> 7;
	v0 = s1 < 1;
	v1 = s1 >> 7;
	a1 = s0 < 1;
	a1 = a1 | v0;
	a2 = a2 << 2;
	v0 = 0x88000000;
	v1 = v1 << 2;
	s2 = v1 | v0;
	a2 = a2 | v0;
	if(unk_a0 <= 0 || unk_a1 <= 0)
	{
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_UNKNOWN_UID;
	}

	uidControlBlock *cb_a0 = UIDCB_FROM_UID(unk_a0);
	uidControlBlock *cb_a1 = UIDCB_FROM_UID(unk_a1);

	if(cb_a0->UID != unk_a0 || cb_a1->UID != unk_a1)
	{
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_UNKNOWN_UID;
	}

	if(SysMemForKernel_82D3CEE3(cb_a0, uid_info.uidBasicType) == 0 || SysMemForKernel_82D3CEE3(cb_a1, uid_info.uidBasicType) == 0)
	{
		sceKernelCpuResumeIntr(intr);

		return SCE_KERNEL_ERROR_NOT_FOUND_UIDFUNC;
	}

	return SCE_KERNEL_ERROR_NOT_FOUND_UIDFUNC;
}

//6458
int BasicDeleteUID(uidControlBlock *cb, uidControlBlock *type, int funcid, void *args)
{
	s6 = unk_a1;
	s5 = unk_a3;
	s4 = unk_a2;
	s3 = unk_a0;

	BasicInfo *info = UID_INFO(BasicInfo, cb, uidBasicType); //v0
	s1 = v0.0;
	a3 = s1.0;
	if(info->unk_0 != 0)
	{
		if(s1.10 > 0 && s1 != s1.0)
		{
			//64c0
			while(1 == 1)
			{
				v0 = a3 + 0x8;
				a1 = 0x4(v0);
				a2 = 0x8(a3);
				s0 = 0x0(a3);
				a0 = a3;
				0x4(a2) = a1;
				v1 = 0x4(v0);
				0x4(v0) = v0;
				0x0(v1) = a2;
				a3.8 = &a3.8;
				v1.4 = a3.4;
				a3.4 = a3;
				(a3.4).0 = a3.0;
				a3.0 = a3;

				free3(a3);

				a3 = s0;
				if(s0 == s1)
				{
					break;
				}
			}
		}

		v0 = 0x14(s1);
		//6514
		s2 = s1 + 0x8;
		a3 = 0x8(s1);

		if(s1.14 > 0 && s1.8 != &(s1.8))
		{
			//6528
			while(1 == 1)
			{
				a1 = 0x4(a3);
				s0 = 0x0(a3);
				v0 = a3 - 0x8;
				a0 = v0;
				0x4(s0) = a1;
				v1 = 0x4(a3);
				0x4(a3) = v1;
				0x0(v1) = s0;
				a1 = 0x4(v0);
				a2 = -0x8(a3);
				0x0(a3) = a3;
				0x4(a2) = a1;
				v1 = 0x4(v0);
				0x4(v0) = v0;
				0x0(v1) = a2;
				-0x8(a3) = v0;
				v0 = free3(...);

				a3 = s0;
				if(s0 == s2)
				{
					break;
				}
			}
		}

		//6574
		FreeUidControlBlock(s1);
	}

	//657c
	return SysMemForKernel_CE05CCB7(cb, type, funcid, args);
}

//65b8
int BasicCreateUID(uidControlBlock *cb, uidControlBlock *type, int funcid, void *args)
{
	SysMemForKernel_CE05CCB7(cb, type, funcid, args);

	BasicInfo *info = UID_INFO(BasicInfo, cb, uidBasicType);
	info->unk_0 = 0;

	return cb->UID;
}

#endif
