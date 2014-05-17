#include <AT89X52.H>
#define	D4	P2_0
#define D5	P2_1
#define	D6	P2_2
#define	D7	P2_3
#define	RW	P2_4
#define	RS	P2_5
#define	ENA	P2_6
#define OK	P2_7
#define LCD_PORT	P2
#define LCD_UNOS	0x3f	//xx11 1111
#define LCD_BOOT_ALTA	193	//retardo de 16ms
#define LCD_BOOT_BAJA 38 //138
#define LCD_DELAY_1_ALTA 236//retardo de 5ms
#define LCD_DELAY_1_BAJA 0 // 100
#define LCD_DELAY_2_ALTA 255//retardo de 114us
#define LCD_DELAY_2_BAJA 56 //156
#define DELAY_ESCRITURA_ALTA 255//retardo de 45us
#define DELAY_ESCRITURA_BAJA 211
#define BORRAR_LCD_ALTA	177	//retardo de 20ms
#define BORRAR_LCD_BAJA 124  // 224
#define DELAY_VISUALIZACION_ALTA 0//delay de 65536us
#define DELAY_VISUALIZACION_BAJA 0
#define NIBBLE_MASK 0x0F
#define POSICION_LCD_MASK 0x80	//1000  0000
#define LCD_RS	0x20  //xx1x xxxx
#define LCD_RW  0x10  //xxx1 xxxx
#define LCD_MODO_4BITS 0x28	//001(DL) (N)0xx  DL:Data Length( 1:8bit 0:4bit) N:Dual Line(1:Dual Line 0:Single Line) VER SEGUN DISPLAY COMPRADO
#define LCD_MODO_DESPLAZAMIENTO 0x06//incrementar contador de direccion automaticamente y el display quieto
#define LCD_PRENDIDO_Y_CURSOR 0x0E// DISPLAY ON CURSOR OFF
#define LCD_OFF 0x08// apagar el display



extern void HABILITAR_DATOS();
extern void LCD_OCUPADO();

// P2.0=D4  P2.1=D5  P2.2=D6   P2.3=D7   P2.4=RW   P2.5=RS   P2.6=ENA 
//sobra el puerto P2.3
//	| or inclusivo (es uno si alguno de los dos es uno sino devuelve 0)		 x|= y --> x = x | y 
//	& AND (devuelve un uno solo si los dos son uno)		x &= y -->		x = x & y
// ~ complemento


void ESCRIBIR_VIBRATOMO();
void DISPLAY_ON();
void DISPLAY_OFF();
void INICIALIZACION_DISPLAY();
void DELAY_MS(unsigned char ALTA, unsigned char BAJA);
void ESCRIBIR_NIBBLE(unsigned char nibble);
void ESCRIBIR_BYTE_LCD(unsigned char c);
void LCD_COMANDO( unsigned char c );
void ESCRIBIR_VECTOR( char * string, unsigned char posicion);
void POSICION_LCD(unsigned char posicion);
void DELAY_2SEG();
void ESCRIBIR_DISPLAY( unsigned char c );
void BORRAR_LCD( void );


void main()
{
	INICIALIZACION_DISPLAY();
	ESCRIBIR_VECTOR("VIBRATOMO",4); //fijarce que no puede ser mayor a 16 si quiero que entre en una linea
	
	DELAY_2SEG();
	BORRAR_LCD();
	ESCRIBIR_VECTOR("GRACIAS MAXI",3);
	BORRAR_LCD();
	ESCRIBIR_VECTOR("SELEC. VELOCIDAD   (PRES OK)    ",0);//16 caracteres linea 1 y 16 caracteres linea 2
	P2_7=1;
	while(OK!= 0)
	{
	}
	ESCRIBIR_VECTOR("30mm/seg        50mm/seg        ",0);
	
}

void INICIALIZACION_DISPLAY() //inicializa el display y lo pone en modo de 4 bits
{
	DELAY_MS(LCD_BOOT_ALTA, LCD_BOOT_BAJA);
	
	LCD_PORT=0x03; 
	HABILITAR_DATOS();//5ms en alto y 5 ms en bajo
	DELAY_MS(LCD_DELAY_1_ALTA, LCD_DELAY_1_BAJA);
	
	LCD_PORT=0x03; 
	HABILITAR_DATOS();
	DELAY_MS(LCD_DELAY_2_ALTA, LCD_DELAY_2_BAJA);
	
	LCD_PORT=0x03; 
	HABILITAR_DATOS();	//revisar si hay que hacerlo 3 veces eso depende del display que usemos
	DELAY_MS(LCD_DELAY_1_ALTA, LCD_DELAY_1_BAJA);
	LCD_PORT=0x02; 
	HABILITAR_DATOS();
	DELAY_MS(LCD_DELAY_1_ALTA, LCD_DELAY_1_BAJA);
	
	
	//selecciono trabajar con 4 bits
	//LCD_PORT=0x26; // 001(DL) (N)0xx  DL:Data Length( 1:8bit 0:4bit) N:Dual Line(1:Dual Line 0:Single Line);
	LCD_COMANDO(LCD_MODO_4BITS);
	LCD_COMANDO(LCD_OFF);
	BORRAR_LCD();
	LCD_COMANDO(LCD_MODO_DESPLAZAMIENTO);
	LCD_COMANDO(LCD_PRENDIDO_Y_CURSOR);
}

void BORRAR_LCD( void )
{
	LCD_COMANDO( 0x01 ); //Comando para limpiar el lcd
	DELAY_MS( BORRAR_LCD_ALTA,BORRAR_LCD_BAJA  );    //Tiempo de espera para el clear
}

void DELAY_MS (unsigned char alta, unsigned char baja)
{
	TMOD=0x01;
	TH0=alta;
	TL0=baja;
	TR0=1;
	while(TF0!=1)
	{
	}
	TF0=0;
}

void DELAY_2SEG()
{
	unsigned char CONT;
	for(CONT=0; CONT!=30; CONT++)//DELAY DE 2 SEGUNDO
	{
		DELAY_MS(DELAY_VISUALIZACION_ALTA,DELAY_VISUALIZACION_BAJA);
	}
}

void LCD_COMANDO( unsigned char c )
{
	LCD_PORT &= ~LCD_UNOS;
	LCD_PORT &= ~LCD_RS;   //RS:0
	LCD_PORT &= ~LCD_RW;   //RW:0
	ESCRIBIR_BYTE_LCD( c );
	DELAY_MS( 255, 126 );	//delay de 40us verificar segun modelos
}

void ESCRIBIR_VECTOR( char * string , unsigned char posicion)
{
	POSICION_LCD( posicion );

	for ( ; *(string)  ; string++ )
	{

		/* Dado que la matriz de caracteres del display no es continua, y el
		 * mapa es 0-7-- 40-47 salta en caso de que la posicion sea 8 hasta la
		 * posicion 40 para trabajar con una linea sola
		 * si trabajo con dos lineas son 0-15-- 40-66*/
		if( posicion == 15 )
		{
			POSICION_LCD( posicion = 40 );
		}
		ESCRIBIR_DISPLAY(  *(string) );
		DELAY_MS( DELAY_ESCRITURA_ALTA, DELAY_ESCRITURA_BAJA );
		posicion++;
	}
}

void POSICION_LCD( unsigned char posicion )
{
	LCD_COMANDO( POSICION_LCD_MASK | posicion);
}

void ESCRIBIR_DISPLAY( unsigned char c ) 
{
	LCD_PORT &= ~LCD_UNOS; //Blanqueo los 6 pines del lcd
	LCD_PORT |=  LCD_RS;   //Setteo  RS 0:Instruction register 1:Data Register
	LCD_PORT &= ~LCD_RW;   //Cleareo RW 0:Writing              1:Reading

	ESCRIBIR_BYTE_LCD( c );
}
void ESCRIBIR_BYTE_LCD(unsigned char c)
{
	ESCRIBIR_NIBBLE(c);	//escribo la parte superior del byte
	ESCRIBIR_NIBBLE(c<<4);	//escribo la parte inferior del byte
}

void ESCRIBIR_NIBBLE(unsigned char nibble)
{
	nibble		&= (NIBBLE_MASK<<4);	//tomo solo la parte superior del nibble para escribir escribiendo 0 en la parte baja
	LCD_PORT	&= ~NIBBLE_MASK;			// pongo 0 en la parte inferior para despues poner los nibbles
	LCD_PORT	|= (nibble>>4);				//bajo el nible y lo paso al los puertos
	
	HABILITAR_DATOS();
}
