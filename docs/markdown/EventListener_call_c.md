## EventListener/call.c

### 原型

`<code>`{=html}gpointer EventListener_action_call(EventListener \*\*el,
GList \*args,

`                                  gboolean dobtrans, EventEmitter *source_ee)``</code>`{=html}

### 描述

直接调用单一监听器。

### 提醒

你不应该直接调用该方法。

### 参数

el

el: this 指针

dobtrans

dontrans: 是否做反传

args

args: 直接传递给回调的参数列表

### 返回

NULL（不进行反传）或回调返回值（进行反传）
