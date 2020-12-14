#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <cstdlib>
#include <memory>
#include <unordered_set>
#include <algorithm>
#define ARRAY_SIZE 5
#define MAX_SIZE  20
#define PI 3.14
//using namespace std;
//using std::cout;

void local_getMyValues(std::vector <int> &data)
{
    data.push_back (10);
    data.push_back (20);
    data.push_back (30);
    data.push_back (40);
    data.push_back (50);
    data.push_back (60);
    data.push_back (70);
}
void local_getMyValues (std::vector <std::string> &names)
{
    names.push_back ("Apoorva");
    names.push_back ("Aarav");
    names.push_back ("Gaurav");
    names.push_back ("Latha");
    names.push_back ("ModernMM");
    names.push_back ("LetsJustLeaveItAtThat");
}
template <std::size_t S>
void local_getMyValues (std::array <std::string, S> &names)
{
    for (int i = 0; i < names.size(); i++)
    {
        names[i] = "Name_" + std::to_string(i+1);
    }
}
void local_printMyVector (std::vector <int> &data)
{
    // std::vector stores data on heap
    // std::array stores data on the stack like regular array
    std::cout << "Size of Vector : " << data.size() << std::endl;
    for (int i=0; i<data.size(); i++)
    {
        std::cout << "Data " << i << " : " << data[i] << std::endl;
    }
    for (int i : data)
        std::cout << "Does this work : " << i << std::endl;
}

void local_writeMyFile (std::string filename, std::vector <std::string>& stringList)
{
    std::ofstream file (filename, std::ios::app);
    for (std::string name : stringList)
        file << "Adding Name : " << name << std::endl;   
    file <<"------------------"<<std::endl;
    file.close();
}
void local_readMyFile_1 (std::string filename, std::vector <std::string> &stringList)
{
    std::ifstream file_read (filename);
    if (!file_read.is_open())
        return ;
    std::vector <std::string> namesList;
    std::string nameVariable;
    while (file_read >> nameVariable)
    {
        namesList.push_back (nameVariable);
    }
    for (std::string name: namesList)
        std::cout << name << std::endl;
    file_read.close();
}
void local_readMyFile_2 (std::string filename)
{
    std::ifstream file (filename);
    if (!file.is_open())
       return;
    std::string string_var;
    while (file.good())
    {
        getline(file, string_var);
        std::cout << "Read line : " << string_var << std::endl;
    }
    file.close();
} 

void local_readWriteMyFile (std::string filename, std::vector <std::string> &stringList)
{
    //local_writeMyFile (filename, stringList);
    //local_readMyFile_1 (filename);
    local_readMyFile_2 (filename);
}
void local_overloadMyFunction (std::vector <int> values)
{   
    for (int a: values)
        std::cout << "Int Value : " << a << std::endl;
}
void local_overloadMyFunction (std::vector <std::string> names)
{
    for (std::string name : names)
        std::cout << "String Value " << name << std::endl;
}

template <typename T>
void local_swapFunction (T &value1, T &value2)
{
    T x = value1;
    value1 = value2;
    value2 = x;
}

template <typename T, std::size_t S>
void local_templatePrintFunction(std::array <T, S> &names)
{
    for (T name: names)
        std::cout << name << std::endl;
}   

//------------------------------------
//   Class
//------------------------------------
class Person 
{
    private :
        std::string name;
        int age;
        std::string address;
    public :
        Person ()
        {
            std::cout << "Am an empty constructor " << std::endl;
        }
        void setName (std::string nameV)
        {
            this->name = nameV;
        }
        std::string getName ()
        {
            return name;
        }
        void setAge (int ageV)
        {
            age = ageV;
        }
        int getAge ()
        {
            return age;
        }
        std::string getAddress ()
        {
            return this->address;
        }
        void printDetails ()
        {
            std::cout <<"Name : "<<name<<" Age : "<< age << " Address : "<<address << std::endl;
        }
        void setAddress(std::string address);
        Person operator + (Person p);
};
void Person::setAddress(std::string address)
{
    this->address = address;
}
Person Person::operator + (Person p)
{
    Person kid = p;
    kid.age = this->age + p.age;
    return kid;
}
Person operator - (Person p1, Person p2)
{
    Person kid = p1;
    kid.setName (p1.getName() + p2.getName());
    kid.setAge( p1.getAge() + p2.getAge());
    return kid;
}

class EmbeddedClass 
{
    bool finish;
    public :
        EmbeddedClass();
        bool getFinish ();
        void setFinish (bool);
};
EmbeddedClass::EmbeddedClass() : finish(false)
{
    std::cout << "EmbeddedClass constructor" << std::endl;
}
bool EmbeddedClass::getFinish ()
{
    return this->finish;
}
void EmbeddedClass::setFinish (bool finish)
{
    this->finish = finish;
}
class Entity
{
    std::string name;
    int age, time;
    EmbeddedClass *embed;
    public :
        Entity (): name("Unknown"), age(15), time(22), embed(NULL)
        {
            std::cout <<"Empty Constructor"<< std::endl;
        }
        Entity (std::string name) : name("whatever"), age(11), time(11), embed(NULL)
        {
           this->name = name;
           std::cout << "Constructor for "<<this->name<< std::endl;
        }
        Entity (Entity &e):name("NoName"), age(e.age), time(e.time), embed(NULL)
        {
            this->embed = new EmbeddedClass;
            this->embed->setFinish(true);
            std::cout <<"Copy Constructor for " <<e.name << std::endl;
        }
        void setName (std::string name)
        {
            this->name = name;
        }
        std::string getName ()
        {
            std::string finish = "";
            if (this->embed)
            {
                finish = (this->embed->getFinish() ? " True " : " False ");
            }
            return this->name + finish;
        }
        int getAge();
};
int Entity::getAge()
{
    return this->age;
}
void local_print4Entities (Entity &one, Entity &two, Entity &three, Entity &four)
{
    std::cout << "First  : " << one.getName ()  << std::endl;
    std::cout << "Second : " << two.getName()   << std::endl;
    std::cout << "Third  : " << three.getName() << std::endl;
    std::cout << "Forth  : " << four.getName()  << std::endl;
}
/* overloaded new operator 
void * operator new (size_t size)
{   
    void *e = calloc (1, size);
    std::cout <<"size : "<<size << std::endl;
    return e;
}*/

/**********************************************************
 *
 *          Main Functions 
 *
 *********************************************************/

void variables_basic()
{
    int vari = 10;
    int x = 100;
    //std::cout << "Enter a value : ";
    //std::cin >> vari ;

    (x = vari) = 50;
    std::cout << "Apoorva x = " << x << " vari : "<< vari << std::endl;
    x = vari = 40;
    std::cout << "Apoorva x = " << x << " vari : "<< vari << std::endl;
}

void vectors_basic ()
{
    std::vector <int> items = {1, 2};
    items.push_back(3);
    for (int i = 0; i < items.size(); i++)
    {
        std::cout <<  "Item" << i << " : " << items[i] << "\t";
    }
    // items.pop_back();
    std::cout << "Size of Vector ITEMS " << items.size() << std::endl;
    local_printMyVector (items);
}
void file_basic ()
{
    std::vector <std::string> names;
    local_getMyValues (names);
    local_readWriteMyFile ("newTextFile_cpp.txt", names);
}
void overloading_basic()
{
    std::vector <int> values;
    std::vector <std::string> names;
    local_getMyValues (values);
    local_getMyValues (names);
    local_overloadMyFunction (values);
    local_overloadMyFunction (names);
}
void templatizeFunctions_basic ()
{
    int a = 10, b = 20;
    std::cout << "a = " << a << " b = " << b << std::endl;
    local_swapFunction (a, b);
    std::cout << "a = " << a << " b = " << b << std::endl;
    std::string str1 = "Gaurav" , str2 = "Aarav";
    std::cout << "str1 = " << str1 << " str2 = " << str2 << std::endl;
    local_swapFunction (str1, str2);
    std::cout << "str1 = " << str1 << " str2 = " << str2 << std::endl;
}

void class_basic()
{
    Person kid1, kid2, kid3;
    kid1.setName ("Gaurav");
    kid1.setAge (11);
    kid1.setAddress ("Sunnyvale");
    kid2.setName ("Aarav");
    kid2.setAge (8);
    kid2.setAddress ("Sunnyvale");
    kid1.printDetails();
    kid2.printDetails();
    kid3 = kid1 + kid2 ;
    kid3.printDetails();
}
void stdArray_basic()
{
    std::array <std::string, ARRAY_SIZE> names;
    local_getMyValues (names); 
    local_templatePrintFunction (names);
}
void newOperator_basic()
{
     Entity *a = new Entity; 
     a->setName ("Another");
     std::cout << "Getting name after overloading new operator " << a->getName() << " age : " << a->getAge() << std::endl;
     delete a;
}

void copyConstructor_basic ()
{
    std::string myNotes = "\n  Every Class provides a default Copy Constructor. \
For example, the copy constructor for Entity class would be : \n\tEntity (Entity &e){}\
\n  Whenever an object is assigned to another, like this the Copy constructor is called:\
\n\tEntity b (\"b-entity\"); \n\tEntity c = b;\n  Also when objects are passed in \
functions without reference, copy constructor is called. \n\tvoid func (Entity e) \
--> calls copy constructor\n\tvoid func (Entity &e) --> doesn't call the copy \
constructor, since the same object is passed by reference, without making a copy\n  The \
main need to implement a copy constructor manually is when there are pointers in the \
class. Since copy constructor by default makes a copy of the variables in the class, the \
pointers will also be just copied. This would not provide the expected/desired output \
and also will cause a crash because of multiple deletes (one for each object destructor) \
of the memory the pointer holds.\n";
    std::cout << myNotes << std::endl ;

    Entity first("First");
    Entity second = first;
    first.setName ("First of all");
    Entity third("Third");
    Entity forth = third;
    forth.setName ("Forth");
    
    local_print4Entities (first, second, third, forth);
}
/*class 3D
{
    double volume, surfaceArea;
    protected :
        void setVolume (double a)
        {
            volume = a;
        }
        void setSurfaceArea (double a)
        {
            surfaceArea = a;
        }
    public :
        double getVolume ()
        {
            return volume;
        }
        double getSurfaceArea ()
        {
            return surfaceArea;
        }
        virtual double calculateVolume () = 0;
        virtual double calculateSurfaceArea () = 0 ;
}; */

class Shape2D
{
    std::string name;
    double area, circumference;
    protected :
        void setArea (double a )
        {
            this->area = a;
        }
        void setCircumference (double a)
        {
            circumference = a;
        }
    public :
        Shape2D (std::string n) : name (n) {}
        std::string getName ()
        {
            return name;
        }
        double getArea () 
        {
            return area;
        }
        double getCircumference ()
        {
            return circumference;
        }
};

class Circle : public Shape2D
{
    double radius;
    public :
        Circle (double r) : Shape2D("Circle"), radius (r)
        {
            setArea (PI * radius * radius);
            setCircumference (2* PI * radius);
        }
};
class Polygon : public Shape2D
{
    int numOfSides;
    protected :
        void setNumOfSides (int numOfSides)
        {
            this->numOfSides = numOfSides;
        }
    public :
        Polygon (std::string name) : Shape2D (name) {}
        int getNumOfSides ()
        {
            return numOfSides;
        }
};
class Triangle : public Polygon
{
    double base, height;
    public :
        Triangle(double b, double h) : Polygon ("Triangle")
        {
            base = b;
            height = h;
            setNumOfSides (3);
            setCircumference (3 * base);   
            setArea (base * height / 2);
        }
};
class Quadrilateral : public Polygon
{
    double a, b, c, d;
    public :
        void quadrilateral_init (double a1, double b1, double c1, double d1)
        {
            a = a1;
            b = b1;
            c = c1;
            d = d1;
            setNumOfSides (4);
            setCircumference ( a + b + c + d);
            setArea ( a * b );
        }
        Quadrilateral( double a1, double b1, double c1, double d1, std::string name = "Quadrilateral") : Polygon (name)
        {
            quadrilateral_init (a1, b1, c1, d1);
        }
};
class Parallelogram : public Quadrilateral
{
    public :
        Parallelogram ( double a, double b, std::string name = "Parallelogram") : Quadrilateral (a, b, a, b, name){}
};
class Rhombus : public Parallelogram
{
    public :
        Rhombus ( double a, std::string name = "Rhombus") : Parallelogram ( a, a, name) {}
};
class Rectangle : public Parallelogram
{
    public :
        Rectangle (double a, double b) : Parallelogram (a, b, "Rectangle") {}
};
class Square : public Rhombus
{
    public :
        Square (double a) : Rhombus (a, "Square") {}
};

double printShape2DData (Shape2D &shape)
{
    std::cout << "Shape         : " << shape.getName() << std::endl; 
    std::cout << "Area          : " << shape.getArea() << std::endl; 
    std::cout << "Circumference : " << shape.getCircumference() << std::endl << std::endl; 
}

void baseDerived_basic ()
{
    Circle circle(5);
    Triangle triangle(10, 7);
    Rectangle rectangle(10, 7);
    Square square(10);
    Shape2D *shape = &circle; 
    printShape2DData ( *shape);
    *shape = triangle;
    printShape2DData ( *shape);
    *shape = rectangle;
    printShape2DData ( *shape);
    *shape = square;
    printShape2DData ( *shape);
}
void smartPointers_basic()
{
    // Include <memory> to use smart_ptr, unique_ptr and weak_ptr
    {
        std::shared_ptr<Circle> circle = std::make_shared<Circle>(5);
    }
}

bool findMatchingPairSum_ordered (const std::vector <int> &data, int sum)
{
    int lo = 0, hi = data.size()-1;
    while (lo < hi)
    {
        int s = data[lo] + data[hi];
        if (s == sum)
            return true;
        else if (s < sum)
            lo += 1;
        else 
            hi -= 1;
    }
    return false;
}

bool findMatchingPairSum_unordered (const std::vector <int> &data, int sum)
{
    std::unordered_set <int> store;
    for (auto &elm : data)
    {
        int complement = sum - elm;
        auto search_elm = store.find (complement);
        if (search_elm != store.end())
           return true;
        store.insert(complement);
    }
    return false;
}
template <typename T>
std::string returnArrayData(T &array, bool isTrue=false)
{
   std::string str = "";
   for (auto elm : array)
      str += std::to_string(elm) + ", ";
   if (isTrue)
      std::cout << "Array Data : "<< str << std::endl;
   return str;
}
void printLeftRightPivot (std::vector <int> &data, int left, int right, int pivot)
{
    std::cout << "left : " << left <<" -- "<< data[left] << " right : " << right <<" --  "<< data[right] ;
    std::cout <<" pivot : "<<pivot <<" -- " << data[pivot] <<  std::endl;
    returnArrayData(data, true);
}

void merge (std::vector <int> &data, int left, int mid, int right)
{
    int newDataSize = right-left+1;
    int newData[newDataSize];
    int i, j, index, tmpi, tmpj;
    for (index = 0, i = left, j = mid; i<mid && j<=right; index++)
    {
        if (data[i]<data[j])
        {
            newData[index] = data[i];
            i++;
        }
        else
        {
            newData[index] = data[j];
            j++;
        }
    }
    for (tmpi = i; tmpi <mid; tmpi++)
        newData[index++] = data[tmpi];
    for (tmpj = j; tmpj <=right; tmpj++)
        newData[index++] = data[tmpj];
    for (i=0, index = left; i< newDataSize; i++, index++)
    {
        data[index] = newData[i];
    }
    printLeftRightPivot (data, left, right, mid);
}
void swap (std::vector <int> &data, int left, int right)
{
    int x = data[left];
    data[left] = data[right];
    data[right] = x;
}

void mergeSort (std::vector <int> &data, int left, int right)
{
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    mergeSort (data, left, mid);
    mergeSort (data, mid+1, right);
    std::cout << "MERGE!!!!   " <<left << "-- " << mid << "-- " << right <<std::endl;
    merge (data, left, mid+1, right);
}
void mergeSort_basic (std::vector <int> &data)
{
    mergeSort (data, 0, data.size()-1);
}

int partition (std::vector <int> &data, int left, int right, int pivot)
{
    for (; left <= right; left++, right--)
    {
        printLeftRightPivot (data, left, right, pivot);
        while (data[left] < data[pivot])
            left++;
        while (data[right] > data[pivot])
            right--;
        printLeftRightPivot (data, left, right, pivot);
        if (left < right)
            swap (data, left, right);
        printLeftRightPivot (data, left, right, pivot);
    }
    std::cout << "PIVOT :: "<<left<<std::endl;
    return left;
}
void quickSort (std::vector <int> &data, int left, int right)
{
    if (left >= right)
        return;
    int mid = (left + right)/2;
    int pivot = partition (data, left, right, mid);
    quickSort (data, left, pivot-1);
    quickSort (data, pivot, right);
    printLeftRightPivot (data, left, right, pivot);
}
void quickSort_basic (std::vector <int> &data)
{
   quickSort (data, 0, data.size()-1);
}

void sort_basic()
{
    std::vector <int>data = {1, 9, 8, 2, 7, 3, 6, 5 , 4};
    //quickSort_basic(data);
    mergeSort_basic(data);
}

void unorderedSet_basic()
{
    std::cout <<"From a given collection of numbers find the matching pair that equals to a sum" << std::endl;
    std::vector <int> data = {2, 2, 4, 6, 7, 9};
    std::cout <<"Found matching pair in ordered set --  " << returnArrayData(data) << " ?? ";
    std::cout << findMatchingPairSum_ordered (data, 10) << std::endl;
    std::vector <int> unordered_data = {4, 2, 6, 2, 9, 7};
    std::cout <<"Found matching pair in unordered set --  " << returnArrayData(unordered_data) << " ?? ";
    std::cout << findMatchingPairSum_unordered (unordered_data, 10) << std::endl;
}
numWaysMakeChange (std::vector <int> &coins, int startCoin, int total)
{
    int numWays = 0;
    if (total == coins[startCoin])
        return 1;
    if (total < coins[startCoin])
        return 0;
    while (total - coins[startCoin] > 0)
    {
        numWays += numWaysMakeChange (coins, startCoin, total-coins[startCoin]); 
        total -= coins[startCoin];
    }
}
int makeChange (std::vector <int> &coins, int total)
{
   for (int i=0; i<coins.size(); i++)
   {
       numWaysMakeChange (coins, 0, total); 
   }
}

void makeChange_problem()
{
   std::cout <<"How many ways to make a total of T if you have quarters, dimes, nickles and pennies."<<std::endl;
   int TOTAL_MONEY = 95;
   std::vector <int> coins = {50, 25, 10, 5, 1};
   int numWays = makeChange (coins, TOTAL_MONEY);
}
int main()
{
    // variables_basic ();
    // vectors_basic ();
    // file_basic ();
    // overloading_basic();
    // templatizeFunctions_basic();
    // class_basic();
    // stdArray_basic();
    // newOperator_basic (); --  Also uncomment : void * operator new (size_t size)
    // copyConstructor_basic();
    //baseDerived_basic();
    // learn virtual functions -- override keyword on the derived classes's function
    // learn pure virtual function // Interface class -- class with only pure virtual functions
    // smartPointers_basic(); 
    // unorderedSet_basic();
    // sort_basic();
    makeChange_problem();
    // Apoorva -- pending
    
    // learn operator overloading (<<)
    // learn about 'new' keyword and 'delete' 
    // learn multiple templates in a function
    // inheritance
    // multiple inheritance
    // protected data
    // friend functions
    return 0;
}
