# 阅读源码心得以及笔记
选定一个文件，用到什么直接跳转，查看相关用法:略读和细读结合

注释：结尾的花括号标明是哪个命名空间的，很舒服

一个一个组件看，最后整体分析

## 一 阅读源码顺序
### 1.1 include/leveldb/slice.h  10/22 重新看完
维护指针和其他字节数组长度

```C++

```
有序列表
1.1
1.2 
无序列表
- adfa
- afasdf
- asdfasd
  






### 1.2 include/leveldb/db.h 10/23 没看具体实现
数据库的主接口

#### 1.2.1 include/leveldb/status.h 10/22 看完
用于报告成功和各种错误信息
使用枚举类型表示各个状态
使用纯虚函数，各个子类实现相关需求

#### 1.2.2 include/leveldb/db_impl.cc 
数据库的主要实现



##### 1.2.2.1 leveldb/include/leveldb/write_batch.h 10/24 看完
将多个更新应用与数据库：保存了一组自动应用于数据库的更新
更新顺序：按照添加的顺序
Put() : 本质append(),加入k：v键值对
Delete(): 追加删除key信息
Append()：多个WriteBatch还可以继续合并，直接复用 write_batch_internal.cc里面的
Clear(): 本质字符串的clear
Iterate(): 支持对batch的迭代处理，为了方便扩展，参数使用的是Handler基类，对应的是抽象工厂模式=>补设计模式的知识

##### 1.2.2.2 leveldb/include/leveldb/iterator.h 10/25 定义
和DB一样，纯虚函数的抽象基类，主要接口

##### 1.2.2.1.1 leveldb/db/write_batch_internal.h write_batch_internal.cc 基本类似，就不细看了
提供静态方法来操作不在公共接口使用的WriteBatch


### 1.3 leveldb/include/leveldb/options.h 10/26 先略过
记录leveldb中参数信息

### 1.4 leveldb/include/leveldb/comparator.h 10/27 复习一遍
抽象出来用于比较各类key的

### 1.5 leveldb/include/leveldb/env.h 10/27  了解了一下
用来访问操作系统功能（文件系统等）的接口
所有Env实现都可以安全地从多个线程进行并发访问，无需任何外部同步

WAL日志
### 1.6 leveldb/db/filename.h 10/29 看完
db相关的文件名的一些操作
直接在命名空间leveldb 下面写的，没有封装成类

### leveldb/db/log_format.h and leveldb/doc/log_format.md 10/29 复习
日志文件相关：日志文件的具体格式

### leveldb/include/leveldb/cache.h and leveldb/util/cache.cc 10/29 基本了解，没有分析具体实现
LRUHandle : 主要用于自定义的hashtable 和 lru缓存节点
cache : 纯虚基类
LRUCache : 
SharedLRUCache : 继承Cache，常用操作：基本是调用内部接口
db的数据被持久化到文件中时，以一定的规则进行组织=>文件格式sstable(sorted strint table)

SST