#!/bin/python
# -*- coding: utf-8 -*-
from pathlib import Path
import json, traceback

class Evocatio:
    def __init__(self,maxDepth = 3):
        self._objects = []
        self._maxDepth = maxDepth

    def evocatio(self,root,lvl=0,keys=[]):
        try:            
            if hasattr(root,"items"):
                for k,v in root.items():
                    try:
                        if keys and k in keys:
                            self._objects.append({k:v})
                        if (hasattr(v,"items") or hasattr(v,"index")) and lvl <= self._maxDepth:
                            self.evocatio(v,lvl+1,keys)
                    except:
                        print(f"[!] {traceback.format_exc()}")
            else:
                if hasattr(root,"index"):
                    for element in root:
                        try:
                            if lvl <= self._maxDepth:
                                self.evocatio(element,lvl+1,keys)
                        except:
                            print(f"[!] {traceback.format_exc()}")
                else:
                    print(f"[!] root object {root} is of type {type(root)}. update method for this type.")
        except:
            print(f"[x] {traceback.format_exc()}")
        return self._objects

    def readJSON(self,fn):
        fd = fn; data = None
        try:
            if not isinstance(fd,Path):
                fd = Path(fd)
            if fd.exists() and fd.is_file():
                data = json.loads(fd.read_text())
        except:
            print(f"[x] {traceback.format_exc()}")
        return data

    def reset(self):
        try:
            print(f"[*] Resetting objects list")
            self._objects.clear()
        except:
            print(f"[x] {traceback.format_exc()}")

    def setMaxDepth(self,depth):
        self._maxDepth = depth

    def show(self):
        try:
            print(f"[*] Objects:\n")
            print(json.dumps(self._objects,indent=4))
        except:
            print(f"[x][show] {traceback.format_exc()}")
