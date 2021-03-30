# For Windows:

`compile.bat` is running 4 commands

1) win_bison <file_name>.y -yd
2) win_flex <file_name>.l
3) gcc y.tab.c lex.yy.c -w
4) a

These commands will compile the files and then it will be ready to take input, that is our program written according to Lucy Syntax.

To compile the files, do as follow:
1) Add the path of the folder 'win_flex_bison' (`..../Lucy/Tools/win_flex_bison`) to the environment, so that we will be able to access the `compile.bat` from any directory
2) Open the cmd and nevigate to the directory where grammar file (`Lucy.y`) and lex file (`Lucy.l`) is.
3) Run the command `compile <file_name>`, e.g. `compile Lucy` and all the 4 commands will run. If compiled successfully, it will be waiting for the input and might show some conflicts if exist, otherwise will show warings/errors.

Note: Here We need to keep the name of grammar file and lex file same. In repository it is Lucy.y and Lucy.l respectively. Otherwise the `compile.bat` won't work and we have to type those all 4 commands turn by turn.

