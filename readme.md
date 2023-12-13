---
title: 故障码管理框架
description: 规范我们的故障管理
versions: V1.0-202312
editors: mengplus
---

# 故障码管理框架

设备故障码统一管理框架，为解决设备运行过程由于外界干扰等问题，导致部分协作组件出现异常无法工作问题，设计故障管理框架，方便在开发过程中，增减故障信息标签，便于友好展示与记录。


## 文件目录

```bash
.
├── error_code.c        #源码
├── error_code_def.h    #类型定义
├── error_code.h        #头文件
├── readme.md           #本说明文件
├── rt_err_code.h       #用户头文件
├── rt_err_code_init.c  #使用示例 rt-thread环境下自动初始化
└── SConscript          #rt-thread自动加入工程的脚本
```

## 架构介绍

### 结构体介绍

```C
// error_code_def.h
typedef struct _ERROR_CODE_DEF error_code_t;
    struct _ERROR_CODE_DEF
    {
        error_code_t *prev; /*!< if NULL is root */
        error_code_t *next;

        uint32_t code;      /*!< 错误码 */
        uint16_t cnt;       /*!< 累计错误计数 */
        uint16_t cnt_max;   /*!< 报错计数 cnt >cnt_max 则为真正的报错*/
        uint16_t cnt_tolal; /*!< 实际发生报错的次数统计 */
        uint32_t err_st;    /*!< 报错开始时间 */
        uint32_t err_ed;    /*!< 报错结束时间 */

        const char *description; /*!< 错误描述 */
    };
```

**参数介绍**

- code
- cnt
- cnt_max
- cnt_to

### 操作接口介绍

见头文件注释[error_code.h](./error_code.h)        #头文件

### 使用示例

1. 初始化框架

   在使用框架之前，需要进行初始化。

   ```c
   // 示例代码
   error_code_init();
   ```

2. 注册故障码

   注册故障码是为了在框架中建立错误码对象，以便后续进行查询和管理。

   ```C
   // 示例代码
   error_code_t er_code_obj = {.code = 305, .description = "EEPRom 异常"};
   uint16_t registration_result = error_code_register(&er_code_obj);
   
   if (registration_result == 0) {
       // 注册成功
   } else {
       // 注册失败，可能是错误码重复等原因
   }
   
   ```

3. 新增异常

   在程序执行过程中，如果遇到异常情况，可以通过下述方式新增异常信息。

   ```C
   // 示例代码
   error_code_t *current_error = er_code_find_system_var();
   // 其他异常处理逻辑...
   error_code_set_flag(current_error);
   ```

4. 查询是否故障

   在程序中可以查询当前是否存在故障。

   ```C
   // 示例代码
   error_code_t *current_error = er_code_find_system_var();
   error_code_clear_flag(current_error);
   ```

5. 清理故障信息

   当异常情况得到处理或解决后，需要清理故障信息。

   ```C
   // 示例代码
   error_code_t *current_error = er_code_find_system_var();
   error_code_clear_flag(current_error);
   ```

6. 获得所有故障码信息，并打印出错的信息

   可以获取所有注册的故障码信息，并打印出错的详细信息

   ```C
   // 示例代码
   const error_code_t *current_error = error_code_get_list();
   while (current_error != NULL) {
       if (error_code_is_error(current_error)) {
           // 打印出错的信息
           printf("Error Code: %u, Description: %s\n", current_error->code, current_error->description);
       }
       current_error = error_code_get_next_list(current_error);
   }
   ```

   

