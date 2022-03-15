/*
    Practical Binary Analysis
    Chapter 4
    Basic Binary Loader API
    Compile: g++ -std=c++17 -o loader_demo3 loader_demo3.cc loader.o -lbfd
*/
#include <errno.h>
#include <exception>
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include "loader.h"

using sectionsMap = std::map<uint16_t, const char*>;

int main(int argc, char** argv){
    size_t i;
    Binary bin;
    Section *sec;
    Symbol *sym;
    std::string fname;
    sectionsMap sections;

    if(argc < 2){
        printf("[*] Usage: %s <binary>\n", argv[0]);
        return 1;
    }

    fname.assign(argv[1]);
    if(load_binary(fname, &bin, Binary::BIN_TYPE_AUTO) < 0){
        return 1;
    }

    printf("[*] loaded binary '%s' %s/%s (%u bits) entr@0x%016jx\n",
        bin.filename.c_str(),
        bin.type_str.c_str(),
        bin.arch_str.c_str(),
        bin.bits, bin.entry);

    for(i = 0; i < bin.sections.size(); i++){
        sec = &bin.sections[i];
        // printf(" 0x%016jx %-8ju %-20s %s\n",
        // sec->vma, sec->size, sec->name.c_str(),
        // sec->type == Section::SEC_TYPE_CODE ? "CODE" : "DATA");
        sections[i] = sec->name.c_str();
    }

    if(bin.symbols.size() > 0){
        printf("[*] scanned symbol tables\n");
        for(i = 0; i < bin.symbols.size(); i++){
            sym = &bin.symbols[i];
            printf(" %-40.32s 0x%016jx %s\n",
                sym->name.c_str(), sym->addr,
                (sym->type & Symbol::SYM_TYPE_FUNC) ? "FUNC" :
                    (sym->type & Symbol::SYM_TYPE_LOCAL) ? "LOCAL" :
                        (sym->type & Symbol::SYM_TYPE_GLOBAL) ? "GLOBAL" : "");
        }
    }

    // printf("[*] What section would you like to dump (enter #):\n");
    // std::string userInput_str = "";
    // uint16_t userInput_int = 0;
    // for(auto it = sections.begin(); it != sections.end(); it++){
    //     printf("[*] %d: %s\n",
    //             it->first,
    //             it->second);
    // }

    // Section* section = NULL;
    // std::string sectionName = "";
    // std::cout << "\nuser> ";
    // try{
    //     std::cin >> userInput_str;
    //     userInput_int = atoi(userInput_str.c_str());
    //     sectionName = (std::string)sections[userInput_int];
    //     section = bin.get_section(sectionName);
    //     dump_section(section);
    // }catch(std::exception& e){
    //     printf("[x] Invalid entry!");
    // }

    unload_binary(&bin);

    return 0;
}
