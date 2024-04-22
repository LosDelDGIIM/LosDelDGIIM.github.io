typedef struct{
    unsigned int slock;
} raw_spinlock_t;

// Para un numero de procesadores mayor que 256=2^8
#if (NR_CPUS < 256)

static __always_inline void __ticket_spin_lock(raw_spinlock_t *lock){
    short inc = 0x0100;

    asm volatile (
        "lock xaddw %w0,%1\n"   /*w: se queda con los dos ultimos LSB.*/
        "1:             \t"     /*b: se queda con el LSB*/
        "cmpb %h0, %b0  \n\t"   /*h: se queda con el segundo LSB*/
        "je 2f          \n\t"   /*f: forward */
        "rep ; nop      \n\t"   /*retardo, es equivalente a pause*/
        "movb %1, %b0   \n\t"
        /* don't need lfence here, because loads are in-order */
        "jmp 1b         \n"     /*b: backward */
        "2:"
        : "+Q" (inc), "+m" (lock->slock) /*%0 es inc, %1 es lock->slock */
        /*Q asigna cualquier registro al que se pueda acceder con rh: a, b, c y d; ej. ah, bh ... */
        :
        : "memory", "cc");
}

static __always_inline void __ticket_spin_unlock(raw_spinlock_t *lock){
    asm volatile( "incb %0"         /*%0 es lock->slock */
        : "+m" (lock->slock)
        :
        : "memory", "cc");
}

// ...
#endif