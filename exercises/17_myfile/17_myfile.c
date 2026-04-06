#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_elf_type(uint16_t e_type) {
  const char *type_str;
  switch (e_type) {
    // TODO: 在这里添加你的代码
  case ET_REL:
    type_str = "Relocatable";
    break;
  case ET_EXEC:
    type_str = "Executable";
    break;
  case ET_DYN:
    type_str = "Shared Object/PIE";
    break;
  case ET_CORE:
    type_str = "CORE";
    break;
  default:
    type_str = "Unknown";
    break;
  }
  printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int main(int argc, char *argv[]) {
  char filepath[2][256] = {
    "./17_myfile.o",
    "./17_myfile",
  };

  int fd;
  Elf64_Ehdr ehdr;

  // TODO: 在这里添加你的代码
  fd = open(filepath[0], O_RDONLY);
  read(fd, &ehdr, sizeof(Elf64_Ehdr));
  print_elf_type(ehdr.e_type);
  close(fd);
  fd = open(filepath[1], O_RDONLY);
  read(fd, &ehdr, sizeof(Elf64_Ehdr));
  print_elf_type(ehdr.e_type);
  close(fd);
  
  return 0;
}
