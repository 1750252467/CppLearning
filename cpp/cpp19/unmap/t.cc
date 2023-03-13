#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <stdexcept>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::ifstream;
using std::runtime_error;
using std::istringstream;

map<string, string> buildMap(ifstream & map_file)
{
    map<string, string> trans_map; // 保存转换规则
    string key; // 要替换的单词
    string value; // 替换后的内容
    // 读取第一个单词存入key中,行中剩余内容存入value
    while (map_file >> key && getline(map_file, value)) {
        if (value.size() > 1) { // 检查是否有转换规则
            trans_map[key] = value.substr(1); // 跳过前导空格
        } else {
            throw runtime_error("no rule for " + key);
        }
    }
    return trans_map;
}

const string & transform(const string & s, const map<string, string> & m)
{
    // 实际的转换工作
    auto map_it = m.find(s);
    // 如果单词在转换规则map中
    if (map_it != m.end()) { // 构造函数：const_iterator cend() const;
                             // 返回容器最后一个元素后的元素的迭代器，类似end()
        return map_it->second; // 使用替换短语
    } else {
        return s; // 否则返回原string
    }
}

void word_transform(ifstream & mapfile, ifstream & input)
{
    auto trans_map = buildMap(mapfile); // 保存转换规则
    string text; // 保存输入中的每一行
    while (getline(input, text)) { // 读取一行输入
        //cout << text << endl;
        istringstream str(text); // 读取每个单词
        string word;
        bool firstword = true; // 控制是否打印空格
        while (str >> word) {
            if (firstword){
                firstword = false;
            } else {
                cout << " "; // 在单词间打印一个空格
            }
            /* cout << "word = " << word << endl; */
            cout << transform(word, trans_map); // 打印输出
        }
        cout << endl; // 完成一行的转换
    } 
    /* cout << endl; */
    /* for(auto & it : trans_map){ */
    /*     cout << it.first << ", " << it.second << endl; */
    /* } */
}

void test0()
{
    string file1, file2;
    cout << "Please enter the rule file: ";
    cin >> file1; // map.txt 

    cout << "Please enter the file to be converted: ";
    cin >> file2; // file.txt 
    
    ifstream mapfile;
    mapfile.open(file1); // map.txt只读打开就可以

    ifstream input;
    input.open(file2); // 读

    word_transform(mapfile, input);

    mapfile.close();
    input.close();
}

int main(int argc, char **argv)
{
    test0();

    return 0;
}

/*
测试代码：
Please enter the rule file: rules
Please enter the file to be converted: text
where are you
why dont you send me a picture
okay? thanks! later
*/