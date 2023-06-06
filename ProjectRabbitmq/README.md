<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [README](#readme)
  - [简介](#%E7%AE%80%E4%BB%8B)
  - [启动步骤](#%E5%90%AF%E5%8A%A8%E6%AD%A5%E9%AA%A4)
  - [Web](#web)
  - [OSS](#oss)
  - [Nginx](#nginx)
  - [RabbitMQ](#rabbitmq)
  - [MySQL](#mysql)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# README

## 简介

企业私有云是指建立在企业内部网络上的云计算环境，为企业提供基于云计算的IT服务。相比于公共云，企业私有云更加安全可控，并且可以根据企业的特定需求进行定制化开发。本文是在基于用户登录，注册，上传，下载基本功能的基础上，采用Nginx分流下载的简单任务来实现负载均衡，以及高并发，使用阿里云备份来避免文件因物理等因素丢失，重在实现和优化存储这一。

## 启动步骤

主服务器---Nginx---RabbitMQ

## Web

```SHELL
http://192.168.128.140:1234/user/signup

sha1sum test.pdf 

```

## OSS

```C++
https://www.aliyun.com/
```



## Nginx

```shell
cd /usr/local/nginx
su root 

cd conf


启动配置文件
sbin/nginx -c conf/9_download.conf
关闭配置文件
sbin/nginx -s quit -c conf/9_download.conf

netstat -apn  |  grep 1235


worker_processes 1;  # 设置工作进程数为1，表示只有1个进程在处理请求
error_log  logs/error.log;  # 错误日志的存放路径
#error_log  logs/error.log  notice;  # 错误级别为notice的日志不写入文件
#error_log  logs/error.log  info;  # 错误级别为info的日志不写入文件

events {
    worker_connections  1024;  # 最大连接数为1024
}

http {
    #include       mime.types;  # 包含mime.types文件

    log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
                      '$status $body_bytes_sent "$http_referer" '
                      '"$http_user_agent" "$http_x_forwarded_for"';  # 定义access log的格式
    access_log  logs/access09.log  main;  # access log的存放路径和格式
    default_type  application/octet-stream;  # 默认MIME类型为application/octet-stream
    sendfile        on;  # 开启sendfile功能
    keepalive_timeout  65;  # keepalive连接超时时间为65秒

    server {
        listen       1235;  # 监听端口号为1235
        server_name  localhost;  # 服务器名称为localhost

        location / {  # 处理根路径的请求
            root  /home/fyk/45cpp/http/project/tmp;  # 根目录为/home/fyk/45cpp/http/project/tmp
        }

        error_page   500 502 503 504  /50x.html;  # 定义错误页面的URI
        location = /50x.html {
            root   html;  # 错误页面的文件路径为html/50x.html
        }
    }
}
```

## RabbitMQ

```C++
docker -ps -a
    
docker stop ID    

docker rm ID #输入上面查到的ID
    
sudo docker run -d --hostname rabbitsvr --name rabbit -p 5672:5672 -p 15672:15672 -p 25672:25672 -v /root/data/rabbitmq:/var/lib/rabbitmq rabbitmq:management

http://192.168.128.140:15672/


关闭 
docker stop ID 
```



## MySQL

```Shell
http://192.168.128.140:1234/user/signup

mysql -u root -p



show databases;

use clouddisk;

truncate tbl_file;truncate tbl_user;truncate tbl_user_file;truncate tbl_user_token;

select * from tbl_user ;
```



```mysql
-- 创建文件表
CREATE TABLE `tbl_file` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `file_sha1` char(40) NOT NULL DEFAULT '' COMMENT '文件hash',
  `file_name` varchar(256) NOT NULL DEFAULT '' COMMENT '文件名',
  `file_size` bigint(20) DEFAULT '0' COMMENT '文件大小',
  `file_addr` varchar(1024) NOT NULL DEFAULT '' COMMENT '文件存储位置',
  `create_at` datetime default NOW() COMMENT '创建日期',
  `update_at` datetime default NOW() on update current_timestamp() COMMENT '更新日期',
  `status` int(11) NOT NULL DEFAULT '0' COMMENT '状态(可用/禁用/已删除等状态)',
  `ext1` int(11) DEFAULT '0' COMMENT '备用字段1',
  `ext2` text COMMENT '备用字段2',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_file_hash` (`file_sha1`),
  KEY `idx_status` (`status`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- 创建用户表
CREATE TABLE `tbl_user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_name` varchar(64) NOT NULL DEFAULT '' COMMENT '用户名',
  `user_pwd` varchar(256) NOT NULL DEFAULT '' COMMENT '用户encoded密码',
  `email` varchar(64) DEFAULT '' COMMENT '邮箱',
  `phone` varchar(128) DEFAULT '' COMMENT '手机号',
  `email_validated` tinyint(1) DEFAULT 0 COMMENT '邮箱是否已验证',
  `phone_validated` tinyint(1) DEFAULT 0 COMMENT '手机号是否已验证',
  `signup_at` datetime DEFAULT CURRENT_TIMESTAMP COMMENT '注册日期',
  `last_active` datetime DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '最后活跃时间戳',
  `profile` text COMMENT '用户属性',
  `status` int(11) NOT NULL DEFAULT '0' COMMENT '账户状态(启用/禁用/锁定/标记删除等)',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_username` (`user_name`),
  KEY `idx_status` (`status`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4;

-- 创建用户token表
CREATE TABLE `tbl_user_token` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_name` varchar(64) NOT NULL DEFAULT '' COMMENT '用户名',
  `user_token` char(40) NOT NULL DEFAULT '' COMMENT '用户登录token',
    PRIMARY KEY (`id`),
  UNIQUE KEY `idx_username` (`user_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- 创建用户文件表
CREATE TABLE `tbl_user_file` (
  `id` int(11) NOT NULL PRIMARY KEY AUTO_INCREMENT,
  `user_name` varchar(64) NOT NULL,
  `file_sha1` varchar(64) NOT NULL DEFAULT '' COMMENT '文件hash',
  `file_size` bigint(20) DEFAULT '0' COMMENT '文件大小',
  `file_name` varchar(256) NOT NULL DEFAULT '' COMMENT '文件名',
  `upload_at` datetime DEFAULT CURRENT_TIMESTAMP COMMENT '上传时间',
  `last_update` datetime DEFAULT CURRENT_TIMESTAMP 
          ON UPDATE CURRENT_TIMESTAMP COMMENT '最后修改时间',
  `status` int(11) NOT NULL DEFAULT '0' COMMENT '文件状态(0正常1已删除2禁用)',
  UNIQUE KEY `idx_user_file` (`user_name`, `file_sha1`),
  KEY `idx_status` (`status`),
  KEY `idx_user_id` (`user_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

truncate tbl_file;truncate tbl_user;truncate tbl_user_file;truncate tbl_user_token;


```

