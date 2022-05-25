# -*- coding: utf-8 -*-
#!/bin/python
# author: bryan kanu
# description: 
#   this program simply loops through the headlines for https://thehackernews.com/, downloads them
#   and writes only the text of the blog articles to a file so they can be read aloud with a 
#   text-to-speech program to facilitate multi-tasking.
# note:
#   this is a stable, dirty version of what is a work in progress; 
#   as more files are consumed, it will be improved.
import urllib.request
import re, traceback

from subprocess import call

findTodaysStories = lambda line: re.finditer("""<a class=\Sstory-link\S href="(.*)">""",line)
cout_t = {"info":"*","error":"x","success":"✓","debug":"DEBUG","warn":"!"}

def cout(message_type,message):
    print(f"[{cout_t[message_type]}] {message}")

def flatten(lines):
    return [line for lst in lines for line in lst]

def downloadUrl(url):
    try:
        blob = "blob.html"
        cout("info",f"Downloading {url}.")
        with urllib.request.urlopen(url) as fd:
            lines = [ line.decode("utf-8").strip() for line in fd.readlines() ]

        cout("info",f"Saving to temporary file {blob}.")
        with open(blob, "w") as fd:
            [ fd.write(f"{line}\n") for line in lines ]

        dispatchStripHTML(blob)
    except:
        cout("error",f"{traceback.format_exc()}")

def dispatchStripHTML(blob):
    stripHTML = "stripHTML.py"
    try:
        cmd = call(["python", f"{stripHTML}", "-f", f"{blob}"])
    except:
        cout("error",f"{traceback.format_exc()}")

def main():
    try:
        with urllib.request.urlopen("https://thehackernews.com/") as fd:
            lines = [ line.decode("utf-8").strip() for line in fd.readlines() ]
        headlines = flatten(list(map((lambda l: [m.group(1) for m in findTodaysStories(l)]),lines)))

        with open(out_file, "w") as fd:
            [ fd.write(f"{line}\n") for line in headlines ]

        for headline in headlines:
            downloadUrl(headline)

    except:
        cout("error",f"{traceback.format_exc()}")

if __name__ == '__main__':
    out_file = "todaysHeadlines.txt"
    cout("success","Running.")
    main()
    cout("success",f"Done. Today's headlines saved to {out_file}.")
