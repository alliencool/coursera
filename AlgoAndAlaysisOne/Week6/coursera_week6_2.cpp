#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>

#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char** argv)
{
    
    ifstream f;
    f.open(argv[1]);
    string s;
    vector<int> numbers;
    int result=0;
    int median;
    while(getline(f,s))
    {
        int num;
        stringstream st(s);
        st>>num;
        numbers.push_back(num);
        sort(numbers.begin(),numbers.end());
        if (numbers.size() % 2 == 0)
            median = numbers[numbers.size() / 2 - 1];
        else
            median = numbers[numbers.size() / 2];
        result += median;
        result %= 10000;   
    }
    cout<<result<<"\n";
    return 0;
}
