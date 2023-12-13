/**
 * @file error_code_def.h
 * @author mengplus (chengmeng_2@outlook.com)
 * @brief 错误码类型
 * @version 0.1
 * @date 2023-12-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __ERROR_CODE_DEF_H_
#define __ERROR_CODE_DEF_H_

#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct _ERROR_CODE_DEF error_code_t;
    struct _ERROR_CODE_DEF
    {
        error_code_t *prev; /*!< if NULL is root */
        error_code_t *next;

        uint32_t code;      /*!< 错误码 */
        uint16_t cnt;       /*!< 累计错误计数 */
        uint16_t cnt_max;   /*!< 报错计数 cnt >cnt_max 则为真正的报错*/
        uint16_t err_cnt; /*!< 实际发生报错的次数统计 */
        uint32_t err_st;    /*!< 报错开始时间 */
        uint32_t err_ed;    /*!< 报错结束时间 */

        const char *description; /*!< 错误描述 */
    };

#ifdef __cplusplus
}
#endif
#endif
