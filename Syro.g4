grammar Syro;

program: statement* EOF;

statement: variableDeclaration
         | functionDeclaration
         | expressionStatement
         ;

variableDeclaration: 'var' Identifier (':' type)? '=' expression ';';

functionDeclaration: 'fn' Identifier parameterList ('->' type)? block;

parameterList: '(' (parameter (',' parameter)*)? ')';

parameter: Identifier ':' type;

block: '{' statement* '}';

expressionStatement: expression ';';

expression
    : expression op=('+' | '-' | '*' | '/') expression
    | '(' expression ')'
    | IntegerLiteral
    | StringLiteral
    | Identifier
    ;

type: Identifier;

Identifier: [a-zA-Z_][a-zA-Z0-9_]*;

IntegerLiteral: [0-9]+;

StringLiteral: '"' (~["\\] | '\\' .)* '"';

WS: [ \t\r\n]+ -> skip;

COMMENT: '//' ~[\r\n]* -> skip;
