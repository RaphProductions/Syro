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
    virtual void print(int indent = 0) const = 0;
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

    void print(int indent = 0) const override;
};

class VariableDeclaration : public Statement
{
public:
    std::string name;
    std::string typeName;
    std::shared_ptr<Expression> initializer;

    void print(int indent = 0) const override;
};

class FunctionDeclaration : public Statement
{
public:
    std::string name;
    std::vector<std::pair<std::string, std::string>> parameters;
    std::string returnTypeName;
    std::vector<std::shared_ptr<Statement>> body;

    void print(int indent = 0) const override;
};

class LiteralExpression : public Expression
{
public:
    std::string value;

    void print(int indent = 0) const override;
};

class IdentifierExpression : public Expression
{
public:
    std::string name;

    void print(int indent = 0) const override;
};

class BinaryExpression : public Expression
{
public:
    std::string op;
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;

    void print(int indent = 0) const override;
};

class CastExpression : public Expression
{
public:
    std::string targetType;
    std::shared_ptr<Expression> expr;

    void print(int indent = 0) const override;
};

void printIndent(int indent);

#endif
