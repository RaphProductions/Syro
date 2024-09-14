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

    auto it = typeMap.find(syroType);
    if (it != typeMap.end())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error("Error: Unknown type '" + syroType + "'");
    }
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
}

void CodeGenerator::generateVariableDeclaration(const VariableDeclaration &varDecl)
{
    indent(currentIndent);
    std::string cType = mapType(varDecl.typeName);
    output << cType << " " << varDecl.name;
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
    std::string returnType;
    try
    {
        returnType = mapType(funcDecl.returnTypeName);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Error in function '" + funcDecl.name + "': " + e.what());
    }
    output << returnType << " " << funcDecl.name << "(";

    for (size_t i = 0; i < funcDecl.parameters.size(); ++i)
    {
        const auto &param = funcDecl.parameters[i];
        std::string paramType;
        try
        {
            paramType = mapType(param.second);
        }
        catch (const std::exception &e)
        {
            throw std::runtime_error("Error in function parameters '" + funcDecl.name + "': " + e.what());
        }
        output << paramType << " " << param.first;
        if (i < funcDecl.parameters.size() - 1)
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
}

void CodeGenerator::indent(int level)
{
    for (int i = 0; i < level; ++i)
    {
        output << "    ";
    }
}
