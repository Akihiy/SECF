//#include <stdio.h>  // ������׼��������⣬�Ա�ʹ��printf��scanf������
//
//int max(int a, int b) {  // ����һ������max�����ڷ������������еĽϴ�ֵ��
//    return (a > b) ? a : b;
//}
//
//int knapsack(int m, int n, int weights[], int values[]) {  // ����һ������knapsack�����ڽ��0/1�������⡣
//    int dp[n + 1][m + 1];  // ����һ����ά����dp�����ڴ洢�м��������
//
//    for (int i = 0; i <= n; i++) {  // ѭ��������Ʒ������
//        for (int j = 0; j <= m; j++) {  // ѭ����������������
//            if (i == 0 || j == 0) {  // �����Ʒ����Ϊ0�򱳰�����Ϊ0��������ܼ�ֵΪ0��
//                dp[i][j] = 0;
//            } else if (weights[i - 1] <= j) {  // �����ǰ��Ʒ������С�ڵ��ڱ���������
//                dp[i][j] = max(dp[i - 1][j], dp[i][j - weights[i - 1]] + values[i - 1]);
//                // ����ѡ��ǰ��Ʒ�Ͳ�ѡ��ǰ��Ʒ����������е�����ܼ�ֵ��
//            } else {  // �����ǰ��Ʒ���������ڱ������������޷����뱳����
//                dp[i][j] = dp[i - 1][j];  // ����ܼ�ֵ�벻ѡ��ǰ��Ʒ�������ͬ��
//            }
//        }
//    }
//
//    return dp[n][m];  // �������ռ���õ�������ܼ�ֵ��
//}
//
//int main() {  // ������
//    int m, n;
//    scanf("%d %d", &m, &n);  // �ӱ�׼�����ȡ��������m����Ʒ����n��
//
//    int weights[n];  // ����һ���������洢��Ʒ��������
//    int values[n];   // ����һ���������洢��Ʒ�ļ�ֵ��
//
//    for (int i = 0; i < n; i++) {  // ѭ����ȡÿ����Ʒ�������ͼ�ֵ��
//        scanf("%d %d", &weights[i], &values[i]);
//    }
//
//    int result = knapsack(m, n, weights, values);  // ����knapsack��������������ܼ�ֵ��
//    printf("max=%d\n", result);  // ��ӡ����ܼ�ֵ����׼�����
//
//    return 0;  // ����0��ʾ��������������
//}

#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int M, n;
    std::cin >> M >> n;

    std::vector<int> m(n + 1);  // ��Ʒ��������
    std::vector<int> v(n + 1);  // ��Ʒ��ֵ����

    for (int i = 1; i <= n; i++) {
        std::cin >> m[i] >> v[i];
    }

    std::vector<int> f(M + 1, 0);  // �Ż��������f
    std::unordered_map<int, std::vector<int>> path;  // �Ż���Ĺ�ϣ��path

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

    // ������
    std::vector<int> x(n + 1, 0);
    for (int item : path[M]) {
        x[item]++;
    }

    // ������
    std::cout << "max=" << f[M] << std::endl;
    std::cout << "x vector: ";
    for (int i = 1; i <= n; i++) {
        std::cout << x[i] << " ";
    }

    return 0;
}









