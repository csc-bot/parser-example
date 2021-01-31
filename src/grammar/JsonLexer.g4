lexer grammar JsonLexer;

INTEGER
   : '0'
   | [1-9] [0-9]*
   ;

STRING: '"' ~ ["\n\r]* '"';

LBRACE: '{';
RBRACE: '}';
LBRACKET: '[';
RBRACKET: ']';
COMMA: ',';
COLON: ':';

WS: [ \n\t\r]+ -> skip;

INVALID: .;
