enum eLosimai {
	l_kategorija,
	l_statymas[128],
	Float:l_koef,
	l_pav[128]
};
new const statymai_kat[][] = {
	{"Skaièiai"},
	{"Juodø/geltonø kamuoliukø kiekis"},
	{"Iðkritusiø kamuoliukø skaièiø suma"},
	{"Iðkritusiø kamuoliukø kiekis"},
	{"Lyginis/Nelyginis"},
	{"Juodas/Geltonas"}
};

new const statymai[][eLosimai] = 
{
	{1,"Iðkris pasirinktas kamuoliukas Nr.1,...,42",5.70,"Áveskite kamuoliuko numerá.\nPvz.:{FFFFFF} 1"},
	{1,"Neiðkris pasirinktas kamuoliukas Nr. 1,...,42",1.14,"Áveskite kamuoliuko numerá.\nPvz.:{FFFFFF} 1"},
	{1,"Iðkris du pasirinkti kamuoliukai Nr. 1,...,42",32.00,"Áveskite kamuoliukø numerius.\nPvz.:{FFFFFF} 1 2"},
	{1,"Iðkris trys pasirinkti kamuoliukai Nr. 1,...,42",225.00,"Áveskite kamuoliukø numerius.\nPvz.:{FFFFFF} 1 2 3"},
	{1,"Iðkris keturi pasirinkti kamuoliukai Nr. 1,...,42",2000.00,"Áveskite kamuoliukø numerius.\nPvz.:{FFFFFF} 1 2 3 4"},
	{1,"Ið septyniø pasirinktø skaièiø neiðkris nei vienas",3.50,"Áveskite pasirinktus skaièius.\nPvz.:{FFFFFF} 1 2 3 4 5 6 7"},
	{1,"Ið septyniø pasirinktø skaièiø iðkris bent vienas pasirinktas skaièius",1.25,"Áveskite pasirinktus skaièius. Pvz.:{FFFFFF} 1 2 3 4 5 6 7"},
	{1,"Ið septyniø pasirinktø skaièiø iðkris bent du pasirinkti skaièiai",2.85,"Áveskite pasirinktus skaièius. Pvz.:{FFFFFF} 1 2 3 4 5 6 7"},
	{1,"Ið septyniø pasirinktø skaièiø iðkris bent trys pasirinkti skaièiai",12.00,"Áveskite pasirinktus skaièius. Pvz.:{FFFFFF} 1 2 3 4 5 6 7"},
	{1,"Ið septyniø pasirinktø skaièiø iðkris bent keturi pasirinkti skaièiai",100.00,"Áveskite pasirinktus skaièius. Pvz.:{FFFFFF} 1 2 3 4 5 6 7"},
	{1,"Ið septyniø pasirinktø skaièiø iðkris bent penki pasirinkti skaièiai",1800.00,"Áveskite pasirinktus skaièius. Pvz.:{FFFFFF} 1 2 3 4 5 6 7"},
	{2,"Iðkritusiø geltonø kamuoliukø skaièiø suma bus maþesnë nei 73,5",1.90,""},
	{2,"Iðkritusiø geltonø kamuoliukø skaièiø suma bus didesnë nei 73,5",1.90,""},
	{2,"Iðkritusiø juodø kamuoliukø skaièiø suma bus maþesnë nei 73,5",1.90,""},
	{2,"Iðkritusiø juodø kamuoliukø skaièiø suma bus didesnë nei 73,5",1.90,""},
	{3,"Iðkritusiø kamuoliukø skaièiø suma bus maþesnë nei 100,5",19.00,""},
	{3,"Iðkritusiø kamuoliukø skaièiø suma bus maþesnë nei 125,5",4.60,""},
	{3,"Iðkritusiø kamuoliukø skaièiø suma bus didesnë nei 125,5",1.17,""},
	{3,"Iðkritusiø kamuoliukø skaièiø suma bus maþesnë nei 150,5",1.90,""},
	{3,"Iðkritusiø kamuoliukø skaièiø suma bus didesnë nei 150,5",1.90,""},
	{3,"Iðkritusiø kamuoliukø skaièiø suma bus maþesnë nei 175,5",1.17,""},
	{3,"Iðkritusiø kamuoliukø skaièiø suma bus didesnë nei 175,5",4.60,""},
	{3,"Iðkritusiø kamuoliukø skaièiø suma bus didesnë nei 200,5",19.00,""},
	{4,"Geltonos spalvos kamuoliukø iðkris maþiau nei 3,5",1.90,""},
	{4,"Geltonos spalvos kamuoliukø iðkris daugiau nei 3,5",1.90,""},
	{4,"Geltonos spalvos kamuoliukø iðkris maþiau nei 2,5",4.55,""},
	{4,"Geltonos spalvos kamuoliukø iðkris daugiau nei 2,5",1.17,""},
	{4,"Geltonos spalvos kamuoliukø iðkris maþiau nei 1,5",20.00,""},
	{4,"Geltonos spalvos kamuoliukø iðkris daugiau nei 1,5",1.01,""},
	{4,"Neiðkris geltonos spalvos kamuoliukas",200.00,""},
	{4,"Juodos spalvos kamuoliukø iðkris maþiau nei 3,5",1.90,""},
	{4,"Juodos spalvos kamuoliukø iðkris daugiau nei 3,5",1.90,""},
	{4,"Juodos spalvos kamuoliukø iðkris maþiau nei 2,5",4.55,""},
	{4,"Juodos spalvos kamuoliukø iðkris daugiau nei 2,5",1.17,""},
	{4,"Juodos spalvos kamuoliukø iðkris maþiau nei 1,5",20.00,""},
	{4,"Juodos spalvos kamuoliukø iðkris daugiau nei 1,5",1.01,""},
	{4,"Neiðkris juodos spalvos kamuoliukas",200.00,""},
	{4,"Iðkris septyni geltonos spalvos kamuoliukai",200.00,""},
	{4,"Iðkris lygiai ðeði geltonos spalvos kamuoliukai",22.00,""},
	{4,"Iðkris lygiai penki geltonos spalvos kamuoliukai",5.90,""},
	{4,"Iðkris lygiai keturi geltonos spalvos kamuoliukai",3.00,""},
	{4,"Iðkris lygiai trys geltonos spalvos kamuoliukai",3.00,""},
	{4,"Iðkris lygiai du geltonos spalvos kamuoliukai",5.90,""},
	{4,"Iðkris lygiai vienas geltonos spalvos kamuoliukas",22.00,""},
	{4,"Iðkris septyni juodos spalvos kamuoliukai",200.00,""},
	{4,"Iðkris lygiai ðeði juodos spalvos kamuoliukai",22.00,""},
	{4,"Iðkris lygiai penki juodos spalvos kamuoliukai",5.90,""},
	{4,"Iðkris lygiai keturi juodos spalvos kamuoliukai",3.00,""},
	{4,"Iðkris lygiai trys juodos spalvos kamuoliukai",3.00,""},
	{4,"Iðkris lygiai du juodos spalvos kamuoliukai",5.90,""},
	{4,"Iðkris lygiai vienas juodos spalvos kamuoliukas",22.00,""},
	{5,"Iðkris daugiau kamuoliukø su nelyginiais skaièiais",1.90,""},
	{5,"Iðkris daugiau kamuoliukø su lyginiais skaièiais",1.90,""},
	{5,"Iðkritusiø kamuoliukø skaièiø suma - nelyginis skaièius",1.90,""},
	{5,"Iðkritusiø kamuoliukø skaièiø suma - lyginis skaièius",1.90,""},
	{5,"Pirmo iðkritusio kamuoliuko skaièius - nelyginis",1.90,""},
	{5,"Pirmo iðkritusio kamuoliuko skaièius - lyginis",1.90,""},
	{5,"Paskutinio iðkritusio kamuoliuko skaièius - nelyginis",1.90,""},
	{5,"Paskutinio iðkritusio kamuoliuko skaièius - lyginis",1.90,""},
	{5,"Pirmø dviejø iðkritusiø kamuoliukø skaièiai - nelyginiai",3.90,""},
	{5,"Pirmø dviejø iðkritusiø kamuoliukø skaièiai - lyginiai",3.90,""},
	{5,"Pirmo iðkritusio kamuoliuko skaièius - nelyginis, antro - lyginis",3.70,""},
	{5,"Pirmo iðkritusio kamuoliuko skaièius - lyginis, antro - nelyginis",3.70,""},
	{5,"Pirmo kamuoliuko skaièius - nelyginis, paskutinio - lyginis",3.70,""},
	{5,"Pirmo kamuoliuko skaièius - lyginis, paskutinio - nelyginis",3.70,""},
	{6,"Pirmas iðkritæs kamuoliukas bus geltonos spalvos",1.90,""},
	{6,"Pirmas iðkritæs kamuoliukas bus juodos spalvos",1.90,""},
	{6,"Paskutinis iðkritæs kamuoliukas bus geltonos spalvos",1.90,""},
	{6,"Paskutinis iðkritæs kamuoliukas bus juodos spalvos",1.90,""},
	{6,"Iðkris daugiau geltonos spalvos kamuoliukø",1.90,""},
	{6,"Iðkris daugiau juodos spalvos kamuoliukø",1.90,""},
	{6,"Antras iðkritæs kamuoliukas bus tos paèios spalvos kaip ir pirmas",1.95,""},
	{6,"Antruoju iðkritæs kamuoliukas bus kitos spalvos nei pirmasis",1.85,""}

};


stock LosimuGui(playerid,idas)
{
	new msgas[128];
	if(idas == 0)
	{
		format(msgas,128,"Statymo suma: {00ff7f}%s€",FormatNumber(GetPVarInt(playerid, "statymo_suma")));
		AddDListItem(playerid,msgas,0);
		for(new i;i<sizeof statymai_kat; i++)
			AddDListItem(playerid,statymai_kat[i],i+1);
		ShowPlayerDList(playerid, 30101,"7 ið 42", "Rinktis", "Iseiti");
	}
	else if(1 <= idas <= 6)
	{
		for(new i;i<sizeof statymai; i++)
		{
			if(statymai[i][l_kategorija] == idas)
			{

				format(msgas,128,"%s\t{00ff7f}%.2f",statymai[i][l_statymas],statymai[i][l_koef]);
				AddDListItem(playerid,msgas, i);
			}
		}
		ShowPlayerDListHeader(playerid, 30102, statymai_kat[idas-1], "Rinktis", "Iseiti","Statymas\tKoeficientas");

	}
}
stock LoadStatymas(playerid,statymoid)
{
	if(strlen(statymai[statymoid][l_pav]) == 0)
	{
		VerifyStatymas(playerid,statymoid, "");
	}
	else // show description
	{
		SetPVarInt(playerid,"statymo_id",statymoid);
		new msg[1024];
		format(msg,1024,"Norite atlikti ðá statymà:\n{FFFFFF}%s\n\n{A9C4E4}%s",statymai[statymoid][l_statymas],statymai[statymoid][l_pav]);
		ShowPlayerDialog(playerid, 30103, DIALOG_STYLE_INPUT, "Statymas", msg, "Gerai", "Atsaukti");
	}
}

stock VerifyStatymas(playerid,statymoid,statymelis[])
{
	new taip = 0;
	new numbers[7];
	new statymux[40];
	// 1,1,2,3,4,7,7,7,7,7,7
	if(statymoid > 10)
	{
		taip = 1;
		SetPVarString(playerid, "pasirinkimas", "Taip");
	}
	else
	{
		
		switch(statymoid+1)
		{
			case 1,2:
			{
				if(sscanf(statymelis,"d",numbers[0]))
				{
					LoadStatymas(playerid,statymoid);
					SendClientMessage(playerid, RED, " * Netinkamas formatas!");
					return;
				}
				if(1 <= numbers[0] <= 42)
				{}
				else
				{
					SendClientMessage(playerid, RED, " * Turite ávesti skaièiø nuo 1 iki 42!");
					LoadStatymas(playerid,statymoid);
					return;
				}
			}
			case 3:
			{
				if(sscanf(statymelis,"dd",numbers[0],numbers[1]))
				{
					LoadStatymas(playerid,statymoid);
					SendClientMessage(playerid, RED, " * Netinkamas formatas!");
					return;
				}
				if(numbers[0] == numbers[1])
				{
					SendClientMessage(playerid, RED, " * Turite ávesti skirtingus skaièius!");
					LoadStatymas(playerid,statymoid);
					return;
				}
				if(1 <= numbers[0] <= 42 && 1 <= numbers[1] <= 42)
				{}
				else
				{
					SendClientMessage(playerid, RED, " * Turite ávesti du skaièius nuo 1 iki 42!");
					LoadStatymas(playerid,statymoid);
					return;
				}
			}
			case 4:
			{
				if(sscanf(statymelis,"ddd",numbers[0],numbers[1],numbers[2]))
				{
					LoadStatymas(playerid,statymoid);
					SendClientMessage(playerid, RED, " * Netinkamas formatas!");
					return;
				}
				if(numbers[0] == numbers[1] || numbers[1] == numbers[2] || numbers[0] == numbers[2])
				{
					SendClientMessage(playerid, RED, " * Turite ávesti skirtingus skaièius!");
					LoadStatymas(playerid,statymoid);
					return;
				}
				if(1 <= numbers[0] <= 42 && 1 <= numbers[1] <= 42 && 1 <= numbers[2] <= 42)
				{}
				else
				{
					SendClientMessage(playerid, RED, " * Turite ávesti tris skaièius nuo 1 iki 42!");
					LoadStatymas(playerid,statymoid);
					return;
				}
			}
			case 5:
			{
				if(sscanf(statymelis,"dddd",numbers[0],numbers[1],numbers[2],numbers[3]))
				{
					LoadStatymas(playerid,statymoid);
					SendClientMessage(playerid, RED, " * Netinkamas formatas!");
					return;
				}
				if(numbers[0] == numbers[1] || numbers[1] == numbers[2] || numbers[2] == numbers[3] || 
					numbers[0] == numbers[2] || numbers[0] == numbers[3] || numbers[1] == numbers[3])
				{
					SendClientMessage(playerid, RED, " * Turite ávesti skirtingus skaièius!");
					LoadStatymas(playerid,statymoid);
					return;
				}
				if(1 <= numbers[0] <= 42 && 1 <= numbers[1] <= 42 && 1 <= numbers[2] <= 42 && 1 <= numbers[3] <= 42)
				{}
				else
				{
					SendClientMessage(playerid, RED, " * Turite ávesti keturis skaièius nuo 1 iki 42!");
					LoadStatymas(playerid,statymoid);
					return;
				}
			}
			case 6..11:
			{
				if(sscanf(statymelis,"ddddddd",numbers[0],numbers[1],numbers[2],numbers[3],numbers[4],numbers[5],numbers[6]))
				{
					LoadStatymas(playerid,statymoid);
					SendClientMessage(playerid, RED, " * Netinkamas formatas!");
					return;
				}
				for(new i;i<7;i++)
				{
					if(numbers[i] < 1 || numbers[i] > 42)
					{
						SendClientMessage(playerid, RED, " * Turite ávesti septynis skaièius nuo 1 iki 42!");
						LoadStatymas(playerid,statymoid);
						return;
					}
					for(new x=i+1;x<7;x++)
					{
						if(numbers[x] == numbers[i])
						{
							SendClientMessage(playerid, RED, " * Turite ávesti skirtingus skaièius!");
							LoadStatymas(playerid,statymoid);
							return;
						}
					}
				}
			}
		}
		for(new i;i<7;i++)
		{
			if(numbers[i] > 0)
			{
				format(statymux,sizeof(statymux),"%s%i ",statymux,numbers[i]);
				new pvar[24];
				format(pvar,24,"numbers_%i",i);
				SetPVarInt(playerid,pvar,numbers[i]);
			}
		}
		SetPVarString(playerid, "pasirinkimas", statymux);
	}
	SetPVarInt(playerid,"statymo_id",statymoid);
	new statymosuma = GetPVarInt(playerid, "statymo_suma");
	new laimejimas = floatround(statymosuma * statymai[statymoid][l_koef]);
	new msgas[1024];
	format(msgas,1024,"Norite atlikti ðá statymà:\n{FFFFFF}%s\n\n{A9C4E4}Jûsø pasirinkimas: {00ff7f}%s\n{A9C4E4}Statoma suma: {00ff7f}%s€\n{A9C4E4}Koeficientas: {00ff7f}%.2f\n\
		{A9C4E4}Galimas laimëjimas: {00ff7f}%s€\n\n\n{FFFFFF}Ar norite atlikti ðá statymà?", statymai[statymoid][l_statymas], \
		 ((taip) ? ("Taip") : (statymux)),FormatNumber(statymosuma),statymai[statymoid][l_koef],FormatNumber(laimejimas));
	ShowPlayerDialog(playerid, 30104,DIALOG_STYLE_MSGBOX, "Statymas",msgas,"Atlikti","Atsaukti");
}
new Losejai=0;
stock MakeStatymas(playerid)
{
	if(GetPVarInt(playerid,"statymas"))
	{
		return SendInfoMessage(playerid,"Tu jau padares statyma!");
	}
	if(!GaliStatyti())
		return SendInfoMessage(playerid,"Losimas jau vyksta! Palauk kito zaidimo");
	new bizid = GetPlayerVirtualWorld(playerid) - MAX_HOUSES*2;
	new suma = GetPVarInt(playerid,"statymo_suma");
	if(bizid < 0)
		return SendInfoMessage(playerid,"Turite buti verslo viduje!");
	if(GetPlayerMoneyA(playerid) < suma)
		return SendInfoMessage(playerid,"~r~Neturi pakankamai pinigu!");
	SetPVarInt(playerid,"statymas",1);
	SetPVarInt(playerid,"statymo_biz",bizid);
	GivePlayerMoneyA(playerid,-suma);
	if(GetPlayerScore(playerid) > 100 && GetPlayerVirtualWorld(playerid)>= MAX_HOUSES*2) BusinessInfo[bizid][bEarning]+=(suma/10);




	new laimejimas = floatround(suma * statymai[GetPVarInt(playerid,"statymo_id")][l_koef]);
	SendClientMessage(playerid,COLOR,"* ======= STATYMO KVITAS =======");
	new msg[256];
	format(msg,256,"* Statymas atliktas: {FFFFFF}%s",BusinessInfo[bizid][bName]);
	SendClientMessage(playerid, COLOR, msg);
	format(msg,256,"* Statymas: {FFFFFF}%s",statymai[GetPVarInt(playerid,"statymo_id")][l_statymas]);
	SendClientMessage(playerid, COLOR, msg);
	new pasirinkimas[24];
	GetPVarString(playerid, "pasirinkimas", pasirinkimas, 24);
	format(msg,256,"* Pasirinkimas: {FFFFFF}%s",pasirinkimas);
	SendClientMessage(playerid, COLOR, msg);
	format(msg,256,"* Statoma suma: {FFFFFF}%s€",FormatNumber(suma));
	SendClientMessage(playerid, COLOR, msg);
	format(msg,256,"* Galimas laimejimas: {FFFFFF}%s€",FormatNumber(laimejimas));
	SendClientMessage(playerid, COLOR, msg);
	SendClientMessage(playerid,-1, "* Dabar laukite kol bus iðridenti kamuoliukai.");
	Losejai++;
	ActorServe(playerid);
	printf("%s pastate ant %i",ReturnName(playerid),GetPVarInt(playerid,"statymo_id"));
	return 1;
}
#define LOSIMAI_FREQUENCY 60
new isridenta = 0;
new Losimai_Laikas = LOSIMAI_FREQUENCY; // kas 2 min
new LAR[7];
stock GaliStatyti()
{
	return (Losimai_Laikas > 0);
}

stock UpdateLosimai()
{
	Losimai_Laikas--;
	if(Losimai_Laikas > 0)
	{
		new msgas[128];
		new minutes = Losimai_Laikas / 60;
		new sekundes = Losimai_Laikas % 60;

		format(msgas,128,"{33CCFF}7 ið 42\n\n\n{FFFFFF}Iki kito loðimo liko {00ff7f}0%i:%s%i",minutes,((sekundes < 10) ? ("0") : ("")),sekundes);
		UpdateDynamic3DTextLabelText(LosimuTD, -1,msgas);
	}
	else if(Losimai_Laikas == 0)
	{
		isridenta = 0;
		UpdateDynamic3DTextLabelText(LosimuTD, -1,"{33CCFF}7 ið 42\n\n\n{FFFFFF}Pradedamas ridenimas!");
		new soundid = 5408 + random(3);
		PlaySoundInArea(soundid,30.0,822.2601,2.1007,1004.1797);
	}
	else 
	{
		if(!isridenta)
		{
			new Kamuoliukai[42];
			for(new i;i<42;i++)
				Kamuoliukai[i] = i+1;
			// shuffle
			for (new z;z<3;z++)
			{
				for (new i=0;i<42;i++)
				{
					new x = random(42);
					new temp = Kamuoliukai[x];
					Kamuoliukai[x] = Kamuoliukai[i];
					Kamuoliukai[i] = temp;
				}
			}
			new startpos = random(30);
			for(new i;i<7;i++)
			{
				LAR[i] = Kamuoliukai[startpos+i];
			}
			isridenta = 1;
		}
		new showcount = (-Losimai_Laikas) / 3;
		new show = (-Losimai_Laikas) % 3;
		if(showcount < 8)
		{
			if(show == 0)
			{

				new msgas[512];
				format(msgas,512,"{33CCFF}7 ið 42\n\n\n{FFFFFF}Iðkritæ kamuoliukai:\n");
				for(new i;i<showcount;i++)
				{
					new color[24];
					if(LAR[i] % 2 == 0)
						color = "{919191}";
					else
						color = "{ffff00}";
					format(msgas,512,"%s%s%i   ",msgas,color,LAR[i]);
				}
				AnounceBalls(showcount);
				UpdateDynamic3DTextLabelText(LosimuTD, -1,msgas);
			}
		}
		else if(showcount == 8)
		{
			Nugaletojai();
			Losimai_Laikas=LOSIMAI_FREQUENCY + 1;
			new soundid = 5400 + random(2);
			PlaySoundInArea(soundid,30.0,822.2601,2.1007,1004.1797);
		}

	}
}
stock AnounceBalls(showcount)
{

	new msgas[512];
	format(msgas,512,"{33CCFF}[7 ið 42]{FFFFFF} Iðkritæ kamuoliukai: ");
	for(new i;i<showcount;i++)
	{
		new color[24];
		if(LAR[i] % 2 == 0)
			color = "{919191}";
		else
			color = "{ffff00}"; // yellow
		format(msgas,512,"%s%s%i  ",msgas,color,LAR[i]);
	}
	foreach(Player, i)
	{
		if(IsPlayerInRangeOfPointEx(30.0, i, 822.2601,2.1007,1004.1797) || GetPVarInt(i,"statymas"))
		{
			PlayerPlaySound(i, 1138, 0.0, 0.0, 0.0); // SMS
			SendClientMessage(i, -1, msgas);
		}
	}
}
stock Nugaletojai()
{
	if(!Losejai)
		return;
	Losejai = 0;
	foreach(Player, i)
	{
		if(GetPVarInt(i,"statymas"))
		{
			CheckWinner(i,GetPVarInt(i,"statymo_id"));
			SetPVarInt(i,"statymas",0);
		}
	}
}
stock CheckWinner(playerid,statymoid,bool:sim=false)
{
	new winner = 0;
	if(statymoid < 11)
	{
		new numbers[7];
		//new rando = random(42);
		for(new i;i<7;i++)
		{
			new temp[24];
			format(temp,24,"numbers_%i",i);
			numbers[i] = GetPVarInt(playerid, temp);//((rando+i) % 42) + 1;//
		}
		switch(statymoid)
		{
			case 0: // "Iðkris pasirinktas kamuoliukas Nr.1,...,42"
			{
				for(new i;i<7;i++)
				{
					if(LAR[i] == numbers[0])
						winner = 1;
				}
			}
			case 1: // "Neiðkris pasirinktas kamuoliukas Nr. 1,...,42"
			{
				winner = 1;
				for(new i;i<7;i++)
				{
					if(LAR[i] == numbers[0])
						winner = 0;
				}
			}
			case 2: // "Iðkris du pasirinkti kamuoliukai Nr. 1,...,42"
			{
				new count = 0;
				for(new i;i<7;i++)
				{
					if(LAR[i] == numbers[0] || LAR[i] == numbers[1])
						count++;
				}
				if(count >= 2)
					winner = 1;

			}
			case 3: // "Iðkris trys pasirinkti kamuoliukai Nr. 1,...,42"
			{
				new count = 0;
				for(new i;i<7;i++)
				{
					if(LAR[i] == numbers[0] || LAR[i] == numbers[1] || LAR[i] == numbers[2])
						count++;
				}
				if(count >= 3)
					winner = 1;
			}
			case 4: // "Iðkris keturi pasirinkti kamuoliukai Nr. 1,...,42"
			{
				new count = 0;
				for(new i;i<7;i++)
				{
					if(LAR[i] == numbers[0] || LAR[i] == numbers[1] || LAR[i] == numbers[2] || LAR[i] == numbers[3])
						count++;
				}
				if(count >= 4)
					winner = 1;
			}
			case 5:
			{
				winner = 1;
				for(new i;i<7;i++)
				{
					for(new x;x<7;x++)
					{
						if(LAR[i] == numbers[x])
							winner = 0;
					}
				}
			}
			case 6:
			{
				for(new i;i<7;i++)
				{
					for(new x;x<7;x++)
					{
						if(LAR[i] == numbers[x])
							winner = 1;
					}
				}
			}
			case 7:
			{
				new count = 0;
				for(new i;i<7;i++)
				{
					for(new x;x<7;x++)
					{
						if(LAR[i] == numbers[x])
							count++;
					}
				}
				if(count >= 2)
					winner=1;
			}
			case 8:
			{
				new count = 0;
				for(new i;i<7;i++)
				{
					for(new x;x<7;x++)
					{
						if(LAR[i] == numbers[x])
							count++;
					}
				}
				if(count >= 3)
					winner=1;
			}
			case 9:
			{
				new count = 0;
				for(new i;i<7;i++)
				{
					for(new x;x<7;x++)
					{
						if(LAR[i] == numbers[x])
							count++;
					}
				}
				if(count >= 4)
					winner=1;
			}
			case 10:
			{
				new count = 0;
				for(new i;i<7;i++)
				{
					for(new x;x<7;x++)
					{
						if(LAR[i] == numbers[x])
							count++;
					}
				}
				if(count >= 5)
					winner=1;
			}
		}
	}
	new geltonusum = 0;
	new juodusum = 0;
	new juodu = 0;
	new geltonu = 0;
	for(new i;i<7;i++)
	{
		if(LAR[i] % 2 == 0) 
		{
			juodusum += LAR[i];
			juodu++;
		}
		else 
		{
			geltonu++;
			geltonusum += LAR[i]; // yellow
		}
	}
	new lyginiu = juodu;
	new nelyginiu = geltonu;
	new sum = geltonusum + juodusum;
	switch(statymoid)
	{
		case 11:
		{
			if(geltonusum < 73.5)
				winner=1;
		}
		case 12:
		{
			if(geltonusum > 73.5)
				winner=1;
		}
		case 13:
		{
			if(juodusum < 73.5)
				winner=1;
		}
		case 14:
		{
			if(juodusum > 73.5)
				winner=1;
		}
		case 15:
		{
			if(sum < 100.5)
				winner = 1;
		}
		case 16:
		{
			if(sum < 125.5)
				winner = 1;
		}
		case 17:
		{
			if(sum > 125.5)
				winner = 1;
		}
		case 18:
		{
			if(sum < 150.5)
				winner = 1;
		}
		case 19:
		{
			if(sum > 150.5)
				winner = 1;
		}
		case 20:
		{
			if(sum < 175.5)
				winner = 1;
		}
		case 21:
		{
			if(sum > 175.5)
				winner = 1;
		}
		case 22:
		{
			if(sum > 200.5)
				winner = 1;
		}
		case 23:
		{
			if(geltonu < 3.5)
				winner = 1;
		}
		case 24:
		{
			if(geltonu > 3.5)
				winner = 1;
		}
		case 25:
		{
			if(geltonu < 2.5)
				winner = 1;
		}
		case 26:
		{
			if(geltonu > 2.5)
				winner = 1;
		}
		case 27:
		{
			if(geltonu < 1.5)
				winner = 1;
		}
		case 28:
		{
			if(geltonu > 1.5)
				winner = 1;
		}
		case 29: // {4,"Neiðkris geltonos spalvos kamuoliukas",200.00,""}
		{
			if(geltonu == 0)
				winner = 1;
		}
		case 30:
		{
			if(juodu < 3.5)
				winner = 1;
		}
		case 31:
		{
			if(juodu > 3.5)
				winner = 1;
		}
		case 32:
		{
			if(juodu < 2.5)
				winner = 1;
		}
		case 33:
		{
			if(juodu > 2.5)
				winner = 1;
		}
		case 34:
		{
			if(juodu < 1.5)
				winner = 1;
		}
		case 35:
		{
			if(juodu > 1.5)
				winner = 1;
		}
		case 36:
		{
			if(juodu == 0)
				winner = 1;
		}
		case 37:
		{
			if(geltonu == 7)
				winner = 1;
		}
		case 38:
		{
			if(geltonu == 6)
				winner = 1;
		}
		case 39:
		{
			if(geltonu == 5)
				winner = 1;
		}
		case 40:
		{
			if(geltonu == 4)
				winner = 1;
		}
		case 41:
		{
			if(geltonu == 3)
				winner = 1;
		}
		case 42:
		{
			if(geltonu == 2)
				winner = 1;
		}
		case 43:
		{
			if(geltonu == 1)
				winner = 1;
		}
		case 44:
		{
			if(juodu == 7)
				winner = 1;
		}
		case 45:
		{
			if(juodu == 6)
				winner = 1;
		}
		case 46:
		{
			if(juodu == 5)
				winner = 1;
		}
		case 47:
		{
			if(juodu == 4)
				winner = 1;
		}
		case 48:
		{
			if(juodu == 3)
				winner = 1;
		}
		case 49:
		{
			if(juodu == 2)
				winner = 1;
		}
		case 50:
		{
			if(juodu == 1)
				winner = 1;
		}
		case 51: // {5,"Iðkris daugiau kamuoliukø su nelyginiais skaièiais",1.90,""},
		{
			if(nelyginiu > lyginiu)
				winner = 1;
		}
		case 52:
		{
			if(lyginiu > nelyginiu)
				winner = 1;
		}
		case 53:
		{
			if(sum % 2 == 1)
				winner = 1;
		}
		case 54:
		{
			if(sum % 2 == 0)
				winner = 1;
		}
		case 55:
		{
			if(LAR[0] % 2 == 1)
				winner = 1;
		}
		case 56:
		{
			if(LAR[0] % 2 == 0)
				winner = 1;
		}
		case 57:
		{
			if(LAR[6] % 2 == 1)
				winner = 1;
		}
		case 58:
		{
			if(LAR[6] % 2 == 0)
				winner = 1;
		}
		case 59: // {5,"Pirmø dviejø iðkritusiø kamuoliukø skaièiai - nelyginiai",3.90,""},
		{
			if(LAR[0] % 2 == 1 && LAR[1] % 2 == 1)
				winner = 1;
		}
		case 60:
		{
			if(LAR[0] % 2 == 0 && LAR[1] % 2 == 0)
				winner = 1;
		}
		case 61:
		{
			if(LAR[0] % 2 == 1 && LAR[1] % 2 == 0)
				winner = 1;
		}
		case 62:
		{
			if(LAR[0] % 2 == 0 && LAR[1] % 2 == 1)
				winner = 1;
		}
		case 63:
		{
			if(LAR[0] % 2 == 1 && LAR[6] % 2 == 0)
				winner = 1;
		}
		case 64:
		{
			if(LAR[0] % 2 == 0 && LAR[6] % 2 == 1)
				winner = 1;
		}
		case 65: //{6,"Pirmas iðkritæs kamuoliukas bus geltonos spalvos",1.90,""},
		{
			if(LAR[0] %2 == 1)
				winner = 1;
		}
		case 66:
		{
			if(LAR[0] %2 == 0)
				winner = 1;
		}
		case 67:
		{
			if(LAR[6] %2 == 1)
				winner = 1;
		}
		case 68:
		{
			if(LAR[6] %2 == 0)
				winner = 1;
		}
		case 69:
		{
			if(geltonu > juodu)
				winner = 1;
		}
		case 70:
		{
			if(juodu > geltonu)
				winner = 1;
		}
		case 71:
		{
			if((LAR[0] % 2) == (LAR[1] % 2))
				winner = 1;
		}
		case 72:
		{
			if((LAR[0] % 2) != (LAR[1] % 2))
				winner = 1;
		}
	}



	if(!sim)
	{
		if(winner)
			IsWinner(playerid,statymoid);
		else
			IsLoser(playerid);
	}
	return winner;
}
stock IsWinner(playerid,statymoid)
{
	new msg[128];
	new suma = floatround(GetPVarInt(playerid,"statymo_suma") * statymai[statymoid][l_koef]);
	format(msg,sizeof(msg)," * Laimejai {FFFFFF}%s€!",FormatNumber(suma));
	SendClientMessage(playerid,BLUE,msg);
	GivePlayerMoneyA(playerid,suma);
	ProcessAchievement(playerid,95,suma);

	new bizid = GetPVarInt(playerid,"statymo_biz");
	if(GetPlayerScore(playerid) > 100) BusinessInfo[bizid][bEarning]-=(suma/10);

}
stock IsLoser(playerid)
{
	SendClientMessage(playerid, BLUE, " * Prapisai.");
	ProcessAchievement(playerid,100);
}
stock TestLoterija(playerid)
{
	// Save live LAR so an ongoing round is not disturbed
	new savedLAR[7];
	for(new i;i<7;i++) savedLAR[i] = LAR[i];

	// Pre-set fixed distinct ball picks for number-based bets (IDs 0-10)
	for(new i;i<7;i++) { new pv[24]; format(pv,24,"numbers_%i",i); SetPVarInt(playerid,pv,i+1); }

	new wins[sizeof statymai];
	new iterations = 3000;
	for(new iter;iter<iterations;iter++)
	{
		// Inline shuffle - same logic as UpdateLosimai but without side-effects
		new Kamuoliukai[42];
		for(new i;i<42;i++) Kamuoliukai[i] = i+1;
		for(new z;z<3;z++)
			for(new i=0;i<42;i++) {
				new x=random(42), tmp=Kamuoliukai[x];
				Kamuoliukai[x]=Kamuoliukai[i]; Kamuoliukai[i]=tmp;
			}
		new startpos=random(30);
		for(new i;i<7;i++) LAR[i]=Kamuoliukai[startpos+i];

		for(new x;x<sizeof statymai;x++)
			wins[x] += CheckWinner(playerid,x,true);
	}

	// Restore live LAR
	for(new i;i<7;i++) LAR[i]=savedLAR[i];

	SendClientMessage(playerid,0x33CCFFFF,
		"[testloterija] {FFFFFF}n=3000 | {AAAAAA}ID  WinRate   Coef    HouseEdge");
	for(new i;i<sizeof statymai;i++)
	{
		new Float:prob = wins[i] * 1.0 / iterations;
		new Float:ev   = prob * statymai[i][l_koef] - 1.0;
		new msg[128];
		format(msg,sizeof(msg),
			"{AAAAAA}[%02i] {FFFFFF}%5.1f%%  x%-5.2f  {%s}%+.1f%%",
			i, prob*100.0, statymai[i][l_koef],
			(ev>=0.0)?("00FF00"):("FF4444"), ev*100.0);
		SendClientMessage(playerid,-1,msg);
		printf("[testloterija] %02i  %.2f%%  x%.2f  %+.2f%%",
			i,prob*100.0,statymai[i][l_koef],ev*100.0);
	}
	SendClientMessage(playerid,0x33CCFFFF,
		"[testloterija] {FFFFFF}Done. {00FF00}Green{FFFFFF}=player edge  {FF4444}Red{FFFFFF}=house edge");
}
	
	for(new i;i<73;i++)
	{
		new Float:proc = (wins[i] * 1.0) / iterations;
		new Float:EV = iterations - wins[i]*(statymai[i][l_koef]);
		printf("%i\t%i\t%.2f%s\t%.2f\t%.2f",i,wins[i],proc*100,("%"),statymai[i][l_koef],EV);
	}
}
