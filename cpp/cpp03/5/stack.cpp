#include<iostream>
using std::cout;
using std::endl;

class Stack {
public:
    Stack(int capacity=10)
    :_capacity(capacity)
    ,_rear(-1)
    ,_base(new int[_capacity]())//对于new 加上小括号才会做清零操作
    {
        cout<<"Stack(int)"<<endl;
    }
    ~Stack()
    {
        if(_base){
            delete [] _base;
            _base = nullptr;
        }
        cout<<"~Stack()"<<endl;
    }

	bool empty() const;	//判断栈是否为空
	bool full() const;	//判断栈是否已满
	void push(int); //元素入栈
	void pop();     //元素出栈
	int  top()const;		//获取栈顶元素
    void test(Stack *s) const;//测试用例

private:
    int _capacity;
    int  _rear;
    int *_base;
};

bool Stack::empty() const
{
    return _rear == -1; 
}

bool Stack::full() const
{
    return _rear == _capacity-1;
}

void Stack::push(int number) 
{
    if(!full()){
        _base[++_rear]=number;
    }else{
        cout<<"Stack is full"<<endl;
    }
}

void Stack::pop()
{
    if(!empty()){
       --_rear;
    }else{
        cout<<"Stack is empty"<<endl;
    }
}


int Stack::top() const
{
        return _base[_rear];    
}

void Stack::test(Stack *s) const
{
    for(int i=1;i<=15;i++)
    {   
        s->push(i);
        cout<<"入栈："<<s->top()<<endl;
    }
    for(int i=1;i<=15;i++){
        
        if(!empty())
            cout<<"出栈："<<s->top()<<endl;

        s->pop();
    }
}

void test0()
{

}

int main(void){
    Stack s;
    s.test(&s);
    return 0;

}
