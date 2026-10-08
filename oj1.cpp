#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
using namespace std;

class Graph
{
private:
    vector<vector<int>> gh;
    vector<int> id;
    vector<pair<int, int>> edge_id;

public:
    Graph()
    {
        gh = vector<vector<int>>();
    }

    int add_vertex(int x)
    {
        int v = id.size();
        for (int i : id)
        {
            if (i == x)
            {
                return v;
            }
        }

        gh.push_back(vector<int>(v, 0));
        for (int i = 0; i < v + 1; i++)
        {
            gh[i].push_back(0);
        }
        id.push_back(x);
        return v + 1;
    }
    void add_edge(int u, int v)
    {

        auto it1 = find(id.begin(), id.end(), u);
        auto it2 = find(id.begin(), id.end(), v);

        if (it1 == id.end() || it2 == id.end())
        {
            return;
        }

        edge_id.push_back({u, v});

        int index1 = it1 - id.begin();
        int index2 = it2 - id.begin();

        gh[index1][index2]++;
        gh[index2][index1]++;
    }

    int vertex_count() const
    {
        return id.size();
    }
    int edge_count() const
    {
        return edge_id.size();
    }
    int degree(int x) const
    {
        auto it = find(id.begin(), id.end(), x);
        int index = it - id.begin();

        int sum = accumulate(gh[index].begin(), gh[index].end(), 0);
        return sum;
    }
    int edge_multiplicity(int u, int v) const
    {
        auto it1 = find(id.begin(), id.end(), u);
        auto it2 = find(id.begin(), id.end(), v);

        if (it1 == id.end() || it2 == id.end())
        {
            return 0;
        }

        int index1 = it1 - id.begin();
        int index2 = it2 - id.begin();

        return gh[index1][index2];
    }

    Graph vertex_induced_subgraph(const std::vector<int> &vertices) const
    {
        Graph subgraph;

        for (int i : vertices)
        {
            subgraph.add_vertex(i);
        }

        for (const auto &it : edge_id)
        {
            int u = it.first;
            int v = it.second;

            bool u_exist = find(vertices.begin(), vertices.end(), u) != vertices.end();
            bool v_exist = find(vertices.begin(), vertices.end(), v) != vertices.end();
            if (u_exist && v_exist)
            {
                subgraph.add_edge(u, v);
            }
        }
        return subgraph;
    }
    Graph edge_induced_subgraph(const std::vector<int> &edge_ids) const
    {
        Graph subgraph;
        for (int i : edge_ids)
        {
            int u = edge_id[i - 1].first;
            int v = edge_id[i - 1].second;

            subgraph.add_vertex(u);
            subgraph.add_vertex(v);
        }

        for (int j : edge_ids)
        {

            int u = edge_id[j - 1].first;
            int v = edge_id[j - 1].second;
            subgraph.add_edge(u, v);
        }

        return subgraph;
    }
};