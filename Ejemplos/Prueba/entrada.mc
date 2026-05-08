var int global = 400;

void patata(int a, int b){
    print("El valor del parámetro a ", a);
    print("\n");
    print("El valor del parámetro b ", b);
    print("\n");
}

int compiladores(){
    return 3;
}

void main() {
    var int a = 5, b = 0;
    var int c = 5;
    
    while (a) {
        var int c = 3;
        print("c = ",c,"\n");
        a = a-1;
    }

    print("El valor de a es: ",a,"\n");
    print("El valor de c es: ",c,"\n");
    print("El valor de global es: ", global, "\n");
}