#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int Mod = 99991;
int n, tot;
int head[100005], nxt[100005], snow[100005][6];

int Hash(int *a) {
    int sum = 0, mul = 1;
    for (int i = 0; i < 6; i++) {
        sum = (sum + a[i]) % Mod;
        mul = (long long)mul * a[i] % Mod;
    }
    return (sum + mul) % Mod;
}

bool Equal(int *a, int *b) {
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            bool eq = 1;
            for (int k = 0; k < 6; k++)
                if (a[(i + k) % 6] != b[(j + k) % 6])
                    eq = 0;
            if (eq)
                return true;
            eq = 1;
            for (int k = 0; k < 6; k++)
                if(a[(i + k) % 6] != b[(j - k + 6) % 6])
                    eq = 0;
            if (eq)
                return true;
        }
    return false;
}

bool insert(int *a) {
    int val = Hash(a);
    for (int i = head[val]; i; i = nxt[i])
        if (Equal(snow[i], a))
            return true;
    ++tot;
    memcpy(snow[tot], a, 6 * sizeof(int));
    nxt[tot] = head[val];
    head[val] = tot;
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a[8];
        for (int j = 0; j < 6; j++)
            scanf("%d", &a[j]);
        if(insert(a)) {
            printf("Twin snowflakes found.");
            return 0;
        }
    }
    printf("No two snowflakes are alike.");
    return 0; 
}