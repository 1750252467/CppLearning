#include<iostream>
#include<string.h>
using std::cout;
using std::endl;

class Student
{
public:
    Student(int num,const char *name,int age)
    :_num(num)
    ,_age(age)
    {
        strcpy(_name,name);

    }
    void print();

private:
    int _num;
    char _name[20];
    int _age;
};


void Student::print(){
    Student *s;
    cout<<"num:"<<s->_num<<endl;
    cout<<"name:"<<s->_name<<endl;

    
    cout<<"age"<<s->_age<<endl;
    cout<<endl;

}

int main(){
    Student A(1,"naxitan",18);
     A.print();   

    Student B(2,"qiqi",18);
    Student C(3,"shatan",18);
    Student D(4,"keli",18);
        
    A.print();
    B.print();
    C.print();
    D.print();

    return 0;
}
