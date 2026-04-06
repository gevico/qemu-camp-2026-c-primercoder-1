// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
    // TODO: 在这里添加你的代码
  int i = 0, j = 0;
  // 去除前导空白字符
  while (str[i] && isspace((unsigned char)str[i])) {
      i++;
  }
  // 去除尾部空白字符
  j = strlen(str) - 1;
  while (j >= i && isspace((unsigned char)str[j])) {
      j--;
  }
  str[j + 1] = '\0';
  // 移动字符串去除前导空白
  if (i > 0) {
      memmove(str, str + i, j - i + 2);
  }
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;

    // TODO: 在这里添加你的代码
  while (fgets(line, sizeof(line), file)) {
    // 去除换行符
    line[strcspn(line, "\n")] = '\0';
    trim(line);

    if (strlen(line) == 0) {
      continue;
    }

    // 如果是单词行（以#开头）
    if (line[0] == '#') {
      // 如果之前有词条，先保存到哈希表
      if (in_entry && strlen(current_word) > 0 && strlen(current_translation) > 0) {
        hash_table_insert(table, current_word, current_translation);
        (*dict_count)++;
      }
      // 提取新单词
      strncpy(current_word, line + 1, sizeof(current_word) - 1);
      current_word[sizeof(current_word) - 1] = '\0';
      trim(current_word);
      memset(current_translation, 0, sizeof(current_translation));
      in_entry = 1;
    } else if (line[0] == 'T' && strncmp(line, "Trans:", 6) == 0) {
      // 提取翻译内容
      char *trans = line + 6;
      trim(trans);
      if (strlen(current_translation) > 0) {
        strncat(current_translation, "; ", sizeof(current_translation) - strlen(current_translation) - 1);
      }
      strncat(current_translation, trans, sizeof(current_translation) - strlen(current_translation) - 1);
    }
  }

  // 保存最后一个词条
  if (in_entry && strlen(current_word) > 0 && strlen(current_translation) > 0) {
    hash_table_insert(table, current_word, current_translation);
    (*dict_count)++;
  }

  fclose(file);
  return 0;
}
