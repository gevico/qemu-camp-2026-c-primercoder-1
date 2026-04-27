# =============================================
# 主 Makefile
# 功能：
#   - mybash：生成二进制，放到 bin/
#   - 其他模块（mysed, myfile, mywc, mytrans）：生成静态库 .a，放到 obj/xxx/，.o 放到 obj/xxx/（或 out/，但建议统一）
#   - 所有子模块 Makefile 应支持 OBJDIR 和 BINDIR 参数
# =============================================

# PWD := $(shell pwd)


# # 所有子模块目录（静态库：生成 .a）
# SUBDIRS := \
# 	mysed \
# 	myfile \
# 	mywc \
# 	mytrans

# # 默认目标：构建 mybash（依赖其他库）
# all: mybash

# # 通用规则：构建每个子模块（静态库）
# $(SUBDIRS):
# 	@echo "building $@..."
# 	@$(MAKE) -C src/$@ OBJDIR=$(PWD)/obj/$@

# # 构建 mybash（可执行文件，依赖上面的库）
# mybash: $(SUBDIRS)
# 	@echo "building src/mybash...";
# 	@$(MAKE) -C src/mybash BINDIR=$(PWD)/bin OBJDIR=$(PWD)/obj/mybash

# # 清理所有生成的文件
# clean:
# 	@for dir in $(SUBDIRS);do echo "Cleaning $$dir.."; $(MAKE) -C src/$$dir clean OBJDIR=$(PWD)/obj/$$dir || true; done
# 	@echo "Cleaning src/mybash...";
# 	$(MAKE) -C src/mybash clean

# .PHONY: all $(SUBDIRS) mybash clean

./bin/mybash: ./main.c
	mkdir -p ./bin
	gcc -g ./main.c -o ./bin/mybash