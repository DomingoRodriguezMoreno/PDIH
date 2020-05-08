#include <stdio.h>
#include <dos.h>

void mi_pausa(){
    union REGS inregs, outregs;
	inregs.h.ah = 8;
	int86(0x21, &inregs, &outregs);
}

void mi_cputchar(char c){
    union REGS inregs, outregs;

    inregs.h.ah = 9;
    inregs.h.al = (int) c;
    inregs.h.bh = 0;
    inregs.x.cx = 1;

    int86(0x10, &inregs, &outregs);

}

int mi_getchar() {
	 union REGS inregs, outregs;
	 int caracter;

	 inregs.h.ah = 1;
	 int86(0x21, &inregs, &outregs);

	 caracter = outregs.h.al;
	 return caracter;
}

int main(){
    union REGS inregs, outregs;
    int tmp;

    //Leer un caracter por teclado
    printf("\nPulsa una tecla:  ");
	tmp = mi_getchar();

    //Mostrar el caracter por pantalla
	printf("\nHas pulsado: ");
    mi_cputchar( (char)tmp );
    mi_pausa();
    return 0;
}
