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

void dfs1(vector<vector<int> >& graph, int i, int&t, vector<bool>& explored, vector<int>& f_times)
{
    explored[i] = true;
    for(int j=0;j<graph[i].size();j++)
    {
        if (!explored[graph[i][j]])
            dfs1(graph,graph[i][j],t,explored,f_times);
    }
    t++;
    f_times[t] = i;
}


void dfs2(vector<vector<int> >& graph, int i, int s, vector<bool>& explored, vector<int>& leader)
{
    explored[i] = true;
    leader[i] = s;
    for(int j=0;j<graph[i].size();j++)
    {
        if (!explored[graph[i][j]])
            dfs2(graph,graph[i][j],s,explored,leader);
    }
}



int main(int argc, char** argv)
{
    ifstream f;
    f.open(argv[1]);
    int max_vert=-1;
    multiset<pair<int,int> > ad_set;
    string s;
    while (getline(f,s))
    {
        stringstream st(s);
        int tail,head;
        st>>tail>>head;
        if (tail - 1 > max_vert)
            max_vert = tail - 1;
        if (head -1 > max_vert)
            max_vert = head - 1;
        ad_set.insert(make_pair(tail-1, head-1));
    }
    vector<vector<int> > g(max_vert),g_rev(max_vert);
    for (multiset<pair<int,int> >::iterator mi=ad_set.begin();mi != ad_set.end(); mi++)
    {
        int first = (*mi).first;
        int second = (*mi).second;
        g[first].push_back(second);
        g_rev[second].push_back(first);
    }
    vector<int> f_times(max_vert + 1, -1);
    vector<int> leader(max_vert + 1, -1);
    vector<bool> explored(max_vert + 1, false);
    int l,t=-1;
    for (int i=max_vert;i>=0;i--)
    {
        if (!explored[i])
        {
            dfs1(g_rev,i,t,explored,f_times);

        }
    }
    explored = vector<bool> (max_vert + 1,false);
    for (int i=max_vert;i>=0;i--)
    {
        if (!explored[f_times[i]])
        {
            l = f_times[i];
            dfs2(g,f_times[i],l,explored,leader);
        }
    }
    map<int,int> scc;
    for (int i=0;i<leader.size();i++)
        scc[leader[i]]++;
    vector<int> result;
    for (map<int,int>::iterator mi=scc.begin();mi!=scc.end();mi++)
    {
        result.push_back((*mi).second);
    }
    sort(result.begin(),result.end());
    for(int i=result.size() - 1 ; i>= ((int(result.size())-6>=0)?result.size()-6:0);i--)
        cout<<result[i]<<" ";
    cout<<"Answer is "<<max_vert<<"\n";
    return 0;
}
