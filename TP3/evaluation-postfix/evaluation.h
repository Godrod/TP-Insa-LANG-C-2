/*!
 * \file    evaluation.h
 * \brief   Declaration of functions to process a stack of int as a post-fix expression
 */

#ifndef EVALUATION
#define EVALUATION

#include "application.h"
#include "stack.h"

typedef struct {
    char c;
    Boolean (*act) (Stack*);
}Map_element;



Boolean add(Stack *s);
Boolean substract(Stack *s);
Boolean multiply(Stack *s);
Boolean divide(Stack *s);
int test_eval(void);

int evaluateExpression(char *str);
int test_eval_string(void);

#endif
