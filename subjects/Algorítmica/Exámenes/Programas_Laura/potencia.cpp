double potencia(double x, int n){
    if(n == 0) return 1;
    int y = potencia(x,n/2);
    y = y * y;
    if(n % 2) // n impar
        y *= x;
    return y;
}