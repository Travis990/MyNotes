#$@ 表示目标
#$<	表示第一个依赖
#$^	表示所有的依赖
#变量引用  $(var) ${var}

CC=gcc
INC=.
CPPFLAGS=-I$(INC)
CFLAGS=-Wall -g -c
TARGET=test
#获取当前目录中所有的.c 赋值给SRC
#等价于SRC=add.c sub.c mul.c div.c test.c
SRC=$(wildcard *.c)

#将$(SRC)中所有出现的.c 替换成.o
#等价于OBJS=add.o sub.o mul.o div.o test.o
OBJS=$(patsubst %.c, %.o, $(SRC))

$(TARGET):$(OBJS)
	$(CC) $^ -o $@

#模式规则 将.c生成对应的.o文件
%.o:%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@	

#伪目标 伪目标无条件执行
#- 表示对应命令执行失败, 会继续往下执行
.PHONY:clean
clean:
	@rm -rf $(OBJS) $(TARGET) 
