## EventEmitter/deon.c

### 原型

`guint EventEmitter_action_deon(EventEmitter **ee, gchar *act)`

### 描述

移除监听某个事件的所有监听器。

### 参数

ee

ee: this 指针

act

act: 要移除的具体事件名称

### 返回

移除了多少个监听器
