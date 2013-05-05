int main()
{
	int fun = 0;
	int *p = malloc(sizeof(int));

	switch(fun)
	{
	case 0:
                free(p);
		fun = 1;
	default:
		fun = -1;
                p = NULL;
	}

	return 0;
}