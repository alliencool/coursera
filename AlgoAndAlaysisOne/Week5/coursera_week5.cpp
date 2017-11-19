#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>

#include <fstream>
#include <sstream>

using namespace std;

template<class T> class MyHeap
{
    vector<pair<int, T> > array;
    map<T, int> positions;

    int parent_id(int i)
    {
        return (i - 1) / 2;
    }

    int get_min_child(int i)
    {
        int child1 = i * 2 + 1;
        int child2 = i * 2 + 2;
        if (child1 >= array.size())
            return -1; 
        if (child2 >= array.size())
            return child1;
        if (array[child1].first < array[child2].first)
            return child1;
        return child2;
    }

    void swap(int i, int j)
    {
        positions[array[i].second] = j;
        positions[array[j].second] = i;
        pair<int, T> tmp;
        tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }

    int heapify(int i)
    {
        int to_swap = get_min_child(i);
        if (to_swap != -1 && array[to_swap].first < array[i].first)
        {
            swap(to_swap, i);
            return to_swap;
        }
        return -1;
    }

    public:
    
    MyHeap()
    {
    }

    MyHeap(const vector<pair<int, T> > from_array) : 
        array(from_array)
    {
    }

    int size() const
    {
        return array.size();
    }
   
    void insert(pair<int, T> element)
    {
        array.push_back(element);
        positions[element.second] = array.size() - 1;
        
        int parent = parent_id(array.size() - 1);
        while (heapify(parent) != -1)
        {
            parent = parent_id(parent);
        }
    }

    void remove(T element)
    {
        int pos = positions[element];
        positions.erase(element);
        if (array.size() == 1)
        {
            array = vector<pair<int, T> > ();
            positions = map<T,int> ();
            return;
        }
        if (pos == array.size() - 1)
        {
            array.pop_back();
            return;
        }
        array[pos] = array.back();
        array.pop_back();
        while((pos = heapify(pos)) != -1) ;
    }

    bool in_heap(T element)
    {
        return (positions.count(element) > 0);
    }

    pair<int, T> get_min()
    {
        pair<int, T> result = array[0];
        remove(result.second);
        return result;
    }
};

void dijkstra_simple(map<int, map<int,int> >& ad_m, map<int, int>& min_length, int s)
{
    set<int> X;
    min_length[s] = 0;
    X.insert(s);
    while(X.size() != ad_m.size()) 
    {
        cout<<X.size()<<"\n";
        int nxt;
        int mn = 1000000000;
        for(set<int>::iterator si=X.begin();si!=X.end();si++)
        {
            for (map<int,int>::iterator mi = ad_m[*si].begin(); mi != ad_m[*si].end();mi++)
            {
                pair<int,int> candidate = (*mi);
                if(min_length[candidate.first] > (min_length[*si] + candidate.second))
                {
                    min_length[candidate.first] = min_length[*si] + candidate.second;
                }
                if (min_length[candidate.first] < mn && X.count(candidate.first) == 0)
                {
                    mn = min_length[candidate.first];
                    nxt = candidate.first;
                }
            }
        }
        X.insert(nxt);
    }
} 



void dijkstra(map<int, map<int,int> >& ad_m, map<int, int>& min_length, int s)
{
    set<int> X;
    min_length[s] = 0;
    MyHeap<int> m_heap;
    m_heap.insert(make_pair(0,s));
    while(X.size() != ad_m.size()) // && m_heap.size() > 0)
    {
        if (m_heap.size() == 0)
        {
            for (set<int>::iterator si=X.begin();si!=X.end();si++)
            {
                cout<<(*si)<<" ";

            }
            cout<<"\n";
            return;
        }
        pair<int,int> nxt = m_heap.get_min();
        X.insert(nxt.second);
        for (map<int,int>::iterator mi = ad_m[nxt.second].begin(); mi != ad_m[nxt.second].end();mi++)
        {
            pair<int,int> candidate = (*mi);
            if(min_length[candidate.first] > (min_length[nxt.second] + candidate.second))
            {
                min_length[candidate.first] = min_length[nxt.second] + candidate.second;
                if (m_heap.in_heap(candidate.first))
                    m_heap.remove(candidate.first);
                m_heap.insert(make_pair(min_length[candidate.first], candidate.first));
            }
        }
    }
} 

int main(int argc, char** argv)
{
    
    MyHeap<int> m_heap;
    map<int, map<int,int> > ad_m;
    map<int,int> min_length;
    ifstream f;
    f.open(argv[1]);
    string s;
    while(getline(f,s))
    {
        int vertex_a, vertex_b, length;
        stringstream st(s);
        st>>vertex_a;
        min_length[vertex_a] = 2000000000;
        string k;
        while (st>>k)
        { 
            vertex_b = stoi(k.substr(0, k.find(',')));
            length = stoi(k.substr(k.find(',') + 1, k.size() - k.find(',')));
            ad_m[vertex_a][vertex_b] = length;
            ad_m[vertex_b][vertex_a] = length;
        }
    }
    dijkstra_simple(ad_m, min_length, 1);
    cout<<min_length[7]<<","
        <<min_length[37]<<","
        <<min_length[59]<<","
        <<min_length[82]<<","
        <<min_length[99]<<","
        <<min_length[115]<<","
        <<min_length[133]<<","
        <<min_length[165]<<","
        <<min_length[188]<<","
        <<min_length[197]
        ;
    cout<<"\n";
    return 0;
}
