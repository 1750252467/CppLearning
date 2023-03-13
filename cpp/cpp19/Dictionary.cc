#include <time.h> 

#include <iostream>
#include <map>
#include <string>
#include <fstream>

using std::cout;
using std::endl;
using std::cin;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::map;


class Dictionary
{
public:
    void read(const string &filename);
    void store(const string &filename);
private:
    map<string,int> _dict;
};


void Dictionary::read(const string &filename)
{
    ifstream ifs;
    ifs.open(filename);
    if(!ifs.good()){
        cerr << "ifs open file error\n";
        return;
    }
    string word;
    
    while(ifs >> word){
        bool isLegal = 0;
        for(auto & ch : word){//判断单词是否合法
            if(ch > 'a' && ch < 'z' || ch > 'A' && ch < 'z'){
                isLegal = 1;
            }else{
                isLegal = 0;
                break;
            }
        }
        if(isLegal){//记录词频
            if(_dict.count(word) > 0){
                int tmp = _dict[word];
                ++tmp;
                _dict[word] = tmp;
            }else{
                _dict[word] = 1;
            }
        }
    }

    cout << "读取结束" << endl;
    ifs.close();
}

void Dictionary::store(const std::string &filename)
{
    ofstream ofs;
    ofs.open(filename);
    if(!ofs.good()){
        cerr << "ofstream open file error\n";
    }
    for(auto & elem : _dict)
    {
        ofs << elem.first << " " << elem.second << endl;
    }

    ofs.close();
}

void test()
{
    Dictionary d;
    string filename;
    cout << "Please enter an absolute path to a file:";
    cin >> filename;

    clock_t startTime,endTime;
    startTime = clock();
    d.read(filename);
    d.store("Dictionary.txt");
    endTime = clock();

    cout << "The run time is :" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    cout << "The memory of file" << filename << "has been saved to file Dictionary.txt" << endl;

}

int main(void)
{
    test();
    return 0;

}
























