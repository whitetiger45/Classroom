/*
    Practical Binary Analysis
    Chapter 4
    Basic Binary Loader API
*/
#ifndef LOADER_H
#define LOADER_h

#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_map> /* ch. 4, Ex 2-3 */

class Binary;
class Section;
class Symbol;
using SymbolsRefDict = std::unordered_map<std::string,uint32_t>; /* ch. 4, Ex 2-3 */
using SymbolRefDictIterator = SymbolsRefDict::iterator; /* ch. 4, Ex 2-3 */

class Symbol{
    public:
        enum SymbolType{
            SYM_TYPE_UKN = 0,
            SYM_TYPE_FUNC = 1,
            SYM_TYPE_LOCAL = 2, /* ch. 4, Ex 3 */
            SYM_TYPE_GLOBAL = 3, /* ch. 4, Ex 2 */
            SYM_TYPE_WEAK = 4 /* ch. 4, Ex 3 */
        };
        
        Symbol() : type(SYM_TYPE_UKN), name(), addr(0) {}

        SymbolType type;
        std::string name;
        uint64_t addr;
};

class Section{
    public:
        enum SectionType{
            SEC_TYPE_NONE = 0,
            SEC_TYPE_CODE = 1,
            SEC_TYPE_DATA = 2
        };

        Section() : binary(NULL), type(SEC_TYPE_NONE),
                vma(0), size(0), bytes(NULL) {}

        bool contains(uint64_t addr) { return (addr >= vma) && (addr-vma < size); }
        void getSectionBytes() {
            for(uint64_t i{0}; i < size; i++){
                if(i%8 == 0 && i != 0) printf(" ");
                printf("%x", bytes[i]);
            }
            printf("\n");
        }

        Binary *binary;
        std::string name;
        SectionType type;
        uint64_t vma;
        uint64_t size;
        uint8_t *bytes;
};

class Binary{
    public:
        enum BinaryType{
            BIN_TYPE_AUTO = 0,
            BIN_TYPE_ELF = 1,
            BIN_TYPE_PE = 2
        };

        enum BinaryArch{
            ARCH_NONE = 0,
            ARCH_X86 = 1
        };

        Binary() : type(BIN_TYPE_AUTO), arch(ARCH_NONE),
                bits(0), entry(0) {}

        Section *get_text_section()
        { for(auto &s : sections) if(s.name == ".text") return &s; return NULL; }

        Section *get_section(std::string secName)
        { for(auto &s : sections) if(s.name == secName) return &s; return NULL; }

        std::string filename;
        BinaryType type;
        std::string type_str;
        BinaryArch arch;
        std::string arch_str;
        unsigned bits;
        uint64_t entry;
        std::vector<Section> sections;
        std::vector<Symbol> symbols;
        SymbolsRefDict syms_ref_dict; /* ch. 4, Ex 2 */
        SymbolRefDictIterator syms_ref_dict_it; /* ch. 4, Ex 2 */
        uint32_t syms_ref_dict_idx = 0; /* ch. 4, Ex 2 */
};

int load_binary(std::string &fname, Binary *bin, Binary::BinaryType type);
void unload_binary(Binary *bin);
void dump_section(Section *section);
Symbol* get_symbol(Binary *bin, std::string sym_key);

#endif /* LOADER_h */
