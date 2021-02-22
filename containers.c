#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// a node for binary tree
struct node
{
	struct node * left, * right; // branches
	char data; // for variable ('X'), operators ('+', '-', '=') and numbers ('0' to '9')
};

struct node * fill_tree (); // parser 
void   print_tree (struct node * tree); // printer
void   free_tree (struct node * tree); // tree destructor
int    calculate_tree (struct node * tree, int variable); // calculator

int main ()
{
	struct node * tree = fill_tree(); // tree input

	int var = 0;
	scanf ("%d", &var); // variable input

	printf ("%d\n", calculate_tree(tree, var)); // calculation result output
	
	free_tree(tree); // tree destruction

	return 0;
}

// formula parsing function
struct node * fill_tree () 
{
	char c = getchar();
	
	struct node * operand = (struct node *)malloc (sizeof (struct node));

	operand->left = operand->right = operand->data = NULL;
	
	if (c == 'X') // variables
	{
		operand->data = 'X';
	}
	else if (c >= '0' && c <= '9') // numbers
	{
		operand->data = c;
	}
	else if (c == '(') // formulas
	{
		operand->left = fill_tree();
		operand->data = getchar();
		operand->right = fill_tree();

		assert (getchar() == ')'); // expecting ')' to come
	}
	else // parsing error
	{
		fprintf(stderr, "wrong formula format, check fill_tree function");
	}

	return operand;
}

// formula printing function (the infix one, just for debugging)
void print_tree (struct node * tree)
{
	if (!tree) // for null pointer cases
		return;

	if (tree->data == '+' || tree->data == '-' || tree->data == '*') printf("(");
	print_tree(tree->left); // left operand
	putchar(tree->data); // operator, variable or number
	print_tree(tree->right); //right operand
	if (tree->data == '+' || tree->data == '-' || tree->data == '*') printf (")");
}

// tree deallocator function
void free_tree (struct node * tree)
{
	if (!tree) // for null pointer cases
		return;

	free_tree (tree->left);
	free_tree (tree->right);

	free (tree);
}

// tree calculation function
int calculate_tree (struct node * tree, int variable)
{
	if (tree->data == 'X') // just replacing 'X' to variable value
		return variable;

	// simple recursive calculations
	if (tree->data == '+') 
		return calculate_tree(tree->left, variable) + calculate_tree(tree->right, variable);

	if (tree->data == '-')
		return calculate_tree (tree->left, variable) - calculate_tree (tree->right, variable);

	if (tree->data == '*')
		return calculate_tree (tree->left, variable) * calculate_tree (tree->right, variable);

	return (int)tree->data - '0'; // only number case left. converting char to int value, assuming data is just number character
}
