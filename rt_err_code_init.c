/**
 * @file error_code_init.c
 * @author mengplus (chengmeng_2@outlook.com)
 * @brief 错误码框架的初始化程序
 * 工厂模式结构，避免注册过程分散在工程中不方便修改
 * @version 0.1
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "error_code.h"
#include "rtdevice.h"
#include "rt_err_code.h"
int rt_error_code_init()
{

    error_code_init();
    return 0;
}

INIT_COMPONENT_EXPORT(rt_error_code_init);

error_code_t *er_code_find_system_var()
{
    // 静态变量，用于缓存最近一次使用的错误码对象
    static error_code_t cached_error_code = {.code = 0}; // 初始化为一个无效的错误码

    // 检查缓存中是否已有相应的错误码对象
    if (cached_error_code.code != 0)
    {
        return &cached_error_code;
    }

    // 如果缓存中没有相应的错误码对象，则进行搜索和注册
    error_code_t er_code_obj = {.code = 305, .cnt_max = 1, .description = "EEPRom 异常"};
    error_code_t *found_obj = error_code_find(er_code_obj.code);
    cached_error_code = er_code_obj;
    if (found_obj != NULL)
    { // 更新缓存
        error_code_unregister(found_obj);
    }
    error_code_register(&cached_error_code);
    return &cached_error_code;
}
