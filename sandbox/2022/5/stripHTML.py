# -*- coding: utf-8 -*-
#!/bin/python3
# author: bryan kanu
# description: 
#   this is a program to strip html tags. I use it to get the text 
#   from blog articles so I can listen (currently using https://ttsreader.com/) to them and multi-task.
# note:
#   this is a stable, dirty version of what is a work in progress; 
#   as more files are consumed, it will be improved.
import argparse, copy, html
import os, re, sys, traceback
from collections import deque
from pathlib import Path

usage = f"""Usage: {sys.argv[0]} -f <file>.html"""

tag_t = {
0:"title",
1:"p",
2:"a",
3:"b",
4:"em",
5:"i",
6:"img",
7:"figure",
8:"strong",
9:"li",
10:"div",
11:"ol",
12:"ul"
}

# a function for looking up the index of HTML element tag indexes in tag_t
index = lambda v: list(tag_t.values()).index(v)

cout_t = {"info":"*","error":"x","success":"✓","debug":"DEBUG","warn":"!"}
def cout(message_type,message):
    print(f"[{cout_t[message_type]}] {message}")

def flatten(lines):
    return [line for lst in lines for line in lst]

# deflate removes empty elements from a list
deflate = lambda lst: list(filter((lambda l: l != ""),lst))

# normalize a unicode string and remove escape bytes
normalize = lambda line: line.encode("ascii","ignore").decode("ascii","ignore")

# function to add a newline character to a line with multiple tags
# i.e. <h4 style="text-align: left;"><strong>3 </strong>&#8212; <strong>Collection</strong></h4><ol>
addNewline = lambda line: line.replace("><",">\n<")

# regular expression to find html tags
singleOpeningTag = lambda line: re.match("(<.*?>){0,1}([\s\S]+){0,}",line)
singleClosingTag = lambda line: re.match("([\s\S]+){1}(<.+>?){1}",line)
multiTagLine = lambda line: re.search("([\s\S]+)?(<.+?>){1}",line)

# a function to dispatch calls to singleOpeningTag and singleClosingTag lambdas
def tagDispatcher(**kwargs):
    ret = []
    for line in kwargs["list"]:
        if not line:
            ret.append("")
            continue
        elif line == "":
            ret.append(line)
            continue
        m = kwargs["f"](line)
        if m:        
            ret.append(m.group(kwargs["mPos"]))
    return ret

# strip html encoding
def stripEncoding(line):
    tmp = re.search("&\S+;",line)
    if tmp:
        x = tmp.span()[0]; y = line.find(";")
        if y > x:
            tmpLine = line[0:x] + line[y+1:]
        #cout("info",f"[stripEncoding] tmp.span(): {tmp.span()} | tmpLine: {tmpLine}")
        return stripEncoding(tmpLine)
    return line

def getBlankElementsInRange(blanks, start, end):
    tmp = []
    for idx,e in enumerate(blanks):
        if idx <= start or idx >= end:
            tmp.append(e)
    return tmp

# a function for looking up the index of HTML element tag indexes in tag_t
def lookupKey(dct,value):
    for k,v in dct.items():
        if value == v:
            return k

# function to calculate the distance of the largest number 
# of consecutive empty strings in the state object
DISTANCE_TRESHOLD = 0x8
def getDistance(blanks):
    # cout("info",f"blanks: {blanks}")
    distanceObj = {"s_idx":-1,"e_idx":-1,"value":0,"maxDistance":0}
    startIdx = blanks[0]; tmpDict = {startIdx:0};
    for idx in range(1,len(blanks)):
        tmp = blanks[idx] - blanks[idx-1]
        if tmp == 1:
            tmpDict[startIdx] += 1           
        else:
            startIdx = blanks[idx]
            tmpDict.update({startIdx:0})
            distanceObj["s_idx"] = idx-1

    # cout("debug",f"distances: {tmpDict}")
    maxDistance = max(tmpDict.values())
    distanceObj["maxDistance"] = maxDistance
    distanceObj["s_idx"] = blanks.index(lookupKey(tmpDict,maxDistance))
    distanceObj["e_idx"] = distanceObj["s_idx"] + maxDistance
    # cout("debug",f"maxDistance: {maxDistance}")
    # cout("debug",f"s_idx: {distanceObj['s_idx']}")
    # cout("debug",f"e_idx: {distanceObj['e_idx']}")
    # cout("debug",
        # f"largest gap in blanks starts at {distanceObj['s_idx']} until {distanceObj['e_idx']}")
    return distanceObj

def getStatesIndexes(state):
    blanks = []
    x = -1; y = -1;
    for idx in range(0,len(state)):
        if state[idx] != "":
            x = idx
            break
    for idx in range(len(state)-1,0,-1):
        if state[idx] != "":
            y = idx
            break
    for idx in range(x,y):
        if state[idx] == "":            
            # cout("debug",f"{idx}) {state[idx]}")
            # if state[idx+1] != "":
                # cout("debug",f"{idx+1}) {state[idx+1]}")
            blanks.append(idx)

    distanceObj = getDistance(blanks)
    blanks = getBlankElementsInRange(blanks,distanceObj["s_idx"],distanceObj["e_idx"])
    blanks.sort()
    #cout("debug",f"(x={x},y={y})")
    #cout("debug",f"state[{x}]: {state[x]}")
    #cout("debug",f"state[{y}]: {state[y]}")
    # cout("debug",f"blanks: {blanks}")
    #cout("debug",f"distanceObj: {distanceObj}")
    return x,y,blanks,distanceObj["s_idx"],distanceObj["e_idx"]

def replace(**kwargs):
    idx = kwargs["idx"]
    kwargs["state"][idx] = kwargs["value"]

def stripTagDispatcher(lines):
    state = [stripOutterTag(line,tag_t[index("title")]) for line in lines]
    try:
        title = deflate(state)[0]
        cout("info",f"Title: {title}")
    except:
        pass
    state = [stripOutterTag(line,tag_t[index("p")]) for line in lines]
    state = [stripInnerTag(line,tag_t[index("em")]) for line in state]
    state = [stripInnerTag(line,tag_t[index("a")]) for line in state]
    state = [stripInnerTag(line,tag_t[index("b")]) for line in state]
    state = [stripInnerTag(line,tag_t[index("strong")]) for line in state]
    state = [stripSelfClosingTag(line,tag_t[index("img")]) for line in state]

    htmlBodyStart,htmlBodyEnd,emptyLinesIdxList,emptyLinesListStartIdx,emptyLinesListEndIdx = getStatesIndexes(state)
    emptyLinesIdxListCpy = copy.deepcopy(emptyLinesIdxList)
    # cout("debug",f"{emptyLinesIdxListCpy}")
    [ replace(**{"state":emptyLinesIdxList,"idx":idx,"value":lines[e]}) for idx,e in enumerate(emptyLinesIdxList) ]
    emptyLinesIdxList = tagDispatcher(**{"f":singleOpeningTag,"list":emptyLinesIdxList,"mPos":2})
    emptyLinesIdxList = tagDispatcher(**{"f":singleClosingTag,"list":emptyLinesIdxList,"mPos":1})
    emptyLinesIdxList = list(map(inlineHTMLElementStrip, emptyLinesIdxList))
    # cout("debug",f"{state}")
    # cout("debug",f"{htmlBodyStart} | {htmlBodyEnd} | {emptyLinesListStartIdx} | {emptyLinesListEndIdx} | {emptyLinesIdxList}")
    [ replace(**{"state":state,"idx":yIdx,"value":emptyLinesIdxList[xIdx]}) for xIdx,yIdx in enumerate(emptyLinesIdxListCpy) ]

    if state[0] == "" and title:
        state[0] = title
    elif title:
        state.insert(0,title)
    state = list(map(html.unescape,state))
    state = list(map(normalize,state))
    state = deflate(state)
    return state

def stripOutterTag(line, tag):
    outterPattern = re.compile(f"^<{tag}[\s]*>(.*)<\s*/{tag}>$")
    tmp = re.match(outterPattern,line)
    if tmp:
        # debug
        #[cout("info",f"[stripOutterTag][*{i}*] {tmp[i]}") for i in range(0,len(tmp.groups())+1)]
        # debug
        try:
            return tmp[1]
        except:
            cout("error",f"exception on line: {line}")
            cout("error", traceback.format_exc())
    return ""

def stripInnerTag(line, tag):
    innerPattern = re.compile(f"^(.*)<{tag}[\s\S]*>(.*)<\s*/{tag}>(.*)$")
    tmp = re.match(innerPattern,line)
    if tmp:
        # debug
        #[cout("info",f"[stripInnerTag][*{i}*][tag=\"{tag}\"] {tmp[i]}") for i in range(0,len(tmp.groups())+1)]
        # debug
        try:
            ret = tmp[1] + tmp[2] + tmp[3]
            return stripInnerTag(ret,tag)
        except:
            cout("error",f"exception on line: {line}")
            cout("error", traceback.format_exc())
    return line

def stripSelfClosingTag(line, tag):
    tagPattern = re.compile(f"<{tag}[\s\S]*/*>")
    tmp = re.search(tagPattern,line)
    if tmp:
        x = tmp.span()[0]
        y = tmp.span()[1]
        tmpLine = line[0:x] + line[y:]
        # debug
        cout("info",f"tmpLine: {tmpLine} | tmp.span(): {tmp.span()} | x: {x}, y: {y}")
        # debug
        try:
            return tmpLine
        except:
            cout("error",f"exception on line: {line}")
            cout("error", traceback.format_exc())
    return line

def swapIfNeeded(s,e):
    if s > e:
        tmp = e
        e = s
        s = tmp
    return s,e

def deHTMLify(**kwargs):
    ret = kwargs["listWord"]
    for idx, c in enumerate(ret):
        if idx >= kwargs["s"] and idx <= kwargs["e"]:
            ret[idx] = ""
        if idx == kwargs["e"]:
            break
    return "".join(ret)

multilineFlag = False
def inlineHTMLElementStrip(line):
    global multilineFlag
    # cout("info", f"Starting with: {line}")
    s = line.find("<"); e = line.find(">")
    if s == -1 and e == -1:
        if not multilineFlag or line == "":
            return line
        elif multilineFlag and line != "":
            s = 0; e = len(line)-1;
    elif s != -1 and e == -1:
        multilineFlag = True
        e = len(line)-1
    elif s == -1 and e != -1:
        multilineFlag = False
        s = 0
    listWord = list(line)
    s,e = swapIfNeeded(s,e)
    listWord = deHTMLify(**{"listWord":listWord,"s":s,"e":e})
    #cout("debug",f"Recursing with: {listWord}")
    return inlineHTMLElementStrip(listWord)

def main(argv):
    if sys.argv[1] != "-f" or len(sys.argv) != 3:
        cout("error",f"{usage}")
        return

    in_file = sys.argv[2]
    try:
        with open(in_file, "r") as fd:
            lines = [ line.strip() for line in fd.readlines() ]

        lines = flatten([ addNewline(line).split("\n") for line in lines ])
        state = stripTagDispatcher(lines)
        # state = list(map(inlineHTMLElementStrip, state))
        # cout("debug",f"{state}")

        with open(out_file, "w") as fd:
            [ fd.write(f"{line}\n") for line in state ]
    except:
        cout("error",f"{traceback.format_exc()}")

if __name__ == '__main__':
    out_file = "output.txt"
    cout("success","Running.")
    main(sys.argv)
    cout("success",f"Done. Check {out_file}.")
