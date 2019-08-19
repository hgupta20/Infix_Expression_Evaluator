/* This file contains the user interface code for the Infix Evaluation Project
 *  Project 5 for CS 211 for Fall 2017
 *
 * Date: 10/21/17
 *
 * Author: Pat Troy
 *
 */

#include "proj5Tokens.h"
#include "proj5Array.h"

void printCommands(){
  printf ("The commands for this program are:\n\n");
  printf ("q - to quit the program\n");
  printf ("? - to list the accepted commands\n");
  printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");


}

void processExpression (Token inputToken, TokenReader *tr);


bool debugMode = false;
int main(int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */
    for(int i = 0; i < argc; i++){
  		if(strcmp(argv[i], "-d") == 0){
  			printf("\nDebug Mode On\n");
  			debugMode = true;
  		}
  	}

    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");


    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       processExpression(inputToken, &tr);
      }

      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }

  printf ("Quitting Program\n");
  return 1;
}
int eval(int v1, int oper, int v2)
  {
    
    if (oper == '+')
      {
          return(v1+v2);
      }
    else if(oper == '*')
      {
        return(v1*v2);
      }
    else if(oper == '-')
      {
        return(v1-v2);
      }
    else{
      if(v2==0)
        {
          printf("\nError Cannot divide by zero");
          return 0;
        }
        else
          return(v1/v2);
    }
  }

void processExpression (Token inputToken, TokenReader *tr)
{
 /**********************************************/
 /* Declare both stack head pointers here      */
 ArrayList *operatorStack = new ArrayList();
 ArrayList *valueStack = new ArrayList();
 int oper;
 int v1;
 int v2;
 int v3;
 operatorStack->init();
 valueStack->init();

 /* Loop until the expression reaches its End */
 while (inputToken.equalsType(EOLN) == false)
   {
    /* The expression contain a VALUE */
    if (inputToken.equalsType(VALUE))
      {
       /* make this a debugMode statement */
       if(debugMode==true)
          printf ("Value: %d, ", inputToken.getValue() );

      valueStack->push(inputToken.getValue());
       // add code to perform this operation here

      }

    /* The expression contains an OPERATOR */
    else if (inputToken.equalsType(OPERATOR))
      {
        if(debugMode==true)
        {
       /* make this a debugMode statement */
       printf ("Operator: %c, ", inputToken.getOperator() );
     }
       if(inputToken.getOperator()=='(')
          operatorStack->push(inputToken.getOperator());
        else if(inputToken.getOperator()=='+'||inputToken.getOperator()=='-')
            {
              //Using 42-'*',43-'+',45-'-',47-'/'
              while(operatorStack->isEmpty()==false && (operatorStack->top()==43 || operatorStack->top()==45 || operatorStack->top()==42|| operatorStack->top()==47))
                  {
                  if(operatorStack->top() != 43 && operatorStack->top() != 45 && operatorStack->top() != 42 && operatorStack->top() != 47)
                    {
                      printf("ERROR - Top of operatorStack is not +, -, *, or /\n");
                      return;
                    }
                  oper =operatorStack->top();
                  operatorStack->pop();
                  //pop (operatorStack)
                  v2 = valueStack->top();
                  valueStack->pop();
                  //pop (valueStack)
                  v1 = valueStack->top();
                  valueStack->pop();
                  v3 = eval ( v1,oper,v2);
                  printf("v1 is %d, v2 is %d", v1,v2);
                  valueStack->push(v3);
                }
            operatorStack->push(inputToken.getOperator());
            }
        else if(inputToken.getOperator()==42||inputToken.getOperator()==47)
          {
            while(operatorStack->isEmpty()==false && (operatorStack->top()==42 || operatorStack->top()==47))
                {
                  if(operatorStack->top() != 43 && operatorStack->top() != 45 && operatorStack->top() != 42 && operatorStack->top() != 47)
                    {
                      printf("ERROR - Top of operatorStack is not +, -, *, or /\n");
                      return;
                    }
                  oper =operatorStack->top();
                  operatorStack->pop();
                  //pop (operatorStack)
                  v2 = valueStack->top();
                  valueStack->pop();
                  //pop (valueStack)
                  v1 = valueStack->top();
                  valueStack->pop();
                  v3 = eval ( v1,oper,v2);
                  valueStack->push(v3);
                }
              operatorStack->push(inputToken.getOperator());
          }
      else if(inputToken.getOperator()==')')
        {
            while(operatorStack->isEmpty()==false && (operatorStack->top()!='('))
              {
                if(operatorStack->top() != 43 && operatorStack->top() != 45 && operatorStack->top() != 42 && operatorStack->top() != 47)
                  {
                    printf("ERROR - Top of operatorStack is not +, -, *, or /\n");
                    return;
                  }
                oper =operatorStack->top();
                operatorStack->pop();
                //pop (operators)
                v2 = valueStack->top();
                valueStack->pop();
                //pop (value)
                v1 = valueStack->top();
                valueStack->pop();
                v3 = eval ( v1,oper,v2);
                valueStack->push(v3);
              }
            if(operatorStack->isEmpty()==true)
                {
                printf("\nERROR - operatorStack is empty\n");
                }
            else{
              operatorStack->pop();

            }
        }



       // add code to perform this operation here


     }

    /* get next token from input */
    inputToken = tr->getNextToken ();
   }
   /* The expression has reached its end */
   //THIRD STEP: once the EndOfLine token is encountered:
    //loop while the operatorStack is not empty
   while(operatorStack->isEmpty()!=true)
    {
      if(operatorStack->top() != 43 && operatorStack->top() != 45 && operatorStack->top() != 42 && operatorStack->top() != 47)
        {
          printf("ERROR - Top of operatorStack is not +, -, *, or /\n");
          return;
        }
      oper =operatorStack->top();
      operatorStack->pop();
      //pop (operatorStack)
      v2 = valueStack->top();
      valueStack->pop();
      //pop (valueStack)
      v1 = valueStack->top();
      valueStack->pop();
      v3 = eval ( v1,oper,v2);
      valueStack->push(v3);
    }
    if(valueStack->isEmpty() == true){
      printf("ERROR - valueStack is empty!!\n");
    }
    else{
      //print out the top of the valueStack at the result of the expression
      printf("\nThe value is %d\n",valueStack->top());
    }
    
    
 printf ("\n");
}
