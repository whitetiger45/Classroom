#! /usr/bin/python3
# -*- coding: utf-8 -*-
#
# last modified: 1/8/2022
#
# Purpose: this example is something I want to be able to reference in the future.
# python does not natively support the switch construct like other programming languages.
# the following PoC is just one of the few ways such a construct can be implemented.
import re, sys
import traceback

SWITCH = { 
"list": lambda csv : csv.split(","),
"set": lambda csv : set(csv.split(",")),
"default": lambda other : f"Are you aware that {other} is not a csv?"
}

USAGE = f"""
Usage:
{sys.argv[0]} --list <comma separated list of whatever (numbers, strings, dates, etc.)>
{sys.argv[0]} --set <comma separated list of whatever (numbers, strings, dates, etc.)>
"""
try:
    if len(sys.argv) != 3 or sys.argv[1].split("--")[1] not in SWITCH.keys():
        print(f"{USAGE}")
    else:
        case = re.match(r"--(.*)",sys.argv[1]).group(1)
        try:
            csv = sys.argv[2]
            print(f"\nPoC Result> {SWITCH[case](csv)}\n")
        except:
            try:
                case = "default"
                print(f"\nPoC Result> {SWITCH[case](csv)}\n")
            except:
                sys.exit(f"\n{traceback.format_exc()}")
except:
    sys.exit(f"\n{traceback.format_exc()}")
