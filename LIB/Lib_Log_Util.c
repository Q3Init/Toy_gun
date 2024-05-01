#ifdef DEBUG_INFO_ENABLE
#include "Lib_Log_Util.h"

#define MAX_LOG_MSG_LEN 			(512)

uint8 uart_log_buffer[MAX_LOG_MSG_LEN] = {0};

enum output_selection_tag{
    NO_MORE_INFO,
    JUST_LEVEL_FUNC_LOG,
    JUST_FUNC_LOG,
    DEFAULT,
};

uint8 log_format = JUST_FUNC_LOG;/* false --> no file_name and line output in log*/

static char *level_str[] = {
    "DBG", "INF", "WRN", "ERR",
};

LOG_LEVEL g_log_level = LOG_DEBUG;

void sys_uart1_sendchar(uint8 data)
{
	/* Loop until the end of transmission */
    while (USART_ReadStatusFlag(USART1, USART_FLAG_TXBE) == RESET);
    USART_TxData(USART1, data);	
}

void sys_uart2_sendchar(uint8 data)
{
	/* Loop until the end of transmission */
    while (USART_ReadStatusFlag(USART2, USART_FLAG_TXBE) == RESET);
    USART_TxData(USART2, data);
}

int HAL_Snprintf(_IN_ char *str, const int len, const char *fmt, ...)
{
    va_list args;
    int rc;

    va_start(args, fmt);
    rc = vsnprintf(str, len, fmt, args);
    va_end(args);

    return rc;
}

void HAL_Printf(_IN_ char *str)
{
	while((*str) != '\0')
	{
		send_char((*str++));
	}
}

static const char *_get_filename(const char *p)
{
    char ch = '/';
    const char *q = strrchr(p,ch);
    if(q == NULL)
    {
        q = p;
    }
    else
    {
        q++;
    }
    return q;
}

void Log_writter(const char *file, const char *func, const int line, const int level, const char *fmt, ...)
{
	if (level < g_log_level) {
		return;
	}
		
	const char *file_name = _get_filename(file);
    sint32 log_length = 0;

    switch(log_format)
    {
        case NO_MORE_INFO:
            break;
        case JUST_LEVEL_FUNC_LOG:
            log_length = HAL_Snprintf((char *)uart_log_buffer,MAX_LOG_MSG_LEN, "%s | %s: ", level_str[level], func);
            break;
        case JUST_FUNC_LOG:
            log_length = HAL_Snprintf((char *)uart_log_buffer,MAX_LOG_MSG_LEN, "%s | ", func);
            break;
        default:
            log_length = HAL_Snprintf((char *)uart_log_buffer,MAX_LOG_MSG_LEN, "%s | %s |%s(%d): ", level_str[level],  file_name, func, line);
            break;
    }

    if((log_length<0) || ((MAX_LOG_MSG_LEN-log_length)<0))
    {
        HAL_Printf("Failed to printf log!\r\n");
    }

    va_list args;
    va_start(args, fmt);
    log_length = vsnprintf((char *)(uart_log_buffer+log_length), MAX_LOG_MSG_LEN-log_length, fmt, args);
    va_end(args);

    if((log_length<0))
    {
        HAL_Printf("Failed to printf log!\r\n");
    }

    HAL_Printf((char *)uart_log_buffer);

    return; 
}
#endif /* DEBUG_INFO_ENABLE */
