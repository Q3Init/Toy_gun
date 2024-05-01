#ifndef LIB_LOG_UTIL_H_
#define LIB_LOG_UTIL_H_

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "MCAL_APM32.h"
#include "MCAL_Cfg_UART.h"

#ifdef DEBUG_INFO_ENABLE
#define Log_d(args...) Log_writter(__FILE__, __FUNCTION__, __LINE__, LOG_DEBUG, args)
#define Log_i(args...) Log_writter(__FILE__, __FUNCTION__, __LINE__, LOG_INFO, args)
#define Log_w(args...) Log_writter(__FILE__, __FUNCTION__, __LINE__, LOG_WARN, args)
#define Log_e(args...) Log_writter(__FILE__, __FUNCTION__, __LINE__, LOG_ERROR, args)

#define send_char(a)		sys_uart2_sendchar(a)

#define 	_IN_            /* 表明这是一个输入参数. */
#define		_OU_            /* 表明这是一个输出参数. */

/**
 * 日志输出等级
 */
typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} LOG_LEVEL;

/**
 * 全局日志级别输出标志, 只输出小于或等于该等级的日志信息
 */
extern LOG_LEVEL g_log_level;

/**
 * @brief 日志打印函数，默认打印到标准输出
 *
 * @param file 源文件名
 * @param func 函数名
 * @param line 行号
 * @param level 日志等级
 */
void Log_writter(const char *file, const char *func, const int line, const int level, const char *fmt, ...);

extern uint8 uart_log_buffer[];

extern uint8 NO_FILE_LINE_LOG;

extern int vsnprintf(char *sbuf, size_t n, const char *format, va_list arg );

#endif  /* DEBUG_INFO_ENABLE */
#endif  /* LIB_LOG_UTIL_H_ */
