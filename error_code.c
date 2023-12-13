/**
 * @file error_code.c
 * @author mengplus (chengmeng_2@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "error_code.h"
#include <time.h>
// 全局的错误码链表头部
static error_code_t error_code_list_head;

// 在 error_code.c 文件中
static int is_duplicate_code(uint32_t code)
{
    error_code_t *current_error = error_code_list_head.next;
    while (current_error != NULL)
    {
        if (current_error->code == code)
        {
            return 1; // 错误码重复
        }
        current_error = current_error->next;
    }
    return 0; // 错误码唯一
}

void error_code_init()
{
    // 初始化错误码链表头部
    error_code_list_head.prev = NULL;
    error_code_list_head.next = NULL;
    error_code_list_head.code = 0;
}

uint16_t error_code_register(error_code_t *obj)
{
    // 检查是否已存在相同错误码
    if (is_duplicate_code(obj->code))
    {
        return 1; // 错误码重复，注册失败
    }

    // 在链表头部插入新的错误码对象
    obj->prev = NULL;
    obj->next = error_code_list_head.next;

    if (error_code_list_head.next != NULL)
    {
        error_code_list_head.next->prev = obj;
    }

    error_code_list_head.next = obj;
    obj->cnt = 0;
    obj->err_cnt = 0;
    obj->err_st = 0;
    obj->err_ed = 0;

    return 0; // 注册成功
}
// 在 error_code.c 源文件中添加移除接口的实现
uint16_t error_code_unregister(error_code_t *obj)
{
    if (obj == NULL)
    {
        return 1; // 无效的错误码对象
    }

    // 从链表中移除该错误码对象
    if (obj->prev != NULL)
    {
        obj->prev->next = obj->next;
    }
    else
    {
        // obj 是链表头部
        error_code_list_head.next = obj->next;
    }

    if (obj->next != NULL)
    {
        obj->next->prev = obj->prev;
    }

    // 释放可能的资源，比如动态分配的内存

    return 0; // 移除成功
}
error_code_t *error_code_get_list()
{
    return error_code_list_head.next;
}

error_code_t *error_code_get_next_list(const error_code_t *item)
{
    return item->next;
}

uint8_t error_code_set_flag(error_code_t *obj)
{

    if (obj->cnt == 0)
    {
        obj->err_st = time(NULL);
    }
    // 设置错误标志
    if (!error_code_is_error(obj))
    {
        obj->cnt++;
    }
    return 0; // 操作成功
}

void error_code_clear_flag(error_code_t *obj)
{
    if (error_code_is_error(obj))
    {
        obj->err_cnt++;
    }
    // 清除错误标志
    obj->cnt = 0; // 设置错误结束标志
}

uint8_t error_code_is_error(error_code_t *obj)
{
    // 检查是否发生错误
    return obj->cnt_max <= obj->cnt;
}
error_code_t *error_code_find(uint32_t code)
{
    error_code_t *current_error = error_code_list_head.next;

    while (current_error != NULL)
    {
        if (current_error->code == code)
        {
            return current_error; // 找到对应的错误码对象
        }
        current_error = current_error->next;
    }

    return NULL; // 未找到对应的错误码对象
}
