parser grammar JollyShellParser;

options {
  tokenVocab=JollyShellLexer;
}

/*****************************************************************************
                              JollyShell Parser Grammar
                              
                           Influenced by Bash Shell Grammar
                        
pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_10
Keep referring this link for the comments below with reference to rules
******************************************************************************/


/*-----------------------------------------------------------------------------
  A prompt is a pipeline or a line break
-----------------------------------------------------------------------------*/
prompt           : pipeline                       //PR: pipeline
                 | LINEBREAK                      //PR: linebreak
                 ;
                 
/*-----------------------------------------------------------------------------
  A pipeline is either a simple command or 
  a pipeline followed by a pipe and a simple command 
-----------------------------------------------------------------------------*/
pipeline         : simple_command                 //PR: simple_command
                 | pipeline PIPE simple_command   //PR: pipeline_recursive
                 ;
                 
/*-----------------------------------------------------------------------------
  A simple command can have 
  a command prefix (redirections, variable assignements)
  a command word (alphanumeric, symbols)
  and a command suffix (arguments, redirections)
-----------------------------------------------------------------------------*/
simple_command   : cmd_prefix cmd_word cmd_suffix //PR: prefix_cmd_suffix
                 | cmd_prefix cmd_word            //PR: prefix_cmd
                 | cmd_prefix                     //PR: prefix_only
                 | cmd_name cmd_suffix            //PR: cmd_suffix
                 | cmd_name                       //PR: single_cmd
                 ;
/*-----------------------------------------------------------------------------
??
-----------------------------------------------------------------------------*/
cmd_name         : WORD       /* Apply rule 7a */ //PR: cmd_name
                 ;
                 
/*-----------------------------------------------------------------------------
  A word is usually a command or its arguments or redirections, filenames
-----------------------------------------------------------------------------*/
cmd_word         : WORD       /* Apply rule 7b */ //PR: cmd_word
                 ;
                 
/*-----------------------------------------------------------------------------
  A command prefix can consist of i/O redirections and variable assignment
  It can never by another command itself (unless ; or && are supported)
-----------------------------------------------------------------------------*/
cmd_prefix       : io_redirect                    // PR: io_redirect_beginning
                 | cmd_prefix io_redirect         // PR: prefix_io_redirect
                 | ASSIGNMENT_WORD                // PR: variable
                 | cmd_prefix ASSIGNMENT_WORD     // PR: prefix_variable
                 ;

/*-----------------------------------------------------------------------------
  A command suffix can consist of arguments and i/o redirections
  It can never be another command itself (unless ; or && are supported)
  
  Example for:    WORD (arguments)
      ls          -l
  
  Example for:    cmd_suffix WORD (arguments)
      echo        "Command 1" ls -l echo "Command 2"
      ls          -l /home/user/Documents
-----------------------------------------------------------------------------*/
cmd_suffix       : io_redirect                    // PR: io_redirect_end
                 | cmd_suffix io_redirect         // PR: suffix_io_redirect
                 | WORD                           // PR: suffix_only
                 | cmd_suffix WORD                // PR: suffix_arguments
                 ;
                 
/*-----------------------------------------------------------------------------
  I/O redirect can be a file or a combination with an I/O number
-----------------------------------------------------------------------------*/
io_redirect      : io_redirect_file               //PR: io_redirection_to_file
                 | IO_NUMBER io_redirect_file     //PR: io_numbered_redirection
                 | IO_NUMBER io_here_doc          //PR: io_numbered_here_doc
                 | io_here_doc                    //PR: here_doc                 
                 ;
                 
/*-----------------------------------------------------------------------------
  I/O file can be input, output, or append with a filename
  Note:
  In Bash, a heredoc typically does not involve a file_name. So it is left out
-----------------------------------------------------------------------------*/
io_redirect_file : REDIRECT_IN file_name          //PR: redirect_in_to_file
                 | REDIRECT_OUT file_name         //PR: redirect_out_to_file
                 | APPEND_OUT file_name           //PR: append_out_to_file
                 ;
                 
/*-----------------------------------------------------------------------------
  Here-doc is specified by the '<<' operator followed by a delimiter
-----------------------------------------------------------------------------*/
io_here_doc      : HEREDOC here_end               //PR: io_here_doc
                 ;

/*-----------------------------------------------------------------------------
  Here-doc delimiter rule
-----------------------------------------------------------------------------*/
here_end         : WORD                           //PR: here_end
                 ;
                                 
/*-----------------------------------------------------------------------------
  Redirection to or from filename
-----------------------------------------------------------------------------*/
file_name        : WORD                           //PR: file_name
                 ;
                 