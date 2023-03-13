#ifndef  __WD__OBSERVER__HPP__
#define __WD__OBSERVER__HPP__

#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

class Observer
{
public:
    virtual void update() = 0;

};


class Baby
:public Observer
{
 public:
    Baby(const string & name)
    :_name(name)
    {}

    void update() override;

    ~Baby() 
    { cout << "~Baby()" << endl;}

 private:
    string _name;
};

class Nurse
:public Observer
{
public:
    Nurse(const string &name)
    :_name(name)
    {}

    void update() override;

    ~Nurse()
    { cout << "~Nurse" << endl; }
private:
    string _name;
};

class Ring;

class Guest
{
public:
    Guest(const string & name)
    :_name(name)
    {}

    void knockAt(Ring &ring);

private:
    string _name;
};


#endif
