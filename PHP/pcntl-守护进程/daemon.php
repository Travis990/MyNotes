<?php
 
$pid = pcntl_fork();
if ($pid < 0) {
	exit(0); # fork子进程失败 -1
}elseif($pid){ # 父进程
    exit(0); 
}else{
	$sid = posix_setsid(); # 让子进程升级为会话
	if ($sid < 0) exit;

	chdir('./'); # 设置工作路径

	# 关闭用不到的文件描述符
	fclose(STDIN);
	fclose(STDOUT);
	fclose(STDERR);

	# 执行核心代码
	for(;;)
	{
		file_put_contents('log.txt', time().PHP_EOL, FILE_APPEND);
		sleep(5);
	}

}

