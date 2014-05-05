PUBLIC PASO						;PARA QUE LAS PUEDA VER DESDE C
PUBLIC DELAY_SLEEP
PUBLIC AVANZAR
PUBLIC RETROCEDER
PUBLIC DELAY_PASOS
PUBLIC AVANZAR_1_PASOM
PUBLIC AVANZAR_1mm
PUBLIC PRENDER
PUBLIC APAGAR
PUBLIC ERROR
PUBLIC RETROCEDER_1mm


;24 pasos del motor son 1,008 mm
;si 1/32 pasos hace el DRV entonces 768 pasos DRV son 1,008mm
; DELAY_PASOS = 1/ (768 * velocidad) donde velocidad son mm/seg

STEP			equ	P1.0	;etiqueto al puerto con el nombre. 
RESET			equ	P1.1
DIR				equ	p1.2
SLEEP			equ	P1.3
FAUL			equ	P1.4
HOME			equ	P1.5
RETRASO_SUP		equ	250		;sale de hacer (65536- retardo deseado) + 6 donde 65536 es el numero maxio del temporizador con 16 bit y 6 el tiempo para setear las variables
RETRASO_INF		equ 236		;retraso sup son los primero 8 bit y el inf son los ultimos 8 
RETRASO_SUP_R	equ	255		;retraso superior e inferior para el retorceso, sale de hacer la misma cuenta que antes
RETRASO_INF_R	equ 45		; la velocidad es de 6mm/seg


cseg at 0x0100

PRENDER:
			SETB SLEEP
			RET

ERROR:
			MOV C,FAUL
			RET
		

APAGAR:
			CLR SLEEP
			RET

DELAY_PASOS_R:						;retardo para el retroceso
			MOV TMOD, #01H
			MOV TH0,#RETRASO_SUP_R
			MOV TL0,#RETRASO_INF_R
			SETB TR0
	CICLO3:	mov R6,TH0
			mov R5,TL0
			JNB TF0,CICLO3
			CLR TF0
			RET
		
		
DELAY_SLEEP:			;es un delay de 1.7ms. Es el tiempo que necesita DRV desde que se lo saca de modo sleep hasta que se le mande la señal para hacer un paso.
			MOV TMOD,#01H
			MOV TH0,#249
			MOV TL0,#98
			SETB TR0
	CICLO:	JNB TF0,CICLO
			CLR TF0
			RET

;			MOV R1,#100
;	LAZO3:	MOV R2,#7 ;
;	LAZO4:	DJNZ R2,LAZO4
;			DJNZ R1,LAZO3
;			RET
			
AVANZAR:
			SETB DIR ;DIR=1 avanza
			RET	
			
DELAY_PASOS:			; es un delay de 1.3ms
			MOV TMOD, #01H
			MOV TH0,#RETRASO_SUP
			MOV TL0,#RETRASO_INF
			SETB TR0
	CICLO2:	JNB TF0,CICLO2
			CLR TF0
			RET

;			MOV R1,#3
;	LAZO5:	MOV R2,#215
;	LAZO6:	DJNZ R2,LAZO6
;			DJNZ R1,LAZO5
;			RET


PASO:					; manda una señal de '1' y '0' para que el DRV haga 1/32 paso
			SETB	STEP
			NOP
			CLR		STEP
			NOP
			RET
			;La señal debe permanecer en alto y bajo 2us por estado para que funcione el DRV
			
AVANZAR_1_PASOM:				;hace un paso completo del motor
			MOV R1,#32
	FALTA:	CALL PASO		
			CALL DELAY_PASOS	;espera entre micropaso y micropaso
			DJNZ R1,FALTA
			RET
			
AVANZAR_1mm:				;avanza 1 mm
			MOV R2,#24
	FALTA2:	CALL AVANZAR_1_PASOM
			DJNZ R2,FALTA2
			RET
			
RETROCEDER_1_PASOM:				;hace un paso completo del motor
			MOV R1,#32
	FALTA3:	CALL PASO		
			CALL DELAY_PASOS_R	;espera entre micropaso y micropaso
			DJNZ R1,FALTA3
			RET
			
RETROCEDER_1mm:				;avanza 1 mm
			MOV R2,#24
	FALTA4:	CALL RETROCEDER_1_PASOM
			DJNZ R2,FALTA4
			RET

RETROCEDER:
			CLR DIR
			RET


	
end