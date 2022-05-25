# -*- coding: utf-8 -*-
#!/bin/python
# author: bryan kanu
# description: 
#   this program simply reads an input file containing urls, 
#   uses the command line utility wget to download that resource, 
#   and then dispatches stripHTML.py on the downloaded blob.
#   only the text of the blog articles will be written to the output
#   file. 
# note:
#   this is a stable, dirty version of what is a work in progress; 
#   as more files are consumed, it will be improved.
import urllib.request
import os, re, traceback

from subprocess import call

cout_t = {"info":"*","error":"x","success":"✓","debug":"DEBUG","warn":"!"}

def cout(message_type,message):
    print(f"[{cout_t[message_type]}] {message}")

def downloadUrl(url):
    try:
        blob = "blob.html"
        cout("info",f"Downloading {url}.")

        try:
            cmd = call(["wget", f"-O", f"{blob}", f"{url}"])
        except:
            cout("error",f"{traceback.format_exc()}")

        dispatchStripHTML(blob)
    except:
        cout("error",f"{traceback.format_exc()}")

def dispatchStripHTML(blob):
    stripHTML = "stripHTML.py"
    cout("info",f"Dispatching stripHTML.")
    try:
        cmd = call(["python", f"{stripHTML}", "-f", f"{blob}"])
        cout("success"," ")
    except:
        cout("error",f"{traceback.format_exc()}")

def main(in_file):
    try:

        cout("info",f"Reading {in_file}.")
        with open(in_file,"r") as fd:
            urls = [ url.strip() for url in fd.readlines() ]
        cout("success","# of urls read: {len(urls)}.")

        if urls:
            for url in urls:
                downloadUrl(url)
        else:
            cout("info",f"Uh-oh...there was a problem. Check to make sure the urls in {in_file} are correct, then try again.")
    except:
        cout("error",f"{traceback.format_exc()}")

if __name__ == '__main__':
    in_file = "urlFeed.txt"
    cout("success","Running.")
    main(in_file)
    cout("success",f"Done.")
