#pragma once

#define PURE	  0;

#define SYS_CLS   system("cls");
#define SYS_PAUSE system("pause");

typedef unsigned int uint;

enum CLASS
{Warior = 1, Thief, Wizard};

enum MonField 
{ Rat_Mon, MushRoom_Mon, Tree_Mon, FieldType_End };
enum MonCemetry 
{ Skeleton_Mon, Whitch_Mon, Ghost_Mon, Cemetry_End };
enum MonHell 
{ Demon_Mon, Lucifer_Mon, Hell_Hound_Mon, Hell_End };

typedef struct
{
	char* pName = nullptr;
	char* pClassName = nullptr;
}NAME;

typedef struct
{
	CLASS eClass;

	int   Level = 1;

	int   MaxHp;
	int   Hp;

	int	  Str;
	int	  Dex;
	int   Int;
	
	int   MaxExp;
	int   Exp;

	int   Money;

	int   Att;
	int	  Armor;

	int   ItemAtt;
	int   ItemArmor;
}INFO;