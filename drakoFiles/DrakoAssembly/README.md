To compile, link & execute an assembly file (linux): 
--------------------------------------------------------------
1) nasm -f elf <file>.asm -o <file>.o
2) the link command is ld -m elf_i386 -o exename <file>.o
-http://stackoverflow.com/questions/19200333/architecture-of-i386-input-file-is-incompatible-with-i386x86-64