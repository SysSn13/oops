#include <iostream>
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
}; // semicolon is required

int main(){
    HumanBeing person;
    person.display(); // call the function using dot operator
    person.name = "Alice";
    person.introduce();
}