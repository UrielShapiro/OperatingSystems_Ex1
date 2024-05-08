#include <cstring>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

const char *PB_FILEPATH = "phonebook.txt";

int main(int argc, char **argv)
{
	char **args = (char **) malloc(sizeof(char *)*(argc + 1));
	memcpy(args, argv, sizeof(char *)*argc);
	args[argc] = NULL;

	// we will emulate the command:
	// echo $(name) , $(num) >> $(PB_FILEPATH)

	// fork to run `echo`
	if (fork() == 0)
	{
		dup2(open(PB_FILEPATH, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH), STDOUT_FILENO);
		execvp("echo", args);	// execute the echo

	}

	return 0;
}
