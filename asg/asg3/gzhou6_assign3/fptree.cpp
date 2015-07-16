#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <queue>
#include <algorithm>
#include "fptree.h"
#include "comb.cpp"
#include "parse.h"


using namespace std;

FP_tree::FP_tree()
{
    root = new Node(-1,0);

}

FP_tree::~FP_tree()
{

}
bool FP_tree::mycompare (pair <vector <int>, int> i, pair <vector <int>, int> j) {return (i.second >  j.second);}

void FP_tree::insert(vector <vector <int> > & topic_table, vector<pair<int,int> > & sorted_L, map<int,int> & L1,  map <vector <int>, int> & freq_patterns)
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
        //cout << "vecs: " << header_table[i].first << endl;
        header_table_map[header_table[i].first] = Node_linked_list;
    }

    map<int,vector <Node*> >::iterator it;
    for(it = header_table_map.begin() ;it!=header_table_map.end() && cnt >0; it++){
        //cout << "map: " << it->first << endl;
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
    }

    int sum = 0;
    for(int row = 0; row < header_table.size(); row++)
    {
        //row = 0;
        vector <vector <Node* > > paths;
        /*** traverse each pointer list in the header table map  ***/
        for(int i = 0; i< header_table_map[header_table[row].first].size(); i++)
        {

            vector <Node* > cur_path;
            Node* curNodeBeta = header_table_map[header_table[row].first][i];
            //cout << "Node is " << curNodeBeta->Node_id << endl;
            while(curNodeBeta!= root)
            {
                // change to keep the end node as well!!!!!!!!!
                cur_path.push_back(curNodeBeta);
                curNodeBeta = curNodeBeta->parent;
                //cout << "Node parent is " << curNodeBeta->Node_id << endl;
            }
            if(cur_path.size()>1) /*** NOT SURE!!! ***/
                paths.push_back(cur_path);
            else if(cur_path.size() == 1);
                //cout << "1 Node path!!! " << cur_path[0]->Node_id << "with cnt " << cur_path[0]->freq_cnt << endl;
        }
        if(paths.empty()){  // ignore 1 node path
            //cout << "Oops" << endl;
            continue;
        }
        /*** print path ***/

        for(int i = 0; i< paths.size(); i++)
        {
            //cout << "path is ";
            //Node* end_node = paths[i][0];
            for(int j = 0; j < paths[i].size(); j++)
            {
                //paths[i][j]->freq_cnt
                //cout <<paths[i][j]->Node_id << "-";
            }
            //cout << " end sup"<< paths[i][0]->freq_cnt << endl;
        }

        /*** Path is right!!! ***/
        /*** Do permutation ***/
        // eg: base: g. path f:1, fm:2
        map <int, int> path_nodes;
        //int cur_base_node_id = header_table[row].first;
        //int cur_base_node_cnt = header_table[row].second;
        for(int i = 0; i< paths.size(); i++) /* MAY BE WRONG!!! */
        {
            Node* end_node = paths[i][0];

            for(int j = 1; j < paths[i].size(); j++)
            {
                int cur_node_id = paths[i][j]->Node_id;
                if(path_nodes.find(cur_node_id) != path_nodes.end())
                    path_nodes[cur_node_id] += end_node->freq_cnt;
                else
                    path_nodes[cur_node_id] = end_node->freq_cnt;
            }

        }
        map <int, int> path_nodes_min_sup = path_nodes;
        map<int,int>::iterator it2;
        int min_support = 100;
        for(it2 = path_nodes.begin(); it2 != path_nodes.end(); it2++)
        {
            //cout << "path_nodes  " <<  it2->first <<"  cnt " << it2->second << endl;

        }

        for(it2 = path_nodes.begin(); it2 != path_nodes.end(); it2++)
        {
            if(it2->second < min_support)
            {
                path_nodes_min_sup.erase(it2->first);
            }
        }

        for(it2 = path_nodes_min_sup.begin(); it2 != path_nodes_min_sup.end(); it2++)
        {
            //cout << "min_sup_nodes  " <<  it2->first <<"  cnt " << it2->second << endl;

        }
        /*** path_nodes_min_sup serves as a dict, need to go back to ori path to permute***/

        /*** Permutation!!! ***/
        //cout << " /*** Permutation!!! ***/ End node is " << paths[0][0]->Node_id << endl;
        map<int, int > paths_node_id;
        int cnt = 0, end_node_id;
        for(int i = 0; i< paths.size(); i++) /* MAY BE WRONG!!! */
        {
            //cout << "End node is " << paths[i][0]->Node_id << endl;
            end_node_id = paths[i][0]->Node_id;
            for(int j = 1; j < paths[i].size(); j++)
            {
                if(path_nodes_min_sup.find(paths[i][j]->Node_id)!=path_nodes_min_sup.end())
                {

                    paths_node_id[paths[i][j]->Node_id] = path_nodes_min_sup[paths[i][j]->Node_id];
                    //cout << "Node " << paths[i][j]->Node_id << " support OK " << paths_node_id[paths[i][j]->Node_id] << endl;
                }
                else ;
                    //cout << "Node " << paths[i][j]->Node_id << " support too low " << path_nodes[paths[i][j]->Node_id] << endl;
            }
        }

        //cout<<"--------------------------------------------------------\n";
        //cout << " /*** Permutation!!! ***/ End node is " << end_node_id << endl;
        //cout << " /*** Permutation!!! ***/ paths_node_id are "  << endl;


/*      map<int,int>::iterator it3;
        for(it3 = paths_node_id.begin(); it3 != paths_node_id.end(); it3++)
        {
            cout << it3->first <<"  cnt " << it3->second << endl;

        }*/
        int counter = 0;
        do_comb(freq_patterns, end_node_id, paths_node_id, counter);
        //cout << "counter is " << counter;
        // Adding 1 elem node:
        sum+=counter;


        //break;
    }
    map<int,int>::iterator it2;
    for(it2 = L1.begin(); it2!= L1.end(); it2 ++)
    {
        vector<int> temp;
        temp.push_back(it2->first);
        freq_patterns[temp] = it2->second;
    }
/*
     map<vector <int> ,int>::iterator it4;
     map<int, string> vocab_map = parse();
     //int line = 1;
    for(it4 = freq_patterns.begin(); it4 != freq_patterns.end(); it4++)
        {
            //if(it4->first.size() == 1)
                //it4->second = L1[it4->first[0]];
            //cout << "Line " << line << endl;
            //line++;
            cout << "Support # " << it4->second << "  ";
            cout << "Freq Pattern: ";
            for(int i = 0; i < it4->first.size(); i++)
                cout << vocab_map[it4->first[i]]<<" ";
            cout << endl;
        }

     //cout << endl<< "######## sum ######## is " << sum;

*/



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
        //cout << "new node " << newnode->Node_id << endl;

        /*----  update header_table  ---- */
        header_table_map[elems.front()].push_back(newnode);
        //cout << "new ht size is " <<  header_table_map[elems.front()].size() << endl;

    }
    elems.pop();
    if(!elems.empty())
        _insert(elems, nextNode, header_table_map);

}




