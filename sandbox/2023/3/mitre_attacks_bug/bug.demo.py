#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# authors: bryan kanu
import json
import re
import sys
import traceback
from pathlib import Path

buffer = 200; # 2* buffer is roughly the size of the result preview
LOOP_START = -1; LOOP_MAX = 18 # Added for the purpose of killing the infinite loop, since this is just a PoC
SEARCH_STR = ""
log_path = Path("mitre.attack.bug.sim.log")
log_str = ""

def query(querystr):
    this_current_query = querystr.split()
    return this_current_query

def append_info_to_log_str(__what__):
    global log_str
    log_str += f"{__what__}\n"

def save_log_str():
    global log_str
    log_path.write_text(log_str)

def reset_vars():
    global LOOP_START, log_str
    log_str = ""; LOOP_START = -1

def result_to_html(content):
    global LOOP_START    
    positions = []
    try:
        positions = [ (content.rindex(x),x) for x in query(SEARCH_STR) ]
    except:
        return
    LOOP_START += 1
    append_info_to_log_str(f"[NOTE] # OF ITERATIONS: {LOOP_START}")    
    if LOOP_START > LOOP_MAX:
        return
    positions.sort()
    all_words = set(map((lambda __pair: __pair[1]),positions))    
    for n,position in enumerate(positions):                
        found_words = set()
        found_words.add(position[1])
        if all_words == found_words:
            append_info_to_log_str(f"\tBREAKING B/C ALLWORDS == FOUNDWORDS")
        else:
            append_info_to_log_str(f"\tNOT BREAKING B/C ALLWORDS != FOUNDWORDS")
        # search around this word
        for m in range(0,len(positions)):
            append_info_to_log_str(f"\tpositions[{m}]: {positions[m]}")
            append_info_to_log_str(f"\t#1 RESULT OF CONDITIONAL: {n} + {m} < {len(positions)} || {n} - {m} > 0: {(n+m<len(positions)) or (n - m > 0)}")
            if n + m < len(positions) or n - m > 0:
                # search idx_j ahead
                exceeded = 0
                append_info_to_log_str(f"\tEXCEEDED: {exceeded}")
                if n + m < len(positions) - 1:
                    append_info_to_log_str(f"\t#2 RESULT OF CONDITIONAL: {n} + {m} < {len(positions)-1}: {(n+m<len(positions)-1)}")
                    ahead_idx,ahead_word = positions[n+m]
                    dist = ahead_idx - position[0]
                    append_info_to_log_str(f"\tAHEAD_IDX: {ahead_idx}, AHEAD_WORD: {ahead_word} (DIST: {dist})")
                    if dist > buffer: # exceeded buffer
                        exceeded += 1
                        append_info_to_log_str(f"\t#1 INCREMENTED EXCEEDED: {exceeded}")
                    elif ahead_word not in found_words: # found a word
                        found_words.add(ahead_word)
                        append_info_to_log_str(f"\t#1 ADDED WORD TO FOUNDWORDS: {found_words}")
                append_info_to_log_str(f"\t#3 RESULT OF CONDITIONAL: {n} - {m} >= 0: {(n - m >= 0)}")
                if n - m >= 0: # search j behind
                    behind_idx,behind_word = positions[n - m]
                    dist = position[0] - behind_idx
                    append_info_to_log_str(f"\tBEHIND_IDX: {behind_idx}, BEHIND_WORD: {behind_word} (DIST: {dist})")
                    if dist > buffer: # exceeded buffer
                        exceeded += 1
                        append_info_to_log_str(f"\t#2 INCREMENTED EXCEEDED: {exceeded}")
                    elif behind_word not in found_words: # found a word
                        found_words.add(behind_word)
                        append_info_to_log_str(f"\t#2 ADDED WORD TO FOUNDWORDS: {found_words}")
                else:
                    append_info_to_log_str(f"\tNOT ENTERING SEARCH J BEHIND B/C: {n} - {m} >= 0: {(n - m >= 0)}")
                if all_words == found_words or exceeded == 2: # found all the words in proximity, or both searches exceeded the buffer
                    if all_words == found_words:
                        append_info_to_log_str(f"\tBREAKING B/C ALLWORDS == FOUNDWORDS")
                    else:
                        append_info_to_log_str(f"\tBREAKING B/C EXCEEDED == {exceeded}")
                    break
                else:
                    append_info_to_log_str(f"\tNOT BREAKING B/C ALLWORDS != FOUNDWORDS && EXCEEDED != 2")

if __name__ == "__main__":
    index_json_data = json.loads(Path("resources/commit_history_src/b27b47a40d844ed208c5d6a3f54d9532a8960569.index.json").read_text())
    content_data = list(map((lambda e: e["content"]),index_json_data))
    print(f"[*] Starting simulation of attack.mitre bug")
    if sys.argv[1] == "-q":
        SEARCH_STR = sys.argv[2]
    else:
        SEARCH_STR = "in a network"
    list(map(result_to_html,content_data))
    print(f"[*] Saving debug strings to {log_path}")
    save_log_str()
    print(f"[*] Finished.")
