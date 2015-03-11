main()
{
	int bp, argc;
	char ** argv;
	
	__asm__("movl %%ebp, %%eax;" : "=a" (bp) ::);
	argc = *(int *)(bp + 8);
	argv = *(char ***)(bp + 12);
	
	printf("%s\n", argv[0]);
	
	return 0;
}