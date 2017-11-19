#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>

#include <fstream>
#include <sstream>

using namespace std;


int main(int argc, char** argv)
{
    
    ifstream f;
    f.open(argv[1]);
    string s;
    unordered_set<long long> numbers;
    while(getline(f,s))
    {
        long long num;
        stringstream st(s);
        st>>num;
        numbers.insert(num);
    }
    cout<<numbers.size()<<"\n";
    return 0;
    vector<bool> flags(20001,false);
    for (unordered_set<long long>::iterator mi=numbers.begin();mi!=numbers.end();mi++)
    {
        long long num = (*mi);
        for(int i=-10000;i<=10000;i++)
            if  (  
                   ( num != (i - num) && numbers.count(i - num) > 0) 
                )
                flags[i + 10000] = true;
    }
    int result = 0;
    for (int i=0;i<flags.size();i++)
        if (flags[i] == true)
            result++;
    cout<<result<<"\n";
    return 0;
}
