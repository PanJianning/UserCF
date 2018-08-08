#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <ostream>
#include <cstdio>
#include "base.hpp"
#include "utils.hpp"

namespace CF {

struct usr_sim {
    int uid;
    float sim;
    usr_sim(): uid(-1),sim(0) {}
    usr_sim(int uid, float sim): uid(uid), sim(sim) {}
    bool operator<(const usr_sim& other) {
        return this->sim > other.sim;
    }
    friend std::ostream& operator<<(std::ostream& out, const usr_sim& instance) {
        out << '(' << instance.uid << ',' << instance.sim << ')';
        return out;
    }
};


class UserCF : public BaseCF {
public:
    UserCF(int num_user, int num_item, const std::vector<usr_item>& usr_items) {
        this->num_user = num_user;
        this->num_item = num_item;
        u2i.resize(num_user+1);
        similarity.resize(num_user+1);
        _make_similary_matrix(usr_items);
    }
    std::vector<int> recommend(int uid, int topk) {
        std::vector<int> items;
        std::unordered_map<int,bool> should_exclude;
        for(const int &iid: u2i[uid]) {
            should_exclude[iid] = true;
        }
        int cnt = 0;
        for(int i = 0; i < similarity[uid].size(); i++) {
            int v = similarity[uid][i].uid;
            for(int &iid : u2i[v]) {
                if(should_exclude[iid]) continue;
                should_exclude[iid] = true;
                items.push_back(iid);
                cnt++;
                if(cnt == topk) break;
            }
            if(cnt == topk) break;
        }
        return items;
    }
private:

    void _make_similary_matrix(const std::vector<usr_item>& usr_items) {

        std::vector<std::vector<int> > i2u(this->num_item);
        std::vector<int> n_like_items(this->num_user, 0);
        for(const auto & ui : usr_items) {
            i2u[ui.iid].push_back(ui.uid);
            u2i[ui.uid].push_back(ui.iid);
            n_like_items[ui.uid] += 1;
        }

        std::unordered_map<int, std::unordered_map<int,int> > uu_common_item;
        _make_uu_common_item(i2u, uu_common_item);

        for(auto it1 = uu_common_item.begin(); it1 != uu_common_item.end(); it1++) {
            std::unordered_map<int, int>& mm = it1->second;
            for(auto it2 = mm.begin(); it2 != mm.end(); it2++) {
                const int& u = it1->first;
                const int& v = it2->first;
                float sim = static_cast<float>(it2->second)/sqrt(n_like_items[u]*n_like_items[v]);
                similarity[it1->first].push_back(usr_sim(v,sim));
            }
        }

        for(auto &v : similarity) {
            std::sort(v.begin(),v.end());
        }

    }

    void _make_uu_common_item(std::vector<std::vector<int> >& i2u,
                              std::unordered_map<int, std::unordered_map<int,int> >& uu_common_item) {

        for(const auto& usrs : i2u) {
            for(int i = 0; i < usrs.size(); i++) {
                for(int j = 0; j < usrs.size(); j++) {
                    if(i!=j) {
                        const int& u = usrs[i];
                        const int& v = usrs[j];
                        if(!uu_common_item.count(u)) {
                            std::unordered_map<int,int> tmp;
                            tmp[v] = 1;
                            uu_common_item[u] = tmp;
                        } else {
                            uu_common_item[u][v] += 1;
                        }
                    }
                }
            }
        }

    }

    int num_user;
    int num_item;
    std::vector<std::vector<int> > u2i;
    std::vector<std::vector<usr_sim> > similarity;
};

}
