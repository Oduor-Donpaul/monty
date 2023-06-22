#include "monty.h"

/**
 * queue - converts a stack to a queue
 * @stack: double pointer to the top node of the stack_t linked list
 * @line_number: current line of the Monty bytecode file
 * Return: nothing
 */
void queue(stack_t **stack, unsigned int line_number)
{
	(*stack)->n = QUEUE;
	(void)line_number;
}
/**
 * pstr - prints the string starting at the top of the stack
 * @stack: double pointer to the top node of the stack
 * @line_number: current line of the monty bytecode file
 * Return: nothing
 */
void pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = (*stack)->next;

	while (temp && temp->n != 0 && (temp->n > 0 && temp->n <= 127))
	{
		printf("%c", temp->n);
		temp = temp->next;
	}

	printf("\n");

	(void)line_number;
}

/**
 * ptchar - prints the character at the top of the stack
 * @stack: double pointer to the top node of the stack
 * @line_number: current line of the Monty bytecode file
 * Return: nothing
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	int value;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	value = (*stack)->n;

	if (value < 0 || value > 127)
	{
		fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%c\n", (char)value);
}

/**
 * nop - doesn't do anything
 * @stack: pointer to the top node of the stack
 * @line_number: the curent line of the monty bytecode file
 * Return: nothing
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

/**
 * mul - multiplies the 2nd top element with the top element of the stack
 * @stack: double pointer to the top node of the stack
 * @line_number - current line in the Monty bytecode file
 * Return: nothing
 */
void mul(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n *= (*stack)->n;
	pop(stack, line_number);
}
