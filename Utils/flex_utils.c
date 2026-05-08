//yywrap es una función que Flex llama automáticamente cuando el lexer llega al final de la entrada (EOF).
//En Linux, cuando linkeas con -lfl (gcc ... -lfl), la librería libfl ya incluye una implementación de yywrap() que retorna 1.
//En Windows, con win_flex, no existe libfl, así que el linker no encuentra yywrap → te da el error undefined reference to 'yywrap'.
//Eso quiere decir, que si quieres trabajar desde Windows necesitas este archivo.
int yywrap(void) {
    return 1;
}