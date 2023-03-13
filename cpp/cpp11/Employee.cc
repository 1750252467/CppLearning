#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Person
{
public:

    Person(string name,int age)
        :_name(name)
         ,_age(age)
    {}

    void display()
    {
        cout<<"name:"<<_name<<endl; 
        cout<<"age:"<<_age<<endl;
    }
private:
    string _name;
    int _age;
};

class Employee
:public Person
{
public:
    Employee(string name,int age,string department,int salary)
        :Person(name,age)
         ,_department(department)
         ,_salary(salary)
    {
        _sumSalary+=_salary;
        _sumPerson++;
    }

    void display()
    {
        Person::display();
        cout<<"department:"<<_department<<endl;
        cout<<"salary:"<<_salary<<endl;
        cout<<endl;
        cout<<endl;
    }

    static double averageSalary()
    {
        return _sumSalary/_sumPerson; 
    }
private:
    string _department;
    double _salary;
    static double _sumSalary;
    static int _sumPerson;
};


double Employee::_sumSalary = 0;

int  Employee::_sumPerson = 0;



void test()
{
    Employee e1("可莉",8,"矮子大队",8888);
    Employee e2("迪奥娜",12,"矮子大队",8888);
    Employee e3("七七",1500,"矮子大队",8888);
    Employee e4("纳西妲",8,"矮子大队",88888);
    Employee e5("旱柚",16,"矮子大队",8888);
    e1.display();
    e2.display();
    e3.display();
    e4.display();
    e5.display();

    cout<<"平均工资"<<Employee::averageSalary()<<endl;


}


int main(void)
{
    test();
    return 0;
}
