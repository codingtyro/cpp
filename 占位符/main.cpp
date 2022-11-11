#include <functional>
#include <string>
#include <iostream>

/**
 * std::bind的两个作用
 * 将可调用对象和其参数绑定成一个仿函数；
 * 只绑定部分参数，减少可调用对象传入的参数。
*/

void goodbye(const std::string& s) {
    std::cout << "Goodbye " << s << '\n';
}

class Object {
  public:
    void hello(const std::string& s) {
        std::cout << "Hello " << s << '\n';
    }
};

/**
 * 取别名的两种方法
*/
using ExampleFunction = std::function<void(const std::string&)> ;
// typedef std::function<void(const std::string&)> ExampleFunction;
int main() {
    Object instance;
    std::string str("World");
    ExampleFunction f = std::bind(&Object::hello, &instance,
                                  std::placeholders::_1);

    // equivalent to instance.hello(str)
    f(str);
    f = std::bind(&goodbye, std::placeholders::_1);

    // equivalent to goodbye(str)
    f(str);


    auto callableFunc =  [](double x, double y,double z) {return x / y + z;};
    //可以合理地使用占位符
    auto NewCallable = std::bind (callableFunc, std::placeholders::_1,2,std::placeholders::_2);  
    std::cout << NewCallable (10,5) << '\n';                       
    return 0;
}
