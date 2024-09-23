#include <stdio.h>
#include <stdlib.h>
enum bool {
	off, on
};
typedef enum bool bool;

struct car{
	char input, light;
	int speed, rtemp, etemp;
	bool AC, ETC;
}c;

void MAIN_SCREEN (char *input){
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");
	scanf (" %c",input);
}

void Sensors_set_menu (char *menu){
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color.\n");
	printf("c. Set the room temperature (Temperature Sensor)\n");
	printf("d. Set the engine temperature (Engine Temperature Sensor)\n");
	scanf (" %c",menu);
}

void traffic_light (char *light, int *speed){
	printf ("Enter traffic light: ");
	scanf (" %c",light);
	switch (*light){
	case 'g':
	case 'G':
		*speed = 100;
		break;
	case 'o':
	case 'O':
		*speed = 30;
		break;
	case 'r':
	case 'R':
		*speed = 0;
		break;
	}
}

void room_temperature (int *rtemp, bool *AC ){
	printf ("Enter room temperature: ");
	scanf (" %d",rtemp);
	if (*rtemp < 10 || *rtemp > 30){
		*rtemp = 20;
		*AC = on;
	}else {
		*AC = off;
	}
}

void engine_temperature (int *etemp, bool *ETC){
	printf ("Enter engine temperature: ");
	scanf (" %d",etemp);
	if (*etemp < 100 || *etemp > 150){
		*etemp = 125;
		*ETC = on;
	}else {
		*ETC = off;
	}
}

void speed_checker (int speed, bool *AC, int *rtemp, bool *ETC, int *etemp){
	if (speed == 30){
		*AC = on;
		*rtemp *= (float) 5/4 + 1;
		*ETC = on;
		*etemp *= (float) 5/4 + 1;
	}
}

void Display (char input, bool AC, int speed, int rtemp, bool ETC, int etemp){
	if (input == 'a'){
		printf ("\nEngine is ON\n");
	}else {
		printf ("\nEngine is OFF\n");
	}
	if (AC == off){
		printf ("AC is off\n");
	}else{
		printf ("AC is on\n");
	}
	printf ("Vehicle Speed = %d Km/hr\n",speed);
	printf ("Room Temperature = %d C\n",rtemp);
	if (ETC == off){
		printf ("Engine Temperature Controller is off\n");
	}else{
		printf ("Engine Temperature Controller is on\n");
	}
	printf ("Engine Temperature = %d C\n\n",etemp);
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	char menu;
	c.speed = 50;
	c.rtemp = 35;
	c.etemp = 90;
	c.ETC = off;
	c.AC = off;

	do{
		MAIN_SCREEN (&c.input);
		switch (c.input){
		case 'c' :
			printf ("Quit the system\n\n");
			return 0;
			break;
		case 'a' :
			printf ("Turn on the vehicle engine\n\n");
			break;
		case 'b' :
			printf ("Turn off the vehicle engine\n\n");
			break;
		}
		while (c.input != 'b'){
			Sensors_set_menu (&menu);
			switch (menu){
			case 'a':
				c.input = 'b';
				break;
			case 'b':
				traffic_light (&c.light, &c.speed);
				speed_checker (c.speed, &c.AC, &c.rtemp,  &c.ETC, &c.etemp);
				Display (c.input, c.AC, c.speed, c.rtemp, c.ETC, c.etemp);
				break;
			case 'c':
				room_temperature (&c.rtemp, &c.AC);
				Display (c.input, c.AC, c.speed, c.rtemp, c.ETC, c.etemp);
				break;
			case 'd':
				engine_temperature (&c.etemp, &c.ETC);
				Display (c.input, c.AC, c.speed, c.rtemp, c.ETC, c.etemp);
				break;
			}
		}
	}while (c.input == 'b');

	return EXIT_SUCCESS;
}
