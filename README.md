# pipex42_by_sdarci
It must behave exactly the same as the shell command below: $> &lt; file1 cmd1 | cmd2 > file2  ( my  program  execute as follows: ./pipex file1 cmd1 cmd2 file2 if there is no file 2 my program create it)

Суть проекта реализовать "трубу" консольную используя только разрешенные функции:
open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid

"Труба" = '|'  ($> &lt; file1 cmd1 | cmd2 > file2)
