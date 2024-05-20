#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <cstring>

const char *PB_FILEPATH = "phonebook.txt";

#define PIPE_READ_END 0
#define PIPE_WRITE_END 1

/**
 * @brief Print the phone number of a person with the given name
 * @return True if the name was found, false otherwise
 */
bool print_number(char *name)
{
	// we will emulate the command:
	// grep $(name) < $(PB_FILEPATH) | cut -d, -f2 | xargs

	// xargs pipe - to remove the newline character and unneccery spaces
	// cut pipe - to extract the phone number
	int pipe_grep_to_cut[2], pipe_cut_to_xargs[2];

	// create the first pipe
	if (pipe(pipe_grep_to_cut) == -1)
	{
		strerror(errno);
		std::cerr << "Error creating pipe" << std::endl;
		exit(1);
	}
	int child_pid;
	// fork for grep
	if ((child_pid = fork()) == 0)
	{
		// close the read end of the pipe
		close(pipe_grep_to_cut[PIPE_READ_END]);

		// open the phonebook file for reading
		int fd = open(PB_FILEPATH, O_RDONLY);
		if (fd == -1)
		{
			strerror(errno);
			std::cerr << "Error opening file" << std::endl;
			exit(1);
		}
		// replaces stdin to the phonebook file
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			strerror(errno);
			std::cerr << "Error redirecting stdin" << std::endl;
			exit(1);
		}

		// redirect the pipe write end into stdout
		if (dup2(pipe_grep_to_cut[PIPE_WRITE_END], STDOUT_FILENO) == -1)
		{
			strerror(errno);
			std::cerr << "Error redirecting stdout" << std::endl;
			exit(1);
		}

		// execute the grep on the received name
		if (execlp("grep", "grep", name, (char *)NULL) < 0)
		{
			strerror(errno);
			std::cerr << "Error executing grep" << std::endl;
			exit(1);
		}
	}

	// wait for the child proccess to end
	wait(&child_pid);

	// check if the child proccess ended with an error (name not found)
	if (WEXITSTATUS(child_pid) != 0)
	{
		return false;
	}

	// create the second pipe
	if (pipe(pipe_cut_to_xargs) == -1)
	{
		strerror(errno);
		std::cerr << "Error creating pipe" << std::endl;
		exit(1);
	}

	if (fork() == 0)
	{
		// close unused pipe ends
		close(pipe_grep_to_cut[PIPE_WRITE_END]);
		close(pipe_cut_to_xargs[PIPE_READ_END]);

		// replace stdin with the read end of the cut pipe
		if (dup2(pipe_grep_to_cut[PIPE_READ_END], STDIN_FILENO) == -1)
		{
			strerror(errno);
			std::cerr << "Error redirecting stdin" << std::endl;
			exit(1);
		}

		// replace stdout with the write end of the xargs pipe
		if (dup2(pipe_cut_to_xargs[PIPE_WRITE_END], STDOUT_FILENO) == -1)
		{
			strerror(errno);
			std::cerr << "Error redirecting stdout" << std::endl;
			exit(1);
		}

		// execute cut: delimiter is ',' and we want the second field (which contains the number)
		if (execlp("cut", "cut", "-d,", "-f2", (char *)NULL) < 0)
		{
			strerror(errno);
			std::cerr << "Error executing cut" << std::endl;
			exit(1);
		}
	}

	// close the unused pipe ends
	close(pipe_grep_to_cut[PIPE_READ_END]);
	close(pipe_grep_to_cut[PIPE_WRITE_END]);

	// save the xargs pid
	int xargs_pid;

	// fork to run xargs
	if ((xargs_pid = fork()) == 0)
	{
		// close the other end of the pipe
		close(pipe_cut_to_xargs[PIPE_WRITE_END]);

		// dup the read end into stdin
		if (dup2(pipe_cut_to_xargs[PIPE_READ_END], STDIN_FILENO) == -1)
		{
			strerror(errno);
			std::cerr << "Error redirecting stdin" << std::endl;
			exit(1);
		}

		// execute xargs - normalizes the output to be more readable (removes unnecessary spaces and newlines)
		if (execlp("xargs", "xargs", (char *)NULL) < 0)
		{
			strerror(errno);
			std::cerr << "Error executing xargs" << std::endl;
			exit(1);
		}
	}

	// close all remaining pipe ends
	close(pipe_cut_to_xargs[PIPE_READ_END]);
	close(pipe_cut_to_xargs[PIPE_WRITE_END]);

	// wait until xargs finishes, to not mix outputs
	waitpid(xargs_pid, NULL, 0);

	// The name was found
	return true;
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "ERROR: Not enough arguments" << std::endl;
		std::cerr << "USAGE: " << argv[0] << " <name>" << std::endl;
		return 1;
	}

	char *name = argv[1];
	std::cout << "Found number(s) for names matching \"" << name << "\": " << std::flush;
	
	if(print_number(name) == false)
	{
		std::cout << "Name not found" << std::endl;
	}
	return 0;
}
