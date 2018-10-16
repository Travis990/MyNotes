CC=gcc
CPPFLAGS= -I./include -I/usr/local/include/hiredis -I/usr/include/mysql/ -I/usr/include/fastcommon/
CFLAGS=-Wall 
LIBS=-lmysqlclient -lhiredis -lfcgi -lm -lfdfsclient

#path
TEST_PATH=./test
COMMON_PATH=./common
CGI_BIN_PATH=./cgi_bin
CGI_SRC_PATH=./cgi_src

#找到COMMON_PATH目录下所有的.c文件
src = $(wildcard $(COMMON_PATH)/*.c)

#将COMMON_PATH目录下所有的.c  转换成.o给obj
obj = $(patsubst $(COMMON_PATH)/%.c, $(COMMON_PATH)/%.o, $(src))

#===============================test测试代码=======================
test_log=$(TEST_PATH)/test_log 		  		# 日志的使用
test_upload=$(TEST_PATH)/test_upload  		# fdfs上传文件
test_redis=$(TEST_PATH)/test_redis    		# redis客户端
test_sql_redis=$(TEST_PATH)/test_sql_redis 	# mysql和redis配合使用

#===============================cgi程序===========================
login.cgi=$(CGI_BIN_PATH)/login.cgi 	#login.cgi  登陆
reg.cgi=$(CGI_BIN_PATH)/reg.cgi 		#reg.cgi    注册
md5.cgi=$(CGI_BIN_PATH)/md5.cgi 		#md5.cgi    秒传
upload.cgi=$(CGI_BIN_PATH)/upload.cgi 	#upload.cgi 上传
myfiles.cgi=$(CGI_BIN_PATH)/myfiles.cgi 	#用户文件列表展示cgi程序
dealfile.cgi=$(CGI_BIN_PATH)/dealfile.cgi 	#分享、删除文件、pv字段处理cgi程序
sharefiles.cgi=$(CGI_BIN_PATH)/sharefiles.cgi 			#共享文件列表展示cgi程序
dealsharefile.cgi=$(CGI_BIN_PATH)/dealsharefile.cgi 	#共享文件pv字段处理、取消分享、转存文件cgi程序


#目标
target=	$(test_log) \
		$(test_upload) \
		$(test_redis) \
		$(test_sql_redis) \
		$(login.cgi) \
		$(reg.cgi) \
		$(md5.cgi) \
		$(upload.cgi) \
		$(myfiles.cgi) \
		$(dealfile.cgi) \
		$(sharefiles.cgi) \
		$(dealsharefile.cgi)

ALL:$(target)

#生成所有的.o文件
$(obj):$(COMMON_PATH)/%.o:$(COMMON_PATH)/%.c
	$(CC) -c $< -o $@ $(CPPFLAGS) $(CFLAGS) 


#=================================test测试代码===================================
#test_log程序
$(test_log):	$(TEST_PATH)/test_log.o \
				$(COMMON_PATH)/make_log.o 
	$(CC) $^ -o $@ $(LIBS)

#upload程序
$(test_upload):	$(TEST_PATH)/upload_file.o \
				$(COMMON_PATH)/make_log.o 
	$(CC) $^ -o $@ $(LIBS)
	
#test_redis程序
$(test_redis):	$(TEST_PATH)/test_redis.o \
				$(COMMON_PATH)/make_log.o \
				$(COMMON_PATH)/redis_op.o
	$(CC) $^ -o $@ $(LIBS)
	
# mysql和redis配合使用
$(test_sql_redis):	$(TEST_PATH)/sql_redis.o \
					$(COMMON_PATH)/deal_mysql.o \
					$(COMMON_PATH)/redis_op.o \
					$(COMMON_PATH)/make_log.o 
	$(CC) $^ -o $@ $(LIBS)
	
#===============================cgi程序===========================
#登陆login.cgi程序
$(login.cgi):	$(CGI_SRC_PATH)/login_cgi.o \
				$(COMMON_PATH)/make_log.o  \
				$(COMMON_PATH)/cJSON.o \
				$(COMMON_PATH)/deal_mysql.o \
				$(COMMON_PATH)/redis_op.o  \
				$(COMMON_PATH)/cfg.o \
				$(COMMON_PATH)/util_cgi.o \
				$(COMMON_PATH)/des.o \
				$(COMMON_PATH)/base64.o \
				$(COMMON_PATH)/md5.o
	$(CC) $^ -o $@ $(LIBS)
	
#注册reg.cgi程序
$(reg.cgi):	$(CGI_SRC_PATH)/reg_cgi.o \
			$(COMMON_PATH)/make_log.o  \
			$(COMMON_PATH)/util_cgi.o \
			$(COMMON_PATH)/cJSON.o \
			$(COMMON_PATH)/deal_mysql.o \
			$(COMMON_PATH)/redis_op.o  \
			$(COMMON_PATH)/cfg.o
	$(CC) $^ -o $@ $(LIBS)
	
#md5.cgi秒传程序
$(md5.cgi):	$(CGI_SRC_PATH)/md5_cgi.o \
			$(COMMON_PATH)/make_log.o  \
			$(COMMON_PATH)/util_cgi.o \
			$(COMMON_PATH)/cJSON.o \
			$(COMMON_PATH)/deal_mysql.o \
			$(COMMON_PATH)/redis_op.o  \
			$(COMMON_PATH)/cfg.o
	$(CC) $^ -o $@ $(LIBS)
	
#upload.cgi上传程序
$(upload.cgi):	$(CGI_SRC_PATH)/upload_cgi.o \
			$(COMMON_PATH)/make_log.o  \
			$(COMMON_PATH)/util_cgi.o \
			$(COMMON_PATH)/cJSON.o \
			$(COMMON_PATH)/deal_mysql.o \
			$(COMMON_PATH)/redis_op.o  \
			$(COMMON_PATH)/cfg.o
	$(CC) $^ -o $@ $(LIBS)
	
#myfiles.cgi用户文件列表展示cgi程序
$(myfiles.cgi):	$(CGI_SRC_PATH)/myfiles_cgi.o \
			$(COMMON_PATH)/make_log.o  \
			$(COMMON_PATH)/util_cgi.o \
			$(COMMON_PATH)/cJSON.o \
			$(COMMON_PATH)/deal_mysql.o \
			$(COMMON_PATH)/redis_op.o  \
			$(COMMON_PATH)/cfg.o
	$(CC) $^ -o $@ $(LIBS)

#分享、删除文件、pv字段处理cgi程序
$(dealfile.cgi):$(CGI_SRC_PATH)/dealfile_cgi.o \
			$(COMMON_PATH)/make_log.o  \
			$(COMMON_PATH)/util_cgi.o \
			$(COMMON_PATH)/cJSON.o \
			$(COMMON_PATH)/deal_mysql.o \
			$(COMMON_PATH)/redis_op.o  \
			$(COMMON_PATH)/cfg.o
	$(CC) $^ -o $@ $(LIBS)
	
#sharefiles.cgi共享文件列表展示cgi程序
$(sharefiles.cgi):	$(CGI_SRC_PATH)/sharefiles_cgi.o \
			$(COMMON_PATH)/make_log.o  \
			$(COMMON_PATH)/util_cgi.o \
			$(COMMON_PATH)/cJSON.o \
			$(COMMON_PATH)/deal_mysql.o \
			$(COMMON_PATH)/redis_op.o  \
			$(COMMON_PATH)/cfg.o
	$(CC) $^ -o $@ $(LIBS)
	
#共享文件pv字段处理、取消分享、转存文件cgi程序
$(dealsharefile.cgi):	$(CGI_SRC_PATH)/dealsharefile_cgi.o \
			$(COMMON_PATH)/make_log.o  \
			$(COMMON_PATH)/util_cgi.o \
			$(COMMON_PATH)/cJSON.o \
			$(COMMON_PATH)/deal_mysql.o \
			$(COMMON_PATH)/redis_op.o  \
			$(COMMON_PATH)/cfg.o
	$(CC) $^ -o $@ $(LIBS)


#clean指令
clean:
	-rm -rf $(target) $(TEST_PATH)/*.o $(CGI_SRC_PATH)/*.o $(COMMON_PATH)/*.o

distclean:
	-rm -rf $(target) $(TEST_PATH)/*.o $(CGI_SRC_PATH)/*.o $(COMMON_PATH)/*.o

#将clean目标 改成一个虚拟符号
.PHONY: clean ALL distclean
