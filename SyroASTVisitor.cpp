#include "SyroASTVisitor.h"

antlrcpp::Any SyroASTVisitor::visitProgram(SyroParser::ProgramContext *ctx)
{
    ast = std::make_shared<Program>();
    for (auto stmtCtx : ctx->statement())
    {
        auto stmt = visit(stmtCtx).as<std::shared_ptr<Statement>>();
        if (stmt)
        {
            ast->statements.push_back(stmt);
        }
    }
    return nullptr;
}

antlrcpp::Any SyroASTVisitor::visitStatement(SyroParser::StatementContext *ctx)
{
    if (ctx->variableDeclaration())
    {
        return visit(ctx->variableDeclaration());
    }
    else if (ctx->functionDeclaration())
    {
        return visit(ctx->functionDeclaration());
    }
    else
    {
        return nullptr;
    }
}

antlrcpp::Any SyroASTVisitor::visitVariableDeclaration(SyroParser::VariableDeclarationContext *ctx)
{
    auto varDecl = std::make_shared<VariableDeclaration>();
    varDecl->name = ctx->Identifier()->getText();
    varDecl->typeName = ctx->type() ? ctx->type()->getText() : "int";
    if (ctx->expression())
    {
        varDecl->initializer = visit(ctx->expression()).as<std::shared_ptr<Expression>>();
    }
    return std::static_pointer_cast<Statement>(varDecl);
}

antlrcpp::Any SyroASTVisitor::visitFunctionDeclaration(SyroParser::FunctionDeclarationContext *ctx)
{
    auto funcDecl = std::make_shared<FunctionDeclaration>();
    funcDecl->name = ctx->Identifier()->getText();

    if (ctx->type())
    {
        funcDecl->returnTypeName = ctx->type()->getText();
    }
    else
    {
        funcDecl->returnTypeName = "void";
    }

    auto paramListCtx = ctx->parameterList();
    if (!paramListCtx->parameter().empty())
    {
        for (auto paramCtx : paramListCtx->parameter())
        {
            std::string paramName = paramCtx->Identifier()->getText();
            std::string paramTypeName = paramCtx->type()->getText();
            funcDecl->parameters.push_back({paramName, paramTypeName});
        }
    }

    for (auto stmtCtx : ctx->block()->statement())
    {
        auto stmt = visit(stmtCtx).as<std::shared_ptr<Statement>>();
        if (stmt)
        {
            funcDecl->body.push_back(stmt);
        }
    }
    return std::static_pointer_cast<Statement>(funcDecl);
}

antlrcpp::Any SyroASTVisitor::visitExpression(SyroParser::ExpressionContext *ctx)
{
    if (ctx->IntegerLiteral())
    {
        auto literal = std::make_shared<LiteralExpression>();
        literal->value = ctx->IntegerLiteral()->getText();
        return std::static_pointer_cast<Expression>(literal);
    }
    else if (ctx->StringLiteral())
    {
        auto literal = std::make_shared<LiteralExpression>();
        literal->value = ctx->StringLiteral()->getText();
        return std::static_pointer_cast<Expression>(literal);
    }
    else if (ctx->Identifier())
    {
        auto identifier = std::make_shared<IdentifierExpression>();
        identifier->name = ctx->Identifier()->getText();
        return std::static_pointer_cast<Expression>(identifier);
    }
    else if (ctx->op)
    {
        auto binaryExpr = std::make_shared<BinaryExpression>();
        binaryExpr->left = visit(ctx->expression(0)).as<std::shared_ptr<Expression>>();
        binaryExpr->right = visit(ctx->expression(1)).as<std::shared_ptr<Expression>>();
        binaryExpr->op = ctx->op->getText();
        return std::static_pointer_cast<Expression>(binaryExpr);
    }
    else if (ctx->expression().size() == 1)
    {
        return visit(ctx->expression(0));
    }
    else
    {
        return nullptr;
    }
}
