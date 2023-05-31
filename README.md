# OSystem

## 🎇UC 
使用 C语言在操作系统 Unix上的用户编程, Unix系统向用户提供了大量的接口, 用户通过系统提供的接口, 可以使用操作系统提供的服务

## 🎇环境变量
- 每个进程都有一张自己的环境变量表, 表中每个条目都是形如 `"Key=Value"` 形式的环境变量
- 进程可以通过环境变量访问计算机的资源
- 在终端下输入 `env`命令, 可以查看环境变量列表
- 通过 `echo $name` 命令可以查看名为 `name` 的环境变量的值
- 环境变量分为两大类: 包括 ***全局环境变量*** 和 ***局部环境变量***
  - 全局环境变量: 当前 Shell和其子程序都是可见的
  - 局部环境变量: 只有当前 Shell可见
  - 可用 `export name` 将局部环境变量设置成全局环境变量
  - 可用 `unset name` 删除环境变量
- 环境变量的添加: 在终端中输入 `NAME=PATH` 命令即可向 ***当前进程*** 添加名为 `NAME`,值为 `PATH` 的环境变量, 如果环境变量已经存在, 就修改其值
- ⭐ 特别注意 `=` 左右 ***不能加空格***
  - 例如 `NAME = PATH` 就是错误的写法
- 常见的环境变量:
  - **PATH 环境变量:** 
    - 个人 Ubuntu下的 PATH路径: `/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin`
    - 可以使用 `echo $PATH` 进行查看
    - 该环境变量所记录的是bash进程对命令的检索路径
    - 格式为 " **:** " 分割的多个路径, 当在 bash下输入命令的时候, 首先在第一个路径下找该命令的可执行程序, 找到就执行, 不再向后寻找, 找不到就向后寻找, 直到找到为止, 如果最后一个路径找不到, 就提示该命令不能找到的错误信息
    - 使用 `PATH=$PATH:.` 表示在原有路径上添加 `:.` , 即查找在执行命令时添加查找当前目录(仅在当前进程有效)
  - 如果没有特殊的操作, 对环境变量的设置仅对带你给钱的 Shell进程有效, 开启新的终端, 之前的操作不会保留
  - 在 ***用户主目录*** 下有名为 `.bashrc` 的脚本文件, 每次 _bash_ 进程启动前, 都会执行脚本文件的内容
  - 如果希望环境变量的设置对每个 _bash_ 进程都有效, 可以将环境变量的设置写在该脚本文件中
  - 执行 `source ~/.bashrc` 命令, 可以使文件立即生效
  - `nilera@nilera-virtual-machine:~$` 这个是 Linux中的提示符, 受 `PS` 路径控制, 例如:使用 `PS1='\W\$'` 命令可以只显示当前目录

## 🎇环境变量表
- 每个进程都有一张独立的环境变量表, 其中的每个条目都是一个形如 `"Key=Value"` 形式的环境变量
- 所谓的环境变量表就是一个 ***以 NULL指针结束的字符指针数组***, 其中的每个元素都是一个字符指针, 指向一个以空字符结尾的字符串, 该字符串就是形如 `"Key=Value"` 形式的环境变量, 该指针数组的地址保存在全局变量 `environ` 中

## 🎇涉及内容:
- 库文件的制作和使用
- 内存管理
- 文件管理和文件系统
- 进程管理
- 信号(软中断)
- 进程间通讯
- 网络管理
- 线程管理

### ✨ 库文件的制作和使用
**单一模型:** 将程序所有的功能全部实现与一个单一源文件的内部, 编译时间长, 不易于维护和升级, 不易于协作开发<p>

**分离模型:** 将程序的不同功能划分到不同的源文件中, 缩短编译时间, 易于协作开发, 不易于管理多个目标文件<p>

**什么是库文件:** 对多个目标文件的管理比较麻烦, 将多个目标文件统一整合成一个库文件<p>

***Q&A :***<p>
**_Q :_** 为什么要把一个程序分成多个源文件, 并由每个元文件编译生成独立的目标文件? <p>
**_A :_** 易于维护, 便于协作 <p>
**_Q :_** 为什么要把多个目标文件合并成一个库文件<p>
**_A :_** 易于使用, 方便复用<p>

可以简单的把库文件看成一种代码仓库, 他提供给使用者一些可以拿来使用的变量、函数或类<p>
库文件一般指计算机上的一类文件, 分 ***静态库*** 和 ***动态库*** 两种
- 静态库
  - 静态库的本质就是将多个目标文件打包成一个文件
  - 链接静态库就是将库中被调用的代码复制到调用模块中
  - 静态库的拓展名为 `.a` , 例如 `libxxx.a` 习惯在库前加 `lib` 表明其为一个库文件
  - 如何制作一个静态库 --> 查看 `./01_dir_lib/static_lib` 文件夹内容

- 动态库
  - 动态库和静态库不同, 链接动态库不需要将被调用的函数代码复制到包含调用代码的可执行文件中, 相反链接器会在调用语句处嵌入一段指令, 在该程序执行到这段指令时, 会加载该动态库并寻找被调用函数的入口地址, 并且执行该指令
  - 如果动态库中的代码同时被多个进程所用, 动态库在内存的实例仅需一份, 为所有使用该库的进程所共享, 因此动态库又叫共享库
  - 动态库的拓展名为 `.so` , 例如 `libxxx.so` 

- 静态库和动态库比较
  - 动态库: 占用内存小, 相对较慢, 程序执行必须依赖库
  - 静态库: 占用内存大, 相对较快, 程序执行不必依赖库
  - 实际开发中还是使用动态库更多, 因为动态库可以 _**更方便的**_ 进行产品的维护和迭代, 而静态库较为麻烦

- 动态库的动态加载
  - 在程序执行的过程中, 开发人员可以动态加载共享库(什么时候用什么时候加载, 减少内存资源的浪费)
  - 在程序中动态加载的动态库需要调用一组特殊的函数, 他们被声明于一个专门的头文件中, 并在一个独立的库中予以实现
  - 使用这组函数需要包含 `#include <dlfcn.h> `头文件, 并链接该库
  - **辅助工具 :**
    > 查看符号表 : nm <p>
    列出目标文件、可执行程序、静态库或共享库中的符号<p>
    例如 : `nm libmath.a`

    > 查看依赖 : ldd <p>
    查看可执行文件或者共享库所依赖的共享库 <p>
    例如 : `ldd a.out`


**相关函数:**<p>
_**`void* dlopen(char const* filename, int flag)`**_
  - 功能 : 将共享库载入内存并获得其访问句柄
  - 参数 : <p>
  **filename :** 动态库路径, 若只给文件名不带目录, 则根据 `LD_LIBRARY_PATH` 环境变量的值搜索动态库<p>
  **flag :** 加载方式, 可取以下值: <p>
  `RTLD_LAZY` - 延迟加载, 使用动态库中符号时才真正加载进内存 <p>
  `RTLD_NOW` - 立即加载 <p>
  **返回值 :** 成功返回动态库访问句柄, 失败返回 NULL <p>
  **句柄 :** 句柄唯一标识了系统内核所维护的共享库对象, 将作为后续幻术调用的参数

_**`void* dlsym(void* handle, char const* symbol)`**_
- 功能 : 从已被加载的动态库中获得特定名称的符号地址
- 参数 : <p>
  **handle :** 动态库访问句柄 <p>
  **sysbol :** 符号名 <p>
  **返回值 :** 成功返回给定符号的地址, 失败返回 NULL <p>
  该函数所返回的指针为 `void*` 类型, 需要构造与实际目标相一致类型的指针, 才能使用 <p>

_**`void* dlclose(void* handle)`**_
- 功能 : 从内存中卸载动态库
- 参数 : <p>
  **handle :** 动态库访问句柄 <p>
  **返回值 :** 成功返回 0, 失败返回非 0 <p>
- 所卸载的共享库并不一定真的从内存中立即消失, 因为其他程序可能还需要使用该库
- 只有所有使用该库的程序都显式或隐式地卸载了该库, 该库所占用的空间才会得到真正的释放
- 无论所卸载的共享库是否阵阵被释放, 传递给 dlclose函数的句柄都会在该函数成功返回后立即失效 <p>

_**`char* dlerror(void)`**_
- 功能 : 获取正在加载、使用和卸载共享库过程中所发生的错误
- **返回值 :** 有错误则返回指向错误信息字符串的指针, 否则返回 NULL

- ```
  if(!handle){
      fprintf(stderr, "dlopen: %s\n", dlerror());
      exit(EXIT_FAILURE);
  }
  ```
**错误处理 :** <p>
- 通过错误号了解具体的错误原因
  - 系统定义的整数类型全局变量 errno中存储了最近一次系统调用的错误编号
  - 头文件 `errno.h` 包含了对errno全局变量的外部生命和各种错误号的宏定义
  - `/usr/include/errno.h`
  - `/usr/include/asm-generic/errno.h`
  - `/usr/include/asm-generic/errno-base.h`

_**`char* stderror(int errnum)`**_ <p>
- 使用时需引用 `#include <string.h>` 头文件
- 功能 : 将整数形式的错误号转换为有意义的字符串
- 参数 : <p>
  **errnum :** 错误号 <p>
  **返回值 :** 返回与参数错误号对应的描述字符串 <p>

_**`void perror(char const* tag)`**_ <p>
- 使用时需引用 `#include <stdio.h>` 头文件
- 功能 : 在**标准出错设备**上打印最近一次函数调用的错误信息 <p>
- 参数 : <p>
  **tag :** 用户自己制定的提示内容, 输出时, 会自动在该提示内容和错误信息之间添加冒号进行分隔

---

### ✨ 内存管理
**程序的运作** <p>
我们写好的代码经过编译后得到可执行文件 `a.out` <p>
`a.out` 是二进制指令的集合, 其内容经操作系统的管理调度被加载到物理内存, CPU在从物理内存中读取指令执行<p>
程序被加载到物理内存, 才能被 CPU所执行, 物理内存的空间有限, 当难以满足使用需求时, 会把一些长期闲置的代码和数据从物理内存缓存到磁盘上, 即**页面换出**, 一旦需要使用那些代码的数据, 再把他们从磁盘上恢复到物理内存中, 即**页面换入** <p>
磁盘上用来缓存物理内存数据的部分称为**交换分区** <p>
磁盘的读写速率要**远慢于**物理内存, 大量的数据换入和换出会导致电脑卡顿 <p>

**物理内存和虚拟内存** <p>
我们在程序中所看到或者使用的地址, 并非是真实的物理内存的地址, 而是经由系统内核的内存管理系统管理后看到的虚拟地址 <p>
虚拟地址和物理地址之间存在映射对应关系 - 系统会维护一张内存映射表 - 物理内存(???)**透明**, 虚拟地址(###)被给予程序员 <p>

| 物理内存 | 虚拟内存 |
| :-: | :-: |
| ??? | ### |

内存管理系统一方面**保证物理内存的安全**, 避免物理内存被直接操作, 同时也**降低了程序员的编码难度** <p>
CPU中包含一个名为 `MMU(Memory Management Unit)`的内存管理单元, 负责完成虚拟地址和物理地址之间的转换 <p>

**虚拟地址空间**




