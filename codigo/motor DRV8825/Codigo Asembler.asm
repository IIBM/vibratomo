PUBLIC PASO						;para que las pueda ver desde C las declaro como "public"
PUBLIC DELAY_SLEEP
PUBLIC AVANZAR
PUBLIC RETROCEDER
PUBLIC DELAY_PASOS
PUBLIC AVANZAR_1mm
PUBLIC PRENDER
PUBLIC APAGAR
PUBLIC RETROCEDER_1mm
PUBLIC HABILITAR_DATOS
PUBLIC DELAY_ALTO
PUBLIC DELAY_BAJO
PUBLIC HABILITAR_INTERRUPCION
PUBLIC DESABILITAR_INTERRUPCION

;12 pasos del motor son 1,008 mm
;si 1/32 pasos hace el DRV entonces 384 pasos DRV son 1,008mm
; DELAY_AVANCE = 1000000/ (384 * velocidad) donde velocidad son mm/seg

STEP			equ	P3.3	;etiqueto al puerto con el nombre del pin del DRV. 
RESET			equ	P3.4
DIR				equ	P1.1
SLEEP			equ	P3.5
FAUL			equ	P1.0
HOME			equ	P3.6


DELAY_RETROCESO	equ 217		;escrito en us

RETRASO_SUP_R	equ	255-((DELAY_RETROCESO-10)/256)			;retraso superior e inferior para el retorceso, sale de hacer la misma cuenta que antes
RETRASO_INF_R	equ 255-((DELAY_RETROCESO-10)-(255-RETRASO_SUP_R)*256)		; la velocidad es de 6mm/seg

RS_LCD			equ P2.5	;etiqueto al puerto con el nombre del pin del display
RW_LCD			equ P2.4
ENEBLE_LCD		equ P2.6
DATA4_LCD		equ	P2.0
DATA5_LCD		equ	P2.1
DATA6_LCD		equ	P2.2
DATA7_LCD		equ	P2.3

OK				equ	P2.7	;etiqueto al puerto con el nombre del boton
ARRIBA 			equ	P1.3
ABAJO 			equ	P1.2
STOP			equ P3.2

dseg at 0x30
DELAY_ALTO: ds 1
DELAY_BAJO: ds 1


cseg at 0x0100

HABILITAR_DATOS:			; da la ventana necesaria al enable para que los datos se transmitan al display
			SETB ENEBLE_LCD
			CLR ENEBLE_LCD
			RET

HABILITAR_INTERRUPCION:
			MOV IE, #81H
			RET
			
DESABILITAR_INTERRUPCION:
			MOV IE, #00H
			RET

PRENDER:
			SETB SLEEP
			RET

APAGAR:
			CLR SLEEP
			RET

DELAY_PASOS_R:						;retardo para el retroceso
			MOV R6,#RETRASO_SUP_R
			MOV R7,#RETRASO_INF_R
			CALL DELAY
			RET

DELAY_PASOS:			; es un delay de 1.3ms
			MOV R6,DELAY_ALTO
			MOV R7,DELAY_BAJO
			CALL DELAY
			RET


DELAY:		
			MOV TMOD, #01H
			MOV TH0,R6
			MOV TL0,R7
			SETB TR0
	CICLO2:	JNB TF0,CICLO2
			CLR TF0
			RET
		
DELAY_SLEEP:			;es un delay de 1.7ms. Es el tiempo que necesita DRV desde que se lo saca de modo sleep hasta que se le mande la señal para hacer un paso.
			MOV TMOD,#01H
			MOV TH0,#248
			MOV TL0,#98
			SETB TR0
	CICLO:	JNB TF0,CICLO
			CLR TF0
			RET

			
AVANZAR:
			SETB DIR ;DIR=1 avanza
			RET	
			
PASO:					; manda una señal de '1' y '0' para que el DRV haga 1/32 paso
			SETB	STEP
			nop
			nop
	SIGUE:	CLR		STEP
			nop
			nop
			RET
			;La señal debe permanecer en alto y bajo 2us por estado para que funcione el DRV
			
			
AVANZAR_1mm:				;avanza 1 mm
			MOV R2,#12
	FALTA2:	MOV R1,#32
	FALTA:	CALL PASO			;hace un paso completo del motor
			CALL DELAY_PASOS	;espera entre micropaso y micropaso
			DJNZ R1,FALTA
			DJNZ R2,FALTA2
			RET
			
RETROCEDER_1_PASOM:				;hace un paso completo del motor
			MOV R1,#32
	FALTA3:	CALL PASO		
			CALL DELAY_PASOS_R	;espera entre micropaso y micropaso
			DJNZ R1,FALTA3
			RET
			
RETROCEDER_1mm:				;avanza 1 mm
			MOV R2,#12
	FALTA4:	CALL RETROCEDER_1_PASOM
			DJNZ R2,FALTA4
			RET

RETROCEDER:
			CLR DIR
			RET
end