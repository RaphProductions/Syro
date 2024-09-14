TARGET = syro
SRC_DIR = source
GEN_DIR = generated
GRAMMAR = Syro.g4
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(GEN_DIR)/SyroLexer.cpp $(GEN_DIR)/SyroParser.cpp $(GEN_DIR)/SyroBaseVisitor.cpp

CXX = g++
CXXFLAGS = -std=c++11 -I/usr/include/antlr4-runtime -I$(GEN_DIR)
LDFLAGS = -lantlr4-runtime

ANTLR = antlr4
ANTLRFLAGS = -Dlanguage=Cpp -visitor

all: $(TARGET)

$(GEN_DIR)/SyroLexer.cpp $(GEN_DIR)/SyroParser.cpp $(GEN_DIR)/SyroBaseVisitor.cpp: $(GRAMMAR)
	@mkdir -p $(GEN_DIR)
	$(ANTLR) $(ANTLRFLAGS) -o $(GEN_DIR) $(GRAMMAR)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

clean:
	@rm -rf $(GEN_DIR)
	@rm -f $(TARGET)

distclean: clean
	@rm -f $(TARGET)
