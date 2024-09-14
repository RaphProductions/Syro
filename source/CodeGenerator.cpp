#include "CodeGenerator.h"
#include <unordered_map>
#include <stdexcept>

std::string CodeGenerator::mapType(const std::string &syroType)
{
    static const std::unordered_map<std::string, std::string> typeMap = {
        {"i8", "signed char"},
        {"i16", "short"},
        {"i32", "int"},
        {"i64", "long long"},
        {"isize", "long"},

        {"u8", "unsigned char"},
        {"u16", "unsigned short"},
        {"u32", "unsigned int"},
        {"u64", "unsigned long long"},
        {"usize", "unsigned long"},

        {"void", "void"},
    };

    // Utilisation directe de at() qui lève std::out_of_range si la clé n'existe pas
    return typeMap.at(syroType);
}

std::string CodeGenerator::generate(const Program &program)
{
    generateProgram(program);
    return output.str();
}

void CodeGenerator::generateProgram(const Program &program)
{
    for (const auto &stmt : program.statements)
    {
        generateStatement(*stmt);
    }
}

void CodeGenerator::generateStatement(const Statement &stmt)
{
    if (auto varDecl = dynamic_cast<const VariableDeclaration *>(&stmt))
    {
        generateVariableDeclaration(*varDecl);
    }
    else if (auto funcDecl = dynamic_cast<const FunctionDeclaration *>(&stmt))
    {
        generateFunctionDeclaration(*funcDecl);
    }
    else if (auto returnStmt = dynamic_cast<const ReturnStatement *>(&stmt))
    {
        generateReturnStatement(*returnStmt);
    }
}

void CodeGenerator::generateReturnStatement(const ReturnStatement &returnStmt)
{
    indent(currentIndent);
    output << "return";
    if (returnStmt.expression)
    {
        output << " ";
        generateExpression(*returnStmt.expression);
    }
    output << ";\n";
}

void CodeGenerator::generateVariableDeclaration(const VariableDeclaration &varDecl)
{
    indent(currentIndent);
    output << mapType(varDecl.typeName) << " " << varDecl.name;
    if (varDecl.initializer)
    {
        output << " = ";
        generateExpression(*varDecl.initializer);
    }
    output << ";\n";
}

void CodeGenerator::generateFunctionDeclaration(const FunctionDeclaration &funcDecl)
{
    indent(currentIndent);
    output << mapType(funcDecl.returnTypeName) << " " << funcDecl.name << "(";

    const size_t paramCount = funcDecl.parameters.size();
    for (size_t i = 0; i < paramCount; ++i)
    {
        const auto &param = funcDecl.parameters[i];
        output << mapType(param.second) << " " << param.first;
        if (i < paramCount - 1)
        {
            output << ", ";
        }
    }

    output << ") {\n";
    currentIndent++;
    for (const auto &stmt : funcDecl.body)
    {
        generateStatement(*stmt);
    }
    currentIndent--;
    indent(currentIndent);
    output << "}\n";
}

void CodeGenerator::generateExpression(const Expression &expr)
{
    if (auto literal = dynamic_cast<const LiteralExpression *>(&expr))
    {
        output << literal->value;
    }
    else if (auto identifier = dynamic_cast<const IdentifierExpression *>(&expr))
    {
        output << identifier->name;
    }
    else if (auto binaryExpr = dynamic_cast<const BinaryExpression *>(&expr))
    {
        output << "(";
        generateExpression(*binaryExpr->left);
        output << " " << binaryExpr->op << " ";
        generateExpression(*binaryExpr->right);
        output << ")";
    }
    else if (auto castExpr = dynamic_cast<const CastExpression *>(&expr))
    {
        output << "(" << mapType(castExpr->targetType) << ") ";
        generateExpression(*castExpr->expr);
    }
    else if (auto funcCallExpr = dynamic_cast<const FunctionCallExpression *>(&expr))
    {
        output << funcCallExpr->functionName << "(";
        const size_t argCount = funcCallExpr->arguments.size();
        for (size_t i = 0; i < argCount; ++i)
        {
            generateExpression(*funcCallExpr->arguments[i]);
            if (i < argCount - 1)
            {
                output << ", ";
            }
        }
        output << ")";
    }
}

void CodeGenerator::indent(int level)
{
    output << std::string(level * 4, ' ');
}
