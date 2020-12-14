#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <map>

#define LARGE_VALUE 1000
#define NODATA  -1
#define MAX_NUM 10
int M, N; // for matrix

//-------------------------------------------------
//      maxAmount
//-------------------------------------------------
int recFn (int a[], int min, int max)
{
    int diff = max - min;
    if (diff < 0)
        return 0;
    if (diff==0)
        return a[min];  
    if (diff==1)
        return std::max(a[min], a[max]);
        
    int newmin_1 = min+1;
    int newmax_1 = max-1;
    if (std::max(a[min+1], a[max])==a[min+1]) 
    {
        newmin_1 = min+2;
        newmax_1 = max;
    }
    int newmin_2 = min+1;
    int newmax_2 = max-1;
    if (std::max(a[min], a[max-1])==a[max-1])
    {
        newmin_2 = min;
        newmax_2 = max-2;
    }
    return (std::max(a[min]+recFn(a, newmin_1, newmax_1), 
        a[max]+recFn(a, newmin_2, newmax_2)));
}

// fn as such, returns the iteration for every turn.. the rec gives the sum 
int maxAmount_rec (int arr[], int min, int max)
{   
    int diff =  max-min;
    if (diff < 0)
        return 0;
    if (diff == 0)
        return arr[min];
    if (diff == 1)
        return (std::max(arr[min], arr[max]));
    return (std::max( arr[min] + std::min ( maxAmount_rec(arr, min+1, max-1), 
                                            maxAmount_rec(arr, min+2, max)), 
                      arr[max] + std::min ( maxAmount_rec(arr, min+1, max-1), 
                                            maxAmount_rec(arr, min,   max-2))));

}
int maxAmount_memoize (int arr[], int min, int max, int store[][10])
{
    int diff = max-min;
    if (store[min][max] != NODATA)
        return store[min][max];
    if (diff < 0)
        store[min][max] = 0;
    else if (diff == 0)
        store[min][max] = arr[min];
    else if (diff == 1)
        store[min][max] = std::max (arr[min], arr[max]);
    else
    {   
        store[min][max] = std::max ( arr[min] + std::min (maxAmount_memoize(arr, min+2, max, store), 
                                                maxAmount_memoize(arr, min+1, max-1, store)), 
                                     arr[max] + std::min (maxAmount_memoize(arr, min, max-2, store),
                                                maxAmount_memoize(arr, min+1, max-1, store)));
    }
    return store[min][max];
}

int maxAmount_dp (int arr[], int min, int max, int (*store)[10])
{
    for (int i=min; i<=max; i++)
    {
        for (int j=min; j<=max; j++)
        {
            int diff = j-i;
            if (diff < 0)
                store[i][j] = 0;
            else if (diff == 0)
                store[i][j] = arr[i];
            else if (diff == 1)
                store[i][j] = std::max(arr[i], arr[j]);
        }
    }
    for (int i=min; i <=max; i++)
    {
        for (int j=min; j <=max; j++)
        {
            if (store[i][j] == NODATA)
            {
                store[i][j] = std::max ( arr[i] + std::min (store[i+2][j], store[i+1][j-1]) ,
                                         arr[j] + std::min (store[i+1][j-1], store[i][j-2]));
            }
        }
    }  
    return (store[min][max]);
}
void printMultiDimentionalVector(std::vector <std::vector<int>> &storeV)
{
    for (auto row: storeV)
    {
        for (auto val: row)
            std::cout << val << "  ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
int maximumAmount(int arr[], int n) 
{
    int store[MAX_NUM][MAX_NUM];
    std::fill (*store, *store+MAX_NUM*MAX_NUM , -1);

    // Initializing 2D vectors
    std::vector <std::vector<int>> storeV(n, std::vector<int>(n, -1));
    printMultiDimentionalVector (storeV);

    //return recFn (arr, 0, n-1);
    //return maxAmount_rec (arr, 0, n-1);
    //return maxAmount_memoize (arr, 0, n-1, store);
    return maxAmount_dp (arr, 0, n-1, store);
    // Your code here
}
void maxAmount_main ()
{
    int arr[] = {8, 15, 3, 7};
    //int arr[] = {5,3,7,10};
    int n = 4;
    std::cout << "Calling maximumAmount :: "<< maximumAmount(arr, n) <<std::endl;
}

//-------------------------------------------------
//      eggDrop (n-eggs, k-floors)
//      eggs -- 1..n, and floors -- 1..k
//-------------------------------------------------
int eggDropRec (int n, int k)
{
    int minFloors = k;
    int val = 0;
    if (n == 0)
        return LARGE_VALUE;
    if (k == 0 || k == 1)
        return k; 
    if (n == 1) 
        return k;
    for (int i = 1; i <= k; i++)
    {
       val = 1 + std::max (eggDropRec (n-1, i-1), eggDropRec (n, k-i));    
       if (val < minFloors)
            minFloors = val;
    }
    return minFloors;
}
// Store n X k
int eggDropMemoize (int n, int k, std::vector<std::vector<int>> &store)
{
    int minFloors = k;
    int val = 0;
    if (store[n][k] != NODATA)
        return store[n][k];
    if (n == 0) // n == 0 - no eggs
        store[n][k] = LARGE_VALUE;
    else if (k == 0 || k == 1) 
        store[n][k] = k;
    else if (n == 1)    
        store[n][k] = k; 
    else
    {
        for (int i = 1; i <= k; i++)
        {
           val = 1 + std::max (eggDropMemoize (n-1, i-1, store), eggDropMemoize (n, k-i, store));    
           if (val < minFloors)
                minFloors = val;
        }
        store[n][k] = minFloors;
    }
    return store[n][k];
}

int eggDropDP (int n, int k, std::vector <std::vector<int>> & store)
{
    for (int i=0; i<=k; i++)
    {
        for (int j=0; j<=n; j++)
        {
            if (i==0)
                store[i][j] = 0;
            else if (j==1)
                store[i][j] = i;
            else if (i==1)
                store[i][j] = 1;
        }
    }
    for (int i=2; i<=k; i++)
    {
        for (int j=2; j<=n; j++)
        {
            int mid = (i)/2 ;
            if (i%2)
                store[i][j] = 1 + std::min ( std::max(store[mid-1][j-1], store[mid+1][j]),
                                             std::max(store[mid][j-1], store[mid][j]));
            else
                if (mid < 2)
                    store[i][j] = 1 + std::max (store[mid][j-1], store[mid-1][j]);
                else
                    store[i][j] = 1 + std::min (std::max (store[mid-1][j-1], store[mid][j]),
                                                std::max (store[mid-2][j-1], store[mid+1][j]));

        }
    }
    return store[k][n];
}
void eggDrop_main()
{
    int n, k;
    std::cout << "Enter  n(eggs) and k(floors) : ";
    std::cin >> n >> k;
    std::cout << "n : " << n << " k : "<< k << std::endl;
    //std::cout << "Num of attemps Recursion : " << eggDropRec(n, k) << std::endl;

    std::vector <std::vector<int>> store (n+1, std::vector<int>(k+1, NODATA));
    std::cout << "Num of attemps Memoize : " << eggDropMemoize(n, k, store) << std::endl;

    std::vector <std::vector<int>> storeDP (k+1, std::vector<int>(n+1, LARGE_VALUE));
    std::cout << "Num of attemps DP : "<< eggDropDP (n, k, storeDP) << std::endl;
}

//-------------------------------------------------
//      Palindrome
//Given a string, find the minimum number of characters to be inserted to convert it to palindrome.
//-------------------------------------------------
int palindromeRec (std::string &pal, int start, int end)
{
    int diff = end - start;
    if (diff <= 0)
        return 0;
    if (diff == 1)
    {
        if (pal[start] == pal[end])
            return 0;
        else
            return 1; // diff-1
    }
    if (pal[start] == pal[end])
        return palindromeRec (pal, start+1, end-1);
    else
        return (1 + std::min (palindromeRec (pal, start+1, end),
                              palindromeRec (pal, start, end-1)));
}
int palindromeMemoize (std::string &pal, int start, int end, std::vector <std::vector <int>> &store)
{
    int diff = end-start;
    if (store[start][end]!=NODATA)
        return store[start][end];
    if (diff <=0)
        store[start][end] = 0;
    else if (diff == 1)  
    {
        if (pal[start] == pal[end])
            store[start][end] = 0;
        else
            store[start][end] = 1;
    }
    else
    {
        if (pal[start] == pal[end])
            store[start][end] = palindromeMemoize(pal, start+1,end-1, store);
        else
            store[start][end] = 1 + std::min (palindromeMemoize(pal, start+1, end, store), 
                                   palindromeMemoize (pal, start, end-1, store));
    }
    return store[start][end];
}
int palindromeDP (std::string &pal, int start, int end, std::vector <std::vector<int>> &store)
{

}

int palindromeFn (std::string &pal)
{
    // return palindromeRec (pal, 0, pal.length()-1);

    std::vector<std::vector<int>> store (pal.length(), std::vector<int> (pal.length(), NODATA));
    return palindromeMemoize (pal, 0, pal.length()-1, store);
}
bool isNum (std::string &str)
{
    for (int i=0; i<str.length(); i++)
        if (!isdigit (str[i]))
            return false;
    return true;
}
void palindrome_main ()
{
    std::string str[20];
    int n = 1;
    std::cout << "Enter n and number of (non-palindrome)strings " << std::endl; 
    std::cin >> str[0] ;
    if (isNum(str[0]))
    {
        n = std::stoi(str[0]);
        for (int i=0; i < n; i++)
            std::cin >> str[i];
    }
    for (int i=0; i < n; i++)
        std::cout << palindromeFn(str[i]) << std::endl;
}

//-------------------------------------------------
//      special keyboard
//      Imagine you have a special keyboard with the following keys: 
//
//      Key 1:  Prints 'A' on screen
//      Key 2: (Ctrl-A): Select screen
//      Key 3: (Ctrl-C): Copy selection to buffer
//      Key 4: (Ctrl-V): Print buffer on screen appending it after what has already been printed.
//
//      Find maximum numbers of A's that can be produced by pressing keys on the special keyboard N times. 
//-------------------------------------------------
// alreadySavedAs - Saved A's previously some time using Key2+Key3 

int specialKeyboardRec(int n, int displayAs, int savedAs)
{
    if (n < 0)
        return 0;
    if (n < 3)
    {
        if (savedAs)
            return n*savedAs;
        return n;
    }       
    return (std::max( 1 + specialKeyboardRec(n-1, displayAs+1, savedAs),
           std::max( displayAs + specialKeyboardRec(n-3, displayAs*2, displayAs),
             savedAs + specialKeyboardRec(n-1, displayAs + savedAs, savedAs))));

}

std::string getString (int n, int d, int s)
{
    return (std::to_string(n) + "-" + 
            std::to_string(d) + "-" +
            std::to_string(s));
}
int specialKeyboardMemoize (int n, int displayAs, int savedAs, std::unordered_map<std::string, int> &store)
{
    if (n < 0)
        return 0;
    std::string keyStr = getString(n, displayAs, savedAs);
    if (store.find(keyStr) != store.end())
        return store[keyStr];
    if (n < 3)
    {
        store[keyStr] = n;
        if (savedAs)
           store[keyStr] = savedAs * n;    
    }
    else
    {
        store[keyStr] = std::max ( 1 + specialKeyboardMemoize(n-1, displayAs+1, savedAs, store),
                        std::max ( displayAs + specialKeyboardMemoize(n-3, displayAs*2, displayAs, store),
                                   savedAs + specialKeyboardMemoize(n-1, displayAs + savedAs, savedAs, store) ));
    }
    return store[keyStr];
}

int specialKeyboardDP_bkup (int n, int displayAs, int savedAs, std::unordered_map <std::string, int> &store)
{
    std::string keyStr = getString(n, displayAs, savedAs);
    if (store.find(keyStr) != store.end())
        return store[keyStr];
    if (n < 3)
    {   
        store[keyStr] = n;
        if (savedAs)
            store[keyStr] = n*savedAs; 
    }
    else if (!displayAs)
    {
        store[keyStr] = 3 + specialKeyboardDP_bkup (n-3, 3, 0, store);
    }
    else 
    {
        store[keyStr] = std::max ( displayAs + specialKeyboardDP_bkup (n-3, displayAs * 2, displayAs, store),
                                   savedAs   + specialKeyboardDP_bkup (n-1, displayAs + savedAs, savedAs, store));
    }
    return store[keyStr];
}
void getMax (std::vector <int> &maxD, std::vector <int> &maxS, int maxD2, int maxS2, int maxD3, int maxS3, int i, bool isDS)
{
    if (!isDS)
    {
        if (maxD[i] < maxD2)
        {
            maxD[i] = maxD2;
            maxS[i] = maxS2;
        }
        if (maxD[i] < maxD3)
        {
            maxD[i] = maxD3;
            maxS[i] = maxS3;
        }
    }
    else
    {
        if (maxD[i] + maxS[i] < maxD2 + maxS2)
        {
            maxD[i] = maxD2;
            maxS[i] = maxS2;
        }
        if (maxD[i] + maxS[i] < maxD3 + maxS3)
        {
            maxD[i] = maxD3;
            maxS[i] = maxS3;
        }
    }
}
int specialKeyboardDP_v1 ( int n)
{
    if (n<0)    
        return 0;
    // maxD_D,  maxD_S  : DisplayAs and SavedAs where DisplayAs is the max
    // maxDS_D, maxDS_S : DisplayAs and SavedAs where DisplayAs+SavedAs is the max
    std::vector <int>  maxD_D  (n, 0);
    std::vector <int>  maxD_S  (n, 0);
    std::vector <int>  maxDS_D (n, 0);
    std::vector <int>  maxDS_S (n, 0);
    int maxD2, maxD3, maxS2, maxS3;

    for (int i=0; i < n; i++)
    {
        if (i < 5)
        {
            maxDS_D[i] = maxD_D[i] = i+1;
            maxDS_S[i] = maxD_S[i] = 0;
        }
        else
        {
            maxDS_D[i] = maxD_D[i] = maxD_D[i-3]*2 ;
            maxDS_S[i] = maxD_S[i] = maxD_D[i-3] ;
            maxD2      = maxDS_D[i-1] + maxDS_S[i-1];
            maxS2      = maxDS_S[i-1];
            maxD3      = maxD_D[i-1] + maxD_S[i-1];
            maxS3      = maxD_S[i-1];

            getMax (maxD_D,  maxD_S,  maxD2, maxS2, maxD3, maxS3, i, false);
            getMax (maxDS_D, maxDS_S, maxD2, maxS2, maxD3, maxS3, i, true);
        } 
    }
    return maxD_D[n-1]; 
}

void getMaxD (int *maxD, int *maxS, int *d2, int *s2, int d3, int s3)
{
    int dsave = *d2, ssave = *s2;
    if (*d2 + *s2 <= *maxD + *maxS)
    {
        *d2 = *maxD;
        *s2 = *maxS;
    }
    if (*d2 + *s2 < d3 + s3)
    {
        *d2 = d3;
        *s2 = s3;
    }
    if (*maxD < dsave)
    {
        *maxD = dsave;
        *maxS = ssave;
    }
    if (*maxD < d3)
    {
        *maxD = d3;
        *maxS = s3;
    }
}

int specialKeyboardDP ( int n)
{
    if (n<0)    
        return 0;
    // maxD_D,  maxD_S  : DisplayAs and SavedAs where DisplayAs is the max
    // maxDS_D, maxDS_S : DisplayAs and SavedAs where DisplayAs+SavedAs is the max
    std::vector <int>  maxD_D  (n, 0);
    std::vector <int>  maxD_S  (n, 0);
    int maxD2, maxD3, maxS2, maxS3;
    int savedMaxDS_D = 0, savedMaxDS_S = 0;

    for (int i=0; i < n; i++)
    {
        if (i < 5)
        {
            savedMaxDS_D = maxD_D[i] = i+1;
            savedMaxDS_S = maxD_S[i] = 0;
        }
        else
        {
            maxD_D[i] = maxD_D[i-3]*2 ;
            maxD_S[i] = maxD_D[i-3] ;
            maxD3     = maxD_D[i-1] + maxD_S[i-1];
            maxS3     = maxD_S[i-1];
            savedMaxDS_D += savedMaxDS_S;

            getMaxD (&maxD_D[i],  &maxD_S[i], &savedMaxDS_D, &savedMaxDS_S, maxD3, maxS3);
        } 
    }
    return maxD_D[n-1]; 
}
void specialKeyboard_main()
{
    int n;
    std::cout << "Enter num Keys : ";
    std::cin >> n;
    //std::cout << specialKeyboardRec(n, 0, 0) << std::endl;

    //std::unordered_map <std::string, int> store ;
    //std::cout << specialKeyboardMemoize(n, 0, 0, store) << std::endl;
    std::cout << specialKeyboardDP_v1(n) << std::endl;
    std::cout << specialKeyboardDP(n) << std::endl;
}

int matrix_r (int m, int n)
{
    if (m == M-1 || n == N-1)
        return 1;
    return matrix_r (m+1, n) + matrix_r (m, n+1);
}
int matrix_m (int m, int n, int store[][20])
{
    if (store[m][n] != 0)
        return store[m][n];
    if (m == M-1 || n == N-1)
        store[m][n] = 1;
    else
        store[m][n] = matrix_r (m+1, n) + matrix_r (m, n+1);
    return store[m][n];
}
int matrix_dp (int m, int n, int store[][20])
{
    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++)
            if (i==m-1 || j==n-1)
                store[i][j] = 1;
    for (int i=m-2; i>=0; i--)
        for (int j=n-2; j>=0; j--)
            store[i][j] = store[i+1][j] + store[i][j+1];

    return store[0][0];
}

//-------------------------------------------------
//      matrix
//-------------------------------------------------
void matrix_main()
{   
    int store[20][20];
    std::fill (*store, *store+20*20, 0);
    std::cout <<"M and N : ";
    std::cin >> M >> N;
    std::cout << M << N;
    std::cout << "Matrix - Recursion : " << matrix_r (0, 0) << std::endl; 
    std::cout << "Matrix - Memoization : " << matrix_m (0, 0, store) << std::endl; 
    std::cout << "Matrix - Dynamic Programming  : " << matrix_dp (M, N, store) << std::endl; 
}


//-------------------------------------------------
//      btree
//-------------------------------------------------
class Dict
{
    public :
        std::unordered_map <char, Dict *> letters;
        bool isWord = false;
        std::string word;
};

bool wordPresent (std::string &word, std::vector <std::string> &wordlist)
{
    Dict *dict = new Dict;
    // Create a b-tree out of the dictionary dict
    for (auto eachword : wordlist)
    {
        Dict *mydict = dict;
        for (auto c : eachword)
        {
            if (mydict->letters.find(c) != mydict->letters.end())
            {
                mydict = mydict->letters[c];
            }
            else
            {
                Dict *newDict = new Dict;
                mydict->letters[c] = newDict;
                mydict = newDict;
            }
        }
        mydict->isWord = true;
        mydict->word = eachword;
    }
    
    for (auto c : word)
    {
        if (dict->letters.find(c) != dict->letters.end())
            dict = dict->letters[c]; 
        else
            return false;
    }
    return dict->isWord; 
}
void btree_main()
{
    // input dictionary and word - find if the word is valid or not
    std::vector <std::string> dictionary = {"ale", "apple", "monkey", "plea"};
    std::string word = "monkey";
    std::cout << (wordPresent (word, dictionary) ? "TRUE":"FALSE" ) << std::endl;
}


//-------------------------------------------------
//      longestWord
//-------------------------------------------------
bool wordinHash_incorrect (std::string &word, std::unordered_map <char, int> wordHash) // making a copy of wordHash
{
    for (auto c : word)
    {
        if (wordHash[c] > 0)
            wordHash[c]--;
        else 
            return false;
    }
    return true;
}
std::string longestword_incorrect (std::string &word0, std::vector <std::string> &wordlist)
{
    // create a hash_map for the word0. For each word1 in the wordlist, check if all the
    // letters in the word1 are present in word0
 
    std::string returnWord = "";
    int returnWordLen = 0;   
    std::unordered_map <char, int> wordHash;
    for (auto c : word0)
    {
        wordHash[c]++;
    }
    
    for (auto word : wordlist)
    {
        if (wordinHash_incorrect (word, wordHash))
        {
            if (returnWordLen < word.length() || (returnWordLen == word.length() && returnWord[0] < word[0]))
            {
                returnWordLen = word.length();
                returnWord = word;
            }
        }           
    }
    return returnWord;
}
bool isWordPossible (std::string &word0, std::string &word)
{
    size_t pos = 0;
    for (auto c : word)
    {
        if ((pos = word0.find(c, pos)) == std::string::npos) 
            return false;
    }
    return true;
}
std::string longestword (std::string &word0, std::vector <std::string> &wordlist)
{
    // find if the word is possible.
    // if this is the longest, save it
    std::string returnWord = "";
    for (auto word : wordlist)
    {
        if (isWordPossible (word0, word))
        {
            if (word.length() > returnWord.length())
                returnWord = word;
            else if ((word.length() == returnWord.length()) && (word[0] < returnWord[0]) )
                returnWord = word;
        } 
    }
    return returnWord;
}
void longestWord_main()
{
    std::vector <std::string> dict = {"ale", "apple", "monkey", "plea"};
    std::string word = "abpcplea";
    //std::cout << "Longest word : " << longestword(word, dict) << std::endl;
    std::cout << "Longest word : " << longestword(word, dict) << std::endl;
}

//int basenum[4] = {2,3,4,5};
//int storeIndex [4] = {2, 2, 3, 4};
//std::vector <unsigned long long int> storeMaxValues = {6, 9, 16, 25};
//std::vector <unsigned long long int> uglynums = {1, 2, 3, 4, 5 };

int basenum[3] = {2,3,5};
int storeIndex [3] = {2, 2, 5};
std::vector <unsigned long long int> storeMaxValues = {6, 9, 25};
std::vector <unsigned long long int> uglynums = {1, 2, 3, 4, 5 };

int getIndexMinMaxValue ()
{
    int minIndex = 0;
    unsigned long long  minValue = storeMaxValues[minIndex];
    for (int i=1; i<storeMaxValues.size(); i++)
    {
        if (minValue > storeMaxValues[i])
        {
            minIndex = i;
            minValue = storeMaxValues[i];
        }
    }
    return minIndex;
}
int isDuplicateMaxValue(unsigned long long int value)
{
    for (int i=0; i<storeMaxValues.size(); i++)
    {
        if (value == storeMaxValues[i])
        {
            return i+1;
        }
    }
    return 0;
}
void updateStoreMaxValue (int index)
{
    unsigned long long int value = 0;
    do
    {
        storeIndex[index]++;
        value = basenum[index] * uglynums[storeIndex[index]];
    } while (isDuplicateMaxValue (value));
    storeMaxValues[index] = value;
}
void removeDuplicates ()
{
    for (int i=0; i<storeMaxValues.size(); i++)
    {
        for (int j=i+1; j<storeMaxValues.size(); j++)
        {
            if (storeMaxValues[i] == storeMaxValues[j])
                storeMaxValues[j] = basenum[j] * uglynums[++storeIndex[j]];
        }
    }
}

unsigned long long int uglyNumber (int n)
{

    int x = 0;
    while ( uglynums.size() < n)
    {
        x = getIndexMinMaxValue ();
        uglynums.push_back (storeMaxValues[x]);
        storeMaxValues[x] = basenum[x] * uglynums[++storeIndex[x]];
        removeDuplicates ();
    }
    return uglynums[n-1];   
}

bool isUglyNumber_bruteForce(unsigned long long i)
{
    while (i%2 == 0)
        i/=2;
    while (i%3 == 0)
        i/=3;
    while (i%5 == 0)
        i/=5;
    if (i > 1)
        return false;
    return true;
}
unsigned long long uglyNumber_bruteForce (int n)
{
    std::vector <int> uglyNumbers;   
    int k = 0;
    for (unsigned long long i=1; k<n; i++)
    {
        if (isUglyNumber_bruteForce (i))    
        {
            uglyNumbers.push_back (i);
            k++;
        }
    }

    //for (auto elm : uglyNumbers)
    //    std::cout << elm << "  ";
    //std::cout << std::endl;
    return uglyNumbers[n-1];
}
void uglyNumber_main()
{
    int n = 1;
    std::cin >> n;
    //std::cout << uglyNumber_bruteForce (n) << std::endl;
    std::cout << uglyNumber (n) << std::endl;
}


//-------------------------------------------------
//      wordBoggle -- 1
//-------------------------------------------------
//Given a dictionary, a method to do lookup in dictionary and a M x N board where every cell has one character. Find all possible words that can be formed by a sequence of adjacent characters. Note that we can move to any of 8 adjacent characters, but a word should not have multiple instances of same cell.
//
//Example:
//
//Input: dictionary[] = {"GEEKS", "FOR", "QUIZ", "GO"};
//       boggle[][]   = {{'G','I','Z'},
//                       {'U','E','K'},
//                       {'Q','S','E'}};
//
//Output:  Following words of dictionary are present
//         GEEKS, QUIZ
// M - rows         Matrix - M X N
// N - columns

void dfs (int x, int y, int myM, int myN,
          std::vector <std::vector <char>> &matrix, 
          std::vector <std::vector <bool>> visited,
          std::unordered_set <std::string> &answer,
          Dict *trie)  
{
    if (visited[x][y] || trie->letters.find(matrix[x][y]) == trie->letters.end())
    {
        return ;
    }
    trie = trie->letters[matrix[x][y]];
    visited[x][y] = true;
    if (trie->isWord)
       answer.insert (trie->word);
    for (int i=(x>0?x-1:x); i<=(x<myM-1?x+1:x); i++)
    {
        for (int j=(y>0?y-1:y); j<=(y<myN-1?y+1:y); j++)
        {
            if ((!(i==x && j==y)) && !visited[i][j])
                
                dfs (i, j, myM, myN, matrix, visited, answer, trie);            
        }
    }
}
std::unordered_set <std::string> wordBoggle1_fn (Dict *dictHead, std::vector<std::vector<char>> &matrix, int myM, int myN)
{
    std::unordered_set <std::string> answer;
    Dict *dict = dictHead;   
    char c;
    for (int i=0; i<myM; i++)
    {
        for (int j=0; j<myN; j++)
        {
            std::vector <std::vector <bool>> visited (myM, std::vector <bool> (myN, false));
            dict = dictHead;
            dfs (i, j, myM, myN, matrix, visited, answer, dict);            
        }
    }
    return answer;
}
void createTrieFromInput (std::vector <std::string> &input, Dict *dictHead)
{
    for (auto eachStr : input)
    {
        Dict *dict = dictHead;
        for (auto c : eachStr)
        {
            if (dict->letters.find(c) != dict->letters.end())
            {
                dict = dict->letters[c];
            }
            else
            {
                Dict *newDict = new Dict;
                dict->letters[c] = newDict;
                dict = newDict;
            }
        }
        dict->isWord = true;
        dict->word = eachStr;
    }
}
void wordBoggle_1_main ()
{
    const int maxT = 12;
    int T, x[maxT], myN[maxT], myM[maxT];
    std::cin >> T ; // Number of testcases;
    std::string inputStr;
    std::vector <std::string> input [maxT];
    std::vector <std::vector <char>> matrix[maxT];
    char value;
    
    for (int i=0; i<T; i++)
    {
        std::cin >> x[i] ; // Number of words in the dictionary;
        for (int j=0; j<x[i]; j++)
        {
            std::cin >> inputStr;
            input[i].push_back(inputStr);
        }
        std::cin >>myM[i] >>myN[i];
        for (int x=0; x<myM[i]; x++)
        {
            std::vector <char> rowVector;
            for (int y=0; y<myN[i]; y++)
            {
                std::cin >> value;
                rowVector.push_back(value);
            }
            matrix[i].push_back(rowVector);
        }
    } 
    for (int i=0; i<T; i++)
    {
        Dict *dict = new Dict;
        createTrieFromInput (input[i], dict);
        auto answer = wordBoggle1_fn (dict, matrix[i], myM[i], myN[i]);
        if (answer.size())
        {
            for (auto eachStr: answer)
                std::cout << eachStr << " ";
        }
        else
            std::cout << "-1";
        std::cout << std::endl;
    }
}

//-------------------------------------------------
//      vectorTest
//-------------------------------------------------
void vectorTest_main()
{
    std::vector <std::string> mystr = {"str20", "str30", "str40"};

    mystr.push_back ("str1");
    mystr.push_back ("str2");
    mystr.push_back ("str3");
    mystr.push_back ("str4");

    std::vector <std::string> newStr = mystr;

    for (int i=0; i<mystr.size(); i++)
    {
        std::cout << "  " << i<<"  "<< mystr[i] << std::endl;
        std::cout << "  " << i<<"  "<< newStr[i] << std::endl;
    }
    newStr.erase (newStr.begin()+2);
    for (auto elm: mystr)
        std::cout << elm <<"   ";
    std::cout <<std::endl;
    for (auto elm: newStr)
        std::cout << elm <<"   ";
    std::cout <<std::endl;
     
}

//-------------------------------------------------
//      jobAssignment
//-------------------------------------------------

std::string jobAssignmentKeyValue (std::vector <int> &remPersons, std::vector <int>&remJobs)
{
    std::string retValue = "X";
    for (auto p : remPersons)
        retValue += "-" + std::to_string(p);
    for (auto j : remJobs)
        retValue += ":" + std::to_string(j);
    return retValue;
}
int  jobAssignment (int matrix[30][30], std::vector<int> remPersons, 
                    std::vector<int> remJobs, std::unordered_map<std::string, int> &store)
{
    std::string keyStr = jobAssignmentKeyValue (remPersons, remJobs);
    std::vector <int> tmpPersons, tmpJobs;
    int count = remPersons.size();
    if (store.find(keyStr) != store.end())
        return store[keyStr];
    if (count == 1)
    {
        store[keyStr] = matrix[remPersons[0]][remJobs[0]];   
    }
    else if (count == 2)
    {
        store[keyStr] = (std::min(matrix[remPersons[0]][remJobs[0]]+matrix[remPersons[1]][remJobs[1]],
               matrix[remPersons[0]][remJobs[1]]+matrix[remPersons[1]][remJobs[0]]));
    }
    else
    {
        int minvalue = 0;
        tmpPersons = remPersons;
        tmpPersons.erase (tmpPersons.begin());
        for (int j=0; j<count; j++)
        {
            tmpJobs = remJobs;
            tmpJobs.erase(tmpJobs.begin()+j);
            int value = matrix[remPersons[0]][remJobs[j]] + jobAssignment (matrix, tmpPersons, tmpJobs, store);      
            if (!minvalue || minvalue > value)
                minvalue = value;
        }
        store[keyStr] = minvalue;
    }
    return store[keyStr];
}

void jobAssignment_main()
{
    const int maxT = 102, maxN = 30;
    int T, n[maxT], val;
    int matrix [maxT][maxN][maxN];

    std::cin >> T;
    for (int i = 0; i < T; i++)
    {
        std::cin >>n[i];
        for (int x=0; x<n[i]; x++)
        {
            for (int y=0; y<n[i]; y++)
            {
                std::cin >>val;
                matrix[i][x][y] = val;
            }
        }
    }

    for (int i=0; i<T; i++)
    {
        std::unordered_map <std::string, int> store;
        std::vector <int> allPersons, allJobs;
        for (int x=0; x<n[i]; x++)
        {
            allPersons.push_back (x);
            allJobs.push_back (x);
        }
        std::cout << jobAssignment (matrix[i], allPersons, allJobs, store) << std::endl;      
    }
}
/***********************************************
 *          getBinaryStr
 **********************************************/
void getBinaryStr (long long int n, std::string &str)
{
    for (long long int i = 1<<30; i; i/=2)
    {
        if (i&n)
            str.append("1");
        else
            str.append("0");
    }
}
void multiplyStrings (std::string &str1, std::string &str2, int times)
{
    for (int i=0; i<times; i++)
        str2.append (str1);
}
void addStrings (std::vector <std::string> &strArray, std::string &str2)
{
    for (auto &eachStr : strArray)
        str2.append (eachStr);
}
int bitsSum_method1 (int n, long long int A[])
{
    std::string addStrs;
    std::vector <std::string> eachStr;
    std::vector <std::string> multipleEachStr;
    for (int i=0; i<n; i++)
    {
        std::string tmpStr,tmpMultiplyStr;
        getBinaryStr (A[i], tmpStr);
        eachStr.push_back (tmpStr);
        multiplyStrings (tmpStr, tmpMultiplyStr, n); 
        multipleEachStr.push_back (tmpMultiplyStr);
    }
    addStrings (eachStr, addStrs);
    int count = 0;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<addStrs.length(); j++)
            if (addStrs[j] != multipleEachStr[i][j])
                count++;
    }
    return count;
}

int xor_countBits (long long int n1, long long int n2)
{
    long long int n = n1^n2;
    long long int noname = n;
    int count = 0;
    for (; n; n=n>>1)
    {
        if (n&1)
            count++;
    }
    return count;
}
int bitsSum_method2 (int n, long long int A[])
{
    int count = 0;
    for (int i=0; i<n; i++)
    {
        for (int j=i+1; j<n; j++)
        {
            count += xor_countBits (A[i], A[j]);
        }
    }
    return count*2;
}
void getBinaryBitSet(long long int num, std::bitset <31>&b)
{
    for (int i=0; num; i++, num>>=1)
    {
        if (num&1)
            b[i] = 1;
    }
}
int bitsSum_method3(int n, long long int A[])
{
    int count = 0;
    std::bitset<31> b[n];
    for (int i=0; i<n; i++)
    {
        getBinaryBitSet(A[i], b[i]);
    }
    for (int i=0; i<31; i++)
    {
        int bitCount = 0;
        for (int j=0; j<n; j++)
        {
            if (b[j][i] == 1)
                bitCount++;
        }
        count += bitCount * (n-bitCount);
    }
    return count*2;
}

int bitsSum_method4(int n, long long int A[])
{
    int count = 0;
    
    for (int j=0; j<31; j++)
    {
        int bitCount = 0;
        for (int i=0; i<n; i++)
        {
            if (A[i]&1<<j)
               bitCount++;        
        }
        count += bitCount * (n-bitCount);
    }

    return count*2;
}
void bitsSum_main()
{
    std::vector <long long int> a;
    int n = 0;
    long long int val;
    std::cin >> n;
    for (int i=0; i<n; i++)
    {
        std::cin >> val;
        a.push_back(val);
    }
    std::cout << bitsSum_method1(n, &a[0]) << std::endl;
    std::cout << bitsSum_method2(n, &a[0]) << std::endl;
    std::cout << bitsSum_method3(n, &a[0]) << std::endl;
    std::cout << bitsSum_method4(n, &a[0]) << std::endl;
}

/*************************************************
 *          countStringsABC
 ************************************************/
int countStringsABC (int n)
{
    if (n<=0)
        return 0;
    // number of ways of arranging a is 1
    // number of ways of arranging b is n
    // number of ways of arranging c is n 
    // number of ways of arranging c, b is n * (n-1) 
    // number of ways of arranging c, c is (n-1)+(n-2)+...+1 = (n)(n-1)/2
    // number of ways of arranging c, c, b is (((n-1) * (n-2)) + ((n-2) * (n-2)) + ((n-3) * (n-2) ... + (1)*(n-2))) 
    //                                        (n-2) * (n-1 + n-2 + .. +1)
    //                                        (n-2) * (n-1)(n)/2
    // Total number of ways of using a, c, c, b is 
    //                                      1 + n + n + n*(n-1) + (n)(n-1)/2 + (n)(n-1)/2 * (n-2)
    //                                      1 + 2n + n*(n-1)*(n+1)/2
    int count = 1 + 2*n + n*(n-1)*(n+1)/2;
    return count;
}

void countStringABC_main ()
{
    int T, n[100];
    std::cin >>T;
    for (int i=0; i<T; i++)
        std::cin >>n[i];

    for (int i=0; i<T; i++)
        std::cout << countStringsABC (n[i]) << std::endl;
}

/*************************************************
 *          numberPatterID
 ************************************************/
std::string numberPatternID_process (std::vector<std::string> &digit, std::string &str, int cur, char prevID, int nextDigit)
{
    std::string resultStr;
    for (int i=0; i<str.length(); i++)
    {
        if (str[i] == 'I')
        {
            if (prevID == 'D')
                cur = nextDigit;
            else
                cur++;
            if (((i+1)<str.length()) && str[i+1] == 'D')
            {
                // Find how many consecutive 'D's, update cur and nextDigit
                int numConsecutiveDs = 0;
                for (int j=i+1; j<str.length() && str[j]=='D'; j++, numConsecutiveDs++);
                cur +=numConsecutiveDs;
                nextDigit = cur+1;

            }
        }
        else if (str[i] == 'D')
            cur--;
        prevID = str[i];
        resultStr.append(digit[cur]);
    }
    return resultStr;
}
std::string numberPatterID(std::string &str)
{
    std::vector <std::string> digits = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    return numberPatternID_process (digits, str, 0, 'D', 0);
}

void numberPatterID_main()
{
    std::string ids[100];
    int T;
    std::cin >> T;
    for (int i=0; i<T; i++)
    {
        std::cin >>ids[i];   
        ids[i].insert(0,"I");
    }
    for (int i=0; i<T; i++)
    {
        std::cout << ids[i] << std::endl;
        std::cout << numberPatterID (ids[i]) << std::endl;
    }
}

//-------------------------------------------------
//      fourSum
//-------------------------------------------------
// r[] : int input array of integers
// k   : the quadruple sum required

bool uniqueQuadruple (std::vector <int> &arr, int k, int n, int ple, std::vector<int> answer, std::vector<std::vector<int>> &answers)
{
    bool res = true;
    if (ple <= 0 || n+1 < ple)
       return false;

    if (ple == 1)   
    {
        for (int i=n; i>=0; i--)
        {
            if (arr[i] == k)
            {
                answer.push_back (arr[i]);
                answers.push_back (answer);
                return true;
            }
        }
        return false;
    }

    if (arr[n] <= k)
    {
        answer.push_back(arr[n]);
        res = uniqueQuadruple(arr, k-arr[n], n-1, ple-1, answer, answers) ;
        answer.pop_back();
        res = uniqueQuadruple(arr, k, n-1, ple, answer, answers);
    }
    else
        res = uniqueQuadruple(arr, k, n-1, ple, answer, answers);
    if (res)
        answers.push_back(answer);
    return res;
        
}
std::vector <std::vector <int>> fourSum_method1 (std::vector <int> &arr, int k)
{
    std::vector <int>answer;
    std::vector <std::vector <int>>answers;
    std::sort (arr.begin(), arr.end(), std::greater<int> ());
    uniqueQuadruple (arr, k, arr.size()-1, 4, answer, answers);
    return answers;
}

std::map <int, int> createOrderedHashSetUniqueNums (std::vector <int> &arr)
{
    std::map <int, int> hashSet ;
    for (auto elm : arr)
    {
        if (hashSet.find(elm) == hashSet.end())
            hashSet[elm] = 1;
        else
            hashSet[elm]++;
    }
    return hashSet;
}
void  fourSum_rec (std::map <int, int> &uniqueNums, int k, int digits, std::vector<int> answer, std::vector<std::vector<int>> &answers)
{
    if (digits == 0)
    {
        if  (k == 0)
        {
            answers.push_back (answer); // found a set --  add to list of answers     
            return;       
        }
        return;
    }
    if (!uniqueNums.size())
        return;
    if (uniqueNums.size() == 1 && (uniqueNums.begin()->second < digits))
        return;
    if (digits == 1)
    {
        if (uniqueNums.find(k) != uniqueNums.end())
        {
            answer.push_back (k);
            answers.push_back (answer); // found a set --  add to list of answers     
            return;       
        }
        return;
    }
    for (auto it=uniqueNums.begin(); it!=uniqueNums.end(); it++)
    {
        for (int i=(it->second>4?4:it->second); i>0 ; i--)
        {
            // add it->first i times to answer
            for (int j=0; j<i; j++)
                answer.push_back (it->first);
            std::map<int,int> tmpUniqueNums (it, uniqueNums.end());
            tmpUniqueNums.erase (tmpUniqueNums.begin());
            fourSum_rec (tmpUniqueNums, k - it->first*i, digits-i, answer, answers);
            for (int j=0; j<i; j++)
                answer.pop_back();
        }
    }
}

void  fourSum_rec_method1 (std::map <int, int> &uniqueNums, int k, int digits, std::vector<int> answer, std::vector<std::vector<int>> &answers)
{
    if (digits == 0)
    {
        if  (k == 0)
        {
            answers.push_back (answer); // found a set --  add to list of answers     
            return;       
        }
        return;
    }
    if (!uniqueNums.size())
        return;
    if (uniqueNums.size() == 1 && (uniqueNums.begin()->second < digits))
        return;
    if (digits == 1)
    {
        if (uniqueNums.find(k) != uniqueNums.end())
        {
            answer.push_back (k);
            answers.push_back (answer); // found a set --  add to list of answers     
            return;       
        }
        return;
    }
    for (auto it=uniqueNums.begin(); it!=uniqueNums.end(); it++)
    {
        for (int i=1; i<=it->second && i<=digits; i++)
        {
            // add it->first i times to answer
            for (int j=0; j<i; j++)
                answer.push_back (it->first);
            std::map<int,int> tmpUniqueNums (it, uniqueNums.end());
            tmpUniqueNums.erase (tmpUniqueNums.begin());
            fourSum_rec (tmpUniqueNums, k - it->first*i, digits-i, answer, answers);
            for (int j=0; j<i; j++)
                answer.pop_back();
        }
    }
}
std::vector <std::vector <int>> fourSum_method2 (std::vector <int> &arr, int k)
{
    std::vector <std::vector <int>> answers;
    std::vector <int> answer;
    std::map <int, int> uniqueNums = createOrderedHashSetUniqueNums (arr);
    fourSum_rec (uniqueNums, k, 4, answer, answers);
    // for each element in the ordered set (std::map - 0, 1, 3, 4..)
    //    for count of element find if 4-count (> 0) unordered_set has key of k-v (v = elem*count)
    return answers;  
}

bool pairsSumPossible (std::pair<int,int> &p1, std::pair<int,int> &p2, std::map<int,int>u)
{
    if ((u[p1.first]--)>0 && (u[p1.second]--)>0 && (u[p2.first]--)>0 && (u[p2.second]--)>0)
        return true;
    return false;
}

void pairsAppend (std::vector<std::vector<int>> &a, std::pair<int,int> &p1, std::pair<int,int>&p2)
{
    std::vector<int> answer = {p1.first, p1.second, p2.first, p2.second};
    std::sort (answer.begin(), answer.end());
    if (!std::count(a.begin(), a.end(), answer))
        a.push_back(answer);
    return;
}
std::vector <std::vector <int>> fourSum_method5 (std::vector <int> &arr, int k)
{
    std::vector <std::vector <int>> answers;
    std::map <int, int> uniqueNums = createOrderedHashSetUniqueNums (arr);

    // create a vector of <sum> : pairs of number contributing to the sum
    std::vector <int> pairsSum;
    std::vector <std::pair <int, int>> pairsNums;
    
    for (std::map<int,int>::iterator it1=uniqueNums.begin(); it1!=uniqueNums.end(); it1++)
    {
        for (auto it2=(it1->second >1 ? it1 : std::next(it1)); it2!=uniqueNums.end(); it2++)
        {
            int num1 = it1->first, num2 = it2->first;
            pairsSum.push_back (num1+num2);
            pairsNums.push_back (std::make_pair(num1, num2));
        }
    }

    for (int i=0; i<pairsSum.size(); i++)
    {
        int j=i, remK = k-pairsSum[i];
        for (std::vector<int>::iterator findIt=pairsSum.begin(); 
            ((findIt = std::find(pairsSum.begin()+j, pairsSum.end(), remK))!= pairsSum.end());
            j++)
        {
            j = std::distance (pairsSum.begin(), findIt);
            if (pairsSumPossible (pairsNums[i], pairsNums[j], uniqueNums))
            {
                pairsAppend (answers, pairsNums[i], pairsNums[j]);
            }
        }
    }
    return answers;  
}


std::vector <std::vector <int>> fourSum_method4 (std::vector <int> &arr, int k)
{
    std::vector <std::vector <int>> answers;
    std::map <int, int> uniqueNums = createOrderedHashSetUniqueNums (arr);

    // create a multimap of <sum> : pairs of number contributing to the sum
    std::multimap <int, std::pair <int, int>> pairsSum;
    
    for (std::map<int,int>::iterator it1=uniqueNums.begin(); it1!=uniqueNums.end(); it1++)
    {
        for (auto it2=(it1->second >1 ? it1 : std::next(it1)); it2!=uniqueNums.end(); it2++)
        {
            int num1 = it1->first, num2 = it2->first;
            pairsSum.insert({num1+num2, std::make_pair(num1, num2)});
        }
    }

    for (auto elm : pairsSum)
    {
        std::cout << "Cutting : " <<elm.first << "--"<<elm.second.first<<":"<<elm.second.second<<std::endl;
    }

    for (std::multimap<int,std::pair<int,int>>::iterator it=pairsSum.begin(); it!=pairsSum.end(); it=pairsSum.erase(it))
    {
        int remK = k-it->first;
        auto findIt = pairsSum.equal_range(remK);
        for (auto matchId = findIt.first; matchId != findIt.second; matchId++)
        {
            if (pairsSumPossible (it->second, matchId->second, uniqueNums))
            {
                pairsAppend (answers, it->second, matchId->second);
            }
        }
    }
    return answers;  
}

std::vector <std::vector <int>> fourSum_method3 (std::vector <int> &arr, int k)
{
    std::vector <std::vector <int>> answers;
    std::map <int, int> uniqueNums = createOrderedHashSetUniqueNums (arr);

    // create a map of <sum> : vector of pairs of number contributing to the sum
    std::map <int, std::vector <std::pair <int, int>>> pairsSum;
    
    for (std::map<int,int>::iterator it1=uniqueNums.begin(); it1!=uniqueNums.end(); it1++)
    {
        for (auto it2=(it1->second >1 ? it1 : std::next(it1)); it2!=uniqueNums.end(); it2++)
        {
            int num1 = it1->first, num2 = it2->first;
            pairsSum[num1+num2].push_back(std::make_pair(num1, num2));
        }
    }

    for (std::map<int,std::vector<std::pair<int,int>>>::iterator it=pairsSum.begin(); it!=pairsSum.end(); it=pairsSum.erase(it))
    {
        int remK = k-it->first;
        if (pairsSum.count(remK))
        {
            if (remK == it->first)
            {
                for (int i=0; i < it->second.size(); i++)
                {
                    for (int j=i; j< it->second.size(); j++)
                    {
                        if (pairsSumPossible (it->second[i], it->second[j], uniqueNums))
                            pairsAppend (answers, it->second[i], it->second[j]);
                    }
                }
            }
            else
            {
                for (auto eachPair1 : it->second)
                {
                    for (auto eachPair2 : pairsSum.find(remK)->second )
                    {
                        if (pairsSumPossible (eachPair1, eachPair2, uniqueNums))
                            pairsAppend (answers, eachPair1, eachPair2);
                    }
                }
            }
        }
    }
    return answers;  
}
void fourSum_main()
{
    //int k = 3;
    //std::vector <int> A = {0,0, 2,1,1};   

    //int k = 5;
    //std::vector <int> A = {0, 0, 0, 1, 1, 3, 3, 4};   

    //int  k = 23;
    //std::vector <int> A = {10, 2, 3, 15, 3, 4, 5, 7, 8};   
    int k = 179;
    std::vector <int> A = {88, 84, 3, 51, 54, 99, 32, 60, 76, 68, 39, 12, 26, 86, 94, 39, 95, 70, 34, 78, 67, 1, 97, 2, 17, 92, 52};

    std::vector <std::vector <int> >answer ;
    //answer = fourSum_method1 (A, k);
    //answer = fourSum_method2 (A, k);
    //answer = fourSum_method3 (A, k);
    //answer = fourSum_method4 (A, k);
    answer = fourSum_method5 (A, k);
    for (auto eachIntArray : answer)
    {
        for (auto eachInt : eachIntArray)
            std::cout << eachInt << " ";
        std::cout << std::endl;
    }
}

//-------------------------------------------------
//      maxArrayIndex
//-------------------------------------------------
int maxIndexDiff(int arr[], int n)
{
    int max = 0;
    for (int i=0; i<n; i++)
    {
        for (int j=n-1; j>i; j--)
        {
            if (arr[i]<=arr[j])
            {
                if (max < j-i)
                    max = j-i;
                break;
            }
        }
        if (n-i-2<=max)
            break;
    }
    return max;
}

void maxArrayIndex_main()
{
    int n = 9;
    int A[] = {34, 8, 10, 3, 2, 80, 30, 33, 1};
    std::cout << maxIndexDiff(A, n) << std::endl;
}

//-------------------------------------------------
//      palindromeIronMan
//-------------------------------------------------
char to_lower(char c)
{
    if (c <= 'Z' && c >= 'A')
        return c+('a'-'A');
    return c;
}
bool isPalindromeIronMan (std::string palStr)
{
    int n = palStr.length();
    for (int i=0, j=n-1; i<j; i++, j--)
    {
       while(!std::isalnum(palStr[i]) && i<j)
           i++;

       while(!std::isalnum(palStr[j]) && j>i)
           j--;
       if (j<=i)
           return true;
       if (to_lower(palStr[i])!=to_lower(palStr[j]))
           return false;
    }    

    return true;
}
void palindromeIronMan_main()
{
    int T;
    std::string palStr;
    bool answers[100];
    std::cin >>T;
    std::cin.ignore();
    for (int i=0; i<T; i++)
    {
        std::getline (std::cin, palStr);
        answers[i] = isPalindromeIronMan(palStr);
    }
    for (int i=0; i<T;i++)
        std::cout << (answers[i] ? "YES" : "NO") << std::endl;

}

//-------------------------------------------------
//     closedSumof3
//-------------------------------------------------
int threeSumClosest(std::vector<int> arr, int target)
{
    int value = 0;
    int tmp = 0;
    int total = arr.size();
    if (total < 3)
       return 0;
    int minValue = arr[0]+arr[1]+arr[2];
    int min = std::abs (minValue - target); 
    for (int i=0; i<total; i++)
    {
        for (int j=i+1; j<total; j++)
        {
            for (int k=j+1; k<total; k++)
            {
                value = arr[i]+arr[j]+arr[k];
                tmp = std::abs (value-target);
                if (tmp < min || (tmp==min && value > minValue))
                {
                    min = tmp;
                    minValue = value;
                    if (!min)
                        return minValue;
                }
            }
        }
    }
    return minValue;
}
void closedSumof3_main()
{
    std::vector<int> arr = {-7,9,8,3,1,1};
    std::cout << threeSumClosest (arr, 2) << std::endl;   

    std::vector<int> arr1 = {5,2,7,5};
    std::cout << threeSumClosest (arr1, 13) << std::endl;   

    std::vector<int> arr2 = {93, 28, 61, 50, -9, 35, 35, 22, 97};
    std::cout << threeSumClosest (arr2, 195) << std::endl;   
}


//-------------------------------------------------
//     longestValidParanthesis
//-------------------------------------------------
typedef long long int ll;
ll longestbalancedPar (std::string &par)
{
    ll val, maxNum = 0;
    std::vector<std::pair<ll, ll>>entry;
    std::vector<bool>entrymutable;
    ll sum =0 ;
    for (ll i=0; i<par.length(); i++)
    {
        if (par[i] == '(')
        {
            if (sum == 0)
            {
                entry.push_back (std::make_pair(i, i));
                entrymutable.push_back(true);
            }
            sum++;
        }
        else if ( par[i] == ')')
        {
            if (sum == 0)
            {
                if (entry.size())
                    entrymutable[entry.size()-1] = false;
                continue;
            }
            sum--;
            if (sum == 0)
            {
                if (entry.size()>1 && entrymutable[entry.size()-2]==true)
                {
                    entry[entry.size()-2].second = i;
                    entry.pop_back();
                    entrymutable.pop_back();
                }
                else
                {
                    entry[entry.size()-1].second = i;
                }
                val = entry[entry.size()-1].second - entry[entry.size()-1].first +1;
                if (maxNum < val)
                    maxNum = val;
             }
        }
    }
    if (sum)
        entry[entry.size()-1].second = par.length()-1-sum;
    val = entry[entry.size()-1].second - entry[entry.size()-1].first+1;
    if (maxNum < val)
        maxNum = val;
    return maxNum;
}

void longestValidParanthesis_main()
{
    int T;
    std::string par;
    std::vector<std::string>pars;
    std::cin >> T;
    for (int i=0; i<T; i++)
    {
        std::cin >> par;
        pars.push_back(par);
    }
    for (int i=0; i<T; i++)
    {
        std::cout << longestbalancedPar(pars[i]) <<std::endl;    
    
    }
}
//-------------------------------------------------
//        customSortComparator
//-------------------------------------------------

bool compareIntervals (const std::pair<int, int> &a, const std::pair<int, int>&b)
{
    return a.first < b.first;
}
std::vector<std::pair<int,int>> overlappedInterval(std::vector<std::pair<int,int>> &vec, int n) 
{
    std::vector<std::pair<int,int>> answer;
    std::pair <int, int> tmpP;
    std::sort (vec.begin(), vec.end(), compareIntervals);
    tmpP = vec[0];
    for (int i=1; i<n; i++)
    {
        if (vec[i].first <= tmpP.second)
            tmpP.second = std::max( tmpP.second, vec[i].second);
        else
        {
            answer.push_back (tmpP);
            tmpP = vec[i];
        }
    }  
    answer.push_back(tmpP);
    return answer;
}

void customSortComparator_main()
{
    //std::vector <std::pair<int,int>> intervals = {{3, 5}, {7, 6}, {1,10}, {2,8}};
    //std::vector <std::pair<int,int>> intervals = {{1,3},{2,4},{6,8},{9,10}};
    std::vector <std::pair<int,int>> intervals = {{1,10},{4,5},{2,3}};
    std::vector <std::pair<int,int>> answer = overlappedInterval (intervals, 3);
    for (auto p : intervals)
        std::cout << p.first << " -- " << p.second << std::endl;
    std::cout <<  std::endl << std::endl;
    for (auto p : answer)
        std::cout << p.first << " -- " << p.second << std::endl;
}

//-------------------------------------------------
//        findCelebrityInMatrix
//-------------------------------------------------
int celebrity(std::vector<std::vector<int>>& M, int n)
{
    
    for (int i=0; i<n; i++)
    {
        int orVal = 0, andVal = 1;
        for (int j=0; j<n && !orVal; j++)
        {
            orVal |= M[i][j];
        }
        if (!orVal)
        {
            for (int k=0; k<n && andVal; k++)
            {
                if (k == i) 
                    continue;
                andVal &= M[k][i];
            }
            if (andVal)
                return i;
        }
    }
    return -1;
}
void findCelebrityInMatrix_main()
{
    int n= 2;
    //std::vector <std::vector<int>> M = {{0, 1, 0}, {0 , 0 ,0}, {0,1,0} };
    std::vector <std::vector<int>> M = {{0, 1}, {1 , 0 } };
    std::cout << celebrity (M, n) << std::endl;    
}


//-------------------------------------------------
//        replace O's With X's
//-------------------------------------------------

bool isSurroundedByXs (std::vector<std::vector<char>> &matrix, int i, int j, int n, int m, bool isSet)
{
    if (!isSet)
        return false;
    bool foundX = false;
    for (int x=i-1; x>=0; x--) // search up
        if (matrix[x][j] == 'X')
            foundX = true;
    if (!foundX)
        return false;

    foundX = false;
    for (int x=i+1; x<n; x++) // search down
        if (matrix[x][j] == 'X')
            foundX = true;
    if (!foundX)
        return false;

    foundX = false;
    for (int y=j-1; y>=0; y--) // search left
        if (matrix[i][y] == 'X')
            foundX = true;
    if (!foundX)
        return false;

    foundX = false;
    for (int y=j+1; y<m; y++) // search right
        if (matrix[i][y] == 'X')
            foundX = true;
    if (!foundX)
        return false;

    return true;
}

bool findConnectedOs (std::vector<std::vector<char>>&matrix, std::vector<std::vector<bool>>&visited, 
                        int i, int j, int n, int m, bool isSet,
                        std::vector <std::pair<int,int>> &os)
{
    visited[i][j] = true;
    os.push_back (std::make_pair(i,j));
    isSet = isSet & isSurroundedByXs (matrix, i, j, n, m, isSet);
    if (i>0 && matrix[i-1][j]=='O' && !visited[i-1][j])
    {
        isSet = findConnectedOs (matrix, visited, i-1, j, n, m, isSet, os);
    }
    if (i<n-1 && matrix[i+1][j]=='O' && !visited[i+1][j])
    {
        isSet = findConnectedOs (matrix, visited, i+1, j, n, m, isSet, os);
    }
    if (j>0 && matrix[i][j-1]=='O' && !visited[i][j-1])
    {
        isSet = findConnectedOs (matrix, visited, i, j-1, n, m, isSet, os);
    }
    if (j<m-1 && matrix[i][j+1]=='O' && !visited[i][j+1])
    {
        isSet = findConnectedOs (matrix, visited, i, j+1, n, m, isSet, os);
    }
    return isSet;
}
void updateOs (std::vector<std::vector<char>>&matrix, std::vector<std::pair<int,int>> &os, bool isSet)
{
    if (!isSet)
        return;
    for (auto &index : os)
    {
        matrix[index.first][index.second] = 'X';
    }
}
void replaceOsWithXs (std::vector<std::vector<char>>&matrix, int n, int m)
{
    std::vector<std::vector<bool>>visited(n, std::vector<bool>(m,false));
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++) 
        {
            if (matrix[i][j] == 'O' && !visited[i][j])
            {
                std::vector <std::pair<int, int>> os;
                bool isSet = findConnectedOs (matrix, visited, i, j, n, m, true, os);
                updateOs(matrix, os, isSet);
                //markConnectedOsX (matrix, os, isSet);
            }
        }

    }

    for (auto row : matrix)
    {
        for (auto c: row)
        {   
            std::cout << c << " ";
        }
    }
    std::cout << std::endl;
    return;
}
void replaceOsWithXs_main()
{
    int T, n[10], m[10];
    std::vector <std::vector<char>> matrix[10];
    std::cin >> T ;

    for (int i=0; i<T; i++)
    {
        std::cin >> n[i] >> m[i];
        matrix[i].resize(n[i]);
        for (int ni=0; ni<n[i]; ni++)
        {
            matrix[i][ni].resize(m[i], 0);
            for (int mi=0; mi<m[i]; mi++)
            {
                std::cin >>matrix[i][ni][mi];
            }
        }   
    }
    for (int i=0; i<T; i++)
    {
        replaceOsWithXs(matrix[i], n[i], m[i]);
    }
}
int main()
{
    //eggDrop_main();
    //maxAmount_main();
    //palindrome_main();
    //specialKeyboard_main();
    //matrix_main();
    //btree_main();
    //longestWord_main();
    //uglyNumber_main();
    //wordBoggle_1_main();
    //vectorTest_main();
    //jobAssignment_main();
    //bitsSum_main();
    //countStringABC_main();
    //numberPatterID_main();
    //fourSum_main();
    //maxArrayIndex_main();
    //palindromeIronMan_main();
    //closedSumof3_main();
    longestValidParanthesis_main();
    //customSortComparator_main();
    //findCelebrityInMatrix_main();
    //replaceOsWithXs_main();
}
