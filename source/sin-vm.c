#include <sin.h>
// #define DEBUG

// Dummy Program, cont array of 4 bytes 
int dummy[] = {
	SET, 0x8, // SET 8
	SET, 0x2, // SET 2
	GTE,
	JPO, 1,
	GET,
	END,
};


int main(int argc, char* argv[])
{	
	stack = stack_new(STACK_SIZE);
	int* program = NULL;

	if (argc == 2)
	{		
		program = read_file(argv[1]);
		endian_swap_buffer(program);
		execute_program(program, output);
	}
	else if (argc == 3)
	{
		program = dummy;
		int result = execute_program(dummy, output);
		if (result != 0) print_error(result);
	}
	else if (argc == 1) // interpreter
	{
		char line[32];
		putchar('>');
		scanf("%s", line);
		printf("%s\n", line);
	}
	else
	{		
		puts("Please supply one file as argument.");
		return 1;
	}

	#ifdef DEBUG
		dump_program(program);
		dump_output();
	#endif
	
	printf("Output 0: %d\n", output[0]);

	return 0;
}
