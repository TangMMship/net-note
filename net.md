计算机网络编程

## 一、分层结构

![img](https://secure2.wostatic.cn/static/xxwoFbYw7sSoqxQL4G8BEY/image.png?auth_key=1695949606-iJdisfWktep9Xs6fAkNH4R-0-53c648ae6e01f047bcbae85e61f46dd8)

### 1.1**IP协议(网际协议)   网络层**

**定义：**

特指为一个相互连接的网络系统从源地址到目标地址传输数据包所提供必要功能的协议。

**特点：**

无连接：ip协议不维护后续数据包的状态信息，每个数据包都是独立的，IP数据包可以不按顺序接收

不可靠：ip协议不能保证数据包能到达目的地，只提供尽力而为的服务。

（ip数据包含有源地址和目标地址）



### 1.2 TCP协议  传输控制协议

tcp协议是面向连接，可靠的传输协议

功能：

提供不同主机间进程的通信

**特点：**

1. 面向连接

   建立链接 — 使用链接 — 释放链接（虚电路）

2. tcp数据包含序号和确认序号

3. 对数据包进行排序和检错，错误的包可以重传

**目标：**

需要高度可靠的面向连接的服务

http ftp smtp等

1.3 UDP 用户数据包协议

功能：

```
不同主机进程间通信
```

特点 1. 传输不建立链接 2. 数据报不需要排序 3. 没有纠错和重传机制

服务对象

只需要查询应答的服务

如 ntp nfs dns

2.1 MAC地址

用于标识设备，48bit

两个16进制数为一组(8bit)，分为6组，每组用  :   隔开  前三组为厂商id ，后三组为主设备id

2.2 ip地址 网际协议地址

ip地址是任意一台主机在网络上的唯一标识

ipv4 32bit

ipv6 128bit

ipv4一般用点分十进制数表示

[xxx.xxx.xxx.xxx](http://xxx.xxx.xxx.xxx)

由网络id和主机id两部分组成

子网id（网络id）：

ip地址中由子网掩码1覆盖的连续位

主机id：

ip地址中由子网掩码0覆盖的连续位

ip地址特点

```
1、子网ip不同的网络不能直接通信，需要路由器转发

2、主机id为0的为网段地址

3、主机id全为1的地址为网段的广播地址
```

![img](https://secure2.wostatic.cn/static/bVMRtV67bPDAbDx45uDUpz/image.png?auth_key=1695953783-eLSGeWu5cgYaWWMfozgJjs-0-3e4d6886fa1eabf5f7f8d0b55825a22d)

公网ip

经过internet nic 划分的地址，可以直接访问互联网

私有ip

局域网内主机联络规划的，不可以直接访问互联网

![img](https://secure2.wostatic.cn/static/46TtecG8NxsMTtT73WVdU6/image.png?auth_key=1695954246-fv9owo7bDqJ7ifKg5UFQRK-0-e6245776434027f255d2ca7018174ee2)