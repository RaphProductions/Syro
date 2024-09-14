#include "CodeGenerator.h"

std::string CodeGenerator::generate(const Program& program) {
    generateProgram(program);
    return output.str();
}

void CodeGenerator::generateProgram(const Program& program) {
    for (const auto& stmt : program.statements) {
        generateStatement(*stmt);
    }
}

void CodeGenerator::generateStatement(const Statement& stmt) {
    if (auto varDecl = dynamic_cast<const VariableDeclaration*>(&stmt)) {
        generateVariableDeclaration(*varDecl);
    } else if (auto funcDecl = dynamic_cast<const FunctionDeclaration*>(&stmt)) {
        generateFunctionDeclaration(*funcDecl);
    }
}

void CodeGenerator::generateVariableDeclaration(const VariableDeclaration& varDecl) {
    indent(currentIndent);
    output << varDecl.type << " " << varDecl.name;
    if (varDecl.initializer) {
        output << " = ";
        generateExpression(*varDecl.initializer);
    }
    output << ";\n";
}

void CodeGenerator::generateFunctionDeclaration(const FunctionDeclaration& funcDecl) {
    indent(currentIndent);
    output << funcDecl.returnType << " " << funcDecl.name << "(";

    for (size_t i = 0; i < funcDecl.parameters.size(); ++i) {
        const auto& param = funcDecl.parameters[i];
        output << param.second << " " << param.first;
        if (i < funcDecl.parameters.size() - 1) {
            output << ", ";
        }
    }
    output << ") {\n";
    currentIndent++;
    for (const auto& stmt : funcDecl.body) {
        generateStatement(*stmt);
    }
    currentIndent--;
    indent(currentIndent);
    output << "}\n";
}

void CodeGenerator::generateExpression(const Expression& expr) {
    if (auto literal = dynamic_cast<const LiteralExpression*>(&expr)) {
        output << literal->value;
    } else if (auto identifier = dynamic_cast<const IdentifierExpression*>(&expr)) {
        output << identifier->name;
    } else if (auto binaryExpr = dynamic_cast<const BinaryExpression*>(&expr)) {
        output << "(";
        generateExpression(*binaryExpr->left);
        output << " " << binaryExpr->op << " ";
        generateExpression(*binaryExpr->right);
        output << ")";
    }
}

void CodeGenerator::indent(int level) {
    for (int i = 0; i < level; ++i) {
        output << "    ";
    }
}
