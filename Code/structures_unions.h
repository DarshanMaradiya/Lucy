//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																														//
// ----------------------------------------------- Unions and structures ---------------------------------------------- //
//																														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// define boolean that uses only 1 byte to store the value
typedef char boolean;
// define string that points to start of the string
typedef char* string;

// Declarations of unions and structures
typedef union varvalue { 
	int ival;
	long lval;
	float fval;
	double dval;
	char cval;
	string strval;
	boolean bval;
}varvalue;

typedef struct variable{
		char* name;
		int type;
		int scope;
		int line;
		union varvalue *value;
		struct variable *next;
}variable;

typedef struct valueNode{
	int type;
	union varvalue *value;
}valueNode;

typedef struct symbolNode{
	char* name;
	int type;
	union varvalue *value;
	struct expressionNode *expression_node;
}symbolNode;

typedef struct listNode{
	struct symbolNode *symbol;
	struct listNode *next;
}listNode;

typedef struct declarationNode{
	int type;
	struct listNode *next;
	int line;
}declarationNode;

typedef struct assignmentNode{
	char* operation;
	char* name;
	struct expressionNode* expression_node;
	int line;
}assignmentNode;

typedef struct ternaryExpression{
	struct expressionNode *expression_node_1;
	struct expressionNode *expression_node_2;
	struct expressionNode *expression_node_3;
}ternaryExpression;

typedef struct binaryExpression{
	char* operation;
	struct expressionNode *expression_node_1;
	struct expressionNode *expression_node_2;
}binaryExpression;

typedef struct unaryExpression{
	char* operation;
	struct expressionNode *expression_node_1;
}unaryExpression;

typedef union expression{
	struct valueNode *value_node;
	char* variable;
	struct ternaryExpression *ternary_expression;
	struct binaryExpression *binary_expression;
	struct unaryExpression *unary_expression;
	struct assignmentNode *assignment_node;
}expression;

typedef struct expressionNode{
	int expression_type;
	union expression* expression;
	struct valueNode *value_node;
	int line;
}expressionNode;

typedef struct swapOperationNode{
	char* variable_1;
	char* variable_2;
	int line;
}swapOperationNode;

typedef union statement{
	struct declarationNode *declaration_node;
	struct assignmentNode *assignment_node;
	struct swapOperationNode *swap_operation_node;
	struct expressionNode *expression_node;
	int break_node;
	int continue_node;
}statement;

typedef struct statementNode{
	int statement_type;
	union statement *statement;
}statementNode;

typedef union construct{
	struct ifConstruct *if_construct;
	struct forConstruct *for_construct;
	struct whileConstruct *while_construct;
}construct;

typedef struct constructNode{
	int construct_type;
	union construct *construct;
}constructNode;

typedef struct statementSetNode{
	int statement_set_type;
	struct statementNode *statement_node;
	struct constructNode *construct_node;
	struct statementSetNode *next;
}statementSetNode;

typedef struct ifBlock{
	struct expressionNode *condition;
	struct statementSetNode *body;
}ifBlock;

typedef struct elifBlock{
	struct expressionNode *condition;
	struct statementSetNode *body;
	struct elifBlock *next;
}elifBlock;

typedef struct elseBlock{
	struct statementSetNode *body; 
}elseBlock;

typedef struct optionalBlocks{
	struct elifBlock *elif_block;
	struct elseBlock *else_block;
}optionalBlocks;

typedef struct ifConstruct{
	struct ifBlock *if_block;
	struct optionalBlocks *optional_blocks;
}ifConstruct;

typedef struct forConstruct{
	struct statementNode *first_statement;
	struct expressionNode *middle_expression;
	struct statementNode *last_statement;
	struct statementSetNode *body;
}forConstruct;

typedef struct whileConstruct{
	struct expressionNode *condition;
	struct statementSetNode *body;
}whileConstruct;