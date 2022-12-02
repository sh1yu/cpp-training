//
// Created by psy on 2022/11/29.
//

#include <iostream>

/// 声明一个模版类ClassA
template<typename T>
class ClassA;

/// 实现模板类 ClassA
template<typename T>
class ClassA {
    T member;
};

/// 实现模版类 vector，在外部实现成员函数定义
template<typename T>
class vector {
public:
    void clear();

private:
    T *elements;
};

template<typename T>
void vector<T>::clear() {
    // Function body
}

/// 模版 add
template<typename T>
T Add(T a, T b) {
    return a + b;
}

float data[1024];

template<typename T>
T GetValue(int i) {
    return static_cast<T>(data[i]);
}

template<typename DstT, typename SrcT>
DstT c_style_cast(SrcT v) {  // 模版参数 DstT 需要人肉指定，放前面
    return (DstT) (v);
}


template<typename T, int Size>
struct Array {
    T data[Size];
};

Array<int, 16> arr;


/// 复杂的包含非typename模版参数的例子
template<int i>
class A {
public:
    void foo(int) {
    }
};

template<uint8_t a, typename b, void *c>
class B {
};

template<bool, void (*a)()>
class C {
};

template<void (A<3>::*a)(int)>
class D {
};

template<int i>
int Add(int a) { // 当然也能用于函数模板
    return a + i;
}

void foo() {
    A<5> a;
    B<
            7, A<5>, nullptr
    > b;    // 模板参数可以是一个无符号八位整数，可以是模板生成的类；可以是一个指针。
    C<false, &foo> c;    // 模板参数可以是一个bool类型的常量，甚至可以是一个函数指针。
    D<&A<3>::foo> d;    // 丧心病狂啊！它还能是一个成员函数指针！
    int x = Add<3>(5);    // x == 8。因为整型模板参数无法从函数参数获得，所以只能是手工指定啦。
}
//
//template<float a>
//class E {
//};        // ERROR: 别闹！早说过只能是整数类型的啦！


int main() {
    //使用模版Add
    std::cout << Add(3, 4) << std::endl;

    int a = 5;
    char b = 3;
    int result = Add<int>(a, b);
    std::cout << result << std::endl;


    float aa = GetValue<float>(0);
    int bb = GetValue<int>(1);
    std::cout << aa << " " << bb << std::endl;

    int v = 0;
    float i = c_style_cast<float>(v);  // 形象地说，DstT会先把你指定的参数吃掉，剩下的就交给编译器从函数参数列表中推导啦。
    std::cout << i << std::endl;
}