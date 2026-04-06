#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;

    // TODO: 在这里添加你的代码
    int i=0;
    while(url[i] && url[i]!='?') i++;
    i++;
    while(url[i]) {
        int j = i;
        int k = i;
        while(url[j] && url[j]!='&') {
            j++;
            if(url[j]=='=') k = j;
        }
        printf("key = ");
        for(int l=i;l<k;l++) printf("%c", url[l]);
        printf(", value = ");
        for(int l=k+1;l<j;l++) printf("%c", url[l]);
        printf("\n");
        if(!url[j]) break;
        i = j + 1;
    }

exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}