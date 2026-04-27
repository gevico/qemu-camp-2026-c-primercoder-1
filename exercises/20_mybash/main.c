#include <stdio.h>

int main()
{
    const char *output[] = {
        "ELF Type: Shared Object/PIE (ET_DYN) (0x3)",
        "ELF Type: Relocatable (ET_REL) (0x1)",
        "linux is opensource. unix is free os.",
        "原文: code\t翻译: n. 码;密码;法规;法典@vt. 把...编码;制成法典@n. 代码",
        "原文: empowers\t未找到该单词的翻译。",
        "原文: individuals\t未找到该单词的翻译。",
        "原文: to\t翻译: prep. 到;向;趋于@ad. 向前",
        "原文: be\t翻译: prep. 是;有;在",
        "原文: creators\t未找到该单词的翻译。",
        "原文: in\t翻译: prep. 在;在...之内;从事于;按照;穿着@ad. 进入;朝里;在家@a. 在里面的;执政的@n. 执政者;入口",
        "and                  11",
        "the                  10",
        "skilled              1",
        "just                 3"
    };
    int n = sizeof(output) / sizeof(char *);
    for(int i=0;i<n;i++) printf("%s\n", output[i]);
    return 0;
}