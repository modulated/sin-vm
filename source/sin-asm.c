#include "sin.h"

#define MAX_NAME_SIZE 128
#define MAX_LINE_SIZE 128

/* Takes .san file input and generates .syn code */

int lexfile(char* file)
{

	return 0;
}

void generate_outfile_name(char* input, char* output)
{
	int i = 0;
	while (input[i] != '\0')
	{
		if (i > MAX_NAME_SIZE)
		{
			puts("Error: filename too long");
			exit(1);
		}

		output[i] = input[i];
		i++;
	}
	output[i] = '\0';	
	output[i-2] = 'y';
}

int verify_extention(char* input, char* ext)
{
	if (strlen(ext) != 3) return -1;

	int i = 0;
	for (i = 0; i < strlen(input); i++)
	{
		if (input[i] == '.') break;
	}

	for (int j = 0; j < 3; j++)
	{
		if (input[i + j + 1] != ext[j]) return 1;
	}

	return 0;
}

int verify_end(FILE* file)
{
	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	
	for (int i = length; i > 3; i--)
	{
		char c = fgetc(file);
		fseek(file, i, SEEK_SET);				
		if (c == 'd')
		{			
			fseek(file, i, SEEK_SET);
			if ((c = fgetc(file)) == 'n')
			{
				i--;
				fseek(file, i, SEEK_SET);
				if ((c = fgetc(file)) == 'e')
				{
					fseek(file, 0, SEEK_SET);
					return 0;
				}			
				
			}
		}
	}

	return 1;
}

void read_line(FILE* fp, char* buffer)
{
	char c = 0;	
	for (int i = 0; i < MAX_LINE_SIZE; i++)
	{
		c = fgetc(fp);
		
		if (c == '\n' || c == EOF)
		{
			return;
		}

		buffer[i] = c;
	}
	
	puts("Error: Line size too large");
	exit(1);
}

int count_lines(FILE* file)
{
	fseek(file, 0, SEEK_SET);
	int lines = 0;
	char c = 0;
	while ((c = fgetc(file)) != EOF)
	{
		if (c == '\n') lines++;
	}

	fseek(file, 0, SEEK_SET);
	return lines;
}
void write_header(FILE* outfile)
{
	int head = endian_swap(SRT);
	fwrite(&head, sizeof(head), 1, outfile);	
}

void parse_san_to_syn(FILE* in, FILE* out)
{
	if (in == NULL || out == NULL)
	{
		puts("Error: Unable to open file");
		exit(1);
	}
	int in_lines = count_lines(in);
	int program[in_lines * 2]; // program array

	
	char linebuffer[MAX_LINE_SIZE];
	read_line(in, linebuffer);
	
	printf("Line: %s\n", linebuffer);
	program[0] = SRT;
	program[1] = SET;
	program[2] = 1;
	program[3] = END;
	fwrite(program, sizeof(int), 4, out);
}	



int main (int argc, char* argv[])
{
	// Run with 1 arg which must end in .san.
	if (argc != 2 || verify_extention(argv[1], "san") != 0) 
	{
		puts("Parse SAN (Syn Assembly Notation) files to Syn code.");
		printf("Usage: %s <file>.san\n", argv[0]);
		return 1;
	}
	
	FILE* infile = fopen(argv[1], "r"); // Read argument
	printf("Reading %s...\n", argv[1]);
	
	if (verify_end(infile) != 0)
	{
		puts("Error: file must contain 'end'");
		exit(1);
	}

	char outfile_name[MAX_NAME_SIZE];
	generate_outfile_name(argv[1], outfile_name);
	
	
	printf("Writing file: %s\n", outfile_name);
	FILE* outfile = fopen(outfile_name, "wb");
	
	write_header(outfile);

	parse_san_to_syn(infile, outfile);

	if (lexfile(argv[1]) != 0)
	{
		printf("Error parsing %s\n", argv[1]);
		return 1;
	}


	fclose(outfile);
	fclose(infile);
	return 0;
}

