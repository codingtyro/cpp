#include <iostream>
class Box {

public:
    //求面积
    double getVolume() {
        return length * width * height;
    }

    void setLength(double len) {
        this->length = len;
    }

    void setWidth(double width) {
        this->width = width;
    }

    void setHeight(double height) {
        this->height = height;
    }
    //重载 + 运算符 , 把两个 Box 相加
    Box operator+(const Box b) {

        Box box_;
        box_.length = this->length + b.length;
        box_.height = this->height + b.height;
        box_.width = this->width + b.width;

        return box_;
    }
    //重载 - 运算符 , 把两个 Box 相减 
    Box operator-(const Box b) {

        Box box_;
        box_.length = this->length - b.length;
        box_.width = this->width - b.width;
        box_.height = this->height - b.height;

        return box_;
    }

private:

    double length;
    double width;
    double height;

};


int main()
{
    Box a;
    a.setHeight(5);
    a.setWidth(5);
    a.setLength(2);

    std::cout << "a. volume:" << a.getVolume() << std::endl;

    Box b;
    b.setHeight(5);
    b.setWidth(5);
    b.setLength(5);

    std::cout << "b. volume:" << b.getVolume() << std::endl;

    Box c;

    c = a + b;

    std::cout << "c. volume:" << c.getVolume() << std::endl;



    Box d;

    d =  b  - a;

    std::cout << "d. volume:" << d.getVolume() << std::endl;

    system("pause");

    return 0;
}
