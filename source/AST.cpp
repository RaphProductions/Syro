#include "AST.h"

void ASTNode::printIndent(std::ostream &os, int indent) const
{
    for (int i = 0; i < indent; ++i)
    {
        os << "  ";
    }
}

void Program::print(std::ostream &os, int indent) const
{
    printIndent(os, indent);
    os << "Program:\n";
    for (const auto &stmt : statements)
    {
        stmt->print(os, indent + 1);
    }
}

void VariableDeclaration::print(std::ostream &os, int indent) const
{
    printIndent(os, indent);
    os << "VariableDeclaration: " << name << " of type " << typeName << "\n";
    if (initializer)
    {
        printIndent(os, indent + 1);
        os << "Initializer:\n";
        initializer->print(os, indent + 2);
    }
}

void FunctionDeclaration::print(std::ostream &os, int indent) const
{
    printIndent(os, indent);
    os << "FunctionDeclaration: " << name << " returns " << returnTypeName << "\n";
    printIndent(os, indent + 1);
    os << "Parameters:\n";
    for (const auto &param : parameters)
    {
        printIndent(os, indent + 2);
        os << param.first << ": " << param.second << "\n";
    }
    printIndent(os, indent + 1);
    os << "Body:\n";
    for (const auto &stmt : body)
    {
        stmt->print(os, indent + 2);
    }
}

void LiteralExpression::print(std::ostream &os, int indent) const
{
    printIndent(os, indent);
    os << "LiteralExpression: " << value << "\n";
}

void IdentifierExpression::print(std::ostream &os, int indent) const
{
    printIndent(os, indent);
    os << "IdentifierExpression: " << name << "\n";
}

void BinaryExpression::print(std::ostream &os, int indent) const
{
    printIndent(os, indent);
    os << "BinaryExpression: " << op << "\n";
    left->print(os, indent + 1);
    right->print(os, indent + 1);
}

void CastExpression::print(std::ostream &os, int indent) const
{
    printIndent(os, indent);
    os << "CastExpression to " << targetType << "\n";
    expr->print(os, indent + 1);
}

void FunctionCallExpression::print(std::ostream &os, int indent) const
{
    printIndent(os, indent);
    os << "FunctionCallExpression: " << functionName << "\n";
    for (const auto &arg : arguments)
    {
        arg->print(os, indent + 1);
    }
}

void ReturnStatement::print(std::ostream &os, int indent) const
{
    printIndent(os, indent);
    os << "ReturnStatement:\n";
    if (expression)
    {
        expression->print(os, indent + 1);
    }
}

std::ostream &operator<<(std::ostream &os, const ASTNode &node)
{
    node.print(os);
    return os;
}
