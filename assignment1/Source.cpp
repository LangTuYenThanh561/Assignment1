#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

const int MADBEAR = 1, LORDLUPIN = 3, ELF = 4, TROLL = 5, SHAMAN = 6, VAJSH = 7, EXCALIBUR = 8, MYTHRIL = 9, EXCALIPOOR = 10, MUSHMARIO = 11;
const int BANDIT = 2, MUSHFIB = 12, MUSHGHOST = 13, MUSHKNIGHT = 14, REMEDY = 15, MAIDENKISS = 16, PHOENIXDOWN = 17, MERLIN = 18, ABYSS = 19;
const int GUINEVERE = 20, LIGHTWING = 21, ODIN = 22, DRAGONSWORD = 23, BROWSER = 99, BROWSERLOST = 0;
const int EVENT_SIZE = 500;
const int MAX_CHARACTER_EACH_LINE = 500;

struct knight
{
	int HP  ;
	int level;
	int remedy;
	int maidenkiss;
	int phoenixdown;
};

// read data from input file to corresponding variables
// return 1 if successfully done, otherwise return 0
void PrintKnight(knight kn)
{
	cout << kn.HP << " " << kn.level << " " << kn.remedy << " " << kn.maidenkiss << " " << kn.phoenixdown << endl;
}
int readFile(const char* filename, knight& theKnight, int& nEvent, int* arrEvent)
{
	const char* file_name = "input.txt";
	FILE* f = 0;
	char* str = new char[MAX_CHARACTER_EACH_LINE];
	int num;

	f = fopen(file_name, "r");
	if (f == NULL)	//file not found || cannot read
		return 0;

	fgets(str, MAX_CHARACTER_EACH_LINE, f);
	if (feof(f))
		return 0;

	int start = 0;
	int len = strlen(str);
	// read HP
	while (start < len && str[start] == ' ')
		start++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0') {
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.HP = num;
	if (theKnight.HP < 1 || theKnight.HP > 999)
		return 0;

	// read level
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0') {
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.level = num;
	if (theKnight.level < 1 || theKnight.level > 10)
		return 0;

	// read remedy
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0') {
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.remedy = num;
	if (theKnight.remedy < 0 || theKnight.remedy > 99)
		return 0;

	// read maidenkiss
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0') {
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.maidenkiss = num;
	if (theKnight.maidenkiss < 0 || theKnight.maidenkiss > 99)
		return 0;

	// read phoenixdown
	while (start < len && (str[start] > '9' || str[start] < '0'))
		start++;
	num = 0;
	while (start < len && str[start] <= '9' && str[start] >= '0') {
		num = num * 10 + str[start] - '0';
		start++;
	}
	theKnight.phoenixdown = num;
	if (theKnight.phoenixdown < 0 || theKnight.phoenixdown > 99)
		return 0;

	// read events
	nEvent = 0;
	while (1) {
		if (feof(f))
			break;
		fgets(str, MAX_CHARACTER_EACH_LINE, f);
		if (str == NULL)
			break;
		start = 0;
		len = strlen(str);
		// cout << "\'" << str << "\'" << "\t" << len << endl;
		while (start < len) {
			while (start < len && (str[start] > '9' || str[start] < '0'))
				start++;
			if (start >= len)
				break;
			arrEvent[nEvent] = 0;
			while (start < len && str[start] <= '9' && str[start] >= '0') {
				arrEvent[nEvent] = arrEvent[nEvent] * 10 + str[start] - '0';
				start++;
			}
			nEvent++;
		}
		delete[] str;
	}
	fclose(f);
	return 1;
}

void display(int* nOut)
{
	if (nOut)
		cout << *nOut;
	else
		cout << "Error!";
}
bool isDragonKnight(int n)
{
	for (int i = n; i > n / 3; i--)
	{
		for (int j = n - i; j > 0; j--)
		{
			int z = n - i - j;
			if (z <= 0) continue;
			if (i * i - j * j - z * z == 0)
			{
				return true;
			}
		}
	}
	return false;
}
bool isPrime(int a)
{
	for (int i = 2; i <= sqrt(a); i++)
	{
		if (a % i == 0)
			return false;
	}
	return true;
}
int nearestFibo(int hp)
{
	int a1 = 1, a2 = 1;
	int a = 0;
	while (a <= hp)
	{
		a = a1 + a2;
		a1 = a2;
		a2 = a;
	}
	return a;
}
string typeKnight(int HP)
{
	if (isDragonKnight(HP) && HP != 888)
		return "DragonKnight";
	if (HP == 888) return "Lancelot";
	if (HP == 999) return "Arthur";
	if (isPrime(HP)) return "Paladin";
	return "Normal";
}
int calLevelO(int index)
{
	int b = index % 10;
	return index > 6 ? (b > 5 ? b : 5) : b;
}
// fight: describe the fight between knight(may be arthur, paladin or another type) with comprtitor 1-5
void fight(int maxHP, string typeKnight, knight& theKnight, double baseDamage, int index, int* nOut, bool hasMythril, bool hasExcalipoor, int& Odinsp, bool hasDragonSword)
{
	if (typeKnight == "Normal" || (typeKnight == "Lancelot" && theKnight.level % 2 == 0) || (typeKnight == "DragonKnight" && !hasDragonSword))
	{
		int level = calLevelO(index + 1);
		if (Odinsp >= 0)
		{
			theKnight.level++;
		}
		else if (theKnight.level > level&& theKnight.level < 10 && hasExcalipoor == false) theKnight.level++;
		else if (theKnight.level < level || hasExcalipoor == true)
		{
			if (hasMythril) return;
			int levelO = calLevelO(index + 1);
			int damage = baseDamage * levelO * 10;
			theKnight.HP -= damage;
			if (theKnight.HP < 0 && theKnight.phoenixdown <= 0)
			{
				*nOut = -1;
				return;
			}
			else if (theKnight.HP < 0 && theKnight.phoenixdown>0)
			{
				theKnight.HP = maxHP;
				theKnight.phoenixdown--;
			}
		}
	}
	else if (typeKnight == "Arthur" || typeKnight == "Paladin")
	{
		theKnight.level += 1;
	}
	else if (typeKnight == "DragonKnight" && hasDragonSword)
	{
		theKnight.level += 1;
	}
	else if (typeKnight == "Lancelot" || theKnight.level % 2 == 1)//case lancelot
	{
		theKnight.level += 1;
	}
}

int main(int argc, char** argv)
{
	const char* filename = "input.txt";

	struct knight theKnight; 
	int nEvent; //number of events
	int* arrEvent = new int[EVENT_SIZE]; // array of events
	int* nOut;                          // final result
	int i;
	readFile(filename, theKnight, nEvent, arrEvent);
	
	//cout << theKnight.HP << ' ' << theKnight.level << ' ' << theKnight.remedy << ' ' << theKnight.maidenkiss << ' ' << theKnight.phoenixdown << endl;
	bool isLostToShaman = false, isLostToVajsh = false, hasExcalibur = false, hasMythril = false, hasExcalipoor = false, hasDragonSword = false, isBrowserLost = false;
	int OdinSupport = -1;
	int indexRecover = -1;
	bool isSupport = false;
	nOut = new int;
	*nOut = 0, i = 0;
	int maxHP = theKnight.HP, oriLevel = theKnight.level;
	string strTypeKnight = typeKnight(theKnight.HP);
	for (i; i < nEvent; i++)
	{
		int theEvent = arrEvent[i];
		//cout << theEvent << endl;
		switch (theEvent)
		{
		case BROWSERLOST:
		{
			isBrowserLost = true;
		} break;
		case MADBEAR:    //deal with MadBear here
		{
			if (hasExcalibur) theKnight.level += 1;
			else
			{
				fight(maxHP, strTypeKnight, theKnight, 1.0, i, nOut, hasMythril, hasExcalipoor, OdinSupport, hasDragonSword);
			}
			if (theKnight.level > 10) theKnight.level = 10;
		}break;
		case BANDIT:
		{
			if (hasExcalibur) theKnight.level += 1;
			else
			{
				fight(maxHP, strTypeKnight, theKnight, 1.5, i, nOut, hasMythril, hasExcalipoor, OdinSupport, hasDragonSword);
			}
			if (theKnight.level > 10) theKnight.level = 10;
		}break;
		case LORDLUPIN:
		{
			if (hasExcalibur) theKnight.level += 1;
			else
			{
				fight(maxHP, strTypeKnight, theKnight, 4.5, i, nOut, hasMythril, hasExcalipoor, OdinSupport, hasDragonSword);
			}
			if (theKnight.level > 10) theKnight.level = 10;
		}break;
		case ELF:
		{
			if (hasExcalibur) theKnight.level += 1;
			else
			{
				fight(maxHP, strTypeKnight, theKnight, 6.5, i, nOut, hasMythril, hasExcalipoor, OdinSupport, hasDragonSword);
			}
			if (theKnight.level > 10) theKnight.level = 10;
		}break;
		case TROLL:
		{
			if (hasExcalibur) theKnight.level += 1;
			else
			{
				fight(maxHP, strTypeKnight, theKnight, 8.5, i, nOut, hasMythril, hasExcalipoor, OdinSupport, hasDragonSword);
			}
			if (theKnight.level > 10) theKnight.level = 10;
		}break;
		case SHAMAN:
		{
			bool beSupported = false;
			if (OdinSupport >= 0)
			{
				beSupported = true;
				theKnight.level += 2;
			}
			if (beSupported == true) break;
			if (hasExcalipoor)
			{
				if (theKnight.remedy > 0)
					theKnight.remedy--;
				else theKnight.HP /= 5;
			}
			if (hasExcalipoor) break;
			if (isLostToShaman || isLostToVajsh) break;
			if (strTypeKnight == "Normal" || (strTypeKnight == "Lancelot" && theKnight.level % 2 == 0) || (strTypeKnight == "DragonKnight" && !hasDragonSword))
			{
				int level = calLevelO(i + 1);
				if (theKnight.level > level) theKnight.level += 2;
				else if (theKnight.level < level)
				{
					isLostToShaman = true;
					if (theKnight.HP < 5) theKnight.HP = 1;
					else theKnight.HP /= 5;
					indexRecover = i + 3;
					if (theKnight.remedy > 0)
					{
						isLostToShaman = false;
						theKnight.remedy--;
						theKnight.HP *= 5;
					}
				}
			}
			else if (strTypeKnight == "Arthur" || strTypeKnight == "Paladin" || (strTypeKnight == "DragonKnight" && hasDragonSword) || (strTypeKnight == "DragonKnight" && !hasDragonSword))
			{
				theKnight.level += 2;
			}
			if (theKnight.level > 10) theKnight.level = 10;
		} break;
		case VAJSH:
		{
			bool beSupported = false;
			if (OdinSupport >= 0)
			{
				beSupported = true;
				theKnight.level += 2;
			}
			if (beSupported == true) break;
			if (hasExcalipoor)
			{
				if (theKnight.maidenkiss > 0)
					theKnight.maidenkiss--;
				else theKnight.level = 1;
			}
			if (hasExcalipoor) break;
			if (isLostToShaman || isLostToVajsh) break;
			if (strTypeKnight == "Normal" || (strTypeKnight == "Lancelot" && theKnight.level % 2 == 0)||(strTypeKnight == "DragonKnight" && !hasDragonSword))
			{
				int level = calLevelO(i + 1);
				if (theKnight.level > level) theKnight.level += 2;
				else if (theKnight.level < level)
				{
					oriLevel = theKnight.level;
					theKnight.level = 1;
					isLostToVajsh = true;
					indexRecover = i + 3;
					if (theKnight.maidenkiss > 0)
					{
						isLostToVajsh = false;
						theKnight.maidenkiss--;
						theKnight.level = oriLevel;
					}
				}
			}
			else if (strTypeKnight == "Arthur" || strTypeKnight == "Paladin" || (strTypeKnight == "DragonKnight" && hasDragonSword))
			{
				theKnight.level += 2;
			}
			if (theKnight.level > 10) theKnight.level = 10;
		} break;
		case EXCALIBUR:
		{
			if (hasDragonSword&&strTypeKnight=="DragonKnight") break;
			hasExcalibur = true;
			if (hasExcalipoor) hasExcalipoor = false;
		} break;
		case MYTHRIL:
		{
			hasMythril = true;
		} break;
		case EXCALIPOOR:
		{
			if ((theKnight.level < 5 && strTypeKnight == "Normal") || (strTypeKnight == "Lancelot" && theKnight.level % 2 == 0))
			{
				hasExcalipoor = true;
				hasExcalibur = false;
			}
			else if (strTypeKnight == "Arthhur" || strTypeKnight == "Paladin" || (strTypeKnight == "DragonKnight")) break;
		} break;
		case MUSHMARIO:
		{
			theKnight.HP += 50;
			if (theKnight.HP > maxHP) theKnight.HP = maxHP;
		}break;
		case MUSHFIB:
		{
			theKnight.HP = nearestFibo(theKnight.HP);
			if (theKnight.HP > maxHP) theKnight.HP = maxHP;
		} break;
		case MUSHGHOST:
		{
			if (strTypeKnight == "Paladin" || (strTypeKnight == "DragonKnight" && hasDragonSword)) break;
			theKnight.HP -= 50;
			if (theKnight.HP < 1) theKnight.HP = 1;

		} break;
		case MUSHKNIGHT:
		{
			maxHP += 50;
			if (maxHP > 999) maxHP = 999;
			theKnight.HP = maxHP;
		} break;
		case REMEDY:
		{
			theKnight.remedy++;
			if (theKnight.remedy > 99) theKnight.remedy = 99;
			if (isLostToShaman)
			{
				theKnight.remedy--;
				theKnight.HP *= 5;
			}
		} break;
		case MAIDENKISS:
		{
			theKnight.maidenkiss++;
			if (theKnight.maidenkiss > 99) theKnight.maidenkiss = 99;
			if (isLostToVajsh)
			{
				theKnight.maidenkiss--;
				theKnight.level = oriLevel;
			}
		} break;
		case PHOENIXDOWN:
		{
			theKnight.phoenixdown++;
			if (theKnight.phoenixdown > 99) theKnight.phoenixdown = 99;
		} break;
		case MERLIN:
		{
			if (isLostToShaman) indexRecover = -1;
			if (isLostToVajsh)
			{
				theKnight.level = oriLevel;
				indexRecover = -1;
			}
			if (theKnight.level < 10) theKnight.level++;
			theKnight.HP = maxHP;
		} break;
		case ABYSS:
		{
			if (strTypeKnight == "DragonKnight" && hasDragonSword) break;
			if (theKnight.level < 7) *nOut = -1;
		}break;
		case GUINEVERE:
		{
			nEvent = (i + 1) * 2 - 1;
			int j = i + 1, k = i - 1;
			for (j; j < nEvent; j++)
				arrEvent[j] = arrEvent[k--];
		} break;
		case LIGHTWING:
		{
			if (arrEvent[i + 1] == 0 || arrEvent[i + 2] == 0 || arrEvent[i + 3] == 0 || arrEvent[i + 1] == 20 || arrEvent[i + 2] == 20 || arrEvent[i + 3] == 20)
				i = nEvent;
			else i += 3;
			if (isLostToShaman || isLostToVajsh) indexRecover += 3;
		} break;
		case ODIN:
		{
			if (isSupport == false)
			{
				isSupport = true;
				OdinSupport = 3;

			}
		} break;
		case DRAGONSWORD:
		{
			if (strTypeKnight == "DragonKnight")
				hasDragonSword = true;

		} break;
		case BROWSER:
		{
			if (theKnight.level == 10) break;
			if (OdinSupport >= 0) theKnight.level = 10;
			if (OdinSupport >= 0) break;
			if ((strTypeKnight == "Normal" && theKnight.level < 10)||(strTypeKnight == "Paladin" && theKnight.level < 8))
				*nOut = -1;
			else if (strTypeKnight == "Lancelot" || (strTypeKnight == "DragonKnight" && hasDragonSword) || strTypeKnight == "Arthur") theKnight.level = 10;
			else if ((strTypeKnight == "Paladin" && theKnight.level >= 8)) theKnight.level = 10;
			else *nOut = -1;
		} break;
		}
		if (theKnight.level > 10) theKnight.level = 10;
		OdinSupport--;
		cout << "su kien thu " << i + 1 << " " << arrEvent[i] << ": ";
		PrintKnight(theKnight);
		if (isBrowserLost)
			break;
		if (isLostToShaman)
			if (i == indexRecover)
			{
				isLostToShaman = false;
				theKnight.HP *= 5;
				if (theKnight.HP > maxHP) theKnight.HP = maxHP;
			}
		if (isLostToVajsh)
			if (i == indexRecover)
			{
				isLostToVajsh = false;
				theKnight.level = oriLevel;
			}
		if (*nOut == -1)
			break;
	}
	if (*nOut == 0)
		*nOut = theKnight.HP + theKnight.level + theKnight.maidenkiss + theKnight.phoenixdown + theKnight.remedy;
	display(nOut);
	return 0;
}