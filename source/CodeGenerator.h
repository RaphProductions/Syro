#pragma once

#include "AST.h"
#include <string>
#include <sstream>

class CodeGenerator
{
public:
    std::string generate(const Program &program);

private:
    std::ostringstream output;

    void generateProgram(const Program &program);
    void generateStatement(const Statement &stmt);
    void generateVariableDeclaration(const VariableDeclaration &varDecl);
    void generateFunctionDeclaration(const FunctionDeclaration &funcDecl);
    void generateExpression(const Expression &expr);
    std::string mapType(const std::string &syroType);

    void indent(int level);
    int currentIndent = 0;
};
