//24 pasos del motor son 1,008 mm
//si 1/32 pasos hace el DRV entonces 768 pasos DRV son 1,008mm
// DELAY_PASOS = velocidad /768 donde velocidad son seg/mm

#include <AT89X52.H>
#define RECORRIDO 10 //defino la long a recorrer en mm
#define CONDICION 1 	//condicion para funcionar


extern void DELAY();
extern void PASO();
extern void DELAY_SLEEP();
extern void AVANZAR();
extern void RETROCEDER();
extern void DELAY_PASOS();
extern void AVANZAR_1_PASOM();
extern void AVANZAR_1mm();
extern void PRENDER();
extern void APAGAR();
extern bit ERROR();
extern void RETROCEDER_1mm();


//volatile uint8_t dis = 0;

void main ()
{
	char R7=0;
	
	if(CONDICION)
	{
		if(ERROR()==0)
		{
			APAGAR();
		}
		else{
			PRENDER();
			AVANZAR();
			DELAY_SLEEP();
			while(R7<RECORRIDO && ERROR()==1)
			{
				AVANZAR_1mm();
				R7++;
			}
			RETROCEDER();
			R7=0;
			while(R7<RECORRIDO && ERROR()==1)
			{
				RETROCEDER_1mm();
				R7++;
			}
		}
	}
	APAGAR();
}

			