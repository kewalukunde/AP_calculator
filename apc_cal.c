#include "apc.c"

char *apc_calculator(char *str,char opt)
{
    d_list *head_op1 = NULL,*head_op2 = NULL,*ptr1,*ptr2,*out_put;
    char *res,*op1,*op2;
    int len1,len2;

    op1 = strtok(str,oprator);
    create_d_list(&head_op1,op1);

    op2 = strtok(NULL,oprator);
    create_d_list(&head_op2,op2);


    switch (opt)
    {
	case '+': out_put = addition(head_op1,head_op2);

		  res = final_string(out_put);
		  break;

	case '-':len1 = strlen(op1);
		 len2 = strlen(op2);

		 if (len1 > len2)
		 {
		     out_put = subtraction(head_op1,head_op2);
		 }
		 else if (len2 > len1)
		 {
		     out_put = subtraction(head_op2,head_op1);
		     printf("-");
		 }
		 else
		 {
		     ptr1 = head_op1;
		     ptr2 = head_op2;

		     while(ptr1 -> next != NULL)
			 ptr1 = ptr1 -> next;
		     while(ptr2 -> next != NULL)
			 ptr2 = ptr2 -> next;

		     len1 = atoi(ptr1 -> num);
		     len2 = atoi(ptr2 -> num);

		     if(len1 > len2)
			 out_put = subtraction(head_op1,head_op2);
		     else if(len1 < len2)
		     {
			 out_put = subtraction(head_op2,head_op1);
			 printf("-");
		     }
		     else
			 out_put = subtraction(head_op2,head_op1);
		 }

		 res = final_string(out_put);
		 break;

	case '*':out_put = multiplication(head_op1,head_op2);
		 res= final_string(out_put);
		 break;

	case '/':len1 = strlen(op1);
		 len2 = strlen(op2);

		 if (len1 > len2)
		 {
		     out_put = division(head_op1,head_op2);
		     res= final_string(out_put);
		 }
		 else
		 {
		     printf("Entered opration is not possible!!\n");
		 }
		 break;

	case '%':len1 = strlen(op1);
		 len2 = strlen(op2);

		 if (len1 > len2)
		 {
		     out_put = modulus(head_op1,head_op2);
		     res= final_string(out_put);
		 }
		 else
		 {
		     printf("Entered opration is not possible!!\n");
		 }
		 break;

	default: printf("\ncan not proceed this opration!!\n");
		 break;
    }
    return res;
}
