#include "SyroASTVisitor.h"

antlrcpp::Any SyroASTVisitor::visitProgram(SyroParser::ProgramContext *ctx)
{
    ast = std::make_shared<Program>();
    for (auto stmtCtx : ctx->statement())
    {
        if (auto stmt = visit(stmtCtx).as<std::shared_ptr<Statement>>())
        {
            ast->statements.push_back(std::move(stmt));
        }
    }
    return nullptr;
}

antlrcpp::Any SyroASTVisitor::visitStatement(SyroParser::StatementContext *ctx)
{
    if (auto varDecl = ctx->variableDeclaration())
        return visit(varDecl);
    else if (auto funcDecl = ctx->functionDeclaration())
        return visit(funcDecl);
    else if (auto retStmt = ctx->returnStatement())
        return visit(retStmt);

    return nullptr;
}

antlrcpp::Any SyroASTVisitor::visitReturnStatement(SyroParser::ReturnStatementContext *ctx)
{
    auto returnStmt = std::make_shared<ReturnStatement>();

    if (auto exprCtx = ctx->expression())
    {
        returnStmt->expression = visit(exprCtx).as<std::shared_ptr<Expression>>();
    }

    return std::static_pointer_cast<Statement>(returnStmt);
}

antlrcpp::Any SyroASTVisitor::visitVariableDeclaration(SyroParser::VariableDeclarationContext *ctx)
{
    auto varDecl = std::make_shared<VariableDeclaration>();
    varDecl->name = ctx->Identifier()->getText();
    varDecl->typeName = ctx->type() ? ctx->type()->getText() : "i32";

    if (auto exprCtx = ctx->expression())
    {
        varDecl->initializer = visit(exprCtx).as<std::shared_ptr<Expression>>();
    }

    return std::static_pointer_cast<Statement>(varDecl);
}

antlrcpp::Any SyroASTVisitor::visitFunctionDeclaration(SyroParser::FunctionDeclarationContext *ctx)
{
    auto funcDecl = std::make_shared<FunctionDeclaration>();
    funcDecl->name = ctx->Identifier()->getText();
    funcDecl->returnTypeName = ctx->type() ? ctx->type()->getText() : "void";

    for (auto paramCtx : ctx->parameterList()->parameter())
    {
        funcDecl->parameters.push_back({paramCtx->Identifier()->getText(),
                                        paramCtx->type()->getText()});
    }

    for (auto stmtCtx : ctx->block()->statement())
    {
        if (auto stmt = visit(stmtCtx).as<std::shared_ptr<Statement>>())
        {
            funcDecl->body.push_back(std::move(stmt));
        }
    }

    return std::static_pointer_cast<Statement>(funcDecl);
}

antlrcpp::Any SyroASTVisitor::visitExpression(SyroParser::ExpressionContext *ctx)
{
    if (ctx->op)
    {
        auto binaryExpr = std::make_shared<BinaryExpression>();
        binaryExpr->left = visit(ctx->expression(0)).as<std::shared_ptr<Expression>>();
        binaryExpr->right = visit(ctx->expression(1)).as<std::shared_ptr<Expression>>();
        binaryExpr->op = ctx->op->getText();
        return std::static_pointer_cast<Expression>(binaryExpr);
    }
    else if (ctx->children.size() > 0 && ctx->children[0]->getText() == "@cast")
    {
        auto castExpr = std::make_shared<CastExpression>();
        castExpr->targetType = ctx->type()->getText();
        castExpr->expr = visit(ctx->expression(0)).as<std::shared_ptr<Expression>>();
        return std::static_pointer_cast<Expression>(castExpr);
    }
    else if (ctx->Identifier() && ctx->argumentList())
    {
        auto funcCallExpr = std::make_shared<FunctionCallExpression>();
        funcCallExpr->functionName = ctx->Identifier()->getText();

        for (auto argCtx : ctx->argumentList()->expression())
        {
            funcCallExpr->arguments.push_back(visit(argCtx).as<std::shared_ptr<Expression>>());
        }

        return std::static_pointer_cast<Expression>(funcCallExpr);
    }
    else if (ctx->IntegerLiteral())
    {
        auto literal = std::make_shared<LiteralExpression>();
        literal->value = ctx->IntegerLiteral()->getText();
        return std::static_pointer_cast<Expression>(literal);
    }
    else if (ctx->Identifier())
    {
        auto identifier = std::make_shared<IdentifierExpression>();
        identifier->name = ctx->Identifier()->getText();
        return std::static_pointer_cast<Expression>(identifier);
    }
    else if (ctx->expression().size() == 1)
    {
        return visit(ctx->expression(0));
    }

    return nullptr;
}
