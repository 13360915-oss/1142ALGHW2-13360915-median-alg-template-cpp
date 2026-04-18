#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// 用來同時儲存數值與權重
struct Item {
    int x;
    double w;
};

// 印出排序後資料
void printSortedValues(const vector<Item>& items) {
    cout << "Sorted data (x, w):\n";
    for (const auto& item : items) {
        cout << "(" << item.x << ", " << fixed << setprecision(2) << item.w << ") ";
    }
    cout << "\n";
}

// ------------------------------
// 1. 求中位數
// ------------------------------
double findMedian(vector<int> values) {
    // 1. 排序
    sort(values.begin(), values.end());

    // 2. 取得資料筆數
    int n = values.size();

    // 3. 若 n 為奇數
    if (n % 2 == 1) {
        return values[n / 2];
    }
    // 4. 若 n 為偶數
    else {
        return (values[n / 2 - 1] + values[n / 2]) / 2.0;
    }
}

// ------------------------------
// 2. 求加權中位數
// ------------------------------
int findWeightedMedian(vector<Item> items) {
    // 1. 依照 x 排序
    sort(items.begin(), items.end(), [](Item a, Item b) {
        return a.x < b.x;
    });

    // 2. 印出排序結果
    printSortedValues(items);

    // 3. 初始化累積權重
    double cumulativeWeight = 0.0;

    cout << "\nProcess:\n";

    // 4. 逐一走訪
    for (const auto& item : items) {
        cumulativeWeight += item.w;

        cout << "x = " << item.x
             << ", w = " << fixed << setprecision(2) << item.w
             << ", cumulative = " << cumulativeWeight << "\n";

        // 若累積權重 >= 0.5
        if (cumulativeWeight >= 0.5) {
            return item.x;
        }
    }

    // 5. 若沒找到
    return -1;
}

int main() {
    // 題目資料
    vector<int> x = {4, 3, 8, 5, 7, 10, 0, 9, 2, 11};
    vector<double> w = {0.05, 0.12, 0.08, 0.15, 0.14, 0.09, 0.10, 0.10, 0.06, 0.11};

    // 組合成 (x, w)
    vector<Item> items;
    for (int i = 0; i < x.size(); i++) {
        items.push_back({x[i], w[i]});
    }

    cout << "Original x values:\n";
    for (int v : x) cout << v << " ";
    cout << "\n\n";

    // 計算中位數
    double median = findMedian(x);
    cout << "Median = " << fixed << setprecision(1) << median << "\n\n";

    // 計算加權中位數
    int weightedMedian = findWeightedMedian(items);
    cout << "\nWeighted Median = " << weightedMedian << "\n";

    return 0;
}
