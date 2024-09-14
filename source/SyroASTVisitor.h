#pragma once

#include "../generated/SyroBaseVisitor.h"
#include "AST.h"
#include <memory>

class SyroASTVisitor : public SyroBaseVisitor
{
public:
    std::shared_ptr<Program> ast;

    antlrcpp::Any visitProgram(SyroParser::ProgramContext *ctx) override;
    antlrcpp::Any visitStatement(SyroParser::StatementContext *ctx) override;
    antlrcpp::Any visitVariableDeclaration(SyroParser::VariableDeclarationContext *ctx) override;
    antlrcpp::Any visitFunctionDeclaration(SyroParser::FunctionDeclarationContext *ctx) override;
    antlrcpp::Any visitExpression(SyroParser::ExpressionContext *ctx) override;
    antlrcpp::Any visitReturnStatement(SyroParser::ReturnStatementContext *ctx) override;
};
