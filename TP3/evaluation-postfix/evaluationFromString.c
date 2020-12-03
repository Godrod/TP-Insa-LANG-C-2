/*!
 * \file  evaluation.c
 * \brief  Definition of functions to process a stack of int as a post-fix expression
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "application.h"
#include "evaluation.h"
#include "stack.h"

Map_element element_tab[4];

int isANumber(char c)
{
    return (c>='0') && (c <= '9');
}

/*!
* Handle a stack to evaluate a postfix expression
* \param[in] str the postfix expression to be evaluated
* \return int the result of the evaluation
*/
int evaluateExpression(char *str){

  Stack s;
  int i;

  init_stack(&s);
  i=0;
  while(str[i] != '\0')
  {
    if(isANumber(str[i]))
        push(&s, str[i] - '0');
    else
    {
        switch(str[i])
        {
            case '+' : add(&s); break;
            case '-' : substract(&s); break;
            case '*' : multiply(&s); break;
            case '/' : divide(&s); break;
            default : fprintf(stderr,"unknown operator\n"); return 0;
        }
    }
    ++i;
  }
  return pop(&s);
}

int evaluateExpression_pf(char *str)
{

  element_tab[0].act = add;
  element_tab[0].c = '+';
  element_tab[1].act = substract;
  element_tab[1].c = '-';
  element_tab[2].act = multiply;
  element_tab[2].c = '*';
  element_tab[3].act = divide;
  element_tab[3].c = '/';


  Stack s;
  int i, j;

  init_stack(&s);
  i=0;
  while(str[i] != '\0')
  {
    if(isANumber(str[i]))
        push(&s, str[i] - '0');
    else
    {
        for (j = 0; j < 3; j++)
        {
          if (str[i] == element_tab[j].c)
          {
            element_tab[j].act(&s);
          }
        }
        
    }
    ++i;
  }
  return pop(&s);
}

/*!
 * \fn int test_eval_string(void)
 * Tests stack functionnalities
 * \return EXIT_SUCCESS if everything is ok
 */
int test_eval_string(void){
    Stack s;
    char * expr1 = "393-4*3/+";
    char * expr2 = "5393-4*3/++sc";

    init_stack(&s);
    /*add your test from expression here*/
    evaluateExpression(expr1);
    while(!isEmpty(&s))
      pop(&s);
    evaluateExpression(expr2);

  return(EXIT_SUCCESS);
}

