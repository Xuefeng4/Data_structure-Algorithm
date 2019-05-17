#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    std::string rt = getRoot()->elem;
    if(rt== "+"){
      AbstractSyntaxTree* left = new AbstractSyntaxTree(getRoot()-> left);
      double leftv = left ->eval();
      AbstractSyntaxTree* right = new AbstractSyntaxTree(getRoot()-> right);
      double rightv  = right -> eval();
       return leftv + rightv;
    } else  if(rt== "-"){
      AbstractSyntaxTree* left = new AbstractSyntaxTree(getRoot()-> left);
      double leftv = left ->eval();
      AbstractSyntaxTree* right = new AbstractSyntaxTree(getRoot()-> right);
      double rightv  = right -> eval();
      return leftv - rightv;
    } else if(rt== "*"){
      AbstractSyntaxTree* left = new AbstractSyntaxTree(getRoot()-> left);
      double leftv = left ->eval();
      AbstractSyntaxTree* right = new AbstractSyntaxTree(getRoot()-> right);
      double rightv  = right -> eval();
      return leftv * rightv;
    }  else if(rt== "/"){
      AbstractSyntaxTree* left = new AbstractSyntaxTree(getRoot()-> left);
      double leftv = left ->eval();
      AbstractSyntaxTree* right = new AbstractSyntaxTree(getRoot()-> right);
      double rightv  = right -> eval();
      return leftv / rightv;
    }else {
      return  std::stod(rt);
    }

}
