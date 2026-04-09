// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void trim(char *str) {
    // TODO: 在这里添加你的代码
    if ( str == NULL || *str == '\0' ){ return; }

    // start space
    char *start =str;
    while ( *start && (isspace(*start) ) ){
        start++;
    }

    char* end = str +strlen(str)-1;
    while( end > start && (isspace(*end) ) ){
        end--;
    }

    int len = end - start +1;
    memmove(str, start, len);
    str[len] = '\0';
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  // 直接使用绝对路径
  const char *dict_path = "./src/mytrans/dict.txt";
  printf("尝试打开的文件: %s\n", dict_path);
  FILE *file = fopen(dict_path, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;

    // TODO: 在这里添加你的代码
    int state = 0; // state = 0 key, state = 1 value
    *dict_count = 0;
    while ( fgets(line, sizeof(char)*1023, file) ){
        char *key_pos = strchr(line, '#');
        char *value_pos = strstr(line, "Trans:");

        // other -> key
        if (state == 0 && key_pos != NULL ){
            strncpy(current_word, key_pos+1, sizeof(current_word)-1);
            current_word[sizeof(current_word)-1] = '\0';
            state = 1;

        }else if (state == 1 && value_pos != NULL ){
            // key -> value
            strncpy(current_translation, value_pos+6, sizeof(current_translation)-1);
            current_translation[sizeof(current_translation)-1] = '\0';
            trim(current_word);
            trim(current_translation);
            hash_table_insert(table, current_word, current_translation);
            (*dict_count)++;
            state = 0;
        }else{
            // error key or error value
            state = 0;
        }
    }
  fclose(file);
  return 0;
}

void to_lowercase(char *str) {
  for (; *str; ++str)
    *str = tolower((unsigned char)*str);
}

int __cmd_mytrans(const char* filename) {
  HashTable *table = create_hash_table();
  if (!table) {
    fprintf(stderr, "无法创建哈希表\n");
    return 1;
  }

  // 获取当前工作目录
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("当前工作目录: %s\n", cwd);
  } else {
    perror("getcwd() 失败");
  }

  printf("=== 哈希表版英语翻译器（支持百万级数据）===\n");
  uint64_t dict_count = 0;
  
  // 使用绝对路径
  const char *dict_path = "./src/mytrans/dict.txt";
  printf("尝试打开词典文件: %s\n", dict_path);
  
  FILE *dict_file = fopen(dict_path, "r");
  if (!dict_file) {
    perror("无法打开词典文件");
    fprintf(stderr, "加载词典失败，请确保 dict.txt 存在。\n");
    free_hash_table(table);
    return 1;
  }
  
  // 读取词典文件
  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int state = 0; // state = 0 key, state = 1 value
  
  while (fgets(line, sizeof(line), dict_file)) {
    char *key_pos = strchr(line, '#');
    char *value_pos = strstr(line, "Trans:");

    // other -> key
    if (state == 0 && key_pos != NULL) {
      strncpy(current_word, key_pos+1, sizeof(current_word)-1);
      current_word[sizeof(current_word)-1] = '\0';
      state = 1;

    } else if (state == 1 && value_pos != NULL) {
      // key -> value
      strncpy(current_translation, value_pos+6, sizeof(current_translation)-1);
      current_translation[sizeof(current_translation)-1] = '\0';
      trim(current_word);
      trim(current_translation);
      hash_table_insert(table, current_word, current_translation);
      dict_count++;
      state = 0;
    } else {
      // error key or error value
      state = 0;
    }
  }
  
  fclose(dict_file);
  printf("词典加载完成，共计%ld词条。\n", dict_count);

  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "无法打开文件 %s。\n", filename);
    free_hash_table(table);
    return 1;
  }

  char text_line[256];
  while (fgets(text_line, sizeof(text_line), file) != NULL) {
    text_line[strcspn(text_line, "\n")] = '\0';

    if (strlen(text_line) == 0) {
        continue;
    }

    // 使用 strtok 按空格分割单词
    char *word = strtok(text_line, " ");
    while (word != NULL) {
      const char *translation = hash_table_lookup(table, word);
      printf("原文: %s\t", word);
      if (translation) {
          printf("翻译: %s\n", translation);
      } else {
          printf("未找到该单词的翻译。\n");
      }

      word = strtok(NULL, " ");
    }
  }

  free_hash_table(table);
  return 0;
}
