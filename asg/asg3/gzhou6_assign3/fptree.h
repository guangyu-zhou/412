#ifndef FPTREE_H
#define FPTREE_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <queue>
#include <algorithm>
#include <unordered_map>


class FP_tree
{

private:
    struct Node
    {
        int Node_id;
        int freq_cnt;
        vector <Node* > children;
        Node* parent;

        Node(int id, int cnt): Node_id(id), freq_cnt(cnt), parent(NULL){}

    };


public:
        FP_tree();
        ~FP_tree();
        void printtree(Node* rt);

        void insert(vector <vector <int> > & topic_table, vector<pair<int,int> > & sorted_L, map<int,int> & L1, map <vector <int>, int> & freq_patterns);

        Node* root;

private:
        void _insert(queue<int> elems, Node* curnode,  map<int, vector <Node*> >& header_table_map);
        bool mycompare (pair< vector <int> ,int> i, pair< vector <int> ,int> j);



};
#include "fptree.cpp"
#endif
