lexer grammar JollyShellLexer;

WORD             : [a-zA-Z0-9_]+;
VARIABLE         : '$' WORD;
IO_NUMBER        : [0-9]+;
ASSIGNMENT_WORD  : '=';
PIPE             : '|';
REDIRECT_IN      : '<';
REDIRECT_OUT     : '>';
HEREDOC          : '<<';
APPEND_OUT       : '>>';
DOUBLE_QUOTED_STRING : '"' (~[\r\n\\] | '\\' .)* '"';
LINEBREAK        : '\n';
