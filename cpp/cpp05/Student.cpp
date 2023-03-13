#include<iostream>
#include<string>
using std::cout;
using std::endl;
using std::string;

class Student
{
public:
    Student(int id,string name)
    :_id(id)
    ,_name(name)
    {
        cout<<"Student()"<<endl;
    }
    
    void * operator new(size_t sz){
        cout<<"void * operator new(size_t)"<<endl;
        return malloc(sz);
    }

    void operator delete(void *ret){
        cout<<"void * operator delete(void *ret)"<<endl;
        free(ret);
    }

    void print() const;
    
    void destory();
private:

    ~Student(){
        cout<<"~Student()"<<endl;
    }

    int _id;
    string _name;
};

void Student::print()const
{
    cout<<"id:"<<_id<<endl;
    cout<<"name:"<<_name<<endl;
}

void Student::destory(){
    delete this;
}
void test0()
{
    cout<<"sizeof(Student):"<<sizeof(Student)<<endl;    
    Student *s = new Student(1,"纳西妲");
    s->print();
    
    s->destory();
}

int main(){
    test0();
    return 0;
}




