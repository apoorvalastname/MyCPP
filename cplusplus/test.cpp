#include <iostream>

class BaseClass
{
    int count;
    public :
        BaseClass (int count1, int count2): count(10) 
        {
            std::cout << "BaseClass Constructor Called with " << count1 << "  "  << count2 << std::endl;
        }
        int getCount ()
        {
            return count;
        }
        void setCount (int count)
        {
            this->count = count;
        }
};  
class DerivedClass : public BaseClass
{
    std::string name;
    public :
        DerivedClass (std::string name) : BaseClass (1, 2)
        {
            std::cout << "DerivedClass Constructor Called" << std::endl;
            this->name = name;
            setCount (20);
        }
};
int main()
{
    DerivedClass d("Apoorva");
    std::cout << "d - Apoorva is created" << std::endl;
    BaseClass *b = &d;
    std::cout << "pointer of base class is created and is assigned derived class object " << std::endl;
    BaseClass justB(5, 6);
    std::cout << b->getCount() <<"  "  << justB.getCount() << std::endl
              << "Derived class calling base class function " << d.getCount() << std::endl;
    return 0;
}
