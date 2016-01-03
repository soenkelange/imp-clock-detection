#include <math.h>
#include <iostream>
#include <stdio.h>

using namespace std;

#define PI 3.14159265


double winkel(int z1, int z2, int z3){
	//Punnkt1, Punkt2, Mitte müssen an die funktion übergeben werden

		int zahl1 = z1;
		int zahl2 = z2;
		int mitte = z3; 
		double a,b, erg;
		
		a = zahl1 - mitte;  // ausrechnen des ersten zeigers 
		b = zahl2 - mitte;  // ausrechnen des zweiten zeigers 

	
		cout<<"a "<<a<< endl;
		cout<<"b "<<b<< endl;

		if(a<0){        //falls die stecke negativ ist muss sie *-1 multipliziert werden 
			a=a*-1;
			cout<<"a "<<a<< endl;
		}

	   
		if(b<0){         //falls die stecke negativ ist muss sie *-1 multipliziert werden 
			b=b*-1;
			cout<<"b "<<b<< endl;
		}
		
		erg = asin(a/b);

		cout<<"Ergebinis: "<< erg<< endl;
		erg = erg * PI / 180.0;
	/*
		result = atan2 (a,b) ;
		cout<<"Result1: "<< result<< endl;
		result = (result )* PI / 180.0;
		cout<<"Result2: "<< result<< endl;
	*/
		
		return(erg);
		
}

int main ()
{

	int gzeiger = 2; //2 stunde
	int kzeiger = 5; //25 minuten

  double erg = winkel(gzeiger,kzeiger,0);
  
  cout<<"Ergebnis des Winkels:" <<erg;

  getchar();

  return(0);
}