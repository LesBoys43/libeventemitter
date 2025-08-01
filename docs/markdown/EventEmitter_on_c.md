## EventEmitter/on.c

### 原型

`<code>`{=html}EventListener \*EventEmitter_action_on(EventEmitter
\*\*ee, gchar \*act,

`                                     const EventListenerFuncPtr cb)``</code>`{=html}

### 描述

监听一个事件。

### 参数

ee

ee: this 指针

act

act: 要监听的具体事件名称

cb

cb: 实际回调函数

### 返回

生成的 EventListener 实例
