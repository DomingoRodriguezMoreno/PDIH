#include <stdio.h>
#include <dos.h>

#define BYTE unsigned char

BYTE MODOTEXTO = 3;
BYTE MODOGRAFICO = 4;
int colorTexto = 15;
int colorFondo = 0;

void mi_pausa(){
    union REGS inregs, outregs;
	inregs.h.ah = 8;
	int86(0x21, &inregs, &outregs);
}

void mi_setvideomode(BYTE modo){
    union REGS inregs, outregs;

    inregs.h.ah = 0x00;
    inregs.h.al = modo;

    int86(0x10, &inregs, &outregs);
}

int main(){
    //Cambiar el modo de video
    mi_setvideomode(MODOGRAFICO);
    printf("\nModo grafico: ");
    mi_pausa();

    mi_setvideomode(MODOTEXTO);
    printf("\nModo Texto: ");
    mi_pausa();

    return 0;
}
