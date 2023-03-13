#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>

using namespace std;
//C++primer p432
class QueryResult;

class TextQuery
{
public:
    //使用类型别名等价地声明一个类型名字 p243页 Screen
    //line_no 代表行号，即vector中的下标
    using line_no = vector<string>::size_type;
    //
    TextQuery(ifstream&);
    //
    QueryResult query(const string&) const;

private:
    //输入文件vector<string>保存整个文件的一份拷贝
    //shared_ptr指向一个动态分配为空的vector<string>,以行号为下标
    shared_ptr<vector<string>> file;
    //set保存每个单词在文本中出现的行号，map用来将每个单词与它出现多个的行号关联起来
    //即每个单词到它所在的行号的集合的映射
    //shared_ptr指向一个动态分配的空set<line_no>
    map<string,shared_ptr<set<line_no>>> wordmap;

};

class QueryResult
{
    friend ostream &print(ostream &,const QueryResult &);
public:
    QueryResult(string s,
                shared_ptr<set<TextQuery::line_no>> p,
                shared_ptr<vector<string>> f)//指向保存输入文件的vector
                :sought(s)
                ,lines(p)
                ,file(f)
                {}
    set<TextQuery::line_no>::iterator begin() {return lines->begin();}
    set<TextQuery::line_no>::iterator end() {return lines->end();}
    shared_ptr<vector<string>> get_file() {return file;}
private:
    //这个查询所代表的单词
    string sought;
    shared_ptr<set<TextQuery::line_no>> lines;//指向保存单词出现行号的set
    shared_ptr<vector<string>> file;//指向输入文件的vector

};
//读取输入文件并建立单词到行号的映射
TextQuery::TextQuery(ifstream &is)
:file(new vector<string> )
{
    string text;
    while(getline(is,text)){ //获得文件中的每一行
        file->push_back(text);//保存此文本               
        int n = file->size()-1;//当前行号，以0下标开始存储
        istringstream line(text);//将文本分解为单词
        string word;
        while(line>>word){//
            //如果单词不在wordmap中，以之为下标在其中添加一项
            auto &lines = wordmap[word];//lines是一个shared_ptr
            if(!lines)//第一次遇到这个单词时，此指针为空，为避免重复插入同行中相同的单词
                lines.reset(new set<line_no>);//分配一个新的set
            lines->insert(n);//将此行号插入set中
        }
    }
}
//在map中定位对应的行号set
QueryResult TextQuery::query(const string& sought) const
{   //如果未找到sought，即单词，则返回一个指向此set的指针(空行号对象)，
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    //使用find来查找单词，避免添加单词到wordmap
    auto loc = wordmap.find(sought);
    if(loc == wordmap.end())
    {
        //未找到
        return QueryResult(sought,nodata,file);
    }else{
        return QueryResult(sought,loc->second,file);//second?
    }
}
//p201
//如果ctr的值大于1，返回Word的复数形式
string make_plural(size_t ctr,const string &word, const string &ending)
{
    return (ctr > 1)?word + ending : word;
}

ostream &print(ostream &os,const QueryResult &qr)
{   //如果找到了单词，打印出现的次数 和位置p434
    os << qr.sought << "occurs" <<qr.lines->size() <<" "
        <<make_plural(qr.lines->size(),"time","s") << endl;//s?
    //打印单词出现的每一行
    for(auto num :*qr.lines)
        os<<"\t(line"<<num+1<<")"
            <<*(qr.file->begin()+num)<<endl;
    return os;
}

//文本查询程序再探相关类的设计
//查询类的抽象基类
class Query_base
{
    friend class Query;
protected:
    //用于eval
    using line_no = TextQuery::line_no;
    //编译器将为显式声明的 default 函数自动生成函数体
    virtual ~Query_base() = default;
private:
    //eval返回与当前Query 匹配的QueryResult 
    virtual QueryResult eval(const TextQuery&) const =0;
    //rep表示查询的一个string
    virtual string rep() const =0;
};
//接口类，负责隐藏整个继承的类，指向Query_base的派生类对象
class Query
{
    friend Query operator ~(const Query &);
    friend Query operator |(const Query&,const Query&);
    friend Query operator &(const Query&,const Query&);
public:
    //构建一个新的WordQuery
    Query(const string&);
    //接口函数：调对应Query_base函数
    QueryResult eval(const TextQuery &t) const
    {
        return q->eval(t);
    }
    std::string rep() const
    {
        return q->rep();
    }
private:
    Query(shared_ptr<Query_base> query)
    :q(query)
    {}
    //指向Query_base
    std::shared_ptr<Query_base> q;
};

//用于查找一个给定的单词，唯一的实际执行查询
class WordQuery
:public Query_base
{
    friend class Query;//使用该类的构造函数
    WordQuery(const string &s):query_word(s){}

    //定义所有继承来的纯虚函数
    QueryResult eval(const TextQuery &t) const
    {
        return t.query(query_word);
    }

    string rep()const
    { return query_word; }

private:
    string query_word;//要查找的单词
};

//没有出现的行的集合
class NotQuery
:public Query_base
{
    friend Query operator~(const Query &);

    NotQuery(const Query &q):query(q){}
    
    string rep()const
    {return "~("+query.rep()+")";}

    QueryResult eval(const TextQuery &)const;

private:
    Query query;
};

//BinaryQuery 没有定义eval，而是继承了该纯虚函数，所以BinaryQuery也是一个纯虚函数

class BinaryQuery
:public Query_base 
{
protected:
    BinaryQuery(const Query &l,const Query &r,string s)
    :lhs(l)
    ,rhs(r)
    ,opSym(s)
    {}

    string rep() const
    { return "("+lhs.rep()+" "+ opSym +" "+rhs.rep()+ ")"; }

    Query lhs,rhs;//左侧和右侧运算对象
    string opSym;//运算符名字
};

//继承了rep，但覆盖了eval
class AndQuery
:public BinaryQuery
{
    friend Query operator&(const Query&,const Query &);
    AndQuery(const Query &left,const Query &right)
    :BinaryQuery(left,right,"&")
    {}

    QueryResult eval(const TextQuery&) const;
};

class OrQuery
:public BinaryQuery
{
    friend Query operator|(const Query&,const Query &);
    OrQuery(const Query &left,const Query &right)
    :BinaryQuery(left,right,"|")
    {}

    QueryResult eval(const TextQuery&) const;
};
//分配一个WorldQuery，然后令其指针成员指向新分配的对象
inline Query::Query(const string &s)
:q(new WordQuery(s))
{}

inline Query operator~(const Query &operand)
{   //分配一个NotQuery对象，并将其指针绑定到一个shaed_ptr<Query_base>
    return shared_ptr<Query_base>(new NotQuery(operand));
}

inline Query operator&(const Query &lhs,const Query &rhs)
{
    return shared_ptr<Query_base>(new AndQuery(lhs,rhs));
}

inline Query operator|(const Query &lhs,const Query &rhs)
{
    return shared_ptr<Query_base>(new OrQuery(lhs,rhs));
}
//返回 运算对象查询结果set的并集
QueryResult OrQuery::eval(const TextQuery& text) const
{
    //通过Query成员lhs和rhs进行的虚调用
    //调用eval返回每个运算对象的QueryResult
    auto right = rhs.eval(text),left = lhs.eval(text);
    //将左侧运算对象的行号拷贝到结果set中
    auto ret_lines = make_shared<set<TextQuery::line_no>>(left.begin(),left.end());
    //插入右侧运算对象所得的行号
    ret_lines->insert(right.begin(),right.end());
    //返回一个新的QueryResult，它表示lhs和rhs的并集
    //get_file都是指向同一文件的
    return QueryResult(rep(),ret_lines,left.get_file());
}
//返回查询结果的交集
QueryResult AndQuery::eval(const TextQuery& text) const
{   //
    auto right = rhs.eval(text),left = lhs.eval(text);
    //初始化set为空
    auto ret_lines = make_shared<set<TextQuery::line_no>>();
    //标准算法库，合并set
    set_intersection(left.begin(),left.end(),
                     right.begin(),right.end(),
                     inserter(*ret_lines,ret_lines->begin()));
    //将两个范围的交集一起写入一个目的的迭代器中
    return QueryResult(rep(),ret_lines,left.get_file());
}
//返回set中不存在的行，
QueryResult NotQuery::eval(const TextQuery& text)const
{   //
    auto result =query.eval(text);
    //开始时结果为空，初始化set为空。
    auto ret_lines = make_shared<set<TextQuery::line_no>>();
    //对对象出现的所有行进行迭代
    auto beg = result.begin(), end = result.end();
    //对于输入文件的每一行，如果该行不在result中，则将其添加到ret_lines 
    auto sz = result.get_file()->size();
    for(size_t n=0;n!=sz;++n)
    {   //检查当前行是否存在
        if(beg ==end||*beg!=n)
            ret_lines->insert(n);//不在，添加
        else if(beg != end)
            ++beg;//继续读取
    }
    return QueryResult(rep(),ret_lines,result.get_file());
}

std::ostream& operator <<(ostream &os,const Query & query)
{
    return os<<query.rep();
}

void InputFile(ifstream &file)
{
    TextQuery tp(file);
    while(true)
    {
        begin:
        cout<<"enter word to look for,or q to quit"<<endl;
        string s;
        if(!(cin>>s)||s=="q")
        {
            break;
        }
        //解析命令
        if(s[0]=='~')
        {
            s.replace(0,1,"");
            Query q =~Query(s);
            QueryResult locs = q.eval(tp);
            print(cout,locs)<<endl;
            continue;
        }
        for(int i=0;i<s.size();i++)
        {
            if(s[i] == '|')
            {
                string left(s.substr(0,i));
                string right(s.substr(i+1,s.size()-i-1));
                Query q = Query(left) | Query(right);
                QueryResult locs =q.eval(tp);
                print(cout,locs)<<endl;
                goto begin;
            }else if(s[i] == '&')
            {
                string left(s.substr(0,i));;
                string right(s.substr(i+1,s.size()-i-1));
                Query q = Query(left) & Query(right);
                QueryResult locs = q.eval(tp);
                print(cout,locs)<<endl;
                goto begin;
            }
        }
        print(cout,tp.query(s))<<endl;
    }
}

int main(void)
{
    string filename;
    cout<<"please enter filename:"<<endl;
    cin>>filename;
    ifstream file(filename);
    if(!file)
    {
        cout<<"filename error"<<endl;
        return -1;
    }
    InputFile(file);
    return 0;
}
































