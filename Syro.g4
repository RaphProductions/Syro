grammar Syro;

program: statement* EOF;

statement:
	variableDeclaration
	| functionDeclaration
	| expressionStatement
	| returnStatement;

returnStatement: 'return' expression? ';';

variableDeclaration:
	'var' Identifier (':' type)? '=' expression ';';

functionDeclaration:
	'fn' Identifier parameterList (':' type)? block;

parameterList: '(' (parameter (',' parameter)*)? ')';

parameter: Identifier ':' type;

block: '{' statement* '}';

expressionStatement: expression ';';

expression:
	expression op = ('*' | '/' | '+' | '-') expression
	| '(' expression ')'
	| '@cast' '<' type '>' '(' expression ')'
	| Identifier '(' argumentList? ')'
	| IntegerLiteral
	| StringLiteral
	| Identifier;

argumentList: expression (',' expression)*;

type: IntegerType | Identifier;

IntegerType:
	'i8'
	| 'i16'
	| 'i32'
	| 'i64'
	| 'isize'
	| 'u8'
	| 'u16'
	| 'u32'
	| 'u64'
	| 'usize';

Identifier: [a-zA-Z_][a-zA-Z0-9_]*;

IntegerLiteral: [0-9]+;

StringLiteral: '"' (~["\\] | '\\' .)* '"';

WS: [ \t\r\n]+ -> skip;

COMMENT: '//' ~[\r\n]* -> skip;