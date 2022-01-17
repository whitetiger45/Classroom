#!/usr/bin/python3
# -*- coding: utf-8 -*-
import argparse, os
import platform, re, sys
import tarfile, traceback, zipfile

from datetime import datetime, date, time, timezone
from pathlib import Path

def getTimestamp():
    return datetime.now(timezone.utc).strftime('%m-%d-%y %H:%M:%S')

def exclude(file):
    tmp = file.split("/")
    exclusionSet = EXCLUSION_LIST.intersection(tmp)
    return len(exclusionSet) != 0

ARCHIVE_DATE = datetime.now(timezone.utc).strftime("%m.%d.%y")
ARCHIVE_DIR = Path(os.getcwd())
ARCHIVE_LIST = Path.joinpath(ARCHIVE_DIR, "ARCHIVED_FILES.txt")
ARCHIVE_LOG = Path.joinpath(ARCHIVE_DIR, f"archive.{ARCHIVE_DATE}.2.ERRORS.LOG")
ARCHIVE_OUT = Path.joinpath(ARCHIVE_DIR, f"archive.{ARCHIVE_DATE}.2.tar.lzma")
ARGS = {
"files-options":{
    "files-list": {
        "help":"comma separated list of directories/files to backup",
        "f": lambda csv : set(csv.split(DELIMETER))
    },
    "files-text": {
        "help":"text file containing directories/files to backup (one directories/file per line)",
        "f": [(lambda f : open(f,"r")),(lambda fd : set([line.strip() for line in fd])), (lambda f : f.close())]
    }
},
"exclusions-options":{
    "exclusions": {
        "help":"comma separated list of directories/files/file types to exclude",
        "f": lambda csv : set(csv.split(DELIMETER))
    },
    "exclusions-file": {
        "help":"file containing exclusions separated by line (one per line)",
        "f": [(lambda f : open(f,"r")),(lambda fd : set([line.strip() for line in fd])), (lambda f : f.close())]
    }
}}
DELIMETER = ","
DIRECTORIES_AND_FILES_TO_BACKUP = []
FILES = []
EXCLUSION_LIST = []
USAGE = f"""Program: backup.py
Usage:

{sys.argv[0]} [files option] [[exclusions option]]

files option (required):
    --files-list [{ARGS["files-options"]["files-list"]["help"]}]
    --files-text [{ARGS["files-options"]["files-text"]["help"]}]

exclusions option (optional):
    --exclusions [{ARGS["exclusions-options"]["exclusions-file"]["help"]}]
    --exclusion-file [{ARGS["exclusions-options"]["exclusions"]["help"]}]
"""
# parser = argparse.ArgumentParser(description='Backup your files.')
# parser.add_argument('--files-list', dest="directories_and_files_to_backup", action='store',
#                     help="comma separated list of directories/files to backup", nargs=1)
# parser.add_argument('--files-text', dest="directories_and_files_to_backup", action='store',
#                     help="file containing directories/files to backup (one directories/file per line)", nargs=1)
# parser.add_argument('--exclusions', dest="EXCLUSION_LIST", action='store',
#                     help="comma separated list of directories/files/file types to exclude", nargs=1)
# parser.add_argument('--exclusion-file', dest="exclusion_file", action='store',
#                     help="file containing exclusions separated by line (one per line)", nargs=1)

# args = parser.parse_args()
def main():
    global EXCLUSION_LIST
    ERRORS = ""; 

    if "Linux" not in platform.system():
        sys.exit("\nThis program is currently only written for Linux.")

    if len(sys.argv) < 3 or sys.argv[1].split("--")[1] not in ARGS["files-options"].keys():
        sys.exit(f"{USAGE}")
    else:
        case = re.match(r"--(.*)",sys.argv[1]).group(1)

    FILES = Path(sys.argv[2])
    try:
        if FILES.exists() and FILES.is_file():
            if case != "files-text":
                case = "files-text"
            fd = ARGS["files-options"][case]["f"][0](FILES)
            DIRECTORIES_AND_FILES_TO_BACKUP = ARGS["files-options"][case]["f"][1](fd)
            ARGS["files-options"][case]["f"][2](fd)
        else:
            if case != "files-list":
                case = "files-list"
            if FILES.exists() and FILES.is_dir():
                DIRECTORIES_AND_FILES_TO_BACKUP = ARGS["files-options"][case]["f"](str(FILES.absolute()))
            else:    
                DIRECTORIES_AND_FILES_TO_BACKUP = ARGS["files-options"][case]["f"](FILES.name)
    except:
        sys.exit(f"\n{traceback.format_exc()}")

    FILES = []

    if len(sys.argv) > 3 and sys.argv[3].split("--")[1] not in ARGS["exclusions-options"].keys():
        sys.exit(f"Usage: {USAGE}")
    elif len(sys.argv) > 3 and sys.argv[3].split("--")[1] in ARGS["exclusions-options"].keys():
        case = re.match(r"--(.*)",sys.argv[3]).group(1)
        EXCLUSIONS = Path(sys.argv[4])
        try:
            if EXCLUSIONS.exists() and EXCLUSIONS.is_file():
                if case != "exclusions-file":
                    case = "exclusions-file"
                fd = ARGS["exclusions-options"][case]["f"][0](EXCLUSIONS)
                EXCLUSION_LIST = ARGS["exclusions-options"][case]["f"][1](fd)
                ARGS["exclusions-options"][case]["f"][2](fd)

            else:
                if case != "exclusions":
                    case = "exclusions"
                if EXCLUSIONS.exists() and EXCLUSIONS.is_dir():
                    EXCLUSION_LIST = ARGS["exclusions-options"][case]["f"](str(EXCLUSIONS.absolute()))
                else:
                    EXCLUSION_LIST = ARGS["exclusions-options"][case]["f"](EXCLUSIONS.name)
        except:
            sys.exit(f"\n{traceback.format_exc()}")

    for path in DIRECTORIES_AND_FILES_TO_BACKUP:
        FILES += list(filter((lambda file : exclude(str(file.absolute())) != True ), Path(path).rglob("*")))

    if not FILES:
        sys.exit("There are no files to backup!")

    try:
        with tarfile.open(ARCHIVE_OUT, "x:xz") as archive_fd:
            for file in FILES:
                try:
                    archive_fd.add(str(file.absolute()),recursive=False)
                except:
                    ERRORS += f"[{getTimestamp()}]: {traceback.format_exc()}\n\n"
    except:
        try:
            ERRORS += f"[{getTimestamp()}]: {traceback.format_exc()}\n\n"
            with open(ARCHIVE_LOG, "w") as archiveErrorLog_fd:
                archiveErrorLog_fd.write(f"{ERRORS}")
        except:
            cmd = f"python3.6 -c 'print(f\"[!] Exception in backup.py: {traceback.format_exc()}\")' | wall "
            os.system(f"""{cmd}""")
        sys.exit(1)

    try:
        with open(ARCHIVE_LIST,"w") as archiveLog_fd:
            archiveLog_fd.write("{0}".format("\n".join(str(file.absolute()) for file in FILES)))
    except:
        try:
            ERRORS += f"[{getTimestamp()}]: {traceback.format_exc()}\n\n"
            with open(ARCHIVE_LOG, "w") as archiveErrorLog_fd:
                archiveErrorLog_fd.write(f"{ERRORS}")
        except:
            cmd = f"python3.6 -c 'print(f\"[!] Exception in backup.py: {traceback.format_exc()}\")' | wall "
            os.system(f"""{cmd}""")

    SUCCESS1 = f"[{getTimestamp()}]: backup lzma archive ready for zip archiving!"
    os.system(f"python3.6 -c 'print(\"{SUCCESS1}\")' | wall ")

    # zip section
    ZIP_ARCHIVE = str(ARCHIVE_OUT.absolute()).split('.tar.lzma')[0] + ".zip"
    cmd0 = f"zip -m {ZIP_ARCHIVE} {str(ARCHIVE_OUT.absolute())} {str(ARCHIVE_LIST.absolute())} {str(ARCHIVE_LIST.absolute())}"
    cmd1 = f"rm -f $(find {str(ARCHIVE_DIR.absolute())} -type f \( -wholename \"*.zip\" \) ! -wholename \"{ZIP_ARCHIVE}\")"
    cmd = f"{cmd0} 2> {ARCHIVE_DIR}/debug.2.errors.log && {cmd1} 2>> {ARCHIVE_DIR}/debug.2.errors.log"

    try:
        os.system(cmd)
        
        if Path(ZIP_ARCHIVE).exists():
            SUCCESS2 = f"zip archive: {ZIP_ARCHIVE} has been created!"
            os.system(f"python3.6 -c 'print(\"{SUCCESS2}\")' | wall ")
        else:
            ERRORS += f"zip archive status: {ZIP_ARCHIVE} was not created. An error occured.\n"
    except:
        ERRORS += f"[{getTimestamp()}]: {traceback.format_exc()}\n\n"

    if ERRORS:
        try:
            with open(ARCHIVE_LOG, "w") as archiveErrorLog_fd:
                archiveErrorLog_fd.write(f"{ERRORS}")
        except:
            cmd = f"python3.6 -c 'print(f\"[!] Exception in backup.py: {traceback.format_exc()}\")' | wall "
            os.system(cmd)

if __name__ == '__main__':
    main()
