#!/bin/python3
# functions needed across projects that make vulnerability research easier
from pwn import *

import argparse, re
import struct, sys, traceback

if len(sys.argv) != 3 or sys.argv[1] != "-f":
    print(f"[!] Usage: python -i {sys.argv[0]} -f FILE_NAME")
elif sys.argv[1] == "-f":
    bin_path = sys.argv[2]
    bin = read(f"{bin_path}")

PAYLOAD_FNAME = "test_32.txt"
BIN = None
SECTIONS = {}

options = {
    0:"dump_bin(START=0,END=-1)",
    1:"search(WHAT) -> START,END",
    2:"write(WHAT,WHERE) (i.e. - write(struct.pack(\">I\",0xdeadbeef),0))",
    # 3:"list_sections()",
    # 4:"print_section(SECTION_NAME)",
    8:"help()"
}

def help():
    print("\nPWN_H.FUNCTION_NAME (ARG_0,...,ARG_N)\n")
    for k in options:
        print(f"[*] {options[k]}")

def dump_bin(start=0,end=-1):
    print(bin[start:end])

# def list_sections():
#     print("\nSECTION_NAME (SECTION_OFFSET, SECTION_SIZE)\n")
#     for section_name,section in SECTIONS.items():
#         print(f"[*]\t{section_name} (offset: {hex(section.header['sh_offset'])}, size: {hex(section.header['sh_size'])})")

# def print_section(section_name):
#     try:
#         print(f"[*]\n{SECTIONS[section_name].data()}")
#     except:
#         print(f"[x] {traceback.format_exc()}")

get_match = lambda m: m.span()
def search(what):
    match_idxs = []
    if isinstance(what,bytes):
        match_idxs = list(map(get_match,list(re.finditer(what,bin))))
    else:
        print(f"[!] Usage: search( [ BYTES ] )")
    return match_idxs

# def set_sections():
#     [ SECTIONS.update({section.name:section}) for section in bin.sections ]

def write(what,where):
    try:
        with open(bin_path,"r+b") as fd:
            fd.seek(where)
            fd.write(what)
    except:
        print(f"[x] {traceback.format_exc()}")

# set_sections()
help()
