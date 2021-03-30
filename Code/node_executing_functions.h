//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																														//
// --------------------------------------------- Node Executing Functions --------------------------------------------- //
//																														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void executeProgram(struct statementSetNode* statement_set_node)
{

	executeStatementSetNode(statement_set_node);
}

void executeStatementSetNode(struct statementSetNode* statement_set_node)
{
	while(statement_set_node != NULL)
	{
		if(statement_set_node->statement_set_type == C_STATEMENT_NODE)
			executeStatementNode(statement_set_node->statement_node);
		else //if(statement_set_node->statement_set_type == C_CONSTRUCT_NODE)
			executeConstructNode(statement_set_node->construct_node);

		if(break_flag == 1 || continue_flag == 1) break;

		statement_set_node = statement_set_node->next;
	}
}

void executeStatementNode(struct statementNode *statement_node)
{
	if(statement_node->statement_type == C_DECLARATION_NODE) executeDeclarationNode(statement_node->statement->declaration_node);
	else if(statement_node->statement_type == C_ASSIGNMENT_NODE) executeAssignmentNode(statement_node->statement->assignment_node);
	else if(statement_node->statement_type == C_SWAP_OPERATION_NODE) executeSwapOperationNode(statement_node->statement->swap_operation_node);
	else if(statement_node->statement_type == C_EXPRESSION_NODE) executeExpressionNode(statement_node->statement->expression_node);
	else if(statement_node->statement_type == C_PRINT_NODE) executePrintStatement(statement_node->statement->expression_node);
	else if(statement_node->statement_type == C_BREAK_NODE) executeBreakStatement(statement_node->statement->break_node);
	else if(statement_node->statement_type == C_CONTINUE_NODE) executeContinueStatement(statement_node->statement->continue_node);
}

void executeBreakStatement(int break_line)
{
	if(break_flag == 0)
	{
		printf("\n[Error : %d] Encountered 'break' outside loop", break_line);
		exit(0);
	}

	break_flag = 1;
}

void executeContinueStatement(int continue_line)
{
	if(continue_flag == 0)
	{
		printf("\n[Error : %d] Encountered 'continue' outside loop", continue_line);
		exit(0);
	}

	continue_flag = 1;
}

void executePrintStatement(struct expressionNode* expression_node)
{
	line = expression_node->line;

	executeExpressionNode(expression_node);

	struct valueNode* value_node = expression_node->value_node;

	switch(value_node->type) {
		case C_INT 		:	printf("%d\n",value_node->value->ival); 						break;
		case C_LONG 	:	printf("%ld\n",value_node->value->lval);						break;
		case C_FLOAT 	:	printf("%f\n",value_node->value->fval);							break;
		case C_DOUBLE 	:	printf("%lf\n",value_node->value->dval);						break;
		case C_CHAR 	:	printf("%c\n",value_node->value->cval);							break;
		case C_STRING 	:	printf("%s\n",value_node->value->strval);						break;
		case C_BOOLEAN 	:	printf("%s\n",(value_node->value->bval == 0)?"false":"true");	break;
	}
}

void executeDeclarationNode(struct declarationNode *declaration_node)
{	
	line = declaration_node->line;

	int type = declaration_node->type;

	// declare each variable listed with initial values
	struct listNode *curr = declaration_node->next;

	for(; curr != NULL; curr = curr->next)
	{
		executeSymbolNode(curr->symbol);
		if(curr->symbol->type != type) {switchUnionValue(curr->symbol->value, curr->symbol->type, type);curr->symbol->type = type;}

		insert(curr->symbol->name, type, curr->symbol->value);
	}
}

void executeSymbolNode(struct symbolNode *symbol)
{
	if(symbol->expression_node == NULL)
	{
		symbol->expression_node = (expressionNode*)malloc(sizeof(expressionNode));
		symbol->expression_node->expression = (expression* )malloc(sizeof(expression));
		symbol->expression_node->expression->value_node = getDefaultValueNode();
		symbol->expression_node->expression_type = C_VALUE_NODE;
		symbol->expression_node->value_node = symbol->expression_node->expression->value_node;
	}
	else executeExpressionNode(symbol->expression_node);

	symbol->type = symbol->expression_node->value_node->type;
	symbol->value = symbol->expression_node->value_node->value;
}

void executeAssignmentNode(struct assignmentNode *assignment_node)
{
	line = assignment_node->line;

	struct variable* var = getVariable(assignment_node->name);
	int operation = assignment_node->operation;

	executeExpressionNode(assignment_node->expression_node);

	struct valueNode* value_node = assignment_node->expression_node->value_node;

	
	if(var->type != value_node->type) {switchUnionValue(value_node->value, value_node->type, var->type);value_node->type = var->type;}

	if(operation == C_ASSIGN)
	{
		if(var->type == C_INT) var->value->ival = value_node->value->ival;
		else if(var->type == C_LONG) var->value->lval = value_node->value->lval;
		else if(var->type == C_FLOAT) var->value->fval = value_node->value->fval;
		else if(var->type == C_DOUBLE) var->value->dval = value_node->value->dval;
		else if(var->type == C_CHAR) var->value->cval = value_node->value->cval;
		else if(var->type == C_STRING) var->value->strval = value_node->value->strval;
		else if(var->type == C_BOOLEAN) var->value->bval = value_node->value->bval;
	}
	else if(operation == C_PLUS_EQUAL)
	{
		if(var->type == C_INT) var->value->ival += value_node->value->ival;
		else if(var->type == C_LONG) var->value->lval += value_node->value->lval;
		else if(var->type == C_FLOAT) var->value->fval += value_node->value->fval;
		else if(var->type == C_DOUBLE) var->value->dval += value_node->value->dval;
		else if(var->type == C_CHAR) var->value->cval += value_node->value->cval;
		// else if(var->type == C_STRING) var->value->strval += value_node->value->strval;
		else if(var->type == C_BOOLEAN) var->value->bval += value_node->value->bval;
	}
	else if(operation == C_MINUS_EQUAL)
	{
		if(var->type == C_INT) var->value->ival -= value_node->value->ival;
		else if(var->type == C_LONG) var->value->lval -= value_node->value->lval;
		else if(var->type == C_FLOAT) var->value->fval -= value_node->value->fval;
		else if(var->type == C_DOUBLE) var->value->dval -= value_node->value->dval;
		else if(var->type == C_CHAR) var->value->cval -= value_node->value->cval;
		// else if(var->type == C_STRING) value_node->value->strval -= value_node->value->strval;
		else if(var->type == C_BOOLEAN) var->value->bval -= value_node->value->bval;
	}
	else if(operation == C_MULTIPLY_EQUAL)
	{
		if(var->type == C_INT) var->value->ival *= value_node->value->ival;
		else if(var->type == C_LONG) var->value->lval *= value_node->value->lval;
		else if(var->type == C_FLOAT) var->value->fval *= value_node->value->fval;
		else if(var->type == C_DOUBLE) var->value->dval *= value_node->value->dval;
		else if(var->type == C_CHAR) var->value->cval *= value_node->value->cval;
		// else if(var->type == C_STRING) var->value->strval *= value_node->value->strval;
		else if(var->type == C_BOOLEAN) var->value->bval *= value_node->value->bval;
	}
	else if(operation == C_DIVIDE_EQUAL)
	{
		if(var->type == C_INT) var->value->ival /= value_node->value->ival;
		else if(var->type == C_LONG) var->value->lval /= value_node->value->lval;
		else if(var->type == C_FLOAT) var->value->fval /= value_node->value->fval;
		else if(var->type == C_DOUBLE) var->value->dval /= value_node->value->dval;
		else if(var->type == C_CHAR) var->value->cval /= value_node->value->cval;
		// else if(var->type == C_STRING) var->value->strval /= value_node->value->strval;
		else if(var->type == C_BOOLEAN) var->value->bval /= value_node->value->bval;
	}
	else if(operation == C_MODULO_EQUAL)
	{
		if(var->type == C_INT) var->value->ival %= value_node->value->ival;
		else if(var->type == C_LONG) var->value->lval %= value_node->value->lval;
		// else if(var->type == C_FLOAT) var->value->fval %= value_node->value->fval;
		// else if(var->type == C_DOUBLE) var->value->dval %= value_node->value->dval;
		else if(var->type == C_CHAR) var->value->cval %= value_node->value->cval;
		// else if(var->type == C_STRING) var->value->strval %= value_node->value->strval;
		else if(var->type == C_BOOLEAN) var->value->bval %= value_node->value->bval;
	}
}

void executeSwapOperationNode(struct swapOperationNode *swap_operation_node)
{
	line = swap_operation_node->line;

	swap(swap_operation_node->variable_1, swap_operation_node->variable_2);
}

void executeExpressionNode(struct expressionNode *expression_node)
{
	line = expression_node->line;

	if(expression_node->expression_type == C_VALUE_NODE)
	{
		expression_node->value_node = makeValueNode(expression_node->expression->value_node->type, expression_node->expression->value_node->value);
	}
	else if(expression_node->expression_type == C_VARIABLE)
	{
		variable* var = getVariable(expression_node->expression->variable);
		expression_node->value_node = makeValueNode(var->type, var->value);
	}
	else if(expression_node->expression_type == C_TERNARY_EXPRESSION)
	{
		executeTernaryExpression(expression_node);
	}
	else if(expression_node->expression_type == C_BINARY_EXPRESSION)
	{
		executeBinaryExpression(expression_node);
	}
	else if(expression_node->expression_type == C_UNARY_EXPRESSION)
	{
		executeUnaryExpression(expression_node);
	}
	else if(expression_node->expression_type == C_ASSIGNMENT_NODE)
	{
		executeAssignmentNode(expression_node->expression->assignment_node);
		variable* var = getVariable(expression_node->expression->assignment_node->name);
		expression_node->value_node = makeValueNode(var->type, var->value);
	}
}

void executeTernaryExpression(struct expressionNode *expression_node)
{
	executeExpressionNode(expression_node->expression->ternary_expression->expression_node_1);
	executeExpressionNode(expression_node->expression->ternary_expression->expression_node_2);
	executeExpressionNode(expression_node->expression->ternary_expression->expression_node_3);

	struct valueNode* value_node_1 = expression_node->expression->ternary_expression->expression_node_1->value_node;
	struct valueNode* value_node_2 = expression_node->expression->ternary_expression->expression_node_2->value_node;
	struct valueNode* value_node_3 = expression_node->expression->ternary_expression->expression_node_3->value_node;
	
	value_node_1 = makeValueNode(value_node_1->type, value_node_1->value);
	value_node_2 = makeValueNode(value_node_2->type, value_node_2->value);
	value_node_3 = makeValueNode(value_node_3->type, value_node_3->value);

	if(value_node_1->type != C_BOOLEAN) {switchUnionValue(value_node_1->value, value_node_1->type, C_BOOLEAN);value_node_1->type = C_BOOLEAN;}	

	if(value_node_1->value->bval)
	{	
		expression_node->value_node = value_node_2;
		// free(value_node_1);
		// free(value_node_3);
	}
	else
	{
		expression_node->value_node = value_node_3;
		// free(value_node_1);
		// free(value_node_2);
	}
}

void executeBinaryExpression(struct expressionNode *expression_node)
{
	executeExpressionNode(expression_node->expression->binary_expression->expression_node_1);
	executeExpressionNode(expression_node->expression->binary_expression->expression_node_2);

	struct valueNode* value_node_1 = expression_node->expression->binary_expression->expression_node_1->value_node;
	struct valueNode* value_node_2 = expression_node->expression->binary_expression->expression_node_2->value_node;

	value_node_1 = makeValueNode(value_node_1->type, value_node_1->value);
	value_node_2 = makeValueNode(value_node_2->type, value_node_2->value);

	int operation = expression_node->expression->binary_expression->operation;

	expression_node->value_node = value_node_1;

	if(operation == C_OR)
	{
		if(value_node_1->type != C_BOOLEAN) {switchUnionValue(value_node_1->value, value_node_1->type, C_BOOLEAN);value_node_1->type = C_BOOLEAN;}
		if(value_node_2->type != C_BOOLEAN) {switchUnionValue(value_node_2->value, value_node_2->type, C_BOOLEAN);value_node_2->type = C_BOOLEAN;}

		value_node_1->value->bval = value_node_1->value->bval || value_node_2->value->bval;
	}
	else if(operation == C_AND)
	{
		if(value_node_1->type != C_BOOLEAN) {switchUnionValue(value_node_1->value, value_node_1->type, C_BOOLEAN);value_node_1->type = C_BOOLEAN;}
		if(value_node_2->type != C_BOOLEAN) {switchUnionValue(value_node_2->value, value_node_2->type, C_BOOLEAN);value_node_2->type = C_BOOLEAN;}

		value_node_1->value->bval = value_node_1->value->bval && value_node_2->value->bval;
	}
	else if(operation == C_BIT_AND)
	{
		// doesn't work with float/double/string
		if(value_node_1->type == C_FLOAT || value_node_1->type == C_DOUBLE || value_node_1->type == C_STRING) {
			printf("\n[Error : %d] bitwise and operation doesn't work with type : %s", line, getDataType(value_node_1->type));
			exit(1);
		}
		if(value_node_2->type == C_FLOAT || value_node_2->type == C_DOUBLE || value_node_2->type == C_STRING) {
			printf("\n[Error : %d] bitwise and operation doesn't work with type : %s", line, getDataType(value_node_2->type));
			exit(1);
		}

		if(value_node_1->type != C_LONG) {switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG;}
		if(value_node_2->type != C_LONG) {switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG;}

		value_node_1->value->lval = value_node_1->value->lval & value_node_2->value->lval;
	}
	else if(operation == C_BIT_OR)
	{
		// doesn't work with float/double/string
		if(value_node_1->type == C_FLOAT || value_node_1->type == C_DOUBLE || value_node_1->type == C_STRING) {
			printf("\n[Error : %d] bitwise or operation doesn't work with type : %s", line, getDataType(value_node_1->type));
			exit(1);
		}
		if(value_node_2->type == C_FLOAT || value_node_2->type == C_DOUBLE || value_node_2->type == C_STRING) {
			printf("\n[Error : %d] bitwise or operation doesn't work with type : %s", line, getDataType(value_node_2->type));
			exit(1);
		}

		if(value_node_1->type != C_LONG) {switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG;}
		if(value_node_2->type != C_LONG) {switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG;}

		value_node_1->value->lval = value_node_1->value->lval | value_node_2->value->lval;
	}
	else if(operation == C_BIT_XOR)
	{
		// doesn't work with float/double/string
		if(value_node_1->type == C_FLOAT || value_node_1->type == C_DOUBLE || value_node_1->type == C_STRING) {
			printf("\n[Error : %d] bitwise xor operation doesn't work with type : %s", line, getDataType(value_node_1->type));
			exit(1);
		}
		if(value_node_2->type == C_FLOAT || value_node_2->type == C_DOUBLE || value_node_2->type == C_STRING) {
			printf("\n[Error : %d] bitwise xor operation doesn't work with type : %s", line, getDataType(value_node_2->type));
			exit(1);
		}

		if(value_node_1->type != C_LONG) {switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG;}
		if(value_node_2->type != C_LONG) {switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG;}

		value_node_1->value->lval = value_node_1->value->lval ^ value_node_2->value->lval;
	}
	else if(operation == C_EQUAL)
	{
		// handle string differently
		if(value_node_1->type == C_STRING)
		{
			if(value_node_2->type == C_STRING)
			{
				value_node_1->value->bval = strcmp(value_node_1->value->strval, value_node_2->value->strval) == 0;
				value_node_1->type = C_BOOLEAN;		
				free(value_node_2);
				return expression_node;
			}
			else
			{
				printf("\n[Error : %d] can not compare string with type : %s", line, getDataType(value_node_2->type));
				exit(1);
			}
		}
		else if(value_node_2->type == C_STRING)
		{
			printf("\n[Error : %d] can not compare string with type : %s", line, getDataType(value_node_1->type));
			exit(1);
		}

		switch(value_node_1->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_DOUBLE);value_node_1->type = C_DOUBLE; 	break;
		}

		switch(value_node_2->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_DOUBLE);value_node_2->type = C_DOUBLE; 	break;
		}

		if(value_node_1->type == C_DOUBLE)
		{
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->bval = value_node_1->value->dval == value_node_2->value->dval;
			else
				value_node_1->value->bval = value_node_1->value->dval == value_node_2->value->lval;
		}
		else
		{
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->bval = value_node_1->value->lval == value_node_2->value->dval;
			else
				value_node_1->value->bval = value_node_1->value->lval == value_node_2->value->lval;
		}

		value_node_1->type = C_BOOLEAN;		
	}
	else if(operation == C_NOT_EQUAL)
	{
		// handle string differently
		if(value_node_1->type == C_STRING)
		{
			if(value_node_2->type == C_STRING)
			{
				value_node_1->value->bval = strcmp(value_node_1->value->strval, value_node_2->value->strval) != 0;
				value_node_1->type = C_BOOLEAN;		
				free(value_node_2);
				return expression_node;
			}
			else
			{
				printf("\n[Error : %d] can not compare string with type : %s", line, getDataType(value_node_2->type));
				exit(1);
			}
		}
		else if(value_node_2->type == C_STRING)
		{
			printf("\n[Error : %d] can not compare string with type : %s", line, getDataType(value_node_1->type));
			exit(1);
		}

		switch(value_node_1->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_DOUBLE);value_node_1->type = C_DOUBLE; 	break;
		}

		switch(value_node_2->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_DOUBLE);value_node_2->type = C_DOUBLE; 	break;
		}

		if(value_node_1->type == C_DOUBLE)
		{
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->bval = value_node_1->value->dval != value_node_2->value->dval;
			else
				value_node_1->value->bval = value_node_1->value->dval != value_node_2->value->lval;
		}
		else
		{
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->bval = value_node_1->value->lval != value_node_2->value->dval;
			else
				value_node_1->value->bval = value_node_1->value->lval != value_node_2->value->lval;
		}

		value_node_1->type = C_BOOLEAN;		
	}
	else if(operation == C_LESS_THEN)
	{
		// handle string differently
		if(value_node_1->type == C_STRING)
		{
			if(value_node_2->type == C_STRING)
			{
				value_node_1->value->bval = strcmp(value_node_1->value->strval, value_node_2->value->strval) < 0;
				value_node_1->type = C_BOOLEAN;		
				free(value_node_2);
				return expression_node;
			}
			else
			{
				printf("\n[Error : %d] can not compare string with type : %s", line, getDataType(value_node_2->type));
				exit(1);
			}
		}
		else if(value_node_2->type == C_STRING)
		{
			printf("\n[Error : %d] can not compare string with type : %s", line, getDataType(value_node_1->type));
			exit(1);
		}

		switch(value_node_1->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_DOUBLE);value_node_1->type = C_DOUBLE; 	break;
		}

		switch(value_node_2->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_DOUBLE);value_node_2->type = C_DOUBLE; 	break;
		}

		if(value_node_1->type == C_DOUBLE)
		{
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->bval = value_node_1->value->dval < value_node_2->value->dval;
			else
				value_node_1->value->bval = value_node_1->value->dval < value_node_2->value->lval;
		}
		else
		{
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->bval = value_node_1->value->lval < value_node_2->value->dval;
			else
				value_node_1->value->bval = value_node_1->value->lval < value_node_2->value->lval;
		}

		value_node_1->type = C_BOOLEAN;		
	}
	else if(operation == C_GREAT_THEN)
	{
		// handle string differently
		if(value_node_1->type == C_STRING)
		{
			if(value_node_2->type == C_STRING)
			{
				value_node_1->value->bval = strcmp(value_node_1->value->strval, value_node_2->value->strval) > 0;
				value_node_1->type = C_BOOLEAN;		
				free(value_node_2);
				return expression_node;
			}
			else
			{
				printf("\n[Error : %d] can not compare string with type : %s", line, getDataType(value_node_2->type));
				exit(1);
			}
		}
		else if(value_node_2->type == C_STRING)
		{
			printf("\n[Error : %d] can not compare string with type : %s", line, getDataType(value_node_1->type));
			exit(1);
		}

		switch(value_node_1->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_DOUBLE);value_node_1->type = C_DOUBLE; 	break;
		}

		switch(value_node_2->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_DOUBLE);value_node_2->type = C_DOUBLE; 	break;
		}

		if(value_node_1->type == C_DOUBLE)
		{
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->bval = value_node_1->value->dval > value_node_2->value->dval;
			else
				value_node_1->value->bval = value_node_1->value->dval > value_node_2->value->lval;
		}
		else
		{
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->bval = value_node_1->value->lval > value_node_2->value->dval;
			else
				value_node_1->value->bval = value_node_1->value->lval > value_node_2->value->lval;
		}

		value_node_1->type = C_BOOLEAN;		
	}
	else if(operation == C_LESS_EQUAL)
	{
		// handle string differently
		if(value_node_1->type == C_STRING)
		{
			if(value_node_2->type == C_STRING)
			{
				value_node_1->value->bval = strcmp(value_node_1->value->strval, value_node_2->value->strval) <= 0;
				value_node_1->type = C_BOOLEAN;		
				free(value_node_2);
				return expression_node;
			}
			else
			{
				printf("\n[Error : %d] can not compare string with type : %s", line, getDataType(value_node_2->type));
				exit(1);
			}
		}
		else if(value_node_2->type == C_STRING)
		{
			printf("\n[Error : %d] can not compare string with type : %s", line, getDataType(value_node_1->type));
			exit(1);
		}

		switch(value_node_1->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_DOUBLE);value_node_1->type = C_DOUBLE; 	break;
		}

		switch(value_node_2->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_DOUBLE);value_node_2->type = C_DOUBLE; 	break;
		}

		if(value_node_1->type == C_DOUBLE)
		{
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->bval = value_node_1->value->dval <= value_node_2->value->dval;
			else
				value_node_1->value->bval = value_node_1->value->dval <= value_node_2->value->lval;
		}
		else
		{
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->bval = value_node_1->value->lval <= value_node_2->value->dval;
			else
				value_node_1->value->bval = value_node_1->value->lval <= value_node_2->value->lval;
		}

		value_node_1->type = C_BOOLEAN;		
	}
	else if(operation == C_GREAT_EQUAL)
	{
		// handle string differently
		if(value_node_1->type == C_STRING)
		{
			if(value_node_2->type == C_STRING)
			{
				value_node_1->value->bval = strcmp(value_node_1->value->strval, value_node_2->value->strval) >= 0;
				value_node_1->type = C_BOOLEAN;		
				free(value_node_2);
				return expression_node;
			}
			else
			{
				printf("\n[Error : %d] can not compare string with type : %s", line, getDataType(value_node_2->type));
				exit(1);
			}
		}
		else if(value_node_2->type == C_STRING)
		{
			printf("\n[Error : %d] can not compare string with type : %s", line, getDataType(value_node_1->type));
			exit(1);
		}

		switch(value_node_1->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_DOUBLE);value_node_1->type = C_DOUBLE; 	break;
		}

		switch(value_node_2->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_DOUBLE);value_node_2->type = C_DOUBLE; 	break;
		}

		if(value_node_1->type == C_DOUBLE)
		{
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->bval = value_node_1->value->dval >= value_node_2->value->dval;
			else
				value_node_1->value->bval = value_node_1->value->dval >= value_node_2->value->lval;
		}
		else
		{
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->bval = value_node_1->value->lval >= value_node_2->value->dval;
			else
				value_node_1->value->bval = value_node_1->value->lval >= value_node_2->value->lval;
		}

		value_node_1->type = C_BOOLEAN;		
	}
	else if(operation == C_L_SHIFT)
	{
		// doesn't work with float/double/string
		if(value_node_1->type == C_FLOAT || value_node_1->type == C_DOUBLE || value_node_1->type == C_STRING) {
			printf("\n[Error : %d] bitwise left shift operation doesn't work with type : %s", line, getDataType(value_node_1->type));
			exit(1);
		}
		if(value_node_2->type == C_FLOAT || value_node_2->type == C_DOUBLE || value_node_2->type == C_STRING) {
			printf("\n[Error : %d] bitwise left shift operation doesn't work with type : %s", line, getDataType(value_node_2->type));
			exit(1);
		}

		if(value_node_1->type == C_LONG) {switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG;}
		if(value_node_2->type == C_LONG) {switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG;}

		value_node_1->value->lval = value_node_1->value->lval << value_node_2->value->lval;
	}
	else if(operation == C_R_SHIFT)
	{
		// doesn't work with float/double/string
		if(value_node_1->type == C_FLOAT || value_node_1->type == C_DOUBLE || value_node_1->type == C_STRING) {
			printf("\n[Error : %d] bitwise right shift operation doesn't work with type : %s", line, getDataType(value_node_1->type));
			exit(1);
		}
		if(value_node_2->type == C_FLOAT || value_node_2->type == C_DOUBLE || value_node_2->type == C_STRING) {
			printf("\n[Error : %d] bitwise right shift operation doesn't work with type : %s", line, getDataType(value_node_2->type));
			exit(1);
		}

		if(value_node_1->type != C_LONG) {switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG;}
		if(value_node_2->type != C_LONG) {switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG;}

		value_node_1->value->lval = value_node_1->value->lval >> value_node_2->value->lval;
	}
	else if(operation == C_PLUS)
	{
		// handle strings differently
		if(value_node_1->type == C_STRING)
		{
			if(value_node_2->type == C_STRING)
			{
				value_node_1->value->strval = strcat(value_node_1->value->strval, value_node_2->value->strval);
			}
			else
			{
				value_node_1->value->strval = strcat(value_node_1->value->strval, toString(value_node_2));
			}
		}
		else if(value_node_2->type == C_STRING)
		{
			value_node_1->value->strval = strcat(toString(value_node_1), value_node_2->value->strval);
			value_node_1->type = C_STRING;
		}
		else
		{
			switch(value_node_1->type) {
				case C_INT 		:
				case C_CHAR 	:
				case C_BOOLEAN 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG; 		break;
				case C_FLOAT 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_DOUBLE);value_node_1->type = C_DOUBLE; 	break;
			}

			switch(value_node_2->type) {
				case C_INT 		:
				case C_CHAR 	:
				case C_BOOLEAN 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG; 		break;
				case C_FLOAT 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_DOUBLE);value_node_2->type = C_DOUBLE; 	break;
			}

			if(value_node_1->type == C_DOUBLE)
			{
				value_node_1->type = C_DOUBLE;
				if(value_node_2->type == C_DOUBLE)
					value_node_1->value->dval = value_node_1->value->dval + value_node_2->value->dval;
				else
					value_node_1->value->dval = value_node_1->value->dval + value_node_2->value->lval;
			}
			else
			{
				if(value_node_2->type == C_DOUBLE)
				{
					value_node_1->type = C_DOUBLE;
					value_node_1->value->dval = value_node_1->value->lval + value_node_2->value->dval;
				}
				else
				{
					value_node_1->type = C_LONG;
					value_node_1->value->lval = value_node_1->value->lval + value_node_2->value->lval;
				}
			}
		}
	}
	else if(operation == C_MINUS)
	{
		// doesn't work with string
		if(value_node_1->type == C_STRING)
		{
			printf("\n[Error : %d] subtraction operation doesn't work with type : string", line);
			exit(1);
		}
		if(value_node_2->type == C_STRING)
		{
			printf("\n[Error : %d] subtraction operation doesn't work with type : string", line);
			exit(1);
		}

		switch(value_node_1->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_DOUBLE);value_node_1->type = C_DOUBLE; 	break;
		}

		switch(value_node_2->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_DOUBLE);value_node_2->type = C_DOUBLE; 	break;
		}
		if(value_node_1->type == C_DOUBLE)
		{
			value_node_1->type = C_DOUBLE;
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->dval = value_node_1->value->dval - value_node_2->value->dval;
			else
				value_node_1->value->dval = value_node_1->value->dval - value_node_2->value->lval;
		}
		else
		{
			if(value_node_2->type == C_DOUBLE)
			{
				value_node_1->type = C_DOUBLE;
				value_node_1->value->dval = value_node_1->value->lval - value_node_2->value->dval;
			}
			else
			{
				value_node_1->type = C_LONG;
				value_node_1->value->lval = value_node_1->value->lval - value_node_2->value->lval;
			}
		}
	}
	else if(operation == C_MULTIPLY)
	{
		// doesn't work with string
		if(value_node_1->type == C_STRING)
		{
			printf("\n[Error : %d] multiply operation doesn't work with type : string", line);
			exit(1);
		}
		if(value_node_2->type == C_STRING)
		{
			printf("\n[Error : %d] multiply operation doesn't work with type : string", line);
			exit(1);
		}

		switch(value_node_1->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_DOUBLE);value_node_1->type = C_DOUBLE; 	break;
		}

		switch(value_node_2->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_DOUBLE);value_node_2->type = C_DOUBLE; 	break;
		}

		if(value_node_1->type == C_DOUBLE)
		{
			value_node_1->type = C_DOUBLE;
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->dval = value_node_1->value->dval * value_node_2->value->dval;
			else
				value_node_1->value->dval = value_node_1->value->dval * value_node_2->value->lval;
		}
		else
		{
			if(value_node_2->type == C_DOUBLE)
			{
				value_node_1->type = C_DOUBLE;
				value_node_1->value->dval = value_node_1->value->lval * value_node_2->value->dval;
			}
			else
			{
				value_node_1->type = C_LONG;
				value_node_1->value->lval = value_node_1->value->lval * value_node_2->value->lval;
			}
		}
	}
	else if(operation == C_DIVIDE)
	{
		// doesn't work with string
		if(value_node_1->type == C_STRING)
		{
			printf("\n[Error : %d] division operation doesn't work with type : string", line);
			exit(1);
		}
		if(value_node_2->type == C_STRING)
		{
			printf("\n[Error : %d] division operation doesn't work with type : string", line);
			exit(1);
		}

		switch(value_node_1->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_DOUBLE);value_node_1->type = C_DOUBLE; 	break;
		}

		switch(value_node_2->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_DOUBLE);value_node_2->type = C_DOUBLE; 	break;
		}
		if(value_node_1->type == C_DOUBLE)
		{
			value_node_1->type = C_DOUBLE;
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->dval = value_node_1->value->dval / value_node_2->value->dval;
			else
				value_node_1->value->dval = value_node_1->value->dval / value_node_2->value->lval;
		}
		else
		{
			if(value_node_2->type == C_DOUBLE)
			{
				value_node_1->type = C_DOUBLE;
				value_node_1->value->dval = value_node_1->value->lval / value_node_2->value->dval;
			}
			else
			{
				value_node_1->type = C_LONG;
				value_node_1->value->lval = value_node_1->value->lval / value_node_2->value->lval;
			}
		}
	}
	else if(operation == C_MODULO)
	{
		// doesn't work with float/double/string
		if(value_node_1->type == C_FLOAT || value_node_1->type == C_DOUBLE || value_node_1->type == C_STRING) {
			printf("\n[Error : %d] modulo operation doesn't work with type : %s", line, getDataType(value_node_1->type));
			exit(1);
		}
		if(value_node_2->type == C_FLOAT || value_node_2->type == C_DOUBLE || value_node_2->type == C_STRING) {
			printf("\n[Error : %d] modulo operation doesn't work with type : %s", line, getDataType(value_node_2->type));
			exit(1);
		}

		if(value_node_1->type != C_LONG) {switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG;}
		if(value_node_2->type != C_LONG) {switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG;}

		value_node_1->value->lval = value_node_1->value->lval % value_node_2->value->lval;
	}
	else if(operation == C_EXP)
	{
		// doesn't work with string
		if(value_node_1->type == C_STRING)
		{
			printf("\n[Error : %d] exponentiation operation doesn't work with type : string", line);
			exit(1);
		}
		if(value_node_2->type == C_STRING)
		{
			printf("\n[Error : %d] exponentiation operation doesn't work with type : string", line);
			exit(1);
		}

		switch(value_node_1->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_1->value, value_node_1->type, C_DOUBLE);value_node_1->type = C_DOUBLE; 	break;
		}

		switch(value_node_2->type) {
			case C_INT 		:
			case C_CHAR 	:
			case C_BOOLEAN 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_LONG);value_node_2->type = C_LONG; 		break;
			case C_FLOAT 	:	switchUnionValue(value_node_2->value, value_node_2->type, C_DOUBLE);value_node_2->type = C_DOUBLE; 	break;
		}
		if(value_node_1->type == C_DOUBLE)
		{
			value_node_1->type = C_DOUBLE;
			if(value_node_2->type == C_DOUBLE)
				value_node_1->value->dval = pow(value_node_1->value->dval, value_node_2->value->dval);
			else
				value_node_1->value->dval = pow(value_node_1->value->dval, value_node_2->value->lval);
		}
		else
		{
			if(value_node_2->type == C_DOUBLE)
			{
				value_node_1->type = C_DOUBLE;
				value_node_1->value->dval = pow(value_node_1->value->lval, value_node_2->value->dval);
			}
			else
			{
				value_node_1->type = C_LONG;
				value_node_1->value->lval = (long)pow(value_node_1->value->lval, value_node_2->value->lval);
			}
		}
	}
}

void executeUnaryExpression(struct expressionNode *expression_node)
{
	struct valueNode* value_node_1;
	int operation = expression_node->expression->unary_expression->operation;

	struct expressionNode *expression_node_1 = expression_node->expression->unary_expression->expression_node_1;
	executeExpressionNode(expression_node_1);

	if(operation == C_FACT)
	{
		value_node_1 = expression_node_1->value_node;
		value_node_1 = makeValueNode(value_node_1->type, value_node_1->value);
		expression_node->value_node = value_node_1;

		// doesn't work with float/double/string
		if(value_node_1->type == C_FLOAT || value_node_1->type == C_DOUBLE || value_node_1->type == C_STRING) {
			printf("\n[Error : %d] factorial operation doesn't work with type : %s", line, getDataType(value_node_1->type));
			exit(1);
		}

		if(value_node_1->type != C_LONG) {switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG;}

		long ans = 1;
		long n = value_node_1->value->lval;

		while(n > 1) ans *= n--;		
		value_node_1->value->lval = ans;
	}
	else if(operation == C_PRE_INC)
	{
		char* name = expression_node_1->expression->variable;
		struct variable* var = getVariable(name);
		
		// doesn't work with string
		if(var->type == C_STRING)
		{
			printf("\n[Error : %d] pre increment operation doesn't work with type : string", line);
			exit(1);
		}

		if(var->type == C_INT) var->value->ival = var->value->ival + 1;		
		else if(var->type == C_LONG) var->value->lval = var->value->lval + 1;		
		else if(var->type == C_FLOAT) var->value->fval = var->value->fval + 1;		
		else if(var->type == C_DOUBLE) var->value->dval = var->value->dval + 1;		
		else if(var->type == C_CHAR) var->value->cval = var->value->cval + 1;		
		// else if(var->type == C_STRING) var->value->strval = var->value->strval + 1;		
		else if(var->type == C_BOOLEAN) var->value->bval = var->value->bval + 1;

		expression_node_1 = makeExpressionNode(name, NULL);
		expression_node->value_node = makeValueNode(var->type, var->value);
	}
	else if(operation == C_PRE_DEC)
	{
		char* name = expression_node_1->expression->variable;
		struct variable* var = getVariable(name);

		// doesn't work with string
		if(var->type == C_STRING)
		{
			printf("\n[Error : %d] pre decrement operation doesn't work with type : string", line);
			exit(1);
		}

		if(var->type == C_INT) var->value->ival = var->value->ival - 1;		
		else if(var->type == C_LONG) var->value->lval = var->value->lval - 1;		
		else if(var->type == C_FLOAT) var->value->fval = var->value->fval - 1;		
		else if(var->type == C_DOUBLE) var->value->dval = var->value->dval - 1;		
		else if(var->type == C_CHAR) var->value->cval = var->value->cval - 1;		
		// else if(var->type == C_STRING) var->value->strval = var->value->strval - 1;		
		else if(var->type == C_BOOLEAN) var->value->bval = var->value->bval - 1;

		expression_node_1 = makeExpressionNode(name, NULL);
		expression_node->value_node = makeValueNode(var->type, var->value);
	}
	else if(operation == C_PLUS)
	{
		value_node_1 = expression_node_1->value_node;
		value_node_1 = makeValueNode(value_node_1->type, value_node_1->value);
		expression_node->value_node = value_node_1;

		// doesn't work with string
		if(value_node_1->type == C_STRING)
		{
			printf("\n[Error : %d] string can't have positive/negative sign", line);
			exit(1);
		}
	}
	else if(operation == C_MINUS)
	{
		value_node_1 = expression_node_1->value_node;
		value_node_1 = makeValueNode(value_node_1->type, value_node_1->value);
		expression_node->value_node = value_node_1;
		
		// doesn't work with string
		if(value_node_1->type == C_STRING)
		{
			printf("\n[Error : %d] string can't have positive/negative sign", line);
			exit(1);
		}

		if(value_node_1->type != C_DOUBLE) {switchUnionValue(value_node_1->value, value_node_1->type, C_DOUBLE);value_node_1->type = C_DOUBLE;}		

		value_node_1->value->dval =  -value_node_1->value->dval;
	}
	else if(operation == C_NOT)
	{
		value_node_1 = expression_node_1->value_node;
		value_node_1 = makeValueNode(value_node_1->type, value_node_1->value);
		expression_node->value_node = value_node_1;
		
		// doesn't work with string
		if(value_node_1->type == C_STRING)
		{
			printf("\n[Error : %d] logical not operation doesn't work with type : string", line);
			exit(1);
		}

		if(value_node_1->type != C_BOOLEAN) {switchUnionValue(value_node_1->value, value_node_1->type, C_BOOLEAN);value_node_1->type = C_BOOLEAN;}		

		value_node_1->value->bval = ! value_node_1->value->bval;
	}
	else if(operation == C_BIT_NOT)
	{
		value_node_1 = expression_node_1->value_node;
		value_node_1 = makeValueNode(value_node_1->type, value_node_1->value);
		expression_node->value_node = value_node_1;
		
		// doesn't work with float/double/string
		if(value_node_1->type == C_FLOAT || value_node_1->type == C_DOUBLE || value_node_1->type == C_STRING) {
			printf("\n[Error : %d] bitwise not operation doesn't work with type : %s", line, getDataType(value_node_1->type));
			exit(1);
		}

		if(value_node_1->type != C_LONG) {switchUnionValue(value_node_1->value, value_node_1->type, C_LONG);value_node_1->type = C_LONG;}
		
		value_node_1->value->lval = ~ value_node_1->value->lval;
	}
	else if(operation == C_POST_INC)
	{

		char* name = expression_node_1->expression->variable;
		struct variable* var = getVariable(name);

		// doesn't work with string
		if(var->type == C_STRING)
		{
			printf("\n[Error : %d] post increment operation doesn't work with type : string", line);
			exit(1);
		}

		expression_node_1 = makeExpressionNode(name, NULL);
		expression_node->value_node = makeValueNode(var->type, var->value);

		if(var->type == C_INT) var->value->ival = var->value->ival + 1;		
		else if(var->type == C_LONG) var->value->lval = var->value->lval + 1;		
		else if(var->type == C_FLOAT) var->value->fval = var->value->fval + 1;		
		else if(var->type == C_DOUBLE) var->value->dval = var->value->dval + 1;		
		else if(var->type == C_CHAR) var->value->cval = var->value->cval + 1;		
		// else if(var->type == C_STRING) var->value->strval = var->value->strval + 1;		
		else if(var->type == C_BOOLEAN) var->value->bval = var->value->bval + 1;
	}
	else if(operation == C_POST_DEC)
	{
		char* name = expression_node_1->expression->variable;
		struct variable* var = getVariable(name);

		// doesn't work with string
		if(var->type == C_STRING)
		{
			printf("\n[Error : %d] post decrement operation doesn't work with type : string", line);
			exit(1);
		}

		expression_node_1 = makeExpressionNode(name, NULL);
		expression_node->value_node = makeValueNode(var->type, var->value);

		if(var->type == C_INT) var->value->ival = var->value->ival - 1;		
		else if(var->type == C_LONG) var->value->lval = var->value->lval - 1;		
		else if(var->type == C_FLOAT) var->value->fval = var->value->fval - 1;		
		else if(var->type == C_DOUBLE) var->value->dval = var->value->dval - 1;		
		else if(var->type == C_CHAR) var->value->cval = var->value->cval - 1;		
		// else if(var->type == C_STRING) var->value->strval = var->value->strval - 1;		
		else if(var->type == C_BOOLEAN) var->value->bval = var->value->bval - 1;
	}
}

void executeConstructNode(struct constructNode *construct_node)
{
	if(construct_node->construct_type == C_IF_CONSTRUCT) executeIfConstruct(construct_node->construct->if_construct);
	else if(construct_node->construct_type == C_FOR_CONSTRUCT) executeForConstruct(construct_node->construct->for_construct);
	else if(construct_node->construct_type == C_WHILE_CONSTRUCT) executeWhileConstruct(construct_node->construct->while_construct);
}

void executeIfConstruct(struct ifConstruct *if_construct)
{
	if(!executeIfBlock(if_construct->if_block))
	{
		int executedElifBlock = 0;
		struct elifBlock* elif_block = if_construct->optional_blocks->elif_block;

		while(1)
		{

			if(elif_block == NULL) break;

			if(executeElifBlock(elif_block))
			{
				executedElifBlock = 1;
				break;
			}

			elif_block = elif_block->next; 
		}

		if(!executedElifBlock && if_construct->optional_blocks->else_block != NULL) executeElseBlock(if_construct->optional_blocks->else_block);
	}
}

int executeIfBlock(struct ifBlock* if_block)
{
	executeExpressionNode(if_block->condition);

	if(!if_block->condition->value_node->value->bval) return 0;

	scope++;

	executeStatementSetNode(if_block->body);
	removeVariables(scope);
	scope--;

	return 1;
}

int executeElifBlock(struct elifBlock* elif_block)
{
	executeExpressionNode(elif_block->condition);

	if(!elif_block->condition->value_node->value->bval) return 0;

	scope++;
	executeStatementSetNode(elif_block->body);
	removeVariables(scope);
	scope--;

	return 1;
}

void executeElseBlock(struct elseBlock* else_block)
{
	scope++;
	executeStatementSetNode(else_block->body);
	removeVariables(scope);
	scope--;
}

void executeForConstruct(struct forConstruct *for_construct)
{
	scope++;
	int tmp = for_first_scope;
	for_first_scope = scope;

	if(for_construct->first_statement != NULL) executeStatementNode(for_construct->first_statement);

	while(1)
	{
		executeExpressionNode(for_construct->middle_expression);
		if(for_construct->middle_expression->value_node->type != C_BOOLEAN) switchUnionValue(for_construct->middle_expression->value_node->value, for_construct->middle_expression->value_node->type, C_BOOLEAN);

		if(for_construct->middle_expression->value_node->value->bval)
		{
			scope++;
			int tmp_break = break_flag;
			int tmp_continue = continue_flag;

			break_flag = -1;
			continue_flag = -1;

			executeStatementSetNode(for_construct->body);
			removeVariables(scope);
			scope--;

			if(break_flag == 1)
			{
				break_flag = tmp_break;
				break;
			}

			break_flag = tmp_break;
			continue_flag = tmp_continue;
		}
		else break;		

		if(for_construct->last_statement != NULL) executeStatementNode(for_construct->last_statement);
	}
	removeVariables(scope);
	scope--;

	for_first_scope = tmp;
}

void executeWhileConstruct(struct whileConstruct *while_construct)
{
	while(1)
	{
		executeExpressionNode(while_construct->condition);
		if(while_construct->condition->value_node->type != C_BOOLEAN) switchUnionValue(while_construct->condition->value_node->value, while_construct->condition->value_node->type, C_BOOLEAN);

		if(while_construct->condition->value_node->value->bval)
		{
			scope++;
			int tmp_break = break_flag;
			int tmp_continue = continue_flag;

			break_flag = -1;
			continue_flag = -1;

			executeStatementSetNode(while_construct->body);
			removeVariables(scope);
			scope--;

			if(break_flag == 1)
			{
				break_flag = tmp_break;
				break;
			}

			break_flag = tmp_break;
			continue_flag = tmp_continue;
		}
		else break;
	}
}