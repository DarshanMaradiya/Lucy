// ----------------------------------------------- Node Helper Functions ---------------------------------------------- //

char* toString(struct valueNode* value_node);
char* getOperationName(int operation);
char* getDataType(int dataType);
struct variable* getVariable(char* name);
struct valueNode* getDefaultValueNode();
union varvalue* cloneValue(int type, union varvalue* value);
struct variable* insert(char* symname, int type, union varvalue *val);
void removeVariables(int scope);
void swap(char* name1, char* name2);
struct statementSetNode* reverseStatementSetNodes(struct statementSetNode* root);
void display();
struct valueNode* makeValueNode(int type, union varvalue *value);
void switchUnionValue(union varvalue* value, int fromType, int toType);
void printIndentation(int indent);

// --------------------------------------------- Node Creation Functions ---------------------------------------------- //

struct expressionNode* makeExpressionNode(char* name, struct valueNode* value_node);
struct expressionNode* unaryOperation(struct expressionNode* expression_node_1, char* operation);
struct expressionNode* binaryOperation(struct expressionNode* expression_node_1, struct expressionNode* expression_node_2, char* operation);
struct expressionNode* ternaryOperation(struct expressionNode* expression_node_1, struct expressionNode* expression_node_2, struct expressionNode* expression_node_3);
struct symbolNode* makeSymbolNode(char* name, struct expressionNode *expression_node_1);
struct listNode* makeListNode(symbolNode *symbol, listNode *list);
struct expressionNode* makeExpressionNodeFromAssignment(struct assignmentNode* assignment_node);
struct declarationNode* makeDeclarationNode(int type, listNode* list);
struct assignmentNode* makeAssignmentNode(char* name, struct expressionNode* expression_node_1, char* operation);
struct swapOperatonNode* makeSwapOperationNode(char* name1, char* name2);
struct statementNode* makeStatementNode(void* Statement, int statement_type);
struct constructNode* makeConstructNode(void* Construct, int construct_type);
struct statementSetNode* makeStatementSetNode(struct statementSetNode* statement_set_node, void* statement_node, int statement_set_type);
struct ifBlock* makeIfBlock(struct expressionNode *condition, struct statementSetNode *body);
struct elifBlock* makeElifBlock(struct expressionNode *condition, struct statementSetNode *body, struct elifBlock* elif_blocks);
struct elseBlock* makeElseBlock(struct statementSetNode *body);
struct optionalBlocks* makeOptionalBlocks(struct elifBlock* elif_block, struct elseBlock* else_block);
struct ifConstruct* makeIfConstruct(struct ifBlock* if_block, struct optionalBlocks* optional_blocks);
struct forConstruct* makeForConstruct(struct statementNode *first_statement, struct expressionNode *middle_expression, struct statementNode *last_statement, struct statementSetNode *body);
struct whileConstruct* makeWhileConstruct(struct expressionNode *condition,	struct statementSetNode *body);

// --------------------------------------------- Node Printing Functions ---------------------------------------------- //

void printDeclarationNode(struct declarationNode* declaration_node);
void printValueNode(struct valueNode* value_node);
void printVariable(char* var_name);
void printAssignmentNode(struct assignmentNode* assignment_node);
void printTernaryExpression(struct ternaryExpression* ternary_expression);
void printBinaryExpression(struct binaryExpression* binary_expression);
void printUnaryExpression(struct unaryExpression* unary_expression);
void printExpressionNode(struct expressionNode* expression_node);
void printSwapOperationNode(struct swapOperationNode* swap_operation_node);
void printPrintNode(struct expressionNode* expression_node);
void printBreakNode();
void printContinueNode();
void printStatementNode(struct statementNode* statement_node);
void printConstructNode(struct constructNode* construct_node);
void printStatementSetNode(struct statementSetNode* statement_set_node);
void printIfConstruct(struct ifConstruct* if_construct);
void printForConstruct(struct forConstruct* for_construct);
void printWhileConstruct(struct whileConstruct* while_construct);

// --------------------------------------------- Node Execution Functions --------------------------------------------- //

void executeProgram(struct statementSetNode* statement_set_node);
void executeStatementSetNode(struct statementSetNode* statement_set_node);
void executeStatementNode(struct statementNode *statement_node);
void executeBreakStatement(int break_line);
void executeContinueStatement(int continue_line);
void executePrintStatement(struct expressionNode* expression_node);
void executeDeclarationNode(struct declarationNode *declaration_node);
void executeSymbolNode(struct symbolNode *symbol);
void executeAssignmentNode(struct assignmentNode *assignment_node);
void executeSwapOperationNode(struct swapOperationNode *swap_operation_node);
void executeExpressionNode(struct expressionNode *expression_node);
void executeTernaryExpression(struct expressionNode *expression_node);
void executeBinaryExpression(struct expressionNode *expression_node);
void executeUnaryExpression(struct expressionNode *expression_node);
void executeConstructNode(struct constructNode *construct_node);
void executeIfConstruct(struct ifConstruct *if_construct);
int executeIfBlock(struct ifBlock* if_block);
int executeElifBlock(struct elifBlock* elif_block);
void executeElseBlock(struct elseBlock* else_block);
void executeForConstruct(struct forConstruct *for_construct);
void executeWhileConstruct(struct whileConstruct *while_construct);