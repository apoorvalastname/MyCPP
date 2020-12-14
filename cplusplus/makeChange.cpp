#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <unordered_map>

//-------------------------------------------
//      retVectorStr
//-------------------------------------------
template <typename T>
std::string retVectorStr (std::vector <T> &data)
{
    std::string str = "{ ";
    for (auto elm: data)
        str += std::to_string(elm) + ", ";
    str += "}" ;
    return str;
}

//-------------------------------------------
//      makeChange
//-------------------------------------------
void printAvailableCoins (std::vector <int> &coins, int index)
{
    std::cout << " Current coin : " << coins[index] << std::endl;
    std::cout << " Available coins : ";
    for (int i= index+1; i<coins.size(); i++)
        std::cout << coins[i] << "   ";
    std::cout << std::endl;
}
int makeChangeRecursion (std::vector <int> &coins, int index, int total)
{
    //  Total ways of making 95 cents with the given coins =
    //  95-50 c with {25, 10, 5,1 , + 1 50c} + 95c with {25, 10, 5, 1}
    
    int numWays = 0;
    //printAvailableCoins (coins, index);
    if (index == coins.size()-1)
    {
        if (total % coins[index] == 0)
            return 1;
        return 0;
    }
    while ( total >= 0)
    {
       numWays += makeChangeRecursion (coins, index+1, total);
       total -= coins[index]; 
    }
    return numWays;
}
std::string coinsForIndex (std::vector <int> &coins, int index)
{
    std::string str = "";
    for (int i=index; i<coins.size(); i++)
    {
        str += '-'+std::to_string(coins[i]);
    }
    return str;
}

#define MAKECHANGE_CONDITION (total-i*coins[index])
int makeChangeMemoize (std::vector <int> &coins, int index, int total, std::unordered_map <std::string, int> &store)
{
    int numWays = 0;
    std::string keyStr = std::to_string(total)+(coinsForIndex(coins, index));
    if (store.find(keyStr) != store.end())
    {
        return store[keyStr];
    }
    else if (index == coins.size()-1)
    {
        store[keyStr] = 0;
        if (total % coins[index] == 0)
            store[keyStr] = 1;
    }
    else
    {
        for (int i=0; MAKECHANGE_CONDITION >= 0; i++)
        {
           numWays += makeChangeMemoize (coins, index+1, MAKECHANGE_CONDITION, store);
        }
        store[keyStr] = numWays;
    }
    return store[keyStr];
}
int makeChangeMemoization (std::vector <int> &coins, int index, int total)
{
   std::unordered_map <std::string, int> store;
   return makeChangeMemoize (coins, index, total, store);
}

int makeChangeDP (std::vector<int> &coins, int index, int total, std::unordered_map <std::string, int> &store)
{
    // Iteration using DP by Creating a table with :
    //      colums -- 0, 1, 2.. total (money)
    //      rows   -- {1}, {1, 5}, {1,5,10} .. with coins
    for (int i=coins.size()-1; i>=0; i--)
    {
        for (int j = 0; j<=total; j++)
        {
           std::string keyStr = std::to_string(j)+(coinsForIndex(coins, i));
           store[keyStr] = 0;
           if (i == coins.size()-1 || j ==0 )
               store[keyStr] = ( j%coins[coins.size()-1]? 0:1);
        }
    }
    for (int i=coins.size()-2; i >=0 ; i--)
    {
        for (int j = 1; j<=total; j++)
        {
            std::string keyStr = std::to_string(j)+coinsForIndex(coins, i);
            std::string keyStrPrevCoin  = std::to_string(j)+coinsForIndex(coins, i+1);
            int mytotal = store[keyStrPrevCoin];
            if (j>=coins[i])
            {
                std::string keyStrPrevTotal = std::to_string(j-coins[i])+coinsForIndex(coins, i);
                mytotal += store[keyStrPrevTotal];
            }
            store[keyStr] += mytotal;
        }
    }
    std::string keyStr = std::to_string(total)+coinsForIndex(coins,0);
    return store[keyStr];
}
int makeChangeDynamicProgramming (std::vector<int> &coins, int index, int total)
{
    std::unordered_map<std::string, int> store;
    return makeChangeDP(coins, index, total, store);
}

void makeChange_problem ()
{
    std::vector <int> coins = {50, 25, 10, 5, 1};
    int total = 95;
    //std::vector <int> coins = {10, 5, 1};
    //int total = 25;

    std::cout << "Using Recursion, the total ways of making " << total <<"c with " << retVectorStr(coins) << " : " << makeChangeRecursion (coins, 0, total) << std::endl;

    std::cout << "Using DP, the total ways of making " << total <<"c with " << retVectorStr(coins) << " : " << makeChangeDynamicProgramming (coins, 0, total) << std::endl;

    std::cout << "Using Memoization, the total ways of making " << total <<"c with " << retVectorStr(coins) << " : " << makeChangeMemoization (coins, 0, total) << std::endl;
    return ;
}
//-------------------------------------------
//      tryRecursion
//-------------------------------------------
#define NODATA -1
int myRecursiveFn (int pow)
{
    int ret = 0;
    if (pow == 0)
        return 1;
    ret += 2 * myRecursiveFn (pow - 1);
    return ret;
}
int myDpArray (int store[], int pow)
{
    // look at myDpVector for simplified coding
    int ret = 0;
    if (store[pow] != NODATA)
    {
        return store[pow];
    }
    store[pow] = 2 * myDpArray (store, pow-1);
    return store[pow];
}
int myDynamicProgrammingArrayFn (int pow)
{
    int store[pow+1];
    std::fill(store, store+pow+1, -1);
    store[0] = 1;
    store[1] = 2;
    return myDpArray (store, pow);
}

int myDpVector (std::vector <int> &store, int pow)
{
    if (store[pow] == NODATA)
    {
        store[pow] = 2 * myDpVector (store, pow-1);
    }
    return store[pow];
}
int myDynamicProgrammingVectorFn (int pow)
{
    std::vector <int> store (pow+1, NODATA);
    store[0] = 1;
    store[1] = 2;
    return myDpVector (store, pow);
}
int myIterationFn (int pow)
{
    int val = 1;
    for (int i=0; i<pow; i++)
        val *= 2;
    return val;
}
void tryRecursion()
{
    int pow = 6;
    std::cout << "Using Recursion : 2 ^ " << pow << " is : "<< myRecursiveFn (pow)<< std::endl;
    std::cout << "Using Memoization with Arrays : 2 ^ " << pow << " is : "<< myDynamicProgrammingArrayFn(pow)<< std::endl;
    std::cout << "Using Memoization with Vectors : 2 ^ " << pow << " is : "<< myDynamicProgrammingVectorFn(pow)<< std::endl;
    std::cout << "Using Iteration : 2 ^ " << pow << " is : "<< myIterationFn(pow)<< std::endl;
}

//-------------------------------------------
//      main
//-------------------------------------------
int main()
{
    makeChange_problem ();
    //tryRecursion();
    //Practise more DP-Memoization-Recursion problems.
    //
}
