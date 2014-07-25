EESchema Schematic File Version 2
LIBS:AT89S8253
LIBS:con-molex
LIBS:con-molex-2
LIBS:EP_molex_6410_7395
LIBS:ep_molex_6410_7395-02
LIBS:L298
LIBS:marula-h-bridge
LIBS:stepper_drivers
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "14 may 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L AT89S8253 U?
U 1 1 5372B27C
P 6800 3200
F 0 "U?" H 6800 3100 50  0000 C CNN
F 1 "AT89S8253" H 6800 3300 50  0000 C CNN
F 2 "DIP-40__600_ELL" H 6800 4250 60  0000 C CNN
F 3 "" H 6800 3200 60  0000 C CNN
	1    6800 3200
	1    0    0    -1  
$EndComp
Text Label 4450 4100 0    60   ~ 0
GND
Text GLabel 6050 4150 0    60   Input ~ 0
GND
$Comp
L C C?
U 1 1 5372B3E9
P 5150 4050
F 0 "C?" H 5150 4150 40  0000 L CNN
F 1 "C" H 5156 3965 40  0000 L CNN
F 2 "~" H 5188 3900 30  0000 C CNN
F 3 "~" H 5150 4050 60  0000 C CNN
	1    5150 4050
	0    1    1    0   
$EndComp
$Comp
L C C?
U 1 1 5372B409
P 5150 3700
F 0 "C?" H 5150 3800 40  0000 L CNN
F 1 "C" H 5156 3615 40  0000 L CNN
F 2 "~" H 5188 3550 30  0000 C CNN
F 3 "~" H 5150 3700 60  0000 C CNN
	1    5150 3700
	0    -1   -1   0   
$EndComp
Text GLabel 4800 4050 0    60   Input ~ 0
GND
Wire Wire Line
	4800 4050 4950 4050
Wire Wire Line
	4950 4050 4950 3850
Wire Wire Line
	5350 4050 6050 4050
Wire Wire Line
	4950 3700 4950 3900
Connection ~ 4950 3900
Wire Wire Line
	6050 3950 5700 3950
Wire Wire Line
	5700 3700 5700 3950
Wire Wire Line
	5350 3700 5700 3700
Text GLabel 7550 2250 2    60   Input ~ 0
VDD
Text GLabel 7550 3150 2    60   Input ~ 0
VDD
Text GLabel 6050 2750 0    60   Input ~ 0
MOSI
Text GLabel 6050 2850 0    60   Input ~ 0
MISO
Text GLabel 6050 2950 0    60   Input ~ 0
SCK
Text GLabel 6050 3050 0    60   Input ~ 0
RESET
Text GLabel 6050 3150 0    60   Input ~ 0
RXD*
Text GLabel 6050 3250 0    60   Input ~ 0
TXD*
$EndSCHEMATC
