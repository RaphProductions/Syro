#pragma once

#include "SyroBaseVisitor.h"
#include "AST.h"
#include <memory>

class SyroASTVisitor : public SyroBaseVisitor
{
public:
    std::shared_ptr<Program> ast;

    virtual antlrcpp::Any visitProgram(SyroParser::ProgramContext *ctx) override;
    virtual antlrcpp::Any visitStatement(SyroParser::StatementContext *ctx) override;
    virtual antlrcpp::Any visitReturnStatement(SyroParser::ReturnStatementContext *ctx) override;
    virtual antlrcpp::Any visitVariableDeclaration(SyroParser::VariableDeclarationContext *ctx) override;
    virtual antlrcpp::Any visitFunctionDeclaration(SyroParser::FunctionDeclarationContext *ctx) override;
    virtual antlrcpp::Any visitAssignmentStatement(SyroParser::AssignmentStatementContext *ctx) override;
    virtual antlrcpp::Any visitExpression(SyroParser::ExpressionContext *ctx) override;
};
