#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

class ASTNode
{
public:
    virtual ~ASTNode() = default;
};

class Expression : public ASTNode
{
};

class Statement : public ASTNode
{
};

class Program : public ASTNode
{
public:
    std::vector<std::shared_ptr<Statement>> statements;
};

class VariableDeclaration : public Statement
{
public:
    std::string name;
    std::string typeName;
    std::shared_ptr<Expression> initializer;
};

class FunctionDeclaration : public Statement
{
public:
    std::string name;
    std::vector<std::pair<std::string, std::string>> parameters;
    std::string returnTypeName;
    std::vector<std::shared_ptr<Statement>> body;
};

class LiteralExpression : public Expression
{
public:
    std::string value;
};

class IdentifierExpression : public Expression
{
public:
    std::string name;
};

class BinaryExpression : public Expression
{
public:
    std::string op;
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
};

class CastExpression : public Expression
{
public:
    std::string targetType;
    std::shared_ptr<Expression> expr;
};

#endif
