#include "antlr4-runtime.h"
#include "SyroLexer.h"
#include "SyroParser.h"
#include "SyroASTVisitor.h"
#include "CodeGenerator.h"
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
        std::cerr << "Impossible d'ouvrir le fichier : " << argv[1] << std::endl;
        return 1;
    }

    antlr4::ANTLRInputStream input(stream);
    SyroLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    SyroParser parser(&tokens);

    antlr4::tree::ParseTree *tree = parser.program();

    SyroASTVisitor visitor;
    visitor.visit(tree);

    if (!visitor.ast)
    {
        std::cerr << "Erreur lors de la construction de l'AST" << std::endl;
        return 1;
    }

    CodeGenerator codeGen;
    std::string code = codeGen.generate(*visitor.ast);

    std::ofstream outFile(argv[2]);
    if (!outFile)
    {
        std::cerr << "Impossible d'ouvrir le fichier de sortie : " << argv[2] << std::endl;
        return 1;
    }
    outFile << code;

    std::cout << "Code C généré avec succès dans " << argv[2] << std::endl;

    return 0;
}
