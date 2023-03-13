#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
using std::cout;
using std::endl;
using std::unordered_map;
using std::string;
using std::vector;
using std::queue;
using std::unordered_set;

class Solution
{
public:
    int ladderLength(string start, string end, vector<string>& a)
    {
        unordered_map<string,int> dist;
        unordered_set<string> dict(a.begin(),a.end());
        //终点不在字典中，返回0
        if(!dict.count(end)) return 0;
        queue<string> q;
        //将起点加入队列以及距离数组
        q.push(start), dist[start] = 1;
        while(q.size())
        {
            auto t = q.front();
            q.pop();
            int distance = dist[t];
            //枚举所有字符的扩展方式；先枚举扩展的位置，再枚举被替换的字符
            for(int i = 0,n = t.size(); i < n; i++)
            {
                string copy = t;
                for(int j = 0; j < 26; j++)
                {

                    //位置 i 上的字符没有被替换
                    if('a'+j == t[i]) continue;
                    //位置 i上的字符被替换为j
                    copy[i] = 'a'+j;
                    //
                    if(copy == end) return distance + 1;
                    //
                    if(!dict.count(copy) || dist.count(copy)) continue;
                    //
                    dist[copy] = distance + 1, q.push(copy);

                }
            }
        }
        return 0;
    }

};


void test()
{
    Solution s;
    
    string begin1("hit"),end1("cog");
    vector<string> a = {"hot", "dot", "dog", "lot", "log", "cog"};

   cout <<  s.ladderLength(begin1,end1,a) << endl;


    string begin2("hit"),end2("cog");
    vector<string> b = {"hot", "dot", "dog", "lot", "log"};
   cout <<  s.ladderLength(begin2,end2,b) << endl;

}

int main(void)
{
    test();
    return 0;
}











