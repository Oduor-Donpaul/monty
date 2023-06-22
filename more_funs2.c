#include "monty.h"

/**
 * mod - modulus of the second top elemt by top element of stack
 * @stack: double pointer to the top node of the stack
 * @line_number: current line of the Monty bytecode file
 *
 * Return: nothing
 */
void mod(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n %= (*stack)->n;
	pop(stack, line_number);
}

/**
 * div - divides the second top element by the top element of stack
 * @stack: double pointer to the top node  of the stack
 * @line_number: current line of the Monty bytecode file
 * Return: nothing
 */
void divv(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n /= (*stack)->n;
	pop(stack, line_number);
}

/**
 * execute - execute monty bytecodes script
 * @fle_fd: file descriptor for monty script
 *
 * Return: exit on sucess or error upon failing
 */
int execute(FILE *fle_fd)
{
	stack_t *stack = NULL;
	char line[1024];
	unsigned int line_number = 0;
	char *opcode;
	void (*op_func)(stack_t **, unsigned int);

	if (fle_fd == NULL)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), fle_fd))
	{
		opcode = strtok(line, " \t\n");

		if (opcode != NULL && opcode[0] != '#')
		{
			line_number++;
			op_func = read_op_func(opcode);

			if (op_func == NULL)
			{
				fprintf(stderr, "L%u: unknown instructions %s\n", line_number, opcode);
				fclose(fle_fd);
				exit(EXIT_FAILURE);
			}
			op_func(&stack, line_number);
		}
	}
	fclose(fle_fd);

	return (0);


}

/**
 * read_op_func - matches the opcode with it's function
 * @opcode: the instruction to match
 * Return: returns a pointer
 */
void (*read_op_func(char *opcode))(stack_t**, unsigned int)
{
	instruction_t op_fun[] = {{"push", push}, {"pall", pall},
		{"pint", pint}, {"pop", pop}, {"swap", swap},
		{"add", add}, {"nop", nop}, {"sub", sub},
		{"div", divv}, {"mul", mul}, {"mod", mod},
		{"pchar", pchar}, {"pstr", pstr},
		{"rotate_b", rotate_b}, {"rotate", rotate},
		{"stack", stack}, {"queue", queue},
		{NULL, NULL}};

	int i;

	for (i = 0; op_fun[i].opcode; i++)
	{
		if (strcmp(opcode, op_fun[i].opcode) == 0)
			return (op_fun[i].f);
	}
	return (NULL);
}


/**
 * main - this is the main entry point
 * @argc: the arguement count
 * @argv: the argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	FILE *file_fd;

	if (argc != 2)
	{
		printf("USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	file_fd = fopen(argv[1], "r");
	if (file_fd == NULL)
	{
		printf("Error: Can't open file %s\n", argv[1]);
		return (EXIT_FAILURE);
	}
	execute(file_fd);
	return (0);
}
