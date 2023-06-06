#include <alibabacloud/oss/OssClient.h>
#include <string>
struct OSSInfo{
        std::string Bucket = "fyk-test1";                                                                                                         
        std::string EndPoint = "oss-cn-hangzhou.aliyuncs.com";
        std::string AccessKeyID = "LTAI5t6KqvrkaeTYkxjQvn5A";
        std::string AccessKeySecret = "9Iv4XknraYJPth7aSxTaGCG3zUh7Dp";
};
enum storeType {
    LOCAL,
    OSS
};
struct MQConfig{
    // 是否开启备份
    enum storeType CurrentStoreType = storeType::OSS;
    // 备份是否启用异步转移
    bool isAsyncTransferEnable = true;
    // 交换器的名称
    std::string transExchange = "uploadserver.trans";
    // routingkey
    std::string transRoutingKey = "oss";
};
