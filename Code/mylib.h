// import constants
#include "constants.h"

// import the global variable to be used
#include "global_variables.h";

// import structure and unions defined for different types of nodes
#include "structures_unions.h";

// import the functions to make, print and execute the nodes of AST
#include "function_declarations.h";
// NOTE: without importing the `function_declarations.h`, different order of following imports may cause errors
#include "node_helper_functions.h";
#include "node_creating_functions.h";
#include "node_printing_functions.h";
#include "node_executing_functions.h"; 
// The compiler has no backend to generate target code,
// Hence execution is being done by 'node executiing functions'
// Which bascically reads the nodes of genrated tree and processes accordingly