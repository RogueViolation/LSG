#define query:%0(%1)	forward SQL_%0(%1); \
						public SQL_%0(%1)

forward SQL_Family(ix);
public SQL_Family(ix)
{
	RestartCheck();
	cache_get_row(0, 1, FamilyInfo[ix][FamilyLeader],SQL,24);
	cache_get_row(0, 2, FamilyInfo[ix][FamilySubstitute],SQL,24);
	new temp[256];
	cache_get_row(0, 3, temp); FamilyInfo[ix][FamilyFunds]=strval(temp);
	cache_get_row(0, 4, temp); FamilyInfo[ix][FamilyLimit]=strval(temp);

	if(isnull(FamilyInfo[ix][FamilyLeader]) || strcmp(FamilyInfo[ix][FamilyLeader],"NULL",true)==0)
	{
		format(FamilyInfo[ix][FamilyLeader], 24, "Nera");
	}
	if(isnull(FamilyInfo[ix][FamilySubstitute]) || strcmp(FamilyInfo[ix][FamilySubstitute],"NULL",true)==0)
	{
		format(FamilyInfo[ix][FamilySubstitute], 24, "Nera");
	}

	cache_get_row(0,5,temp); // SandelioLimitai
	sscanf(temp,"p<|>a<i>[3]",FamilyInfo[ix][SandelioLimitai]);
	cache_get_row(0,6,temp); // SaugyklosLimitai
	sscanf(temp,"p<|>a<i>[10]",FamilyInfo[ix][SaugyklosLimitai]);
	cache_get_row(0,7,temp); // FamilySaugykla
	sscanf(temp,"p<|>a<i>[10]",FamilyInfo[ix][FamilySaugykla]);

	cache_get_row(0,8,temp); FamilyInfo[ix][ApleidimoDelay]=strval(temp);
	return 1;
}

forward SQL_LoadTyrimai();
public SQL_LoadTyrimai()
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows)
	{
		return 1;
	}
	new temp[24];
	new jau=0;

	while(jau < rows)
	{
		new TyrTypes:type;
		new TyrStatusEnum:status;
		new ticksDone;
		cache_get_row(jau, 0, temp), type = TyrTypes:strval(temp);
		cache_get_row(jau, 1, temp), status = TyrStatusEnum:strval(temp);
		cache_get_row(jau, 2, temp), ticksDone = strval(temp);

		PreloadTyrimas(type, status, ticksDone);
		jau++;
	}

	return 1;
}

forward SQL_GangIspejimai();
public SQL_GangIspejimai() 
{
	// reset old ispejimai
	for(new ix;ix<MAX_FAMILY;ix++)
	{
	   	FamilyInfo[ix][FamilyIspejimai] = 0;
	}
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows)
	{
		return 1;
	}
	
	new temp[12];
	new jau=0;

	while(jau < rows)
	{
		new gangid, count;
		cache_get_row(jau, 1, temp), gangid = strval(temp);
		cache_get_row(jau, 3, temp), count = strval(temp);
		FamilyInfo[gangid][FamilyIspejimai] = min(FamilyInfo[gangid][FamilyIspejimai] + count, 2); // max 2 ispejimai
		if(FamilyInfo[gangid][FamilyIspejimai] == 2)
		{
			/*if(FamilyInfo[gangid][ApleidimoDelay]==0)
			{
				FamilyInfo[gangid][ApleidimoDelay] = 3 + random(2);
				SaveFamily(gangid);
			}*/
			EmptyGang(gangid);
		}
		jau++;
	}
	return 1;
}

forward SQL_Sandeliai();
public SQL_Sandeliai()
{
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
	
	new temp[12];
	new jau=0;
	while(jau < rows)
	{
		cache_get_row(jau, 1, temp), PlaceOwnedBy[jau] = strval(temp);
		cache_get_row(jau, 2, temp), KiekYra[jau] = strval(temp);
		cache_get_row(jau, 3, temp), BombaYra[jau] = strval(temp);
		if(PlaceOwnedBy[jau] != -1) GangZoneSpalva[jau]=FamilyInfo[PlaceOwnedBy[jau]][FamilyZone][1];
		else GangZoneSpalva[jau]=0x00F2FFAB;
		//FamilyInfo[0][FamilyZone][0] = GangZoneCreate(2063.092285, -1396.866943, 2271.092285, -1220.866943); // ballas
		jau++;
	}
	//KiekYra[4]=1;
	return 1;
}

forward SQL_SaveRaceExists(playerid, racename[]);
public SQL_SaveRaceExists(playerid, racename[]) 
{
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
	if(rows)
	{
		new msg[256];
		format(msg,sizeof(msg), "Lenktynës \"%s\" jau egzistuoja.",racename);
		SendClientMessage(playerid, COLORYR_RED, msg);
		return;
	}
	else
	{
		SaveRace(playerid, racename, /*phase=*/2);
	}
}
forward SQL_LoadRace(playerid, racename[]);
public SQL_LoadRace(playerid, racename[])
{
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
	if(!rows)
	{
		new msg[256];
		format(msg,sizeof(msg), "Lenktynës \"%s\" neegzistuoja.",racename);
		SendClientMessage(playerid, COLORYR_RED, msg);
		return;
	}
	new temp[512];
	cache_get_row(0, 2, temp); // config
	new unused[50], fileversion;
	sscanf(temp,"s[24]is[24]iiif",unused,fileversion,CBuilder, ORacemode, ORacelaps, Airrace, CPsize);
	OAirrace = Airrace;
	OCPsize = CPsize;
	Racemode=ORacemode; Racelaps=ORacelaps; //Allows changing the modes, but disables highscores if they've been changed.

	cache_get_row(0,3, temp);
	new i = 0;
	for(new j=0;j<5;j++)
	{
		TopRacers[j]=strtokex(temp,i);
		TopRacerTimes[j]=strval(strtokex(temp,i));
	}
	cache_get_row(0,4, temp);
	i = 0;
	for(new j=0;j<5;j++)
	{
		TopLappers[j]=strtokex(temp,i);
		TopLapTimes[j]=strval(strtokex(temp,i));
	}
	format(CRaceName, sizeof(CRaceName), racename);
    LCurrentCheckpoint=-1; RLenght=0; RLenght=0;

	i = 0;
	while(i < rows)
	{
		LCurrentCheckpoint++;
		cache_get_row(i, 8, temp), RaceCheckpoints[LCurrentCheckpoint][0] = floatstr(temp);
		cache_get_row(i, 9, temp), RaceCheckpoints[LCurrentCheckpoint][1] = floatstr(temp);
		cache_get_row(i, 10, temp), RaceCheckpoints[LCurrentCheckpoint][2] = floatstr(temp);

		if(LCurrentCheckpoint >= 1)
		{
		    RLenght+=Distance(RaceCheckpoints[LCurrentCheckpoint][0],RaceCheckpoints[LCurrentCheckpoint][1],
								RaceCheckpoints[LCurrentCheckpoint][2],RaceCheckpoints[LCurrentCheckpoint-1][0],
								RaceCheckpoints[LCurrentCheckpoint-1][1],RaceCheckpoints[LCurrentCheckpoint-1][2]);
		}
		i ++;
	}
	LLenght = RLenght + Distance(RaceCheckpoints[LCurrentCheckpoint][0],RaceCheckpoints[LCurrentCheckpoint][1],
								RaceCheckpoints[LCurrentCheckpoint][2],RaceCheckpoints[0][0],RaceCheckpoints[0][1],
								RaceCheckpoints[0][2]);
	LoadRace(playerid, racename, /*phase=*/ 2);
}

forward SQL_ShowRaces(playerid);
public SQL_ShowRaces(playerid)
{
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
	if(!rows)
	{
		SendClientMessage(playerid, COLORYR_RED,  "Lenktyniu nerasta. Ar ivedete pilna zaidejo varda?");
		return;
	}
	new dialogtext[4096];
	
	format(dialogtext,sizeof(dialogtext),"Pavadinimas\tCP");
	new temp[51], pav[50], cpcount;
	new idx = 0;
	while(idx < rows)
	{	
		cache_get_row(idx, 0, pav);
		cache_get_row(idx, 1, temp), cpcount = strval(temp);
		format(dialogtext, 4096, "%s\n%s\t%i",dialogtext, pav, cpcount);
		idx++;
	}
	ShowPlayerDialog(playerid, 14011, DIALOG_STYLE_TABLIST_HEADERS, "Lenktynes", dialogtext, "Gerai","");
}

forward SQL_CheckAcc(playerid);
public SQL_CheckAcc(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows, fields);
	if(!rows) // Jai zaidejo failas neegzistuoja jam ismes registracijos GUI lentele.
	{
		new girismsg[128];
		format(girismsg,128,"{FFFFFF}Labas, {CC0033}%s{FFFFFF}!\n\nIvesk slaptazodi, kuri naudosi veliau.",ReturnName(playerid));
		ShowPlayerDialog(playerid,9876,DIALOG_STYLE_PASSWORD,"Registracija",girismsg,"Regintis","Iseiti");
	}
	else // Jai zaidejo failas egzistuoja tada jam ismes Prisijungimo GUI lentele.
	{
		new temp[12];
		cache_get_row(0, 0, temp);
		new xp = strval(temp);
		cache_get_row(0,1, temp);
		new skinas = strval(temp);
		cache_get_row(0,3, temp);
		new uniformed = strval(temp);
		if(uniformed)
		{
			cache_get_row(0,2, temp);
			skinas = strval(temp);
		}
		if(skinas > 0)
		{
			SetPlayerSkin(playerid, skinas);
			/*cache_get_row(0,4,temp);
			new akiniaiload = strval(temp);
			cache_get_row(0,5,temp);
			new kepureload = strval(temp);
			if(akiniaiload)
			{
				SetPlayerAttachedObject(playerid, AKINIU_SLOT, CommonRed+akiniaiload-1, 2, AkiniuOffSet[skinas][0], AkiniuOffSet[skinas][1], AkiniuOffSet[skinas][2], AkiniuOffSet[skinas][3], AkiniuOffSet[skinas][4], AkiniuOffSet[skinas][5],AkiniuOffSet[skinas][6],AkiniuOffSet[skinas][6]);
			}
			if(kepureload)
			{
				playerDB[playerid][kepure]=kepureload;
				AttachKepure(playerid,skinas);
			}*/
			SetTimerEx("Sokimas",100,false,"i",playerid);
		}
	
		
		SetPVarInt(playerid, "PXP", xp);
		new girismsg[128];
		format(girismsg,128,"{FFFFFF}Labas, {CC0033}%s{FFFFFF}!\n\nIvesk savo slaptazodi.",ReturnName(playerid));
		ShowPlayerDialog(playerid,9877,DIALOG_STYLE_PASSWORD,"Prisijungimas",girismsg,"Prisijungti","Iseiti");
		LoginStart[playerid]=GetTickCount();
	}
	RemoveBuildings(playerid);

	return 1;
}

forward SQL_Whitelist(playerid,ip[]);
public SQL_Whitelist(playerid,ip[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows, fields);
	if(!rows && strcmp(ip, "127.0.0.1", true) != 0 && IsProdEnvironment() && PROXYCHECK_ENABLED)
	{
		new formato[256];

		format(formato, sizeof formato, "blackbox.ipinfo.app/lookup/%s", ip);
		HTTP(playerid, HTTP_GET, formato, "", "MyHttpResponse");
	}
}

forward SQL_DeploymentRestart();
public SQL_DeploymentRestart() 
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows, fields);
	if(!rows) {
		print("Failed to load restart config");
		return;
	}
	new row[125];
	cache_get_row(0, 0, row);
	new delay = strval(row);
	if(delay == 0)
		return;
	HandleRestart(delay);
}

forward SQL_Pending(playerid);
public SQL_Pending(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		new row[512];
		//mysql_fetch_row_format(row," ");
		//mysql_free_result();
		new
			name[MAX_PLAYER_NAME],
			adminname[MAX_PLAYER_NAME],
			reason[128];
		cache_get_row(0, 0, name);
		cache_get_row(0, 1, adminname);
		cache_get_row(0, 2, reason);
		//sscanf(row,"s[24]s[24]s[128]",name,adminname,reason);
		GetPlayerName(playerid,name,MAX_PLAYER_NAME);
		format(row,sizeof(row)," * LSG Pending Bans: %s buvo uþblokuotas administratoriaus %s. Prieþastis: %s.",name,adminname,reason);
		SendClientMessageToAll(RED,row);
		new plrIP[16];
		GetPlayerIp(playerid, plrIP, sizeof(plrIP));
		new query2[256];
		format(query2,sizeof(query2),"INSERT INTO BANS (Vardas,IP,Priezastis,Adminas,Date) VALUES ('%s','%s','%s','%s',NOW())",name,plrIP,reason,adminname);
		mysql_query(query2);
		format(query2,sizeof(query2),"DELETE FROM Pending WHERE `Name`='%s' LIMIT 1",name);
		mysql_query(query2);
		MLog(playerid,"Uzbanino","ss",name,reason);
		new msg[60];
		format(msg,sizeof(msg),"PBan %s",name);
		MLog(playerid,msg,"s",reason);
		SendClientMessage(playerid, RED, " * Jus gavote BAN!");
		SendClientMessage(playerid, RED, " * Jei manote, jog ivyko klaida, tuomet spauskite mygtuka F8, kad pasidarytumete savo irodymus. Ju reikes ban apeliacijai.");
		KickEx(playerid);
		return 0;
	}
	return 1;
}

forward SQL_HBans(playerid);
public SQL_HBans(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows, fields);
	if(rows)
	{
		Kick(playerid);
		return 0;
	}
	return 1;
}

forward SQL_Ban(playerid);
public SQL_Ban(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows)
	{
		new query[128];
		format(query,sizeof(query),"SELECT `Kreditai` FROM `Account` WHERE `Name`='%s' LIMIT 1",ReturnName(playerid));
		//mysql_query(query);
		mysql_function_query(SQL, query, true, "SQL_Ban2", "ii", playerid,rows);
		SetPVarInt(playerid, "PlayerBans", rows);
		playerDB[playerid][banned]=true;
		return 0;
	}
	return 1;

}


forward SQL_Ban2(playerid,bans);
public SQL_Ban2(playerid,bans)
{
	RestartCheck();
	new rowas[20];
	cache_get_row(0,0,rowas);
	playerDB[playerid][kreditai]=strval(rowas);
	playerDB[playerid][banned]=true;
	new msz[128];
	format(msz,128,"Pirkti kreditus(turite %i)\nGauti unban(nuo 20 kreditu)",playerDB[playerid][kreditai]);
	ShowPlayerDialog(playerid, 1990, DIALOG_STYLE_LIST, "Kreditai",msz,"Taip","Ne");
	SendClientMessage(playerid,0x38CF30FF,"Jus esate uþblokuotas. Norëdami toliau þaisti mûsø serveryje naudokite UNBAN paslaugà.");
	new msgas[127];
	if(bans > 1)
		format(msgas,127," * Ðiuo metu turite {00FF00}%i{FFFFFF} banus ant savo vardo ir IP. Unban nuims tik vienà ið jø.",bans);
	SendClientMessage(playerid, -1, msgas);
	TogglePlayerControllable(playerid,false);
	NotSpawned[playerid]=true;
	return 1;
}
forward SQL_LoadKelione(playerid, kelioneid, deleting);
public SQL_LoadKelione(playerid, kelioneid, deleting)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows == 0)
		return SendInfoMessage(playerid, "Tokios keliones nera!");
	if(deleting)
	{
		new query[512];
		format(query,sizeof(query),"DELETE FROM Keliones WHERE id='%i'",kelioneid);
		mysql_query(query);
		format(query,sizeof(query), "DELETE FROM Checkpoints WHERE type='kelione' AND id='%i'",kelioneid);
		mysql_query(query);
		SendInfoMessage(playerid, "Sekmingai istrynei kelione!");
		return 1;
	}
	new row=0;
	new temp[512];
	new pav[100];
	new kurejas[50];
	cache_get_row(0, 1, pav);
	format(Keliones[KelionesPavadinimas],128,pav);
	cache_get_row(0,2, kurejas);
	Keliones[TotalCP] = rows;
    while(row < rows)
    {
		cache_get_row(row, 6, temp), KelionesKurimas[row][koordx] = floatstr(temp);
		cache_get_row(row, 7, temp), KelionesKurimas[row][koordy] = floatstr(temp);
		cache_get_row(row, 8, temp), KelionesKurimas[row][koordz] = floatstr(temp);
		row ++;
    }
	KelionesKurimas[row][koordx]=0.0;
	KelionesKurimas[row][koordy]=0.0;
	KelionesKurimas[row][koordz]=0.0;
	Keliones[Paskutinysis]=row-1;
	Keliones[DabartinisCP]=0;
	new Pranesimas[256];
	new byWho[50];
	if(strlen(kurejas) > 2)
		format(byWho, 50, "by %s", kurejas);
	if(playerid != -1)
		format(Pranesimas,sizeof(Pranesimas), "[racija] Operatore: Direktorius kvieèia prisijungti prie kelionës: %s [%i CP] %s",Keliones[KelionesPavadinimas], Keliones[TotalCP], byWho);
	else
		format(Pranesimas,sizeof(Pranesimas), "[racija] Operatore: Serveris kvieèia prisijungti prie kelionës: %s [%i CP] %s",Keliones[KelionesPavadinimas], Keliones[TotalCP], byWho);
	SendMessageToKlubai(0xFFFFFF30,Pranesimas);
	SendMessageToKlubai(0xFFFFFF30,"[racija] Operatore: Tai padarysite paraðæ /prisijungti");
	Keliones[Ijungta]=true;
	Keliones[Kuriama]=false;
	Keliones[paskutinisCP]=false;
	Keliones[Dalyviai]=0;
	Keliones[Atlygis]=0;
	if(playerid != -1)
		SendInfoMessage(playerid,"Noredami isjungti kelione rasykite /kelione");
	return 1;
}
forward SQL_ShowKeliones(playerid,deleting);
public SQL_ShowKeliones(playerid,deleting)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows == 0)
		return SendInfoMessage(playerid, "Kelioniu nera!");
	new temp[100];
	new id = 0;
	new name[100];
	new author[24];
	new cpcount;
	new row;
	new msgas[4096];
	format(msgas,sizeof(msgas),"ID\tPavadinimas\tKurejas\tCP\n");
	for(new idx=0; idx < 50; idx++)
	{
		// cp, name, cpcount
		if(row < rows) 
		{
			cache_get_row(row, 0, temp), id = strval(temp);
		}
		if(row < rows && id == idx)
		{
			// cp, name, cpcount
			cache_get_row(row, 0, temp), id = strval(temp);
			cache_get_row(row, 1, name);
			cache_get_row(row, 2, author);
			cache_get_row(row, 3, temp), cpcount = strval(temp);
			format(msgas,sizeof(msgas),"%s%i.\t%s\t%s\t%i\n", msgas,id + 1,name,author,cpcount);
			row++;
		}
		else 
		{
			format(msgas,sizeof(msgas),"%s%i.\t<NERA>\t\t\n", msgas,idx + 1);
		}
	}
	if(deleting == 0)
		ShowPlayerDialog(playerid, 8582, DIALOG_STYLE_TABLIST_HEADERS, "Keliones", msgas, "Gerai","Atsaukti");
	else
		ShowPlayerDialog(playerid,8583,DIALOG_STYLE_TABLIST_HEADERS,"Istrinti Keliones",msgas,"Gerai","Atsaukti");
	return 1;
}
forward SQL_SaveKelione(playerid);
public SQL_SaveKelione(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new temp[24];
	new currId = 0;
	new row;
	while(row < rows)
	{
		cache_get_row(row,0,temp);
		if(strval(temp) == currId)
			currId ++;
		row++;
	}
	if(currId >= 49) 
	{
		return SendInfoMessage(playerid,"Kelioniu limitas(50) pasiektas! Istrinkite senas keliones!");
	}

	Keliones[Kuriama]=false;
	Keliones[Kurejas]=-1;

	SaveKelione(currId, playerid);
	for(new i;i<CP;i++)
	{
		KelionesKurimas[i][koordx]=0.0;
		KelionesKurimas[i][koordy]=0.0;
		KelionesKurimas[i][koordz]=0.0;
	}
	CP=0;
	SendClientMessage(playerid, GREEN, " * Kelione sekmingai issaugota!");
	return 1;
}
/*
forward SQL_Pradiniai(playerid);
public SQL_Pradiniai(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows) 
	{
		GivePlayerMoneyA(playerid,COST_PRADINIAI);
	}
	return 1;
}

*/


forward SQL_Ataskaitos(playerid);
public SQL_Ataskaitos(playerid)
{
	RestartCheck();
	new dialogtext[4028],x=GetPVarInt(playerid,"Ataskaitosnr")*40,Nameas[MAX_PLAYER_NAME],Veiksmas[100],Variable[100],Data[30];
	
	new y=0;
	new rows,fields;
	cache_get_data(rows,fields);
	new lolas;
	while(lolas < rows)
	{
		x++;
		y++;
		//sscanf(row,"p<|>s[24]s[100]s[100]s[30]",Nameas,Veiksmas,Variable,Data);
		cache_get_row(lolas,0,Nameas);
		cache_get_row(lolas,1,Veiksmas);
		cache_get_row(lolas,2,Variable);
		cache_get_row(lolas,3,Data); 
		format(dialogtext,4028,"%s%i. %s %s(%s) [%s]\n",dialogtext,x,Nameas,Veiksmas,Variable,Data);
		lolas++;
	}
	if(y)
		ShowPlayerDialog(playerid,9535,DIALOG_STYLE_LIST,"Ataskaita",dialogtext,"Gerai","Toliau");
	return 1;
}

forward SQL_Bagazine(playerid,mid,listitem);
public SQL_Bagazine(playerid,mid,listitem)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows == listitem)
	{
		new row[128];
		format(row,sizeof(row),"SELECT Item From Bagazine Where Vardas='%s' AND Masina=%i",ReturnName(playerid),mid);
		mysql_function_query(SQL, row, true, "SQL_Bagazine2", "i", playerid);
		return 1;
	}
	else
	{	
		playerDB[playerid][daiktas]=listitem;
		new x;
		new Countas; //,Item;
		while(x < rows)
		{
			if(listitem == x)
			{
				//sscanf(row,"p<|>ii",Item,Countas);
				new temp[12];
				//cache_get_row(x,0,temp), Item = strval(temp);
				cache_get_row(x,1,temp), Countas = strval(temp);
				new msg[128];
				format(msg,sizeof(msg),"Kiek norite paimti?\nDaugiausiai galite paimti %i.",Countas);
				ShowPlayerDialog(playerid,1510,DIALOG_STYLE_INPUT,((mid==4)?("Spintele"):("Bagazine")),msg,"Gerai","Atgal");
				break;
			}
			x++;
		}
	}
	//mysql_free_result();
	return 1;
}

forward SQL_Bagazine2(playerid);
public SQL_Bagazine2(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows >= 2)
	{
		if(GetPVarInt(playerid,"Bomba"))
		{
			return SendInfoMessage(playerid,"Bagazineje nera vietos!");
		}
		new temp[12];
		cache_get_row(0,0,temp), BagazinesItems[playerid][0] = strval(temp);
		cache_get_row(1,0,temp), BagazinesItems[playerid][1] = strval(temp);
		new itemname[2][30];
		for(new i;i<2;i++)
		{
			new Item=BagazinesItems[playerid][i];
			if(Item < 50)
			{
				GetWeaponName(Item,itemname[i],30);
			}
			else
			{
				if(Item==50) // nark
				{
					itemname[i]="Seklos";
				}
				else if(Item==51)
				{
					itemname[i]="Zole";
				}	
				else if(Item==52)
				{
					itemname[i]="Amfetaminas";
				}
				else if(Item==53)
				{
					itemname[i]="LSD";
				}
				else if(Item==54)
				{
					itemname[i]="Ekstazis";
				}
				else if(Item==55)
				{
					itemname[i]="Pinigai";
				}
				else if(Item==60)
				{
					itemname[i]="Bomba";
				}
				else if(Item==56)
				{
					itemname[i]="Masalas";
				}
				else if(Item == 57)
				{
					itemname[i]="Zuvis";
				}		
			}	

		}
		new msg[128];
		format(msg,sizeof(msg),"{FF0000}Bagazines limitas - 2 daiktai. Galite papildyti siuos daiktus:\n{FFFFFF}%s\n%s",itemname[0],itemname[1]);
		ShowPlayerDialog(playerid,1499,DIALOG_STYLE_LIST,"Padeti",msg,"Rinktis","Iseiti");
		return 1;
	}
	if(GetPVarInt(playerid,"Bomba"))
	{
		new vehicleid = GetClosestVehicleid(playerid,10.0);
		if(!vehicleid || vehicleid == INVALID_VEHICLE_ID)
			return 0;
		GetVehicleParamsEx(vehicleid,VehVars[0],VehVars[1],VehVars[2],VehVars[3],VehVars[4],VehVars[5],VehVars[6]);
		if(VehVars[5] != VEHICLE_PARAMS_ON) return 1;
		new exas;
		new mid = GetPlayerFromCarlistID(vehicleid, exas);
		if(!mid) return 0;
		AddToBagazine(playerid,mid,60,1);
		RemovePlayerAttachedObject(playerid,SLOT_KROVINYS);
		SetPVarInt(playerid,"Bomba",0);
		ClearAnimations(playerid);
		return 1;
	}
	ShowPlayerDialog(playerid,1501,DIALOG_STYLE_LIST,"Padeti","Ginklas arba gesintuvas\nSeklos\nZole\nAmfetaminas\nLSD\nRatai\nPinigai\nMasalas\nZuvis","Rinktis","Iseiti");
	return 1;
}

forward SQL_UpdateKred5(playerid);
public SQL_UpdateKred5(playerid)
{
	RestartCheck();
	new var[20];
	cache_get_row(0,0,var);
	playerDB[playerid][kreditai]=StringToInt(var);
}
forward SQL_GetSaugykla(playerid,itemid);
public SQL_GetSaugykla(playerid,itemid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(itemid >= rows)
	{
		SendClientMessage(playerid, RED, " * Ivyko klaida!");
		return;
	}
	new temp[30];
	cache_get_row(itemid,0,temp);
	new id = strval(temp);
	SetPVarInt(playerid, "SaugyklosId", id);
	cache_get_row(itemid,2,temp);
	new typ = strval(temp);
	new msg[512];
	new status[24];
	new Float:coo[6];
	GetPlayerPos(playerid,coo[3],coo[4],coo[5]);
	new idas = -1;
	if(Carlist[playerid][Typ] == -1)
	{
		idas = 0;
	}
	else if(Carlist2[playerid][Typ] == -1)
	{
		idas = 1;
	}
	else if(Carlist3[playerid][Typ] == -1)
	{
		idas = 2;
	}
	if(typ == -1 || idas == -1)
	{
	    if(Carlist[playerid][Typ]!=-1)
		{
			if(Carlist[playerid][Status]==0) {
				status = #TEXT_RED"Sprogæs";
			}
			else {
				GetVehiclePos(Carlist[playerid][Carid],coo[0],coo[1],coo[2]);
				new Float:atstumas = ((floatabs(coo[0]-coo[3])+floatabs(coo[1]-coo[4])+floatabs(coo[2]-coo[5]))/3)/100;
				if(GetVehicleVirtualWorld(Carlist[playerid][Carid]))
					status = #TEXT_GREEN"Garaþe";
				else
					format(status,24,#TEXT_GREEN"%.1fkm",atstumas);
			}
		    format(msg,sizeof(msg),#TEXT_BLUE"• "#TEXT_WHITE"%s\t%s",aVehicleNames[Carlist[playerid][Typ]][Name],status);
	        AddDListItem(playerid, msg, 0);
		}
		if(Carlist2[playerid][Typ]!=-1)
		{
			if(Carlist2[playerid][Status]==0) {
				status = #TEXT_RED"Sprogæs";
			}
			else {
				GetVehiclePos(Carlist2[playerid][Carid],coo[0],coo[1],coo[2]);
				new Float:atstumas = ((floatabs(coo[0]-coo[3])+floatabs(coo[1]-coo[4])+floatabs(coo[2]-coo[5]))/3)/100;
				if(GetVehicleVirtualWorld(Carlist2[playerid][Carid]))
					status = #TEXT_GREEN"Garaþe";
				else
					format(status,24,#TEXT_GREEN"%.1fkm",atstumas);
			}
		    format(msg,sizeof(msg),#TEXT_BLUE"• "#TEXT_WHITE"%s\t%s",aVehicleNames[Carlist2[playerid][Typ]][Name],status);
	        AddDListItem(playerid, msg, 1);
		}
		if(Carlist3[playerid][Typ]!=-1)
		{
			if(Carlist3[playerid][Status]==0) {
				status = #TEXT_RED"Sprogæs";
			}
			else {
				GetVehiclePos(Carlist3[playerid][Carid],coo[0],coo[1],coo[2]);
				new Float:atstumas = ((floatabs(coo[0]-coo[3])+floatabs(coo[1]-coo[4])+floatabs(coo[2]-coo[5]))/3)/100;
				if(GetVehicleVirtualWorld(Carlist3[playerid][Carid]))
					status = #TEXT_GREEN"Garaþe";
				else
					format(status,24,#TEXT_GREEN"%.1fkm",atstumas);
			}
		    format(msg,sizeof(msg),#TEXT_BLUE"• "#TEXT_WHITE"%s\t%s",aVehicleNames[Carlist3[playerid][Typ]][Name],status);
	        AddDListItem(playerid, msg, 2);
		}
	}
	if(typ == -1)
	{
		if(strlen(msg) < 1)
		{
			SendInfoMessage(playerid,"~r~Neturi automobiliu!");
			ShowSaugykla(playerid);
			return;
		}
		ShowPlayerDListHeader(playerid, 15538, "Padeti automobili", "Rinktis", "Iseiti","Automobilis\tAtstumas");
		
	}
	else // car exists!
	{
		new CarArray[ahCar]; // used as pointer to store data
		if(idas == -1)
		{
			SendInfoMessage(playerid,"~r~Neturi vietos automobiliui, pasirink kuri nori pastatyti i jo vieta!");
			ShowPlayerDListHeader(playerid, 15539, "Padeti automobili", "Rinktis", "Iseiti","Automobilis\tAtstumas");
		
			return;
		}

		cache_get_row(itemid,2,temp), CarArray[Typ]=strval(temp);
		cache_get_row(itemid,3,temp), CarArray[X]=floatstr(temp);
		cache_get_row(itemid,4,temp), CarArray[Y]=floatstr(temp);
		cache_get_row(itemid,5,temp), CarArray[Z]=floatstr(temp);
		cache_get_row(itemid,6,temp), CarArray[Rotation]=floatstr(temp);
		cache_get_row(itemid,7,temp), CarArray[Status]=strval(temp);
		cache_get_row(itemid,8,temp), CarArray[Lock]=strval(temp);
		cache_get_row(itemid,9,temp), CarArray[Paintjob]=strval(temp);
		cache_get_row(itemid,10,temp), CarArray[Color1]=strval(temp);
		cache_get_row(itemid,11,temp), CarArray[Color2]=strval(temp);
		cache_get_row(itemid,12,temp), CarArray[mod1]=strval(temp);
		cache_get_row(itemid,13,temp), CarArray[mod2]=strval(temp);
		cache_get_row(itemid,14,temp), CarArray[mod3]=strval(temp);
		cache_get_row(itemid,15,temp), CarArray[mod4]=strval(temp);
		cache_get_row(itemid,16,temp), CarArray[mod5]=strval(temp);
		cache_get_row(itemid,17,temp), CarArray[mod6]=strval(temp);
		cache_get_row(itemid,18,temp), CarArray[mod7]=strval(temp);
		cache_get_row(itemid,19,temp), CarArray[mod8]=strval(temp);
		cache_get_row(itemid,20,temp), CarArray[mod9]=strval(temp);
		cache_get_row(itemid,21,temp), CarArray[mod10]=strval(temp);
		cache_get_row(itemid,22,temp), CarArray[mod11]=strval(temp);
		cache_get_row(itemid,23,temp), CarArray[mod12]=strval(temp);
		cache_get_row(itemid,24,temp), CarArray[mod13]=strval(temp);
		cache_get_row(itemid,25,temp), CarArray[mod14]=strval(temp);
		cache_get_row(itemid,26,temp), CarArray[mod15]=strval(temp);
		cache_get_row(itemid,27,temp), CarArray[mod16]=strval(temp);
		cache_get_row(itemid,28,temp), CarArray[mod17]=strval(temp);
		
		cache_get_row(itemid,29,temp), CarArray[Gas]=strval(temp);
		
		cache_get_row(itemid,30,temp), CarArray[Sirena]=strval(temp);

		cache_get_row(itemid,31,CarArray[NumPlate],SQL,40);

		cache_get_row(itemid,32,temp), CarArray[Energy]=strval(temp);

		cache_get_row(itemid,33,temp), CarArray[VirtualW]=strval(temp);
		
		cache_get_row(itemid,34,temp), CarArray[CDraud]=strval(temp);
		
		cache_get_row(itemid,35,temp), CarArray[Rankinis]=strval(temp);
		cache_get_row(itemid,36,temp), CarArray[VeHP]=floatstr(temp);

		cache_get_row(itemid,37,temp), CarArray[Rida]=floatstr(temp);

		if(idas == 0)
		{
			Carlist[playerid] = CarArray;
			if(CarArray[Typ]!=-1 && CarArray[Status]==1)
			{
				Carlist[playerid][Carid] = CreateTunedCar(playerid);
			}
		}
		else if(idas == 1)
		{
			Carlist2[playerid] = CarArray;
			if(CarArray[Typ]!=-1 && CarArray[Status]==1)
			{
				Carlist2[playerid][Carid] = CreateTunedCar2(playerid);
			}
		}
		else if(idas == 2)
		{
			Carlist3[playerid] = CarArray;
			if(CarArray[Typ]!=-1 && CarArray[Status]==1)
			{
				Carlist3[playerid][Carid] = CreateTunedCar3(playerid);
			}
		}
		new query[128];
		format(query,128,"Update CarSaugykla Set Typ=-1 WHERE Vardas='%s' AND Id='%i'",ReturnName(playerid),id);
		mysql_query(query);
		SendInfoMessage(playerid,"~g~Sekmingai pasiemei automobili! Jis atsirado parkavimo vietoje.");
		printf("[car saugykla] %s paeme automobili id %i modelis %i is saugyklos i id %i. Rida %.2f",ReturnName(playerid),itemid,CarArray[Typ],idas,CarArray[Rida]);
		ShowSaugykla(playerid);
	}
}
forward SQL_GetSaugykla2(playerid,idas);
public SQL_GetSaugykla2(playerid,idas)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new itemid = 0;
	if(itemid >= rows)
	{
		SendClientMessage(playerid, RED, " * Ivyko klaida!");
		return;
	}
	new temp[30];
	// pasiruosiam padeti auto

	// paloadinam nauja auto
	new CarArray[ahCar]; // used as pointer to store data

	cache_get_row(itemid,2,temp), CarArray[Typ]=strval(temp);
	cache_get_row(itemid,3,temp), CarArray[X]=floatstr(temp);
	cache_get_row(itemid,4,temp), CarArray[Y]=floatstr(temp);
	cache_get_row(itemid,5,temp), CarArray[Z]=floatstr(temp);
	cache_get_row(itemid,6,temp), CarArray[Rotation]=floatstr(temp);
	cache_get_row(itemid,7,temp), CarArray[Status]=strval(temp);
	cache_get_row(itemid,8,temp), CarArray[Lock]=strval(temp);
	cache_get_row(itemid,9,temp), CarArray[Paintjob]=strval(temp);
	cache_get_row(itemid,10,temp), CarArray[Color1]=strval(temp);
	cache_get_row(itemid,11,temp), CarArray[Color2]=strval(temp);
	cache_get_row(itemid,12,temp), CarArray[mod1]=strval(temp);
	cache_get_row(itemid,13,temp), CarArray[mod2]=strval(temp);
	cache_get_row(itemid,14,temp), CarArray[mod3]=strval(temp);
	cache_get_row(itemid,15,temp), CarArray[mod4]=strval(temp);
	cache_get_row(itemid,16,temp), CarArray[mod5]=strval(temp);
	cache_get_row(itemid,17,temp), CarArray[mod6]=strval(temp);
	cache_get_row(itemid,18,temp), CarArray[mod7]=strval(temp);
	cache_get_row(itemid,19,temp), CarArray[mod8]=strval(temp);
	cache_get_row(itemid,20,temp), CarArray[mod9]=strval(temp);
	cache_get_row(itemid,21,temp), CarArray[mod10]=strval(temp);
	cache_get_row(itemid,22,temp), CarArray[mod11]=strval(temp);
	cache_get_row(itemid,23,temp), CarArray[mod12]=strval(temp);
	cache_get_row(itemid,24,temp), CarArray[mod13]=strval(temp);
	cache_get_row(itemid,25,temp), CarArray[mod14]=strval(temp);
	cache_get_row(itemid,26,temp), CarArray[mod15]=strval(temp);
	cache_get_row(itemid,27,temp), CarArray[mod16]=strval(temp);
	cache_get_row(itemid,28,temp), CarArray[mod17]=strval(temp);
	
	cache_get_row(itemid,29,temp), CarArray[Gas]=strval(temp);
	
	cache_get_row(itemid,30,temp), CarArray[Sirena]=strval(temp);

	cache_get_row(itemid,31,CarArray[NumPlate],SQL,40);

	cache_get_row(itemid,32,temp), CarArray[Energy]=strval(temp);

	cache_get_row(itemid,33,temp), CarArray[VirtualW]=strval(temp);
	
	cache_get_row(itemid,34,temp), CarArray[CDraud]=strval(temp);
	
	cache_get_row(itemid,35,temp), CarArray[Rankinis]=strval(temp);
	cache_get_row(itemid,36,temp), CarArray[VeHP]=floatstr(temp);

	cache_get_row(itemid,37,temp), CarArray[Rida]=floatstr(temp);

	// padedam sena auto

	if(PadetiMasina(playerid,idas) == 0)
        return;

	// swap
	if(idas == 0)
	{
		Carlist[playerid] = CarArray;
		if(CarArray[Typ]!=-1 && CarArray[Status]==1)
		{
			Carlist[playerid][Carid] = CreateTunedCar(playerid);
		}
	}
	else if(idas == 1)
	{
		Carlist2[playerid] = CarArray;
		if(CarArray[Typ]!=-1 && CarArray[Status]==1)
		{
			Carlist2[playerid][Carid] = CreateTunedCar2(playerid);
		}
	}
	else if(idas == 2)
	{
		Carlist3[playerid] = CarArray;
		if(CarArray[Typ]!=-1 && CarArray[Status]==1)
		{
			Carlist3[playerid][Carid] = CreateTunedCar3(playerid);
		}
	}


	SendInfoMessage(playerid,"~g~Sekmingai pasiemei automobili! Jis atsirado parkavimo vietoje.");
	ShowSaugykla(playerid);
}

forward SQL_CarSaugykla(playerid);
public SQL_CarSaugykla(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new carlist[5000];
	format(carlist,sizeof(carlist),"Vieta\tAutomobilis\tRida\n");
	new x;
	while(x<rows)
	{
		new temp[30]; new id;
		cache_get_row(x,0,temp);
		new ridaz[24];
		cache_get_row(x,1,ridaz);
		id=strval(temp);
		if(id == -1)
			format(carlist,sizeof(carlist),"%s%i.\tLaisva vieta\t\n",carlist,x+1);
		else
		{
			format(carlist,sizeof(carlist),"%s%i.\t%s\t%skm\n",carlist,x+1,aVehicleNames[id][Name],ridaz);
		}
		x++;
	}
	SetPVarInt(playerid, "PirktiSaugykla", x);
	if(x < 50)
	{
		format(carlist,sizeof(carlist),"%s%i.\t{FF0000}Pirkti vietà...",carlist,x+1);
	}
	new title[120];
	format(title,120,"Transport saugykla (%i/50)", x);
	ShowPlayerDialog(playerid, 15535, DIALOG_STYLE_TABLIST_HEADERS, title, carlist, "Gerai","Atsaukti");
}
forward SQL_GetEggs(playerid);
public SQL_GetEggs(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new x;
	while(x<rows)
	{
		new temp[30]; new id;
		cache_get_row(x,0,temp);
		id=strval(temp);
		EggFound[playerid][id]=1;
		x++;
	}
	
}

forward SQL_GetProgress(playerid);
public SQL_GetProgress(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new x;
	while(x<rows)
	{
		new temp[30]; new id;
		cache_get_row(x,0,temp);
		id=strval(temp);
		cache_get_row(x,1,temp);
		Achievements[playerid][id]=floatstr(temp);
		x++;
	}
	
}
forward SQL_XPCheck(playerid);
public SQL_XPCheck(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	PendingBan(playerid);
	if(!rows)
	{
		playerDB[playerid][authstate]=4;
		return 1;
	}
	new temp[40];
	cache_get_row(0,1,temp);
	playerDB[playerid][pgang] = strval(temp);
	new expas[20];
	cache_get_row(0,0,expas);
	if(0==strcmp(expas,"NULL",true)) format(expas,20,"0");
	if(!strval(expas))
	{
		new ipas[20];
		GetPlayerIp(playerid,ipas,sizeof(ipas));
		new queryx[128];
		format(queryx,sizeof(queryx),"SELECT 1 FROM `Account` WHERE `Xp`>0 AND `IP`='%s'",ipas);
		//mysql_function_query(SQL, queryx, true, "SQL_Pradiniai", "i", playerid);
		if(GetPlayerMoneyA(playerid) == 0)
		{
			GivePlayerMoneyA(playerid,COST_PRADINIAI);
			playerDB[playerid][banke]+=2000;
		}
		SetPlayerPoz(playerid,1743.1915,-1944.5928,13.5661);
		SetPlayerFacingAngle(playerid,173.6375);
		SetCameraBehindPlayer(playerid);
		playerDB[playerid][authstate]=4;
		return 1;
	}
	GameTextForPlayer(playerid,"~r~] Kraunamas Tavo zaidimas ]",50000,5);
	new file[256];
	format(file,sizeof(file),"SELECT * FROM `Account` WHERE Name = '%s' LIMIT 1",ReturnName(playerid));
	mysql_function_query(SQL, file, true, "SQL_LoadGame", "i", playerid);
	return 1;
}
forward SQL_LoadGame(playerid);
public SQL_LoadGame(playerid)
{
	RestartCheck();
	new 
		IpString[24],
		Float:Coo[3],
		Float:HP,Float:Armour,
		WA[24],
		value[8],
		temp[30];
	//mysql_fetch_row_format(row,"|");
	cache_get_row(0,2,temp), value[0] = strval(temp);
	cache_get_row(0,3,temp), playerDB[playerid][banke] = strval(temp);
	cache_get_row(0,4,temp), playerDB[playerid][seklos] = strval(temp);
	cache_get_row(0,5,temp), playerDB[playerid][zole] = strval(temp);
	cache_get_row(0,7,temp), value[1] = strval(temp);
	cache_get_row(0,8,temp), playerDB[playerid][pgang] = strval(temp);
	cache_get_row(0,9,temp), playerDB[playerid][kalejimo_laikas] = strval(temp);
	cache_get_row(0,10,temp), value[2] = strval(temp);
	cache_get_row(0,11,temp), playerDB[playerid][mobsas] = strval(temp);
	cache_get_row(0,12,temp), playerDB[playerid][namu] = strval(temp);

	
	cache_get_row(0,13,temp), WA[0] = strval(temp);
	cache_get_row(0,14,temp), WA[1] = strval(temp);
	cache_get_row(0,15,temp), WA[2] = strval(temp);
	cache_get_row(0,16,temp), WA[3] = strval(temp);
	cache_get_row(0,17,temp), WA[4] = strval(temp);
	cache_get_row(0,18,temp), WA[5] = strval(temp);
	cache_get_row(0,19,temp), WA[6] = strval(temp);
	cache_get_row(0,20,temp), WA[7] = strval(temp);
	cache_get_row(0,21,temp), WA[8] = strval(temp);
	cache_get_row(0,22,temp), WA[9] = strval(temp);
	cache_get_row(0,23,temp), WA[10] = strval(temp);
	cache_get_row(0,24,temp), WA[11] = strval(temp);
	cache_get_row(0,25,temp), WA[12] = strval(temp);
	cache_get_row(0,26,temp), WA[13] = strval(temp);
	cache_get_row(0,27,temp), WA[14] = strval(temp);
	cache_get_row(0,28,temp), WA[15] = strval(temp);
	cache_get_row(0,29,temp), WA[16] = strval(temp);
	cache_get_row(0,30,temp), WA[17] = strval(temp);
	cache_get_row(0,31,temp), WA[18] = strval(temp);
	cache_get_row(0,32,temp), WA[19] = strval(temp);
	cache_get_row(0,33,temp), WA[20] = strval(temp);
	cache_get_row(0,34,temp), WA[21] = strval(temp);
	cache_get_row(0,35,temp), WA[22] = strval(temp);
	cache_get_row(0,36,temp), WA[23] = strval(temp);
	
	cache_get_row(0,37,temp), playerDB[playerid][pFS] = strval(temp);
	cache_get_row(0,38,temp), playerDB[playerid][pBoxiSkill] = strval(temp);
	cache_get_row(0,39,temp), playerDB[playerid][pKneeSkill] = strval(temp);
	cache_get_row(0,40,temp), playerDB[playerid][pKungSkill] = strval(temp);
	cache_get_row(0,41,temp), playerDB[playerid][pGrabSkill] = strval(temp);
	cache_get_row(0,42,temp), playerDB[playerid][pElbowSkill] = strval(temp);
	cache_get_row(0,43,temp), playerDB[playerid][specialybe] = strval(temp);
	cache_get_row(0,44,temp), playerDB[playerid][drabuziai] = strval(temp);
	cache_get_row(0,45,temp), playerDB[playerid][uniforma] = strval(temp);
	
	cache_get_row(0,46,temp), playerDB[playerid][uniformd] = !!strval(temp);
	cache_get_row(0,47,temp), playerDB[playerid][admin] = !!strval(temp);
	playerDB[playerid][logina] = playerDB[playerid][admin];
	
	cache_get_row(0,48,temp), value[3] = strval(temp);
	cache_get_row(0,49,temp), playerDB[playerid][lytis] = strval(temp);
	
	cache_get_row(0,50,temp), Coo[0] = floatstr(temp);
	cache_get_row(0,51,temp), Coo[1] = floatstr(temp);
	cache_get_row(0,52,temp), Coo[2] = floatstr(temp); 
	
	cache_get_row(0,53,temp), value[4] = strval(temp);
	cache_get_row(0,54,temp), playerDB[playerid][amfetaminas] = strval(temp);
	
	cache_get_row(0,55,temp), playerDB[playerid][teisesm] = !!strval(temp);
	cache_get_row(0,56,temp), playerDB[playerid][teisess] = !!strval(temp);
	cache_get_row(0,57,temp), playerDB[playerid][laikrodis] = !!strval(temp);
	
	cache_get_row(0,58,temp), value[5] = strval(temp);
	cache_get_row(0,59,temp), value[6] = strval(temp);
	
	cache_get_row(0,60,temp), playerDB[playerid][draudimas] = strval(temp);
	if(playerDB[playerid][draudimas] > 250) playerDB[playerid][draudimas]=250;
	cache_get_row(0,61,temp), playerDB[playerid][teises] = !!strval(temp);
	cache_get_row(0,62,temp), playerDB[playerid][teor] = !!strval(temp);
	cache_get_row(0,63,temp), playerDB[playerid][kortele] = !!strval(temp);
	cache_get_row(0,64,temp), playerDB[playerid][imtuvas] = !!strval(temp);
	
	cache_get_row(0,65,IpString);
	
	cache_get_row(0,66,temp), playerDB[playerid][plead] = strval(temp);
	cache_get_row(0,67,temp), playerDB[playerid][kreditai] = strval(temp);
	
	cache_get_row(0,68,temp), value[7] = strval(temp);
	cache_get_row(0,69,temp), playerDB[playerid][raktas] = strval(temp);
	cache_get_row(0,70,temp), playerDB[playerid][pradirbo] = strval(temp);

	cache_get_row(0,71,temp), playerDB[playerid][fejerverkai][0] = !!strval(temp);
	cache_get_row(0,72,temp), playerDB[playerid][fejerverkai][1] = !!strval(temp);
	cache_get_row(0,73,temp), playerDB[playerid][fejerverkai][2] = !!strval(temp);
	cache_get_row(0,74,temp), playerDB[playerid][fejerverkai][3] = !!strval(temp);
	cache_get_row(0,75,temp), playerDB[playerid][fejerverkai][4] = !!strval(temp);
	cache_get_row(0,76,temp), playerDB[playerid][fejerverkai][5] = !!strval(temp);
	cache_get_row(0,77,temp), playerDB[playerid][fejerverkai][6] = !!strval(temp);
	cache_get_row(0,78,temp), playerDB[playerid][fejerverkai][7] = !!strval(temp);
	
	cache_get_row(0,79,temp), playerDB[playerid][akiniai] = strval(temp);
	cache_get_row(0,80,temp), playerDB[playerid][zuvis] = strval(temp);
	cache_get_row(0,81,temp), playerDB[playerid][masalas] = strval(temp);
	
	cache_get_row(0,82,temp), playerDB[playerid][sotumas] = floatstr(temp);
	
	cache_get_row(0,83,temp), playerDB[playerid][lsd] = strval(temp);
	cache_get_row(0,84,temp), playerDB[playerid][ratai] = strval(temp);
	cache_get_row(0,85,temp), playerDB[playerid][kepure] = strval(temp);
	cache_get_row(0,86,temp), playerDB[playerid][salmas] = strval(temp);
	cache_get_row(0,87,temp), playerDB[playerid][cigaretes] = strval(temp);
	//new checkconfig;
	cache_get_row(0,88,temp), HP = floatstr(temp);
	cache_get_row(0,89,temp), Armour = floatstr(temp);
	cache_get_row(0,90,temp), PConfig[playerid]= PCFG:strval(temp);
	cache_get_row(0,91,temp), playerDB[playerid][jobpts]=strval(temp);
	cache_get_row(0,92,temp), playerDB[playerid][bakelis]=!!strval(temp);
	cache_get_row(0,93,temp), playerDB[playerid][pligonis]=strval(temp);
	cache_get_row(0,94,temp), playerDB[playerid][loterijos]=strval(temp);
	cache_get_row(0,95,temp), playerDB[playerid][adr]=strval(temp);
	if(playerDB[playerid][kepure]>=sizeof(Kepures))
	{
		playerDB[playerid][kepure]=0;
	}

	if(BitFlag_Get(PConfig[playerid],PCFG_PASISLEPES))
	{
		TextDrawShowForPlayer(playerid, SleptisTD);
		playerDB[playerid][pasislepes]=true;
	}
	else
	{
			TextDrawHideForPlayer(playerid, SleptisTD);
			playerDB[playerid][pasislepes]=false;
	}

	ResetPlayerMoneyA(playerid);
	GivePlayerMoneyA(playerid,value[0]);
	SetPlayerWantedLevel(playerid,value[1]);

	playerDB[playerid][authstate]=4;

	new i=0,amo;
	while(i<24)
	{
		amo=i+1;
		if(WA[i])
		{
			GivePlayerWeaponEx(playerid,WA[i],WA[amo]);
		}
		i+=2;
	}

	SetPlayerScore(playerid,value[3]);
	//SetPlayerPoz(playerid,Coo[0],Coo[1],Coo[2]);
	SetPlayerPoz(playerid,Coo[0],Coo[1],Coo[2],value[4],value[6]);
	SetPlayerHealth(playerid,HP);
	SetPlayerArmour(playerid,Armour);
	new msa[80];
	playerDB[playerid][vip]=!!value[7];
	if(playerDB[playerid][vip])
	{
		format(msa,sizeof(msa)," * Jusu vip galios dar %i d.",value[7]);
		SendClientMessage(playerid,YELLOW,msa);
	}
	playerDB[playerid][spaz]=!!value[2];
	if(playerDB[playerid][spaz])
	{
		format(msa,sizeof(msa)," * Jusu sveikatos pazymejimas galios dar %i d.",value[2]);
		SendClientMessage(playerid,COLOR,msa);
	}
	playerDB[playerid][draudimasg]=!!value[5];
	if(playerDB[playerid][draudimasg])
	{
		format(msa,sizeof(msa)," * Jusu sveikatos draudimas galios dar %i d.",value[5]);
		SendClientMessage(playerid,RED,msa);
	}
	if(playerDB[playerid][pligonis])
	{
		format(msa,sizeof(msa)," * Jusu privacios ligonines abonimentas galios dar %i d.",playerDB[playerid][pligonis]);
		SendClientMessage(playerid,GREEN,msa);
	}
	//SendClientMessage(playerid, WHITE, " * LSG Kalëdø eventas: /kaledos");

	//SendClientMessage(playerid,YELLOW," * Kvieciame dalyvauti musu velykiniam evente: /kiausinis");
	//SendClientMessage(playerid,WHITE," * Noredami rasti kaledu event, rasykite /kaledos");
	if(playerDB[playerid][admin])
	{
		/*AllowPlayerTeleport(playerid,true);
		playerDB[playerid][logina]=true;*/
		TextDrawShowForPlayer(playerid,LogTD);
	}
	/*else
		AllowPlayerTeleport(playerid,false);*/
	


	if(playerDB[playerid][kalejimo_laikas]>0)
	{
		//SetTimerEx("UnjailPlayer",playerDB[playerid][kalejimo_laikas]*1000,0,"iffffi",playerid,3180.9961,-966.1835,293.3473,365.3682,0);
		playerDB[playerid][kalejimo_total]=playerDB[playerid][kalejimo_laikas];
		playerDB[playerid][ikalintas]=true;
	}

	if(playerDB[playerid][pgang]!=-1 && 0==strcmp(FamilyInfo[playerDB[playerid][pgang]][FamilyLeader],"Nera",true))
	{
		playerDB[playerid][pgang]=-1;
	}

	if(playerDB[playerid][drabuziai] == -1 || playerDB[playerid][drabuziai] == 0 || playerDB[playerid][drabuziai] == 1) playerDB[playerid][drabuziai]=20;

	if(playerDB[playerid][uniformd] && playerDB[playerid][uniforma] != -1) {
		SetTimerEx("Antigodmode", 5000, false, "iii",playerid,1,playerDB[playerid][uniforma]);
		SetPlayerSkin(playerid,playerDB[playerid][uniforma]);
	}
	else {
		SetTimerEx("Antigodmode", 5000, false, "iii",playerid,0,playerDB[playerid][drabuziai]);
		SetPlayerSkin(playerid,playerDB[playerid][drabuziai]);
	}


	new skinid = GetPlayerSkin(playerid);
	if(skinid==-1) SetPlayerSkin(playerid, 20), skinid=20;
	if (playerDB[playerid][laikrodis])
		TextDrawShowForPlayer(playerid, TextdrawTime);//Time
		
	if(playerDB[playerid][akiniai])
	{
		SetPlayerAttachedObject(playerid, AKINIU_SLOT, CommonRed+playerDB[playerid][akiniai]-1, 2, AkiniuOffSet[skinid][0], AkiniuOffSet[skinid][1], AkiniuOffSet[skinid][2], AkiniuOffSet[skinid][3], AkiniuOffSet[skinid][4], AkiniuOffSet[skinid][5],AkiniuOffSet[skinid][6],AkiniuOffSet[skinid][6]);
	}
	if(playerDB[playerid][kepure])
	{
		AttachKepure(playerid,skinid);
	}
	if (playerDB[playerid][ikalintas])
	{
//	SetPlayerPoz(playerid,264.1211,82.7391,1001.0391);
		if(random(2) == 0)
		{
			SetPlayerPoz(playerid,3091.0691,-1507.0050,107.7223);
		}
		else
		{
			SetPlayerPoz(playerid,3091.0193,-1525.4700,107.7223);
		}
		SetTimerEx("Freeze",100,false,"i",playerid);
		SetPlayerVirtualWorld(playerid, 0);
	}
	
	SetPlayerSkills(playerid);

	GameTextForPlayer(playerid,"~r~] Tavo duomenys ikelti ]",5000,5);

	new file[128];
	format(file,sizeof(file),"SELECT 0 FROM `Emails` WHERE UPPER(`Reciever`)=UPPER('%s') AND `New`=1",ReturnName(playerid));
	mysql_function_query(SQL, file, true, "SQL_NewEmail", "i", playerid);
	format(file,sizeof(file),"SELECT variable from Config Where value='%s'",ReturnName(playerid));
	mysql_function_query(SQL, file, true, "SQL_LoadPareigos", "i", playerid);
	format(file,sizeof(file),"SELECT Color From Spalvos Where Vardas='%s' AND `Set`=1",ReturnName(playerid));
	mysql_function_query(SQL, file, true, "SQL_LoadSpalva", "i", playerid);
	format(file,sizeof(file),"SELECT SUM(`Variable`) from `Logs` WHERE Zaidejas='%s' AND Veiksmas='LSD' AND Data > SUBDATE(NOW(), 1)",ReturnName(playerid));
	mysql_function_query(SQL, file, true, "SQL_LoadNark", "ii", playerid,0);
	format(file,sizeof(file),"SELECT SUM(`Variable`) from `Logs` WHERE Zaidejas='%s' AND Veiksmas='Ratai' AND Data > SUBDATE(NOW(), 1)",ReturnName(playerid));
	mysql_function_query(SQL, file, true, "SQL_LoadNark", "ii", playerid,1);
	format(file,sizeof(file),"SELECT SUM(`Variable`) from `Logs` WHERE Zaidejas='%s' AND Veiksmas='Amfa' AND Data > SUBDATE(NOW(), 1)",ReturnName(playerid));
	mysql_function_query(SQL, file, true, "SQL_LoadNark", "ii", playerid,2);
	Masina(playerid);
	CheckForUnban(playerid);
	RenderTexts(playerid);
	LoadNTA(playerid);
	LoadKeyBinds(playerid);
	ZolesStats(playerid, -1);
	SetTimerEx("LoadRadio", 500, false, "i", playerid);
	SetTimerEx("LoadPlayerKVS", 3000, false, "i", playerid);
	return 1;
}
forward SQL_LoadNark(playerid,type);
public SQL_LoadNark(playerid,type)
{
	RestartCheck();
	new lolas[23], value;
	cache_get_row(0,0,lolas); value=strval(lolas);
	if(value > 0) CheckNarkomanas(playerid,type,0);// playerDB[playerid][narko][type]=1;
	return 1;
}
forward SQL_LoadSpalva(playerid);
public SQL_LoadSpalva(playerid)
{
	RestartCheck();
	new fields,rows;
	cache_get_data(rows,fields);
	if(rows)
	{
		new color,lolas[40];
		cache_get_row(0,0,lolas);
		color = hexstr(lolas);
		if(color == 0xCCCCCCFF) color = 0xA8A8A8FF;
		SetPlayerColor(playerid,color);
	}
	return 1;
}

forward SQL_LoadPareigos(playerid);
public SQL_LoadPareigos(playerid)
{
	RestartCheck();
	new fields,rows;
	cache_get_data(rows,fields);
	new lolas[40];
	new x;
	while(x<rows)
	{
		cache_get_row(x,0,lolas);
		SetPVarInt(playerid,lolas,1);
		x++;
	}
	return 1;
}
forward SQL_NewEmail(playerid);
public SQL_NewEmail(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows)
	{
		new msa[128];
		SetTimerEx("GavaiEmail",7000,false,"i",playerid);
		if(rows >= 10)
			format(msa,sizeof(msa)," * Turite {51A0D5}%i{FFFFFF} naujø el. laiðkø (/email).",rows);
		else
			format(msa,sizeof(msa)," * Turite {51A0D5}%i{FFFFFF} naujus el. laiðkus (/email).",rows);
		SendClientMessage(playerid,-1,msa);

	}

	return 1;
}

forward SQL_Houses();
public SQL_Houses()
{
	RestartCheck();
	new 
		houseid,
		zinute[256],temp[25];
	new rows,fields;
	cache_get_data(rows,fields);
	new x;
	while(x<rows)
	{
		cache_get_row(x,0,temp), houseid = strval(temp);
		//print(temp);
		cache_get_row(x,1,hInfo[houseid][Name],SQL,24);
		cache_get_row(x,2,hInfo[houseid][Renter],SQL,24);
		cache_get_row(x,3,temp), hInfo[houseid][Rentable] = strval(temp);
		cache_get_row(x,4,temp), hInfo[houseid][Rentcost] = strval(temp);
		cache_get_row(x,5,temp), hInfo[houseid][Cost] = strval(temp);
		cache_get_row(x,6,temp), hInfo[houseid][Locked] = strval(temp);
		cache_get_row(x,9,temp), hInfo[houseid][vidus] = strval(temp);
		cache_get_row(x,10,temp), hInfo[houseid][iconx] = floatstr(temp);
		cache_get_row(x,11,temp), hInfo[houseid][icony] = floatstr(temp);
		cache_get_row(x,12,temp), hInfo[houseid][iconz] = floatstr(temp);
		cache_get_row(x,13,temp), hInfo[houseid][zole] = strval(temp);
		cache_get_row(x,14,temp), hInfo[houseid][pinigai] = strval(temp);
		cache_get_row(x,15,temp), hInfo[houseid][kulkos][0] = strval(temp);
		cache_get_row(x,16,temp), hInfo[houseid][gunas][0] = strval(temp);
		cache_get_row(x,17,temp), hInfo[houseid][kulkos][1] = strval(temp);
		cache_get_row(x,18,temp), hInfo[houseid][gunas][1] = strval(temp);
		cache_get_row(x,19,temp), hInfo[houseid][kulkos][2]= strval(temp);
		cache_get_row(x,20,temp), hInfo[houseid][gunas][2] = strval(temp);
		cache_get_row(x,21,temp), hInfo[houseid][kulkos][3] = strval(temp);
		cache_get_row(x,22,temp), hInfo[houseid][gunas][3] = strval(temp);
		cache_get_row(x,23,temp), hInfo[houseid][kulkos][4] = strval(temp);
		cache_get_row(x,24,temp), hInfo[houseid][gunas][4] = strval(temp);
		cache_get_row(x,25,temp), hInfo[houseid][kulkos][5] = strval(temp);
		cache_get_row(x,26,temp), hInfo[houseid][gunas][5] = strval(temp);
		cache_get_row(x,27,temp), hInfo[houseid][kulkos][6] = strval(temp);
		cache_get_row(x,28,temp), hInfo[houseid][gunas][6] = strval(temp);
		cache_get_row(x,29,temp), hInfo[houseid][kulkos][7] = strval(temp);
		cache_get_row(x,30,temp), hInfo[houseid][gunas][7] = strval(temp);
		cache_get_row(x,31,temp), hInfo[houseid][kulkos][8] = strval(temp);
		cache_get_row(x,32,temp), hInfo[houseid][gunas][8] = strval(temp);
		cache_get_row(x,33,temp), hInfo[houseid][kulkos][9] = strval(temp);
		cache_get_row(x,34,temp), hInfo[houseid][gunas][9] = strval(temp);
		cache_get_row(x,35,temp), hInfo[houseid][kulkos][10] = strval(temp);
		cache_get_row(x,36,temp), hInfo[houseid][gunas][10] = strval(temp);
		cache_get_row(x,37,temp), hInfo[houseid][kulkos][11] = strval(temp);
		cache_get_row(x,38,temp), hInfo[houseid][gunas][11] = strval(temp);
		cache_get_row(x,39,temp), hInfo[houseid][krumeliai] = strval(temp);
		cache_get_row(x,40,temp), hInfo[houseid][dregme] = strval(temp);
		cache_get_row(x,41,temp), hInfo[houseid][bukle] = strval(temp);
		cache_get_row(x,42,temp), hInfo[houseid][amzius] = strval(temp);
		cache_get_row(x,43,temp), hInfo[houseid][nark] = strval(temp);
		cache_get_row(x,44,temp), hInfo[houseid][hmaistas] = strval(temp);
		cache_get_row(x,45,temp), hInfo[houseid][lsd] = strval(temp);
		cache_get_row(x,46,temp), hInfo[houseid][ratai] = strval(temp);
		cache_get_row(x,47,temp), hInfo[houseid][seklos] = strval(temp);
		cache_get_row(x,48,temp), hInfo[houseid][hRadio] = strval(temp);
		cache_get_row(x,49,temp), hInfo[houseid][Garazas] = strval(temp);
		cache_get_row(x,50,temp), hInfo[houseid][GarazoX] = floatstr(temp);
		cache_get_row(x,51,temp), hInfo[houseid][GarazoY] = floatstr(temp);
		cache_get_row(x,52,temp), hInfo[houseid][GarazoZ] = floatstr(temp);
		cache_get_row(x,53,temp), hInfo[houseid][GarazoA] = floatstr(temp);
		cache_get_row(x,54,temp), hInfo[houseid][tobulina] = strval(temp);
		cache_get_row(x,55,temp), hInfo[houseid][daugiabutis] = strval(temp);
		cache_get_row(x,56,temp), hInfo[houseid][hMokesciai]=strval(temp);
		cache_get_row(x,57,temp), hInfo[houseid][polyId]=strval(temp);

		Iter_Add(Houses, houseid);
		
		if(hInfo[houseid][tobulina]) SetTimerEx("Tobulinti",2*60*60*1000,false,"i",houseid);
		hInfo[houseid][islauztos]=0;
		//Inter[ hInfo[housenumber][vidus] ][ IntX ],Inter[ hInfo[housenumber][vidus] ][ IntY ],Inter[ hInfo[housenumber][vidus] ][ IntZ ]
		new vw;
		if(hInfo[houseid][daugiabutis]) vw=(MAX_HOUSES*2+MAX_BUSINESSES+hInfo[houseid][daugiabutis]-1);
		if(strcmp(hInfo[houseid][Name],"Nera",true)==0)
		{
			HousePickup[houseid] = CreatePickupA(1273, 23, hInfo[houseid][iconx], hInfo[houseid][icony], hInfo[houseid][iconz],vw);//not bought
			format(zinute,sizeof(zinute),"Namas Nr.: {FF0000}%i",houseid);
			HouseText[houseid] = CreateDynamic3DTextLabel(zinute, COLOR_WHITE, hInfo[houseid][iconx], hInfo[houseid][icony], hInfo[houseid][iconz], 50, _,_, 1,vw);
		}
		else
		{
			format(zinute,sizeof(zinute),"{FFFFFF}Namas Nr.: {FF0000}%i\n{FFFFFF}Savininkas: {FF0000}%s",houseid,hInfo[houseid][Name]);
			HousePickup[houseid] = CreatePickupA(1272, 23, hInfo[houseid][iconx], hInfo[houseid][icony], hInfo[houseid][iconz],vw);//bought
			HouseText[houseid] = CreateDynamic3DTextLabel(zinute, COLOR_WHITE, hInfo[houseid][iconx], hInfo[houseid][icony], hInfo[houseid][iconz], 50, _,_, 1,vw);
		}
		if(hInfo[houseid][Garazas])
		{
			format(zinute,sizeof(zinute),"Garaþas Nr.: {FF0000}%i\n{FFFFFF}Noredami áeiti, spauskite {FF0000}~k~~GROUP_CONTROL_BWD~",houseid);
			GarazoText[houseid] = CreateDynamic3DTextLabel(zinute, COLOR_WHITE, hInfo[houseid][GarazoX],hInfo[houseid][GarazoY],hInfo[houseid][GarazoZ], 10, _,_, 1);
		}
		LoadInterior(houseid);
		//LoadTextures(houseid);
		//LoadBaldai(houseid);
		x++;
		
	}
	mysql_function_query(SQL,"SELECT * FROM `baldai` ORDER By `houseid`",true,"SQL_BaldaiLoad","");
	mysql_function_query(SQL,"SELECT * FROM `Textures` ORDER By `houseid`",true,"SQL_TextureLoad","i",-1);
	LoadInvisibleInteriors();
	printf(" * House System : %d Houses load!",houseid);
	return 1;
}

forward SQL_Kiemai();
public SQL_Kiemai()
{
	RestartCheck();
	new 
		houseid,
		temp[25];
	new rows,fields;
	cache_get_data(rows,fields);
	new x;
	while(x<rows)
	{
		cache_get_row(x,0,temp), houseid = strval(temp);
		hInfo[houseid][hKiemas]=1;
		cache_get_row(x,1,temp), hInfo[houseid][kiemox] = floatstr(temp);
		cache_get_row(x,2,temp), hInfo[houseid][kiemoy] = floatstr(temp);
		cache_get_row(x,3,temp), hInfo[houseid][kiemoz] = floatstr(temp);
		hInfo[houseid][kLocked]=1;
		x++;
	}
	printf(" * House System : %d Kiemai loaded!",x);
}
forward SQL_BaldaiLoad();
public SQL_BaldaiLoad()
{
	RestartCheck();
	//new temp[20],row[1024],Xp,Vardux[24];
	new rows,fields;
	new temp[50];
	cache_get_data(rows,fields);
	new x;
	new houseid;
	new idx;
	new lasthouse=-1;
	while(x<rows)
	{
		//new idx;
		cache_get_row(x,1,temp); houseid=strval(temp);
		if(lasthouse != houseid)
		{
			idx=0;
			lasthouse=houseid;
		}
		BalduSistema[houseid][idx][b_used]=1;
		cache_get_row(x,2,temp); BalduSistema[houseid][idx][b_obj]=strval(temp);
		cache_get_row(x,3,temp); BalduSistema[houseid][idx][b_x]=floatstr(temp);
		cache_get_row(x,4,temp); BalduSistema[houseid][idx][b_y]=floatstr(temp);
		cache_get_row(x,5,temp); BalduSistema[houseid][idx][b_z]=floatstr(temp);
		cache_get_row(x,6,temp); BalduSistema[houseid][idx][b_rx]=strval(temp);
		cache_get_row(x,7,temp); BalduSistema[houseid][idx][b_ry]=strval(temp);
		cache_get_row(x,8,temp); BalduSistema[houseid][idx][b_rz]=strval(temp);
		cache_get_row(x,9,temp); BalduSistema[houseid][idx][b_cat]=strval(temp);
		//CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, STREAMER_TAG_AREA areaid = STREAMER_TAG_AREA -1, priority = 0)
		//BalduSistema[houseid][idx][b_oid]=CreateDynamicObject(BalduSistema[houseid][idx][b_obj],BalduSistema[houseid][idx][b_x],BalduSistema[houseid][idx][b_y],BalduSistema[houseid][idx][b_z],BalduSistema[houseid][idx][b_rx],BalduSistema[houseid][idx][b_ry],BalduSistema[houseid][idx][b_rz],GetHouseVirtualWorld(houseid), _, _, 50.0);
		//FixBalduObj(BalduSistema[houseid][idx][b_oid]);
		CreateBaldas(houseid,idx);
		idx++;
		//cache_get_row(x,1,temp), Xp=strval(temp);
		//format(row,sizeof(row),"%s %iXp",Vardux,Xp);
		//SendClientMessage(playerid,YELLOW,row);
		x++;
	}		
	return 1;
}
forward SQL_IsmestiCheck(playerid,name[],reason[]);
public SQL_IsmestiCheck(playerid,name[],reason[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	
	if(!rows)
	{
		return SendInfoMessage(playerid,"Blogai ivedei varda.");
	}
	new query[128];
	format(query,128,"SELECT `Xp`,`Pradirbo`,`Job` FROM `Account` WHERE `Name` = '%s'",name);
	mysql_function_query(SQL, query, true, "SQL_IsmestiCheck2", "iss", playerid,name,reason);

	return 1;
}
forward SQL_IsmestiCheck2(playerid,name[],reason[]);
public SQL_IsmestiCheck2(playerid,name[],reason[])
{
	RestartCheck();
	new expas[50];
	new xpint,pradirboint,spec;
	cache_get_row(0,0,expas), xpint=strval(expas);
	cache_get_row(0,1,expas), pradirboint=strval(expas);
	cache_get_row(0,2,expas), spec=strval(expas);
	if(!xpint) return SendInfoMessage(playerid,"Zaidejas neissaugojo zaidimo.");
	
	
	new lol=-1,lol2=-1,lol3=-1,lol4=-1,lol5=-1;
	if(playerDB[playerid][plead] == 2){ lol = 2; lol2=93; } // medikai
	else if(playerDB[playerid][plead] == 3){ lol = 3; lol2 = 20; lol3 = 39;} // transportas
	else if(playerDB[playerid][plead] == 5){ lol = 41; lol2 = 44;} // furistai
	else if(playerDB[playerid][plead] == 6){ lol = 6; lol2 = 28;} // autospeciai
	else if(playerDB[playerid][plead] == 66){ lol = 66; lol2 = 67;} // zudikai
	else if(playerDB[playerid][plead] == 70){ lol = 70; lol2 = 73; lol3 = 72;} // autoklubas
	else if(playerDB[playerid][plead] == 80){ lol = 80; lol2 = 81; lol3 = 83; lol4 = 84; lol5=82;}
	else if(playerDB[playerid][plead] == 50){ lol = 50;} // skelbejai
	else if(playerDB[playerid][plead] == 98){ lol = 71;} // baikeriai

	else if(playerDB[playerid][plead] == 58){ lol = 58;} // vagys

	else if(playerDB[playerid][plead] == 90){ lol = 31; lol2=32;} // dealeriai 
	else if(playerDB[playerid][plead] == 34) lol=34;
	else if(playerDB[playerid][plead] == 60){ lol=60;}

	if(spec!= lol && spec!= lol2 && spec!= lol3 && spec!= lol4 && spec!= lol5 ) return SendInfoMessage(playerid,"Zaidejas nedirba pas jus.");
	new query[128];
	if(pradirboint >= 100 && !Pareigos(playerid,"Dyrikai")) return SendInfoMessage(playerid,"Privalote sumoketi zaidejui alga!");
	
	format(query,128,"UPDATE `Account` SET `Job` = 0,`Uniformd` =0,`Uniforma` =-1,Pradirbo=0,Naud=0 WHERE `Name` = '%s'",name);
	mysql_query(query);
	new msg[128];
	if(Pareigos(playerid,"Dyrikai") && pradirboint >= 100)
		format(msg,sizeof(msg),"Meras %s Jus ismete is darbo be algos.~Priezastis: %s.",ReturnName(playerid),reason);
	else
		format(msg,sizeof(msg),"Direktorius %s Jus ismete is darbo.~Priezastis: %s.",ReturnName(playerid),reason);

	EAtaskaita("Darbo Birza",name,"Ismetimo Ataskaita",msg);
	format(msg,sizeof(msg),"%s buvo ismestas is jusu firmos.",name);
	SendInfoMessage(playerid,msg);
	MLog(playerid,"Ismete","ss",name, reason);

	return 1;
}
forward SQL_NarkoTest(playerid,id,type);
public SQL_NarkoTest(playerid,id,type)
{
	new temp[24]; new times;
	cache_get_row(0,0,temp); times=strval(temp);
	//if(times < 2) return 1;
	new msg[128];
	if(type==0) //lsd
	{
		if(times >= 4)
		{
			format(msg,sizeof(msg)," LSD Testas: {FF0000}TEIGIAMAS(narkomanas)");
		}
		else
		{
			format(msg,sizeof(msg)," LSD Testas: {00FF00}NEIGIAMAS(kraujas svarus)");
		}
		SendClientMessage(playerid,WHITE,msg);
		SendClientMessage(id,WHITE,msg);
	}
	else if(type == 1) // ratai
	{
		if(times >= 3)
		{
			format(msg,sizeof(msg)," Ekstazio Testas: {FF0000}TEIGIAMAS(narkomanas)");
		}
		else
		{
			format(msg,sizeof(msg)," Ekstazio Testas: {00FF00}NEIGIAMAS(kraujas svarus)");
		}
		SendClientMessage(playerid,WHITE,msg);
		SendClientMessage(id,WHITE,msg);
	}	
	else if(type==2) // amfa
	{
		if(times >= 3)
		{
			format(msg,sizeof(msg)," Amfetamino Testas: {FF0000}TEIGIAMAS(narkomanas)");
		}
		else
		{
			format(msg,sizeof(msg)," Amfetamino Testas: {00FF00}NEIGIAMAS(kraujas svarus)");
		}
		SendClientMessage(playerid,WHITE,msg);
		SendClientMessage(id,WHITE,msg);
	}
	return 1;
}
forward SQL_IpSearch(playerid);
public SQL_IpSearch(playerid)
{
	RestartCheck();
	new temp[20],row[1024],Xp,Vardux[24];
	new rows,fields;
	cache_get_data(rows,fields);
	new x;
	while(x<rows)
	{
		cache_get_row(x,0,Vardux);
		cache_get_row(x,1,temp), Xp=strval(temp);
		format(row,sizeof(row),"%s %iXp",Vardux,Xp);
		SendClientMessage(playerid,YELLOW,row);
		x++;
	}		
	return 1;
}

forward SQL_NameSearch(playerid);
public SQL_NameSearch(playerid)
{
	RestartCheck();
	new row[1024];
	cache_get_row(0,0,row);
	SendClientMessage(playerid,YELLOW,row);
	return 1;
}

forward SQL_AccSearch(playerid);
public SQL_AccSearch(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows == 0)
	{
		return SendInfoMessage(playerid, "Zaidejai nerasti!");
	}
	if(rows > 100)
	{
		return SendInfoMessage(playerid, "Ivyko klaida!");
	}
	for(new i = 0; i < rows; i++)
	{
		new msg[256];
		new name[24];
		new xp[24];
		new ipas[24];
		cache_get_row(i, 0, name);
		cache_get_row(i, 1, xp);
		new temp[24];
		cache_get_row(i,2, temp);
		new unused;
		sscanf(temp,"p<.>iiis[24]",unused,unused,unused,ipas);
		format(msg,256,"* %s %sXP ***.***.***.%s",name,xp,ipas);
		SendClientMessage(playerid, YELLOW, msg);
	}
	return 1;
}

forward SQL_PendingCheck(playerid,vardas[],prz[]);
public SQL_PendingCheck(playerid,vardas[],prz[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows) { SendInfoMessage(playerid,"Sis zaidejas jau laukiamuju sarase!"); return 1; }
	new query[128];
	format(query,sizeof(query),"SELECT * FROM BANS WHERE Vardas='%s'",vardas);
	mysql_function_query(SQL, query, true, "SQL_Pending2", "iss", playerid,vardas,prz);
	return 1;
}
forward SQL_Pending2(playerid,vardas[],prz[]);
public SQL_Pending2(playerid,vardas[],prz[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows) { SendInfoMessage(playerid,"Sis zaidejas jau blokuotas!"); return 1; }
	if(GetPlayeridMid(vardas) != INVALID_PLAYER_ID) return SendInfoMessage(playerid,"Sis zaidejas prisijunges! Naudokite /ban");
	new query[129];
	format(query,sizeof(query),"SELECT Adminas FROM Account WHERE Name='%s' and Adminas=1 LIMIT 1",vardas);
	mysql_function_query(SQL, query, true, "SQL_Pending3", "iss", playerid,vardas,prz);
	return 1;
}
forward SQL_Pending3(playerid,vardas[],prz[]);
public SQL_Pending3(playerid,vardas[],prz[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows) { SendInfoMessage(playerid,"Tai administratorius!"); return 1; }
	new prz2[256];
	new day,month,year;
	getdate(year,month,day);
	format(prz2,256,"%s %d.%02d.%02d",prz,year,month,day);
	new query[512];
	format(query,sizeof(query),"INSERT INTO Pending (Name,Admin,Reason) VALUES ('%s','%s','%s')",vardas,ReturnName(playerid),prz2);
	mysql_query(query);
	format(query,sizeof(query),"Sekmingai uzdejai laukiama bana %s uz %s.",vardas,prz2);
	SendInfoMessage(playerid,query);
	return 1;
}

forward SQL_NarkCheck(playerid,type,alert);
public SQL_NarkCheck(playerid,type,alert)
{
	new temp[24]; new times;
	cache_get_row(0,0,temp); times=strval(temp);
	if(times < 2) return 1;
	if(type==0) //lsd
	{
		if(times >= 4)
		{
			playerDB[playerid][narko][0]=1;
			if(alert==1)
			{
				SendClientMessage(playerid,RED,"[NARK] Tapai priklausomas nuo LSD!");
				SendClientMessage(playerid,RED,"[NARK] Siandien nejausi alkio jausmo!");
			}
		}
	
	}
	else if(type == 1) // ratai
	{
		if(times >= 3)
		{
			playerDB[playerid][narko][1]=1;
			if(alert==1)
			{
				SendClientMessage(playerid,RED,"[NARK] Tapai priklausomas nuo Ekstazio!");
				SendClientMessage(playerid,RED,"[NARK] Siandien ligonineje gulesi daug trumpiau ir gausi iki 150 HP!");
			}
		}
	}	
	else if(type==2) // amfa
	{
		if(times >= 3)
		{
			playerDB[playerid][narko][2]=1;
			if(alert==1)
			{
				SendClientMessage(playerid,RED,"[NARK] Tapai priklausomas nuo Amfetamino!");
				SendClientMessage(playerid,RED,"[NARK] Siandien jo neigiamas poveikis bus daug silpnesnis!");
			}
		}
	}
	return 1;
}

forward SQL_Darbuotojai(playerid);
public SQL_Darbuotojai(playerid)
{
	RestartCheck();
	new	
		name[24],
		x=0;
	new msg[128];
	new rows,fields; cache_get_data(rows,fields);
	new darbas[50];
	if(rows)
	{
		new row[256],dirbo,job,naud;//name[MAX_PLAYER_NAME],job;
		while(x<rows)
		{
			//sscanf(row,"p<|>s[24]ii",name,job,dirbo);
			cache_get_row(x,0,name);
			cache_get_row(x,1,row), job=strval(row);
			cache_get_row(x,2,row), dirbo=strval(row);
			cache_get_row(x,3,row), naud=strval(row);
			format(darbas,sizeof(darbas),"%s",ReturnJob(job));
			/*
			switch(job)
			{
				case 2: darbas = "Medikas";
				case 3: darbas = "Taksistas";
				case 6: darbas =  "Mechanikas";
				case 20: darbas = "Transporteris";
				case 31: darbas = "Kontrabandininkas";
				case 32: darbas = "Dyleris";
				case 39: darbas = "Limuzino vairuotojas";
				case 41: darbas = "Furistas";
				case 44: darbas = "Kurjeris";
				case 50: darbas = "Skelbejas";
				case 58: darbas = "Vagis";
				case 66: darbas = "Gaisrininkas";
				case 70: darbas = "Automanas";
				case 71: darbas = "Baikeris";
				//case 72: darbas = "Jacht klubo nariu";
				case 73: darbas = "Motomanas";
				case 80: darbas = "Policininkas";
				case 81: darbas = "ARAS";
				case 82: darbas = "VST";
				case 83: darbas = "Kareivis";
				case 84: darbas = "Kobra 11";
				case 34: darbas = "N.Turto agentas";
				default: darbas = "Kazkuo";
			}*/
			if(naud == 3)
				naud = 3;
			new id = GetPlayeridMid(name);
			
			if(id != INVALID_PLAYER_ID) format(msg,sizeof(msg),"%i. %s(%s; %i min)",x+1,name,darbas,playerDB[id][pradirbo]); // ; %i naud. balai ,playerDB[id][jobpts]
			else format(msg,sizeof(msg),"%i. %s(%s; %i min)",x+1,name,darbas,dirbo); // ,naud
			
			if(id != INVALID_PLAYER_ID) SendClientMessage(playerid,GREEN,msg);
			else SendClientMessage(playerid,RED,msg);
			//format(query,150,"SELECT COUNT(Variable) FROM Logs Where Zaidejas='%s' AND Veiksmas ='Dirba'",name);
			//mysql_function_query(SQL, query, true, "SQL_Darbuotojai2", "iisii",playerid,x,name,job,dirbo);

			x++;
		}	
	}
	return 1;
}
/*
forward SQL_Darbuotojai2(playerid,idas,name[],job,dirbo);
public SQL_Darbuotojai2(playerid,idas,name[],job,dirbo)
{
	RestartCheck();
	new	msg[128],
		id;

	new darbas[25],row[256],naud;//name[MAX_PLAYER_NAME],job;
	cache_get_row(0,0,row); naud = strval(row);
	switch(job)
	{
		case 2: darbas = "Medikas";
		case 3: darbas = "Taksistas";
		case 6: darbas =  "Mechanikas";
		case 20: darbas = "Transporteris";
		case 31: darbas = "Kontrabandininkas";
		case 32: darbas = "Dyleris";
		case 39: darbas = "Limuzino vairuotojas";
		case 41: darbas = "Furistas";
		case 44: darbas = "Kurjeris";
		case 50: darbas = "Skelbejas";
		case 58: darbas = "Vagis";
		case 66: darbas = "Gaisrininkas";
		case 70: darbas = "Automanas";
		case 71: darbas = "Baikeris";
		//case 72: darbas = "Jacht klubo nariu";
		case 73: darbas = "Motomanas";
		case 80: darbas = "Policininkas";
		case 81: darbas = "ARAS";
		case 82: darbas = "VST";
		case 83: darbas = "Kareivis";
		case 84: darbas = "Kobra 11";
		default: darbas = "Kazkuo";
	}
	id = GetPlayeridMid(name);
	
	if(id != INVALID_PLAYER_ID) format(msg,sizeof(msg),"%i. %s(%s; %i min; %i naud. balai)",idas+1,name,darbas,playerDB[id][pradirbo],naud);
	else format(msg,sizeof(msg),"%i. %s(%s; %i min; %i naud. balai)",idas+1,name,darbas,dirbo,naud);
	
	if(id != INVALID_PLAYER_ID) SendClientMessage(playerid,GREEN,msg);
	else SendClientMessage(playerid,RED,msg);
	return 1;
}
*/

forward SQL_Skirti(playerid,laikas,vardas[]);
public SQL_Skirti(playerid,laikas,vardas[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows){ SendClientMessage(playerid, RED," * Tokio zaidejo nera!!"); return 1;}
	new temp[12];
	cache_get_row(0,0,temp);
	if(strval(temp) != 0) { SendClientMessage(playerid, RED," * Zaidejas jau direktorius. Nuimk jam direktoriu su /nuimtidyr"); return 1; }
	new query[129];
	format(query,sizeof(query),"UPDATE Account Set `Lead`=%i WHERE Name='%s' LIMIT 1",laikas,vardas);
	mysql_query(query);
	SendClientMessage(playerid, 0xD9E916FF, "* Sekmingai pavertete direktoriumi.");
	return 1;
}

forward SQL_Nuimti(playerid,vardas[],priezastis[]);
public SQL_Nuimti(playerid,vardas[],priezastis[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows){ SendClientMessage(playerid, RED," * Tokio zaidejo nera!!"); return 1;}
	new temp[12];
	cache_get_row(0,0,temp);
	new leadas = strval(temp);
	if(leadas == 0) { SendClientMessage(playerid, RED," * Zaidejas ne direktorius!!"); return 1; }
	if(Pareigos(playerid,"Gaujos") && !Pareigos(playerid,"Dyrikai") && leadas != 98 && leadas != 90 && leadas != 58)
	{
		return SendInfoMessage(playerid, "Gauju priziuretojas gali nuimti tik nelegaliu darbu direktorius");
	}
	new query[128];
	format(query,sizeof(query),"UPDATE `Account` SET `Lead`=0 WHERE `Name`='%s' LIMIT 1",vardas);
	mysql_query(query);
	SendInfoMessage(playerid,"Sekmingai nuemei direktoriu.");
	new msg[128];
	format(msg,sizeof(msg),"Jums buvo nuimtos direktoriaus pareigos.~Priezastis: %s",priezastis);
	EAtaskaita("Savivaldybe",vardas,"Pareigos",msg);
	return 1;
}

forward SQL_ShowAktyvumas(playerid,vardas[]);
public SQL_ShowAktyvumas(playerid,vardas[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows){ SendInfoMessage(playerid,"Tokio zaidejo nera!!");return 1;}
	new temp[12];
	cache_get_row(0,0,temp);
	new temp2[12];
	cache_get_row(0,1,temp2);
	new query[128];
	if(strcmp(temp,"NULL",true) == 0)
		return SendClientMessage(playerid, -1, " * Zaidejas nebuvo prisijunges per paskutines 7d.");
	format(query,sizeof(query)," * Zaidejas %s per paskutines 7d. buvo prisijunges %s min, ir aktyvus %s min.",vardas, temp,temp2);
	SendClientMessage(playerid, -1, query);
	return 1;
}

forward SQL_NuimtiA(playerid,vardas[]);
public SQL_NuimtiA(playerid,vardas[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows){ SendInfoMessage(playerid,"Tokio zaidejo nera!!");return 1;}
	new temp[12];
	cache_get_row(0,0,temp);
	if(strval(temp) == 0) { SendInfoMessage(playerid,"Zaidejas ne administratorius!"); return 1; }
	new query[128];
	format(query,sizeof(query),"UPDATE `Account` SET `Adminas`=0 WHERE `Name`='%s' LIMIT 1",vardas);
	mysql_query(query);
	SendInfoMessage(playerid,"Sekmingai nuemei administratoriu.");
	SetNuimtasAdmin(playerid);
	return 1;
}

forward SQL_GautiN(playerid,housenumber);
public SQL_GautiN(playerid,housenumber)
{
	RestartCheck();
	new temp[12];
	cache_get_row(0,0,temp);
	GivePlayerMoneyA(playerid, strval(temp));
	new query[128];
	format(query,sizeof(query),"UPDATE `Namai` SET `RentGet`=0 WHERE `ID`=%i",housenumber);
	mysql_query(query);
	return 1;
}

forward SQL_MoketiN(playerid,housenumber);
public SQL_MoketiN(playerid,housenumber)
{
	RestartCheck();
	new temp[12];
	cache_get_row(0,0,temp);
	new kaina = strval(temp);
	if(GetPlayerMoneyA(playerid)<kaina) return SendInfoMessage(playerid,"Jum neuztenka pinigu sumoket savininkui!");
	SendInfoMessage(playerid,"Sumokejot nuomininkui!");
	GivePlayerMoneyA(playerid, -kaina);
	new query[128];
	format(query,sizeof(query),"UPDATE `Namai` SET `RentGet`='%i',`RentPay`=0 WHERE `ID`=%i",kaina,housenumber);
	mysql_query(query);
	return 1;
}

forward SQL_ReikiaMoketi(ii,houseid);
public SQL_ReikiaMoketi(ii,houseid)
{
	RestartCheck();
	new str2[150],temp[12];
	cache_get_row(0,0,temp);
	format(str2, sizeof(str2), "Jums reik moket %d€ uz sios valandos namo nr. %i nuoma! Esate skolingi %i€.", hInfo[houseid][Rentcost],houseid,strval(temp));
	SendClientMessage(ii, c_y, str2);
	return 1;
}

forward SQL_Masina(playerid);
public SQL_Masina(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(Carlist[playerid][Typ] != -1 || Carlist2[playerid][Typ] != -1 || Carlist3[playerid][Typ] != -1) return 1;
	if(rows)
	{
		//new row[2048];
		//mysql_fetch_row_format(row,"|");
		new temp[30];
		cache_get_row(0,1,temp), Carlist[playerid][Typ]=strval(temp);
		cache_get_row(0,2,temp), Carlist[playerid][X]=floatstr(temp);
		cache_get_row(0,3,temp), Carlist[playerid][Y]=floatstr(temp);
		cache_get_row(0,4,temp), Carlist[playerid][Z]=floatstr(temp);
		cache_get_row(0,5,temp), Carlist[playerid][Rotation]=floatstr(temp);
		cache_get_row(0,6,temp), Carlist[playerid][Status]=strval(temp);
		cache_get_row(0,7,temp), Carlist[playerid][Lock]=strval(temp);
		cache_get_row(0,8,temp), Carlist[playerid][Paintjob]=strval(temp);
		cache_get_row(0,9,temp), Carlist[playerid][Color1]=strval(temp);
		cache_get_row(0,10,temp), Carlist[playerid][Color2]=strval(temp);
		cache_get_row(0,11,temp), Carlist[playerid][mod1]=strval(temp);
		cache_get_row(0,12,temp), Carlist[playerid][mod2]=strval(temp);
		cache_get_row(0,13,temp), Carlist[playerid][mod3]=strval(temp);
		cache_get_row(0,14,temp), Carlist[playerid][mod4]=strval(temp);
		cache_get_row(0,15,temp), Carlist[playerid][mod5]=strval(temp);
		cache_get_row(0,16,temp), Carlist[playerid][mod6]=strval(temp);
		cache_get_row(0,17,temp), Carlist[playerid][mod7]=strval(temp);
		cache_get_row(0,18,temp), Carlist[playerid][mod8]=strval(temp);
		cache_get_row(0,19,temp), Carlist[playerid][mod9]=strval(temp);
		cache_get_row(0,20,temp), Carlist[playerid][mod10]=strval(temp);
		cache_get_row(0,21,temp), Carlist[playerid][mod11]=strval(temp);
		cache_get_row(0,22,temp), Carlist[playerid][mod12]=strval(temp);
		cache_get_row(0,23,temp), Carlist[playerid][mod13]=strval(temp);
		cache_get_row(0,24,temp), Carlist[playerid][mod14]=strval(temp);
		cache_get_row(0,25,temp), Carlist[playerid][mod15]=strval(temp);
		cache_get_row(0,26,temp), Carlist[playerid][mod16]=strval(temp);
		cache_get_row(0,27,temp), Carlist[playerid][mod17]=strval(temp);
		cache_get_row(0,28,temp), Carlist2[playerid][Typ]=strval(temp);
		cache_get_row(0,29,temp), Carlist2[playerid][X]=floatstr(temp);
		cache_get_row(0,30,temp), Carlist2[playerid][Y]=floatstr(temp);
		cache_get_row(0,31,temp), Carlist2[playerid][Z]=floatstr(temp);
		cache_get_row(0,32,temp), Carlist2[playerid][Rotation]=floatstr(temp);
		cache_get_row(0,33,temp), Carlist2[playerid][Status]=strval(temp);
		cache_get_row(0,34,temp), Carlist2[playerid][Lock]=strval(temp);
		cache_get_row(0,35,temp), Carlist2[playerid][Paintjob]=strval(temp);
		cache_get_row(0,36,temp), Carlist2[playerid][Color1]=strval(temp);
		cache_get_row(0,37,temp), Carlist2[playerid][Color2]=strval(temp);
		cache_get_row(0,38,temp), Carlist2[playerid][mod1]=strval(temp);
		cache_get_row(0,39,temp), Carlist2[playerid][mod2]=strval(temp);
		cache_get_row(0,40,temp), Carlist2[playerid][mod3]=strval(temp);
		cache_get_row(0,41,temp), Carlist2[playerid][mod4]=strval(temp);
		cache_get_row(0,42,temp), Carlist2[playerid][mod5]=strval(temp);
		cache_get_row(0,43,temp), Carlist2[playerid][mod6]=strval(temp);
		cache_get_row(0,44,temp), Carlist2[playerid][mod7]=strval(temp);
		cache_get_row(0,45,temp), Carlist2[playerid][mod8]=strval(temp);
		cache_get_row(0,46,temp), Carlist2[playerid][mod9]=strval(temp);
		cache_get_row(0,47,temp), Carlist2[playerid][mod10]=strval(temp);
		cache_get_row(0,48,temp), Carlist2[playerid][mod11]=strval(temp);
		cache_get_row(0,49,temp), Carlist2[playerid][mod12]=strval(temp);
		cache_get_row(0,50,temp), Carlist2[playerid][mod13]=strval(temp);
		cache_get_row(0,51,temp), Carlist2[playerid][mod14]=strval(temp);
		cache_get_row(0,52,temp), Carlist2[playerid][mod15]=strval(temp);
		cache_get_row(0,53,temp), Carlist2[playerid][mod16]=strval(temp);
		cache_get_row(0,54,temp), Carlist2[playerid][mod17]=strval(temp);
		cache_get_row(0,55,temp), Carlist3[playerid][Typ]=strval(temp);
		cache_get_row(0,56,temp), Carlist3[playerid][X]=floatstr(temp);
		cache_get_row(0,57,temp), Carlist3[playerid][Y]=floatstr(temp);
		cache_get_row(0,58,temp), Carlist3[playerid][Z]=floatstr(temp);
		cache_get_row(0,59,temp), Carlist3[playerid][Rotation]=floatstr(temp);
		cache_get_row(0,60,temp), Carlist3[playerid][Status]=strval(temp);
		cache_get_row(0,61,temp), Carlist3[playerid][Lock]=strval(temp);
		cache_get_row(0,62,temp), Carlist3[playerid][Paintjob]=strval(temp);
		cache_get_row(0,63,temp), Carlist3[playerid][Color1]=strval(temp);
		cache_get_row(0,64,temp), Carlist3[playerid][Color2]=strval(temp);
		cache_get_row(0,65,temp), Carlist3[playerid][mod1]=strval(temp);
		cache_get_row(0,66,temp), Carlist3[playerid][mod2]=strval(temp);
		cache_get_row(0,67,temp), Carlist3[playerid][mod3]=strval(temp);
		cache_get_row(0,68,temp), Carlist3[playerid][mod4]=strval(temp);
		cache_get_row(0,69,temp), Carlist3[playerid][mod5]=strval(temp);
		cache_get_row(0,70,temp), Carlist3[playerid][mod6]=strval(temp);
		cache_get_row(0,71,temp), Carlist3[playerid][mod7]=strval(temp);
		cache_get_row(0,72,temp), Carlist3[playerid][mod8]=strval(temp);
		cache_get_row(0,73,temp), Carlist3[playerid][mod9]=strval(temp);
		cache_get_row(0,74,temp), Carlist3[playerid][mod10]=strval(temp);
		cache_get_row(0,75,temp), Carlist3[playerid][mod11]=strval(temp);
		cache_get_row(0,76,temp), Carlist3[playerid][mod12]=strval(temp);
		cache_get_row(0,77,temp), Carlist3[playerid][mod13]=strval(temp);
		cache_get_row(0,78,temp), Carlist3[playerid][mod14]=strval(temp);
		cache_get_row(0,79,temp), Carlist3[playerid][mod15]=strval(temp);
		cache_get_row(0,80,temp), Carlist3[playerid][mod16]=strval(temp);
		cache_get_row(0,81,temp), Carlist3[playerid][mod17]=strval(temp);
		
		cache_get_row(0,82,temp), Carlist[playerid][Gas]=strval(temp);
		cache_get_row(0,83,temp), Carlist2[playerid][Gas]=strval(temp);
		cache_get_row(0,84,temp), Carlist3[playerid][Gas]=strval(temp);
		
		cache_get_row(0,85,temp), Carlist[playerid][Sirena]=strval(temp);
		cache_get_row(0,86,temp), Carlist2[playerid][Sirena]=strval(temp);
		cache_get_row(0,87,temp), Carlist3[playerid][Sirena]=strval(temp);
		
		cache_get_row(0,88,Carlist[playerid][NumPlate],SQL,40);
		cache_get_row(0,89,Carlist2[playerid][NumPlate],SQL,40);
		cache_get_row(0,90,Carlist3[playerid][NumPlate],SQL,40);
		
		cache_get_row(0,91,temp), Carlist[playerid][Energy]=strval(temp);
		cache_get_row(0,92,temp), Carlist2[playerid][Energy]=strval(temp);
		cache_get_row(0,93,temp), Carlist3[playerid][Energy]=strval(temp);
		
		cache_get_row(0,94,temp), Carlist[playerid][VirtualW]=strval(temp);
		cache_get_row(0,95,temp), Carlist2[playerid][VirtualW]=strval(temp);
		cache_get_row(0,96,temp), Carlist3[playerid][VirtualW]=strval(temp);
		
		cache_get_row(0,97,temp), Carlist[playerid][CDraud]=strval(temp);
		cache_get_row(0,98,temp), Carlist2[playerid][CDraud]=strval(temp);
		cache_get_row(0,99,temp), Carlist3[playerid][CDraud]=strval(temp);
		
		cache_get_row(0,100,temp), Carlist[playerid][Rankinis]=strval(temp);
		cache_get_row(0,101,temp), Carlist2[playerid][Rankinis]=strval(temp);
		cache_get_row(0,102,temp), Carlist3[playerid][Rankinis]=strval(temp);

		cache_get_row(0,103,temp), Carlist[playerid][VeHP]=floatstr(temp);
		cache_get_row(0,104,temp), Carlist2[playerid][VeHP]=floatstr(temp);
		cache_get_row(0,105,temp), Carlist3[playerid][VeHP]=floatstr(temp);

		cache_get_row(0,106,temp), Carlist[playerid][Rida]=floatstr(temp);
		cache_get_row(0,107,temp), Carlist2[playerid][Rida]=floatstr(temp);
		cache_get_row(0,108,temp), Carlist3[playerid][Rida]=floatstr(temp);

		if(Carlist[playerid][Typ]!=-1 && Carlist[playerid][Status]==1)
		{
			Carlist[playerid][Carid]=CreateTunedCar(playerid);
		}
		if(Carlist2[playerid][Typ]!=-1 && Carlist2[playerid][Status]==1)
		{
			Carlist2[playerid][Carid]=CreateTunedCar2(playerid);
		}
		if(Carlist3[playerid][Typ]!=-1 && Carlist3[playerid][Status]==1)
		{
			Carlist3[playerid][Carid]=CreateTunedCar3(playerid);
		}
	}
	return 1;
}	

forward SQL_Bizniai();
public SQL_Bizniai()
{
	RestartCheck();
	new temp[30];
	new rows,fields; cache_get_data(rows,fields);
	new idx=0;
	while(idx<rows)
	{
		Iter_Add(Businesses, idx);
		cache_get_row(idx,0,BusinessInfo[idx][bName],SQL,64);
		cache_get_row(idx,1,BusinessInfo[idx][bOwner],SQL,24);
		cache_get_row(idx,2,temp), BusinessInfo[idx][bEnterX]=floatstr(temp);
		cache_get_row(idx,3,temp), BusinessInfo[idx][bEnterY]=floatstr(temp);
		cache_get_row(idx,4,temp), BusinessInfo[idx][bEnterZ]=floatstr(temp);
		cache_get_row(idx,5,temp), BusinessInfo[idx][bExitX]=floatstr(temp);
		cache_get_row(idx,6,temp), BusinessInfo[idx][bExitY]=floatstr(temp);
		cache_get_row(idx,7,temp), BusinessInfo[idx][bExitZ]=floatstr(temp);
		
		cache_get_row(idx,8,temp), BusinessInfo[idx][EnterInterior]=strval(temp);
		cache_get_row(idx,9,temp), BusinessInfo[idx][EnterWorld]=strval(temp);
		cache_get_row(idx,10,temp), BusinessInfo[idx][bPrice]=strval(temp);
		cache_get_row(idx,11,temp), BusinessInfo[idx][bNumber]=strval(temp);
		cache_get_row(idx,12,temp), BusinessInfo[idx][bEarning]=strval(temp);
		cache_get_row(idx,13,temp), BusinessInfo[idx][bType]=strval(temp);
		cache_get_row(idx,14,temp), BusinessInfo[idx][bOwned]=strval(temp);
		cache_get_row(idx,15,temp), BusinessInfo[idx][bRadio]=strval(temp);
		cache_get_row(idx,16,temp), BusinessInfo[idx][bMokesciai]=strval(temp);
		cache_get_row(idx,17,temp), BusinessInfo[idx][bPaeme]=strval(temp);
		
/*		sscanf(result,"p<|>s[50]s[24]ffffffddddddddd",
				BusinessInfo[idx][bName],
				BusinessInfo[idx][bOwner],
				BusinessInfo[idx][bEnterX],
				BusinessInfo[idx][bEnterY],
				BusinessInfo[idx][bEnterZ],
				BusinessInfo[idx][bExitX],
				BusinessInfo[idx][bExitY],
				BusinessInfo[idx][bExitZ],
				BusinessInfo[idx][EnterInterior],
				BusinessInfo[idx][EnterWorld],
				BusinessInfo[idx][bPrice],
				BusinessInfo[idx][bNumber],
				BusinessInfo[idx][bEarning],
				BusinessInfo[idx][bType],
				BusinessInfo[idx][bOwned],
				BusinessInfo[idx][bRadio],
				BusinessInfo[idx][bMokesciai]);
		*/
		BusinessInfo[idx][EnterWorld] = idx+MAX_HOUSES*2;
		//UTF8_Decode(BusinessInfo[idx][bName], BusinessInfo[idx][bName], 1024);
		new string[128];
		if(BusinessInfo[idx][bType] == 17)
		{
			BankID[TotalBanks]=idx;
			
			//Iter_Add(BusinessBankai,idx);
			Loop(is,5)
			{
				Loop(ass,MAX_IN_QUE) { BankArray[TotalBanks][is][ass]=-1; }
				format(string,sizeof(string),"{FFFFFF}Kasa {33FF33}%i\n{FF0000}%i",is+1,999);
				//BankuSystem[idx][is]=((is*100)+1);
				BankuTextai[TotalBanks][is] = CreateDynamic3DTextLabel(string, 0xFFFFFFFF, BankuTCord[is][0],BankuTCord[is][1],BankuTCord[is][2], 15.0, _, _, 1, (idx+MAX_HOUSES*2));
			}
			TotalBanks++;
		}
		if(BusinessInfo[idx][bOwned] == 0)
			format(string, sizeof(string), VERSLAS_PARDUODAMAS, GetBussinessType(BusinessInfo[idx][bType]),BusinessInfo[idx][bPrice]);
		else
			format(string, sizeof(string), VERSLAS_NEPARDUODAMAS, BusinessInfo[idx][bName],BusinessInfo[idx][bOwner],GetBussinessType(BusinessInfo[idx][bType]));
		businesstext[idx] = CreateDynamic3DTextLabel(string,0x00BC00FF,BusinessInfo[idx][bEnterX],BusinessInfo[idx][bEnterY],BusinessInfo[idx][bEnterZ],40.0, _,_, 1);
		CreatePickupA(19197,1,BusinessInfo[idx][bEnterX],BusinessInfo[idx][bEnterY],BusinessInfo[idx][bEnterZ]);
		isejimotext[idx] = CreateDynamic3DTextLabel("Iðëjimas\n\n{FFFFFF}Noredami iðeiti spauskite {00864b}[ENTER]",COLOR_WHITE,BusinessInfo[idx][bExitX],BusinessInfo[idx][bExitY],BusinessInfo[idx][bExitZ],30.0, _,_, 1, BusinessInfo[idx][EnterWorld]);
		CreatePickupA(19197,1,BusinessInfo[idx][bExitX],BusinessInfo[idx][bExitY],BusinessInfo[idx][bExitZ]);
		SetNPCSkinCoord(BusinessInfo[idx][EnterWorld],BusinessInfo[idx][EnterInterior],BusinessInfo[idx][bExitX],BusinessInfo[idx][bExitY],BusinessInfo[idx][bExitZ]); 

		if(iconsbiz[BusinessInfo[idx][bType]] != 0)
		{
			businessicon[idx] = CreateDynamicMapIcon(BusinessInfo[idx][bEnterX],BusinessInfo[idx][bEnterY],BusinessInfo[idx][bEnterZ], 	iconsbiz[BusinessInfo[idx][bType]] , 0, _, _, _);
		}
		//CreateDynamicMapIcon(Float:x, Float:y, Float:z, type, color, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_MAP_ICON_SD, style = MAPICON_LOCAL, STREAMER_TAG_AREA areaid = STREAMER_TAG_AREA -1, priority = 0)

		// kuriam aktorius
		//CreateNPC(idx,BusinessInfo[idx][bType],BusinessInfo[idx][EnterInterior],BusinessInfo[idx][EnterWorld]);
		
		idx++;
	}
	printf(" * Business system: %i businesses load.",idx);
	SetTimer("Banks",30000,true);
	return 1; 

}

forward SQL_ShowNarius(playerid);
public SQL_ShowNarius(playerid)
{
	RestartCheck();
	new result[512];
	new fields,rows;
	cache_get_data(rows,fields);
	new x;
	format(G_DialogList,sizeof(G_DialogList),"");
	while(x<rows)
	{
		cache_get_row(x,0,result);
		new id = GetPlayeridMid(result);
		if(id == INVALID_PLAYER_ID || !IsPlayerConnected(id) || playerDB[id][authstate] == 0)
			format(G_DialogList,sizeof(G_DialogList),"%s\n%s",G_DialogList,result);
		else
			format(G_DialogList,sizeof(G_DialogList),"%s\n{FF0000}%s",G_DialogList,result);
		x++;
	}
	if(x > 0)
		ShowPlayerDialog(playerid,8563,DIALOG_STYLE_LIST,"Gaujos nariai",G_DialogList,"Ismesti","Atsaukti");
	else {
		SendClientMessage(playerid, COLOR, " * Gaujoje nera nariu!");
		return ShowGangDialog(playerid);
	}
	return 1;
}
stock ApplyDyrKoef(mins,lead)
{
	if(!lead)
		return mins;
	if(!IsDyrKoefEnabled())
		return mins;
		
	return mins * 2;
}
forward SQL_ShowDarbuotojai(playerid);
public SQL_ShowDarbuotojai(playerid)
{
	RestartCheck();
	new row[128],damin,dajob,dalead,TotalPradirbo,Float:kofas;
	new x,fields,rows;
	cache_get_data(rows,fields);
	while(x<rows)
	{
		cache_get_row(x,0,row), damin=strval(row);
		cache_get_row(x,1,row), dajob=strval(row);
		cache_get_row(x,2,row), dalead=strval(row);
		//sscanf(row,"p<|>dd",damin,dajob);
		switch(dajob)
		{
			case 80: damin=floatround(damin * 1.329);
			case 81: damin=floatround(damin * 1.493);
			case 83: damin=floatround(damin * 1.575);
			case 84: damin=floatround(damin * 1.411);

			case 73: damin=floatround(damin * 1.655);
			case 39: damin=floatround(damin * 1.207);
			case 20: damin=floatround(damin * 1.517);
			case 41: damin=floatround(damin * 1.469);
			case 32: damin=floatround(damin * 1.06);
			case 93: damin=floatround(damin * 2.049);
		}
		damin = ApplyDyrKoef(damin, dalead);
		TotalPradirbo+=damin;
		x++;
	}
	//TotalPradirbo=mysql_fetch_int();
	if(!TotalPradirbo) TotalPradirbo++;
	kofas = (pelnas[playerDB[playerid][plead]-1] / TotalPradirbo);
	
	new query[500],
		lol=-1,
		lol2=-1,
		lol3=-1,
		lol4=-1,
		lol5=-1;
	if(playerDB[playerid][plead] == 2){ lol = 2; lol2=93; } // medikai
	else if(playerDB[playerid][plead] == 3){ lol = 3; lol2 = 20; lol3 = 39;} // transportas
	else if(playerDB[playerid][plead] == 5){ lol = 41; lol2 = 44;} // furistai
	else if(playerDB[playerid][plead] == 6){ lol = 6; lol2 = 28;} // autospeciai
	else if(playerDB[playerid][plead] == 66){ lol = 66; lol2 = 67;} // zudikai
	else if(playerDB[playerid][plead] == 70){ lol = 70; lol2 = 73; lol3 = 72;} // autoklubas
	else if(playerDB[playerid][plead] == 80){ lol = 80; lol2 = 81; lol3 = 83; lol4 = 84; lol5=82;}
	else if(playerDB[playerid][plead] == 50){ lol = 50;} // skelbejai
	else if(playerDB[playerid][plead] == 98){ lol = 71;} // baikeriai
	else if(playerDB[playerid][plead] == 58){ lol = 58;} // vagys
	else if(playerDB[playerid][plead] == 90){ lol = 31; lol2=32;} // dealeriai 
	else if(playerDB[playerid][plead] == 34){ lol = 34;} // nta
	else if(playerDB[playerid][plead] == 60){ lol = 60;} // inkasatorius
	
	format(query,sizeof(query),"SELECT `Name`,`Pradirbo`,`Job`,`Lead` FROM `Account` WHERE (`Job` = %i OR `Job` = %i OR `Job` = %i OR `Job` = %i OR `Job` = %i)",lol,lol2,lol3,lol4,lol5);
	

	mysql_tquery(SQL,query,"SQL_ShowDarbuotojai2","if",playerid,kofas);
	return 1;
}
forward SQL_ShowDarbuotojai2(playerid,Float:Kf);
public SQL_ShowDarbuotojai2(playerid,Float:Kf)
{
	RestartCheck();
	new Nameas[24],Pradirbo,Lead,RealMin,Alga,Darbas,kiekyr,result[256];
	new rows,fields;
	cache_get_data(rows,fields);
	format(G_DialogList,sizeof(G_DialogList),"");
	new x;
	while(x < rows)
	{
		cache_get_row(x,0,Nameas);
		cache_get_row(x,1,result), Pradirbo = strval(result); RealMin=Pradirbo;
		cache_get_row(x,2,result), Darbas = strval(result);
		cache_get_row(x,3,result), Lead = strval(result);
		//sscanf(result,"p<|>s[24]dd",Nameas,Pradirbo,Darbas);
		if(Pradirbo > 99)
		{
			switch(Darbas)
			{
				case 80: Pradirbo=floatround(Pradirbo * 1.329);
				case 81: Pradirbo=floatround(Pradirbo * 1.493);
				case 83: Pradirbo=floatround(Pradirbo * 1.575);
				case 84: Pradirbo=floatround(Pradirbo * 1.411);
				
				
				case 73: Pradirbo=floatround(Pradirbo * 1.655);
				case 39: Pradirbo=floatround(Pradirbo * 1.207);
				case 20: Pradirbo=floatround(Pradirbo * 1.517);
				case 41: Pradirbo=floatround(Pradirbo * 1.469);
				case 32: Pradirbo=floatround(Pradirbo * 1.06);
				case 93: Pradirbo=floatround(Pradirbo * 2.049);
			}
			Pradirbo = ApplyDyrKoef(Pradirbo, Lead);
			Alga = floatround(Kf*Pradirbo);
			
			format(G_DialogList,sizeof(G_DialogList),"%s\n%s:  %imin.  Alga %i€",G_DialogList,Nameas,RealMin,Alga);
			kiekyr++;
		}
		x++;
		
	}
	//mysql_free_result();
	if(kiekyr) ShowPlayerDialog(playerid,7563,DIALOG_STYLE_LIST,"Darbuotojai",G_DialogList,"Ismoketi","Atsaukti");
	else SendInfoMessage(playerid,"Per mazai darbuotoju!");
	return 1;
}

forward SQL_Ismoketi(playerid,listitemid);
public SQL_Ismoketi(playerid,listitemid)
{
	RestartCheck();
	new row[128],damin,dajob,dalead,x,rows,fields;
	new Float:Kf,TotalPradirbo;
	cache_get_data(rows,fields);
	while(x<rows)
	{
		cache_get_row(x,0,row), damin=strval(row);
		cache_get_row(x,1,row), dajob=strval(row);
		cache_get_row(x,2,row), dalead=strval(row);
		//sscanf(row,"p<|>dd",damin,dajob);
		switch(dajob)
		{
			case 80: damin=floatround(damin * 1.329);
			case 81: damin=floatround(damin * 1.493); // swat
			case 83: damin=floatround(damin * 1.575); // armija
			case 84: damin=floatround(damin * 1.411); // kobra
			
			
			
			case 73: damin=floatround(damin * 1.655);
			case 39: damin=floatround(damin * 1.207);
			case 20: damin=floatround(damin * 1.517);
			case 41: damin=floatround(damin * 1.469);
			case 32: damin=floatround(damin * 1.06);
			case 93: damin=floatround(damin * 2.049);
		}
		damin = ApplyDyrKoef(damin,dalead);
		TotalPradirbo+=damin;
		x++;
	}
	Kf = (pelnas[playerDB[playerid][plead]-1] / TotalPradirbo);
	new query[500],
		lol=-1,lol2=-1,lol3=-1,lol4=-1,lol5=-1;
	
	if(playerDB[playerid][plead] == 2){ lol = 2; lol2=93; } // medikai
	else if(playerDB[playerid][plead] == 3){ lol = 3; lol2 = 20; lol3 = 39;} // transportas
	else if(playerDB[playerid][plead] == 5){ lol = 41; lol2 = 44;} // furistai
	else if(playerDB[playerid][plead] == 6){ lol = 6; lol2 = 28;} // autospeciai
	else if(playerDB[playerid][plead] == 66){ lol = 66; lol2 = 67;} // zudikai
	else if(playerDB[playerid][plead] == 70){ lol = 70; lol2 = 73; lol3 = 72;} // autoklubas
	else if(playerDB[playerid][plead] == 80){ lol = 80; lol2 = 81; lol3 = 83; lol4 = 84; lol5 = 82;}
	else if(playerDB[playerid][plead] == 50){ lol = 50;} // skelbejai
	else if(playerDB[playerid][plead] == 98){ lol = 71;} // baikeriai
	else if(playerDB[playerid][plead] == 58){ lol = 58;} // vagys
	else if(playerDB[playerid][plead] == 90){ lol = 31; lol2=32;} // dealeriai 
	else if(playerDB[playerid][plead] == 34){ lol = 34;} // nta
	else if(playerDB[playerid][plead] == 60){ lol = 60;} // inkasatorius
	format(query,sizeof(query),"SELECT `Name`,`Pradirbo`,`Job`,`Naud`,`Lead` FROM `Account` WHERE `Pradirbo` > 99 AND (`Job` = %i OR `Job` = %i OR `Job` = %i OR `Job` = %i OR `Job` = %i)",lol,lol2,lol3,lol4,lol5);
	mysql_function_query(SQL, query, true, "SQL_Ismoketi2", "ifi",playerid,Kf,listitemid);
	
	return 1;
}
forward SQL_Ismoketi2(playerid,Float:Kf,listitemid);
public SQL_Ismoketi2(playerid,Float:Kf,listitemid)
{
	RestartCheck();
	new x = 0,
		Pradirbo,
		Alga,
		Darbas,
		Lead,
		procentas=0,
		RealMin,
		queryz[128],
	//	Nauda,
		Nameas[MAX_PLAYER_NAME];
	new result[256];
	new rows,fields;
	cache_get_data(rows,fields);
	while(x<rows)
	{
		if(x==listitemid)
		{
			cache_get_row(x,0,Nameas);
			cache_get_row(x,1,result), Pradirbo = strval(result); RealMin=Pradirbo;
			cache_get_row(x,2,result), Darbas = strval(result);
//			cache_get_row(x,3,result), Nauda = strval(result);
			cache_get_row(x,4,result), Lead = strval(result);
			//sscanf(result,"p<|>s[24]dd",Nameas,Pradirbo,Darbas);
			switch(Darbas)
			{
				case 80: Pradirbo=floatround(Pradirbo * 1.329);
				case 84: Pradirbo=floatround(Pradirbo * 1.411);
				case 81: Pradirbo=floatround(Pradirbo * 1.493);
				case 83: Pradirbo=floatround(Pradirbo * 1.575);
				case 73: Pradirbo=floatround(Pradirbo * 1.655);
				case 39: Pradirbo=floatround(Pradirbo * 1.207);
				case 20: Pradirbo=floatround(Pradirbo * 1.517);
				case 41: Pradirbo=floatround(Pradirbo * 1.469);
				case 32: Pradirbo=floatround(Pradirbo * 1.06);
				case 93: Pradirbo=floatround(Pradirbo * 2.049);
			}
			Pradirbo = ApplyDyrKoef(Pradirbo,Lead);
			Alga = floatround(Kf*Pradirbo);
			procentas = floatround(Alga/100);
			//BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning]+=procentas;
			BusinessMoney(procentas*3/2);
			new msg[128];
			format(msg,sizeof(msg),"Pervedei %i EUR Alga %s.",Alga,Nameas);
			SendInfoMessage(playerid,msg);
			MLog(playerid,"Ismokejo alga","si", Nameas,Alga);
			format(msg,sizeof(msg),"Direktorius %s Jums pervede alga.~Pajamos: %sEUR.~Pervedimo mokestis:%iEUR.~Pradirbtos minutes: %imin.",ReturnName(playerid),FormatNumber(Alga),procentas,RealMin);
			EAtaskaita("Bankas",Nameas,"Algos Ataskaita",msg);
			Alga-=procentas;
			new forplayerid = GetIdForAlgos(Nameas);
			pelnas[playerDB[playerid][plead]-1]-=Alga;
			ResetFakeWorkerMins(playerDB[playerid][plead]);
			//format(queryz,sizeof(queryz),"DELETE From Logs Where Veiksmas='Dirba' AND Zaidejas='%s'",Nameas);
			//mysql_query(queryz);
			if(forplayerid == INVALID_PLAYER_ID || playerDB[forplayerid][authstate]!=4)
			{
				format(queryz,sizeof(queryz),"UPDATE `Account` SET `Money.Bank`=(`Money.Bank`+%i),`Pradirbo`=0,`Naud`=0 WHERE `Name` = '%s'",Alga,Nameas);
				//mysql_query(queryz);
				mysql_tquery(SQL,queryz,"SQL_IsmoketaAlga","isi",playerid,Nameas,Alga);
			}
			else
			{
				format(msg,sizeof(msg)," * Zaidejui %s pervedete %i€ alga.",ReturnName(forplayerid),Alga);
				SendClientMessage(playerid,ORANGE,msg);
				format(msg,sizeof(msg)," * Jums buvo pervesta %s€ alga i banko saskaita.",FormatNumber(Alga));
				SendClientMessage(forplayerid,ORANGE,msg);
				if(Darbas==80 || Darbas == 82 || Darbas==81 || Darbas==83 || Darbas==84)
				{
					ProcessAchievement(forplayerid,66);
				}
				playerDB[forplayerid][jobpts]=0;
				playerDB[forplayerid][pradirbo]=0;
				playerDB[forplayerid][banke]+=Alga;
				SavePlayerData(forplayerid,true);
				ShowDarbuotojus(playerid);
			}
			break;
		}
		x++;
	}
	
	return 1;
}
forward SQL_IsmoketaAlga(playerid,Zaid[],Alga);
public SQL_IsmoketaAlga(playerid,Zaid[],Alga)
{
	RestartCheck();
	new msg[128];
	ShowDarbuotojus(playerid);
	format(msg,sizeof(msg)," * Zaidejui %s pervedete %i€ alga.",Zaid,Alga);
	SendClientMessage(playerid,ORANGE,msg);
	return 1;
}

forward SQL_ShowEmail(playerid);
public SQL_ShowEmail(playerid)
{
	RestartCheck();
	//mysql_function_query(SQL, query, true, "SQL_UpdateKred3", "i", playerid);
	new fields,rows;
	cache_get_data(rows,fields);
	new inbox,outbox,temp[12],string[256];
	cache_get_row(0,0,temp), inbox=strval(temp);
	if(rows > 1)
	{
		cache_get_row(1,0,temp), outbox=strval(temp);
	}
	format(string,sizeof(string),"{FFFFFF}\
									Gautieji\t{FF0000}%i{FFFFFF} Naujø\n\
									Issiustieji\t{FF0000}%i{FFFFFF} Neperskaitytø\n\
									Raðyti",inbox,outbox);
	ShowPlayerDialog(playerid, DIALOGID, DIALOG_STYLE_TABLIST,"E-Mail",string,"Gerai","Atgal");
	return 1;
}

forward SQL_Tagai(i);
public SQL_Tagai(i)
{
	RestartCheck();
	new query[256],result[20];
	new rows,fields;
	cache_get_data(rows,fields);
	
	if(!rows)
	{
		format(query,sizeof(query),"INSERT INTO `Tags` (`ID`,`Gang`) VALUES (%i,'-1')",i);
		mysql_query(query);
	}
	else
	{
		cache_get_row(0,0,result);
		TagOwnedBy[i]=strval(result);
	}
	if(TagOwnedBy[i] != -1) TagObj[i] = CreateDynamicObject(FamilyInfo[TagOwnedBy[i]][FamilySpray],GaujuTagai[i][0],GaujuTagai[i][1],GaujuTagai[i][2],GaujuTagai[i][3],GaujuTagai[i][4],GaujuTagai[i][5]);
	else TagObj[i] = CreateDynamicObject(18663,GaujuTagai[i][0],GaujuTagai[i][1],GaujuTagai[i][2],GaujuTagai[i][3],GaujuTagai[i][4],GaujuTagai[i][5]);
	if(TagOwnedBy[i] == 4) // mafia
	{
		SetDynamicObjectMaterialText(TagObj[i], 0, "†THE†\nMAFIA", OBJECT_MATERIAL_SIZE_256x256, "Copperplate Gothic Light", 82, 1, 0xBB000000, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);

	}
	else if(TagOwnedBy[i] == 5) // dnb
	{

		SetDynamicObjectMaterialText(TagObj[i], 0, "Da’\nNÅNG\nBoyZ", OBJECT_MATERIAL_SIZE_128x128, "Segoe Script", 42, 1, 0xBBEEEEEE, 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
	}


	return 1;
}

forward SQL_LoadVariable();
public SQL_LoadVariable()
{
	RestartCheck();
	new x,fields,rows;
	cache_get_data(rows,fields);
	new variable[256];
	new result[256];
	while(x<rows)
	{
		cache_get_row(x,0,variable);
		cache_get_row(x,1,result);
		if(strcmp(variable,"aak",false)==0) Server[aak]=strval(result);
		else if(strcmp(variable,"amp",false)==0) Server[amp]=strval(result);
		else if(strcmp(variable,"adgl",false)==0) Server[adgl]=strval(result);
		else if(strcmp(variable,"aawp",false)==0) Server[aawp]=strval(result);
		else if(strcmp(variable,"atveztan",false)==0) Server[atveztan]=strval(result);
		else if(strcmp(variable,"kysiai",false)==0) Server[kysiufondas]=strval(result);
		else if(strcmp(variable,"afondas",false)==0) Server[afondas]=strval(result);
		else if(strcmp(variable,"aak",false)==0) Server[aak]=strval(result);
		else if(strcmp(variable,"aak",false)==0) Server[aak]=strval(result);
		else if(strcmp(variable,"RadioUrl",false)==0) cache_get_row(x,1,g_StartRadio);
		else if(strfind(variable,"FURU_",false) != -1) 
		{
			new id = strval(variable[5]);
			FURU_ATVEZTA[id]=strval(result);
		}
		x++;
	}
	return 1;
}

forward SQL_Rekordas();
public SQL_Rekordas()
{
	RestartCheck();
	new result[12];
	cache_get_row(0,0,result);
	Server[rekordas] = strval(result);
	return 1;
}

forward SQL_Stiliai(playerid);
public SQL_Stiliai(playerid)
{
	RestartCheck();
	new row[24];
	new x,rows,fields;
	cache_get_data(rows,fields);
	AddDListItem(playerid,"Iprastas", 0);
	while(x<rows)
	{
		cache_get_row(x,0,row);
		new sID = strval(row);
		switch(sID)
		{
			case WALK_DEFAULT: AddDListItem(playerid,"Iprastas", sID);
			case WALK_NORMAL: AddDListItem(playerid,"Normalus", sID);
			case WALK_PED: AddDListItem(playerid,"Praeivis", sID);
			case WALK_GANGSTA: AddDListItem(playerid,"Gangsteris", sID);
			case WALK_GANGSTA2: AddDListItem(playerid,"Gangsteris 2", sID);
			case WALK_OLD: AddDListItem(playerid,"Senis", sID);
			case WALK_FAT_OLD: AddDListItem(playerid,"Storas senis", sID);
			case WALK_FAT: AddDListItem(playerid,"Storulis", sID);
			case WALK_LADY: AddDListItem(playerid,"Panele", sID);
			case WALK_LADY2: AddDListItem(playerid,"Panele 2", sID);
			case WALK_WHORE: AddDListItem(playerid,"Kekse", sID);
			case WALK_WHORE2: AddDListItem(playerid,"Kekse 2", sID);
			case WALK_DRUNK: AddDListItem(playerid,"Girtuoklis", sID);
			case WALK_BLIND: AddDListItem(playerid,"Aklasis", sID);
		}
		x++;
		//format(zinutes,sizeof(zinutes),"%s%s\n",zinutes,pav);
	}

	ShowPlayerDList(playerid, 467, "Stiliai", "Pasirinkti","Atgal");
	SendInfoMessage(playerid,"~r~Vaiksciojimo stilius gali isigyti uz kreditus.");
	return 1;
}

forward SQL_Ataskaita(playerid);
public SQL_Ataskaita(playerid)
{
	RestartCheck();
	new dialogtext[4028],x,Nameas[MAX_PLAYER_NAME],Veiksmas[100],Variable[30],Data[30];
	new fields,rows;
	cache_get_data(rows,fields);
	new y;
	while(x<rows)
	{
		y++;
		cache_get_row(x,0,Nameas);
		cache_get_row(x,1,Veiksmas);
		cache_get_row(x,2,Variable);
		cache_get_row(x,3,Data);
		//sscanf(row,"p<|>s[24]s[100]s[100]s[30]",Nameas,Veiksmas,Variable,Data);
		format(dialogtext,4028,"%s%i. %s %s(%s) [%s]\n",dialogtext,y,Nameas,Veiksmas,Variable,Data);
		x++;
	}
	//mysql_free_result();
	if(x) ShowPlayerDialog(playerid,9535,DIALOG_STYLE_LIST,"Ataskaita",dialogtext,"Gerai","Toliau");
	return 1;
}

forward SQL_Daugiabuciai(playerid);
public SQL_Daugiabuciai(playerid)
{
	RestartCheck();
	new row[128],string[128];
	new x,rows,fields; cache_get_data(rows,fields);
	while(x<rows)
	{
		if(x == MAX_DAUGIABUCIAI) return printf("DAUGIABUCIU LIMITAS PASIEKTAS");
		cache_get_row(x,1,row), Daugiabuciai[x][dX]=floatstr(row);
		cache_get_row(x,2,row), Daugiabuciai[x][dY]=floatstr(row);
		cache_get_row(x,3,row), Daugiabuciai[x][dZ]=floatstr(row);
		cache_get_row(x,4,row), Daugiabuciai[x][dLift]=strval(row);
		//if(sscanf(row,"p<|>{i}fffi",Daugiabuciai[x][dX],Daugiabuciai[x][dY],Daugiabuciai[x][dZ],Daugiabuciai[x][dLift])) print("Error with Flat sscanf!");
		Daugiabuciai[x][dEX]=1;
		format(string,sizeof(string),"Daugiabutis Nr.:{FF0000} %i",x+1);
		Daugiabuciai[x][dIT] = CreateDynamic3DTextLabel(string,COLOR_YELLOW,Daugiabuciai[x][dX],Daugiabuciai[x][dY],Daugiabuciai[x][dZ],20.0);
		Daugiabuciai[x][dLiftU]=false;
		Iter_Add(Daugiabuciai,x);
		x++;
	}
	printf("* Flat system: Loaded %i Flats",x);
	return 1;
}

forward SQL_IsUnique(playerid);
public SQL_IsUnique(playerid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new unique = 0;
	if(!rows) 
	{
		unique = 1;
	}
	new hashas[128];
	gpci(playerid,hashas,sizeof(hashas));
	mysql_real_escape_string(hashas,hashas);
	new ip[24];
	GetPlayerIp(playerid,ip,24);
	new queryx[512];
	format(queryx,sizeof(queryx),"INSERT INTO Registrations(`Name`,`Ip`,`Diskid`,`Time`,`Unique`) VALUES ('%s','%s','%s',NOW(),%i)",ReturnName(playerid),ip,hashas,unique);
	mysql_query(queryx);
	return 1;
}

forward SQL_Rubai(playerid);
public SQL_Rubai(playerid)
{
	RestartCheck();
	//new msg[4024];
	new row[10],x;
	new rows,fields; cache_get_data(rows,fields);
	new rubai[320];
	
	while(x<rows)
	{
		cache_get_row(x,0,row);
		rubai[x]=strval(row);
		//format(msg,sizeof(msg),"%s\nRubai Nr.%i",msg,strval(row));
		x++;
	}
	galikast[playerid]=false;
	SetTimerEx("GaliKast",1000,0,"i",playerid);
	if(x) ShowModelSelectionMenuEx(playerid, rubai, x, "Pasirinkite skina", GUI_MYSKINS, 0.0, 0.0, 0.0, 1.0);//, Float:mZoom = 1.0, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899 , tdSelectionColor = 0xFFFF00AA);
	else ShowPlayerDialog(playerid,1010,DIALOG_STYLE_MSGBOX,"Neturite rubu","Jus neturite pirktiniu rubu.\nJuos galite nusipirkti uz kreditus(/kreditai)","Gerai","");
	//else ShowPlayerDialog(playerid,1011,DIALOG_STYLE_LIST,"Rubai",msg,"Gerai","Atsaukti");
	return 1;
}

forward SQL_Spalvos(playerid);
public SQL_Spalvos(playerid)
{
	RestartCheck();
	new msg[4024];
	new row[20],x;
	new rows,fields; cache_get_data(rows,fields);
//	new rubai[300];
	new name[24];
	GetPlayerName(playerid,name,24);
	while(x<rows)
	{
		cache_get_row(x,0,row);
		new newstring[20];
		//strdel(row,0,
		strmid(newstring,row,2,8);
		//strmid(string, "Extract 'HELLO' without the !!!!: HELLO!!!!", 34, 39); //string contains "HELLO"
		format(msg,sizeof(msg),"%s{%s}%s\n",msg,newstring,name);
		x++;
	}
	if(x >= 7)
		ProcessAchievement(playerid,88);
	if(x) ShowPlayerDialog(playerid,1012,DIALOG_STYLE_LIST,"Spalvos",msg,"Gerai","Atsaukti"); //ShowModelSelectionMenuEx(playerid, rubai, x, "Pasirinkite skina", GUI_MYSKINS, 0.0, 0.0, 0.0, 1.0);//, Float:mZoom = 1.0, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899 , tdSelectionColor = 0xFFFF00AA);
	else ShowPlayerDialog(playerid,1010,DIALOG_STYLE_MSGBOX,"Neturite spalvu","Jus neturite pirktiniu vardo spalvu.\nJas galite nusipirkti uz kreditus(/kreditai)","Gerai","");
	//else ShowPlayerDialog(playerid,1011,DIALOG_STYLE_LIST,"Rubai",msg,"Gerai","Atsaukti");
	return 1;
}

forward SQL_Bagazas2(playerid,carid,itemid,count);
public SQL_Bagazas2(playerid,carid,itemid,count)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new query[256];
	if(rows)
	{
		if(itemid == 60)
			format(query,sizeof(query),"UPDATE Bagazine Set Count=1 WHERE Vardas='%s' AND Masina=%i AND Item=%i",count,ReturnName(playerid),carid,itemid);
		else
			format(query,sizeof(query),"UPDATE Bagazine Set Count=Count+%i WHERE Vardas='%s' AND Masina=%i AND Item=%i",count,ReturnName(playerid),carid,itemid);
		mysql_tquery(SQL,query);
		ShowBagazine(playerid);
		return 1;
	}
	else
	{
		format(query,sizeof(query),"INSERT INTO Bagazine(Vardas,Masina,Item,Count) VALUES ('%s',%i,%i,%i)",ReturnName(playerid),carid,itemid,count);
		mysql_tquery(SQL,query);
		ShowBagazine(playerid);
		return 1;
	}
}

forward SQL_Bagazas(playerid,mid);
public SQL_Bagazas(playerid,mid)
{
	RestartCheck();
	new Item,Countas;
	new x,fields,rows;
	cache_get_data(rows,fields);
	new msg[3024];
	new temp[12];
	while(x<rows)
	{
		cache_get_row(x,0,temp), Item= strval(temp);
		cache_get_row(x,1,temp), Countas= strval(temp);
		format(msg,sizeof(msg),"%s%s\n",msg,ReturnItemInfo(Item,Countas));
		x++;
	}
	format(msg,sizeof(msg),"%s{FF0000}Padeti...",msg);
	ShowPlayerDialog(playerid,1500,DIALOG_STYLE_LIST,((mid==4)?("Spintele"):("Bagazine")),msg,"Gerai","Atgal");
	return 1;
}

forward SQL_UnbanCheck(playerid,param[]);
public SQL_UnbanCheck(playerid,param[])
{
	RestartCheck();
	new fields,rows; cache_get_data(rows,fields);
	if(!rows)
	{
		return SendInfoMessage(playerid,"Banas nerastas!");
	}
	new uzrasas[128];
	format(uzrasas,128,"DELETE FROM `BANS` WHERE `Vardas` = '%s' or `IP`='%s' LIMIT 1",param,param);
	mysql_query(uzrasas);
	MLog(playerid,"Unban","s",param);
	SendInfoMessage(playerid,"Sekmingai atblokavai!");
	return 1;
}

forward SQL_IsmestiBaldus(playerid,houseid,slot);
public SQL_IsmestiBaldus(playerid,houseid,slot)
{
	RestartCheck();
	new Pav[50];
	cache_get_row(0,0,Pav);
	new msg[256];
	format(msg,sizeof(msg),"Ar norite ismesti baldus: %s Nr.%i?",Pav,BalduSistema[houseid][slot][b_obj]);
	PlayerLastBaldai[playerid]=slot;
	ShowPlayerDialog(playerid, 6881,DIALOG_STYLE_MSGBOX,"Baldu ismetimas",msg,"Gerai","Atsaukti");
	return 1;
}
forward SQL_Bagazine3(playerid,mid,kiek);
public SQL_Bagazine3(playerid,mid,kiek)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new x;
	new Countas,Item;
	
	while(x<rows)
	{
		if(playerDB[playerid][daiktas] == x)
		{
			//sscanf(row,"p<|>ii",Item,Countas);
			new temp[12];
			cache_get_row(x,0,temp), Item=strval(temp);
			cache_get_row(x,1,temp), Countas=strval(temp);
			if(kiek > Countas)
			{
				//mysql_free_result();
				SendInfoMessage(playerid,"Jus tiek neturite!");
				ShowBagazine(playerid);
				return 1;
			}
			if(Item == 56)
			{
				if(playerDB[playerid][masalas]+kiek > 200) 
					return SendInfoMessage(playerid,"~r~Nebepatempsi!");
			}
			if(Item == 57)
			{
				if(playerDB[playerid][zuvis]+kiek > 19) 
					return SendInfoMessage(playerid,"~r~Nebepatempsi!");
			}
			if(Item < 50)
			{
				new
					slot = GetWeaponsSlot(Item),
					weaponidas, kiekturi;
				
				GetPlayerWeaponData(playerid,slot,weaponidas,kiekturi);
				if(weaponidas != Item)
					kiekturi = 0;
				
				if(kiekturi + kiek >= 10000)
				{
					return SendInfoMessage(playerid,"~r~Negali paimti daugiau nei 10.000 kulku!");
				}

			}

			new row[256];

			if(Countas == kiek) format(row,sizeof(row),"DELETE FROM Bagazine WHERE Vardas='%s' AND Masina=%i AND Item=%i",ReturnName(playerid),mid,Item);
			else format(row,sizeof(row),"UPDATE Bagazine SET Count=Count-%i WHERE Vardas='%s' AND Masina=%i AND Item=%i",kiek,ReturnName(playerid),mid,Item);
			mysql_tquery(SQL,row);
			GiveItem(playerid,Item,kiek, mid);
			break;
		}
		x++;
	}
	return 1;
}
forward SQL_Laikrastis(playerid);
public SQL_Laikrastis(playerid)
{
	RestartCheck();
	new fields,rows;
	cache_get_data(rows,fields);
	new kiekbans = rows;
	if(rows <= 3) return ShowPlayerDialog(playerid,6432,DIALOG_STYLE_MSGBOX,"LSG Laikrastis","	   {FF9900}LSG Laikrastis\n{FFFFFF}Serveryje per mazai banu!","Praeitas psl.","Kitas psl."),0;
	new queryz[128];
	format(queryz,sizeof(queryz),"SELECT `Vardas`,`Adminas`,`Priezastis` FROM `BANS` LIMIT %i,3",(kiekbans-3));
	mysql_function_query(SQL, queryz, true, "SQL_Laikrastis2", "i", playerid);
	return 1;
}
forward SQL_Laikrastis2(playerid);
public SQL_Laikrastis2(playerid)
{
	RestartCheck();
	new Vardas[30],Admin[30],Reason[100],dialogolangas[512],x;
	new fields,rows;
	cache_get_data(rows,fields);
	format(dialogolangas,sizeof(dialogolangas),"	   {FF9900}LSG Laikrastis{FFFFFF}\n Vardas  |  Priezastis  |  Administratorius\n\n");
	while(x<rows)
	{
		//sscanf(result,"p<|>s[24]s[24]s[100]",Vardas,Admin,Reason);
		cache_get_row(x,0,Vardas);
		cache_get_row(x,1,Admin);
		cache_get_row(x,2,Reason);
		format(dialogolangas,sizeof(dialogolangas),"%s\n %s  |  %s  |  %s",dialogolangas,Vardas,Reason,Admin);
		x++;
	}
	ShowPlayerDialog(playerid,6432,DIALOG_STYLE_MSGBOX,"LSG Laikrastis",dialogolangas,"Praeitas psl.","Kitas psl.");
}
forward SQL_Laikrastis3(playerid);
public SQL_Laikrastis3(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows) { return SendClientMessage(playerid,RED,"Error."); }
	new Rekordas,Date[20],Pagerino[MAX_PLAYER_NAME];
	cache_get_row(0,0,Date), Rekordas=strval(Date);
	cache_get_row(0,1,Date);
	cache_get_row(0,2,Pagerino);
	//sscanf(result,"p<|>is[20]s[24]",Rekordas,Date,Pagerino);
	new string[512];
	format(string,sizeof(string),"	   {FF9900}LSG Laikrastis{FFFFFF}\n      Rekordas: {00FF00}%i{FFFFFF}\n      Data: {00FF00}%s{FFFFFF}\n      Pagerino: {00FF00}%s{FFFFFF}",Rekordas,Date,Pagerino);
	ShowPlayerDialog(playerid,6434,DIALOG_STYLE_MSGBOX,"LSG Laikrastis",string,"Praeitas psl.","Kitas Psl.");
	return 1;
}
forward SQL_Laikrastis4(playerid);
public SQL_Laikrastis4(playerid)
{
	RestartCheck();
	new string[1024];
	format(string,sizeof(string),"	   {FF9900}LSG Laikrastis\n    {FFFFFF}Statistika:\n");
	new temp[12];
	new Akauntu,Banu,TuriNama,TuriNamus,YraBizniu,NupirktiBzn,PoTrisMasinas;
	cache_get_row(0,0,temp), Akauntu = strval(temp);
	cache_get_row(1,0,temp), Banu = strval(temp);
	cache_get_row(2,0,temp), TuriNama = strval(temp);
	cache_get_row(3,0,temp), TuriNamus = strval(temp);
	cache_get_row(4,0,temp), YraBizniu = strval(temp);
	cache_get_row(5,0,temp), NupirktiBzn = strval(temp);
	cache_get_row(6,0,temp), PoTrisMasinas = strval(temp);
	format(string,sizeof(string),"%s\n o Yra Akauntu:{00FF00} %i{FFFFFF}.\n o Uzbaninti:{00FF00} %i{FFFFFF}.\n o Turi 1 Nama:{00FF00} %i{FFFFFF}. Turi 2 Namus:{00FF00} %i{FFFFFF}.\n o Yra Verslu:{00FF00} %i{FFFFFF}, nupirkti:{00FF00} %i{FFFFFF}.\n o Zaidejai turintys 3 automobilius:{00FF00} %i",string,Akauntu,Banu,TuriNama,TuriNamus,YraBizniu,NupirktiBzn,PoTrisMasinas);
	ShowPlayerDialog(playerid,6435,DIALOG_STYLE_MSGBOX,"LSG Laikrastis",string,"Praeitas psl.","Kitas psl.");
}
forward SQL_Laikrastis5(playerid);
public SQL_Laikrastis5(playerid)
{
	RestartCheck();
	new result[3048];
	new string[3548];
	cache_get_row(0,0,result);
	replaceChar(result,'~','\n');
//	UTF8_Decode(result, result2, 1024);
	format(string,sizeof(string),"	   {FF9900}LSG Laikrastis{FFFFFF}\n\n\n{00FF00}%s",result);
	ShowPlayerDialog(playerid,6436,DIALOG_STYLE_MSGBOX,"LSG Laikrastis",string,"Praeitas psl.","Uzversti");
}
forward SQL_Apanele(playerid);
public SQL_Apanele(playerid)
{
	RestartCheck();
	new row[50];
	new rows,fields;
	cache_get_data(rows,fields);
	new x;
	while(x<rows)
	{
		cache_get_row(x,0,row);
		if(strcmp(row,"Cheateriai",true)==0 )
		{
			AddDListItem(playerid, "Vagiu masinos", 0);
			AddDListItem(playerid, "Ginklai namuose, Kulku gamyba", 10);
		}
		else if(strcmp(row,"Admin",true)==0 || strcmp(row,"Admin2",true)==0) 
		{
			AddDListItem(playerid, "Emigracijos", 1);
			AddDListItem(playerid, "Pyzdino is afondo", 3);
			AddDListItem(playerid, "Jail/Kill", 5);
			AddDListItem(playerid, "Banai/Kickai", 6);
			AddDListItem(playerid, "Vagiu masinos", 0);
			AddDListItem(playerid, "Ginklai namuose, Kulku gamyba", 10);
			AddDListItem(playerid, "Save/Relog komandos",13);
			AddDListItem(playerid, "Range komanda",15);
			AddDListItem(playerid, "Padejo/paeme is kfondo", 20);
			AddDListItem(playerid, "N paspaudimai", 21);
			AddDListItem(playerid, "Pelnu pakeitimai", 22);
		}
		else if(strcmp(row,"Serveris",true)==0)
		{
			AddDListItem(playerid, "Slaptazodzio keitimai",2);
			AddDListItem(playerid, "Fix NPC",8);
			AddDListItem(playerid, "Vagiu masinos", 0);
			AddDListItem(playerid, "Ginklai namuose, Kulku gamyba", 10);
			AddDListItem(playerid, "Prieme/Ismete is darbo",9);
			AddDListItem(playerid, "Jail/Kill", 5);
			AddDListItem(playerid, "Banai/Kickai", 6);
			AddDListItem(playerid, "Save/Relog komandos",13);
			AddDListItem(playerid, "Padejo/paeme is kfondo", 20);
		}
		else if(strcmp(row,"DJ2",true)==0)
		{
			AddDListItem(playerid, "LOGIN daina",14);
		}
		else if(strcmp(row,"Dyrikai",true)==0 || strcmp(row,"Gaujos",true)==0)
		{
			AddDListItem(playerid, "Prieme/Ismete is darbo",9);
			AddDListItem(playerid, "Padejo/paeme is kfondo", 20);
			AddDListItem(playerid,	"Ismokejo alga",23);
			//MLog(playerid,"Paeme is kfondo","is",suma,reason);
		}
		x++;
	}
	AddDListItem(playerid, "Namu pirkimai", 4);
	AddDListItem(playerid, "Verslu pirkimai",7);
	AddDListItem(playerid, "Vardu keitimai",11);
	AddDListItem(playerid, "Banai/Kickai", 6);
	AddDListItem(playerid, "Mirtys/Nuzudymai", 12);
	AddDListItem(playerid, "Star dejimas", 16);
	AddDListItem(playerid, "AntiCheat Warnings", 17);
	AddDListItem(playerid, "Masinu Sprogimai", 18);
	AddDListItem(playerid, "Gauju ispejimai", 24);
	AddDListItem(playerid, "Iskvietimai", 25);
	ShowPlayerDList(playerid, 341, "Apanele", "Pasirinkti","Atgal");
	return 1;
}
forward SQL_NameChange(playerid,inputtext[]);
public SQL_NameChange(playerid,inputtext[])
{
	RestartCheck();
	new numrows,fields;
	cache_get_data(numrows,fields);
	new currentname[24];
	GetPlayerName(playerid,currentname,24);
	new isejo2 = SetPlayerName(playerid, inputtext);
	new isejo = InvalidNickKick(playerid, false);

	
	
	if(isejo==1)
	{
		SetPlayerName(playerid,currentname);
		return ShowPlayerDialog(playerid,88,DIALOG_STYLE_INPUT,"Vardo keitimas","Demesio! Jusu vardas musu serveryje netinkamas.\nJusu Vardas turi buti Vardas_Pavarde formatu.\nIveskite pageidaujama varda savo veikejui.\nVardas gali buti lietuviskas arba angliskas.{FF0000}\nJusu vardas netinkamas.","Ok","Ok");
	}
	else if(isejo2==-1 || numrows == 1)
	{
		SetPlayerName(playerid,currentname);
		return ShowPlayerDialog(playerid,88,DIALOG_STYLE_INPUT,"Vardo keitimas","Demesio! Jusu vardas musu serveryje netinkamas.\nJusu Vardas turi buti Vardas_Pavarde formatu.\nIveskite pageidaujama varda savo veikejui.\nVardas gali buti lietuviskas arba angliskas.{FF0000}\nToks vardas jau naudojamas.","Ok","Ok");
	}
	else if(isejo2==0)
	{
		SetPlayerName(playerid,currentname);
		return ShowPlayerDialog(playerid,88,DIALOG_STYLE_INPUT,"Vardo keitimas","Demesio! Jusu vardas musu serveryje netinkamas.\nJusu Vardas turi buti Vardas_Pavarde formatu.\nIveskite pageidaujama varda savo veikejui.\nVardas gali buti lietuviskas arba angliskas.{FF0000}\nTai dabartinis jusu vardas.","Ok","Ok");
	}
	else SendInfoMessage(playerid,"~g~Vardo keitimas sekmingas!");
	
	MLog(playerid,"Vardo keitimas is","s",currentname);
	NameChangeQuery(currentname, inputtext);
	GetPlayerName(playerid, StoredNames[playerid], MAX_PLAYER_NAME);
	return 1;

}
forward SQL_NameChange2(playerid,inputtext[]);
public SQL_NameChange2(playerid,inputtext[])
{
	RestartCheck();
	SetPVarString(playerid, "NewName",inputtext);
	new numrows,fields;
	cache_get_data(numrows,fields);
	MakePurchase(playerid, PURCHASE_VARDAS, numrows);
	return 1;
}
forward SQL_NameChange3(playerid,oldname[], newname[]);
public SQL_NameChange3(playerid,oldname[], newname[])
{
	RestartCheck();
	new numrows,fields;
	cache_get_data(numrows,fields);
	if(!numrows)
	{
		return SendClientMessage(playerid, -1, "Tokio vardo nera!");
	}
	if(numrows == 2)
	{
		return SendClientMessage(playerid, -1, "Toks vardas jau egzistuoja!");
	}
	new foundvardas[24];
	cache_get_row(0, 0, foundvardas);
	if(strcmp(foundvardas, oldname, true) != 0)
	{
		return SendClientMessage(playerid, -1, "Toks vardas jau egzistuoja!");
	}
	if(GetPlayeridMid(oldname) != INVALID_PLAYER_ID) return SendInfoMessage(playerid,"Sis zaidejas prisijunges! Naudokite /leistkeist");
	if(GetPlayeridMid(newname) != INVALID_PLAYER_ID) return SendInfoMessage(playerid,"Naujo vardo zaidejas prisijunges!");

	new isejo = InvalidNickCheck(newname);

	if(isejo==1)
	{
		return SendClientMessage(playerid, -1, "Naujas vardas netinkamas!");
	}

	NameChangeQuery(oldname, newname);
	SendClientMessage(playerid, -1, "Vardo keitimas sekmingas!");
	
	MLog(playerid,"Vardo pakeitimas","ss",oldname, newname);
	return 1;

}
forward SQL_GIsmesti(playerid,listitem);
public SQL_GIsmesti(playerid,listitem)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new	result[128],queryz[100];
	new x = 0;
	while(x<rows)
	{
		if(x==listitem)
		{
			cache_get_row(x,0,result);
			if(0==strcmp(FamilyInfo[playerDB[playerid][pgang]][FamilyLeader],result,true)) return SendInfoMessage(playerid,"~r~Negali ismesti gaujos vado!");
			new msg[128];
			format(msg,sizeof(msg),"Ismetei %s.",result);
			SendInfoMessage(playerid,msg);
			new forplayerid = GetIdForAlgos(result);
			if(forplayerid == INVALID_PLAYER_ID || playerDB[forplayerid][authstate]!=4)
			{
				if(0==strcmp(result,FamilyInfo[playerDB[playerid][pgang]][FamilySubstitute],true)) format(FamilyInfo[playerDB[playerid][pgang]][FamilySubstitute],24,"Nera");
				format(queryz,sizeof(queryz),"UPDATE `Account` SET `Gangas`=-1 WHERE `Name` = '%s'",result);
				mysql_query(queryz);
			}
			else
			{
				if(0==strcmp(ReturnName(forplayerid),FamilyInfo[playerDB[playerid][pgang]][FamilySubstitute],true)) format(FamilyInfo[playerDB[playerid][pgang]][FamilySubstitute],24,"Nera");
				SendInfoMessage(forplayerid,"~r~Jus ismete is gaujos!");
				playerDB[forplayerid][pgang]=-1;
				SavePlayerData(forplayerid,true);
			}
			break;
		}
		x++;
	}
	ShowGNarius(playerid);
	return 1;
}

forward SQL_Cpass(playerid,inputtext[]);
public SQL_Cpass(playerid,inputtext[])
{
	RestartCheck();
	new fafa[128];
	cache_get_row(0,0,fafa);
	if(strcmp(fafa, sha256_hash(inputtext),true) != 0){ SendInfoMessage(playerid,"~r~Senas slaptazodis neteisingas!"); return 1;}
	printf(" [PASS] %s Keicia password (senas)",ReturnName(playerid));
	ShowPlayerDialog(playerid,12313,DIALOG_STYLE_INPUT,"Cpass","Iveskite nauja slaptazodi","Gerai","Atsaukti");
	return 1;
}

forward SQL_CheckUnban(playerid);
public SQL_CheckUnban(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows)
	{
		SendInfoMessage(playerid,"~r~Jus neuzblokuotas!");
		new kredita[30];
		format(kredita,sizeof(kredita),"Turite %i kreditø",playerDB[playerid][kreditai]);
		ShowPlayerDialog(playerid, 1989, DIALOG_STYLE_TABLIST, kredita , PASLAUGU_DIALOG, "Pirkti", "Atsaukti");
		return 1;
	}
	if(!GiveKreditai(playerid, -20))
	{
		SendInfoMessage(playerid,"~r~Truksta kreditu!");
		new kredita[30];
		format(kredita,sizeof(kredita),"Turite %i kreditø",playerDB[playerid][kreditai]);
		ShowPlayerDialog(playerid, 1989, DIALOG_STYLE_TABLIST, kredita , PASLAUGU_DIALOG, "Pirkti", "Atsaukti");
		return 1;
	}
	new ip[20];
	GetPlayerIp(playerid,ip,sizeof(ip));
	new uzrasas[400];
	format(uzrasas,400,"DELETE FROM `BANS` WHERE `Vardas` = '%s' or `IP`='%s' LIMIT 1 ",ReturnName(playerid),ip);
	mysql_query(uzrasas);
	SendInfoMessage(playerid,"Galite toliau zaisti!~n~ Prisijunkite is naujo.");
	KickEx(playerid);
	return 1;
}
forward SQL_CheckStilius(playerid,listitem);
public SQL_CheckStilius(playerid,listitem)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows)
	{
		//mysql_free_result();
		return SendInfoMessage(playerid,"Tu jau turi si stiliu!");
	}
	MakePurchase(playerid, PURCHASE_STILIUS, listitem);
	return 1;
}
forward SQL_UpdateKred(playerid);
public SQL_UpdateKred(playerid)
{
	RestartCheck();
	new rowas[20];
	cache_get_row(0,0,rowas);
	playerDB[playerid][kreditai]=StringToInt(rowas);
	new msz[128];
	format(msz,128,"Pirkti kreditus(turite %i)\nGauti unban(nuo 20 kreditu)",playerDB[playerid][kreditai]);
	ShowPlayerDialog(playerid, 1990, DIALOG_STYLE_LIST, "Kreditai",msz,"Taip","Ne");
	return 1;
}
forward SQL_UpdateKred2(playerid);
public SQL_UpdateKred2(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows){ return 0; }
	new query[127];
	format(query,sizeof(query),"SELECT `Kreditai` From `Account` WHERE `Name`='%s'",ReturnName(playerid));
	mysql_function_query(SQL, query, true, "SQL_UpdateKred3", "i", playerid);
	return 1;
}
forward SQL_UpdateKred3(playerid);
public SQL_UpdateKred3(playerid)
{
	RestartCheck();
	new var[20];
	cache_get_row(0,0,var);
	playerDB[playerid][kreditai]=StringToInt(var);
	new msg[128];
	format(msg,sizeof(msg),"Apie kreditus\nPirkti kreditus\nPirkti paslaugas(%i kred.)",playerDB[playerid][kreditai]);
	ShowPlayerDialog(playerid, 1987, DIALOG_STYLE_LIST, "Kreditai",msg,"Taip","Ne");
	return 1;
}
forward SQL_GIsmesti2(playerid,escname[]);
public SQL_GIsmesti2(playerid,escname[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows) return SendInfoMessage(playerid,"~r~Tokio zaidejo nera.");
	new temp[12];
	cache_get_row(0,0,temp), fields=strval(temp);
	if(fields != playerDB[playerid][pgang]) return SendInfoMessage(playerid,"~r~Zaidejas ne jusu gaujoje.");
	new query[256];
	format(query,sizeof(query),"UPDATE `Account` SET `Gangas`='-1' WHERE `Name`='%s'",escname);
	mysql_query(query);
	SendInfoMessage(playerid,"~g~Ismetei!");
	return 1;
}
forward SQL_GangLimit(playerid);
public SQL_GangLimit(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new total = rows;
	if(total >= MAX_IN_FAMILY)
	{
		new string[128];
		format(string,sizeof(string),"Jusu gauja virsijo limita (%i/%i zmoniu)",total,MAX_IN_FAMILY);
		ShowGangDialog(playerid);
		return SendInfoMessage(playerid,string);
	}
	ShowPlayerDialog(playerid,5251,DIALOG_STYLE_INPUT,"Pakviesti","Iveskite zaidejo varda, kuri norite pakviesti.","Gerai","Blogai");
	return 1;
}
forward SQL_GangNariai(playerid);
public SQL_GangNariai(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new vardas[50];
	new x;
	while(x < rows)
	{
		cache_get_row(x,0,vardas);

		format(vardas,sizeof(vardas),"%i.%s",x+1,vardas);
		new id = GetPlayeridMid(vardas);
		if(id == INVALID_PLAYER_ID || !IsPlayerConnected(id) || playerDB[id][authstate] == 0)
			format(vardas,sizeof(vardas),"%i.%s",x+1,vardas);
		else
			format(vardas,sizeof(vardas),"%i.%s {FF0000}ON",x+1,vardas);


		SendClientMessage(playerid,GANG_COLOR,vardas);
		x++;
	}
	return ShowGangDialog(playerid);
}
forward SQL_Pervesti(playerid,id,inputtext[]);
public SQL_Pervesti(playerid,id,inputtext[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows < 1)
	{
		return SendInfoMessage(playerid,"~r~Blogai ivedei varda.");
	}

	new expas[12];
	cache_get_row(0,0,expas);
	if(!strval(expas)) return SendInfoMessage(playerid,"~r~Zaidejas neissaugojo zaidimo.");
	
	
	new procentas = playerDB[playerid][perveda]/100;
	//BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning]+=procentas;
	BusinessMoney(procentas*3/2);
	playerDB[playerid][perveda]-=procentas;
	new query[128];
	format(query,128,"UPDATE `Account` SET `Money.Bank` = `Money.Bank`+%i WHERE `Name` = '%s'",playerDB[playerid][perveda],inputtext);
	mysql_query(query);
	MLog(playerid,"Pervede","is",playerDB[playerid][perveda],inputtext);
	playerDB[playerid][banke]-=(playerDB[playerid][perveda]+procentas);
	
	SendInfoMessage(playerid,"Pervedimas sekmingas.");
	ProcessAchievement(playerid, 109);
	new msg[128];
	format(msg,sizeof(msg),"%s Jums pervede %i EUR.~Pervedimo mokestis: %iEUR.",ReturnName(playerid),playerDB[playerid][perveda]+procentas,procentas);
	EAtaskaita("Bankas",inputtext,"Pervedimo ataskaita",msg);
	format(msg,sizeof(msg),"Zaidejui %s Jus pervedete %i EUR.~Pervedimo mokestis: %iEUR.",inputtext,playerDB[playerid][perveda]+procentas,procentas);
	EAtaskaita("Bankas",ReturnName(playerid),"Pervedimo ataskaita",msg);
	if(!playerDB[playerid][kortele]) return SendInfoMessage(playerid,"Jus neturite banko saskaitos.~n~Pasiimkite ja kitoje kasoje.");
	format(msg,sizeof(msg),"{FFFFFF}Pervesti pinigus. Balansas: {33FF33}%i€\n{FFFFFF}Pervesti kreditus. Balansas: {33FF33}%i kred",playerDB[playerid][banke],playerDB[playerid][kreditai]);
	ShowPlayerDialog(playerid, 616, DIALOG_STYLE_LIST,"Bankas", msg, "Taip", "Ne");
	playerDB[playerid][perveda]=0;
	return 1;
}
forward SQL_PervestiKred(playerid,id,inputtext[]);
public SQL_PervestiKred(playerid,id,inputtext[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows < 1)
	{
		return SendInfoMessage(playerid,"~r~Blogai ivedei varda.");
	}

	new expas[12];
	cache_get_row(0,0,expas);
	if(!strval(expas)) return SendInfoMessage(playerid,"~r~Zaidejas neissaugojo zaidimo.");
	if(GetPlayerMoneyA(playerid) < 1000) return SendInfoMessage(playerid,"Neturi 1000EUR mokesciui");
	GivePlayerMoneyA(playerid, - 1000);
	
	//BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning]+=666;
	
	BusinessMoney(1000);
	if(!GiveKreditai(playerid, -playerDB[playerid][perveda]))
	{
		return SendInfoMessage(playerid, "Neuztenka kreditu!");
	}
	new query[128];
	format(query,128,"UPDATE `Account` SET `Kreditai` = `Kreditai`+%i WHERE `Name` = '%s'",playerDB[playerid][perveda],inputtext);
	mysql_query(query);
	MLog(playerid,"Pervede kred","is",playerDB[playerid][perveda],inputtext);
	SendInfoMessage(playerid,"Pervedimas sekmingas.");
	ProcessAchievement(playerid, 109);
	new msg[128];
	format(msg,sizeof(msg),"%s Jums pervede %i kred.",ReturnName(playerid),playerDB[playerid][perveda]);
	EAtaskaita("Bankas",inputtext,"Pervedimo ataskaita",msg);
	format(msg,sizeof(msg),"Zaidejui %s Jus pervedete %i kred.",inputtext,playerDB[playerid][perveda]);
	EAtaskaita("Bankas",ReturnName(playerid),"Pervedimo ataskaita",msg);
	if(!playerDB[playerid][kortele]) return SendInfoMessage(playerid,"Jus neturite banko saskaitos.~n~Pasiimkite ja kitoje kasoje.");
	format(msg,sizeof(msg),"{FFFFFF}Pervesti pinigus. Balansas: {33FF33}%i€\n{FFFFFF}Pervesti kreditus. Balansas: {33FF33}%i kred",playerDB[playerid][banke],playerDB[playerid][kreditai]);
	ShowPlayerDialog(playerid, 616, DIALOG_STYLE_LIST,"Bankas", msg, "Taip", "Ne");
	playerDB[playerid][perveda]=0;
	return 1;
}
forward SQL_Skinas(playerid,listitem);
public SQL_Skinas(playerid,listitem)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new msg[128];
	new row[10],x,skinid;
	while(x < rows)
	{
		cache_get_row(x,0,row);
		if(x==listitem) { skinid=strval(row); break; }
		x++;
	}
	format(msg,sizeof(msg),"Issirinkote skina Nr.~g~%i",skinid);
	SendInfoMessage(playerid,msg);
	SetPlayerSkin(playerid,skinid);
	playerDB[playerid][drabuziai]=skinid;
	new query[128];
	format(query,sizeof(query),"Update Spinta Set LastUsed=NOW() Where Vardas='%s' AND Skin=%i",ReturnName(playerid),skinid);
	mysql_query(query);
	return 1;
}
forward SQL_SpalvaSet(playerid,listitem);
public SQL_SpalvaSet(playerid,listitem)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new msg[128];
	new row[20],x; //,skinid;
	while(x < rows)
	{
		cache_get_row(x,0,row);
		if(x==listitem) 
		{ 
		
		break; 
		
		
		}
		x++;
	}
	if(isnull(row)) return 1;
	format(msg,sizeof(msg),"Issirinkote nauja vardo spalva!");
	if(strcmp(row,"0xFFFFFFFF",true)==0) SetPlayerColor(playerid,0xFFFFFFFF);
	if(strcmp(row,"0xCCCCCCFF",true)==0) SetPlayerColor(playerid,0xA8A8A8FF);
	if(strcmp(row,"0x00FF00FF",true)==0) SetPlayerColor(playerid,0x00FF00FF);
	if(strcmp(row,"0x0033FFFF",true)==0) SetPlayerColor(playerid,0x0033FFFF);
	if(strcmp(row,"0x33FFFFFF",true)==0) SetPlayerColor(playerid,0x33FFFFFF);
	if(strcmp(row,"0xFF00FFFF",true)==0) SetPlayerColor(playerid,0xFF00FFFF);
	if(strcmp(row,"0xFF6600FF",true)==0) SetPlayerColor(playerid,0xFF6600FF);
	if(strcmp(row,"0xFF0000FF",true)==0) SetPlayerColor(playerid,0xFF0000FF);
	if(strcmp(row,"0xFFFF00FF",true)==0) SetPlayerColor(playerid,0xFFFF00FF);
	// auksine
		//#FFD700
	// new spalvos
	if(strcmp(row,"0xFFCCCCFF",true)==0) SetPlayerColor(playerid,0xFFCCCCFF);
	if(strcmp(row,"0x33FFCCFF",true)==0) SetPlayerColor(playerid,0x33FFCCFF);
	if(strcmp(row,"0x003300FF",true)==0) SetPlayerColor(playerid,0x003300FF);
	if(strcmp(row,"0x660000FF",true)==0) SetPlayerColor(playerid,0x660000FF);
	if(strcmp(row,"0xCCFFFFFF",true)==0) SetPlayerColor(playerid,0xCCFFFFFF);
	if(strcmp(row,"0x6600CCFF",true)==0) SetPlayerColor(playerid,0x6600CCFF);
	// auksas sidabras bronza
	if(strcmp(row,"0xC98910FF",true)==0) SetPlayerColor(playerid,0xC98910FF);
	if(strcmp(row,"0xD2D2D230",true)==0) SetPlayerColor(playerid,0xD2D2D230);
	if(strcmp(row,"0x965A38FF",true)==0) SetPlayerColor(playerid,0x965A38FF);

	SendInfoMessage(playerid,msg);
	new query[256];
	format(query,sizeof(query),"UPDATE Spalvos Set `Set`=0 WHERE Vardas='%s'",ReturnName(playerid));
	mysql_query(query);
	format(query,sizeof(query),"UPDATE Spalvos Set `Set`=1 WHERE Vardas='%s' AND Color='%s' LIMIT 1",ReturnName(playerid),row);
	mysql_query(query);
	//SetPlayerSkin(playerid,skinid);
	//playerDB[playerid][drabuziai]=skinid;
	return 1;
}
forward SQL_Login(playerid,inputtext[]);
public SQL_Login(playerid,inputtext[])
{
	RestartCheck();
	
	new row[128];
	cache_get_row(0,0,row);
	if(strcmp(row, sha256_hash(inputtext),true) != 0)
	{
		new query[256];
		format(query,sizeof(query),"SELECT Kodas From RemindPassword Where Vardas='%s'",ReturnName(playerid));
		mysql_function_query(SQL, query, true, "SQL_Login2", "is", playerid,inputtext);
		
	}
	else // Jai slaptazodis yra teisingas.
	{
		if(playerDB[playerid][authstate]==2)
		{
			SendClientMessage(playerid,COLOR," * Tu jau prisijunges!");
			return 1;
		}
		CheckEmailStatus(playerid,1);
		
	}
	return 1;
}
forward SQL_Login2(playerid,inputtext[]);
public SQL_Login2(playerid,inputtext[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows)
	{
		new kodas[128];
		cache_get_row(0,0,kodas);
		if(strcmp(sha256_hash(kodas), sha256_hash(inputtext),true) != 0)
		{
			ShowPlayerDialog(playerid,9877,DIALOG_STYLE_PASSWORD,"Prisijungimas","Slaptazodis neteisingas.\nIveskite savo slaptazodi:","Prisijungti","Iseiti");
			TextDrawShowForPlayer(playerid,PassReminder);
			SelectTextDraw(playerid, 0x00FF00FF); 
			TextDrawShowForPlayer(playerid,PassReminder);
			SetPVarInt(playerid,"WrongPass",GetPVarInt(playerid,"WrongPass")+1);
			if(GetPVarInt(playerid,"WrongPass") > 3)
			{
				SendClientMessage(playerid,RED," * Per daug neteisingu bandymu!");
				AC_Kick(playerid,"Neteisingas slaptazodis");
			}
		}
		else
		{
			new file[256];
			format(file,256,"UPDATE `Account` SET `Slaptazodis` = '%s' WHERE `Name` = '%s'",sha256_hash(inputtext),ReturnName(playerid));
			mysql_query(file);
			format(file,128,"DELETE From RemindPassword Where Vardas='%s'",ReturnName(playerid));
			mysql_query(file);
			format(file,sizeof(file)," * DEMESIO! Jusu naujasis slaptazodis: %s , senasis slaptazodis nebegalioja.",inputtext);
			SendClientMessage(playerid,WHITE,file);
			if(playerDB[playerid][authstate]==2)
			{
				SendClientMessage(playerid,COLOR," * Tu jau prisijunges!");
				return 1;
			}
			CheckEmailStatus(playerid,1);
		}
	}
	else
	{
		ShowPlayerDialog(playerid,9877,DIALOG_STYLE_PASSWORD,"Prisijungimas","Slaptazodis neteisingas.\nIveskite savo slaptazodi:","Prisijungti","Iseiti");
		TextDrawShowForPlayer(playerid,PassReminder);
		SelectTextDraw(playerid, 0x00FF00FF); 
		TextDrawShowForPlayer(playerid,PassReminder);
		SetPVarInt(playerid,"WrongPass",GetPVarInt(playerid,"WrongPass")+1);
		if(GetPVarInt(playerid,"WrongPass") > 3)
		{
			SendClientMessage(playerid,RED," * Per daug neteisingu bandymu!");
			AC_Kick(playerid,"Neteisingas slaptazodis");
		}
	}
	return 1;
}
forward SQL_Inbox(playerid);
public SQL_Inbox(playerid)
{
	RestartCheck();
	new 
		temp[12],
		ID,
		Subject[100],
		Sender[60],
		Time2[15],
		Date[20],
		Message[2600],
		New=0,
		Mk;
	cache_get_row(0,0,temp), ID=strval(temp);
	cache_get_row(0,1,Sender);
	cache_get_row(0,2,Subject);
	cache_get_row(0,3,Time2);
	cache_get_row(0,4,Date);
	cache_get_row(0,5,temp), New=strval(temp);
	cache_get_row(0,6,temp), Mk=strval(temp);
	cache_get_row(0,7,Message);
	if(Mk< 0) return 1;
	//sscanf(result,"p<|>is[60]s[100]s[15]s[20]iis[256]",ID,Sender,Subject,Time2,Date,New,Mk,Message);
	replaceChar(Message,'~','\n');
	new result[4096];
	format(result,sizeof(result),"{FFFFFF}Data:{FF9933} %s{FFFF33} %s\n{FFFFFF}Siuntejas:{FFFF33} %s\n{FFFFFF}Tema: %s\n\n\n%s",Date,Time2,Sender,Subject,Message);

	format(RecieverP[playerid],60,"%s",Sender);
	MkP[playerid]=ID;
	ShowPlayerDialog(playerid,DIALOGID-1,DIALOG_STYLE_MSGBOX,"Zinute",result,"Veiksmai","Atgal");
	if(New)
	{
		format(result,sizeof(result),"UPDATE `Emails` SET `New`=0 WHERE `ID`='%i' LIMIT 1",ID);
		mysql_query(result);
	}
	return 1;
}
forward SQL_Outbox(playerid);
public SQL_Outbox(playerid)
{
	RestartCheck();
	new result[4096];
	new
		Subject[100],
		Reciever[60],
		Time2[15],
		Date[20],
		Message[2600];
	cache_get_row(0,0,Reciever);
	cache_get_row(0,1,Subject);
	cache_get_row(0,2,Time2);
	cache_get_row(0,3,Date);
	cache_get_row(0,4,Message);
	//sscanf(result,"p<|>s[60]s[100]s[15]s[20]s[256]",Reciever,Subject,Time2,Date,Message);
	replaceChar(Message,'~','\n');
	format(result,sizeof(result),"{FFFFFF}Data:{FF9933} %s{FFFF33} %s\n{FFFFFF}Gavejas:{FFFF33} %s\n{FFFFFF}Tema: %s\n\n\n%s",Date,Time2,Reciever,Subject,Message);
	ShowPlayerDialog(playerid,DIALOGID-2,DIALOG_STYLE_MSGBOX,"Zinute",result,"Gerai","Atsaukti");
	return 1;
}
forward SQL_Gautieji(playerid);
public SQL_Gautieji(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new 
		result[4096],
		Subject[20],
		Sender[60],
		Time2[20],
		New,
		temp[12],
		x
		;
	
	if(!rows) return SendInfoMessage(playerid,"Tu neturi laisku!"),ShowEmail(playerid);
	format(result,sizeof(result),"Tema\tSiuntëjas\tData\n");
	while(x<rows)
	{
		//sscanf(QR,"p<|>s[60]s[100]s[10]i",Sender,Subject,Time2,New);
		cache_get_row(x,0,Sender);
		cache_get_row(x,1,Subject);
		cache_get_row(x,2,Time2);
		cache_get_row(x,3,temp), New=strval(temp);
		//if(strlen(Subject) > 15)
		if(!New)
			format(result,sizeof(result),"%s{878787}%s\t{FF9933}%s\t{FFFF33}%s\n",result,Subject,Sender,Time2);
		else
			format(result,sizeof(result),"%s{FFFFFF}%s\t{FF9933}%s\t{FFFF33}%s\n",result,Subject,Sender,Time2);
		x++;
	}
	//mysql_free_result();
	ShowPlayerDialog(playerid,DIALOGID+1,DIALOG_STYLE_TABLIST_HEADERS,"Gautieji",result,"Gerai","Atgal");
	return 1;
}
forward SQL_Issiustieji(playerid);
public SQL_Issiustieji(playerid)
{
	RestartCheck();
	new fields,rows;
	cache_get_data(rows,fields);
	
	new	result[4096],
		Subject[100],
		Reciever[60],
		Time2[100],
		New,
		x,
		temp[12]
		;

	if(!rows) return SendInfoMessage(playerid,"Neturi issiustu laisku!");
	format(result,sizeof(result),"Tema\tGavëjas\tData\n");
	while(x < rows)
	{
		//sscanf(QR,"p<|>s[60]s[100]s[10]i",Reciever,Subject,Time2,New);
		cache_get_row(x,0,Reciever);
		cache_get_row(x,1,Subject);
		cache_get_row(x,2,Time2);
		cache_get_row(x,3,temp),New=strval(temp);
		if(!New)
			format(result,sizeof(result),"%s{878787}%s\t{FF9933}%s\t{FFFF33}%s\n",result,Subject,Reciever,Time2);
		else
			format(result,sizeof(result),"%s{FFFFFF}%s\t{FF9933}%s\t{FFFF33}%s\n",result,Subject,Reciever,Time2);
		x++;
	}
	//mysql_free_result();
	ShowPlayerDialog(playerid,DIALOGID+2,DIALOG_STYLE_TABLIST_HEADERS,"Issiustieji",result,"Gerai","Atgal");
	return 1;
}
forward SQL_SendMass(playerid);
public SQL_SendMass(playerid)
{
	RestartCheck();
	new
		query[4096],
		hour,
		minute,
		second,
		day,
		month,
		year,
		mk,
		msg[128];
		
	new inputtext[2600];
	GetPVarString(playerid, "MsgText", inputtext, 2600);

	gettime(hour,minute,second);
	getdate(year,month,day);
	mk = mktime(hour,minute,second,day,month,year);
	new fields,rows;
	cache_get_data(rows,fields);
	new x;
	while(x<rows)
	{
		cache_get_row(x,0,msg);
		format(query,sizeof(query),"INSERT INTO `Emails` (Sender,Reciever,Date,Time,MK,New,Subject,Text,DateTime) VALUES('%s','%s','%i-%i-%i','%02d:%02d',%i,1,'%s','%s',NOW())",
											ReturnName(playerid),msg,day,month,year,hour,minute,mk,SubjectP[playerid],inputtext);
		mysql_query(query);
		new mid = GetIdForAlgos(msg);
		if(mid != INVALID_PLAYER_ID)
			GameTextForPlayer(mid,"Gautas E-Mail.", 2000,5);
		x++;
	}
	LastEmail[playerid] = GetTickCount();
	SendInfoMessage(playerid,"Masine Zinute issiusta!");
	return 1;
}
forward SQL_MailCheck(playerid);
public SQL_MailCheck(playerid)
{
	RestartCheck();
	new
		query[4096],
		hour,
		minute,
		second,
		day,
		month,
		year,
		mk;
		
	new inputtext[2600];
	GetPVarString(playerid, "MsgText", inputtext, 2600);

	gettime(hour,minute,second);
	getdate(year,month,day);
	mk = mktime(hour,minute,second,day,month,year);
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows)
	{
		return SendInfoMessage(playerid,"Toks zaidejas neegzistuoja!!");
	}
	format(query,sizeof(query),"INSERT INTO `Emails` (Sender,Reciever,Date,Time,MK,New,Subject,Text,DateTime) VALUES('%s','%s','%i-%i-%i','%02d:%02d',%i,1,'%s','%s',NOW())",
													ReturnName(playerid),RecieverP[playerid],day,month,year,hour,minute,mk,SubjectP[playerid],inputtext);
	mysql_query(query);
	new mid = GetIdForAlgos(RecieverP[playerid]);
	if(mid != INVALID_PLAYER_ID)
		GameTextForPlayer(mid,"Gautas E-Mail.", 2000,5);
	SendInfoMessage(playerid,"Zinute issiusta!");
	
	LastEmail[playerid] = GetTickCount();
	ProcessAchievement(playerid,32);
	return 1;
}
forward SQL_UpdateKred4(playerid,kaina,dealeris,kiek,answer);
public SQL_UpdateKred4(playerid,kaina,dealeris,kiek,answer)
{
	RestartCheck();
	new rowas[20];
	cache_get_row(0,0,rowas);
	playerDB[playerid][kreditai]=StringToInt(rowas);
	
	if(answer == 1)
	{
		if(GetPlayerMoneyA(playerid) < kaina*kiek)
		{
			SendInfoMessage(playerid,"Neturi Litu Ubage");
			SendInfoMessage(playerid," Neturi Litu Ubagas");
			return 1;
		}
		if(!GiveKreditai(dealeris, -kiek))
		{
			return SendInfoMessage(playerid,"Jis tiek nebeturi!");
		}
		GiveKreditai(playerid, kiek);
		
		GivePlayerMoneyA(playerid,-kaina*kiek);
		GivePlayerMoneyA(dealeris,kaina*kiek);
		SendInfoMessage(playerid,"Kreditai priimti");
		SendInfoMessage(playerid,"Kreditai atiduoti");
		MLog(playerid,"Nusipirko krd po","isiss",kiek,"vnt",kaina,"lt",ReturnName(dealeris));
		LogKredituSell(dealeris, kiek, playerid, kaina);
		return 1;
	}

	SendInfoMessage(playerid,"Kreditai nepriimti");
	SendInfoMessage(playerid,"Kreditai neatiduoti");
	return 1;
}

forward SQL_GangCount(playerid,pi);
public SQL_GangCount(playerid,pi)
{
	RestartCheck();
	new total,fields;
	cache_get_data(total,fields);
	if(total >= MAX_IN_FAMILY)
	{
		new string[128];
		format(string,sizeof(string),"Gauja virsija limita(%i/%i zmoniu)",total,MAX_IN_FAMILY);
		return SendInfoMessage(playerid,string);
	}
	playerDB[playerid][ginvited][pi]=false;
	new msg[128];
	format(msg,128,"[gauja] %s prisijunge prie musu gaujos!",ReturnName(playerid));
	if(GetPVarInt(playerid, "LeftPD") == 1)
		ProcessAchievement(playerid, 80);
	SendMessageToFamily(pi,COLOR,msg);
	SendInfoMessage(playerid,"Sekmingai prisijungei prie musu gaujos!");
	playerDB[playerid][pgang]=pi;
	MLog(playerid,"Prisijunge prie gaujos","i", pi);
	CheckTraitorAch(playerid);
	PlaySound(playerid,43200);
	SavePlayer(playerid,true);
	return 1;
}

forward SQL_TraitorCheck(playerid);
public SQL_TraitorCheck(playerid)
{
	RestartCheck();
	new total,fields;
	cache_get_data(total,fields);
	if(total >= MAX_FAMILY)
	{
		new x;
		new arr[MAX_FAMILY];
		while(x<total)
		{
			new temp[20];
			cache_get_row(x,0,temp);
			arr[strval(temp)]=1;
			x++;
		}
		new a;
		for(new i;i<MAX_FAMILY;i++)
		{
			if(arr[i]==1) a++;
		}
		if(a== MAX_FAMILY)
		{
			ProcessAchievement(playerid,38);
		}
	}
}


forward SQL_AdminList(playerid);
public SQL_AdminList(playerid)
{
	new var[30];
	new rows, fields;
    cache_get_data(rows, fields);

	new jau=0;
	while(jau < rows)
	{
		cache_get_row(jau, 0, var);
		cmd_onlinetime(playerid,var);
		jau++;
	}
	return 1;
}

forward SQL_CheckUnbanAch(playerid);
public SQL_CheckUnbanAch(playerid)
{
	new rows, fields;
    cache_get_data(rows, fields);
    if(rows)
    	ProcessAchievement(playerid,90);
}


forward SQL_Praleido(playerid,vardas[]);
public SQL_Praleido(playerid,vardas[])
{	
	RestartCheck();
	new time[24],timevar;
	cache_get_row(0, 0, time);

	timevar=strval(time);
	cache_get_row(1, 0, time);
	new msg[228];
	format(msg,sizeof(msg)," * Administratorius %s praleido %imin. per savaite(%iN)",vardas,timevar,strval(time));
	SendClientMessage(playerid,YELLOW,msg);
}

forward SQL_DyrList(playerid);
public SQL_DyrList(playerid)
{
	new var[30];
	new vardas[30];
	new rows, fields;
    cache_get_data(rows, fields);

	new jau=0;
	while(jau < rows)
	{
		cache_get_row(jau, 0, vardas);
		cache_get_row(jau, 1, var);
		new dyrikas = strval(var);
		
		new query[1024];
		format(query,sizeof(query),"SELECT SUM(`Variable`) From Logs WHERE UPPER(`Zaidejas`)=UPPER('%s') AND Veiksmas='Praleido'",vardas);
		mysql_function_query(SQL, query, true, "SQL_PraleidoDyr", "isi", playerid, vardas,dyrikas);
		
		jau++;
	}
	return 1;
}
forward SQL_PraleidoDyr(playerid,vardas[],dyrikas);
public SQL_PraleidoDyr(playerid,vardas[],dyrikas)
{	
	RestartCheck();
	new time[24],timevar;
	new kieno[80];
	if(dyrikas == 2) kieno = "Mediku";
	else if(dyrikas == 3) kieno = "Transporto";
	//else if(dyrikas == 4) kieno = "Apsauginiu";
	else if(dyrikas == 5) kieno = "Kroviniu Transporto";
	else if(dyrikas == 6) kieno = "Mechaniku";
	else if(dyrikas == 66) kieno = "Gaisrininku";
	else if(dyrikas == 70) kieno = "Autoklubo";
	else if(dyrikas == 80) kieno = "Teisesaugos";
	else if(dyrikas == 50) kieno = "Skelbeju";
	else if(dyrikas == 98) kieno = "Baikeriu";
	else if(dyrikas == 90) kieno = "Dealeriu";
	else if(dyrikas == 58) kieno = "Vagiu";
	else if(dyrikas == 34) kieno = "Nekilnojamo Turto agentu";
	else if(dyrikas == 60) kieno = "Inkasatoriu";
	cache_get_row(0, 0, time);
	timevar=strval(time);
	new msg[228];
	format(msg,sizeof(msg)," * %s direktorius %s praleido %imin. per paskutines 7d.",kieno,vardas,timevar);
	SendClientMessage(playerid,YELLOW,msg);
	return 1;
}

forward SQL_PastasCheck(playerid);
public SQL_PastasCheck(playerid)
{
	//SendClientMessage(playerid,COLOR,"PastasCheck");
	RestartCheck();
	new rows,fields; cache_get_data(rows,fields);
	if(!rows)
	{
		SendClientMessage(playerid, COLOR_RED, " * Tavo el.pasto adresas nenustatytas.");
		KickEx(playerid,300);
		return 1;
	}
	new row[60];
	cache_get_row(0,0,row);
	new query[256];
	format(query,sizeof(query),"SELECT * From `RemindPassword` WHERE Vardas='%s'",ReturnName(playerid));
	mysql_function_query(SQL, query, true, "SQL_PastasCheck2", "is", playerid,row);
	return 1;
}
forward SQL_PastasCheck2(playerid,emailas[]);
public SQL_PastasCheck2(playerid,emailas[])
{
	//SendClientMessage(playerid,COLOR,"PastasCheck2");
	RestartCheck();
	new rows,fields; cache_get_data(rows,fields);
	if(rows)
	{
		SendClientMessage(playerid, COLOR_RED, " * Tu jau issiuntei priminimo prasyma. Jei negauni laisko, bandyk vel po 24 valandu.");
		KickEx(playerid,300);
		return 1;
	}
	SendPassReminder(playerid,emailas);
	return 1;
}

forward SQL_Patruliai();
public SQL_Patruliai()
{
	RestartCheck();
	new temp[30];
	new rows,fields; cache_get_data(rows,fields);
	new idx=0;
	while(idx<rows)
	{
		cache_get_row(idx,0,Patruliai[idx][pavv],SQL,12);
		cache_get_row(idx,1,temp); Patruliai[idx][possx]=floatstr(temp);
		cache_get_row(idx,2,temp); Patruliai[idx][possy]=floatstr(temp);
		cache_get_row(idx,3,temp); Patruliai[idx][rangee]=floatstr(temp);
		cache_get_row(idx,4,temp); Patruliai[idx][pplmax]=strval(temp);
		Patruliai[idx][dynamicarea] = CreateDynamicAreaAroundPos(Patruliai[idx][possx],Patruliai[idx][possy],Patruliai[idx][rangee]);
		Patruliai[idx][gangz] = CreateGangZoneAroundPos(Patruliai[idx][possx],Patruliai[idx][possy],Patruliai[idx][rangee]);
		Patruliai[idx][used]=1;
		Patruliai[idx][pplin]=0;
		idx++;
	}
	return 1;
}

forward SQL_SaveMasina(playerid,query[],name[]);
public SQL_SaveMasina(playerid,query[],name[])
{
	RestartCheck();
	//printf("1 - %s",query);
	new rows,fields;
	cache_get_data(rows,fields);
	if(DEBUG) printf("10");
	if(!rows)
	{
		if(DEBUG) printf("11");
		//mysql_free_result();
		new var[1024];
		format(var,sizeof(var),"INSERT INTO `Cars` (`Owner`,`AH_Typ`,`AH2_Typ`,`AH3_Typ`,`AH_X`,`AH_Y`,`AH_Z`,`AH_Rot`,`AH2_X`,`AH2_Y`,`AH2_Z`,`AH2_Rot`,`AH3_X`,`AH3_Y`,`AH3_Z`,`AH3_Rot`) VALUES ('%s',-1,-1,-1,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000)",name);
	    mysql_function_query(SQL, var, false, "SQL_SaveMasina2", "is", playerid, query);
		return 1;
	}
	if(DEBUG) printf("12");
	mysql_query(query);
	return 1;
}
forward SQL_SaveMasina2(playerid,query[]);
public SQL_SaveMasina2(playerid,query[])
{
	RestartCheck();
	//printf("2 - %s",query);
	if(DEBUG) printf("13");
	mysql_query(query);
	return 1;
}

forward SQL_SelectedBaldai(playerid,obj);
public SQL_SelectedBaldai(playerid,obj)
{
	RestartCheck();
	//new msg[4024];
	new row[10];
	cache_get_row(0,0,row);
	new kaina = strval(row);
	if(!kaina) return 0;
	new msg[128];
	format(msg,sizeof(msg),"Ar norite pirkti preke nr.%i?\nKaina: %i€",obj,kaina);
	ShowPlayerDialog(playerid,6878,DIALOG_STYLE_MSGBOX,"Baldai",msg,"Gerai","Atsaukti");
	PlayerLastBaldai[playerid]=obj;
	PlayerLastKaina[playerid]=kaina;
	return 1;
}

forward SQL_ShowCat(playerid);
public SQL_ShowCat(playerid)
{
	if(LoadOrderInka(playerid))
		return;
	new msg[1024];
	RestartCheck();
	//new msg[4024];
	new x;
	new rows,fields; cache_get_data(rows,fields);
	new temp[60];
	while(x<rows)
	{
		cache_get_row(x,1,temp);
		format(msg,sizeof(msg),"%s%i.%s\n",msg,x+1,temp);
		x++;
	}
	ShowPlayerDialog(playerid,6879,DIALOG_STYLE_LIST,"Baldai",msg,"Gerai","Atsaukti");
}

forward SQL_LoadCat(playerid);
public SQL_LoadCat(playerid)
{
	new row[12]; new id;
	cache_get_row(0,0,row);
	id = strval(row);
	ShowBaldaiShope(playerid,id);
	return 1;
}


/*
forward SQL_ViewCategory(playerid,houseid,listitem);
public SQL_ViewCategory(playerid,houseid,listitem)
{
	RestartCheck();
	new msg[1024];
	new row[50],x;
	new rows,fields; cache_get_data(rows,fields);	
	if(!rows) return SendInfoMessage(playerid,"~r~Neturi baldu sioje kategorijoje!");
	new objectid,cat;
	while(x<rows)
	{
		
		cache_get_row(x,2,row);
		objectid=strval(row);
		cache_get_row(x,
		//format(msg,sizeof(msg),"%s%s\n",msg,row);
		x++;
	}
	//ShowPlayerDialog(playerid,6873,DIALOG_STYLE_LIST,
	return 1;
}
*/
forward SQL_SelectMoveBaldai(playerid,houseid);
public SQL_SelectMoveBaldai(playerid,houseid)
{
	RestartCheck();
	//new msg[1024];
	new row[50],x;
	new rows,fields; cache_get_data(rows,fields);
	new frm[100];
	new baldaicats[1000]; // actually 32 but 1000 should last for a while

	if(houseid >= MAX_HOUSES)
		return 1;

	for(new i;i<MAX_BALDAI;i++)
	{
		if(BalduSistema[houseid][i][b_used]) //listitem
		{
			if(BalduSistema[houseid][i][b_cat] >= 0)
				baldaicats[BalduSistema[houseid][i][b_cat]]++;
		}
	}

	while(x<rows)
	{
		new temp[24];
		cache_get_row(x,0,temp);
		new catid = strval(temp);
		cache_get_row(x,1,row);
		format(frm,100,"%s\t"#TEXT_BLUE"%i",row,baldaicats[catid]);
		AddDListItem(playerid, frm, catid);
		//format(msg,sizeof(msg),"%s%s\n",msg,row);
		x++;
	}
	ShowPlayerDListHeader(playerid, 6872,"Pasirinkite kategorija", "Rinktis", "Iseiti","Kategorija\tBaldø kiekis");
	//ShowPlayerDialog(playerid,6872,DIALOG_STYLE_LIST,"Pasirinkite kategorija",msg,"Gerai","Atsaukti");
	return 1;
}
forward SQL_SelectDeleteBaldai(playerid,houseid);
public SQL_SelectDeleteBaldai(playerid,houseid)
{
	RestartCheck();
	//new msg[1024];
	new row[50],x;
	new rows,fields; cache_get_data(rows,fields);

	while(x<rows)
	{
		new temp[24];
		cache_get_row(x,0,temp);
		new catid = strval(temp);
		cache_get_row(x,1,row);
		AddDListItem(playerid, row, catid);
		x++;
	}
	ShowPlayerDList(playerid,6875,"Pasirinkite kategorija","Gerai","Atsaukti");
	return 1;
}

forward SQL_BaldaiShope(playerid,cat);
public SQL_BaldaiShope(playerid,cat)
{
	RestartCheck();
	//new msg[4024];
	new row[10],x;
	new rows,fields; cache_get_data(rows,fields);
	new baldai[300];
	//id,cat,pav,obj,kaina
	while(x<rows)
	{
		if(x==300) break;
		cache_get_row(x,0,row);
		baldai[x]=strval(row);
		//format(msg,sizeof(msg),"%s\nRubai Nr.%i",msg,strval(row));
		x++;
	}
	if(x) ShowModelSelectionMenuEx(playerid, baldai, x, "Pasirinkite baldus", GUI_BALDAI+cat, 340.0, 0.0, 180.0, 1.5,0xF2FEBFBB,0xE6FE8099,0x88888899);
	else ShowPlayerDialog(playerid,1010,DIALOG_STYLE_MSGBOX,"Nera baldu","Sioje kategorijoje dabar neturime baldu!","Gerai","");
	//else ShowPlayerDialog(playerid,1011,DIALOG_STYLE_LIST,"Rubai",msg,"Gerai","Atsaukti");
	return 1;
}


forward SQL_BalduQuery(houseid);
public SQL_BalduQuery(houseid)
{
	RestartCheck();
	new rows,fields; cache_get_data(rows,fields);
	new idx=0;
	new temp[15];
	while(idx<rows)
	{
		BalduSistema[houseid][idx][b_used]=1;
		cache_get_row(idx,2,temp); BalduSistema[houseid][idx][b_obj]=strval(temp);
		cache_get_row(idx,3,temp); BalduSistema[houseid][idx][b_x]=floatstr(temp);
		cache_get_row(idx,4,temp); BalduSistema[houseid][idx][b_y]=floatstr(temp);
		cache_get_row(idx,5,temp); BalduSistema[houseid][idx][b_z]=floatstr(temp);
		cache_get_row(idx,6,temp); BalduSistema[houseid][idx][b_rx]=strval(temp);
		cache_get_row(idx,7,temp); BalduSistema[houseid][idx][b_ry]=strval(temp);
		cache_get_row(idx,8,temp); BalduSistema[houseid][idx][b_rz]=strval(temp);
		cache_get_row(idx,9,temp); BalduSistema[houseid][idx][b_cat]=strval(temp);
		//BalduSistema[houseid][idx][b_oid]=CreateDynamicObject(BalduSistema[houseid][idx][b_obj],BalduSistema[houseid][idx][b_x],BalduSistema[houseid][idx][b_y],BalduSistema[houseid][idx][b_z],BalduSistema[houseid][idx][b_rx],BalduSistema[houseid][idx][b_ry],BalduSistema[houseid][idx][b_rz],GetHouseVirtualWorld(houseid), _, _, 50.0);
		//FixBalduObj(BalduSistema[houseid][idx][b_oid]);
		CreateBaldas(houseid,idx);
		idx++;
	}
	return 1;
}

forward SQL_LoadGaujosVadui(playerid,gang);
public SQL_LoadGaujosVadui(playerid,gang)
{
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
	new msg[1024];
	new lolas;
	if(rows)
	{
		new lastuseris[24],status,Float:health,Float:gasas,temp[30];
		while(lolas < rows)
		{
			cache_get_row(lolas,2,lastuseris);
			cache_get_row(lolas,3,temp); status=strval(temp);
			cache_get_row(lolas,4,temp); health=floatstr(temp);
			cache_get_row(lolas,5,temp); gasas=floatstr(temp);
			if(!status) format(msg,sizeof(msg),"%s{FF0000}%i.Paskutinis naudojo %s(%iHP/%iL)\n",msg,lolas+1,lastuseris,floatround(health),floatround(gasas));
			else if(status==2) format(msg,sizeof(msg),"%s{FFFFFF}%i.Dabar naudojasi %s(%iHP/%iL)\n",msg,lolas+1,lastuseris,floatround(health),floatround(gasas));
			else if(status==1) format(msg,sizeof(msg),"%s{00FF00}%i.Paskutinis naudojo %s(%iHP/%iL)\n",msg,lolas+1,lastuseris,floatround(health),floatround(gasas));
			//format(dialogtext,3048,"%s%i. %s %s(%s) [%s]\n",dialogtext,x,Nameas,Veiksmas,Variable,Data);
			lolas++;
		}
	}
	if(lolas < 10)
	{
		format(msg,sizeof(msg),"%s{FFFFFF}Pirkti automobili("#COST_DCGANGCAR"€)",msg);
	}
	ShowPlayerDialog(playerid,7801,DIALOG_STYLE_LIST,"Gaujos automobiliai",msg,"Gerai","Atsaukti");
	return 1;
}

forward SQL_ChosenCar(playerid,gang,listitem);
public SQL_ChosenCar(playerid,gang,listitem)
{
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
	if(!rows)
	{
		if(GetPlayerMoneyA(playerid) < COST_DCGANGCAR)
			return SendInfoMessage(playerid,"Truksta pinigu!");
		GivePlayerMoneyA(playerid,-COST_DCGANGCAR);
		new query[512];
		format(query,sizeof(query),"INSERT INTO `gangcars` (`gang`,`lastuser`,`status`,`health`,`gas`,`mod1`,`mod2`,`mod3`,`mod4`,`mod5`,`mod6`,`mod7`,`mod8`,`mod9`,`mod10`,`mod11`,`mod12`,`mod13`,`mod14`,`mod15`,`mod16`,`mod17`) VALUES (%i,'-',1,'1000','40',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)",gang);
		mysql_query(query);
		SendInfoMessage(playerid,"Nupirkai gaujos automobili!");	
		format(query,sizeof(query),"SELECT * From `gangcars` WHERE `gang`=%i",playerDB[playerid][pgang]);
		mysql_function_query(SQL, query, true, "SQL_LoadGaujosVadui", "ii", playerid,playerDB[playerid][pgang]);
		return 1;
	}
	new status,temp[30]; 
	cache_get_row(0,3,temp); status=strval(temp);
	new id;
	cache_get_row(0,0,temp); id=strval(temp);
	if(!status)
	{
		if(GetPlayerMoneyA(playerid) < COST_DCGANG)
			return SendInfoMessage(playerid,"Truksta pinigu remontui! Reikia "#COST_DCGANG"EUR");
		GivePlayerMoneyA(playerid,-COST_DCGANG);
		new query[256];
		format(query,sizeof(query),"UPDATE `gangcars` SET `status`=1,`health`='1000', `gas`='40' WHERE `id`=%i",id);
		mysql_query(query);
		SendInfoMessage(playerid,"Sutaisei masina!");
		format(query,sizeof(query),"SELECT * From `gangcars` WHERE `gang`=%i",playerDB[playerid][pgang]);
		mysql_function_query(SQL, query, true, "SQL_LoadGaujosVadui", "ii", playerid,playerDB[playerid][pgang]);

	}
	else SendInfoMessage(playerid," Masinai remonto nereikia!");
	return 1;
}
forward SQL_LoadGaujos(playerid,gang);
public SQL_LoadGaujos(playerid,gang)
{
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
	if(!rows) return SendInfoMessage(playerid,"~r~Gaujos vadas nenupirko automobiliu!");
	new msg[1024];
	new lolas;
	new lastuseris[24],status,Float:health,Float:gasas,temp[30]; 
	while(lolas < rows)
	{
		cache_get_row(lolas,2,lastuseris);
		cache_get_row(lolas,3,temp); status=strval(temp);
		cache_get_row(lolas,4,temp); health=floatstr(temp);
		cache_get_row(lolas,5,temp); gasas=floatstr(temp);
		if(!status) format(msg,sizeof(msg),"%s{FF0000}%i.Paskutinis naudojo %s(%iHP/%iL)\n",msg,lolas+1,lastuseris,floatround(health),floatround(gasas));
		else if(status==2) format(msg,sizeof(msg),"%s{FFFFFF}%i.Dabar naudojasi %s(%iHP/%iL)\n",msg,lolas+1,lastuseris,floatround(health),floatround(gasas));
		else if(status==1) format(msg,sizeof(msg),"%s{00FF00}%i.Paskutinis naudojo %s(%iHP/%iL)\n",msg,lolas+1,lastuseris,floatround(health),floatround(gasas));
		//format(dialogtext,3048,"%s%i. %s %s(%s) [%s]\n",dialogtext,x,Nameas,Veiksmas,Variable,Data);
		lolas++;
	}
	if(lolas) ShowPlayerDialog(playerid,7800,DIALOG_STYLE_LIST,"Gaujos automobiliai",msg,"Gerai","Atsaukti");
	return 1;
}

forward SQL_LoadGCar(playerid,gang);
public SQL_LoadGCar(playerid,gang)
{
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
	if(!rows) return SendInfoMessage(playerid,"~r~Klaida!");
	new temp[30];
	new status;
	cache_get_row(0,3,temp); status=strval(temp);
	if(!status) return SendInfoMessage(playerid,"Sis automobilis susprogdintas!");
	else if(status==2) return SendInfoMessage(playerid,"Sis automobilis jau naudojamas!");
	else
	{
		cache_get_row(0,0,temp); 
		new id=strval(temp);
		new mods[17];
		for(new i;i<17;i++)
		{
			cache_get_row(0,6+i,temp); mods[i]=strval(temp);
		}
		new Float:health,Float:gasas;
		cache_get_row(0,4,temp); health=floatstr(temp);
		cache_get_row(0,5,temp); gasas=floatstr(temp);
		DestroyOldCar(playerid);
		new query[256];
		format(query,sizeof(query),"UPDATE `gangcars` set `status`=2,`lastuser`='%s' WHERE `id`=%i",ReturnName(playerid),id);
		mysql_query(query);
		new job=100+gang;
		new car=0;
		PlayerLastJob[playerid][0]=job;
		PlayerLastJob[playerid][1]=car; //={job,car};
		_PlayerTeleporting[playerid]=6;
		PlayerCar[playerid] = CreateVehicle(DarbinesCar[job][car][DCmodel],0.0,0.0,0.0,DarbinesCar[job][car][DCR],DarbinesCar[job][car][DCcolor1],DarbinesCar[job][car][DCcolor2],-1,DarbinesCar[job][car][DCsirens]);
		OnVehicleSpawn(PlayerCar[playerid]);
		SetVehicleToRespawn(PlayerCar[playerid]);
		vehicleDB[PlayerCar[playerid]][gas]=40.0;
		if(health > 250.0)
		{
			SetTimerEx("SetCarHp",1000,false,"iff",PlayerCar[playerid],health,gasas);
		}
		for(new i;i<17;i++)
		{
			if(mods[i])
				AddVehicleComponent(PlayerCar[playerid],mods[i]);
		}
		vehicleDB[PlayerCar[playerid]][energy]=50.0;
		vehicleDB[PlayerCar[playerid]][OldHP]=1000.0;
		cache_get_row(0,23,temp); 
		vehicleDB[PlayerCar[playerid]][rida] = floatstr(temp);

		FadeColorForPlayer(playerid,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,10,5);
		TogglePlayerControllable(playerid,false);
		Stop(playerid);
		SendClientMessage(playerid,GREEN," * Gavote gaujos automobili. Susprogdinus ji teks moketi "#COST_DCGANG"€");
	}
	return 1;
}
forward SQL_LoadDarbineDelay(playerid,job,car);
public SQL_LoadDarbineDelay(playerid,job,car)
{
	new query[127];
	format(query,sizeof(query),"SELECT * From `Darbines` WHERE `Vardas`='%s' AND `Job`=%i AND `Cartype`=%i LIMIT 1",ReturnName(playerid),job,car);
	mysql_function_query(SQL, query, true, "SQL_LoadDarbine", "iii", playerid,job,car);
}
forward SQL_LoadDarbine(playerid,job,car);
public SQL_LoadDarbine(playerid,job,car)
{
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
	new temp[20];
	if(!rows)
	{
		DestroyOldCar(playerid);
		new query[256];
		format(query,sizeof(query),"INSERT INTO `Darbines` (`Vardas`,`Job`,`Cartype`,`Status`,`Health`,`Degalai`) VALUES ('%s','%i','%i',1,'1000.0','40.0')",ReturnName(playerid),job,car);
		mysql_query(query);
		PlayerLastJob[playerid][0]=job;
		PlayerLastJob[playerid][1]=car; //={job,car};
		_PlayerTeleporting[playerid]=6;
		PlayerCar[playerid] = CreateVehicle(DarbinesCar[job][car][DCmodel],0.0,0.0,0.0,DarbinesCar[job][car][DCR],DarbinesCar[job][car][DCcolor1],DarbinesCar[job][car][DCcolor2],-1,DarbinesCar[job][car][DCsirens]);
		OnVehicleSpawn(PlayerCar[playerid]);
		SetVehicleToRespawn(PlayerCar[playerid]);
		if(DarbinesCar[job][car][DCmodel] == 477) // zr-350
		{
			CarLights[playerid] = CreateObject(19309,0.0, 0.0, 0.0, 0.0, 0.0, 96.0);
			AttachObjectToVehicle(CarLights[playerid], PlayerCar[playerid], -0.019999, -0.274999, 0.811999, 0.000000, 0.000000, 91.454948); //Object Model: 19309 | 
		}
		vehicleDB[PlayerCar[playerid]][gas]=40.0;
		vehicleDB[PlayerCar[playerid]][energy]=50.0;
		vehicleDB[PlayerCar[playerid]][OldHP]=1000.0;
		vehicleDB[PlayerCar[playerid]][rida]=0.0;
		FadeColorForPlayer(playerid,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,10,5);
		TogglePlayerControllable(playerid,false);
		Stop(playerid);
		SendClientMessage(playerid,GREEN," * Gavote darbiná automobilá. Susprogdinto darbinio automobilio taisymas kainuos "#COST_DCMINI"-"#COST_DCSUPAKV"€.");
		return 1;
	
	}
	else
	{
		new status;
		cache_get_row(0,4,temp);
		status = strval(temp);
		if(status)
		{
			PlayerLastJob[playerid][0]=job;
			PlayerLastJob[playerid][1]=car; //={job,car};
			cache_get_row(0,5,temp);
			new Float:vhp,Float:gasas;
			vhp=floatstr(temp);
			cache_get_row(0,6,temp);
			gasas=floatstr(temp);
			if(PlayerCar[playerid] != -1)
			{
				if(GetVehicleModel(PlayerCar[playerid]) == DarbinesCar[job][car][DCmodel])
				{
					if(vehicleDB[PlayerCar[playerid]][dega])
					{
						SendInfoMessage(playerid,"Jusu masina dega!");
						return 1;
					}
					GetVehicleHealth(PlayerCar[playerid],vhp);
					gasas=vehicleDB[PlayerCar[playerid]][gas];
				}
			}
			new Float:oldrida = 0.0;
			if(PlayerCar[playerid] != -1 && GetVehicleModel(PlayerCar[playerid]) == DarbinesCar[job][car][DCmodel])
				oldrida = vehicleDB[PlayerCar[playerid]][rida];
			DestroyOldCar(playerid);

			_PlayerTeleporting[playerid]=6;
			PlayerCar[playerid] = CreateVehicle(DarbinesCar[job][car][DCmodel],0.0,0.0,0.0,DarbinesCar[job][car][DCR],DarbinesCar[job][car][DCcolor1],DarbinesCar[job][car][DCcolor2],-1,DarbinesCar[job][car][DCsirens]);
			OnVehicleSpawn(PlayerCar[playerid]);
			SetVehicleToRespawn(PlayerCar[playerid]);
			if(DarbinesCar[job][car][DCmodel] == 477) // zr-350
			{
				CarLights[playerid] = CreateObject(19309,0.0, 0.0, 0.0, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(CarLights[playerid], PlayerCar[playerid], -0.019999, -0.274999, 0.811999, 0.000000, 0.000000, 91.454948); //Object Model: 19309 | 
			}
			new mods[17];
			for(new i;i<17;i++)
			{
				cache_get_row(0,7+i,temp); mods[i]=strval(temp);
				if(mods[i] != 0) AddVehicleComponent(PlayerCar[playerid],mods[i]);
			}
			cache_get_row(0,24,temp); 
			if(oldrida > 0.0)
				vehicleDB[PlayerCar[playerid]][rida] = oldrida;
			else
				vehicleDB[PlayerCar[playerid]][rida] = floatstr(temp);
			new color1, color2, paintjob;
			cache_get_row(0,25, temp), color1 = strval(temp);
			cache_get_row(0,26, temp), color2 = strval(temp);
			cache_get_row(0,27, temp), paintjob = strval(temp);
			if(color1 != -1 || color2 != -1)
			{
				ChangeVehicleColor(PlayerCar[playerid], color1, color2);
			}
			if(paintjob != -1)
			{
				ChangeVehiclePaintjob(PlayerCar[playerid], paintjob);
			}
			FadeColorForPlayer(playerid,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,10,5);
			TogglePlayerControllable(playerid,false);
			Stop(playerid);
			if(vhp > 250.0)
			{
				SetTimerEx("SetCarHp",1000,false,"iff",PlayerCar[playerid],vhp,gasas);
				
			}
		}
		else
		{
			
			PlayerLastJob[playerid][0]=job;
			PlayerLastJob[playerid][1]=car;
			new msg[128];
			new cost;
			switch(job)
			{
				case 90..99:
				{
					cost=COST_DCMINI;
				}
				case 2,3,6,20,31,32,34,39,41,44,50,58,66,70,71,73,80,81,82,83,84: // su pakv
				{
					cost=COST_DCSUPAKV;
				
				}
				default:
				{
					cost=COST_DCBEPAKV;
				
				}
			}
			if(job == 36) cost=0;
			format(msg,sizeof(msg),"Remontuoti darbini automobili(%i€)\nRemontuoti ir nuimti tune(%i€)",cost,cost);
			ShowPlayerDialog(playerid,5601,DIALOG_STYLE_LIST,"Darbinis automobilis",msg,"Gerai","Atsaukti");
		}
		return 1;
	}

	//ShowPlayerDialog(playerid,5600,DIALOG_STYLE_LIST,"Darbinis automobilis","Gauti automobili(admin)","Gerai","Atsaukti");

}

forward SQL_LoadDarbineCar(playerid,job,car);
public SQL_LoadDarbineCar(playerid,job,car)
{
	new veh = GetPlayerVehicleID(playerid);
	if(!JobCars[veh][0]) return RemovePlayerFromVehicle(playerid);
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
	new temp[20];
	if(!rows)
	{
		DestroyOldCar(playerid);
		new query[256];
		format(query,sizeof(query),"INSERT INTO `Darbines` (`Vardas`,`Job`,`Cartype`,`Status`,`Health`,`Degalai`) VALUES ('%s','%i','%i',1,'1000.0','40.0')",ReturnName(playerid),job,car);
		mysql_query(query);
		PlayerCar[playerid] = veh;
		OnVehicleSpawn(veh);
		vehicleDB[veh][uzeris]=playerid;
		JobCars[veh][0] = 0;
		strcpy(vehicleDB[veh][lastuser],ReturnName(playerid),MAX_PLAYER_NAME);
		DarbinesCar[job][car][DCrespawn]=1;
		vehicleDB[veh][rida] = 0;
		if(DarbinesCar[job][car][DCmodel] == 477) // zr-350
		{
			CarLights[playerid] = CreateObject(19309,0.0, 0.0, 0.0, 0.0, 0.0, 96.0);
			AttachObjectToVehicle(CarLights[playerid], PlayerCar[playerid], -0.019999, -0.274999, 0.811999, 0.000000, 0.000000, 91.454948); //Object Model: 19309 | 
		}
		TogglePlayerControllable(playerid,true);
		if(!IsAPBike(veh)) SetVehicleParamsEx(veh,false,VehVars[1],VehVars[2],-1,VehVars[4],VehVars[5],VehVars[6]);
		else
			SetVehicleParamsEx(veh,true,VehVars[1],VehVars[2],-1,VehVars[4],VehVars[5],VehVars[6]);
		SendClientMessage(playerid,GREEN," * Gavote darbiná automobilá. Susprogdinto darbinio automobilio taisymas kainuos "#COST_DCMINI"-"#COST_DCSUPAKV"€.");
		return 1;
	}
	else
	{
		new status;
		cache_get_row(0,4,temp);
		status = strval(temp);
		if(status)
		{
			cache_get_row(0,5,temp);
			new Float:vhp,Float:gasas;
			vhp=floatstr(temp);
			cache_get_row(0,6,temp);
			gasas=floatstr(temp);
			if(PlayerCar[playerid] != -1)
			{
				if(GetVehicleModel(PlayerCar[playerid]) == DarbinesCar[job][car][DCmodel])
				{
					if(vehicleDB[PlayerCar[playerid]][dega])
					{
						SendInfoMessage(playerid,"Jusu masina dega!");
						return RemovePlayerFromVehicle(playerid);
					}
					GetVehicleHealth(PlayerCar[playerid],vhp);
					gasas=vehicleDB[PlayerCar[playerid]][gas];
				}
			}
			new Float:oldrida = 0.0;
			if(PlayerCar[playerid] != -1 && GetVehicleModel(PlayerCar[playerid]) == DarbinesCar[job][car][DCmodel])
				oldrida = vehicleDB[PlayerCar[playerid]][rida];
			DestroyOldCar(playerid);
			PlayerCar[playerid] = veh;
			OnVehicleSpawn(veh);
			vehicleDB[veh][uzeris]=playerid;
			TogglePlayerControllable(playerid,true);
			JobCars[veh][0] = 0;
			strcpy(vehicleDB[veh][lastuser],ReturnName(playerid),MAX_PLAYER_NAME);
			DarbinesCar[job][car][DCrespawn] = 1;
			if(DarbinesCar[job][car][DCmodel] == 477) // zr-350
			{
				CarLights[playerid] = CreateObject(19309,0.0, 0.0, 0.0, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(CarLights[playerid], PlayerCar[playerid], -0.019999, -0.274999, 0.811999, 0.000000, 0.000000, 91.454948); //Object Model: 19309 | 
			}
			new mods[17];
			new tunebonus = 0;
			new isabike = IsABike(PlayerCar[playerid]);
			for(new i;i<17;i++)
			{
				cache_get_row(0,7+i,temp); mods[i]=strval(temp);
				if(mods[i] != 0) 
				{
					AddVehicleComponent(PlayerCar[playerid],mods[i]);
					if(!isabike)
						tunebonus++;
				}
			}
			cache_get_row(0,24,temp); 
			if(oldrida > 0.0)
				vehicleDB[veh][rida] = oldrida;
			else
				vehicleDB[veh][rida] = floatstr(temp);
			new color1, color2, paintjob;
			cache_get_row(0,25, temp), color1 = strval(temp);
			cache_get_row(0,26, temp), color2 = strval(temp);
			cache_get_row(0,27, temp), paintjob = strval(temp);
			if(color1 != -1 || color2 != -1)
			{
				ChangeVehicleColor(PlayerCar[playerid], color1, color2);
				tunebonus++;
			}
			if(paintjob != -1)
			{
				ChangeVehiclePaintjob(PlayerCar[playerid], paintjob);
				if(!isabike)
					tunebonus++;
			}
			SetPlayerTuneBonus(playerid, tunebonus);
			GetVehicleParamsEx(veh,VehVars[0],VehVars[1],VehVars[2],VehVars[3],VehVars[4],VehVars[5],VehVars[6]);
			if(!IsAPBike(veh)) SetVehicleParamsEx(veh,false,VehVars[1],VehVars[2],-1,VehVars[4],VehVars[5],VehVars[6]);
			else
				SetVehicleParamsEx(veh,true,VehVars[1],VehVars[2],-1,VehVars[4],VehVars[5],VehVars[6]);
			if(vhp > 250.0)
			{
				SetTimerEx("SetCarHp",200,false,"iff",PlayerCar[playerid],vhp,gasas);
			}
		}
		else
		{
			RemovePlayerFromVehicle(playerid);
			PlayerLastJob[playerid][0]=job;
			PlayerLastJob[playerid][1]=car;
			new msg[128];
			new cost;
			switch(job)
			{
				case 90..99:
				{
					cost=COST_DCMINI;
				}
				case 2,3,6,20,31,32,34,39,41,44,50,58,66,70,71,73,80,81,82,83,84: // su pakv
				{
					cost=COST_DCSUPAKV;
				
				}
				default:
				{
					cost=COST_DCBEPAKV;
				
				}
			}
			if(job == 36) cost=0;
			format(msg,sizeof(msg),"Remontuoti darbini automobili(%i€)\nRemontuoti ir nuimti tune(%i€)",cost,cost);
			ShowPlayerDialog(playerid,5602,DIALOG_STYLE_LIST,"Darbinis automobilis",msg,"Gerai","Atsaukti");
		}
	
	}
	return 1;

}
/*
forward SQL_LoadDarbineUpgrade(playerid,job,car,veh);
public SQL_LoadDarbineUpgrade(playerid,job,car,veh)
{
	if(GetPlayerVehicleID(playerid) != veh) return 0;
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
	new temp[20];
	if(!rows)
	{
		DestroyOldCar(playerid);
		new query[256];
		format(query,sizeof(query),"INSERT INTO `Darbines` (`Vardas`,`Job`,`Cartype`,`Status`,`Health`,`Degalai`) VALUES ('%s','%i','%i',1,'1000.0','40.0')",ReturnName(playerid),job,car);
		mysql_query(query);
		PlayerLastJob[playerid][0]=job;
		PlayerLastJob[playerid][1]=car; //={job,car};
		_PlayerTeleporting[playerid]=8;
		PlayerCar[playerid] = veh;
		if(DarbinesCar[job][car][DCmodel] == 477) // zr-350
		{
			CarLights[playerid] = CreateObject(19309,0.0, 0.0, 0.0, 0.0, 0.0, 96.0);
			AttachObjectToVehicle(CarLights[playerid], PlayerCar[playerid], -0.019999, -0.274999, 0.811999, 0.000000, 0.000000, 91.454948); //Object Model: 19309 | 
		}

		FadeColorForPlayer(playerid,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,10,5);
		TogglePlayerControllable(playerid,false);
		SendClientMessage(playerid,GREEN," * Gavote darbini automobili. Susprogdinus ji teks moketi "#COST_DCMINI"-"#COST_DCSUPAKV"€");
		return 1;
	}
	else
	{
		new status;
		cache_get_row(0,4,temp);
		status = strval(temp);
		if(status)
		{
			PlayerLastJob[playerid][0]=job;
			PlayerLastJob[playerid][1]=car; //={job,car};
			cache_get_row(0,5,temp);
			new Float:vhp,Float:gasas;
			vhp=floatstr(temp);
			cache_get_row(0,6,temp);
			gasas=floatstr(temp);
			if(PlayerCar[playerid] != -1)
			{
				if(GetVehicleModel(PlayerCar[playerid]) == DarbinesCar[job][car][DCmodel])
				{
					if(vehicleDB[PlayerCar[playerid]][dega])
					{
						SendInfoMessage(playerid,"Jusu masina dega!");
						return 1;
					}
					GetVehicleHealth(PlayerCar[playerid],vhp);
					gasas=vehicleDB[PlayerCar[playerid]][gas];
				}
			}
			DestroyOldCar(playerid);

			_PlayerTeleporting[playerid]=6;
			PlayerCar[playerid] = CreateVehicle(DarbinesCar[job][car][DCmodel],0.0,0.0,0.0,DarbinesCar[job][car][DCR],DarbinesCar[job][car][DCcolor1],DarbinesCar[job][car][DCcolor2],-1,DarbinesCar[job][car][DCsirens]);
			OnVehicleSpawn(PlayerCar[playerid]);
			SetVehicleToRespawn(PlayerCar[playerid]);
			if(DarbinesCar[job][car][DCmodel] == 477) // zr-350
			{
				CarLights[playerid] = CreateObject(19309,0.0, 0.0, 0.0, 0.0, 0.0, 96.0);
				AttachObjectToVehicle(CarLights[playerid], PlayerCar[playerid], -0.019999, -0.274999, 0.811999, 0.000000, 0.000000, 91.454948); //Object Model: 19309 | 
			}
			new mods[17];
			for(new i;i<17;i++)
			{
				cache_get_row(0,7+i,temp); mods[i]=strval(temp);
				if(mods[i] != 0) AddVehicleComponent(PlayerCar[playerid],mods[i]);
			}
			FadeColorForPlayer(playerid,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,10,5);
			TogglePlayerControllable(playerid,false);
			Stop(playerid);
			if(vhp > 250.0)
			{
				SetTimerEx("SetCarHp",1000,false,"iff",PlayerCar[playerid],vhp,gasas);
				
			}
		}
		else
		{
			
			PlayerLastJob[playerid][0]=job;
			PlayerLastJob[playerid][1]=car;
			new msg[128];
			new cost;
			switch(job)
			{
				case 90..99:
				{
					cost=COST_DCMINI;
				}
				case 2,3,6,20,31,32,34,39,41,44,50,58,66,70,71,73,80,81,82,83,84: // su pakv
				{
					cost=COST_DCSUPAKV;
				
				}
				default:
				{
					cost=COST_DCBEPAKV;
				
				}
			}
			if(job == 36) cost=0;
			format(msg,sizeof(msg),"Remontuoti darbini automobili(%i€)",cost);
			ShowPlayerDialog(playerid,5601,DIALOG_STYLE_LIST,"Darbinis automobilis",msg,"Gerai","Atsaukti");
		}
		return 1;
	}

	//ShowPlayerDialog(playerid,5600,DIALOG_STYLE_LIST,"Darbinis automobilis","Gauti automobili(admin)","Gerai","Atsaukti");

}
*/

forward SQL_LimitSandeliai(playerid,sandelis,kiek);
public SQL_LimitSandeliai(playerid,sandelis,kiek)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);

	if(sandelis < 0 || sandelis >= 3)
		return 1;

	new gang = playerDB[playerid][pgang];

	if(gang == -1 || PlaceOwnedBy[sandelis] != gang)
		return 1;

	new limit = FamilyInfo[gang][SandelioLimitai][sandelis];

	if(strcmp(FamilyInfo[gang][FamilyLeader],ReturnName(playerid),true) == 0 || strcmp(FamilyInfo[gang][FamilySubstitute],ReturnName(playerid),true) == 0)
		limit = 999999;

	new taken = 0;
	if(rows > 0)
	{
		new temp[20];
		cache_get_row(0,0,temp), taken = strval(temp);
	}

	if(KiekYra[sandelis] < kiek)
	{
		return SendInfoMessage(playerid,"Tiek sandelyje neturime!");
	}

	if(taken + kiek > limit)
	{
		new msg[128];
		format(msg,sizeof(msg),"Tiek paimti negali.~n~Siandien tu jau paemei ~r~%i ~w~is ~r~%i~w~ dienos limito.",taken,limit);
		return SendInfoMessage(playerid,msg);
	}
	
	new const costs[] = {COST_SEKLOS,COST_LSD,COST_RATAI};



	if(GetPlayerMoneyA(playerid) < kiek*costs[sandelis]) return SendInfoMessage(playerid,"~r~Truksta pinigu!");

	KiekYra[sandelis]-=kiek;
	GivePlayerMoneyA(playerid,-kiek*costs[sandelis]);
	ProcessAchievement(playerid, 127, kiek);
	if(kiek)
	{
		if(sandelis == 0)
		{
			MLog(playerid,"Nusipirko Seklu","i", kiek);
			playerDB[playerid][seklos]+=kiek;
		}
		else if(sandelis == 1)
		{
			MLog(playerid,"Nusipirko LSD","i", kiek);
			playerDB[playerid][lsd]+=kiek;
		}
		else if(sandelis == 2)
		{
			MLog(playerid,"Nusipirko Ratu","i", kiek);
			playerDB[playerid][ratai]+=kiek;
		}
	}
	
	SendInfoMessage(playerid,"Narkotikai nupirkti!");
	
	return 1;
}
forward SQL_LimitAmfa(playerid,inputtext[],kaina);
public SQL_LimitAmfa(playerid,inputtext[],kaina)
{
	RestartCheck();
	new kiek = strval(inputtext);
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows == 0 || playerDB[playerid][plead] == 90)
	{
		GivePlayerMoneyA(playerid,-kaina);
		playerDB[playerid][amfetaminas]+=kiek;
		Pelnas(playerid,89,floatround(kaina/3));
		SendInfoMessage(playerid,"Geros dienos!");
		MLog(playerid,"Paeme Amfetamina","i", kiek);
		Server[atveztan]-=kiek;
	}
	else
	{	
		new Countas;
		new temp[20];
		cache_get_row(0,0,temp), Countas = strval(temp);
		if(Countas+kiek > LIMIT_AMFA) // && playerDB[playerid][plead] != 90)
		{
			new msg[128];
			format(msg,sizeof(msg)," * Tiek paimti negali. Ðiandien dar gali paimti %i pakeliø.",LIMIT_AMFA-Countas);
			SendClientMessage(playerid, -1, msg);
			return SendInfoMessage(playerid,"~r~Tiek paimti negali. Amfetamino limitas per diena - "#LIMIT_AMFA"pak.");
		}
		else
		{
			GivePlayerMoneyA(playerid,-kaina);
			Pelnas(playerid,89,floatround(kaina/3));
			playerDB[playerid][amfetaminas]+=kiek;
			SendInfoMessage(playerid,"Geros dienos!");
			MLog(playerid,"Paeme Amfetamina","i", kiek);
			Server[atveztan]-=kiek;
		}
	}
	return 1;
}
forward SQL_LimitDeagle(playerid,inputtext[],kaina);
public SQL_LimitDeagle(playerid,inputtext[],kaina)
{
	RestartCheck();
	new kiek = strval(inputtext);
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows == 0 || playerDB[playerid][plead] == 90)
	{
		GivePlayerMoneyA(playerid,-kaina);
		GivePlayerWeaponEx(playerid,24,7*kiek);
		ProcessAchievement(playerid,36,7*kiek);
		Pelnas(playerid,89, floatround(strval(inputtext)*100/2));
		Server[adgl]-=kiek;
		SendInfoMessage(playerid,"Geros dienos!");
		MLog(playerid,"Paeme Deagle","i", kiek);
		ShowPlayerDialog(playerid, 9002, DIALOG_STYLE_LIST, "Ginklai", "Desert eagle\nMp5\nAk47\nAWP", "Rinktis", "Iseiti");
	}
	else
	{	
		new Countas;
		new temp[20];
		cache_get_row(0,0,temp), Countas = strval(temp);
		if(Countas+kiek > LIMIT_DEAGLE) // && playerDB[playerid][plead] != 90)
		{
			new msg[128];
			format(msg,sizeof(msg)," * Tiek paimti negali. Ðiandien dar gali paimti %i apkabø.",LIMIT_DEAGLE-Countas);
			SendClientMessage(playerid, -1, msg);
			return SendInfoMessage(playerid,"~r~Tiek paimti negali. Deagle limitas per diena - "#LIMIT_DEAGLE"apk.");
		}
		else
		{
			GivePlayerMoneyA(playerid,-kaina);
			GivePlayerWeaponEx(playerid,24,7*kiek);
			ProcessAchievement(playerid,36,7*kiek);
			Pelnas(playerid,89, floatround(strval(inputtext)*100/2));
			Server[adgl]-=kiek;
			SendInfoMessage(playerid,"Geros dienos!");
			MLog(playerid,"Paeme Deagle","i",kiek);
			ShowPlayerDialog(playerid, 9002, DIALOG_STYLE_LIST, "Ginklai", "Desert eagle\nMp5\nAk47\nAWP", "Rinktis", "Iseiti");
		}
	}
	return 1;
}

forward SQL_LimitGangMoney(playerid,kiek);
public SQL_LimitGangMoney(playerid,kiek)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(playerDB[playerid][pgang] == -1 || kiek > FamilyInfo[playerDB[playerid][pgang]][FamilyLimit])
		return SendClientMessage(playerid, -1, " * Tiek paimti negali!");

	if(rows > 0)
	{
		new Countas;
		new temp[20];
		cache_get_row(0,0,temp), Countas = strval(temp);
		if(Countas + kiek > FamilyInfo[playerDB[playerid][pgang]][FamilyLimit])
		{
			new msg[128];
			format(msg,sizeof(msg)," * Tiek paimti negali. Ðiandien jau paemei %i/%i €.",Countas,FamilyInfo[playerDB[playerid][pgang]][FamilyLimit]);
			SendClientMessage(playerid, -1, msg);
			return 1;
		}
	}

	GivePlayerMoneyA(playerid,kiek);
	FamilyInfo[playerDB[playerid][pgang]][FamilyFunds]-=kiek;
	new msg1[50];
	format(msg1,sizeof(msg1),"Paeme is fondo(%i)",playerDB[playerid][pgang]);
	MLog(playerid,msg1,"i", kiek);
	SendInfoMessage(playerid,"Sekmingai paemei pinigus is gaujos fondo!");
	SaveFamily(playerDB[playerid][pgang]);

	return 1;
}

forward SQL_LimitSaugykla(playerid, idas, kiek);
public SQL_LimitSaugykla(playerid, idas, kiek)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);

	if(!IsPlayerConnected(playerid))
		return 1;

	new gang = playerDB[playerid][pgang];
	if(gang == -1 || idas < 0 || idas > 9)
		return 1;
	new limit = FamilyInfo[gang][SaugyklosLimitai][idas];

	if(strcmp(FamilyInfo[gang][FamilyLeader],ReturnName(playerid),true) == 0 || strcmp(FamilyInfo[gang][FamilySubstitute],ReturnName(playerid),true) == 0)
		limit = 999999;

	new taken = 0;
	if(rows > 0)
	{
		new temp[20];
		cache_get_row(0,0,temp), taken = strval(temp);
	}


	if(FamilyInfo[gang][FamilySaugykla][idas] < kiek)
	{
		SendInfoMessage(playerid,"Tiek saugykloje neturime!");
		return ShowGangNarioDialog(playerid, 1);
	}



	if(taken + kiek > limit)
	{
		new msg[128];
		format(msg,sizeof(msg),"Tiek paimti negali.~n~Siandien tu jau paemei ~r~%i ~w~is ~r~%i~w~ dienos limito.",taken,limit);
		SendInfoMessage(playerid,msg);
		return ShowGangNarioDialog(playerid, 1);
	}

	new const names[][] =
	{
		"LSD",
		"Ratu",
		"Seklu",
		"Zoles",
		"Amfetamino",
		"Deagle",
		"Sniper Rifle",
		"Combat Shotgun",
		"AK-47",
		"MP5"
	};
	switch(idas)
	{
		case 0:
		{
			playerDB[playerid][lsd] += kiek;
		}
		case 1:
		{
			playerDB[playerid][ratai] += kiek;
		}
		case 2:
		{
			playerDB[playerid][seklos] += kiek;
		}
		case 3:
		{
			playerDB[playerid][zole] += kiek;
		}
		case 4:
		{
			playerDB[playerid][amfetaminas] += kiek;
		}
		case 5,6,7,8,9:
		{
			new const gunai[] = {24,34,27,30,29};
			new weap = gunai[idas-5];

			new
				slot = GetWeaponsSlot(weap),
				weaponidas, kiekturi;
			
			GetPlayerWeaponData(playerid,slot,weaponidas,kiekturi);
			if(weaponidas != weap)
				kiekturi = 0;
			
			if(kiekturi + kiek >= 10000)
			{
				return SendInfoMessage(playerid,"~r~Negali paimti daugiau nei 10.000 kulku!");
			}

			GivePlayerWeaponEx(playerid,weap,kiek);
		}
		default:
		{
			return SendInfoMessage(playerid,"~r~Ivyko klaida!");
		}
	}
	FamilyInfo[gang][FamilySaugykla][idas] -= kiek;
	new msg1[50];
	format(msg1,sizeof(msg1),"Paeme is saugyklos(%s)",names[idas]);
	MLog(playerid,msg1,"i", kiek);
	ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
	SendInfoMessage(playerid,"~g~Paemei daiktus is saugyklos!");

	SaveFamily(gang);
	SavePlayerData(playerid,true);

	ShowGangNarioDialog(playerid,1);

	return 1;
}
forward SQL_LimitAK(playerid,inputtext[],kaina);
public SQL_LimitAK(playerid,inputtext[],kaina)
{
	RestartCheck();
	new kiek = strval(inputtext);
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows == 0 || playerDB[playerid][plead] == 90)
	{
		GivePlayerMoneyA(playerid,-kaina);
		GivePlayerWeaponEx(playerid,30,30*kiek);
		ProcessAchievement(playerid,36,30*kiek);
		Pelnas(playerid,89, floatround(strval(inputtext)*100/2));
		Server[aak]-=kiek;
		SendInfoMessage(playerid,"Geros dienos!");
		MLog(playerid,"Paeme AK-47","i", kiek);
		ShowPlayerDialog(playerid, 9002, DIALOG_STYLE_LIST, "Ginklai", "Desert eagle\nMp5\nAk47\nAWP", "Rinktis", "Iseiti");
	}
	else
	{	
		new Countas;
		new temp[20];
		cache_get_row(0,0,temp), Countas = strval(temp);
		if(Countas+kiek > LIMIT_AK47) // && playerDB[playerid][plead] != 90)
		{
			new msg[128];
			format(msg,sizeof(msg)," * Tiek paimti negali. Ðiandien dar gali paimti %i apkabø.",LIMIT_AK47-Countas);
			SendClientMessage(playerid, -1, msg);
			return SendInfoMessage(playerid,"~r~Tiek paimti negali. AK47 limitas per diena - "#LIMIT_AK47"apk.");
		}
		else
		{
			GivePlayerMoneyA(playerid,-kaina);
			GivePlayerWeaponEx(playerid,30,30*kiek);
			ProcessAchievement(playerid,36,30*kiek);
			Pelnas(playerid,89, floatround(strval(inputtext)*100/2));
			Server[aak]-=kiek;
			SendInfoMessage(playerid,"Geros dienos!");
			MLog(playerid,"Paeme AK-47","i", kiek);
			ShowPlayerDialog(playerid, 9002, DIALOG_STYLE_LIST, "Ginklai", "Desert eagle\nMp5\nAk47\nAWP", "Rinktis", "Iseiti");
		}
	}
	return 1;
}
forward SQL_LimitMP(playerid,inputtext[],kaina);
public SQL_LimitMP(playerid,inputtext[],kaina)
{
	RestartCheck();
	new kiek = strval(inputtext);
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows == 0 || playerDB[playerid][plead] == 90)
	{
		GivePlayerMoneyA(playerid,-kaina);
		GivePlayerWeaponEx(playerid,29,30*kiek);
		ProcessAchievement(playerid,36,30*kiek);
		Pelnas(playerid,89, floatround(strval(inputtext)*100/2));
		Server[amp]-=kiek;
		SendInfoMessage(playerid,"Geros dienos!");
		MLog(playerid,"Paeme MP5","i", kiek);
		ShowPlayerDialog(playerid, 9002, DIALOG_STYLE_LIST, "Ginklai", "Desert eagle\nMp5\nAk47\nAWP", "Rinktis", "Iseiti");
	}
	else
	{	
		new Countas;
		new temp[20];
		cache_get_row(0,0,temp), Countas = strval(temp);
		if(Countas+kiek > LIMIT_MP5) // && playerDB[playerid][plead] != 90)
		{
			new msg[128];
			format(msg,sizeof(msg)," * Tiek paimti negali. Ðiandien dar gali paimti %i apkabø.",LIMIT_MP5-Countas);
			SendClientMessage(playerid, -1, msg);
			return SendInfoMessage(playerid,"~r~Tiek paimti negali. MP5 limitas per diena - "#LIMIT_MP5"apk.");
		}
		else
		{
			GivePlayerMoneyA(playerid,-kaina);
			GivePlayerWeaponEx(playerid,29,30*kiek);
			ProcessAchievement(playerid,36,30*kiek);
			Pelnas(playerid,89, floatround(strval(inputtext)*100/2));
			Server[amp]-=kiek;
			SendInfoMessage(playerid,"Geros dienos!");
			MLog(playerid,"Paeme MP5","i", kiek);
			ShowPlayerDialog(playerid, 9002, DIALOG_STYLE_LIST, "Ginklai", "Desert eagle\nMp5\nAk47\nAWP", "Rinktis", "Iseiti");
		}
	}
	return 1;
}
forward SQL_LimitSniper(playerid,inputtext[],kaina);
public SQL_LimitSniper(playerid,inputtext[],kaina)
{
	RestartCheck();
	new kiek = strval(inputtext);
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows == 0 || playerDB[playerid][plead] == 90)
	{
		GivePlayerMoneyA(playerid,-kaina);
		GivePlayerWeaponEx(playerid,34,10*kiek);
		ProcessAchievement(playerid,36,10*kiek);
		Pelnas(playerid,89, floatround(strval(inputtext)*100/2));
		Server[aawp]-=kiek;
		SendInfoMessage(playerid,"Geros dienos!");
		MLog(playerid,"Paeme AWP","i", kiek);
		ShowPlayerDialog(playerid, 9002, DIALOG_STYLE_LIST, "Ginklai", "Desert eagle\nMp5\nAk47\nAWP", "Rinktis", "Iseiti");
	}
	else
	{	
		new Countas;
		new temp[20];
		cache_get_row(0,0,temp), Countas = strval(temp);
		if(Countas+kiek > LIMIT_AWP) //&& playerDB[playerid][plead] != 90)
		{
			new msg[128];
			format(msg,sizeof(msg)," * Tiek paimti negali. Ðiandien dar gali paimti %i apkabø.",LIMIT_AWP-Countas);
			SendClientMessage(playerid, -1, msg);
			return SendInfoMessage(playerid,"~r~Tiek paimti negali. Sniper limitas per diena - "#LIMIT_AWP"apk.");
		}
		else
		{
			GivePlayerMoneyA(playerid,-kaina);
			GivePlayerWeaponEx(playerid,34,10*kiek);
			ProcessAchievement(playerid,36,10*kiek);
			Pelnas(playerid,89, floatround(strval(inputtext)*100/2));
			Server[aawp]-=kiek;
			SendInfoMessage(playerid,"Geros dienos!");
			MLog(playerid,"Paeme AWP","i", kiek);
			ShowPlayerDialog(playerid, 9002, DIALOG_STYLE_LIST, "Ginklai", "Desert eagle\nMp5\nAk47\nAWP", "Rinktis", "Iseiti");
		}
	}
	return 1;
}

forward SQL_LoadAchMax();
public SQL_LoadAchMax()
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new x;
	if(rows > 135) rows=135; // LIMITAS
	while(x<rows)
	{
		new temp[40];
		cache_get_row(x,0, temp);
		RequiredAchPoints[x]=strval(temp);
		x++;
	}
}
forward SQL_LoadAchMax2();
public SQL_LoadAchMax2()
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new x;
	if(rows > 135) rows=135; // LIMITAS
	while(x<rows)
	{
		new temp[40];
		cache_get_row(x, 0, temp);
		new idas = strval(temp);
		cache_get_row(x, 1, temp);
		new countas = strval(temp);
		if(idas < 150)
		{
			AccountsWithAch[idas] = countas;
		}
		x++;
	}
}
forward SQL_LoadAchMax3();
public SQL_LoadAchMax3()
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows)
	{
		new temp[12];
		cache_get_row(0, 0, temp);
		TotalAccounts = strval(temp);
	}
}

forward SQL_GetAchName(playerid,id);
public SQL_GetAchName(playerid,id)
{
	RestartCheck();
	new achname[50];
	//new temp[20];//,amount;
	cache_get_row(0,0,achname);
//	cache_get_row(0,1,temp), amount=strval(temp);
	SetPlayerChatBubble(playerid,achname,TEXTCOL_GOLD,30,10000); // 10 sec.
	new msg[256];
	format(msg,sizeof(msg),"*** Pasiekimas atrakintas:{00FF00} %s{FFFFFF}. Atlygis : 50XP",achname);

	SendClientMessage(playerid,0xFFFFFFFF,msg);
	format(msg,sizeof(msg),"~g~%s",achname);
	GameTextForPlayer(playerid,msg,5000,5);
	SendClientMessage(playerid,0xFFFFFFFF,"*** Savo progresa gali sekti parases /pasiekimai");
	PlayerPlaySound(playerid,4201,0,0,0);
	SetPlayerScore(playerid,GetPlayerScore(playerid)+50);
	
}
forward SQL_DumpAchievements(playerid,forplayerid,page);
public SQL_DumpAchievements(playerid,forplayerid,page)
{
	SetPVarInt(playerid,"PageId", page);
	format(G_DialogList,sizeof(G_DialogList),"ID\tPasiekimas\tProgresas\n");
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new achieved;
	if(rows > 135) rows=135; // LIMITAS
	new x;
	new total = 0;
	if(page != 0)
	{
		x = 100 * page;
	}
	while(x<rows)
	{
		new Countas;
		new temp[40];
		new AchName[50];
		cache_get_row(x,1, AchName);
		cache_get_row(x,3, temp), Countas=strval(temp);
		new progress[48] = " ";
		if(Achievements[playerid][x] >= Countas) 
		{
			achieved++;
			if(Countas != 1)
			{
				format(progress,48,"{66CD00}%s",FormatNumber(Countas));
			}
			if(total < 100)
				format(G_DialogList,sizeof(G_DialogList),"%s{66CD00}%i\t{66CD00}%s\t%s\n",G_DialogList,x+1,AchName,progress);
		}
		else
		{
			if(Countas != 1)
			{
				format(progress,48,"{CFDBC5}%s / %s",FormatNumber(floatround(Achievements[playerid][x])),FormatNumber(Countas));
			}
			if(total < 100)
				format(G_DialogList,sizeof(G_DialogList),"%s{CFDBC5}%i\t{CFDBC5}%s\t%s\n",G_DialogList,x+1,AchName,progress);
		}
		x++;
		total ++;
	}
	if(total >= 100)
	{
		format(G_DialogList,sizeof(G_DialogList),"%sToliau...",G_DialogList);
	}
	new header[50];
	if(page == 0)
		format(header,sizeof(header),"Pasiekimai %i/%i (%.1f%%)",achieved,x, (achieved * 100.0) / x);
	else
		format(header,sizeof(header),"Pasiekimai");
	if(forplayerid==-1)
	{
		ShowPlayerDialog(playerid,6385,DIALOG_STYLE_TABLIST_HEADERS,header,G_DialogList,"Gerai","Atsaukti");
	}
	else
	{
		ShowPlayerDialog(forplayerid,6387,DIALOG_STYLE_TABLIST_HEADERS,header,G_DialogList,"Gerai","Atsaukti");
		SetPVarInt(forplayerid,"AchForPlayer",playerid);
	}

}

forward SQL_ShowAchInfo(playerid,id);
public SQL_ShowAchInfo(playerid,id)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	new temp[30],desc[200],achname[50],req,result[2048];
	cache_get_row(0,1,achname);
	cache_get_row(0,2,desc);
	cache_get_row(0,3,temp); req=strval(temp);
	new bool:status = (Achievements[playerid][id] >=req);
	new Float:accs = 0.0;
	if(TotalAccounts > 0)
		accs = (AccountsWithAch[id] * 100.0) / TotalAccounts;
	format(result,sizeof(result),"{e3c3c3}%s\n%s\n\n{A9C4E4}%s\n\nSurinkta: {e3c3c3}%s / %s\n{A9C4E4}Ðá pasiekimà turi {e3c3c3}%.3f%% {A9C4E4}þaidëjø.",achname,((status)?("{00FF00}Ávykdyta"):("{FF0000}Neávykdyta")),desc,FormatNumber(floatround(Achievements[playerid][id])),FormatNumber(req), accs);
	ShowPlayerDialog(playerid,6386,DIALOG_STYLE_MSGBOX,achname,result,"Atgal","");
}

forward SQL_CheckIsiAch(playerid);
public SQL_CheckIsiAch(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows >= 17) ProcessAchievement(playerid,53);
}
forward SQL_PutOnGift(playerid);
public SQL_PutOnGift(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows) return SendInfoMessage(playerid,"~r~Neturi dovanos :(");
	new temp[30];
	cache_get_row(0,0,temp);
	ApplyItem(playerid,strval(temp));
	SendInfoMessage(playerid,"~g~Uzsidejai~w~ dovana!"); 
	return 1;
}

forward SQL_LoadTraffic();
public SQL_LoadTraffic()
{
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
	
	new temp[36];
	new jau=0;
	new Float:Coo[4];
	new stringas[128];
	new type;
	while(jau < rows)
	{
		cache_get_row(jau, 0, temp), Coo[0] = floatstr(temp);
		cache_get_row(jau, 1, temp), Coo[1] = floatstr(temp);
		cache_get_row(jau, 2, temp), Coo[2] = floatstr(temp);
		cache_get_row(jau, 3, temp), Coo[3] = floatstr(temp);
		cache_get_row(jau, 4, stringas);
		cache_get_row(jau,5, temp), type = strval(temp);
		CreateTrafficSign(type,	Coo[0],Coo[1],Coo[2],Coo[3], 120.0, stringas);
		jau++;
	}
}

forward SQL_UnbanCost(playerid);
public SQL_UnbanCost(playerid)
{
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
	new cost = floatround(20*(floatpower(2,rows)));
	if(cost == 20)
	{
		MakePurchase(playerid, PURCHASE_UNBAN, 20);
	}
	else
	{
		new msg[256];
		format(msg,sizeof(msg),"Jus jau gavote %i ban per paskutines 7 dienas!\nKad palaikytumeme tvarka serveryje, jusu unban kaina pakeleme iki %i kreditu.\nAr norite pirkti unban?",(rows+1),cost);
		ShowPlayerDialog(playerid,1999,DIALOG_STYLE_MSGBOX,"Unban",msg,"Pirkti","Nepirkti");
		PlayerUnbanCost[playerid]=cost;
	
	}
	return 1;

}
forward SQL_CheckIfNumberIsUsed(playerid, newnumber[]);
public SQL_CheckIfNumberIsUsed(playerid, newnumber[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows)
	{
		SendClientMessage(playerid, COLOR_RED, " * Sis telefono numeris jau naudojamas!");
		KickEx(playerid);
	}
	else
	{
		SendSMSConfirmation2(playerid, newnumber);
	}
	return 1;
}
forward SQL_TryNumberConfirm(playerid);
public SQL_TryNumberConfirm(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows)
	{
		SendClientMessage(playerid, COLOR_RED, " * Siuo metu negalime patvirtinti jusu numerio, nes galime siusti tik viena SMS zinute kas valanda. Prasome pabandyti veliau.");
		KickEx(playerid);
	}
	else
	{
		ShowPlayerDialog(playerid,9989,DIALOG_STYLE_INPUT,"Iveskite telefono numeri","\
		{ffffff}Iveskite savo mob. telefono numeri, kad patvirtumete savo registracija.\n\n\
		Galimi formatai:\n\
		{f55d42}86*******\n\
		{f55d42}3706*******\n\
		{f55d42}+3706*******\n\
		\n\n\n\
		{ffffff}Jeigu neturite lietuvisko numerio, tuomet sukurkite tema musu forumo Pagalbos skiltyje ir jusu akaunta perziuresime rankiniu budu.","Gerai","Atsaukti");
	}
	return 1;
}
forward SQL_CheckNumberStatus(playerid,login);
public SQL_CheckNumberStatus(playerid,login)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	SetPVarInt(playerid, "loginvar", login);
	if(!rows)
	{
		TryNumberConfirm(playerid);
		return 1;
	}
	new temp[24];
	cache_get_row(0,3,temp);
	new conf=strval(temp);
	cache_get_row(0,4,temp);
	SetPVarInt(playerid, "ConfirmationCode", strval(temp));
	if(!conf)
	{
		ShowPlayerDialog(playerid,9990,DIALOG_STYLE_LIST,"Nepatvirtinas telefono numeris","Ivesti patvirtinimo koda\nSiusti koda is naujo","Gerai","Atsijungti");
		return 1;
	}
	else
	{
		LetPlayerSpawn(playerid, login);	
	}
	return 1;
	
	
}


forward SQL_CheckEmailS(playerid,login);
public SQL_CheckEmailS(playerid,login)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows)
	{
		ShowPlayerDialog(playerid,9889,DIALOG_STYLE_INPUT,"Iveskite el.pasto adresa","Iveskite el.pasto adresa, kuri norite susieti su siuo akauntu.\nPamirsus slaptazodi, naujas bus atsiustas siuo adresu.","Gerai","Atsaukti");
		return 1;
	}
	
	new emailas[100],confirmationas[10],temp[10],conf;
	cache_get_row(0,1,emailas);
	//SetPVarString(playerid,"EmailAddress",emailas);
	cache_get_row(0,2,confirmationas);
	cache_get_row(0,3,temp); conf=strval(temp);
	new domain[100];
	cache_get_row(0,6,domain);
	if(!conf)
	{
		ShowPlayerDialog(playerid,1997,DIALOG_STYLE_LIST,"Nepatvirtinas e-mail","Ivesti patvirtinimo koda\nSiusti koda is naujo\nPakeisti e-mail","Gerai","Atsijungti");
		return 1;
	
	}
	else
	{
		if(GetPVarInt(playerid,"PXP") >= 1000 || IsValidEmailDomain(domain) || !PHONE_CONFIRMATION_ENABLED)
		{
			LetPlayerSpawn(playerid, login);
		}
		else
		{
			CheckNumberStatus(playerid,login);
		}
		
	}
	return 1;
	
	
}
stock IsValidEmailDomain(domain[])
{
	return (strcmp(domain,"lsgyvenimas.lt",true)==0);
	/* ||
			strcmp(domain,"gmail.com",true)==0 || 
			strcmp(domain,"inbox.lt",true)==0 || 
			strcmp(domain,"yahoo.com",true)==0 || 
			strcmp(domain,"one.lt",true)==0);*/
}
forward SQL_ResendConfirmation(playerid);
public SQL_ResendConfirmation(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows)
	{
		ShowPlayerDialog(playerid,9889,DIALOG_STYLE_INPUT,"Iveskite el.pasto adresa","Iveskite el.pasto adresa, kuri norite susieti su siuo akauntu.\nPamirsus slaptazodi, naujas bus atsiustas siuo adresu.","Gerai","Atsaukti");
		return 1;
	}
	new emailas[50],confirmas[10];
	cache_get_row(0,0,emailas);
	cache_get_row(0,1,confirmas);
	SendEmailConfirmation(playerid,emailas,confirmas);
	return 1;
}
forward SQL_Confirmationas(playerid,code[]);
public SQL_Confirmationas(playerid,code[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(strlen(code) != 5) 
	{
		ShowPlayerDialog(playerid,1998,DIALOG_STYLE_INPUT,"Patvirtinimo kodas","Kodas yra sudarytas is 5 simboliu. Pasitikrinkite ar nenukopijavote tarpo.\nIveskite koda cia:","Gerai","Atsaukti");
		return 1;
	}
	else
	{
		new kodas[10];
		cache_get_row(0,0,kodas);
		if(strcmp(kodas,code,false)==0)
		{
			new query[128];
			format(query,128,"Update Pastas Set Confirmed=1, Confirmation=NULL WHERE Vardas='%s'",ReturnName(playerid));
			mysql_query(query);
			SendClientMessage(playerid,GREEN," * Sekmingai patvirtinote savo el.pasto adresa. Sekmes zaidime!");
			SendClientMessage(playerid,WHITE," * Savo apranga galite issirinkti rodyklemis apacioje. Kai issirinksite - spauskite \"Spawn\"");
			ShowPlayerDialog(playerid,1996,DIALOG_STYLE_MSGBOX,"Lietuviskos raides","Ar taisyklingai matote zemiau parasyta zodi?\n\n"#HCOLOR"Aèiû"#DCOLOR"\n\nJei pasirinksite taip - zaidime matysite lietuviskus simbolius.\nJei pasirinksite ne - zaidime lietuviskos raides bus konvertuojamos i ju atitikmeni (be nosiniu, varneliu ir t.t.)\nLietuviskas raides visada galite isijungti per VVP (/p) paspaude Nustatymai.","Taip","Ne");
			return 1;
		}
		else
		{
			ShowPlayerDialog(playerid,1998,DIALOG_STYLE_INPUT,"Patvirtinimo kodas","Neteisingas kodas!\nIveskite koda cia:","Gerai","Atsaukti");

		}
	}
	
	return 1;
}
forward SQL_SetAuthState(playerid);
public SQL_SetAuthState(playerid)
{
	RestartCheck();
	new temp[25],xp;
	cache_get_row(0,0,temp);
	xp=strval(temp);
	if(xp < 1) 
	{
		if(playerDB[playerid][authstate]!=4)
			playerDB[playerid][authstate]=1;
	}
	else
	{
		playerDB[playerid][vip]=false;
		if(playerDB[playerid][authstate]!=4)
			playerDB[playerid][authstate]=2; // Zaidejas prisijunges
		SendInfoMessage(playerid,"Jus sekmingai prisijungete! Linkime gero zaidimo ir geros nuotaikos!");
		SetSpawnInfo(playerid,GetPlayerTeam(playerid),GetPlayerSkin(playerid),1743.1915,-1944.5928,13.5661,0.0,0,0,0,0,0,0);
		SpawnPlayer(playerid);
		CancelSelectTextDraw(playerid); 
		TextDrawHideForPlayer(playerid,PassReminder);
		SetTimerEx("OnPlayerLogin",0,false,"i",playerid);
	}
}
forward SQL_IsEmailUsed(playerid,email[]);
public SQL_IsEmailUsed(playerid,email[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows)
		SendEmailConfirmation(playerid,email,"");
	else
	{
		ShowPlayerDialog(playerid,9889,DIALOG_STYLE_INPUT,"Iveskite el.pasto adresa","El. pasto adresas jau naudojamas.\nIveskite el.pasto adresa, kuri norite susieti su siuo akauntu.\nPamirsus slaptazodi, naujas bus atsiustas siuo adresu.","Gerai","Atsaukti");
	}
	return 1;
}
forward SQL_EmailNotification(playerid,newemail[]);
public SQL_EmailNotification(playerid,newemail[])
{
	RestartCheck();
	new temp[128];
	cache_get_row(0,0,temp);
	SendNotification(playerid,temp,newemail);

	new query[350];
	new newemailex[256];
	mysql_real_escape_string(newemail,newemailex,_,256);
	format(query,sizeof(query),"INSERT INTO Pastas (Vardas,Email) VALUES ('%s','%s') ON DUPLICATE KEY UPDATE NewEmail='%s', ChangeDate=NOW()",ReturnName(playerid),newemail,newemailex);
	mysql_query(query);
	format(query,sizeof(query)," * Jusu emailas 48 valandø bëgyje bus pakeistas á %s",newemail);
	MLog(playerid,"Email keitimas is","s", temp);
	MLog(playerid,"Email keitimas i","s", newemailex);
	SendClientMessage(playerid, COLOR, query);
}

forward SQL_AtsauktiKeitima(playerid);
public SQL_AtsauktiKeitima(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows)
		return SendInfoMessage(playerid, "~r~Email keitimo prasymas nerastas arba jis jau ivykdytas!");
	else
	{
		new query[350];
		format(query,sizeof(query),"Update Pastas Set NewEmail=NULL, ChangeDate=NULL WHERE Vardas='%s'",ReturnName(playerid));
		mysql_query(query);
		return SendInfoMessage(playerid,"Sekmingai atsaukei email keitima!");
	}
}

forward SQL_Changepassas(playerid,vardas[],passwordas[]);
public SQL_Changepassas(playerid,vardas[],passwordas[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows) return SendClientMessage(playerid, RED, " * Zaidejas nerastas!");
	new query[256];
	format(query,256,"UPDATE Pastas Set Email='konfiskuotiacc@lsgyvenimas.lt'  WHERE Vardas='%s'",vardas);
	mysql_query(query);
	format(query,256,"DELETE From RemindPassword WHERE Vardas='%s'",vardas);
	mysql_query(query);
	format(query,256,"UPDATE Account Set Slaptazodis='%s' WHERE Name='%s'",sha256_hash(passwordas),vardas);
	mysql_query(query);
	format(query,256,"INSERT INTO changedpass(Vardas,Newpass,Newhash,Data) VALUES('%s','%s',%i,NOW())",vardas,passwordas,123);
	mysql_query(query);
	SendClientMessage(playerid, YELLOW, " * Sekmingai pakeitei zaidejo slaptazodi!");
	return 1;
}

forward SQL_Atimamvipa(playerid,vardas[]);
public SQL_Atimamvipa(playerid,vardas[])
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(!rows) return SendClientMessage(playerid, RED, " * Zaidejas nerastas!");
	new query[256];
	format(query,sizeof(query),"UPDATE `Account` SET `Vip`=0 WHERE `Name` = '%s'",vardas);
	mysql_query(query);
	SendClientMessage(playerid,YELLOW," * Sekmingai nuemei zmogui vipa!");
	//playerDB[playerid][vip]=true;
	return 1;
}

forward SQL_LoadFSHouses();
public SQL_LoadFSHouses() // SQL_LoadFSHouses
{
	RestartCheck();
	new 
		hid,
		temp[25];
	new rows,fields;
	cache_get_data(rows,fields);
	new x;
	while(x<rows)
	{
		cache_get_row(x,0,temp), hid = strval(temp);
		cache_get_row(x,1,temp), fsHouses[hid][fspos][0] = floatstr(temp);
		cache_get_row(x,2,temp), fsHouses[hid][fspos][1] = floatstr(temp);
		cache_get_row(x,3,temp), fsHouses[hid][fspos][2] = floatstr(temp);
		cache_get_row(x,4,temp), fsHouses[hid][fangle] = floatstr(temp);
		cache_get_row(x,5,temp), fsHouses[hid][fcost] = strval(temp);
		
		fsHouses[hid][fobjid]=CreateDynamicObject(19471,fsHouses[hid][fspos][0],fsHouses[hid][fspos][1],fsHouses[hid][fspos][2],0,0,fsHouses[hid][fangle]);
		new tmp[128];
		format(tmp,128,"Kaina: {33CC00}%s{FFFFFF} €\nDaugiau informacijos - spauskite {33CC00}'~k~~GROUP_CONTROL_BWD~'",FormatNumber(fsHouses[hid][fcost]));
		fsHouses[hid][ftextid] = CreateDynamic3DTextLabel( tmp, 0xFFFFFFFF,fsHouses[hid][fspos][0],fsHouses[hid][fspos][1],fsHouses[hid][fspos][2]+1.0,5.0 );
		x++;
	}
}
forward SQL_CheckRoges(playerid);
public SQL_CheckRoges(playerid)
{
	SetPlayerAttachedObject(playerid, DOVANOS_SLOT, 19065, 2, 0.120000, 0.040000, -0.003500, 0, 100, 100, 1.4, 1.4, 1.4);
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows == 0)
	{
		ShowPlayerDialog(playerid,4859,DIALOG_STYLE_MSGBOX,"Kalëdø Senelis","{10A112}Kalëdø eventas 2017\nPirmiausiai pakalbëk su Kalëdø Seneliu prie miesto eglutës.","Aèiû!","");

	}
	else
	{
		new temp[30]; 
		new cps;
		
		cache_get_row(0,0,temp);
		cps = strval(temp);
		// if dovana == 1 then neatsieme
		if(cps == 0)
		{
			ShowPlayerDialog(playerid,4859,DIALOG_STYLE_MSGBOX,"Kalëdø Senelis","{10A112}Kalëdø eventas 2017\nIðdalink dovanas LSG þaidëjams kuo greièiau, kad patektum á TOP Seneliø lentelæ.\nDovanø gausi vien uþ tai, kad pabaigsi trasà, o vëliau galësi bandyti gerinti savo laikà.\nLaikas pradës skaièiuotis nuo tada, kai paimsi pirmà checkpointà.","Gerai!","");
			CreateRoges(playerid);
		}
		else// if 12 then give gift
		{
			ShowPlayerDialog(playerid,4859,DIALOG_STYLE_MSGBOX,"Kalëdø Senelis","{10A112}Kalëdø eventas 2017\nIðdalink dovanas LSG þaidëjams kuo greièiau, kad patektum á TOP Seneliø lentelæ.\nDovanø gausi vien uþ tai, kad pabaigsi trasà, o vëliau galësi bandyti gerinti savo laikà.\nLaikas pradës skaièiuotis nuo tada, kai paimsi pirmà checkpointà.","Gerai!","");
			CreateRoges(playerid);
		}
	}
}
/*
forward SQL_CheckGift(playerid);
public SQL_CheckGift(playerid)
{
	//SetPlayerAttachedObject(playerid, DOVANOS_SLOT, 19065, 2, 0.120000, 0.040000, -0.003500, 0, 100, 100, 1.4, 1.4, 1.4);
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows == 0)
	{
		//new msgas[1024];
		ResetGunData(playerid);
		if(GetPlayerScore(playerid) >= 1500) 
		{
			playerDB[playerid][vip]=true;
			new query[256];
			format(query,sizeof(query),"UPDATE `Account` SET `Vip`=`Vip`+10 WHERE `Name` = '%s'",ReturnName(playerid));
			mysql_query(query);
			ShowPlayerDialog(playerid, 15536, DIALOG_STYLE_MSGBOX, "Kaledu senis", "{FF0000}Ho Ho Ho!\n\n{FFFFFF}Ðtai kà gavai dovanø:\n\n{00864b} • Pakelá cigareèiø\n • 5 LSD\n • 300 Deagle kulkø\n • 100 Sniper kulkø\n • 300 MP5 kulkø\n • 10 raktø\n • +10 dienø VIP statuso.\n\n\n\
				{FFFFFF}Tikiuosi patiko mano dovana! Iki susitikimo kitais metais.", "Aèiû!","");
		}
		else
			ShowPlayerDialog(playerid, 15536, DIALOG_STYLE_MSGBOX, "Kaledu senis", "{FF0000}Ho Ho Ho!\n\n{FFFFFF}Ðtai kà gavai dovanø:\n\n{00864b} • Pakelá cigareèiø\n • 5 LSD\n • 300 Deagle kulkø\n • 100 Sniper kulkø\n • 300 MP5 kulkø\n • 10 raktø\n\n\n\
				{FFFFFF}Tikiuosi patiko mano dovana! Iki susitikimo kitais metais.", "Aèiû!","");

		if(playerDB[playerid][lsd] + 5 < 10)
			playerDB[playerid][lsd] += 5;
		else
			playerDB[playerid][lsd] = 10;

		playerDB[playerid][cigaretes]=20;
		GivePlayerWeaponEx(playerid,24, 300);
		GivePlayerWeaponEx(playerid,34, 100);
		GivePlayerWeaponEx(playerid,29, 300);

		playerDB[playerid][raktas]=10;
		new queryz[256];
		new IP[24];
		GetPlayerIp(playerid,IP,24);
		format(queryz,sizeof(queryz),"INSERT Into `Kaledos17`(`Vardas`,`Ip`,`Time`,`Dovana`) VALUES ('%s','%s',1,0)",ReturnName(playerid),IP);
		mysql_query(queryz);
	}
	else
	{
		SendInfoMessage(playerid,"Aciu uz dalyvavima!");
	}
}*/
forward SQL_UpdatedTime(playerid);
public SQL_UpdatedTime(playerid)
{
	mysql_function_query(SQL, "SELECT Vardas,Time FROM `Kaledos17` WHERE TIME IS NOT NULL ORDER BY Time ASC LIMIT 10", true, "SQL_Leaderboard", "");
}
forward SQL_Leaderboard();
public SQL_Leaderboard()
{
	new rows,fields; 
	cache_get_data(rows,fields);
	new idx=0;
	new Vardai[1024];
	new Laikai[1024];
	if(!rows) return;
	while(idx<rows)
	{
		new Vardas[24];
		new temp[24],taimas;
		cache_get_row(idx,0,Vardas);
		cache_get_row(idx,1,temp), taimas = strval(temp);
		idx++;
		format(Vardai,1024,"%s%i.%s\n",Vardai,idx,Vardas);
		format(Laikai,1024,"%s%02d:%02d.%02d\n",Laikai,(taimas / 60000),((taimas / 1000) % 60),(taimas % 1000) / 10);



	}
	SetDynamicObjectMaterialText(SeneliuVardai, 0,Vardai, 140, "courier", 20, 1, 0xFFFFFFFF, 0x00000000, 0);
	//SeneliuLaikai = CreateDynamicObject(19360, 1471.588500, -1621.675048, 13.739295, 0.000000, 0.000000, 25.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterialText(SeneliuLaikai, 0, Laikai, 140, "courier", 20, 1, 0xFFFFFFFF, 0x00000000, 2);

}
forward SQL_KVS(playerid);
public SQL_KVS(playerid)
{
	RestartCheck();
	new numrows,fields;
	cache_get_data(numrows,fields);
	if(numrows)
	{
		for(new i;i<numrows;i++)
		{
			new key[50],val[512];
			cache_get_row(i,1,key);
			cache_get_row(i,2,val);
			OnPlayerKVSLoaded(playerid,key,val);
		}
	}
}
forward SQL_kiausas(playerid);
public SQL_kiausas(playerid)
{
	RestartCheck();
	new numrows,fields;
	cache_get_data(numrows,fields);
	new sum = 0;
	//new prizasx = 0;
	new nepadeti = 0;
	if(numrows)
	{
		new temp[12];
		new k[5];
		for(new i;i<5;i++)
		{
			cache_get_row(0,i,temp), k[i] = strval(temp);
			if(k[i] > 0)
				sum++;
			if(k[i] == 1)
				nepadeti++;
		}
		//cache_get_row(0,5,temp), prizasx = strval(temp);
	}
	new msg[512];
//	new prizas[100];
	format(msg,sizeof(msg),"{FFFFFF}Apie Gimtadienio eventa\nPadeti priza i namus (Turi %s%i{FFFFFF} nepadetu prizu)",(nepadeti ? ("{00FF00}") : ("{FF0000}")),nepadeti);
	ShowPlayerDialog(playerid, 5990, DIALOG_STYLE_LIST, "LSG Gimtadienis 2018", msg,"Gerai","Atsaukti");
	return 1;
}

forward SQL_ShowKiausai(playerid);
public SQL_ShowKiausai(playerid)
{
	RestartCheck();
	new numrows,fields;
	cache_get_data(numrows,fields);
	new k[5];

	if(numrows)
	{
		for(new i;i<5;i++)
		{
			new temp[4];
			cache_get_row(0,i,temp), k[i] = strval(temp);
		}
	}
	new msg[512];
	new const sandeliai[5][10] = {
		"LSD","Seklu","Ratu","Ginklu","Pinigu"
	};
 	for(new i;i<5;i++)
 	{
 		new status[50];
 		if(k[i] == 0)
 			status = "{FF0000}Neturi{FFFFFF}";
 		else if(k[i] == 1)
 			status= "{00FF00}Turi{FFFFFF}";
 		else
 			status = "{FF0000}Padetas{FFFFFF}";
 		if(i == 0)
 			format(msg,sizeof(msg),"%s sandelio prizas [%s]",sandeliai[i],status);
 		else
 			format(msg,sizeof(msg),"%s\n%s sandelio prizas[%s]",msg,sandeliai[i],status);
 	}
 	//format(msg,512,"Kiausinis 1 [%s]\nKiausinis 2 [%s]\nKiausinis 3 [%s]\nKiausinis 4 [%s]\nKiausinis 5 [%s]",
// 		((k[0]) ? (turi) : (neturi)),((k[1]) ? (turi) : (neturi)),((k[2]) ? (turi) : (neturi)),((k[3]) ? (turi) : (neturi)),((k[4]) ? (turi) : (neturi)));
 	ShowPlayerDialog(playerid, 5992, DIALOG_STYLE_LIST, "Prizai",msg,"Padeti","Atsaukti");
}

forward SQL_PadetiKiausai(playerid,kiausinis);
public SQL_PadetiKiausai(playerid,kiausinis)
{
	RestartCheck();
	new numrows,fields;
	cache_get_data(numrows,fields);
	new k[5];
	if(numrows)
	{
		for(new i;i<5;i++)
		{
			new temp[4];
			cache_get_row(0,i,temp), k[i] = strval(temp);
		}
	}
	if(k[kiausinis] == 0)
	{
		SendInfoMessage(playerid,"~r~Neturi sio prizo!");
		ShowPlayerKiausai(playerid);
	}
	else if(k[kiausinis] == 2)
	{
		SendInfoMessage(playerid,"~r~Sis prizas jau padetas!~n~Naudok /baldai -> Dovanos");
		ShowPlayerKiausai(playerid);
	}
	else
	{
		if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Priza gali padeti tik name!");
		new housenumber,pname[MAX_PLAYER_NAME];
		housenumber = GetPlayerHouseID(playerid);
		GetPlayerName(playerid, pname, 24);

		if ( strcmp(hInfo[housenumber][Name],pname,false) ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");

		new baldaiid=-1;
		for(new i;i<MAX_BALDAI;i++)
		{
			if(!BalduSistema[housenumber][i][b_used])
			{
				baldaiid=i;
				break;
			}
		}
		if(baldaiid == -1)
		{
			SendClientMessage(playerid, TEXTCOL_GOLD, " * Tavo name nebera vietos naujiems baldams! Ismesk senus parases /baldai");
			return 1;
		}
		else
		{
			new const prizai[] = {19833,19473,2036,1654,2690};
			new i = baldaiid;
			new hid = housenumber;
			BalduSistema[hid][i][b_used]=1;
			BalduSistema[hid][i][b_obj]=prizai[kiausinis];
			BalduSistema[hid][i][b_cat]=13;

			GetPlayerPos(playerid,BalduSistema[hid][i][b_x],BalduSistema[hid][i][b_y],BalduSistema[hid][i][b_z]);
			GetXYInFrontOfPlayer(playerid,BalduSistema[hid][i][b_x],BalduSistema[hid][i][b_y],1.0);
			BalduSistema[hid][i][b_z]-=0.5;
			BalduSistema[hid][i][b_rx]=0.0;
			BalduSistema[hid][i][b_ry]=0.0;
			BalduSistema[hid][i][b_rz]=0.0;
			//BalduSistema[hid][i][b_oid]=CreateDynamicObject(BalduSistema[hid][i][b_obj],BalduSistema[hid][i][b_x],BalduSistema[hid][i][b_y],BalduSistema[hid][i][b_z],BalduSistema[hid][i][b_rx],BalduSistema[hid][i][b_ry],BalduSistema[hid][i][b_rz],GetHouseVirtualWorld(hid), _, _, 50.0);
			CreateBaldas(hid,i);
			SaveBaldai(hid);
		}


		new query[256];
		format(query,256,"UPDATE `Easter18` SET `k%i`=2 WHERE Vardas='%s'",kiausinis+1,pname);
		mysql_query(query);
		ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
		SendClientMessage(playerid, TEXTCOL_GOLD, " * Sekmingai pasidejai priza! Ji perstatyti gali parases /baldai");
	}
	return 1;
}

forward SQL_CheckPrize(playerid);
public SQL_CheckPrize(playerid)
{
	RestartCheck();
	new numrows,fields;
	cache_get_data(numrows,fields);
	new k[5];
	if(!numrows)
	{
		SendInfoMessage(playerid,"Tu dar neturi visu kiausiniu!");
		//cmd_kiausinis(playerid,"");
		return;
	}
	else
	{
		new temp[24];
		new sum =0;
		for(new i;i<5;i++)
		{
			cache_get_row(0,i,temp), k[i] = strval(temp);
			if(k[i] > 0)
				sum++;
		}
		if(sum < 5)
		{
			SendInfoMessage(playerid,"Tu dar neturi visu kiausiniu!");
			//cmd_kiausinis(playerid,"");
			return;
		}
		new prizasx= 0;
		cache_get_row(0,5,temp);
		prizasx = strval(temp);
		if(prizasx)
		{
			SendInfoMessage(playerid,"Tu jau atsiemei priza!");
			//cmd_kiausinis(playerid,"");
			return;
		}
		PlayerPlaySound(playerid,4201,0,0,0);
		SendClientMessage(playerid, TEXTCOL_GOLD, " * Sveikiname ivykdzius LSG Velyku eventa! Pasirink viena is siu prizu:");
		SendClientMessage(playerid, TEXTCOL_GOLD, " * Jei dabar neturi vietos automobiliui, tai parduok viena is ju ir grizk i sita meniu.");
		ShowPlayerDialog(playerid, 5993, DIALOG_STYLE_LIST, "Velyku prizas", "Gaidzio skinas\nVienetinis automobilis Tampa", "Gerai", "Atgal");

	}

}

forward SQL_ShowOrders(playerid,type);
public SQL_ShowOrders(playerid,type)
{
	new const types[][] = {
		"Pinigø perveþimas", "verslui"
	};
	RestartCheck();
	new numrows,fields;
	cache_get_data(numrows,fields);
	if(!numrows)
	{
		SendClientMessage(playerid, TEXTCOL_GOLD, " * Inkasatoriai *");
		SendClientMessage(playerid, COLOR, " * Ðiuo metu privaèiø uþsakymø nëra.");
		/*new msg[1024];
		format(msg,sizeof(msg),"")
		ShowPlayerDialog(playerid,17004,DIALOG_STYLE_MSGBOX,"Inkasatoriai",msg,"Gerai","Atsaukti");*/
	}
	else
	{
		new uzsakymai[4048];
		new x = 0;
		while( x < numrows && x < 10)
		{
			new temp[24],vardux[24],vieta[50],data[20];
			new forid,suma,idas;
			cache_get_row(x,0,temp), idas = strval(temp);
			cache_get_row(x,1,vardux);
			cache_get_row(x,3,temp), forid = strval(temp);
			cache_get_row(x,4,temp), suma = strval(temp);
			cache_get_row(x,7,data);
			new statusas[50],status;
			cache_get_row(x,5,temp),status = strval(temp);
			if(status)
			{
				cache_get_row(x,6,temp);
				format(statusas,50,"{FF0000}Vykdo {FFFFFF}%s",temp);
			}
			else
			{
				format(statusas,50,"{00FF00}Neávykdytas{FFFFFF}");
			}

			if(type == 0)
				format(vieta,50,"%s",BusinessInfo[forid][bName]);

			format(uzsakymai, 4048,"%s%s%i.%s (uþsakë: {008000}%s{FFFFFF}) [%s]:\n\t\
									%s {008000}\"%s\"{FFFFFF} suma: {008000}%i{FFFFFF}€ [%s]",uzsakymai,((x==0)? ("") : ("\n")),
									idas,types[2*type],vardux,statusas,types[2*type+1],vieta,suma,data);
			x++;
		}
		ShowPlayerDialog(playerid, 17001, DIALOG_STYLE_LIST,"Uþsakymai", uzsakymai, "Priimti", "Atsaukti");
	}
}

forward SQL_CheckOrder(playerid,type,forid,amount);
public SQL_CheckOrder(playerid,type,forid,amount)
{
	RestartCheck();
	new numrows,fields;
	cache_get_data(numrows,fields);
	if(!numrows)
	{
		CreateOrder(playerid,type,forid,amount);
	}
	else
	{
		SendClientMessage(playerid, TEXTCOL_GOLD, " * Inkasatoriai *");
		SendClientMessage(playerid, COLOR, " * Uþsakymas ðiam verslui jau yra mûsø sistemoje.");
		if(playerDB[playerid][specialybe] == 60)
		{
			ShowPlayerDialog(playerid,17000,DIALOG_STYLE_LIST,"Inkasatoriai","Padaryti uþsakymà\nPriimti uþsakymà","Gerai","Atsaukti");
		}
		else
		{
			ShowPlayerDialog(playerid,17000,DIALOG_STYLE_LIST,"Inkasatoriai","Padaryti uþsakymà","Gerai","Atsaukti");
		}
	}
}

forward SQL_StartOrder(playerid,idas);
public SQL_StartOrder(playerid,idas)
{
	RestartCheck();
	new numrows,fields;
	cache_get_data(numrows,fields);
	if(!numrows)
	{
		SendClientMessage(playerid, TEXTCOL_GOLD, " * Inkasatoriai *");
		SendClientMessage(playerid, COLOR, " * Ðiuo metu uþsakymø nëra.");
		return;
	}
	new x = 0;
	new forid = 0;
	new amount = 0;
	//new unfinished = 0;
	new pname[24];
	new orderid;
	GetPlayerName(playerid, pname, 24);
	new temp[24];
	new status = 0;
	while(x < numrows)
	{

		cache_get_row(x,0,temp),orderid=strval(temp);
		cache_get_row(x,5,temp),status = strval(temp);
		cache_get_row(x,3,temp),forid = strval(temp);
		cache_get_row(x,4,temp),amount = strval(temp);
		if(status == 1 && x == idas)
		{
			cache_get_row(x,6,temp);
			if(0 != strcmp(temp,pname,true))
			{
				SendClientMessage(playerid, COLOR, " * Sita uzsakyma jau vykdo kitas inkasatorius!");
				return;
			}

		}
		if(idas == x)
		{
			break;
		}
		x++;
	}
	if(status == 1)
	{
		SendClientMessage(playerid, COLOR, " * Jus turite nepabaigta uzsakyma, todel ji privalote pabaigti.");
	}
	else
	{
		new uzstatas = amount/10;
		if(GetPlayerMoneyA(playerid) < uzstatas)
		{
			new msg[128];
			format(msg,sizeof(msg), " * Ðitam kroviniui reikia %i€ uþstato, tu tiek neturi.",uzstatas);
			SendClientMessage(playerid, COLOR, msg);
			return;
		}
		new msg[128];
		format(msg,sizeof(msg), " * Sumokëjai %i€ uþstatà, já atgausi pristatæs pinigus.",uzstatas);
		SendClientMessage(playerid, COLOR, msg);
		GivePlayerMoneyA(playerid, -uzstatas);
	}
	InkaUzsakymai[playerid][uforid]=forid;
	InkaUzsakymai[playerid][uamount]=amount;
	InkaUzsakymai[playerid][utype]=0;
	InkaUzsakymai[playerid][ustatus]=1;
	SendClientMessage(playerid, COLOR, " * Priëmei uþsakymà. Sësk á darbinæ maðinà, kad pamatytum, kur tau reikia vaþiuoti.");
	new query[256];
	format(query,256,"UPDATE Orders SET `status`=1, `takenby`='%s' WHERE `orderid`=%i",pname,orderid);
	mysql_query(query);
	format(query,256,"UPDATE Orders SET `status`=0 WHERE `takenby`='%s' and `status`=1 and `orderid`<>%i",pname,orderid);
	mysql_query(query);
}

forward SQL_PickInka() ;
public SQL_PickInka() 
{
	RestartCheck();
	new numrows,fields;
	cache_get_data(numrows,fields);
	if(!numrows)
	{
		return;
	}
	new id = random(numrows);
	new temp[24],worldas;
	cache_get_row(id,0,temp),worldas=strval(temp);
	new busid = worldas - MAX_HOUSES*2;
	if(BusinessInfo[busid][bEarning] <= 2000)
		return;
	new query[256];
	format(query,sizeof(query), "INSERT INTO Orders(`from`,`type`,`forid`,`amount`,`status`,`date`) VALUES ('%s',%i,%i,%i,0,NOW())","Serveris",0,busid,2000);
	mysql_query(query);
	SendMessageToInka(TEXTCOL_GOLD,"[racija] Operatore: Naujas uzsakymas musu firmoje!");
}

forward SQL_PirktiNark(playerid,bizid);
public SQL_PirktiNark(playerid,bizid)
{
	RestartCheck();
	new numrows,fields;
	cache_get_data(numrows,fields);
	if(!numrows)
	{
		return SendInfoMessage(playerid,"~r~Siuo metu neturime narkotiku!");
	}
	new msg[2048];
	new x=0;
	new temp[24],type,kiekis,price;
	format(msg,2048,"Narkotikas\tKiekis\tKaina uþ vnt.\n");
	while(x < numrows) 
	{
		cache_get_row(x,1,temp), type = strval(temp);
		cache_get_row(x,2,temp), price = strval(temp);
		cache_get_row(x,3,temp), kiekis = strval(temp);
		format(msg,sizeof(msg),"%s%s\t%i\t%i€\n",msg,NarkTypes[type],kiekis,price);
		format(temp,sizeof(temp),"nark_type_%i",x);
		SetPVarInt(playerid, temp, type);
		format(temp,sizeof(temp),"nark_count_%i",x);
		SetPVarInt(playerid, temp, kiekis);
		format(temp,sizeof(temp),"nark_price_%i",x);
		SetPVarInt(playerid, temp, price);
		x++;
	}
	ShowPlayerDialog(playerid,585,DIALOG_STYLE_TABLIST_HEADERS,"Narkotiku pirkimas",msg,"Gerai","Atsaukti");
	return 1;
}
forward SQL_CheckNarkBuy(playerid, type, kiek, price,idx);
public SQL_CheckNarkBuy(playerid, type, kiek, price,idx)
{
	RestartCheck();
	new numrows,fields;
	cache_get_data(numrows,fields);
	if(!numrows)
	{
		return SendInfoMessage(playerid,"~r~Ivyko klaida!");
	}
	new temp[24]; 
	new amount;
	cache_get_row(0,0,temp), amount = strval(temp);
	if(amount < kiek)
	{
		return SendInfoMessage(playerid,"~r~Ivyko klaida!!");
	}
	GivePlayerMoneyA(playerid,-kiek*price);
	//BusinessMoney(kiek*price);
	if(GetPlayerScore(playerid) > 100 && GetPlayerVirtualWorld(playerid)>= MAX_HOUSES*2) BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning]+=kiek*price;
	ActorServe(playerid);
	new msg[128];
	format(msg,sizeof(msg)," * Nusipirkai %i vnt. %s{FFFFFF} uz %i€.",kiek,NarkTypes[type],kiek*price);
	SendClientMessage(playerid, WHITE, msg);
	if(type==0)
		playerDB[playerid][zole]+=kiek;
	if(type==1)
		playerDB[playerid][lsd]+=kiek;
	if(type==2)
		playerDB[playerid][ratai]+=kiek;
	if(type==3)
		playerDB[playerid][amfetaminas]+=kiek;
	format(msg,sizeof(msg),"UPDATE NarkTrade Set amount=amount-%i WHERE busid=%i AND type=%i",kiek,idx,type);
	mysql_query(msg);
	format(msg,sizeof(msg),"DELETE FROM NarkTrade Where amount <= 0");
	mysql_query(msg);
	return 1;
}
forward SQL_CheckNarkSell(playerid, type, kiekis, price);
public SQL_CheckNarkSell(playerid, type, kiekis, price)
{
	RestartCheck();
	new numrows,fields;
	cache_get_data(numrows,fields);
	if(!IsInBiz(playerid))
		return SendInfoMessage(playerid,"Ivyko klaida!");
	if(numrows)
	{
		return SendInfoMessage(playerid,"~r~Sis narkotikas jau parduodamas jusu versle!");
	}
	if(type==0)
    {
        if(playerDB[playerid][zole] < kiekis)
            return SendInfoMessage(playerid,"~r~Tu tiek neturi!");
		playerDB[playerid][zole]-=kiekis;
    }
	if(type==1)
    {
        if(playerDB[playerid][lsd] < kiekis)
            return SendInfoMessage(playerid,"~r~Tu tiek neturi!");
		playerDB[playerid][lsd]-=kiekis;
    }
	if(type==2)
    {
        if(playerDB[playerid][ratai] < kiekis)
            return SendInfoMessage(playerid,"~r~Tu tiek neturi!");
		playerDB[playerid][ratai]-=kiekis;
    }
	if(type==3)
    {
        if(playerDB[playerid][amfetaminas] < kiekis)
            return SendInfoMessage(playerid,"~r~Tu tiek neturi!");
		playerDB[playerid][amfetaminas]-=kiekis;
    }
	new query[256];
	new idx = GetPlayerVirtualWorld(playerid) - MAX_HOUSES*2;
	format(query,256,"INSERT INTO NarkTrade(busid,type,price,amount) VALUES (%i,%i,%i,%i)",idx,type,price,kiekis);
	mysql_query(query);
	SendInfoMessage(playerid,"~g~Idejai narkotikus i prekyba! Pinigus gausi i pelna.");
	return 1;
}

forward SQL_CheckAsmeninis(playerid,saudyklosid,time,weaponid);
public SQL_CheckAsmeninis(playerid,saudyklosid,time,weaponid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows == 0)
	{
		SendClientMessage(playerid, WHITE, " **** ASMENINIS REKORDAS ****");
		SendClientMessage(playerid, GREEN, " * Pagerinai savo asmenini rekorda! Dabar bandyk pagerinti LSG rekorda!");
		new query[256];
		new Float:pataikymas = (SaudyklosStats[playerid][s_shot]*100.0)/SaudyklosStats[playerid][s_bullets];
		format(query,256,"REPLACE INTO Saudykla(Vardas,Saudykla,Laikas,Ginklas,Data,Pataikymas) VALUES('%s',%i,%i,%i,NOW(),'%f')",ReturnName(playerid),saudyklosid,time,weaponid,pataikymas);
		mysql_tquery(SQL,query);
	}
	else
	{
		new temp[24];
		cache_get_row(0,0,temp);
		new lold = strval(temp);
		if(time < lold)
		{
			SendClientMessage(playerid, WHITE, " **** ASMENINIS REKORDAS ****");
			SendClientMessage(playerid, GREEN, " * Pagerinai savo asmenini rekorda! Dabar bandyk pagerinti LSG rekorda!");
			new query[256];
			new Float:pataikymas = (SaudyklosStats[playerid][s_shot]*100.0)/SaudyklosStats[playerid][s_bullets];
			format(query,256,"REPLACE INTO Saudykla(Vardas,Saudykla,Laikas,Ginklas,Data,Pataikymas) VALUES('%s',%i,%i,%i,NOW(),'%f')",ReturnName(playerid),saudyklosid,time,weaponid,pataikymas);
			mysql_tquery(SQL,query);
		}
	}
}

forward SQL_CheckSaudykla(playerid);
public SQL_CheckSaudykla(playerid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows == 0)
	{
		PlayerPlaySound(playerid, 1183, 0.0, 0.0, 0.0);
		SendClientMessage(playerid, TEXTCOL_GOLD, " **** REKORDAS ****");
		SendClientMessage(playerid, TEXTCOL_GOLD, " * Tu patekai i pirma vieta TOP 10 lenteleje su savo pasirodymu!");
		SendClientMessage(playerid, TEXTCOL_GOLD, " * Dabar gali bandyti tai padaryti su kitu ginklu.");
		SetTimerEx("StopMusic",2000,false, 	"i", playerid); //, ...)
	}
	else
	{
		new temp[24];
		cache_get_row(0,0,temp);
		new num = strval(temp);
		if(num == 0)
		{
			PlayerPlaySound(playerid, 1183, 0.0, 0.0, 0.0);
			SendClientMessage(playerid, TEXTCOL_GOLD, " **** REKORDAS ****");
			SendClientMessage(playerid, TEXTCOL_GOLD, " * Tu patekai i pirma vieta TOP 10 lenteleje su savo pasirodymu!");
			SendClientMessage(playerid, TEXTCOL_GOLD, " * Dabar gali bandyti tai padaryti su kitu ginklu.");
			SetTimerEx("StopMusic",2000,false, 	"i", playerid); //, ...)
		}
		else if(num < 10)
		{
			SendClientMessage(playerid, -1, " **** TOP 10 ****");
			new msg[128];
			format(msg,128," * Tu patekai i %i vieta TOP 10 lenteleje!",num+1);
			SendClientMessage(playerid, ORANGE, msg);
			PlayerPlaySound(playerid,4201,0,0,0);
		}
	}


}

forward SQL_SaudyklosGun(playerid,saudyklosid);
public SQL_SaudyklosGun(playerid,saudyklosid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows == 0) {
		ShowPlayerDialog(playerid, 10400, DIALOG_STYLE_LIST, "Ðaudykla", "Dalyvauti\nTOP 10","Gerai","Atsaukti");
		return SendInfoMessage(playerid,"~r~Dar niekas nedalyvavo rungtyje!");
	}
	new x;
	while(x<rows)
	{
		new temp[30]; new id;
		cache_get_row(x,0,temp);
		id = strval(temp);
		GetWeaponName(id,temp,30);
		AddDListItem(playerid, temp, id);
		x++;
	}
	ShowPlayerDList(playerid, 10402, "Pasirinkite ginklà", "Rinktis", "Atsaukti");
	return 1;
}
forward SQL_SaudyklosTOP(playerid,saudyklosid);
public SQL_SaudyklosTOP(playerid,saudyklosid)
{
	RestartCheck();
	new rows,fields;
	cache_get_data(rows,fields);
	if(rows == 0) {
		ShowPlayerDialog(playerid, 10400, DIALOG_STYLE_LIST, "Ðaudykla", "Dalyvauti\nTOP 10","Gerai","Atsaukti");
		return SendInfoMessage(playerid,"~r~Dar niekas nedalyvavo rungtyje!");
	}
	new x;
	while(x<rows)
	{
		new textaz[128];
		if(x == 0)
			format(textaz,128,"{FFD700}");
		else if(x==1)
			format(textaz,128,"{bec7c7}");
		else if(x==2)
			format(textaz,128,"{cd7f32}");
		new zaidejas[24],laikas[24],Float:pataikymas;
		new temp[24];
		cache_get_row(x,0,zaidejas);
		cache_get_row(x,2,temp);
		new time = strval(temp);
		new secs = time / 1000;

		new mins = secs / 60;
		new seconds = secs % 60;
		new ms = (time % 1000) / 10;

		format(laikas,24,"%i:%s%i.%s%i",mins,(seconds < 10 ? ("0"):("")),seconds,(ms < 10? ("0"):("")),ms);

		cache_get_row(x,5,temp);

		pataikymas = floatstr(temp);

		format(textaz,sizeof(textaz),"%s%i.\t%s\t%s\t%.1f%%",textaz,x+1,zaidejas,laikas,pataikymas);
		AddDListItem(playerid, textaz);
		x++;
	}
	ShowPlayerDListHeader(playerid, 10403, "Pasirinkite ginklà", "Rinktis", "Atsaukti","#\tZaidejas\tLaikas\tPataikymas");
	return 1;

}
forward SQL_CheckNTA(playerid,nta,houseid);
public SQL_CheckNTA(playerid,nta,houseid)
{
	new rows, fields;
    cache_get_data(rows, fields);
    if(rows)
    {
    	return SendInfoMessage(playerid,"Sis namas jau turi uzsakymu padarytu maziau nei pries 24h.");
    }

    if(GetPlayerMoneyA(playerid) < 25000)
    	return SendInfoMessage(playerid,"Neturi pakankamai pinigu!");
    new Float:Co[3];
    GetPlayerPos(nta,Co[0],Co[1],Co[2]);
    if(!IsPlayerInRangeOfPointEx(20.0,playerid, Co[0], Co[1], Co[2]))
    	return SendInfoMessage(playerid,"Jus per toli nuo NTA agento!");
    new query[256];
    format(query,sizeof(query),"INSERT INTO Irengimas VALUES(%i,'%s',NOW())",houseid,ReturnName(nta));
    mysql_query(query);
    GivePlayerMoneyA(playerid,-25000);
    GivePlayerMoneyA(nta,20000);
    Pelnas(nta,33,35000);
    new msgas[150];
    format(msgas,150," * Jus gavote uþsakymà nuo %s irengti nama nr.%i. Turite tam padaryti 24 valandas, uþ baldø iðlaidas tarkitës su uþsakovu.",ReturnName(playerid),houseid);
    SendClientMessage(nta, -1, msgas);
    SetPVarInt(nta,"irengineja",houseid);
    printf(msgas);
    format(msgas,150," * Uþsakëte namo nr.%i interjero irengimà ið NTA %s.",houseid,ReturnName(nta));
    SendClientMessage(playerid, -1, msgas);
    SendClientMessage(playerid, -1, " * Jeigu norite, kad jums NTA nupirktø baldø - duokite jiems pinigø ið anksto.");
    return 1;
}

forward SQL_LoadNTA(playerid);
public SQL_LoadNTA(playerid)
{
	new rows, fields;
    cache_get_data(rows, fields);
    if(rows)
    {
    	new temp[24];
    	cache_get_row(0,0,temp);
    	SetPVarInt(playerid,"irengineja",strval(temp));
    }
}

/*
forward SQL_CheckSenelis(playerid) ;
public SQL_CheckSenelis(playerid) 
{
	new rows, fields;
    cache_get_data(rows, fields);
    SetPlayerHealth(playerid, 100);
    SetPlayerArmour(playerid, 100);
    SendClientMessage(playerid, COLOR, " * Tu buvai pagydytas!");
    if(rows)
    {
    	return SendInfoMessage(playerid,"Aciu uz dalyvavima!");
    }
	new pataike = GetPVarInt(playerid, "Pataike");
	if(pataike >= 100)
	{
		new query[128];
		new IP[24];
		GetPlayerIp(playerid,IP,24);
		format(query,sizeof(query),"SELECT `Dovana` From `Kaledos17` WHERE Vardas='%s'",ReturnName(playerid));
		mysql_function_query(SQL, query, true, "SQL_CheckGift", "i", playerid);
	}
	else
	{

		new msgas[600];
		format(msgas,600,"\t\t\t\t{cb4335}Los Santos Gyvenimas\n{FFFFFF}\t\t\t\tÐv. Kalëdos 2018\n\n\n\
			Pamirðkime vargus ir ðiandien negalvokim,\nKas buvo, kà rytoj likimas duos.\nTegu Kalëdø snaigës ðoka baltà ðoká -\nJuk reikia mûsø sielai atgaivos.\n\
			\n\n{f2d7d5}Sveikinu tave su graþiausiomis metu ðventëmis! Ávykdyk Ðv. Kalëdø eventà ir gauk kalëdiná prizà!\nPrie eglutës gali ið sniego padaryti gniûþtæ(MOUSE1) ir mesti á kitus þmones.\n\nPataikytos gniûþtës: {FFFFFF}%i/100",pataike);
		ShowPlayerDialog(playerid, 15536, DIALOG_STYLE_MSGBOX, "Kalëdinë eglutë",msgas, "Gerai","");
		
		return 1;
	}
	return 1;
}
*/
forward SQL_CheckNTABaldai(playerid,houseid,showdialog);
public SQL_CheckNTABaldai(playerid,houseid,showdialog)
{
	new rows, fields;
    cache_get_data(rows, fields);
    if(!rows)
    {
    	if(showdialog)
    		SendInfoMessage(playerid,"Sis namas neturi uzsakymo ji irengti arba nuo jo praejo 24 valandos.");
    	return;
    }
    SetPVarInt(playerid,"irengineja",houseid);
    if(showdialog)
    	ShowPlayerDialog(playerid,6871,DIALOG_STYLE_LIST,"Baldu sistema","Perstatyti, pasirinkti baldus","Gerai","Atsaukti");
    return;
}

forward SQL_TextureLoad(pid);
public SQL_TextureLoad(pid)
{
	RestartCheck();
	//new temp[20],row[1024],Xp,Vardux[24];
	new rows,fields;
	new temp[50];
	cache_get_data(rows,fields);
	new x;
	new houseid;

	while(x<rows)
	{
		//new idx;
		cache_get_row(x,0,temp); 

		houseid=strval(temp);

		cache_get_row(x,1,temp); 
		new isdoor=strval(temp);
		cache_get_row(x,2,temp);
		new matid = strval(temp);
		cache_get_row(x,3,temp);
		new tid = strval(temp);
		
		Texturize(houseid,isdoor,matid,tid);

		x++;
	}		
	if(pid != -1)
		Texturize(GetPlayerHouseID(pid),GetPVarInt(pid, "isdoor"),GetPVarInt(pid, "matid"),8932);
	return 1;
}

forward SQL_LoadKeybinds(playerid);
public SQL_LoadKeybinds(playerid)
{
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
	
	new temp[512];
	new jau=0;
	while(jau < rows)
	{
		new id;
		cache_get_row(jau, 0, temp);
		id = strval(temp);
		new varname[20];
		new varname2[20];
		format(varname,20,"KeyBind_%i",id);
		format(varname2,20,"KeyBindSet_%i",id);

		cache_get_row(jau, 1, temp);
		SetPVarString(playerid, varname, temp);
		SetPVarInt(playerid, varname2, 1);
		jau++;
	}
}
forward SQL_LoadSienaSQL();
public SQL_LoadSienaSQL()
{
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
    NameCount = 0;

	new jau=0;
	while(jau < rows)
	{
		new nameas[24];
		new color[10];
		cache_get_row(jau, 0, nameas);
		cache_get_row(jau, 1, color);
		AddName(nameas,color, 0);
		jau++;
	}
	new num_boards = (NameCount / NAMES_ON_STULPELIS) + 1;
	for(new i;i<num_boards;i++)
	{
		ReloadBoard(i);
	}
}
forward SQL_CheckSiena(playerid);
public SQL_CheckSiena(playerid)
{
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
    if(rows)
    	return SendInfoMessage(playerid,"~r~Tu jau pasirasei ant sios sienos!");
    else
    {
		new colstring[12];
		format(colstring,12,"%06x",(GetPlayerColor(playerid) >>> 8));

		new pname[24];
		GetPlayerName(playerid, pname, 24);

		new ret = AddName(pname,colstring,1);
		if(ret)
		{
			new query[256];
			format(query,sizeof(query),"INSERT INTO Siena(Name,Color,Date) VALUES ('%s','%s',NOW())",pname,colstring);
			mysql_query(query);
			return SendInfoMessage(playerid,"~g~Nice!~n~~w~Aciu uz tavo parasa.");
		}
		else
		{
			return SendInfoMessage(playerid,"~r~Deja, bet ant sienos nebera vietos");
		}
    }
}

forward SQL_Kaledos(playerid,id);
public SQL_Kaledos(playerid,id)
{
	RestartCheck();
	new rows, fields;
    cache_get_data(rows, fields);
    new gifts[7];
    if(!rows)
    {
    	new query[256];
    	new IP[24];
    	GetPlayerIp(playerid, IP, 24);
    	new hashas[128];
		gpci(playerid,hashas,sizeof(hashas));
		format(query,256,"INSERT INTO Kaledos(Vardas,Ip,Registered,Hashas) VALUES('%s','%s',NOW(),'%s')",ReturnName(playerid), IP, hashas);
		mysql_query(query);
    }
    else
    {
    	new temp[24];
		cache_get_row(0, 2, temp); gifts[0]=strval(temp); // vip
		cache_get_row(0, 3, temp); gifts[1]=strval(temp); // papuosimai
		cache_get_row(0, 4, temp); gifts[2]=strval(temp); // mesos
		cache_get_row(0, 5, temp); gifts[3]=strval(temp);
		cache_get_row(0, 6, temp); gifts[4]=strval(temp);
		cache_get_row(0, 7, temp); gifts[5]=strval(temp);
		cache_get_row(0, 8, temp); gifts[6]=strval(temp);
    }
	new day,month,year;
	getdate(year, month, day);
	new kaledudiena = day - 20; // from 0 to 6
	if(kaledudiena < 0 || kaledudiena > 6)
		return SendInfoMessage(playerid,"Sugrizk gruodzio 20 diena!");
    if(id == 0) // introduction
	{
		new msgas[800];
		format(msgas,800,"\t\t\t\t\t{cb4335}Los Santos Gyvenimas\n{FFFFFF}\t\t\t\t\t  Ðv. Kalëdos 2021\n\n\n\
			Pamirðkime vargus ir ðiandien negalvokim,\nKas buvo, kà rytoj likimas duos.\nTegu Kalëdø snaigës ðoka baltà ðoká -\nJuk reikia mûsø sielai atgaivos.\n\
			\n\n{f2d7d5}Sveikiname Jus su graþiausiomis metø ðventëmis!\
			\nTe iðsipildo visos jûsø svajonës, o ateinantys metai tebûna tokie pat turiningi kaip Kûèiø stalas.\n\n\
			Visada jûsø\n-LSG Administracija\n\n\
            Ðiemet Kalëdø Senelis paliko visiems dovanø: tiek geriems, tiek blogiems,\n\
            bet prieð tai - jis praðë tavæs ávykdyti vienà misijà!");
		ShowPlayerDialog(playerid, 15536, DIALOG_STYLE_MSGBOX, "Kalëdinë eglutë",msgas, "Toliau","");
		playerDB[playerid][kepure]=13;
		AttachKepure(playerid,GetPlayerSkin(playerid));
        new Float:HP;
        GetPlayerHealth(playerid, HP);
        if(HP < 100)
            SetPlayerHealth(playerid, 100);
        GetPlayerArmour(playerid, HP);
        if(HP < 100)
            SetPlayerArmour(playerid, 100);
        PlayAudioStreamForPlayer(playerid, "http://www.lsgyvenimas.lt/sounds/christmas3.mp3");
        //SetPVarInt(playerid, "Pataike", 0);
	}
	else if(id == 1) // mission
	{
		if(GetPlayerScore(playerid) < 1000)
		{
			SendInfoMessage(playerid,"Sugrizk kai turesi bent 1000 XP!");
			return 1;
		}
		new gift = gifts[0];

        new msgas[600];
        if(gift == 1)
        {
            format(msgas,600,"{cb4335}Los Santos Gyvenimas\n{FFFFFF}Ðv. Kalëdos 2021\n\n\n\
					Sveikinu ávykdþius Kalëdø senelio misijà ir dëkoju uþ dalyvavimà LSG Kalëdø evente. Iki susitikimo kitais metais - ho ho ho!!!");
        }
        else
        {
            new gniuztes = GetPVarInt(playerid, "Pataike");
            if(gniuztes < 100)
            {
                format(msgas,600,"{cb4335}Los Santos Gyvenimas\n{FFFFFF}Ðv. Kalëdos 2021\n\n\n\
                        Tavo misija ðiemet - nubausti visus LSG nedorëlius sniegu!! Pataikyk 100 sniego gniûþèiø ir sugráþk pas mane atsiimti dovanos!\n\
                        \n\n\
                        Pataikytos gniûþtës: {cb4335}%i{FFFFFF}/100.", gniuztes);
            }
            else
            {
                ResetGunData(playerid);
                VykdoMisija(playerid, 0, 1);
                if(playerDB[playerid][admin] || playerDB[playerid][vip] || GetPlayerScore(playerid) >= 50000)
                {
                    format(msgas,600,"{cb4335}Los Santos Gyvenimas\n{FFFFFF}Ðv. Kalëdos 2021\n\n\n\
                        Hohoho - tu sëkmingai ávykdei Kalëdinæ misijà!\n\
                        \n\n\
                        Ðtai kà Kalëdø Senelis tau paliko dovanø:\n\n\
                        • 1000 kulkø Desert Eagle\n\
                        • 1000 kulkø Sniper Rifle\n\
                        • 500 kulkø Combat Shotgun\n\
                        • 500 kulkø M4.\n\n\
                        \n\
                        Iki susitikimo kitais metais ir linkiu tau paèiø linksmiausiø ðvenèiø!");

                    GivePlayerWeaponEx(playerid,24,1000); // dgl
                    GivePlayerWeaponEx(playerid,34,1000); // sniper
                    GivePlayerWeaponEx(playerid,27,500); // combat sg
                    GivePlayerWeaponEx(playerid,31,500); // m4
                    
                }
                else
                {
                    format(msgas,600,"{cb4335}Los Santos Gyvenimas\n{FFFFFF}Ðv. Kalëdos 2021\n\n\n\
                        Hohoho - tu sëkmingai ávykdei Kalëdinæ misijà!\n\
                        \n\n\
                        Ðtai kà Kalëdø Senelis tau paliko dovanø:\n\n\
                        • 100 kulkø Desert Eagle\n\
                        • 1000 kulkø Rifle\n\
                        • 1000 kulkø Shotgun\n\
                        \n\
                        Iki susitikimo kitais metais ir linkiu tau paèiø linksmiausiø ðvenèiø!");

                    GivePlayerWeaponEx(playerid,24,100); // dgl
                    GivePlayerWeaponEx(playerid,33,1000); // sniper
                    GivePlayerWeaponEx(playerid,25,1000); // shotgun

                }
            }

        }

        ShowPlayerDialog(playerid, 15548, DIALOG_STYLE_MSGBOX, "Kalëdinë eglutë",msgas, "Gerai","");
        /*
		if(gift == 0) 
		{
			KaleduMisija(playerid,kaledudiena);
			VykdoMisija(playerid,kaledudiena,1); // in progress
		}
		else if(gift == 1)
		{
			KaleduMisija2(playerid,kaledudiena);
		}
		else if(gift == 2)
		{
			new msgas[600];
			if(kaledudiena == 1 || kaledudiena == 2)
			{
				format(msgas,600,"{cb4335}Los Santos Gyvenimas\n{FFFFFF}Ðv. Kalëdos 2020\n\n\n\
				Naudok komandà "#TEXT_BLUE"/padetidovana"#TEXT_WHITE" savo namuose, kad pasidëtum baldus.");
			}
			else if(kaledudiena == 6)
			{
				format(msgas,600,"{cb4335}Los Santos Gyvenimas\n{FFFFFF}Ðv. Kalëdos 2020\n\n\n\
				Naudok komandà "#TEXT_BLUE"/dovana Vardas_Pavarde"#TEXT_WHITE", kad áteiktum dovanà kitam þaidëjui.");
			}
			else
			{
				format(msgas,600,"{cb4335}Los Santos Gyvenimas\n{FFFFFF}Ðv. Kalëdos 2020\n\n\n\
					Ðiandienos misijà tu jau ávykdei - sugráþk rytoj ir gausi naujà uþduotá!");
			}
			ShowPlayerDialog(playerid, 15548, DIALOG_STYLE_MSGBOX, "Kalëdinë eglutë",msgas, "Aèiû","");
		}
		else if(gift == 3)
		{
			if(kaledudiena < 6)
			{
				format(msgas,600,"{cb4335}Los Santos Gyvenimas\n{FFFFFF}Ðv. Kalëdos 2020\n\n\n\
					Ðiandienos misijà tu jau ávykdei - sugráþk rytoj ir gausi naujà uþduotá!");
			}
			else
			{
				format(msgas,600,"{cb4335}Los Santos Gyvenimas\n{FFFFFF}Ðv. Kalëdos 2020\n\n\n\
					Sveikinu ávykdþius paskutinæ Kalëdø senelio misijà ir dëkoju uþ dalyvavimà LSG Kalëdø evente. Iki susitikimo kitais metais - ho ho ho!!!");
			}
			
			ShowPlayerDialog(playerid, 15548, DIALOG_STYLE_MSGBOX, "Kalëdinë eglutë",msgas, "Aèiû","");
		}*/
	} 
	else if(id == 3) // padeti dovana
	{
		new housenumber = GetPlayerHouseID(playerid);
		if(housenumber == 0)
			return SendInfoMessage(playerid,"Privalote buti namie!");

		new hid = housenumber;
	
		new slots = GetFreeBaldaiSlots(hid);

		if(gifts[1] == 2)
		{
			if(slots < 13)
			{
				SendInfoMessage(playerid," Truksta vietos naujiems baldams!");
				return 1;
			}
			for(new i=19054;i<=19066;i++)
			{
				PadetiDovana(hid, i);
			}
			VykdoMisija(playerid,1,3);
		}
		else if(gifts[2] == 2)
		{
			new objs[6] = {2905,2905,2906,2906,2907,2908};

			if(slots < 13)
			{
				SendInfoMessage(playerid," Truksta vietos naujiems baldams!");
				return 1;
			}
			for(new i;i<6;i++)
			{
				PadetiDovana(hid, objs[i]);
			}
			VykdoMisija(playerid,2,3);
		}
		else
		{
			SendInfoMessage(playerid,"~r~Neturi jokiu dovanu!");
			return 1;
		}

		SendClientMessage(playerid,WHITE," * Padëjai dovana! Jà gali perstatyti paraðæs /baldai -> Dovanos.");
		SaveBaldai(hid);
		ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);

	}
	else if(id == 4) // /dovana V_P
	{
		if(gifts[6] == 2 || gifts[6] == 1)
		{
			Dovanoti(playerid, GetPVarInt(playerid, "Dovanoja"));
			VykdoMisija(playerid,6,3);
		}
		else
		{
			SendInfoMessage(playerid,"~r~Neturi jokiu dovanu!");
			return 1;
		}
	}
	return 1;
}
forward SQL_Pelnai();
public SQL_Pelnai()
{
	new rows,fields;
	cache_get_data(rows,fields);
	new x;
	new temp[20],suma,id;
	while(x<rows)
	{
		cache_get_row(x,0,temp),id=strval(temp);
		if(id<100)
		{
			cache_get_row(x,1,temp),suma=strval(temp);
			pelnas[id]=suma;
		}
		x++;
	}
	return 1;
}