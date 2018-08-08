#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include "base.hpp"
#include "user_cf.hpp"

using namespace std;
using namespace CF;

struct Metric {
    double precision;
    double recall;
    double f1;
    Metric() = default;
    Metric(double p, double r): precision(p),recall(r) {
        if(p <= 10e-8 && r <= 10e-8)  f1 = 0;
        else f1 = 2*p*r/(p+r);
    }
    friend ostream& operator<<(ostream& out, const Metric& m) {
        char buffer[128];
        sprintf(buffer, "f1=%.2f%%, precision=%.2f%%, recall=%.2f%%", m.f1*100,
                m.precision*100, m.recall*100);
        out << buffer;
        return out;
    }
};

Metric evaluate(BaseCF* cf, int k, vector<vector<int>>& ground_true) {
    std::vector<int> rec_items;
    double total_inter = 0;
    int total_rec = 0;
    int total_true = 0;
    for(int uid = 0; uid < ground_true.size(); uid++) {
        if(ground_true[uid].empty()) continue;
        rec_items = cf->recommend(uid,k);
        total_inter += num_intersect(rec_items, ground_true[uid]);
        total_rec += rec_items.size();
        total_true += ground_true[uid].size();
    }
    return 	Metric(total_inter/total_rec, total_inter/total_true);
}

int main() {
    std::vector<usr_item> train_usr_items;
    std::vector<usr_item> test_usr_items;
    load_user_items("ml-100k/u1.base", train_usr_items);
    load_user_items("ml-100k/u1.test", test_usr_items);

    UserCF usr_cf(1000,2000, train_usr_items);
    MostPopular mp_cf(1000,2000,train_usr_items);

    std::vector<std::vector<int> > ground_true(1000);

    for(auto& ui: test_usr_items) {
        ground_true[ui.uid].push_back(ui.iid);
    }

    vector<int> ks = {5,10,20,40,80,160};
    cout << "MostPopular:\n";
    for(int k : ks) {
        cout << "k=" << k << ", " << evaluate(&mp_cf, k, ground_true) << endl;
    }
    cout << "UesrCF:\n";
    for(int k : ks) {
        cout << "k=" << k << ", " << evaluate(&usr_cf, k, ground_true) << endl;
    }
    return 0;
}
