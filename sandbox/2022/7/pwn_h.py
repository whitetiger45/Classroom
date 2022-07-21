#!/bin/python3
# functions needed across projects that make vulnerability research easier
from pwn import *

import argparse, struct
import sys, traceback

if len(sys.argv) != 3 or sys.argv[1] != "-f":
    print(f"[!] Usage: python -i {sys.argv[0]} -f FILE_NAME")
elif sys.argv[1] == "-f":
    context = ELF(f"{sys.argv[2]}")

DYNELF = None
PAYLOAD_FNAME = "test_32.txt"
PROC = None

options = {
    0:"disassemble(WHAT,N_BYTES)",
    1:"list_functions()",
    2:"list_symbols()",
    3:"save_payload(PAYLOAD)",
    4:"read_payload(F_NAME) -> PAYLOAD",
    5:"list_libraries()",
    6:"start_proc() -> PROC",
    7:"load_dyn_lib(DYN_LIB_PATH) -> DYNELF",
    8:"list_dyn_functions()",
    9:"help()"
}

def help():
    print("\nPWN_H.FUNCTION_NAME (ARG_0,...,ARG_N)\n")
    for k in options:
        print(f"[*] {options[k]}")

def disassemble(what,n_bytes):
    try:
        if isinstance(what,str):
            print(f"{context.disasm(context.sym[what],n_bytes)}")
        elif isinstance(what,int):
            print(f"{context.disasm(what,n_bytes)}")
    except:
        print(f"[x] {traceback.format_exc()}")

def leak(address):
    data = PROC.elf.read(address, 4)
    log.debug("%#x => %s", address, enhex(data or b''))
    return data

def list_dyn_functions():
    if DYNELF:
        print("\nDYNFUNCTION_NAME (DYNFUNCTION_ADDRESS)\n")
        for df_name,df_info in DYNELF.elf.sym.items():
            print(f"[*]\t{df_name} ({hex(df_info)})")
    else:
        print("[!] No dynamic library loaded. Call load_dyn_lib(DYN_LIB_PATH) first then try again")

def list_functions():
    print("\nFUNCTION_NAME (FUNCTION_SIZE)\n")
    for f_name,f_info in context.functions.items():
        print(f"[*]\t{f_name} ({hex(f_info.size)} bytes)")

def list_libraries():
    print("\nLIBRARY_NAME (LIBRARY_ADDRESS)\n")
    for lib_name,lib_addr in context.libs.items():
        print(f"[*]\t{lib_name} ({hex(lib_addr)})")

def list_symbols():
    print("\nSYMBOL_NAME (SYMBOL_ADDRESS)\n")
    for s_name,s_addr in context.symbols.items():
        print(f"[*]\t{s_name} ({hex(s_addr)})")

def load_dyn_lib(dyn_lib_path):
    global DYNELF
    if not PROC:
        start_proc()
    DYNELF = DynELF(leak,PROC.elf.sym["main"],elf=ELF(dyn_lib_path))

def read_payload(f_name):
    fd = open(f_name, "r", errors="backslashreplace")
    payload = "".join( line for line in fd.readlines() )
    fd.close()
    return payload

def save_payload(payload):
    payload = str(payload)[2:-1]
    p = process(f"python2.7 -c 'print \"{payload}\"' > {PAYLOAD_FNAME}",
        shell=True, stderr=open('/dev/null', 'w+b'))
    # p.close()

def start_proc():
    global PROC
    PROC = process(context.path)
