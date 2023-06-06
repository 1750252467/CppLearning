#include "unixHeader.h"
#include "Mq.h"
#include "OSSInfo.h"
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <nlohmann/json.hpp>
using Json = nlohmann::json;
using namespace AmqpClient;
using namespace AlibabaCloud::OSS;
int main(){
    MQInfo mqinfo;
    OSSInfo OSSinfo;
    // 消费消息队列当中的数据
    Channel::ptr_t channel = Channel::Create();
    channel->BasicConsume(mqinfo.OSSQueue,mqinfo.OSSQueue);
    while(true){
        Envelope::ptr_t envelope;
        bool flag = channel->BasicConsumeMessage(envelope,15000);
        if(flag == false){
            fprintf(stderr,"time out\n");
            continue;
        }

        Json fileinfo = Json::parse(envelope->Message()->Body());
        std::string currentLocation = fileinfo["filepath"];
        std::string ossLocation = "oss/";
        ossLocation += fileinfo["filehash"];

        ClientConfiguration conf;
        OssClient client(OSSinfo.EndPoint,OSSinfo.AccessKeyID,OSSinfo.AccessKeySecret,conf);
        auto outcome = client.PutObject(OSSinfo.Bucket,ossLocation,currentLocation);
        if(outcome.isSuccess() == false){
        fprintf(stderr,"Fail, code = %s, msg = %s, requestID = %s\n", 
                outcome.error().Code().c_str(), 
                outcome.error().Message().c_str(),
                outcome.error().RequestId().c_str());
        }
    }
}
