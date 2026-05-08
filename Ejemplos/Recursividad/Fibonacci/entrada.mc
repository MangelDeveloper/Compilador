int fibo(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    return fibo(n-1)+fibo(n-2);
}

void main(){
    //fibo 8 = 21 -> fibo_n = 21;
    var int fibo_n = fibo(8);
    print("fibonacci de 8 es: ", fibo_n,"\n");
}