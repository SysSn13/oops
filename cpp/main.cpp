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


/* Copy constructor
    // - when we use dynamic memory allocation, we need to copy the object to another object
    // - copy constructor is called when we create a new object using an existing object

class Person{
    public:
    string *name;
    int age;
    Person(string name,int age):name(new string(name)),age(age){}
    // copy constructor
    Person(const Person &other):name(new string(*other.name)),age(other.age){}

    void introduce(){
        cout<<"My name is "<<*name<<". I'm "<<age<<" year old."<<endl;
    }
};

int main(){
    Person person1("Alice",18);
    Person person2(person1); // copy constructor is called
    *person2.name = "Bob";
    person2.age = 20;
    person1.introduce();
    person2.introduce();
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



/* Exception Handling
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
*/

/* Overriding new and delete operators
class TestClass{
public:
    int age;
    TestClass(int age):age(age){}
    void print(){
        cout<<"Age: "<<age<<endl;
    }
    void *operator new(size_t size){
        cout<<"Allocating memory"<<endl;
        void * pointer;
        pointer = malloc(size);
        if(!pointer){
            throw bad_alloc();
        }
        return pointer;
    }
    void operator delete(void *pointer){
        cout<<"Deallocating memory"<<endl;
        free(pointer);
    }
};
int main(){
    TestClass *t = new TestClass(10);
    t->print();
    delete t;
}

*/


/* Overriding stream insertion and stream extraction operators
class Person{
    public:
    int age;
    Person(int age):age(age){}
    Person(){}
    friend ostream &operator << (ostream &output,Person &p);
    // steam extraction operator
    friend istream &operator >> (istream &input, Person &p);
};

ostream &operator << (ostream &output,Person &p){
    output<<"Age: "<<p.age<<endl;
    return output;
}
istream &operator >> (istream &input,Person &p){
    input>>p.age;
    return input;
}
int main(){
    Person p;
    cin>>p;
    cout<<p;
}

*/

// set unset flags of IO streams
/*
#include <iomanip> // for manipulators

// manipulator functions
ostream &rightArrow(ostream &output){
    output<<" ---> ";
    return output;
}

istream &getName(istream &input){
    cout<<"enter your name:\n";
    return input;
}

int main(){
    cout.setf(ios::showpos | ios::showpoint);// or sepearated by commas (a,b,c ...)
    cout.unsetf(ios::showpos);
    cout<<100.12<<"\n";

    bool boolVal;
    //cin.setf(ios::boolalpha);
    // cin>>boolVal;
    // or
    // cin>> boolalpha >> boolVal;
    cout.setf(ios::boolalpha);
    cout<<boolVal<<"\n";

    // set precision
    cout.precision(6); // no effect on intergers only for floating point numbers
    cout<<123.456789<<"\n";
    cout.fill('*'); // fill character
    cout.setf(ios::left); // left justification
    cout.width(15); // if no of char is less than 15 then it will be padded with fill character
    cout<<"Hello World!"<<endl;
    cout<<setw(20)<<setfill('.')<<hex<< 1000<<endl; // manuipluate the output in hexadecimal, only affects within given expression


    string name;
    cin>> getName >> name;
    cout<<rightArrow << name;
}   
*/

// string stream
/*
#include <sstream>
int main(){
    stringstream ss;
    ss<<"Hello "<<"World!"<<" Example"; // stream insertion
    cout<<ss.str()<<endl;
    string w;
    ss>>w; // stream extraction
    cout<<w<<endl;
    while(getline(ss,w,' ')){
        cout<<w<<endl;
    }
    ss.str(""); // clear the string stream
}
*/


/*
// #include preprocessor directive

// importing a file

// #include "filename.cpp" // double quotes for user defined source files
#include <vector> // for standard library

// Macro: A fragment of code which is given a name

// 1. Object type macros:

#define ll long long

#define lli ll int

#define message "we can define macros in multpile \
lines using backslash"

// 2. Function macros:
#define ABS(number) ((number)>0?(number):-(number))


#define LINUX 1
#define MAC 2

#define OS LINUX

int main(){
    cout<<ABS(10)<<"\n";
    cout<<ABS(-10.901)<<"\n";


    // if endif elif else conditionals Macros
    #if OS == LINUX
    cout<<"OS is Linux"<<endl;
    #elif OS == MAC
    cout<<"OS is Mac"<<endl;
    #else
    cout<<"OS is unknown"<<endl;
    #endif

    #ifdef OS // ifndef for not defined
    cout<<"OS is defined"<<endl;
    #else
    cout<<"OS is not defined"<<endl;
    #endif

    #undef OS // undefines a macro
    #ifdef OS
    cout<<"OS is defined"<<endl;
    #else
    cout<<"OS is not defined"<<endl;
    #endif

    // predefined macros
    
    // __FILE__ // current file name
    // __LINE__ // current line number
    // __DATE__ // current date
    // __TIME__ // current time
    // __STDC__ // standard C
    // __cplusplus // C++
    

   #line 100 "newfile.cpp" // sets the line number and file name
    
}

*/


/*
// Generic programming
//         |-> typename or class

template <typename T> void display(T value);
template <typename T> void display(T x,T y);
template <typename A,typename B> void display(A x,B y); // overloading generic functions
template <typename T> void display1(T x,int y);
template <typename T> T add(T x,T y);   

void display(int x){ // overrides generic function for integer input
    cout<<"overridden "<<x<<endl;
}

// or we can write this explicit function like this :-
// template <> void display<int>(int x){
//     cout<<"overridden "<<x<<endl;
// }

// generic class

template <class T1,class T2> class MyClass{ // T1 a placeholder for the datatype we are going to use in the class
    T1 p1;
    T2 p2;
public:
    MyClass(T1 x, T2 y){
        p1 = x;
        p2 = y;
    }
    void display(){
        cout<<p1<<" "<<p2<<endl;
    }
};

// explicit specialization of generic class
template <> class MyClass<int,int>{
int p1,p2;
public:
    MyClass(int x,int y):p1(x),p2(y){}
    void display(){
        cout<<p1<<" "<<p2<<" explicit "<<endl;
    }
};

// lets implement a generic Pair class
//                  |-> default value (must start from right side in given args)
template <class T1=int,class T2=int> class Pair{
public:
    T1 first;
    T2 second;
    Pair(){}
    Pair(T1 first,T2 second):first(first),second(second){}
};

int main(){
    display(10);
    display(10,20);
    display(10,"20");
    display1("test",10);
    display(add(1,2));
    display(add(string("abc"),string("efg")));

    MyClass<int,int> intObject(31,45);
    MyClass<double,string> strObject(123.123,"str2");

    intObject.display();
    strObject.display();
    Pair<int,string> obj(15,"test");
    Pair<> defaultPair(1,2);
    cout<<obj.first<<" "<<obj.second<<endl;
    cout<<defaultPair.first<<" "<<defaultPair.second<<endl;
}

template <typename T> void display1(T x,int y){
    while(y--)cout<<x<<" ";
    cout<<endl;
}

template <typename T> void display(T value){
    cout<<value<<endl;
}
template <typename T> void display(T x,T y){
    cout<<x<<" "<<y<<endl;
}
template <typename A,typename B> void display(A x,B y){
    cout<<x<<" "<<y<<endl;
}
template <typename T> T add(T x,T y){
    return x+y;
}
*/


/*
// Namespaces

#include "file_one.cpp"
#include "file_two.cpp"

// use a namespace by:
// using namespace one;

// nested namespaces

namespace Outer{

    int num;
    namespace Inner{
        int num2;
        string num = "999"; // overrrides name defined in outer space
    }
}

// extending a namespace
namespace Outer{
    int temp;
}

// UnNamed or Anonymous namespaces
// Unnamed namespace "limits access" of class, variable, function, and objects to "the file in which it is defined". Unnamed namespace functionality is similar to static keywords in C/C++.
// static keyword limits access of global variables and functions to the file in which they are defined.
// There is a difference between an unnamed namespace and a static keyword because of which unnamed namespace has an advantage over static. The static keyword can be used with variables, functions, and objects but not with a user-defined class.

namespace{
    int x;
    void anonyMethod(){
        cout<<"x: "<<x<<endl;
    }

    namespace three{
        int x =204; // nested namespace can override the names defined in outer scope
        void display(){
            cout<<x<<endl;
        }

    }
}

// namespace aliases

namespace verylargenamespacename
{
    int x;
    namespace nestednamespace{
        void display(){
            cout<<x<<endl;
        }
    }

} // namespace verylargenamespacename

namespace shortName= verylargenamespacename;
namespace nested = shortName::nestednamespace; 

// inline nested namespaces

namespace AppVersion{
    namespace v1{
        void display(){
            cout<<"function from v1\n";
        }
    }
    namespace v2{
        void display(){
            cout<<"function from v2\n";
        }
    }
    inline namespace v3{ // after adding inline keyword now you can access v3 members in AppVersion directly
        void display(){
            cout<<"function from v3\n";
        }
    }

    namespace v3{ // this will also be treated as an inline namespace
        void otherMethod(){
            cout<<"other method from v3\n";
        }
    }
}
int main(){
    one::displayNum();
    two::displayNum();
    Outer::num = 15;
    cout<<Outer::num<<":" << Outer::Inner::num<<endl;
    Outer::Inner::num2 = 20;
    using namespace Outer;
    cout<<Inner::num2<<"\n";

    x = 25; // not need to use "using" keyword or "scope resolution" operator (::)
    anonyMethod();

    cout<<x<<" ";
    three::display();
    shortName::x= 123;
    nested::display();

    AppVersion::display();
    AppVersion::otherMethod();
    AppVersion::v2::display();
}
*/