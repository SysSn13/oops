#include <iostream>
using namespace std;

class HumanBeing{
    public: // access specifier
    // available outside the class
    void display(){
        cout<<"I am a human being"<<endl;
    }
}; // semicolon is required

int main(){
    HumanBeing person;
    person.display(); // call the function using dot operator
}