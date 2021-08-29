#include <iostream>
#include <string>
#include <vector>
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

    // virtual function
    virtual void about(){
        cout<<"I am a human being"<<endl;
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


/*  Order of calling constructor and destructor
    during object creation:
        1. BaseClass
        2. DerivedClass
    during object destruction:
        1. DerivedClass
        2. BaseClass
*/  

// Multiply inheritance

/*
    class DerivedClass : public BaseClass, public BaseClass2{

    };
*/


class Student : public HumanBeing{
public:
    int stundetId;
    string school;                  
    using HumanBeing :: address; // change the access mode of address from protected to public

    // contrstructor for derived class                          |-> passing values to base class constructor
    Student(string name,string school,int age,int studentId):HumanBeing(name,age),school(school),stundetId(studentId){}
    
    // member function overriding
    // - function of derived class is invoked instead of base class function
    void introduce(){
        cout<<"My name is "<<name<<". I'm "<<getAge()<<" year old. I'm a student at "<<school<<" school. My student id is "<<stundetId<<endl;
        // access the overriden member function
        // HumanBeing::introduce();
    }

    void about(){
        cout<<"I am a student"<<endl;
    } 
};



/* Virtual function
    - a function which is defined in a base class with virtual keyword
    - if a derived class overrides the function, then overridden function will be called instead of base class function
    - virtal nature of a function is also inherited by derived class so the function will be virtual in derived class as well
    Polimorphism:
        many forms
        it occurs when there is herirachy of classes and they are related by inheritance
*/

class Teacher : public HumanBeing{
    public:
    int teacherId;
    Teacher(string name,int age,int teacherId):HumanBeing(name,age),teacherId(teacherId){}
    void about(){
        cout<<"I am a teacher"<<endl;
    }
};
// example of polimorphism
void whoIs(HumanBeing *person){
    person->about();
    // here if person is a student, then it will call student::about()
    // if person is a teacher, then it will call teacher::about()
    // because 'about' method is a virtual function in the base class
    // we can see, the function is called depending on the type of the object
}


/* Pure virtual function / Abstract class
Syntax:
    virtual void methodName()=0;
    
    - methodName() is a pure virtual function
    - if derived class does not override this function, then compiler will generate an error
    - If a class has at least one pure virtual function, then it is called a abstract class
    - we cannnot create an object of an abstract class
*/

class AbstractClassExample{
    public:
    virtual void method1()=0;
};

// defining the pure virtual function of a Abstract class
void AbstractClassExample::method1(){
    cout<<"From abstract class"<<endl;
}

class DerivedFromAbstract : public AbstractClassExample{
    public:
    void method1(){
        cout<<"From derived class"<<endl;
        AbstractClassExample::method1(); // calling the pure virtual function from the base class
    }
};
/*
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

    // calling the overriden function
    student->HumanBeing::introduce();

    // polymorphism concept
    Teacher *teacher = new Teacher("Bob", 18, 567);
    whoIs(student);
    whoIs(teacher);
    delete student;


    // abstract class
    DerivedFromAbstract *abstructExample = new DerivedFromAbstract();
    abstructExample->method1();
    delete abstructExample;
}

*/

/* Diamond problem  

class A{
public:
    vois method(){

    }
  ...  
};

class B: public A{
  ...
};

class C: public A{
  ...
};

class D : public B, public C{

};

D *d = new D();
d->method();
now we have a diamond problem because there is ambiquity in the inheritance hierarchy

solution:
    virtual inheritance

class B: virtual public A{

};

class C: virtual public A{

};

others will be same

constructor call order: A,B,C,D
*/

/* Nested class

    - a class can have another class as a member

    class OuterClass{
        public:
            string var;
            class InnerClass{ // only avaialble in the scope of OuterClass
                public:
                    string val;
                    void method(){
                        cout<<"InnerClass"<<endl;
                    }
            };
            InnerClass inner;

            void displayInner(){
                cout<<inner.val<<endl;
            }
    }


    Creating object:

    OuterClass outer;
    outer.var = "outer";
    outer.inner.val = "Hello";
    outer.inner.method();
    outer.displayInner();

    // creating an object of inner class
    OuterClass::InnerClass inner;
    inner.val = "inner";
*/


/* Local class
    - class only available in the scope of the function

void studentList(){

    class Student{
        public:
        string name;
        int age;
        Student(string name,int age):name(name),age(age){}
        void introduce(){
            cout<<"My name is "<<name<<". I'm "<<age<<" year old."<<endl;
        }        
    }
    Student student1("Alice",18);
    Student student2("Bob",19);

    student1.introduce();
    ...
}

*/



/* Operator overloading


class Avg{
public:
    int total;
    int count;
    double average;
    Avg(){}
    Avg(int total,int count):total(total),count(count){
        if(count<=0)
            average = -1;
        else
            average = (total+0.0)/(count+0.0);
    }
    // overloading the + operator
    Avg operator+(Avg a){ //  return type can be anything
        int total_cnt = a.count + count;
        int total_sum = a.total + total;
        return Avg(total_sum,total_cnt);
    }
    Avg operator-(Avg a);

    
    // No need to pass the class object
    void operator +=(int bonus){
        total += bonus;
    }
    // for a friend function we have to pass the object explicilty
    friend void operator-=(Avg &a,int bonus){
        a.total -= bonus;
    }
    Avg operator--(){ // prefix
        total -= 1;
        return *this;
    }
    Avg operator--(int){ // postfix
        Avg duplicate = Avg(*this);
        total -= 1;
        return duplicate;
    }

    friend Avg operator++(Avg &); // prefix
    friend Avg operator++(Avg &,int); // postfix 
};

Avg Avg::operator-(Avg a){
    int total_cnt = count - a.count;
    int total_sum = total - a.total;
    return Avg(total_sum,total_cnt);
}
Avg operator++(Avg &a){
    a.total += 1;
    return a;
}


Avg operator++(Avg &a,int){
    Avg res(a);
    a.total +=1;
    return res; // returning a duplicate
}

class Values{
public:
    vector<int> v;
    Values(int a,int b,int c){
        v = {a,b,c};
    }

    // since it is a specical operator in c++ we can not overload it using friend function
    // overloading special [] subscript operator
    int operator[](int ind){
        return v[ind];
    }
    
    // overloading special () function call operator
    void operator()(int a){
        // do something
        v.back() = a;
    }

    // overloading class member operator
    Values *operator->(){
        return this;
    }
};

int main(){
    Avg a = Avg(6,2); 
    cout<<a.average<<endl;
    Avg b = Avg(10,4);
    cout<<b.average<<endl;
    Avg c = b - a;
    cout<<c.count<<" "<<c.total<<" "<<c.average<<endl;

    c += 6;
    c -=1;
    cout<<c.total<<endl;    
    cout<<(++c).total<<" "<<c.total<<endl;
    cout<<(c++).total<<" "<<c.total<<endl;
    cout<<(--c).total<<" "<<c.total<<endl;
    cout<<(c--).total<<" "<<c.total<<endl;

    Values v(2,5,1); // constructor call
    cout<<v[2]<<endl;

    v(10); // function call
    cout<<v[2]<<endl;

    //             |-> arrow operator 
    for(auto ele:v->v){
        cout<<ele<<" ";
    }
    cout<<endl;
}

/*
Rules and restriction for overloading operator:

    - by overloading an operator we can not change the precedence of the operator
    - can not change the number of operands a operator takes
    - can not overload these operators:
        ? :: .* .

*/

// */



// /* Exception Handling
#include <exception>
#include <stdexcept>

class OverSpeedException: public exception{
 int speed;
 public:
    OverSpeedException(int speed):speed(speed){}

    // override what() method
    const char *what() const throw(){ 
        return "Vehicle is overspeed";
    }       
    
    int getSpeed(){
        return speed;
    }
};

void testException(){
    throw runtime_error("Some error");
}
int main(){
    int a = 10,b=1;
    int c;
    try{
        if(b==0)
            throw runtime_error("divide by zero error."); // runtime_error is a derived class of exception and it overrides the virtual what() function
        c = a/b;
        cout<<c<<endl;
    }
    catch(runtime_error &error){
        cout<<"Exception caught: "<<error.what()<<endl;
    }
    catch(const char*error){
        cout<<error<<endl;
    }
    catch(...){ // catches all the exception
        cout<<"Exception caught"<<endl;
    } 

    try{
        testException();

        // nested try-catch
        try{

        } catch(...){

            throw; // throws out of the inner try-catch
        }
    }
    catch(int e){
        cout<<"Exception caught: "<<e<<endl;
    }
    catch(const char *e){
        cout<<"Exception caught: "<<e<<endl;
    }
    catch(runtime_error e){
        cout<<"Exception caught: "<<e.what()<<endl;
    }
    catch(...){
        cout<<"Unepected exception caught"<<endl;
    }

    // using custom exception
    try{
        int speed = 100;
        throw OverSpeedException(speed);
    }catch(OverSpeedException e){
        cout<<"Exception caught: "<<e.what()<<endl;
        cout<<"Speed: "<<e.getSpeed()<<endl;    
    }
    
}
// */

