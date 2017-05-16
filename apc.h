#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_SIZE 6

static char *oprator = "+-*/%";

typedef struct node
{
	char num[NUM_SIZE];
	struct node *prv,*next;
}d_list;

char *final_string(d_list*);
char *be_insert(char*);
d_list *addition(d_list*,d_list*);
d_list *subtraction(d_list*,d_list*);
d_list *multiplication(d_list*,d_list*);
d_list *devision(d_list*,d_list*);
d_list *modulus(d_list*,d_list*);
char *apc_calculator(char *str,char opt);
int create_d_list(d_list **head,char *str);
char* my_itoa(long long int num);
char* rev_string(char *s);
int insert(d_list **head,char *data);
d_list *create_node(char *data);
int print_list(d_list *head);
