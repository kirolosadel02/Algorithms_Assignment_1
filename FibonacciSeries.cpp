#include <iostream>
#include <vector>
using namespace std;
vector<long long> memory;

unsigned long long recursive_fib(int n){
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;
    return recursive_fib(n-1) + recursive_fib(n-2);
}
///////////////////////////////////////////////////////////////////////////////////////////////

unsigned long long DPfib(long long n) {//O(n)
    if(n == 0)
        return 0;
    if(n == 1)
        return 1;

    if (memory[n] != -1)
        return memory[n];

    return memory[n] = DPfib(n - 1) + DPfib(n - 2);
}

///////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<long long>> multiply(const vector<vector<long long>>& a, const vector<vector<long long>>& b) {
    vector<vector<long long>> result(2, vector<long long>(2));
    result[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
    result[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
    result[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
    result[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
    return result;
}


vector<vector<long long>> matrixPower(vector<vector<long long>> base, int n) {
    vector<vector<long long>> result = {{1, 0}, {0, 1}};

    while (n > 0) {
        if (n % 2 == 1)
            result = multiply(result, base);
        base = multiply(base, base);
        n /= 2;
    }
    return result;
}

unsigned long long MatrixMultiplicationFibonacci(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    vector<vector<long long>> base = {{1, 1}, {1, 0}};
    vector<vector<long long>> result = matrixPower(base, n - 1);
    return result[0][0];
}

int main(){
    int n=8000;
    memory.resize(n+1);
    fill(memory.begin(), memory.end(), -1);
    unsigned long long recFibResult = recursive_fib(6);
    unsigned long long DPFibResult = DPfib(n);
    unsigned long long MatrixMultiplicationFibResult = MatrixMultiplicationFibonacci(n);
    cout << "Recursive Fibonacci result : " << recFibResult<<'\n';
    cout << "Dynamic Programming Fibonacci result : " << DPFibResult << '\n';
    cout << "Matrix Multiplication Fibonacci result : "<< MatrixMultiplicationFibResult<<'\n';
    
}