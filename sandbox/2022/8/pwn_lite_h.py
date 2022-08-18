# -*- coding: utf-8 -*-
#!/bin/python3
# functions needed across projects that make vulnerability research easier
from os import path, system
import re, struct, sys, traceback

bin = None
if len(sys.argv) != 3 or sys.argv[1] != "-f":
    print(f"[!] Usage: python -i {sys.argv[0]} -f FILE_NAME")
elif sys.argv[1] == "-f":
    bin_path = sys.argv[2]
    if path.exists(bin_path):
        try:
            with open(bin_path,"r+b") as fd:
                bin = fd.read()
        except:
            print("[x] {traceback.format_exc()}")
            sys.exit(-1)

PAYLOAD_FNAME = "test_32.txt"
BIN = None
SECTIONS = {}

options = {
    0:"dump_bin(START=0,END=-1)",
    1:"search(WHAT) -> START,END",
    2:"write(WHAT,WHERE) (i.e. - write(struct.pack(\">I\",0xdeadbeef),0))",
    3:"read_payload(F_NAME)",
    4:"save_payload(PAYLOAD)",
    8:"help()"
}

def help():
    print("\nPWN_H.FUNCTION_NAME (ARG_0,...,ARG_N)\n")
    for k in options:
        print(f"[*] {options[k]}")

def dump_bin(start=0,end=-1):
    print(bin[start:end])

get_match = lambda m: m.span()
def search(what):
    match_idxs = []
    if isinstance(what,bytes):
        match_idxs = list(map(get_match,list(re.finditer(what,bin))))
    else:
        print(f"[!] Usage: search( [ BYTES ] )")
    return match_idxs

def read_payload(f_name):
    payload = None
    try:
        with open(f_name, "rb") as fd:
            payload = fd.read()
    except:
        print(f"[x] {traceback.format_exc()}")
    return payload

def save_payload(payload):
    payload = str(payload)[2:-1]
    try:
        system(f"""python2.7 -c 'print \"{payload}\"' > {PAYLOAD_FNAME}""")
    except:
        print(f"[x] {traceback.format_exc()}")

def write(what,where):
    try:
        with open(bin_path,"r+b") as fd:
            fd.seek(where)
            fd.write(what)
    except:
        print(f"[x] {traceback.format_exc()}")

help()
