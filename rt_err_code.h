/**
 * @file rt_err_code.h
 * @author mengplus (chengmeng_2@outlook.com)
 * @brief 错误码框架使用接口
 * @version 0.1
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __RT_ERROR_CODE_H_
#define __RT_ERROR_CODE_H_

#include "error_code.h"
#ifdef __cplusplus
extern "C"
{
#endif

    error_code_t *er_code_find_system_var();
#ifdef __cplusplus
}
#endif

#endif
