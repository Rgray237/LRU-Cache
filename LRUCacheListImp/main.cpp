//
//  main.cpp
//  LRUCache
//
//  Created by Robert Gray on 4/7/17.
//  Copyright © 2017 Robert Gray. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <list>



template <class k_t,class v_t>
class LRUCache
{
public:
    LRUCache(int cap):cp(cap){};
    std::list<std::pair<k_t,v_t>> ls;
    std::unordered_map<k_t,decltype(ls.begin())> mp;
    int cp;
    
    
    void set(k_t k,v_t v)
    {
        typename decltype(mp)::iterator it;
        it = mp.find(k);
        if (it != mp.end())
        {
            ls.erase(it->second);
            mp.erase(it);
        }
        ls.push_front(std::pair<k_t,v_t>(k,v));
        mp.insert(std::make_pair(k, ls.begin()));
        clean();
    }
    v_t get(k_t k)
    {
        typename decltype(mp)::iterator it;
        v_t ret;
        it = mp.find(k);
        if (it != mp.end())
        {
            ret = it->second->second;
            ls.erase(it->second);
            mp.erase(it);
            ls.push_front(std::make_pair(k, ret));
            mp.insert(std::make_pair(k, ls.begin()));
        }
        else
            ret = -1;
        
        return ret;
    }
    void printAll()
    {
        auto it = ls.begin();
        for (it = ls.begin();it != ls.end();it++)
        {
            std::cout<<"("<<it->first<<","<<it->second<<")"<<" ";
        }
        std::cout<<std::endl;
    }
    void clean()
    {
        if (mp.size()>cp)
        {
            mp.erase(ls.back().first);
            ls.pop_back();
        
        }
    }
    
};


int main() {
    
    int n, capacity,i;
    std::cout<<"Please enter number of commands to process: ";
    std::cin >> n;
    std::cout<<"Please enter LRU Cache capacity int: ";
    std::cin>>capacity;
    LRUCache<int,std::string> l(capacity);
    for(i=0;i<n;i++) {
        std::cout<<"Please enter command: e.g. 'set 2 hello' or 'get 2'"<<std::endl;
        std::string command;
        std::cin >> command;
        if(command == "get") {
            int key;
            std::cin >> key;
            std::cout<<l.get(key)<<std::endl;
            l.printAll();
        }
        else if(command == "set") {
            int key;
            std::string value;
            std::cin >> key >> value;
            l.set(key, value);
            l.printAll();
        }
    }
    
    return 0;
}
