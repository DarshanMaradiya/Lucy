//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																														//
// --------------------------------------------- Node Creating Functions ---------------------------------------------- //
//																														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct expressionNode* makeExpressionNode(char* name, struct valueNode* value_node)
{
	struct expressionNode* expression_node = (expressionNode*)malloc(sizeof(expressionNode));
	expression_node->line = line;

	expression_node->expression = (expression* )malloc(sizeof(expression));

	if(name != NULL)
	{
		expression_node->expression_type = C_VARIABLE;
		expression_node->expression->variable = name;
		expression_node->value_node = NULL;
	}

	if(value_node != NULL)
	{
		expression_node->expression_type = C_VALUE_NODE;
		expression_node->expression->value_node = value_node;
		expression_node->value_node = NULL;
	}

	return expression_node;
}

struct expressionNode* unaryOperation(struct expressionNode* expression_node_1, char* operation)
{
	struct expressionNode* expression_node = (expressionNode*)malloc(sizeof(expressionNode));
	expression_node->line = line;
	
	expression_node->expression_type = C_UNARY_EXPRESSION;

	expression_node->expression = (expression* )malloc(sizeof(expression));
	expression_node->expression->unary_expression = (unaryExpression* )malloc(sizeof(unaryExpression));
	expression_node->expression->unary_expression->operation = operation;
	expression_node->expression->unary_expression->expression_node_1 = expression_node_1;

	expression_node->value_node = NULL;

	return expression_node;
}

struct expressionNode* binaryOperation(struct expressionNode* expression_node_1, struct expressionNode* expression_node_2, char* operation)
{
	struct expressionNode* expression_node = (expressionNode*)malloc(sizeof(expressionNode));
	expression_node->line = line;

	expression_node->expression_type = C_BINARY_EXPRESSION;

	expression_node->expression = (expression* )malloc(sizeof(expression));
	expression_node->expression->binary_expression = (binaryExpression* )malloc(sizeof(binaryExpression));
	expression_node->expression->binary_expression->expression_node_1 = expression_node_1;
	expression_node->expression->binary_expression->expression_node_2 = expression_node_2;
	expression_node->expression->binary_expression->operation = operation;

	expression_node->value_node = NULL;

	return expression_node;
}

struct expressionNode* ternaryOperation(struct expressionNode* expression_node_1, struct expressionNode* expression_node_2, struct expressionNode* expression_node_3)
{
	struct expressionNode* expression_node = (expressionNode*)malloc(sizeof(expressionNode));
	expression_node->line = line;
	
	expression_node->expression_type = C_TERNARY_EXPRESSION;

	expression_node->expression = (expression* )malloc(sizeof(expression));
	expression_node->expression->ternary_expression = (ternaryExpression* )malloc(sizeof(ternaryExpression));
	expression_node->expression->ternary_expression->expression_node_1 = expression_node_1;
	expression_node->expression->ternary_expression->expression_node_2 = expression_node_2;
	expression_node->expression->ternary_expression->expression_node_3 = expression_node_3;
	
	expression_node->value_node = NULL;

	return expression_node;
}

struct symbolNode* makeSymbolNode(char* name, struct expressionNode *expression_node_1)
{
	struct symbolNode *symbol_node = (symbolNode *)malloc(sizeof(symbolNode));
	
	symbol_node->name = name;

	symbol_node->expression_node = expression_node_1;
	
	symbol_node->type = NULL;
	
	symbol_node->value = NULL;

	return symbol_node;
}

struct listNode* makeListNode(symbolNode *symbol, listNode *list)
{
	struct listNode *list_node = (listNode *)malloc(sizeof(listNode));
	
	list_node->symbol = symbol;
	
	list_node->next = list;
	
	return list_node;
}

struct expressionNode* makeExpressionNodeFromAssignment(struct assignmentNode* assignment_node)
{
	struct expressionNode* expression_node = (expressionNode*)malloc(sizeof(expressionNode));
	expression_node->line = line;
	
	expression_node->expression_type = C_ASSIGNMENT_NODE;

	expression_node->expression = (expression* )malloc(sizeof(expression));
	expression_node->expression->assignment_node = assignment_node;
	
	expression_node->value_node = NULL;

	return expression_node;
}

struct declarationNode* makeDeclarationNode(int type, listNode* list)
{
	struct declarationNode* declaration_node = (declarationNode* )malloc(sizeof(declarationNode));
	
	declaration_node->type = type;
	
	declaration_node->next = list;

	declaration_node->line = line;

	return declaration_node;
}

struct assignmentNode* makeAssignmentNode(char* name, struct expressionNode* expression_node_1, char* operation)
{
	struct assignmentNode* assignment_node = (assignmentNode* )malloc(sizeof(assignmentNode));
	
	assignment_node->operation = operation;

	assignment_node->name = name;

	assignment_node->expression_node = expression_node_1;

	assignment_node->line = line;

	return assignment_node;
}

struct swapOperatonNode* makeSwapOperationNode(char* name1, char* name2)
{
	struct swapOperationNode *swap_operation_node = (swapOperationNode* )malloc(sizeof(swapOperationNode));
	
	swap_operation_node->variable_1 = name1;
	
	swap_operation_node->variable_2 = name2;

	swap_operation_node->line = line;
	
	return swap_operation_node;
}

struct statementNode* makeStatementNode(void* Statement, int statement_type)
{
	struct statementNode *statement_node = (statementNode* )malloc(sizeof(statementNode));
	
	statement_node->statement_type = statement_type;
	
	statement_node->statement = (statement* )malloc(sizeof(statement));
	if(statement_type == C_DECLARATION_NODE) 			statement_node->statement->declaration_node = (declarationNode* )Statement;
	else if(statement_type == C_ASSIGNMENT_NODE) 		statement_node->statement->assignment_node = (assignmentNode* )Statement;
	else if(statement_type == C_SWAP_OPERATION_NODE) 	statement_node->statement->swap_operation_node = (swapOperationNode* )Statement;
	else if(statement_type == C_EXPRESSION_NODE) 		statement_node->statement->expression_node = (expressionNode* )Statement;
	else if(statement_type == C_PRINT_NODE) 			statement_node->statement->expression_node = (expressionNode* )Statement;
	else if(statement_type == C_BREAK_NODE) 			statement_node->statement->break_node = line;
	else if(statement_type == C_CONTINUE_NODE) 		statement_node->statement->continue_node = line;
	
	return statement_node;
}

struct constructNode* makeConstructNode(void* Construct, int construct_type)
{
	struct constructNode *construct_node = (constructNode* )malloc(sizeof(constructNode));
	
	construct_node->construct_type = construct_type;
	
	construct_node->construct = (construct* )malloc(sizeof(construct));
	if(construct_type == C_IF_CONSTRUCT) 			construct_node->construct->if_construct = (ifConstruct* )Construct;
	else if(construct_type == C_FOR_CONSTRUCT) 	construct_node->construct->for_construct = (forConstruct* )Construct;
	else if(construct_type == C_WHILE_CONSTRUCT) 	construct_node->construct->while_construct = (whileConstruct* )Construct;
	
	return construct_node;
}

struct statementSetNode* makeStatementSetNode(struct statementSetNode* statement_set_node, void* statement_node, int statement_set_type)
{
	if(statement_node == NULL) return statement_set_node;

	struct statementSetNode* new_statement_set_node = (statementSetNode* )malloc(sizeof(statementSetNode));
	
	new_statement_set_node->statement_set_type = statement_set_type;
	
	new_statement_set_node->next = NULL;

	if(statement_set_type == C_STATEMENT_NODE) 
	{
		new_statement_set_node->statement_node = (statementNode *)statement_node;
	}
	else // if(statement_set_type == C_CONSTRUCT_NODE)
	{
		new_statement_set_node->construct_node = (constructNode *)statement_node;
	}

	if(statement_set_node == NULL) return new_statement_set_node;

	// Following line is adding node at front (for time efficiency), hence wherever, in other grammars where STATEMENT grammar is used, the list has to be reversed first
	// The above comment is only valid if nodes are not being added recursively by grammar
	new_statement_set_node->next = statement_set_node; 			
	
	return new_statement_set_node;
}

struct ifBlock* makeIfBlock(struct expressionNode *condition, struct statementSetNode *body)
{
	struct ifBlock* if_block = (ifBlock* )malloc(sizeof(ifBlock));
	
	if_block->condition = condition;
	
	if_block->body = body;
	
	return if_block;
}

struct elifBlock* makeElifBlock(struct expressionNode *condition, struct statementSetNode *body, struct elifBlock* elif_blocks)
{
	struct elifBlock* elif_block = (elifBlock* )malloc(sizeof(elifBlock));
	
	elif_block->condition = condition;
	
	elif_block->body = body;
	
	elif_block->next = elif_blocks;
	
	return elif_block;
}

struct elseBlock* makeElseBlock(struct statementSetNode *body)
{
	struct elseBlock* else_block = (elseBlock* )malloc(sizeof(elseBlock));
	
	else_block->body = body;
	
	return else_block;
}

struct optionalBlocks* makeOptionalBlocks(struct elifBlock* elif_block, struct elseBlock* else_block)
{
	struct optionalBlocks *optional_blocks = (optionalBlocks* )malloc(sizeof(optionalBlocks));
	
	optional_blocks->elif_block = elif_block;
	
	optional_blocks->else_block = else_block;
	
	return optional_blocks;
}

struct ifConstruct* makeIfConstruct(struct ifBlock* if_block, struct optionalBlocks* optional_blocks)
{
	struct ifConstruct* if_construct = (ifConstruct* )malloc(sizeof(ifConstruct));
	
	if_construct->if_block = if_block;
	
	if_construct->optional_blocks = optional_blocks;
	
	return if_construct;
}

struct forConstruct* makeForConstruct(struct statementNode *first_statement, struct expressionNode *middle_expression, struct statementNode *last_statement, struct statementSetNode *body)
{
	struct forConstruct* for_construct = (forConstruct* )malloc(sizeof(forConstruct));
	
	for_construct->first_statement = first_statement;
	
	for_construct->middle_expression = middle_expression;
	
	for_construct->last_statement = last_statement;
	
	for_construct->body = body;

	return for_construct;
}

struct whileConstruct* makeWhileConstruct(struct expressionNode *condition,	struct statementSetNode *body)
{
	struct whileConstruct* while_construct = (whileConstruct* )malloc(sizeof(whileConstruct));
	
	while_construct->condition = condition;
	
	while_construct->body = body;
	
	return while_construct;
}