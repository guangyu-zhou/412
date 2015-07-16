#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <queue>
#include "fptree.h"


using namespace std;

FP_tree::FP_tree()
{
    root = new Node(-1,0);

}

FP_tree::~FP_tree()
{

}

void FP_tree::insert(vector <vector <int> > & topic_table, vector<pair<int,int> > & sorted_L)
{
    vector<pair<int, vector <Node*> > > header_table;
    /*** header_table should looks like:
    sorted_L[0]   ||  empty vector
    sorted_L[1]   ||  empty vector
        ...
    sorted_L[n-1]   ||  empty vector ***/
    for(int i = 0 ; i < sorted_L.size(); i++)
    {
        vector <Node*> Node_linked_list;
        pair<int, vector<Node*> > mypair;
        mypair.first = sorted_L[i].first;
        mypair.second = Node_linked_list;
        header_table.push_back(mypair);
    }

    int cnt = 10;
    map<int, vector <Node*> > header_table_map;

    for(int i = 0; i< header_table.size(); i++)
    {
        vector <Node*> Node_linked_list;
        cout << "vecs: " << header_table[i].first << endl;
        header_table_map[header_table[i].first] = Node_linked_list;
    }

    map<int,vector <Node*> >::iterator it;
    for(it = header_table_map.begin() ;it!=header_table_map.end() && cnt >0; it++){
        cout << "map: " << it->first << endl;
        cnt --;
    }

    for(int rows = 0 ; rows < 10; rows++){
        //cout << "vecs: " << header_table[rows].first << endl;
    }

    /*** Processing table ***/
    for(int rows = 0 ; rows < topic_table.size(); rows++)
    {
        queue<int> dumpQ;
        for(int i = 0; i < topic_table[rows].size(); i++)
        {
            dumpQ.push(topic_table[rows][i]);
        }

        _insert(dumpQ, root, header_table_map);
        //mytree.printtree(mytree.root);
    }

    /*** Checkking header_table_map ***/
    //if(header_table_map.find(3)==header_table_map.end())
    /*cout << "node 3 with ptr size " << header_table_map[3].size();
    cout << "node 4 with ptr size " << header_table_map[4].size();
    cout << "node 2 with ptr size " << header_table_map[2].size() << endl;*/
    cout << "header_table size " << header_table.size() << endl;
    for(int row = 0; row < header_table.size(); row++)
    {
        //row = 0;
        vector <vector <Node* > > paths;
        for(int i = 0; i< header_table_map[header_table[row].first].size(); i++)
        {

            vector <Node* > cur_path;
            Node* curNodeBeta = header_table_map[header_table[row].first][i];
            cout << "Node is " << curNodeBeta->Node_id << endl;
            while(curNodeBeta->parent != root)
            {
                curNodeBeta = curNodeBeta->parent;
                //cout << "Node parent is " << curNodeBeta->Node_id << endl;
                cur_path.push_back(curNodeBeta);
            }
            if(!cur_path.empty())
                paths.push_back(cur_path);
        }
        /*** print path ***/
        for(int i = 0; i< paths.size(); i++)
        {
            cout << "path is ";
            for(int j = 0; j < paths[i].size(); j++)
            {
                cout << paths[i][j]->Node_id << "-";
            }
            cout << endl;
        }
        /*** Do permutation ***/
        // eg: base: g. path f:1, fm:2
        map <int, int> path_nodes;
        int cur_base_node_id = header_table[row].first;
        int cur_base_node_cnt = header_table[row].second;
        for(int i = 0; i< paths.size(); i++)
        {
            for(int j = 0; j < paths[i].size(); j++)
            {
                int cur_node_id = paths[i][j]->Node_id;
                int cur_node_cnt = paths[i][j]->freq_cnt;
                if(path_nodes.find(cur_node_id) != path_nodes.end())
                    path_nodes[cur_node_id] += cur_node_cnt;
                else
                    path_nodes[cur_node_id] = cur_node_cnt;
            }

        }
        map <int, int> path_nodes_min_sup = path_nodes;
        map<int,int>::iterator it2;
        int min_support = 3;

        int cur_base_node_id = header_table[row].first;
        int cur_base_node_cnt = header_table[row].second;
        for(it2 = path_nodes.begin(); it2 != path_nodes.end(); it2++)
        {
            if(it2->second < min_support)
            {
                path_nodes_min_sup.erase(it2->first);
            }

        }
        //break;
    }




}

void FP_tree::printtree(Node* rt)
{
    //cout << "id "<< rt->Node_id << "cnt"<< rt->freq_cnt<< endl;
    if(rt->children.size()!=0)
    {
        //cout << "next branch" << endl;
        //for(int i = 0; i < rt->children.size(); i++)
        printtree(rt->children[0]);
        //cout << "size " << rt->children.size() << endl;
    }

}

void FP_tree::_insert(queue<int> elems, Node* curnode, map< int, vector <Node*> >& header_table_map)
{
    bool inchild = 0;
    Node* nextNode;
    for(int i=0; i< curnode->children.size(); i++)
    {
        if(curnode->children[i]->Node_id == elems.front())   // cur elem is in the child
        {
            curnode->children[i]->freq_cnt ++;
            nextNode = curnode->children[i];
            inchild = 1;
            break;
        }
    }
    if(!inchild){
        Node* newnode = new Node(elems.front(), 1);
        newnode->parent = curnode;
        curnode->children.push_back(newnode);
        nextNode = newnode;
        cout << "new node " << newnode->Node_id << endl;

        /*----  update header_table  ---- */
        header_table_map[elems.front()].push_back(newnode);
        cout << "new ht size is " <<  header_table_map[elems.front()].size() << endl;

    }
    elems.pop();
    if(!elems.empty())
        _insert(elems, nextNode, header_table_map);

}


