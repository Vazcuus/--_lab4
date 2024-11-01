unsigned long long factorial(int n) {
    if (n < 0) {
        throw "Negative numbers do not have factorials.";
    }
    
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}