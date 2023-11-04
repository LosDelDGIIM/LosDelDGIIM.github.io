#include <stdio.h>          // Para printf()
#include <stdlib.h>         // Para exit()
#include <sys/time.h>       // para gettimeofday(), struct timeval

int resultado = 0;

#ifndef TEST
#define TEST 5
#endif

/* -------------------------------------------------------------------- */
#if TEST==1
/* -------------------------------------------------------------------- */
#define SIZE 4
unsigned lista[SIZE]={0x80000000, 0x00400000, 0x00000200, 0x00000001};
#define RESULT 4

/* -------------------------------------------------------------------- */
#elif TEST==2
/* -------------------------------------------------------------------- */
#define SIZE 8
unsigned lista[SIZE]={  0x7fffffff, 0xffbfffff, 0xfffffdff, 0xfffffffe,
                        0x01000023, 0x00456700, 0x8900ab00, 0x00cd00ef};
#define RESULT 156

/* -------------------------------------------------------------------- */
#elif TEST==3
/* -------------------------------------------------------------------- */
#define SIZE 8
unsigned lista[SIZE]={  0x0,        0x01020408, 0x35906a0c, 0x70b0d0e0,
                        0xffffffff, 0x12345678, 0x9abcdef0, 0xdeadbeef};
#define RESULT 116

/* -------------------------------------------------------------------- */
#elif TEST==4 || TEST==0
/* -------------------------------------------------------------------- */
#define NBITS 20
#define SIZE (1<<NBITS)     // tamaño suficiente para tiempo apreciable
unsigned lista[SIZE];       // unsigned para desplazamiento derecha lógico
#define RESULT ( NBITS * ( 1 << NBITS-1 ) ) // Hay NBITS Columas, y cada columna tiene SIZE/2 1s.
/* -------------------------------------------------------------------- */
#else
#error "Definir TEST entre 0..4"
#endif
/* -------------------------------------------------------------------- */

// Función empleada para saber cuánto tarda cada versión del popcount
void crono(int (*func)(), char* msg){
    struct timeval tv1,tv2;     // gettimeofday() secs-usecs
    long tv_usecs;              // y sus cuentas
    
    gettimeofday(&tv1,NULL);
    resultado = func(lista, SIZE);
    gettimeofday(&tv2,NULL);

    
    tv_usecs=(tv2.tv_sec -tv1.tv_sec )*1e6+ (tv2.tv_usec-tv1.tv_usec);

    #if TEST==0
    printf("%ld" "\n", tv_usecs);
    
    #else
        printf("resultado = %d\t", resultado);
        printf("%s:%9ld us\n", msg, tv_usecs);
    #endif
}


// Lenguaje C - for
# define NUM_BITS 8*sizeof(unsigned)    // Multiplico por 8, ya que 1 byte tiene 8 bits.
int popcount1(unsigned* array, size_t len){

    int res=0;
    unsigned x;
    for (size_t i=0; i<len; ++i){
        
        x = array[i];

        for (int j=0; j<NUM_BITS; ++j){
            res += x & 1;   // Obtengo el LS bit cada vez
            x >>= 1;
        }
    }

    return res;
}

// Lenguaje C - while
int popcount2(unsigned* array, size_t len){

    int res=0;
    unsigned x;
    for (size_t i=0; i<len; ++i){
        
        x = array[i];

        // Al ser un while, cuando ya solo quedan 0 no sigo iterando
        while(x){
            res += x & 1;       // Obtengo el LS bit cada vez.
            x >>= 1;
        }
    }

    return res;
}

// leng.ASM-body while 4i
int popcount3(unsigned* array, size_t len){

    int res=0;
    unsigned x;
    for (size_t i=0; i<len; ++i){
        
        x = array[i];

        asm("\n"
    "ini3:                  \n\t"
    "   shr %[x]            \n\t"
    "   adc $0, %[r]        \n\t"
    "   test %[x], %[x]     \n\t"
    "   jne ini3            \n\t"
        : [r]"+r" (res)
        : [x] "r" (x)
        : "cc"
        );
    }

    return res;
}



// leng.ASM-body while 3i
int popcount4(unsigned* array, size_t len){

    int res=0;
    unsigned x;
    for (size_t i=0; i<len; ++i){
        
        x = array[i];

        asm("\n"
    "   clc                 \n\t"       // Set CF a 0 
    "ini4:                  \n\t"
    "   adc $0, %[r]        \n\t"
    "   shr %[x]            \n\t"
    "   jnz ini4            \n\t"
    "                       \n\t"
    "   adc $0, %[r]        \n\t"       // Cuando se quite el último bit 1, se saldrá del bucle. Pero ese 1 hay que sumarlo
        : [r]"+r" (res)
        : [x] "r" (x)
        : "cc"
        );
    }

    return res;
}


// CS:APP2e 3.49-group 8b
int popcount5(unsigned* array, size_t len){

    int res=0;
    unsigned x;
    for (size_t i=0; i<len; ++i){
        
        x = array[i];

        int val = 0;
        for (size_t i = 0; i < 8; i++) {
            /*
                En cada iteración, aplico esta máscara 0x01010101 para obtener los LSB de cada byte.
                Como desplazo un bit cada vez, itero sobre todo el byte.
                De esta forma, obtengo el popcount cada byte en su LSB. 
            */
            val += x & 0x01010101;
            x >>= 1;
        }

        /**
            Como son de 32 bits, tienen 4 bytes.
            Con el >>16, el popcount del 4º ( y 3º) LSB se lo sumo al del 2º ( y 1º) LSB.
                    De esta forma, En el 2º LSB tengo la suma del popcount del 2º y 4º
                                   En el 1º LSB tengo la suma del popcount del 1º y 3º

            Con el >>8, el valor del 2º LSB se lo sumo al del 1º LSB.
                    De esta forma, En el 1º LSB tengo la suma del popcount del
                    1º y 3º (ya los tenía) y del 2º y 4º (los acabo de añadir).
                
            De esta forma, en el LSB tengo el popcount total del número.
            Esta suma se dice en árbol, ya que vamos "uniendo las ramas".
        */
        val += (val >> 16);
        val += (val >> 8);
        
        // Aplico la máscara para obtener el LSB, y lo sumo al acumulado del array.
        res += val & 0xFF;
    }

    return res;
}


//types and constants used in the functions below
const unsigned long m1  = 0x5555555555555555; //binary: 0101...
const unsigned long m2  = 0x3333333333333333; //binary: 00110011..
const unsigned long m4  = 0x0f0f0f0f0f0f0f0f; //binary: 4 zeros, 4 ones ...
const unsigned long m8  = 0x00ff00ff00ff00ff; //binary: 8 zeros, 8 ones ...
const unsigned long m16 = 0x0000ffff0000ffff; //binary: 16 zeros, 16 ones ...
const unsigned long m32 = 0x00000000ffffffff; //binary: 32 zeros, 32 ones ...

// Wikipedia- naive - 32b
int popcount6(unsigned* array, size_t len){

    int res=0;
    unsigned x;
    for (size_t i=0; i<len; ++i){
        
        x = array[i];

        x = (x & m1 ) + ((x >> 1 ) & m1 ); //put count of each 2  bits into LSB of those 2
        x = (x & m2 ) + ((x >> 2 ) & m2 ); //put count of each 4  bits into LSB of those 4
        x = (x & m4 ) + ((x >> 4 ) & m4 ); //put count of each 8  bits into LSB of those 8
        x = (x & m8 ) + ((x >> 8 ) & m8 ); //put count of each 16 bits into LSB of those 16
        x = (x & m16) + ((x >> 16) & m16); //put count of each 32 bits into LSB of those 32 (POPCOUNT)
        
        res += x;
    }

    return res;
}


// Wikipedia- naive - 128b
int popcount7(unsigned* array, size_t len){

    int res=0;
    unsigned long x1, x2;

    // Si len no es múltiplo de 4, quedarán números sin leerse.
    if (len & 0x3) printf("leyendo bloques de 128b (4 unsigned) pero len no múltiplo de 4\n");

    for (size_t i=0; i<len; i+=4){
        
        // Hay unsigned (32 bits) pero quiero leer dos unsigned long (2*64).
        // Obtengo la dirección, la convierto en puntero a unsigned long, y ya obtengo el unsigned long.
        x1 = *(unsigned long *) &array[i];
        x2 = *(unsigned long *) &array[i+2];

        x1 = (x1 & m1 ) + ((x1 >> 1 ) & m1 ); //put count of each 2  bits into LSB of those 2
        x1 = (x1 & m2 ) + ((x1 >> 2 ) & m2 ); //put count of each 4  bits into LSB of those 4
        x1 = (x1 & m4 ) + ((x1 >> 4 ) & m4 ); //put count of each 8  bits into LSB of those 8
        x1 = (x1 & m8 ) + ((x1 >> 8 ) & m8 ); //put count of each 16 bits into LSB of those 16
        x1 = (x1 & m16) + ((x1 >> 16) & m16); //put count of each 32 bits into LSB of those 32
        x1 = (x1 & m32) + ((x1 >> 32) & m32); //put count of each 64 bits into LSB of those 64 (POPCOUNT)

        x2 = (x2 & m1 ) + ((x2 >> 1 ) & m1 );
        x2 = (x2 & m2 ) + ((x2 >> 2 ) & m2 );
        x2 = (x2 & m4 ) + ((x2 >> 4 ) & m4 );
        x2 = (x2 & m8 ) + ((x2 >> 8 ) & m8 );
        x2 = (x2 & m16) + ((x2 >> 16) & m16);
        x2 = (x2 & m32) + ((x2 >> 32) & m32);
        
        res += x1 + x2;
    }

    return res;
}






int main(){
    #if TEST==0 || TEST==4 // inicializar array
        size_t i;
        for (i=0; i<SIZE; i++)
        lista[i]=i;
    #endif

    
    crono(popcount1 , "popcount1 (lenguaje C -for)       ");
    crono(popcount2 , "popcount2 (lenguaje C -while)     ");
    crono(popcount3 , "popcount3 (leng.ASM-body while 4i)");
    crono(popcount4 , "popcount4 (leng.ASM-body while 3i)");
    crono(popcount5 , "popcount5 (CS:APP2e 3.49-group 8b)");
    crono(popcount6 , "popcount6 (Wikipedia- naive - 32b)");
    crono(popcount7 , "popcount7 (Wikipedia- naive -128b)");/*
    crono(popcount8 , "popcount8 (asm SSE3 - pshufb 128b)");
    crono(popcount9 , "popcount9 (asm SSE4- popcount 32b)");
    crono(popcount10, "popcount10(asm SSE4- popcount128b)");
    */

    #if TEST != 0
    printf("calculado = %d\n", RESULT);
    #endif

    exit(0);
}