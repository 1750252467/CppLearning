#include "Subject.hpp"
#include "Observer.hpp"

#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;

void Ring::attach(Observer *obj)
{
    auto it = std::find(_observerList.begin(),_observerList.end(),obj);
    if(it == _observerList.end()){
        _observerList.push_back(obj);
    }
}

void Ring::detach(Observer *obj)
{
    auto it = std::find(_observerList.begin(),_observerList.end(),obj);
    if(it != _observerList.end()){
        _observerList.erase(it);
    }

}

void Ring::notify()
{
    cout << "Ring is alarming!" <<endl;
    cout << "notify all Observers" << endl;
    for(auto & obj : _observerList){
        obj->update();
    }
}

void Ring::setState(State * state)
{
    _ringState.reset(state);//参数不为空时会先释放原来拥有的对象，再获取新对象的所有权
    RingState * p =dynamic_cast<RingState*>(_ringState.get());
    if(p && p->_flag == true){
        notify();
    }
}

State *Ring::getState() const
{
    return _ringState.get();
}


void Ring::bePressed()
{
    State *pstate = new RingState(true);
    setState(pstate);
}
