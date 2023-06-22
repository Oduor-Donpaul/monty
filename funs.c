#include "monty.h"

/**
 * add - adds the top 2 elements of stackl
 * @stack: the stack that we are accessing the top elements to add
 * @line_number: the current line in the monty bytecode file
 * Return: nothing
 */
void add(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n += (*stack)->n;
	pop(stack, line_number);
}

/**
 * sub - subtracts top elemt from second top
 * @stack: double pointer to the top element of the stack
 * @line_number: current line in the Monty bytecode file
 * Return: nothing
 */
void sub(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n -= (*stack)->n;
	pop(stack, line_number);
}

/**
 * stack - converts queue to a stack
 * @stack: double pointer to the top node of a stack_t linked list
 * @line_number: current line of the Monty bytecode file
 * Return: nothing
 */
void stack(stack_t **stack, unsigned int line_number)
{
	(*stack)->n = STACK;
	(void)line_number;
}

/**
 * rotr - rotates the stack to the bottom
 * @stack: double pointer to top node of the stack
 * @line_number: currentline of the monty bytecode file
 * Return: nothing
 */
void rotate_b(stack_t **stack, unsigned int line_number)
{
	stack_t *top = *stack;
	stack_t *last = NULL;

	if (top != NULL && top->next != NULL)
	{
		while (top->next != NULL)
			top = top->next;

		last = top;
		last->prev->next = NULL;
		last->prev = NULL;
		last->next = *stack;
		(*stack)->prev = last;
		*stack = last;
	}
	(void)line_number;
}

/**
 * rotate - rotates the stack to the top
 * @stack: double pointer to the top of our stack
 * @line_number: current line in the Monty bytecode file
 * Retrun: nothing
 */
void rotate(stack_t **stack, unsigned int line_number)
{
	stack_t *top, *bottom;

	if (*stack != NULL && (*stack)->next != NULL)
	{
		top = *stack;
		bottom = *stack;

		while (bottom->next != NULL)
			bottom = bottom->next;

		*stack = top->next;
		(*stack)->prev = NULL;
		bottom->next = top;
		top->prev = bottom;
		top->next = NULL;
	}
	(void)line_number;
}


