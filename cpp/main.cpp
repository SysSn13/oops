#include <iostream>
#include <string>
using namespace std;

class HumanBeing{
    public: // access specifier
    // available outside the class
    string name;
    void display(){
        cout<<"I am a human being"<<endl;
    }
    void introduce(){
        cout<<"My name is "<<name<<endl;
    }
    void method1();
}; // semicolon is required

// defining method outside the class using scope resolution operator
void HumanBeing::method1(){
    cout<<"I am a method of HumanBeing. Name: "<<HumanBeing::name<<endl;
}

// HumanBeing::name = "Alice" will cause error as we cannot assign value to a non-static member


int main(){
    HumanBeing person; // object created in stack
    person.display(); // call the function using dot operator
    person.name = "Alice";
    person.introduce();
    HumanBeing* personPtr = new HumanBeing(); // object created in heap, dynamically allocated
    personPtr->name = "Bob";
    personPtr->introduce();

    personPtr->method1();
}