CMD:cheal(playerid,params[])
{
    if(!playerDB[playerid][admin]) return 1;
    new vardas[128];
	if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Pagydyti zaidejo masina: /cheal [dalis vardo] arba /cheal [atstumas]"); return 1;}
	if(IsNumeric(vardas))
	{
		new Float:Coo[3];
		GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
		foreach (Player, player)
		{
				if(IsPlayerInRangeOfPointEx(strval(vardas), player, Coo[0],Coo[1],Coo[2]))
				{
					if(IsPlayerInAnyVehicle(player))
					{
						new vid = GetPlayerVehicleID(player);
						new Float:VHP;
						GetVehicleHealth(vid, VHP);
						RepairVehicle(vid);
						if(VHP > 1001.0)
							SetVehicleHealth(vid, VHP);
					}
				}
		}
		SendInfoMessage(playerid,"Pagydete.");
		return 1;

	}
	new id = GetPlayeridMid(vardas);
	if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	new mess[128],name[MAX_PLAYER_NAME],rec[MAX_PLAYER_NAME];
	GetPlayerName(playerid,name,sizeof(name));
	GetPlayerName(id,rec,sizeof(rec));
	format(mess,sizeof(mess),"***%s pagyde jusu masina!",name);
	SendClientMessage(id,0xD9E916FF,mess);
	format(mess,sizeof(mess),"***Pagydete %s masina!",rec);
	SendClientMessage(playerid,0xD9E916FF,mess);
	if(!IsPlayerInAnyVehicle(id)) return SendInfoMessage(playerid,"Zaidejas ne automobilyje.");
	RepairVehicle(GetPlayerVehicleID(id));
	return 1;
}
CMD:aminutes(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 1;
	new tname[128],dminutes;
	if(sscanf(params,"s[24]d",tname,dminutes))
	{
		SendInfoMessage(playerid,"Norint pakeisti þaidëjo minutes naudokite /aminutes [vardas] [kiek].");
		return 1;
	}
	if(dminutes < 0) return 0;
	new tid = GetPlayeridMid(tname);
	if(tid==INVALID_PLAYER_ID)
	{
		SendInfoMessage(playerid,"Zaidejas neprisijunges.");
		return 1;
	}
	GetPlayerName(tid,tname,sizeof(tname));
	new mess[128],name[MAX_PLAYER_NAME];
	format(mess,sizeof(mess),"***Nustatëte %s %s minuèiø ",FormatNumber(dminutes),tname);
	SendClientMessage(playerid,COLOR,mess);
	playerDB[playerid][pradirbo]=dminutes;
	return 1;
}
CMD:relog(playerid,params[])
{
    if(!playerDB[playerid][admin]) return 1;
    new vardas[128];
	if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Atjungti zaideja: /relog [dalis vardo]"); return 1;}
	new id = GetPlayeridMid(vardas);
	if (id == INVALID_PLAYER_ID || IsPlayerNPC(id)) { SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	SendClientMessage(id,COLOR," * Jus relogino administratorius!");
	new PIP[24];
	GetPlayerIp(id,PIP,sizeof(PIP));
	SetPVarString(id,"PIP",PIP);
	format(vardas,sizeof(vardas),"banip %s",PIP);
	SendRconCommand(vardas);
	SetPVarInt(id,"relog",1);
	MLog(playerid,"Relog","s",ReturnName(id));
	return 1;
}
CMD:heal(playerid,params[])
{
    if(!playerDB[playerid][admin]) return 1;
    new vardas[128];
	if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Pagydyti zaideja: /heal [dalis vardo] arba /heal [atstumas]"); return 1;}
	if(IsNumeric(vardas))
	{
		new Float:Coo[3];
		GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
		foreach (Player, player)
		{
				if(IsPlayerInRangeOfPointEx(strval(vardas), player, Coo[0],Coo[1],Coo[2]))
				{
					SetPlayerHealth(player,100);
					SetPlayerArmour(player,100);

				}
		}
		SendInfoMessage(playerid,"Pagydete.");
		return 1;

	}
	new id = GetPlayeridMid(vardas);
	if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	new mess[128],name[MAX_PLAYER_NAME],rec[MAX_PLAYER_NAME];
	GetPlayerName(playerid,name,sizeof(name));
	GetPlayerName(id,rec,sizeof(rec));
	format(mess,sizeof(mess),"***%s pagyde jus!",name);
	SendClientMessage(id,0xD9E916FF,mess);
	format(mess,sizeof(mess),"***Pagydete %s!",rec);
	SendClientMessage(playerid,0xD9E916FF,mess);
	SetPlayerHealth(id,100);
	SetPlayerArmour(id,100);
	return 1;
}

CMD:akiniai2(playerid,params[])
{
			#pragma unused params
			if(!playerDB[playerid][admin]) return 1;
			//GivePlayerWeaponEx(playerid,44,1);
			SendInfoMessage(playerid,"Gavote naktinio matymo akinius");
			return 1;
}
CMD:akiniai(playerid,params[])
{
			#pragma unused params
			if(!playerDB[playerid][admin]) return 1;
		//	GivePlayerWeaponEx(playerid,45,1);
			SendInfoMessage(playerid,"Gavote infraraudonuosius akinius");
			return 1;
}


CMD:oba(playerid,params[])
{
			#pragma unused params
			if(!playerDB[playerid][admin]) return 0;
			//ResetPlayerWeapons(playerid);
			GivePlayerWeaponEx(playerid,6,10);
			GivePlayerWeaponEx(playerid,24,100000);
			GivePlayerWeaponEx(playerid,27,100000);
			GivePlayerWeaponEx(playerid,31,100000);
			GivePlayerWeaponEx(playerid,32,100000);
			GivePlayerWeaponEx(playerid,34,100000);
			GivePlayerWeaponEx(playerid,43,100000);
			//GivePlayerWeaponEx(playerid,46,100000);
			GivePlayerWeaponEx(playerid,22,100000);
			SendInfoMessage(playerid,"Ginklus naudokite ismintingai !");
			return 1;
}
CMD:eventgun(playerid,params[])
{
			#pragma unused params
			if(!playerDB[playerid][admin]) return 0;
			//ResetPlayerWeapons(playerid);
			GivePlayerWeaponEx(playerid,22,100000); //pistule
			GivePlayerWeaponEx(playerid,33,100000); //rifle
			GivePlayerWeaponEx(playerid,25,100000); //pompa
			SendInfoMessage(playerid,"Ginklus dalinkite ismintingai !");
			return 1;
}

CMD:visraktis(playerid,params[])
{
			#pragma unused params
			if(!playerDB[playerid][admin]) return 0;
			SendInfoMessage(playerid,"Gavote masinu visrakti");
			playerDB[playerid][bypass] = true;
			for(new vehicleid;vehicleid<MAX_VEHICLES;vehicleid++)
			{
				SetVehicleParamsForPlayerEx(vehicleid,playerid,0,0);
			}
			return 1;
}

CMD:afondas(playerid,params[])
{
			#pragma unused params
			if(!playerDB[playerid][admin]) return 1;
			//if(FALSE==false) return SendClientMessage(playerid,RED," * AFONDO NER");
			new msg[128];
			format(msg,sizeof(msg),"Siandien administratoriu fonde yra: %i €",Server[afondas]);
			SendClientMessage(playerid, 0xD9E916FF, msg);
			SendClientMessage(playerid, 0xD9E916FF, "* Jei norite, galite paimti ( /af_paimti ) arba ideti ( /af_padeti ) pinigu i fonda.");
			SendClientMessage(playerid, 0xFF0000FF, "* Demesio: Administratoriu fondo pinigai yra skirti TIK zaidejams serveryje (renginiu forma).");
			return 1;
}
CMD:af_paimti(playerid,params[])
{
			if(!playerDB[playerid][admin]) return 1;
			//if(FALSE==false) return SendClientMessage(playerid,RED," * AFONDO NER");
			new kiek;
			if(sscanf(params,"d",kiek)){SendClientMessage(playerid,0xD9E916FF,"* Paimti pinigus is fondo: /af_paimti [kiek]"); return 1;}

			if(Server[afondas] < kiek || kiek < 0){SendInfoMessage(playerid,"Siandien administratoriu fonde tiek neturime."); return 1;}

			GivePlayerMoneyA(playerid,kiek); Server[afondas]-=kiek;
			SendInfoMessage(playerid,"Pinigai sekmingai nupyzdinti.");
			MLog(playerid,"Nupyzdino is afondo","i", kiek);
			
			return 1;
}
CMD:af_padeti(playerid,params[])
{
			if(!playerDB[playerid][admin]) return 1;
			//if(FALSE==false) return SendClientMessage(playerid,RED," * AFONDO NER");
			new kiek;
			if(sscanf(params,"d",kiek)){SendClientMessage(playerid,0xD9E916FF,"* Padeti pinigus i fondo: /af_padeti [kiek]"); return 1;}

			if(GetPlayerMoneyA(playerid) < kiek || kiek < 0){SendInfoMessage(playerid,"Tu tiek neturi."); return 1;}

			GivePlayerMoneyA(playerid,-kiek); Server[afondas]+=kiek;
			SendInfoMessage(playerid,"Pinigai sekmingai padeti");
			MLog(playerid,"Padejo i afonda","i", kiek);
			return 1;
}
CMD:kick(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 1;
	new vardas[128],prz[128];
	if(sscanf(params,"s[24]s[128]",vardas,prz)){SendInfoMessage(playerid,"Ismesti zaideja: /kick [dalis vardo/ID] [priezastis]"); return 1;}
	new id;
	if(IsNumeric(vardas))
	{
		id = strval(vardas);
		if (!IsPlayerConnected(id)){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	}
	else
	{
		id = GetPlayeridMid(vardas);
		if(GetPlayersCountByName(playerid,vardas)) return 1;
	}
	if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	if (playerDB[id][admin]){ SendInfoMessage(playerid,"Administratoriaus ismesti negalima."); return 1;}
	if(playerDB[id][authstate]==0 || IsPlayerNPC(id)) { SendInfoMessage(playerid,"Zaidejas dar jungiasi."); return 1;}
	
	new msg[128],adminname[MAX_PLAYER_NAME];
	GetPlayerName(id,vardas,sizeof(vardas));
	GetPlayerName(playerid,adminname,sizeof(adminname));

	format(msg,sizeof(msg),"[kick] %s iðmetë %s ið serverio (%s).",adminname,vardas,prz);
	SendClientMessageToAll(0xD9E916FF,msg);
	MLog(playerid,"Iskickino","ss",vardas,prz);
	format(msg,sizeof(msg),"Kick %s",vardas);
	MLog(playerid,msg,"s",prz);

	//TogglePlayerClock(playerid, true);
	//SetPlayerTime(playerid, 3, 33);

//"Kick %s","Ban %s", adminname,prz
	KickEx(id);
	return 1;
}
CMD:id(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 1;
	new vardas[128],prz[128];
	if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Parodyti zaidejo ID /id [vardo dalis]"); return 1;}
	new id = GetPlayeridMid(vardas);
	if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	format(prz,sizeof(prz),"Zaidejo %s ID %i",ReturnName(id),id);
	SendClientMessage(playerid,WHITE,prz);
	return 1;
}
CMD:lastkicks(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new vardux[128];
	if(sscanf(params,"s[128]",vardux)) return SendInfoMessage(playerid,"Naudojimas: /lastkicks [Vardas_Pavarde/ID]");
	new idas=INVALID_PLAYER_ID;
	if(IsNumeric(vardux)) idas = strval(vardux);
	if(idas != INVALID_PLAYER_ID) GetPlayerName(idas,vardux,MAX_PLAYER_NAME);
	
	new msg[128],msg2[128],msg3[128];
	format(msg,sizeof(msg),"Kick %s",vardux);
	format(msg2,sizeof(msg2),"Ban %s",vardux);
	format(msg3,sizeof(msg3),"PBan %s",vardux);
	Ataskaita(playerid,msg,msg2,msg3);//,"AC_Ban","AC_Kick");
	return 1;
}

CMD:takew(playerid,params[])
{
			if(!playerDB[playerid][admin]) return 1;
			new vardas[128];
			if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Atimti ginklus: /takew [dalis vardo]"); return 1;}
			new id = GetPlayeridMid(vardas);
			if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
			//ResetPlayerWeapons(id);
			ResetGunData(id);
			new messas[128];
			format(messas,128,"[TAKEW] Administratorius {B0E0E6}%s{FFFFFF} jums atëmë ginklus.",ReturnName(playerid));
			SendClientMessage(id, -1, messas);
			SendInfoMessage(playerid,"Ginklai atimti!");
			return 1;
}


CMD:taisykla(playerid,params[])
{
			#pragma unused params
			if(!playerDB[playerid][admin]) return 1;
			if(Taisyklz){
				Taisyklz=false;
				SendInfoMessage(playerid,"Uzdarei taisykla.");
				return 1;
			}
			else if(!Taisyklz)
			{
				Taisyklz=true;
				SendInfoMessage(playerid,"Atidarei taisykla.");
				return 1;
			}
			return 1;
}

CMD:akomandos(playerid,params[])
{
            #pragma unused params
			if(!playerDB[playerid][admin]) return 1;
			SendClientMessage(playerid, 0xD9E916FF, "* /a [tekstas] - skelbti");
			SendClientMessage(playerid, 0xD9E916FF, "* /g [tekstas] - skelbti per viduri ekrano");
			SendClientMessage(playerid, 0xD9E916FF, "* /visraktis - masinu visraktis");
			SendClientMessage(playerid, 0xD9E916FF, "* /skristi - gauti skraidancia kuprine");
			SendClientMessage(playerid, 0xD9E916FF, "* /gydyti - sutaiso masina ir pagydo tave");
			SendClientMessage(playerid, 0xD9E916FF, "* /range - Event Ginklai,ist,heal,skin per atstuma");
			SendClientMessage(playerid, 0xD9E916FF, "* // [tekstas] - rasyti i admin chata (kurio zaidejai nemato)");
			SendClientMessage(playerid, 0xD9E916FF, "* Administratoriaus komandos - zaidejo manipuliacija");
			SendClientMessage(playerid, 0xD9E916FF, "* /takew [dalis vardo] - atima ginklus");
			SendClientMessage(playerid, 0xD9E916FF, "* /freeze [dalis vardo] /unfreeze[dalis vardo] - susaldyti ar atitirpinti");
			SendClientMessage(playerid, 0xD9E916FF, "* /pzu [dalis vardo] - priziureti zaideja");
			SendClientMessage(playerid, 0xD9E916FF, "* /kick [dalis vardo] /ban [dalis vardo] /jail [dalis vardo] [sekundes] /pban");
			SendClientMessage(playerid, 0xD9E916FF, "* /oba,/komplektas,/komplektas1,/komplektas2,/komplektas3 - ginklai...");
			SendClientMessage(playerid, 0xD9E916FF, "* /boom - susprogdina masina /lastkicks [Vardas_Pavarde] - pamatyti paskutinius zaidejo kickus");
			SendClientMessage(playerid, 0xD9E916FF, "* /cheal - pataiso zaidejo masina /heal - pagydo zaideja");
			SendClientMessage(playerid, 0xD9E916FF, "* /tpmenu - svarbiausios vietos. /leistkeist - leisti zmogui pasikeisti nicka.");
			SendClientMessage(playerid, 0xD9E916FF, "* Eventu komandos: /spawngun /spawncar /spawncp /eventgun");
			SendClientMessage(playerid, 0xD9E916FF, "* Administratoriaus komandos (PAGE UP TO SEE ALL)");
			return 1;
}


CMD:ipsearch(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	if(!Pareigos(playerid,"Admin"))
		return SendInfoMessage(playerid, "Naudok komanda /accounts");
	new IP[128];
	//if(!Pareigos(playerid,"Emigracija")) return SendClientMessage(playerid,COLOR," * Sia komanda gali naudotis tik emigruojantis adminas!");
	if(sscanf(params,"s[24]",IP)){SendClientMessage(playerid, 0xD9E916FF, "* Rasti zaidejus pagal IP: /ipsearch [IP ADRESAS]"); return 1;}
	mysql_real_escape_string(IP, IP);
	new query[128];
	format(query,128,"SELECT `Name`,`Xp` FROM `Account` WHERE `IP` = '%s'",IP);
	mysql_function_query(SQL, query, true, "SQL_IpSearch", "i", playerid);
	return 1;
}

CMD:namesearch(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	if(!Pareigos(playerid,"Admin"))
		return SendInfoMessage(playerid, "Naudok komanda /accounts");
	new IP[128];
	//if(!Pareigos(playerid,"Emigracija")) return SendClientMessage(playerid,COLOR," * Sia komanda gali naudotis tik emigruojantis adminas!");
	if(sscanf(params,"s[24]",IP)){SendClientMessage(playerid, 0xD9E916FF, "* Rasti IP pagal varda: /namesearch [vardas]"); return 1;}
	new id = GetPlayeridMid(IP);
	if (id != INVALID_PLAYER_ID)
	{ 
		GetPlayerIp(id,IP,sizeof(IP));
		SendClientMessage(playerid,YELLOW,IP);
		return 1;
	}
	mysql_real_escape_string(IP, IP);
	new query[128];
	format(query,128,"SELECT `IP` FROM `Account` WHERE `Name` = '%s'",IP);
	mysql_function_query(SQL, query, true, "SQL_NameSearch", "i", playerid);
	return 1;
}

CMD:accounts(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new query[512];
	new namestr[24];
	if(sscanf(params,"s[24]",namestr)){SendClientMessage(playerid, 0xD9E916FF, "* Rasti zaidejo akauntus: /accounts [vardas]"); return 1;}
	new msg[256];
	format(msg,256, "Zaidejo %s akauntai:", namestr);
	SendClientMessage(playerid, YELLOW, msg);
	mysql_real_escape_string(namestr, namestr);
	new id = GetPlayeridMid(namestr);
	if (id != INVALID_PLAYER_ID)
	{ 
		new IP[24];
		GetPlayerIp(id,IP,sizeof(IP));
		format(query,512, "SELECT `Name`,`Xp`,`Ip` FROM Account WHERE Ip = '%s'", IP);
	}
	else
		format(query,512, "SELECT `Name`,`Xp`,`Ip` FROM Account WHERE Ip = (SELECT Ip FROM Account WHERE `Name`='%s')", namestr);
	mysql_function_query(SQL, query, true, "SQL_AccSearch", "i", playerid);
	return 1;
}

CMD:jail(playerid,params[])
{
			if(!playerDB[playerid][admin]) return 0;
			new vardas[128],laikas,reason[128];

			if(sscanf(params,"s[24]ds[128]",vardas,laikas,reason)){SendClientMessage(playerid, 0xD9E916FF, "* Pasodinti nusikalteli i kalejima: /jail [dalis vardo] [sekundes] [priezastis]"); return 1;}
			new id = GetPlayeridMid(vardas);
			if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio zaidejo nera"); return 1;}

			new msg[128];
			GetPlayerName(id,vardas,sizeof(vardas));
			if(laikas != 0) laikas += GetPlayerWantedLevel(id)*1000;
			SetPlayerWantedLevel(id,0);
			new x = GetFreeKamera(id);
			JailPlayer(id,Kameros[x][0],Kameros[x][1],Kameros[x][2],0,playerDB[playerid][kalejimo_laikas]*1000,0,3180.9961,-966.1835,293.3473,365.7195,0,true); 
			//if(random(2) == 0){ JailPlayer(id,3091.0691,-1507.0050,106.0223,0,laikas*1000,0,3180.9961,-966.1835,293.3473,365.7195,0,true); }
			//else { JailPlayer(id,3091.0193,-1525.4700,106.0223,0,laikas*1000,0,3180.9961,-966.1835,293.3473,365.7195,0,true); }
			playerDB[id][kalejimo_laikas] = laikas;
			if(laikas < 1) return SendInfoMessage(playerid,"[jail] Paleidote!");
			format(msg,sizeof(msg),"[jail] Ikalinote %s (%is) uz %s.",vardas,laikas,reason);
			SendClientMessage(playerid,0xD9E916FF,msg);
			format(msg,sizeof(msg)," * Jus buvote ikalintas %is uz %s administratoriaus {B0E0E6}%s{FFFFFF}",laikas,reason,ReturnName(playerid));
			SendClientMessage(id,0xD9E916FF,msg);
			MLog(playerid,"Jailino","sis",vardas,laikas,reason);
			return 1;
}

CMD:ban(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new vardas2[128],prz2[128],vardas[128],prz[128];
	if(sscanf(params,"s[24]s[128]",vardas2,prz2)){SendClientMessage(playerid, 0xD9E916FF, "* Baninti zaideja: /ban [dalis vardo] [priezastis]"); return 1;}
	mysql_real_escape_string(vardas2,vardas,_,256);
	mysql_real_escape_string(prz2,prz);
	new id;
	if(IsNumeric(vardas))
	{
		id = strval(vardas);
		if (!IsPlayerConnected(id)){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	}
	else
	{
		id = GetPlayeridMid(vardas);
		if(GetPlayersCountByName(playerid,vardas)) return 1;
	}
	if (id == INVALID_PLAYER_ID || IsPlayerNPC(id)) { SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	if (playerDB[id][admin]){ SendInfoMessage(playerid,"Administratoriaus ismesti negalima."); return 1;}
	//if(playerDB[id][authstate]==0) { SendInfoMessage(playerid,"Zaidejas dar jungiasi."); return 1;}
	new msg[128],adminname[MAX_PLAYER_NAME];
	GetPlayerName(id,vardas,sizeof(vardas));
	GetPlayerName(playerid,adminname,sizeof(adminname));
	//format(msg,sizeof(msg),"[ban] %s uzblokavo jus, nes jus %s",adminname,prz);
	TogglePlayerControllable(id,false);
	//SendClientMessage(id,0xD9E916FF,msg);
	new plrIP[16];
	new query[512];
	GetPlayerIp(id, plrIP, sizeof(plrIP));
	mysql_real_escape_string(prz,prz);
	new gangas = playerDB[id][pgang];
	format(query,sizeof(query),"INSERT INTO BANS (Vardas,IP,Priezastis,Adminas,Date,Gauja) VALUES ('%s','%s','%s','%s',NOW(),%i)",vardas,plrIP,prz,adminname,gangas);
	mysql_query(query);
	SendClientMessage(id, RED, " * Jus gavote BAN!");
	SendClientMessage(id, RED, " * Jei manote, jog ivyko klaida, tuomet spauskite mygtuka F8, kad pasidarytumete savo irodymus. Ju reikes ban apeliacijai.");
	format(msg,sizeof(msg),"[ban] %s uþblokavo %s ( %s )",adminname,vardas,prz);
	SendClientMessageToAll(0xD9E916FF,msg);
	MLog(playerid,"Uzbanino","ss",vardas,prz);
	format(msg,sizeof(msg),"Ban %s",vardas);
	MLog(playerid,msg,"s",prz);
	KickEx(id);
//"Kick %s","Ban %s", adminname,prz
	return 1;
}



CMD:pban(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new vardas2[128],prz2[128],vardas[128],prz[128];
	if(sscanf(params,"s[24]s[128]",vardas2,prz2)){SendInfoMessage(playerid,"Uzdeti laukiama bana: /pban [pilnas vardas] [priezastis]"); return 1;}
	new adminname[MAX_PLAYER_NAME];
	mysql_real_escape_string(vardas2,vardas);
	mysql_real_escape_string(prz2,prz);
	GetPlayerName(playerid,adminname,sizeof(adminname));
	new query[512];
	format(query,sizeof(query),"SELECT * FROM Pending WHERE Name='%s'",vardas);
	mysql_function_query(SQL, query, true, "SQL_PendingCheck", "iss", playerid,vardas,formatwithoutLT(prz));
	return 1;
}

CMD:freeze(playerid,params[])
{

	if(!playerDB[playerid][admin]) return 0;
	new vardas[128];
	if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Uzsaldyti zaideja: /freeze [nicko dalis]"); return 1;}
	new id = GetPlayeridMid(vardas);
	if (id == INVALID_PLAYER_ID){SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	TogglePlayerControllable(id,false);
	SendInfoMessage(playerid,"Zaidejas uzrakintas!");
	return 1;
}
CMD:unfreeze(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new vardas[128];
	if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Atitirpinti zaideja: /unfreeze [nicko dalis]"); return 1;}
	new id = GetPlayeridMid(vardas);
	if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	TogglePlayerControllable(id,true);
	SendInfoMessage(playerid,"Zaidejas atrakintas!");
	return 1;
}
CMD:to(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 1;
	if(gPlayerDialog[playerid]!= -1)
	{
		return SendClientMessage(playerid,BLUE," * Uzdaryk dialoga.");
	}
    new vardas[128];
	if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Keliauti pas (be masinos): /to [dalis vardo]"); return 1;}
	new id = GetPlayeridMidEx(vardas);
	if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	backInterior[playerid] = GetPlayerInterior(playerid);
	backWorld[playerid] = GetPlayerVirtualWorld(playerid);
	GetPlayerPos(playerid, backCoords[playerid][0], backCoords[playerid][1], backCoords[playerid][2]);
	SetPlayerInterior(playerid,GetPlayerInterior(id));
	SetPlayerVirtualWorld(playerid,GetPlayerVirtualWorld(id));
	new Float:tempcoo[3];
	GetPlayerPos(id,tempcoo[0],tempcoo[1],tempcoo[2]);
	SetPlayerPoz(playerid,tempcoo[0],tempcoo[1],tempcoo[2]);
	SetCameraBehindPlayer(playerid);
	if(FPS[playerid])  AttachCameraToObject(playerid, FirstPersonObject[playerid]);
	return 1;
}
CMD:back(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 1;
	if(backCoords[playerid][0] == 0.0)
		return SendInfoMessage(playerid, "Siuo metu komandos naudoti negali");
	SetPlayerInterior(playerid, backInterior[playerid]);
	SetPlayerVirtualWorld(playerid, backWorld[playerid]);
	SetPlayerPoz(playerid, backCoords[playerid][0], backCoords[playerid][1], backCoords[playerid][2]);
	return 1;
}
CMD:tokord(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 1;
	new Float:Coo[4],int;
	if(sscanf(params,"p<,>I(0)fffF(0.0)",int,Coo[0],Coo[1],Coo[2],Coo[3])) return SendClientMessage(playerid,COLOR,"/tokord [int] [x] [y] [z] [a]");
	if(GetPlayerVehicleID(playerid)) SetVehiclePoz(GetPlayerVehicleID(playerid),Coo[0],Coo[1],Coo[2]),SetVehicleZAngle(GetPlayerVehicleID(playerid),Coo[3]);
	else SetPlayerPoz(playerid,Coo[0],Coo[1],Coo[2]),SetPlayerFacingAngle(playerid,Coo[3]);
	SetPlayerInterior(playerid,int);
	return 1;
}

CMD:get(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 1;
    new vardas[128];
	if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Gauti zaideja: /get [dalis vardo]"); return 1;}

	new id = GetPlayeridMidEx(vardas);
	if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio zaidejo nera"); return 1;}
	if (playerDB[id][ikalintas]) {SendInfoMessage(playerid,"Nusikaltelis kalejime."); return 1;}
	if(playerDB[id][suristas] || playerDB[id][ant] ) { SendInfoMessage(playerid,"Zaidejas surakintas/suristas"); return 1; }
	if(playerDB[id][psratasvydis]) return SendInfoMessage(playerid,"Zaidejas dazasvydyje");
	SetPlayerInterior(id,GetPlayerInterior(playerid));
	SetPlayerVirtualWorld(id,GetPlayerVirtualWorld(playerid));
	new Float:tempcoo[3];
	GetPlayerPos(playerid,tempcoo[0],tempcoo[1],tempcoo[2]);
	SetPlayerPoz(id,tempcoo[0],tempcoo[1],tempcoo[2]+1);
	SetCameraBehindPlayer(id);
	if(FPS[id])  AttachCameraToObject(id, FirstPersonObject[id]);
	return 1;

}
CMD:kill(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 1;
	new vardas[128];
	if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Nuzudyti zaideja: /kill [dalis vardo]"); return 1;}

	new id = GetPlayeridMid(vardas);
	if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	new mess[128],rec[MAX_PLAYER_NAME];
	GetPlayerName(id,rec,sizeof(rec));
	format(mess,sizeof(mess),"Nuzudete %s!",rec);
	SendInfoMessage(playerid,mess);
	new messas[128];
	format(messas,128,"[KILL] Jus nuþudë administratorius {B0E0E6}%s{FFFFFF}.",ReturnName(playerid));
	SendClientMessage(id, -1, messas);
	MLog(playerid,"Nukilino","s",rec);
	SetPlayerHealth(id,0);
	return 1;
}

CMD:pzu(playerid,params[])
{
	if(!playerDB[playerid][admin] && !IsPlayerAdmin(playerid)) return 1;
	EnterWarn{playerid}=0;
	if(!galikast[playerid]) return 1;
	if(GetPVarInt(playerid, "PSpectating")) 
	{
		EndSpectate(playerid);
	}
	else 
	{
		
		new vardas[24];
		if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Priziureti zaideja: /pzu [dalis vardo arba ID]"); return 1;}
		new id;
		if(IsNumeric(vardas))
		{
			id = strval(vardas);
			if (!IsPlayerConnected(id)){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		}
		else
		{
			id = GetPlayeridMidEx(vardas);
		}
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		if (id == playerid){ SendInfoMessage(playerid,"Pasiziurek i veidrodi :D"); return 1;}
		if(PlayerSpectated[id] != -1) 
		{ 
			new msg[128];
			format(msg,128,"Si zaideja jau priziuri~p~ %s",ReturnName(PlayerSpectated[id]));
			SendInfoMessage(playerid,msg); 

			format(msg,128,"~p~%s~w~ bando priziureti si zaideja",ReturnName(playerid));
			SendInfoMessage(PlayerSpectated[id] ,msg); 
			return 1; 
		}
		StartSpectate(playerid, id);
	}
	return 1;
}

CMD:gydyti(playerid,params[])
{
            #pragma unused params
			if(!playerDB[playerid][admin]) return 1;
			if(IsPlayerInAnyVehicle(playerid))
			{
				//SetVehicleHealth(GetPlayerVehicleID(playerid),1000);
				RepairVehicle(GetPlayerVehicleID(playerid));
			}
			SetPlayerHealth(playerid,100);
			SetPlayerArmour(playerid,100);
			SendInfoMessage(playerid,"Gyvybiu kodas");
			return 1;
}
CMD:skristi(playerid,params[])
{
            #pragma unused params
			if(!playerDB[playerid][admin]) return 1;
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USEJETPACK);
			SendInfoMessage(playerid,"Gavote Jet-Pack");
			return 1;
}
CMD:komplektas3(playerid,params[])
{
            #pragma unused params
			if(!playerDB[playerid][admin]) return 1;
			//ResetPlayerWeapons(playerid);
			GivePlayerWeaponEx(playerid,1,10);
			GivePlayerWeaponEx(playerid,5,1);
			GivePlayerWeaponEx(playerid,16,100000);
			GivePlayerWeaponEx(playerid,23,100000);
			GivePlayerWeaponEx(playerid,27,100000);
			GivePlayerWeaponEx(playerid,31,100000);
			GivePlayerWeaponEx(playerid,32,100000);
			GivePlayerWeaponEx(playerid,34,100000);
			//GivePlayerWeaponEx(playerid,46,100000);
			GivePlayerWeaponEx(playerid,43,100000);
			SendInfoMessage(playerid,"Ginklus naudokite ismintingai !");
			return 1;
}
CMD:komplektas1(playerid,params[])
{
            #pragma unused params
			if(!playerDB[playerid][admin]) return 1;
			//ResetPlayerWeapons(playerid);
			GivePlayerWeaponEx(playerid,3,10);
			GivePlayerWeaponEx(playerid,8,1);
			GivePlayerWeaponEx(playerid,24,100000);
			GivePlayerWeaponEx(playerid,25,100000);
			GivePlayerWeaponEx(playerid,32,100000);
			GivePlayerWeaponEx(playerid,30,100000);
			GivePlayerWeaponEx(playerid,33,100000);
			//GivePlayerWeaponEx(playerid,46,100000);
			GivePlayerWeaponEx(playerid,43,100000);
			SendInfoMessage(playerid,"Ginklus naudokite ismintingai !");
			return 1;
}
CMD:komplektas2(playerid,params[])
{
            #pragma unused params
			if(!playerDB[playerid][admin]) return 1;
			//ResetPlayerWeapons(playerid);
			GivePlayerWeaponEx(playerid,1,10);
			GivePlayerWeaponEx(playerid,9,1);
			GivePlayerWeaponEx(playerid,23,100000);
			GivePlayerWeaponEx(playerid,27,100000);
			GivePlayerWeaponEx(playerid,31,100000);
			GivePlayerWeaponEx(playerid,32,100000);
			GivePlayerWeaponEx(playerid,34,100000);
			//GivePlayerWeaponEx(playerid,46,100000);
			GivePlayerWeaponEx(playerid,43,100000);
			SendInfoMessage(playerid,"Ginklus naudokite ismintingai !");
			return 1;
}

CMD:boom(playerid,params[])
{
            #pragma unused params
			if(!playerDB[playerid][admin]) return 1;
			new vehicleid = GetPlayerVehicleID(playerid);
			SetVehicleHealth(vehicleid,200.0);
			return 1;

}
CMD:a(playerid,params[])
{
			if(!playerDB[playerid][admin]) return 1;
			new textax[256];
			if(sscanf(params,"s[256]",textax)){SendInfoMessage(playerid,"Naudojimas: /a [tekstas]"); return 1;}
			new zin[256],name[MAX_PLAYER_NAME];
			GetPlayerName(playerid,name,MAX_PLAYER_NAME);
			if(playerDB[playerid][lytis] == 2)
				format(zin,sizeof(zin), "Administratorë %s || %s",name,textax);
			else
				format(zin,sizeof(zin),"Administratorius %s || %s",name,textax);
			SendClientMessageToAllEx(ADMIN_COLOR,zin);
			return 1;
}
CMD:plaukti(playerid,params[])
{
            #pragma unused params
			if(!playerDB[playerid][admin]) return 1;

			ApplyAnimation(playerid,"SWIM","SWIM_crawl",4.1,1,1,1,1,1);
			return 1;
}
CMD:g(playerid,params[])
{
            if(!playerDB[playerid][admin]) return 1;
            new zin[256],textax[128];
			if(sscanf(params,"s[128]",textax)){SendInfoMessage(playerid,"Naudojimas: /ag [tekstas]"); return 1;}
			format(zin,sizeof(zin),"~n~~n~~n~~n~~n~~n~~n~~n~%s",textax); // /ag 
			GameTextForAll(textax, 10000, 3 );
			return 1;
}
CMD:arsandeliai(playerid,params[])
{
            if(!playerDB[playerid][admin]) return 1;
			if (IsSandeliai()){
				GameTextForAll("Sandeliai", 10000, 3 );
			}

CMD:testloterija(playerid,params[])
{
	#pragma unused params
	if(!playerDB[playerid][admin] && !IsPlayerAdmin(playerid)) return 1;
	SendClientMessage(playerid,0x33CCFFFF,"[testloterija] Running 3000 simulations, please wait...");
	TestLoterija(playerid);
	return 1;
}
			else {
				GameTextForAll("Ne Sandeliai", 10000, 3 );
			}
			return 1;
}
CMD:komplektas(playerid,params[])
{
			#pragma unused params
			if(!playerDB[playerid][admin]) return 1;
			//ResetPlayerWeapons(playerid);
			GivePlayerWeaponEx(playerid,24,100000);
			GivePlayerWeaponEx(playerid,32,100000);
			//GivePlayerWeaponEx(playerid,46,100000);
			GivePlayerWeaponEx(playerid,34,100000);
			GivePlayerWeaponEx(playerid,6,1);
			SendInfoMessage(playerid,"Ginklus naudokite ismintingai !");
			return 1;
}
CMD:clearchat(playerid,params[])
{
	if(!playerDB[playerid][admin]) return SendClientMessage(playerid,COLOR," * Si komanda tik administratoriams ;)");
	new count;
	if (sscanf(params, "d",count))
	{
		SendClientMessage(playerid,WHITE,"* Naudojimas: /clearchat [1-100]");
		return 1;
	}
	if(count < 1 || count > 100) return SendClientMessage(playerid,WHITE,"* Naudojimas: /clearchat [1-100]");
	for(new x;x<count;x++) SendClientMessageToAll(-1,"");
	SendClientMessage(playerid,-1," * Pravalei!");
	return 1;
}

CMD:respawn(playerid,params[])
{
		#pragma unused params
    	if(!playerDB[playerid][admin]){SendClientMessage(playerid,WHITE,"* *** Si komanda tik administratoriams. *** *"); return 1;}
		new v = GetClosestVehicleid(playerid,19.0,GetPlayerVehicleID(playerid));
		if(!v || v==INVALID_VEHICLE_ID) return SendInfoMessage(playerid,"Masina per toli!");
		new playeridx;
		if(GetPlayerFromCarlistID(v,playeridx) || IsVagiuCar(v) || IsVairavimoMokyklosCar(v)) return SendInfoMessage(playerid,"~r~Respawninnt gali tik DARBINIUS automobilius.");
	 	vehicleDB[v][lastpos][0]=0;
		vehicleDB[v][lastpos][1]=0;
		vehicleDB[v][lastpos][2]=0;
		SendInfoMessage(playerid,"Respawned.");
		//SetVehicleToRespawn(v);
		foreach(Player,i)
		{
			if(PlayerCar[i]==v)
			{
				DestroyOldCar(i); 
				return 1;
			}
		}
		//DestroyVehicle(v);
		if(VehicleSpawned[v]== 1)
		{
			spawnedvehs--;
			VehicleSpawned[v]=0;
			DestroyVehicle(v);
			return 1;
		}
		SetVehicleToRespawn(v);
		return 1;

}

CMD:skin(playerid,params[])
{
    	if(!playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda tik administratoriams"); return 1;}
		new vardas[128],price;
		if (sscanf(params, "s[24]d",vardas,price))
		{
			SendInfoMessage(playerid,"Naudojimas: /skin [vardas] [ID]");
			new rubai[320];
			new x = 0;
			for(new i;i<312;i++) if(i != 74)
			{
				rubai[x]=i;
				x++;
			}
			//galikast[playerid]=false;
			//SetTimerEx("GaliKast",1000,0,"i",playerid);
			ShowModelSelectionMenuEx(playerid, rubai, x, "Pasirinkite skina", GUI_CHOOSESKIN, 0.0, 0.0, 0.0, 1.0);//, Float:mZoom = 1.0, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899 , tdSelectionColor = 0xFFFF00AA);
			return 1;
		}
		new id = GetPlayeridMid(vardas);
		if(price > 311) return 1;
		if(id != INVALID_PLAYER_ID && GetPlayerState(id) == PLAYER_STATE_ONFOOT) SetPlayerSkin(id,price);
		return 1;
}
CMD:skinat(playerid,params[])
{
    	if(!playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda tik administratoriams"); return 1;}
		new vardas[128];
		if (sscanf(params, "s[24]",vardas))
		{
			SendInfoMessage(playerid,"Naudojimas: /skinat [vardas]");
			return 1;
		}
		new id = GetPlayeridMid(vardas);
		if(id != INVALID_PLAYER_ID) SetPlayerSkin(id,playerDB[id][drabuziai]);
		return 1;
}
CMD:log(playerid,params[])
{
    	if(!playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda tik administratoriams"); return 1;}
		if(!playerDB[playerid][logina])
		{
			SendInfoMessage(playerid,"Sekmingai pradejai logint!");
			playerDB[playerid][logina]=true;
			TextDrawShowForPlayer(playerid,LogTD);
		}
		else
		{
		    SendInfoMessage(playerid,"Baigei logint!");
			playerDB[playerid][logina]=false;
			TextDrawHideForPlayer(playerid,LogTD);
		}
		return 1;
}

CMD:aevent(playerid,params[])
{
	new Event[128],DalyviaiX;
	if(!playerDB[playerid][admin]) return 0;
	if(Server[EventON])
	{
		SendClientMessageToAll(ORANGE," * Eventas nutrauktas!");
		Server[EventON]=false;
	}
	else
	{
		new msg[128];
		if(sscanf(params,"is[128]",DalyviaiX,Event)) return SendInfoMessage(playerid,"Naudojimas: /event [dalyviu skaicius(0 - neribojamas)] [pavadinimas]");
		Server[EventNr]=1+random(99);
		eventid++;
		if(DalyviaiX==0)
		{
			if(playerDB[playerid][lytis] == 2)
				format(msg,sizeof(msg)," * Administratorë %s rengia eventà \"%s\"! Raðykite /event %i",ReturnName(playerid),Event,Server[EventNr]);
			else
				format(msg,sizeof(msg)," * Administratorius %s rengia eventà \"%s\"! Raðykite /event %i",ReturnName(playerid),Event,Server[EventNr]);
			DalyviaiX=-1;
		}
		else if(DalyviaiX > 0)
		{
			if(playerDB[playerid][lytis] == 2)
				format(msg,sizeof(msg)," * Administratorë %s rengia eventà \"%s\". Dalyviø: %i! Raðykite /event %i",ReturnName(playerid),Event,DalyviaiX,Server[EventNr]);
			else
				format(msg,sizeof(msg)," * Administratorius %s rengia eventà \"%s\". Dalyviø: %i! Raðykite /event %i",ReturnName(playerid),Event,DalyviaiX,Server[EventNr]);
		}
		else SendInfoMessage(playerid,"Klaida");
		
		SendClientMessageToAll(ORANGE,msg);
		Server[EventON]=true;	
		GetPlayerPos(playerid,Server[EventCoo][0],Server[EventCoo][1],Server[EventCoo][2]);
		Server[EventInt]=GetPlayerInterior(playerid);
		Server[EventVW]=GetPlayerVirtualWorld(playerid);
		Server[EventTime]=60;
		Server[Dalyviai]=DalyviaiX;
		
	}
	return 1;
}
CMD:stats(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new zaidejas[128];
	if(sscanf(params,"s[24]",zaidejas)) return SendInfoMessage(playerid,"Naudojimas: /stats [Vardo_Dalis]");
	new id = GetPlayeridMid(zaidejas);
	if(id == INVALID_PLAYER_ID) return SendInfoMessage(playerid,"Tokio zaidejo nera!");
	Stats(id,playerid);
	return 1;
}

CMD:tele(playerid,params[])
{
       	if(!playerDB[playerid][admin]) return SendInfoMessage(playerid,"Si komanda administratoriams.");
		new name[128];
		if (sscanf(params, "s[24]",name)) {SendInfoMessage(playerid,"/tele [vardas]"); return 1;}
		new idas = GetPlayeridMid(name);
		if(!IsPlayerConnected(idas)){SendInfoMessage(playerid,"Zaidejas neprisijunges"); return 1;}
		new Float: coo[3];
		GetPlayerPos(playerid,coo[0],coo[1],coo[2]);
		new masinx = GetPlayerVehicleID(idas);
		SetVehiclePoz(masinx,coo[0],coo[1],coo[2]+5);
		SetPlayerInterior(idas,GetPlayerInterior(playerid));
        LinkVehicleToInterior(masinx, GetPlayerInterior(playerid));
		SetPlayerVirtualWorld(idas,GetPlayerVirtualWorld(playerid));
		SetVehicleVirtualWorld(masinx,GetPlayerVirtualWorld(playerid));
		SendInfoMessage(playerid,"Atitelinai!");
		return 1;
}

CMD:cartp(playerid,params[])
{
	if(!playerDB[playerid][admin]) return SendInfoMessage(playerid,"Si komanda administratoriams.");
	if(gPlayerDialog[playerid]!= -1)
	{
		return SendClientMessage(playerid,BLUE," * Uzdaryk dialoga.");
	}
	new name[128];
	if (sscanf(params, "s[24]",name)) {SendInfoMessage(playerid,"Keliauti pas zaideja su masina /cartp [vardas]"); return 1;}
	new idas = GetPlayeridMid(name);
	if(!IsPlayerConnected(idas)){SendInfoMessage(playerid,"Zaidejas neprisijunges"); return 1;}
	new Float:coo[3];
	GetPlayerPos(idas,coo[0],coo[1],coo[2]);
	new masinx = GetPlayerVehicleID(playerid);
	SetVehiclePoz(masinx,coo[0],coo[1],coo[2]+5);
	SetPlayerInterior(playerid ,GetPlayerInterior(idas));
	LinkVehicleToInterior(masinx, GetPlayerInterior(idas));
	SetPlayerVirtualWorld(playerid,GetPlayerVirtualWorld(idas));
	SetVehicleVirtualWorld(masinx,GetPlayerVirtualWorld(idas));
	SendInfoMessage(playerid,"Atsitelinai!");
	return 1;
}

//Vartai adminams
CMD:aoras(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][admin])
	{
		MoveObject(oras, 1961.446045, -2189.604248, 8.171829, 1.0001);
	}
	return 1;
}
CMD:uoras(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][admin])
	{
		MoveObject(oras, 1961.383423, -2189.649658, 15.320267, 1.0001);
	}
	return 1;
}

CMD:avestuves(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][admin] || playerDB[playerid][prez] || playerDB[playerid][specialybe]==35)
	{
		MoveObject(vestuves,834.447205, -1828.492432, 7.608822, 1.0001);
	}
	return 1;
}
CMD:uvestuves(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][admin] || playerDB[playerid][prez] || playerDB[playerid][specialybe]==35 )
	{
		MoveObject(vestuves,834.436035, -1828.537842, 13.997225, 1.0001);
	}
	return 1;
}

CMD:muzikaoff(playerid,params[])
{
	#pragma unused params
	if(!playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda tik administratoriams."); return 1;}
	//if(!Pareigos(playerid,"DJ")) return SendInfoMessage(playerid,"Jus neturite teises leisti muzikos!");
	g_RadioON=false;
  	foreach(Player,id)
	{
		if(playerDB[id][klausoisadmin]!=0)
		{
			StopAudioStreamForPlayer(id);
			playerDB[id][klausoisadmin]=0;
		}
	}
	SendInfoMessage(playerid,"Sekmingai isjungei muzona!");
	return 1;
}

CMD:gatesasas(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	OpenCells();
	return 1;
}
CMD:ids(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	ShowPlayerDialog(playerid,0,DIALOG_STYLE_MSGBOX,"Darbu IDs","ID - Darbas\n\n2) Mediku\n3) Transporto\n5) Kroviniu Transporto\n6) Mechaniku\n34) N.Turto agentu\n66) Gaisrininku\n70) Autoklubo\n80) Teisesaugos\n50) Skelbeju\n98) Baikeriu\n90) Dealeriu\n58) Vagiu\n60) Inkasatoriu","Iseiti","");
	return 1;
}
CMD:leistkeist(playerid,params[])
{
	//if(!IsPlayerAdmin(playerid)) return 0;
	if(!playerDB[playerid][admin]) return 0;
	new vardas[128];
	if(sscanf(params,"s[24]",vardas)) return SendClientMessage(playerid,COLOR," * Naudojimas: /leistkeist [Vardas_Pavarde]");
	new id = GetPlayeridMid(vardas);
	if(id == INVALID_PLAYER_ID || !IsPlayerConnected(id) || playerDB[id][authstate] == 0) return SendClientMessage(playerid,RED," * Zaidejas neprisijunges!");
	if(GetPlayerScore(id) > 2000)
	{
		if(!Pareigos(playerid,"Admin") && !Pareigos(playerid,"Admin2")) return SendInfoMessage(playerid,"Sis zaidejas turi per daug xp, jam negali leist pasikeisti vardo.");
	}
	SendClientMessage(playerid,COLOR," * Leidai zmogui pasikeisti varda!");
	ShowPlayerDialog(id,88,DIALOG_STYLE_INPUT,"Vardo keitimas","Demesio! Jusu vardas musu serveryje netinkamas.\nJusu Vardas turi buti Vardas_Pavarde formatu.\nIveskite pageidaujama varda savo veikejui.\nVardas gali buti lietuviskas arba angliskas.","Ok","Ok");
	return 1;
}

CMD:fixcar(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new name[24],kelinta;
	if(sscanf(params,"s[24]d",name,kelinta)) return SendClientMessage(playerid,COLOR," * Naudojimas: /fixcar [Vardas] [Kelinta masina]");
	new i = GetPlayeridMid(name);
	if(i == INVALID_PLAYER_ID || !IsPlayerConnected(i)) return SendClientMessage(playerid,COLOR," * Tokio zaidejo nera.");
	if(kelinta < 1 || kelinta > 3) return SendClientMessage(playerid,RED," * Masinos nr nuo 1 iki 3.");
	new Float:Coo[4];
	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	GetPlayerFacingAngle(playerid,Coo[3]);
	new vw=GetPlayerVirtualWorld(playerid);
	if(kelinta == 1)
	{
		if(Carlist[i][Typ] != -1 && Carlist[i][Carid] > 0)
		{
			Carlist[i][X]=Coo[0]; 
			Carlist[i][Y]=Coo[1]; 
			Carlist[i][Z]=Coo[2]; 
			Carlist[i][Rotation]=Coo[3];
			SetVehiclePos(Carlist[i][Carid],Carlist[i][X],Carlist[i][Y],Carlist[i][Z]);
			SetVehicleZAngle(Carlist[i][Carid],Carlist[i][Rotation]);
			SetVehicleVirtualWorld(Carlist[i][Carid],vw);
			vehicleDB[Carlist[i][Carid]][rankinis]=false;
		}
		else SendClientMessage(playerid,COLOR," * Masina neegzistuoja.");
	}
	else if(kelinta == 2)
	{
		if(Carlist2[i][Typ] != -1 && Carlist2[i][Carid] > 0)
		{
			Carlist2[i][X]=Coo[0]; 
			Carlist2[i][Y]=Coo[1]; 
			Carlist2[i][Z]=Coo[2]; 
			Carlist2[i][Rotation]=Coo[3];
			SetVehiclePos(Carlist2[i][Carid],Carlist2[i][X],Carlist2[i][Y],Carlist2[i][Z]);
			SetVehicleZAngle(Carlist2[i][Carid],Carlist2[i][Rotation]);
			SetVehicleVirtualWorld(Carlist2[i][Carid],vw);
			vehicleDB[Carlist2[i][Carid]][rankinis]=false;
		}
		else SendClientMessage(playerid,COLOR," * Masina neegzistuoja.");
	}
	else if(kelinta == 3)
	{
		if(Carlist3[i][Typ] != -1 && Carlist3[i][Carid] > 0)
		{
			Carlist3[i][X]=Coo[0]; 
			Carlist3[i][Y]=Coo[1]; 
			Carlist3[i][Z]=Coo[2]; 
			Carlist3[i][Rotation]=Coo[3];
			SetVehiclePos(Carlist3[i][Carid],Carlist3[i][X],Carlist3[i][Y],Carlist3[i][Z]);
			SetVehicleZAngle(Carlist3[i][Carid],Carlist3[i][Rotation]);
			SetVehicleVirtualWorld(Carlist3[i][Carid],vw);
			vehicleDB[Carlist3[i][Carid]][rankinis]=false;
		}
		else SendClientMessage(playerid,COLOR," * Masina neegzistuoja.");
	}
	return 1;
}

CMD:vmvartai(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	if(!VMVartaiOpen)
	{
		RotateObject(vmvartai,0, 10 ,270);
		VMVartaiOpen=true;
	}
	else
	{
		RotateObject(vmvartai,0, 90 ,270);
		VMVartaiOpen=false;
	}
	// posX="1811.8243408203" posY="-1886.7038574219" posZ="13.314064025879" rotX="0" rotY="90.750183105469" rotZ="270.24975585938"
	return 1;
}
CMD:int(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new vid;
	if(sscanf(params,"i",vid)) return SendClientMessage(playerid,RED," /interjerai [0-30]");
	if(vid < 0 || vid > 30) return SendClientMessage(playerid,RED,"* Ner tokio!");
	SetPlayerPoz(playerid,Inter[ vid ][ IntX ],Inter[ vid ][ IntY ],Inter[ vid ][ IntZ ]);
	SetPlayerInterior(playerid,Inter[ vid ][ Int ]);
	return 1;
}
CMD:tovagiucar(playerid, params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new p = strval(params);
	new car = 0;
	switch(p)
	{
		case 0: car = dune;
		case 1: car = club;
		case 2: car = turismo;
		case 3: car = hotknife;
		case 4: car = bloodring;
		case 5: car = voodoo;
		case 6: car = esperanto;
		case 7: car = previon;
		case 8: car = romero;
		case 9: car = hotring;
	}
	new Float:Coo[3];
	GetVehiclePos(car,Coo[0],Coo[1],Coo[2]);
	SetPlayerPoz(playerid, Coo[0],Coo[1],Coo[2]);
	return 1;
}
CMD:range(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new Float:range,Float:Coo[3],veiksmas[128],stat1,stat2;
	if(sscanf(params,"fs[128]I(-1)I(-1)",range,veiksmas,stat1,stat2))
	{
		SendClientMessage(playerid,ORANGE,"/range [atstumas] (Ginklas,Heal,Cheal,Ist,Skin,Takew,Respawn,Freeze,Unfreeze,Car,Nos)");
		/*
		SendClientMessage(playerid,ORANGE,"/range [atstumas] Ginklas [ginklo id] [kulkos]");
		SendClientMessage(playerid,ORANGE,"/range [atstumas] Heal [gyvybes] [armour]");
		SendClientMessage(playerid,ORANGE,"/range [atstumas] Cheal [gyvybes] ");
		SendClientMessage(playerid,ORANGE,"/range [atstumas] Ist");
		SendClientMessage(playerid,ORANGE,"/range [atstumas] Skin [skin id]");
		SendClientMessage(playerid,ORANGE,"/range [atstumas] Takew");
		*/
		return SendInfoMessage(playerid,"/range [atstumas] [veiksmas]");
	}
	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	if(range < 1.0 || range > 300.0) return SendInfoMessage(playerid,"Atstumas nuo 1 iki 300!");
	
	if(strcmp(veiksmas,"Nos",true)==0)
	{
		foreach(Player,id)
		{
			if(stat1 == -1) stat1=100;
			if(stat2 == -1) stat2=100;
			if(stat1 < 1 || stat1 > 100 || stat2 < 0 || stat2>100) return SendClientMessage(playerid,ORANGE,"/range [atstumas] Heal (hp) (armour)");
			
			if(IsPlayerInRangeOfPointEx(range,id,Coo[0],Coo[1],Coo[2]) && GetPlayerState(id) != PLAYER_STATE_SPECTATING)
			{
				if(GetPlayerState(id) == PLAYER_STATE_DRIVER) 
				{
					new veh = GetPlayerVehicleID(id);
					AddVehicleComponent(veh,1010);
				}
			}
		}

	}
	else if(strcmp(veiksmas,"Ginklas",true)==0)
	{
		if(stat1 == -1) return SendClientMessage(playerid,ORANGE,"/range [atstumas] Ginklas [ginklo id]");
		if(stat1 < 1 || stat1 > 46) return SendClientMessage(playerid,ORANGE,"Sio ginklo duoti negalima!");
		switch(stat1)
		{
			case 0,19,20,21,28,32,35,36,38,44,45: return SendClientMessage(playerid,ORANGE,"Sio ginklo duoti negalima!");
		}
		foreach(Player,id)
		{
			if(IsPlayerInRangeOfPointEx(range,id,Coo[0],Coo[1],Coo[2]) && GetPlayerState(id)!=PLAYER_STATE_DRIVER && GetPlayerState(id) != PLAYER_STATE_SPECTATING  && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(id))
			{
				DeletePlayerWeapon(id,stat1);
				GivePlayerWeaponEx(id,stat1,100000);
			}
		}
	}
	
	else if(strcmp(veiksmas,"Car",true)==0)
	{
		if(stat1 < 400 || stat1 > 611) return SendClientMessage(playerid,ORANGE,"/range [atstumas] Car [modelis 400-611] (spalva 0-255)");
		if(stat1 == 471) return SendInfoMessage(playerid,"Nebuk grincas");
		//if(stat2 == -1) stat2=223;
		if(stat2 < -1 || stat2 > 255) return SendClientMessage(playerid,ORANGE,"/range [atstumas] Car [modelis 400-611] (spalva 0-255)");
		foreach(Player,id)
		{
			if(IsPlayerInRangeOfPointEx(range,id,Coo[0],Coo[1],Coo[2]) && GetPlayerState(id)!=PLAYER_STATE_SPECTATING && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(id))
			{
				/*new Float:oldrida = 0.0;
				if(PlayerCar[id] != -1 && GetVehicleModel(PlayerCar[id]) == stat1)
					oldrida = vehicleDB[PlayerCar[id]][rida];*/

				DestroyOldCar(id);
				_PlayerTeleporting[id]=7;
				new col;
				if(stat2 == -1) col = random(255);
				else col=stat2;
				PlayerCar[id] = CreateVehicle(stat1,0.0,0.0,0.0,0.0,col,1,-1);
				OnVehicleSpawn(PlayerCar[id]);
				SetVehicleNumberPlate(PlayerCar[id],"EVENT");
				SetVehicleToRespawn(PlayerCar[id]);
				SetVehicleNumberPlate(PlayerCar[id],"EVENT");
				//SetPVarInt(id, "iseventcar", 1);
				//if(oldrida > 0)
				//	vehicleDB[PlayerCar[id]][rida]=oldrida;
				vehicleDB[PlayerCar[id]][rida]=0.0;
				vehicleDB[PlayerCar[id]][gas]=100.0;
				vehicleDB[PlayerCar[id]][energy]=50.0;
				vehicleDB[PlayerCar[id]][OldHP]=1000.0;
				vehicleDB[PlayerCar[id]][norida]=1;
				FadeColorForPlayer(id,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,10,5);
				TogglePlayerControllable(id,false);
				Stop(id);
				SendClientMessage(id,GREEN," * Gavote evento automobili.");
				playerInEventCar[id]=2;
				
			}
		}
	}
	else if(strcmp(veiksmas,"Heal",true)==0)
	{
		foreach(Player,id)
		{
			if(stat1 == -1) stat1=100;
			if(stat2 == -1) stat2=100;
			if(stat1 < 1 || stat1 > 100 || stat2 < 0 || stat2>100) return SendClientMessage(playerid,ORANGE,"/range [atstumas] Heal (hp) (armour)");
			
			if(IsPlayerInRangeOfPointEx(range,id,Coo[0],Coo[1],Coo[2]) && GetPlayerState(id) != PLAYER_STATE_SPECTATING  && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(id))
			{
				SetPlayerHealth(id,stat1);
				SetPlayerArmour(id,stat2);
			}
		}
	}
	else if(strcmp(veiksmas,"Cheal",true)==0)
	{
		for(new i;i<MAX_VEHICLES;i++)
		{

			if(stat1 == -1) stat1=1000;
			else if(stat1 < 300 || stat1 > 10000) return SendClientMessage(playerid, ORANGE, "/range [atstumas] Cheal [300-10000]");

			if(IsVehicleInRangeOfPoint(i,range,Coo[0],Coo[1],Coo[2]) && GetPlayerVirtualWorld(playerid) == GetVehicleVirtualWorld(i))
			{
				new Float:VHP;
				GetVehicleHealth(i, VHP);

				RepairVehicle(i);
				if(VHP > stat1)
					SetVehicleHealth(i, VHP);
				else
					SetVehicleHealth(i,stat1);
			}
		}
	}
	else if(strcmp(veiksmas,"Ist",true)==0)
	{
		new tick=GetTickCount();
		foreach(Player,id)
		{
			if( id!=playerid && IsPlayerInRangeOfPointEx(range,id,Coo[0],Coo[1],Coo[2]) && GetPlayerState(id) != PLAYER_STATE_SPECTATING && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(id))
			{
				new howmany;
				for(new i;i<5;i++)
				{
					if((tick - LastKills[id][i]) < 1000*60*15) // 15min
						howmany++;
					LastKills[id][i]=0;
				}
				new ix = GetPlayerWantedLevel(id)-howmany;
				if(ix < 0) ix=0;
				SetPlayerWantedLevel(id,ix);
			}
		}
	}
	else if(strcmp(veiksmas,"Skin",true)==0)
	{
		if(stat1 <= 0 || stat1 >= 312) return SendClientMessage(playerid,ORANGE,"/range [atstumas] Skin [skin id] [skin id2]");
		if(stat2 >= 312) return SendClientMessage(playerid,ORANGE,"/range [atstumas] Skin [skin id] [skin id2]");
		new x=0;
		foreach(Player,id)
		{
			if(id!= playerid && IsPlayerInRangeOfPointEx(range,id,Coo[0],Coo[1],Coo[2]) && GetPlayerState(id)==PLAYER_STATE_ONFOOT && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(id))
			{
				if(stat2 != -1)
				{
					if(!x) 
					{
						SetPlayerSkin(id,stat1);
						x=1;
					}
					else
					{
						SetPlayerSkin(id,stat2);
						x=0;
					}
				}
				else
					SetPlayerSkin(id,stat1);
			}
		}
	}
	else if(strcmp(veiksmas,"Takew",true)==0)
	{
		foreach(Player,id)
		{
			if(id!=playerid && IsPlayerInRangeOfPointEx(range,id,Coo[0],Coo[1],Coo[2]) && GetPlayerState(id) != PLAYER_STATE_SPECTATING && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(id))
			{
				//if(GetPlayerState(id)!=PLAYER_STATE_DRIVER)
				//	ResetPlayerWeapons(id);
				ResetGunData(id);
				new messas[128];
				format(messas,128,"[TAKEW] Administratorius {B0E0E6}%s{FFFFFF} jums atëmë ginklus.",ReturnName(playerid));
				SendClientMessage(id, -1, messas);
			}
		}
	}
	else if(strcmp(veiksmas,"freeze",true)==0)
	{
		foreach(Player,id)
		{
			if(id!=playerid && IsPlayerInRangeOfPointEx(range,id,Coo[0],Coo[1],Coo[2]) && GetPlayerState(id) != PLAYER_STATE_SPECTATING)
			{
				TogglePlayerControllable(id,false);
			}
		}
	}
	else if(strcmp(veiksmas,"unfreeze",true)==0)
	{
		foreach(Player,id)
		{
			if(id!=playerid && IsPlayerInRangeOfPointEx(range,id,Coo[0],Coo[1],Coo[2]) && GetPlayerState(id) != PLAYER_STATE_SPECTATING)
			{
				TogglePlayerControllable(id,true);
			}
		}
	}
	else if(strcmp(veiksmas,"Respawn",true)==0)
	{
		new Float:coo[3];
		GetPlayerPos(playerid,coo[0],coo[1],coo[2]);
		for (new i;i<MAX_VEHICLES;i++)
		{
			if(!GetVehicleModel(i)) continue;
			if(GetVehicleDistanceFromPoint(i,coo[0],coo[1],coo[2]) < range)
			{
				new v = i;
				new playeridx;
				if(GetPlayerFromCarlistID(v,playeridx) || IsVagiuCar(v) || IsVairavimoMokyklosCar(v)) continue;
				vehicleDB[v][lastpos][0]=0;
				vehicleDB[v][lastpos][1]=0;
				vehicleDB[v][lastpos][2]=0;
				SendInfoMessage(playerid,"Respawned.");
				new bool:stop=false;
				foreach(Player,x)
				{
					if(PlayerCar[x]==v)
					{
						DestroyOldCar(x); stop=true;
					}
				}
				if(VehicleSpawned[v]== 1)
				{
					spawnedvehs--;
					VehicleSpawned[v]=0;
					DestroyVehicle(v);
				}
				else if(!stop)
					SetVehicleToRespawn(v);
			}
		}
	}
	MLog(playerid,"Range","s",params);
	return 1;
}
CMD:tpmenu(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new msgas[1024];
	format(msgas,1024,"{FF0000}Centrinis Viesbutis\r\n{FF0000}Policijos Departamentas\r\n{FF0000}Los Santos Ligonine\r\n{FF0000}Dillimore\r\n{FF0000}Kalejimas\r\n{FF0000}Vairavimo Mokykla\r\n");
	format(msgas,1024,"%sLektuvas\r\nNascar Trasa\r\nLiberty City\r\nArena\r\nStunt Arena\r\nLektuvas2\r\nSandelys\r\nStriptizo Klubas\r\nPolicijos Departamentas 2\r\nKlubas\r\nApleista sala\r\n\
		DM patalpa\r\nDerbio trasa\r\nDust 2\r\nMirties katedra\r\nAptvertas miestas(kitas pasaulis)\r\nDidelis namas\r\nDirt Track\nSandelis\nDM vieta 2\nFour Dragons\nFortas\nDazu miestas\nEaster Island(kitas pasaulis)",msgas);
	ShowPlayerDialog(playerid,2582,DIALOG_STYLE_LIST,"Teleportu Meniu",msgas,"Rinktis","Atsaukti");
	return 1;
}
CMD:gunids(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	ShowPlayerDialog(playerid,1,DIALOG_STYLE_MSGBOX,"Gun ID's","Brass Knuckles - 1\r\nGolf Club - 2\r\nNightstick - 3\r\nKnife - 4\r\nBaseball bat - 5\r\nShovel - 6\r\nPool Cue - 7\r\nKatana - 8\r\nChainsaw - 9\r\nFlowers - 14\r\nGrenade - 16\r\nColt - 22\r\nSilenced colt - 23\r\nDeagle - 24\r\nShotgun - 25\r\nSawed-Off Shotgun - 26\r\nCombat Shotgun - 27\r\nMP5 - 29\r\nAK-47 - 30\r\nM4 - 31\r\nRifle - 33\r\nSniper rifle - 34\r\nFlamethrower - 37\r\nSpraycan - 41\r\nCamera - 43\r\nParachute - 46","Uzdaryti","");
	return 1;
}

/*
CMD:attach(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new id[2];
	if(sscanf(params,"ii",id[0],id[1])) return 1;
	AttachTrailerToVehicle(id[1],id[0]);
	return 1;
}
*/
CMD:invisible(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	if(!playerDB[playerid][invisible])
	{
		SendClientMessage(playerid,0x9E5FA0FF,"* Taves nematys zaidejai!");
		TextDrawShowForPlayer(playerid, InvisTD);
		//SetPlayerColor(playerid,PLAYCOL_HIDDEN);
		playerDB[playerid][invisible]=true;
	}
	else
	{
		SendClientMessage(playerid,COLOR,"* Tave matys zaidejai!");
		TextDrawHideForPlayer(playerid, InvisTD);
		playerDB[playerid][invisible]=false;
	}
	return 1;
}

CMD:tovehicle(playerid,params[])
{
	if(!playerDB[playerid][admin]) return SendInfoMessage(playerid,"Si komanda tik administratoriams!");
	new vehicleid = GetClosestVehicleid(playerid,10.0);
	if(!vehicleid || vehicleid == INVALID_VEHICLE_ID)
		return SendInfoMessage(playerid,"Prieikite arciau automobilio!");
	if(GetDriver(vehicleid)==INVALID_PLAYER_ID)
		PutPlayerInVehicle(playerid,vehicleid,0);
	else 
	{
		new msg[128];
		format(msg,sizeof(msg)," * I si automobili isesti negalite, nes ji vairuoja %s(%i)",ReturnName(GetDriver(vehicleid)),GetDriver(vehicleid));
		return 
			SendClientMessage(playerid,COLOR,msg);
	}
	return 1;
}

CMD:testfall(playerid,params[])
{
	new vardenis[128];
	if(!playerDB[playerid][admin]) return 0;
	if(sscanf(params,"s[24]",vardenis)) return SendInfoMessage(playerid,"Patikrinti zaideja del anti-bikefall /testfall [vardas]");
	new pid = GetPlayeridMid(vardenis);
	if(pid == INVALID_PLAYER_ID || !IsPlayerConnected(pid)) return SendInfoMessage(playerid,"Netinkamas zaidejas!");
	SetPVarInt(pid,"Nowarn",1);
	new vid = GetPlayerVehicleID(pid);
	SetVehicleVelocity(vid, 2, 2, 0);
	SendClientMessage(playerid, -1, "Tikrinam!");
	return 1;
}
CMD:admincar(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new model = 411;
	DestroyOldCar(playerid);
	_PlayerTeleporting[playerid]=7;
	PlayerCar[playerid] = CreateVehicle(model,0.0,0.0,0.0,0.0,223,223,-1);
	OnVehicleSpawn(PlayerCar[playerid]);
	SetVehicleNumberPlate(PlayerCar[playerid],"ADMIN");
	SetVehicleToRespawn(PlayerCar[playerid]);
	SetVehicleNumberPlate(PlayerCar[playerid],"ADMIN");

	vehicleDB[PlayerCar[playerid]][gas]=100.0;
	vehicleDB[PlayerCar[playerid]][energy]=50.0;
	vehicleDB[PlayerCar[playerid]][OldHP]=1000.0;
	FadeColorForPlayer(playerid,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,10,5);
	TogglePlayerControllable(playerid,false);
	Stop(playerid);
	SendClientMessage(playerid,GREEN," * Gavote darbini automobili.");
	return 1;
}
CMD:createtempobj(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	new modelid = strval(params), Float:Coo[3];
	if(!modelid)
		return 0;
	GetPlayerPos(playerid, Coo[0], Coo[1],Coo[2]);
	GetXYInFrontOfPlayer(playerid, Coo[0], Coo[1], 5.0);
	new objid = CreateDynamicObject(modelid, Coo[0], Coo[1], Coo[2], 0, 0 , 0);
	new msg[256];
	format(msg,256,"Created obj %i", objid);
	SendClientMessage(playerid, -1, msg);
	return 1;
}
CMD:attachtempobj(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	new vehid = GetPlayerVehicleID(playerid);
	new objid,Float:xx,Float:yy,Float:zz,Float:rx,Float:ry,Float:rz;
	if(sscanf(params,"iffffff", objid, xx,yy,zz, rx,ry,rz))
	{
		SendClientMessage(playerid, -1, "Invalid args");
		return 1;
	}
	AttachDynamicObjectToVehicle(objid, vehid, xx,yy,zz, rx,ry,rz);
	SendClientMessage(playerid, -1, "Done");
	return 1;
}
CMD:deletetempobj(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	new objid = strval(params);
	DestroyDynamicObject(objid);
	SendClientMessage(playerid, -1, "Done");
	return 1;
}
CMD:ecar(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new model;
	if(!IsNumeric(params))
	{
		//new msg[128];
		for(new i;i<212;i++)
		{
			if(strfind(aVehicleNames[i][Name],params,true) != -1)
			{
				model = i+400;
				break;
			}
		}
		if(model == 0)
			return SendInfoMessage(playerid,"/ecar [modelis]");
	}
	else
		model = strval(params);
	if(model > 611 || model < 400) return SendInfoMessage(playerid,"Netinkamas modelis(400-611).");
	if(model == 471) return SendInfoMessage(playerid,"Nebuk grincas");
	DestroyOldCar(playerid);
	_PlayerTeleporting[playerid]=7;
	PlayerCar[playerid] = CreateVehicle(model,0.0,0.0,0.0,0.0,223,223,-1);
	OnVehicleSpawn(PlayerCar[playerid]);
	SetVehicleNumberPlate(PlayerCar[playerid],"ADMIN");
	SetVehicleToRespawn(PlayerCar[playerid]);
	SetVehicleNumberPlate(PlayerCar[playerid],"ADMIN");
	if(model == 477) // zr-350
	{
		CarLights[playerid] = CreateObject(19309,0.0, 0.0, 0.0, 0.0, 0.0, 96.0);
		AttachObjectToVehicle(CarLights[playerid], PlayerCar[playerid], -0.019999, -0.274999, 0.811999, 0.000000, 0.000000, 91.454948); //Object Model: 19309 | 
	}
	vehicleDB[PlayerCar[playerid]][gas]=100.0;
	vehicleDB[PlayerCar[playerid]][energy]=50.0;
	vehicleDB[PlayerCar[playerid]][OldHP]=1000.0;
	vehicleDB[PlayerCar[playerid]][rida]=0.0;
	vehicleDB[PlayerCar[playerid]][norida]=1;
	FadeColorForPlayer(playerid,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,10,5);
	TogglePlayerControllable(playerid,false);
	Stop(playerid);
	SendClientMessage(playerid,GREEN," * Gavote darbini automobili.");
	return 1;
}
CMD:kz_ideti(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new type,textazas[128];
	if(sscanf(params,"iS()[128]",type,textazas)) return SendInfoMessage(playerid,"Naudojimas: /kz_ideti [0-22] (tekstas)");
	if(type < 0 || type > 22) return SendInfoMessage(playerid,"Naudojimas: /kz_ideti [0-22] (tekstas)");
	new Float:Coo[4];
	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	GetPlayerFacingAngle(playerid,Coo[3]);
	Coo[3]+=180;
	if(Coo[3] >= 360.0) Coo[3]-=360.0;
	CreateTrafficSign(type, Coo[0],Coo[1],Coo[2],Coo[3], 120.0, textazas);
	return 1;
}
CMD:kz_istrinti(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new signid = GetClosestTrafficSign(playerid);
	if(signid != -1)
	{
		DestroyTrafficSign(signid);
	}
	return 1;
}

CMD:gerimai_ideti(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	if(pickups[0][kaledugerimai])
	{
		return SendInfoMessage(playerid, "Gerimai jau ideti");
	}
	new Float:Coo[3];
	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	new world = GetPlayerVirtualWorld(playerid);
	pickups[0][kaledugerimai]=CreatePickupA(1274 ,2,Coo[0],Coo[1],Coo[2], world);
	SendInfoMessage(playerid, "Sukurei!");
	return 1;
}
CMD:gerimai_istrinti(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	if(pickups[0][kaledugerimai])
	{
		DestroyPickup(pickups[0][kaledugerimai]);
		pickups[0][kaledugerimai]=0;
		SendClientMessage(playerid, -1, "Done");
		return 1;
	}
	SendInfoMessage(playerid, "Klaida!");
	return 1;
}

CMD:carid(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new vardas[128];
	if (sscanf(params, "s[24]",vardas))
	{
		SendInfoMessage(playerid,"Naudojimas: /carid [dalis pavadinimo]");
		return 1;
	}
	new msg[128];
	for(new i;i<212;i++)
	{
		if(strfind(aVehicleNames[i][Name],vardas,true) != -1)
		{
			format(msg,sizeof(msg)," * Automobilio %s ID: %i",aVehicleNames[i][Name],i+400);
			return SendClientMessage(playerid, -1, msg);
		}
	}
	SendClientMessage(playerid, -1, " * Automobilis nerastas!");
	return 1;
}
CMD:n(playerid,params[])
{
	if(playerDB[playerid][admin])
	{
		if(!galikast[playerid]) return 1;
		galikast[playerid]=false;
		SetTimerEx("GaliKast",3000,0,"i",playerid);
		new reasonas[128];
		format(reasonas,sizeof(reasonas),"[admin] %s priemë pagalbos praðymà (~k~~CONVERSATION_NO~).",ReturnName(playerid));
		MLog(playerid,"N","i", 1);
		SendMessageToAdmin(reasonas);
	}
	return 0;
}

CMD:kamuolys(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	RecreateBall();
	SendFuleMessage("[Futbolas] Kamuolys sugrazintas i aikstes viduri.");
	return 1;
}

CMD:pzutable(playerid, params[])
{
	if(!playerDB[playerid][admin]) return SendInfoMessage(playerid,"Si komanda tik administratoriams.");
	if(PlayerPokerWaitQue[playerid] != -1) return SendInfoMessage(playerid, "Negali naudoti sios komandos laukdamas eileje");
	if(GetPlayerInterior(playerid))
	{
		for(new i;i<MAX_POKER_GAMES;i++)
		{
			if(IsPlayerInRangeOfPointEx(3.0,playerid,PokerTables[i][0],PokerTables[i][1],PokerTables[i][2]))
			{
				if(!playerDB[playerid][playingpoker])
				{
					if(Poker[i][GameUsed])
					{
						if(Poker[i][watching] != -1) return SendInfoMessage(playerid," * Si zaidima jau kazkas stebi!");
						new ppl;
						//new y;
						for(new x;x<6;x++)
						{
							if(Poker[i][players][x] != -1)
							{
								ppl++;
							}
						}
						if(ppl < 2) return SendInfoMessage(playerid,"Zaidimas nevyksta!");
						ApplyAnimation(playerid,"INT_OFFICE", "FF_Dam_Fwd",4.0,0,0,0,1,0,1);
						playerDB[playerid][playingpoker]=1;
						if(Poker[i][TheStep]>=0)	
							for(new x;x<3;x++)
							{
								TextDrawShowForPlayer(playerid,Poker[i][TableKorta][x]);
								//TextDrawDestroy(TableKorta[i]);
							}
						if(Poker[i][TheStep] >=1)
							TextDrawShowForPlayer(playerid,Poker[i][TableKorta][3]);
						if(Poker[i][TheStep] >=2)
							TextDrawShowForPlayer(playerid,Poker[i][TableKorta][4]);
						//TextDrawDestroy(JusuKortos);
						TextDrawShowForPlayer(playerid,Poker[i][BankTD]);
						CreatePlayerTextDraws(playerid);
						for(new y;y<6;y++)
						{
							if(Poker[i][players][y] != -1)
							{
								TextDrawShowForPlayer(playerid,Poker[i][PokerAction][y]);
								TextDrawShowForPlayer(playerid,Poker[i][PokerMoney][y]);
								TextDrawShowForPlayer(playerid,Poker[i][PokerName][y]);
								for(new x;x<2;x++)
								{
									PlayerTextDrawShow(playerid,Korta[playerid][y][x]);
								}
							}
							
						}
						for(new x;x<5;x++)
						{
							PlayerTextDrawHide(playerid,Mygtukas[x][playerid]);
						}
						SetPlayerCameraPos(playerid,PokerCameras[i][0],PokerCameras[i][1],PokerCameras[i][2]);
						SetPlayerCameraLookAt(playerid,PokerCameras[i][3],PokerCameras[i][4],PokerCameras[i][5], CAMERA_MOVE);
						SendClientMessage(playerid,-1,"Noredami iseiti spauskite ESC!");
						Poker[i][watching] = playerid;
						SelectTextDraw(playerid, 0xACCBF1FF);
					}
					else
					{
						return SendInfoMessage(playerid,"Zaidimas nevyksta!");
					}
					return 1;
				}	
				else
				{
					OnPlayerClickTextDraw(playerid, Text:INVALID_TEXT_DRAW);
					return 1;
				}
			}
		}
	}
	SendInfoMessage(playerid,"Prieikite prie stalo");
	return 1;
}
CMD:blinds(playerid,params[])
{
	if(!playerDB[playerid][admin]) return SendInfoMessage(playerid,"Si komanda tik administratoriams.");
	if(playerDB[playerid][playingpoker])
	{
		new id=-1;
		for(new x;x<MAX_POKER_GAMES;x++)
		{
			if(Poker[x][watching] == playerid)
				id=x;
		
		}
		if(id != -1)
		{
			new blinds[2];
			if(sscanf(params,"dd",blinds[0],blinds[1])) return SendInfoMessage(playerid,"Naudojimas: /blinds [small blind] [large blind]");
			if(blinds[0] < 1 || blinds[0] > 100000 || blinds[1] < 1 || blinds[1] > 100000 || blinds[0] > blinds[1])
				return SendInfoMessage(playerid,"Blinds nuo 1 iki 100,000 ir small blind mazesnis uz big.");
			PokerBlinds[id][0] = blinds[0];
			PokerBlinds[id][1] = blinds[1];
			new
				tmpstr[ 60 ];
				
			format( tmpstr, 60, "Blinds %i/%i€\nBuy in %i-%i€\nSpauskite [H]", PokerBlinds[id][0],PokerBlinds[id][1],PokerBlinds[id][2],PokerBlinds[id][3] );
			UpdateDynamic3DTextLabelText(PokerBlindsTD[id],COLOR_PILKA, tmpstr);
			SendClientMessage(playerid,-1," * Blindai pakeisti! Nepamirskite sugrazinti ju i normalius (25-50,100-200,500-1000,5000-10000)");
			return 1;
		}
	}
	SendInfoMessage(playerid,"Turite stebeti zaidima su /pzutable");
	return 1;
}
CMD:createactor(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new Float:Coo[4];
	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	GetPlayerFacingAngle(playerid, Coo[3]);
	new skinas = strval(params);
	if(!skinas || skinas > 310)
		return SendInfoMessage(playerid," /createactor [skinas] ");
	new actor = CreateActor(skinas, 0, 0, 0, 0);
	SetTimerEx("MakeActor",1000,false,"iffffi",actor,Coo[0],Coo[1],Coo[2],Coo[3],GetPlayerVirtualWorld(playerid));
	new msg[128];
	format(msg,sizeof(msg)," * Sukurei aktoriu ID: %i",actor);
	SendClientMessage(playerid, -1, msg);
	return 1;
}
CMD:deleteactor(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new skinas = strval(params);
	if(!IsValidActor(skinas))
		return SendInfoMessage(playerid," /deleteactor [id] ");
	DestroyActor(skinas);
	new msg[128];
	format(msg,sizeof(msg)," * Istrynei aktoriu ID: %i",skinas);
	SendClientMessage(playerid, -1, msg);
	return 1;
}

CMD:actionactor(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new actorid,library[24],veiksmas[24];
	if(sscanf(params,"is[24]s[24]",actorid,library,veiksmas))
		return SendInfoMessage(playerid," /actionactor [id] [library] [action]");
	if(!_animLibExist(library))
		return SendInfoMessage(playerid," Tokios library nera!");
	ApplyActorAnimation(actorid, library, veiksmas,4.0, 1, 0,0,0,0);
	ApplyActorAnimation(actorid, library, veiksmas,4.0, 1, 0,0,0,0);
	new msg[128];
	format(msg,sizeof(msg)," * Pakeitei aktoriaus veiksma ID: %i",actorid);
	SendClientMessage(playerid, -1, msg);
	return 1;
}

CMD:moliugas(playerid,params[])
{
	if(playerDB[playerid][admin])
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid, CAP_SLOT))
			RemovePlayerAttachedObject(playerid, CAP_SLOT);
		else
			SetPlayerAttachedObject(playerid, CAP_SLOT, 19320, 2, 0.1, 0, 0.0, 0, 90, 0, 0.65, 0.65, 0.65, 0, 0);
	}
	return 1;
}
CMD:halloweenadmin(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	Halloween(strval(params));
	return 1;
}
CMD:spawngun(playerid,params[])
{
	if(!playerDB[playerid][admin])
		return SendInfoMessage(playerid,"Tai administratoriaus komanda!");
	new gunid = strval(params);
	if(gunid < 1 || gunid > 46 || GetWeaponModel(gunid) == -1) return SendClientMessage(playerid,ORANGE,"Naudojimas: /spawngun [id]");
	switch(gunid)
	{
		case 0,19,20,21,28,32,35,36,38,44,45: return SendClientMessage(playerid,ORANGE,"Sio ginklo duoti negalima!");
	}
	new Float:Coo[3];

	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	GetXYInFrontOfPlayer(playerid, Coo[0],Coo[1], 5); //1221
	
	new slot = -1;
	for(new i;i<100;i++)
	{
		if(GunId[i] == 0)
		{
			slot = i;
			break;
		}
	}
	if(spawnedguns == 99 || slot == -1)
		return SendInfoMessage(playerid,"Pasiektas ginklu limitas!");


	GunPickup[slot] = CreatePickupA(GetWeaponModel(gunid), 2, Coo[0],Coo[1],Coo[2],GetPlayerVirtualWorld(playerid));
	GunId[slot] = gunid;
	GunTimer[slot] = SetTimerEx("DestroySpawnGun", 1000*60*60*2, false,"i", slot);
	spawnedguns++;

	return 1;
}
CMD:spawncp(playerid,params[])
{
	if(!playerDB[playerid][admin])
		return SendInfoMessage(playerid,"Tai administratoriaus komanda!");
	new itemas[24],amnt;
	if(sscanf(params,"s[24]d",itemas,amnt)){SendInfoMessage(playerid,"Naudojimas: /spawncp [health/armour] [kiekis 1-200]"); return 1;}
	new pickuptype = 0;
	if(strcmp(itemas,"health",true)==0)
		pickuptype = 1240;
	else if(strcmp(itemas,"armour",true)==0)
		pickuptype = 1242;
	else
		return SendInfoMessage(playerid,"Naudojimas: /spawncp [health/armour] [kiekis 1-200]");
	if(amnt < 1 || amnt > 200)
		return SendInfoMessage(playerid,"Naudojimas: /spawncp [health/armour] [kiekis 1-200]");
	new Float:Coo[3];

	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	GetXYInFrontOfPlayer(playerid, Coo[0],Coo[1], 5); //1221
	
	new slot = -1;
	for(new i;i<100;i++)
	{
		if(GunId[i] == 0)
		{
			slot = i;
			break;
		}
	}
	if(spawnedguns == 99 || slot == -1)
		return SendInfoMessage(playerid,"Pasiektas pickupu limitas!");


	GunPickup[slot] = CreatePickupA(pickuptype, 2, Coo[0],Coo[1],Coo[2], GetPlayerVirtualWorld(playerid));
	GunId[slot] = pickuptype;
	GunAmnt[slot] = amnt;
	GunTimer[slot] = SetTimerEx("DestroySpawnGun", 1000*60*60*2, false,"i", slot);
	spawnedguns++;

	return 1;
}
CMD:spawncar(playerid,params[])
{
	if(!playerDB[playerid][admin])
		return SendInfoMessage(playerid,"Tai administratoriaus komanda!");
	new model;
	if(!IsNumeric(params))
	{
		//new msg[128];
		for(new i;i<212;i++)
		{
			if(strfind(aVehicleNames[i][Name],params,true) != -1)
			{
				model = i+400;
				break;
			}
		}
		if(model == 0)
			return SendInfoMessage(playerid,"/spawncar [modelis]");
	}
	else
		model = strval(params);
	if(model > 611 || model < 400) 
		return SendInfoMessage(playerid,"Netinkamas modelis(400-611).");
	if(model == 471) return SendInfoMessage(playerid,"Nebuk grincas");
	if(spawnedvehs > 40)
		return SendInfoMessage(playerid,"Pasiektas masinu limitas!");

	new Float:Coo[3];
	GetPlayerPos(playerid, Coo[0], Coo[1], Coo[2]);
	new Float:Ang;
	GetPlayerFacingAngle(playerid, Ang);

	new cid = CreateVehicle(model, Coo[0], Coo[1], Coo[2], Ang, -1, -1, -1, 0);
	OnVehicleSpawn(cid);
	SetVehicleNumberPlate(cid,"SPAWNCAR");
	SetVehicleToRespawn(cid);
	SetVehicleNumberPlate(cid,"SPAWNCAR");

	LinkVehicleToInterior(cid,GetPlayerInterior(playerid));
	SetVehicleVirtualWorld(cid, GetPlayerVirtualWorld(playerid));


	vehicleDB[cid][gas]=100.0;
	vehicleDB[cid][energy]=50.0;
	vehicleDB[cid][OldHP]=1000.0;
	vehicleDB[cid][norida]=1;


	VehicleSpawned[cid]=1;
	spawnedvehs++;
	SetTimerEx("DestroySpawnCar", 1000*60*60*2, false,"i", cid);
	return 1;
}

CMD:paimticp(playerid,params[])
{
	if(!playerDB[playerid][admin])
		return SendInfoMessage(playerid,"Si komanda administratoriams");
	new vardas[24];
	if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Paimti pasibuginusi cp: /paimticp [vardo_dalis]"); return 1;}

	new id = GetPlayeridMid(vardas);
	if (id == INVALID_PLAYER_ID){SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	if(CheckNukeCp(id,100))
	{
		SendClientMessage(playerid, -1, "Paemei zaidejui cp!");
	}
	else
	{
		SendClientMessage(playerid, -1, "Zaidejas nedirba arba per toli nuo cp.");
	}
	return 1;

}

// super admin

CMD:kaledumisijaadmin(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	KaleduMisija(playerid, strval(params));
	return 1;
}

CMD:addaname(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	new test[256];
	if(sscanf(params,"s",test)) {
		return SendInfoMessage (playerid, "/addaname [name]");
	}
	
	if(AddPlayerName(playerid))
		return SendClientMessage(playerid, -1, "Done!");
	else
		return SendClientMessage(playerid, -1, "Fail!");
}

CMD:reloadboard(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	mysql_function_query(SQL, "SELECT Name,Color from Siena order by sid ASC", true, "SQL_LoadSienaSQL", "");
	SendClientMessage(playerid, -1, "Done");
	return 1;
}

CMD:mypolygonid(playerid,params[])
{
	new poly = GetPlayerPoly(playerid);
	if(poly == -1)
		return SendClientMessage(playerid, -1, "none");
	else
		SendClientMessage(playerid, -1, "poly found");

	new Float:Coo[3];

	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	if(IsPointInPolyRange(poly,Coo[0],Coo[1],Coo[2], 5.0))
		SendClientMessage(playerid, -1, "in range");
	else
		SendClientMessage(playerid, -1, "not in range");
	return 1;
}
CMD:myvirtualworld(playerid,params[])
{
	if(!playerDB[playerid][admin])
		return SendInfoMessage(playerid,"Si komanda administratoriams");
	new tmp[20];
  	valstr(tmp, GetPlayerVirtualWorld(playerid));
	SendClientMessage(playerid, -1, tmp);
	return 1;
}

CMD:testmods(playerid,params[])
{
	if(!playerDB[playerid][admin])
		return 0;
	StartModsMinigame(playerid);
	return 1;
}

CMD:fixsandelis(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	new KuriVieta,mid;

	if(sscanf(params,"ii",KuriVieta,mid)) {
		SendClientMessage(playerid, -1, "Sandeliu id: (0)Seklu (1)LSD (2)Ratu (3)Ginklu (4)Pinigu");
		SendClientMessage(playerid, -1, "Gang ids: (-1)PD (0)Ballas (1)VLA (2)GSF (3)Vagos (4)Mafia (5)Nang");
		return SendInfoMessage(playerid,"/fixsandelis [sandelioid] [gang]");
	}
	if(mid < -1 || mid > 5)
		return SendInfoMessage(playerid,"Invalid gangid");
	if(mid == -1 && KuriVieta != 3)
		return SendInfoMessage(playerid,"PD gali priklausyti tik ginklu sandelis");
	if(KuriVieta < 0 || KuriVieta > 4)
		return SendInfoMessage(playerid, "Invalid sandelioid");

	PlaceOwnedBy[KuriVieta]=mid;
	if(PlaceOwnedBy[KuriVieta]==-1)
		GangZoneSpalva[KuriVieta]=0x00F2FFAB;
	else
		GangZoneSpalva[KuriVieta]=FamilyInfo[mid][FamilyZone][1];
	GangZoneHideForAll(GangZone[KuriVieta]);
	GangZoneShowForAll(GangZone[KuriVieta],GangZoneSpalva[KuriVieta]);
	SendClientMessage(playerid, -1, "Success!");
	return 1;
}
CMD:isdalinodovanas(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	SetPVarInt(playerid,"IsdalinoDovanas",strval(params));
	return 1;
}
CMD:timeset(playerid,params[])
{
	if(IsPlayerAdmin(playerid) && strval(params) > 0) 
	{
		dazutime = strval(params);
		SendClientMessage(playerid, -1, "Success!");
		return 1;
	}
	return 0;
}

CMD:destroydynamic(playerid,params[])
{
	if(IsPlayerAdmin(playerid))
	{
		if(!strval(params))
		{
			SendClientMessage(playerid, -1, "fail");
			return 1;
		}
		DestroyDynamicObject(strval(params));
		SendClientMessage(playerid, -1, "Success!");
		return 1;
	}
	return 0;
}
CMD:loadinterior(playerid,params[])
{
	if(IsPlayerAdmin(playerid))
		LoadInterior(GetPlayerHouseID(playerid));
	return 1;
}
CMD:texturize(playerid,params[])
{
	if(IsPlayerAdmin(playerid))
	{
		new id,mid,tid;
		if(sscanf(params,"iii",id,mid,tid)) return SendInfoMessage(playerid,"/texturize [isdoor] [matid] [textureid]");
		Texturize(GetPlayerHouseID(playerid),id,mid,tid);
		SaveTexture(GetPlayerHouseID(playerid),id,mid,tid);
	}
	return 1;
}
CMD:resettextures(playerid,params[])
{
	if(IsPlayerAdmin(playerid))
	{
		new id,mid;
		if(sscanf(params,"ii",id,mid)) return SendInfoMessage(playerid,"/resettextures [isdoor] [matid]");
		TogglePlayerControllable(playerid, false);
		ResetTextures(GetPlayerHouseID(playerid),id,mid);
		if(!playerDB[playerid][ant] && !playerDB[playerid][suristas])
			SetTimerEx("Atfreezint",1000,false,"i",playerid);
	}
	return 1;
}

CMD:totag(playerid,params[])
{
	new i = strval(params);
	if(playerDB[playerid][admin])
		SetPlayerPoz(playerid,GaujuTagai[i][0],GaujuTagai[i][1],GaujuTagai[i][2]);
}
CMD:shake(playerid,params[])
{
	if(IsPlayerAdmin(playerid))
		Shake(0);
	return 1;
}
CMD:zuveleset(playerid,params[])
{
	if(IsPlayerAdmin(playerid)) 
	{
		zuvele=true;
		SendClientMessage(playerid, -1, "Success!");
		return 1;
	}
	return 0;
}
CMD:lobisset(playerid,params[])
{
	if(IsPlayerConnected(playerid)) 
	{
		LobiuDB[IsPicked] = false;
		SendClientMessage(playerid, -1, "Success!");
		return 1;
	}
	return 0;
}
CMD:setrida(playerid,params[]) 
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	vehicleDB[GetPlayerVehicleID(playerid)][rida]=floatstr(params);
	return 1;
}

CMD:rogutes(playerid,params[]) 
{

	if(IsPlayerAdmin(playerid))
		CreateRoges(playerid);

	return 1;
}

CMD:setnextcpadminas(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	SetNextNukeCp(playerid, strval(params));
	return 1;
}

CMD:trythenuke(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	for(new i;i<removedCount;i++)
	{
		RemovedObjects[i][rActive]=1;
	}
	if(strval(params) == 1)
	{
		RemoveNukeObjectsForAll();
	}
	else
	{
		RestoreNukeObjectsForAll();
	}
	SendClientMessage(playerid, -1, "Done");
	return 1;
}
CMD:cleanupnuke(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	for(new i;i<removedCount;i++)
	{
		if(RemovedObjects[i][rfRestoredId] != 0)
		{
			DestroyDynamicObject(RemovedObjects[i][rfRestoredId]);
			RemovedObjects[i][rfRestoredId] = 0;
		}
	}
	DestroyProps();
	NuclearBlast[NukeInProgress] = 4;
	SendClientMessage(playerid, -1, "Done");
	return 1;
}
CMD:cleanupnuke2(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	for(new i;i<removedCount;i++)
	{
		if(RemovedObjects[i][rfRestoredId] != 0)
		{
			DestroyDynamicObject(RemovedObjects[i][rfRestoredId]);
			RemovedObjects[i][rfRestoredId] = 0;
		}
	}
	SendClientMessage(playerid, -1, "Done");
	return 1;
}
CMD:padetidovanaadmin(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	new objektas = strval(params);
	if(!objektas)
		return SendInfoMessage(playerid, "/padetidovana [id]");
	new housenumber;
	housenumber = GetPlayerHouseID(playerid);
	if(GetPlace(playerid) != PLACE_HOUSE)
		return SendInfoMessage(playerid,"Privalote buti namie!");
	new hid = housenumber;
	if(PadetiDovana(hid, objektas))
	{
		SendClientMessage(playerid,WHITE," * Padëjai dovana! Jà gali perstatyti paraðæs /baldai -> Dovanos.");
		SaveBaldai(hid);
		ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
		return 1;
	}
	SendInfoMessage(playerid,"Nera vietos naujiems baldams!");
	return 1;
}

CMD:createtheprops(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	CreateProps();
	NuclearBlast[NukeInProgress] = 3;
	return 1;
}

CMD:distastoactor(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	ActorServe(playerid);
	return 1;
}

CMD:setpelnas(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	if(GetPlace(playerid) != PLACE_BIZ)
		return SendInfoMessage(playerid,"Turite buti versle!");
	BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning] = strval(params);
	SendClientMessage(playerid, COLOR, " Success!");
	return 1;
}

CMD:changeloterija(playerid,params[])
{
	if(IsPlayerAdmin(playerid)) {
		GenerateCars();
		return 1;
	}
	return 0;
	//vehicleDB[GetPlayerVehicleID(playerid)][rida] = strval(params);
}

CMD:tomechpos(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new id = strval(params);
	SetVehiclePoz(GetPlayerVehicleID(playerid), MechanikaiCars[id][0], MechanikaiCars[id][1], MechanikaiCars[id][2]);
	SetVehicleZAngle(GetPlayerVehicleID(playerid), MechanikaiCars[id][3]);
	return 1;
}

CMD:setmin(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	playerDB[playerid][pradirbo]=strval(params);
	return 1;
}
/*

CMD:testspray(playerid,params[])
{
	if(MoneyVan == -1)
		MoneyVan = GetPlayerVehicleID(playerid);
	else
		MoneyVan=-1;
	return 1;
}
CMD:testmoney(playerid,params[])
{
	ThrowMoney(playerid);
	return 1;
}
*/

CMD:saveallplayers(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	SendClientMessage(playerid, -1, " * Working...");
	for(new i;i<MAX_PLAYERS;i++) if(IsPlayerConnected(playerid) && GetPlayerScore(playerid) > 10)
	{
		SavePlayerData(i,false);
	}
	SendClientMessage(playerid, -1, " * Saved!");
	return 1;
}
CMD:kickallplayers(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	SendClientMessage(playerid, -1, " * Working...");
	for(new i;i<MAX_PLAYERS;i++) if(IsPlayerConnected(playerid) && i != playerid)
	{
		Kick(i);
	}
	SendClientMessage(playerid, -1, " * Kicked!");
	return 1;
}
CMD:tovagys(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new veh = GetPlayerVehicleID(playerid);
	new id = strval(params)-1;
	SetVehiclePoz(veh,VogiamosMasinos[id][X],VogiamosMasinos[id][Y],VogiamosMasinos[id][Z]);
	SetVehicleZAngle(veh,VogiamosMasinos[id][Au]);
	return 1;
}
CMD:changename(playerid, params[])
{
	if(!Pareigos(playerid,"Admin") && !Pareigos(playerid,"Admin2")) return SendInfoMessage(playerid,"Si komanda ne tau ");
	new vardas[128],naujasvardas[128];
	if (sscanf(params, "s[24]s[24]",vardas,naujasvardas))
	{
		SendInfoMessage(playerid,"Naudojimas /changename [senas V_P] [naujas V_P]");
		return 1;
	}
	mysql_real_escape_string(vardas,vardas,_,256);
	mysql_real_escape_string(naujasvardas,naujasvardas,_,256);
	new query[512];
	format(query,sizeof(query),"SELECT Name FROM `Account` WHERE `Name` IN ('%s', '%s')",vardas, naujasvardas);
	mysql_function_query(SQL, query, true, "SQL_NameChange3", "iss", playerid,vardas, naujasvardas);
	return 1;
}
CMD:changepass(playerid,params[])
{
	if(!Pareigos(playerid,"Admin") && !Pareigos(playerid,"Admin2")) return SendInfoMessage(playerid,"Si komanda ne tau ");
	new vardas[128],passwordas[128];
	if (sscanf(params, "s[24]s[24]",vardas,passwordas))
	{
		SendInfoMessage(playerid,"Naudojimas /changepass [Vardas_Pavarde] [naujas pw]");
		return 1;
	}
	mysql_real_escape_string(vardas,vardas);
	mysql_real_escape_string(passwordas,passwordas);
	if(strlen(passwordas) > 10) return SendInfoMessage(playerid,"Slaptazodis iki 10 simboliu!");
	new id = GetPlayeridMidEx(vardas);
	if (id != INVALID_PLAYER_ID){ 
		format(vardas,sizeof(vardas),"%s",ReturnName(id));
		SendClientMessage(playerid,YELLOW," * Zaidejas prisijunges, atjungiame....");
		Kick(id);
		
	}
	new query[256];
	format(query,256,"SELECT * From Account Where Name='%s'",vardas);
	mysql_function_query(SQL, query, true, "SQL_Changepassas", "iss", playerid,vardas,passwordas);
	return 1;
}

CMD:dropnuclear(playerid, params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	new vardass[128],kiekis;
	if (sscanf(params, "s[24]i",vardass,kiekis))
	{
		SendClientMessage(playerid,-1," * Naudojimas /dropnuclear [vardas] [dialogid]");
		return 1;
	}
	new id = GetPlayeridMidEx(vardass);
	if (id == INVALID_PLAYER_ID)
	{ 
		SendClientMessage(playerid, -1, "Tokio zaidejo nera");
		return 1;
	}
	if(gPlayerDialog[id] != -1)
	{
		SendClientMessage(playerid, -1 ,"Zaidejas atsidares dialoga");
		return 1;
	}
	CallRemoteFunction("DropNuke", "ii", id, kiekis);
	SendClientMessage(playerid, -1, "Done!");
	return 1;
}

CMD:gispejimas(playerid,params[])
{
	if(!Pareigos(playerid,"Gaujos") && !Pareigos(playerid,"Admin")) 
		return SendInfoMessage(playerid,"Si komanda ne tau ");
	new gauja[128],kiekis, priezastis[128];
	if (sscanf(params, "s[24]is[100]",gauja,kiekis,priezastis))
	{
		SendClientMessage(playerid,-1," * Gaujos: Ballas VLA GSF Vagos Mafia Nang");
		SendClientMessage(playerid,-1," * Kiekis: 0 - nuima visus ispejimus, 1 - uzdeda 1/2, 2 - uzdeda 2/2");
		SendClientMessage(playerid,-1," * Naudojimas /gispejimas [gauja] [kiekis] [priezastis]");
		return 1;
	}
	new gangid = -1;
	if(strcmp(gauja,"Ballas", true) == 0) gangid = 0;
	if(strcmp(gauja,"VLA", true) == 0) gangid = 1;
	if(strcmp(gauja,"GSF", true) == 0) gangid = 2;
	if(strcmp(gauja,"Vagos", true) == 0) gangid = 3;
	if(strcmp(gauja,"Mafia", true) == 0) gangid = 4;
	if(strcmp(gauja,"Nang", true) == 0) gangid = 5;
	
	if(gangid == -1 || kiekis < 0 || kiekis > 2)
	{
		SendClientMessage(playerid,-1," * Gaujos: Ballas VLA GSF Vagos Mafia Nang");
		SendClientMessage(playerid,-1," * Kiekis: 0 - nuima visus ispejimus, 1 - uzdeda 1/2, 2 - uzdeda 2/2");
		SendClientMessage(playerid,-1," * Naudojimas /gispejimas [gauja] [kiekis] [priezastis]");
		return 1;
	}
	mysql_real_escape_string(priezastis,priezastis);
	if(kiekis == 0)
	{
		if(FamilyInfo[gangid][FamilyIspejimai] == 0)
			return SendClientMessage(playerid, -1, " * Gauja neturi ispejimu!");
		DeleteGangIspejimai(gangid, playerid, priezastis);
		SendClientMessage(playerid, -1, " * Sekmingai nuemei gaujos ispejimus! Pasitikrink rezultata per /gaujos");
	}
	else
	{
		if(FamilyInfo[gangid][FamilyIspejimai] == 2)
			return SendClientMessage(playerid, -1, " * Gauja jau turi 2/2 ispejimus!");

		AddGangIspejimas(playerid, gangid, kiekis, priezastis);
		SendClientMessage(playerid, -1, " * Sekmingai uzdejai ispejima! Pasitikrink rezultata per /gaujos");
	}
	return 1;
}

CMD:atimtivip(playerid,params[])
{
	if(!Pareigos(playerid,"Admin") && !Pareigos(playerid,"Admin2")) return SendInfoMessage(playerid,"Si komanda ne tau ");
	new vardas[128];
	if (sscanf(params, "s[24]",vardas))
	{
		SendInfoMessage(playerid,"Naudojimas /atimtivip [Vardas_Pavarde]");
		return 1;
	}
	mysql_real_escape_string(vardas,vardas);
	new id = GetPlayeridMidEx(vardas);
	if (id != INVALID_PLAYER_ID)
	{ 
		playerDB[id][vip]=false;
		SendClientMessage(playerid, YELLOW, " * Zaidejas prisijunges... nuimam prisijungusiam vipa..");
	}
	new query[256];
	format(query,256,"SELECT * From Account Where Name='%s'",vardas);
	mysql_function_query(SQL, query, true, "SQL_Atimamvipa", "is", playerid,vardas);
	return 1;
}


CMD:createacar(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new model;
	if(sscanf(params,"i",model)) return SendInfoMessage(playerid,"Pagaminti automobili /createacar [modelis]");
	if(model < 400 || model > 611) return SendInfoMessage(playerid,"Pagaminti automobili /createacar [modelis]");
	new Float:Coo[3];
	new string[128];
	new Float:Angle;
	GetPlayerFacingAngle(playerid,Angle);
	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	if(Carlist[playerid][Typ]==-1)
	{
		Carlist[playerid][Status]=1; 
		Carlist[playerid][Lock]=0;
		Carlist[playerid][Typ]=model-400;
		Carlist[playerid][X] = Coo[0];
		Carlist[playerid][Y] = Coo[1];
		Carlist[playerid][Z] = Coo[2];
		Carlist[playerid][Rotation] = Angle;
		Carlist[playerid][Carid]=CreateVehicle(model,Carlist[playerid][X],Carlist[playerid][Y],Carlist[playerid][Z],Carlist[playerid][Rotation],-1,-1,-1);
		format(Carlist[playerid][NumPlate],40,"{FF0000}NERA");
		SetVehicleNumberPlate(Carlist[playerid][Carid],"{FF0000}NERA");
		new vehicleid = Carlist[playerid][Carid];
		format(vehicleDB[vehicleid][nuomuoja],24,"no");
		format(vehicleDB[vehicleid][lastuser],MAX_PLAYER_NAME,"");
		vehicleDB[vehicleid][energy]=50;
		vehicleDB[vehicleid][OldHP]=1000;
		vehicleDB[vehicleid][gas]=50;
		vehicleDB[vehicleid][rida]=0.0;
		new name[24];
		GetPlayerName(playerid,name,24);
		format(string,128,"Sveikiname! Jus nusipirkote %s uz 0EUR! Tai pirmoji jusu masina",aVehicleNames[Carlist[playerid][Typ]][Name]);
		SendInfoMessage(playerid,string);
		printf("%s %s",name,string);
	}
	else if(Carlist2[playerid][Typ]==-1)
	{
		Carlist2[playerid][Status]=1; 
		Carlist2[playerid][Lock]=0;
		Carlist2[playerid][Typ]=model-400;
		Carlist2[playerid][X] = Coo[0];
		Carlist2[playerid][Y] = Coo[1];
		Carlist2[playerid][Z] = Coo[2];
		Carlist2[playerid][Rotation] = Angle;
		Carlist2[playerid][Carid]=CreateVehicle(model,Carlist2[playerid][X],Carlist2[playerid][Y],Carlist2[playerid][Z],Carlist2[playerid][Rotation],-1,-1,-1);
		format(Carlist2[playerid][NumPlate],40,"{FF0000}NERA");
		SetVehicleNumberPlate(Carlist2[playerid][Carid],"{FF0000}NERA");
		new vehicleid = Carlist2[playerid][Carid];
		format(vehicleDB[vehicleid][nuomuoja],24,"no");
		format(vehicleDB[vehicleid][lastuser],MAX_PLAYER_NAME,"");
		vehicleDB[vehicleid][energy]=50;
		vehicleDB[vehicleid][OldHP]=1000;
		vehicleDB[vehicleid][gas]=50;
		vehicleDB[vehicleid][rida]=0.0;
		new name[24];
		GetPlayerName(playerid,name,24);
		format(string,128,"Sveikiname! Jus nusipirkote %s uz 0EUR! Tai antroji jusu masina",aVehicleNames[Carlist2[playerid][Typ]][Name]);
		SendInfoMessage(playerid,string);
		printf("%s %s",name,string);
	}
	else if(Carlist3[playerid][Typ]==-1)
	{
		Carlist3[playerid][Status]=1; 
		Carlist3[playerid][Lock]=0;
		Carlist3[playerid][Typ]=model-400;
		Carlist3[playerid][X] = Coo[0];
		Carlist3[playerid][Y] = Coo[1];
		Carlist3[playerid][Z] = Coo[2];
		Carlist3[playerid][Rotation] = Angle;
		Carlist3[playerid][Carid]=CreateVehicle(model,Carlist3[playerid][X],Carlist3[playerid][Y],Carlist3[playerid][Z],Carlist3[playerid][Rotation],-1,-1,-1);
		format(Carlist3[playerid][NumPlate],40,"{FF0000}NERA");
		SetVehicleNumberPlate(Carlist3[playerid][Carid],"{FF0000}NERA");
		new vehicleid = Carlist3[playerid][Carid];
		format(vehicleDB[vehicleid][nuomuoja],24,"no");
		format(vehicleDB[vehicleid][lastuser],MAX_PLAYER_NAME,"");
		vehicleDB[vehicleid][energy]=50;
		vehicleDB[vehicleid][OldHP]=1000;
		vehicleDB[vehicleid][gas]=50;
		vehicleDB[vehicleid][rida]=0.0;
		new name[24];
		GetPlayerName(playerid,name,24);
		format(string,128,"Sveikiname! Jus nusipirkote %s uz 0EUR! Tai trecioji jusu masina",aVehicleNames[Carlist3[playerid][Typ]][Name]);
		SendInfoMessage(playerid,string);
		printf("%s %s",name,string);
	}
	else
		return SendInfoMessage(playerid,"Neturi laisvos vietos!");
	
	return 1;

}
CMD:testbaldai(playerid)
{
	if(!playerDB[playerid][admin]) return 0;
	return ShowBaldaiCat(playerid);
}
CMD:dovanubaldai(playerid,params[])
{
	if(IsPlayerAdmin(playerid))
	{
		ShowBaldaiCat(playerid,3);
	}
	return 1;
}
CMD:kfondas(playerid,params[])
{
	if(!Pareigos(playerid,"Dyrikai") && !Pareigos(playerid,"Admin") && !Pareigos(playerid,"Admin2"))
		return SendInfoMessage(playerid,"Si komanda ne tau");
	new msg[128];
	format(msg,sizeof(msg)," * Siuo metu kysiu fonde yra %i€. Naudokite /kf_paimti [suma] [trumpa priezastis]",Server[kysiufondas]);
	SendClientMessage(playerid,YELLOW,msg);
	return 1;
}
CMD:kf_paimti(playerid,params[])
{
	if(!Pareigos(playerid,"Dyrikai") && !Pareigos(playerid,"Admin") && !Pareigos(playerid,"Admin2"))
		return SendInfoMessage(playerid,"Si komanda ne tau");
	new suma,reason[128];
	if(sscanf(params,"is[128]",suma,reason)) return SendInfoMessage(playerid,"Naudojimas: /kf_paimti [suma] [priezastis]");
	if(suma <= 0) return SendInfoMessage(playerid,"Netinkama suma!");
	if(suma > Server[kysiufondas]) return SendInfoMessage(playerid,"Kysiu fonde tiek nera!");
	GivePlayerMoneyA(playerid,suma);
	Server[kysiufondas]-=suma;
	MLog(playerid,"Paeme is kfondo","is",suma,reason);
	SendInfoMessage(playerid,"Paemei pinigus!");
	return 1;
}
CMD:kf_padeti(playerid,params[])
{
	if(!Pareigos(playerid,"Dyrikai") && !Pareigos(playerid,"Admin") && !Pareigos(playerid,"Admin2"))
		return SendInfoMessage(playerid,"Si komanda ne tau");
	new suma,reason[128];
	if(sscanf(params,"is[128]",suma,reason)) return SendInfoMessage(playerid,"Naudojimas: /kf_padeti [suma] [priezastis]");
	if(suma <= 0) return SendInfoMessage(playerid,"Netinkama suma!");
	if(suma > GetPlayerMoneyA(playerid)) return SendInfoMessage(playerid,"Tu tiek neturi!");
	GivePlayerMoneyA(playerid,-suma);
	Server[kysiufondas]+=suma;
	MLog(playerid,"Padejo i kfonda","is",suma,reason);
	SendInfoMessage(playerid,"Padejai pinigus!");
	return 1;
}
CMD:rmon(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	//GivePlayerMoneyA(playerid,-GetPlayerMoneyA(playerid));
	ResetPlayerMoneyA(playerid);
	return 1;
}
CMD:onlinetime(playerid,params[])
{
	if(!Pareigos(playerid,"Admin") && !Pareigos(playerid,"Admin2")) return SendInfoMessage(playerid,"Si komanda ne tau ");
	new vardas2[128],vardas[128];
	if (sscanf(params, "s[24]",vardas2))
	{
		SendInfoMessage(playerid,"Naudojimas /onlinetime [Vardas_Pavarde]");
		return 1;
	}
	mysql_real_escape_string(vardas2,vardas);
	new query[1024];
	format(query,sizeof(query),"SELECT SUM(`Variable`) From Logs WHERE UPPER(`Zaidejas`)=UPPER('%s') AND Veiksmas='Praleido' UNION SELECT SUM(`Variable`) From Logs WHERE UPPER(`Zaidejas`)=UPPER('%s') AND Veiksmas='N'",vardas,vardas);
	mysql_function_query(SQL, query, true, "SQL_Praleido", "is", playerid, vardas);
	return 1;
}


CMD:dyrtime(playerid,params[])
{
	if(!Pareigos(playerid,"Admin") && !Pareigos(playerid,"Admin2") && !Pareigos(playerid,"Dyrikai")) return SendInfoMessage(playerid,"Si komanda ne tau ");

	mysql_function_query(SQL, "SELECT Name, `Lead` From Account Where `Lead` > 0", true, "SQL_DyrList", "i", playerid);
	return 1;
}
CMD:admintime(playerid,params[])
{
	if(!Pareigos(playerid,"Admin") && !Pareigos(playerid,"Admin2")) return SendInfoMessage(playerid,"Si komanda ne tau ");

	mysql_function_query(SQL, "SELECT Name From Account Where Adminas=1", true, "SQL_AdminList", "i", playerid);
	return 1;
}
CMD:anuliuoti(playerid,params[])
{
	if(!Pareigos(playerid,"Admin") && !Pareigos(playerid,"Admin2")) return SendInfoMessage(playerid,"Si komanda ne tau ");

	ShowPlayerDialog(playerid, 15454, DIALOG_STYLE_MSGBOX, "Minutes", "Ar tikrai nori anuliuoti administratoriu ir direktoriu minutes?", "Taip","Ne");
	return 1;
}
CMD:debugon(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	DEBUG=!!strval(params);
	return 1;
}

CMD:testint(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	SetPlayerInterior(playerid,strval(params));
	return 1;
}

CMD:selectobj(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	SelectObject(playerid);
	SendClientMessage(playerid, 0xFFFFFFFF, "SERVER: Please select the object you'd like to edit!");
	return 1;
}
CMD:cancelobj(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	CancelEdit(playerid);
	SendClientMessage(playerid, 0xFFFFFFFF, "SERVER: You stopped editing!");
	return 1;
}
CMD:weaptest(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	GivePlayerWeaponEx(playerid,strval(params),500);
	return 1;
}
CMD:unban(playerid,params[])
{
	if(!playerDB[playerid][admin] || (!Pareigos(playerid,"Banai") && !Pareigos(playerid,"Banai2"))) return SendClientMessage(playerid,RED,"Neturite tam pareigu");
	new uzrasas[128];
	new param[128];
	if(sscanf(params,"s[128]",param)) return SendInfoMessage(playerid,"Naudojimas: /unban [vardas_pavarde arba IP]");
	mysql_real_escape_string(param,param);
	format(uzrasas,128,"SELECT `Vardas` FROM `BANS` WHERE `Vardas` = '%s' or `IP`='%s'",param,param);
	mysql_function_query(SQL, uzrasas, true, "SQL_UnbanCheck", "is",playerid,param);
	
	return 1;
}

CMD:resetweps(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	foreach(Houses,houseid)
	{
		for(new slot;slot<12;slot++)
		{
			hInfo[houseid][gunas][slot]=0;
			hInfo[houseid][kulkos][slot]=0;
		}
	}
	new query[128];
	for(new slot;slot<12;slot++)
	{
		format(query,sizeof(query),"UPDATE `Namai` SET `Ginklas%i`=0,`Kulkos%i`=0",slot,slot);
		mysql_query(query); 
	}
	return 1;
}

CMD:loadvars(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	LoadVars();
	return 1;
}
CMD:savevars(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	SaveVars();
	return 1;
}
CMD:radiostart(playerid,params[])
{
	if(!Pareigos(playerid,"DJ2")) return 0;
	strcpy(g_StartRadio,params,128);
	return 1;
}
CMD:tohouse(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 1;
	new houseid = strval(params);
	SetPlayerPoz(playerid,hInfo[houseid][iconx],hInfo[houseid][icony],hInfo[houseid][iconz]);
	new vw;
	if(hInfo[houseid][daugiabutis]) vw=(MAX_HOUSES*2+MAX_BUSINESSES+hInfo[houseid][daugiabutis]-1);
	SetPlayerVirtualWorld(playerid,vw);
	return 1;
}

CMD:setjob(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new jobid,vardux[24];
	if(sscanf(params,"s[24]i",vardux,jobid)) return SendClientMessage(playerid,COLOR," * vardas ir jobid");
	new id = GetPlayeridMid(vardux);
	//if( id == playerid) return SendInfoMessage(playerid,"~r~Sau uzmesti negali.");
	if(id == INVALID_PLAYER_ID) return SendInfoMessage(playerid,"~r~Tokio zaidejo nera.");

	playerDB[id][specialybe]=jobid;
	return 1;
}

CMD:changehouse(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 1;
	new houseid = GetHouseID(playerid);
	if(houseid == -255) return SendClientMessage(playerid,RED,"ERROR");
	hInfo[houseid][Cost] = strval(params);
	new query[128];
	format(query,sizeof(query),"UPDATE `Namai` SET `Cost`=%i WHERE `ID`=%i",hInfo[houseid][Cost],houseid);
	mysql_query(query);
	return 1;
}

CMD:infomessage(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	SendInfoMessage(playerid,params);
	return 1;
}
CMD:lol(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	FireTime();
	return 1;
}
CMD:createhouse(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new type;
	if(sscanf(params,"d",type)) return SendClientMessage(playerid,COLOR," * Naudojimas: /createhouse [Lygis 1-5(daugiabuciams 10-14)]");
	if(type == 0 || (type > 5 && type < 10) || type == 15 || type > 16) return SendClientMessage(playerid,COLOR," * Naudojimas: /createhouse [Lygis 1-5(daugiabuciams 10-15)(apts 16)]");
	new idx = FindEmtyHouseSlot();
	if(idx == -1) return SendClientMessage(playerid,COLOR,"* Pasiektas namu limitas!");
	format(hInfo[idx][Name],24,"Nera");
	format(hInfo[idx][Renter],24,"ForRent");
	hInfo[idx][Rentable] = 0;
	hInfo[idx][Rentcost] = 0;
	if(type >= 10 && type != 16) hInfo[idx][daugiabutis]=(GetPlayerVirtualWorld(playerid)-(MAX_HOUSES*2+MAX_BUSINESSES)+1);
	else hInfo[idx][daugiabutis]=0;

	if(type == 16)
	{
		new poly = GetPlayerPoly(playerid);
		if(poly == -1)
			return SendClientMessage(playerid, -1, "Poligonas nerastas!");
		hInfo[idx][polyId] = poly;
	}
	else
	{
		hInfo[idx][polyId] = -1;
	}
	new randomas,normalvalue;
	switch(type)
	{
		case 1: normalvalue=10000,randomas=random(500);
		case 2: normalvalue=100000,randomas=random(500);
		case 3: normalvalue=200000,randomas=random(1000);
		case 4: normalvalue=350000,randomas=random(1500);
		case 5: normalvalue=500000,randomas=random(2000);
		case 10: normalvalue=60000,randomas=random(50);
		case 11: normalvalue=55000,randomas=random(50);
		case 12: normalvalue=50000,randomas=random(50);
		case 13: normalvalue=45000,randomas=random(50);
		case 14: normalvalue=40000,randomas=random(50);
		case 16: normalvalue=500000,randomas=random(5000);
		default: 
		{
			return SendClientMessage(playerid, -1, "Tipas nerastas!");
		}
	}
	new houseid = idx;
	hInfo[houseid][Cost] = (normalvalue+(randomas*100));
	hInfo[houseid][Locked] = 1;
	hInfo[houseid][tobulina] = 0;
	hInfo[houseid][hmaistas] = 0;
	if(type <= 5) hInfo[houseid][vidus] = type-1;
	else hInfo[houseid][vidus]=0;
	hInfo[houseid][zole] = 0;
	hInfo[houseid][nark] = 0;
	hInfo[houseid][pinigai] = 0;
	hInfo[houseid][hRadio]=0;
	GetPlayerPos(playerid,hInfo[houseid][iconx],hInfo[houseid][icony],hInfo[houseid][iconz]);
	new query[512];
	format(query,sizeof(query),"INSERT INTO `Namai`(`ID`,`Cost`,`Locked`,`Vidus`,`X`,`Y`,`Z`,`Daugiabutis`,`polyId`) VALUES(%i,%i,%i,%i,'%f','%f','%f',%i,%i)",
				idx,hInfo[houseid][Cost],hInfo[houseid][Locked],hInfo[houseid][vidus],hInfo[houseid][iconx],hInfo[houseid][icony],hInfo[houseid][iconz],hInfo[houseid][daugiabutis],hInfo[houseid][polyId]);
	mysql_query(query);
	new zinute[128];
	Iter_Add(Houses, idx);
	new vw;
	if(hInfo[houseid][daugiabutis]) vw=(MAX_HOUSES*2+MAX_BUSINESSES+hInfo[houseid][daugiabutis]-1);
	HousePickup[houseid] = CreatePickupA(1273, 23, hInfo[houseid][iconx],hInfo[houseid][icony],hInfo[houseid][iconz],vw);//not bought
	format(zinute,sizeof(zinute),"Namas Nr.: {FF0000}%i",houseid);
	HouseText[houseid] = CreateDynamic3DTextLabel(zinute, COLOR_WHITE, hInfo[houseid][iconx],hInfo[houseid][icony],hInfo[houseid][iconz], 50,  _,_, 1,vw);
	
	print("-");
	print("--------------House Created--------------");
	printf("- Houseid: %d", houseid);
	printf("- Buy Cost: %d€", hInfo[houseid][Cost]);
	print("-----------------------------------------");
	print("-");
	SendClientMessage(playerid,COLOR,"* Namas sukurtas!");
	return 1;
}
CMD:createdgb(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new x = FindEmtyDGBSlot();
	if(x == -1) return SendClientMessage(playerid,RED," * ERROR");
	GetPlayerPos(playerid,Daugiabuciai[x][dX],Daugiabuciai[x][dY],Daugiabuciai[x][dZ]);
	new string[128];
	format(string,sizeof(string),"Daugiabutis Nr.:{FF0000} %i",x+1);
	Daugiabuciai[x][dIT] = CreateDynamic3DTextLabel(string,COLOR_YELLOW,Daugiabuciai[x][dX],Daugiabuciai[x][dY],Daugiabuciai[x][dZ],20.0);
	Daugiabuciai[x][dEX] = 1;
	Daugiabuciai[x][dLift] = 0;
	Iter_Add(Daugiabuciai, x);
	return 1;
}
CMD:movedgb(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new x;
	if(sscanf(params,"i",x)) return SendClientMessage(playerid,RED," * /movedgb [id]");
	x--;
	if(x == -1 || !Daugiabuciai[x][dEX]) return SendClientMessage(playerid,RED," * ERROR");
	GetPlayerPos(playerid,Daugiabuciai[x][dX],Daugiabuciai[x][dY],Daugiabuciai[x][dZ]);
	DestroyDynamic3DTextLabel(Daugiabuciai[x][dIT]);
	new string[128];
	format(string,sizeof(string),"Daugiabutis Nr.:{FF0000} %i",x+1);
	Daugiabuciai[x][dIT] = CreateDynamic3DTextLabel(string,COLOR_YELLOW,Daugiabuciai[x][dX],Daugiabuciai[x][dY],Daugiabuciai[x][dZ],20.0);
	return 1;
}
CMD:deletedgb(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	foreach(Daugiabuciai,x)
	{
		if(IsPlayerInRangeOfPointEx(5.0,playerid,Daugiabuciai[x][dX],Daugiabuciai[x][dY],Daugiabuciai[x][dZ]))
		{
			DestroyDynamic3DTextLabel(Daugiabuciai[x][dIT]);
			Daugiabuciai[x][dEX]=0;
			Iter_SafeRemove(Daugiabuciai,x,x);
			return 1;
		}
	}
	SendClientMessage(playerid,RED," * Error!");
	return 1;
}

CMD:fixweaps(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new query[2000];
	for(new i;i<12;i++)
	{
		format(query,sizeof(query),"UPDATE `Account` SET `Ginklas%i`=0,`Ammo%i`=0",i,i);
		mysql_query(query);
		format(query,sizeof(query),"UPDATE `Namai` SET `Ginklas%i`=0,`Kulkos%i`=0",i,i);
		mysql_query(query);
	}
	return SendClientMessage(playerid, COLOR," * Pavyko!");
}


CMD:bandomkeist(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	if(!isnull(params)) playerDB[playerid][pgang]=strval(params);
	ChangeGangTag(playerid,GetClosestTag(playerid));
	return 1;
}
CMD:pelnas(playerid,params[])
{
	if(!Pareigos(playerid,"Dyrikai") && !Pareigos(playerid, "Gaujos")) return SendInfoMessage(playerid,"Si komanda ne tau ");
	new kiekis,id;
	if(sscanf(params,"ii",id,kiekis))
	{
		SendClientMessage(playerid,COLOR," * Naudojimas: /pelnas [id] [kiekis]");
		SendClientMessage(playerid,COLOR," * Jei norite patikrinti pelna, rasykite /pelnas [id] 0");
		return 1;
	}
	if(id < 1 || id >= 100) return SendInfoMessage(playerid,"netinkamas id");
	if(Pareigos(playerid,"Gaujos") && !Pareigos(playerid,"Dyrikai") && id != 98 && id != 90 && id != 58)
	{
		return SendInfoMessage(playerid, "Gauju priziuretojas gali keisti tik nelegaliu darbu pelna!");
	}
	if(kiekis == 0)
	{
		new msg[128];
		format(msg,sizeof(msg),"Dabar Firmos pelnas yra: %i €.",pelnas[id-1]);
		SendClientMessage(playerid,RED,msg);
	}
	else if(kiekis < 0)
	{
		return SendInfoMessage(playerid, "Netinkamas kiekis!");
	}
	else
	{
		if(GetPlayerMoneyA(playerid) < kiekis) return SendInfoMessage(playerid,"Jus tiek neturite!");
		GivePlayerMoneyA(playerid, -kiekis);
		new msg[128];
		pelnas[id-1]=pelnas[id-1]+kiekis;
		format(msg,sizeof(msg),"Po pridejimo firmos pelnas yra: %i €.",pelnas[id-1]);
		SendClientMessage(playerid,RED,msg);
		MLog(playerid,"Padejo i pelna","ii",id,kiekis);
	}
	return 1;
}

CMD:creategarage(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new houseid,type;
	if(sscanf(params,"dd",houseid,type)) return SendClientMessage(playerid,COLOR," * /creategarage [houseid] [tipas 1-3]");
	if(type < 1 || type > 3) return SendClientMessage(playerid,COLOR," * /creategarage [houseid] [tipas 1-3]");
	new vehicleid = GetPlayerVehicleID(playerid);
	if(!vehicleid) return SendClientMessage(playerid,COLOR," * Turi nustatinet sededamas masinoj. Atsisuk taip, kad masinos priekis ziuretu i priesinga puse nei vartai.");
	hInfo[houseid][Cost] = (hInfo[houseid][Cost]+100000);
	hInfo[houseid][Garazas]=type;
	GetVehiclePos(vehicleid,hInfo[houseid][GarazoX],hInfo[houseid][GarazoY],hInfo[houseid][GarazoZ]);
	GetVehicleZAngle(vehicleid,hInfo[houseid][GarazoA]);
	DestroyDynamic3DTextLabel(GarazoText[houseid]);
	new zinute[256];
	format(zinute,sizeof(zinute),"Garaþas Nr.: {FF0000}%i\n{FFFFFF}Noredami ieiti, spauskite {FF0000}~k~~GROUP_CONTROL_BWD~",houseid);
	GarazoText[houseid] = CreateDynamic3DTextLabel(zinute, COLOR_WHITE, hInfo[houseid][GarazoX],hInfo[houseid][GarazoY],hInfo[houseid][GarazoZ], 10, _,_, 1);
	new query[256];
	format(query,sizeof(query),"UPDATE `Namai` SET `Garazas`=%i, `GarazoX`='%f', `GarazoY`='%f', `GarazoZ`='%f', `GarazoA`='%f',`Cost`=%i WHERE `ID`=%i",
													hInfo[houseid][Garazas],hInfo[houseid][GarazoX],hInfo[houseid][GarazoY],hInfo[houseid][GarazoZ],hInfo[houseid][GarazoA],hInfo[houseid][Cost],houseid);
	mysql_query(query);
	return 1;
}
CMD:deletegarage(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new houseid;
	if(sscanf(params,"d",houseid)) return SendClientMessage(playerid,COLOR," * /deletegarage [houseid]");
	hInfo[houseid][Garazas]=0;
	DestroyDynamic3DTextLabel(GarazoText[houseid]);
	return 1;
}
CMD:deletehouse(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new idx = -1;
    foreach(Houses,i)
	{
	    if(IsPlayerInRangeOfPointEx(2.0, playerid, hInfo[i][iconx],hInfo[i][icony],hInfo[i][iconz]))
		{
			if(hInfo[i][daugiabutis])
				if(GetPlayerVirtualWorld(playerid)-(MAX_HOUSES*2+MAX_BUSINESSES) != hInfo[i][daugiabutis]) continue;
	        idx=i;
		}
	}
	if(idx == -1) return SendClientMessage(playerid,COLOR," * Tu ne prie namo!");
	new query[128];
	format(query,sizeof(query),"DELETE From `Namai` WHERE `ID`=%i LIMIT 1",idx);
	mysql_query(query);
	format(hInfo[idx][Name],24,"");
	format(hInfo[idx][Renter],24,"ForRent");
	hInfo[idx][Rentable] = 0;
	hInfo[idx][Rentcost] = 0;
	new houseid = idx;
	hInfo[houseid][Cost] = 0;
	hInfo[houseid][Locked] = 0;
	hInfo[houseid][tobulina] = 0;
	hInfo[houseid][hmaistas] = 0;
	hInfo[houseid][vidus] = 0;
	hInfo[houseid][zole] = 0;
	hInfo[houseid][nark] = 0;
	hInfo[houseid][pinigai] = 0;
	hInfo[houseid][hRadio]=0;
	hInfo[houseid][Garazas]=0;
	Iter_Remove(Houses, idx);
	DestroyPickup(HousePickup[houseid]);
	DestroyDynamic3DTextLabel(HouseText[houseid]);
	DestroyDynamic3DTextLabel(GarazoText[houseid]);
	return 1;
}
CMD:createbiz(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new cost,type;
	if(sscanf(params,"dd",cost,type)) return SendClientMessage(playerid,COLOR," * Naudojimas: /createbiz [Kaina] [Tipas]");
	new Float:Pos[3];
	GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
	new idx = FindEmtyBizSlot();
	if(idx == -1) return SendClientMessage(playerid,COLOR,"* Pasiektas bizniu limitas!");
	format(BusinessInfo[idx][bName],64,"-");
	format(BusinessInfo[idx][bOwner],64,"Nera");
	BusinessInfo[idx][bEnterX] = Pos[0];
    BusinessInfo[idx][bEnterY] = Pos[1];
    BusinessInfo[idx][bEnterZ] = Pos[2];
    BusinessInfo[idx][EnterWorld] = idx+MAX_HOUSES*2;
    BusinessInfo[idx][bPrice] = cost;
    BusinessInfo[idx][bNumber] = 1;
    BusinessInfo[idx][bEarning] = 0;
    BusinessInfo[idx][bType] = type;
    BusinessInfo[idx][bOwned] = 0;
    Iter_Add(Businesses, idx);
    switch(type)
    {
		case 1:
		{
		    new id = random(sizeof(SportoKlubai));
          	BusinessInfo[idx][bExitX] = SportoKlubai[id][bX];
		    BusinessInfo[idx][bExitY] = SportoKlubai[id][bY];
		    BusinessInfo[idx][bExitZ] = SportoKlubai[id][bZ];
		    BusinessInfo[idx][EnterInterior] = SportoKlubai[id][bInt];
		}
		case 2:
		{
		    new id = random(sizeof(MaistoPardes));
          	BusinessInfo[idx][bExitX] = MaistoPardes[id][bX];
		    BusinessInfo[idx][bExitY] = MaistoPardes[id][bY];
		    BusinessInfo[idx][bExitZ] = MaistoPardes[id][bZ];
		    BusinessInfo[idx][EnterInterior] = MaistoPardes[id][bInt];
		}
		case 3:
		{
		    new id = random(sizeof(RubuPardes));
          	BusinessInfo[idx][bExitX] = RubuPardes[id][bX];
		    BusinessInfo[idx][bExitY] = RubuPardes[id][bY];
		    BusinessInfo[idx][bExitZ] = RubuPardes[id][bZ];
		    BusinessInfo[idx][EnterInterior] = RubuPardes[id][bInt];
		}
		case 4:
		{
		    new id = random(sizeof(Klubai));
          	BusinessInfo[idx][bExitX] = Klubai[id][bX];
		    BusinessInfo[idx][bExitY] = Klubai[id][bY];
		    BusinessInfo[idx][bExitZ] = Klubai[id][bZ];
		    BusinessInfo[idx][EnterInterior] = Klubai[id][bInt];
		}
		case 5:
		{
		    new id = random(sizeof(CluckinPardes));
          	BusinessInfo[idx][bExitX] = CluckinPardes[id][bX];
		    BusinessInfo[idx][bExitY] = CluckinPardes[id][bY];
		    BusinessInfo[idx][bExitZ] = CluckinPardes[id][bZ];
		    BusinessInfo[idx][EnterInterior] = CluckinPardes[id][bInt];
		}
		case 6:
		{
		    new id = random(sizeof(GinkluPardes));
          	BusinessInfo[idx][bExitX] = GinkluPardes[id][bX];
		    BusinessInfo[idx][bExitY] = GinkluPardes[id][bY];
		    BusinessInfo[idx][bExitZ] = GinkluPardes[id][bZ];
		    BusinessInfo[idx][EnterInterior] = GinkluPardes[id][bInt];
		}
		case 7:
		{
		    /*new id = random(sizeof(Barai));
          	BusinessInfo[idx][bExitX] = Barai[id][bX];
		    BusinessInfo[idx][bExitY] = Barai[id][bY];
		    BusinessInfo[idx][bExitZ] = Barai[id][bZ];
		    BusinessInfo[idx][EnterInterior] = Barai[id][bInt]; */
			BusinessInfo[idx][bExitX] = -1543.4035;
		    BusinessInfo[idx][bExitY] = -446.2759;
		    BusinessInfo[idx][bExitZ] = 6.1000;
		    BusinessInfo[idx][EnterInterior] = 0;
		}
		case 8:
		{
		    new id = random(sizeof(FejerverkuPardes));
          	BusinessInfo[idx][bExitX] = FejerverkuPardes[id][bX];
		    BusinessInfo[idx][bExitY] = FejerverkuPardes[id][bY];
		    BusinessInfo[idx][bExitZ] = FejerverkuPardes[id][bZ];
		    BusinessInfo[idx][EnterInterior] = FejerverkuPardes[id][bInt];
		}
		case 9:
		{
		    new id = random(sizeof(XXXPardes));
          	BusinessInfo[idx][bExitX] = XXXPardes[id][bX];
		    BusinessInfo[idx][bExitY] = XXXPardes[id][bY];
		    BusinessInfo[idx][bExitZ] = XXXPardes[id][bZ];
		    BusinessInfo[idx][EnterInterior] = XXXPardes[id][bInt];
		}
		case 10:
		{
		    new id = random(sizeof(MesainiuPardes));
          	BusinessInfo[idx][bExitX] = MesainiuPardes[id][bX];
		    BusinessInfo[idx][bExitY] = MesainiuPardes[id][bY];
		    BusinessInfo[idx][bExitZ] = MesainiuPardes[id][bZ];
		    BusinessInfo[idx][EnterInterior] = MesainiuPardes[id][bInt];
		}
		case 11:
		{
		    new id = random(sizeof(Picerijos));
          	BusinessInfo[idx][bExitX] = Picerijos[id][bX];
		    BusinessInfo[idx][bExitY] = Picerijos[id][bY];
		    BusinessInfo[idx][bExitZ] = Picerijos[id][bZ];
		    BusinessInfo[idx][EnterInterior] = Picerijos[id][bInt];
		}
		case 12:
		{
		    new id = random(sizeof(SpurguPardes));
          	BusinessInfo[idx][bExitX] = SpurguPardes[id][bX];
		    BusinessInfo[idx][bExitY] = SpurguPardes[id][bY];
		    BusinessInfo[idx][bExitZ] = SpurguPardes[id][bZ];
		    BusinessInfo[idx][EnterInterior] = SpurguPardes[id][bInt];
		}
		case 13:
		{
		    new id = random(sizeof(AkiniuPardes));
          	BusinessInfo[idx][bExitX] = AkiniuPardes[id][bX];
		    BusinessInfo[idx][bExitY] = AkiniuPardes[id][bY];
		    BusinessInfo[idx][bExitZ] = AkiniuPardes[id][bZ];
		    BusinessInfo[idx][EnterInterior] = AkiniuPardes[id][bInt];
		}
		case 14:
		{
		    new id = random(sizeof(Draudimai));
          	BusinessInfo[idx][bExitX] = Draudimai[id][bX];
		    BusinessInfo[idx][bExitY] = Draudimai[id][bY];
		    BusinessInfo[idx][bExitZ] = Draudimai[id][bZ];
		    BusinessInfo[idx][EnterInterior] = Draudimai[id][bInt];
		}
		case 15:
		{
		    new id = random(sizeof(Losimai));
          	BusinessInfo[idx][bExitX] = Losimai[id][bX];
		    BusinessInfo[idx][bExitY] = Losimai[id][bY];
		    BusinessInfo[idx][bExitZ] = Losimai[id][bZ];
		    BusinessInfo[idx][EnterInterior] = Losimai[id][bInt];
		}
		case 16:
		{
		    new id = random(sizeof(Hoteliai));
          	BusinessInfo[idx][bExitX] = Hoteliai[id][bX];
		    BusinessInfo[idx][bExitY] = Hoteliai[id][bY];
		    BusinessInfo[idx][bExitZ] = Hoteliai[id][bZ];
		    BusinessInfo[idx][EnterInterior] = Hoteliai[id][bInt];
		}
		case 17:
		{
		    new id = random(sizeof(Bankai));
          	BusinessInfo[idx][bExitX] = Bankai[id][bX];
		    BusinessInfo[idx][bExitY] = Bankai[id][bY];
		    BusinessInfo[idx][bExitZ] = Bankai[id][bZ];
		    BusinessInfo[idx][EnterInterior] = Bankai[id][bInt];
		}
		case 18: // baldai
		{
			BusinessInfo[idx][bExitX] = 1985.3573;
		    BusinessInfo[idx][bExitY] = 696.0308;
		    BusinessInfo[idx][bExitZ] = 2819.5959;
		    BusinessInfo[idx][EnterInterior] = 3;
		}
		case 19: // elektronika
		{
			BusinessInfo[idx][bExitX] = -870.2403;
		    BusinessInfo[idx][bExitY] = -1214.9985;
		    BusinessInfo[idx][bExitZ] = 3248.9958;
		    BusinessInfo[idx][EnterInterior] = 2;
		}
		case 20: // interjerai
		{
			BusinessInfo[idx][bExitX] = -897.2283;
		    BusinessInfo[idx][bExitY] = -2586.2732;
		    BusinessInfo[idx][bExitZ] = 2146.5549;
		    BusinessInfo[idx][EnterInterior] = 1;
		}
		case 21: // degalines
		{
			new id = random(2);
			if(id == 0) // didele
			{
				/*BusinessInfo[idx][bExitX] = 1927.2897; 
				BusinessInfo[idx][bExitY] = -1772.1680;
				BusinessInfo[idx][bExitZ] = 0.3869;*/
				BusinessInfo[idx][bExitX] = 1957.2231; 
				BusinessInfo[idx][bExitY] = -1742.2622;
				BusinessInfo[idx][bExitZ] = -5.1705;

				BusinessInfo[idx][EnterInterior] = 3;
			
			
			}
			else // maza
			{
				/*
				BusinessInfo[idx][bExitX] = 2511.1814;
				BusinessInfo[idx][bExitY] = -1477.1946;
				BusinessInfo[idx][bExitZ] = -0.734;
				*/
				BusinessInfo[idx][bExitX] = 1010.2056;
				BusinessInfo[idx][bExitY] = -934.5389;
				BusinessInfo[idx][bExitZ] = 23.6933;

				BusinessInfo[idx][EnterInterior] = 3;
			
			}
          
		
		}
    }
	new string[128];

    if(BusinessInfo[idx][bOwned] == 0)
		format(string, sizeof(string), VERSLAS_PARDUODAMAS, GetBussinessType(BusinessInfo[idx][bType]),BusinessInfo[idx][bPrice]);
	else
    	format(string, sizeof(string), VERSLAS_NEPARDUODAMAS, BusinessInfo[idx][bName],BusinessInfo[idx][bOwner],GetBussinessType(BusinessInfo[idx][bType]));

	businesstext[idx] = CreateDynamic3DTextLabel(string,0x00BC00FF,BusinessInfo[idx][bEnterX],BusinessInfo[idx][bEnterY],BusinessInfo[idx][bEnterZ],40.0, _,_, 1);
	isejimotext[idx] = CreateDynamic3DTextLabel("Iðëjimas",COLOR_WHITE,BusinessInfo[idx][bExitX],BusinessInfo[idx][bExitY],BusinessInfo[idx][bExitZ],30.0, _,_, BusinessInfo[idx][EnterWorld], 1);
	return 1;
}

CMD:tobiz(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new i = strval(params);
	SetPlayerPoz(playerid,BusinessInfo[i][bEnterX],BusinessInfo[i][bEnterY],BusinessInfo[i][bEnterZ]);
	return 1;
}
CMD:changebiz(playerid,params[])
{
	if(!playerDB[playerid][admin]) return 0;
	new cost;
	if(sscanf(params,"d",cost)) return SendInfoMessage(playerid,"Naudojimas: /changebiz [Kaina]");
	new idx = -1;
    foreach(Businesses,i)
	{
	    if(IsPlayerInRangeOfPointEx(2.0, playerid, BusinessInfo[i][bEnterX],BusinessInfo[i][bEnterY],BusinessInfo[i][bEnterZ]))
	        idx=i;
	}
	if(idx == -1) return print("Error!");
	BusinessInfo[idx][bPrice] = cost;
	DestroyDynamic3DTextLabel(businesstext[idx]);
	new string[128];

    if(BusinessInfo[idx][bOwned] == 0)
		format(string, sizeof(string), VERSLAS_PARDUODAMAS, GetBussinessType(BusinessInfo[idx][bType]),BusinessInfo[idx][bPrice]);
	else
    	format(string, sizeof(string), VERSLAS_NEPARDUODAMAS, BusinessInfo[idx][bName],BusinessInfo[idx][bOwner],GetBussinessType(BusinessInfo[idx][bType]));

	businesstext[idx] = CreateDynamic3DTextLabel(string,0x00BC00FF,BusinessInfo[idx][bEnterX],BusinessInfo[idx][bEnterY],BusinessInfo[idx][bEnterZ],40.0, _,_, 1);
	return 1;
	
}

CMD:bizid(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
    new idx = -1;
    foreach(Businesses,i)
	{
	    if(IsPlayerInRangeOfPointEx(2.0, playerid, BusinessInfo[i][bEnterX],BusinessInfo[i][bEnterY],BusinessInfo[i][bEnterZ]))
	    {
			new msg[128];
			format(msg,sizeof(msg),"%i",idx);
			SendClientMessage(playerid,-1,msg);
		}
	}

	return 1;
}
CMD:deletebiz(playerid,params[])
{
    if(!IsPlayerAdmin(playerid)) return 0;
    new idx = -1;
    foreach(Businesses,i)
	{
	    if(IsPlayerInRangeOfPointEx(2.0, playerid, BusinessInfo[i][bEnterX],BusinessInfo[i][bEnterY],BusinessInfo[i][bEnterZ]))
	        idx=i;
	}
	if(idx == -1) idx = strval(params);
//	if(BusinessInfo[idx][bType]==17) Iter_Remove(BusinessBankai,idx);
	format(BusinessInfo[idx][bName],64,"-");
	format(BusinessInfo[idx][bOwner],64,"Nera");
	BusinessInfo[idx][bEnterX] = 0.000;
    BusinessInfo[idx][bEnterY] = 0.000;
    BusinessInfo[idx][bEnterZ] = 0.000;
    BusinessInfo[idx][EnterWorld] = 0;
    BusinessInfo[idx][bPrice] = 0;
    BusinessInfo[idx][bNumber] = 0;
    BusinessInfo[idx][bEarning] = 0;
    BusinessInfo[idx][bType] = 0;
    BusinessInfo[idx][bOwned] = 0;
    BusinessInfo[idx][bExitX] = 0.000;
    BusinessInfo[idx][bExitY] = 0.000;
    BusinessInfo[idx][bExitZ] = 0.000;
    BusinessInfo[idx][EnterInterior] = 0;
    DestroyDynamic3DTextLabel(businesstext[idx]);
	DestroyDynamic3DTextLabel(isejimotext[idx]);
    Iter_Remove(Businesses,idx);
    return 1;
}

CMD:apleistiza(playerid,params[])
{
	if(IsPlayerAdmin(playerid)) return ApleistiVerslai();
	return 0;
}
CMD:saveallbiz(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	SendClientMessage(playerid, -1, "* Saving..");
	SaveBusinesses();
	SendClientMessage(playerid, -1, "* Done!");
	return 1;
}

CMD:apmokymai(playerid,params[])
{
	if(IsPlayerAdmin(playerid))
	{
		playerDB[playerid][apmokymai]=1;
		Apmokymai(playerid);
		return 1;
	}
	return 0;
}
CMD:serverstats(playerid,params[])
{
	if(IsPlayerAdmin(playerid)) ServerStats(playerid,0);
	return 1;
}
CMD:fururespawn(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	FuruRespawn();
	return 1;
}
CMD:muzikaex(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	ShowPlayerDialog(playerid,2897,DIALOG_STYLE_INPUT,"Adresas","Ivesk adresa","Ok","Cancel");
	return 1;
}
CMD:medalis(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new color,vardas[128];
	if(sscanf(params,"is[128]",color,vardas)) return SendInfoMessage(playerid,"Neteisingas komandos naudojimas! /medalis [1,2,3] [Vardas_Pavarde]");
	new mid = GetPlayeridMid(vardas);
	if(mid != INVALID_PLAYER_ID)
	{
		switch(color)
		{
			case 1: SetPlayerColor(mid,0xC98910FF);
			case 2: SetPlayerColor(mid,0xD2D2D230);
			case 3: SetPlayerColor(mid,0x965A38FF);
		}
	}
	new string[128];
	switch(color)
	{
		case 1: format(string,sizeof(string),"0xC98910FF");
		case 2: format(string,sizeof(string),"0xD2D2D230");
		case 3: format(string,sizeof(string),"0x965A38FF");
	}
	mysql_real_escape_string(vardas, vardas);
	new query[150];
	format(query,sizeof(query),"INSERT INTO Spalvos (Vardas,Color) VALUES ('%s','%s') ON DUPLICATE KEY UPDATE Color='%s'",vardas,string,string);
	mysql_query(query);
	return 1;
}
CMD:premija(playerid,params[])
{
    	if(!IsPlayerAdmin(playerid)) return 0;
		//if(!playerDB[playerid][admin]){SendClientMessage(playerid,WHITE,"* *** Tokios komandos nera. Visos komandos /Pagalba *** *"); return 1;}
		new daug;
		if (sscanf(params, "d",daug))
		{
			SendClientMessage(playerid,WHITE,"* *** Tokios komandos nera. Visos komandos /Pagalba *** *");
			return 1;
		}
		GivePlayerMoneyA(playerid,daug);
		SendClientMessage(playerid,0xFF000090,"Sekmingai nuknisai premija.");
		return 1;
}
CMD:skirtidyr(playerid,params[])
{
        if(!playerDB[playerid][admin]) return 0;
		if(!Pareigos(playerid,"Dyrikai") && !Pareigos(playerid,"Gaujos")) return SendInfoMessage(playerid,"Si komanda ne tau ");
		new vardas[128],laikas;
		if (sscanf(params, "s[24]d",vardas,laikas))
		{
			SendInfoMessage(playerid,"Naudojimas /skirtidyr [Vardas_Pavarde] [id]");
			return 1;
		}
		if(Pareigos(playerid,"Gaujos") && !Pareigos(playerid,"Dyrikai") && laikas != 98 && laikas != 90 && laikas != 58)
		{
			return SendInfoMessage(playerid, "Gauju priziuretojas gali skirti tik nelegaliu darbu direktorius");
		}
		new id = GetPlayeridMid(vardas);
		if(laikas < 1 || laikas > 100) return SendInfoMessage(playerid,"Naudok /nuimtidyr");
		if(!IsPlayerConnected(id) || id == INVALID_PLAYER_ID || playerDB[id][authstate]!=4) 
		{ 
			new query[128];
			mysql_real_escape_string(vardas, vardas);
			format(query,sizeof(query),"SELECT `Lead` FROM `Account` WHERE `Name`='%s' LIMIT 1",vardas);
			mysql_function_query(SQL, query, true, "SQL_Skirti", "iis",playerid,laikas,vardas);
			
			return 1;
		}
// SendInfoMessage(playerid,"Tokio zaidejo nera"); return 1;
		playerDB[id][plead] = laikas;
		SavePlayerData(id,true);
		SendClientMessage(id, 0xD9E916FF, "* Jus buvote paverstas direktoriumi.");
		ProcessAchievement(id,94);
		SendClientMessage(playerid, 0xD9E916FF, "* Sekmingai pavertete direktoriumi.");
		return 1;
}

CMD:nuimtidyr(playerid,params[])
{
		if(!playerDB[playerid][admin]) return 0;
		if(!Pareigos(playerid,"Dyrikai") && !Pareigos(playerid,"Gaujos")) return SendInfoMessage(playerid,"Si komanda ne tau ");
		new vardas[128],priezastis[128];
		if (sscanf(params, "s[24]s[128]",vardas,priezastis))
		{
			SendInfoMessage(playerid,"Naudojimas /nuimtidyr [Vardas_Pavarde] [priezastis]");
			return 1;
		}

		new id = GetPlayeridMid(vardas);
		if(!IsPlayerConnected(id) || id == INVALID_PLAYER_ID || playerDB[id][authstate]!=4)
		{
			new query[256];
			mysql_real_escape_string(vardas, vardas);
			format(query,sizeof(query),"SELECT `Lead` FROM `Account` WHERE `Name`='%s' LIMIT 1",vardas);
			mysql_function_query(SQL, query, true, "SQL_Nuimti", "iss",playerid,vardas,priezastis);
			return 1;
		}
		else
		{
			new leadas = playerDB[id][plead];
			if(playerDB[id][plead] == 0) return SendInfoMessage(playerid,"Zaidejas ne direktorius!");
			if(Pareigos(playerid,"Gaujos") && !Pareigos(playerid,"Dyrikai") && leadas != 98 && leadas != 90 && leadas != 58)
			{
				return SendInfoMessage(playerid, "Gauju priziuretojas gali nuimti tik nelegaliu darbu direktorius");
			}
			playerDB[id][plead]=0;
			new msg[128];
			format(msg,sizeof(msg),"Jums buvo nuimtos direktoriaus pareigos.~Priezastis: %s",priezastis);
			EAtaskaita("Savivaldybe",ReturnName(id),"Pareigos",msg);
			SendInfoMessage(playerid,"Sekmingai nuemei direktoriu.");
		}
		return 1;
}

CMD:aktyvumas(playerid,params[])
{
	if(!Pareigos(playerid,"Admin") && !Pareigos(playerid,"Admin2")) 
		return 0;
	new vardas[128];
	mysql_real_escape_string(vardas,vardas);
	if (sscanf(params, "s[24]",vardas))
	{
		SendInfoMessage(playerid,"Naudojimas /aktyvumas [Vardas_Pavarde]");
		return 1;
	}
	new query[256];
	format(query,256,"SELECT SUM(TIMESTAMPDIFF(Minute,Login,Logout)), SUM(`Time`) FROM Login WHERE `Name`='%s' AND Login > SUBDATE(NOW(), 7) AND Logout is NOT NULL", vardas);
	mysql_function_query(SQL, query, true, "SQL_ShowAktyvumas", "is", playerid,vardas);
	return 1;
}

CMD:skirtiadm(playerid,params[])
{
		if(!Pareigos(playerid,"Admin") && !Pareigos(playerid,"Admin2")) return SendInfoMessage(playerid,"Si komanda ne tau ");
		new vardas[128],laikas;
		if (sscanf(params, "s[24]d",vardas,laikas))
		{
			SendInfoMessage(playerid,"Naudojimas /skirtiadm [Vardas_Pavarde] [1/0]");
			return 1;
		}
		new id = GetPlayeridMidEx(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio zaidejo nera"); return 1;}


		playerDB[id][admin] = !!laikas;
		playerDB[id][invisible]=false;
		TextDrawHideForPlayer(id, InvisTD);
		//SavePlayerData(id,true);
		if(laikas == 0)
		{
			SendClientMessage(id, 0xD9E916FF, "* Jums buvo nuimtas administratorius.");
			SendClientMessage(playerid, 0xD9E916FF, "* Nuimiai administratoriu.");
			return 1;
		}
		SendClientMessage(id, 0xD9E916FF, "* Jus buvote paverstas administratoriumi.");
		ProcessAchievement(id,94);
		SendClientMessage(playerid, 0xD9E916FF, "* Sekmingai pavertete administratoriumi.");
		return 1;
}
CMD:nuimtiadm(playerid,params[])
{
		if(!playerDB[playerid][admin]) return SendInfoMessage(playerid,"Si komanda ne tau");

		if(!Pareigos(playerid,"Admin") 
			&& !Pareigos(playerid,"Admin2")
			&& !Pareigos(playerid,"Dyrikai")
			&& !Pareigos(playerid,"Forumas")
			&& !Pareigos(playerid,"Gaujos")
			&& !Pareigos(playerid,"Discord")) return SendInfoMessage(playerid,"Si komanda ne tau");

		new vardas2[128],vardas[128];
		if (sscanf(params, "s[24]",vardas2))
		{
			SendInfoMessage(playerid,"Naudojimas /nuimtiadm [Vardas_Pavarde]");
			return 1;
		}
		new bool:superadmin = Pareigos(playerid,"Admin") || Pareigos(playerid,"Admin2");
		if(!superadmin && GetPVarInt(playerid, "Nuimtiadm") == 1)
		{
			SendClientMessage(playerid, -1, "Daugiau nuimti admin negali");
			return 1;
		}
		new id = GetPlayeridMidEx(vardas2);

		if (id != INVALID_PLAYER_ID) 
		{ 
			if(!playerDB[id][admin])
			{
				SendClientMessage(playerid, -1, "Zaidejas ne admin!");
				return 1;
			}
			playerDB[id][admin] = false;
			playerDB[id][invisible]=false;
			TextDrawHideForPlayer(id, InvisTD);
			SendClientMessage(id, 0xD9E916FF, "* Jums buvo nuimtas administratorius.");
			SendClientMessage(playerid, 0xD9E916FF, "* Nuemei administratoriu.");
			SetNuimtasAdmin(playerid);
			return 1;
		}

        mysql_real_escape_string(vardas2,vardas);
		new query[256];
		format(query,sizeof(query),"SELECT Adminas FROM `Account` WHERE `Name`='%s' LIMIT 1",vardas);
		mysql_function_query(SQL, query, true, "SQL_NuimtiA", "is", playerid,vardas);
		return 1;
}



CMD:setdyrikas(playerid,params[])
{
    	if(!IsPlayerAdmin(playerid)) return 0;
		if(!playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda tik administratoriams"); return 1;}
		new vardas[128],laikas;
		if (sscanf(params, "s[24]d",vardas,laikas))
		{
			SendClientMessage(playerid,WHITE,"* *** Tokios komandos nera. Visos komandos /Pagalba *** *");
			return 1;
		}
		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio zaidejo nera"); return 1;}


		playerDB[id][plead] = laikas;
		SavePlayerData(id,true);
		if(laikas == 0)
		{
			SendClientMessage(id, 0xD9E916FF, "* Jums buvo nuimtas direktorius.");
			SendClientMessage(playerid, 0xD9E916FF, "* Nuimiai direktoriu.");
			return 1;
		}
		SendClientMessage(id, 0xD9E916FF, "* Jus buvote paverstas direktoriumi.");
		SendClientMessage(playerid, 0xD9E916FF, "* Sekmingai pavertete ji direktoriumi.");

		return 1;
}

CMD:ppeln(playerid,params[])
{
    	if(!IsPlayerAdmin(playerid)) return 0;
		if(!playerDB[playerid][admin]){SendClientMessage(playerid,WHITE,"* *** Tokios komandos nera. Visos komandos /Pagalba *** *"); return 1;}
		new price,pricez;
		if (sscanf(params, "dd",price,pricez))
		{
			SendClientMessage(playerid,WHITE,"* *** Tokios komandos nera. Visos komandos /Pagalba *** *");
			return 1;
		}

		new msgeze[128];
		pelnas[price]=pelnas[price]+pricez;
		format(msgeze,sizeof(msgeze),"Dabar Firmos pelnas yra: %i €.",pelnas[price]);
		SendClientMessage(playerid,0xFF000090,msgeze);
		return 1;
}
CMD:iskraustyti(playerid,params[])
{
		if(!playerDB[playerid][admin]){SendClientMessage(playerid,WHITE,"* *** Tokios komandos nera. Visos komandos /Pagalba *** *"); return 1;}
		if(!Pareigos(playerid,"Namai")) return SendClientMessage(playerid, RED, " Si komanda ne tau ");

		new housenumber;
		if (sscanf(params, "d",housenumber))
		{
			SendClientMessage(playerid,WHITE,"* Naudojimas: /iskraustyti [namo nr]");
			return 1;
		}
		new str[50],pname[24];

		GetPlayerName(playerid, pname, 24);
		SendClientMessage(playerid, c_y, "Jus pagrobete nama!");
		format(str, sizeof(str), "%s pardave houseid 0",pname);
		print(str);
		GivePlayerMoneyA(playerid, (hInfo[housenumber][Cost] /4));
		ClearHouse(housenumber, /*deletebaldai=*/ true, /*deleteitems=*/ true);
		
		format(hInfo[housenumber][Name],255,"Nera");
		new query[128];
		format(query,sizeof(query),"UPDATE `Namai` SET `Name`='%s',`Locked`=1 WHERE `ID`=%i",hInfo[housenumber][Name],housenumber);
		mysql_query(query);
		new vw;
		if(hInfo[housenumber][daugiabutis]) vw=(MAX_HOUSES*2+MAX_BUSINESSES+hInfo[housenumber][daugiabutis]-1);
		DestroyPickup(HousePickup[housenumber]);
		HousePickup[housenumber] = CreatePickupA(1273, 23, hInfo[housenumber][iconx], hInfo[housenumber][icony], hInfo[housenumber][iconz],vw);
		new zinute[512];
		DestroyDynamic3DTextLabel(HouseText[housenumber]);
		format(zinute,sizeof(zinute),"Namas Nr.: {FF0000}%i",housenumber);
		HouseText[housenumber] = CreateDynamic3DTextLabel(zinute, COLOR_WHITE, hInfo[housenumber][iconx], hInfo[housenumber][icony], hInfo[housenumber][iconz], 50, _,_, 1,vw);
		return 1;
}
CMD:pelnadmin(playerid,params[])
{
    	if(!IsPlayerAdmin(playerid)) return 0;
		if(!playerDB[playerid][admin]){SendClientMessage(playerid,WHITE,"* *** Tokios komandos nera. Visos komandos /Pagalba *** *"); return 1;}
		new price;
		if (sscanf(params, "d",price))
		{
			SendClientMessage(playerid,WHITE,"* *** Tokios komandos nera. Visos komandos /Pagalba *** *");
			return 1;
		}
		new msg[128];
		format(msg,sizeof(msg),"Firmos pelnas yra: %i €.",pelnas[price]);
		SendClientMessage(playerid,0xFF000090,msg);
		return 1;
}
CMD:meras(playerid,params[])
{
	if(!Pareigos(playerid,"Dyrikai"))
	{
		SendInfoMessage(playerid,"Si komanda tik merui.");
		return 1;
	}
	new zinute[128];
	if(sscanf(params,"s[128]",zinute))
	{
		SendInfoMessage(playerid,"/meras [zinute] ");
		return 1;
	}
	new msg[128];
	new nam[24];
	GetPlayerName(playerid, nam, MAX_PLAYER_NAME);
	if(playerDB[playerid][lytis] == 2)
		format(msg, sizeof(msg), "* Merë %s: %s",nam, zinute);
	else
		format(msg, sizeof(msg), "* Meras %s: %s",nam, zinute);
	SendClientMessageToAllEx(0xFFD700FF,msg); // PREZ_COLOR
	return 1;
}
CMD:minigun(playerid,params[])
{
	if(!Pareigos(playerid,"Admin") && !Pareigos(playerid,"Admin2") && !(playerDB[playerid][admin] && helovynas))
	{
		SendInfoMessage(playerid,"Si komanda tik prezidentui.");
		return 1;
	}
	GivePlayerWeaponEx(playerid, WEAPON_MINIGUN, 20000);
	SendInfoMessage(playerid,"Sekmes naudojant!");
	return 1;
}
CMD:prez(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
	{
		SendInfoMessage(playerid,"Si komanda tik prezidentui.");
		return 1;
	}
	new zinute[128];
	if(sscanf(params,"s[128]",zinute))
	{
		SendInfoMessage(playerid,"/prez [zinute] ");
		return 1;
	}
	new msg[128];
	new nam[24];
	GetPlayerName(playerid, nam, MAX_PLAYER_NAME);
	format(msg, sizeof(msg), "* Prezidentas %s: %s",nam, zinute);
	SendClientMessageToAllEx(0xFFD700FF,msg);
	return 1;
}

CMD:vice(playerid,params[])
{
	if(!Pareigos(playerid,"Admin") && !Pareigos(playerid,"Admin2"))
	{
		SendInfoMessage(playerid,"Si komanda tik vice-prezidentui.");
		return 1;
	}
	new zinute[128];
	if(sscanf(params,"s[128]",zinute))
	{
		SendInfoMessage(playerid,"/vice [zinute] ");
		return 1;
	}
	new msg[128];
	new nam[24];
	GetPlayerName(playerid, nam, MAX_PLAYER_NAME);
	format(msg, sizeof(msg), "* Viceprezidentas %s: %s",nam, zinute);
	SendClientMessageToAllEx(0xFFD700FF,msg);
	return 1;
}
CMD:permaban(playerid,params[])
{
	if(!IsPlayerAdmin(playerid) && !Pareigos(playerid,"Permaban")) return 0;
	new vardas2[128],prz2[128],vardas[128],prz[128];
	if(sscanf(params,"s[24]s[128]",vardas2,prz2)){SendClientMessage(playerid, 0xD9E916FF, "* Perma Baninti zaideja: /permaban [dalis vardo] [priezastis]"); return 1;}
	mysql_real_escape_string(vardas2,vardas);
	mysql_real_escape_string(prz2,prz);
	new id = GetPlayeridMid(vardas);
	if (id == INVALID_PLAYER_ID){ SendClientMessage(playerid, 0xD9E916FF, "* Tokio vardo nera"); return 1;}
	if (playerDB[id][admin]){ SendClientMessage(playerid, 0xD9E916FF, "* Administratoriaus ismesti negalima."); return 1;}
	
	new msg[128],adminname[MAX_PLAYER_NAME];
	GetPlayerName(id,vardas,sizeof(vardas));
	GetPlayerName(playerid,adminname,sizeof(adminname));
	format(msg,sizeof(msg),"[ban] %s uzblokavo jus visiems laikams, nes jus %s",adminname,prz);
	TogglePlayerControllable(id,false);
	SendClientMessage(id,0xD9E916FF,msg);
	new query[512];
	new ip[24];
	GetPlayerIp(id, ip, 24);
	format(query,sizeof(query),"INSERT INTO Permabans(address,player,reason,time) VALUES ('%s','%s','%s',DATE_FORMAT(NOW(), '%%Y-%%m-%%dT%%+0000'))",ip, vardas, prz);
	mysql_query(query);
	BanEx(id,prz);
	format(msg,sizeof(msg),"[PERMA BAN] %s uzblokavo %s ( %s )",adminname,vardas,prz);
	SendClientMessageToAll(0xD9E916FF,msg);
	return 1;
}

CMD:nuimtivip(playerid,params[])
{
			if(!IsPlayerAdmin(playerid)) return 0;
			new vardas[MAX_PLAYER_NAME];
			if(sscanf(params,"s[24]",vardas)){SendClientMessage(playerid, 0xD9E916FF, "* Nuimti vip /setvip [nick]"); return 1;}
			new id = GetPlayeridMid(vardas);
			if (id == INVALID_PLAYER_ID){ SendClientMessage(playerid, 0xD9E916FF, "* Tokio zaidejo nera"); return 1;}
			new msg[128], query[256];
			GetPlayerName(id,vardas,sizeof(vardas));
			SendClientMessage(id,0xD9E916FF,"* Jums buvo nuimtas VIP. Kita syki elgsites atsargiau ;)");
			playerDB[id][vip] = false;
			format(query,sizeof(query),"UPDATE `Account` SET `Vip`=0 WHERE `Name` = '%s'",vardas);
			mysql_query(query);
			format(msg,sizeof(msg),"Nuemete VIP %s.",vardas);
			SendClientMessage(playerid,0xD9E916FF,msg);
			return 1;

}

CMD:setvip(playerid,params[])
{
			if(!IsPlayerAdmin(playerid)) return 0;
			new vardas[128];
			if(sscanf(params,"s[24]",vardas)){SendClientMessage(playerid, 0xD9E916FF, "* Uzdeti vip /setvip [nick]"); return 1;}
			new id = GetPlayeridMid(vardas);
			if (id == INVALID_PLAYER_ID){ SendClientMessage(playerid, 0xD9E916FF, "* Tokio zaidejo nera"); return 1;}
			new msg[128], query[256];
			GetPlayerName(id,vardas,sizeof(vardas));
			SendClientMessage(id,0xD9E916FF,"* Jums buvo uzdetas VIP. Matyt gerai pasitarnavote serveriui ;)");
			playerDB[id][vip] = true;
			format(query,sizeof(query),"UPDATE `Account` SET `Vip`=`Vip`+30 WHERE `Name` = '%s'",vardas);
			mysql_query(query);
			format(msg,sizeof(msg),"Uzdejote VIP %s.",vardas);
			SendClientMessage(playerid,0xD9E916FF,msg);
			return 1;
}

CMD:modgang(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new namux[24],id;
	if(sscanf(params,"s[24]d",namux,id)){SendClientMessage(playerid, COLOR, "/modgang [new_lead] [id]"); return 1;}

	FamilyInfo[id][FamilyLeader]=namux;
	return 1;

}
CMD:dxpxx(playerid,params[])
{
			if(!IsPlayerAdmin(playerid)) return 0;
			new tname[128],moneys;
			if(sscanf(params,"s[24]d",tname,moneys)){SendClientMessage(playerid, COLOR, "/dxp [nick] [kiek]"); return 1;}
			new tid = GetPlayeridMid(tname);
			GetPlayerName(tid,tname,sizeof(tname));

			SetPlayerScore(tid,GetPlayerScore(tid)+moneys);
			new mess[128],name[MAX_PLAYER_NAME];
			GetPlayerName(playerid,name,sizeof(name));
			format(mess,sizeof(mess),"***[%s >> %i XP] Gavote %i XP is %s",name,moneys,moneys,name);
			SendClientMessage(tid,COLOR,mess);
			format(mess,sizeof(mess),"***[%i XP >> %s] Davete %i XP %s",moneys,tname,moneys,tname);
			SendClientMessage(playerid,COLOR,mess);
			return 1;
}

CMD:dkreditai(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new tname[128],moneys;
	if(sscanf(params,"s[24]d",tname,moneys)){SendClientMessage(playerid, COLOR, "/dkreditai [nick] [kiek]"); return 1;}
	new tid = GetPlayeridMid(tname);
	GetPlayerName(tid,tname,sizeof(tname));
	if(!IsPlayerConnected(tid)) return 0;
	GiveKreditai(tid, moneys);
	new mess[128],name[MAX_PLAYER_NAME];
	GetPlayerName(playerid,name,sizeof(name));
	format(mess,sizeof(mess),"***[%s >> %i Kred] Gavote %i kreditus is %s",name,moneys,moneys,name);
	SendClientMessage(tid,COLOR,mess);
	format(mess,sizeof(mess),"***[%i Kred >> %s] Davete %i kreditus %s",moneys,tname,moneys,tname);
	SendClientMessage(playerid,COLOR,mess);
	return 1;
}

CMD:restartas(playerid,params[])
{
            #pragma unused params
			if(!IsPlayerAdmin(playerid)) return 1;
			Restartas();
			return 1;

}
CMD:tg(playerid,params[])
{
		if(!IsPlayerAdmin(playerid)) return 0;
		new id,name[128];
		if(sscanf(params,"ds[24]",id,name))
		{
			SendClientMessage(playerid,COLOR,"* /tg [id] [lead]");
			return 1;
		}
		new pid = GetPlayeridMid(name);
		if(pid != INVALID_PLAYER_ID) playerDB[pid][pgang]=id;
		format(FamilyInfo[id][FamilyLeader], 32, name);
		SaveFamily(id);
		return 1;
}
CMD:autorr(playerid,params[])
{
		if(!IsPlayerAdmin(playerid)) return 0;
		if(!autorestart)
		{
			SendClientMessage(playerid,GREEN,"* AutoRR ijungtas!");
		    autorestart=true;
		}
		else
		{
			SendClientMessage(playerid,RED,"* AutoRR isjungtas!");
		    autorestart=false;
		}
		return 1;
}
CMD:noadmin(playerid,params[])
{
		if(!IsPlayerAdmin(playerid)) return 0;
		new name[128];
		if(sscanf(params,"s[24]",name))
		{
			SendClientMessage(playerid,COLOR,"* /noadmin [nick]");
			return 1;
		}

		new id = GetPlayeridMid(name);

		if(id==INVALID_PLAYER_ID)
		{
			SendClientMessage(playerid,COLOR,"* Tokio vardo nera.");
			return 1;
		}

		if(!playerDB[id][admin])
		{
			SendClientMessage(playerid,COLOR,"* Zaidejas ne adminas.");
			return 1;
		}

		playerDB[id][admin]=false;
		SavePlayerData(id,true);
		SendClientMessage(playerid,COLOR,"* Success!");
		return 1;

}

CMD:setadmin(playerid,params[])
{
		if(!IsPlayerAdmin(playerid)) return 0;
		new name[128];
		if(sscanf(params,"s[24]",name))
		{
			SendClientMessage(playerid,COLOR,"* /setadmin [nick]");
			return 1;
		}

		new id = GetPlayeridMid(name);

		if(id==INVALID_PLAYER_ID)
		{
			SendClientMessage(playerid,COLOR,"* Tokio vardo nera.");
			return 1;
		}

		if(playerDB[id][admin])
		{
			SendClientMessage(playerid,COLOR,"* Nori adminui suteikti admina?.");
			return 1;
		}

		playerDB[id][admin]=true;
		SavePlayerData(id,true);
		SendClientMessage(playerid,COLOR,"* Success!");
		return 1;
}

CMD:syncvehicles(playerid,params[])
{
	#pragma unused params
	if(!IsPlayerAdmin(playerid))
		return 0;
	SyncVehicles();
	return 1;
}

CMD:addkiemas(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	if(!strval(params))
		return SendInfoMessage(playerid,"/addkiemas [namo nr]");
	new hid = strval(params);
	if(hid < 0 || hid > MAX_HOUSES)
		return SendInfoMessage(playerid,"Netinkamas namo nr");
	hInfo[hid][hKiemas]=1;
	GetPlayerPos(playerid,hInfo[hid][kiemox],hInfo[hid][kiemoy],hInfo[hid][kiemoz]);
	new query[256];
	format(query,sizeof(query),"REPLACE INTO `Kiemas`(houseid,kiemox,kiemoy,kiemoz) VALUES (%i,'%f','%f','%f')",hid,hInfo[hid][kiemox],hInfo[hid][kiemoy],hInfo[hid][kiemoz]);	
	mysql_query(query);
	SendClientMessage(playerid, -1, "Success!");
	return 1;
}

CMD:removekiemas(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	if(!strval(params))
		return SendInfoMessage(playerid,"/addkiemas [namo nr]");
	new hid = strval(params);
	if(hid < 0 || hid > MAX_HOUSES)
		return SendInfoMessage(playerid,"Netinkamas namo nr");
	hInfo[hid][hKiemas]=0;
	new query[256];
	format(query,sizeof(query),"Delete from Kiemas Where houseid=%i",hid);	
	mysql_query(query);
	SendClientMessage(playerid, -1, "Success!");
	return 1;
}

CMD:manozona(playerid,params[])
{
	if(CheckZone(playerid)) 
		SendClientMessage(playerid, COLOR, "taip");
	return 1;
}

CMD:dropgibs(playerid,params[])
{
	if(!IsPlayerAdmin(playerid))
		return 0;
	DropGibs(playerid);
	return 1;
}

CMD:hban(playerid,params[])
{
	if(!IsPlayerAdmin(playerid)) return 0;
	new vardenis[128];
	if(sscanf(params,"s[128]",vardenis)) return SendInfoMessage(playerid,"/hban [vardas_Pavarde]");
	new id = GetPlayeridMid(vardenis);
	//if( id == playerid) return SendInfoMessage(playerid,"~r~Sau uzmesti negali.");
	if(id == INVALID_PLAYER_ID) return SendInfoMessage(playerid,"~r~Tokio zaidejo nera.");
	new query[128];
	new hashas[128];
	gpci(id,hashas,sizeof(hashas));
	format(query,sizeof(query),"INSERT INTO HBans (Vardas,Hash) VALUES ('%s','%s')",ReturnName(id),hashas);
	mysql_query(query);
	return 1;
}
