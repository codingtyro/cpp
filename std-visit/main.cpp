#include <iostream>
#include <variant>
#include <string>
 
struct MyVisitor
{
    void operator()(double d) const {
        std::cout << d << '\n';
    }
    void operator()(int i) const {
        std::cout << i << '\n';
    }
    void operator()(const std::string& s) const {
        std::cout << s << '\n';
}
};
int main()
{
    std::variant<int, double, std::string> var1(42), var2(3.14), var3("visit");
 
    std::visit(MyVisitor(), var1); // calls operator() for matching int type
 
    std::visit(MyVisitor(), var2); // calls operator() for matching double type
 
    std::visit(MyVisitor(), var3); // calls operator() for matching std::string type
 
    return 0;
}