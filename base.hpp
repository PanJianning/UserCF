#ifndef CF_BASE_HPP
#define CF_BASE_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <ostream>
#include <cstdio>
#include <iostream>
#include "utils.hpp"

namespace CF {

class BaseCF {
public:
    virtual std::vector<int> recommend(int uid, int topk) = 0;
    virtual ~BaseCF() = default;
};

class MostPopular : public BaseCF {
public:
    MostPopular(int num_user, int num_item, const std::vector<usr_item>& usr_items) {
        this->num_user = num_user;
        this->num_item = num_item;
        popular_items.resize(num_item+1,0);
        u2i.resize(num_user+1);
        for(auto& ui : usr_items) {
            popular_items[ui.iid] += 1;
            u2i[ui.uid].push_back(ui.iid);
        }
        popular_items = argsort(popular_items);
    }
    std::vector<int> recommend(int uid, int topk) {
        std::vector<int> items;
        std::unordered_map<int,bool> should_exclude;
        for(const int &iid : u2i[uid]) {
            should_exclude[iid] = true;
        }
        int cnt = 0;
        for(const auto& iid : popular_items) {
            if(should_exclude[iid])	continue;
            should_exclude[iid] = true;
            items.push_back(iid);
            cnt++;
            if(cnt == topk) break;
        }
        return items;
    }
private:
    std::vector<int> popular_items;
    std::vector<std::vector<int> > u2i;
    int num_user;
    int num_item;
};
}

#endif
