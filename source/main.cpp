#include "antlr4-runtime.h"
#include "../generated/SyroLexer.h"
#include "../generated/SyroParser.h"
#include "SyroASTVisitor.h"
#include "CodeGenerator.h"
#include "SyroErrorListener.h"
#include <iostream>
#include <fstream>

int main(int argc, const char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: syro <source_file.syro> <output_file.c>" << std::endl;
        return 1;
    }

    std::ifstream stream(argv[1]);
    if (!stream)
    {
        std::cerr << "Unable to open file: " << argv[1] << std::endl;
        return 1;
    }

    antlr4::ANTLRInputStream input(stream);
    SyroLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    SyroParser parser(&tokens);

    SyroErrorListener errorListener;
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);

    antlr4::tree::ParseTree *tree = parser.program();

    if (errorListener.hasErrors)
    {
        std::cerr << "Compilation failed due to syntax errors." << std::endl;
        return 1;
    }

    SyroASTVisitor visitor;
    visitor.visit(tree);

    if (!visitor.ast)
    {
        std::cerr << "Error while constructing the AST" << std::endl;
        return 1;
    }

    CodeGenerator codeGen;
    std::string code = codeGen.generate(*visitor.ast);

    std::ofstream outFile(argv[2]);
    if (!outFile)
    {
        std::cerr << "Unable to open output file: " << argv[2] << std::endl;
        return 1;
    }
    outFile << code;

    std::cout << "C code successfully generated in " << argv[2] << std::endl;

    return 0;
}
