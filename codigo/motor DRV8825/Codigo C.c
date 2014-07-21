#include <AT89X52.H>

/* Para el motor
24 pasos del motor son 1,008 mm
si 1/32 pasos hace el DRV entonces 768 pasos DRV son 1,008mm
DELAY_PASOS = velocidad /768 donde velocidad son seg/mm */

#define RECORRIDO 30 //defino la long a recorrer en mm
#define ERROR P1_0	//nfaul
#define RESET P3_4  //reset

// Para el LCd
#define	D4	P2_0
#define D5	P2_1
#define	D6	P2_2
#define	D7	P2_3
#define	RW	P2_4
#define	RS	P2_5
#define	ENA	P2_6
#define LCD_PORT	P2
#define OK	P2_7
#define ARRIBA P1_3
#define ABAJO P1_2
#define INICIAR P1_4
#define STOP P3_2


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
#define DELAY_BOTONES_ALTA 0 //delay de 50ms
#define DELAY_BOTONES_BAJA 176
#define NIBBLE_MASK 0x0F
#define POSICION_LCD_MASK 0x80	//1000  0000
#define LCD_RS	0x20  //xx1x xxxx
#define LCD_RW  0x10  //xxx1 xxxx
#define LCD_MODO_4BITS 0x28	//001(DL) (N)0xx  DL:Data Length( 1:8bit 0:4bit) N:Dual Line(1:Dual Line 0:Single Line) VER SEGUN DISPLAY COMPRADO
#define LCD_MODO_DESPLAZAMIENTO 0x06//incrementar contador de direccion automaticamente y el display quieto
#define LCD_PRENDIDO_SIN_CURSOR 0x0C// DISPLAY ON CURSOR OFF
#define LCD_PRENDIDO_CURSOR_PARPADEANTE 0x0D// Display ON Cursor parpadiando
#define LCD_OFF 0x08// apagar el display


//agregamos las rutinas de asembler
extern void HABILITAR_DATOS();
extern void PASO();
extern void DELAY_SLEEP();
extern void AVANZAR();
extern void RETROCEDER();
extern void DELAY_PASOS();
extern void AVANZAR_1_PASOM();
extern void AVANZAR_1mm();
extern void PRENDER();
extern void APAGAR();
extern void RETROCEDER_1mm();
extern void HABILITAR_INTERRUPCION();
extern void DESABILITAR_INTERRUPCION();
extern unsigned char DELAY_ALTO;
extern unsigned char DELAY_BAJO;


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
void BOTONES_LISTOS();
void OPCION_NO_CORTAR();
void MENU_NO_CORTAR();
void ESCRIBIR_CARACTER();
void FLECHA_ABAJO();
void FLECHA_ARRIBA();
void MOTOR();
void DEFINIR_DELAY(unsigned char vel);
void ACCION_EMERGENCIA();


unsigned char pos; //para moverme entre las opciones del menú y mostrar de a dos lineas por el display
unsigned char pos2; //para seleccionar una opcion de las dos lineas mostradas por el display
unsigned char pos3; // para seleccionar uno de los valor de la velocidad que introduce el usuario
unsigned char cancelar; // para salir de los distintos menues
unsigned char vel; // variable para realizar la cuenta del delay de la velocidad 

void main()
{
	APAGAR();
	INICIALIZACION_DISPLAY();
	ESCRIBIR_VECTOR("VIBRATOMO",4); //al inicializar el equipo mostramos por display la palabra vibrátomo
	ESCRIBIR_CARACTER();	//graba los caracteres de las flechas para arriba y para abajo en el LCD
	DELAY_2SEG();	
	BORRAR_LCD();
	ESCRIBIR_VECTOR("SELEC. VELOCIDAD   (PRES OK)    ",0);
	OK=1;
	while(OK!= 0)	//espera a que se presiones el boton ok 
	{
	}
	pos=0;
	pos2=0;
	cancelar=0;
	BOTONES_LISTOS(); //es un delay para evitar el rebote del boton 
	do
	{
		cancelar=0;
		if(pos<2) 		//parte del menu para las dos primeras opciones de corte
		{
			ESCRIBIR_VECTOR("0.5 mm/seg      0.7 mm/seg     ",0); //muestro las primeras dos lineas del menú
			FLECHA_ABAJO();
			if(pos==0)
			{
				POSICION_LCD(0);
			}
			else
			{	
				POSICION_LCD(40);
			}
			LCD_COMANDO(LCD_PRENDIDO_CURSOR_PARPADEANTE);
			while(pos<2 && cancelar!=1)
			{
				if(ARRIBA==0 && pos==1)
				{
					POSICION_LCD(0);
					pos=0;
					BOTONES_LISTOS();
				}
				if(ABAJO==0 && pos==0)
				{
					POSICION_LCD(40);
					pos=1;
					BOTONES_LISTOS();
				}
				if(ABAJO==0 && pos==1)
				{
					pos=2;
					BOTONES_LISTOS();
				}
				if(OK== 0)
				{
					BOTONES_LISTOS();
					pos2=0;
					switch(pos)
					{
						case 0:
							while (cancelar!=1)
							{
								LCD_COMANDO(LCD_PRENDIDO_SIN_CURSOR);
								if(pos2==0)
								{
									ESCRIBIR_VECTOR("VEL: 0.5 mm/seg   PESS INICIAR  ",0);
									FLECHA_ABAJO();
									pos2=2;
								}
								if(INICIAR==0)
								{
									BOTONES_LISTOS();
									vel=5;
									DEFINIR_DELAY(vel);
									ESCRIBIR_VECTOR("CORTANDO CON    VEL: 0.5 mm/seg ",0);
									HABILITAR_INTERRUPCION();
									MOTOR();
									DESABILITAR_INTERRUPCION();
									//cancelar=1;
									pos=0;
									pos2=0;
								}
								MENU_NO_CORTAR();	//este parte de menu se repite en para cada opcion de corte por lo que se hizo una funcion aparte con ella asi
							}						//nos ahorramos memoria de codigo
							break;
						case 1:
							while (cancelar!=1)
							{
								LCD_COMANDO(LCD_PRENDIDO_SIN_CURSOR);
								if(pos2==0)
								{
									ESCRIBIR_VECTOR("VEL: 0.7 mm/seg   PESS INICIAR  ",0);
									FLECHA_ABAJO();									
									pos2=2;
								}
								if(INICIAR==0)
								{
									BOTONES_LISTOS();
									vel=7;
									DEFINIR_DELAY(vel);
									ESCRIBIR_VECTOR("CORTANDO CON    VEL: 0.7 mm/seg ",0);
									HABILITAR_INTERRUPCION();
									MOTOR();
									DESABILITAR_INTERRUPCION();
									//cancelar=1;
									pos=0;
									pos2=0;
								}
								MENU_NO_CORTAR();
							}
							break;
						default:
							break;
					}
				}
			}
		}
		if(pos>1 && pos<4)	//parte del menu para las siguientes dos opciones de corte
		{
			ESCRIBIR_VECTOR("0.9 mm/seg      1.1 mm/seg      ",0); //muestro las segundas dos lineas del menú
			FLECHA_ARRIBA();
			FLECHA_ABAJO();
			if(pos==2)
			{
				POSICION_LCD(0);
			}
			else
			{	
				POSICION_LCD(40);
			}
			LCD_COMANDO(LCD_PRENDIDO_CURSOR_PARPADEANTE);
			while(pos>1 && pos<4)
			{
				if(ARRIBA==0 && pos==2)
				{
					POSICION_LCD(0);
					pos=1;
					BOTONES_LISTOS();
				}
				if(ARRIBA==0 && pos==3)
				{
					POSICION_LCD(0);
					pos=2;
					BOTONES_LISTOS();
				}
				if(ABAJO==0 && pos==2)
				{
					POSICION_LCD(40);
					pos=3;
					BOTONES_LISTOS();
				}
				if(ABAJO==0 && pos==3)
				{
					pos=4;
					BOTONES_LISTOS();
				}
				if(OK== 0)
				{
					pos2=0;
					BOTONES_LISTOS();
					switch(pos)
					{
						case 2:
							while (cancelar!=1)
							{
								LCD_COMANDO(LCD_PRENDIDO_SIN_CURSOR);
								if(pos2==0)
								{
									ESCRIBIR_VECTOR("VEL: 0.9 mm/seg   PESS INICIAR  ",0);
									FLECHA_ABAJO();									
									pos2=2;
								}
								if(INICIAR==0)
								{
									BOTONES_LISTOS();
									vel=9;
									DEFINIR_DELAY(vel);
									ESCRIBIR_VECTOR("CORTANDO CON    VEL: 0.9 mm/seg ",0);
									HABILITAR_INTERRUPCION();
									MOTOR();
									DESABILITAR_INTERRUPCION();
									//cancelar=1;
									pos=0;
									pos2=0;
								}
								MENU_NO_CORTAR();
							}
							break;
						case 3:
							while (cancelar!=1)
							{
								LCD_COMANDO(LCD_PRENDIDO_SIN_CURSOR);
								if(pos2==0)
								{
									ESCRIBIR_VECTOR("VEL: 1.1 mm/seg   PESS INICIAR  ",0);
									FLECHA_ABAJO();									
									pos2=2;
								}
								if(INICIAR==0)
								{
									BOTONES_LISTOS();
									vel=11;
									DEFINIR_DELAY(vel);
									ESCRIBIR_VECTOR("CORTANDO CON    VEL: 1.1 mm/seg ",0);
									HABILITAR_INTERRUPCION();
									MOTOR();
									DESABILITAR_INTERRUPCION();
									//cancelar=1;
									pos=0;
									pos2=0;
								}
								MENU_NO_CORTAR();
							}
							break;
						default:
							break;
					}
				}
			}
		}
		if(pos>3 && pos<6)	//parte del menu para las siguientes dos opciones de corte
		{
			ESCRIBIR_VECTOR("1.3 mm/seg      1.5 mm/seg       ",0); //muestro las terceras dos lineas del menú
			FLECHA_ABAJO();
			FLECHA_ARRIBA();
			if(pos==4)
			{
				POSICION_LCD(0);
			}
			else
			{	
				POSICION_LCD(40);
			}
			LCD_COMANDO(LCD_PRENDIDO_CURSOR_PARPADEANTE);
			BOTONES_LISTOS();
			while(pos>3 && pos<6)
			{
				if(ARRIBA==0 && pos==4)
				{
					POSICION_LCD(0);
					pos=3;
					BOTONES_LISTOS();
				}
				if(ARRIBA==0 && pos==5)
				{
					POSICION_LCD(0);
					pos=4;
					BOTONES_LISTOS();
				}
				if(ABAJO==0 && pos==4)
				{
					POSICION_LCD(40);
					pos=5;
					BOTONES_LISTOS();
				}
				if(ABAJO==0 && pos==5)
				{
					pos=6;
					BOTONES_LISTOS();
				}
				if(OK== 0)
				{
					BOTONES_LISTOS();
					pos2=0;
					switch(pos)
					{
						case 4:
							while (cancelar!=1)
							{
								LCD_COMANDO(LCD_PRENDIDO_SIN_CURSOR);
								if(pos2==0)
								{
									ESCRIBIR_VECTOR("VEL: 1.3 mm/seg   PESS INICIAR  ",0);
									FLECHA_ABAJO();									
									pos2=2;
								}
								if(INICIAR==0)
								{
									BOTONES_LISTOS();
									vel=13;
									DEFINIR_DELAY(vel);
									ESCRIBIR_VECTOR("CORTANDO CON    VEL: 1.3 mm/seg ",0);
									HABILITAR_INTERRUPCION();
									MOTOR();
									DESABILITAR_INTERRUPCION();
									//cancelar=1;
									pos=0;
									pos2=0;
								}
								MENU_NO_CORTAR();
							}
							break;
						case 5:
							while (cancelar!=1)
							{
								LCD_COMANDO(LCD_PRENDIDO_SIN_CURSOR);
								if(pos2==0)
								{
									ESCRIBIR_VECTOR("VEL: 1.5 mm/seg   PESS INICIAR  ",0);
									FLECHA_ABAJO();									
									pos2=2;
								}
								if(INICIAR==0)
								{
									BOTONES_LISTOS();
									vel=15;
									DEFINIR_DELAY(vel);
									ESCRIBIR_VECTOR("CORTANDO CON    VEL: 1.5 mm/seg ",0);
									HABILITAR_INTERRUPCION();
									MOTOR();
									DESABILITAR_INTERRUPCION();
									//cancelar=1;
									pos=0;
									pos2=0;
								}
								MENU_NO_CORTAR();
							}
							break;
						default:
							break;
					}
				}
			}
		}
		if(pos>5 && pos<8)	//parte del menu para las siguientes dos opciones de corte
		{
			ESCRIBIR_VECTOR("1.7 mm/seg      1.9 mm/seg       ",0); //muestro las cuartas dos lineas del menú
			FLECHA_ARRIBA();
			FLECHA_ABAJO();
			if(pos==6)
			{
				POSICION_LCD(0);
			}
			else
			{	
				POSICION_LCD(40);
			}
			LCD_COMANDO(LCD_PRENDIDO_CURSOR_PARPADEANTE);
			BOTONES_LISTOS();
			while(pos>5 && pos<8)
			{
				if(ARRIBA==0 && pos==6)
				{
					POSICION_LCD(0);
					pos=5;
					BOTONES_LISTOS();
				}
				if(ARRIBA==0 && pos==7)
				{
					POSICION_LCD(0);
					pos=6;
					BOTONES_LISTOS();
				}
				if(ABAJO==0 && pos==6)
				{
					POSICION_LCD(40);
					pos=7;
					BOTONES_LISTOS();
				}
				if(ABAJO==0 && pos==7)
				{
					pos=8;
					BOTONES_LISTOS();
				}
				if(OK== 0)
				{
					BOTONES_LISTOS();
					pos2=0;
					switch(pos)
					{
						case 6:
							while (cancelar!=1)
							{
								LCD_COMANDO(LCD_PRENDIDO_SIN_CURSOR);
								if(pos2==0)
								{
									ESCRIBIR_VECTOR("VEL: 1.7 mm/seg   PESS INICIAR  ",0);
									FLECHA_ABAJO();
									pos2=2;
								}
								if(INICIAR==0)
								{
									BOTONES_LISTOS();
									vel=17;
									DEFINIR_DELAY(vel);
									ESCRIBIR_VECTOR("CORTANDO CON    VEL: 1.7 mm/seg ",0);
									HABILITAR_INTERRUPCION();
									MOTOR();
									DESABILITAR_INTERRUPCION();
									//cancelar=1;
									pos=0;
									pos2=0;
								}
								MENU_NO_CORTAR();
							}
							break;
						case 7:
							while (cancelar!=1)
							{
								LCD_COMANDO(LCD_PRENDIDO_SIN_CURSOR);
								if(pos2==0)
								{
									ESCRIBIR_VECTOR("VEL: 1.9 mm/seg   PESS INICIAR  ",0);
									FLECHA_ABAJO();
									pos2=2;
								}
								if(INICIAR==0)
								{
									BOTONES_LISTOS();
									vel=19;
									DEFINIR_DELAY(vel);
									ESCRIBIR_VECTOR("CORTANDO CON    VEL: 1.9 mm/seg ",0);
									HABILITAR_INTERRUPCION();
									MOTOR();
									DESABILITAR_INTERRUPCION();
									//cancelar=1;
									pos=0;
									pos2=0;
								}
								MENU_NO_CORTAR();
							}
							break;
						default:
							break;
					}
				}
			}
		}
		if(pos==8)	//parte del menu donde el usuario ingresa la velocidad que desea para el corte
		{
			ESCRIBIR_VECTOR("INTRODUCCIR     VELOCIDAD       ",0); //muestro las quintas dos lineas del menú
			FLECHA_ARRIBA();
			POSICION_LCD(0);
			LCD_COMANDO(LCD_PRENDIDO_CURSOR_PARPADEANTE);
			BOTONES_LISTOS();
			while(pos==8 && cancelar!=1)
			{
				if(ARRIBA==0 && pos==8)
				{
					POSICION_LCD(0);
					pos=7;
					BOTONES_LISTOS();
				}
				if(OK== 0)
				{
					BOTONES_LISTOS();
					pos2=1;
					pos=0;
					ESCRIBIR_VECTOR("VEL: 0.0 mm/seg                ",0);
					POSICION_LCD(45);
					ESCRIBIR_DISPLAY(0);
					POSICION_LCD(47);
					ESCRIBIR_DISPLAY(0);
					POSICION_LCD(5);
					while(pos2<15)
					{
						if(ABAJO==0)
						{	
							BOTONES_LISTOS();
							ESCRIBIR_DISPLAY('0'+pos2);
							pos=pos2;
							pos2++;
							POSICION_LCD(5);
							if(pos2==10)
							{
								pos2=0;
								POSICION_LCD(5);
							}
						}
						if(OK== 0)
						{
							BOTONES_LISTOS();
							pos2=15;
						}
					}
					pos2=1;
					pos3=0;
					POSICION_LCD(7);
					while(pos2<11)
					{
						if(ABAJO==0)
						{
							BOTONES_LISTOS();							
							ESCRIBIR_DISPLAY('0'+pos2);
							pos3=pos2;
							pos2++;
							POSICION_LCD(7);
							if(pos2==10)
							{
								pos2=0;
							}
						}
						if(OK== 0)
						{
							BOTONES_LISTOS();
							pos2=11;
						}
					}
					pos2=0;
					LCD_COMANDO(LCD_PRENDIDO_SIN_CURSOR);
					while (cancelar!=1)
					{
						if(pos2==0)
						{
							ESCRIBIR_VECTOR("VEL: x.x mm/seg   PESS INICIAR  ",0);
							POSICION_LCD(5);
							ESCRIBIR_DISPLAY('0'+pos);
							POSICION_LCD(7);
							ESCRIBIR_DISPLAY('0'+pos3);
							FLECHA_ABAJO();
							pos2=2;
						}
						if(INICIAR==0)
						{
							BOTONES_LISTOS();
							vel=(pos*10)+pos3;
							DEFINIR_DELAY(vel);
							ESCRIBIR_VECTOR("CORTANDO CON    VEL: X.X mm/seg ",0);
							POSICION_LCD(45);
							ESCRIBIR_DISPLAY('0'+pos);
							POSICION_LCD(47);
							ESCRIBIR_DISPLAY('0'+pos3);
							HABILITAR_INTERRUPCION();
							MOTOR();
							DESABILITAR_INTERRUPCION();
							//cancelar=1;
							//pos=0;
							pos2=0;
						}
						MENU_NO_CORTAR();
					}
				}
			}
		}

	}while(pos<10);
}

void DEFINIR_DELAY(unsigned char vel) //funcion que se usa para definr el retraso que se usa entre cada paso segun la velocidad requerida
{
	unsigned int espera;
	espera = 10000000/ (384 * vel);
	DELAY_ALTO=255-((espera-10)/256);
	DELAY_BAJO=255-((espera-10)-(255-DELAY_ALTO)*256);
}


EMERGENCIA() interrupt 0 //funcion de interrupcion que se utiliza cuando el usuario aprieta el boton rojo para parar el corte de la maquina
{
	ACCION_EMERGENCIA();
}
	
void ACCION_EMERGENCIA()
{
	BOTONES_LISTOS();
	ESCRIBIR_VECTOR("RETIRE MUESTRA YPRESIONE OK     ",0);
	while(OK!= 0)
	{
	}
	BOTONES_LISTOS();
	ESCRIBIR_VECTOR("   ESPERE...                    ",0);
}	
	
void MOTOR() //función que maneja el funcionamiento del motor
{
	char cont=0;
	RESET=0;
	DELAY_SLEEP();
	RESET=1;
	DELAY_SLEEP();
	PRENDER();
	AVANZAR();
	DELAY_SLEEP();
	if(ERROR==0) 
	{
		APAGAR(); //si se produjo un error con el DRV, se lo apaga
		ESCRIBIR_VECTOR("PROBLEMA CON DRVREINICIAR EQUIPO",0);
		while(1)
		{
		}
	}
	else{ //si no hubo error, se mueve el motor
		while(cont<RECORRIDO) //avance de la cuchilla
		{
			AVANZAR_1mm();
			cont++;
		}
		RETROCEDER();
		cont=0;
		while(cont<RECORRIDO && ERROR==1) //retroceso de la cuchilla
		{
			RETROCEDER_1mm();
			cont++;
		}
	}
	APAGAR(); //al finalizar de cortar y volver la cuchilla a su lugar de inicio, se lleva al DRV a modo sleep
}

void ESCRIBIR_CARACTER()
{
	LCD_COMANDO(64);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);
	RS=1;
	ESCRIBIR_BYTE_LCD(4);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	LCD_COMANDO(65);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	RS=1;
	ESCRIBIR_BYTE_LCD(4);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	LCD_COMANDO(66);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	RS=1;
	ESCRIBIR_BYTE_LCD(4);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	LCD_COMANDO(67);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	RS=1;
	ESCRIBIR_BYTE_LCD(4);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	LCD_COMANDO(68);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	RS=1;
	ESCRIBIR_BYTE_LCD(4);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	LCD_COMANDO(69);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	RS=1;
	ESCRIBIR_BYTE_LCD(21);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	LCD_COMANDO(70);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	RS=1;
	ESCRIBIR_BYTE_LCD(14);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	LCD_COMANDO(71);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	RS=1;
	ESCRIBIR_BYTE_LCD(4);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);
	
	LCD_COMANDO(72);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);
	RS=1;
	ESCRIBIR_BYTE_LCD(4);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	LCD_COMANDO(73);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	RS=1;
	ESCRIBIR_BYTE_LCD(14);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	LCD_COMANDO(74);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	RS=1;
	ESCRIBIR_BYTE_LCD(21);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	LCD_COMANDO(75);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	RS=1;
	ESCRIBIR_BYTE_LCD(4);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	LCD_COMANDO(76);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	RS=1;
	ESCRIBIR_BYTE_LCD(4);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	LCD_COMANDO(77);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	RS=1;
	ESCRIBIR_BYTE_LCD(4);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	LCD_COMANDO(78);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	RS=1;
	ESCRIBIR_BYTE_LCD(4);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	LCD_COMANDO(79);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

	RS=1;
	ESCRIBIR_BYTE_LCD(4);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);

}

void FLECHA_ARRIBA() //funcion para mostrar la flecha arriba al final de la priemra linea del LCD
{
	POSICION_LCD(15);
	ESCRIBIR_DISPLAY(1);
}

void FLECHA_ABAJO()	 //funcion para mostrar la flecha arriba al final de la segunda linea del LCD
{
	POSICION_LCD(55);
	ESCRIBIR_DISPLAY(0);
}

void MENU_NO_CORTAR() //parte del menu que se repite varias veces en el menu principal
{
	if(ABAJO==0)
	{					 
		pos2=1;
		BOTONES_LISTOS();
	}
	if(pos2==1)
	{
		OPCION_NO_CORTAR();
	}
	if(ARRIBA==0)
	{
		pos2=0;
		BOTONES_LISTOS();
	}
	if(OK==0)
	{
		BOTONES_LISTOS();
		cancelar=1;
		pos=0;
	}
}

void BOTONES_LISTOS ()
{
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);
	while(OK!=1 || ABAJO!=1 || ARRIBA!=1 || INICIAR!=1)
	{
	}
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);
	DELAY_MS(DELAY_BOTONES_ALTA,DELAY_BOTONES_BAJA);
	OK=1;
	ABAJO=1;
	ARRIBA=1;
	INICIAR=1;
}

void OPCION_NO_CORTAR()
{
	ESCRIBIR_VECTOR("OTRA VELOCIDAD  PRECIONAR OK    ",0);
	FLECHA_ARRIBA();
	pos2=2;
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
	HABILITAR_DATOS();	
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
	LCD_COMANDO(LCD_PRENDIDO_SIN_CURSOR);
}

void BORRAR_LCD( void ) //borra lo que este en la pantalla del LCD
{
	LCD_COMANDO( 0x01 ); //Comando para limpiar el lcd
	DELAY_MS( BORRAR_LCD_ALTA,BORRAR_LCD_BAJA  );    //Tiempo de espera para el clear
}

void DELAY_MS (unsigned char alta, unsigned char baja) //funcion que se utiliza para generar retrasos
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

void LCD_COMANDO( unsigned char c ) // funcion para pasarle comandos al LCD
{
	LCD_PORT &= ~LCD_UNOS;
	LCD_PORT &= ~LCD_RS;   //RS:0
	LCD_PORT &= ~LCD_RW;   //RW:0
	ESCRIBIR_BYTE_LCD( c );
	DELAY_MS( 255, 126 );	//delay de 40us verificar segun modelos
}

void ESCRIBIR_VECTOR( char * string , unsigned char posicion) //Funcion utilizada para escribir en la pantalla del LCD 
{
	POSICION_LCD( posicion );

	for ( ; *(string)  ; string++ )
	{

		/* Dado que la matriz de caracteres del display no es continua, y el
		 * mapa es 0-7-- 40-47 salta en caso de que la posicion sea 8 hasta la
		 * posicion 40 para trabajar con una linea sola
		 * si trabajo con dos lineas son 0-15-- 40-66*/
		if( posicion == 16 )
		{
			POSICION_LCD( posicion = 40 );
		}
		ESCRIBIR_DISPLAY(  *(string) );
		DELAY_MS( DELAY_ESCRITURA_ALTA, DELAY_ESCRITURA_BAJA );
		posicion++;
	}
}

void POSICION_LCD( unsigned char posicion ) // para posicionarse en la pantalla del LCD
{
	LCD_COMANDO( POSICION_LCD_MASK | posicion);
	DELAY_MS(LCD_DELAY_2_ALTA,LCD_DELAY_2_BAJA);
}

void ESCRIBIR_DISPLAY( unsigned char c ) //escribe un solo caracter en el LCD
{
	LCD_PORT &= ~LCD_UNOS; //Blanqueo los 6 pines del lcd
	LCD_PORT |=  LCD_RS;   //Setteo  RS 0:Instruction register 1:Data Register
	LCD_PORT &= ~LCD_RW;   //Cleareo RW 0:Writing              1:Reading

	ESCRIBIR_BYTE_LCD( c );
	DELAY_MS(DELAY_ESCRITURA_ALTA,DELAY_ESCRITURA_BAJA);
}

void ESCRIBIR_BYTE_LCD(unsigned char c) // le pase un byte de informacion al LCD de a 4 bits por el mode en qe se seteo el LCD
{
	ESCRIBIR_NIBBLE(c);	//escribo la parte superior del byte
	ESCRIBIR_NIBBLE(c<<4);	//escribo la parte inferior del byte
}

void ESCRIBIR_NIBBLE(unsigned char nibble)// complemento de la funcion ESCRIBIR_BYTE_LCD
{
	nibble		&= (NIBBLE_MASK<<4);	//tomo solo la parte superior del nibble para escribir escribiendo 0 en la parte baja
	LCD_PORT	&= ~NIBBLE_MASK;			// pongo 0 en la parte inferior para despues poner los nibbles
	LCD_PORT	|= (nibble>>4);				//bajo el nible y lo paso al los puertos
	
	HABILITAR_DATOS();
}
