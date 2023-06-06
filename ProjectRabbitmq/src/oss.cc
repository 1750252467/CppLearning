#include <alibabacloud/oss/OssClient.h>

using namespace AlibabaCloud::OSS;
#include <string>
struct OSSInfo{
    std::string Bucket = "bucket-liaozs-test1";
    std::string EndPoint = "oss-cn-hangzhou.aliyuncs.com";
    std::string AccessKeyID = "LTAI5tLEWyaQW2AamggUfwLm";
    std::string AccessKeySecret = "epyJasbhulgKHdOISGnOQdlSJYog9s";
};
int main(void){
    /* 初始化网络等资源。*/
    InitializeSdk();
    ClientConfiguration conf;
    OSSInfo info;
    OssClient client(info.EndPoint, info.AccessKeyID, info.AccessKeySecret, conf);
    //上传文件的请求
    std::string objectPath = "test/1.txt";//指定文件在OSS当中的路径
    time_t expire = time(nullptr) + 1200;
    auto outcome = client.GeneratePresignedUrl(info.Bucket,objectPath,expire,Http::Get);
    if(outcome.isSuccess() == false){
        fprintf(stderr,"Fail, code = %s, msg = %s, requestID = %s\n", 
                outcome.error().Code().c_str(), 
                outcome.error().Message().c_str(),
                outcome.error().RequestId().c_str());
    }
    else{
        fprintf(stderr,"Url = %s\n",outcome.result().c_str());
    }
    // auto outcome = client.PutObject(info.Bucket,objectPath,"tmp/1.txt");//第三个参数填写文件在本地的路径
    // if(outcome.isSuccess() == false){
    //     fprintf(stderr,"Fail, code = %s, msg = %s, requestID = %s\n", 
    //             outcome.error().Code().c_str(), 
    //             outcome.error().Message().c_str(),
    //             outcome.error().RequestId().c_str());
    // }
    /* 释放网络等资源。*/
    ShutdownSdk();
    return 0;
}