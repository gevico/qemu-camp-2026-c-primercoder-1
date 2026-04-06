#include <stdio.h>

int main() {
    char str[]="Don't ask what your country can do for you, but ask what you can do for your country.";
    int wordCount = 0;
    // TODO: 在这里添加你的代码
    int state = 0;
    int i=0;
    while(str[i]) {
        if(str[i] == ' ') {
            if(state==1) state = 0;
        } else {
            if(state==0) {
                wordCount++;
                state = 1;
            }
        }
        i++;
    }
    
    printf("单词数量: %d\n", wordCount);
    
    return 0;
}