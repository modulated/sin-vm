#include <syn.h>

#define DEBUG

int op_get () {
	#ifdef DEBUG
		puts("GET");
	#endif

	return POP;
}

void op_set (int x) {
	#ifdef DEBUG
		puts("SET");
	#endif

	PUSH(x);
}

void op_clr () {
	#ifdef DEBUG
		puts("CLR");
	#endif


}

void op_add () {
	#ifdef DEBUG
		puts("ADD");
	#endif

	PUSH(POP + POP);
}

void op_sub() {
	PUSH(POP - POP);

	#ifdef DEBUG
		puts("SUB");
	#endif
}

void op_mul() {
	PUSH(POP * POP);
	
	#ifdef DEBUG
		puts("MUL");
	#endif
}

void op_div() {
	PUSH(POP / POP);
	
	#ifdef DEBUG
		puts("DIV");
	#endif
}

void op_mod() {
	PUSH(POP % POP);
	
	#ifdef DEBUG
		puts("MOD");
	#endif
}

void op_ini() {
	#ifdef DEBUG
		puts("INI");
	#endif

	int i = 0;
	scanf("%d", &i);
	PUSH(i);
}

void op_out() {
	#ifdef DEBUG
		puts("OUT");
	#endif

	printf("%d\n", POP);
}

int execute_program(int* input, int* output)
{
	int index = 0;
	int out_counter = 0;
	int cur = 0;

	while ((cur = input[index++]) != END)
	{
		switch(cur)
		{
			case GET: 
				if (out_counter < OUTPUT_SIZE) 
				{
					output[out_counter++] = op_get();
					break;
				}
				else return ERR_OUTPUT_OVERFLOW;
				 
			case SET:
				op_set(input[index++]);
				break;

			case CLR:
				op_clr();
				out_counter--;
				output[out_counter] = 0;
				break;
				
			case JMP:
				index = input[index];
				printf("JMP to %d\n", index);
				break;

			case ADD:
				op_add();
				break;
			
			case SUB:
				op_sub();
				break;
			
			case MUL:
				op_mul();
				break;
			
			case MOD:
				op_mod();
				break;

			case INI:
				op_ini();
				break;

			case OUT:
				op_out();
				break;

			case NOP: break;
			default: return ERR_ILLEGAL_INSTRUCTION;
		}
	}

	return 0;
}

int sancode_to_syncode(char* code)
{
	instruction_toupper(code);
	/* BASIC */
	if (strncmp(code, "SRT", 3) == 0) return SRT;
	if (strncmp(code, "END", 3) == 0) return END;
	if (strncmp(code, "NOP", 3) == 0) return NOP;
	if (strncmp(code, "SET", 3) == 0) return SET;
	if (strncmp(code, "GET", 3) == 0) return GET;
	if (strncmp(code, "CLR", 3) == 0) return CLR;
	
	/* MATHS */
	if (strncmp(code, "INC", 3) == 0) return INC;
	if (strncmp(code, "DEC", 3) == 0) return DEC;
	if (strncmp(code, "ADD", 3) == 0) return ADD;
	if (strncmp(code, "SUB", 3) == 0) return SUB;
	if (strncmp(code, "MUL", 3) == 0) return MUL;
	if (strncmp(code, "DIV", 3) == 0) return DIV;
	if (strncmp(code, "MOD", 3) == 0) return MOD;
	
	
	
	return ERR_ILLEGAL_INSTRUCTION;
}

size_t get_filesize(char* file)
{
	struct stat info;
	stat(file, &info);
	return info.st_size;
}

void instruction_toupper(char* inst)
{	
	for (int i = 0; i < 3; i++)
	{
		inst[i] = toupper(inst[i]);
	}
}

int* read_file(char* file)
{
	FILE* fp = fopen(file, "rb");
	int fsize = get_filesize(file);

	int head = 0;
	fread(&head, sizeof(int), 1, fp);
	head = endian_swap(head);
	if (head != SRT)
	{
		puts("File not byte code...");
		printf("Expecting %x \t Got %x\n", SRT, head);
		exit(1);
	}

	int* buffer = malloc(fsize);
	fread(buffer, fsize, sizeof(int), fp);
	fclose(fp);
	
	return buffer;
}

void endian_swap_buffer (int* buffer)
{
	int i = 0;
	while (buffer[i] != END)
	{
		buffer[i] = endian_swap(buffer[i]);
		i++;
	}
}

void dump_program(int* prog)
{
	int cur = 0;
	while (prog[cur] != END)
	{
		printf("%i: %X\n", cur, prog[cur]);
		cur++;
	}
	printf("%i: %X\n", cur, prog[cur]);
}

void dump_output()
{
	for (int i = 0; i < OUTPUT_SIZE; i++)
	{
		printf("%d: %d\n", i, output[i]);
	}
}

int endian_swap (int in)
{
	return 
	((in >> 24) & 0x000000ff) | // move byte 3 to byte 0
	((in <<  8) & 0x00ff0000) | // move byte 1 to byte 2
	((in >>  8) & 0x0000ff00) | // move byte 2 to byte 1
	((in << 24) & 0xff000000); // byte 0 to byte 3
}

void print_error(int error)
{
	switch (error)
	{
		case ERR_ILLEGAL_INSTRUCTION:
			puts("Error: Illegal instruction");
			exit(1);
		case ERR_OUTPUT_OVERFLOW:
			puts("Error: Output buffer overflow");
			exit(1);
		case ERR_STACK_OVERFLOW:
			puts("Error: Stack overflow");
			exit(1);
		case ERR_UNKNOWN_ERROR:
			puts("Error: Unknown");
			exit(1);
	}
}