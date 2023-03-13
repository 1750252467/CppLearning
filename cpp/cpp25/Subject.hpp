#ifndef __WD__SUBJECT_HPP__
#define __WD__SUBJECT_HPP__

#include <list>
#include <memory>
#include <iostream>

using std::list;
using std::cout;
using std::endl;
using std::shared_ptr;

class Observer;


class State
{
public:
    virtual void print() const = 0;
    virtual ~State() {}

};

class RingState
:public State
{
public:
    RingState(bool flag)
    :_flag(flag)
    {}

    void print() const override
    {        
        cout << "ring state:" << _flag << endl;
    }

    bool _flag;
};


class Subject
{
public:
    virtual void attach(Observer *obj) = 0;
    virtual void detach(Observer *obj) = 0;
    virtual void notify() = 0;
    virtual void setState(State* state) = 0;
    virtual State * getState() const = 0;
    virtual ~Subject(){}
};

class Ring 
:public Subject
{
public:
    void bePressed();
    virtual void attach(Observer * obj) override;
    virtual void detach(Observer *obj) override;
    virtual void notify() override;
    virtual void setState(State * state) override;
    virtual State * getState() const override;
private:
    list<Observer*> _observerList;
    shared_ptr<State> _ringState;
};


#endif
