#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <unistd.h>

#if defined(DEBUG_LEVEL) && (DEBUG_LEVEL == 1)
#define DEBUG_PRINT(fmt, ...) \
    fprintf(stdout, "DEBUG: func=%s, line=%d\n", __func__, __LINE__)

#elif defined(DEBUG_LEVEL) && (DEBUG_LEVEL == 2)
#define DEBUG_PRINT(fmt, ...) \
    fprintf(stdout, "DEBUG: func=%s, line=%d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__)

#elif defined(DEBUG_LEVEL) && (DEBUG_LEVEL == 3)
#define DEBUG_PRINT(fmt, ...) do { \
    fprintf(stdout, "DEBUG: func=%s, line=%d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__); \
    void *buffer[16]; \
    int nptrs = backtrace(buffer, 16); \
    backtrace_symbols_fd(buffer, nptrs, STDERR_FILENO); \
} while (0)

#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)

#endif

















//! MUST BE ENSURE THE DEBUG_PRINT("x=%d", x) AT THE 48 LINE

// 测试代码
void test() {
    int x = 42;
    DEBUG_PRINT("x=%d", x);
}

int main() {
    test();
    return 0;
}