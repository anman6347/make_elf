#include <elf.h>
#include <unistd.h>
#include <stdio.h>

int main ()
{
    /* hello1.o */

    /*
    0   -----------------------------
                ELF Header
    64  -----------------------------
                .text section
    110  -----------------------------
                .rodata section
    125 -----------------------------
                .strtab section
    141 -----------------------------
                .symtab section
    237 -----------------------------
                .rela.text section
    261 -----------------------------
                .shstrtab section
    313 -----------------------------
                section header table
    */

    /* ELF header */
    Elf64_Ehdr ehdr1 = {
        .e_ident = {ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3,     // 0x7f, E, L, F
                    ELFCLASS64,                             // 64 bit
                    ELFDATA2LSB,                            // Little endian (this is required by x86-64)
                    EV_CURRENT,                             // ELF Version 1 (current)
                    ELFOSABI_SYSV,                          // System V ABI
                    0                                       // ABI version
                    },
        .e_type = ET_REL,                   // Relocatable file
        .e_machine = EM_X86_64,             // x86-64
        .e_version = EV_CURRENT,            // ELF version 1 (current)
        .e_entry = 0,                       // Entry point virtual address
        .e_phoff = 0,                       // Program header table doesn't exist
        .e_shoff = 313,                     // Section header table file offset
        .e_flags = 0,                       // No professor-specific flags in X86-64
        .e_ehsize = sizeof(Elf64_Ehdr),     // ELF header size in bytes
        .e_phentsize = sizeof(Elf64_Phdr),  // Program header table entry size
        .e_phnum = 0,                       // Program header table entry count
        .e_shentsize = sizeof(Elf64_Shdr),  // Section Header table entry size
        .e_shnum = 7,                       // Section header table entry count
        .e_shstrndx = 6,                    // Section header string table index
    };

    /* SECTIONS */
    // 0 (.null Section)

    // 1 (.text Section)
    unsigned char TEXT1[] = {
        0x48, 0xC7, 0xC0, 0x01, 0x00, 0x00, 0x00,       // MOV  RAX, 1 (syscall number for Write)
        0x48, 0xC7, 0xC7, 0x01, 0x00, 0x00, 0x00,       // MOV  RDI, 1 (fildes = stdout)
        0x48, 0xC7, 0xC6, 0x00, 0x00, 0x00, 0x00,       // MOV  RSI, message (the address of the string that will be written)
        0x48, 0xC7, 0xC2, 0x0E, 0x00, 0x00, 0x00,       // MOV  RDX, 14 (the number of bytes to write)
        0x0F, 0x05,                                     // Syscall
        0x48, 0xC7, 0xC0, 0x3C, 0x00, 0x00, 0x00,       // MOV  RAX, 60 (syscall number for Exit)
        0x48, 0xC7, 0xC7, 0x00, 0x00, 0x00, 0x00,       // MOV RDI, 0 (exit(0))
        0x0F, 0x05                                      // Syscall
    };

    // 2 (.rodata section)
    char message1[15] = "Hello, World!\n";

    // 3 (.strtab section)
    char strtab1[] = {'\0', '_', 's', 't', 'a', 'r', 't','\0', 'm', 'e', 's', 's', 'a', 'g', 'e', '\0'};
    int strtab_index1[3] = {0, 1, 8};

    // 4 (.symtab section)
    Elf64_Sym symtab1[] = {
        {   // STN_UNDEF
            .st_shndx = SHN_UNDEF
        },
        {   // .rodata section
            .st_name = 0,
            .st_info = ELF64_ST_INFO(STB_LOCAL, STT_SECTION),
            .st_shndx = 2,
        },
        {
            // message
            .st_name = strtab_index1[2],
            .st_info = ELF64_ST_INFO(STB_LOCAL, STT_OBJECT),
            .st_other = 0,
            .st_shndx = 2,
            .st_value = 0,
            .st_size = sizeof(strtab1) / sizeof(char)
        },
        {   // main function
            .st_name = strtab_index1[1],                         // the name of this symbol
            .st_info = ELF64_ST_INFO(STB_GLOBAL, STT_FUNC),     // global symbol + associated with a function
            .st_other = 0,                                      // reserved
            .st_shndx = 1,                                      // defined in .text section
            .st_value = 0,                                      // section offset
            .st_size = sizeof(TEXT1) / sizeof(char)              // associated size
        }
    };


    // 5 (.rela section)
    Elf64_Rela relatext1[] = {
        {   // message
            .r_offset = 17, // Location at which to apply the action (section offset)
            .r_info = ELF64_R_INFO(2, R_X86_64_64),
            .r_addend = 0
        },
    };

    // 6 (.shstrtab section)
    char shstrtab1[] = {
        '\0',
        '.', 't', 'e', 'x', 't', '\0',
        '.', 'r', 'o', 'd', 'a', 't', 'a', '\0',
        '.', 's', 't', 'r', 't', 'a', 'b', '\0',
        '.', 's', 'y', 'm', 't', 'a', 'b', '\0',
        '.', 'r', 'e', 'l', 'a', '.', 't', 'e', 'x', 't', '\0',
        '.', 's', 'h', 's', 't', 'r', 't', 'a', 'b', '\0'
    };
    int shstrtab_index1[7] = {0, 1, 7, 15, 23, 31, 42};



    // Section Header Table
    Elf64_Shdr section_headers1 [] = {
        {   // .null section
            .sh_type = SHT_NULL,
            .sh_link = SHN_UNDEF,
        },
        {   // .text section
            .sh_name = shstrtab_index1[1],                       // the name of this section
            .sh_type = SHT_PROGBITS,                            // this section holds information defined by the program
            .sh_flags = SHF_ALLOC | SHF_EXECINSTR,              // occupies memory + executable machine instructions
            .sh_addr = 0,                                       // the virtual address where this section will be located
            .sh_offset = sizeof(Elf64_Ehdr),                    // file offset of this section
            .sh_size = sizeof(TEXT1) / sizeof(unsigned char),    // size of this section
            .sh_link = SHN_UNDEF,                               // required by .text section
            .sh_info = 0,                                       // required by .text section
            .sh_addralign = 0,                                  // no alignment constraints
            .sh_entsize = 0                                     // .text doesn't have a table
        },
        {   // .rodata section
            .sh_name = shstrtab_index1[2],
            .sh_type = SHT_PROGBITS,
            .sh_flags = SHF_ALLOC,
            .sh_addr = 0,
            .sh_offset = 110,
            .sh_size = sizeof(message1) / sizeof(char),
            .sh_link = SHN_UNDEF,
            .sh_info = 0,
            .sh_addralign = 0,
            .sh_entsize = 0
        },
        {   // .strtab section
            .sh_name = shstrtab_index1[3],
            .sh_type = SHT_STRTAB,
            .sh_flags = 0,          // no flags
            .sh_addr = 0,
            .sh_offset = 125,
            .sh_size = sizeof(strtab1) / sizeof(char),
            .sh_link = SHN_UNDEF,
            .sh_info = 0,
            .sh_addralign = 0,
            .sh_entsize = 0         // .strtab doesn't have a table of "fixed-size" entries
        },
        {   // .symtab section
            .sh_name = shstrtab_index1[4],
            .sh_type = SHT_SYMTAB,
            .sh_flags = 0,
            .sh_addr = 0,
            .sh_offset = 141,
            .sh_size = sizeof(Elf64_Sym) * 4,
            .sh_link = 3,           // The section header index of the associated stringtable (Unix Systam V specific)
            .sh_info = 3,           // One greater than the symbol table index of thelast local symbol (Unix Systam V specific)
            .sh_addralign = 0,
            .sh_entsize = sizeof(Elf64_Sym)
        },
        {   // .rela.text section
            .sh_name = shstrtab_index1[5],
            .sh_type = SHT_RELA,
            .sh_flags = 0,
            .sh_addr = 0,
            .sh_offset = 237,
            .sh_size = sizeof(Elf64_Rela) * 1,
            .sh_link = 4,           // The section header index of the associated symbol table
            .sh_info = 1,           // The section header index of the section to which the relocation applies
            .sh_addralign = 0,
            .sh_entsize = sizeof(Elf64_Rela)
        },
        {   // .shstrtab section
            .sh_name = shstrtab_index1[6],
            .sh_type = SHT_STRTAB,
            .sh_flags = 0,
            .sh_addr = 0,
            .sh_offset = 261,
            .sh_size = sizeof(shstrtab1),
            .sh_link = SHN_UNDEF,
            .sh_info = 0,
            .sh_addralign = 0,
            .sh_entsize = 0
        }
    };


    // output to hello1.o
    FILE *fp1;
    fp1 = fopen("hello1.o", "ab");

    fwrite(&ehdr1, sizeof(Elf64_Ehdr), 1, fp1);
    fwrite(TEXT1, sizeof(TEXT1), 1, fp1);
    fwrite(message1, sizeof(message1), 1, fp1);
    fwrite(strtab1, sizeof(strtab1), 1, fp1);
    fwrite(symtab1, sizeof(symtab1), 1, fp1);
    fwrite(relatext1, sizeof(relatext1), 1, fp1);
    fwrite(shstrtab1, sizeof(shstrtab1), 1, fp1);
    fwrite(section_headers1, sizeof(section_headers1), 1, fp1);

    fclose(fp1);


    /* hello2.o */

    /*
    0   -----------------------------
                ELF Header
    64  -----------------------------
                .text section
    110  -----------------------------
                .rodata section
    125 -----------------------------
                .strtab section
    141 -----------------------------
                .symtab section
    237 -----------------------------
                .rela.text section
    261 -----------------------------
                .shstrtab section
    313 -----------------------------
                section header table
    */

    /* ELF header */
    Elf64_Ehdr ehdr2 = {
        .e_ident = {ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3,
                    ELFCLASS64,
                    ELFDATA2LSB,
                    EV_CURRENT,
                    ELFOSABI_SYSV,
                    0
                    },
        .e_type = ET_REL,
        .e_machine = EM_X86_64,
        .e_version = EV_CURRENT,
        .e_entry = 0,
        .e_phoff = 0,
        .e_shoff = 313,
        .e_flags = 0,
        .e_ehsize = sizeof(Elf64_Ehdr),
        .e_phentsize = sizeof(Elf64_Phdr),
        .e_phnum = 0,
        .e_shentsize = sizeof(Elf64_Shdr),
        .e_shnum = 7,
        .e_shstrndx = 6,
    };


    /* SECTIONS */
    // 0 (.null Section)

    // 1 (.text Section)
    unsigned char TEXT2[] = {
        0x48, 0xC7, 0xC0, 0x01, 0x00, 0x00, 0x00,       // MOV  RAX, 1 (syscall number for Write)
        0x48, 0xC7, 0xC7, 0x01, 0x00, 0x00, 0x00,       // MOV  RDI, 1 (fildes = stdout)
        0x48, 0xC7, 0xC6, 0x00, 0x00, 0x00, 0x00,       // MOV  RSI, message (the address of the string that will be written)
        0x48, 0xC7, 0xC2, 0x0E, 0x00, 0x00, 0x00,       // MOV  RDX, 14 (the number of bytes to write)
        0x0F, 0x05,                                     // Syscall
        0x48, 0xC7, 0xC0, 0x3C, 0x00, 0x00, 0x00,       // MOV  RAX, 60 (syscall number for Exit)
        0x48, 0xC7, 0xC7, 0x00, 0x00, 0x00, 0x00,       // MOV RDI, 0 (exit(0))
        0x0F, 0x05                                      // Syscall
    };

    // 2 (.rodata section)
    char message2[15] = "Hello, World!\n";

    // 3 (.strtab section)
    char strtab1[] = {'\0', '_', 's', 't', 'a', 'r', 't','\0', 'm', 'e', 's', 's', 'a', 'g', 'e', '\0'};
    int strtab_index1[3] = {0, 1, 8};

    // 4 (.symtab section)
    Elf64_Sym symtab1[] = {
        {   // STN_UNDEF
            .st_shndx = SHN_UNDEF
        },
        {   // .rodata section
            .st_name = 0,
            .st_info = ELF64_ST_INFO(STB_LOCAL, STT_SECTION),
            .st_shndx = 2,
        },
        {
            // message
            .st_name = strtab_index1[2],
            .st_info = ELF64_ST_INFO(STB_LOCAL, STT_OBJECT),
            .st_other = 0,
            .st_shndx = 2,
            .st_value = 0,
            .st_size = sizeof(strtab1) / sizeof(char)
        },
        {   // main function
            .st_name = strtab_index1[1],                         // the name of this symbol
            .st_info = ELF64_ST_INFO(STB_GLOBAL, STT_FUNC),     // global symbol + associated with a function
            .st_other = 0,                                      // reserved
            .st_shndx = 1,                                      // defined in .text section
            .st_value = 0,                                      // section offset
            .st_size = sizeof(TEXT1) / sizeof(char)              // associated size
        }
    };


    // 5 (.rela section)
    Elf64_Rela relatext1[] = {
        {   // message
            .r_offset = 17, // Location at which to apply the action (section offset)
            .r_info = ELF64_R_INFO(2, R_X86_64_64),
            .r_addend = 0
        },
    };

    // 6 (.shstrtab section)
    char shstrtab1[] = {
        '\0',
        '.', 't', 'e', 'x', 't', '\0',
        '.', 'r', 'o', 'd', 'a', 't', 'a', '\0',
        '.', 's', 't', 'r', 't', 'a', 'b', '\0',
        '.', 's', 'y', 'm', 't', 'a', 'b', '\0',
        '.', 'r', 'e', 'l', 'a', '.', 't', 'e', 'x', 't', '\0',
        '.', 's', 'h', 's', 't', 'r', 't', 'a', 'b', '\0'
    };
    int shstrtab_index1[7] = {0, 1, 7, 15, 23, 31, 42};



    // Section Header Table
    Elf64_Shdr section_headers1 [] = {
        {   // .null section
            .sh_type = SHT_NULL,
            .sh_link = SHN_UNDEF,
        },
        {   // .text section
            .sh_name = shstrtab_index1[1],                       // the name of this section
            .sh_type = SHT_PROGBITS,                            // this section holds information defined by the program
            .sh_flags = SHF_ALLOC | SHF_EXECINSTR,              // occupies memory + executable machine instructions
            .sh_addr = 0,                                       // the virtual address where this section will be located
            .sh_offset = sizeof(Elf64_Ehdr),                    // file offset of this section
            .sh_size = sizeof(TEXT1) / sizeof(unsigned char),    // size of this section
            .sh_link = SHN_UNDEF,                               // required by .text section
            .sh_info = 0,                                       // required by .text section
            .sh_addralign = 0,                                  // no alignment constraints
            .sh_entsize = 0                                     // .text doesn't have a table
        },
        {   // .rodata section
            .sh_name = shstrtab_index1[2],
            .sh_type = SHT_PROGBITS,
            .sh_flags = SHF_ALLOC,
            .sh_addr = 0,
            .sh_offset = 110,
            .sh_size = sizeof(message1) / sizeof(char),
            .sh_link = SHN_UNDEF,
            .sh_info = 0,
            .sh_addralign = 0,
            .sh_entsize = 0
        },
        {   // .strtab section
            .sh_name = shstrtab_index1[3],
            .sh_type = SHT_STRTAB,
            .sh_flags = 0,          // no flags
            .sh_addr = 0,
            .sh_offset = 125,
            .sh_size = sizeof(strtab1) / sizeof(char),
            .sh_link = SHN_UNDEF,
            .sh_info = 0,
            .sh_addralign = 0,
            .sh_entsize = 0         // .strtab doesn't have a table of "fixed-size" entries
        },
        {   // .symtab section
            .sh_name = shstrtab_index1[4],
            .sh_type = SHT_SYMTAB,
            .sh_flags = 0,
            .sh_addr = 0,
            .sh_offset = 141,
            .sh_size = sizeof(Elf64_Sym) * 4,
            .sh_link = 3,           // The section header index of the associated stringtable (Unix Systam V specific)
            .sh_info = 3,           // One greater than the symbol table index of thelast local symbol (Unix Systam V specific)
            .sh_addralign = 0,
            .sh_entsize = sizeof(Elf64_Sym)
        },
        {   // .rela.text section
            .sh_name = shstrtab_index1[5],
            .sh_type = SHT_RELA,
            .sh_flags = 0,
            .sh_addr = 0,
            .sh_offset = 237,
            .sh_size = sizeof(Elf64_Rela) * 1,
            .sh_link = 4,           // The section header index of the associated symbol table
            .sh_info = 1,           // The section header index of the section to which the relocation applies
            .sh_addralign = 0,
            .sh_entsize = sizeof(Elf64_Rela)
        },
        {   // .shstrtab section
            .sh_name = shstrtab_index1[6],
            .sh_type = SHT_STRTAB,
            .sh_flags = 0,
            .sh_addr = 0,
            .sh_offset = 261,
            .sh_size = sizeof(shstrtab1),
            .sh_link = SHN_UNDEF,
            .sh_info = 0,
            .sh_addralign = 0,
            .sh_entsize = 0
        }
    };


    // output to hello1.o
    FILE *fp1;
    fp1 = fopen("hello1.o", "ab");

    fwrite(&ehdr1, sizeof(Elf64_Ehdr), 1, fp1);
    fwrite(TEXT1, sizeof(TEXT1), 1, fp1);
    fwrite(message1, sizeof(message1), 1, fp1);
    fwrite(strtab1, sizeof(strtab1), 1, fp1);
    fwrite(symtab1, sizeof(symtab1), 1, fp1);
    fwrite(relatext1, sizeof(relatext1), 1, fp1);
    fwrite(shstrtab1, sizeof(shstrtab1), 1, fp1);
    fwrite(section_headers1, sizeof(section_headers1), 1, fp1);

    fclose(fp1);


    return 0;
}
