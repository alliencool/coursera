#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <cstdlib>
#include <ctime>
#include <thread>

using namespace std;

pair<int,int> get_ind_set(multiset<pair<int,int> >& edges, int num)
{
    pair<int,int> result;
    int i = 0;
    multiset<pair<int,int> >::iterator si = edges.begin();
    while(i <= num)
    {
        result = *si;
        si++;
        i++;
    }
    return result;
}

int karger_min_cut(multiset<pair<int,int> > edges, set<int> vertices)
{
    while (vertices.size() > 2)
    {
        int chosen = rand() % edges.size();
        pair<int,int> edge = get_ind_set(edges, chosen);
        vertices.erase(edge.second);
        multiset<pair<int,int> > new_edges;
        for(multiset<pair<int,int> >::iterator si=edges.begin();si!=edges.end();si++)
        {
            int first,second;
            first = (*si).first;
            if (first == edge.second)
                first = edge.first;
            second = (*si).second;
            if (second == edge.second)
                second = edge.first;
            if (first != second)
                new_edges.insert(make_pair(first,second));
        }
        edges = new_edges;
    }
    return edges.size();
}

int main(int argc, char** argv)
{
    ifstream f;
    f.open(argv[1]);
    multiset<pair<int,int> > ad_set;
    set<int> vertices;
    string s;
    while (getline(f,s))
    {
        stringstream st(s);
        int ind,tmp;
        st>>ind;
        vertices.insert(ind);
        while(true)
        {
            st>>tmp;
            if (st.eof())
                break;
            if (ad_set.count(make_pair(ind,tmp)) + ad_set.count(make_pair(tmp,ind)) == 0)
                ad_set.insert(make_pair(ind,tmp));
        }
    }
    f.close();
    int mn = -1;
    for (int i=0;i<vertices.size() * vertices.size();i++)
    {
        srand(time(NULL));
        int r = karger_min_cut(ad_set,vertices);
        if (r < mn || mn == -1)
            mn = r;
        if (i % 1000 == 0)
        {
            cout<<i<<" step. The answer for now is "<<mn<<"\n";
        }
    }
    cout<<"Answer is "<<mn<<"\n";
    return 0;
}
