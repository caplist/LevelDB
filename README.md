# 阅读源码心得以及笔记
选定一个文件，用到什么直接跳转，查看相关用法:略读和详细读结合

注释：结尾的花括号标明是哪个命名空间的，很舒服

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
#### 1.2.1 include/leveldb/status.h status.cc 10/22 看完
用于报告成功和各种错误信息
使用枚举类型表示各个状态
使用纯虚函数，各个子类实现相关需求

#### 1.2.2 include/leveldb/db_impl.cc 
数据库的主要实现


##### 1.2.2.1 leveldb/include/leveldb/write_batch.h write_batch.cc 10/24 看完
将多个更新应用与数据库：保存了一组自动应用于数据库的更新
更新顺序：按照添加的顺序
Put() : 本质append(),加入k：v键值对
Delete(): 追加删除key信息
Append()：多个WriteBatch还可以继续合并，直接复用 write_batch_internal.cc里面的
Clear(): 本质字符串的clear
Iterate(): 支持对batch的迭代处理，为了方便扩展，参数使用的是Handler基类，对应的是抽象工厂模式=>补设计模式的知识


##### 1.2.2.1.1 leveldb/db/write_batch_internal.h write_batch_internal.cc 基本类似，就不细看了
提供静态方法来操作不在公共接口使用的WriteBatch
