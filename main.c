#include <stdio.h>
#include <stdlib.h>

/* node types */
enum
{
	NUMBER,
	ADD,
	PRINT
};

/* node struct */
typedef struct node_struct
{
	int type;

	/* if node is a number */
	int number;

	struct node_struct *left;
	struct node_struct *right;
} Node;

/* constructors */
Node *number_node(int number)
{
	Node *node = (Node*)malloc(sizeof(Node));
	
	node->type = NUMBER;
	node->number = number;
	
	return node;
}

Node *add_node(Node *left, Node *right)
{
	Node *node = (Node*)malloc(sizeof(Node));
	
	node->type = ADD;
	node->left = left;
	node->right = right;
	
	return node;
}

Node *print_node(Node *left)
{
	Node *node = (Node*)malloc(sizeof(Node));

	node->type = PRINT;
	node->left = left;

	return node;
}

/* compile node */
void compile_node(Node *node)
{
	switch (node->type)
	{
		case NUMBER:
			printf("PUSH %.2d\n", node->number);
			break;

		case ADD:
			compile_node(node->left);
			compile_node(node->right);
			printf("ADD\n");
			break;

		case PRINT:
			compile_node(node->left);
			printf("PRINT");
			break;
	}
}

/* run node */
Node *run_node(Node *node)
{
	switch (node->type)
	{
		case NUMBER:
		{
			return node;
		}

		case ADD:
		{
			Node *a = run_node(node->left);
			Node *b = run_node(node->right);

			if (a->type == NUMBER && b->type == NUMBER)
				return number_node(a->number + b->number);

			else
			{
				fprintf(stderr, "invalid add type");
				exit(1);
			}
		}

		case PRINT:
		{
			Node *result = run_node(node->left);

			if (result->type == NUMBER)
			{
				printf("%d\n", result->number);
			}
			return number_node(0);
		}
	}
}

/* main */
int main()
{
	Node *ast = print_node(
		add_node(
			add_node(
				number_node(10),
				number_node(15)
			),
			add_node(
				number_node(20),
				number_node(25)
			)
		)
	);


	printf("RUN:\n");
	run_node(ast);
	
	printf("\nCOMPILE:\n");
	compile_node(ast);
	return 0;
}

