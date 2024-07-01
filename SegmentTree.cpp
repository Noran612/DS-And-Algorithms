#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;

    void build(vector<int>& nums, int treeIndex, int lo, int hi) {
        if (lo == hi) {
            tree[treeIndex] = nums[lo];
            return;
        }
        int mid = lo + (hi - lo) / 2;
        build(nums, 2 * treeIndex + 1, lo, mid);
        build(nums, 2 * treeIndex + 2, mid + 1, hi);
        tree[treeIndex] = tree[2 * treeIndex + 1] + tree[2 * treeIndex + 2];
    }

    int query(int treeIndex, int lo, int hi, int i, int j) {
        if (lo > j || hi < i) return 0;
        if (i <= lo && hi <= j) return tree[treeIndex];
        int mid = lo + (hi - lo) / 2;
        return query(2 * treeIndex + 1, lo, mid, i, j) + query(2 * treeIndex + 2, mid + 1, hi, i, j);
    }

    void update(int treeIndex, int lo, int hi, int idx, int val) {
        if (lo == hi) {
            tree[treeIndex] = val;
            return;
        }
        int mid = lo + (hi - lo) / 2;
        if (idx <= mid) update(2 * treeIndex + 1, lo, mid, idx, val);
        else update(2 * treeIndex + 2, mid + 1, hi, idx, val);
        tree[treeIndex] = tree[2 * treeIndex + 1] + tree[2 * treeIndex + 2];
    }

public:
    SegmentTree(vector<int>& nums) {
        if (nums.size() > 0) {
            n = nums.size();
            tree.resize(4 * n);
            build(nums, 0, 0, n - 1);
        }
    }

    int query(int i, int j) {
        return query(0, 0, n - 1, i, j);
    }

    void update(int idx, int val) {
        update(0, 0, n - 1, idx, val);
    }
};

int main() {
    vector<int> nums = {1, 3, 5, 7, 9, 11};
    SegmentTree segTree(nums);
    
    cout << segTree.query(1, 3) << endl; // 15
    segTree.update(1, 10);
    cout << segTree.query(1, 3) << endl; // 22

    return 0;
}
