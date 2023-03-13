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
//保存转换规则
// map<string,string> buildMap(ifstream & map_file)
// {
//     map<string,string> trans_map;
//     string key;
//     string value;
    
//     while(map_file >> key && getline(map_file,value)){
//         if(value.size() > 1){
//             trans_map[key] = value.substr(1);
//         }else{
//             throw runtime_error("no rule for" + key);
//         }
//     }
//     return trans_map;
// }

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

const string & transform(const string & s, const map<string,string> & m)
{
    auto map_it = m.find(s);

    if(map_it != m.end()){
        return map_it->second;
    }else{
        return s;
    }
}

void word_transform(ifstream & mapfile,ifstream & input)
{
    auto trans_map = buildMap(mapfile);
    
    string text;
    while(getline(input,text)){

        istringstream str(text);//避免频繁io,提高性能
        string word;
        bool firstword = true;
        while(str >> word){
            if(firstword){
                firstword = false;
            }else{
                cout << " ";
            }

            cout << transform(word,trans_map);
        }
        cout << endl;

    }
}


void test()
{
    string file1,file2;
    cout << "Please enter the rule file: ";
   cin >> file1;

    cout << "Please enter the file to be converted: ";
    cin >> file2;

    ifstream mapfile;
    mapfile.open(file1);

    ifstream input;
    input.open(file2);

    word_transform(mapfile,input);

    mapfile.close();
    input.close();
}

int main(void)
{
    test();
    return 0;

}













