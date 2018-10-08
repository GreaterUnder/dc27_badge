EESchema Schematic File Version 4
LIBS:DC27-badge-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Driver_LED:IS31FL736 U?
U 1 1 5BD866E6
P 5750 3450
AR Path="/5BA1B02E/5BD866E6" Ref="U?"  Part="1" 
AR Path="/5BD866AF/5BD866E6" Ref="U2"  Part="1" 
F 0 "U2" H 5750 3450 50  0000 C CNN
F 1 "IS31FL736" H 5750 3300 50  0000 C CNN
F 2 "dc27-sao-extras:QFN-40-1EP_5x5mm_P0.4mm_EP3.5x3.5mm" H 5700 1600 50  0001 C CNN
F 3 "http://www.issi.com/WW/pdf/IS31FL3216.pdf" H 4120 4590 50  0001 C CNN
	1    5750 3450
	1    0    0    -1  
$EndComp
Text GLabel 4650 4100 0    50   Output ~ 0
SW12
Wire Wire Line
	4750 4100 4650 4100
Text GLabel 4650 3950 0    50   Output ~ 0
SW11
Text GLabel 4650 3800 0    50   Output ~ 0
SW10
Text GLabel 4650 3650 0    50   Output ~ 0
SW9
Text GLabel 4650 3500 0    50   Output ~ 0
SW8
Text GLabel 4650 3350 0    50   Output ~ 0
SW7
Text GLabel 4650 3200 0    50   Output ~ 0
SW6
Text GLabel 4650 3050 0    50   Output ~ 0
SW5
Text GLabel 4650 2900 0    50   Output ~ 0
SW4
Text GLabel 4650 2750 0    50   Output ~ 0
SW3
Text GLabel 4650 2600 0    50   Output ~ 0
SW2
Text GLabel 4650 2450 0    50   Output ~ 0
SW1
Wire Wire Line
	4750 3950 4650 3950
Wire Wire Line
	4650 3800 4750 3800
Wire Wire Line
	4750 3650 4650 3650
Wire Wire Line
	4650 3500 4750 3500
Wire Wire Line
	4750 3350 4650 3350
Wire Wire Line
	4650 3200 4750 3200
Wire Wire Line
	4650 2900 4750 2900
Wire Wire Line
	4750 2750 4650 2750
Wire Wire Line
	4650 2600 4750 2600
Wire Wire Line
	4750 2450 4650 2450
Text GLabel 6950 3000 2    50   Output ~ 0
CS4
Text GLabel 6950 2850 2    50   Output ~ 0
CS3
Text GLabel 6950 2700 2    50   Output ~ 0
CS2
Text GLabel 6950 2550 2    50   Output ~ 0
CS1
Text GLabel 6950 3750 2    50   Output ~ 0
CS8
Text GLabel 6950 3600 2    50   Output ~ 0
CS7
Text GLabel 6950 3450 2    50   Output ~ 0
CS6
Text GLabel 6950 3300 2    50   Output ~ 0
CS5
Wire Wire Line
	6950 3750 6800 3750
Wire Wire Line
	6800 3600 6950 3600
Wire Wire Line
	6950 3450 6800 3450
Wire Wire Line
	6800 3300 6950 3300
Wire Wire Line
	6950 3000 6800 3000
Wire Wire Line
	6800 2850 6950 2850
Wire Wire Line
	6950 2700 6800 2700
Wire Wire Line
	6800 2550 6950 2550
NoConn ~ 6800 3950
Text GLabel 1850 1250 0    50   Input ~ 0
VCC5V
$Comp
L Device:C C1
U 1 1 5BDAD420
P 2100 1450
F 0 "C1" H 2215 1496 50  0000 L CNN
F 1 "0.47uF" H 2215 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2138 1300 50  0001 C CNN
F 3 "~" H 2100 1450 50  0001 C CNN
	1    2100 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5BDAD49F
P 2700 1450
F 0 "C2" H 2815 1496 50  0000 L CNN
F 1 "0.1uF" H 2815 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2738 1300 50  0001 C CNN
F 3 "~" H 2700 1450 50  0001 C CNN
	1    2700 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 1250 2100 1250
Wire Wire Line
	2100 1250 2100 1300
Wire Wire Line
	2100 1250 2700 1250
Wire Wire Line
	2700 1250 2700 1300
Connection ~ 2100 1250
$Comp
L power:GND #PWR04
U 1 1 5BDADD7C
P 2100 1800
F 0 "#PWR04" H 2100 1550 50  0001 C CNN
F 1 "GND" H 2105 1627 50  0000 C CNN
F 2 "" H 2100 1800 50  0001 C CNN
F 3 "" H 2100 1800 50  0001 C CNN
	1    2100 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5BDADD94
P 2700 1800
F 0 "#PWR05" H 2700 1550 50  0001 C CNN
F 1 "GND" H 2705 1627 50  0000 C CNN
F 2 "" H 2700 1800 50  0001 C CNN
F 3 "" H 2700 1800 50  0001 C CNN
	1    2700 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 1600 2100 1800
Wire Wire Line
	2700 1600 2700 1800
Text GLabel 3100 1250 2    50   Output ~ 0
PVCC1
Wire Wire Line
	2700 1250 3100 1250
Connection ~ 2700 1250
Text GLabel 1850 2250 0    50   Input ~ 0
VCC5V
$Comp
L Device:C C3
U 1 1 5BDAF5E8
P 2100 2450
F 0 "C3" H 2215 2496 50  0000 L CNN
F 1 "0.47uF" H 2215 2405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2138 2300 50  0001 C CNN
F 3 "~" H 2100 2450 50  0001 C CNN
	1    2100 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5BDAF5EE
P 2700 2450
F 0 "C4" H 2815 2496 50  0000 L CNN
F 1 "0.1uF" H 2815 2405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2738 2300 50  0001 C CNN
F 3 "~" H 2700 2450 50  0001 C CNN
	1    2700 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 2250 2100 2250
Wire Wire Line
	2100 2250 2100 2300
Wire Wire Line
	2100 2250 2700 2250
Wire Wire Line
	2700 2250 2700 2300
Connection ~ 2100 2250
$Comp
L power:GND #PWR06
U 1 1 5BDAF5F9
P 2100 2800
F 0 "#PWR06" H 2100 2550 50  0001 C CNN
F 1 "GND" H 2105 2627 50  0000 C CNN
F 2 "" H 2100 2800 50  0001 C CNN
F 3 "" H 2100 2800 50  0001 C CNN
	1    2100 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5BDAF5FF
P 2700 2800
F 0 "#PWR07" H 2700 2550 50  0001 C CNN
F 1 "GND" H 2705 2627 50  0000 C CNN
F 2 "" H 2700 2800 50  0001 C CNN
F 3 "" H 2700 2800 50  0001 C CNN
	1    2700 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 2600 2100 2800
Wire Wire Line
	2700 2600 2700 2800
Text GLabel 3100 2250 2    50   Output ~ 0
PVCC2
Wire Wire Line
	2700 2250 3100 2250
Connection ~ 2700 2250
Text GLabel 1850 3250 0    50   Input ~ 0
VCC5V
$Comp
L Device:C C5
U 1 1 5BDAFD53
P 2100 3450
F 0 "C5" H 2215 3496 50  0000 L CNN
F 1 "0.47uF" H 2215 3405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2138 3300 50  0001 C CNN
F 3 "~" H 2100 3450 50  0001 C CNN
	1    2100 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5BDAFD59
P 2700 3450
F 0 "C6" H 2815 3496 50  0000 L CNN
F 1 "0.1uF" H 2815 3405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2738 3300 50  0001 C CNN
F 3 "~" H 2700 3450 50  0001 C CNN
	1    2700 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 3250 2100 3250
Wire Wire Line
	2100 3250 2100 3300
Wire Wire Line
	2100 3250 2700 3250
Wire Wire Line
	2700 3250 2700 3300
Connection ~ 2100 3250
$Comp
L power:GND #PWR09
U 1 1 5BDAFD64
P 2100 3800
F 0 "#PWR09" H 2100 3550 50  0001 C CNN
F 1 "GND" H 2105 3627 50  0000 C CNN
F 2 "" H 2100 3800 50  0001 C CNN
F 3 "" H 2100 3800 50  0001 C CNN
	1    2100 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5BDAFD6A
P 2700 3800
F 0 "#PWR010" H 2700 3550 50  0001 C CNN
F 1 "GND" H 2705 3627 50  0000 C CNN
F 2 "" H 2700 3800 50  0001 C CNN
F 3 "" H 2700 3800 50  0001 C CNN
	1    2700 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 3600 2100 3800
Wire Wire Line
	2700 3600 2700 3800
Text GLabel 3100 3250 2    50   Output ~ 0
AVCC
Wire Wire Line
	2700 3250 3100 3250
Connection ~ 2700 3250
Text GLabel 1850 4250 0    50   Input ~ 0
VCC5V
$Comp
L Device:C C7
U 1 1 5BDAFD76
P 2100 4450
F 0 "C7" H 2215 4496 50  0000 L CNN
F 1 "0.47uF" H 2215 4405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2138 4300 50  0001 C CNN
F 3 "~" H 2100 4450 50  0001 C CNN
	1    2100 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 5BDAFD7C
P 2700 4450
F 0 "C8" H 2815 4496 50  0000 L CNN
F 1 "0.1uF" H 2815 4405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2738 4300 50  0001 C CNN
F 3 "~" H 2700 4450 50  0001 C CNN
	1    2700 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 4250 2100 4250
Wire Wire Line
	2100 4250 2100 4300
Wire Wire Line
	2100 4250 2700 4250
Wire Wire Line
	2700 4250 2700 4300
Connection ~ 2100 4250
$Comp
L power:GND #PWR012
U 1 1 5BDAFD87
P 2100 4800
F 0 "#PWR012" H 2100 4550 50  0001 C CNN
F 1 "GND" H 2105 4627 50  0000 C CNN
F 2 "" H 2100 4800 50  0001 C CNN
F 3 "" H 2100 4800 50  0001 C CNN
	1    2100 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5BDAFD8D
P 2700 4800
F 0 "#PWR013" H 2700 4550 50  0001 C CNN
F 1 "GND" H 2705 4627 50  0000 C CNN
F 2 "" H 2700 4800 50  0001 C CNN
F 3 "" H 2700 4800 50  0001 C CNN
	1    2700 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 4600 2100 4800
Wire Wire Line
	2700 4600 2700 4800
Text GLabel 3100 4250 2    50   Output ~ 0
DVCC
Wire Wire Line
	2700 4250 3100 4250
Connection ~ 2700 4250
Text GLabel 5450 1850 1    50   Input ~ 0
PVCC1
Wire Wire Line
	5450 1850 5450 2100
Text GLabel 5650 1850 1    50   Input ~ 0
PVCC2
Wire Wire Line
	5650 1850 5650 2100
$Comp
L power:GND #PWR03
U 1 1 5BDB2F4A
P 6050 1150
F 0 "#PWR03" H 6050 900 50  0001 C CNN
F 1 "GND" H 6055 977 50  0000 C CNN
F 2 "" H 6050 1150 50  0001 C CNN
F 3 "" H 6050 1150 50  0001 C CNN
	1    6050 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 2100 5850 1900
Wire Wire Line
	5850 1900 5950 1900
Connection ~ 5950 1900
Wire Wire Line
	5950 1900 5950 2100
$Comp
L Device:R_US R5
U 1 1 5BDB589A
P 7100 4250
F 0 "R5" V 7200 4250 50  0000 C CNN
F 1 "20K" V 7300 4250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7140 4240 50  0001 C CNN
F 3 "~" H 7100 4250 50  0001 C CNN
	1    7100 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	6800 4250 6950 4250
$Comp
L power:GND #PWR011
U 1 1 5BDB67EB
P 7450 4300
F 0 "#PWR011" H 7450 4050 50  0001 C CNN
F 1 "GND" H 7455 4127 50  0000 C CNN
F 2 "" H 7450 4300 50  0001 C CNN
F 3 "" H 7450 4300 50  0001 C CNN
	1    7450 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 4250 7450 4250
Wire Wire Line
	7450 4250 7450 4300
Text GLabel 1900 5200 0    50   Input ~ 0
VCC3V3
$Comp
L Device:C C9
U 1 1 5BDB89D2
P 2100 5500
F 0 "C9" H 2215 5546 50  0000 L CNN
F 1 "C" H 2215 5455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2138 5350 50  0001 C CNN
F 3 "~" H 2100 5500 50  0001 C CNN
	1    2100 5500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5BDB8A02
P 2100 5750
F 0 "#PWR015" H 2100 5500 50  0001 C CNN
F 1 "GND" H 2105 5577 50  0000 C CNN
F 2 "" H 2100 5750 50  0001 C CNN
F 3 "" H 2100 5750 50  0001 C CNN
	1    2100 5750
	1    0    0    -1  
$EndComp
NoConn ~ 6800 3150
$Comp
L power:GND #PWR014
U 1 1 5BDBBD80
P 5600 5600
F 0 "#PWR014" H 5600 5350 50  0001 C CNN
F 1 "GND" H 5605 5427 50  0000 C CNN
F 2 "" H 5600 5600 50  0001 C CNN
F 3 "" H 5600 5600 50  0001 C CNN
	1    5600 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 4850 5600 5200
Wire Wire Line
	6350 5200 6000 5200
Connection ~ 5600 5200
Wire Wire Line
	6000 4850 6000 5200
Connection ~ 6000 5200
$Comp
L Device:R_US R6
U 1 1 5BDBF4DB
P 5100 5150
F 0 "R6" H 5168 5196 50  0000 L CNN
F 1 "100k" H 5168 5105 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5030 5150 50  0001 C CNN
F 3 "~" H 5100 5150 50  0001 C CNN
	1    5100 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 5200 5600 5500
Wire Wire Line
	5100 4850 5100 5000
Wire Wire Line
	5100 5300 5100 5500
Wire Wire Line
	5100 5500 5600 5500
Connection ~ 5600 5500
Wire Wire Line
	5600 5500 5600 5600
Wire Wire Line
	5750 4850 5750 5200
Wire Wire Line
	5600 5200 5750 5200
Connection ~ 5750 5200
Wire Wire Line
	5750 5200 5850 5200
Wire Wire Line
	5850 4850 5850 5200
Connection ~ 5850 5200
Wire Wire Line
	5850 5200 6000 5200
Text GLabel 5250 1850 1    50   Input ~ 0
AVCC
Text GLabel 5350 1850 1    50   Input ~ 0
DVCC
Wire Wire Line
	5350 1850 5350 2100
Wire Wire Line
	5250 2100 5250 1850
Text Notes 1600 950  2    50   ~ 10
Decoupling\n
Text Notes 8550 1000 2    50   ~ 10
I2C Bus Pullups
Text GLabel 6100 2000 1    50   BiDi ~ 0
SDA_LED
Wire Wire Line
	6100 2000 6100 2100
Text GLabel 6200 2000 1    50   BiDi ~ 0
SCL_LED
Text GLabel 6300 2000 1    50   BiDi ~ 0
SCB_LED
Wire Wire Line
	6200 2000 6200 2100
Wire Wire Line
	6300 2000 6300 2100
Text GLabel 6450 2000 1    50   BiDi ~ 0
INTB_LED
Wire Wire Line
	6450 2000 6450 2100
Wire Wire Line
	5950 1050 6050 1050
Wire Wire Line
	6050 1050 6050 1150
Wire Wire Line
	5950 1050 5950 1900
Text GLabel 9750 1850 2    50   BiDi ~ 0
SDA_LED
Text GLabel 9750 2100 2    50   BiDi ~ 0
SCL_LED
Text GLabel 9750 2350 2    50   BiDi ~ 0
SDB_LED
Text GLabel 9750 2600 2    50   BiDi ~ 0
INTB_LED
Text GLabel 2700 5200 2    50   Output ~ 0
VIO
Wire Wire Line
	2100 5650 2100 5750
Text GLabel 7400 4100 2    50   Input ~ 0
VIO
Wire Wire Line
	6800 4100 7400 4100
Text GLabel 8500 1150 0    50   Input ~ 0
VCC3V3
$Comp
L Device:R R1
U 1 1 5BDEF0A9
P 8700 1450
F 0 "R1" H 8770 1496 50  0000 L CNN
F 1 "100k" H 8770 1405 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8630 1450 50  0001 C CNN
F 3 "~" H 8700 1450 50  0001 C CNN
	1    8700 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5BDEF0EE
P 9050 1450
F 0 "R2" H 9120 1496 50  0000 L CNN
F 1 "1k" H 9120 1405 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8980 1450 50  0001 C CNN
F 3 "~" H 9050 1450 50  0001 C CNN
	1    9050 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5BDEF141
P 9450 1450
F 0 "R3" H 9520 1496 50  0000 L CNN
F 1 "1k" H 9520 1405 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9380 1450 50  0001 C CNN
F 3 "~" H 9450 1450 50  0001 C CNN
	1    9450 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 1150 8700 1150
Wire Wire Line
	8700 1150 8700 1300
Wire Wire Line
	8700 1150 9050 1150
Wire Wire Line
	9050 1150 9050 1300
Connection ~ 8700 1150
Wire Wire Line
	9050 1150 9450 1150
Wire Wire Line
	9450 1150 9450 1300
Connection ~ 9050 1150
Text GLabel 8550 1850 0    50   BiDi ~ 0
SDA_MCU
Text GLabel 8550 2100 0    50   BiDi ~ 0
SCL_MCU
Text GLabel 8550 2350 0    50   BiDi ~ 0
SDB_MCU
Text GLabel 8550 2600 0    50   BiDi ~ 0
INTB_MCU
Wire Wire Line
	8550 1850 9050 1850
Wire Wire Line
	9750 2100 9450 2100
Wire Wire Line
	9750 2350 9050 2350
Wire Wire Line
	9050 1600 9050 1850
Connection ~ 9050 1850
Wire Wire Line
	9050 1850 9750 1850
Wire Wire Line
	9450 1600 9450 2100
Connection ~ 9450 2100
Wire Wire Line
	9450 2100 8550 2100
$Comp
L Device:R R4
U 1 1 5BE14E00
P 9050 2950
F 0 "R4" H 9120 2996 50  0000 L CNN
F 1 "100k" H 9120 2905 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8980 2950 50  0001 C CNN
F 3 "~" H 9050 2950 50  0001 C CNN
	1    9050 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 2800 9050 2350
Connection ~ 9050 2350
Wire Wire Line
	9050 2350 8550 2350
$Comp
L power:GND #PWR08
U 1 1 5BE17376
P 9050 3250
F 0 "#PWR08" H 9050 3000 50  0001 C CNN
F 1 "GND" H 9055 3077 50  0000 C CNN
F 2 "" H 9050 3250 50  0001 C CNN
F 3 "" H 9050 3250 50  0001 C CNN
	1    9050 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 3100 9050 3250
Wire Wire Line
	8700 1600 8700 2600
Wire Wire Line
	8550 2600 8700 2600
Connection ~ 8700 2600
Wire Wire Line
	8700 2600 9750 2600
Wire Wire Line
	4650 3050 4750 3050
Wire Wire Line
	6350 4850 6350 5200
Wire Wire Line
	1900 5200 2100 5200
Wire Wire Line
	2100 5350 2100 5200
Connection ~ 2100 5200
Wire Wire Line
	2100 5200 2700 5200
Text Notes 7350 7500 0    50   ~ 0
DC 27 Badge - Team Ides - John Adams / Bill Paul
$EndSCHEMATC
