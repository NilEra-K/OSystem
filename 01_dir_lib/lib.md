## 如何制作一个静态库

使用 `gcc -c filename.c` 可以直接生成目标文件, 即生成 `filename.o` 文件

**计算功能 :** `calc{calc.h | calc.c} -> calc.o` <p>
**显示功能 :** `show{show.h | show.c} -> show.o` <p>
**制作静态数学库 :** `calc.o + show.o = libmath.a` <p>
**打包该动态库需要命令 :** `ar -r libmath.a calc.o show.o`
