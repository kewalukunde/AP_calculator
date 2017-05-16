#include "../include/apc.h"

/* creating Double link list od a string */
int create_d_list(d_list **head,char *str)
{

    int count = 0,i = 3;
    char *num = calloc(6,sizeof(char));
    int n;

    count = (strlen(str) - 1);

    /* collecting 4 char and then inserted as node */
    while (count >= 0)
    {
	num[i] = str[count];
	if (i == 0 )
	{
	    insert(head,num);
	    i = 4;
	}
	count--;
	i--;
    }

    /* if char is less 3 */
    if (i != 3)
    {
	while (i>=0)
	{
	    num[i] = '0';
	    i--;
	}
	insert(head,num);
    }
    return 0;
}

/* adding two nodes id the number > 9999
   adding one carry in next number */
d_list *addition(d_list *head1,d_list *head2)
{
    d_list *ptr1,*ptr2,*head_res = NULL;
    long long int num1,num2;
    int i = 3,count;
    static carry = 0;
    char *op_put;
    char *res = calloc(6,sizeof(char));

    ptr1 = head1;
    ptr2 = head2;
    while ((ptr1 != NULL) && (ptr2 != NULL))
    {
	num1 = atoll(ptr1 -> num);
	num2 = atoll(ptr2 -> num);

	if (carry == 1)
	{
	    num2++;
	    carry = 0;
	}

	if ((num1+num2) > 9999)
	{
	    carry = 1;
	    op_put = my_itoa((num1 + num2) -10000);
	}
	else 
	    op_put = my_itoa(num1 + num2);

	op_put = be_insert(op_put);

	insert(&head_res,op_put);

	ptr1 = ptr1 -> next;
	ptr2 = ptr2 -> next;
    }

    if (ptr1 != NULL)
    {
	if (carry == 1)
	{
	    insert(&head_res,my_itoa(atoi(ptr1 -> num)+1));
	    ptr1 = ptr1 -> next;
	    carry = 0;
	}
	while (ptr1 != NULL)
	{	    
	    insert(&head_res,ptr1 -> num);
	    ptr1 = ptr1 -> next;
	}
    }
    else if (ptr2 != NULL)
    {    
	if (carry == 1)
	{
	    insert(&head_res,my_itoa(atoi(ptr2 -> num)+1));
	    ptr2 = ptr2 -> next;
	    carry = 0;
	}
	while (ptr2 != NULL)
	{	    
	    insert(&head_res,ptr2 -> num);
	    ptr2 = ptr2 -> next;
	}
    }
    else if (carry == 1)
    {
	insert(&head_res,"0001");
	carry = 0;
    }
    return head_res;
}

/* subtractin of two nodes if num2 > num1
  generet borrow  and substract from next upcoming node*/
d_list *subtraction(d_list *head1,d_list *head2)
{
    d_list *ptr1,*ptr2,*head_res = NULL;
    long long int num1,num2;
    static int borrow = 0;
    static char *op_put;
    //char *res = calloc(6,sizeof(char));

    ptr1 = head1;
    ptr2 = head2;

    while ((ptr1 != NULL) && (ptr2 != NULL))
    {
	num1 = atoll(ptr1 -> num);
	num2 = atoll(ptr2 -> num);

	if (borrow == 1)
	{
	    num1--;
	    borrow = 0;
	}

	if (num2 > num1)
	{
	    num1 = num1 + 10000;
	    borrow = 1;
	}

	op_put = my_itoa(num1 - num2);

	op_put = be_insert(op_put);
	insert(&head_res,op_put);

	ptr1 = ptr1 -> next;
	ptr2 = ptr2 -> next;
    }

    if (ptr1 != NULL)
    {
	if (borrow == 1)
	{
	    insert(&head_res,my_itoa(atoi(ptr1 -> num)-1));
	    ptr1 = ptr1 -> next;
	    borrow = 0;
	}
	while (ptr1 != NULL)
	{	    
	    insert(&head_res,ptr1 -> num);
	    ptr1 = ptr1 -> next;
	}
    }
    else
    {   
	if (borrow == 1)
	{
	    insert(&head_res,my_itoa(atoi(ptr1 -> num)-1));
	    ptr1 = ptr1 -> next;
	    borrow = 0;
	}
	while (ptr2 != NULL)
	{	    
	    insert(&head_res,ptr2 -> num);
	    ptr2 = ptr2 -> next;
	}
    }
    return head_res;
}

/* multiplication is suceesive addition 
   here adding the number it self by number of time */
d_list *multiplication(d_list *head1,d_list *head2)
{
    d_list *ptr1,*ptr2,*head_res = NULL;
    long long int num1,num2;
    int i = 0,j;
    char **buff = calloc(10,sizeof(char*));

    ptr2 = head2;
    while (ptr2 != NULL)
    {
	num2 = atoll(ptr2 -> num);
	while (num2)
	{
		head_res = addition(head_res,head1);
		num2--;
	}
	
	j = i; 
	if (j != 0)
	{
	    while (j != 0)
	    {
		insert_first(&head_res,"0000");
		j--;
	    }
	}
	buff[i] = final_string(head_res);

	head_res = NULL;
	i++;
	j++;
	ptr2 = ptr2 -> next;
    }
    head_res = NULL;
    head1 = NULL;

    i = 0;
    while (buff[i] != NULL)
    {
	create_d_list(&head1,buff[i]);

	head_res = addition(head_res,head1);
	head1 = NULL;
	i++;
    }
    return head_res;
}

/* dividing num2 with nodes of first number 
 * if node is smoller number that num2
   then include next node and divide number */
d_list *division(d_list *head1,d_list *head2)
{
    d_list *ptr1,*ptr2,*tmp,*head_res = NULL;
    long long int num1,num2;
    int count = 0,j=0,i=0,i_res,m_res = 0;
    char *op_put,*ex = NULL;
   
    ptr1 = head1;
    num2 = atoll(final_string(head2));
    
    while (ptr1 -> next != NULL)
	ptr1 = ptr1 -> next;

    while (ptr1 != NULL)
    {
	if (ex != NULL)
	{
	    strcat(ex,ptr1 -> num);
	    num1 = atoll(ex);
	}
	else
	{
	    num1 = atoll(ptr1 -> num);
	    ex = (ptr1 -> num);
	}

	if (num2 > num1)
	{
	    while(num2 > num1)
	    {
//		printf("ex = %s\n",ex);
		ptr1 = ptr1 -> prv;
		strcat(ex,ptr1 -> num);
//		printf("ex = %s\n",ex);
		num1 = atoll(ex);
	    }
	    op_put = my_itoa(num1 / num2); 
	    m_res = num1 % num2;
//	    printf("if := i_res =%s,m_res = %d\n",op_put,m_res);
	}
	else
	{
//	    printf("else := num1 =%lld,num2 = %lld\n",num1,num2);
	    i_res = num1/num2;
	    m_res = num1%num2;
//	    printf("else := i_res =%d,m_res = %d\n",i_res,m_res);
	    op_put = my_itoa(i_res);
	}
//	printf("op_put = %s\n",op_put);
	op_put = be_insert(op_put);
//	printf("op_put = %p\n",op_put);
	insert_first(&head_res,op_put);

	ex = my_itoa(m_res);

	ptr1 = ptr1 -> prv;

	if (ptr1 != NULL)
	{    
	    strcat(ex,ptr1 -> num);
	    op_put = my_itoa(atoll(ex) / num2);
	    m_res = atoll(ex) % num2;
//	    printf("op_put = %s\n",op_put);
//	    printf("i_res = %s,m_res = %d\n",op_put,m_res);
	    ex = my_itoa(m_res);
	    op_put = be_insert(op_put);
//	    printf("op_put = %s\n",op_put);
	    insert_first(&head_res,op_put);
	}
	else
	    break;

	ptr1 = ptr1 -> prv;
    }
    //printf("\nres = " );
  //  print_list(head_res);
    return head_res;
}

/* same procedure just returning remender insted of division */
d_list *modulus(d_list *head1,d_list *head2)
{
    d_list *ptr1,*ptr2,*tmp,*head_res = NULL;
    long long int num1,num2;
    int count = 0,j=0,i=0,i_res,m_res = 0;
    char *op_put,*ex = NULL;
   
    ptr1 = head1;
    num2 = atoll(final_string(head2));
    
    while (ptr1 -> next != NULL)
	ptr1 = ptr1 -> next;

    while (ptr1 != NULL)
    {
	if (ex != NULL)
	{
	    strcat(ex,ptr1 -> num);
	    num1 = atoll(ex);
	}
	else
	{
	    num1 = atoll(ptr1 -> num);
	    ex = (ptr1 -> num);
	}

	if (num2 > num1)
	{
	    while(num2 > num1)
	    {
		ptr1 = ptr1 -> prv;
		strcat(ex,ptr1 -> num);
		num1 = atoll(ex);
	    }
	    op_put = my_itoa(num1 / num2); 
	    m_res = num1 % num2;
	}
	else
	{
	    i_res = num1/num2;
	    m_res = num1%num2;
	    op_put = my_itoa(i_res);
	}
	op_put = be_insert(op_put);
	insert_first(&head_res,op_put);

	ex = my_itoa(m_res);

	ptr1 = ptr1 -> prv;

	if (ptr1 != NULL)
	{    
	    strcat(ex,ptr1 -> num);
	    op_put = my_itoa(atoll(ex) / num2);
	    m_res = atoll(ex) % num2;
	    ex = my_itoa(m_res);
	    op_put = be_insert(op_put);
	    insert_first(&head_res,op_put);
	}
	else
	    break;

	ptr1 = ptr1 -> prv;
    }
    head_res = NULL;
    create_d_list(&head_res,ex);
    return head_res;
}

/* this function convert the double link list into 
   string and return the cahrecter pointer */
char *final_string(d_list *head)
{
    d_list *ptr;
    char *num,*out,*op_str = calloc(100,sizeof(char));
    int i = 0;
    ptr = head;

    if (ptr == NULL)
	return NULL;

    while(ptr -> next != NULL)
    {
	ptr = ptr->next;
    }
    while(ptr != NULL)
    {
	out = strcat(op_str,ptr -> num);

	ptr = ptr -> prv;
	i++;
    }
    return out;
}

/* basicaly this function is insert last */
int insert(d_list **head,char *data)
{
    d_list *ptr,*new;

    if (*head == NULL)
    {
	*head = create_node(data);	   
    }
    else
    {
	ptr = *head;
	while (ptr->next != NULL)
	    ptr = ptr -> next;

	new = create_node(data);
	ptr -> next = new;
	new -> prv = ptr;
    }
}

/* insert fist node */
int insert_first(d_list **head,char *data)
{
    d_list *ptr,*new;

    if (*head == NULL)
    {
	*head = create_node(data);	   
    }
    else
    {
	ptr = *head;
	new = create_node(data);

	ptr -> prv = new;
	new -> next = ptr;
	*head = new;
    }
}

d_list *create_node(char *data)
{
    d_list *new = malloc(sizeof(d_list));
    if (new != NULL)
    {
	strcpy(new->num,data);
	new->prv = NULL;
	new->next = NULL;
    }

    return new;
}

int print_list(d_list *head)
{
    d_list *ptr;
    int i=1;

    if (head == NULL)
	return 0;

    ptr = head;

    while(ptr->next != NULL)
	ptr = ptr->next;


    while(ptr != NULL)
    {
	printf("%s  ",ptr->num);
	ptr = ptr->prv;
	i++;
    }
}

/* itoa function which converts int to ascci */
char* my_itoa(long long int num)
{
    int i=0;
    char *str, *ret;
    char *s = calloc(100,sizeof(char));

    // check number is < 0.
    if ( num < 0)
    {
	num *= -1;
    }

    // loop to convert int to char.
    while ( num )
    { 
	s[i] =(num % 10) + 48;
	num =(num / 10);
	i++;
    }
    s[i] = '\0';

    //printf("\nstring at itoa = %s\n",s);
    // call rev_string function to make string rev.
    str = rev_string(s);
    return str;
}

/* reverce strting used in itoa */
char* rev_string(char *s)
{
    char *buff = calloc(100,sizeof(char));
    int size, i=0,f;

    size = strlen(s);

    int j = size-1;
    f = 4 - j;
    /*   // save first '-' char
	 if (s[0] == '-')
	 {
	 buff[0] = '-';
	 i++;
	 }*/

    // save reverce string is another array and then return address
    while (i<size)
    {
	buff[j] = s[i]; 
	i++;
	j--;
    }
    buff[i]= '\0';

    return buff;
}

/* this funtion adds zeroes if needed*/
char *be_insert(char *str)
{
    char *res = calloc(6,sizeof(char));
    int i = 3, count = (strlen(str) - 1);
    if(count < 3)
    {
	while (count >= 0)
	{
	    res[i] = str[count];
	    count--;
	    i--;
	}
	while (i>=0)
	{
	    res[i] = '0';
	    i--;
	}
	i = 3;
     
     return res;
    }
    return str;
}
