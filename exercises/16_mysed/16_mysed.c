#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    // TODO: 在这里添加你的代码
    int idx1 = 2, len1=0, idx2, len2=0;
    int i = idx1;
    while(cmd[i] != '/') {
         len1++;
         i++;
    }
    i++;
    idx2 = i;
    while(cmd[i] && cmd[i] != '/') {
        len2++;
        i++;
    }
    *old_str = (char *)calloc(len1+1, sizeof(char));
    *new_str = (char *)calloc(len2+1, sizeof(char));
    memcpy(*old_str, cmd+idx1, len1);
    memcpy(*new_str, cmd+idx2, len2);

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    // TODO: 在这里添加你的代码
    int lenstr = strlen(str), lenold = strlen(old), lennew = strlen(new);
    char newstr[MAX_LINE_LENGTH] = {0};
    int gi = 0, si = 0, finded = 0;
    while(si<lenstr) {
        if(!finded) {
            int isequ = 1;
            for(int i=0;i<lenold;i++) {
                if(!(si+i<lenstr && str[si+i]==old[i])) {
                    isequ = 0;
                    break;
                }
            }
            if(isequ) {
                for(int i=0;i<lennew;i++) {
                    newstr[gi+i] = new[i];
                }
                gi += lennew;
                si += lenold;
                finded = 1;
            } else {
                newstr[gi] = str[si];
                gi++;
                si++;
            }
        } else {
            newstr[gi++] = str[si++];
        }
    }
    strcpy(str, newstr);
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
