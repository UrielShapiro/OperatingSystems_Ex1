#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

const char *PB_FILEPATH = "phonebook.txt";

#define PIPE_READ_END 0
#define PIPE_WRITE_END 1

bool print_number(char *name)
{
	// we will emulate the command:
	// grep $(name) < $(PB_FILEPATH) | cut -d, -f2 | xargs

	int pipe_grep_to_cut[2], pipe_cut_to_xargs[2];
	// create the first pipe
	pipe(pipe_grep_to_cut);
	// fork for grep
	if (fork() == 0)
	{
		// close the read end of the pipe
		close(pipe_grep_to_cut[PIPE_READ_END]);
		// open the phonebook file for reading and dup it into stdin
		dup2(open(PB_FILEPATH, O_RDONLY), STDIN_FILENO);
		// dup the pipe write end into stdout
		dup2(pipe_grep_to_cut[PIPE_WRITE_END], STDOUT_FILENO);
		// execute the grep
		execlp("grep", "grep", name, (char *) NULL);
	}
	
	// create the second pipe
	pipe(pipe_cut_to_xargs);
	if (fork() == 0)
	{
		// close unused pipe ends
		close(pipe_grep_to_cut[PIPE_WRITE_END]);
		close(pipe_cut_to_xargs[PIPE_READ_END]);
		// dup the first pipe into stdin
		dup2(pipe_grep_to_cut[PIPE_READ_END], STDIN_FILENO);
		// dup the second pipe into stdout
		dup2(pipe_cut_to_xargs[PIPE_WRITE_END], STDOUT_FILENO);
		// execute cut
		execlp("cut", "cut", "-d,", "-f2", (char *) NULL);
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
		dup2(pipe_cut_to_xargs[PIPE_READ_END], STDIN_FILENO);
		// execute xargs
		execlp("xargs", "xargs", (char *) NULL);
	}
	// close all remaining pipe ends
	close(pipe_cut_to_xargs[PIPE_READ_END]);
	close(pipe_cut_to_xargs[PIPE_WRITE_END]);

	// wait until xargs finishes, to not mix outputs
	waitpid(xargs_pid, NULL, 0);
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
	print_number(name);
	return 0;
}
