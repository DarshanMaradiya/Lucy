//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																														//
// -------------------------------------------------- Global Variables ------------------------------------------------ //
//																														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Line counter
int line = 1;

// Scope counter
int scope = 0;

// Scope of for loops first statement
int for_first_scope = -1;

// Break validator
int break_flag = 0; // {0 : unset, 1 : do break, -1 : ready to break}

// Continue validator
int continue_flag = 0; // {0 : unset, 1 : do continue, -1 : ready to continue}

// To print indentations in AST
int indent = -1;

// Head of LinkedList of Symbol Entries
struct variable *start = NULL;