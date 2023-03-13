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
    
    ~Student(){
        cout<<"~Student()"<<endl;
    }
    void print() const;
    
private:

    void * operator new(size_t sz);
    void operator delete(void *ret);

    int _id;
    string _name;
};

void Student::print()const
{
    cout<<"id:"<<_id<<endl;
    cout<<"name:"<<_name<<endl;
}

//void Student::destory(){
//    delete this;
//}
void test0()
{
    cout<<"sizeof(Student):"<<sizeof(Student)<<endl;    
    Student s(1,"纳西妲");
    s.print();
}

int main(){
    test0();
    return 0;
}




