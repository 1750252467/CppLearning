#include <string>
struct MQInfo{
    std::string URL = "amqp://guest:guest@127.0.0.1:5672";
    std::string Exchange = "uploadserver.trans";
    std::string OSSQueue = "uploadserver.trans.oss";
    std::string RoutingKey = "oss";
};