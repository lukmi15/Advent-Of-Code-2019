#!/usr/bin/python2.7

#Python code
#Author(s)		: Lukas Mirow
#Date of creation	: 12/08/2019

module_masses = [78207,
89869,
145449,
73634,
78681,
81375,
131482,
126998,
50801,
115839,
77949,
53203,
146099,
56912,
59925,
132631,
115087,
89543,
123234,
108110,
109873,
81923,
124264,
87981,
106554,
147239,
73615,
72609,
129684,
84175,
64915,
98124,
74391,
55211,
120961,
119116,
148275,
89605,
115986,
120547,
50299,
137922,
78906,
145216,
80424,
122610,
61408,
97573,
127533,
116820,
76068,
77400,
117943,
85231,
102442,
62002,
58761,
56479,
98200,
85971,
73985,
88908,
82719,
120604,
83378,
88241,
122574,
76731,
99810,
137548,
102617,
105352,
137585,
83238,
118817,
149419,
107629,
63893,
56049,
70693,
83844,
76413,
87021,
90259,
124289,
102527,
139625,
106607,
120241,
101098,
66142,
96591,
82277,
142297,
116671,
131881,
94861,
79741,
73561,
115214]

def calc_fuel_for_mass(mass):
	return int(mass / 3) - 2

def recurse_fuel_for_fuel(fuel_mass):
	fuel_for_fuel = 0
	fuel_to_add = fuel_mass
	while (True):
		fuel_to_add = calc_fuel_for_mass(fuel_to_add)
		if (fuel_to_add > 0):
			fuel_for_fuel += fuel_to_add
		else:
			break
	return fuel_for_fuel

total_fuel = 0
for module_mass in module_masses:
	fuel_for_module = calc_fuel_for_mass(module_mass)
	fuel_for_fuel = recurse_fuel_for_fuel(fuel_for_module)
	total_fuel += fuel_for_module + fuel_for_fuel

print total_fuel
