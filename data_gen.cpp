/*
Weak: acetic acid and sodium bicarbonate
Strong: NaOH, HCl
Assume 1 liter of weak solution
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;

void acetic()
{
	float A, B, C;
	float Ka = 0.0000177;//value found online
	float pKa = -log10(Ka);// Should be about 4.7520

	ofstream myfile;//open text file
	myfile.open("acetic.txt");

	cout << "Molarity CH3CO2H: ";
	cin >> A;
	cout << "\nMolarity H3O+: ";
	cin >> B;
	cout << "\nMolarity NaOH: ";
	cin >> C;
	cout << "\n";

//Find initial pH
	cout << "PART 1!\n";
	int mL = 0;
	float x = (Ka + sqrt((Ka*Ka) -4*(A*Ka)))/2.0;//modified quad formula
	float pH = -log10(x);
	//string result = "(" + string(mL) + "," + string(pH) + ")";
	stringstream s;
	s << "(" << mL << "," << pH << ")";
	myfile << s.str() << "\n";

//Part 2:
	cout << "PART 2!\n";
	mL = 1;//add 1 mL NaOH
	//Assume 1 liter of acetic acid
	//Use mmol to make increments simpler
	float mmolC; //declared here to increase scope

	while((A-C) != 0.0)
	{
		float Vt = 1000 + mL;//Find total volume of solution
		float mmolA = A*Vt;//find mmol of acid
		mmolC = C*Vt;//Find mmol of base; mol NaOH = mol OH-
		pH = pKa + log10(mmolC/(mmolA-mmolC));
		//string result = "(" + string(mL) + "," + string(pH) + ")";
		stringstream s;
		s << "(" << mL << "," << pH << ")";
		myfile << s.str() << "\n";
		mL++;
	}

//Part 3:
	cout << "PART 3!\n";
	mL++;
	float Base = mmolC/(1000.0+mL);
	float Kb = (pow(11, Ka))/Ka;
	x = (Kb + sqrt((Kb*Kb) + 4.0*(Base*Kb)))/2.0;
	pH = 14.00 + log10(x);
	//string result = "(" + string(mL) + "," + string(pH) + ")";
	//myfile << result << "\n";
	s << "(" << mL << "," << pH << ")";
	myfile << s.str() << "\n";
	mL++;//needed because for loop inc after running on current value

//Part 4:
	cout << "PART 4!\n";
	for(; mL < (mL+4); mL++)
	{
		float excess = (mL*mmolC)-A;
		float y = excess/(1000.0+mL);//[OH-]
		pH = 14.0 + log10(y);
		stringstream s;
		s << "(" << mL << "," << pH << ")";
		myfile << s.str() << "\n";
	}

//Close file
myfile.close();
//End of function....
}

void bicarbonate()
{
	//do stuff
	//string result = "(" + string(mL) + "," + string(pH) + ")";
}

int main()
{
	int select;
	cout << "SELECT 1 FOR ACETIC ACID, OR 2 FOR SODIUM BICARBONATE: ";
	cin >> select;

	switch (select)
	{
		case 1:
			acetic();
			break;
		case 2:
			bicarbonate();
			break;
		default:
			cout << "ERROR IN SELECT\n";
			break;
	}

	cout << "PRESS ENTER TO TERMINATE PROGRAM\n";
	cin.get();
	return 0;
}
