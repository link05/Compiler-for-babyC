#ifndef YOUR_CODE_H
#define YOUR_CODE_H

typedef struct s_table s_table;
struct s_table{
	char * var_name;
	int offset;
	s_table * next;
};
extern s_table * head;
typedef enum{ASTNODE_ARITH_OP, ASTNODE_LOGIC_OP, ASTNODE_COMPARE,ASTNODE_ASSIGN, ASTNODE_IDENT, ASTNODE_NUM, ASTNODE_IF, ASTNODE_WHILE,ASTNODE_LHS,ASTNODE_IF_ELSE,ASTNODE_STMT} ASTNodeType;

// Define all operation types (add, mult, etc) here.
typedef enum{ADD_OP, MULT_OP,SUB_OP,DIV_OP,AND_OP,OR_OP,GE_OP,LE_OP,L_OP,G_OP,NE_OP,E_OP} ASTOp; 

typedef struct ASTNode ASTNode;
struct ASTNode{
	ASTNodeType type; 
    ASTOp op; // The actual operation (add, mult, etc)
	int num;  //Need to store the actual value for number nodes
	char *name; //Need to store the actual variable name for ident nodes
	ASTNode* left; // Left child
	ASTNode* right; // Right child
	s_table * index;
	
	// The following pointer is just a suggestion; you don't have to use it if you have a better design.
	ASTNode* next; // a pointer used to link statement nodes together in a statement list
// Depending on your implementation, you may need to add other fields to this struct 

};

// Add functions to create the different kinds of ASTNodes 
// These functions are called by the code embedded in the grammar.
// Here are some samples:  
ASTNode * CreateNumNode(int num);
ASTNode * CreateIdentNode(char* name);
ASTNode * CreateStatementListNode(ASTNode* st, ASTNode* stList);
ASTNode * CreateAddNode(ASTNode * expr,ASTNode * term);
ASTNode * CreateSubNode(ASTNode* expr,ASTNode * term);
ASTNode * CreateMultNode(ASTNode * term,ASTNode * factor);
ASTNode * CreateDivNode(ASTNode * term,ASTNode * factor);
ASTNode * CreateAsnNode(ASTNode * term,ASTNode * factor);

//for if statement prodotype
ASTNode * CreateIfNode(ASTNode*condition, ASTNode*stmtlst);
ASTNode * CreateIfElseNode(ASTNode * condition, ASTNode* stmtlst,ASTNode* elsepart);

//for while loop
ASTNode * CreateWhileNode(ASTNode * cond, ASTNode*stmnt);
//for operators
ASTNode * CreateAndNode(ASTNode * condition, ASTNode *term);
ASTNode * CreateAsnNode(ASTNode * LHS,ASTNode * Expr);
ASTNode * CreateLHSNode(char * lhs);
ASTNode * CreateEqlCmpNode(ASTNode *cmp1, ASTNode * cmp2);
ASTNode * CreateNEqlCmpNode(ASTNode *cmp1, ASTNode * cmp2);
ASTNode * CreateGtrCmpNode(ASTNode *cmp1, ASTNode * cmp2);
ASTNode * CreateLessCmpNode(ASTNode *cmp1, ASTNode * cmp2);
ASTNode * CreateLEqlCmpNode(ASTNode *cmp1, ASTNode * cmp2);
ASTNode * CreateGEqlCmpNode(ASTNode *cmp1, ASTNode * cmp2);
ASTNode * CreateOrNode(ASTNode * condition, ASTNode *term);

// Need a function to add a declaration to your symbol table
/*
  check if the variable already exists in symbol table, if so give error msg.
  if it does not exist then add it to the symbol table
*/
void AddDeclaration(char* name);

// This is the function that generates ILOC code after the construction of the AST
void GenerateILOC(ASTNode* node,char num);
int CheckNode(ASTNode * node);
void IncrementReg();
int containsBlock(ASTNode * node);
#endif
