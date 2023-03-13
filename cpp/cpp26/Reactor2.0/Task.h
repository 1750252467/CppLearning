#ifndef __Task_H__
#define __Task_H__


class Task
{
public:
    Task(){}

    virtual ~Task() {}
    
    virtual void process() = 0;


};




#endif
