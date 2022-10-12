#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"
#include "scanner.h"
#include "expressionTree.h"

#ifndef BUILDTREE_OFF
bool isOperand(Token t)
{
  return(t.type == T_MUL || t.type == T_DIV || t.type == T_SUB || t.type == T_ADD);  
}

TreeNode * buildExpressionTree(Scanner * s) 
{

    Token t1 = nextToken(s);

    if(t1.type == T_VAL)
        {
        Token t2 = nextToken(s);
        if(!isOperand(t2)){
            exit(1);
        }
        TreeNode *root = buildTreeNode(t2);
        Token t3 = nextToken(s);
        if(t3.type == T_LPAREN)
            {
            root -> left = buildTreeNode(t1);
            root -> right = buildExpressionTree(s);
            Token t5 = nextToken(s);

            if(t5.type == T_EOF)
            {
                return root;
            }
            else if(isOperand(t5))
            {
                TreeNode *root2 = buildTreeNode(t5);
                root2 -> left = root;
                root2 -> right = buildExpressionTree(s);
                return root2;
            }
            return root;
        }
        else if(t3.type == T_VAL)
            {
            Token t4 = nextToken(s);
            if(t4.type == T_RPAREN)
            {
                root -> left = buildTreeNode(t1);
                root -> right = buildTreeNode(t3);
                Token t6 = nextToken(s);
                if(t6.type == T_EOF)
                {
                    return root;
                }
                if(isOperand(t6))
                {
                    TreeNode *root3 = buildTreeNode(t6);
                    root3 -> left = root;
                    Token t7 = nextToken(s);
                    if(t7.type == T_LPAREN)
                    {
                        root3 -> right = buildExpressionTree(s);
                    }
                    if(t7.type == T_VAL)
                    {
                        root3 -> right = buildTreeNode(t7);
                        Token t8 = nextToken(s);
                        if(t8.type == T_RPAREN)
                        {
                            Token t9 = nextToken(s);
                            if(isOperand(t9))
                            {
                                TreeNode *root4 = buildTreeNode(t9);
                                root4 -> left = root3;
                                root4 -> right = buildExpressionTree(s);
                                return root4;
                            }
                            return root3;
                        }
                        else if(t8.type == T_EOF){
                            exit(1);
                        }
                    }
                    return root3;
                }
                return root;
            }
        }
    }
    else if(t1.type == T_LPAREN)
    {
        return buildExpressionTree(s);
    }

    return buildExpressionTree(s);
}
#endif

#ifndef POSTFIX_OFF
void makePostFix(TreeNode * t, FILE * fptr) {
	
    if (t == NULL) 
    {
        return;
    }
    makePostFix(t -> left, fptr); // print root -> left 
    makePostFix(t -> right, fptr); // print root -> right
    if(t->t.type == T_VAL)
    {
        fprintf(fptr, "%f ", t->t.value);
    }
    else
    {
        fprintf(fptr, "%c ", t->t.type); // print root 
    }
}
#endif


