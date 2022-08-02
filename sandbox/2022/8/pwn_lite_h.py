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
    0:"dump_bin(START=NONE,END=NONE)",
    1:"search(WHAT) -> START,END",
    2:"write(WHAT,WHERE) (i.e. - write(struct.pack(\">I\",0xdeadbeef),0))",
    3:"list_sections()",
    8:"help()"
}

def help():
    print("\nPWN_H.FUNCTION_NAME (ARG_0,...,ARG_N)\n")
    for k in options:
        print(f"[*] {options[k]}")

def dump_bin(start=0,end=-1):
    print(bin[start:end])

def list_sections():
    print("\nSECTION_NAME (SECTION_OFFSET, SECTION_SIZE)\n")
    for section in bin.sections:
        print(f"[*]\t{section.name} (offset: {hex(section.header['sh_offset'])}, size: {hex(section.header['sh_size'])})")

get_match = lambda m: m.span()
def search(what):
    match_idxs = []
    if isinstance(what,bytes):
        match_idxs = list(map(get_match,list(re.finditer(what,bin.data))))
    else:
        print(f"[!] Usage: search( [ BYTES ] )")
    return match_idxs

def write(what,where):
    try:
        with open(bin_path,"r+b") as fd:
            fd.seek(where)
            fd.write(what)
    except:
        print(f"[x] {traceback.format_exc()}")

help()
