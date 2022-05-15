# 魔方大作业文档
## Update
底层十字目前采用暴力算法实现，接口在namespace BruteCross的BruteCross函数，用时可以忽略不计
## 分工
### 1
- 底层角块归位
- 顶层十字
### 2
- 第二层棱块归位
- 顶面还原
### 3
- 顶层角块
- 顶层棱块
- 编写数据生成器
- 编写测试程序

## 目前想到的任务
- 实现12个旋转函数
- 底层十字
- 底层角块归位
- 第二层棱块归位
- 顶层十字
- 顶面还原
- 顶层角块归位
- 顶层棱块归位
- 编写测试程序
- 编写数据生成器
## 实现进度
### 已完成的任务
- 实现旋转函数
- 编写数据生成器
- 通过搜索法寻找底层十字

由于搜索寻找十字可能超时，可能需要写一个朴素的底层十字算法。

## 实现约定
### 关于基础数据结构的约定
魔方的状态保存在一个三维char数组中，形式与OJ上的测试题目相同

1-6个面分别为前后左右上下

数组下标从1开始，每个cube[i]中保存一个3*3矩阵
### 关于预编译指令
预编译指令
```cpp
#define RotateDebug // 旋转debug代码
#define CrossDebug  // Cross的debug代码
```
## 一些数组说明
```cpp
// 用于保存各种操作
char opts[] = "RrUuFfDdLlBb";
// 每个面的标准颜色
char StandardColor[] = "GBORWY";
```
## 已经实现的功能及其说明

### 输出函数

```cpp
void CrossTester()
```
输出样例如下

GGB BWY BBO YRR RRW YYY 
GGW BBW OOO BRO RWG YYY 
GGG BBR GOO RRO WWO WYW 

### 旋转函数
在实现旋转函数前先实现了3个辅助函数
```cpp
void ClockwiseRotate(char** a)
void antiClockwiseRotate(char** a)
void Exchange(char* a[4],char* b[4],char* c[4],char* d[4])
```
实现了12个旋转函数

为了便于操作，实现了几个辅助的旋转函数
```cpp
void StringToRotate(const char ops) //用来进行ops对应的旋转
void StringToAntirotate(const char ops) //用来进行ops方向相反的旋转
char GetRevOpt(char ops) //获取与ops方向相反的操作
void RunFormula(char *Formula,int len) //执行一段公式，Formula为公式对应数组，len为公式长度
```
### 生成测试数据

这一部分实现了两个函数
```cpp
- void ReSet() //用于将魔方重置成标准状态
- void TestCaseGenerator(int len,int Seed = 0) //用于生成测试样例的主函数
```
生成测试案例的方法：

将魔方状态初始化为已还原状态，并对其进行随机打乱
向标准输出流中输出打乱后的魔方状态并输出打乱公式
    
打乱步数作为参数传入$TestCaseGenerator$函数
$TestCaseGenerator$函数同时提供一个$Seed$参数，若传入的$Seed$值为零，会以运行程序时的系统时间作为随机数种子，否则以传入的$Seed$值作为种子。

### 底层十字（搜索法）
这一部分实现了两个函数
```cpp
// 判断是否已经完成了底层十字 已完成则返回1，未完成返回0
bool IsCross()
// 尝试使用迭代加深搜索寻找底层十字公式
bool IDFS(int deep)
// 底层十字主函数
void SearchCross()
```

这一部分通过迭代加深搜索实现Cross，目前测试出的最长用时约3.2 Second。其生成种子见TestData.txt

另外，完成了一个测试函数用于生成Cross的数据并检验时间，目前测试了三组数据。见CrossResult*.txt
最长的时间为3.421

Update 目前所测试的数据最长用时在CrossResult4.txt中，用时6.919，用8步完成底层十字

#### 底层十字还需要的工作

* 编写一个朴素的底层十字
* 尝试使用双向搜索寻找底层十字
 

