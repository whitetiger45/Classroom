## Ghidra-2-Yara

A formatted code to yara rule string preparation tool.

This tool is useful for quickly generating yara strings from ghidra-formatted code.

To use this tool, copy the disassembly from ghidra, then execute the program, passing the 
text file with the ghidra formatted code as the only command line argument. 

A text file called 'yara_from_ghidra.txt' will be written in the same directory that the program is executed in, and 
the text file will contain the yara-rule-ready ghidra disassembly code.

Inspired by: [Continued Malware Identification with Yara](https://class.malware.re/2020/03/10/more-yara-examples.html)

