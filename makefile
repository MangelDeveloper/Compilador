# Archivos y variables
EXEC = ejecutable_miniC
LEX_FILE = ./miniC/miniC.l
YACC_FILE = ./miniC/miniC.y
#Variables de archivos.o
LEXYY_OBJ = ./miniC/lex.yy.o
MINIC_TAB_OBJ = ./miniC/miniC.tab.o
TSIMBOLOS_OBJ = ./TablaSimbolos/tabla_simbolos.o
LCODIGO_OBJ = ./GeneracionCodigo/listaCodigo.o
GEN_CODIGO_OBJ = ./GeneracionCodigo/generacion_codigo.o
STACK_OBJ = ./Utils/stack.o
STACK_INT_OBJ = ./Utils/stack_int.o
STACK_TSIMBOLOS_OBJ = ./Utils/stack_tabla_simbolos.o
THASH_OBJ = ./Utils/tabla_hash.o
FLEX_UTILS_OBJ = ./Utils/flex_utils.o
INPUT_FILE = Ejemplos\Prueba\entrada.mc
#INPUT_FILE = ./Ejemplos/Recursividad/Fibonacci/entrada.mc
#INPUT_FILE = ./Ejemplos/Recursividad/Factorial/entrada.mc

OBJ = main.o \
    $(LEXYY_OBJ) \
    $(MINIC_TAB_OBJ) \
    $(TSIMBOLOS_OBJ) \
    $(LCODIGO_OBJ) \
    $(GEN_CODIGO_OBJ) \
    $(FLEX_UTILS_OBJ) \
    $(THASH_OBJ) \
    $(STACK_OBJ) \
    $(STACK_INT_OBJ) \
    $(STACK_TSIMBOLOS_OBJ)

ifeq ($(OS),Windows_NT)
    BISON = win_bison
    FLEX = win_flex
    RM = del /Q
    LIBS =
    RUN = $(EXEC).exe
    RUN_GDB = gdb --args $(EXEC).exe
    CLEAN = if exist "main.o" del /Q "main.o" & \
            if exist "miniC\miniC.tab.o" del /Q "miniC\miniC.tab.o" & \
            if exist "miniC\lex.yy.o" del /Q "miniC\lex.yy.o" & \
            if exist "miniC\miniC.tab.c" del /Q "miniC\miniC.tab.c" & \
            if exist "miniC\miniC.tab.h" del /Q "miniC\miniC.tab.h" & \
            if exist "miniC\lex.yy.c" del /Q "miniC\lex.yy.c" & \
            if exist "TablaSimbolos\tabla_simbolos.o" del /Q "TablaSimbolos\tabla_simbolos.o" & \
            if exist "GeneracionCodigo\listaCodigo.o" del /Q "GeneracionCodigo\listaCodigo.o" & \
            if exist "GeneracionCodigo\generacion_codigo.o" del /Q "GeneracionCodigo\generacion_codigo.o" & \
            if exist "Utils\stack.o" del /Q "Utils\stack.o" & \
            if exist "Utils\stack_int.o" del /Q "Utils\stack_int.o" & \
            if exist "Utils\stack_tabla_simbolos.o" del /Q "Utils\stack_tabla_simbolos.o" & \
            if exist "Utils\tabla_hash.o" del /Q "Utils\tabla_hash.o" & \
            if exist "Utils\flex_utils.o" del /Q "Utils\flex_utils.o"
else
    BISON = bison
    FLEX = flex
    RM = rm -f
    LIBS = -lfl
    RUN = ./$(EXEC)
    RUN_GDB = gdb --args ./$(EXEC)
	CLEAN = rm -f $(EXEC) $(OBJ) ./miniC/miniC.tab.* ./miniC/lex.yy.c
endif

# Regla por defecto
all: $(EXEC)

# Regla para compilar el ejecutable
$(EXEC): $(OBJ)
	@gcc $(OBJ) $(LIBS) -g -o $(EXEC)

# Reglas de compilación de objetos
main.o: main.c
	@gcc -c main.c -g -o main.o

# Reglas para generar archivos de Bison y Flex
./miniC/miniC.tab.c ./miniC/miniC.tab.h: $(YACC_FILE)
	@$(BISON) -d -v -o ./miniC/miniC.tab.c $(YACC_FILE)

# Compilación de los archivos cabecera generados por bison
./miniC/miniC.tab.o: ./miniC/miniC.tab.c ./miniC/miniC.tab.h
	@gcc -c ./miniC/miniC.tab.c -g -o ./miniC/miniC.tab.o

# Compilación de lex.yy.o
./miniC/lex.yy.o: ./miniC/lex.yy.c ./miniC/miniC.tab.h
	@gcc -c ./miniC/lex.yy.c -g -o ./miniC/lex.yy.o

# Compilación del archivo lex.yy.c
./miniC/lex.yy.c: ./miniC/miniC.l ./miniC/miniC.tab.h
	@$(FLEX) -o ./miniC/lex.yy.c ./miniC/miniC.l

# Compilación de la tabla de símbolos
./TablaSimbolos/tabla_simbolos.o: ./TablaSimbolos/tabla_simbolos.c ./TablaSimbolos/tabla_simbolos.h
	@gcc -c ./TablaSimbolos/tabla_simbolos.c -g -o ./TablaSimbolos/tabla_simbolos.o

#Generación de la lista de código
./GeneracionCodigo/listaCodigo.o: ./GeneracionCodigo/listaCodigo.c ./GeneracionCodigo/listaCodigo.h
	@gcc -c ./GeneracionCodigo/listaCodigo.c -g -o ./GeneracionCodigo/listaCodigo.o

# Compilación de la generación de código en ensamblador
./GeneracionCodigo/generacion_codigo.o: ./GeneracionCodigo/generacion_codigo.c ./GeneracionCodigo/generacion_codigo.h
	@gcc -c ./GeneracionCodigo/generacion_codigo.c -g -o ./GeneracionCodigo/generacion_codigo.o

# Compilación de la generación de la estructura de datos Stack (Pila)
./Utils/stack.o: ./Utils/stack.c ./Utils/stack.h
	@gcc -c ./Utils/stack.c -g -o ./Utils/stack.o

# Compilación de la lista de símbolos
./Utils/tabla_hash.o: ./Utils/tabla_hash.c ./Utils/tabla_hash.h
	@gcc -c ./Utils/tabla_hash.c -g -o ./Utils/tabla_hash.o

./Utils/stack_int.o: ./Utils/stack_int.c ./Utils/stack_int.h
	@gcc -c ./Utils/stack_int.c -g -o ./Utils/stack_int.o

# Compilación de la lista de símbolos
./Utils/stack_tabla_simbolos.o: ./Utils/stack_tabla_simbolos.c ./Utils/stack_tabla_simbolos.h
	@gcc -c ./Utils/stack_tabla_simbolos.c -g -o ./Utils/stack_tabla_simbolos.o

# Compilación de los métodos auxiliares
./Utils/flex_utils.o: ./Utils/flex_utils.c
	@gcc -c ./Utils/flex_utils.c -g -o ./Utils/flex_utils.o

# Limpiar archivos generados
clean:
	@$(CLEAN)

#Si estamos en Windows
ifeq ($(OS),Windows_NT)
# Ejecutar normalmente
run: $(EXEC) $(INPUT_FILE)
	@chcp 65001 > nul && $(RUN) $(INPUT_FILE)

# Limpiar y ejecutar
refresh: clean all
	@chcp 65001 > nul
	@$(RUN) $(INPUT_FILE)

# Ejecutar con GDB
test: $(EXEC) $(INPUT_FILE)
	@chcp 65001 > nul && $(RUN_GDB) $(INPUT_FILE)

else
run: $(EXEC) $(INPUT_FILE)
	$(RUN) $(INPUT_FILE)

# Limpiar y ejecutar
refresh: clean all run

# Ejecutar con GDB
test: $(EXEC) $(INPUT_FILE)
	$(RUN_GDB) $(INPUT_FILE)
endif