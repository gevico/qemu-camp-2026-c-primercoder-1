#include <stdio.h>
#include <stdlib.h>

/*
 * 19 字符串分割器（类似 strtok_r）
 * 目标：实现线程安全的字符串分割函数，不依赖静态全局状态
 * 原型：char* strtok_r(char *str, const char *delim, char **saveptr)
 * 示例：输入 "hello,world test"，分隔符 ", " → 依次得到 hello、world、test
 */

static int is_delim(char c, const char *delim) {
    while (*delim) {
        if (c == *delim) return 1;
        delim++;
    }
    return 0;
}

/* 线程安全版本：通过 saveptr 维护调用状态，不使用静态变量 */
char *strtok_r(char *str, const char *delim, char **saveptr) {
    char *token_start;
    
    /* 如果是第一次调用，使用 str；否则使用 saveptr 中保存的地址 */
    if (str != NULL) {
        token_start = str;
    } else {
        token_start = *saveptr;
    }
    
    /* 跳过开头的分隔符 */
    while (*token_start && is_delim(*token_start, delim)) {
        token_start++;
    }
    
    /* 如果已经到达字符串末尾，返回 NULL */
    if (*token_start == '\0') {
        *saveptr = token_start;
        return NULL;
    }
    
    /* 找到当前 token 的结束位置 */
    char *token_end = token_start;
    while (*token_end && !is_delim(*token_end, delim)) {
        token_end++;
    }
    
    /* 如果结束位置不是字符串末尾，则将其替换为 '\0'，并更新 saveptr */
    if (*token_end != '\0') {
        *token_end = '\0';
        *saveptr = token_end + 1;
    } else {
        *saveptr = token_end;
    }
    
    return token_start;
}
int main(void) {
    char buf[] = "hello,world test";
    const char *delim = ", ";
    char *save = NULL;

    char *tok = strtok_r(buf, delim, &save);
    while (tok) {
        printf("%s\n", tok);
        tok = strtok_r(NULL, delim, &save);
    }
    return 0;
}
