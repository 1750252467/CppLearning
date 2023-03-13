
#include <iostream>

#include <sw/redis++/redis++.h>


using namespace sw::redis;
using std::cout;
using std::endl;

void testConnect()
{
    ConnectionOptions connection_options;
    connection_options.host = "127.0.0.1";  // Required.
    //connection_options.port = 6666; // Optional. The default port is 6379.
    //connection_options.password = "auth";   // Optional. No password by default.
    connection_options.db = 1;  // Optional. Use the 0th database by default.就是0号数据库

    // Optional. 在我们成功向redis发送请求或接收响应之前超时。
    // 默认情况下，超时时间为0ms，即永远不会超时并阻塞，直到我们成功发送或接收。
    // 注意:如果任何命令超时，我们会抛出TimeoutError异常。
    //connection_options.socket_timeout = std::chrono::milliseconds(200);
    
    Redis redis1(connection_options);

    ConnectionPoolOptions pool_options;
    pool_options.size = 3;  // 池大小，即最大连接数

    // Optional. 等待连接的最大时间。默认为0ms，意味着永远等待.
    // 假设连接池的大小是3，当有4个线程尝试获取连接时，其中一个会被阻塞。
    pool_options.wait_timeout = std::chrono::milliseconds(100);

    // Optional. 连接的最大生存时间。默认为0ms，这意味着连接永远不会过期。
    // 如果连接已经创建了很长时间，即超过`connection_lifetime`，
    // 它将过期并重新连接。
    pool_options.connection_lifetime = std::chrono::minutes(10);

    //set 命令
    auto redis = Redis("tcp://127.0.0.1:6379");//先创建对象，重复使用
    // 用c风格的字符串隐式构造StringView。相当于set命令
    redis.set("key1", "value1");
    redis.set("key2", "value2");
    redis.set("key3", "value3");

        // Or just: auto val = redis.get("key");
    Optional<std::string> val = redis.get("key1");

    //get命令
    // Optional<T> has a conversion to bool.
    // If it's NOT a null Optional<T> object, it's converted to true.
    // Otherwise, it's converted to false.
    if (val) {
        // Key exists. Dereference val to get the string result.
        std::cout << *val << std::endl;
    } else {
        // Redis server returns a NULL Bulk String Reply.
        // It's invalid to dereference a null Optional<T> object.
        std::cout << "key doesn't exist." << std::endl;
    }
    //mget命令
    std::vector<Optional<std::string>> values;
    redis.mget({"key1", "key2", "key3"}, std::back_inserter(values));
    for (const auto &val : values) {
        if (val) {
            std::cout << *val << std::endl;
            // Key exist, process the value.
        }
    }

// // Implicitly construct StringView with std::string.
// std::string key("key");
// std::string val("value");

// redis.set(key, val);

// // Explicitly pass StringView as parameter.
// std::vector<char> large_data;
// // Avoid copying.
// redis.set("key", StringView(large_data.data(), large_data.size()));

// // ***** Parameters of long long type *****

// // For index.
// redis.bitcount(key, 1, 3);

// // For number.
// redis.incrby("num", 100);

// // ***** Parameters of double type *****

// // For score.
// redis.zadd("zset", "m1", 2.5);
// redis.zadd("zset", "m2", 3.5);
// redis.zadd("zset", "m3", 5);

// // For (longitude, latitude).
// redis.geoadd("geo", std::make_tuple("member", 13.5, 15.6));

//     // ***** Time-related parameters *****

// using namespace std::chrono;

// redis.expire(key, seconds(1000));

// auto tp = time_point_cast<seconds>(system_clock::now() + seconds(100));
// redis.expireat(key, tp);

// // ***** Some options for commands *****

// if (redis.set(key, "value", milliseconds(100), UpdateType::NOT_EXIST)) {
//     std::cout << "set OK" << std::endl;
// }

// redis.linsert("list", InsertPosition::BEFORE, "pivot", "val");

// std::vector<std::string> res;

// // (-inf, inf)
// redis.zrangebyscore("zset", UnboundedInterval<double>{}, std::back_inserter(res));

// // [3, 6]
// redis.zrangebyscore("zset",
//     BoundedInterval<double>(3, 6, BoundType::CLOSED),
//     std::back_inserter(res));

// // (3, 6]
// redis.zrangebyscore("zset",
//     BoundedInterval<double>(3, 6, BoundType::LEFT_OPEN),
//     std::back_inserter(res));

// // (3, 6)
// redis.zrangebyscore("zset",
//     BoundedInterval<double>(3, 6, BoundType::OPEN),
//     std::back_inserter(res));

// // [3, 6)
// redis.zrangebyscore("zset",
//     BoundedInterval<double>(3, 6, BoundType::RIGHT_OPEN),
//     std::back_inserter(res));

// // [3, +inf)
// redis.zrangebyscore("zset",
//     LeftBoundedInterval<double>(3, BoundType::RIGHT_OPEN),
//     std::back_inserter(res));

// // (3, +inf)
// redis.zrangebyscore("zset",
//     LeftBoundedInterval<double>(3, BoundType::OPEN),
//     std::back_inserter(res));

// // (-inf, 6]
// redis.zrangebyscore("zset",
//     RightBoundedInterval<double>(6, BoundType::LEFT_OPEN),
//     std::back_inserter(res));

// // (-inf, 6)
// redis.zrangebyscore("zset",
//     RightBoundedInterval<double>(6, BoundType::OPEN),
//     std::back_inserter(res));

// // ***** Pair of iterators *****

// std::vector<std::pair<std::string, std::string>> kvs = {{"k1", "v1"}, {"k2", "v2"}, {"k3", "v3"}};
// redis.mset(kvs.begin(), kvs.end());

// std::unordered_map<std::string, std::string> kv_map = {{"k1", "v1"}, {"k2", "v2"}, {"k3", "v3"}};
// redis.mset(kv_map.begin(), kv_map.end());

// std::unordered_map<std::string, std::string> str_map = {{"f1", "v1"}, {"f2", "v2"}, {"f3", "v3"}};
// redis.hmset("hash", str_map.begin(), str_map.end());

// std::unordered_map<std::string, double> score_map = {{"m1", 20}, {"m2", 12.5}, {"m3", 3.14}};
// redis.zadd("zset", score_map.begin(), score_map.end());

// std::vector<std::string> keys = {"k1", "k2", "k3"};
// redis.del(keys.begin(), keys.end());

// // ***** Parameters of initializer_list type *****

// redis.mset({
//     std::make_pair("k1", "v1"),
//     std::make_pair("k2", "v2"),
//     std::make_pair("k3", "v3")
// });

// redis.hmset("hash",
//     {
//         std::make_pair("f1", "v1"),
//         std::make_pair("f2", "v2"),
//         std::make_pair("f3", "v3")
//     });

// redis.zadd("zset",
//     {
//         std::make_pair("m1", 20.0),
//         std::make_pair("m2", 34.5),
//         std::make_pair("m3", 23.4)
//     });

// redis.del({"k1", "k2", "k3"});


}



int main(void)
{
    testConnect();

    return 0;
}