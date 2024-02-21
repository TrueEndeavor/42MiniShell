// Shell.

//#include "user.h"
#include "fcntl.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/* PIPEX HEADERS */
void	ft_execute(char **argv, char **envp);
char	*ft_get_path(char *cmd, char **envp);
void	ft_error(char *str);
void	ft_free(char *path, char **cmd);
char	**ft_split(const char *s, char c);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_substr(const char *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	ft_check_arg(int argc, char **argv);

/*  */

// Parsed command representation
#define EXEC_CMD  1
#define REDIR_CMD 2
#define PIPE_CMD  3

#define MAXARGS 10

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;


typedef struct cmd {
  int type;
} t_cmd_P;

typedef struct execcmd {
  int type;
  char *argv[MAXARGS];
  char *eargv[MAXARGS];
} t_execcmd_P;

typedef struct redircmd {
  int type;
  struct cmd *cmd;
  char *file;
  char *efile;
  int mode;
  int fd;
} t_redircmd_P;

typedef struct pipecmd {
  int type;
  struct cmd *left;
  struct cmd *right;
} t_pipecmd_P;

int fork1(void);  // Fork but panics on failure.
void panic(char*);
struct cmd *parsecmd(char*);
struct cmd *parseline(char **ps, char *es);
void runcmd(struct cmd *cmd, char **envp);

void print_execcmd(t_cmd_P *cmd);
void print_pipecmd(t_cmd_P *cmd);
void print_cmd(t_cmd_P *cmd);

int
fork1(void)
{
  int pid;

  pid = fork();
  if(pid == -1)
    panic("fork");
  return pid;
}

/* ----LIBFT
----*/

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	count;

	len = strlen(src);
	if (!size || !src)
		return (len);
	count = 0;
	while (count < size - 1 && *src)
	{
		*dst++ = *src++;
		count++;
	}
	*dst = '\0';
	return (len);
}


size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		slen;
	size_t		dlen;
	size_t		count;

	count = 0;
	slen = strlen(src);
	if (!size)
		return (slen);
	dlen = strlen(dst);
	if (size <= dlen)
		return (size + slen);
	while ((dlen + count) < size - 1 && src[count])
	{
		dst[dlen + count] = src[count];
		count++;
	}
	dst[dlen + count] = '\0';
	return (dlen + slen);
}


char	*ft_strnstr(const char *big, const char	*little, size_t len)
{
	size_t		little_len;

	if (*little == '\0')
		return ((char *)big);
	else if (len == 0 || *big == '\0')
		return (NULL);
	little_len = strlen(little);
	while (len > 0 && len >= little_len && *big && *little)
	{
		if (strncmp(big, little, little_len) == 0)
			return ((char *)big);
		++big;
		--len;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total;

	if (!s1 || !s2)
		return (NULL);
	s1_len = strlen(s1);
	s2_len = strlen(s2);
	total = s1_len + s2_len;
	dst = malloc(total + 1 * sizeof(char));
	if (dst == NULL)
		return (NULL);
	memcpy(dst, s1, s1_len + 1);
	ft_strlcat(dst, s2, total + 1);
	return (dst);
}


static int	substr_count(char const *s, char c)
{
	size_t	count;
	int		char_match;

	count = 0;
	char_match = 0;
	while (*s)
	{
		if (*s == c)
			char_match = 0;
		else
		{
			if (!char_match)
			{
				char_match = 1;
				count++;
			}
		}
		s++;
	}
	return (count);
}

static int	substr_len(char const *s, char c)
{
	int			len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}	

static void	*free_mem(char **new, int i)
{
	while (i--)
	{
		if (new[i])
			free(new[i]);
	}
	free(new);
	return (NULL);
}



static int	split(char **new, char const *s, char c)
{
	int	i;
	int	subs_len;

	i = 0;
	subs_len = 0;
	while (*s)
	{
		while (*s == c)
			++s;
		if (*s)
		{
			subs_len = substr_len(s, c);
			new[i] = calloc((subs_len + 1), sizeof(char));
			if (!new[i])
			{
				free_mem(new, i);
				return (0);
			}
			ft_strlcpy(new[i], s, subs_len + 1);
			s = s + subs_len;
			i++;
		}
	}
	new[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**new;

	if (!s)
		return (NULL);
	new = calloc((substr_count(s, c) + 1), sizeof(char *));
	if (!new)
		return (NULL);
	if (!split(new, s, c))
		return (NULL);
	return (new);
}


/*--------------------
PIPEX - CODE - START
----------------------*/
void	ft_execute(char **cmd, char **envp)
{
	char	*path;
printf("ft_execute\n");
	if (cmd[0][0] == '/' || strncmp(cmd[0], "./", 2) == 0)
	{
	printf("calling execve\n");
		if (execve(cmd[0], cmd, envp) == -1)
		{
			ft_free(NULL, cmd);
			ft_error("execve failed\n");
		}
	}
	path = ft_get_path(cmd[0], envp);
	if (!path)
	{
	printf("no path\n");
		ft_free(path, cmd);
		ft_error("PATH not found\n");
	}
	if (execve(path, cmd, envp) == -1)
	{
		ft_free(path, cmd);
		ft_error("execve failed\n");
	}
}

char	*ft_get_path(char *cmd, char **envp)
{
	int		i;
	char	**possible_paths;
	char	*path;
	char	*complete_path;

	i = 0;
	while (envp && envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (NULL);
	path = envp[i] + 5;
	possible_paths = ft_split(path, ':');
	i = 0;
	while (possible_paths[i])
	{
		path = ft_strjoin(possible_paths[i++], "/");
		complete_path = ft_strjoin(path, cmd);
		free (path);
		if (access(complete_path, F_OK) == 0)
			return (complete_path);
		free(complete_path);
	}
	ft_free(NULL, possible_paths);
	return (NULL);
}

void	ft_free(char *path, char **cmd)
{
	int	i;

	i = 0;
	if (path)
		free(path);
	if (*cmd)
	{
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
	}
}

void	ft_error(char *str)
{
	dprintf(2, "%s\n", str);
	exit(EXIT_FAILURE);
}

/*--------------------
PIPEX - CODE - END
----------------------*/

void
runcmd(struct cmd *cmd,char **envp)
{
  int p[2];
  struct backcmd *bcmd;
  struct execcmd *ecmd;
  struct listcmd *lcmd;
  struct pipecmd *pcmd;
  struct redircmd *rcmd;

  if(cmd == 0)
    exit(0);

  switch(cmd->type){
  default:
    panic("runcmd");

  case EXEC_CMD:
    ecmd = (struct execcmd*)cmd;
    if(ecmd->argv[0] == 0)
      exit(0);
    ft_execute(ecmd->argv, envp);
    dprintf(2, "exec %s failed\n", ecmd->argv[0]);
    break;

  case REDIR_CMD:
    rcmd = (struct redircmd*)cmd;
    close(rcmd->fd);
    if(open(rcmd->file, rcmd->mode, 0777) < 0){
      dprintf(2, "open %s failed\n", rcmd->file);
      exit(0);
    }
    runcmd(rcmd->cmd, envp);
    break;

  case PIPE_CMD:
    pcmd = (struct pipecmd*)cmd;
    if(pipe(p) < 0)
      panic("pipe");
    if(fork1() == 0){
      close(1);
      dup(p[1]);
      close(p[0]);
      close(p[1]);
      runcmd(pcmd->left, envp);
    }
    if(fork1() == 0){
      close(0);
      dup(p[0]);
      close(p[0]);
      close(p[1]);
      runcmd(pcmd->right, envp);
    }
    close(p[0]);
    close(p[1]);
    wait(0);
    wait(0);
    break;
  }
  exit(0);
}

char*
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
getcmd(char *buf, int nbuf)
{
  dprintf(2, "$ ");
  memset(buf, 0, nbuf);
  gets(buf, nbuf);
  if(buf[0] == 0) // EOF
    return -1;
  return 0;
}

int
main(int ac, char **av, char **envp)
{
  (void *)av;
  static char buf[100];
  int fd;

  // Ensure that three file descriptors are open.
  while((fd = open("console", O_RDWR)) >= 0){
    if(fd >= 3){
      close(fd);
      break;
    }
  }

  // Read and run input commands.
  while(getcmd(buf, sizeof(buf)) >= 0){
    if(buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' '){
      // Chdir must be called by the parent, not the child.
      buf[strlen(buf)-1] = 0;  // chop \n
      if(chdir(buf+3) < 0)
        dprintf(2, "cannot cd %s\n", buf+3);
      continue;
    }
    if(fork1() == 0)    
      runcmd(parsecmd(buf), envp);
    wait(0);    
  }
  exit(1);
}

void
panic(char *s)
{
  dprintf(2, "%s\n", s);
  exit(1);
}

//PAGEBREAK!
// Constructors

struct cmd*
execcmd(void)
{
  struct execcmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = EXEC_CMD;
  return (struct cmd*)cmd;
}

struct cmd*
redircmd(struct cmd *subcmd, char *file, char *efile, int mode, int fd)
{
  struct redircmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = REDIR_CMD;
  cmd->cmd = subcmd;
  cmd->file = file;
  cmd->efile = efile;
  cmd->mode = mode;
  cmd->fd = fd;
  return (struct cmd*)cmd;
}

struct cmd*
pipecmd(struct cmd *left, struct cmd *right)
{
  struct pipecmd *cmd;

  cmd = malloc(sizeof(*cmd));
  memset(cmd, 0, sizeof(*cmd));
  cmd->type = PIPE_CMD;
  cmd->left = left;
  cmd->right = right;
  return (struct cmd*)cmd;
}

//PAGEBREAK!
// Printers

void print_execcmd(t_cmd_P *cmd)
{
    t_execcmd_P *execCmd = (t_execcmd_P *)cmd;
    printf("Type: EXEC_CMD\n");
    for (int i=0; i < MAXARGS; i++)
        printf("argv: %s\n", execCmd->argv[i]);
    // Add any additional fields specific to t_execcmd_P if needed
}

void print_redircmd(t_cmd_P *cmd)
{
    t_redircmd_P *redirectCmd = (t_redircmd_P *)cmd;
    printf("Type: REDIR_CMD\n");
    printf("File: %s\n", redirectCmd->file);
    printf("Mode: %d\n", redirectCmd->mode);
    printf("File Descriptor: %d\n", redirectCmd->fd);
    // Recursively print the sub-command if it's not NULL
    if (redirectCmd->cmd != NULL) {
        printf("Sub-command:\n");
        print_cmd(redirectCmd->cmd);
    }
}

void print_pipecmd(t_cmd_P *cmd)
{
    t_pipecmd_P *pipeCmd = (t_pipecmd_P *)cmd;
    printf("Type: PIPE_CMD\n");
    printf("Left command:\n");
    print_cmd(pipeCmd->left);
    printf("Right command:\n");
    print_cmd(pipeCmd->right);
}

void print_cmd(t_cmd_P *cmd) 
{
    if (cmd == NULL) {
        printf("Command is NULL\n");
        return;
    }
    printf("command type = %d\n",cmd->type);
    switch (cmd->type) {
        case EXEC_CMD:
            print_execcmd(cmd);
            break;
        case REDIR_CMD:
            print_redircmd(cmd);
            break;
        case PIPE_CMD:
            print_pipecmd(cmd);
            break;
        default:
            printf("Unknown command type\n");
            break;
    }
}

//PAGEBREAK!
// Parsing

char whitespace[] = " \t\r\n\v";
char symbols[] = "<|>&;()";

int
gettoken(char **ps, char *es, char **q, char **eq)
{
  char *s;
  int ret;

  s = *ps;
  while(s < es && strchr(whitespace, *s))
    s++;
  if(q)
    *q = s;
  ret = *s;
  switch(*s){
  case 0:
    break;
  case '|':
  case '(':
  case ')':
  case ';':
  case '&':
  case '<':
    s++;
    break;
  case '>':
    s++;
    if(*s == '>'){
      ret = '+';
      s++;
    }
    break;
  default:
    ret = 'a';
    while(s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
      s++;
    break;
  }
  if(eq)
    *eq = s;

  while(s < es && strchr(whitespace, *s))
    s++;
  *ps = s;
  return ret;
}

int
peek(char **ps, char *es, char *toks)
{
  char *s;

  s = *ps;
  while(s < es && strchr(whitespace, *s))
    s++;
  *ps = s;
  return *s && strchr(toks, *s);
}

struct cmd *parsepipe(char**, char*);
struct cmd *parseexec(char**, char*);
struct cmd *nulterminate(struct cmd*);

struct cmd*
parsecmd(char *s)
{
  char *es;
  struct cmd *cmd;

  es = s + strlen(s);
  cmd = parseline(&s, es);
  peek(&s, es, "");
  if(s != es){
    dprintf(2, "leftovers: %s\n", s);
    panic("syntax");
  }
  nulterminate(cmd);
printf("######END OF parsecmd######\n");
print_cmd(cmd);
  return cmd;
}

struct cmd*
parseline(char **ps, char *es)
{
  printf ("###entering parseline###\n");
  struct cmd *cmd;

  cmd = parsepipe(ps, es);

  printf ("###exiting parseline###\n");
  return cmd;
}

struct cmd*
parsepipe(char **ps, char *es)
{
  printf ("###entering parsepipe###\n");
  struct cmd *cmd;

  cmd = parseexec(ps, es);
  if(peek(ps, es, "|")){
    gettoken(ps, es, 0, 0);
    cmd = pipecmd(cmd, parsepipe(ps, es));
  }
  printf ("###exiting parsepipe###\n");
  return cmd;
}

struct cmd*
parseredirs(struct cmd *cmd, char **ps, char *es)
{
  int tok;
  char *q, *eq;

    printf ("###entering parseredir###\n");
/* printf("current ps: %s\n", *ps); 
printf("current es: %s\n", es);  */
  
  while(peek(ps, es, "<>"))
  {
/* printf("after peek ps: %s\n", *ps); 
printf("after peek es: %s\n", es);  */
 
    tok = gettoken(ps, es, 0, 0);
printf("after gettoken 1 ps: %s\n", *ps); 
printf("after gettoken 1 es: %s\n", es); 
  

    if(gettoken(ps, es, &q, &eq) != 'a')
      panic("missing file for redirection");
/* printf("after gettoken 2 ps: %s\n", *ps); 
printf("after gettoken 2 es: %s\n", es);  */
    switch(tok){
    case '<':
      cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
      break;
    case '>':
      cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT, 1);
      break;
    case '+':  // >>
      cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT, 1);
      break;
    }
  }
  print_redircmd(cmd);
  printf ("###exiting parseredir###\n");
  return cmd;
}

struct cmd*
parseexec(char **ps, char *es)
{
  char *q, *eq;
  int tok, argc;
  struct execcmd *cmd;
  struct cmd *ret;

    printf ("###entering parseexec###\n");
  ret = execcmd();
  cmd = (struct execcmd*)ret;

  argc = 0;
  ret = parseredirs(ret, ps, es); // calling redirects - 1
  while(!peek(ps, es, "|)&;")){
    if((tok=gettoken(ps, es, &q, &eq)) == 0)
    {
      break;
    }
 
    if(tok != 'a')
      panic("syntax");
    cmd->argv[argc] = q;
    cmd->eargv[argc] = eq;
    argc++;
    if(argc >= MAXARGS)
      panic("too many args");
//printf("maybe next (!) ps: %s\n", *ps);      
    ret = parseredirs(ret, ps, es); // calling redirects - 2+
  }
  cmd->argv[argc] = 0;
  cmd->eargv[argc] = 0;
  printf ("###exiting parseexec###\n");
  return ret;
}

// NUL-terminate all the counted strings.
struct cmd*
nulterminate(struct cmd *cmd)
{
  int i;
  struct backcmd *bcmd;
  struct execcmd *ecmd;
  struct listcmd *lcmd;
  struct pipecmd *pcmd;
  struct redircmd *rcmd;

  if(cmd == 0)
    return 0;

  switch(cmd->type){
  case EXEC_CMD:
    ecmd = (struct execcmd*)cmd;
    for(i=0; ecmd->argv[i]; i++)
      *ecmd->eargv[i] = 0;
    break;

  case REDIR_CMD:
    rcmd = (struct redircmd*)cmd;
    nulterminate(rcmd->cmd);
    *rcmd->efile = 0;
    break;

  case PIPE_CMD:
    pcmd = (struct pipecmd*)cmd;
    nulterminate(pcmd->left);
    nulterminate(pcmd->right);
    break;

  }
  return cmd;
}
