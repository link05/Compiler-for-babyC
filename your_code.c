#include "your_code.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
This method adds node to symboltable
*/

int reg_count =1;
int rarp=0;
int blocklevel=0;
FILE * fp;
s_table * AddNode(s_table * head, char * variable)
{
 if(head== NULL)
   {
	head =(s_table*)malloc(sizeof(s_table));
	head->var_name=variable;
	head->next= NULL;
	head->offset=0;
   }
   
   else
   {
	s_table * temp = head;
	while(temp->next != NULL)
	{
	  temp= temp->next;	
	}
	s_table * node = (s_table*)malloc(sizeof(s_table));
	node->var_name=variable;
	node->offset=temp->offset+4;
	node->next=NULL;
	temp->next= node;
   }
   return head;
}

void PrintList(s_table * head)
{
	s_table * temp = head;
	while(temp->next != NULL)
	{
	  printf("variable %s in linkedlist with offset %d\n",temp->var_name,temp->offset);
	  temp= temp->next;	
	}
	printf("variable %s in linkedlist with offset %d\n",temp->var_name,temp->offset);
}

int isThere(s_table * head, char * target)
{
  s_table * current= head;
  int found=-1; //-1 meaning not found`
  //current being null means there are no items in linkedlist so therefore return 0
  if(current == NULL) return found;
  
  //if header does have node
  else
  {
   while(current != NULL && found ==-1) //continue until we have reached the end or we found target in linkedlist
   {
	if(strcmp(current->var_name,target) == 0) 
	{
		found=current->offset;
	}
	current= current->next;
   }
   return found;
  }
}
ASTNode* CreateNumNode(int num)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_NUM; 
    node->num = num;
    return node;
}

s_table * FindVar(s_table * head,char * name)
{
	//reference node to s_table var
   int offset= isThere(head,name); //returns offset value
   
   offset= offset/4;
   int i=0;
   s_table * temp= head;
   for(i=0;i<offset;i++) temp= temp->next;
   return temp;
}

ASTNode * CreateOrNode(ASTNode * condition, ASTNode *term)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = ASTNODE_LOGIC_OP;
  node->op= OR_OP;
  node->left=condition;
  node->right=term;
  return node;
}

ASTNode * CreateAndNode(ASTNode * condition, ASTNode *term)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = ASTNODE_LOGIC_OP;
  node->op= AND_OP;
  node->left=condition;
  node->right=term;
  return node;
}

ASTNode* CreateIfNode(ASTNode*condition,ASTNode*stmtlst)
{
 ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
 node->type=ASTNODE_IF;
 node->left=condition;
 node->right=stmtlst;
 return node;
}

ASTNode * CreateIfElseNode(ASTNode * condition, ASTNode* stmtlst,ASTNode* elsepart)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type=ASTNODE_IF_ELSE;
  node->left=condition;
  node->right=stmtlst;
  node->next= elsepart;
  return node;
}

ASTNode* CreateIdentNode(char* name)
{
  //check if the identifer exists before modifying it
  if(isThere(head,name)== -1)
  {
	yyerror("Ident not declared.");
  }
  else
  {
   ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
   node->type=ASTNODE_IDENT;
   node->name=name;
   node->index= FindVar(head,name);
   return node;
  }
}

ASTNode * CreateAddNode(ASTNode * expr,ASTNode * term)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = ASTNODE_ARITH_OP;
  node->op = ADD_OP;
  node->left = expr;
  node->right = term;
  return node;
}

ASTNode * CreateSubNode(ASTNode* expr,ASTNode * term)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = ASTNODE_ARITH_OP;
  node->op = SUB_OP;
  node->left = expr;
  node->right = term;
  return node;	
}

ASTNode * CreateMultNode(ASTNode * term,ASTNode * factor)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = ASTNODE_ARITH_OP;
  node->op = MULT_OP;
  node->left = term;
  node->right = factor;
  return node;
}

ASTNode * CreateDivNode(ASTNode * term,ASTNode * factor)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
  node->type = ASTNODE_ARITH_OP;
  node->op = DIV_OP;
  node->left = term;
  node->right = factor;
  return node;
}

ASTNode * CreateAsnNode(ASTNode * LHS,ASTNode * Expr)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));	
  node->type=ASTNODE_ASSIGN;
  node->left=LHS;
  node->right=Expr;
  return node;
}

ASTNode *CreateLHSNode(char * lhs)
{
  
  if(isThere(head,lhs) ==-1)
  {
    yyerror("Ident not declared.\n");
  }
  else
  {
   ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));	
   node->type=ASTNODE_LHS;
   node->name=lhs;
   return node;
  }
}

ASTNode * CreateEqlCmpNode(ASTNode *cmp1, ASTNode * cmp2)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));	
  node->type = ASTNODE_LOGIC_OP;
  node->op=E_OP;
  node->left= cmp1;
  node->right = cmp2;
  return node;
}
ASTNode * CreateNEqlCmpNode(ASTNode *cmp1, ASTNode * cmp2)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));	
  node->type = ASTNODE_LOGIC_OP;
  node->op=NE_OP;
  node->left= cmp1;
  node->right = cmp2;
  return node;
}
ASTNode * CreateGtrCmpNode(ASTNode *cmp1, ASTNode * cmp2)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));	
  node->type = ASTNODE_LOGIC_OP;
  node->op=G_OP;
  node->left= cmp1;
  node->right = cmp2;
  return node;
}
ASTNode * CreateLessCmpNode(ASTNode *cmp1, ASTNode * cmp2)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));	
  node->type = ASTNODE_LOGIC_OP;
  node->op=L_OP;
  node->left= cmp1;
  node->right = cmp2;
  return node;
}
ASTNode * CreateLEqlCmpNode(ASTNode *cmp1, ASTNode * cmp2)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));	
  node->type = ASTNODE_LOGIC_OP;
  node->op=LE_OP;
  node->left= cmp1;
  node->right = cmp2;
  return node;  
}
ASTNode * CreateGEqlCmpNode(ASTNode *cmp1, ASTNode * cmp2)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));	
  node->type = ASTNODE_LOGIC_OP;
  node->op=GE_OP;
  node->left= cmp1;
  node->right = cmp2;
  return node;  
}

ASTNode * CreateWhileNode(ASTNode * cond, ASTNode * Stmt)
{
  ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));	
  node->type= ASTNODE_WHILE;
  node->left=cond;
  node->right=Stmt;
  return node;
}

// Take a statement node and a statement list node and connect them together
// to form a bigger statement list node (add the statement to the statement list).
// Return a pointer to the bigger list that resulted from this linking
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList)
{
 ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));	
 node->type= ASTNODE_STMT;
 node->left=st;
 node->right=stList;
 return node;
}


/*
  call method to check if that declaration already exists
  if not, then create it
*/
void AddDeclaration(char* name)
{
 if(isThere(head,name)!= -1)
  {
   char err[100]="Multiple declarations of '";
   strcat(err,name);
   strcat(err,"'.");
   yyerror(err);
  }
  else
  {
	head=AddNode(head,name);
    //PrintList(head);  
  }
}


/*
 num holds the char # value which will be used for naming
 the file
*/
void GenerateILOC(ASTNode* node,char num)
{
   char filename[10];
   strcpy(filename,"test");
   filename[4]=num;
   filename[5]='\0'; //if you dont have this then you will have garbage in your arry
   strcat(filename,".iloc");
   
   fp=fopen(filename,"wb");
   if(fp == NULL) printf("Error could not open file");
   else
   {
	CheckNode(node);
    fclose(fp);     
   }
  
}

int CheckNode(ASTNode * node)
{
	int reg1,reg2;
	int result=-1;
	switch(node->type)
	{
	  case ASTNODE_ASSIGN:
	    reg1 = CheckNode(node->right);
	    
	    
		fprintf(fp,"\tstoreAI r%d -> rarp, %d\n",reg1,node->left->index->offset); 
	    //rarp= 4+ rarp;
	    break;
	  
	  case ASTNODE_IDENT:
	    result=reg_count;
	   
		fprintf(fp,"\tloadAI rarp, %d -> r%d\n",node->index->offset,result);
	    IncrementReg();
		
		break;
	  
	  case ASTNODE_NUM:
	    result=reg_count;
		fprintf(fp,"\tloadi %d -> r%d\n",node->num,result);
		IncrementReg();
		break;
		
	  case ASTNODE_WHILE:
		fprintf(fp,"L%d_C:\n",blocklevel);
		reg1 = CheckNode(node->left);
		fprintf(fp,"\tcbr r%d -> L%d_B, L%d_O\n",reg1,blocklevel,blocklevel);
		
		fprintf(fp,"L%d_B:\n",blocklevel);
		if(containsBlock(node->right)) blocklevel++;
		reg2 = CheckNode(node->right);
		fprintf(fp,"\tjumpi -> L%d_C\n",blocklevel);
		fprintf(fp,"L%d_O:\n",blocklevel);
		blocklevel--;
		break;
		
	  case ASTNODE_LOGIC_OP:
		switch(node->op)
		{
		  case OR_OP:
		    if (node->left != NULL) reg1 = CheckNode(node->left);
		    if(node->right != NULL) reg2= CheckNode(node->right);
			fprintf(fp,"\tor r%d, r%d -> r%d\n",reg1,reg2,reg_count);
			result=reg_count;
			IncrementReg();
			break;
		
		  case AND_OP:
		    if (node->left != NULL) reg1 = CheckNode(node->left);
		    if(node->right != NULL) reg2= CheckNode(node->right);
			fprintf(fp,"\tand r%d, r%d -> r%d\n",reg1,reg2,reg_count);
			result=reg_count;
			IncrementReg();
			break;
		
			
		  case G_OP:
		    if (node->left != NULL) reg1= CheckNode(node->left);
			if(node->right != NULL) reg2= CheckNode(node->right);
			fprintf(fp,"\tcmp_GT r%d, r%d -> r%d\n",reg1,reg2,reg_count);
			result=reg_count;
			IncrementReg();
			break;
			
		case GE_OP:
		    if (node->left != NULL) reg1= CheckNode(node->left);
			if(node->right != NULL) reg2= CheckNode(node->right);
			fprintf(fp,"\tcmp_GE r%d, r%d -> r%d\n",reg1,reg2,reg_count);
			result=reg_count;
			IncrementReg();
			break;
			
		  case L_OP:
		    if (node->left != NULL) reg1= CheckNode(node->left);
			if(node->right != NULL) reg2= CheckNode(node->right);
			fprintf(fp,"\tcmp_LT r%d, r%d -> r%d\n",reg1,reg2,reg_count);
			result=reg_count;
			IncrementReg();
			break;
			
		  case LE_OP:
		    if (node->left != NULL) reg1= CheckNode(node->left);
			if(node->right != NULL) reg2= CheckNode(node->right);
			fprintf(fp,"\tcmp_LE r%d, r%d -> r%d\n",reg1,reg2,reg_count);
			result=reg_count;
			IncrementReg();
			break;
			
		  case E_OP:
		    if (node->left != NULL) reg1= CheckNode(node->left);
			if(node->right != NULL) reg2= CheckNode(node->right);
			fprintf(fp,"\tcmp_EQ r%d, r%d -> r%d\n",reg1,reg2,reg_count);
			result=reg_count;
			IncrementReg();
			break;
			
		case NE_OP:
		    if (node->left != NULL) reg1= CheckNode(node->left);
			if(node->right != NULL) reg2= CheckNode(node->right);
			fprintf(fp,"\tcmp_NE r%d, r%d -> r%d\n",reg1,reg2,reg_count);
			result=reg_count;
			IncrementReg();
			break;
			
		}
		break;
	
	  case ASTNODE_ARITH_OP:
	    switch(node->op)
		{
		  case ADD_OP:
		    if (node->left != NULL) reg1= CheckNode(node->left);
			if(node->right != NULL) reg2= CheckNode(node->right);
			result=reg_count;
			fprintf(fp,"\tadd r%d, r%d -> r%d\n",reg1,reg2,reg_count);
			IncrementReg();
			break;
			
		  case SUB_OP:
		    if (node->left != NULL) reg1= CheckNode(node->left);
			if(node->right != NULL) reg2= CheckNode(node->right);
			fprintf(fp,"\tsub r%d, r%d -> r%d\n",reg1,reg2,reg_count);
			result=reg_count;
			IncrementReg();
			break;
			
		  case MULT_OP:
		    if (node->left != NULL) reg1= CheckNode(node->left);
			if(node->right != NULL) reg2= CheckNode(node->right);
			fprintf(fp,"\tmult r%d, r%d -> r%d\n",reg1,reg2,reg_count);
			result=reg_count;
			IncrementReg();
			break;
		
		  case DIV_OP:
		    if (node->left != NULL) reg1= CheckNode(node->left);
			if(node->right != NULL) reg2 = CheckNode(node->right);
			fprintf(fp,"\tdiv r%d, r%d -> r%d\n",reg1,reg2,reg_count);
			result=reg_count;
			IncrementReg();
			break;
		}
	    break;
	  case ASTNODE_STMT:
		//change this later
	    if(node->left != NULL) 
		{
			int inital_block_level=blocklevel; //0 significes block does not need inner block
			if(containsBlock(node->left)) blocklevel++;
			if(blocklevel==0)blocklevel++;   //to account for first blocklevel(it starts with 1)...cant make 1 at top b/c due to recursive call it
			CheckNode(node->left);
			//if(inital_block_level != blocklevel) blocklevel--;
		}
        if(node->right != NULL) CheckNode(node->right);
		break;
		
	  case ASTNODE_IF:
		if(node->left != NULL)reg1= CheckNode(node->left);
		fprintf(fp,"\tcbr r%d -> L%d_T, L%d_M\n",reg1,blocklevel,blocklevel);
		fprintf(fp,"L%d_T:\n",blocklevel);
		
		if(containsBlock(node->right)) blocklevel++;
		if(node->right != NULL) reg2= CheckNode(node->right);
		fprintf(fp,"L%d_M:\n",blocklevel);
		blocklevel--;
		break;
		
	case ASTNODE_IF_ELSE:
		if(node->left != NULL)reg1= CheckNode(node->left);
		fprintf(fp,"\tcbr r%d -> L%d_T, L%d_E\n",reg1,blocklevel,blocklevel);
		fprintf(fp,"L%d_T:\n",blocklevel);
		
		if(containsBlock(node->right)) blocklevel++;
		if(node->right!= NULL)reg2= CheckNode(node->right);
		fprintf(fp,"\tjumpi -> L%d_M\n",blocklevel);
		fprintf(fp,"L%d_E:\n",blocklevel);
		if(containsBlock(node->next)) blocklevel++;
		if(node->next != NULL) CheckNode(node->next);
		fprintf(fp,"L%d_M:\n",blocklevel);
		blocklevel--;
		break; 
	}
	return result;
}

int containsBlock(ASTNode * node)
{
  if(node->type == ASTNODE_IF_ELSE)return 1;
  else if(node->type == ASTNODE_IF) return 1;
  else if(node->type == ASTNODE_WHILE) return 1;	
  else return 0;
	 
  }

void IncrementReg()
{
	reg_count++;
}
