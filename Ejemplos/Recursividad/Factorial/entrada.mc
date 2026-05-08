int factorial(int n){
    if(n == 0) return 1;
    return n*factorial(n-1);
}

void main(){
    //factorial 5 = 120;
    var int fact_n = factorial(5);
    print("factorial de 5 es: ", fact_n,"\n");
}