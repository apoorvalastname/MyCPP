#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>

void testRecursion (std::map<int, int> &mymap)
{
    for (auto elm = mymap.begin() ; elm!=mymap.end(); elm++)
        std::cout << elm->first << "  " << elm->second << std::endl;
    std::cout <<std::endl;
    std::map <int, int> tmpMap = mymap;
    tmpMap.erase (tmpMap.begin());
    testRecursion (tmpMap);
}


void testMapVectorPair (std::map <int, int> &mymap)
{
    // create a map with <sum> and vector of pairs
    std::map <int, std::vector <std::pair <int, int>>> d2map;
    
    for (auto it1 = mymap.begin(); it1 != mymap.end(); it1++)
    {
        for (auto it2 = std::next(it1); it2 != mymap.end(); it2++)
        {
            d2map[it1->first+it2->first].push_back(std::make_pair(it1->first, it2->first));
        }
    }
}

void testVectorIterator ()
{
    std::vector <int> test = {1,2,3, 9, 6, 4,5, 2, 1, 3, 8, 3};
    int i=1;
    for (auto it=test.begin(); it!=test.end(); it++, i++)
    {
        std::cout << i << " " << *it << std::endl;
    }
    std::cout << "2 :: " <<std::count (test.begin(), test.end(), 2) << std::endl;
    auto pos2 = test.begin();
    i=0;
    while (pos2 != test.end())
    {
        pos2 = std::find (std::next(pos2), test.end(), 2);
        std::cout << ++i << "  "<< *pos2 << std::endl;
    }
}

bool comp (std::pair<int, std::pair<int,int>> &p1, std::pair<int, std::pair<int,int>> &p2)
{
    return p1.first > p2.first;
}
void testEqualRangeOnVectorWithCompareFunction(std::map<int, int>&mymap, int k)
{
    //std::vector <std::pair<int, std::pair<int, int>>> sums;
    std::vector <int> sums;
    std::vector <std::pair<int, int>> sumNums;
    for (auto itr1=mymap.begin(); itr1!=mymap.end(); itr1++)
    {
        for (auto itr2=(itr1->second>1 ?itr1 : std::next(itr1)); itr2 !=mymap.end(); itr2++)
        {
            int num1 = itr1->first, num2 = itr2->first;
            sums.push_back(num1+num2);
            sumNums.push_back(std::make_pair(num1, num2));
        }
    }
    for (int i=0; i<sums.size(); i++)
    {
        int remK = k-sums[i];
        int j = i;
        std::vector<int>::iterator it;
        for (std::vector<int>::iterator it = sums.begin(); ((it=std::find(sums.begin()+j, sums.end(), remK)) != sums.end()); j++)
        {   
            j = std::distance (sums.begin(), it);
            std::cout << sums[i] << "-" << sumNums[i].first<<":"<<sumNums[i].second <<"    ";
            std::cout << sums[j] << "-" << sumNums[j].first<<":"<<sumNums[j].second <<std::endl;
        }
    }
}

void testMultiMap(std::map<int, int>&mymap, int k)
{
    std::multimap<int,std::pair<int,int>> my2d;
    for (auto itr1=mymap.begin(); itr1!=mymap.end(); itr1++)
    {
        for (auto itr2=(itr1->second>1 ?itr1 : std::next(itr1)); itr2 !=mymap.end(); itr2++)
        {
            my2d.insert({itr1->first + itr2->first,  std::make_pair(itr1->first, itr2->first)});
        }   
    }

    
    // for each element in the multimap, check if there is a corresponding k-sum  
    for (auto itr = my2d.begin(); itr!=my2d.end(); itr++)
    {
        int sum = k-itr->first;
        auto valuePos = my2d.equal_range (sum);
        for (auto posItr = valuePos.first; posItr!= valuePos.second; posItr++)
        {
            std::cout << itr->first <<" "<< itr->second.first <<" "<< itr->second.second << "- ";
            std::cout << posItr->first << " "<<posItr->second.first <<" "<<posItr->second.second <<std::endl;
            //if (possiblePairSum ())
            //     appendPairSumAnswer()
        }       
    }
}
void testMap()
{
    std::map <int, int> myset ;

    myset[1] = 2;
    myset[3] = 1;
    myset[7] = 3;
    myset[4] = 2;
    myset[5] = 1;
    myset[6] = 3;

    for (auto &elm: myset)
        std::cout << elm.first << " -- "<< elm.second <<std::endl;
    //testRecursion (myset);
    //testMapVectorPair (myset);
    //testVectorIterator ();
    //testMultiMap(myset, 15);
    testEqualRangeOnVectorWithCompareFunction(myset, 15);
}

// word boggle
// create a trie from a vector or strings dictionary
// dfs the matrix to see if we can find any string in the dictionary
class Trie
{
    public:
        std::unordered_map <char, Trie *> letters;
        bool isWord;
        bool isFound;
};

Trie *createTrie (std::vector<std::string> &dict)
{
    Trie *topNode = new Trie;
    Trie *head = topNode;
    for (auto &word : dict)
    {
        head = topNode;
        for (auto &c : word)
        {
            if (head->letters.find(c) == head->letters.end())
                head->letters[c] = new Trie;
            head = head->letters[c];
        }
        head->isWord = true;
    }
    return topNode;
}

void dfs(std::vector<std::vector<char>> &matrix, int i, int j, Trie *dict, std::string answer, std::vector<std::vector<bool>>visited, std::vector<std::string> &answers, int N, int M)
{
    if (dict->letters.find(matrix[i][j]) != dict->letters.end())
    {
        answer.append(1u,matrix[i][j]);
        dict = dict->letters[matrix[i][j]];
        if (dict->isWord && !dict->isFound)
        {
            answers.push_back(answer);
            dict->isFound = true;
        }
        visited[i][j] = true;
        int maxX = (i<N-1?i+1:i);
        int maxY = (j<M-1?j+1:j);
        for (int x=(i?i-1:i); x<=maxX; x++)
        {
            for (int y=(j?j-1:j); y<=maxY; y++)
            {
                if (!((x==i) && (y==j)) && !(visited[x][y]))
                {
                    dfs(matrix, x, y, dict, answer, visited, answers, N, M);
                }
            }
        }
    }
}

void trie_main()
{
//    int N=3, M=3;
//    std::vector<std::vector<char>> matrix = {{'G','I','Z'}, {'U','E','K'}, {'Q','S','E'}};
//    std::vector<std::string> dict = {"GEEKS", "FOR", "QUIZ", "GO"};
    int N=4, M=2;
    std::vector<std::vector<char>> matrix = {{'f','f'}, {'d','e'}, {'f','b'}, {'b','e'}};
    std::vector<std::string> dict = {"dfd", "ded", "fd", "e", "dec", "df"};
    Trie *head = createTrie(dict);
    std::vector<std::vector<bool>> visited(N, std::vector<bool>(M, false));
    std::string answer;
    std::vector<std::string>answers;

    for (int i=0; i<N; i++)
    {
        std::vector<char> eachRow = matrix[i];
        for (int j=0; j<M; j++)
        {
            dfs(matrix, i, j, head, answer, visited, answers, N, M);
        }
    }

    for (auto ans : answers)
        std::cout << ans << std::endl;
}


int main()
{
    //testMap();
    trie_main();
}
