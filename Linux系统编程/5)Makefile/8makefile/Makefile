
#$@ 表示目标
#$<	表示第一个依赖
#$^	表示所有的依赖
#变量引用  $(var) ${var}

TARGET=test
#获取当前目录中所有的.c 赋值给SRC
#等价于SRC=add.c sub.c mul.c div.c test.c
SRC=$(wildcard *.c)

#将$(SRC)中所有出现的.c 替换成.o
#等价于OBJS=add.o sub.o mul.o div.o test.o
OBJS=$(patsubst %.c, %.o, $(SRC))

$(TARGET):$(OBJS)
	gcc $^ -o $@

#模式规则 将.c生成对应的.o文件
%.o:%.c
	gcc -c $^ -o $@	

debug:
	echo $(SRC)
	echo $(OBJS)

#目标
clean:
	rm -rf $(OBJS) $(TARGET) 
