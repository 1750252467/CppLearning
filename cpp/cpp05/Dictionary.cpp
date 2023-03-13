#include<iostream>
#include<fstream>
#include<vector>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

struct Record
{
    string _word;
    int _frequency;
    Record(string w,int f)
    :_word(w)
    ,_frequency(f)
    {}
};

class Dictionary
{
public:
    void read(const std::string &filename);
    void store(const std::string &filename);
private:
    vector<Record> _dict;
};

void Dictionary::read(const std::string &filename)
{
    ifstream ifs;
    ifs.open(filename);
    if(!ifs.good()){
        cerr<<"ifs open file error\n";
        return;
    }
    string word;
    cout<<"_dict'size:"<<_dict.size()<<endl;
    cout<<"_dict'capacity:"<<_dict.capacity()<<endl;
    _dict.reserve(100);
    cout<<"_dict'size:"<<_dict.size()<<endl;
    cout<<"_dict'capacity:"<<_dict.capacity()<<endl;

    while(ifs >> word){
        bool isLegal = 0;
        for(auto & ch : word){
            if(ch > 'a'&& ch < 'z'|| ch > 'A'&& ch < 'Z'){
                isLegal = 1;
            }else{
                isLegal = 0;
                break;
            }
        }
        if(isLegal){
            int flag = 0;
            for(int i = 0;i < _dict.size();++i){
                if(_dict[i]._word == word){
                    _dict[i]._frequency += 1;
                    flag = 1;
                    break;
                }
            }
            if(!flag){
                _dict.emplace_back(word,1);
            }
        }
    }
    cout<<"_dict'size:"<<_dict.size()<<endl;
    cout<<"_dict'capacity()"<<endl;

    _dict.shrink_to_fit();
    cout<<"_dict'size:"<<_dict.size()<<endl;
    cout<<"_dict'capacity:"<<_dict.capacity()<<endl;

    cout<<"读取结束"<<endl;

}

void Dictionary::store(const std::string &filename)
{
    ofstream ofs;

    ofs.open(filename);
    if(!ofs.good()){
        cerr<<"ofstream open file error\n";
        return;
    }

    for(int i = 0;i < _dict.size();++i){
        ofs<<_dict[i]._word<<" "<<_dict[i]._frequency<<"\n";
    }

    ofs.close();
}

void test0()
{
    Dictionary d;
    string filename;
    cout<<"Please enter an absolute path to a file:";
    cin>>filename;
    d.read(filename);

    d.store("Dictionary.txt");
    cout<<"The memory of file"<<filename<<" has been saved to file Dictionary.txt"<<endl;

}

int main(int argc, char **argv)
{

    test0();

    return 0;
}
