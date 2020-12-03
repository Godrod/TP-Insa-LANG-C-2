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
#include "test.h"

static Boolean binary_operator(Stack *s, int operation){

  int op1,op2; /*the operands*/
  int res; /*the result*/

  if (isEmpty(s)){
    fprintf(stderr,"Empty stack : can not proceed to the binary operation\n");
    return(FALSE);
  }
  op1=pop(s);

  if (isEmpty(s)){
    fprintf(stderr,"Empty stack : can not proceed to the binary operation\n");
    return(FALSE);
  }
  op2=pop(s);

  /* computation*/
  switch(operation){
      case ADD:
        res = op1 + op2;
        break;
      case SUBSTRACT:
        res = op2 - op1;
        break;
      case MULTIPLY:
        res = op2 * op1;
        break;
      case DIVIDE:
        res = op2 / op1;
        break;
      default:
        fprintf(stderr,"Unknown operator\n");
        return(FALSE);
  }

  /* Put the result in the stack */
  push(s,res);

  return(TRUE);
}

Boolean binary_operator_pf (Stack *s, int(*op)(int, int))
{
	int op1,op2; /*the operands*/
  	int res; /*the result*/

  	if (isEmpty(s)){
    	fprintf(stderr,"Empty stack : can not proceed to the binary operation\n");
    	return(FALSE);
 	}
 	op1=pop(s);

  	if (isEmpty(s)){
    	fprintf(stderr,"Empty stack : can not proceed to the binary operation\n");
    	return(FALSE);
  	}
  	op2=pop(s);
	

	res = op(op1, op2);

	push(s, res);
	return TRUE;
}

int add_func(int a, int b)
{
	return a + b;
}

int sub_func(int a, int b)
{
	return b - a;
}

int multiply_func(int a, int b)
{
	return a * b;
}

int divide_func(int a, int b)
{
	return b / a;
}


/*!
* Modify the stack state by adding its two first values
* \param[in,out] s the stack to be modified
* \return Booolean TRUE if the operation is successful, FALSE otherwise
*/
Boolean add(Stack *s){
	return binary_operator_pf(s, add_func);
}

/*!
* Modify the stack state by substracting its two first values
* \param[in,out] s the stack to be modified
* \return Booolean TRUE if the operation is successful, FALSE otherwise
*/
Boolean substract(Stack *s){
	return binary_operator_pf(s, sub_func);
}

/*!
* Modify the stack state by substracting its two first values
* \param[in,out] s the stack to be modified
* \return Booolean TRUE if the operation is successful, FALSE otherwise
*/
Boolean multiply(Stack *s){
	return binary_operator_pf(s, multiply_func);
}
/*!
* Modify the stack state by substracting its two first values
* \param[in,out] s the stack to be modified
* \return Booolean TRUE if the operation is successful, FALSE otherwise
*/
Boolean divide(Stack *s){
	return binary_operator_pf(s, divide_func);
}



/*!
 * \fn int test_eval(void)
 * Tests stack functionnalities
 * \return EXIT_SUCCESS if everything is ok
 */
int test_eval(void){

    Stack s;

    init_stack(&s);
    push(&s,1);
    push(&s,2);
    substract(&s);
    display_test_int("Test substract()",-1,pop(&s)); push(&s,-1); /*the push is to put back the popped value for the test*/
    push(&s,3);
    add(&s);
    display_test_int("Test add()",2,pop(&s)); push(&s,2); /*the push is to put back the popped value for the test*/
    push(&s,4);
    push(&s,5);
    add(&s);
    add(&s);

    display_test_check_by_user("Test substract() and add() : (display stack should be 0 11)");
    display_stack(&s);

    push(&s,5);
    multiply(&s);
    display_test_int("Test multiply() 11 by 5:", 55, pop(&s)); push(&s, 55);
    display_stack(&s);
    
    push(&s, 5);
    divide(&s);
    display_test_int("Test divide() 55 by 5:", 11, pop(&s)); push(&s, 11);
    display_stack(&s);

	return(EXIT_SUCCESS);
}

