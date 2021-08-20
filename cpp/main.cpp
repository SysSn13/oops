#include <iostream>
#include <string>
using namespace std;

class HumanBeing{
private: // private access specifier only accessible within the class
    int age;
public: // access specifier
    // available outside the class
    string name;

    // constructor,a special function which is called when a object is created.
    // - must be defined in the public section
    // - must have the same name as the class
    // - must have no return type
    
    HumanBeing(string name, int age){
        cout<<"Constructor called"<<endl;
        this->name = name;
        this->age = age;
    }

    void display(){
        cout<<"I am a human being"<<endl;
    }
    void setAge(int age){
        this->age = age;
    }
    void introduce(){
        cout<<"My name is "<<name<<". I'm "<<age<<" year old."<<endl;
    }
    void method1();
}; // semicolon is required

// defining method outside the class using scope resolution operator
void HumanBeing::method1(){
    cout<<"I am a method of HumanBeing. Name: "<<HumanBeing::name<<endl;
}

// HumanBeing::name = "Alice" will cause error as we cannot assign value to a non-static member


int main(){
    HumanBeing person("",18); // object created in stack
    person.display(); // call the function using dot operator
    person.name = "Alice";
    person.introduce();
    HumanBeing* personPtr = new HumanBeing("",14); // object created in heap, dynamically allocated
    personPtr->name = "Bob";
    
    // personPtr->age = 18; // error as age is private
    // use a public method to set the age
    personPtr->setAge(18);

    personPtr->introduce();

    personPtr->method1();
}