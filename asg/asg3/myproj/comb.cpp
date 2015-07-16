#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int find_min_freq(vector <int> v1, map<int, int> a)
{
    int cur_min = a[v1[0]];
    for(int i = 0; i< v1.size(); i++)
    {
        if(cur_min > a[v1[i]]);
            cur_min = a[v1[i]];
    }
    return cur_min;
}

void do_comb(map <vector <int>, int> & ret_map, int end_n, map<int, int> a, int& cnt) {
    int n, r;
    n = a.size();
    vector <int> patterns;
    map<int,int>::iterator it;
    for(it = a.begin(); it != a.end(); it++)
    {
        patterns.push_back(it->first);
    }
    //std::cin >> r;
    //int test[4] = {1,2,3,4};
    //n = 4;
    //cout <<"n " << n;
    for(r = 0; r <= n; r++)
    {
        std::vector<bool> v(n);
        std::fill(v.begin() + r, v.end(), true);

        do {
            vector <int> ret_vec;
            ret_vec.push_back(end_n);
            cnt++;
            for (int i = 0; i < n; ++i) {
               if (!v[i]) {
                   //std::cout << patterns[i] << " ";
                   ret_vec.push_back(patterns[i]);
               }
            }
            //sort(ret_vec.begin(), ret_vec.end());
            ret_map[ret_vec] = find_min_freq(ret_vec, a);
            //ret_map[ret_vec] = 1;
            //std::cout << "\n";
        } while (std::next_permutation(v.begin(), v.end()));
        //ret_map[ret_vec] = find_min_freq(ret_vec);
        //for(int i = 0; i < ret_vec.size(); i++)
          //  cout << "vec is " << ret_vec[i]<< endl;


    }
    /*
    map<vector <int> ,int>::iterator it2;
    for(it2 = ret_map.begin(); it2 != ret_map.end(); it2++)
    {
        cout << "\n vec map is " << endl;
        for(int i = 0; i < it2->first.size(); i++)
            cout << it2->first[i]<<" ";
        cout << "\n counter is" << it2->second << endl;

    }*/
}
