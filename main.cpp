#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

class NestedInteger {
  private:
    bool isInt;
    int my_int;
    std::vector<NestedInteger> my_vec;
    
  public:
    NestedInteger(int a_int) {
        my_int = a_int;
        isInt = true;
    }

    NestedInteger(const std::vector<NestedInteger> & vec) {
        my_vec = vec;
        isInt = false;
    }

    bool isInteger() {
        return isInt;
    }

    int getInteger() {
        if (isInt)
            return my_int;
    }

    const std::vector<NestedInteger> & getList() {
        if (!isInt)
            return my_vec;
    }
};

class solution {
  public:
    int depthSumInverse(const std::vector<NestedInteger> & nums) {
        std::vector<std::vector<int>> ints_weight;
        std::queue<NestedInteger> qu;
        for (auto & in : nums)
            qu.push(in);
        while (!qu.empty()) {
            std::vector<int> ints;
            std::queue<NestedInteger> children;
            while (!qu.empty()) {
                auto curr = qu.front();
                qu.pop();
                if (curr.isInteger()) {
                    ints.push_back(curr.getInteger());
                }
                else {
                    for (auto & n : curr.getList())
                        children.push(n);
                }
            }
            qu = children;
            ints_weight.push_back(ints);
        }

        int wsum = 0;
        for (int wt = 1; wt <= int(ints_weight.size()); wt++)
            wsum += wt*std::accumulate(ints_weight[ints_weight.size()-wt].begin(),
                                       ints_weight[ints_weight.size()-wt].end(), 0);

        return wsum;
    }
};

int main() {
    std::vector<NestedInteger> nested;
    // nested.push_back(NestedInteger(std::vector<NestedInteger>{1,1}));
    // nested.push_back(NestedInteger(2));
    // nested.push_back(NestedInteger(std::vector<NestedInteger>{1,1}));

    nested.push_back(NestedInteger(1));
    nested.push_back(NestedInteger(std::vector<NestedInteger>{4, std::vector<NestedInteger>{6}}));

    solution soln;
    int wsum = soln.depthSumInverse(nested);
    std::cout << "The inverse depth sum is:\n";
    std::cout << wsum << std::endl;
}
