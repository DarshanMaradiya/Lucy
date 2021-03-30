//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																														//
// ----------------------------------------------- Node Helper Functions ---------------------------------------------- //
//																														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char* toString(struct valueNode* value_node)
{
	int type = value_node->type;
    char* str;
    if(type == C_INT)
    {
        int length = snprintf( NULL, 0, "%d", (value_node->value->ival));
        str = malloc( length + 1 );
        snprintf( str, length + 1, "%d", (value_node->value->ival));
    }
	else if(type == C_LONG)
    {
        int length = snprintf( NULL, 0, "%ld", (value_node->value->lval));
        str = malloc( length + 1 );
        snprintf( str, length + 1, "%ld", (value_node->value->lval));
    }
	else if(type == C_FLOAT)
    {
        int length = snprintf( NULL, 0, "%f", (value_node->value->fval));
        str = malloc( length + 1 );
        snprintf( str, length + 1, "%f", (value_node->value->fval));
    }
	else if(type == C_DOUBLE)
    {
        int length = snprintf( NULL, 0, "%lf", (value_node->value->dval));
        str = malloc( length + 1 );
        snprintf( str, length + 1, "%lf", (value_node->value->dval));
    }
	else if(type == C_CHAR)
    {
        int length = snprintf( NULL, 0, "%c", (value_node->value->cval));
        str = malloc( length + 1 );
        snprintf( str, length + 1, "%c", (value_node->value->cval));
    }
	else if(type == C_BOOLEAN)
    {
        str = value_node->value->bval? "true" : "false";
    }
    return str;
}

char* getOperationName(int operation) {
	switch(operation) {
		case C_OR 			: 	return("||");

		case C_AND 			: 	return("&&");

		case C_BIT_OR 		: 	return("|");

		case C_BIT_XOR 		: 	return("^");

		case C_BIT_AND 		: 	return("&");

		case C_EQUAL 		: 	return("==");
		case C_NOT_EQUAL 	: 	return("!=");

		case C_LESS_THEN 	: 	return("<");
		case C_GREAT_THEN 	: 	return(">");
		case C_LESS_EQUAL 	: 	return("<=");
		case C_GREAT_EQUAL 	: 	return(">=");

		case C_L_SHIFT 		: 	return("<<");
		case C_R_SHIFT 		: 	return(">>");

		case C_PLUS 		: 	return("+");
		case C_MINUS 		: 	return("-");

		case C_MULTIPLY 	: 	return("*");
		case C_DIVIDE 		: 	return("/");
		case C_MODULO 		: 	return("%");

		case C_EXP 			: 	return("**");

		case C_FACT 		: 	return(".!");

		case C_PRE_INC 		: 	return("++.");
		case C_PRE_DEC 		: 	return("--.");

		case C_NOT 			: 	return("!.");
		case C_BIT_NOT 		: 	return("~");

		case C_POST_INC 	: 	return(".++");
		case C_POST_DEC 	: 	return(".--");

		case C_ASSIGN 		: 	return("=");
		case C_PLUS_EQUAL 	: 	return("+=");
		case C_MINUS_EQUAL 	: 	return("-=");
		case C_MULTIPLY_EQUAL : return("*=");
		case C_DIVIDE_EQUAL : 	return("/=");
		case C_MODULO_EQUAL : 	return("%=");
	}
}

char* getDataType(int dataType) {
	switch(dataType) {
		case C_INT 		:	return("int");
		case C_LONG 	:	return("long");
		case C_FLOAT 	:	return("float");
		case C_DOUBLE 	:	return("double");
		case C_CHAR 	:	return("char");
		case C_STRING 	:	return("string");
		case C_BOOLEAN	: 	return("boolean");
		case C_VOID 	:	return("void");
	}
}

struct variable* getVariable(char* name)
{
	struct variable *curr = start, *ans = NULL;
	for(; curr != NULL; curr = curr->next)
		if(strcmp(curr->name, name) == 0 && curr->scope <= scope)
			{
				if(ans == NULL || ans->scope < curr->scope) ans = curr;
			}

	if(ans != NULL) return ans;

	printf("[Error : %d] can not find symbol\nvariable : %s\n", line, name);
	exit(0);
	return NULL;
}

struct valueNode* getDefaultValueNode()
{
	union varvalue* value = (varvalue *)malloc(sizeof(varvalue));
	value->ival = value->lval = value->fval = value->dval = value->cval = value->strval = value->bval = 0;

	struct valueNode* value_node = (valueNode *)malloc(sizeof(valueNode));
	value_node->type = C_INT;
	value_node->value = value;

	return value_node;
}

union varvalue* cloneValue(int type, union varvalue* value)
{
	union varvalue *var_value = (varvalue *)malloc(sizeof(varvalue));

	switch(type) {
		case C_INT 		:	var_value->ival = value->ival;	break;
		case C_LONG 	:	var_value->lval = value->lval;	break;
		case C_FLOAT 	:	var_value->fval = value->fval;	break;
		case C_DOUBLE 	:	var_value->dval = value->dval;	break;
		case C_CHAR 	:	var_value->cval = value->cval;	break;
		case C_STRING 	:	var_value->strval = strdup(value->strval);	break;
		case C_BOOLEAN 	:	var_value->bval = value->bval;	break;
	}

	return var_value;
}

struct variable* insert(char* symname, int type, union varvalue *val)
{
	if(start==NULL){
        struct variable *new_node;
        new_node = (struct variable*) malloc(sizeof(struct variable));
        new_node->name = symname;
        new_node->type = type;
        new_node->value = val;
        new_node->scope = scope;
        new_node->line = line;

        start = new_node;
        start->next = NULL;
        return start;
    }
    else{
        struct variable *ptr = start;
        while(ptr->next!=NULL) {
        	if(strcmp(ptr->name, symname) == 0)
        	{
        		if(ptr->scope == scope || ptr->scope == for_first_scope)
        		{
        			printf("\n[Error : %d] Re-Declaration of variable : %s\n", line, symname);
	            	exit(1);
	            	return NULL;
        		}
        	}
        	ptr = ptr->next;
        }
        
        if(strcmp(ptr->name, symname) == 0)
        {
        	if(ptr->scope == scope || ptr->scope == for_first_scope)
        	{
        		printf("\n[Error : %d] Re-Declaration of variable : %s\n", line, symname);
	           	exit(1);
	           	return NULL;
        	}
        }
        struct variable *new_node;
        new_node = (struct variable*) malloc(sizeof(struct variable));
        new_node->name = symname;
        new_node->type = type;
        new_node->value = val;
        new_node->scope = scope;
        new_node->line = line;

        ptr->next = new_node;
        new_node->next = NULL;

        return new_node;
    }
}

void removeVariables(int scope)
{
	while(start != NULL && start->scope == scope)
		start = start->next;

	variable* curr = start;

	while(curr != NULL)
	{
		while(curr->next != NULL && curr->next->scope == scope)
			curr->next = curr->next->next;

		curr = curr->next;
	}
}

void swap(char* name1, char* name2)
{
	struct variable* var1 = getVariable(name1);
	struct variable* var2 = getVariable(name2);

	int tmpType1 = var1->type;
	union varvalue* tmpValue1 = var1->value;

	// handle when both types are not string
	if(var2->type != var1->type) switchUnionValue(var2->value, var2->type, var1->type);

	var1->value = var2->value;

	// handle when both types are not string
	if(tmpType1 != var2->type) switchUnionValue(tmpValue1, tmpType1, var2->type);

	var2->value = tmpValue1;
}

struct statementSetNode* reverseStatementSetNodes(struct statementSetNode* root)
{
	if(root == NULL || root->next == NULL) return root;

	struct statementSetNode *curr, *prev, *next;
	prev = NULL;
	curr = root;

	while(curr != NULL)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	return prev;
}

void display()
{
	printf("\n\n%10s %10s %10s %10s\n","Name","Type","Scope","Value");
	struct variable *curr = start;

	for(;curr != NULL;curr = curr->next)
	{
		switch(curr->type) {
			case C_INT 		:	printf("%10s int     %10d %10d\n",curr->name,curr->scope,curr->value->ival);	break;
			case C_LONG 	:	printf("%10s long    %10d %10d\n",curr->name,curr->scope,curr->value->lval);	break;
			case C_FLOAT 	:	printf("%10s float   %10d %10d\n",curr->name,curr->scope,curr->value->fval);	break;
			case C_DOUBLE 	:	printf("%10s double  %10d %10d\n",curr->name,curr->scope,curr->value->dval);	break;
			case C_CHAR 	:	printf("%10s char    %10d %10d\n",curr->name,curr->scope,curr->value->cval);	break;
			case C_STRING 	:	printf("%10s string  %10d %10d\n",curr->name,curr->scope,curr->value->strval);	break;
			case C_BOOLEAN 	:	printf("%10s boolean %10d %10d\n",curr->name,curr->scope,(curr->value->bval == 0)?"false":"true");	break;
		}
	}
}

struct valueNode* makeValueNode(int type, union varvalue *value)
{
	struct valueNode *newnode = (valueNode *)malloc(sizeof(valueNode));
	newnode->type = type;
	newnode->value = cloneValue(type, value);
	return(newnode);
}

void switchUnionValue(union varvalue* value, int fromType, int toType)
{
	switch(toType) {
		case C_INT 		:
			switch(fromType) {
				case C_INT 		:	value->ival = value->ival;	break;
				case C_LONG 	:	value->ival = value->lval;	break;
				case C_FLOAT 	:	value->ival = value->fval;	break;
				case C_DOUBLE 	:	value->ival = value->dval;	break;
				case C_CHAR 	:	value->ival = value->cval;	break;
				case C_STRING 	:	printf("\n[Error : %d] can not convert string to int", line); exit(1); //value->ival = value->strval;
				case C_BOOLEAN 	:	value->ival = value->bval;	break;
			}
			break;
		case C_LONG 	:
			switch(fromType) {
				case C_INT 		:	value->lval = value->ival;	break;
				case C_LONG 	:	value->lval = value->lval;	break;
				case C_FLOAT 	:	value->lval = value->fval;	break;
				case C_DOUBLE 	:	value->lval = value->dval;	break;
				case C_CHAR 	:	value->lval = value->cval;	break;
				case C_STRING 	:	printf("\n[Error : %d] can not convert string to long", line); exit(1); //value->ival = value->strval;
				case C_BOOLEAN 	:	value->lval = value->bval;	break;
			}
			break;
		case C_FLOAT 	:
			switch(fromType) {
				case C_INT 		:	value->fval = value->ival;	break;
				case C_LONG 	:	value->fval = value->lval;	break;
				case C_FLOAT 	:	value->fval = value->fval;	break;
				case C_DOUBLE 	:	value->fval = value->dval;	break;
				case C_CHAR 	:	value->fval = value->cval;	break;
				case C_STRING 	:	printf("\n[Error : %d] can not convert string to float", line); exit(1); //value->ival = value->strval;
				case C_BOOLEAN 	:	value->fval = value->bval;	break;
			}
			break;
		case C_DOUBLE 	:
			switch(fromType) {
				case C_INT 		:	value->dval = value->ival;	break;
				case C_LONG 	:	value->dval = value->lval;	break;
				case C_FLOAT 	:	value->dval = value->fval;	break;
				case C_DOUBLE 	:	value->dval = value->dval;	break;
				case C_CHAR 	:	value->dval = value->cval;	break;
				case C_STRING 	:	printf("\n[Error : %d] can not convert string to double", line); exit(1); //value->ival = value->strval;
				case C_BOOLEAN 	:	value->dval = value->bval;	break;
			}
			break;
		case C_CHAR 	:
			switch(fromType) {
				case C_INT 		:	value->cval = value->ival;	break;
				case C_LONG 	:	value->cval = value->lval;	break;
				case C_FLOAT 	:	value->cval = value->fval;	break;
				case C_DOUBLE 	:	value->cval = value->dval;	break;
				case C_CHAR 	:	value->cval = value->cval;	break;
				case C_STRING 	:	printf("\n[Error : %d] can not convert string to char", line); exit(1); //value->ival = value->strval;
				case C_BOOLEAN 	:	value->cval = value->bval;	break;
			}
			break;
		case C_STRING 	:
			switch(fromType) {
				case C_INT 		:	value->strval = toString(makeValueNode(C_INT, value));	break;
				case C_LONG 	:	value->strval = toString(makeValueNode(C_LONG, value));	break;
				case C_FLOAT 	:	value->strval = toString(makeValueNode(C_FLOAT, value));	break;
				case C_DOUBLE 	:	value->strval = toString(makeValueNode(C_DOUBLE, value));	break;
				case C_CHAR 	:	value->strval = toString(makeValueNode(C_CHAR, value));	break;
				case C_STRING 	:	value->strval = value->strval;							break;
				case C_BOOLEAN 	:	value->strval = toString(makeValueNode(C_BOOLEAN, value));break;
			}
			break;
		case C_BOOLEAN 	:
			switch(fromType) {
				case C_INT 		:	value->bval = value->ival ? 1 : 0;	break;
				case C_LONG 	:	value->bval = value->lval ? 1 : 0;	break;
				case C_FLOAT 	:	value->bval = value->fval ? 1 : 0;	break;
				case C_DOUBLE 	:	value->bval = value->dval ? 1 : 0;	break;
				case C_CHAR 	:	value->bval = value->cval ? 1 : 0;	break;
				case C_STRING 	:	value->bval = value->strval ? 1 : 0;break;
				case C_BOOLEAN 	:	value->bval = value->bval ? 1 : 0;	break;
			}
			break;
	}
}

void printIndentation(int indent)
{
	printf("\n");
	while(indent-- > 0) printf("|    ");
	printf("|----");
}