/* =====================================================================================
 *
 *       Filename:  apc_main.c
 *        Created:  Saturday 11 February 2017 03:18:21  IST
 *         Author:  KEWAL UKUNDE , kewalukunde@gmail.com
 *   Organization:  Emertxe technology Banglore
 *
 * =====================================================================================
 */

#include "../include/apc.h"

int main()
{
    char *buff = calloc(200,sizeof(char));
    char *result,opt;
    int i=0,j=0,op_flag = 0,non_num_flag = 0;

    system("clear");
    printf("\n\t\tARBITRARY PRECISION CALCULATOR");
    /* this loop make program compitable for any ip */
    while (1)
    {
	printf("\n\n");
	scanf("%s",buff);

	/* for exit from program enter q */
	if (!strcmp("q",buff))
	    break;
	else
	{
	    /* enterd charecter should be numric or operetor */
	    while (buff[i] != '\0')
	    {
		if (((buff[i] >= 47) && (buff[i] <= 57)) || (buff[i] == 37) || (buff[i] == 42) || (buff[i] == 43) || (buff[i] == 45))
		    i++;
		else
		{
		    non_num_flag = 1;
		    printf("This operation not possible!!\n");
		    break;
		}
	    }
	}

	i = 0;
	/* collecting operetor from enterd string */
	while (buff[i] != '\0')
	{
	    while (oprator[j])
	    {
		//printf("buff = %c , optr =%c, flag = %d\n",buff[i],oprator[j],flag);
		if (buff[i] == oprator[j])
		{
	            opt = oprator[j];
		    op_flag++;
		    break;
		}
		j++;
	    }
	    j = 0;
	    i++;	
	}

	//printf("flag = %d, op = %c\n",flag,opt);
	/* passing number and operetor to calculator function*/
	if ((op_flag == 1) && (non_num_flag == 0))
	{
	    result = apc_calculator(buff,opt);

	    if (result == NULL)
		printf("0000\n");
	    else
		printf("%s\n",result);
	}
	else if (op_flag == 0)
	    printf("No operator present!!\n");
	else if (op_flag > 1)
	    printf("To many operator present!!\n");
	
	free(buff);
	buff = calloc(200,sizeof(char));
	i=0;
	j=0;
	op_flag = 0;
	non_num_flag = 0;
    }
    return 0;	

}
