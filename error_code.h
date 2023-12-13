/**
 * @file error_code.h
 * @author mengplus (chengmeng_2@outlook.com)
 * @brief 错误码管理框架
 * @version 0.1
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __ERROR_CODE_H_
#define __ERROR_CODE_H_

#include "error_code_def.h"

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief 初始化错误码系统
     */
    void error_code_init();

    /**
     * @brief 注册错误码对象
     * @param obj 错误码对象
     * @return 注册成功返回0，否则返回错误码
     */
    uint16_t error_code_register(error_code_t *obj);
    /**
     * @brief 注销注册码
     * @param obj 待注销对象
     * @return uint16_t 0移除成功
     */
    uint16_t error_code_unregister(error_code_t *obj);
    /**
     * @brief 获取错误码列表的头部
     * @return 错误码列表的头部
     */
    error_code_t *error_code_get_list();

    /**
     * @brief 获取下一个错误码对象
     * @param item 当前错误码对象
     * @return 下一个错误码对象
     */
    error_code_t *error_code_get_next_list(const error_code_t *item);

    /**
     * @brief 设置错误标志
     * @param obj 错误码对象
     * @return 操作成功返回0，否则返回错误码
     */
    uint8_t error_code_set_flag(error_code_t *obj);

    /**
     * @brief 清除错误标志
     * @param obj 错误码对象
     * @return 操作成功返回0，否则返回错误码
     */
    void error_code_clear_flag(error_code_t *obj);

    /**
     * @brief 检查是否发生错误
     * @param obj 错误码对象
     * @return 发生错误返回非零，否则返回0
     */
    uint8_t error_code_is_error(error_code_t *obj);

    /**
     * @brief 根据错误码查找对应的错误码对象
     * @param code 错误码
     * @return 对应的错误码对象，如果未找到返回NULL
     */
    error_code_t *error_code_find(uint32_t code);

#ifdef __cplusplus
}
#endif
#endif
