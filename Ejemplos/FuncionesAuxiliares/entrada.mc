void patata(int a, int b){
    print("He entrado a la función patata\n", "El valor del parámetro es ", a+b, "\n");
}

int compiladores(){
    return 4;
}

void main() {
    const int a = 0, b = 0;
    print ("Inicio del programa\n");
    var int c = 5+2-2;
    if (a) print ("a","\n");
    else if (b) print ("No a y b\n");
    else while (c) {
        var int a = 0;
        var int d = 4+3*5;
        print("c = ",c,"\n");
        c = c-2+1;
        print(d+1,"\n");
    }
    var int ab = 7;
    patata(ab,3+10);
    var int resultado = compiladores();
    print("Valor de resultado ", resultado, "\n");
    print("Valor de la función compiladores(): " , compiladores());
    print ("Final","\n");
}