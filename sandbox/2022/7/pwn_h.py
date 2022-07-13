#!/bin/python3
# functions needed across projects that make vulnerability research easier
from pwn import *

import argparse, struct
import sys, traceback

if len(sys.argv) != 3 or sys.argv[1] != "-f":
    print(f"[!] Usage: python -i {sys.argv[0]} -f FILE_NAME")
elif sys.argv[1] == "-f":
    context = ELF(f"{sys.argv[2]}")

PAYLOAD_FNAME = "test_32.txt"
options = {
    0:"disassemble(WHAT,N_BYTES)",
    1:"list_functions()",
    2:"list_symbols()",
    3:"save_payload(PAYLOAD)",
    4:"read_payload(F_NAME) -> PAYLOAD",
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

def list_functions():
    print("\nFUNCTION_NAME (FUNCTION_SIZE)\n")
    for f_name,f_info in context.functions.items():
        print(f"[*]\t{f_name} ({hex(f_info.size)} bytes)")

def list_symbols():
    print("\nSYMBOL_NAME (SYMBOL_ADDRESS)\n")
    for s_name,s_addr in context.symbols.items():
        print(f"[*]\t{s_name} ({hex(s_addr)})")

def save_payload(payload):
    payload = str(payload)[2:-1]
    p = process(f"python2.7 -c 'print \"{payload}\"' > {PAYLOAD_FNAME}",
        shell=True, stderr=open('/dev/null', 'w+b'))
    # p.close()

def read_payload(f_name):
    fd = open(f_name, "r", errors="backslashreplace")
    payload = "".join( line for line in fd.readlines() )
    fd.close()
    return payload
