#ifndef CF_UTILS_HPP
#define CF_UTILS_HPP

#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <fstream>

namespace CF {

struct usr_item {
    int uid;
    int iid;
    usr_item(): uid(-1), iid(-1) {}
    usr_item(int uid, int iid): uid(uid), iid(iid) {}
};

std::vector<int> argsort(const std::vector<int>& nums) {
    std::vector<std::pair<int,int> > tmp;
    for(int i = 0; i < nums.size(); i++) {
        tmp.push_back(std::make_pair(i,nums[i]));
    }
    std::sort(tmp.begin(),tmp.end(), [](const std::pair<int,int>& a,
    const std::pair<int,int>& b) {
        return a.second > b.second;
    });
    std::vector<int> res;
    for(auto item : tmp) {
        res.push_back(item.first);
    }
    return res;
}

int num_intersect(const std::vector<int>& item_pred, const std::vector<int>& item_true) {
    std::unordered_map<int,bool> mark;
    for(auto& item : item_true) mark[item] = true;
    int cnt = 0;
    for(auto& item : item_pred) {
        if(mark.count(item)) {
            cnt++;
        }
    }
    return cnt;
}

void load_user_items(const char* filepath, std::vector<usr_item>& usr_items) {
    usr_items.clear();
    std::fstream f;
    f.open(filepath, std::ios::in);
    int uid, iid, rat, timestamp;
    while(!f.eof()) {
        f >> uid >> iid >> rat >> timestamp;
        usr_items.push_back(usr_item(uid,iid));
    }
    f.close();
}

}
#endif
