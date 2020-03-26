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

void mi_gotoxy(int x, int y){
    union REGS inregs, outregs;

    inregs.h.ah = 2;
    inregs.h.dh = x;
    inregs.h.dl = y;
    inregs.h.bh = 0;

    int86(0x10, &inregs, &outregs);
}

void mi_setcursortype(int tipo_cursor){
    union REGS inregs, outregs;
    inregs.h.ah = 0x01;

    switch(tipo_cursor){
        case 0: //invisible
            inregs.h.ch = 010;
            inregs.h.cl = 000;
        break;
        case 1: //normal
            inregs.h.ch = 010;
            inregs.h.cl = 010;
        break;
        case 2: //grueso
            inregs.h.ch = 000;
            inregs.h.cl = 010;
        break;
    }

    int86(0x10, &inregs, &outregs);
}

void mi_setvideomode(BYTE modo){
    union REGS inregs, outregs;

    inregs.h.ah = 0x00;
    inregs.h.al = modo;

    int86(0x10, &inregs, &outregs);
}

int mi_getvideomode(){
    union REGS inregs, outregs;
    int video;

    inregs.h.ah = 0xF;

    int86(0x10, &inregs, &outregs);

    video = outregs.h.al;
    
    return video;
}

void mi_textcolor(int c){
    colorTexto = c;
}

void mi_textbackground(int c){
    colorFondo = c;
}

void mi_clrscr(){
    union REGS inregs, outregs;

    inregs.h.ah = 6;
    inregs.h.al = 0;
    inregs.h.bh = 0;
    inregs.h.ch = 0;
    inregs.h.cl = 0;
    inregs.h.dh = 100;
    inregs.h.dl = 100;

    int86(0x10, &inregs, &outregs);
}

void mi_cputchar(char c){
    union REGS inregs, outregs;

    inregs.h.ah = 9;
    inregs.h.al = (int) c;
    inregs.h.bl = colorTexto + (colorFondo << 4);
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
    int tmp;

    //Leer un caracter por teclado mostrandolo
	printf("\nPulsa una tecla:  ");
	tmp = mi_getchar();

    //Mostrar un caracter por pantalla cambiando el color (Rojo)
	printf("\nHas pulsado: ");
    mi_cputchar( (char)tmp );
    
    //Cambiar el aspecto del cursor
	printf("\nCursor invisible: ");
   	mi_setcursortype(0);
   	mi_pausa();
   	printf("\nCursor grueso: ");
   	mi_setcursortype(2);
   	mi_pausa();
   	printf("\nCursor normal: ");
   	mi_setcursortype(1);
   	mi_pausa();

    
    //Cambiar el modo de video
    mi_setvideomode(MODOGRAFICO);
    printf("\nModo grafico: ");
    mi_pausa();

    mi_setvideomode(MODOTEXTO);
    printf("\nModo Texto: ");
    mi_pausa();
    

    //obtener modo video actual
    tmp = mi_getvideomode();
    printf("\nModo videoactual: %i", tmp);
    mi_pausa();

    //Cambiar color de texto y fondo
    mi_textcolor(1);
    mi_textbackground(4);
    printf("\nColor de texto y fondo cambiados: ");
    mi_cputchar( (char)'H' );
    mi_pausa();

    //Limpiar terminal
    mi_clrscr();
    mi_pausa();

    return 0;
}
