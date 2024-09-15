#pragma once

#include "AST.h"
#include <string>
#include <unordered_map>
#include <sstream>

class CodeGenerator
{
public:
    std::string generate(const Program &program);

private:
    std::ostringstream output;
    int currentIndent = 0;

    std::string mapType(const std::string &syroType);

    void generateProgram(const Program &program);
    void generateStatement(const Statement &stmt);
    void generateVariableDeclaration(const VariableDeclaration &varDecl);
    void generateFunctionDeclaration(const FunctionDeclaration &funcDecl);
    void generateReturnStatement(const ReturnStatement &returnStmt);
    void generateAssignmentStatement(const AssignmentStatement &assignStmt);
    void generateExpression(const Expression &expr);

    void indent(int level);
};
