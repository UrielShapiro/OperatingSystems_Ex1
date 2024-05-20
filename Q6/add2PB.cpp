#include <cstring>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

const char *PB_FILEPATH = "phonebook.txt";

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: No arguments provided" << std::endl;
		return 1;
	}

	// Create a new array for the arguments to pass to execvp (need to add NULL at the end)
	char **args = (char **)malloc(sizeof(char *) * (argc + 1));
	if (args == NULL)
	{
		std::cerr << "Error allocating memory" << std::endl;
		return 1;
	}

	memcpy(args, argv, sizeof(char *) * argc);
	args[argc] = NULL;

	// we will emulate the command:
	// echo ...(args) >> $(PB_FILEPATH)

	// open the phonebook file for writing and append (will create the file if it doesn't exist)
	int fd = open(PB_FILEPATH, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		strerror(errno);
		std::cerr << "Error opening file" << std::endl;
		return 1;
	}

	// Redirect stdout to the phonebook file
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		strerror(errno);
		std::cerr << "Error redirecting stdout" << std::endl;
		return 1;
	}

	if(execvp("echo", args) == -1) // "echo" the arguments to the phonebook file (after stdout has been redirected)
	{
		strerror(errno);
		std::cerr << "Error executing echo" << std::endl;
		return 1;
	}
	return 0;
}
