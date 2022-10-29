/**
 * 当C++工程较大时，程序内存在大量的变量、函数和类，如果这些变量、函数和类都存在于同一个作用域中，
 * 一不小心就可能会导致命名冲突。为了解决这个问题，C++引入了命名空间(namespace)这个概念，这样在不
 * 同的命名空间中允许存在同名的标识符。
*/

#include <iostream>  
namespace N1 //定义命名空间N1  
{  
    int a = 10;  
}  
namespace N2 //定义命名空间N2  
{  
    int a = 30;  
}  
int main()  
{  
    int a = 50;  
    printf("N1::a = %d\n", N1::a); //输出命名空间N1中的成员变量a  
    printf("N2::a = %d\n", N2::a); //输出命名空间N2中的成员变量a  
    printf("a = %d\n",a);//输出主函数中的变量a  
    return 0;  
} 
