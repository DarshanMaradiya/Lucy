@echo off
win_bison "%1.y" -yd
win_flex "%1.l"
gcc y.tab.c lex.yy.c -w
a
