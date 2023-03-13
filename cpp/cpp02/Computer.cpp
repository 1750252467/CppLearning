#include<iostream>
#include<string.h>
using std::cout;
using std::endl;

class Computer
{
public:

    void setpp();
    void setBrand(const char *brand){
        strcpy(_brand,brand);
    }

    void setPrice(double  price){
        _price = price;
        
    }

    void printf(){
        cout<<"brand:"<<_brand<<endl;
        cout<<"price"<<_price<<endl;

    }

private:
    char _brand[20];
    double _price;
};


void Computer::setpp(){
    
    cout<<"pp"<<endl;

}



void test0(){
    int a=0;

    Computer c1;
    c1.setBrand("Lenovo");
    c1.setPrice(9999);

    c1.printf();
    c1.setpp();
}
int main(void){
    test0();
    return 0;
}















