#include<iostream>
using std::cout;
using std::endl;

class Queue {
public:
    Queue(int capacity=10)
    :_capacity(capacity)
    ,_front(0)
    ,_rear(0)
    ,_base(new int[_capacity]())
    {
        cout<<"Queue(int)"<<endl;
    }

    ~Queue(){
        if(_base){
            delete [] _base;
            _base = nullptr;
        }
        cout<<"~Queue()"<<endl;
    }

    bool empty() const;	//判断栈是否为空
    bool full() const;	//判断栈是否已满
    void push(int); //元素入队
    void pop();     //元素出队
    int  front() const;	//获取队头元素
    int  back() const;	//获取队尾元素
     void test(Queue *q);//测试用例

private:
    int _capacity;
    int _front;
    int _rear;
    int *_base;

};

bool Queue::empty() const
{
    return _front == _rear;
}

bool Queue::full() const
{
    return( _rear+1)%_capacity == _front;
}

void Queue::push(int number)
{
    if(!full()){
        _base[_rear++]=number;//后置++，rear位置没有元素
        _rear %= _capacity;//循环数组实现队列
    }else{
        cout<<"queue is full"<<endl;
    }
}

void Queue::pop()
{
    if(!empty()){
        _front++;
        _front %= _capacity;//循环数组实现队列
    }else{
        cout<<"queue is empty"<<endl;
    }
}

int Queue::front() const
{
    return _base[_front];
}

int Queue::back() const
{
    return _base[(_rear - 1 + _capacity )% _capacity];
}

void Queue::test(Queue *q)
{
    for(int i=0;i<15;i++){
        q->push(i);
        if(!full())
        cout<<"入队" <<q->back()<<endl;
    }
    for(int i=0;i<15;i++){
        if(!empty())
        cout<< "出队"<<q->front()<<endl;
        q->pop();
    }
}

int main(void){
    Queue q;
    q.test(&q);
    return 0;
}

