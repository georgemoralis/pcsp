/*
 *  17/06/2022 - synced with jpcsp 14/06/2022 - a5e0793c
 */
#include "Elf32.h"

/*TODO*/  //    // File offset
/*TODO*/  //    private int elfOffset;
/*TODO*/  //    private boolean kernelMode;
/*TODO*/  //
/*TODO*/  //    // Headers
/*TODO*/  //    private Elf32Header header;
/*TODO*/  //    private List<Elf32ProgramHeader> programHeaderList;
/*TODO*/  //    private List<Elf32SectionHeader> sectionHeaderList;
/*TODO*/  //    private HashMap<String, Elf32SectionHeader> sectionHeaderMap;
/*TODO*/  //    private Elf32SectionHeader shstrtab;
/*TODO*/  //
/*TODO*/  //    // Debug info
/*TODO*/  //    private String ElfInfo; // ELF header
/*TODO*/  //    private String ProgInfo; // ELF program headers
/*TODO*/  //    private String SectInfo; // ELF section headers
/*TODO*/  //
/*TODO*/  //    public Elf32(ByteBuffer f) throws IOException {
/*TODO*/  //        elfOffset = f.position();
/*TODO*/  //        loadHeader(f);
/*TODO*/  //        if (header.isValid()) {
/*TODO*/  //            loadProgramHeaders(f);
/*TODO*/  //            loadSectionHeaders(f);
/*TODO*/  //        }
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void loadHeader(ByteBuffer f) throws IOException {
/*TODO*/  //        header = new Elf32Header(f);
/*TODO*/  //        ElfInfo = header.toString();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void loadProgramHeaders(ByteBuffer f) throws IOException {
/*TODO*/  //        programHeaderList = new LinkedList<Elf32ProgramHeader>();
/*TODO*/  //        StringBuilder sb = new StringBuilder();
/*TODO*/  //
/*TODO*/  //        for (int i = 0; i < header.getE_phnum(); i++) {
/*TODO*/  //            f.position(elfOffset + header.getE_phoff() + (i * header.getE_phentsize()));
/*TODO*/  //            Elf32ProgramHeader phdr = new Elf32ProgramHeader(f);
/*TODO*/  //
/*TODO*/  //            // Save loaded header
/*TODO*/  //            programHeaderList.add(phdr);
/*TODO*/  //
/*TODO*/  //            // Construct ELF program header info for debugger
/*TODO*/  //            sb.append("-----PROGRAM HEADER #" + i + "-----" + "\n");
/*TODO*/  //            sb.append(phdr.toString());
/*TODO*/  //
/*TODO*/  //            // yapspd: if the PRX file is a kernel module then the most significant
/*TODO*/  //            // bit must be set in the phsyical address of the first program header.
/*TODO*/  //            if (i == 0 && (phdr.getP_paddr() & 0x80000000) != 0) {
/*TODO*/  //                kernelMode = true;
/*TODO*/  //                Emulator.log.debug("Kernel mode PRX detected");
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        ProgInfo = sb.toString();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    private void loadSectionHeaders(ByteBuffer f) throws IOException {
/*TODO*/  //        sectionHeaderList = new LinkedList<Elf32SectionHeader>();
/*TODO*/  //        sectionHeaderMap = new HashMap<String, Elf32SectionHeader>();
/*TODO*/  //
/*TODO*/  //        // 1st pass
/*TODO*/  //        // - save headers
/*TODO*/  //        // - find .shstrtab
/*TODO*/  //        for (int i = 0; i < header.getE_shnum(); i++) {
/*TODO*/  //            f.position(elfOffset + header.getE_shoff() + (i * header.getE_shentsize()));
/*TODO*/  //            Elf32SectionHeader shdr = new Elf32SectionHeader(f);
/*TODO*/  //
/*TODO*/  //            // Save loaded header
/*TODO*/  //            sectionHeaderList.add(shdr);
/*TODO*/  //
/*TODO*/  //            // Find the .shstrtab section
/*TODO*/  //            if (shdr.getSh_type() == Elf32SectionHeader.SHT_STRTAB
/*TODO*/  //                    && // 0x00000003
/*TODO*/  //                    shstrtab == null
/*TODO*/  //                    && // Some programs have 2 STRTAB headers,
/*TODO*/  //                    // the header with size 1 has to be ignored.
/*TODO*/  //                    shdr.getSh_size() > 1) {
/*TODO*/  //                shstrtab = shdr;
/*TODO*/  //            }
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        if (shstrtab == null) {
/*TODO*/  //            Emulator.log.debug(".shstrtab section not found");
/*TODO*/  //            return;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        // 2nd pass
/*TODO*/  //        // - Construct ELF section header info for debugger
/*TODO*/  //        StringBuilder sb = new StringBuilder();
/*TODO*/  //        int SectionCounter = 0;
/*TODO*/  //        for (Elf32SectionHeader shdr : sectionHeaderList) {
/*TODO*/  //            int position = elfOffset + shstrtab.getSh_offset() + shdr.getSh_name();
/*TODO*/  //            f.position(position); // removed past end of file check (fiveofhearts 18/10/08)
/*TODO*/  //
/*TODO*/  //            // Number the section
/*TODO*/  //            sb.append("-----SECTION HEADER #" + SectionCounter + "-----" + "\n");
/*TODO*/  //
/*TODO*/  //            String SectionName = Utilities.readStringZ(f); // removed readStringZ exception check
          //            (fiveofhearts 18/10/08)
/*TODO*/  //            if (SectionName.length() > 0) {
/*TODO*/  //                shdr.setSh_namez(SectionName);
/*TODO*/  //                sb.append(SectionName + "\n");
/*TODO*/  //                sectionHeaderMap.put(SectionName, shdr);
/*TODO*/  //            } else {
/*TODO*/  //                //Emulator.log.debug("Section header #" + SectionCounter + " has no name");
/*TODO*/  //            }
/*TODO*/  //
/*TODO*/  //            // Add this section header's info
/*TODO*/  //            sb.append(shdr.toString());
/*TODO*/  //            SectionCounter++;
/*TODO*/  //        }
/*TODO*/  //
/*TODO*/  //        SectInfo = sb.toString();
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    /**
/*TODO*/  //     * @return The elf was loaded from some kind of file or buffer. The elf
/*TODO*/  //     * offset is an offset into this buffer where the elf actually starts. If
/*TODO*/  //     * the returned offset is non-zero this is typically due to the elf being
/*TODO*/  //     * embedded inside a pbp.
/*TODO*/  //     */
/*TODO*/  //    public int getElfOffset() {
/*TODO*/  //        return elfOffset;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public Elf32Header getHeader() {
/*TODO*/  //        return header;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public List<Elf32ProgramHeader> getProgramHeaderList() {
/*TODO*/  //        return programHeaderList;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public Elf32ProgramHeader getProgramHeader(int index) {
/*TODO*/  //        if (index < 0 || index >= programHeaderList.size()) {
/*TODO*/  //            return null;
/*TODO*/  //        }
/*TODO*/  //        return programHeaderList.get(index);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public List<Elf32SectionHeader> getSectionHeaderList() {
/*TODO*/  //        return sectionHeaderList;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public Elf32SectionHeader getSectionHeader(int index) {
/*TODO*/  //        if (index < 0 || index >= sectionHeaderList.size()) {
/*TODO*/  //            return null;
/*TODO*/  //        }
/*TODO*/  //        return sectionHeaderList.get(index);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public Elf32SectionHeader getSectionHeader(String name) {
/*TODO*/  //        return sectionHeaderMap.get(name);
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public String getElfInfo() {
/*TODO*/  //        return ElfInfo;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public String getProgInfo() {
/*TODO*/  //        return ProgInfo;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public String getSectInfo() {
/*TODO*/  //        return SectInfo;
/*TODO*/  //    }
/*TODO*/  //
/*TODO*/  //    public boolean isKernelMode() {
/*TODO*/  //        return kernelMode;
/*TODO*/  //    }
