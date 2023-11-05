//#include <stdio.h>  // 包含标准输入输出库，以便使用printf和scanf函数。
//
//int max(int a, int b) {  // 定义一个函数max，用于返回两个整数中的较大值。
//    return (a > b) ? a : b;
//}
//
//int knapsack(int m, int n, int weights[], int values[]) {  // 定义一个函数knapsack，用于解决0/1背包问题。
//    int dp[n + 1][m + 1];  // 创建一个二维数组dp，用于存储中间计算结果。
//
//    for (int i = 0; i <= n; i++) {  // 循环遍历物品数量。
//        for (int j = 0; j <= m; j++) {  // 循环遍历背包容量。
//            if (i == 0 || j == 0) {  // 如果物品数量为0或背包容量为0，则最大总价值为0。
//                dp[i][j] = 0;
//            } else if (weights[i - 1] <= j) {  // 如果当前物品的重量小于等于背包容量。
//                dp[i][j] = max(dp[i - 1][j], dp[i][j - weights[i - 1]] + values[i - 1]);
//                // 计算选择当前物品和不选择当前物品的两种情况中的最大总价值。
//            } else {  // 如果当前物品的重量大于背包容量，则无法放入背包。
//                dp[i][j] = dp[i - 1][j];  // 最大总价值与不选择当前物品的情况相同。
//            }
//        }
//    }
//
//    return dp[n][m];  // 返回最终计算得到的最大总价值。
//}
//
//int main() {  // 主函数
//    int m, n;
//    scanf("%d %d", &m, &n);  // 从标准输入读取背包容量m和物品数量n。
//
//    int weights[n];  // 创建一个数组来存储物品的重量。
//    int values[n];   // 创建一个数组来存储物品的价值。
//
//    for (int i = 0; i < n; i++) {  // 循环读取每个物品的重量和价值。
//        scanf("%d %d", &weights[i], &values[i]);
//    }
//
//    int result = knapsack(m, n, weights, values);  // 调用knapsack函数，计算最大总价值。
//    printf("max=%d\n", result);  // 打印最大总价值到标准输出。
//
//    return 0;  // 返回0表示程序正常结束。
//}

#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int M, n;
    std::cin >> M >> n;

    std::vector<int> m(n + 1);  // 物品重量数组
    std::vector<int> v(n + 1);  // 物品价值数组

    for (int i = 1; i <= n; i++) {
        std::cin >> m[i] >> v[i];
    }

    std::vector<int> f(M + 1, 0);  // 优化后的向量f
    std::unordered_map<int, std::vector<int>> path;  // 优化后的哈希表path

    for (int i = 1; i <= n; i++) {
        for (int j = m[i]; j <= M; j++) {
            int tmp = f[j - m[i]] + v[i];
            if (f[j] < tmp) {
                f[j] = tmp;
                path[j] = path[j - m[i]];
                path[j].push_back(i);
            }
        }
    }

    // 解向量
    std::vector<int> x(n + 1, 0);
    for (int item : path[M]) {
        x[item]++;
    }

    // 输出结果
    std::cout << "max=" << f[M] << std::endl;
    std::cout << "x vector: ";
    for (int i = 1; i <= n; i++) {
        std::cout << x[i] << " ";
    }

    return 0;
}









