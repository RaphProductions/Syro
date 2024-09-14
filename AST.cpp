#include "AST.h"

void printIndent(int indent) {
    for (int i = 0; i < indent; ++i)
        std::cout << "  ";
}

void Program::print(int indent) const {
    printIndent(indent);
    std::cout << "Program" << std::endl;
    for (const auto& stmt : statements) {
        stmt->print(indent + 1);
    }
}

void VariableDeclaration::print(int indent) const {
    printIndent(indent);
    std::cout << "VariableDeclaration: " << name << " : " << type << std::endl;
    if (initializer) {
        printIndent(indent + 1);
        std::cout << "Initializer:" << std::endl;
        initializer->print(indent + 2);
    }
}

void FunctionDeclaration::print(int indent) const {
    printIndent(indent);
    std::cout << "FunctionDeclaration: " << name << std::endl;
    printIndent(indent + 1);
    std::cout << "Parameters:" << std::endl;
    for (const auto& param : parameters) {
        printIndent(indent + 2);
        std::cout << param.first << " : " << param.second << std::endl;
    }
    printIndent(indent + 1);
    std::cout << "ReturnType: " << returnType << std::endl;
    printIndent(indent + 1);
    std::cout << "Body:" << std::endl;
    for (const auto& stmt : body) {
        stmt->print(indent + 2);
    }
}

void LiteralExpression::print(int indent) const {
    printIndent(indent);
    std::cout << "LiteralExpression: " << value << std::endl;
}

void IdentifierExpression::print(int indent) const {
    printIndent(indent);
    std::cout << "IdentifierExpression: " << name << std::endl;
}

void BinaryExpression::print(int indent) const {
    printIndent(indent);
    std::cout << "BinaryExpression: " << op << std::endl;
    printIndent(indent + 1);
    std::cout << "Left:" << std::endl;
    left->print(indent + 2);
    printIndent(indent + 1);
    std::cout << "Right:" << std::endl;
    right->print(indent + 2);
}
