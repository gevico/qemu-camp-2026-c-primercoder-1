#include <stdio.h>

int main() {
    char source[] = "Hello, World! This is a test string for my_strcpy function.\n";
    char destination[101];
    
	// TODO: 在这里添加你的代码
    int i=0, j=0;
    while(destination[i++]=source[j++]);    
    printf("拷贝后的字符串: %s", destination);
    
    return 0;
}