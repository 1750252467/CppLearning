#include <mysql/mysql.h>
#include <stdio.h>

int main(){
    MYSQL *conn = NULL;
    char *host = "localhost";
    char *user = "root";
    char *passwd = "a0b0";
    char *db ="45cpp";
    //初始化mysql句柄
    conn = mysql_init(NULL);
    //建立连接
    if(mysql_real_connect(conn,host,user,passwd,db,0,NULL,0)==NULL){
        printf("error:%s\n",mysql_error(conn));
        return EXIT_FAILURE;
    }
    //将编码设置为gbk
    if (mysql_query(conn, "set names gbk"))
    {
        return mysql_errno(conn);
    }

    //执行查询
    char *query ="select *from Student";
    //设置编码格式为utf8
    int ret = mysql_query(conn, "set names utf8");

     ret = mysql_query(conn,query);
    if(ret != 0){
        printf("error query1:%s\n",mysql_error(conn));
        return EXIT_FAILURE;
    }
    //4.获取结果集，N行数据
    //myaql_use_result不会直接保存查询结果
    //MYSQL_RES *result =mysql_use_result(conn);
    //mysql_store_result会直接把所有的查询结果存储下来
    MYSQL_RES* result =mysql_store_result(conn);
    if(result ==NULL){
        printf("error querry2: %s\n",mysql_error(conn));
        return EXIT_FAILURE;
    }

    int rows = mysql_num_rows(result);
    int cols = mysql_num_fields(result);
    printf("rows:%d,cols:%d\n",rows,cols);

    //5.获取每一行数据
    MYSQL_ROW row;
    while((row =mysql_fetch_row(result))!=NULL){//检查每行查询结果是否正确，
        for(int i = 0; i < cols;i++){
            printf("%10s",row[i]);
        }
        printf("\n");
    }
    //释放结果集
    mysql_free_result(result);
    //关闭连接
    mysql_close(conn);
    return 0;
}

