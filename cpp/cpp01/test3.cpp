#include<iostream>
using std::cin;
using std::cout;
using std::endl;


namespace wd
{
//void print(){
//    int x;
//    cin>>x;
//    if(x++>5){
//        cout<<x<<endl;
//    }else
//    {
//        cout<<x--<<endl;
//    }
//}
//void print(){
//    int a[5]={1,2,3,4,5}; 
//    int *ptr=(int *)(&a+1); 
//    printf("%d,%d",*(a+1),*(ptr-1));
//
//}
//int  print(int x){
//    int countx = 0;
//    while(x)
//    {
//          countx++;
//          x = x&(x-1);
//    }
//    return countx;
//}

//void print(){
//    for(int i=0;-i<20;i--)
//        cout<<"hello"<<endl;
//}

static int hot=200;
void print(){
int &rad=hot;
hot = hot + 100;
cout<< rad << endl;
}
}

using wd::print;
int main(int argc,char **argv){

    print();
    return 0;
}
