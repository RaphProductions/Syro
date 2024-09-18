#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>

class ASTNode
{
public:
    virtual ~ASTNode() = default;

    virtual void print(std::ostream &os, int indent = 0) const = 0;

protected:
    void printIndent(std::ostream &os, int indent) const;
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

    void print(std::ostream &os, int indent = 0) const override;
};

class VariableDeclaration : public Statement
{
public:
    std::string name;
    std::string typeName;
    std::shared_ptr<Expression> initializer;

    void print(std::ostream &os, int indent = 0) const override;
};

class FunctionDeclaration : public Statement
{
public:
    std::string name;
    std::vector<std::pair<std::string, std::string>> parameters;
    std::string returnTypeName;
    std::vector<std::shared_ptr<Statement>> body;

    void print(std::ostream &os, int indent = 0) const override;
};

class LiteralExpression : public Expression
{
public:
    std::string value;

    void print(std::ostream &os, int indent = 0) const override;
};

class IdentifierExpression : public Expression
{
public:
    std::string name;

    void print(std::ostream &os, int indent = 0) const override;
};

class BinaryExpression : public Expression
{
public:
    std::string op;
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;

    void print(std::ostream &os, int indent = 0) const override;
};

class CastExpression : public Expression
{
public:
    std::string targetType;
    std::shared_ptr<Expression> expr;

    void print(std::ostream &os, int indent = 0) const override;
};

class FunctionCallExpression : public Expression
{
public:
    std::string functionName;
    std::vector<std::shared_ptr<Expression>> arguments;

    void print(std::ostream &os, int indent = 0) const override;
};

class ReturnStatement : public Statement
{
public:
    std::shared_ptr<Expression> expression;

    void print(std::ostream &os, int indent = 0) const override;
};

class AssignmentStatement : public Statement
{
public:
    std::string variableName;
    std::string operatorSymbol;
    std::shared_ptr<Expression> expression;

    void print(std::ostream &os, int indent = 0) const override;
};

class IfElseStatement : public Statement
{
public:
    Expression ifExpression;
    std::vector<std::shared_ptr<Statement>> ifBody;

    std::vector<std::shared_ptr<Statement>> elseBody;

    void print(std::ostream &os, int indent = 0) const override;
};

std::ostream &operator<<(std::ostream &os, const ASTNode &node);
