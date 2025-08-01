## EventEmitter/controlflags.c

### get_control_flags

#### 原型

`GList *EventEmitter_action_get_control_flags(EventEmitter ee)`

#### 描述

获取某个发射器的控制标志。

#### 参数

ee

ee: this 指针

#### 返回

0：是否允许调用 emit 1：是否允许调用 on

### put_control_flags

#### 原型 {#原型_1}

`<code>`{=html}void EventEmitter_action_put_control_flags(EventEmitter
\*\*ee,

`                                          gboolean emittable,`\
`                                          gboolean onable)``</code>`{=html}

#### 描述 {#描述_1}

设置某个发射器的控制标志。

#### 参数 {#参数_1}

ee

ee: this 指针

emittable

emittable: 是否允许发射新的事件

onable

onable: 是否允许新监听器加入
