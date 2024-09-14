antlr4 -Dlanguage=Cpp -visitor Syro.g4
# g++ -std=c++11 -I/usr/include/antlr4-runtime -o syro main.cpp SyroLexer.cpp SyroParser.cpp SyroBaseListener.cpp SyroListener.cpp -lantlr4-runtime
# g++ -std=c++11 -I/usr/include/antlr4-runtime -o syro main.cpp SyroLexer.cpp SyroParser.cpp SyroBaseVisitor.cpp SyroVisitor.cpp AST.cpp -lantlr4-runtime
g++ -std=c++11 -I/usr/include/antlr4-runtime -o syro main.cpp SyroLexer.cpp SyroParser.cpp SyroBaseVisitor.cpp SyroASTVisitor.cpp AST.cpp CodeGenerator.cpp -lantlr4-runtime
# g++ -std=c++11 -I/usr/local/include/antlr4-runtime -o syro main.cpp SyroLexer.cpp SyroParser.cpp SyroBaseVisitor.cpp SyroASTVisitor.cpp AST.cpp CodeGenerator.cpp -lantlr4-runtime
