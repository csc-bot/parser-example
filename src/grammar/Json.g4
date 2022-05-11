grammar Json;

document
   : element
   ;

element
   : object
   | array
   | number
   | string
   ;

object
   : LBRACE RBRACE
   | LBRACE member (COMMA member)* RBRACE
   ;

member
   : STRING COLON element
   ;

array
   : LBRACKET RBRACKET
   | LBRACKET element (COMMA element)* RBRACKET
   ;

number
   : INTEGER
   ;

string
   : STRING
   ;

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
