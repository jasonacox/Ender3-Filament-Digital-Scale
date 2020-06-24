EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L ardruino_rur:TM1637Display U3
U 1 1 5EF2C6FC
P 5000 2850
F 0 "U3" H 5578 2901 50  0000 L CNN
F 1 "TM1637Display" H 5578 2810 50  0000 L CNN
F 2 "" H 5000 2850 50  0001 C CNN
F 3 "" H 5000 2850 50  0001 C CNN
	1    5000 2850
	1    0    0    -1  
$EndComp
$Comp
L ardruino_rur:ATTINY85 U1
U 1 1 5EF2DCD8
P 5450 4050
F 0 "U1" V 4856 4050 60  0000 C CNN
F 1 "ATTINY85" V 4962 4050 60  0000 C CNN
F 2 "" H 5450 4050 60  0000 C CNN
F 3 "" H 5450 4050 60  0000 C CNN
	1    5450 4050
	0    1    1    0   
$EndComp
$Comp
L Device:CP C1
U 1 1 5EF32E57
P 3700 4200
F 0 "C1" H 3818 4246 50  0000 L CNN
F 1 "100uF" H 3818 4155 50  0000 L CNN
F 2 "" H 3738 4050 50  0001 C CNN
F 3 "~" H 3700 4200 50  0001 C CNN
	1    3700 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 3950 6850 3950
Wire Wire Line
	6850 3950 6850 3850
Wire Wire Line
	5750 4150 6950 4150
Wire Wire Line
	6950 4150 6950 3850
Wire Wire Line
	6450 3750 6450 3450
Wire Wire Line
	4450 3000 4450 3200
Wire Wire Line
	4450 3200 5750 3200
Wire Wire Line
	5750 3200 5750 3750
Connection ~ 5750 3750
Wire Wire Line
	5150 3950 4100 3950
Wire Wire Line
	4100 3950 4100 2700
Wire Wire Line
	4100 2700 4450 2700
Wire Wire Line
	5150 4150 4300 4150
Wire Wire Line
	4300 4150 4300 2800
Wire Wire Line
	4300 2800 4450 2800
Wire Wire Line
	5150 4350 4400 4350
Wire Wire Line
	4400 4350 4400 2900
Wire Wire Line
	4400 2900 4450 2900
Wire Wire Line
	5750 3750 6450 3750
$Comp
L power:+5V #PWR?
U 1 1 5EF4577D
P 3500 4050
F 0 "#PWR?" H 3500 3900 50  0001 C CNN
F 1 "+5V" V 3515 4178 50  0000 L CNN
F 2 "" H 3500 4050 50  0001 C CNN
F 3 "" H 3500 4050 50  0001 C CNN
	1    3500 4050
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5EF47556
P 3500 4350
F 0 "#PWR?" H 3500 4100 50  0001 C CNN
F 1 "GND" V 3505 4222 50  0000 R CNN
F 2 "" H 3500 4350 50  0001 C CNN
F 3 "" H 3500 4350 50  0001 C CNN
	1    3500 4350
	0    1    1    0   
$EndComp
Wire Wire Line
	3500 4050 3700 4050
Wire Wire Line
	3500 4350 3700 4350
Wire Wire Line
	4400 4350 3700 4350
Connection ~ 4400 4350
Connection ~ 3700 4350
Wire Wire Line
	4400 4350 4400 5000
Wire Wire Line
	3700 4050 3800 4050
Wire Wire Line
	3800 4050 3800 3000
Wire Wire Line
	3800 3000 4450 3000
Connection ~ 3700 4050
Connection ~ 4450 3000
Wire Wire Line
	7300 3450 7300 5000
Connection ~ 6450 3750
Wire Wire Line
	4400 5000 5850 5000
$Comp
L Switch:SW_Push SW1
U 1 1 5EF3ED53
P 5850 4700
F 0 "SW1" V 5759 4848 50  0000 L CNN
F 1 "SW_Push" V 5850 4848 50  0000 L CNN
F 2 "" H 5850 4900 50  0001 C CNN
F 3 "~" H 5850 4900 50  0001 C CNN
F 4 "Tare" V 5941 4848 50  0000 L CNN "Desc"
	1    5850 4700
	0    1    1    0   
$EndComp
Wire Wire Line
	5850 4350 6000 4350
Wire Wire Line
	5750 4350 5850 4350
Connection ~ 5850 4350
Wire Wire Line
	5850 4350 5850 4500
Wire Wire Line
	5850 4900 5850 5000
Connection ~ 5850 5000
Wire Wire Line
	5850 5000 7300 5000
$Comp
L hx711:LC? LC??
U 1 1 5EF62F73
P 6500 2050
F 0 "LC??" H 6425 2265 50  0001 C CNN
F 1 "LC?" H 6425 2174 50  0001 C CNN
F 2 "" H 6500 2050 50  0001 C CNN
F 3 "" H 6500 2050 50  0001 C CNN
	1    6500 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 2500 6600 2350
Wire Wire Line
	6500 2350 6500 2600
Wire Wire Line
	6500 2600 6950 2600
Wire Wire Line
	6850 2700 6400 2700
Wire Wire Line
	6400 2700 6400 2350
Wire Wire Line
	6300 2350 6300 3250
Wire Wire Line
	6300 3250 6500 3250
$Comp
L Device:R R1
U 1 1 5EF339A8
P 6150 4400
F 0 "R1" V 5943 4400 50  0000 C CNN
F 1 "61K" V 6034 4400 50  0000 C CNN
F 2 "" V 6080 4400 50  0001 C CNN
F 3 "~" H 6150 4400 50  0001 C CNN
	1    6150 4400
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 4350 6000 4400
Wire Wire Line
	6300 4400 6450 4400
Wire Wire Line
	6950 2600 6950 2850
Wire Wire Line
	6850 2700 6850 2850
$Comp
L hx711:HX711 U2
U 1 1 5EF3125B
P 6900 3450
F 0 "U2" V 6709 3006 50  0000 R CNN
F 1 "HX711" V 6800 3006 50  0000 R CNN
F 2 "ADC Weight Sensor Module" V 6891 3006 50  0000 R CNN
F 3 "" H 6600 3800 50  0001 C CNN
	1    6900 3450
	0    -1   1    0   
$EndComp
Wire Wire Line
	7300 3250 7300 2500
Wire Wire Line
	7300 2500 6600 2500
Wire Wire Line
	6450 3750 6450 4400
$EndSCHEMATC
