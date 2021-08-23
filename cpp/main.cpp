#include <iostream>
#include <string>
using namespace std;



/*
Access modes for a class member:
    1. public:
        accessible from anywhere
    2. private:
        accessible only from within the class
    3. protected:
        accessible from within the class and from derived classes
        - like private members, protected members are inaccessible outside of the class. However, they can be accessed by derived classes and friend classes/functions.

default access modifier: private
*/

class HumanBeing{
protected:
    string address;
private: // private access specifier only accessible within the class
    int age;
public: // access specifier
    string name;
    string *temp;
    // Since c++17 you can declare static members inline and instantiate them inside the body of class without the need of an out-of-class definition
    // like this: inline static int count = 0;

    static int count; // static variable, will be shared by all instances of the class

    // constructor,a special function which is executed when a object is created.
    // - must be defined in the public section
    // - must have the same name as the class
    // - must have no return type

    HumanBeing(){
        this->name = "NONE";
        this->age = 0;
        temp  = new string;
        *temp = "NONE";
        count++;
    }

    // destructor, a special function which is executed when a object is destroyed.
    // - must be defined in the public section
    // - must have the same name as the class
    // - must have no return type
    // tilde symbol is used before the function name
    ~HumanBeing(){
        cout<<name<<" is being destroyed"<<endl;
        delete temp; // release the memory
    }

    // we can overload constructor. e.g.:
    HumanBeing(string name, int age=0 ):name(name){
        cout<<"Constructor called"<<endl;
        this->age = age;
        count++;
    }

    void display(){
        cout<<"I am a human being"<<endl;
    }
    void setAge(int age){
        this->age = age;
    }
    int getAge(){
        return age;
    }
    void introduce(){
        cout<<"My name is "<<name<<". I'm "<<age<<" year old."<<endl;
    }
    void method1();

    void displayCount(){
        cout<<"Human being count: "<<count<<endl;
    }

    // static method
    // - can be called without creating an object
    // - method will be shared by all instances of the class
    // - we can only use static variables and functions in static methods
    static void humanCount(){
        cout<<"(static method )Human being count: "<<count<<endl;
    }
    
    // when we want to access the private properties of a class from outside the class, we can use friend function
    friend void displayAge(HumanBeing &person);

}; // semicolon is required

// defining method outside the class using scope resolution operator
void HumanBeing::method1(){
    cout<<"I am a method of HumanBeing. Name: "<<HumanBeing::name<<endl;
}

// HumanBeing::name = "Alice" will cause error as we cannot assign value to a non-static member

// we need to provide a defination for static member variable
// Notice, that the
// initializer is not required: if absent,
// count will be zero-initialized.
int HumanBeing::count = 0; 

void displayAge(HumanBeing &person){
    cout<<"(friend funtion) Age: "<<person.age<<endl;
}

// Inheritence
// it is an is-a relationship. We use inheritance only if an is-a relationship is present between the two classes.
// - a class can inherit members from another class
// - code reusebility, reuse the code of another class
// - scaleability, we can create a hierarchy of classes
/*
                   |  public | private | protected    |
        accessible |   1     |    0    |       1      |

syntax:  
                            |->access specifier (default: private])
    class DerivedClass : public BaseClass{
                    |->colon 
    };
*/

/* access modifiers for inheritance
    1. public: 
        change in access mode: No change. same as base class

    2. private:
        change in access mode: all the members of base class become private members of the derived class
        - accessible only from within the derived class

        public  ->   private
        protected -> private

    3. protected:
        change in access mode: public members of base class become protected members of the derived class

        public -> protected

*/

class Student : public HumanBeing{
public:
    int stundetId;
    string school;                  
    using HumanBeing :: address; // change the access mode of address from protected to public

    // contrstructor for derived class
    Student(string name,string school,int age,int studentId):HumanBeing(name,age),school(school),stundetId(studentId){}
    
    // member function overriding
    // - function of derived class is invoked instead of base class function
    void introduce(){
        cout<<"My name is "<<name<<". I'm "<<getAge()<<" year old. I'm a student at "<<school<<" school. My student id is "<<stundetId<<endl;
    }
};

int main(){
    HumanBeing person; // object created in stack
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
    personPtr->displayCount();

    // calling static method using class name and scope resolution operator
    HumanBeing::humanCount();
    
    // calling a friend function
    displayAge(person);
    delete personPtr; // delete the object


    // Inheritence
    Student *student = new Student("Alice", "MIT", 18, 123);
    student->introduce();

    delete student;
}