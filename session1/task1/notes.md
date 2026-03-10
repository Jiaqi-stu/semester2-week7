这个报错的意思是：你访问了列表中不存在的索引位置。

报错信息
IndexError: list assignment index out of range

意思是：
列表赋值时索引超出了范围。

你的代码问题在哪里
data = [0] * 10

这行代码创建了一个长度为 10 的列表：

[0,0,0,0,0,0,0,0,0,0]

它的 索引范围是：
0 到 9

但是你的函数里：

for i in range(100):
    x[i] = (i + 1) * (i + 1)

range(100) 会让 i 从 0 到 99。

当 i = 10 时：

x[10]

但是列表只有 0–9，所以 Python 就报错：
IndexError
解决方法1（推荐）：按照列表长度循环
def assign_values(x):
    for i in range(len(x)):
        x[i] = (i + 1) * (i + 1)

这样无论列表多大都不会越界。
—————————————————————————————————————————————————————————————————————————————————————————————
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
—————————————————————————————————————————————————————————————————————————————————————————————
*** stack smashing detected ***: terminated
Aborted (core dumped)

意思是：你的程序破坏了栈内存（stack memory corruption），系统检测到后强制终止程序。

问题出在哪里

你的代码：

int data[10] = { 0 };

只创建了 10个元素的数组：

data[0] 到 data[9]

但是函数里：

for (int i = 0; i < 100; ++i) {
    x[i] = (i + 1) * (i + 1);
}

循环 100次：

x[0] ... x[99]

当 i >= 10 时：

x[10], x[11], ... x[99]

这些 都超出了数组范围。

在 C 语言里会发生什么

C 不会自动检查数组越界。

所以程序会开始写入：

data[10]
data[11]
...

这些其实是：

其他变量的内存

函数返回地址

栈保护区

当程序破坏了这些区域，系统检测到 stack protector 被覆盖，就会报：

*** stack smashing detected ***

意思是：

栈被破坏了（Stack Smashing）

然后系统为了安全：

Aborted (core dumped)

强制终止程序。

为什么 Python 只是 IndexError

Python：

IndexError: list assignment index out of range

因为 Python 会自动检查边界。

而 C：

不检查

直接写内存

导致更危险的问题

解决方法1（推荐）

按数组大小循环：

void assign_values(int x[], int n)
{
    for (int i = 0; i < n; ++i) {
        x[i] = (i + 1) * (i + 1);
    }
}

主函数：

int main(void)
{
    int data[10] = {0};

    assign_values(data, 10);

    printf("Done!\n");

    return 0;
}