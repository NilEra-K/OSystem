## 如何制作一个静态库

下面以制作一个静态数学库 `libmath.a` 为例<p>
- 使用 `gcc -c filename.c` 可以直接生成目标文件, 即生成 `filename.o` 文件
- **计算功能 :** `calc{calc.h | calc.c} -> calc.o` <p>
- **显示功能 :** `show{show.h | show.c} -> show.o` <p>
- **制作静态数学库 :** `calc.o + show.o = libmath.a` <p>
- **打包该动态库需要命令 :** `ar -r libmath.a calc.o show.o` <p>
- **如何使用一个静态库 :** 使用 `gcc main.c libmath.a` 进行编译 <p>
- **如何查看静态库中的函数 :** 使用 `nm libmath.a` 命令进行查看 <p>
- 编译并链接静态库
    - 直接链接静态库 `gcc main.c libmath.a`
    - 用 `-l` 参数指定库名, 用 `-L` 参数制定库路径 `gcc main.c -lmath -L` <p>
    **特别注意 :** 这里的 `-lmath` 是 `libmath.a` 去掉前缀 `lib` 和后缀 `.a` 得到的名字
    - 用 `-l` 参数指定库名, 用 `LIBRARY_PATH` 环境变量指定库路径 <p>
    `LIBRARY_PATH = $LIBRARY_PATH:..` <p>
    `export LIBRARY_PATH=$LIBRARY_PATH:.` <p>
    `gcc main.c -l math`


## 如何制作一个动态库
下面以制作一个动态数学库为例
- 编译成目标文件: <p>
`gcc -c -fpic calc.c` <p>
`gcc -c -fpic show.c` <p>
    - `PIC` (Position Independent Code, 位置无关代码), 调用代码通过相对地址标识调用代码的位置, 模块中的指令与该模块被加载到内存中的位置无关
    - `-fPIC` : 大模式, 生成代码比较大, 运行速度比较慢, 所有平台都支持
    - `-fpic` : 小模式, 生成代码比较小, 运行速度比较快, 仅部分平台支持

- 打包成动态库: <p>
`gcc -shared calc.o show.o -o libmath.so`
- 在未配置环境变量 **`LD_LIBRARY_PATH`** 时, 直接用 `gcc main.c libmath.so` 进行编译会导致出现 `error while loading shared libraries: libmath.so: cannot open shared object file: No such file or directory` 错误, 表示找不到相关的动态库
- 使用 `LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.` 命令进行环境变量的配置 <p>
- 使用 `export LD_LIBRARY_PATH` 命令局部环境变量声明为全局环境变量

鲜牛奶年年男男女女男男女女男男女女男男女女男男女女男男女女嗯一直