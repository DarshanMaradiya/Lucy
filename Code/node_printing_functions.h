//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																														//
// --------------------------------------------- Node Printing Functions ---------------------------------------------- //
//																														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printDeclarationNode(struct declarationNode* declaration_node)
{
	indent++;

	printIndentation(indent);
	printf("Declaration Node of type %s : ", getDataType(declaration_node->type));

	struct listNode* curr = declaration_node->next;

	for(;curr != NULL; curr = curr->next)
	{
		printIndentation(indent);
		printf("variable : %s",curr->symbol->name);

		printIndentation(indent);
		printf("Expression :");
		if(curr->symbol->expression_node != NULL) printExpressionNode(curr->symbol->expression_node);
	}

	printIndentation(indent);
	indent--;
}

void printValueNode(struct valueNode* value_node)
{
	switch(value_node->type) {
			case C_INT 		:	printf(" (int : %d) ",value_node->value->ival);								break;
			case C_LONG 	:	printf(" (long : %ld) ",value_node->value->lval);							break;
			case C_FLOAT 	:	printf(" (float : %f) ",value_node->value->fval);							break;
			case C_DOUBLE 	:	printf(" (double : %ld) ",value_node->value->dval);							break;
			case C_CHAR 	:	printf(" (char : '%c') ",value_node->value->cval);							break;
			case C_STRING 	:	printf(" (string : \"%s\") ",value_node->value->strval);						break;
			case C_BOOLEAN 	:	printf(" (boolean : %s) ",(value_node->value->bval == 0)?"false":"true");	break;
		}
}

void printVariable(char* var_name)
{
	indent++;
	
	printIndentation(indent);
	printf("Variable : %s", var_name);

	printIndentation(indent);
	indent--;
}

void printAssignmentNode(struct assignmentNode* assignment_node)
{
	indent++;

	printIndentation(indent);
	printf("Assignment Node :");

	printIndentation(indent);
	printf("variable : %s", assignment_node->name);

	printIndentation(indent);
	printf("operation : %s", getOperationName(assignment_node->operation));

	printIndentation(indent);
	printf("Expression : ");

	printExpressionNode(assignment_node->expression_node);

	printIndentation(indent);
	indent--;
}

void printTernaryExpression(struct ternaryExpression* ternary_expression)
{
	indent++;

	printIndentation(indent);
	printf("Ternay Expression :");

	printIndentation(indent);
	printf("Operand-1 : ");printExpressionNode(ternary_expression->expression_node_1);

	printIndentation(indent);
	printf("Operand-2 : ");printExpressionNode(ternary_expression->expression_node_2);

	printIndentation(indent);
	printf("Operand-3 : ");printExpressionNode(ternary_expression->expression_node_2);

	printIndentation(indent);
	indent--;
}

void printBinaryExpression(struct binaryExpression* binary_expression)
{
	indent++;

	printIndentation(indent);
	printf("Binary Expression :");

	printIndentation(indent);
	printf("Operation : %s", getOperationName(binary_expression->operation));

	printIndentation(indent);
	printf("Operand-1 : ");printExpressionNode(binary_expression->expression_node_1);

	printIndentation(indent);
	printf("Operand-2 : ");printExpressionNode(binary_expression->expression_node_2);

	printIndentation(indent);
	indent--;
}

void printUnaryExpression(struct unaryExpression* unary_expression)
{
	indent++;

	printIndentation(indent);
	printf("Unary Expression :");

	printIndentation(indent);
	printf("Operation : %s", getOperationName(unary_expression->operation));

	printIndentation(indent);
	printf("Operand-1 : ");printExpressionNode(unary_expression->expression_node_1);

	printIndentation(indent);
	indent--;
}

void printExpressionNode(struct expressionNode* expression_node)
{
	if(expression_node->expression_type == C_VALUE_NODE) printValueNode(expression_node->expression->value_node);
	else if(expression_node->expression_type == C_VARIABLE) printVariable(expression_node->expression->variable);
	else if(expression_node->expression_type == C_TERNARY_EXPRESSION) printTernaryExpression(expression_node->expression->ternary_expression);
	else if(expression_node->expression_type == C_BINARY_EXPRESSION) printBinaryExpression(expression_node->expression->binary_expression);
	else if(expression_node->expression_type == C_UNARY_EXPRESSION) printUnaryExpression(expression_node->expression->unary_expression);
	else if(expression_node->expression_type == C_ASSIGNMENT_NODE) printAssignmentNode(expression_node->expression->assignment_node);
}

void printSwapOperationNode(struct swapOperationNode* swap_operation_node)
{
	indent++;

	printIndentation(indent);
	printf("SwapOperation Node :");

	printIndentation(indent);
	printf("Variable-1 :");printVariable(swap_operation_node->variable_1);

	printIndentation(indent);
	printf("Variable-2 :");printVariable(swap_operation_node->variable_2);

	printIndentation(indent);
	indent--;
}

void printPrintNode(struct expressionNode* expression_node) {
	indent++;
	printIndentation(indent);
	printf("Print Statement : ");

	printExpressionNode(expression_node);
	
	printIndentation(indent);
	indent--;
}

void printBreakNode() {
	indent++;
	printIndentation(indent);
	printf("Break Statement : ");

	printIndentation(indent);
	indent--;
}

void printContinueNode() {
	indent++;
	printIndentation(indent);
	printf("Continue Statement : ");

	printIndentation(indent);
	indent--;
}

void printStatementNode(struct statementNode* statement_node)
{
	if(statement_node->statement_type == C_DECLARATION_NODE) printDeclarationNode(statement_node->statement->declaration_node);
	else if(statement_node->statement_type == C_ASSIGNMENT_NODE) printAssignmentNode(statement_node->statement->assignment_node);
	else if(statement_node->statement_type == C_SWAP_OPERATION_NODE) printSwapOperationNode(statement_node->statement->swap_operation_node);
	else if(statement_node->statement_type == C_EXPRESSION_NODE) printExpressionNode(statement_node->statement->expression_node);
	else if(statement_node->statement_type == C_PRINT_NODE) printPrintNode(statement_node->statement->expression_node);
	else if(statement_node->statement_type == C_BREAK_NODE) printBreakNode();
	else if(statement_node->statement_type == C_CONTINUE_NODE) printContinueNode();
}

void printConstructNode(struct constructNode* construct_node)
{
	if(construct_node->construct_type == C_IF_CONSTRUCT) printIfConstruct(construct_node->construct->if_construct);
	else if(construct_node->construct_type == C_FOR_CONSTRUCT) printForConstruct(construct_node->construct->for_construct);
	else if(construct_node->construct_type == C_WHILE_CONSTRUCT) printWhileConstruct(construct_node->construct->while_construct);
}

void printStatementSetNode(struct statementSetNode* statement_set_node)
{
	struct statementSetNode* curr = statement_set_node;

	while(curr != NULL) 
	{
		if(curr->statement_set_type == C_STATEMENT_NODE) printStatementNode(curr->statement_node);
		else //if(curr->statement_set_type == C_CONSTRUCT_NODE)
			printConstructNode(curr->construct_node);
		curr = curr->next;
	}
}

void printIfConstruct(struct ifConstruct* if_construct)
{
	indent++;

	printIndentation(indent);
	printf("If Construct :");

	printIndentation(indent);
	printf("If Block :");

	printIndentation(indent);
	printf("Conditional Expression : ");

	printExpressionNode(if_construct->if_block->condition);

	printIndentation(indent);
	printf("Body :");

	printStatementSetNode(if_construct->if_block->body);

	struct elifBlock *curr = if_construct->optional_blocks->elif_block;

	while(curr != NULL)
	{
		printIndentation(indent);
		printf("Elif Block :");

		printIndentation(indent);
		printf("Conditional Expression : ");
		printExpressionNode(curr->condition);

		printIndentation(indent);
		printf("Body :");

		printStatementSetNode(curr->body);
		curr = curr->next;
	}

	if(if_construct->optional_blocks->else_block != NULL)
	{
		printIndentation(indent);
		printf("Else Block :");

		printIndentation(indent);
		printf("Body :");

		printStatementSetNode(if_construct->optional_blocks->else_block->body);
	}

	printIndentation(indent);
	indent--;
}

void printForConstruct(struct forConstruct* for_construct)
{
	indent++;

	printIndentation(indent);
	printf("For Construct : ");

	printIndentation(indent);
	printf("First Statement : ");

	if(for_construct->first_statement != NULL) printStatementNode(for_construct->first_statement);

	printIndentation(indent);
	printf("Middle Expression : ");

	if(for_construct->middle_expression != NULL) printExpressionNode(for_construct->middle_expression);

	printIndentation(indent);
	printf("Last Statement : ");

	if(for_construct->last_statement != NULL) printStatementNode(for_construct->last_statement);
	
	printIndentation(indent);
	printf("Body : ");

	printStatementSetNode(for_construct->body);

	printIndentation(indent);
	indent--;
}

void printWhileConstruct(struct whileConstruct* while_construct)
{
	indent++;

	printIndentation(indent);
	printf("While Construct : ");

	printIndentation(indent);
	printf("Condition : ");

	printExpressionNode(while_construct->condition);
	
	printIndentation(indent);
	printf("Body : ");

	printStatementSetNode(while_construct->body);

	printIndentation(indent);
	indent--;
}