
CC=gcc
CPPFLAGS= -I./include -I/usr/local/include/hiredis
CFLAGS=-Wall 
LIBS=-lhiredis

#找到当前目录下所有的.c文件
src = $(wildcard *.c)

#将当前目录下所有的.c  转换成.o给obj
obj = $(patsubst %.c, %.o, $(src))

#日志
test_log=./test/test_log

#上传文件
test_upload=./test/test_upload

#redis客户端
test_redis=./test/test_redis


target=$(test_log) $(test_upload) $(test_redis)


ALL:$(target)


#生成所有的.o文件
$(obj):%.o:%.c
	$(CC) -c $< -o $@ $(CPPFLAGS) $(CFLAGS) 

#test_log程序
$(test_log):./test/test_log.o make_log.o 
	$(CC) $^ -o $@ $(LIBS)

#upload程序
$(test_upload):./test/upload_file.o make_log.o 
	$(CC) $^ -o $@ $(LIBS)
	
#test_redis程序
$(test_redis):./test/test_redis.o make_log.o redis_op.o
	$(CC) $^ -o $@ $(LIBS)


#clean指令
clean:
	-rm -rf $(obj) $(target) ./test/*.o

distclean:
	-rm -rf $(obj) $(target) ./test/*.o

#将clean目标 改成一个虚拟符号
.PHONY: clean ALL distclean
