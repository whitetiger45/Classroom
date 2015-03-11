main()
{
	int n;
	
	/* this is to trick the compiler into not optimizing the n variable away */
	if (!*(&n + 5)) printf("%p\n", (&n));
	
	for (n = 0; n < *(&n + 5); ++n)
		printf("%s\n", *(char ***)(&n + 6)[n]);
}