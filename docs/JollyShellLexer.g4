lexer grammar JollyShellLexer;

/*
  Represents a word, allowing letters, digits, and underscores, hyphens
*/
WORD            : [a-zA-Z_][a-zA-Z0-9-/]* ;

/* 
  A command name is a variable name, which never starts with a digit
*/
NAME            : [a-zA-Z_][a-zA-Z_]* ; 

/* 
  Assignment word, a variable assignment
*/
ASSIGNMENT_WORD : NAME '=' ;

IO_NUMBER        : [0-9]+;
PIPE             : '|';
REDIRECT_IN      : '<';
REDIRECT_OUT     : '>';
HEREDOC          : '<<';
APPEND_OUT       : '>>';
LINEBREAK        : '\n';
