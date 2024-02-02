parser grammar JollyShellParser;

options {
  tokenVocab=JollyShellLexer;
}

program          : pipeline
                 | LINEBREAK
                 ;
                 
pipeline         : simple_command
                 | pipeline PIPE simple_command
                 ;
                 
simple_command   : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
                 ;

cmd_name         : WORD
                 ;

cmd_word         : DOUBLE_QUOTED_STRING
                 | WORD
                 | VARIABLE
                 ;

cmd_prefix       : io_redirect
                 | cmd_prefix io_redirect
                 | ASSIGNMENT_WORD
                 | cmd_prefix ASSIGNMENT_WORD
                 ;

cmd_suffix       : io_redirect
                 | cmd_suffix io_redirect
                 | WORD
                 | cmd_suffix WORD
                 ;

io_redirect      : io_file
                 | IO_NUMBER io_file
                 | io_here
                 | IO_NUMBER io_here
                 ;

io_file          : REDIRECT_IN filename
                 | REDIRECT_OUT filename
                 | APPEND_OUT filename
                 | HEREDOC WORD
                 ;

io_here          : HEREDOC here_end
                 ;
                 
here_end         : WORD
                 ;
                                 
filename         : WORD
                 ;
                 
