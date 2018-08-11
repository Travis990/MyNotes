
#$@ 表示目标
#$<	表示第一个依赖
#$^	表示所有的依赖
#变量引用  $(var) ${var}

OBJS=add.o sub.o mul.o div.o test.o
TARGET=test

#目标:依赖
#	命令
#等价于test:add.o sub.o mul.o div.o test.o
$(TARGET):$(OBJS)
	@#gcc $(OBJS) -o $(TARGET)
	gcc $^ -o $@
	echo $@
	echo $^
	echo $<

add.o:add.c
	gcc -c $^ -o $@
sub.o:sub.c
	gcc -c $^ -o $@  
mul.o:mul.c
	gcc -c $^ -o $@ 
div.o:div.c
	gcc -c $^ -o $@ 
test.o:test.c
	gcc -c $^ -o $@ 

#如果Makefile中没有显示指定生成目标代码规则 那么就使用隐式的规则

#目标
clean:
	rm -rf $(OBJS) $(TARGET) 
