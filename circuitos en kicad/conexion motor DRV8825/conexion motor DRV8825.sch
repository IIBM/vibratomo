EESchema Schematic File Version 2
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
LIBS:marula-h-bridge
LIBS:conexion motor DRV8825-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "15 jun 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	4950 1900 5500 1900
Connection ~ 5900 2300
Wire Wire Line
	5900 2200 5900 2300
Wire Wire Line
	7300 4600 7400 4600
Wire Wire Line
	7400 4600 7400 4400
Wire Wire Line
	7400 4400 7300 4400
Wire Wire Line
	6800 4250 6800 4400
Wire Wire Line
	6800 4250 6600 4250
Connection ~ 6900 3550
Wire Wire Line
	6900 3300 6900 3550
Wire Wire Line
	7650 4200 6700 4200
Wire Wire Line
	6700 4200 6700 4000
Wire Wire Line
	6700 4000 6600 4000
Wire Wire Line
	7650 3850 7650 3800
Wire Wire Line
	7650 3800 6600 3800
Wire Wire Line
	4050 3600 4200 3600
Wire Wire Line
	4200 3600 4200 3200
Wire Wire Line
	4200 3200 4400 3200
Wire Wire Line
	4050 2600 4200 2600
Wire Wire Line
	4200 2600 4200 2800
Wire Wire Line
	4050 3100 4600 3100
Wire Wire Line
	4600 2950 4600 2800
Wire Wire Line
	4600 2800 4200 2800
Connection ~ 4400 2800
Wire Wire Line
	7650 3650 6600 3650
Wire Wire Line
	6600 3650 6600 3700
Wire Wire Line
	7650 4000 6800 4000
Wire Wire Line
	6800 4000 6800 3900
Wire Wire Line
	6800 3900 6600 3900
Wire Wire Line
	6600 3550 6950 3550
Wire Wire Line
	6950 3550 6950 3500
Wire Wire Line
	7400 3300 7400 3500
Wire Wire Line
	7400 3500 7350 3500
Wire Wire Line
	6600 4450 6750 4450
Wire Wire Line
	6750 4450 6750 4600
Wire Wire Line
	6750 4600 6800 4600
Connection ~ 5400 1900
Connection ~ 6400 1900
Wire Wire Line
	5100 2300 6400 2300
Wire Wire Line
	4600 3200 4500 3200
Wire Wire Line
	4500 3200 4500 3100
Connection ~ 4500 3100
Text GLabel 6650 1900 1    60   Input ~ 0
Vcc
Text GLabel 5200 1900 1    60   Input ~ 0
VM
Text GLabel 5900 2300 3    60   Input ~ 0
GND
$Comp
L C C3
U 1 1 5353552D
P 6400 2100
F 0 "C3" H 6450 2200 50  0000 L CNN
F 1 "0.1uF" H 6450 2000 50  0000 L CNN
F 2 "" H 6400 2100 60  0001 C CNN
F 3 "" H 6400 2100 60  0001 C CNN
	1    6400 2100
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 53535525
P 5400 2100
F 0 "C2" H 5450 2200 50  0000 L CNN
F 1 "0.33uF" H 5450 2000 50  0000 L CNN
F 2 "" H 5400 2100 60  0001 C CNN
F 3 "" H 5400 2100 60  0001 C CNN
	1    5400 2100
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 535332CA
P 4600 5150
F 0 "D1" H 4600 5250 50  0000 C CNN
F 1 "LED" H 4600 5050 50  0000 C CNN
F 2 "" H 4600 5150 60  0001 C CNN
F 3 "" H 4600 5150 60  0001 C CNN
	1    4600 5150
	-1   0    0    1   
$EndComp
Text GLabel 4600 4050 0    60   Input ~ 0
GND
$Comp
L DRV8825 U1
U 1 1 53532AEA
P 5550 3750
F 0 "U1" H 5000 4750 60  0000 C CNN
F 1 "DRV8825" H 6050 2450 60  0000 C CNN
F 2 "" H 5550 3750 60  0001 C CNN
F 3 "" H 5550 3750 60  0001 C CNN
	1    5550 3750
	1    0    0    -1  
$EndComp
Text GLabel 7400 4500 2    60   Input ~ 0
GND
$Comp
L R R3
U 1 1 53519831
P 7050 4400
F 0 "R3" V 7130 4400 50  0000 C CNN
F 1 "R" V 7050 4400 50  0000 C CNN
F 2 "" H 7050 4400 60  0001 C CNN
F 3 "" H 7050 4400 60  0001 C CNN
	1    7050 4400
	0    -1   -1   0   
$EndComp
$Comp
L R R4
U 1 1 53519828
P 7050 4600
F 0 "R4" V 7130 4600 50  0000 C CNN
F 1 "R" V 7050 4600 50  0000 C CNN
F 2 "" H 7050 4600 60  0001 C CNN
F 3 "" H 7050 4600 60  0001 C CNN
	1    7050 4600
	0    -1   -1   0   
$EndComp
$Comp
L C C4
U 1 1 5351978E
P 6600 3150
F 0 "C4" H 6650 3250 50  0000 L CNN
F 1 "0.01uF" H 6650 3050 50  0000 L CNN
F 2 "" H 6600 3150 60  0001 C CNN
F 3 "" H 6600 3150 60  0001 C CNN
	1    6600 3150
	1    0    0    -1  
$EndComp
Text GLabel 7400 3400 2    60   Input ~ 0
VM
$Comp
L R R5
U 1 1 53519715
P 7150 3300
F 0 "R5" V 7230 3300 50  0000 C CNN
F 1 "1M" V 7150 3300 50  0000 C CNN
F 2 "" H 7150 3300 60  0001 C CNN
F 3 "" H 7150 3300 60  0001 C CNN
	1    7150 3300
	0    -1   -1   0   
$EndComp
$Comp
L C C6
U 1 1 535196F1
P 7150 3500
F 0 "C6" H 7200 3600 50  0000 L CNN
F 1 "0.1uF" H 7050 3400 50  0000 L CNN
F 2 "" H 7150 3500 60  0001 C CNN
F 3 "" H 7150 3500 60  0001 C CNN
	1    7150 3500
	0    -1   -1   0   
$EndComp
Text GLabel 6650 4700 2    60   Input ~ 0
VM
$Comp
L CONN_2 P3
U 1 1 5351909C
P 8000 4100
F 0 "P3" V 7950 4100 40  0000 C CNN
F 1 "CONN_2" V 8050 4100 40  0000 C CNN
F 2 "" H 8000 4100 60  0001 C CNN
F 3 "" H 8000 4100 60  0001 C CNN
	1    8000 4100
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P2
U 1 1 53519096
P 8000 3750
F 0 "P2" V 7950 3750 40  0000 C CNN
F 1 "CONN_2" V 8050 3750 40  0000 C CNN
F 2 "" H 8000 3750 60  0001 C CNN
F 3 "" H 8000 3750 60  0001 C CNN
	1    8000 3750
	1    0    0    -1  
$EndComp
Text GLabel 5600 5250 3    60   Input ~ 0
GND
Text GLabel 5450 5250 0    60   Input ~ 0
GND
Text GLabel 4050 3600 0    60   Input ~ 0
GND
$Comp
L R R2
U 1 1 53518FD0
P 4050 3350
F 0 "R2" V 4130 3350 50  0000 C CNN
F 1 "R" V 4050 3350 50  0000 C CNN
F 2 "" H 4050 3350 60  0001 C CNN
F 3 "" H 4050 3350 60  0001 C CNN
	1    4050 3350
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 53518FCC
P 4050 2850
F 0 "R1" V 4130 2850 50  0000 C CNN
F 1 "R" V 4050 2850 50  0000 C CNN
F 2 "" H 4050 2850 60  0001 C CNN
F 3 "" H 4050 2850 60  0001 C CNN
	1    4050 2850
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 53518FB1
P 4400 3000
F 0 "C1" H 4450 3100 50  0000 L CNN
F 1 "0.47uF" H 4450 2900 50  0000 L CNN
F 2 "" H 4400 3000 60  0001 C CNN
F 3 "" H 4400 3000 60  0001 C CNN
	1    4400 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 4550 4600 4550
Wire Wire Line
	3100 4750 4600 4750
$Comp
L CONN_2 P4
U 1 1 53595FBD
P 2900 5200
F 0 "P4" V 2850 5200 40  0000 C CNN
F 1 "CONN_2" V 2950 5200 40  0000 C CNN
F 2 "" H 2900 5200 60  0000 C CNN
F 3 "" H 2900 5200 60  0000 C CNN
	1    2900 5200
	-1   0    0    1   
$EndComp
$Comp
L CONN_2 P5
U 1 1 53595FCA
P 2900 5600
F 0 "P5" V 2850 5600 40  0000 C CNN
F 1 "CONN_2" V 2950 5600 40  0000 C CNN
F 2 "" H 2900 5600 60  0000 C CNN
F 3 "" H 2900 5600 60  0000 C CNN
	1    2900 5600
	-1   0    0    1   
$EndComp
$Comp
L CONN_2 P6
U 1 1 53595FD0
P 2900 6000
F 0 "P6" V 2850 6000 40  0000 C CNN
F 1 "CONN_2" V 2950 6000 40  0000 C CNN
F 2 "" H 2900 6000 60  0000 C CNN
F 3 "" H 2900 6000 60  0000 C CNN
	1    2900 6000
	-1   0    0    1   
$EndComp
Wire Wire Line
	3250 4550 3250 5100
Wire Wire Line
	3400 4650 3400 5500
Wire Wire Line
	3400 5500 3250 5500
Wire Wire Line
	3550 5900 3250 5900
Wire Wire Line
	3550 4750 3550 5900
Wire Wire Line
	3250 5300 2500 5300
Wire Wire Line
	2350 5700 3250 5700
Wire Wire Line
	2500 6100 3250 6100
Wire Wire Line
	2500 5300 2500 6100
Connection ~ 2500 5700
Text GLabel 2350 5700 0    60   Input ~ 0
GND
Text GLabel 2400 4550 0    60   Input ~ 0
Vcc
$Comp
L R R6
U 1 1 535963DA
P 2850 4550
F 0 "R6" V 2930 4550 40  0000 C CNN
F 1 "R" V 2857 4551 40  0000 C CNN
F 2 "~" V 2780 4550 30  0000 C CNN
F 3 "~" H 2850 4550 30  0000 C CNN
	1    2850 4550
	0    -1   -1   0   
$EndComp
Connection ~ 3250 4550
Wire Wire Line
	2400 4550 2600 4550
Connection ~ 3400 4650
Wire Wire Line
	3100 4650 4600 4650
$Comp
L R R7
U 1 1 53596633
P 2850 4650
F 0 "R7" V 2930 4650 40  0000 C CNN
F 1 "R" V 2857 4651 40  0000 C CNN
F 2 "~" V 2780 4650 30  0000 C CNN
F 3 "~" H 2850 4650 30  0000 C CNN
	1    2850 4650
	0    -1   -1   0   
$EndComp
$Comp
L R R8
U 1 1 53596639
P 2850 4750
F 0 "R8" V 2930 4750 40  0000 C CNN
F 1 "R" V 2857 4751 40  0000 C CNN
F 2 "~" V 2780 4750 30  0000 C CNN
F 3 "~" H 2850 4750 30  0000 C CNN
	1    2850 4750
	0    -1   -1   0   
$EndComp
Connection ~ 3550 4750
Wire Wire Line
	2600 4550 2600 4750
Connection ~ 2600 4650
$Comp
L R R9
U 1 1 53596842
P 4100 5100
F 0 "R9" V 4180 5100 40  0000 C CNN
F 1 "R" V 4107 5101 40  0000 C CNN
F 2 "~" V 4030 5100 30  0000 C CNN
F 3 "~" H 4100 5100 30  0000 C CNN
	1    4100 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 4350 4400 4850
Wire Wire Line
	4400 4850 4100 4850
Wire Wire Line
	4100 5350 4400 5350
Wire Wire Line
	4400 5350 4400 5150
Connection ~ 6650 1900
Wire Wire Line
	6300 1900 7150 1900
$Comp
L CONN_2 P7
U 1 1 53596D93
P 7850 1900
F 0 "P7" V 7800 1900 40  0000 C CNN
F 1 "CONN_2" V 7900 1900 40  0000 C CNN
F 2 "" H 7850 1900 60  0000 C CNN
F 3 "" H 7850 1900 60  0000 C CNN
	1    7850 1900
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P8
U 1 1 53596D99
P 8400 1900
F 0 "P8" V 8350 1900 40  0000 C CNN
F 1 "CONN_2" V 8450 1900 40  0000 C CNN
F 2 "" H 8400 1900 60  0000 C CNN
F 3 "" H 8400 1900 60  0000 C CNN
	1    8400 1900
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P9
U 1 1 53596D9F
P 8950 1900
F 0 "P9" V 8900 1900 40  0000 C CNN
F 1 "CONN_2" V 9000 1900 40  0000 C CNN
F 2 "" H 8950 1900 60  0000 C CNN
F 3 "" H 8950 1900 60  0000 C CNN
	1    8950 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 1900 7150 1800
Wire Wire Line
	7150 1800 8600 1800
Connection ~ 7500 1800
Connection ~ 8050 1800
Wire Wire Line
	7350 2000 8600 2000
Connection ~ 8050 2000
Wire Wire Line
	7350 2000 7350 2050
Connection ~ 7500 2000
Text GLabel 7350 2050 0    60   Input ~ 0
GND
Text GLabel 4800 5150 2    60   Input ~ 0
Vcc
$Comp
L CONN_3X2 P1
U 1 1 53596FF5
P 2950 4100
F 0 "P1" H 2950 4350 50  0000 C CNN
F 1 "CONN_3X2" V 2950 4150 40  0000 C CNN
F 2 "" H 2950 4100 60  0000 C CNN
F 3 "" H 2950 4100 60  0000 C CNN
	1    2950 4100
	1    0    0    -1  
$EndComp
Text GLabel 6650 4800 2    60   Input ~ 0
VM
Wire Wire Line
	6600 4700 6650 4700
Wire Wire Line
	6600 4800 6650 4800
$Comp
L CONN_2 P10
U 1 1 5359730D
P 4600 2000
F 0 "P10" V 4550 2000 40  0000 C CNN
F 1 "CONN_2" V 4650 2000 40  0000 C CNN
F 2 "" H 4600 2000 60  0000 C CNN
F 3 "" H 4600 2000 60  0000 C CNN
	1    4600 2000
	-1   0    0    1   
$EndComp
Wire Wire Line
	4950 2100 5100 2100
Wire Wire Line
	5100 2100 5100 2300
Connection ~ 5400 2300
$Comp
L LM7805 U2
U 1 1 535974E7
P 5900 1950
F 0 "U2" H 6050 1754 60  0000 C CNN
F 1 "LM7805" H 5900 2150 60  0000 C CNN
F 2 "~" H 5900 1950 60  0000 C CNN
F 3 "~" H 5900 1950 60  0000 C CNN
	1    5900 1950
	1    0    0    -1  
$EndComp
Text GLabel 6950 1500 0    60   Input ~ 0
GND
Text GLabel 5000 1500 0    60   Input ~ 0
GND
$Comp
L CP1 C5
U 1 1 535ADC9B
P 5000 1700
F 0 "C5" H 5050 1800 50  0000 L CNN
F 1 "470 uF" H 5050 1600 50  0000 L CNN
F 2 "~" H 5000 1700 60  0000 C CNN
F 3 "~" H 5000 1700 60  0000 C CNN
	1    5000 1700
	-1   0    0    1   
$EndComp
$Comp
L CP1 C7
U 1 1 535ADCB2
P 6950 1700
F 0 "C7" H 7000 1800 50  0000 L CNN
F 1 "100 uF" H 7000 1600 50  0000 L CNN
F 2 "~" H 6950 1700 60  0000 C CNN
F 3 "~" H 6950 1700 60  0000 C CNN
	1    6950 1700
	-1   0    0    1   
$EndComp
Connection ~ 5000 1900
Wire Wire Line
	6650 1900 6950 1900
Connection ~ 6950 1900
$Comp
L R R10
U 1 1 539DBE41
P 7050 4300
F 0 "R10" V 7130 4300 50  0000 C CNN
F 1 "R" V 7050 4300 50  0000 C CNN
F 2 "" H 7050 4300 60  0001 C CNN
F 3 "" H 7050 4300 60  0001 C CNN
	1    7050 4300
	0    -1   -1   0   
$EndComp
$Comp
L R R11
U 1 1 539DBE47
P 7050 4500
F 0 "R11" V 7130 4500 50  0000 C CNN
F 1 "R" V 7050 4500 50  0000 C CNN
F 2 "" H 7050 4500 60  0001 C CNN
F 3 "" H 7050 4500 60  0001 C CNN
	1    7050 4500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6800 4600 6800 4500
Wire Wire Line
	7300 4500 7300 4600
Wire Wire Line
	7300 4400 7300 4300
Connection ~ 6800 4300
Text GLabel 2550 3950 0    60   Input ~ 0
STEP
Text GLabel 2550 4050 0    60   Input ~ 0
DIR
Text GLabel 2550 4150 0    60   Input ~ 0
FAUL
Text GLabel 3350 3950 2    60   Input ~ 0
HOME
Text GLabel 3350 4150 2    60   Input ~ 0
SLEEP
Text GLabel 3350 4050 2    60   Input ~ 0
RESET
Wire Wire Line
	4400 4350 4600 4350
Text GLabel 4600 3650 0    60   Input ~ 0
STEP
Text GLabel 4600 3550 0    60   Input ~ 0
DIR
Text GLabel 4400 4350 0    60   Input ~ 0
FAUL
Text GLabel 4600 4250 0    60   Input ~ 0
HOME
Text GLabel 4600 3950 0    60   Input ~ 0
SLEEP
Text GLabel 4600 3850 0    60   Input ~ 0
RESET
$EndSCHEMATC
