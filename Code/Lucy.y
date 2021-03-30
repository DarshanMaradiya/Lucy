%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include <string.h>
	#include "mylib.h"
%}
%union
{
	int ival;
	float fval;
	double dval;
	char cval;
	char* strval;
	char bval;
	char* id;

	struct valueNode* value_node;
	struct symbolNode* symbol_node;
	struct listNode* list_node;

	struct declarationNode* declaration_node;
	struct assignmentNode* assignment_node;
	struct expressionNode* expression_node;
	struct statementNode* statement_node;
	struct constructNode* construct_node;
	struct statementSetNode* statement_set_node;

	struct ifBlock* if_block;
	struct elifBlock* elif_blocks;
	struct elseBlock* else_block;
	struct optionalBlocks* optional_blocks;
	struct ifConstructNode* if_construct;
	struct forConstruct* for_construct;
	struct whileConstruct* while_construct;
}

%token <ival> INT_VAL
%token <fval> FLOAT_VAL
%token <dval> DOUBLE_VAL
%token <cval> CHAR_VAL
%token <strval> STRING_VAL
%token <bval> BOOLEAN_VAL
%token <id> ID

%token INT LONG FLOAT DOUBLE CHAR STRING BOOLEAN VOID
%token PLUS MINUS MULTIPLY DIVIDE MODULO EXCLAIMATION
%token SWAP
%token POWER INCREMENT DECREMENT
%token BIT_AND BIT_OR BIT_XOR BIT_NOT L_SHIFT R_SHIFT
%token AND OR
%token EQUAL NOT_EQUAL LESS_THEN GREAT_THEN LESS_EQUAL GREAT_EQUAL
%token ASSIGN PLUS_EQUAL MINUS_EQUAL MULTIPLY_EQUAL DIVIDE_EQUAL MODULO_EQUAL
%token ROUNDOPEN ROUNDCLOSE CURLYOPEN CURLYCLOSE SQUAREOPEN SQUARECLOSE
%token COLON SEMICOLON QUESTIONMARK DOT COMMA BSLASH NEW_LINE PRINT
%token IF ELIF ELSE FOR WHILE 
%token BREAK CONTINUE SWITCH RETURN DEFAULT CASE
%token MAIN

%type <ival> DT 
%type <list_node> LIST 
%type <symbol_node> IDS

%type <if_block> IF_BLOCK
%type <elif_blocks> ELIF_BLOCKS
%type <else_block> ELSE_BLOCK
%type <optional_blocks> OPTIONAL_BLOCKS
%type <if_construct> IF_CONSTRUCT
%type <statement_node> FIRST LAST
%type <expression_node> MIDDLE
%type <for_construct> FOR_CONSTRUCT
%type <while_construct> WHILE_CONSTRUCT

%type <statement_set_node> STATEMENT_SET BODY
%type <statement_node> STATEMENT
%type <construct_node> CONSTRUCT
%type <declaration_node> DECLARATION
%type <assignment_node> ASSIGNMENT
%type <expression_node> EXPRESSION TERNARY LOG_OR LOG_AND BITWISE_OR BITWISE_XOR BITWISE_AND
%type <expression_node> REL_E REL_C BIT_SHIFT ARITH_1 ARITH_2 EXP FACT UNARY POST_INC_DEC BRACKETS ID_VAL
%type <value_node> VAL

%%
PROGRAM : DT MAIN ROUNDOPEN ROUNDCLOSE OPTIONAL_NEWLINES
		  CURLYOPEN OPTIONAL_NEWLINES
		  	STATEMENT_SET 				
		  CURLYCLOSE
		  {
		  		/*$8 = reverseStatementSetNodes($8);*/
		  		printf("--------------------------------- \n\n");
		  		printf("\n	----------------- Abstract Syntax  Tree	----------------- \n\n");
		  		printStatementSetNode($8);
		  		printf("\n\n");
		  		executeProgram($8);
		  		/*display();*/
		  		exit(0);
		  }
		;

OPTIONAL_NEWLINES : /* epsilon */
				 | NEW_LINE OPTIONAL_NEWLINES 						{line++;}
				 ;

TERMINATOR : NEW_LINE 												{line++;}
		   | SEMICOLON
		   | NEW_LINE TERMINATOR									{line++;}
		   | SEMICOLON TERMINATOR
		   ;

OPTIONAL_TERMINATOR : /* epsilon */
					| TERMINATOR
					;

STATEMENT_SET : /* epsilon */ 										{$$ = NULL;}
			  | TERMINATOR 											{$$ = NULL;}
			  | STATEMENT 			 								{$$ = makeStatementSetNode(NULL, $1, C_STATEMENT_NODE);}
			  | STATEMENT TERMINATOR STATEMENT_SET					{$$ = makeStatementSetNode($3, $1, C_STATEMENT_NODE);}
   			/*| CONSTRUCT 		 									{$$ = makeStatementSetNode(NULL, $1, C_CONSTRUCT_NODE);}*/
   			  | CONSTRUCT OPTIONAL_TERMINATOR STATEMENT_SET			{$$ = makeStatementSetNode($3, $1, C_CONSTRUCT_NODE);}
   			  ;

STATEMENT : DECLARATION												{$$ = makeStatementNode($1, C_DECLARATION_NODE);}
		  | ASSIGNMENT 												{$$ = makeStatementNode($1, C_ASSIGNMENT_NODE);}
		  | ID SWAP ID 												{$$ = makeStatementNode(makeSwapOperationNode($1, $3), C_SWAP_OPERATION_NODE);}
		  | EXPRESSION 												{$$ = makeStatementNode($1, C_EXPRESSION_NODE);}
		  | PRINT ROUNDOPEN EXPRESSION ROUNDCLOSE 					{$$ = makeStatementNode($3, C_PRINT_NODE);}
		  | BREAK 													{$$ = makeStatementNode(NULL, C_BREAK_NODE);}
		  | CONTINUE 												{$$ = makeStatementNode(NULL, C_CONTINUE_NODE);}
		  ;

CONSTRUCT : IF_CONSTRUCT 											{$$ = makeConstructNode($1, C_IF_CONSTRUCT);}
		  | FOR_CONSTRUCT 											{$$ = makeConstructNode($1, C_FOR_CONSTRUCT);}
		  | WHILE_CONSTRUCT 										{$$ = makeConstructNode($1, C_WHILE_CONSTRUCT);}
		  ;

DECLARATION : DT LIST 												{$$ = makeDeclarationNode($1, $2);}
			;

DT : INT 															{$$ = C_INT;}
   | LONG 															{$$ = C_LONG;}
   | FLOAT 															{$$ = C_FLOAT;}
   | DOUBLE 														{$$ = C_DOUBLE;}
   | CHAR 															{$$ = C_CHAR;}
   | STRING 														{$$ = C_STRING;}
   | BOOLEAN 														{$$ = C_BOOLEAN;}
   | VOID 															{$$ = C_VOID;}
   ;

LIST : IDS 			   												{$$ = makeListNode($1, NULL);}
     | IDS COMMA LIST  												{$$ = makeListNode($1, $3);}
     ;

IDS : ID 															{$$ = makeSymbolNode($1, NULL);}
    | ID ASSIGN EXPRESSION											{$$ = makeSymbolNode($1, $3);}
    ;

ASSIGNMENT : ID ASSIGN EXPRESSION 									{$$ = makeAssignmentNode($1, $3, C_ASSIGN);}
		   | ID PLUS_EQUAL EXPRESSION 								{$$ = makeAssignmentNode($1, $3, C_PLUS_EQUAL);}
		   | ID MINUS_EQUAL EXPRESSION 								{$$ = makeAssignmentNode($1, $3, C_MINUS_EQUAL);}
		   | ID MULTIPLY_EQUAL EXPRESSION 							{$$ = makeAssignmentNode($1, $3, C_MULTIPLY_EQUAL);}
		   | ID DIVIDE_EQUAL EXPRESSION 							{$$ = makeAssignmentNode($1, $3, C_DIVIDE_EQUAL);}
		   | ID MODULO_EQUAL EXPRESSION 							{$$ = makeAssignmentNode($1, $3, C_MODULO_EQUAL);}
		   ;

EXPRESSION : TERNARY 												{$$ = $1;}
		   | ASSIGNMENT 											{$$ = makeExpressionNodeFromAssignment($1);}
		   ;

TERNARY : LOG_OR QUESTIONMARK LOG_OR COLON LOG_OR 					{$$ = ternaryOperation($1, $3, $5);}
		| LOG_OR 													{$$ = $1;}
		;

LOG_OR : LOG_OR OR LOG_AND 											{$$ = binaryOperation($1, $3, C_OR);}
	   | LOG_AND 													{$$ = $1;}
	   ;

LOG_AND : LOG_AND AND BITWISE_OR 									{$$ = binaryOperation($1, $3, C_AND);}
		| BITWISE_OR 												{$$ = $1;}
		;

BITWISE_OR : BITWISE_OR BIT_OR BITWISE_XOR 							{$$ = binaryOperation($1, $3, C_BIT_OR);}
		   | BITWISE_XOR 											{$$ = $1;}
		   ;

BITWISE_XOR : BITWISE_XOR BIT_XOR BITWISE_AND 						{$$ = binaryOperation($1, $3, C_BIT_XOR);}
			| BITWISE_AND 											{$$ = $1;}
			;

BITWISE_AND : BITWISE_AND BIT_AND REL_E 							{$$ = binaryOperation($1, $3, C_BIT_AND);}
			| REL_E 												{$$ = $1;}
			;

REL_E : REL_E EQUAL REL_C 											{$$ = binaryOperation($1, $3, C_EQUAL);}
	  | REL_E NOT_EQUAL REL_C 										{$$ = binaryOperation($1, $3, C_NOT_EQUAL);}
	  | REL_C 														{$$ = $1;}
	  ;

REL_C : REL_C LESS_THEN BIT_SHIFT 									{$$ = binaryOperation($1, $3, C_LESS_THEN);}
	  | REL_C GREAT_THEN BIT_SHIFT 									{$$ = binaryOperation($1, $3, C_GREAT_THEN);}
	  | REL_C LESS_EQUAL BIT_SHIFT 									{$$ = binaryOperation($1, $3, C_LESS_EQUAL);}
	  | REL_C GREAT_EQUAL BIT_SHIFT 								{$$ = binaryOperation($1, $3, C_GREAT_EQUAL);}
	  | BIT_SHIFT 													{$$ = $1;}
	  ;

BIT_SHIFT : BIT_SHIFT L_SHIFT ARITH_1 								{$$ = binaryOperation($1, $3, C_L_SHIFT);}
		  | BIT_SHIFT R_SHIFT ARITH_1 								{$$ = binaryOperation($1, $3, C_R_SHIFT);}
		  | ARITH_1 												{$$ = $1;}
		  ;

ARITH_1 : ARITH_1 PLUS ARITH_2 										{$$ = binaryOperation($1, $3, C_PLUS);}
		| ARITH_1 MINUS ARITH_2 									{$$ = binaryOperation($1, $3, C_MINUS);}
		| ARITH_2 													{$$ = $1;}
		;

ARITH_2 : ARITH_2 MULTIPLY EXP 										{$$ = binaryOperation($1, $3, C_MULTIPLY);}
		| ARITH_2 DIVIDE EXP 										{$$ = binaryOperation($1, $3, C_DIVIDE);}
		| ARITH_2 MODULO EXP 										{$$ = binaryOperation($1, $3, C_MODULO);}
		| EXP 														{$$ = $1;}
		;

EXP : FACT POWER EXP 												{$$ = binaryOperation($1, $3, C_EXP);}
	| FACT 															{$$ = $1;}
	;

FACT : FACT EXCLAIMATION 											{$$ = unaryOperation($1, C_FACT);}
	 | UNARY 														{$$ = $1;}
	 ;

UNARY : INCREMENT ID 												{$$ = unaryOperation(makeExpressionNode($2, NULL), C_PRE_INC);}
	  | DECREMENT ID 												{$$ = unaryOperation(makeExpressionNode($2, NULL), C_PRE_DEC);}
	  | PLUS POST_INC_DEC											{$$ = unaryOperation($2, C_PLUS);}
	  | MINUS POST_INC_DEC											{$$ = unaryOperation($2, C_MINUS);}
	  | EXCLAIMATION POST_INC_DEC									{$$ = unaryOperation($2, C_NOT);}
	  | BIT_NOT POST_INC_DEC 										{$$ = unaryOperation($2, C_BIT_NOT);}	
	  | POST_INC_DEC 												{$$ = $1;}
	  ;

POST_INC_DEC : ID INCREMENT 										{$$ = unaryOperation(makeExpressionNode($1, NULL), C_POST_INC);}
			 | ID DECREMENT 										{$$ = unaryOperation(makeExpressionNode($1, NULL), C_POST_DEC);}
			 | BRACKETS 											{$$ = $1;}
			 ;

BRACKETS : ROUNDOPEN ID_VAL ROUNDCLOSE 								{$$ = $2;}
		 | ROUNDOPEN EXPRESSION ROUNDCLOSE 							{$$ = $2;}		
		 | ID_VAL 													{$$ = $1;}
		 ;

ID_VAL : ID 														{$$ = makeExpressionNode($1, NULL);}
  	   | VAL 														{$$ = makeExpressionNode(NULL, $1);}
       ;

VAL : INT_VAL 		{union varvalue *var_value = (varvalue *)malloc(sizeof(varvalue)); var_value->ival = $1; $$ = makeValueNode(C_INT, var_value);}
    | FLOAT_VAL 	{union varvalue *var_value = (varvalue *)malloc(sizeof(varvalue)); var_value->fval = $1; $$ = makeValueNode(C_FLOAT, var_value);}
    | DOUBLE_VAL 	{union varvalue *var_value = (varvalue *)malloc(sizeof(varvalue)); var_value->dval = $1; $$ = makeValueNode(C_DOUBLE, var_value);}
    | CHAR_VAL 		{union varvalue *var_value = (varvalue *)malloc(sizeof(varvalue)); var_value->cval = $1; $$ = makeValueNode(C_CHAR, var_value);}
    | STRING_VAL	{union varvalue *var_value = (varvalue *)malloc(sizeof(varvalue)); var_value->strval = $1; $$ = makeValueNode(C_STRING, var_value);}
    | BOOLEAN_VAL 	{union varvalue *var_value = (varvalue *)malloc(sizeof(varvalue)); var_value->bval = $1; $$ = makeValueNode(C_BOOLEAN, var_value);}
    ;   


IF_CONSTRUCT : IF_BLOCK 
			   OPTIONAL_BLOCKS 										{$$ = makeIfConstruct($1, $2);}
			 ;

BODY : CURLYOPEN 
	   OPTIONAL_NEWLINES
			STATEMENT_SET 
	   CURLYCLOSE 													{$$ = $3;}
	 | STATEMENT OPTIONAL_TERMINATOR								{$$ = makeStatementSetNode(NULL, $1, C_STATEMENT_NODE);}
	 | CONSTRUCT 													{$$ = makeStatementSetNode(NULL, $1, C_CONSTRUCT_NODE);}
	 ;
	 
IF_BLOCK : IF ROUNDOPEN EXPRESSION ROUNDCLOSE  
		   OPTIONAL_NEWLINES 					
        	 BODY 
           OPTIONAL_NEWLINES										{$$ = makeIfBlock($3, $6);}
		 ;

OPTIONAL_BLOCKS : ELIF_BLOCKS 
				  ELSE_BLOCK 				 						{$$ = makeOptionalBlocks($1, $2);}
				;

ELIF_BLOCKS : /* epsilon */  										{$$ = NULL;}
			| ELIF ROUNDOPEN EXPRESSION ROUNDCLOSE 
			  OPTIONAL_NEWLINES 					
              	BODY 
              OPTIONAL_NEWLINES 
              ELIF_BLOCKS											{$$ = makeElifBlock($3, $6, $8);}
           ;

ELSE_BLOCK : /* epsilon */ 											{$$ = NULL;}
		   | ELSE 
		     OPTIONAL_NEWLINES
			   BODY		 											{$$ = makeElseBlock($3);}						
		   ;

FOR_CONSTRUCT : FOR ROUNDOPEN 
					FIRST SEMICOLON 
					MIDDLE SEMICOLON 
					LAST ROUNDCLOSE 
				OPTIONAL_NEWLINES
				BODY												{$$ = makeForConstruct($3, $5, $7, $10);}
			  ;

LAST : FIRST 														{$$ = $1;}
	 ; 									

FIRST : STATEMENT 													{$$ = $1;}
	  | /* epsilon */ 												{$$ = NULL;}
	  ;

MIDDLE : EXPRESSION													{$$ = $1;}
	   | /* epsilon */	 											{union varvalue *var_value = (varvalue *)malloc(sizeof(varvalue)); 
	   																 var_value->bval = 1; 
	   																 $$ = makeExpressionNode(NULL,makeValueNode(C_BOOLEAN, var_value));}
	   ;

WHILE_CONSTRUCT : WHILE ROUNDOPEN EXPRESSION ROUNDCLOSE 
				  OPTIONAL_NEWLINES
				  	BODY  											{$$ = makeWhileConstruct($3, $6);}
				;

%%

main(){
	yyparse();
}

