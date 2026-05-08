var int global = 400;

int compiladores(int global){
    return global;
}

void main() {
    print("El valor devuelto de la función compiladores es: ", compiladores(10), "\n");
    print("El valor de global es: ", global, "\n");
}