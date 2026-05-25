CMD:auto(playerid,params[])
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendInfoMessage(playerid,"Si komanda tik vairuotojui!");
	ShowPlayerDialog(playerid,1687,DIALOG_STYLE_LIST,"Automobilis","Variklis\nÐviesos\nPriekinis dangtis\nBagaþinë\nRadija","Gerai","Iseit");
	return 1;
}

CMD:nr(playerid,params[])
{
	if(!galikast[playerid]) return 1;
	if(playerDB[playerid][specialybe]!=80 && playerDB[playerid][specialybe]!=81 && playerDB[playerid][specialybe] != 82 && playerDB[playerid][specialybe] != 83 && playerDB[playerid][specialybe] != 84){SendInfoMessage(playerid,"Si komanda tik Teisesaugai."); return 1;}
	new numeris[128];
	if(sscanf(params,"s[128]",numeris)) return SendInfoMessage(playerid,"Naudojimas: /nr [numeris]");
	if(strlen(numeris) < 3 || strlen(numeris) > 10) return SendInfoMessage(playerid,"Netinkamas numeris");
	new id = SearchVehicleID(numeris);
	if(id == -1) return SendInfoMessage(playerid,"Automobilis nerastas!");
	galikast[playerid]=false;
	SendInfoMessage(playerid,"Ieskome automobilio... Tai gali uztrukti.");
	SetTimerEx("NumerioPaieska",5000+random(5000),false,"ii",playerid,id);
	return 1;
}

CMD:dazai(playerid,params[])
{
	if(!playerDB[playerid][psratasvydis])
		return SendInfoMessage(playerid,"~r~Komanda nauodajama dazasvydyje!");

	new textaz[128];
	if (sscanf(params, "s[128]",textaz)) return SendInfoMessage(playerid,"Noredami kalbeti per dazu racija rasykite /dazai [tekstas]");

	new votemenu[256];
	if(playerDB[playerid][psratasvydis] == 2) // 2 raudoni, 1 melyni
		format(votemenu,256,#TEXT_GREEN"[DAÞASVYDIS] "#TEXT_RED"%s{FFFFFF}: %s",ReturnName(playerid),textaz);
	else
		format(votemenu,256,#TEXT_GREEN"[DAÞASVYDIS] "#TEXT_BLUE"%s{FFFFFF}: %s",ReturnName(playerid),textaz);

	SendMessageToDazaiThird(-1,votemenu);
	return 1;
}

CMD:fw(playerid, params[])
{
	if((GetPlayerInterior(playerid)!=0 && !CheckZone(playerid)) || GetPlayerVehicleID(playerid) != 0 || GetPlayerHouseID(playerid) != 0 ) return SendInfoMessage(playerid,"Islisk i lauka!");
	if(SafeArea(playerid) && !playerDB[playerid][admin])
		return SendInfoMessage(playerid,"Saugioje zonoje fejerverku deti negali.");
	new Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	if((pos[1] < -1301.4 && pos[1] > -1303.2417 && pos[0] < 1786.2131 && pos[0] > 1784.1555) || (pos[1] > -1301.4 && pos[1] < -1299.1447 && pos[0] < 1785.6147 && pos[0] > 1781.9902))
		return SendInfoMessage(playerid,"Islisk i lauka!");    
	// 
	if(((1110.9355 < pos[0] < 1216.6061) && (-1211.0791 < pos[1] < -1152.7689)) || (  ( 247.5167 < pos[0] < 320.7534) && (-1640.1964 < pos[1] < -1569.4169)  )) // ligonines aps & beachside aps
		return SendInfoMessage(playerid,"Cia fejerverku deti negali.");
	if(playerDB[playerid][ant] || playerDB[playerid][suristas] || playerDB[playerid][pila])
		return SendInfoMessage(playerid,"Dabar deti fejerverku negali.");
	new Float:Coo[3];
	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	if(IsPlayerInRangeOfPointEx(50.0,playerid,-60.7811,48.0869,3.1103)) // lsd
	{
		if(Coo[2] < 2.6) // lsd po zeme
		{
			AC_Warn(playerid,"FW po zeme");
			HideProgressBarForPlayer(playerid,Veiksmai);
			return 1;
		}
	}
	else if(IsPlayerInRangeOfPointEx(50.0,playerid,2318.0364,38.2342,26.4844)) // ratai
	{
		if(Coo[2] < 26.0)
		{
			AC_Warn(playerid,"FW po zeme");
			return 1;
		}
	}
	else if(IsPlayerInRangeOfPointEx(50.0,playerid,-365.9257,-1423.4869,25.7266)) // seklos
	{
		if(Coo[2] < 25.0)
		{
			AC_Warn(playerid,"FW po zeme");
			return 1;
		}
	}
	else if(IsPlayerInRangeOfPointEx(50.0,playerid,213.6279,1867.3140,13.1406)) // ginklai
	{
		if(Coo[2] < 12.5)
		{
			SendInfoMessage(playerid,"Cia fejerverko deti negali.");
			return 1;
		}
	}
	else if(IsPlayerInRangeOfPointEx(50.0,playerid,2541.9163,-1296.3842,1044.1250)) // pinigai
	{
		if(Coo[2] < 1043.0)
		{
			AC_Warn(playerid,"FW po zeme");
			return 1;
		}
	}
	if(Coo[2] > 500.0)
	{
		AC_Warn(playerid,"FW danguje?");
		return 1;
	}
	new bool:show=false;
	if(playerDB[playerid][fejerverkai][0]) {show=true, AddDListItem(playerid, "'Star Dream'", 0); }
    if(playerDB[playerid][fejerverkai][1]) {show=true, AddDListItem(playerid, "'Dynamite'", 1); }
	if(playerDB[playerid][fejerverkai][2]) {show=true, AddDListItem(playerid, "Raketa 'Saturn'", 2); }
	if(playerDB[playerid][fejerverkai][3]) {show=true, AddDListItem(playerid, "Raketa 'Thunder'", 3); }
	if(playerDB[playerid][fejerverkai][4]) {show=true, AddDListItem(playerid, "Fontanas 'Rising Sun'", 4); }
	if(playerDB[playerid][fejerverkai][5]) {show=true, AddDListItem(playerid, "Fontanas 'Ocean Wave'", 5); }
	if(playerDB[playerid][fejerverkai][6]) {show=true, AddDListItem(playerid, "Volkanas 'Vixen'", 6); }
	if(playerDB[playerid][fejerverkai][7]) {show=true, AddDListItem(playerid, "Baterija 'Midnight Episode'", 7); }

	if(show)
	{
		ShowPlayerDList(playerid, 8685, "Fejerverkai", "Rinktis", "Iseiti");
	}
	else
		SendInfoMessage(playerid,"~r~Neturi fejerverku!");
	return 1;
}


CMD:i(playerid,params[])
{
	#pragma unused params
	new money[512];
	format(money,sizeof(money),"Pinigai\t{00BBFF}%i€",playerDB[playerid][pinigai]);
    if(GetPlayerMoneyA(playerid)) AddDListItem(playerid, money, INV_TELEFONAS);
    format(money,sizeof(money),"Kreditinë kortelë\t{00BBFF}%i€",playerDB[playerid][banke]);
    if(playerDB[playerid][kortele]) AddDListItem(playerid, money, INV_KREDITINE);
	format(money,sizeof(money),"Telefono sàskaita\t{00BBFF}%i€",playerDB[playerid][mobsas]);
    AddDListItem(playerid, money, INV_TELEFONAS);
    if(playerDB[playerid][teises]) AddDListItem(playerid, "Vairavimo teisës", INV_TEISES);
	if(playerDB[playerid][teisesm]) AddDListItem(playerid, "Motociklø teisës", INV_TEISESM);
	if(playerDB[playerid][teisess]) AddDListItem(playerid, "Skraidymo teisës", INV_TEISESS);
	if(playerDB[playerid][spaz]) AddDListItem(playerid, "Sveikatos paz.", INV_SPAZ);
    format(money,sizeof(money),"Sëklos\t{00BBFF}%i vnt",playerDB[playerid][seklos]);
    if(playerDB[playerid][seklos]) AddDListItem(playerid, money, INV_SEKLOS);
    format(money,sizeof(money),"Automobilio raktas\t{00BBFF}%i vnt",playerDB[playerid][raktas]);
    if(playerDB[playerid][raktas]) AddDListItem(playerid, money, INV_RAKTAS);
    format(money,sizeof(money),"Þuvis\t{00BBFF}%i vnt",playerDB[playerid][zuvis]);
    if(playerDB[playerid][zuvis]) AddDListItem(playerid, money, INV_ZUVIS);
    format(money,sizeof(money),"Masalas\t{00BBFF}%i gr",playerDB[playerid][masalas]);
    if(playerDB[playerid][masalas]) AddDListItem(playerid, money, INV_MASALAS);
    if(playerDB[playerid][bakelis]) AddDListItem(playerid, "Kuro Bakelis",INV_BAKELIS);
	if(playerDB[playerid][maistas]) AddDListItem(playerid, "Maistas",INV_MAISTAS);
	if(playerDB[playerid][laikrodis]) AddDListItem(playerid, "Laikrodis",INV_LAIKRODIS);
	if(playerDB[playerid][maistaslauk]) AddDListItem(playerid, "Maistas issinesimui",INV_MAISTASLAUK);
	format(money,sizeof(money),"Þolë\t{00BBFF}%i gr",playerDB[playerid][zole]);
    if(playerDB[playerid][zole]) AddDListItem(playerid, money, INV_ZOLE);
	format(money,sizeof(money),"Amfetaminas\t{00BBFF}%i vnt",playerDB[playerid][amfetaminas]);
    if(playerDB[playerid][amfetaminas]) AddDListItem(playerid, money, INV_NARK);
	format(money,sizeof(money),"LSD\t{00BBFF}%i vnt",playerDB[playerid][lsd]);
	if(playerDB[playerid][lsd]) AddDListItem(playerid, money, INV_LSD);
	format(money,sizeof(money),"Adrenalinas\t{00BBFF}%i vnt",playerDB[playerid][adr]);
	if(playerDB[playerid][adr]) AddDListItem(playerid, money, INV_ADR);
	format(money,sizeof(money),"Ratai\t{00BBFF}%i vnt",playerDB[playerid][ratai]);
	if(playerDB[playerid][ratai]) AddDListItem(playerid, money, INV_RATAI);
	format(money,sizeof(money),"Cigaretës\t{00BBFF}%i vnt",playerDB[playerid][cigaretes]);
	if(playerDB[playerid][cigaretes]) AddDListItem(playerid, money, INV_CIGARETES);
	if(IsPlayerAttachedObjectSlotUsed(playerid,SLOT_LAGAMINAS)) AddDListItem(playerid, "Laiðkai", INV_LAISKAI);
	if(IsPlayerAttachedObjectSlotUsed(playerid,TAZER_SLOT)) AddDListItem(playerid, "Tazeris", INV_TAZERIS);
	if(playerDB[playerid][kepure])
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid,CAP_SLOT))
		{
			AddDListItem(playerid, "Kepurë\t{00BBFF}Uþdëta", INV_KEPURE);
		}
		else
		{
			AddDListItem(playerid, "Kepurë\t{00BBFF}Nuimta", INV_KEPURE);
		}
	}	
	if(playerDB[playerid][salmas])
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid,SALMO_SLOT))
		{
			AddDListItem(playerid, "Ðalmas\t{00BBFF}Uþdëtas", INV_SALMAS);
		}
		else
		{
			AddDListItem(playerid, "Ðalmas\t{00BBFF}Nuimtas", INV_SALMAS);
		}
	}	
	if(playerDB[playerid][akiniai])
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid,AKINIU_SLOT))
		{
			AddDListItem(playerid, "Akiniai \t{00BBFF}Uþdëti", INV_AKINIAI);
		}
		else
		{
			AddDListItem(playerid, "Akiniai\t{00BBFF}Nuimti", INV_AKINIAI);
		}
	}	
	
    new wepid=GetPlayerWeapon(playerid);
	new ammo=GetPlayerAmmo(playerid);
	
	GetWeaponName(wepid,money,sizeof(money));

    switch(wepid)
	{       //mp5,dgl,awp,ak
		    case 29,24,34,30: { if(playerDB[playerid][specialybe] ==32 || playerDB[playerid][admin]) AddDListItem(playerid, money, INV_GUN,ammo); }
		    case 18,23,27,44,45,31,32,40,39,0..13,16,WEAPON_HEATSEEKER, WEAPON_UZI, WEAPON_MINIGUN, WEAPON_ROCKETLAUNCHER: { }
			default: AddDListItem(playerid, money, INV_GUN,ammo);
	}
	new actionas = GetPlayerSpecialAction(playerid);
	if(actionas == SPECIAL_ACTION_DRINK_BEER || actionas == SPECIAL_ACTION_DRINK_WINE || actionas == SPECIAL_ACTION_DRINK_SPRUNK) 
		AddDListItem(playerid, "Gërimas", INV_GERIMAS,action);
	AddDListItem(playerid,"Rûbai",INV_RUBAI);
	AddDListItem(playerid,"Spalvos",INV_SPALVOS);
	//AddDListItem(playerid,"Dovanos",INV_DOVANA);
    ShowPlayerDListHeader(playerid, 1338, "Inventorius", "Rinktis", "Iseiti","Daiktas\tKiekis");
	return 1;
}

CMD:inv(playerid,params[])
{
	#pragma unused params
	cmd_i(playerid,params);
	return 1;
}

CMD:inventorius(playerid,params[])
{
	#pragma unused params
	cmd_i(playerid,params);
	return 1;
}

CMD:ismest(playerid,params[])
{
	if(!playerDB[playerid][plead]) return SendInfoMessage(playerid,"Tai direktoriaus komandos.");
	new name[128],reason[128];
	if(sscanf(params,"s[128]s[128]",name,reason))
	{
		SendInfoMessage(playerid,"Noredami ismesti darbuotoja is savo firmos rasykite: /ismest [vardo dalis] [priezastis]");
		return 1;
	}

	new id = GetPlayeridMid(name);
	

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
	else if(playerDB[playerid][plead] == 34){ lol=34;}
	else if(playerDB[playerid][plead] == 60){ lol=60;}


	if(id == INVALID_PLAYER_ID || playerDB[id][authstate]!=4)
	{
	    new query[128];
		mysql_real_escape_string(name,name,_,256);
		format(query,128,"SELECT * FROM `Account` WHERE `Name` = '%s' LIMIT 1",name);
		mysql_function_query(SQL, query, true, "SQL_IsmestiCheck", "iss", playerid,name,reason);

		return 1;
	}

	if(playerDB[id][specialybe]!= lol && playerDB[id][specialybe]!= lol2 && playerDB[id][specialybe]!= lol3 && playerDB[id][specialybe]!= lol4 && playerDB[id][specialybe]!= lol5 )
	{
		SendInfoMessage(playerid,"Zaidejas nedirba jusu firmoje.");
		return 1;
	}
	if(playerDB[id][pradirbo] >= 100 && !Pareigos(playerid,"Dyrikai")) return SendInfoMessage(playerid,"Privalote sumoketi zaidejui alga!");
	GetPlayerName(id,name,sizeof(name));

	if(playerDB[playerid][plead] == LEAD_TEISESAUGA) SendClientMessage(id,GANG_COLOR,"Jus buvote ismestas is Los Santos teisesaugos burio.");
	else if(playerDB[playerid][plead] == LEAD_MEDIKAI) SendClientMessage(id,GANG_COLOR,"Jus buvote ismestas is Los Santos mediku komandos.");
	else if(playerDB[playerid][plead] == LEAD_AUTOSPECAI) SendClientMessage(id,GANG_COLOR,"Jus buvote ismestas is Los Santos mechaniku gretu.");
	else if(playerDB[playerid][plead] == LEAD_GAISRAS) SendClientMessage(id,GANG_COLOR,"Jus buvote ismestas is Los Santos gaisrines tarnybos.");
	else if(playerDB[playerid][plead] == LEAD_VALSTYBE) SendClientMessage(id,GANG_COLOR,"Jus buvote ismestas is valstybines imones.");
	else if(playerDB[playerid][plead] == LEAD_KLUBAI) SendClientMessage(id,GANG_COLOR,"Jus buvote ismestas is klubo.");
	else if(playerDB[playerid][plead] == LEAD_TRANSPORTAS) SendClientMessage(id,GANG_COLOR,"Jus buvote ismestas is Los Santos taksistu.");
	else if(playerDB[playerid][plead] == LEAD_FURISTAS) SendClientMessage(id,GANG_COLOR,"Jus buvote ismestas is Los Santos pervezimo firmos.");
	else if(playerDB[playerid][plead] == LEAD_GIDAI) SendClientMessage(id,GANG_COLOR,"Jus buvote ismestas is Los Santos Gidu.");
	else if(playerDB[playerid][plead] == LEAD_BAIKERIAI) SendClientMessage(id,GANG_COLOR,"Jus buvote ismestas is Los Santos Baikeriu.");
	else if(playerDB[playerid][plead] == LEAD_DEAL) SendClientMessage(id,GANG_COLOR,"Jus buvote ismestas is Los Santos Dealeriu.");
	else if(playerDB[playerid][plead] == 60) SendClientMessage(id,GANG_COLOR,"Jus buvote ismestas is Los Santos Inkasatoriu.");
	else if(playerDB[playerid][plead] == 34) SendClientMessage(id,GANG_COLOR,"Jus buvote ismestas is Nekilnojamo turto agentu.");
	playerDB[id][leanvited][playerDB[playerid][plead]-1]=false;
	new msg[128];
	format(msg,sizeof(msg),"Direktorius %s Jus ismete is darbo.~Priezastis: %s.",ReturnName(playerid),reason);
	EAtaskaita("Darbo birza",name,"Ismetimo Ataskaita",msg);
	format(msg,sizeof(msg),"%s buvo ismestas is jusu firmos.",name);
	SendInfoMessage(playerid,msg);
	MLog(playerid,"Ismete","ss",name, reason);
	if(playerDB[id][uniformd])SetPlayerSkin(id,playerDB[id][drabuziai]);

	playerDB[id][specialybe]=0;
	playerDB[id][uniformd]=false;
	playerDB[id][uniforma]=-1;
	DeletePlayerWeaponsForJob(id);
	playerDB[id][pradirbo]=0;
	playerDB[id][jobpts]=0;
	SavePlayerData(id,true);
	return 1;
}


CMD:skamb(playerid,params[])
{
    	if(!playerDB[playerid][telon]) return SendInfoMessage(playerid,"Jusu telefonas yra ~r~isjungtas~w~. Naudokite /telon .");
		new tname[MAX_PLAYER_NAME],vardux[128];
		if(playerDB[playerid][ikalintas]) return SendInfoMessage(playerid,"Policija ateme jusu telefona. Prasome naudotis taksofonu.");
		if(playerDB[playerid][suristas]) return SendInfoMessage(playerid,"Tu suristas! Naudokis /sms !");
		if(sscanf(params,"s[24]",vardux))
		{
			SendInfoMessage(playerid,"Skambinti jam ( jai ): /skamb [vardo dalis]");
			return 1;
		}
		if(playerDB[playerid][mobsas] < 10)
		{
			SendInfoMessage(playerid,"Jums nepakanka saskaitos. Pasipildykite ja kioske.");
			return 1;
		}
		if(0==strcmp(vardux,"Bankas",true))
		{
		    if(playerDB[playerid][plead]>0)
		    {
		    	PlaySound(playerid,3600);
		        SetTimerEx("Bankininke",random(10000),false,"i",playerid);
		        SendInfoMessage(playerid,"Prasome palaukti.");
		        playerDB[playerid][mobsas]-=10;
		        if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_NONE)
				{
					SendClientMessage(playerid,COLOR,"* Kai baigsite rageli padekite su ( /bai ).");
					SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
					SetPlayerAttachedObject(playerid, TEL_SLOT, 330, 6); // 4 = attachment slot, 330 = cellphone model, 6 = right hand
				}
		        return 1;
		    }
		}
		new tid = GetPlayeridMid(vardux);
		if(tid==INVALID_PLAYER_ID)
		{
			SendInfoMessage(playerid,"Operatorius: Tokio vardo nera.");
			return 1;
		}
    	if(!playerDB[tid][telon]) return SendInfoMessage(playerid,"Gavejo telefonas yra isjungtas.");
		if(playerDB[tid][ikalintas]) return SendInfoMessage(playerid,"Telefonas yra uz rysio zonos ribu.");
		if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_NONE)
		{
			SendClientMessage(playerid,COLOR,"* Kai baigsite rageli padekite su ( /bai ).");
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
			SetPlayerAttachedObject(playerid, TEL_SLOT, 330, 6); // 4 = attachment slot, 330 = cellphone model, 6 = right hand
		}
		PlaySound(playerid,3600);




		if(tid==playerid)
		{
			SendInfoMessage(playerid,"Operatorius: Linija uzmita.");
			return 1;
		}

		GetPlayerName(tid,tname,sizeof(tname));

		if(playerDB[tid][skambutis] !=-1)
		{
			SendInfoMessage(playerid,"Operatorius: Linija uzimta.");
			return 1;
		}

		new msg[128],name[MAX_PLAYER_NAME];
		GetPlayerName(playerid,name,sizeof(name));
		format(msg,sizeof(msg),"Jums skambina %s. Galite atsiliepti ~g~/ans~w~ arba atmesti ~r~/den",name);
		SendInfoMessage(tid,msg);
		PlayerPlaySound(tid, 1097,-119.9460,23.1096,12.2238); // Muzika
		format(msg,sizeof(msg),"Skambinate %s...",tname);
		SendInfoMessage(playerid,msg);
		playerDB[playerid][skambutis]=tid;
		playerDB[tid][rid][5]=playerid;
		return 1;
}

CMD:xp(playerid,params[])
{
		new tname[MAX_PLAYER_NAME],vardux[128];
		if(sscanf(params,"s[24]",vardux)) return SendInfoMessage(playerid,"Parodyti jo ( jos ) patirti: /xp [nick]");
		new tid = GetPlayeridMid(vardux);
		if(tid==INVALID_PLAYER_ID){SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		GetPlayerName(tid,tname,sizeof(tname));
		new msg[128];
		format(msg,sizeof(msg),"***%s patirtis yra: %iXP",tname,GetPlayerScore(tid));
		SendClientMessage(playerid,COLOR,msg);
		return 1;
}
CMD:gauja(playerid,params[])
{
		new tname[MAX_PLAYER_NAME],vardux[128];
		if(sscanf(params,"s[24]",vardux)) return SendInfoMessage(playerid,"Parodyti jo ( jos ) gauja: /gauja [nick]");
		new tid = GetPlayeridMid(vardux);
		if(tid==INVALID_PLAYER_ID){SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		GetPlayerName(tid,tname,sizeof(tname));
		new Float:Coo[3];
		GetPlayerPos(tid,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(200, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(tid) == PLAYER_STATE_SPECTATING)
		{
			if(GaujaCount[playerid] >= 10) {
				SendInfoMessage(playerid,"Sios komandos taip daznai naudoti negali");
				return 1;
			}
			GaujaCount[playerid]++;
		}

		if(playerDB[tid][pgang] == -1)
		{
			new msg[128];
			format(msg,sizeof(msg)," * %s nepriklauso jokiai gaujai.",tname);
			SendClientMessage(playerid,COLOR,msg);
			return 1;
		}

		new msg[128];
		format(msg,sizeof(msg)," * %s priklauso \"%s\" gaujai.",tname,FamilyInfo[playerDB[tid][pgang]][FamilyName]);
		SendClientMessage(playerid,COLOR,msg);
		return 1;
}
CMD:cpass(playerid,params[])
{
	#pragma unused params
	ShowPlayerDialog(playerid,12312,DIALOG_STYLE_INPUT,"Cpass","Iveskite sena slaptazodi","Gerai","Atsaukti");
	return 1;
}
CMD:alko(playerid,params[])
{
		if(playerDB[playerid][specialybe]!=80){SendInfoMessage(playerid,"Si komanda tik policininkams"); return 1;}
        new vardas[128];
		if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Patikrinti, ar zaidejas blaivus ar ne: /alko [vardo_dalis]"); return 1;}

		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		if (id == playerid){ SendInfoMessage(playerid,"Save gali pasitikrinti ir paprasciau!"); return 1;}
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(5, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(id) == PLAYER_STATE_SPECTATING){SendInfoMessage(playerid,"Zaidejas per toli!"); return 1;}

		if(GetPlayerState(id) == PLAYER_STATE_DRIVER)
		{
			new girtas = GetPlayerDrunkLevel(id);
			new Float:laipsnis,msg[128];
			laipsnis=girtas/5000;
			if(girtas == 0){SendInfoMessage(playerid,"Zaidejas blaivus."); SendInfoMessage(playerid,"Policija nustate kad jus esate blaivus."); return 1;}
			if(girtas < 2000){
				format(msg, 128, "* Alkotesteris rodo: %3.1f promiliu. tai leistinas kiekis", laipsnis);}
			if(girtas > 2000 && girtas <= 7500){
				format(msg, 128, "* Alkotesteris rodo: %3.1f promiliu. tai lengvas girtumo laipsnis", laipsnis);}
			if(girtas > 7500 && girtas <= 12500){
				format(msg, 128, "* Alkotesteris rodo: %3.1f promiliu. tai vidutinis girtumo laipsnis", laipsnis);}
			if(girtas > 12500){
				format(msg, 128, "* Alkotesteris rodo: %3.1f promiliu. tai sunkus girtumo laipsnis", laipsnis);}
			SendClientMessage(playerid,GREEN,msg);
			SendClientMessage(id,GREEN,msg);
			return 1;
		}
		SendInfoMessage(playerid,"Zaidejas nevairuoja automobilio.");
		return 1;


}

CMD:bauda(playerid,params[])
{
    	if(playerDB[playerid][specialybe]!=80 && playerDB[playerid][specialybe] != 82 && playerDB[playerid][specialybe]!=81 && playerDB[playerid][specialybe] != 83 && playerDB[playerid][specialybe] != 84){SendInfoMessage(playerid,"Si komanda tik teisesaugai."); return 1;}
		new tname[128];
		if(playerDB[playerid][suristas]) return SendInfoMessage(playerid,"Tu suristas!");
		if(sscanf(params,"s[24]",tname)){SendInfoMessage(playerid,"Nustatyti bauda: /bauda [dalis nicko]"); return 1;}
		if(PlayerSpectated[playerid] != -1)
		{
			new msgpzu[256];
			format(msgpzu,256,"[PZU] %s: /bauda %s",ReturnName(playerid), tname);
			SendClientMessage(PlayerSpectated[playerid], COLOR, msgpzu);
		}
		new tid = GetPlayeridMid(tname);

		if(tid==INVALID_PLAYER_ID)
		{
			SendInfoMessage(playerid,"Tokio zaidejo nera.");
			return 1;
		}
		if (tid == playerid){ SendInfoMessage(playerid,"Saves isteisinti negalesi!!!!"); return 1;}
		/*if(GetPlayerScore(tid) < 70)
		{
			SendClientMessage(playerid, RED, "* Nusikaltelis dar nepatyres,ir negali is jo imti pinigu,todel gabenk ji i cype!");
			SendClientMessage(tid,RED, "* Jus esate nepatyres nusikaltelis,todel nebusit pasodintas i belange!!!");
			return 1;
		}*/
		GetPlayerName(tid,tname,sizeof(tname));
		new bauda = GetPlayerWantedLevel(tid)*1000;
		if(PlaceOwnedBy[5] == -1)
		{
			bauda = (bauda * 3) / 2;
		}
		if(bauda == 0){SendInfoMessage(playerid,"Zaidejas nenusikaltes"); return 1;}
		if(GetPlayerWantedLevel(tid) == 10 && !playerDB[tid][ant])
			return SendInfoMessage(playerid,"~r~Sunkus nusikaltelis bauda gali susimoketi tik policijos departamente!");

		new Float:Coo[3];
		GetPlayerPos(tid,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(5, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(tid)==PLAYER_STATE_SPECTATING){SendInfoMessage(playerid,"Zaidejas per toli!"); return 1;}
		if(GetPlayerScore(tid) < 500) return SendInfoMessage(playerid,"Zaidejas turi per mazai xp (reikia 500)");
		playerDB[tid][rkaina][1]=bauda;
		playerDB[tid][rid][1]=playerid;
		new msg[128],name[MAX_PLAYER_NAME];
		GetPlayerName(playerid,name,sizeof(name));
		format(msg,sizeof(msg),"* %s jums siulo moketi bauda: %i €. Moketi?",name,bauda);
		if(bauda >= 10000) ProcessAchievement(tid,51);
		ShowPlayerDialog(tid, 888, DIALOG_STYLE_MSGBOX, "Bauda", msg, "Taip", "Ne");
		SendClientMessage(tid,GREEN,msg);

		new msgz[128];
		GetPlayerName(tid,tname,sizeof(tname));
		format(msgz,sizeof(msgz),"Pasiulete %s moketi %i EUR bauda",tname,bauda);
		SendInfoMessage(playerid,msgz);
		
		return 1;
}


CMD:nark(playerid,params[])
{
    	if(playerDB[playerid][specialybe]!=80 && playerDB[playerid][specialybe]!=84 && playerDB[playerid][specialybe]!=81 && playerDB[playerid][specialybe]!=83){SendInfoMessage(playerid,"Si komanda tik policininkams"); return 1;}
        new vardas[128];
		if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Patikrinti, ar zaidejas turi narkotiku: /nark [vardo_dalis]"); return 1;}

		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		if (id == playerid){ SendInfoMessage(playerid,"Save gali pasitikrinti ir paprasciau!"); return 1;}
		new year,month,day;
		getdate(year, month, day);
		if(month == 12 && day == 25)
			return SendInfoMessage(playerid,"Siandien sios komandos naudoti negali del Kaledinio evento.");
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(5, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(id) == PLAYER_STATE_SPECTATING){SendInfoMessage(playerid,"Jis ( Ji ) per toli!"); return 1;}
		if(playerDB[id][specialybe]==32 && (GetPlayerSkin(id) == 225 || GetPlayerSkin(id)==30)) 
		{
			new msg[128];
			format(msg,128," * %s aptikrina %s ir nieko neranda.",ReturnName(playerid),ReturnName(id));
			ProxDetector(30.0, playerid, msg, COLOR_CHAT1,COLOR_CHAT2,COLOR_CHAT3,COLOR_CHAT4,COLOR_CHAT5);
			SendClientMessage(playerid,0x0000A890,"* Jis ( Ji ) neturi narkotiku.");
			ProcessAchievement(id,73);
			return 1;
		}
		if(SafeArea(id) == 24)
		{
			return SendInfoMessage(playerid,"Nebuk grincas!");
		}
		if(playerDB[id][amfetaminas]>0 || playerDB[id][lsd]>0 || playerDB[id][ratai]>0)
		{
			SendClientMessage(playerid,0xFF000090,"* Jis ( Ji ) turi narkotiku, galite ji suimti. Nepamirskite ju konfiskuoti!");
			new msg[128];
			format(msg,128," * %s aptikrina %s ir randa narkotiniu medziagu!",ReturnName(playerid),ReturnName(id));
			ProxDetector(30.0, playerid, msg, COLOR_CHAT1,COLOR_CHAT2,COLOR_CHAT3,COLOR_CHAT4,COLOR_CHAT5);
			return 1;
		}
    	new msg[128];
		format(msg,128," * %s aptikrina %s ir nieko neranda.",ReturnName(playerid),ReturnName(id));
		ProxDetector(30.0, playerid, msg, COLOR_CHAT1,COLOR_CHAT2,COLOR_CHAT3,COLOR_CHAT4,COLOR_CHAT5);
		SendClientMessage(playerid,0x0000A890,"* Jis ( Ji ) neturi narkotiku.");
		ProcessAchievement(id,73);
		return 1;


}
CMD:fix(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][raktas] < 1) return SendInfoMessage(playerid,"Neturite rakto!");
	new vehicleid = GetClosestVehicleid(playerid,999.99,GetPlayerVehicleID(playerid));
	new Float:Coo[3];
	GetVehiclePos(vehicleid,Coo[0],Coo[1],Coo[2]);
	if(!IsPlayerInRangeOfPointEx(5, playerid, Coo[0],Coo[1],Coo[2])){SendInfoMessage(playerid,"Jus esate per toli nuo masinos variklio."); return 1;}
	GetVehicleParamsEx(vehicleid,VehVars[0],VehVars[1],VehVars[2],VehVars[3],VehVars[4],VehVars[5],VehVars[6]);
	if(!VehVars[4]) return SendInfoMessage(playerid,"Privalote atidaryti kapota! Masinoje rasykite /auto ");
	if(playerDB[playerid][ant] || playerDB[playerid][suristas]) return SendInfoMessage(playerid,"Dabar masinos taisyti negali.");
	/*GetVehicleHealth(vehicleid,HP);
	if( (HP+200) > 1000) SetVehicleHealth(vehicleid, 1000);
	else SetVehicleHealth(vehicleid,HP+200); */

	SendInfoMessage(playerid,"Sutaisete automobili!");
	if(Taisymas(playerid,0)==1)
	{
		playerDB[playerid][raktas]--;
		LogA(playerid,"Raktas");
	}
	return 1;
}
CMD:bakelis(playerid,params[])
{
	#pragma unused params
	if(!playerDB[playerid][bakelis]) return SendInfoMessage(playerid,"Neturite bakelio!");
	new vehicleid = GetClosestVehicleid(playerid,8.0);
	if (vehicleid == INVALID_VEHICLE_ID) {
		vehicleid = GetPlayerVehicleID(playerid);
		if(!vehicleid)
			return SendInfoMessage(playerid,"Tu per toli nuo masinos!");
	}
	new Float:Coo[3];
	GetVehiclePos(vehicleid,Coo[0],Coo[1],Coo[2]);
	if(!IsPlayerInRangeOfPointEx(8, playerid, Coo[0],Coo[1],Coo[2])){SendInfoMessage(playerid,"Jus esate per toli nuo masinos."); return 1;}
	if(vehicleDB[vehicleid][gas]+20 <= aBakai[GetVehicleModel(vehicleid)-400]) vehicleDB[vehicleid][gas]+=20;
	else vehicleDB[vehicleid][gas]=aBakai[GetVehicleModel(vehicleid)-400];
	SendInfoMessage(playerid,"Pripylete degalu i automobili!");

	playerDB[playerid][bakelis]=false;
	LogA(playerid,"Kuro bakelis");
	return 1;
}
CMD:raktas(playerid,params[])
{
        new vardas[128];
		if(playerDB[playerid][specialybe]!=6 && !playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda skirta tik mechanikams."); return 1;}
		new kiek = 1;
		if(sscanf(params,"s[24]I(1)",vardas,kiek)){SendInfoMessage(playerid,"Norint iteikti rakta rasykite: /raktas [vardo dalis] (kiek)"); return 1;}
		new id = GetPlayeridMid(vardas);
		if(kiek < 1 || kiek >= 10)
			return SendInfoMessage(playerid,"Raktu kiekis nuo 1 iki 9!");
		if (id == INVALID_PLAYER_ID){SendInfoMessage(playerid,"Atsiprasome, taciau zaidejas yra neprisijunges."); return 1;}
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(5, playerid, Coo[0],Coo[1],Coo[2])){SendInfoMessage(playerid,"Atsiprasome, taciau zaidejas yra per toli."); return 1;}

		if(playerDB[id][raktas] + kiek >= 10) return SendInfoMessage(playerid,"Zaidejas tiek raktu nepatemps!");
		if(GetPlayerMoneyA(playerid)<COST_RAKTAS*kiek)
		{
			SendInfoMessage(playerid,"Rakto iteikimas kainuoja "#COST_RAKTAS"EUR.");
			return 1;
		}

		GivePlayerMoneyA(playerid,-COST_RAKTAS*kiek);
		Pelnas(playerid,5,COST_RAKTAS*2*kiek);

		if(id != playerid) playerDB[playerid][jobpts]++;
		SendInfoMessage(playerid,"Raktas iteiktas.");
		SendInfoMessage(id,"Jus gavote rakta. Su juo galite sutaisyti nedeganti automobili.");

		playerDB[id][raktas]+= kiek;
		return 1;
}
CMD:gesintuvas(playerid,params[])
{
        new vardas[128];
		if(playerDB[playerid][specialybe]!=66 && !playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda skirta tik gaisrininkams."); return 1;}
		if(sscanf(params,"s[24]",vardas))
		{
			SendClientMessage(playerid,-1,"Norint iteikti gesintuva rasykite: /gesintuvas [vardo dalis]."); 
			SendInfoMessage(playerid,"Gavote gesintuva");
			GivePlayerWeaponEx(playerid,42,100000); //pompa
			return 1;
		}
		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Atsiprasome, taciau zaidejas yra neprisijunges."); return 1;}
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(5, playerid, Coo[0],Coo[1],Coo[2])){SendInfoMessage(playerid,"Atsiprasome, taciau zaidejas yra per toli."); return 1;}
		if(GetPlayerState(id) == PLAYER_STATE_PASSENGER || GetPlayerState(id) == PLAYER_STATE_DRIVER)
		{
			return SendInfoMessage(playerid,"~r~Zaidejas privalo islipti is masinos");
		}

		if(GetPlayerMoneyA(playerid)<COST_GESINTUVAS)
		{
			SendInfoMessage(playerid,"Gesintuvo iteikimas kainuoja "#COST_GESINTUVAS"EUR.");
			return 1;
		}

		GivePlayerMoneyA(playerid,-COST_GESINTUVAS);
        if(id!=playerid)
        	Pelnas(playerid,65,COST_GESINTUVAS*2);
        if(id != playerid) playerDB[playerid][jobpts]++;
		SendInfoMessage(playerid,"Gesintuvas iteiktas.");
		SendInfoMessage(id,"Jus gavote gesintuva. Su juo galite uzgesinti deganti automobili.");

		GivePlayerWeaponEx(id,42,1000);
		return 1;
}
CMD:narktest(playerid,params[])
{
	new vardas[128];
	if(playerDB[playerid][specialybe]!=2 && playerDB[playerid][specialybe]!=93 && !playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda skirta tik medikams."); return 1;}
	if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Norint patikrinti zmogaus krauja: /narktest [vardo dalis]."); return 1;}
	new id = GetPlayeridMid(vardas);
	if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Atsiprasome, taciau zaidejas yra neprisijunges."); return 1;}
	new Float:Coo[3];
	if(id == playerid) return SendInfoMessage(playerid,"Sau testo atlikti negali!");
	GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
	if(!IsPlayerInRangeOfPointEx(5, playerid, Coo[0],Coo[1],Coo[2])){SendInfoMessage(playerid,"Atsiprasome, taciau zaidejas yra per toli."); return 1;}


	if(GetPlayerMoneyA(playerid)<COST_NARKTEST)
	{
		SendInfoMessage(playerid,"Narkotiku testas kainuoja "#COST_NARKTEST"EUR.");
		return 1;
	}

	GivePlayerMoneyA(playerid,-COST_NARKTEST);
	Pelnas(playerid,1,COST_NARKTEST*3);
	playerDB[playerid][jobpts]++;
	GetPlayerName(id,vardas,MAX_PLAYER_NAME);
	new query[256];
	
	for(new type;type<3;type++)
	{
		if(type==0)
		{
			format(query,sizeof(query),"SELECT SUM(`Variable`) From Logs WHERE UPPER(`Zaidejas`)=UPPER('%s') AND Veiksmas='LSD' LIMIT 1",vardas);
		}
		else if(type==1)
		{
			format(query,sizeof(query),"SELECT SUM(`Variable`) From Logs WHERE UPPER(`Zaidejas`)=UPPER('%s') AND Veiksmas='Ratai' LIMIT 1",vardas);
		}
		else if(type==2)
		{
			format(query,sizeof(query),"SELECT SUM(`Variable`) From Logs WHERE UPPER(`Zaidejas`)=UPPER('%s') AND Veiksmas='Amfa' LIMIT 1",vardas);
		}
		mysql_function_query(SQL, query, true, "SQL_NarkoTest", "iii", playerid,id,type);
	}
		
	/*
	SendInfoMessage(playerid,"Sveikatos pazimejimas iteiktas.");
	playerDB[id][spaz]=true;
	SendInfoMessage(id,"Jums buvo iteiktas sveikatos pazymejimas. Nepamirskite po savaites vel pasitikrinti.");
	if(id != playerid) pelnas[1]+=(COST_SPAZ/2);
	playerDB[playerid][jobpts]++;
	new file[128], vardasx[24]; // Susikuriam string kintamuosius.
	GetPlayerName(id, vardasx, 24); // Gaunam zaidejo varda.

	format(file,128,"UPDATE `Account` SET `MLicense`= 7 WHERE `Name` = '%s'",vardasx);
	mysql_query(file);*/
	return 1;
}

CMD:spaz(playerid,params[])
{
        new vardas[128];
		if(playerDB[playerid][specialybe]!=2 && playerDB[playerid][specialybe]!=93 && !playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda skirta tik medikams."); return 1;}
		if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Norint iteikti sveikatos pazymejima rasykite: /spaz [vardo dalis]."); return 1;}
		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Atsiprasome, taciau zaidejas yra neprisijunges."); return 1;}
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(5, playerid, Coo[0],Coo[1],Coo[2])){SendInfoMessage(playerid,"Atsiprasome, taciau zaidejas yra per toli."); return 1;}


		if(GetPlayerMoneyA(playerid)<COST_SPAZ)
		{
			SendInfoMessage(playerid,"Sveikatos pazymejimo iteikimas kainuoja "#COST_SPAZ"EUR.");
			return 1;
		}

		GivePlayerMoneyA(playerid,-COST_SPAZ);
		ProcessAchievement(playerid,27);
		SendInfoMessage(playerid,"Sveikatos pazimejimas iteiktas.");
		
		playerDB[id][spaz]=true;
		SendInfoMessage(id,"Jums buvo iteiktas sveikatos pazymejimas. Nepamirskite po savaites vel pasitikrinti.");

		if(id != playerid) 
			Pelnas(playerid,1,COST_SPAZ*3);
		playerDB[playerid][jobpts]++;
		new file[128], vardasx[24]; // Susikuriam string kintamuosius.
		GetPlayerName(id, vardasx, 24); // Gaunam zaidejo varda.

		format(file,128,"UPDATE `Account` SET `MLicense`= 7 WHERE `Name` = '%s'",vardasx);
		mysql_query(file);
		return 1;
}


CMD:pinigai(playerid,params[])
{
        new name[128];
    	if(sscanf(params,"s[24]",name)){SendInfoMessage(playerid,"Norint suzinoti kiek zaidejas turi pinigu rasykite: /pinigai [dalis vardo]."); return 1;}
		new id = GetPlayeridMid(name);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Zaidejas nera prisijunges."); return 1;}
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(50, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(id) == PLAYER_STATE_SPECTATING){SendInfoMessage(playerid,"Zaidejas per toli, prieikite arciau."); return 1;}
		new mess[128];
		GetPlayerName(id,name,sizeof(name));
		format(mess,sizeof(mess),"Kiðenëje %s turi %s€, o banke turi %s€.",name,FormatNumber(playerDB[id][pinigai]),FormatNumber(playerDB[id][banke]));
		SendClientMessage(playerid,COLOR,mess);
		return 1;


}




CMD:duoti(playerid,params[])
{
        if(GetPlayerScore(playerid) < 100){ SendInfoMessage(playerid,"Jus dar nepakankamai patyres, kad duotumet pinigu, reikia: xp>100."); return 1;}
		if(TradingWith[playerid] != -1) return SendInfoMessage(playerid,"Uzdaryk mainus!");
    	new tname[128],moneys;
		if(sscanf(params,"s[24]d",tname,moneys))
		{
			SendInfoMessage(playerid,"Norint duoti pinigu rasykite /duoti [vardas] [kiek].");
			return 1;
		}
		if(moneys < 0) return 0;
		new tid = GetPlayeridMid(tname);
		if(tid==INVALID_PLAYER_ID)
		{
			SendInfoMessage(playerid,"Zaidejas neprisijunges.");
			return 1;
		}
		if(tid == playerid)
			return SendInfoMessage(playerid,"Sau pinigu duoti negali.");

		GetPlayerName(tid,tname,sizeof(tname));

		if(GetPlayerMoneyA(playerid) < moneys){SendInfoMessage(playerid,"Jus neturite tiek pinigu."); return 1;}
		new Float:Coo[3];
		GetPlayerPos(tid,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(5, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(tid)==PLAYER_STATE_SPECTATING || GetPlayerVirtualWorld(tid) != GetPlayerVirtualWorld(playerid)){SendInfoMessage(playerid,"Zaidejas yra per toli."); return 1;}
		GivePlayerMoneyA(tid,moneys);
		GivePlayerMoneyA(playerid,-moneys);
		new mess[128],name[MAX_PLAYER_NAME];
		GetPlayerName(playerid,name,sizeof(name));
		format(mess,sizeof(mess),"***[%s >> %i €] Gavote %s € is %s",name,moneys,FormatNumber(moneys),name);
		SendClientMessage(tid,COLOR,mess);
		format(mess,sizeof(mess),"***[%i € >> %s] Davete %s € %s",moneys,tname,FormatNumber(moneys),tname);
		SendClientMessage(playerid,COLOR,mess);
		if(GetPlayerScore(tid) < 3000)
			ProcessAchievement(playerid,99,moneys);
        new msg[128];
		format(msg,128," * %s duoda %s € %s.",name,FormatNumber(moneys),ReturnName(tid));
		ProxDetector(5.0, playerid, msg, COLOR_CHAT1,COLOR_CHAT2,COLOR_CHAT3,COLOR_CHAT4,COLOR_CHAT5);

		return 1;
}

CMD:ginklas(playerid,params[])
{
    	new tname[128],moneys;
		if(sscanf(params,"s[24]d",tname,moneys))
		{
			SendInfoMessage(playerid,"Norint duoti ginkla rasykite: /ginklas [vardos dalis] [kiekis].");
			return 1;
		}
		if(GetPlayerWeapon(playerid) < 2) return SendInfoMessage(playerid,"Pasirinkite ginkla, kuri norite duoti.");
        if(moneys <= 0) return SendInfoMessage(playerid,"Irasykite tinkama kulku skaiciu.");
		new tid = GetPlayeridMid(tname);

		if(tid==INVALID_PLAYER_ID)
		{
			SendInfoMessage(playerid,"Zaidejas neprisijunges.");
			return 1;
		}

		GetPlayerName(tid,tname,sizeof(tname));

		new ammo = GetPlayerAmmo(playerid);
		new weapon = GetPlayerWeapon(playerid);
		if(weapon < 0) weapon=0;
		if(ammo < moneys || ammo > 10000)
		{
			SendInfoMessage(playerid,"Jus neturite tiek kulku.");
			return 1;
		}
		new Float:Coo[3];
		GetPlayerPos(tid,Coo[0],Coo[1],Coo[2]);
		if(GetPlayerScore(playerid) < 100)
			return SendInfoMessage(playerid,"Ginklus gali duoti tik nuo 100xp");
		if(!IsPlayerInRangeOfPointEx(5, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(tid) == PLAYER_STATE_SPECTATING || GetPlayerState(playerid) == PLAYER_STATE_SPECTATING || GetPlayerVirtualWorld(tid) != GetPlayerVirtualWorld(playerid))
		{
			SendInfoMessage(playerid,"Zaidejas yra per toli.");
			return 1;
		}
		if(GetPlayerState(tid) == PLAYER_STATE_PASSENGER || GetPlayerState(tid) == PLAYER_STATE_DRIVER)
		{
			return SendInfoMessage(playerid,"~r~Zaidejas privalo islipti is masinos");
		}
		if(GetPlayerState(playerid) == PLAYER_STATE_PASSENGER || GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			return SendInfoMessage(playerid,"~r~Privalai islipti is masinos");
		}
		new bolas=0;
		new name[MAX_PLAYER_NAME];
		GetPlayerName(playerid,name,sizeof(name));
		for(new i; i<MAX_FAMILY;i++)
		{
			if(0==strcmp(FamilyInfo[i][FamilyLeader],name,false) || 0==strcmp(FamilyInfo[i][FamilySubstitute],name,false) )
				bolas=1;
		}	
		if(!playerDB[playerid][admin] && !bolas)
		{
			switch(weapon)
			{       //mp5,dgl,awp,ak
			    //case 29,24,30,34: { if(playerDB[playerid][specialybe] !=32) return SendInfoMessage(playerid,"Siuos ginklus gali duoti tik Dealeriai."); }
			   				//case 27: { if(playerDB[playerid][pgang] != PlaceOwnedBy[3]) { return SendInfoMessage(playerid,"Siu ginklu duoti negalima."); } }
				case WEAPON_HEATSEEKER, WEAPON_UZI, WEAPON_MINIGUN: { SendInfoMessage(playerid,"Necheatink!"); Kick(playerid); return 1; }
				case 18,23,44,45,32,40,39,0..7,9..13,16,17, WEAPON_ROCKETLAUNCHER: { return SendInfoMessage(playerid,"Siu ginklu duoti negalima."); }
			}
		}
		else
		{
		    switch(weapon)
		    {
		        case WEAPON_HEATSEEKER, WEAPON_UZI, WEAPON_MINIGUN, WEAPON_ROCKETLAUNCHER:
					return SendInfoMessage(playerid,"Siu ginklu duoti negalima.");
				case 18,23,44,45,32,40,39,0..7,9..13,16,17: { return SendInfoMessage(playerid,"Siu ginklu duoti negalima."); }

		    }
		}
		new slotz = GetWeaponsSlot(weapon);


		
		if(GunData[playerid][slotz][0] != weapon || (ammo > GunData[playerid][slotz][1])) 
			return 1;//return Kick(playerid);


		new ab[2];
		

		

		ab[0]=GunData[tid][slotz][0];
		ab[1]=GunData[tid][slotz][1];
		if(ab[0] != weapon)
		{
			if(ab[0] == 27 && weapon == 25)
				return SendInfoMessage(playerid,"Sis zaidejas turi combat shotgun, todel jam negalite duoti shotgun.");
			if(ab[0] == 24 && weapon == 22)
				return SendInfoMessage(playerid,"Sis zaidejas turi desert eagle, todel jam negalite duoti pistol.");
			if(ab[0] == 34 && weapon == 33)
				return SendInfoMessage(playerid,"Sis zaidejas turi AWP, todel negalite jam duoti rifle.");
		}

		GivePlayerWeaponEx(tid,weapon,moneys);

		GivePlayerWeaponEx(playerid, weapon, -moneys);
		//GivePlayerWeaponEx(tid, weapon, moneys);
		//UpdateWeaps(tid,weapon,moneys);
		NoCheck[tid]=3;
		NoCheck[playerid]=3;
		new mess[128],wep[64];
		GetWeaponName(weapon,wep,sizeof(wep));

		format(mess,sizeof(mess),"Davete %s (%i) %s",wep,moneys,tname);
		SendInfoMessage(playerid,mess);

		GetPlayerName(playerid,tname,sizeof(tname));
		format(mess,sizeof(mess),"%s jums dave %s (%i)",tname,wep,moneys);
		SendInfoMessage(tid,mess);
		
        new msg[128];
		format(msg,128," * %s duoda %s %s.",tname,wep,ReturnName(tid));
		ProxDetector(30.0, playerid, msg, COLOR_CHAT1,COLOR_CHAT2,COLOR_CHAT3,COLOR_CHAT4,COLOR_CHAT5);

		return 1;
}
CMD:vip(playerid,params[])
{
		new textaz[128];
		if(sscanf(params,"s[128]",textaz))
		{
			SendClientMessage(playerid,ORANGE,"Prisijunge VIP'ai:");
			new zin[50],nr;
			foreach (Player, i)
			{
				if(playerDB[i][vip] && !playerDB[i][invisible])
				{
				    nr++;
					format(zin,50,"%i. %s",nr,ReturnName(i));
                    SendClientMessage(playerid,ORANGE,zin);
				}
			}
			return 1;
		}
		if(!playerDB[playerid][vip] && GetPlayerScore(playerid) < 100)
		{
			return SendInfoMessage(playerid,"Vipams rasyti gali tik nuo 100xp!");
		}
		new zin[128],name[MAX_PLAYER_NAME];
		GetPlayerName(playerid,name,MAX_PLAYER_NAME);
		format(zin,sizeof(zin),"%s VIPAMS: %s",name,textaz);

		foreach (Player, i)
		{
			if((playerDB[i][vip]  || playerDB[i][admin]) && BitFlag_Get(PConfig[i],PCFG_SHOWVIPCHAT))
			{
			    if(i != playerid)
					SendClientMessage(i,COLOR_GREEN,zin);
			}
		}
		SendClientMessage(playerid,COLOR_GREEN,zin);
		return 1;
}
CMD:vkick(playerid,params[])
{
		if(!playerDB[playerid][vip]) return SendInfoMessage(playerid,"Si komanda tik vipam.");
		new vardas[128],prz[128];

		if(sscanf(params,"s[24]s[128]",vardas,prz)){SendInfoMessage(playerid,"Ismesti zaideja: /vkick [dalis vardo] [priezastis]"); return 1;}
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
		if (playerDB[id][vip]){ SendInfoMessage(playerid,"~r~VIP ismesti negalima!."); return 1;}
		if(GetPVarInt(id, "nokick") > GetTickCount()) { SendInfoMessage(playerid, "Siuo metu zaidejo ismesti negali"); return 1;}
		if (playerDB[id][admin] || playerDB[id][playingpoker]){ SendInfoMessage(playerid,"~r~Nori prarasti VIP?"); return 1;}
		if(playerDB[id][authstate]==0 || IsPlayerNPC(id)) { SendInfoMessage(playerid,"Zaidejas dar jungiasi."); return 1;}
		new tick=GetTickCount();
		if((tick-LastKick[playerid]) < 60000) return SendInfoMessage(playerid,"~r~Kickinti galite tik kas minute!");
		LastKick[playerid]=tick;
		new msg[128],vipname[MAX_PLAYER_NAME];
		GetPlayerName(id,vardas,sizeof(vardas));
		GetPlayerName(playerid,vipname,sizeof(vipname));
		format(msg,sizeof(msg),"[kick] %s ismete %s is serverio (%s).",vipname,vardas,prz);
		SendClientMessageToAll(BLUE,msg);
		//format(msg,sizeof(msg),"[kick] %s",prz);
		//SendClientMessage(id,BLUE,msg);
		Stop(id);
		TogglePlayerControllable(id,false);
		KickEx(id);
		MLog(playerid,"Iskickino","ss",vardas,prz);
		return 1;
}


CMD:admin(playerid,params[])
{
		new textaz[128];
        if(sscanf(params,"s[128]",textaz))
		{
			SendClientMessage(playerid,0x45A9BAFF,"Prisijungæ administratoriai:");
			new nr;
			new zin[50];
			foreach (Player, i)
			{
				if(playerDB[i][admin] && !playerDB[i][invisible])
				{
				    nr++;
					format(zin,50,"%i. %s",nr,ReturnName(i));
                    SendClientMessage(playerid,0x45A9BAFF,zin);
				}
			}
			SendInfoMessage(playerid,"Naudojimas: /admin [problema]");
			return 1;
		}
		new zin[128],name[MAX_PLAYER_NAME];
		GetPlayerName(playerid,name,MAX_PLAYER_NAME);
		format(zin,sizeof(zin),"%s administratoriams: %s",name,textaz);
		lastiadmin=playerid;
		new xp = GetPlayerScore(playerid);
		foreach (Player, i)
		{
			if(playerDB[i][admin])
			{
				if(xp > 3000)
					SendClientMessage(i,0x91649BFF,zin);
				else
					SendClientMessage(i,0xD9A0B8FF,zin);
			}
		}
		SendClientMessage(playerid,0xB64977FF,zin);
		return 1;
}
CMD:hp(playerid,params[])
{
        new tname[MAX_PLAYER_NAME],namux[128];

		if(sscanf(params,"s[24]",namux)) {SendInfoMessage(playerid,"Parodyti jo ( jos ) hp: /hp [nick]"); return 1;}

		new tid = GetPlayeridMid(namux);
		if(tid==INVALID_PLAYER_ID){SendInfoMessage(playerid,"Tokio vardo nera "); return 1;}
		new Float:Coo[3];
		GetPlayerPos(tid,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(15, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(tid) == PLAYER_STATE_SPECTATING){SendInfoMessage(playerid,"Zaidejas per toli, prieikite arciau."); return 1;}
		GetPlayerName(tid,tname,sizeof(tname));
		new Float:thealth;
		GetPlayerHealth(tid,thealth);
		new msg[128];
		format(msg,sizeof(msg),"***%s sveikata: %i/100",tname,floatround(thealth));
		SendClientMessage(playerid,COLOR,msg);
		return 1;
}
CMD:vhp(playerid,params[])
{
        new tname[MAX_PLAYER_NAME],namux[128];

		if(sscanf(params,"s[24]",namux)) {SendInfoMessage(playerid,"Parodyti jo ( jos ) automobilio hp: /vhp [nick]"); return 1;}

		new tid = GetPlayeridMid(namux);
		if(tid==INVALID_PLAYER_ID){SendInfoMessage(playerid,"Tokio vardo nera "); return 1;}
		new Float:Coo[3];
		GetPlayerPos(tid,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(15, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(tid) == PLAYER_STATE_SPECTATING){SendInfoMessage(playerid,"Zaidejas per toli, prieikite arciau."); return 1;}
		new vehicleid = GetPlayerVehicleID(tid);
		if(!vehicleid) return SendInfoMessage(playerid,"Zaidejas ne automobilyje!");
		GetPlayerName(tid,tname,sizeof(tname));
		new Float:thealth;
		GetVehicleHealth(vehicleid,thealth);
		new msg[128];
		format(msg,sizeof(msg),"***%s sveikata: %i/1000",tname,floatround(thealth));
		SendClientMessage(playerid,COLOR,msg);
		return 1;
}


CMD:gskin(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][pgang] == -1) 
		return SendInfoMessage(playerid,"Tu neturi gaujos!");

	SendClientMessage(playerid, COLOR_GREEN,"======={GAUJU SKINAI}======");
	SendClientMessage(playerid, COLOR_WHITE," /gskin1 /gskin2 /gskin3 /gskin4");
	return 1;
	
}
CMD:gskin1(playerid,params[])
{
	if(!playerDB[playerid][vip]) return SendInfoMessage(playerid,"Si komanda tik vipam.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) 
		return SendInfoMessage(playerid,"Islipk is masinos!");
	if(playerDB[playerid][pgang] == -1) 
		return SendInfoMessage(playerid,"Tu neturi gaujos!");
	if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_NONE)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Bandyk dar karta.");
	}
	if(!galikast[playerid])
	{
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Pabandyk veliau.");
	}
	galikast[playerid]=false;
	SetTimerEx("GaliKast",5000,0,"i",playerid);
	new listitem = 0;
	SetPlayerSkin(playerid,FamilySkins[playerDB[playerid][pgang]][listitem]);
	playerDB[playerid][drabuziai] = FamilySkins[playerDB[playerid][pgang]][listitem];
	playerDB[playerid][uniformd] = false;
	return 1;
}
CMD:gskin2(playerid,params[])
{
	if(!playerDB[playerid][vip]) return SendInfoMessage(playerid,"Si komanda tik vipam.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) 
		return SendInfoMessage(playerid,"Islipk is masinos!");
	if(playerDB[playerid][pgang] == -1) 
		return SendInfoMessage(playerid,"Tu neturi gaujos!");
	if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_NONE)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Bandyk dar karta.");
	}
	if(!galikast[playerid])
	{
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Pabandyk veliau.");
	}
	galikast[playerid]=false;
	SetTimerEx("GaliKast",5000,0,"i",playerid);
	new listitem = 1;
	SetPlayerSkin(playerid,FamilySkins[playerDB[playerid][pgang]][listitem]);
	playerDB[playerid][drabuziai] = FamilySkins[playerDB[playerid][pgang]][listitem];
	playerDB[playerid][uniformd] = false;
	return 1;
}
CMD:gskin3(playerid,params[])
{
	if(!playerDB[playerid][vip]) return SendInfoMessage(playerid,"Si komanda tik vipam.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) 
		return SendInfoMessage(playerid,"Islipk is masinos!");
	if(playerDB[playerid][pgang] == -1) 
		return SendInfoMessage(playerid,"Tu neturi gaujos!");
	if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_NONE)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Bandyk dar karta.");
	}
	if(!galikast[playerid])
	{
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Pabandyk veliau.");
	}
	galikast[playerid]=false;
	SetTimerEx("GaliKast",5000,0,"i",playerid);
	new listitem = 2;
	SetPlayerSkin(playerid,FamilySkins[playerDB[playerid][pgang]][listitem]);
	playerDB[playerid][drabuziai] = FamilySkins[playerDB[playerid][pgang]][listitem];
	playerDB[playerid][uniformd] = false;
	return 1;
}
CMD:gskin4(playerid,params[])
{
	if(!playerDB[playerid][vip]) return SendInfoMessage(playerid,"Si komanda tik vipam.");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) 
		return SendInfoMessage(playerid,"Islipk is masinos!");
	if(playerDB[playerid][pgang] == -1) 
		return SendInfoMessage(playerid,"Tu neturi gaujos!");
	if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_NONE)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Bandyk dar karta.");
	}
	if(!galikast[playerid])
	{
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Pabandyk veliau.");
	}
	galikast[playerid]=false;
	SetTimerEx("GaliKast",5000,0,"i",playerid);
	new listitem = 3;
	SetPlayerSkin(playerid,FamilySkins[playerDB[playerid][pgang]][listitem]);
	playerDB[playerid][drabuziai] = FamilySkins[playerDB[playerid][pgang]][listitem];
	playerDB[playerid][uniformd] = false;
	return 1;
}

CMD:vskin1(playerid,params[])
{
	#pragma unused params
	if(!playerDB[playerid][vip]) return SendInfoMessage(playerid,"Si komanda tik vipam.");
	if(playerDB[playerid][psratasvydis]) return SendInfoMessage(playerid,"Cia keist skino negali!");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendInfoMessage(playerid,"Islipk is masinos!"); 
	if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_NONE)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Bandyk dar karta.");
	}
	if(!galikast[playerid])
	{
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Pabandyk veliau.");
	}
	galikast[playerid]=false;
	SetTimerEx("GaliKast",5000,0,"i",playerid);
	SetPlayerSkin( playerid, 297 );  // 163
	return 1;
}

CMD:vskin2(playerid,params[])
{
	#pragma unused params
	if(!playerDB[playerid][vip]) return SendInfoMessage(playerid,"Si komanda tik vipam.");
	if(playerDB[playerid][psratasvydis]) return SendInfoMessage(playerid,"Cia keist skino negali!");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendInfoMessage(playerid,"Islipk is masinos!"); 
	if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_NONE)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Bandyk dar karta.");
	}
	if(!galikast[playerid])
	{
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Pabandyk veliau.");
	}
	galikast[playerid]=false;
	SetTimerEx("GaliKast",5000,0,"i",playerid);
	SetPlayerSkin( playerid, 185 );
	return 1;
}

CMD:vskin3(playerid,params[])
{
	#pragma unused params
	if(!playerDB[playerid][vip]) return SendInfoMessage(playerid,"Si komanda tik vipam.");
	if(playerDB[playerid][psratasvydis]) return SendInfoMessage(playerid,"Cia keist skino negali!");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendInfoMessage(playerid,"Islipk is masinos!"); 
	if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_NONE)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Bandyk dar karta.");
	}
	if(!galikast[playerid])
	{
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Pabandyk veliau.");
	}
	galikast[playerid]=false;
	SetTimerEx("GaliKast",5000,0,"i",playerid);
	SetPlayerSkin( playerid, 83 );
	return 1;
}
CMD:vskin4(playerid,params[])
{
	#pragma unused params
	if(!playerDB[playerid][vip]) return SendInfoMessage(playerid,"Si komanda tik vipam.");
	if(playerDB[playerid][psratasvydis]) return SendInfoMessage(playerid,"Cia keist skino negali!");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendInfoMessage(playerid,"Islipk is masinos!"); 
	if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_NONE)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Bandyk dar karta.");
	}
	if(!galikast[playerid])
	{
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Pabandyk veliau.");
	}
	galikast[playerid]=false;
	SetTimerEx("GaliKast",5000,0,"i",playerid);
	SetPlayerSkin( playerid, 84 );
	return 1;
}

CMD:vskin5(playerid,params[])
{
	#pragma unused params
	if(!playerDB[playerid][vip]) return SendInfoMessage(playerid,"Si komanda tik vipam.");
	if(playerDB[playerid][psratasvydis]) return SendInfoMessage(playerid,"Cia keist skino negali!");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendInfoMessage(playerid,"Islipk is masinos!"); 
	if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_NONE)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Bandyk dar karta.");
	}
	if(!galikast[playerid])
	{
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Pabandyk veliau.");
	}
	galikast[playerid]=false;
	SetTimerEx("GaliKast",5000,0,"i",playerid);
	SetPlayerSkin( playerid, 82 );
	return 1;
}
CMD:vskin6(playerid,params[])
{
	#pragma unused params
	if(!playerDB[playerid][vip]) return SendInfoMessage(playerid,"Si komanda tik vipam.");
	if(playerDB[playerid][psratasvydis]) return SendInfoMessage(playerid,"Cia keist skino negali!");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendInfoMessage(playerid,"Islipk is masinos!"); 
	if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_NONE)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Bandyk dar karta.");
	}
	if(!galikast[playerid])
	{
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Pabandyk veliau.");
	}
	galikast[playerid]=false;
	SetTimerEx("GaliKast",5000,0,"i",playerid);
	SetPlayerSkin( playerid, 98 );
	return 1;
}

CMD:vskin7(playerid,params[])
{
	#pragma unused params
	if(!playerDB[playerid][vip]) return SendInfoMessage(playerid,"Si komanda tik vipam.");
	if(playerDB[playerid][psratasvydis]) return SendInfoMessage(playerid,"Cia keist skino negali!");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendInfoMessage(playerid,"Islipk is masinos!"); 
	if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_NONE)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Bandyk dar karta.");
	}
	if(!galikast[playerid])
	{
		return SendInfoMessage(playerid,"Dabar skino keisti negali. Pabandyk veliau.");
	}
	galikast[playerid]=false;
	SetTimerEx("GaliKast",5000,0,"i",playerid);
	SetPlayerSkin( playerid, 249 );
	return 1;
}

CMD:vskin(playerid,params[])
{
	#pragma unused params
	SendClientMessage(playerid, COLOR_GREEN,"======={VIP SKINAI}======");
	SendClientMessage(playerid, COLOR_WHITE," /vskin1 /vskin2 /vskin3 /vskin4");
	SendClientMessage(playerid, COLOR_WHITE," /vskin5 /vskin6 /vskin7");
	return 1;
}

CMD:start(playerid,params[])
{
	#pragma unused params
	if(!playerDB[playerid][vip] && !playerDB[playerid][admin]) return SendInfoMessage(playerid,"Si komanda tik vipam.");
	if(playerDB[playerid][admin])
	{
		new pName[MAX_PLAYER_NAME];
		new strings[60];
		if (as == false)
		{
			as = true;
			GetPlayerName(playerid, pName, 24);
			format(strings, 60, "*** %s pradëjo skaièiavimà.", pName);
			ProcessAchievement(playerid, 115);
			SendClientMessageToAll(COLOR_GREEN, strings);
			GameTextForAll("~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~g~-~y~ Trys ~g~-",1000,3);
			skaiciavimas=3;
			new Float:coo[3];
			foreach (Player, i)
			{
				GetPlayerPos(i,coo[0],coo[1],coo[2]);
				PlayerPlaySound(i,1056,coo[0],coo[1],coo[2]);
			}
			SetTimer("Count",1000,0);
			//SetTimer("Count1",2000,0);
			//SetTimer("Countgo",3000,0);
			//SetTimer("stop",6000,0);

		}
		else SendInfoMessage(playerid,"Tai jau pradeta !");
		return 1;
	}
	else
	{
		new pName[MAX_PLAYER_NAME];
		new strings[60];
		if (as == false)
		{
			as = true;
			GetPlayerName(playerid, pName, 24);
			format(strings, 60, "*** %s Pradetas skaiciavimas.", pName);
			SendClientMessageToAll(COLOR_LIGHTBLUE, strings);
			ProcessAchievement(playerid, 115);
			//GameTextForAll("~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~g~-~y~ Trys ~g~-",1000,3);
			new Float:Pos[3];
			GetPlayerPos(playerid,Pos[0],Pos[1],Pos[2]);
			skaiciavimas=3;
			new Float:coo[3];
			foreach (Player, i)
			{
				if(IsPlayerInRangeOfPointEx(150.0,i,Pos[0],Pos[1],Pos[2]))
				{
					GetPlayerPos(i,coo[0],coo[1],coo[2]);
					PlayerPlaySound(i,1056,coo[0],coo[1],coo[2]);
					GameTextForPlayer(i,"~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~g~-~y~ Trys ~g~-",1000,3);
				}
			}
			//SetTimer("CountV",1000,0);
			SetTimerEx("CountV",1000,0,"i",playerid);
			//SetTimer("Count1",2000,0);
			//SetTimer("Countgo",3000,0);
			//SetTimer("stop",6000,0);

		}
		else SendInfoMessage(playerid,"Tai jau pradeta !");
		return 1;
	
	}
}


CMD:dchat(playerid,params[])
{
	if(!playerDB[playerid][plead]) return SendInfoMessage(playerid,"Tai direktoriaus komandos.");
	switch(playerDB[playerid][plead])
	{
		case 98,90,58: return SendInfoMessage(playerid,"Nelegalus darbai neturi /dchat!");
	}
	new msg[256],msgz[24],zinuc[256];

	GetPlayerName(playerid, msgz, MAX_PLAYER_NAME);
	
	if(sscanf(params,"s[256]",zinuc))
	{
		SendInfoMessage(playerid,"Paskelbti atrankas: /dchat [zinute]");
		return 1;
	}
	/*new dar[30];
	switch(playerDB[playerid][plead])
	{
		case 2: dar="Medikø";
		case 3: dar="Transporto";
		case 5: dar="Kroviniø Tr.";
		case 6: dar="Mechanikø";
		case 34: dar = "NTA";
		case 66: dar = "Gaisrinës";
		case 70: dar = "Autoklubo";
		case 80: dar = "Teisësaugos";
		case 50: dar = "Skelbëjø";
		case 98: dar = "Baikeriø";
		case 90: dar = "Dyleriø";
		case 58: dar = "Vagiø";
		case 60: dar = "Inkasatoriø";
		default: dar = "";
	}*/


	if(playerDB[playerid][lytis] == 2)
		format(msg, sizeof(msg), "* Direktorë %s: %s", msgz, zinuc);
	else
		format(msg, sizeof(msg), "* Direktorius %s: %s", msgz, zinuc);
	SendClientMessageToAllEx(PREZ_COLOR,msg);
	return 1;

}

CMD:priimti(playerid,params[]) 
	return cmd_priimt(playerid,params);
CMD:priimt(playerid,params[])
{
	if(!playerDB[playerid][plead]) return SendInfoMessage(playerid,"Tai direktoriaus komandos.");
	new name[128];
	if(sscanf(params,"s[24]",name))
	{
		SendInfoMessage(playerid,"Noredami priimti darbuotoja i savo firma rasykite: /priimt [vardo dalis]");
		return 1;
	}
	new id = GetPlayeridMid(name);

	if(id == INVALID_PLAYER_ID)
	{
		SendInfoMessage(playerid,"Nurodyto vardo nera.");
		return 1;
	}

	new lol=-1,lol2=-1,lol3=-1,lol4=-1,lol5=-1;
	if(playerDB[playerid][plead] == 2){ lol = 2; lol2=93; } // medikai
	else if(playerDB[playerid][plead] == 3){ lol = 3; lol2 = 20; lol3 = 39;} // transportas
	else if(playerDB[playerid][plead] == 5){ lol = 41; lol2 = 44;} // furistai
	else if(playerDB[playerid][plead] == 6){ lol = 6; lol2 = 28;} // autospeciai
	else if(playerDB[playerid][plead] == 66){ lol = 66; lol2= 67;} // zudikai
	else if(playerDB[playerid][plead] == 70){ lol = 70; lol2 = 73; lol3 = 72;} // autoklubas
	else if(playerDB[playerid][plead] == 80){ lol = 80; lol2 = 81; lol3 = 83; lol4 = 84; lol5=-1;}// teisesauga
	else if(playerDB[playerid][plead] == 50){ lol = 50;} // skelbejai
	else if(playerDB[playerid][plead] == 98){ lol = 81;} // baikeriai
	else if(playerDB[playerid][plead] == 34) { lol=34;}
	else if(playerDB[playerid][plead] == 58){ lol = 58;} //

	else if(playerDB[playerid][plead] == 90){ lol = 31; lol2=32;} // dealeriai 
	else if(playerDB[playerid][plead] == 60){ lol=60;}
	if(playerDB[id][leanvited][playerDB[playerid][plead]-1] ||
	playerDB[id][specialybe]== lol ||
	playerDB[id][specialybe]== lol2 ||
	playerDB[id][specialybe]== lol3 ||
	playerDB[id][specialybe]== lol4 ||
	playerDB[id][specialybe]== lol5)
	{
		SendInfoMessage(playerid,"Jis ( Ji ) jau priimtas.");
		return 1;
	}
	GetPlayerName(id,name,sizeof(name));
	/*
	if(lol==81 || lol== 31 || lol==58)
	{
		if(playerid != id) 
		{
			if(GetPlayerMoneyA(playerid) < COST_KYSIS) return SendInfoMessage(playerid,"Jums truksta pinigu. Kysis i mero fonda - "#COST_KYSIS"€/pakv.");
			Server[kysiufondas]+=COST_KYSIS;
			GivePlayerMoneyA(playerid,-COST_KYSIS);
			MLog(playerid,"Padejo i kfonda","is",COST_KYSIS,name);
			SendClientMessage(playerid,WHITE," * Padejai "#COST_KYSIS"€ i kysiu fonda!");
		}
	}*/




	if(playerDB[playerid][plead] == LEAD_TEISESAUGA) SendClientMessage(id,GANG_COLOR,"Jus esate kvieciamas istoti i Los Santos teisesauga buri.");
	else if(playerDB[playerid][plead] == LEAD_MEDIKAI) SendClientMessage(id,GANG_COLOR,"Jus esate kvieciamas prisijungti prie Los Santos mediku komandos.");
	//else if(playerDB[playerid][plead] == LEAD_APSAUGA) SendClientMessage(id,GANG_COLOR,"Jus esate kvieciamas dirbti Los Santos apsauginiu.");
	else if(playerDB[playerid][plead] == LEAD_AUTOSPECAI) SendClientMessage(id,GANG_COLOR,"Jus esate kvieciamas i Los Santos mechaniku gretas.");
	else if(playerDB[playerid][plead] == LEAD_GAISRAS) SendClientMessage(id,GANG_COLOR,"Jus esate kvieciamas dirbti Los Santos gaisrininku.");
	else if(playerDB[playerid][plead] == LEAD_KLUBAI) SendClientMessage(id,GANG_COLOR,"Jus esate kvieciamas i automanu kluba.");
	else if(playerDB[playerid][plead] == LEAD_VALSTYBE) SendClientMessage(id,GANG_COLOR,"Jus esate kvieciamas dirbti Los Santos skelbeju.");
	else if(playerDB[playerid][plead] == LEAD_TRANSPORTAS) SendClientMessage(id,GANG_COLOR,"Jus esate kvieciamas dirbti Los Santos taksistu.");
	else if(playerDB[playerid][plead] == LEAD_FURISTAS) SendClientMessage(id,GANG_COLOR,"Jus esate kvieciamas dirbti Los Santos kroviniu pervezeju.");
	else if(playerDB[playerid][plead] == LEAD_GIDAI) SendClientMessage(id,GANG_COLOR,"Jus esate kvieciamas dirbti Los Santos Gidu.");
	else if(playerDB[playerid][plead] == LEAD_BAIKERIAI) SendClientMessage(id,GANG_COLOR,"Jus esate kvieciamas dirbti Los Santos Baikeriu.");
	else if(playerDB[playerid][plead] == LEAD_DEAL) SendClientMessage(id,GANG_COLOR,"Jus esate kvieciamas dirbti Los Santos Kontrabandininku.");
	else if(playerDB[playerid][plead] == LEAD_PADUGNES) SendClientMessage(id,GANG_COLOR,"Prisijunk prie musu sunie ( vagiu ).");
	else if(playerDB[playerid][plead] == 34) SendClientMessage(id,GANG_COLOR,"Jus esate kvieciamas istoti i Los Santos nekilnojamo turto agentu buri");
	else if(playerDB[playerid][plead] == 60) SendClientMessage(id,GANG_COLOR,"Jus esate kvieciamas istoti i Los Santos Inkasatorius");
	playerDB[id][leanvited][playerDB[playerid][plead]-1]=true;
	new msg[128];
	format(msg,sizeof(msg),"Pakvietete %s istoti i jusu firma.",name);
	ProcessAchievement(id,41);
	SendInfoMessage(playerid,msg);
	MLog(playerid,"Prieme","s",name);
	return 1;

}



CMD:isspirti(playerid,params[])
{
		if(!IsPlayerInAnyVehicle(playerid))
		{
			SendInfoMessage(playerid,"Turite buti masinoje!");
			return 1;
		}
		if(GetPlayerInterior(playerid) != 0) 
		{
			SendInfoMessage(playerid, "Cia sitos komandos naudoti negali");
			return 1;
		}
		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		{
			SendInfoMessage(playerid,"Turite buti masinos vairuotojas!!");
			return 1;
		}
		new tname[128];
		if(sscanf(params,"s[24]",tname)){SendInfoMessage(playerid,"Isspirti zaideja is masinos: /isspirt(i) [dalis nicko]"); return 1;}
		new tid = GetPlayeridMid(tname);
		if(tid==INVALID_PLAYER_ID)
		{
			SendInfoMessage(playerid,"Tokio zaidejo nera.");
			return 1;
		}
		if(!IsPlayerInAnyVehicle(tid) || GetPlayerVehicleID(tid) != GetPlayerVehicleID(playerid))
		{
			SendInfoMessage(playerid,"Zaidejas ne jusu masinoje!");
			return 1;
		}
		if(tid==playerid) return SendInfoMessage(playerid,"Islipk!");
		RemovePlayerFromVehicle(tid);
		new msg[128], uname[MAX_PLAYER_NAME];
		GetPlayerName(tid, uname, MAX_PLAYER_NAME);
		format(msg, sizeof(msg), "Jus isspyrete %s is savo masinos!", uname);
		SendInfoMessage(playerid,msg);
		return 1;
}
CMD:isspirt(playerid,params[])
{
	return cmd_isspirti(playerid,params);
}
CMD:mismesti(playerid,params[])
{
		#pragma unused params
		foreach (Player, i)
		{
			new playerstate = GetPlayerState(i);
			if(IsPlayerInVehicle(i,Carlist3[playerid][Carid]) || IsPlayerInVehicle(i,Carlist[playerid][Carid]) || IsPlayerInVehicle(i,Carlist2[playerid][Carid]))
			{
				if(playerstate == PLAYER_STATE_DRIVER)
				{
					RemovePlayerFromVehicle(i);
					GameTextForPlayer(i,"~r~Jus ismete savininkas!",3000,5);
					return 1;
				}
			}
		}
		return 1;
}

CMD:parduoti(playerid,params[])
{
	#pragma unused params
    new msg[512];
	if(TradingWith[playerid] != -1) return SendInfoMessage(playerid,"Uzdaryk mainus!");
	if(Carlist[playerid][Typ] == -1 && Carlist2[playerid][Typ] == -1 && Carlist3[playerid][Typ] == -1)
		return SendInfoMessage(playerid,"~r~Neturi ka parduoti!");
    if(Carlist[playerid][Typ]!=-1)
	{
		new price = (aVehicleNames[Carlist[playerid][Typ]][Price]/5)*2;
		if(Carlist[playerid][Typ]==149)
			price = 100;
	    format(msg,sizeof(msg),#TEXT_BLUE"• "#TEXT_WHITE"%s\t%s€",aVehicleNames[Carlist[playerid][Typ]][Name],FormatNumber(price));
        AddDListItem(playerid, msg, 0);
	}
	if(Carlist2[playerid][Typ]!=-1)
	{
		new price = (aVehicleNames[Carlist2[playerid][Typ]][Price]/5)*2;
		if(Carlist2[playerid][Typ]==149)
			price = 100;
	    format(msg,sizeof(msg),#TEXT_BLUE"• "#TEXT_WHITE"%s\t%s€",aVehicleNames[Carlist2[playerid][Typ]][Name],FormatNumber(price));
        AddDListItem(playerid, msg, 1);
	}
	if(Carlist3[playerid][Typ]!=-1)
	{
		new price = (aVehicleNames[Carlist3[playerid][Typ]][Price]/5)*2;
		if(Carlist3[playerid][Typ]==149)
			price = 100;
	    format(msg,sizeof(msg),#TEXT_BLUE"• "#TEXT_WHITE"%s\t%s€",aVehicleNames[Carlist3[playerid][Typ]][Name],FormatNumber(price));
        AddDListItem(playerid, msg, 2);
	}
	
	ShowPlayerDListHeader(playerid, 304, "Parduoti", "Rinktis", "Iseiti","Automobilis\tKaina");

	//	ShowPlayerDialog(playerid,304,DIALOG_STYLE_LIST,"Parduoti","Pirmas automobilis\nAntras automobilis\nTrecias automobilis","Rinktis","Iseiti");
	return 1;
}

CMD:siulyti(playerid,params[])
{
	return SendInfoMessage(playerid, "Naudok komanda /mainytis");
}

CMD:siulyti2(playerid,params[])
{
	return SendInfoMessage(playerid, "Naudok komanda /mainytis");
}

CMD:siulyti3(playerid,params[])
{
	return SendInfoMessage(playerid, "Naudok komanda /mainytis");
}
CMD:atsaukti(playerid,params[])
{
		#pragma unused params
		new string[128];


		foreach (Player, i)
		{
			if (offerCar[i][0]==playerid)
			{
				offerCar[i]={-1,0};
				SendInfoMessage(playerid,"Jus nutraukete savo pasiulyma.");
				new playername[MAX_PLAYER_NAME];
				GetPlayerName(playerid,playername,sizeof(playername));
				format(string,128,"%s nutrauke pasiulyma.",playername);
				SendClientMessage(i, HOMER, string);
				return 1;
			}
			if (offerCar2[i][0]==playerid)
			{
				offerCar2[i]={-1,0};
				SendInfoMessage(playerid,"Jus nutraukete savo pasiulyma.");
				new playername[MAX_PLAYER_NAME];
				GetPlayerName(playerid,playername,sizeof(playername));
				format(string,128,"%s nutrauke pasiulyma.",playername);
				SendClientMessage(i, HOMER, string);
				return 1;
			}
			if (offerCar3[i][0]==playerid)
			{
				offerCar3[i]={-1,0};
				SendInfoMessage(playerid,"Jus nutraukete savo pasiulyma.");
				new playername[MAX_PLAYER_NAME];
				GetPlayerName(playerid,playername,sizeof(playername));
				format(string,128,"%s nutrauke pasiulyma.",playername);
				SendClientMessage(i, HOMER, string);
				return 1;
			}
		}
		SendInfoMessage(playerid,"Jus nesiulote savo masinos!");
		return 1;
}

CMD:perleisti(playerid,params[])
{
		new tname[128];
		if(sscanf(params,"s[24]",tname)){SendInfoMessage(playerid,"Perleisti bizni /perleisti [vardo_dalis]"); return 1;}
		new tid = GetPlayeridMid(tname);

		if(tid==INVALID_PLAYER_ID){SendInfoMessage(playerid,"Tokio zaidejo nera"); return 1;}
		if(TradingWith[playerid] != -1) return SendInfoMessage(playerid,"Uzdaryk mainus!");
		if(tid==playerid){SendInfoMessage(playerid,"Sau biznio perleisti negali!"); return 1;}
		//if(ArTuriBiz(playerid) == -1) return SendInfoMessage(playerid,"Jus neturite verslo!");
		if(!IsInBiz(playerid)) return SendInfoMessage(playerid,"Jus neesate viduje!");
		new i = GetPlayerVirtualWorld(playerid) - MAX_HOUSES*2;
		if(strcmp(BusinessInfo[i][bOwner],ReturnName(playerid),false) || !BusinessInfo[i][bOwned]) return SendInfoMessage(playerid,"Tai ne jusu verslas!");
		//if(ArTuriBiz(tid) != -1) return SendInfoMessage(playerid,"Zaidejas jau turi versla!");
		new msg[128],name[24];
		GetPlayerName(playerid,name,24);
		GetPlayerName(tid,tname,24);
		format(msg,128," * %s Atidave jums savo bizni : \"%s\"",name,BusinessInfo[i][bName]);
		SendClientMessage(tid, PURPLE,msg);
		SendInfoMessage(playerid,"Atidavete savo bizni!");
		strmid(BusinessInfo[i][bOwner],tname,0,MAX_PLAYER_NAME,MAX_PLAYER_NAME);
		new string[128];
	    new idx =i;
	    format(string, sizeof(string), VERSLAS_NEPARDUODAMAS, BusinessInfo[i][bName],BusinessInfo[i][bOwner],GetBussinessType(BusinessInfo[idx][bType]));
		DestroyDynamic3DTextLabel(businesstext[i]);
		businesstext[i] = CreateDynamic3DTextLabel(string,0x00BC00FF,BusinessInfo[i][bEnterX],BusinessInfo[i][bEnterY],BusinessInfo[i][bEnterZ],40.0, _,_, 1);
		ProcessAchievement(tid,45);
		return 1;
}

CMD:bucinys(playerid,params[])
{
		new name[128];
		if(sscanf(params,"s[24]",name)){SendInfoMessage(playerid,"Pabuciuoti zaideja: /bucinys [vardoo dalis]"); return 1;}
		new tid = GetPlayeridMid(name);
		if(tid==INVALID_PLAYER_ID){SendInfoMessage(playerid,"Tokio zaidejo nera"); return 1;}
		if(tid==playerid){SendInfoMessage(playerid,"Saves pabuciuoti negali!"); return 1;}
		if(GetDistanceBetweenPlayers(playerid,tid) > 3 || GetPlayerState(tid) == PLAYER_STATE_SPECTATING || GetPlayerVirtualWorld(tid) != GetPlayerVirtualWorld(playerid)){SendInfoMessage(playerid,"Zaidejas per toli!"); return 1;}
		if(IsPlayerInAnyVehicle(playerid) || IsPlayerInAnyVehicle(tid)){SendInfoMessage(playerid,"Masinoje buciuotis negalima!"); return 1;}
		if(playerDB[playerid][ikalintas] || playerDB[tid][ikalintas]) {SendInfoMessage(playerid,"Kalejime buciuotis negalima."); return 1;}
		SiuloBuciuotis[tid]=playerid;
		new msg[128];
		GetPlayerName(playerid,name,24);
		format(msg,128,"~p~%s Siulo jums pasibuciuoti! Noredami sutikti rasykite /ok",name);
		SendInfoMessage(tid,msg);
		SendInfoMessage(playerid,"Siulote pasibuciuoti.");
		return 1;
}
CMD:paspausti(playerid,params[])
{
		new name[128];
		if(sscanf(params,"s[24]",name)){SendInfoMessage(playerid,"Paspausti ranka: /paspausti [vardo dalis]"); return 1;}
		new tid = GetPlayeridMid(name);
		if(tid==INVALID_PLAYER_ID){SendInfoMessage(playerid,"Tokio zaidejo nera"); return 1;}
		if(tid==playerid){SendInfoMessage(playerid,"Paspaudei sau ranka!"); return 1;}
		if(GetDistanceBetweenPlayers(playerid,tid) > 3 || GetPlayerState(tid) == PLAYER_STATE_SPECTATING || GetPlayerVirtualWorld(tid) != GetPlayerVirtualWorld(playerid)){SendInfoMessage(playerid,"Zaidejas per toli!"); return 1;}
		if(IsPlayerInAnyVehicle(playerid) || IsPlayerInAnyVehicle(tid)){SendInfoMessage(playerid,"Paspaudei ranka!"); return 1;}
		if(playerDB[playerid][ikalintas] || playerDB[tid][ikalintas] || CheckZone(tid) != 0) {SendInfoMessage(playerid,"Kalejime/sandeliuose paspausti rankos negalima."); return 1;}
		SiuloPaspausti[tid]=playerid;
		new msg[128];
		GetPlayerName(playerid,name,24);
		format(msg,128,"~p~%s Siulo jums paspausti ranka! Noredami sutikti rasykite /ok",name);
		SendInfoMessage(tid,msg);
		SendInfoMessage(playerid,"Siulote paspausti ranka.");
		return 1;
}
CMD:ok(playerid,params[])
{
		#pragma unused params

    	if(SiuloBuciuotis[playerid]!= -1)
    	{
			new tid = SiuloBuciuotis[playerid],Float:Coo[3];
			GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
			if(!IsPlayerInRangeOfPointEx(5, tid, Coo[0],Coo[1],Coo[2])){ SiuloBuciuotis[playerid]=-1; SendInfoMessage(playerid,"Oro buciniu nedalinam!"); return 1;}
			SetPlayerPos(tid,Coo[0],Coo[1]+1.28,Coo[2]);
			PlayerFacePlayer(playerid, tid);
			ClearAnimations(playerid);
			ClearAnimations(tid);
			ApplyAnimation(playerid,"KISSING","Grlfrd_Kiss_03",4.0,0,0,0,0,0,1); //Pakeisti animacija
			ApplyAnimation(tid,"KISSING","Grlfrd_Kiss_03",4.0,0,0,0,0,0,1);
			SiuloBuciuotis[playerid]=-1;
			SiuloBuciuotis[tid]=-1;
			return 1;
		}
		if(SiuloPaspausti[playerid]!= -1)
    	{
			new tid = SiuloPaspausti[playerid],Float:Coo[3];
			if(playerDB[playerid][admin])
				ProcessAchievement(tid,91);
			GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
			if(!IsPlayerInRangeOfPointEx(5, tid, Coo[0],Coo[1],Coo[2])){ SiuloPaspausti[playerid]=-1; SendInfoMessage(playerid,"Zaidejas yra per toli!"); return 1;}
			SetPlayerPos(tid,Coo[0],Coo[1]+0.78,Coo[2]);
			PlayerFacePlayer(playerid, tid);
			ClearAnimations(playerid);
			ClearAnimations(tid);
			switch(random(9))
			{
				case 0:
	            {
	                ApplyAnimation(playerid, "GANGS", "hndshkaa", 4.0,0,0,0,0,0,1);
	                ApplyAnimation(tid, "GANGS", "hndshkaa", 4.0,0,0,0,0,0,1);
				}
	            case 1:
	            {
	                ApplyAnimation(playerid, "GANGS", "hndshkba", 4.0,0,0,0,0,0,1);
	                ApplyAnimation(tid, "GANGS", "hndshkba", 4.0,0,0,0,0,0,1);
	            }
	            case 2:
	            {
	                ApplyAnimation(playerid, "GANGS", "hndshkca", 4.0,0,0,0,0,0,1);
	                ApplyAnimation(tid, "GANGS", "hndshkca", 4.0,0,0,0,0,0,1);
	            }
	            case 3:
	            {
	                ApplyAnimation(playerid, "GANGS", "hndshkcb", 4.0,0,0,0,0,0,1);
	                ApplyAnimation(tid, "GANGS", "hndshkcb", 4.0,0,0,0,0,0,1);
	            }
	            case 4:
	            {
	                ApplyAnimation(playerid, "GANGS", "hndshkda", 4.0,0,0,0,0,0,1);
	                ApplyAnimation(tid, "GANGS", "hndshkda", 4.0,0,0,0,0,0,1);
	            }
	            case 5:
	            {
	                ApplyAnimation(playerid, "GANGS", "hndshkea", 4.0,0,0,0,0,0,1);
	                ApplyAnimation(tid, "GANGS", "hndshkea", 4.0,0,0,0,0,0,1);
	            }
	            case 6:
	            {
	                ApplyAnimation(playerid, "GANGS", "hndshkfa", 4.0,0,0,0,0,0,1);
	                ApplyAnimation(tid, "GANGS", "hndshkfa", 4.0,0,0,0,0,0,1);
	            }
	            case 7:
	            {
	                ApplyAnimation(playerid, "GANGS", "hndshkfa_swt", 4.0,0,0,0,0,0,1);
	                ApplyAnimation(tid, "GANGS", "hndshkfa_swt", 4.0,0,0,0,0,0,1);
	            }
	            case 8:
	            {
	                ApplyAnimation(playerid, "GANGS", "prtial_hndshk_01", 4.0,0,0,0,0,0,1);
	               	ApplyAnimation(tid, "GANGS", "prtial_hndshk_01", 4.0,0,0,0,0,0,1);
	            }
			}
			SiuloPaspausti[playerid]=-1;
			SiuloPaspausti[tid]=-1;
			return 1;
		}
		return 1;
}


CMD:darbai(playerid,params[])
{
		#pragma unused params
		if((GetPlayerState(playerid) == PLAYER_STATE_DRIVER && playerDB[playerid][specialybe]==5) ||
			 (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && playerDB[playerid][specialybe]==55) ||
			  (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && playerDB[playerid][specialybe]==62) ||
			   vagia[playerid] || (IsPlayerInAnyVehicle(playerid) && (vpakrauta[GetPlayerVehicleID(playerid)]==1 || vbankomatams[GetPlayerVehicleID(playerid)]==1)) )
		{
			SendInfoMessage(playerid,"Prasome islipti is automobilio.");
			return 1;
		}
		ShowPlayerDialog(playerid,012,DIALOG_STYLE_LIST,"Darbai",#TEXT_GREEN"• "#TEXT_WHITE"Mini darbai\n"#TEXT_GREEN"• "#TEXT_WHITE"Darbai be pakvietimo\n"#TEXT_GREEN"• "#TEXT_WHITE"Darbai su pakvietimu\n"#TEXT_GREEN"• "#TEXT_WHITE"Nelegalûs darbai\n \n"#TEXT_GREEN"• "#TEXT_WHITE"Apie darbus","Rinktis","Iseiti");		return 1;
}
CMD:gps(playerid,params[])
{
	return cmd_kur(playerid,params);
}
CMD:kur(playerid,params[])
{
	new stata = GetPlayerState(playerid);
	new vehicleid = GetPlayerVehicleID(playerid);
	if(stata == PLAYER_STATE_DRIVER && (playerDB[playerid][specialybe]==5 || playerDB[playerid][specialybe]==55 || playerDB[playerid][specialybe]==62 || vagia[playerid] || vpakrauta[vehicleid]==1 || vbankomatams[vehicleid]==1) )
	{
		SendInfoMessage(playerid,"Prasome islipti is automobilio.");
		return 1;
	}
	new name[128];
	if(sscanf(params,"s[24]",name))
	{
		//ShowPlayerDialog(playerid,666,DIALOG_STYLE_LIST,"Rasti","Darba\nZmogu\nNama\nBanka\nVairavimo mokykla\nLigonine\nPolicija\nHotelis\nMasinu turgus\nOro uostas\nKlubas\nRegitra\nAutomobiliu nuoma\nZvejyba\nDarbiniu masinu taisykla\nSavivaldybe\nDazasvydis","Rinktis","Iseiti");
		KurMenu(playerid);
		return 1;
	}
    // 
	if(IsNumeric(name))
	{
		new id = strval(name);
		if(id >= MAX_HOUSES || id <= 0 || (strval(hInfo[id][Name]) == 0 && strlen(hInfo[id][Name]) < 3)) return SendInfoMessage(playerid,"Tokio namo nera.");
		new x = hInfo[id][daugiabutis]-1;
		if(!hInfo[id][daugiabutis]) 
			SetPlayerCheckpoint(playerid,hInfo[id][iconx],hInfo[id][icony],hInfo[id][iconz],2);
		else 			
			SetPlayerCheckpoint(playerid,Daugiabuciai[x][dX],Daugiabuciai[x][dY],Daugiabuciai[x][dZ],5.0);
		SendInfoMessage(playerid,"Namo pozicija rodoma Radare!");
		return 1;
	}

	new id = GetPlayeridMid(name);

	if(id == playerid) return SendInfoMessage(playerid,"Ieskai saves?");
	if(id==INVALID_PLAYER_ID)
	{
		SendInfoMessage(playerid,"Tokio vardo nera.");
		return 1;
	}

	if(playerDB[id][pasislepes]|| playerDB[id][suristas] || GetPlayerState(id) == PLAYER_STATE_SPECTATING || GetPlayerInterior(id) != 0 || GetPlayerVirtualWorld(id) != 0)
	{
		SendInfoMessage(playerid,"Zaidejo pozicijos nustatyti neimanoma.");
		return 1;
	}

	new msg[128],Float:coo[6];
	GetPlayerName(id,name,sizeof(name));
	GetPlayerPos(id,coo[0],coo[1],coo[2]);
	GetPlayerPos(playerid,coo[3],coo[4],coo[5]);
	new Float:atstumas = ((floatabs(coo[0]-coo[3])+floatabs(coo[1]-coo[4])+floatabs(coo[2]-coo[5]))/3)/100;
	SetPlayerCheckpoint(playerid,coo[0],coo[1],coo[2],2);

	new salis1[10],salis2[10];

	if(coo[0]-coo[3]>0) salis1="rytus"; else salis1="vakarus";
	if(coo[1]-coo[4]>0) salis2="siaures"; else salis2="pietu";

	format(msg,sizeof(msg),"%s dabartine vieta rodoma GPS. Jis ( Ji ) yra %.1f KM i %s %s nuo jusu.",name,atstumas,salis2,salis1);
	SendInfoMessage(playerid,msg);
	return 1;
}

CMD:mapp(playerid,params[])
	return cmd_kur(playerid,params);


CMD:nparduoti(playerid,params[])
{
		/*if(playerDB[playerid][amfetaminas]<1)
		{
			SendClientMessage(playerid,GREEN,"* Tu neturi narkotiku");
			return 1;
		}*/
		/*
		if(playerDB[playerid][specialybe] !=32)
		{
			SendClientMessage(playerid,GREEN,"* Tu ne dyleris!");
			return 1;
		}
		*/
		new vardas[128], kiek, kaina,rusele[129], rusis;

		if(sscanf(params,"s[24]s[24]dd",vardas,rusele,kiek,kaina))
		{
			SendClientMessage(playerid,BLUE,"* Parduoti narkotiku: /nparduoti [vardo dalis] [rusis] [kiek] [vieno_kaina]");
			SendClientMessage(playerid,COLOR,"* Narkotiku rusys: 1 - Amfetaminas; 2 - Seklos; 3 - Zole; 4 - LSD; 5 - Ekstazis");
			return 1;
		}
        if(kiek <= 0 || kaina < 0 || kaina > 1000000) return 0;
		if(kiek  * kaina < 0 || kiek * kaina > 100000000)
			return SendClientMessage(playerid,-1,"KLAIDA!");
		if(strcmp(rusele,"amfa",true) == 0 || strcmp(rusele,"amfetaminas",true) == 0)
			rusis=1;
		else if(strcmp(rusele,"seklos",true) == 0)
			rusis=2;
		else if(strcmp(rusele,"kanapes",true) == 0 || strcmp(rusele,"zole",true) == 0)
			rusis=3;
		else if(strcmp(rusele,"lsd",true) == 0)
			rusis=4;
		else if(strcmp(rusele,"ratai",true) == 0 || strcmp(rusele,"ekstazis",true) == 0)
			rusis=5;
		else if(strval(rusele) >= 1 && strval(rusele) <= 5)
			rusis = strval(rusele);
		if(rusis < 1 || rusis > 5)
		{
			SendClientMessage(playerid,BLUE,"* Parduoti narkotiku: /nparduoti [vardo dalis] [rusis] [kiek] [vieno_kaina]");
			SendClientMessage(playerid,COLOR,"* Narkotiku rusys: 1 - Amfetaminas; 2 - Seklos; 3 - Zole; 4 - LSD; 5 - Ekstazis");
			return 1;
		}
		new ArTuri;
		switch(rusis)
		{
			case 1: ArTuri = playerDB[playerid][amfetaminas];
			case 2: ArTuri = playerDB[playerid][seklos];
			case 3: ArTuri = playerDB[playerid][zole];
			case 4: ArTuri = playerDB[playerid][lsd];
			case 5: ArTuri = playerDB[playerid][ratai];
		}
		if(ArTuri < kiek) return SendInfoMessage(playerid,"Jus tiek neturite!");


		new id = GetPlayeridMid(vardas);
		if(GetPlayerScore(playerid) < 100)
			return SendInfoMessage(playerid,"Narkotikus gali duoti tik nuo 100xp");
		if (id == INVALID_PLAYER_ID || id == playerid)
		{
			SendInfoMessage(playerid,"Tokio vardo nera");
			return 1;
		}
  		if(kaina > GetPlayerMoneyA(id)) return SendInfoMessage(playerid,"Zaidejas neturi tiek pinigu!");
		if( GetPlayerScore(id) < 200 ) return SendInfoMessage(playerid,"Zaidejas dar nepakankamai patyres.");

		new Float:narkx, Float:narky, Float:narkz;
		GetPlayerPos(id, narkx, narky, narkz);
		if(!IsPlayerInRangeOfPointEx(10, playerid, narkx, narky, narkz) || GetPlayerState(id) == PLAYER_STATE_SPECTATING || GetPlayerState(playerid)==PLAYER_STATE_SPECTATING || GetPlayerVirtualWorld(id) != GetPlayerVirtualWorld(playerid)){
			SendInfoMessage(playerid,"Jus per toli nuo pirkejo (10 m)");
			return 1;
		}
		if(playerDB[id][textas] || playerDB[id][rid][0] != -1 || gPlayerDialog[id] != -1)
			return SendInfoMessage(playerid,"Sis zaidejas jau gavo pasiulyma kazka pirkti, todel jis privalo uzdaryti dialoga.");

		//playerDB[id][textas]=1;
		playerDB[id][rkiekis][0]=kiek;
		playerDB[id][rkaina][0]=kaina;
		playerDB[id][rrusis]=rusis;
		playerDB[id][rid][0]=playerid;
		new msg[256],name[MAX_PLAYER_NAME];
		GetPlayerName(playerid,name,sizeof(name));
		new rusisz[50];
		switch(rusis)
		{
			case 1: rusisz="Amfetamino";
			case 2: rusisz="Seklø";
			case 3: rusisz="Kanapiø";
			case 4: rusisz="LSD";
			case 5: rusisz="Ekstazio";
			// 6 reserved for kred
		}

		format(msg,sizeof(msg),"%s jums siûlo %i paketø %s po %s€. Sutikti galite paspaudæ ~k~~CONVERSATION_YES~, o atmesti paspaudæ ~k~~CONVERSATION_NO~",name,kiek,rusisz,FormatNumber(kaina));
		SendClientMessage(id,BLUE,msg);
		//ShowPlayerDialog(id, 887, DIALOG_STYLE_MSGBOX, "Narkotikai", msg, "Taip", "Ne");
		GetPlayerName(id,name,sizeof(name));
		format(msg,sizeof(msg),"Pasiulete %s %i paketu %s po %s EUR.",name,kiek,rusisz,FormatNumber(kaina));
		SendInfoMessage(playerid,msg);
		Pasiule[id]=GetTickCount();

		return 1;
}
CMD:siulytikred(playerid,params[])
{
		if(playerDB[playerid][kreditai]<1)
		{
			SendInfoMessage(playerid,"Tu neturi kreditu");
			return 1;
		}
		new vardas[128], kiek, kaina;

		if(sscanf(params,"s[24]dd",vardas,kiek,kaina))
		{
			SendInfoMessage(playerid,"Parduoti kreditus: /siulytikred [vardo dalis] [kiek] [vieno_kaina]");
			return 1;
		}
		if(TradingWith[playerid] != -1) return SendInfoMessage(playerid,"Uzdaryk mainus!");
        if(kiek < 0 || kaina < 0 || kaina > 1000000) return 0;


		if(kiek > playerDB[playerid][kreditai])
		{
			SendInfoMessage(playerid,"Tu neturi tiek kreditu!");
			return 1;
		}
		if(kiek  * kaina < 0 || kiek * kaina > 100000000)
			return SendClientMessage(playerid,-1,"KLAIDA!");
		new id = GetPlayeridMid(vardas);

		if (id == INVALID_PLAYER_ID || id == playerid)
		{
			SendInfoMessage(playerid,"Tokio vardo nera");
			return 1;
		}
        if(kaina > GetPlayerMoneyA(id)) return SendInfoMessage(playerid,"Zaidejas neturi tiek pinigu!");
		if(GetPlayerScore(id) < 100) return SendInfoMessage(playerid,"Zaidejas turi per mazai XP(reikia 100)");
		new Float:narkx, Float:narky, Float:narkz;
		GetPlayerPos(id, narkx, narky, narkz);
		if(!IsPlayerInRangeOfPointEx(10, playerid, narkx, narky, narkz) || GetPlayerState(id) == PLAYER_STATE_SPECTATING || GetPlayerState(playerid)==PLAYER_STATE_SPECTATING)
		{
			SendInfoMessage(playerid,"Jus per toli nuo pirkejo (10 m)");
			return 1;
		}
		if(!galikast[playerid])
		{
			SendInfoMessage(playerid,"Negali taip daznai siulyti. Palauk.");
			return 1;
		}
		if(playerDB[id][textas] || playerDB[id][rid][0] != -1 || gPlayerDialog[id] != -1)
			return SendInfoMessage(playerid,"Sis zaidejas jau gavo pasiulyma kazka pirkti, todel jis privalo uzdaryti dialoga.");

		galikast[playerid]=false;
		SetTimerEx("GaliKast",10000,0,"i",playerid);
		
		//playerDB[id][textas]=2;
		playerDB[id][rkiekis][0]=kiek;
		playerDB[id][rkaina][0]=kaina;
		playerDB[id][rid][0]=playerid;
		playerDB[id][rrusis]=6;
		new msg[256],name[MAX_PLAYER_NAME];
		GetPlayerName(playerid,name,sizeof(name));
		Pasiule[id] = GetTickCount();
		format(msg,sizeof(msg),"%s jums siûlo %i kreditø po %s€ uþ vienetà. Sutikti galite paspaudæ ~k~~CONVERSATION_YES~, o atmesti paspaudæ ~k~~CONVERSATION_NO~",name,kiek,FormatNumber(kaina));
		//ShowPlayerDialog(id, 886, DIALOG_STYLE_MSGBOX, "Kreditai", msg, "Taip", "Ne");
		SendClientMessage(id,BLUE,msg);
		GetPlayerName(id,name,sizeof(name));
		format(msg,sizeof(msg),"Siulote %s %i kreditus po %i €",name,kiek,kaina);
		SendInfoMessage(playerid,msg);
		return 1;

}
CMD:zparduoti(playerid,params[])
{
		return SendInfoMessage(playerid,"Naudokite /nparduoti"),1;
}


CMD:s(playerid,params[])
{
	return cmd_skelb(playerid,params);
}

CMD:ita(playerid,params[])
{
    	if(!playerDB[playerid][admin] && playerDB[playerid][specialybe]!=80 && playerDB[playerid][specialybe]!=81 && playerDB[playerid][specialybe] != 83 && playerDB[playerid][specialybe] != 84 && playerDB[playerid][specialybe] != 82){SendInfoMessage(playerid,"Si komanda tik Teisesaugai."); return 1;}
		new vardas[128],itarimas[64],star;
		if(playerDB[playerid][mire] || playerDB[playerid][suristas]) return SendInfoMessage(playerid,"Ilsekis lavone!");
		if(sscanf(params,"s[24]ds[128]",vardas,star,itarimas)){SendInfoMessage(playerid,"Itarti zaideja: /ita [nick] [zvaigzdutes] [itarimas]"); return 1;}
		new id = GetPlayeridMid(vardas);

		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		if (id == playerid){ SendInfoMessage(playerid,"Saves itarti negali"); return 1;}
		if(star < 1) return SendInfoMessage(playerid," Netinkamas zvaigzduciu skaicius!");

		//if ( star > 6 ){ SendClientMessage(playerid, RED, "* Zvaigzduciu skaicius tarp 1 ir 6"); return 1;}
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(100, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(id) == PLAYER_STATE_SPECTATING){SendInfoMessage(playerid,"Zaidejas per toli, kaip tu gali pamatyti ka jis daro?"); return 1;}
		new msg[128],police[MAX_PLAYER_NAME],itar[MAX_PLAYER_NAME];
		GetPlayerName(playerid,police,sizeof(police));
		GetPlayerName(id,itar,sizeof(itar));
		if(PlayerSpectated[playerid] != -1)
		{
			new msgpzu[256];
			format(msgpzu,256,"[PZU] %s: /ita %s %i %s",ReturnName(playerid), vardas, star, itarimas);
			SendClientMessage(PlayerSpectated[playerid], COLOR, msgpzu);
		}
		//MLog(playerid,"/ita","sis", itar,star,itarimas);
		if((GetPlayerWantedLevel(id)+star) < 10 )
		{
			SetPlayerWantedLevel(id,GetPlayerWantedLevel(id)+star);
		}
		else SetPlayerWantedLevel(id,10);
		if(GetPlayerWantedLevel(id) == 10) ProcessAchievement(playerid,14);
		format(msg,sizeof(msg),"[racija] %s: pastebejau, kaip %s %s!",police,itar,itarimas);
		new itarimaz[128];
		format(itarimaz,sizeof(itarimaz)," *** Policininkas %s pastebejo ir itaria jus %s(%istar) *** ",police,itarimas,star);
		SendClientMessage(id,RED,itarimaz);
		MLog(playerid,"Dave star","ssi",itar,itarimas,star);
		SendMessageToTeisesauga(0x7DB34DFF,msg);
		return 1;
}
/*
CMD:blokada(playerid,params[])
{
    	if(!playerDB[playerid][admin] && playerDB[playerid][specialybe]!=80 && playerDB[playerid][specialybe]!=81 && playerDB[playerid][specialybe] != 83 && playerDB[playerid][specialybe] != 84 && playerDB[playerid][specialybe] != 82){SendInfoMessage(playerid,"Si komanda tik Teisesaugai."); return 1;}
		new vardas[128],itarimas[64],star;
		if(playerDB[playerid][mire] || playerDB[playerid][suristas]) return SendInfoMessage(playerid,"Ilsekis lavone!");
		new const blokados[] = {1427, 1425, 1282, 1424, 1422, 1423, 1459, 978, 979, 981, 3091, 1238, 19425, 19467};
		ShowModelSelectionMenuEx(playerid, blokados, sizeof(blokados), "Blokados", GUI_BLOKADOS, 0.0, 0.0, 180.0);
		return 1;
}*/

CMD:zvejoti(playerid,params[])
{
	#pragma unused params
	if(!IsPlayerAttachedObjectSlotUsed(playerid,MESKERE_SLOT)) return SendInfoMessage(playerid,"Neturi meskeres!");
	if(playerDB[playerid][zuvis] >= 20) return SendInfoMessage(playerid,"Turi per daug zuvies!");
	if(!playerDB[playerid][masalas]) return SendInfoMessage(playerid,"Neturi masalo!");
	if(IsPlayerInAnyVehicle(playerid)) return SendInfoMessage(playerid,"Islipk is masinos!");
 	new vehicleid = GetClosestVehicleid(playerid, 9.0);
	if(vehicleid == INVALID_VEHICLE_ID)
		vehicleid = GetPlayerSurfingVehicleID(playerid);
 	if(vehicleid == INVALID_VEHICLE_ID || !IsABoat(GetVehicleModel(vehicleid))) return SendInfoMessage(playerid,"Zvejoti gali tik is valties!");
	new animlib[32];
	new animname[32];
	GetAnimationName(GetPlayerAnimationIndex(playerid),animlib,32,animname,32);
	if(strcmp(animlib, "SWIM", true) == 0)
	{
		return SendInfoMessage(playerid,"Zvejoti gali tik is valties!");
	}
	new Float:pos[3];
	GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
	MapAndreas_FindZ_For2DCoord(pos[0],pos[1],pos[2]);
	if(pos[2] > 2.0)
	{
		return SendInfoMessage(playerid,"Valtis turi buti vandenyje!");
	}
	SendInfoMessage(playerid,"Pradejai zvejot!~n~Traukti zuvi gali paspaudes MOUSE1");
	
 	playerDB[playerid][zvejoja]=true;
 	ApplyAnimation(playerid,"SWORD","sword_idle",1.0,1,0,0,0,0,1);
 	return 1;
}

CMD:mechanikas(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]!=6 && !playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda tik mechanikams."); return 1;}
	//new veh=GetPlayerVehicleID(playerid);
	//if(GetVehicleModel(veh) == 504 || GetVehicleModel(veh) == 502 || GetVehicleModel(veh) == 494  || GetVehicleModel(veh) == 503 || (IsEventCar(veh) && !ArNuosava(veh))) return SendInfoMessage(playerid,"Sia komanda cia naudotis negalite!");
	LogA(playerid,"Mechanikas");
	if(playerDB[playerid][ant] || playerDB[playerid][suristas]) return SendInfoMessage(playerid," Tu surakintas/suristas!");
	ShowPlayerDialog(playerid,007,DIALOG_STYLE_LIST,"Mechaniku meniu","Sutaisyti varikli("#COST_TAISYMAS"€)\nPripilti degalu("#COST_DEGALAI"€)\nRestauruoti masina("#COST_RESTAURAVIMAS"€)\nIdeti signalizacija(2000€)\nUzdeti spalva(100€)\nIdeti Nitro(1000€)\nIdeti hydraulika(1500€)\nRatai(1000€)\nPakrauti Akumuliatoriu("#COST_AKUMAS"€)\nNuimti paintjob(500€)\nNuimti tune(5000€)\nSutvirtinti këbulà(500€)","Rinktis","Iseiti");
	return 1;
}
CMD:sedes(playerid,params[])
{
		if(playerDB[playerid][specialybe]!=15 && !playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda tik advokatams."); return 1;}
        new vardas[128];
		if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Patikrinti kiek zaidejas sedes kalejime: /sedes [vardo_dalis]"); return 1;}

		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		if(!playerDB[id][ikalintas]) return SendInfoMessage(playerid,"Zaidejas nesedi kalejime.");
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(100, playerid, Coo[0],Coo[1],Coo[2])){SendInfoMessage(playerid,"Zaidejas per toli, kaip tu gali ji isteisinti?"); return 1;}
		new sedi = playerDB[id][kalejimo_laikas];
		new kaina = sedi/2;
		if(PlaceOwnedBy[5] == -1)
		{
			kaina = (kaina * 3) / 2;
		}
		new msg[128];
		format(msg,128,"Nusikaltelis sedes %isec. Isteisinimo Kaina - %i€",sedi,kaina);
		SendClientMessage(playerid,RED,msg);
		SendClientMessage(playerid,COLOR,"* Noredami ji isteisinti naudokite /isteisinti");
		return 1;

}
CMD:isteisinti(playerid,params[])
{
    	if(playerDB[playerid][specialybe]!=15 && !playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda tik advokatams."); return 1;}
        new vardas[128];
		if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Isteisinti zaideja: /isteisinti [vardo_dalis]"); return 1;}

		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		if (id == playerid){ SendInfoMessage(playerid,"Saves isteisinti negali"); return 1;}
		if(!playerDB[id][ikalintas] ) return SendInfoMessage(playerid,"Zaidejas nesedi kalejime.");
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(100, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(id) == PLAYER_STATE_SPECTATING){SendInfoMessage(playerid,"Zaidejas per toli, kaip tu gali ji isteisinti?"); return 1;}

		new sedi = playerDB[id][kalejimo_laikas];
		new kaina = sedi/2;
		if(PlaceOwnedBy[5] == -1)
		{
			kaina = (kaina * 3) / 2;
		}
		if(GetPlayerMoneyA(playerid) < kaina)
		{
			new msg[128];
			format(msg,128,"~r~Jums truksta pinigu. Kaina - %iEUR",kaina);
			SendInfoMessage(playerid,msg);
			return 1;
		}
		//UnjailPlayer(id,3180.9961,-966.1835,293.3473,359.00,0);
		playerDB[id][kalejimo_laikas]=1;
		GivePlayerMoneyA(playerid,-kaina);
		SendInfoMessage(playerid,"~g~Sekmingai ji isteisinai");
		ProcessAchievement(playerid, 81);
		ProcessAchievement(id,52);
		SendInfoMessage(id,"~g~Jus isteisino!");
		return 1;


}

CMD:ist(playerid,params[])
{
		if(playerDB[playerid][specialybe]!=80 && playerDB[playerid][specialybe]!=81 && playerDB[playerid][specialybe]!=83 && playerDB[playerid][specialybe]!=84 && !playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda tik teisesaugai"); return 1;}
        new vardas[128],priez[128];
		if(sscanf(params,"s[24]s[128]",vardas,priez)){SendInfoMessage(playerid,"Isteisinti zaideja: /ist [vardo_dalis] [priezastis]"); return 1;}

		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		if (id == playerid){ SendInfoMessage(playerid,"Saves isteisinti negali"); return 1;}
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(100, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(id) == PLAYER_STATE_SPECTATING){SendInfoMessage(playerid,"Zaidejas per toli, kaip tu gali ji isteisinti?"); return 1;}
		new msg[128],police[MAX_PLAYER_NAME];
		GetPlayerName(playerid,police,sizeof(police));
		GetPlayerName(id,vardas,sizeof(vardas));
		SetPlayerWantedLevel(id,0);
		format(msg,sizeof(msg),"[racija] %s: Isteisinau %s(Priezastis:%s).",police,vardas,priez);
		MLog(playerid,"Isteisino","ss",vardas,priez);
		SendMessageToTeisesauga(0x7DB34DFF,msg);
		
		return 1;

}

CMD:kong(playerid,params[])
{
		if(playerDB[playerid][specialybe]!=80 && playerDB[playerid][specialybe]!=84 && playerDB[playerid][specialybe]!=81 && playerDB[playerid][specialybe]!=83){SendInfoMessage(playerid,"Si komanda tik policininkams"); return 1;}
        new vardas[128];
		if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Atimti ginkla: /kong [vardo_dalis]"); return 1;}

		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(5, playerid, Coo[0],Coo[1],Coo[2])){SendInfoMessage(playerid,"Zaidejas per toli, kaip tu ruosiesi atimti is jo ginkla ? :O"); return 1;}
		new msg[128],police[MAX_PLAYER_NAME];
		GetPlayerName(playerid,police,sizeof(police));
		GetPlayerName(id,vardas,sizeof(vardas));
		//if(GetPlayerState(id)!=PLAYER_STATE_DRIVER)
		//	ResetPlayerWeapons(id);
		ResetGunData(id);
		//DeletePlayerWeapon(id, GetPlayerWeapon(id));
		format(msg,sizeof(msg),"[racija] %s: Atemiau %s ginklus.",police,vardas);
		new messas[128];
		format(messas,128,"* Pareigûnas {B0E0E6}%s{FFFFFF} ið jûsø atëmë ginklus.",ReturnName(playerid));
		SendClientMessage(id, -1, messas);
		SendMessageToTeisesauga(0x7DB34DFF,msg);
		return 1;
}

CMD:kon(playerid,params[])
{
		if(playerDB[playerid][specialybe]!=80 && playerDB[playerid][specialybe]!=84 && playerDB[playerid][specialybe]!=81 && playerDB[playerid][specialybe]!=83){SendInfoMessage(playerid,"Si komanda tik policininkams"); return 1;}
        new vardas[128];
		if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Atimti narkotikus: /kon [vardo_dalis]"); return 1;}

		new year,month,day;
		getdate(year, month, day);
		if(month == 12 && day == 25)
			return SendInfoMessage(playerid,"Siandien sios komandos naudoti negali del Kaledinio evento.");
		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		if(SafeArea(id) == 24)
		{
			return SendInfoMessage(playerid,"Nebuk grincas!");
		}
		if(playerDB[id][specialybe]==32 && (GetPlayerSkin(id) == 225 || GetPlayerSkin(id)==30)) 
		{
			return SendInfoMessage(playerid,"Is dylerio negali atimti narkotiku!");
		}
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(5, playerid, Coo[0],Coo[1],Coo[2])){SendInfoMessage(playerid,"Zaidejas per toli, kaip tu ruosiesi atimti is jo narkotikus ? :O"); return 1;}
		new msg[128],police[MAX_PLAYER_NAME];
		GetPlayerName(playerid,police,sizeof(police));
		GetPlayerName(id,vardas,sizeof(vardas));
		playerDB[id][amfetaminas]=0;
		playerDB[id][lsd]=0;
		playerDB[id][ratai]=0;
		format(msg,sizeof(msg),"[racija] %s: Atemiau narkotikus %s.",police,vardas);
		new messas[128];
		format(messas,128,"* Pareigûnas {B0E0E6}%s{FFFFFF} ið jûsø atëmë narkotikus.",ReturnName(playerid));
		SendClientMessage(id, -1, messas);
		SendMessageToTeisesauga(0x7DB34DFF,msg);
		return 1;
}

CMD:sekti(playerid,params[])
{
		
		if(playerDB[playerid][specialybe] != 71 && playerDB[playerid][specialybe]!=80 && playerDB[playerid][specialybe] != 82 && playerDB[playerid][specialybe] != 84 && playerDB[playerid][specialybe]!=81 &&playerDB[playerid][specialybe]!=83 && !playerDB[playerid][admin])
		{
			SendInfoMessage(playerid,"Si komanda tik policininkams ir baikeriams"); 
			return 1;
		}
        
		new vardas[128];
		
		if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Sekti zaideja : /sekti [vardo_dalis]"); return 1;}
		if(PlayerSpectated[playerid] != -1)
		{
			new msgpzu[256];
			format(msgpzu,256,"[PZU] %s: /sekti %s",ReturnName(playerid), vardas);
			SendClientMessage(PlayerSpectated[playerid], COLOR, msgpzu);
		}
		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		if (id == playerid){ SendInfoMessage(playerid,"Saves sekti negali."); return 1;}
		PlayCrimeReportForPlayer(playerid,id,22);
		return 1;
}

CMD:ant(playerid,params[])
{
    	if(playerDB[playerid][specialybe]!=80 && playerDB[playerid][specialybe] != 82 && playerDB[playerid][specialybe]!=81 && playerDB[playerid][specialybe]!=83 && playerDB[playerid][specialybe]!=84 && !playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda tik policininkams"); return 1;}
		
		if(playerDB[playerid][mire] || playerDB[playerid][suristas]) return SendInfoMessage(playerid,"Ilsekis lavone!");
	    new vardas[128];
		if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Uzdeti/nuimti zaidejui antrankius: /ant [vardo_dalis]"); return 1;}
		if(PlayerSpectated[playerid] != -1)
		{
			new msgpzu[256];
			format(msgpzu,256,"[PZU] %s: /ant %s",ReturnName(playerid), vardas);
			SendClientMessage(PlayerSpectated[playerid], COLOR, msgpzu);
		}
		new id = GetPlayeridMid(vardas);
		if(playerDB[playerid][suristas]) return SendInfoMessage(playerid,"Tu suristas!");
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		new nameas[24];
		format(nameas,24,"%s",ReturnName(id));
		if(strcmp(vardas,nameas,false) == 0 || strcmp(vardas,nameas[2],false) == 0)
			return SendInfoMessage(playerid,"Uzdeti/nuimti zaidejui antrankius: /ant [vardo_dalis]");
		if (id == playerid){ SendInfoMessage(playerid,"Saves susirakinti/atsirakinti negali"); return 1;}
		if(playerDB[id][mire]) return SendInfoMessage(playerid,"Zaidejas jau mires!");
		if(playerDB[id][suristas]) return SendInfoMessage(playerid,"Zaidejas suristas!");
		if(IsPlayerAfk(id)) return SendInfoMessage(playerid,"Zaidejas AFK!");
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(CheckZone(playerid) || !IsPlayerInRangeOfPointEx(4, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(id)==PLAYER_STATE_SPECTATING){SendInfoMessage(playerid,"Zaidejas per toli, prieikite arciau."); return 1;}
		if(GetPlayerWantedLevel(id) == 10 && !playerDB[id][ant] && !SafeArea(id))
			return SendInfoMessage(playerid,"~r~Sunkaus nusikaltelio negali surakinti! Turi ji nusauti!");
		if(playerDB[id][specialybe]==71 && CalculateBaimesFaktorius(id) >= 200)
			return SendInfoMessage(playerid,"~r~Baikerio surakinti negali, nes jo bijai! Numesk ji nuo motociklo!");


		new msg[128],police[MAX_PLAYER_NAME];
		GetPlayerName(playerid,police,sizeof(police));
		GetPlayerName(id,vardas,sizeof(vardas));
		//if(playerDB[playerid][ant]) return SendInfoMessage(playerid,"Jus esate surakintas!");
		if(!playerDB[id][ant])
		{
			playerDB[id][ant]=true;
			TogglePlayerControllable(id,false);

			format(msg,sizeof(msg),"~r~Surakinote %s.",vardas);
			SendInfoMessage(playerid,msg);
			format(msg,sizeof(msg),"Surakinote %s.",vardas);
			SendClientMessage(playerid,RED,msg);

			format(msg,sizeof(msg),"~r~Jus surakino %s.",police);
			SendInfoMessage(id,msg);
			format(msg,sizeof(msg),"Jus surakino %s.",police);
			SendClientMessage(id,RED,msg);
			SetPlayerAttachedObject(id, CUFF_SLOT, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
			if(GetPlayerScore(id) < 11000) SendClientMessage(id,-1,"Jei atsijungsite busite uzbanintas.");
			if(!IsPlayerInAnyVehicle(id))
			{
				/*
				ApplyAnimation(id,"SWORD","sword_block",50.0,0,0,0,1,0,1);
				ApplyAnimation(id,"SWORD","sword_block",50.0,0,0,0,1,0,1);
				*/
				SetPlayerSpecialAction(id, 24); // SPECIAL_ACTION_CUFFED
			}
		}else{
			playerDB[id][ant]=false;
			TogglePlayerControllable(id,true);

			format(msg,sizeof(msg),"~b~Paleidote %s.",vardas);
			SendInfoMessage(playerid,msg);
			format(msg,sizeof(msg),"Paleidote %s.",vardas);
			SendClientMessage(playerid,BLUE,msg);
			format(msg,sizeof(msg),"~b~Jus paleido %s.",police);
			SendInfoMessage(id,msg);
			format(msg,sizeof(msg),"Jus paleido %s.",police);
			SendClientMessage(id,BLUE,msg);
			RemovePlayerAttachedObject(id,CUFF_SLOT);
			SetPlayerSpecialAction(id, SPECIAL_ACTION_NONE);
				//SetPlayerSpecialAction(playerid, 24); // SPECIAL_ACTION_CUFFED
			//ApplyAnimation(id, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 0, 0);

		}
		return 1;


}

CMD:suristi(playerid,params[])
{
    	if(playerDB[playerid][specialybe]!=71 && !playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda tik baikeriams."); return 1;}
        new vardas[128];
		if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Suristi ikaita: /suristi [vardo_dalis]"); return 1;}

		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		if (id == playerid){ SendInfoMessage(playerid,"Saves suristi/atristi negali"); return 1;}
		if(gPlayerDialog[playerid]== 8252) // baikeriu gunai
		{
			AC_Ban(playerid, "Cheat");
			return 1;
		}
		if(strcmp(vardas,ReturnName(id),false) == 0)
			return SendInfoMessage(playerid,"Naudojimas: /suristi [vardo dalis]");
		if(PlayerSpectated[playerid] != -1)
		{
			new msgpzu[256];
			format(msgpzu,256,"[PZU] %s: /suristi %s",ReturnName(playerid), vardas);
			SendClientMessage(PlayerSpectated[playerid], COLOR, msgpzu);
		}
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(2, playerid, Coo[0],Coo[1],Coo[2])  || GetPlayerState(id)==PLAYER_STATE_SPECTATING){SendInfoMessage(playerid,"Zaidejas per toli, prieikite arciau."); return 1;}
		if(playerDB[playerid][ant]) return SendInfoMessage(playerid,"Pirma nusiimk antrankius.");
		new msg[128],police[MAX_PLAYER_NAME];
		GetPlayerName(playerid,police,sizeof(police));
		GetPlayerName(id,vardas,sizeof(vardas));
		if(GetPlayerState(id)==PLAYER_STATE_DRIVER) return SendInfoMessage(playerid,"Vairuotojo suristi negali.");
		if(playerDB[id][ikalintas]) return SendInfoMessage(playerid,"Zaidejas sedi kalejime!");
		if(IsPlayerAfk(id)) return SendInfoMessage(playerid,"Zaidejas AFK!");
		if(!playerDB[id][ant])
		{
			if(!playerDB[id][suristas])
			{
				if(!playerDB[playerid][virve]) return SendInfoMessage(playerid,"Neturi virves.");
				playerDB[id][suristas]=true;
				TogglePlayerControllable(id,false);
				playerDB[playerid][virve]=false;
				format(msg,sizeof(msg),"~r~Surisote %s.",vardas);
				SendInfoMessage(playerid,msg);
				format(msg,sizeof(msg),"~r~Jus suriso %s.",police);
				SendInfoMessage(id,msg);
				KillTimer(Suristas[id]);
				Suristas[id]=-1;
				Suristas[id] = SetTimerEx("Atristi",600000,0,"i",id);
				SendClientMessage(id,ORANGE," * Kvieskites pagalba! Jei nepavyks, automatiskai atsirisite per 10 minuciu! (Atsijungti draudziama)");
				if(!IsPlayerInAnyVehicle(id))
				{
					ApplyAnimation(id, "ped", "cower", 3.0, 1, 0, 0, 0, 0, 1);
					ApplyAnimation(id, "ped", "cower", 3.0, 1, 0, 0, 0, 0, 1);
				}
			}
			else
			{
				KillTimer(Suristas[id]);
				Suristas[id]=-1;
				playerDB[id][suristas]=false;
				TogglePlayerControllable(id,true);
				playerDB[playerid][virve]=true;
				format(msg,sizeof(msg),"~b~Atrisote %s.",vardas);
				SendInfoMessage(playerid,msg);

				format(msg,sizeof(msg),"~b~Jus atriso %s.",police);
				SendInfoMessage(id,msg);
				if(!IsPlayerInAnyVehicle(playerid)) ClearAnimations(id, 1);
			}
		}else{ SendClientMessage(playerid,RED," * Zmogus surakintas antrankiais. Koks tolkas ji surisinet? :D"); return 1; }

		return 1;

}


CMD:isodinti(playerid,params[])
{
    if(playerDB[playerid][specialybe]!=80 && playerDB[playerid][specialybe]!=81 && playerDB[playerid][specialybe] != 82 && playerDB[playerid][specialybe]!=83 && playerDB[playerid][specialybe] != 84 && playerDB[playerid][specialybe] != 71 && !playerDB[playerid][admin])
	{
		SendInfoMessage(playerid,"Si komanda tik teisesaugai ir baikeriams."); return 1;
	}
	new vardas[128];
	if(sscanf(params,"s[24]",vardas)) return SendInfoMessage(playerid,"Naudojimas: /isodinti [vardo dalis]");
	if(PlayerSpectated[playerid] != -1)
	{
		new msgpzu[256];
		format(msgpzu,256,"[PZU] %s: /isodinti %s",ReturnName(playerid), vardas);
		SendClientMessage(PlayerSpectated[playerid], COLOR, msgpzu);
	}
	new id = GetPlayeridMid(vardas);
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendInfoMessage(playerid,"Jus privalote vairuoti automobili!");
	new vehicleid = GetPlayerVehicleID(playerid);
	if(id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	if(id == playerid){ SendInfoMessage(playerid,"Saves isodinti negali"); return 1;}
	if(strcmp(vardas,ReturnName(id),false) == 0)
			return SendInfoMessage(playerid,"Naudojimas: /isodinti [vardo dalis]");
	if(!playerDB[id][ant] && !playerDB[id][suristas]) return SendInfoMessage(playerid,"Galite isodinti tik surakinta ar surista zaideja!");
	new Float:Coo[3];
	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	if(!IsPlayerInRangeOfPointEx(5, id, Coo[0],Coo[1],Coo[2])){SendInfoMessage(playerid,"Zaidejas per toli, privaziuokite arciau."); return 1;}
	if(IsPlayerAfk(id)) return SendInfoMessage(playerid,"Zaidejas AFK!");
	new model = GetVehicleModel(GetPlayerVehicleID(playerid));
	
	/*if(model != 463 && (!IsPoliceCar(vehicleid) || model == BMX || model == MTBIKE || model == BIKE || model == 520 || model == 425))
		return SendInfoMessage(playerid,"I sia transporto priemone isodinti negali!");*/
	new maxseats = GetMaxSeats(model);
	if(maxseats < 2)
		return SendInfoMessage(playerid,"I sia transporto priemone isodinti negali!");
	new seat = 1;
	if(maxseats > 2) // 4-viete masina
	{
		new occupied[2];
		foreach(Player,i)
		{
		    if(GetPlayerVehicleID(i) == vehicleid)
		    {
		        if(GetPlayerVehicleSeat(i) == 2)
		        {
		            occupied[0] = 1;
		        }
		        if(GetPlayerVehicleSeat(i) == 3)
		        {
		            occupied[1] = 1;
		        }
		    }
		}
		if(occupied[0] == 0)
			seat = 2;
		else if(occupied[1] == 0)
			seat = 3;
		else
			return SendInfoMessage(playerid,"Nera laisvos vietos. Galima isodinti tik i galine vieta.");
	}
	else // 2-viete masina
	{
		foreach(Player,i)
		{
		    if(GetPlayerVehicleID(i) == vehicleid)
		    {
		        if(GetPlayerVehicleSeat(i) == seat)
		        {
		            return SendInfoMessage(playerid,"Nera laisvos vietos. Galima isodinti tik i galine vieta.");
		        }
		    }
		}
	}
	PutPlayerInVehicle(id,vehicleid,seat);
	//LastVehicle[id]=veh;
	playerDB[id][pCar]=GetPlayerVehicleID(id);
	//playerDB[id][pCar]=vehicleid;
	if(playerDB[playerid][specialybe]==71 && playerDB[id][ant])
	{
		SendClientMessage(playerid,COLOR,"Zemelapyje parodyta vieta, kur galite nupjauti zmogui antrankius!");
		SetPlayerCheckpoint(playerid,2351.3904,-651.9200,127.6273,5.0);
	}
	if(playerDB[playerid][specialybe]==71 && id == playerDB[playerid][baikeruzd])
	{
		SendClientMessage(playerid,COLOR,"Zemelapyje parodyta vieta, kur turite nuvezti savo auka!");
		SetPlayerCheckpoint(playerid,2351.3904,-651.9200,127.6273,5.0);
	}
	SendInfoMessage(id," Jus buvote priverstinai isodintas!");
	SendInfoMessage(playerid,"Sekmingai isodinote!");
	return 1;
}

// pd komandos
CMD:atristi(playerid,params[])
{
    	new vardas[128];
		if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Atristi ikaita: /atristi [vardo_dalis]"); return 1;}
		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		if (id == playerid){ SendInfoMessage(playerid,"Saves atristi negali"); return 1;}
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(2, playerid, Coo[0],Coo[1],Coo[2])){SendInfoMessage(playerid,"Zaidejas per toli, prieikite arciau."); return 1;}
		if(playerDB[playerid][suristas] || playerDB[playerid][ant]) return SendInfoMessage(playerid,"Pirma atsirisk pats :D");
		new msg[128],police[MAX_PLAYER_NAME];
		GetPlayerName(playerid,police,sizeof(police));
		GetPlayerName(id,vardas,sizeof(vardas));
		if(GetPlayerState(id)==PLAYER_STATE_DRIVER) return SendInfoMessage(playerid,"Vairuotojo atristi negali.");
		if(!playerDB[id][ant])
		{
			if(!playerDB[id][suristas])
			{
				SendInfoMessage(playerid,"Zaidejas nesuristas.");
				return 1;
			}
			else
			{
				playerDB[id][suristas]=false;
				TogglePlayerControllable(id,true);
				playerDB[playerid][virve]=true;
				format(msg,sizeof(msg),"~b~Atrisote %s.",vardas);
				SendInfoMessage(playerid,msg);

				format(msg,sizeof(msg),"~b~Jus atriso %s.",police);
				SendInfoMessage(id,msg);
				KillTimer(Suristas[id]);
				Suristas[id]=-1;
				if(!IsPlayerInAnyVehicle(id)) ClearAnimations(id);
			}
		}else{ SendInfoMessage(playerid,"Zmogus surakintas antrankiais."); return 1; }

		return 1;
}


CMD:tei(playerid,params[])
{
	if(playerDB[playerid][specialybe]!=80 && playerDB[playerid][specialybe]!=84){SendInfoMessage(playerid,"Si komanda tik policininkams"); return 1;}
    new vardas[128];
	if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Atimti vairavimo teises: /tei [vardo_dalis]"); return 1;}
	new id = GetPlayeridMid(vardas);
	if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	new Float:Coo[3];
	GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
	if(!IsPlayerInRangeOfPointEx(3, playerid, Coo[0],Coo[1],Coo[2])){SendInfoMessage(playerid,"Zaidejas per toli, prieikite arciau."); return 1;}

	new msg[128],police[MAX_PLAYER_NAME];
	GetPlayerName(playerid,police,sizeof(police));
	GetPlayerName(id,vardas,sizeof(vardas));

	playerDB[id][teor]=false;

	if(IsPlayerInAnyVehicle(id))
	{
		new model = GetVehicleModel(GetPlayerVehicleID(id));
		if(model == 509 || model == 481 || model == 510 || model == 462 || model == 448 || model == 574 || model == 423 || model == 588) return SendInfoMessage(playerid,"Siam transportui nereik pazymejimo.");
		if(model == 448 || model == 581 || model == 522 || model == 461 || model == 521 || model == 523 || model == 463 || model == 586 || model == 468)
		{
			if(!playerDB[id][teisesm]) { SendInfoMessage(playerid,"Zaidejas neturi motociklu teisiu!."); return 1;}
			format(msg,128," * %s atema %s motociklu teises!",ReturnName(playerid),ReturnName(id));
			ProxDetector(30.0, playerid, msg, COLOR_CHAT1,COLOR_CHAT2,COLOR_CHAT3,COLOR_CHAT4,COLOR_CHAT5);
			
			playerDB[id][teisesm]=false;
			playerDB[id][teor]=false;
			format(msg,sizeof(msg),"Atemete %s motociklu teises.",vardas);
			SendInfoMessage(playerid,msg);

			format(msg,sizeof(msg),"%s ateme jusu motociklu teises.",police);
			SendInfoMessage(playerid,msg);
			RemovePlayerFromVehicle(id);
			return 1;

		}
		else
		{
			if(!playerDB[id][teises]) { SendInfoMessage(playerid,"Zaidejas neturi teisiu!."); return 1;}
			playerDB[id][teises]=false;
			playerDB[id][teor]=false;
			format(msg,128," * %s atema %s vairavimo teises!",ReturnName(playerid),ReturnName(id));
			ProxDetector(30.0, playerid, msg, COLOR_CHAT1,COLOR_CHAT2,COLOR_CHAT3,COLOR_CHAT4,COLOR_CHAT5);
			format(msg,sizeof(msg),"Atemete %s vairavimo teises.",vardas);
			SendInfoMessage(playerid,msg);

			format(msg,sizeof(msg),"%s ateme jusu vairavimo teises.",police);
			SendInfoMessage(id,msg);
			RemovePlayerFromVehicle(id);
			return 1;
		}
	}
	GetVehiclePos(playerDB[id][masina],Coo[0],Coo[1],Coo[2]);
	if(IsPlayerInRangeOfPointEx(10,id,Coo[0],Coo[1],Coo[2]))
	{
		new model = GetVehicleModel(playerDB[id][masina]);
		if(model == 509 || model == 481 || model == 510 || model == 462 || model == 448 || model == 574 || model == 423 || model == 588) return SendInfoMessage(playerid,"Siam transportui nereik pazymejimo.");
		if(model == 448 || model == 581 || model == 522 || model == 461 || model == 521 || model == 523 || model == 463 || model == 586 || model == 468)
		{
			if(!playerDB[id][teisesm]) { SendInfoMessage(playerid,"Zaidejas neturi motociklu teisiu!."); return 1;}
			playerDB[id][teisesm]=false;
			format(msg,128," * %s atema %s motociklu teises!",ReturnName(playerid),ReturnName(id));
			ProxDetector(30.0, playerid, msg, COLOR_CHAT1,COLOR_CHAT2,COLOR_CHAT3,COLOR_CHAT4,COLOR_CHAT5);
			format(msg,sizeof(msg),"Atemete %s motociklu teises.",vardas);
			SendInfoMessage(playerid,msg);

			format(msg,sizeof(msg),"%s ateme jusu motociklu teises.",police);
			SendInfoMessage(id,msg);
			return 1;

		}
		else
		{
			if(!playerDB[id][teises]) { SendInfoMessage(playerid,"Zaidejas neturi teisiu!."); return 1;}
			playerDB[id][teises]=false;
			format(msg,128," * %s atema %s vairavimo teises!",ReturnName(playerid),ReturnName(id));
			ProxDetector(30.0, playerid, msg, COLOR_CHAT1,COLOR_CHAT2,COLOR_CHAT3,COLOR_CHAT4,COLOR_CHAT5);
			format(msg,sizeof(msg),"Atemete %s vairavimo teises.",vardas);
			SendInfoMessage(playerid,msg);

			format(msg,sizeof(msg),"%s ateme jusu vairavimo teises.",police);
			SendInfoMessage(playerid,msg);
			return 1;
		}

	}
	SendInfoMessage(playerid,"Zaidejas per toli nuo masinos!");
	return 1;
}

CMD:paz(playerid,params[])
{
    	if(playerDB[playerid][specialybe]!=80 && playerDB[playerid][specialybe]!= 84){SendInfoMessage(playerid,"Si komanda tik policininkams"); return 1;}
        new vardas[128];
		if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Patikrinti, zaidejo varuotojo pazym.: /paz [vardo_dalis]"); return 1;}

		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		if (id == playerid){ SendInfoMessage(playerid,"Save gali pasitikrinti ir paprasciau!"); return 1;}
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(30, playerid, Coo[0],Coo[1],Coo[2])){SendInfoMessage(playerid,"Zaidejas per toli!"); return 1;}
		if(IsPlayerInAnyVehicle(id))
		{
			new model = GetVehicleModel(GetPlayerVehicleID(id));
			if(model == 509 || model == 481 || model == 510 || model == 462 || model == 448 || model == 574 || model == 423 || model == 588) return SendInfoMessage(playerid,"Siam transportui nereik pazymejimo.");
			if(model == 448 || model == 581 || model == 522 || model == 461 || model == 521 || model == 523 || model == 463 || model == 586 || model == 468)
			{
				if(playerDB[id][teisesm])
				{
					SendInfoMessage(playerid,"Zaidejo motociklu pazymejimas galioja.");
					SendInfoMessage(id,"Policija: Jusu motociklu pazymejimas galioja! Atsiprasome uz sutrukdyma.");
					return 1;
				}
				SendInfoMessage(playerid,"Zaidejo motociklu pazymejimas negalioja! Turite teise ji suimti!");
				SendInfoMessage(id,"Policija: Vairuojate be motociklu pazymejimo.. Jus suimamas!");
				return 1;

			}
			else
			{

				if(playerDB[id][teises]) { SendInfoMessage(playerid,"Zaidejo pazymejimas galioja."); SendInfoMessage(id,"Policija: Jusu pazymejimas galioja! Atsiprasome uz sutrukdyma.");	return 1;}

				SendInfoMessage(playerid,"Zaidejo pazymejimas negalioja! Turite teise ji suimti!");
				SendInfoMessage(id,"Policija: Vairuojate be vairuotojo pazymejimo.. Jus suimamas!");
				return 1;

			}
		}
		GetVehiclePos(playerDB[id][masina],Coo[0],Coo[1],Coo[2]);
		if(IsPlayerInRangeOfPointEx(10,id,Coo[0],Coo[1],Coo[2]))
		{
			new model = GetVehicleModel(playerDB[id][masina]);
			if(model == 509 || model == 481 || model == 510 || model == 462 || model == 448 || model == 574 || model == 423 || model == 588) return SendInfoMessage(playerid,"Siam transportui nereik pazymejimo.");
			if(model == 448 || model == 581 || model == 522 || model == 461 || model == 521 || model == 523 || model == 463 || model == 586 || model == 468)
			{
				if(playerDB[id][teisesm])
				{
					SendInfoMessage(playerid,"Zaidejo motociklu pazymejimas galioja.");
					SendInfoMessage(id,"Policija: Jusu motociklu pazymejimas galioja! Atsiprasome uz sutrukdyma.");
					return 1;
				}
				SendInfoMessage(playerid,"Zaidejo motociklu pazymejimas negalioja! Turite teise ji suimti!");
				SendInfoMessage(id,"Policija: Vairuojate be motociklu pazymejimo.. Jus suimamas!");
				return 1;

			}
			else
			{

				if(playerDB[id][teises]) { SendInfoMessage(playerid,"Zaidejo pazymejimas galioja."); SendInfoMessage(id,"Policija: Jusu pazymejimas galioja! Atsiprasome uz sutrukdyma.");	return 1;}

				SendInfoMessage(playerid,"Zaidejo pazymejimas negalioja! Turite teise ji suimti!");
				SendInfoMessage(id,"Policija: Vairuojate be vairuotojo pazymejimo.. Jus suimamas!");
				return 1;

			}
		}
		SendInfoMessage(playerid,"Zaidejas nesedi masinoje!!");
		return 1;


}

CMD:tikrinti(playerid,params[])
{
		if(playerDB[playerid][specialybe]!=81 && playerDB[playerid][specialybe]!=83 && playerDB[playerid][specialybe] != 84){SendInfoMessage(playerid,"Si komanda tik Teisesaugai(ARAS,Kobra 11 ir Armijai)"); return 1;}
		new vardas[128];
		if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Patikrinti, zaideja del kontrabandos ar vogtos masinos -  /tikrinti [vardas]"); return 1;}
		new msg[128];
		new police[24];
		GetPlayerName(playerid, police, 24);
		new itar[24];
		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		new Float:cord[4];
		GetPlayerPos(id,cord[0],cord[1],cord[2]);
		if (id == playerid){ SendInfoMessage(playerid,"Save gali pasitikrinti ir paprasciau!"); return 1;}
		GetPlayerName(id, itar, 24);
		if(!IsPlayerInRangeOfPointEx(10,playerid,cord[0],cord[1],cord[2]) || GetPlayerState(id) == PLAYER_STATE_SPECTATING) return SendInfoMessage(playerid,"Zaidejas yra per toli. ");
		if(!playerDB[id][ant]) return SendInfoMessage(playerid,"Zaidejas nesurakintas!");
		if(IsPlayerInAnyVehicle(id))
		{
			new vehicleid = GetPlayerVehicleID(id);
			if(GetPlayerWantedLevel(id) > 4) return SendInfoMessage(playerid,"Zaidejas jau gaudomas!!");
			if(krovinys[vehicleid] > 0 && (vak[vehicleid] || vmp[vehicleid] || vdgl[vehicleid] || vawp[vehicleid]))
			{
				format(msg,sizeof(msg),"[racija] %s: pastebëjau, kaip %s veþa nelegalius ginklus!",police,itar);
				SendMessageToTeisesauga(0x7DB34DFF,msg);
				SendInfoMessage(playerid,"Zaidejas veza nelegalius ginklus!!!!");
				SendInfoMessage(id,"Policija: Vezate nelegalius ginklus! Jus suimamas.");
				vehicleDB[vehicleid][pakrauta]=0;
				krovinys[vehicleid]=0;
				vmp[vehicleid]=0;
				vak[vehicleid]=0;
				vdgl[vehicleid]=0;
				vawp[vehicleid]=0;
				if( GetPlayerWantedLevel(id)+1 < 10) SetPlayerWantedLevel(id,GetPlayerWantedLevel(id)+1);
				else SetPlayerWantedLevel(id,10);
				if(!playerDB[id][ant])
				{
					playerDB[id][ant]=true;
					TogglePlayerControllable(id,false);

					SendInfoMessage(playerid,"Surakinote kontrabandininka");
					SendInfoMessage(id,"Jus surakino.");
				}
				return 1;
			}
			else if(vehicleDB[vehicleid][pakrauta] == 2)
			{
				format(msg,sizeof(msg),"[racija] %s: pastebëjau, kaip %s veþa narkotikus!",police,itar);
				SendMessageToTeisesauga(0x7DB34DFF,msg);
				SendInfoMessage(playerid,"Zaidejas veza narkotines medziagas!");
				SendInfoMessage(id,"Policija: Vezate narkotikus!!! Jus suimamas.");
				vehicleDB[vehicleid][pakrauta]=0;
				if( GetPlayerWantedLevel(id)+2 < 10) SetPlayerWantedLevel(id,GetPlayerWantedLevel(id)+2);
				else SetPlayerWantedLevel(id,10);
				if(!playerDB[id][ant])
				{
					playerDB[id][ant]=true;
					TogglePlayerControllable(id,false);
					SetPlayerAttachedObject(id, CUFF_SLOT, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
					SendClientMessage(playerid,0xFF000090,"Surakinote vagi.");
					SendClientMessage(id,0xFF000090,"Jus surakino.");
				}
				return 1;
			}
			else if(IsVagiuCar(vehicleid))
			{
				format(msg,sizeof(msg),"[racija] %s: pastebëjau, kaip %s veþa vogtà maðinà!",police,itar);
				SendMessageToTeisesauga(0x7DB34DFF,msg);
				SendInfoMessage(playerid,"Zaidejo masina vogta!!!!!");
				SendInfoMessage(id,"Policija: Vezate vogta masina. Jus suimamas");
				new respawnint = GetPlayerVehicleID(id);
				vehicleDB[respawnint][lastpos][0]=0;
				vehicleDB[respawnint][lastpos][1]=0;
				vehicleDB[respawnint][lastpos][2]=0;
				SetVehicleToRespawn(respawnint);
				if(GetPlayerWantedLevel(id)+2 < 10) SetPlayerWantedLevel(id,GetPlayerWantedLevel(id)+2);
				else SetPlayerWantedLevel(id,10);
				if(!playerDB[id][ant])
				{
					playerDB[id][ant]=true;
					TogglePlayerControllable(id,false);
					if(!IsPlayerInAnyVehicle(id))
					{
						//RemovePlayerAttachedObject(playerid,CUFF_SLOT);
						//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
						SetPlayerSpecialAction(id, 24); // SPECIAL_ACTION_CUFFED
						SetPlayerAttachedObject(id, CUFF_SLOT, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
					}
					SendClientMessage(playerid,0xFF000090,"Surakinote vagi.");
					SendClientMessage(id,0xFF000090,"Jus surakino.");
				}
				return 1;
			}
			else if(InkaUzsakymai[id][utype] == 1 && GetVehicleModel(vehicleid) == 428)
			{
				format(msg,sizeof(msg),"[racija] %s: pastebëjau, kaip %s veþa padirbtus pinigus!",police,itar);
				SendMessageToTeisesauga(0x7DB34DFF,msg);
				SendInfoMessage(playerid,"Zaidejo masina pilna padirbtu pinigu!");
				SendInfoMessage(id,"Policija: Vezate padirbtus pinigus! Esate suimamas.");
				InkaUzsakymai[id][utype]=0;
				RemovePlayerFromVehicle(id);
				if(GetPlayerWantedLevel(id)+2 < 10) SetPlayerWantedLevel(id,GetPlayerWantedLevel(id)+2);
				else SetPlayerWantedLevel(id,10);
				if(!playerDB[id][ant])
				{
					playerDB[id][ant]=true;
					TogglePlayerControllable(id,false);
					if(!IsPlayerInAnyVehicle(id))
					{
						//RemovePlayerAttachedObject(playerid,CUFF_SLOT);
						//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
						SetPlayerSpecialAction(id, 24); // SPECIAL_ACTION_CUFFED
						SetPlayerAttachedObject(id, CUFF_SLOT, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
					}
					SendClientMessage(playerid,0xFF000090,"Surakinote inkasatoriu.");
					SendClientMessage(id,0xFF000090,"Jus surakino.");
				}
				return 1;
			}
			else if(vehicleDB[vehicleid][pakrauta] == 0)
			{
				SendInfoMessage(playerid,"Zaidejas svarus!");
				SendInfoMessage(id,"Policija: Patikrinome jusu masina. Atleiskite uz sutrugdyma.");
				return 1;
			}
			return 1;
		}
		new vehicleid = playerDB[id][masina];
		new Float:Coo[3];
		GetVehiclePos(vehicleid,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(30, id, Coo[0],Coo[1],Coo[2])){SendInfoMessage(playerid," Zaidejo automobilis per toli!"); return 1;}
		if(GetPlayerWantedLevel(id) > 4) return SendInfoMessage(playerid,"Zaidejas jau gaudomas!!");
		if(krovinys[vehicleid] > 0  && (vak[vehicleid] || vmp[vehicleid] || vdgl[vehicleid] || vawp[vehicleid]))
		{
			format(msg,sizeof(msg),"[racija] %s: pastebëjau, kaip %s veþa nelegalius ginklus!",police,itar);
			SendMessageToTeisesauga(0x7DB34DFF,msg);
  			vehicleDB[vehicleid][pakrauta]=0;
			krovinys[vehicleid]=0;
			vmp[vehicleid]=0;
			vak[vehicleid]=0;
			vdgl[vehicleid]=0;
			vawp[vehicleid]=0;
			SendInfoMessage(playerid,"Zaidejas veza nelegalius ginklus!!!!");
			SendInfoMessage(id,"Policija: Vezate nelegalius ginklus! Jus suimamas.");
			vehicleDB[vehicleid][pakrauta]=0;
			if( GetPlayerWantedLevel(id)+1 < 10) SetPlayerWantedLevel(id,GetPlayerWantedLevel(id)+1);
			else SetPlayerWantedLevel(id,10);
			if(!playerDB[id][ant])
			{
				playerDB[id][ant]=true;
				TogglePlayerControllable(id,false);
				if(!IsPlayerInAnyVehicle(id))
				{
					//RemovePlayerAttachedObject(playerid,CUFF_SLOT);
					//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
					SetPlayerSpecialAction(id, 24); // SPECIAL_ACTION_CUFFED
					SetPlayerAttachedObject(id, CUFF_SLOT, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
				}
				SendClientMessage(playerid,0xFF000090,"Surakinote kontrabandininka");
				SendClientMessage(id,0xFF000090,"Jus surakino.");
			}
			return 1;
		}
		else if(vehicleDB[vehicleid][pakrauta] == 2)
		{
			format(msg,sizeof(msg),"[racija] %s: pastebëjau, kaip %s veþa narkotikus!",police,itar);
			SendMessageToTeisesauga(0x7DB34DFF,msg);
			SendInfoMessage(playerid,"Zaidejas veza narkotines medziagas.");
			SendInfoMessage(id,"Vezate narkotikus!!! Jus suimamas.");
			vehicleDB[vehicleid][pakrauta]=0;
			if( GetPlayerWantedLevel(id)+2 < 10) SetPlayerWantedLevel(id,GetPlayerWantedLevel(id)+2);
			else SetPlayerWantedLevel(id,10);
			if(!playerDB[id][ant])
			{
				playerDB[id][ant]=true;
				TogglePlayerControllable(id,false);
				if(!IsPlayerInAnyVehicle(id))
				{
					//RemovePlayerAttachedObject(playerid,CUFF_SLOT);
					//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
					SetPlayerSpecialAction(id, 24); // SPECIAL_ACTION_CUFFED
					SetPlayerAttachedObject(id, CUFF_SLOT, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
				}
				SendClientMessage(playerid,0xFF000090,"Surakinote kontrabandininka");
				SendClientMessage(id,0xFF000090,"Jus surakino.");
			}
			return 1;
		}
		else if(IsVagiuCar(vehicleid))
		{
			format(msg,sizeof(msg),"[racija] %s: pastebëjau, kaip %s veþa vogtà maðinà!",police,itar);
			SendMessageToTeisesauga(0x7DB34DFF,msg);
			SendInfoMessage(playerid,"Zaidejo masina vogta!!!!!");
			SendInfoMessage(id,"Policija: Vezate vogta masina. Jus suimamas");
			new respawnint = playerDB[id][masina];
			vehicleDB[respawnint][lastpos][0]=0;
			vehicleDB[respawnint][lastpos][1]=0;
			vehicleDB[respawnint][lastpos][2]=0;
			SetVehicleToRespawn(respawnint);
			if(GetPlayerWantedLevel(id)+2 < 10) SetPlayerWantedLevel(id,GetPlayerWantedLevel(id)+2);
			else SetPlayerWantedLevel(id,10);
			if(!playerDB[id][ant])
			{
				playerDB[id][ant]=true;
				TogglePlayerControllable(id,false);
				if(!IsPlayerInAnyVehicle(id))
				{
					//RemovePlayerAttachedObject(playerid,CUFF_SLOT);
					//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
					SetPlayerSpecialAction(id, 24); // SPECIAL_ACTION_CUFFED
					SetPlayerAttachedObject(id, CUFF_SLOT, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
				}
				SendClientMessage(playerid,0xFF000090,"Surakinote vagi.");
				SendClientMessage(id,0xFF000090,"Jus surakino.");
			}
			return 1;
		}
		else if(InkaUzsakymai[id][utype] == 1 && GetVehicleModel(vehicleid) == 428)
		{
			format(msg,sizeof(msg),"[racija] %s: pastebëjau, kaip %s veþa padirbtus pinigus!",police,itar);
			SendMessageToTeisesauga(0x7DB34DFF,msg);
			SendInfoMessage(playerid,"Zaidejo masina pilna padirbtu pinigu!");
			SendInfoMessage(id,"Policija: Vezate padirbtus pinigus! Esate suimamas.");
			InkaUzsakymai[id][utype]=0;
			RemovePlayerFromVehicle(id);
			if(GetPlayerWantedLevel(id)+2 < 10) SetPlayerWantedLevel(id,GetPlayerWantedLevel(id)+2);
			else SetPlayerWantedLevel(id,10);
			if(!playerDB[id][ant])
			{
				playerDB[id][ant]=true;
				TogglePlayerControllable(id,false);
				if(!IsPlayerInAnyVehicle(id))
				{
					//RemovePlayerAttachedObject(playerid,CUFF_SLOT);
					//SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
					SetPlayerSpecialAction(id, 24); // SPECIAL_ACTION_CUFFED
					SetPlayerAttachedObject(id, CUFF_SLOT, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
				}
				SendClientMessage(playerid,0xFF000090,"Surakinote inkasatoriu.");
				SendClientMessage(id,0xFF000090,"Jus surakino.");
			}
			return 1;
		}
		else
		{
			SendInfoMessage(playerid,"Zaidejas svarus!");
			SendInfoMessage(id,"Policija: Patikrinome jusu masina. Atleiskite uz sutrugdyma.");
			return 1;
		}
}

CMD:matuoklis(playerid,params[])
{
		#pragma unused params
	if(playerDB[playerid][specialybe]!=80 && playerDB[playerid][specialybe]!= 84 && !playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda tik teisesaugai"); return 1;}
	if(!aktivuotas[playerid])
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			SendInfoMessage(playerid,"Komanda nenaudojama masonoje");
			aktivuotas[playerid] = false;
			return 1;
		}
		aktivuotas[playerid] = true;
		SendInfoMessage(playerid,"Greicio matuoklis~g~ ijungtas");

		ApplyAnimation(playerid,"PED","gang_gunstand",4.0,1,0,0,0,0,1);
		ApplyAnimation(playerid,"PED","gang_gunstand",4.0,1,0,0,0,0,1);
		SetTimerEx("CheckS", 1000, false, "i", playerid);
		return 1;
	}
	else
	{
		if(IsPlayerInAnyVehicle(playerid))
		{
			SendInfoMessage(playerid,"Komanda nenaudojama masinoje");
			aktivuotas[playerid] = false;
			ApplyAnimation(playerid, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 0, 0);
			return 1;
		}
		aktivuotas[playerid] = false;
		SendInfoMessage(playerid,"Greicio matuoklis~r~ isjungtas");
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 0, 0);
		return 1;
	}
}


CMD:telon(playerid,params[])
{
	if(!playerDB[playerid][telon])
	{
	    playerDB[playerid][telon]=true;
	    SendInfoMessage(playerid,"~g~Ijungei~w~ savo telefona!");
	    return 1;
	}
	else
	{
	    playerDB[playerid][telon]=false;
		SendInfoMessage(playerid,"~r~Isjungei~w~ savo telefona!");
		if(playerDB[playerid][skambutis]!= -1)
		{
			SendInfoMessage(playerid,"Pokalbis baigtas.");
			PlayerPlaySound(playerid, 1186, 0.0, 0.0, 0.0); // Isjunge muzika
			new pokalbis = playerDB[playerid][skambutis];
			playerDB[pokalbis][skambutis]=-1;
			SendInfoMessage(playerid,"Pokalbis baigtas.");
			PlayerPlaySound(pokalbis, 1186, 0.0, 0.0, 0.0); // Isjunge muzika
			playerDB[playerid][skambutis]=-1;
		}
	    return 1;
	}
}


CMD:sms(playerid,params[])
{
    if(playerDB[playerid][ikalintas]) return SendInfoMessage(playerid,"Policija ateme jusu telefona. Prasome naudotis taksofonu.");
    if(!playerDB[playerid][telon]) return SendInfoMessage(playerid,"Jusu telefonas yra isjungtas. Naudokite /telon .");
	new vardas[128],vardas2[MAX_PLAYER_NAME],texts[128];
	if(sscanf(params,"s[24]s[128]",vardas,texts)) {SendInfoMessage(playerid,"Parasyti trumpaja zinute: /sms [dalis_vardo] [tekstas]"); return 1;}

	if(playerDB[playerid][mobsas] < 2)
	{
		ProcessAchievement(playerid,40);
		if(!playerDB[playerid][admin])
		{
			SendInfoMessage(playerid,"Jums nepakanka saskaitos! Pasipildykite ja spaudos kioske.");
			
			return 1;
		}
	}
	new recieverid = INVALID_PLAYER_ID;
	if(IsNumeric(vardas))
	{
		recieverid = strval(vardas);
	}
	else
	{
		recieverid = GetPlayeridMid(vardas);
	}

	if(recieverid == INVALID_PLAYER_ID || !IsPlayerConnected(recieverid) || playerDB[recieverid][invisible])
	{
		SendInfoMessage(playerid,"Tokio vardo nera");
		return 1;
	}
    if(playerDB[recieverid][ikalintas]) return SendInfoMessage(playerid,"Telefonas yra uz rysio zonos ribu.");
	if(!playerDB[recieverid][telon]) return SendInfoMessage(playerid,"Gavejo telefonas yra isjungtas.");
	GetPlayerName(playerid,vardas2,sizeof(vardas2));
	GetPlayerName(recieverid,vardas,sizeof(vardas));
	if(!playerDB[playerid][admin])
		playerDB[playerid][mobsas]-=2;

	new tex[128];
	if(recieverid != INVALID_PLAYER_ID)
	{
		format(tex,sizeof(tex),"SMS: [%s >> %s ]:",vardas2,vardas);
		SendClientMessage(recieverid,TEXTCOL_SILVER,tex);
		SendClientMessage(recieverid,TEXTCOL_RED,texts);
	}

	if(playerid!=INVALID_PLAYER_ID)
	{
		if(IsPlayerAfk(recieverid)) 
			format(tex,sizeof(tex),"SMS: [%s >> %s {FFFFFF}[AFK]{98B134} ]:",vardas2,vardas);
		else
			format(tex,sizeof(tex),"SMS: [%s >> %s ]:",vardas2,vardas);
		SendClientMessage(playerid,TEXTCOL_GREEN,tex);
		SendClientMessage(playerid,TEXTCOL_RED,texts);
	}
	ProcessAchievement(playerid, 82);
	parase[recieverid]=playerid;
	PlayerPlaySound(recieverid, 1138, 0.0, 0.0, 0.0); // SMS
	return 1;

}

CMD:me(playerid,params[])
{
	new zinute[256];
	if(sscanf(params,"s[256]",zinute))
	{
		SendInfoMessage(playerid,"/me [veiksmas]");
		return 1;
	}
	new msg[256];
	GetPlayerName(playerid, msg, MAX_PLAYER_NAME);
	format(msg, sizeof(msg), "* %s %s", msg, zinute);

	new Float:coo[3];
	GetPlayerPos(playerid,coo[0],coo[1],coo[2]);
	new vw = GetPlayerVirtualWorld(playerid);
	foreach (Player, player)
	{
			if(IsPlayerInRangeOfPointEx(30,player,coo[0],coo[1],coo[2]) && GetPlayerVirtualWorld(player)==vw)
			{
				SendClientMessageEx(player,COLOR,msg);
			}
	}
	return 1;
}

CMD:moneta(playerid,params[])
{
	#pragma unused params

	new idas = GetPVarInt(playerid, "moneta_pasiule");
	if(GetPVarInt(idas,"moneta_text"))
	{
		SendClientMessage(idas, ORANGE, " * Zaidejas atsauke savo pasiulyma.");
		SendClientMessage(playerid, ORANGE, " * Atsaukete savo pasiulyma");
		SetPVarInt(idas,"moneta_text",0);
		SetPVarInt(playerid,"moneta_pasiule",0);
		return 1;
	}
	if(!galikast[playerid]) return 1;
	galikast[playerid]=false;
	SetTimerEx("GaliKast",3000,0,"i",playerid);
	new vardas[25], suma; //[256];
	if(sscanf(params,"s[25]d",vardas,suma))
	{
		SendInfoMessage(playerid,"Galite mesti moneta is pinigu parase /moneta [vardo dalis] [suma]");
		IsmestiMoneta(playerid);
	}
	else
	{
		if(!BitFlag_Get(PConfig[playerid],PCFG_MONETA))
			return SendInfoMessage(playerid,"~r~Tu isjunges monetos pasiulymus. Juos ijungti gali per VVP (/p -> Nustatymai)");
		if(GetPlayerScore(playerid) < 100)
			return SendInfoMessage(playerid,"~r~Turi per mazai xp!");
		if(suma <= 0 || suma > 100000000)
			return SendInfoMessage(playerid,"Netinkama suma.");

		new id = GetPlayeridMid(vardas);
		if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		if (playerDB[id][invisible]){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
		if (id == playerid){ SendInfoMessage(playerid,"Su savim mesti negali!"); return 1;}
		if(GetPlayerScore(id) < 100)
			return SendInfoMessage(playerid,"~r~Zaidejas turi per mazai xp!");
		if(!BitFlag_Get(PConfig[id],PCFG_MONETA))
			return SendInfoMessage(playerid,"~r~Zaidejas isjunges monetos pasiulymus. Juos ijungti gali per VVP (/p -> Nustatymai)");
		new Float:Coo[3];
		GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
		if(!IsPlayerInRangeOfPointEx(10, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(id) == PLAYER_STATE_SPECTATING)
			return SendInfoMessage(playerid,"Zaidejas per toli!");
		if(GetTickCount() - GetPVarInt(playerid, "monetatime") < 10*1000)
		{
			return SendInfoMessage(playerid,"Moneta gali siulyti tik kas 10 sekundziu.");
		}
		if(GetTickCount() - GetPVarInt(id,"monetaoffertime") < 10*1000)
		{
			return SendInfoMessage(playerid,"Sis zaidejas jau turi monetos pasiulyma");
		}
		if(GetPlayerMoneyA(playerid) < suma)
			return SendInfoMessage(playerid,"Neturi pakankamai pinigu.");
		if(GetPlayerMoneyA(id) < suma)
			return SendInfoMessage(playerid,"Zaidejas neturi tiek pinigu.");
		if(GetPVarInt(playerid,"moneta_text"))
			return SendInfoMessage(playerid,"Tu jau turi pasiulyma!");
		SetPVarInt(playerid, "monetatime", GetTickCount());
		SetPVarInt(playerid, "moneta_pasiule",id);
		SetPVarInt(id, "monetaoffertime", GetTickCount());
		SetPVarInt(id, "moneta_id", playerid);
		SetPVarInt(id, "moneta_sum",suma);
		SetPVarInt(id, "moneta_text", 1);



		new msgas[256];
		format(msgas,sizeof(msgas)," * %s siûlo jums mesti monetà ið %s€. Jeigu sutinkate, raðykite \"skaicius\" arba \"herbas\".",ReturnName(playerid),FormatNumber(suma));
		SendClientMessage(id, ORANGE, msgas);
		format(msgas,sizeof(msgas)," * Pasiûlëte %s mesti monetà ið %s€.",ReturnName(id),FormatNumber(suma));

		SendClientMessage(playerid, ORANGE, msgas);


	}

	
	return 1;
}

CMD:vchat(playerid,params[])
{
	if(!playerDB[playerid][vip])
	{
		SendInfoMessage(playerid,"Ði komanda tik vipams.");
		return 1;
	}
	new zinute[256];
	if(sscanf(params,"s[256]",zinute))
	{
		SendInfoMessage(playerid,"/vchat [zinute] ");
		return 1;
	}
	new tick = GetTickCount();
	if((tick-LastVipMessage[playerid]) < 10000) return SendInfoMessage(playerid,"~r~Vip zinute galite rasyti tik kas 10 sekundziu!");
	LastVipMessage[playerid]=tick;
	new msg[256];
	GetPlayerName(playerid, msg, MAX_PLAYER_NAME);
	format(msg, sizeof(msg), "VIP %s:%s", msg, zinute);
	foreach(Player, i)
	{
		if(BitFlag_Get(PConfig[i],PCFG_SHOWVCHAT))
			SendClientMessageEx(i,YELLOW,msg);
	}
//	SendClientMessageToAll(YELLOW,msg);
	return 1;
}



CMD:parkuoti(playerid,params[])
{
    #pragma unused params
	if(CheckZone(playerid)) return 0;
	if (IsPlayerInVehicle(playerid,Carlist[playerid][Carid]))
	{
		GetVehiclePos(Carlist[playerid][Carid],Carlist[playerid][X],Carlist[playerid][Y],Carlist[playerid][Z]);
		GetVehicleZAngle(Carlist[playerid][Carid],Carlist[playerid][Rotation]);
		Carlist[playerid][VirtualW] = GetVehicleVirtualWorld(Carlist[playerid][Carid]);
		SendInfoMessage(playerid,"Pirmoji Masina sekmingai priparkuota.");
	}
	else if (IsPlayerInVehicle(playerid,Carlist2[playerid][Carid]))
	{
		GetVehiclePos(Carlist2[playerid][Carid],Carlist2[playerid][X],Carlist2[playerid][Y],Carlist2[playerid][Z]);
		GetVehicleZAngle(Carlist2[playerid][Carid],Carlist2[playerid][Rotation]);
		Carlist2[playerid][VirtualW] = GetVehicleVirtualWorld(Carlist2[playerid][Carid]);
		SendInfoMessage(playerid,"Antroji Masina sekmingai priparkuota.");
	}
	else if (IsPlayerInVehicle(playerid,Carlist3[playerid][Carid]))
	{
		GetVehiclePos(Carlist3[playerid][Carid],Carlist3[playerid][X],Carlist3[playerid][Y],Carlist3[playerid][Z]);
		GetVehicleZAngle(Carlist3[playerid][Carid],Carlist3[playerid][Rotation]);
		SendInfoMessage(playerid,"Trecioji Masina sekmingai priparkuota.");
		Carlist3[playerid][VirtualW] = GetVehicleVirtualWorld(Carlist3[playerid][Carid]);
	}
	else { SendInfoMessage(playerid,"Cia ne jusu masina!"); }
	return 1;
}

CMD:spos(playerid,params[])
{
    #pragma unused params
	if(CheckZone(playerid)) return 0;
	if (IsPlayerInVehicle(playerid,Carlist[playerid][Carid]))
	{
		GetVehiclePos(Carlist[playerid][Carid],Carlist[playerid][X],Carlist[playerid][Y],Carlist[playerid][Z]);
		GetVehicleZAngle(Carlist[playerid][Carid],Carlist[playerid][Rotation]);
		Carlist[playerid][VirtualW] = GetVehicleVirtualWorld(Carlist[playerid][Carid]);
		SendInfoMessage(playerid,"Pirmoji Masina sekmingai priparkuota. Kita syki naudokite /parkuoti");
	}
	else if (IsPlayerInVehicle(playerid,Carlist2[playerid][Carid]))
	{
		GetVehiclePos(Carlist2[playerid][Carid],Carlist2[playerid][X],Carlist2[playerid][Y],Carlist2[playerid][Z]);
		GetVehicleZAngle(Carlist2[playerid][Carid],Carlist2[playerid][Rotation]);
		Carlist2[playerid][VirtualW] = GetVehicleVirtualWorld(Carlist2[playerid][Carid]);
		SendInfoMessage(playerid,"Antroji Masina sekmingai priparkuota. Kita syki naudokite /parkuoti");
	}
	else if (IsPlayerInVehicle(playerid,Carlist3[playerid][Carid]))
	{
		GetVehiclePos(Carlist3[playerid][Carid],Carlist3[playerid][X],Carlist3[playerid][Y],Carlist3[playerid][Z]);
		GetVehicleZAngle(Carlist3[playerid][Carid],Carlist3[playerid][Rotation]);
		Carlist3[playerid][VirtualW] = GetVehicleVirtualWorld(Carlist3[playerid][Carid]);
		SendInfoMessage(playerid,"Trecioji Masina sekmingai priparkuota. Kita syki naudokite /parkuoti");
	}
	else { SendInfoMessage(playerid,"Cia ne jusu masina!"); }
	return 1;
}

CMD:remontuoti(playerid,params[])
{
    #pragma unused params
    new msg[512];
    new status[24];
    new cost[50];
    if(Carlist[playerid][Typ]!=-1)
	{
		if(Carlist[playerid][Status]==0) {
			status = #TEXT_RED"Reikia";
			new reparatur = floatround(aVehicleNames[Carlist[playerid][Typ]][Repair]/AdjustByRida(0,RIDA_REMONTAS,Carlist[playerid][Rida]));
			format(cost,sizeof cost,"%s€",FormatNumber(reparatur));
		}
		else {
			status = #TEXT_GREEN"Nereikia";
			cost = "";
		}
	    format(msg,sizeof(msg),#TEXT_BLUE"• "#TEXT_WHITE"%s\t%s\t%s",aVehicleNames[Carlist[playerid][Typ]][Name],status,cost);
        AddDListItem(playerid, msg, 0);
	}
	if(Carlist2[playerid][Typ]!=-1)
	{
		if(Carlist2[playerid][Status]==0) {
			status = #TEXT_RED"Reikia";
			new reparatur = floatround(aVehicleNames[Carlist2[playerid][Typ]][Repair]/AdjustByRida(0,RIDA_REMONTAS,Carlist2[playerid][Rida]));
			format(cost,sizeof cost,"%s€",FormatNumber(reparatur));
		}
		else {
			status = #TEXT_GREEN"Nereikia";
			cost = "";
		}
	    format(msg,sizeof(msg),#TEXT_BLUE"• "#TEXT_WHITE"%s\t%s\t%s",aVehicleNames[Carlist2[playerid][Typ]][Name],status,cost);
        AddDListItem(playerid, msg, 1);
	}
	if(Carlist3[playerid][Typ]!=-1)
	{
		if(Carlist3[playerid][Status]==0) {
			status = #TEXT_RED"Reikia";
			new reparatur = floatround(aVehicleNames[Carlist3[playerid][Typ]][Repair]/AdjustByRida(0,RIDA_REMONTAS,Carlist3[playerid][Rida]));
			format(cost,sizeof cost,"%s€",FormatNumber(reparatur));
		}
		else {
			status = #TEXT_GREEN"Nereikia";
			cost = "";
		}
	    format(msg,sizeof(msg),#TEXT_BLUE"• "#TEXT_WHITE"%s\t%s\t%s",aVehicleNames[Carlist3[playerid][Typ]][Name],status,cost);
        AddDListItem(playerid, msg, 2);
	}
	ShowPlayerDListHeader(playerid, 302, "Remontuoti", "Rinktis", "Iseiti","Automobilis\tRemontas\tKaina");
//	ShowPlayerDialog(playerid,302,DIALOG_STYLE_LIST,"Remontuoti",msg,"Rinktis","Iseiti");
	return 1;
}
CMD:rakinti(playerid,params[])
{
    #pragma unused params
    new msg[512];
    new status[24];
	if(Carlist[playerid][Typ]!=-1)
	{
		if (Carlist[playerid][Lock]==0)
			status = #TEXT_GREEN"Atrakinta";
		else
			status = #TEXT_RED"Uþrakinta";
	    format(msg,sizeof(msg),#TEXT_BLUE"• "#TEXT_WHITE"%s\t%s",aVehicleNames[Carlist[playerid][Typ]][Name],status);
        AddDListItem(playerid, msg, 0);
	}
	if(Carlist2[playerid][Typ]!=-1)
	{
		if (Carlist2[playerid][Lock]==0)
			status = #TEXT_GREEN"Atrakinta";
		else
			status = #TEXT_RED"Uþrakinta";
	    format(msg,sizeof(msg),#TEXT_BLUE"• "#TEXT_WHITE"%s\t%s",aVehicleNames[Carlist2[playerid][Typ]][Name],status);
        AddDListItem(playerid, msg, 1);
	}
	if(Carlist3[playerid][Typ]!=-1)
	{
		if (Carlist3[playerid][Lock]==0)
			status = #TEXT_GREEN"Atrakinta";
		else
			status = #TEXT_RED"Uþrakinta";
	    format(msg,sizeof(msg),#TEXT_BLUE"• "#TEXT_WHITE"%s\t%s",aVehicleNames[Carlist3[playerid][Typ]][Name],status);
        AddDListItem(playerid, msg, 2);
	}
	ShowPlayerDListTab(playerid, 301, "Rakinti", "Rinktis", "Iseiti");
//    	ShowPlayerDialog(playerid,301,DIALOG_STYLE_LIST,"Rakinti",msg,"Rinktis","Iseiti");
	return 1;
}

CMD:kurmasina(playerid,params[])
{
    #pragma unused params
    new msg[512];
	new status[24];
	new Float:coo[6];
	GetPlayerPos(playerid,coo[3],coo[4],coo[5]);
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
	ShowPlayerDListHeader(playerid, 303, "Kur masina?", "Rinktis", "Iseiti","Automobilis\tAtstumas");
	
//	ShowPlayerDialog(playerid,303,DIALOG_STYLE_LIST,"Kur masina?",msg,"Rinktis","Iseiti");
	return 1;
}
CMD:islipti(playerid,params[])
{
    #pragma unused params
    if (Spectating[playerid][0]!=-1)
	{
		TogglePlayerControllable(playerid,1);
		SetVehicleParamsForAll(aVehicleNames[Spectating[playerid][0]][Carid],0,0);
		Spectating[playerid][0]=-1;
		new masinx = GetPlayerVehicleID(playerid);
		Stop(playerid);
		new vehicleid = masinx;
		vehicleDB[vehicleid][lastpos][0]=0;
		vehicleDB[vehicleid][lastpos][1]=0;
		vehicleDB[vehicleid][lastpos][2]=0;
		SetVehicleToRespawn(masinx);
	}
	else { SendInfoMessage(playerid,"Jus nesate parduodamoje masinoje."); }
	return 1;
}

CMD:skelb(playerid,params[])
{
	if(playerDB[playerid][specialybe]!=50 && playerDB[playerid][admin]==false) {SendInfoMessage(playerid,"Si komanda tik skelbejams."); return 1;}
	new zinute[256],spalvike;
	if(sscanf(params,"cs[256]",spalvike,zinute))
	{
		SendClientMessage(playerid,WHITE,"/skelb [spalva r/m] [ka?] ");
		SendClientMessage(playerid,0xFF0080FF,"Rozinis skelbimas kainuoja "#MONEYP_SKELBEJAI2"€");
		SendClientMessage(playerid,ABLUE,"Melynas skelbimas kainuoja "#MONEYP_SKELBEJAI"€");
		return 1;
	}
	new tick = GetTickCount();
	if(tick - LastSkelbimas[playerid] < 30*1000)
		return SendInfoMessage(playerid,"Skelbti gali tik kas 30 sekundziu!");
	LastSkelbimas[playerid]=tick;
	if(spalvike == 'R' || spalvike == 'r')
	{
		if(GetPlayerMoneyA(playerid) < MONEYP_SKELBEJAI2)
		{
			SendInfoMessage(playerid,"Rozinio Skelbimo kaina "#MONEYP_SKELBEJAI2"EUR, jus tiek neturite.");
			return 1;
		}
		new name[MAX_PLAYER_NAME];
		new zin[256];
		GetPlayerName(playerid,name,MAX_PLAYER_NAME);
		format(zin,sizeof(zin),"Skelbëjas %s: %s",name,zinute);
		SendClientMessageToAllEx(0xFF0080FF,zin);
		GivePlayerMoneyA(playerid,-MONEYP_SKELBEJAI2);
		
		Pelnas(playerid,49,MONEYP_SKELBEJAI);
		playerDB[playerid][jobpts]++;
		ProcessAchievement(playerid,63);
		return 1;
	}
	else if(spalvike == 'm' || spalvike == 'M')
	{
		if(GetPlayerMoneyA(playerid) < MONEYP_SKELBEJAI)
		{
			SendInfoMessage(playerid,"Melyno Skelbimo kaina "#MONEYP_SKELBEJAI"EUR, jus tiek neturite.");
			return 1;
		}
		GivePlayerMoneyA(playerid,-MONEYP_SKELBEJAI);
		Pelnas(playerid,49,MONEYP_SKELBEJAI);
		new msg[256];
		GetPlayerName(playerid, msg, MAX_PLAYER_NAME);
		format(msg,sizeof(msg),"Skelbëjas %s: %s",msg,zinute);
		SendClientMessageToAllEx(ABLUE,msg);
		playerDB[playerid][jobpts]++;
		ProcessAchievement(playerid,63);
	}
	else SendInfoMessage(playerid,"/skelb [spalva r/m] [ka?] ");
	return 1;
}




CMD:balansas(playerid,params[])
{
    #pragma unused params
    if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 428) return SendInfoMessage(playerid,"Siomis komandomis gali naudotis tik bankininko masinoje.");

	if(!playerDB[playerid][kortele]) return SendInfoMessage(playerid,"Demesio! Jus neturite banko korteles!");
	new vehicleid = GetPlayerVehicleID(playerid);
	new vairuotojas = GetDriver(vehicleid);
	//if(vairuotojas == playerid) return 1;
	if(vairuotojas == INVALID_PLAYER_ID)
	{
		SendInfoMessage(playerid,"Nera bankininko ar inkasatoriaus.");
		//Stop(playerid);
		return 1;
	}
	new msg[128];
	format(msg,sizeof(msg),"Banke jus turite: %i EUR",playerDB[playerid][banke]);
	SendInfoMessage(playerid,msg);
	return 1;
}

CMD:padet(playerid,params[])
{
    if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 428) return SendInfoMessage(playerid,"Siomis komandomis gali naudotis tik bankininko masinoje.");

	if(!playerDB[playerid][kortele]) return SendInfoMessage(playerid,"Demesio! Jus neturite banko korteles!");
	new vehicleid = GetPlayerVehicleID(playerid);
	new vairuotojas = GetDriver(vehicleid);
	//if(vairuotojas == playerid) return 1;
	if(vairuotojas == INVALID_PLAYER_ID)
	{
		SendInfoMessage(playerid,"Nera bankininko ar inkasatoriaus.");
		//Stop(playerid);
		return 1;
	}
	new kiek;
	if(sscanf(params,"d",kiek))
	{
		SendInfoMessage(playerid,"Padet pinigu i banka: /padet [kiek]");
		return 1;
	}
    if(kiek <= 0) return SendInfoMessage(playerid,"Rasykite normaliu skaiciu!");
	if(GetPlayerMoneyA(playerid) < kiek)
	{
		SendInfoMessage(playerid,"Tu tiek neturi!");
		return 1;
	}

	GivePlayerMoneyA(playerid,-kiek);
	playerDB[playerid][banke]+=kiek;
	////ApplyAnimation(playerid, "GANGS", "DEALER_DEAL", 4.000000, 0, 0, 0, 0, -1);
	return 1;
}
CMD:paimt(playerid,params[])
{
    if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 428) return SendInfoMessage(playerid,"Siomis komandomis gali naudotis tik bankininko masinoje.");
	if(!playerDB[playerid][kortele]) return SendInfoMessage(playerid,"Demesio! Jus neturite banko korteles!");
	new kiek;
	new vehicleid = GetPlayerVehicleID(playerid);
	new vairuotojas = GetDriver(vehicleid);
	//if(vairuotojas == playerid) return 1;
	if(vairuotojas == INVALID_PLAYER_ID)
	{
		SendInfoMessage(playerid,"Nera bankininko ar inkasatoriaus.");
		//Stop(playerid);
		return 1;
	}
	if(sscanf(params,"d",kiek))
	{
		SendInfoMessage(playerid,"Paimt pinigu is banko: /paimt [kiek]");
		return 1;
	}
	if(kiek <= 0) return SendInfoMessage(playerid,"Rasykite normaliu skaiciu!");
	if(playerDB[playerid][banke] < kiek)
	{
		SendInfoMessage(playerid,"Banke, jus tiek neturite!");
		return 1;
	}

	playerDB[playerid][banke]-=kiek;
	GivePlayerMoneyA(playerid,kiek);
	ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
	return 1;
}


CMD:gydytis(playerid,params[])
{
    #pragma unused params
	SendInfoMessage(playerid,"Naudokite /pavalgyti!");
	return 1;

}

CMD:pavalgyti(playerid,params[])
{
	#pragma unused params
    if(GetPlace(playerid)==PLACE_HOUSE)
	{ 
		new housenumber,pname[MAX_PLAYER_NAME];
		housenumber = GetPlayerHouseID(playerid);
		if(hInfo[housenumber][hmaistas] >= 100)
		{
			hInfo[housenumber][hmaistas]-=100;
			GetPlayerName(playerid, pname, 24);

			if ( strcmp(hInfo[housenumber][Name],pname,false) && strcmp(hInfo[housenumber][Renter],pname,false) ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");

			SendInfoMessage(playerid,"Pasidarei maisto namie!");
			SetPlayerHealth(playerid,120);
			new query[128];
			format(query,sizeof(query),"UPDATE `Namai` SET `Maistas`=%i WHERE `ID`=%i",hInfo[housenumber][hmaistas],housenumber);
			mysql_query(query);
			new msg[128];
			format(msg,sizeof(msg),"Namie liko %ig maisto.",hInfo[housenumber][hmaistas]);
			SendClientMessage(playerid,COLOR_YELLOW,msg);
			Valgymas(playerid,90);
			LogA(playerid,"Pavalge Namie");
			ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
			return 1;
		}
		else if(playerDB[playerid][maistaslauk] > 0)
		{
			Valgymas(playerid,50);
			SendInfoMessage(playerid,"Valgai maista issinesimui!");
			ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
			playerDB[playerid][maistaslauk]=0;
		}
		else return SendInfoMessage(playerid,"Neturi maisto!");
	}
	else if(playerDB[playerid][maistaslauk] > 0)
	{
		Valgymas(playerid,50);
		SendInfoMessage(playerid,"Valgai!");
		ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
		playerDB[playerid][maistaslauk]=0;
	}
	else
	{
		SendInfoMessage(playerid,"Neturi maisto. Nusipirk 24/7 parduotuveje arba restorane. Taip pat gali pavalgyti namie.");
	}
	return 1;
}


CMD:spyna(playerid,params[])
{
    #pragma unused params
    if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");
	new pname[24],housenumber;
	housenumber = GetPlayerHouseID(playerid);
	GetPlayerName(playerid, pname, 24);

	if(hInfo[housenumber][Locked] == 1 && !hInfo[housenumber][islauztos])
	{
		if(strcmp(hInfo[housenumber][Name],pname,false)==0 || strcmp(hInfo[housenumber][Renter],pname,false)==0)
		{
			SendInfoMessage(playerid,"Jus ~g~atrakinote~w~ savo namus!");
			hInfo[housenumber][Locked] = 0;
			new query[128];
			format(query,sizeof(query),"UPDATE `Namai` SET `Locked`=%i WHERE `ID`=%i",hInfo[housenumber][Locked],housenumber);
			mysql_query(query);
			return 1;
		}
		else
		{
			SendInfoMessage(playerid,"Neturi raktu!");
		}
	}
	else if(hInfo[housenumber][Locked] == 0 && !hInfo[housenumber][islauztos])
	{
		if(strcmp(hInfo[housenumber][Name],pname,false)==0 || strcmp(hInfo[housenumber][Renter],pname,false)==0) 
		{
			SendInfoMessage(playerid,"Jus ~r~uzrakinote~w~ savo namus!");
			hInfo[housenumber][Locked] = 1;
			new query[128];
			format(query,sizeof(query),"UPDATE `Namai` SET `Locked`=%i WHERE `ID`=%i",hInfo[housenumber][Locked],housenumber);
			mysql_query(query);
			return 1;
		}
		else
		{
			SendInfoMessage(playerid,"Neturi raktu!");
			return 1;
		}
	}
	return 1;
}
CMD:saugot(playerid,params[])
{
	#pragma unused params
	if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");

	new housenumber,pname[MAX_PLAYER_NAME];
	housenumber = GetPlayerHouseID(playerid);
	GetPlayerName(playerid, pname, 24);

	if ( strcmp(hInfo[housenumber][Name],pname,false) && strcmp(hInfo[housenumber][Renter],pname,false) ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
	ProcessAchievement(playerid,18);
	SavePlayerData(playerid,false);
	return 1;
}
CMD:savex(playerid,params[])
{
    if(!playerDB[playerid][admin]) return 1;
    new vardas[128];
	if(sscanf(params,"s[24]",vardas)){SendInfoMessage(playerid,"Issaugoti zaideja /savex [zaidejo vardas]"); return 1;}
	new id = GetPlayeridMid(vardas);
	if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	if(playerDB[id][authstate]==0) { SendInfoMessage(playerid,"Zaidejas dar jungiasi."); return 1;}
	SavePlayerData(id,false);
	MLog(playerid,"Save","s",ReturnName(id));
	return 1;
}
CMD:saugoti(playerid,params[]) return cmd_saugot(playerid,params);
CMD:padeti(playerid,params[])
{
	#pragma unused params
	if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");
	if(GetPlayerScore(playerid) < 100) return SendInfoMessage(playerid," Daiktus pasideti gali tik nuo 100xp!");
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
	{
		printf("%s bande pasideti daiktus i nama per pzu",ReturnName(playerid));
		return 1;
	}
	new housenumber,pname[MAX_PLAYER_NAME];
	housenumber = GetPlayerHouseID(playerid);
	GetPlayerName(playerid, pname, 24);

	if ( strcmp(hInfo[housenumber][Name],pname,false) ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");

	ShowPlayerDialog(playerid,506,DIALOG_STYLE_LIST,"Padeti","Þolë\nAmfetaminas\nSëklos\nLSD\nRatai\nPinigai\nGinklai\nMaistas","Rinktis","Iseiti");
	return 1;
}
CMD:paimti(playerid,params[])
{
	#pragma unused params
	if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");

	new housenumber,pname[MAX_PLAYER_NAME];
	housenumber = GetPlayerHouseID(playerid);
	GetPlayerName(playerid, pname, 24);
	new i=housenumber;
	if ( strcmp(hInfo[housenumber][Name],pname,false) ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
	new msg[1024];
	format(msg,sizeof(msg),"{FFFFFF}Þolë {00BBFF}%i {FFFFFF}g\nAmfetaminas {00BBFF}%i {FFFFFF}vnt\nSëklos {00BBFF}%i {FFFFFF}vnt\nLSD {00BBFF}%i {FFFFFF}vnt\nRatai {00BBFF}%i {FFFFFF}vnt\nPinigai {00BBFF}%i {FFFFFF}€\nGinklai",hInfo[i][zole],hInfo[i][nark],hInfo[i][seklos],hInfo[i][lsd],hInfo[i][ratai],hInfo[i][pinigai]);
	ShowPlayerDialog(playerid,507,DIALOG_STYLE_LIST,"Paimti",msg,"Rinktis","Iseiti");
	//ShowPlayerDialog(playerid,507,DIALOG_STYLE_LIST,"Paimti","Zole\nAmfetaminas\nSeklos\nLSD\nRatai\nPinigai\nGinklai","Rinktis","Iseiti");
	
	return 1;
}
CMD:leistirengti(playerid,params[])
{
	if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");
	new str1[50],pname[24],housenumber;
	housenumber = GetPlayerHouseID(playerid);
	GetPlayerName(playerid, pname, 24);
	format(str1, sizeof(str1), "Houses/houseid%d", housenumber);

	if(strcmp(hInfo[housenumber][Name],pname,false)) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");

	ShowPlayerDialog(playerid, 6952, DIALOG_STYLE_INPUT, "Irengimas", "Áveskite NTA agento vardà, kuriam norite leisti árengti jûsø namà.\nTai jums kainuos 25.000€ + iðlaidos uþ baldus susitarus su NTA.\nJis/ji turës 24 valandas per kurias galës perstatyti ir pirkti naujus baldus jûsø namui.", "Gerai", "Atðaukti");


	return 1;
}
CMD:remontas(playerid,params[])
{
	#pragma unused params
	if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");
	new str1[50],pname[24],housenumber;
	housenumber = GetPlayerHouseID(playerid);
	GetPlayerName(playerid, pname, 24);
	format(str1, sizeof(str1), "Houses/houseid%d", housenumber);
	if(hInfo[housenumber][polyId] != -1)
		return SendInfoMessage(playerid,"Sio namo remontuoti negali!");
	if(strcmp(hInfo[housenumber][Name],pname,false)) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
	if(hInfo[housenumber][vidus] == 29 || (hInfo[housenumber][daugiabutis] && hInfo[housenumber][vidus] == 18))
	{
		SendInfoMessage(playerid,"Jusu vidus jau geriausias!");
		return 1;
	}
	new kaina = ((hInfo[housenumber][daugiabutis]) ? COST_REMONTASDGB:COST_REMONTAS);
	
	if(GetPlayerMoneyA(playerid) < kaina)
	{
		new mes[128];
		format(mes,128,"Truksta pinigu. Kitam lygiui reikia %iEUR.",kaina);
		SendInfoMessage(playerid,mes);
		return 1;
	}
	new nta=-1;
	foreach(Player,i)
	{
		if(playerDB[i][specialybe]==34 && i != playerid && GetPlayerHouseID(i) == housenumber)
		{
			nta=i;
			break;
		}
	}
	if(nta== -1) return SendInfoMessage(playerid,"~r~Privalote i namus pakviesti nekilnojamo turto agenta!");
	hInfo[housenumber][tobulina] = 1;
	GivePlayerMoneyA(playerid,-kaina);
	ProcessAchievement(playerid,119);
	GivePlayerMoneyA(nta, 1000);
	Pelnas(nta,33,10000);
	SendClientMessage(nta,COLOR," * Gavote 1000€ i rankas ir 15000€ i pelna uz atlikta darba!");
	SetTimerEx("Tobulinti",2*60*60*1000,false,"i",housenumber);
	//SetTimerEx("Tobulinti",3000,false,"i",housenumber);
	new vw;
	if(hInfo[housenumber][daugiabutis]) vw=(MAX_HOUSES*2+MAX_BUSINESSES+hInfo[housenumber][daugiabutis]-1);
	new msg[128];
	format(msg, 128, "* Remontuojate savo namo vidu. Tai uztruks 2 valandas. Dabartinis lygis - %i, po tobulinimo - %i.", hInfo[housenumber][vidus]+1,hInfo[housenumber][vidus]+2);
	foreach(Player, i)
	{
		if(GetPlace(i) == PLACE_HOUSE && housenumber == GetPlayerHouseID(i))
		{
			SetPlayerPoz(i,hInfo[housenumber][iconx],hInfo[housenumber][icony],hInfo[housenumber][iconz]+0.5);
			SetPlayerInterior(i, 0);
			SetPlayerVirtualWorld(i,vw);
			SendInfoMessage(i,"Prasome nesilanktyti namuose, kol juos remontuosime.");
			SetTimerEx("SavePlayerData",1000,false,"ii",playerid,0);
		}
	}
	SendClientMessage(playerid, COLOR_WHITE, msg);
	format(msg,sizeof(msg),"UPDATE `Namai` SET `Tobulina`=1 WHERE `ID`=%i",housenumber);
	mysql_query(msg);
	return 1;
}
CMD:lvl(playerid,params[])
{
	new moneys;
	if(sscanf(params,"d",moneys)){SendInfoMessage(playerid,"Sumazinti namo lygi. /lvl [lygis]");  return 1;}

	if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");
	new str1[50],pname[24],housenumber;
	housenumber = GetPlayerHouseID(playerid);
	moneys--;
	GetPlayerName(playerid, pname, 24);
	format(str1, sizeof(str1), "Houses/houseid%d", housenumber);
	if(hInfo[housenumber][polyId] != -1)
		return SendInfoMessage(playerid,"Sio namo remontuoti negali!");

	if(strcmp(hInfo[housenumber][Name],pname,false)) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
	if(moneys >= hInfo[housenumber][vidus])
	{
		SendInfoMessage(playerid,"Jusu vidus per mazo lygio!");
		return 1;
	}
	if(moneys < 1) return SendInfoMessage(playerid,"Blogai ivedete lygi!");
	new nta=-1;
	foreach(Player,i)
	{
		if(playerDB[i][specialybe]==34 && i != playerid && GetPlayerHouseID(i) == housenumber)
		{
			nta=i;
			break;
		}
	}
	if(nta== -1) return SendInfoMessage(playerid,"~r~Privalote i namus pakviesti nekilnojamo turto agenta!");
	hInfo[housenumber][tobulina] = 1;
	GivePlayerMoneyA(nta, 1000);
	Pelnas(playerid,33,2000);
	SendClientMessage(nta,COLOR," * Gavote 1000€ i rankas ir 2000€ i pelna uz atlikta darba!");
	SetTimerEx("Tobulinti2",2*60*60*1000,false,"ii",housenumber,moneys);
	new vw;
	if(hInfo[housenumber][daugiabutis]) vw=(MAX_HOUSES*2+MAX_BUSINESSES+hInfo[housenumber][daugiabutis]-1);
	new msg[128];
	format(msg, 128, "* Tobulinate savo namo vidu. Tai uztruks 2 valandas. Dabartinis lygis - %i, po tobulinimo - %i.", hInfo[housenumber][vidus]+1,moneys+1);
	SetPlayerPoz(playerid,hInfo[housenumber][iconx],hInfo[housenumber][icony],hInfo[housenumber][iconz]+0.5);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid,vw);
	SendInfoMessage(playerid,"Prasome nesilanktyti namuose, kol juos tobulinsime.");
	SetTimerEx("SavePlayerData",1000,false,"ii",playerid,0);
	SendClientMessage(playerid, COLOR_WHITE, msg);
	return 1;
}

CMD:radijan(playerid,params[])
{
	if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");
	new pname[24],housenumber;
	housenumber = GetPlayerHouseID(playerid);
	GetPlayerName(playerid, pname, 24);
	if (strcmp(hInfo[housenumber][Name],pname,false)) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
	new string[512] = "Jokia";
	for(new ix, j = sizeof(RADIO_PLUGIN); ix < j; ix++)
	{
		format(string,sizeof(string),"%s\n%s",string,RADIO_PLUGIN[ix][RADIO_NAME]);
	}
	ShowPlayerDialog(playerid,9758,DIALOG_STYLE_LIST,"Radija",string,"Rinktis","Isjungti");
	return 1;
}
CMD:sodinti(playerid,params[])
{
    if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");
	new str1[50],pname[24],housenumber;
	housenumber = GetPlayerHouseID(playerid);
	GetPlayerName(playerid, pname, 24);
	format(str1, sizeof(str1), "Houses/houseid%d", housenumber);

	if (strcmp(hInfo[housenumber][Name],pname,false)) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
	new moneys;
	if(sscanf(params,"d",moneys)){SendInfoMessage(playerid,"/sodinti [kiek]");  return 1;}


	if(moneys <= 0){SendInfoMessage(playerid,"Noredami pasodinti krumelius rasykite /sodinti [kiek]");  return 1;}
	if(playerDB[playerid][seklos] < moneys){SendInfoMessage(playerid,"Deja, bet tiek jus neturite...");  return 1;}
	if(hInfo[GetPlayerHouseID(playerid)][krumeliai] > 0){SendInfoMessage(playerid,"Negalite sodinti daugiau krumeliu! pirma pasalinkite senuosius! /israuti");  return 1;}
	if(moneys > 10){SendInfoMessage(playerid,"Viename name galite auginti ne daugiau kaip 10 krumeliu vienu metu!");  return 1;}
	if(hInfo[GetPlayerHouseID(playerid)][daugiabutis] && moneys > 3) return SendInfoMessage(playerid,"Daugiabutyje galite auginti tik iki 3 krumeliu!");
	hInfo[GetPlayerHouseID(playerid)][krumeliai] = moneys;
	playerDB[playerid][seklos] -= moneys;
	hInfo[GetPlayerHouseID(playerid)][dregme] = 100;
	hInfo[GetPlayerHouseID(playerid)][bukle] = 100;
	hInfo[GetPlayerHouseID(playerid)][amzius] = 0;
	new msg[128];
	format(msg, 128, "Pasodinote %i krumeliu Kanapiu (zoles)", moneys);
	SendInfoMessage(playerid,msg);
	return 1;
}
CMD:laistyti(playerid,params[])
{
	#pragma unused params
	if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");
	new pname[24],housenumber;
	housenumber = GetPlayerHouseID(playerid);
	GetPlayerName(playerid, pname, 24);

	if (strcmp(hInfo[housenumber][Name],pname,false)) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
	if(hInfo[GetPlayerHouseID(playerid)][krumeliai] == 0){SendInfoMessage(playerid,"Nera ka laistyti! :(");  return 1;}
	hInfo[GetPlayerHouseID(playerid)][dregme] += 20;
	new msg[128];
	format(msg, 128, "Palaistete kanapes! Dregme: %i proc.", hInfo[GetPlayerHouseID(playerid)][dregme]);
	SendInfoMessage(playerid,msg);
	return 1;
}
CMD:israuti(playerid,params[])
{
	#pragma unused params
	if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");
	new pname[24],housenumber;
	housenumber = GetPlayerHouseID(playerid);
	GetPlayerName(playerid, pname, 24);

	if (strcmp(hInfo[housenumber][Name],pname,false)) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
	if(hInfo[GetPlayerHouseID(playerid)][krumeliai] == 0){SendInfoMessage(playerid,"Nera ka rauti! :(");  return 1;}
	hInfo[GetPlayerHouseID(playerid)][krumeliai] = 0;
	SendInfoMessage(playerid,"Isrovete kanapes!!! :O");
	SavePlayerData(playerid, false);
	return 1;
}
CMD:derlius(playerid,params[])
{
	#pragma unused params
	if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");
	new pname[24],housenumber;
	housenumber = GetPlayerHouseID(playerid);
	GetPlayerName(playerid, pname, 24);

	if (strcmp(hInfo[housenumber][Name],pname,false)) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
	if(hInfo[GetPlayerHouseID(playerid)][krumeliai] == 0){SendInfoMessage(playerid,"Deja, jus neauginate kanapiu.");  return 1;}
	if(hInfo[GetPlayerHouseID(playerid)][amzius] < 168){SendInfoMessage(playerid,"Dar per anksti imti derliu!");  return 1;}
	new derlius, msg[128];
	derlius = floatround((hInfo[GetPlayerHouseID(playerid)][bukle] * hInfo[GetPlayerHouseID(playerid)][krumeliai]) / 100, floatround_floor);
	format(msg, 128, "* Nuemete derliu! Is %i krumeliu gavote: %i gramu zoles! Sekmes vartojant! :D", hInfo[GetPlayerHouseID(playerid)][krumeliai], derlius);
	SendClientMessage(playerid, COLOR_WHITE, msg);
	playerDB[playerid][zole] += derlius;
	ProcessAchievement(playerid, 128);
	hInfo[GetPlayerHouseID(playerid)][krumeliai] = 0;
	SavePlayerData(playerid, false);
	return 1;
}

CMD:vinfo(playerid,params[])
{
		#pragma unused params
		SendClientMessage(playerid,YELLOW,"*=====================VIP======================");
		SendClientMessage(playerid,GREEN,"VIP nariai gali:");
		SendClientMessage(playerid,GREEN,"* raðyti vieðai (/vchat [tekstas]);");
		SendClientMessage(playerid,GREEN,"* kickinti þaidëjus uþ taisykliø prasiþengimus (/vkick [vardas] [prieþastis]);");
		SendClientMessage(playerid,GREEN,"* pradëti skaièiavimà (/start);");
		SendClientMessage(playerid,GREEN,"* gauti ginklø uþ 300€ (/vginklai);");
		SendClientMessage(playerid,GREEN,"* gauti galimybæ pakeisti þaidëjo iðvaizdà (/vskin /gskin);");
		SendClientMessage(playerid,GREEN,"* uþsidëti ðarvus (/varmour).");
		SendClientMessage(playerid,RED,"* VIP narystës kaina mënesiui - 30 kreditø.");
		SendClientMessage(playerid,RED,"* Uþsisakyti VIP galite paraðæ /kreditai.");
		SendClientMessage(playerid,RED,"* Nusizengus VIP taisyklems jûs gausite ban arba prarasite VIP! Bûtinai su jomis susipaþinkite mûsø tinklapye www.Lsgyvenimas.lt");
		return 1;
}
CMD:vipinfo(playerid,params[])
{
		//#pragma unused params
		return cmd_vinfo(playerid,params);
}
CMD:bai(playerid,params[])
{
		#pragma unused params
		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USECELLPHONE)
		{
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
			RemovePlayerAttachedObject(playerid,TEL_SLOT);
		}
        PlayerPlaySound(playerid, 1186, 0.0, 0.0, 0.0); // Isjunge muzika
		if(playerDB[playerid][skambutis]!= -1)
		{
			PlaySound(playerid,45400);
			SendInfoMessage(playerid,"Pokalbis baigtas.");
			//PlayerPlaySound(playerid, 1186, 0.0, 0.0, 0.0); // Isjunge muzika
			new pokalbis = playerDB[playerid][skambutis];
			playerDB[pokalbis][skambutis]=-1;
			SendInfoMessage(pokalbis,"Pokalbis baigtas.");
			PlaySound(pokalbis,45400);
			//PlayerPlaySound(pokalbis, 1186, 0.0, 0.0, 0.0); // Isjunge muzika
			if(GetPlayerSpecialAction(pokalbis) == SPECIAL_ACTION_USECELLPHONE)
			{
				SetPlayerSpecialAction(pokalbis,SPECIAL_ACTION_STOPUSECELLPHONE);
				RemovePlayerAttachedObject(pokalbis,TEL_SLOT);
			}
			playerDB[playerid][skambutis]=-1;
		}
		return 1;
}
CMD:vginklai(playerid,params[])
{
		#pragma unused params
		if(!playerDB[playerid][vip]){ return SendInfoMessage(playerid,"Si komanda tik vipam!"); }
		if(playerDB[playerid][ikalintas]){ return SendInfoMessage(playerid,"Kalejime niekas ginklu neduos!"); }

		if(GetPlayerMoneyA(playerid) < COST_VGINKLAI)
		{
			SendInfoMessage(playerid,"Vip ginklai kainuoja "#COST_VGINKLAI"EUR , jus tiek neturite.");
			return 1;
		}
		if(playerDB[playerid][vgun]==false){ return SendInfoMessage(playerid,"Atleiskite, bet ginklus galite gauti tik kas 2 min."); }
		//ResetPlayerWeapons(playerid);
		GivePlayerWeaponEx(playerid,1,1);
		GivePlayerWeaponEx(playerid,5,1); //beisbolke
		GivePlayerWeaponEx(playerid,22,100000); //pistule
		GivePlayerWeaponEx(playerid,33,100000); //rifle
		GivePlayerWeaponEx(playerid,25,100000); //pompa
		GivePlayerMoneyA(playerid,-COST_VGINKLAI);
		SendInfoMessage(playerid,"VIP Ginklus naudokite ismintingai !");
		playerDB[playerid][vgun]=false;
		ProcessAchievement(playerid, 121);
		SetTimerEx("laikasss",120000,0,"i",playerid);
		LogA(playerid,"Vginklai");
		return 1;
}

CMD:varmour(playerid,params[])
{
	#pragma unused params
	if(!playerDB[playerid][vip]){ return SendInfoMessage(playerid,"Si komanda tik vipam!"); }
	new msg[128];
	new left = (VarmourTaimas[playerid] - GetTickCount())/1000;
	if(left > 0)
	{
		if(left >= 60)
			format(msg,128,"Atleiskite, bet sarvus galite gauti tik kas 2 min. Liko: %dm%02ds",left/60, left % 60);
		else
			format(msg,128,"Atleiskite, bet sarvus galite gauti tik kas 2 min. Liko: %is",left);
		return SendInfoMessage(playerid,msg); 
	}
	new keys,lr,ud;
	GetPlayerKeys(playerid,keys,ud,lr);
	if(keys & KEY_HANDBRAKE || keys & KEY_FIRE || playerDB[playerid][ant] || playerDB[playerid][suristas])
		return SendInfoMessage(playerid,"Dabar sarvu uzsideti negali");
	SetPlayerArmour(playerid,100);
	SendInfoMessage(playerid,"Uzsidejote sarvus!");
	VarmourTaimas[playerid] = GetTickCount() + 120*1000;
	LogA(playerid,"Varmour");
	return 1;
}
CMD:zole(playerid,params[])
{
	return SendInfoMessage(playerid,"Naudok /pusti!");
}
CMD:variklis(playerid,params[])
{
	return cmd_auto(playerid,params);
}

CMD:pusti(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][zole] <= 0){ SendInfoMessage(playerid,"Nebeturite ka pusti! Uzsiauginkite zoles namuose arba pirkite is kitu!"); return 1;}
	if(playerDB[playerid][psratasvydis] || playerDB[playerid][ant] || playerDB[playerid][suristas]) return SendInfoMessage(playerid,"Cia negali vartot narkotiku!");
	new Float:giv, girtas;
	girtas=GetPlayerDrunkLevel(playerid);
	GetPlayerHealth(playerid, giv);
	new left = (NarkTaimas[playerid] - GetTickCount())/1000;
	if(playerDB[playerid][parukes] || playerDB[playerid][ruko] || left >= 0 || girtas >= 3000){ SendInfoMessage(playerid,"Jus jau per daug apsineses. Dar viena doze galetu jus pribaigti, todel nusprendziate neberukyti"); return 1;}
	SendInfoMessage(playerid,"Susisukate kasiaka ir megaujates stipriu Kanapiu poveikiu.");
	SendClientMessage(playerid,COLOR,"Spauskite MOUSE1, kad Traukti arba ENTER, kad ismesti.");
	playerDB[playerid][zole] -- ;
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_SMOKE_CIGGY);
	playerDB[playerid][pucia]=true;
	LogA(playerid,"Pucia");
	ProcessAchievement(playerid,49);
	ProcessAchievement(playerid, 126);
	Invul[playerid]=true;
	SetTimerEx("NoInvul",1000,false,"i",playerid);
	return 1;

}

CMD:amfa(playerid,params[])
{
	if(playerDB[playerid][amfetaminas]<1)
	{
		SendInfoMessage(playerid,"Neturite narkotiku");
		return 1;
	}
	if(playerDB[playerid][psratasvydis]) return SendInfoMessage(playerid,"Cia negali vartot narkotiku!");
	new keys,lr,ud;
	GetPlayerKeys(playerid,keys,ud,lr);
	if(keys & KEY_HANDBRAKE || keys & KEY_FIRE || playerDB[playerid][ant] || playerDB[playerid][suristas])
		return SendInfoMessage(playerid,"Dabar narkotiku vartoti negali");
	new girtas;
	girtas=GetPlayerDrunkLevel(playerid);
	new msg[128];
	new left = (NarkTaimas[playerid] - GetTickCount())/1000;	

	if(girtas >= 5000)
	{ 
		return SendInfoMessage(playerid,"Tu jau apsineses!");
	}
	else if(left > 0)
	{
		if(left >= 60)
			format(msg,128,"Tu jau apsineses! Palauk %dm%02ds",left/60, left % 60);
		else
			format(msg,128,"Tu jau apsineses! Palauk %is",left);
		return SendInfoMessage(playerid,msg); 
	}
	ApplyAnimation(playerid,"PED","WALK_DRUNK",4.1,1,1,0,0,0);
	playerDB[playerid][amfetaminas]-=1;
	new Float:giv;
	GetPlayerHealth(playerid,giv);
	if(giv+100.0 <= 150) SetPlayerHealth(playerid, giv + 100.0);
	else SetPlayerHealth(playerid, 150.0);
	GetPlayerArmour(playerid,giv);
	if(giv+100.0 <= 150) SetPlayerArmour(playerid, giv + 100.0);
	else SetPlayerArmour(playerid, 150.0);
	Invul[playerid]=true;
	SetTimerEx("NoInvul",1000,false,"i",playerid);
	SendInfoMessage(playerid,"Susniojai amfetamina!~n~Gavai 120 HP ir 120 Armour");
	ProcessAchievement(playerid, 126);
	//SendInfoMessage(playerid,"Gavote 200HP ir 200 Armour");
	if(playerDB[playerid][narko][2])
		SetPlayerDrunkLevel(playerid, girtas+4000);
	else
		SetPlayerDrunkLevel(playerid, girtas+8000);
	LogA(playerid,"Amfa");
	MLog(playerid,"Amfa","i",1);
	CheckNarkomanas(playerid,2,1);
	//playerDB[playerid][narkomanas]=true;
	NarkTaimas[playerid] = GetTickCount() + 120*1000;
	//SetTimerEx("NeNarkomanas", 120000, false, "i", playerid);
	return 1;

}

CMD:narkotikai(playerid,params[])
{
	#pragma unused params
	SendClientMessage(playerid,0xF50AF5FF,"* Narkotiku komandos:");
	SendClientMessage(playerid,0x9E5FA0FF,"* /amfa /ratai /lsd /pusti /nparduoti /adr");
	return 1;
}

CMD:imti(playerid,params[])
{
		#pragma unused params
    	new spec = playerDB[playerid][specialybe];
		new Float:Coo[3],name[24],msg[128];
		if(playerDB[playerid][ant] || playerDB[playerid][suristas])
			return SendInfoMessage(playerid, "Surakintas/suristas negali imti iskvietimu!");
		if(GetPlayerState(playerid)==PLAYER_STATE_DRIVER)
		{
			new model = GetVehicleModel(GetPlayerVehicleID(playerid));
			switch(model)
			{
				case HOTDOG,423,478,448:
				{
					if(kvieciafood == -1) return SendInfoMessage(playerid,"Siuo metu greito maisto iskvietimu nera.");
					if(!IsPlayerConnected(kvieciafood))
					{
						SendClientMessage(playerid,Orange," * Zaidejas atsijunge.");
						kvieciafood = -1;
						return 1;
					}
					GetPlayerPos(kvieciafood,Coo[0],Coo[1],Coo[2]);
					GetPlayerName(kvieciafood,name,24);
					SetPlayerCheckpoint(playerid,Coo[0],Coo[1],Coo[2],5);
					format(msg,sizeof(msg)," %s dabartinë vieta rodoma radare. Sekimà gali iðjungti naudodamas /sekimas",name);
					SendClientMessage(playerid,RED,msg);
					format(msg,sizeof(msg)," %s prieme jusu iskvietima(%s)!",ReturnName(playerid),JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
					SendClientMessage(kvieciafood,COLOR,msg);
					format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
					
					
					SetPVarInt(kvieciafood, "PriemeKlienta", playerid);
					SetPVarInt(playerid, "PriemeIskvietima", kvieciafood);
					MLog(playerid,"Prieme iskvietima", "s", "Maistas");

					foreach (Player, i)
					{
						if(GetPlayerState(i)==PLAYER_STATE_DRIVER)
						{
							new modelis = GetVehicleModel(GetPlayerVehicleID(i));
							switch(modelis)
							{
								case HOTDOG,423,478,448:
								{
									SendClientMessage(i,0xE3B92430,msg);
								}
							}
						}
					}
					kvieciafood=-1;
					return 1;
				}
			}
		}
		if(spec == 2 || spec == 93)
		{
			if(kvieciamedikus == -1) return SendInfoMessage(playerid,"Siuo metu iskvietimu nera.");
			else if (kvieciamedikus == -100)
			{
				StartMedikuMission(playerid);
				return 1;
			}
			if(!IsPlayerConnected(kvieciamedikus))
			{
				SendInfoMessage(playerid,"Zaidejas atsijunge.");
				kvieciamedikus = -1;
				return 1;
			}
			GetPlayerPos(kvieciamedikus,Coo[0],Coo[1],Coo[2]);
			GetPlayerName(kvieciamedikus,name,24);
			SetPlayerCheckpoint(playerid,Coo[0],Coo[1],Coo[2],5);
			format(msg,sizeof(msg)," %s dabartinë vieta rodoma radare. Sekimà gali iðjungti naudodamas /sekimas",name);
			SendClientMessage(playerid,RED,msg);
			format(msg,sizeof(msg)," %s prieme jusu iskvietima(%s)!",ReturnName(playerid),JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
			SendClientMessage(kvieciamedikus,COLOR,msg);
			format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
			SendMessageToMedics(RED,msg);
			SetPVarInt(kvieciamedikus, "PriemeKlienta", playerid);
			SetPVarInt(playerid, "PriemeIskvietima", kvieciamedikus);
			MLog(playerid,"Prieme iskvietima", "s", "Medikai");
			kvieciamedikus=-1;
			
			return 1;
		}
		else if(spec == 30)// kriminalistas
		{
			if(kvieciakrimi == -1) return SendInfoMessage(playerid,"Iskvietimu nera!");
			if(kvieciakrimi == playerid) return SendInfoMessage(playerid,"Juk tai jus padarete si nusikaltima!");
			if(!galikeist[playerid]) return SendInfoMessage(playerid,"Dar nepraejo 5 minutes nuo praeito priemimo!");
			galikeist[playerid]=false;
			SetTimerEx("GaliKeist",300000,0,"i",playerid); 
			SetPlayerCheckpoint(playerid,kvieciakrimic[0],kvieciakrimic[1],kvieciakrimic[2],15);
			format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
			foreach(Player,i) if(playerDB[i][specialybe] == 30) SendClientMessage(i, -1,msg);
			kvieciakrimi = -1;
			return 1;
		}
		else if(spec == 3 || spec == 20 || spec == 39)
		{
			if(spec == 20)
			{
				if(kviecialimo != -1)
				{
					if(!IsPlayerConnected(kviecialimo))
					{
						SendClientMessage(playerid,Orange," * Zaidejas atsijunge.");
						kviecialimo = -1;
						return 1;
					}
					GetPlayerPos(kviecialimo,Coo[0],Coo[1],Coo[2]);
					GetPlayerName(kviecialimo,name,24);
					SetPlayerCheckpoint(playerid,Coo[0],Coo[1],Coo[2],5);
					format(msg,sizeof(msg)," %s dabartinë vieta rodoma radare. Sekimà gali iðjungti naudodamas /sekimas",name);
					SendClientMessage(playerid,RED,msg);
					format(msg,sizeof(msg)," %s prieme jusu iskvietima(%s)!",ReturnName(playerid),JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
					SendClientMessage(kviecialimo,COLOR,msg);
					kviecialimo=-1;
					format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
					SetPVarInt(kviecialimo, "PriemeKlienta", playerid);
					SetPVarInt(playerid, "PriemeIskvietima", kviecialimo);
					MLog(playerid,"Prieme iskvietima", "s", "Limuzinai");
					SendMessageToTransportas(RED,msg);
					return 1;
				}
			}
			if(kvieciataxi == -1) return SendInfoMessage(playerid,"Siuo metu iskvietimu nera.");
			if(!IsPlayerConnected(kvieciataxi))
			{
				SendClientMessage(playerid,Orange," * Zaidejas atsijunge.");
				kvieciataxi = -1;
				return 1;
			}
			GetPlayerPos(kvieciataxi,Coo[0],Coo[1],Coo[2]);
			GetPlayerName(kvieciataxi,name,24);
			SetPlayerCheckpoint(playerid,Coo[0],Coo[1],Coo[2],5);
			format(msg,sizeof(msg)," %s dabartinë vieta rodoma radare. Sekimà gali iðjungti naudodamas /sekimas",name);
			SendClientMessage(playerid,RED,msg);
			format(msg,sizeof(msg)," %s prieme jusu iskvietima(%s)!",ReturnName(playerid),JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
			SendClientMessage(kvieciataxi,COLOR,msg);
			format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
			SendMessageToTransportas(RED,msg);
			SetPVarInt(kvieciataxi, "PriemeKlienta", playerid);
			SetPVarInt(playerid, "PriemeIskvietima", kvieciataxi);
			MLog(playerid,"Prieme iskvietima", "s", "Taksi");
			kvieciataxi=-1;
			return 1;
		}
		
		else if(spec == 66)
		{
			if(kvieciagais == -1) return SendInfoMessage(playerid,"Siuo metu iskvietimu nera.");
			else if(kvieciagais == -100)
			{
				if(!FireDB[inProgress] && !MiskoGaisrai[inProgress])
				{
					kvieciagais=-1;
					SendClientMessage(playerid,RED," * Gaisras jau uzgesintas!");
				}
				else if(FireDB[inProgress] && FireDB[fPlace] ==0)
				{
					new houseid = FireDB[fNumber];
					if(hInfo[houseid][daugiabutis])
					{
						format(msg,sizeof(msg)," * Namas Nr.%i daugiabutyje Nr.%i",houseid,hInfo[houseid][daugiabutis]);
						SendClientMessage(playerid,-1,msg);
						SendInfoMessage(playerid,"Iskvietimas priimtas!");
						SetPlayerCheckpoint(playerid,Daugiabuciai[hInfo[houseid][daugiabutis]-1][dX],Daugiabuciai[hInfo[houseid][daugiabutis]-1][dY],Daugiabuciai[hInfo[houseid][daugiabutis]-1][dZ],20.0);
						format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
						SendMessageToGaisras(RED,msg);
						return 1;
					}
					else
					{
						SendInfoMessage(playerid,"Iskvietimas priimtas!");
						SetPlayerCheckpoint(playerid,hInfo[houseid][iconx],hInfo[houseid][icony],hInfo[houseid][iconz],20.0);
						format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
						SendMessageToGaisras(RED,msg);
						return 1;
					}
				}
				else if(FireDB[inProgress] && FireDB[fPlace] == 1)
				{
					new houseid = FireDB[fNumber];
					if(hInfo[houseid][daugiabutis])
					{
						format(msg,sizeof(msg)," * Namas Nr.%i daugiabutyje Nr.%i",houseid,hInfo[houseid][daugiabutis]);
						SendClientMessage(playerid,-1,msg);
						SendInfoMessage(playerid,"Iskvietimas priimtas!");
						SetPlayerCheckpoint(playerid,Daugiabuciai[hInfo[houseid][daugiabutis]-1][dX],Daugiabuciai[hInfo[houseid][daugiabutis]-1][dY],Daugiabuciai[hInfo[houseid][daugiabutis]-1][dZ],20.0);
						format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
						SendMessageToGaisras(RED,msg);
						return 1;
					}
					else
					{
						SendInfoMessage(playerid,"Iskvietimas priimtas!");
						SetPlayerCheckpoint(playerid,hInfo[houseid][iconx],hInfo[houseid][icony],hInfo[houseid][iconz],20.0);
						format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
						SendMessageToGaisras(RED,msg);
						return 1;
					}
				}
				else if(FireDB[inProgress] && FireDB[fPlace] == 2)
				{
					new world = FireDB[fNumber];
					SetPlayerCheckpoint(playerid,BusinessInfo[world][bEnterX],BusinessInfo[world][bEnterY],BusinessInfo[world][bEnterZ],20.0);
					SendInfoMessage(playerid,"Iskvietimas priimtas!");
					format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
					SendMessageToGaisras(RED,msg);
					return 1;
				}
				else if(FireDB[inProgress] && FireDB[fPlace] == 3)
				{
					new world = FireDB[fNumber];
					SetPlayerCheckpoint(playerid,Daugiabuciai[world][dX],Daugiabuciai[world][dY],Daugiabuciai[world][dZ],20.0);
					SendInfoMessage(playerid,"Iskvietimas priimtas!");
					format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
					SendMessageToGaisras(RED,msg);
					return 1;
				}
				else if(MiskoGaisrai[inProgress]) 
				{
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 563) 
					{
						SendClientMessage(playerid,RED," * Misko gaisrui uzgesinti reikia sraigtasparnio!");//, color, const message[])
						return 1;
					}
					SetPlayerCheckpoint(playerid,MiskoGaisrai[fCenter][0],MiskoGaisrai[fCenter][1],MiskoGaisrai[fCenter][2],20.0);
					SendInfoMessage(playerid,"Iskvietimas priimtas!");
					format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
					SendMessageToGaisras(RED,msg);
					return 1;
				}
				/*	inProgress=false,
					Float:fCoo[3],
					fVW,
					fInt,
					fHealth,
					fObj,
					fPlace, // 0 house, 1 house outside, 2 verslas, 3 daugiabutis
					fNumber*/
			}
			if(!IsPlayerConnected(kvieciagais))
			{
				SendClientMessage(playerid,Orange," * Zaidejas atsijunge.");
				kvieciagais = -1;
				return 1;
			}
			GetPlayerPos(kvieciagais,Coo[0],Coo[1],Coo[2]);
			GetPlayerName(kvieciagais,name,24);
			SetPlayerCheckpoint(playerid,Coo[0],Coo[1],Coo[2],5);
			format(msg,sizeof(msg)," %s dabartinë vieta rodoma radare. Sekimà gali iðjungti naudodamas /sekimas",name);
			SendClientMessage(playerid,RED,msg);
			format(msg,sizeof(msg)," %s prieme jusu iskvietima(%s)!",ReturnName(playerid),JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
			SendClientMessage(kvieciagais,COLOR,msg);
			format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
			SendMessageToGaisras(RED,msg);
			SetPVarInt(kvieciagais, "PriemeKlienta", playerid);
			SetPVarInt(playerid, "PriemeIskvietima", kvieciagais);
			MLog(playerid,"Prieme iskvietima", "s", "Gaisrine");
			kvieciagais=-1;
			return 1;
		}
		else if(spec == 6)
		{
			if(kvieciamech == -1) return SendInfoMessage(playerid,"Siuo metu iskvietimu nera.");
			if(!IsPlayerConnected(kvieciamech))
			{
				SendClientMessage(playerid,Orange," * Zaidejas atsijunge.");
				kvieciamech = -1;
				return 1;
			}
			GetPlayerPos(kvieciamech,Coo[0],Coo[1],Coo[2]);
			GetPlayerName(kvieciamech,name,24);
			SetPlayerCheckpoint(playerid,Coo[0],Coo[1],Coo[2],5);
			format(msg,sizeof(msg)," %s dabartinë vieta rodoma radare. Sekimà gali iðjungti naudodamas /sekimas",name);
			SendClientMessage(playerid,RED,msg);
			format(msg,sizeof(msg)," %s prieme jusu iskvietima(%s)!",ReturnName(playerid),JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
			SendClientMessage(kvieciamech,COLOR,msg);
			format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
			SendMessageToAutospecai(RED,msg);
			SetPVarInt(kvieciamech, "PriemeKlienta", playerid);
			SetPVarInt(playerid, "PriemeIskvietima", kvieciamech);
			MLog(playerid,"Prieme iskvietima", "s", "Mechanikai");
			kvieciamech=-1;
			return 1;
		}
		else if(spec == 80 || spec == 81 || spec == 83 || spec == 84 || spec == 82)
		{
			if(kvieciapd == -1) return SendInfoMessage(playerid,"Siuo metu iskvietimu nera.");
			if(!IsPlayerConnected(kvieciapd))
			{
				SendClientMessage(playerid,Orange," * Zaidejas atsijunge.");
				kvieciapd = -1;
				return 1;
			}
			//GetPlayerPos(kvieciapd,Coo[0],Coo[1],Coo[2]);
			GetPlayerName(kvieciapd,name,24);
			//SetPlayerCheckpoint(playerid,Coo[0],Coo[1],Coo[2],5);
			SetPlayerCheckpoint(playerid,kvieciapdcord[0],kvieciapdcord[1],kvieciapdcord[2],15);
			format(msg,sizeof(msg)," %s dabartinë vieta rodoma radare. Sekimà gali iðjungti naudodamas /sekimas",name);
			SendClientMessage(playerid,RED,msg);
			format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
			SendMessageToTeisesauga(RED,msg);
			if(playerDB[kvieciapd][specialybe]!=58)
			{
				format(msg,sizeof(msg)," %s prieme jusu iskvietima(%s)!",ReturnName(playerid),JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
				SendClientMessage(kvieciapd,COLOR,msg);
				SetPVarInt(kvieciapd, "PriemeKlienta", playerid);
				SetPVarInt(playerid, "PriemeIskvietima", kvieciapd);
				MLog(playerid,"Prieme iskvietima", "s", "Policija");
			}
			
			//kvieciapd=-1;
			return 1;
		}
		else if(spec == 32)
		{
			if(kvieciadyl == -1) return SendInfoMessage(playerid,"Siuo metu iskvietimu nera.");
			if(!IsPlayerConnected(kvieciadyl))
			{
				SendClientMessage(playerid,Orange," * Zaidejas atsijunge.");
				kvieciadyl = -1;
				return 1;
			}
			GetPlayerPos(kvieciadyl,Coo[0],Coo[1],Coo[2]);
			GetPlayerName(kvieciadyl,name,24);
			SetPlayerCheckpoint(playerid,Coo[0],Coo[1],Coo[2],5);
			format(msg,sizeof(msg)," %s dabartinë vieta rodoma radare. Sekimà gali iðjungti naudodamas /sekimas",name);
			SendClientMessage(playerid,RED,msg);
			format(msg,sizeof(msg)," %s prieme jusu iskvietima(%s)!",ReturnName(playerid),JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
			SendClientMessage(kvieciadyl,COLOR,msg);
			format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
			SendMessageToDeal(RED,msg);
			SetPVarInt(kvieciadyl, "PriemeKlienta", playerid);
			SetPVarInt(playerid, "PriemeIskvietima", kvieciadyl);
			MLog(playerid,"Prieme iskvietima", "s", "Dyleriai");
			kvieciadyl=-1;
			return 1;
		}
		else if(spec == 50)
		{
			if(kvieciaskelb == -1) return SendInfoMessage(playerid,"Siuo metu iskvietimu nera.");
			if(!IsPlayerConnected(kvieciaskelb))
			{
				SendClientMessage(playerid,Orange," * Zaidejas atsijunge.");
				kvieciaskelb = -1;
				return 1;
			}
			GetPlayerPos(kvieciaskelb,Coo[0],Coo[1],Coo[2]);
			GetPlayerName(kvieciaskelb,name,24);
			SetPlayerCheckpoint(playerid,Coo[0],Coo[1],Coo[2],5);
			format(msg,sizeof(msg)," %s dabartinë vieta rodoma radare. Sekimà gali iðjungti naudodamas /sekimas",name);
			SendClientMessage(playerid,RED,msg);
			format(msg,sizeof(msg)," %s prieme jusu iskvietima(%s)!",ReturnName(playerid),JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
			SendClientMessage(kvieciaskelb,COLOR,msg);
			format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
			SendMessageToValstybe(RED,msg);
			SetPVarInt(kvieciaskelb, "PriemeKlienta", playerid);
			SetPVarInt(playerid, "PriemeIskvietima", kvieciaskelb);
			MLog(playerid,"Prieme iskvietima", "s", "Skelbejai");
			kvieciaskelb=-1;
			return 1;
		}
		else if(spec==15)
		{	
			GetPlayerPos(kvieciaadv,Coo[0],Coo[1],Coo[2]);
			GetPlayerName(kvieciaadv,name,24);
			if(GetPlayerInterior(kvieciaadv) == 0)
			{
				format(msg,sizeof(msg)," %s dabartinë vieta rodoma radare. Sekimà gali iðjungti naudodamas /sekimas",name);
				SendClientMessage(playerid,RED,msg);
				SetPlayerCheckpoint(playerid,Coo[0],Coo[1],Coo[2],5);
				SetPVarInt(kvieciaadv, "PriemeKlienta", playerid);
				SetPVarInt(playerid, "PriemeIskvietima", kvieciaadv);
			}
			else
			{
				format(msg,sizeof(msg)," %s yra mazajame kalejime arba kokiam kitam pastate.",name);
				SendClientMessage(playerid,RED,msg);
			}
			format(msg,sizeof(msg)," %s prieme jusu iskvietima(%s)!",ReturnName(playerid),JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
			SendClientMessage(kvieciaadv,COLOR,msg);
			format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
			MLog(playerid,"Prieme iskvietima", "s", "Advokatai");
			foreach (Player, i)
			{
				if(playerDB[i][specialybe]==15)
				{
					SendClientMessage(i,COLOR,msg);
				}
			}
			return 1;
		}
		else if(spec == 34)
		{
			if(kviecianta == -1) return SendInfoMessage(playerid,"Siuo metu iskvietimu nera.");
			if(!IsPlayerConnected(kviecianta))
			{
				SendClientMessage(playerid,Orange," * Zaidejas atsijunge.");
				kviecianta = -1;
				return 1;
			}
			GetPlayerPos(kviecianta,Coo[0],Coo[1],Coo[2]);
			GetPlayerName(kviecianta ,name,24);
			SetPlayerCheckpoint(playerid,Coo[0],Coo[1],Coo[2],5);
			format(msg,sizeof(msg)," %s dabartinë vieta rodoma radare. Sekimà gali iðjungti naudodamas /sekimas",name);
			SendClientMessage(playerid,RED,msg);
			format(msg,sizeof(msg)," %s prieme jusu iskvietima(%s)!",ReturnName(playerid),JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
			SendClientMessage(kviecianta,COLOR,msg);
			format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
			SendMessageToNTA(RED,msg);
			SetPVarInt(kviecianta, "PriemeKlienta", playerid);
			SetPVarInt(playerid, "PriemeIskvietima", kviecianta);
			MLog(playerid,"Prieme iskvietima", "s", "NTA");
			kviecianta=-1;
			return 1;
		}
		else if(spec == 71)
		{
			if(kvieciabaikerius == -1) return SendInfoMessage(playerid,"Siuo metu iskvietimu nera.");
			if(!IsPlayerConnected(kvieciabaikerius))
			{
				SendClientMessage(playerid,Orange," * Zaidejas atsijunge.");
				kvieciabaikerius = -1;
				return 1;
			}
			GetPlayerPos(kvieciabaikerius,Coo[0],Coo[1],Coo[2]);
			GetPlayerName(kvieciabaikerius ,name,24);
			SetPlayerCheckpoint(playerid,Coo[0],Coo[1],Coo[2],5);
			format(msg,sizeof(msg)," %s dabartinë vieta rodoma radare. Sekimà gali iðjungti naudodamas /sekimas",name);
			SendClientMessage(playerid,RED,msg);
			format(msg,sizeof(msg)," %s prieme jusu iskvietima(%s)!",ReturnName(playerid),JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
			SendClientMessage(kvieciabaikerius,COLOR,msg);
			format(msg,sizeof(msg),"[racija] Operatore: %s prieme iskvietima.",ReturnName(playerid));
			SendMessageToBaikeriai(RED,msg);
			SetPVarInt(kvieciabaikerius, "PriemeKlienta", playerid);
			SetPVarInt(playerid, "PriemeIskvietima", kvieciabaikerius);
			MLog(playerid,"Prieme iskvietima", "s", "Baikeriai");
			kvieciabaikerius=-1;
			return 1;
		}
		SendInfoMessage(playerid,"Ka nori paimti?");
		return 1;

}
CMD:sekimas(playerid,params[])
{
	if(GetPVarInt(playerid, "PriemeIskvietima") != -1 || GetPVarInt(playerid, "PriemeKlienta") != -1)
	{
		PlayerTextDrawHide(playerid,JobText[playerid]);
		SendClientMessage(playerid, -1, " * Iðjungei sekimà!");
		SetPVarInt(playerid, "PriemeKlienta", -1);
		SetPVarInt(playerid, "PriemeIskvietima", -1);
	}
	return 1;
}
CMD:dkomandos(playerid,params[])
{
	#pragma unused params
	SendClientMessage(playerid,0xF50AF5FF,"* Direktoriu komandos:");
	SendClientMessage(playerid,0x9E5FA0FF,"* /priimt /ismest");
	SendClientMessage(playerid,0x9E5FA0FF,"* /bendradarbiai /dpadeti - padeti kysi is nelegalaus darbo");
	SendClientMessage(playerid,0x9E5FA0FF,"* /darbuotojai /leidimas /manodarbai");
	SendClientMessage(playerid,0x9E5FA0FF,"* /dchat ( naudoti tik pranesinet atrankas ir algas!!!)");
	SendClientMessage(playerid,0x9E5FA0FF,"* /d - chatas tarp direktoriu.");
	
	return 1;

}
CMD:fps(playerid, params[]) 
{ 
    //SendClientMessageEx(playerid, COLOR_LIME, "If you think you cannot use /fps , Please /resetfps to fix it up. Then use /fps again."); //Depend on you that you will use it or not. 
    if(FPS[playerid] == false) // You can use FPS[playerid] == 0) 0=False. 
    { 
        FPS[playerid] = true;//Same as before, You can use 1 tho. 
        StartFPS(playerid);//Called that StartFPS stock to use FPS. 
		SendInfoMessage(playerid,"~g~Ijungei FPS mod.");
    } 
    else if(FPS[playerid] == true)// Same as before, you can use 1 here. 
    { 
        FPS[playerid] = false;// You can use 0 if you don't want to false. 
        StopFPS(playerid);//Called Stock StopFPS 
		SendInfoMessage(playerid,"~r~Isjungei FPS mod.");
    } 
    return 1; 
} 


CMD:bendradarbiai(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==0) return SendClientMessage(playerid,COLOR," * Bedarbiai neturi bendradarbiu ;)");
	new msg[256],x;
	SendClientMessage(playerid,COLOR,"Jusu bendradarbiai:");
	new lol=-1,lol2=-1,lol3=-1,lol4=-1,lol5=-1,spec = playerDB[playerid][specialybe];
	if(spec == 2 || spec == 93) { lol=2; lol2=93; }
	else if(spec == 3 || spec == 20 || spec == 39){ lol = 3; lol2 = 20; lol3 = 39;}
	else if(spec == 41 || spec == 44){ lol = 41; lol2 = 44;}
	else if(spec == 6 || spec == 28){ lol = 6; lol2 = 28;}
	else if(spec == 70 || spec == 73 || spec == 72){ lol = 70; lol2 = 73; lol3 = 72;}
	else if(spec == 80 || spec == 81 || spec == 83 || spec == 84 || spec == 82){ lol = 80; lol2 = 81; lol3 = 83; lol4 = 84; lol5=82;}
	else if(spec == 31 || spec == 32){ lol = 31; lol2=32;}
	else { lol=spec; }
	new tickas = GetTickCount();
	foreach(Player, i)
	{
		if((playerDB[i][specialybe] == lol || playerDB[i][specialybe] == lol2 || playerDB[i][specialybe] == lol3 || playerDB[i][specialybe] == lol4 || playerDB[i][specialybe] == lol5) && !playerDB[i][invisible])
		{
			x++;
			if(playerDB[i][plead]>0)
				format(msg,256,"%i. Dir. %s pradirbo %imin.",x,ReturnName(i),playerDB[i][pradirbo]);
			else
				format(msg,256,"%i. %s pradirbo %imin.",x,ReturnName(i),playerDB[i][pradirbo]);
			if(IsPlayerAfkEx(i,tickas))
				format(msg,256,"%s [AFK]",msg);
			if(i == playerid) SendClientMessage(playerid,RED,msg);
			else SendClientMessage(playerid,COLOR,msg);
		}
	}
	// --- Fake workers (solo feature) ---
	new myPlead = playerDB[playerid][plead];
	if(myPlead > 0)
	{
		new cidx = GetCompanyIdx(myPlead);
		if(cidx != -1)
		{
			new pIdx = myPlead - 1;
			new firmFund = (pIdx >= 0 && pIdx < 100) ? pelnas[pIdx] : 0;
			new TotalMins;
			for(new w = 0; w < MAX_FAKE_WORKERS_PER_CO; w++)
				if(g_FakeWorkerActive[cidx][w] && g_FakeWorkerMins[cidx][w] >= 100)
					TotalMins += g_FakeWorkerMins[cidx][w];
			if(TotalMins < 1) TotalMins = 1;
			new Float:Kf = float(firmFund) / float(TotalMins);
			SendClientMessage(playerid,COLOR," --- Virtualus darbuotojai ---");
			for(new w = 0; w < MAX_FAKE_WORKERS_PER_CO; w++)
			{
				if(!g_FakeWorkerActive[cidx][w]) continue;
				if(g_FakeWorkerMins[cidx][w] < 100) continue;
				new estAlga = floatround(Kf * g_FakeWorkerMins[cidx][w]);
				x++;
				format(msg,256,"%i. %s - %d min. (~%d EUR)",x,g_FakeWorkerName[cidx][w],g_FakeWorkerMins[cidx][w],estAlga);
				SendClientMessage(playerid,0xAAAAAAAA,msg);
			}
		}
	}
	return 1;
}
CMD:gnariai(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][pgang]==-1) return SendInfoMessage(playerid,"Tu neturi gaujos!");
	new msg[50],x;

	SendClientMessage(playerid,COLOR," * Gaujos nariai:");

	foreach(Player, i)
	{
	    if(playerDB[i][pgang] == playerDB[playerid][pgang] && i != playerid && !playerDB[i][invisible])
	    {
	        x++;
	        format(msg,50,"%i. %s",x,ReturnName(i));
			SendClientMessage(playerid,COLOR,msg);
	    }
	}
	return 1;
}
CMD:eiti(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][mire] && playerDB[playerid][pospawn])
	{
		KillTimer(Gydosi[playerid]);
		Gydosi[playerid]=-1;
		playerDB[playerid][mire]=false;
		if(!playerDB[playerid][ant]) TogglePlayerControllable(playerid,true);
		ClearAnimations(playerid, 1);
		SendInfoMessage(playerid,"Gero kelio!");
		return 1;
	}
	else SendInfoMessage(playerid,"Si komanda naudojama ligoniams.");
	return 1;

}



CMD:direktoriai(playerid,params[])
{
	#pragma unused params
	new msg[80],x;
	new vardas[MAX_PLAYER_NAME];
	SendClientMessage(playerid,COLOR,"Prisijungæ direktoriai:");
	foreach (Player, i)
	{
		if(!playerDB[i][invisible] && Pareigos(i,"Dyrikai") && !Pareigos(i,"Admin") && !Pareigos(i,"Admin2"))
		{
			if(playerDB[i][lytis]==1)
			{
				x++;
				GetPlayerName(i,vardas,MAX_PLAYER_NAME);
				format(msg,80,"%i. %s - Meras.",x,vardas);
				SendClientMessage(playerid,YELLOW,msg);
			}
			else
			{
				x++;
				GetPlayerName(i,vardas,MAX_PLAYER_NAME);
				format(msg,80,"%i. %s - Mere.",x,vardas);
				SendClientMessage(playerid,YELLOW,msg);
			}
		}
		else if(playerDB[i][plead] != 0 && !playerDB[i][invisible])
		{
			x++;
			GetPlayerName(i,vardas,MAX_PLAYER_NAME);
			new dyrikas = playerDB[i][plead];
			new kieno[80];
			if(dyrikas == 2) kieno = "Medikø";
			else if(dyrikas == 3) kieno = "Transporto";
			//else if(dyrikas == 4) kieno = "Apsauginiu";
			else if(dyrikas == 5) kieno = "Kroviniø transporto";
			else if(dyrikas == 6) kieno = "Mechanikø";
			else if(dyrikas == 66) kieno = "Gaisrininkø";
			else if(dyrikas == 70) kieno = "Autoklubo";
			else if(dyrikas == 80) kieno = "Teisësaugos";
			else if(dyrikas == 50) kieno = "Skelbejø";
			else if(dyrikas == 98) kieno = "Baikeriø";
			else if(dyrikas == 90) kieno = "Dealeriø";
			else if(dyrikas == 58) kieno = "Vagiø";
			else if(dyrikas == 34) kieno = "Nekilnojamo turto agentø";
			else if(dyrikas == 60) kieno = "Inkasatoriø";
			format(msg,80,"%i. %s - %s direktorius.",x,vardas,kieno);
			SendClientMessage(playerid,YELLOW,msg);
		}
	}
	return 1;
}



CMD:darbuotojai(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][plead]==0) return SendInfoMessage(playerid,"Tai direktoriu komanda!");
	if(!galikast[playerid]) return SendInfoMessage(playerid,"~r~Palaukite.");
	galikast[playerid]=false;
	SetTimerEx("GaliKast",5000,0,"i",playerid);
	
	SendClientMessage(playerid,COLOR," * Visi darbuotojai:");
	new query[250];
	new lol=-1,
		lol2=-1,
		lol3=-1,
		lol4=-1,
		lol5=-1;
	if(playerDB[playerid][plead] == 2){ lol = 2; lol2=93; } // medikai
	else if(playerDB[playerid][plead] == 3){ lol = 3; lol2 = 20; } // transportas lol3 = 39;
	else if(playerDB[playerid][plead] == 5){ lol = 41; lol2 = 44;} // furistai
	else if(playerDB[playerid][plead] == 6){ lol = 6; lol2 = 28;} // autospeciai
	else if(playerDB[playerid][plead] == 66){ lol = 66;} // gaisrininkai
	else if(playerDB[playerid][plead] == 70){ lol = 70; lol2 = 73; lol3 = 72;} // autoklubas
	else if(playerDB[playerid][plead] == 80){ lol = 80; lol2 = 81; lol3 = 83; lol4 = 84; lol5=82;} // teisesauga
	else if(playerDB[playerid][plead] == 50){ lol = 50;} // skelbejai
	else if(playerDB[playerid][plead] == 98){ lol = 71;} // baikeriai
	else if(playerDB[playerid][plead] == 58){ lol = 58;} // vagys
	else if(playerDB[playerid][plead] == 90){ lol = 31; lol2=32;} // dealeriai 
	else if(playerDB[playerid][plead] == 34){ lol = 34;} // nta
	else if(playerDB[playerid][plead] == 60){ lol=60;}
	format(query,250,"SELECT `Name`,`Job`,`Pradirbo`,`Naud` From `Account` WHERE `Job`=%d or `Job`=%d or `Job`=%d or `Job`=%d or `Job`=%d order by `Job`",lol,lol2,lol3,lol4,lol5);
	mysql_function_query(SQL, query, true, "SQL_Darbuotojai", "i",playerid);
	return 1;
}

CMD:lobis(playerid,params[])
{
		#pragma unused params
        SearchLobis(playerid);
		SendInfoMessage(playerid,"Kasti gali ir paspaudes ENTER");
		return 1;
}
CMD:persirengti(playerid,params[])
{
    	#pragma unused params
		if(playerDB[playerid][psratasvydis]) return SendInfoMessage(playerid,"Cia keist skino negali!");
    	if(GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerHouseID(playerid) == 0)
		{
			SendInfoMessage(playerid,"Lauke persirengti jus negalite. Ka pagalvos zmones?");
			return 1;
		}
		if(playerDB[playerid][uniformd])
		{
			SetPlayerSkin(playerid,playerDB[playerid][drabuziai]);
			playerDB[playerid][uniformd]=false;
			SendInfoMessage(playerid,"Jus persirengete i savo kasdieninius drabuzius.");
			ApplyAnimation(playerid,"PLAYIDLES","stretch",4.1,0,0,0,0,0);
		}else{
			if(playerDB[playerid][uniforma]==-1)
			{
				SendInfoMessage(playerid,"Jus neturite darbines uniformos.");
				return 1;
			}

			SetPlayerSkin(playerid,playerDB[playerid][uniforma]);
			playerDB[playerid][uniformd]=true;
			SendInfoMessage(playerid,"Jus persirengete i savo darbine uniforma.");
			ApplyAnimation(playerid,"PLAYIDLES","stretch",4.1,0,0,0,0,0);
		}
		return 1;
}
CMD:pirkti_desraini(playerid,params[])
{
    	#pragma unused params
		if(playerDB[playerid][sotumas] >= 95.0) return SendInfoMessage(playerid,"~r~Tu ne alkanas!");
		if(IsPlayerInWorld(playerid))
			return SendInfoMessage(playerid, "Cia sios komandos naudoti negali!");
		for(new v=1;v<MAX_VEHICLES;v++)
		{
			if(GetVehicleModel(v) == HOTDOG)
			{
				new Float:Coo[3];
				GetVehiclePos(v,Coo[0],Coo[1],Coo[2]);
				if(IsPlayerInRangeOfPointEx(8,playerid,Coo[0],Coo[1],Coo[2]))
				{
					new vairuotojas = GetDriver(v);
					if(GetPlayerMoneyA(playerid) < 25) return SendInfoMessage(playerid,"Jums neuztenka pinigu.");
					if(vairuotojas == INVALID_PLAYER_ID) return SendInfoMessage(playerid,"Nera pardavejo."); // Nera vairuotojo, kam testi?
					if(GetPlayerScore(playerid) > 100)
						GivePlayerMoneyA(vairuotojas,25);
					SetPlayerHealth(playerid,100);
					GivePlayerMoneyA(playerid,-30);
					ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
					Valgymas(playerid,20.0);
					SendInfoMessage(playerid,"Jus nusipirkote desraini.");
					return 1;
				}
			}
		}
		SendInfoMessage(playerid,"Salia jusu nera desrainiu pardavejo.");
		return 1;
}
CMD:pirkti_pieno(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][sotumas] >= 95.0) return SendInfoMessage(playerid,"~r~Tu ne alkanas!");
	if(IsPlayerInWorld(playerid))
		return SendInfoMessage(playerid, "Cia sios komandos naudoti negali!");
	for(new v=1;v<MAX_VEHICLES;v++)
	{
		if(GetVehicleModel(v) ==543)
		{
			new Float:Coo[3];
			GetVehiclePos(v,Coo[0],Coo[1],Coo[2]);
			if(IsPlayerInRangeOfPointEx(8,playerid,Coo[0],Coo[1],Coo[2]))
			{
				new vairuotojas = GetDriver(v);
				if(GetPlayerMoneyA(playerid) < 25) return SendInfoMessage(playerid,"Jums neuztenka pinigu.");
				if(vairuotojas == INVALID_PLAYER_ID) return SendInfoMessage(playerid,"Nera pardavejo."); // Nera vairuotojo, kam testi?
				if(GetPlayerScore(playerid) > 100)
					GivePlayerMoneyA(vairuotojas,25);
				SetPlayerHealth(playerid,100);
				GivePlayerMoneyA(playerid,-30);
				ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
				Valgymas(playerid,20.0);
				SendInfoMessage(playerid,"Jus nusipirkote pieno.");
				return 1;
			}
		}
	}
	SendInfoMessage(playerid,"Salia jusu nera pieno pardavejo.");
	return 1;
}
CMD:pirkti_pica(playerid,params[])
{
    	#pragma unused params
		if(playerDB[playerid][sotumas] >= 95.0) return SendInfoMessage(playerid,"~r~Tu ne alkanas!");
		if(IsPlayerInWorld(playerid))
			return SendInfoMessage(playerid, "Cia sios komandos naudoti negali!");
    	for(new v=1;v<MAX_VEHICLES;v++)
		{
			if(GetVehicleModel(v) == 448)
			{
				new Float:Coo[3];
				GetVehiclePos(v,Coo[0],Coo[1],Coo[2]);
				if(IsPlayerInRangeOfPointEx(4,playerid,Coo[0],Coo[1],Coo[2]))
				{
					new vairuotojas = GetDriver(v);
					if(GetPlayerMoneyA(playerid) < 25) return SendInfoMessage(playerid,"Jums neuztenka pinigu.");
					if(vairuotojas == INVALID_PLAYER_ID) return SendInfoMessage(playerid,"Nera pardavejo."); // Nera vairuotojo, kam testi?
					if(GetPlayerScore(playerid) > 100)
						GivePlayerMoneyA(vairuotojas,20);
					SetPlayerHealth(playerid,100);
					GivePlayerMoneyA(playerid,-25);
					ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
					Valgymas(playerid,20.0);
					SendInfoMessage(playerid,"Jus nusipirkote pica.");
					return 1;
				}
			}
		}
		SendInfoMessage(playerid,"Salia jusu nera picu isveziotojo.");
		return 1;
}
CMD:pirkti_ledus(playerid,params[])
{
    	#pragma unused params
		if(playerDB[playerid][sotumas] >= 95.0) return SendInfoMessage(playerid,"~r~Tu ne alkanas!");
		if(IsPlayerInWorld(playerid))
			return SendInfoMessage(playerid, "Cia sios komandos naudoti negali!");
    	for(new v=1;v<MAX_VEHICLES;v++)
		{
			if(GetVehicleModel(v) == 423)
			{
				new Float:Coo[3];
				GetVehiclePos(v,Coo[0],Coo[1],Coo[2]);
				if(IsPlayerInRangeOfPointEx(8,playerid,Coo[0],Coo[1],Coo[2]))
				{
					new vairuotojas = GetDriver(v);
					if(GetPlayerMoneyA(playerid) < 25) return SendInfoMessage(playerid,"Jums neuztenka pinigu.");
					if(vairuotojas == INVALID_PLAYER_ID) return SendInfoMessage(playerid,"Nera pardavejo."); // Nera vairuotojo, kam testi?
					if(GetPlayerScore(playerid) > 100)
						GivePlayerMoneyA(vairuotojas,20);
					SetPlayerHealth(playerid,100);

					GivePlayerMoneyA(playerid,-25);
					ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
					Valgymas(playerid,20.0);
					SendInfoMessage(playerid,"Jus nusipirkote ledu porcija.");
					return 1;
				}
			}
		}
		SendInfoMessage(playerid,"Salia jusu nera ledu pardavejo.");
		return 1;
}
CMD:pirkti_zuvi(playerid,params[])
{
		#pragma unused params
		if(playerDB[playerid][sotumas] >= 95.0) return SendInfoMessage(playerid,"~r~Tu ne alkanas!");
		if(IsPlayerInWorld(playerid))
			return SendInfoMessage(playerid, "Cia sios komandos naudoti negali!");
    	for(new v=1;v<MAX_VEHICLES;v++)
		{
			if(GetVehicleModel(v) == 478)
			{
				new Float:Coo[3];
				GetVehiclePos(v,Coo[0],Coo[1],Coo[2]);
				if(IsPlayerInRangeOfPointEx(8,playerid,Coo[0],Coo[1],Coo[2]))
				{
					new vairuotojas = GetDriver(v);
					if(vairuotojas == INVALID_PLAYER_ID) return SendInfoMessage(playerid,"Nera pardavejo."); // Nera vairuotojo, kam testi?
					if(GetPlayerMoneyA(playerid) < 25) return SendInfoMessage(playerid,"Jums neuztenka pinigu.");
					if(GetPlayerScore(playerid) > 100)
						GivePlayerMoneyA(vairuotojas,20);
					SetPlayerHealth(playerid,100);
					GivePlayerMoneyA(playerid,-25);
					ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
					Valgymas(playerid,20.0);
					SendInfoMessage(playerid,"Jus nusipirkote zuvies.");
					return 1;
				}
			}
		}
		SendInfoMessage(playerid,"Salia jusu nera zuvies pardavejo.");
		return 1;
}
CMD:ans(playerid,params[])
{
		#pragma unused params
		if(playerDB[playerid][ikalintas]) return SendInfoMessage(playerid,"Policija ateme jusu telefona. Prasome naudotis taksofonu.");
		if(playerDB[playerid][skambutis]!=-1)
		{
			SendInfoMessage(playerid,"Jus jau kalbate.");
			return 1;
		}

		if(playerDB[playerid][rid][5]==-1)
		{
			SendInfoMessage(playerid,"Jums niekas neskambina.");
			return 1;
		}

		if(playerDB[playerDB[playerid][rid][5]][skambutis]!=playerid)
		{
			SendInfoMessage(playerid,"Jums niekas neskambina.");
			playerDB[playerid][skambutis]=-1;
			return 1;
		}
		new addon[128];
		new msg[256],name[MAX_PLAYER_NAME];
		GetPlayerName(playerDB[playerid][rid][5],name,sizeof(name));
		format(msg,sizeof(msg),"Jus sujungtas su %s. Pokalbi galite baigti parase: /bai. %s",name,addon);
		SendClientMessage(playerid,COLOR,msg);
		PlayerPlaySound(playerid, 1186, 0.0, 0.0, 0.0); // Isjungia muzika
		GetPlayerName(playerid,name,sizeof(name));
		format(msg,sizeof(msg),"Jus sujungtas su %s. Pokalbi galite baigti parase: /bai. %s",name,addon);
		SendClientMessage(playerDB[playerid][rid][5],COLOR,msg);
		playerDB[playerid][skambutis]=playerDB[playerid][rid][5];

		playerDB[playerDB[playerid][skambutis]][mobsas]-=4;


		if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_NONE)
		{
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
			SetPlayerAttachedObject(playerid, TEL_SLOT, 330, 6); // 4 = attachment slot, 330 = cellphone model, 6 = right hand
		}

		return 1;
}
CMD:den(playerid,params[])
{
		#pragma unused params
    	if(playerDB[playerid][skambutis]!=-1)
		{
			SendInfoMessage(playerid,"Naudokite /bai");
			return 1;
		}

		if(playerDB[playerid][rid][5]==-1)
		{
			SendInfoMessage(playerid,"Jums niekas neskambina ");
			return 1;
		}

		if(playerDB[playerDB[playerid][rid][5]][skambutis]!=playerid)
		{
			SendInfoMessage(playerid,"Jums niekas neskambina ");
			playerDB[playerid][skambutis]=-1;
			return 1;
		}

		new msg[128],name[MAX_PLAYER_NAME];
		GetPlayerName(playerDB[playerid][rid][5],name,sizeof(name));
		format(msg,sizeof(msg),"%s pokalbis atmestas.",name);
		SendInfoMessage(playerid,msg);
		GetPlayerName(playerid,name,sizeof(name));
		format(msg,sizeof(msg),"%s atmete pokalbi.",name);
		SendInfoMessage(playerDB[playerid][rid][5],msg);
		PlayerPlaySound(playerid, 1186, 0.0, 0.0, 0.0); // Isjunge muzika
		playerDB[playerid][skambutis]=-1;
		playerDB[playerDB[playerid][rid][5]][skambutis]=-1;
		return 1;

}

CMD:gaudomi(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]!=80 && playerDB[playerid][specialybe]!=81 && playerDB[playerid][specialybe] != 82 && playerDB[playerid][specialybe]!=83 && playerDB[playerid][specialybe] != 84){SendInfoMessage(playerid,"Si komanda Skirta teisesaugai."); return 1;}
	new zins[256] = "* Gaudomi:";
	new name[MAX_PLAYER_NAME];
	SendClientMessage(playerid,BLUE,zins);
	new total = 0;
	foreach (Player, i)
	{
		if(GetPlayerWantedLevel(i)>0  && !playerDB[i][invisible])
		{
			new lol[128] = "* ";

			GetPlayerName(i,name,MAX_PLAYER_NAME);
			if(playerDB[i][ikalintas])
			{
				format(lol,128,"%s %s(%i lygiu)(Kalejime),",lol,name,GetPlayerWantedLevel(i));
				SendClientMessage(playerid,GREEN,lol);
			}
			else if(GetPlayerWantedLevel(i) == 10)
			{
				format(lol,128,"%s %s(%i lygiu),",lol,name,GetPlayerWantedLevel(i));
				SendClientMessage(playerid,RED,lol);
			}
			else
			{
				format(lol,128,"%s %s(%i lygiu),",lol,name,GetPlayerWantedLevel(i));
				SendClientMessage(playerid,COLOR,lol);
			}
			total++;
		}
	}
	if(GaudomiCleanup[playerid] && total == 0)
		ProcessAchievement(playerid,67);
	if(total>=10)
		GaudomiCleanup[playerid]=1;
	return 1;

}

CMD:siulytinama(playerid,params[])
{
		new price,name[128];
		if (sscanf(params, "s[24]d",name,price))
		{
			SendInfoMessage(playerid,"Naudojimas: /siulytinama [vardas] [kaina]");
			return 1;
		}
		if(TradingWith[playerid] != -1) return SendInfoMessage(playerid,"Uzdaryk mainus!");
		new sellplayerid = GetPlayeridMid(name);

		if(sellplayerid == INVALID_PLAYER_ID || sellplayerid == playerid) return SendInfoMessage(playerid,"Tokio zaidejo nera.");

		if (price<50000)
		{
			SendInfoMessage(playerid,"Dovanosi nama? Kaina turi virsyti $50000.");
			return 1;
		}
		if (GetPlayerMoneyA(sellplayerid) < price)
		{
			SendInfoMessage(playerid,"Zaidejas neturi tiek pinigu.");
			return 1;
		}
		new pnames[24],housenumber,string[128];
		housenumber = GetHouseID(playerid);
		if(housenumber == -255 || housenumber == -1 ) return SendInfoMessage(playerid,"Jus ne prie namo!");
		GetPlayerName(playerid, pnames, 24);
		if (strcmp(hInfo[housenumber][Name],pnames,false)) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
		offerHouse[sellplayerid][0]=playerid;
		offerHouse[sellplayerid][1]=price;
		offerHouse[sellplayerid][2]=housenumber;
		new playername[MAX_PLAYER_NAME];
		new sellplayername[MAX_PLAYER_NAME];
		GetPlayerName(playerid,playername,sizeof(playername));
		GetPlayerName(sellplayerid,sellplayername,sizeof(sellplayername));
		format(string,128,"Jus siulote %s savo nama(nr.%i) uz %i EUR!",sellplayername,housenumber,price);
		SendInfoMessage(playerid,string);
		SendClientMessage(playerid, HOMER, "Nutraukite pasiulyma su - /atsauktinama.");
		format(string,128,"%s siulo savo nama nr.%i uz %i €.",playername,housenumber,price);
		SendClientMessage(sellplayerid, HOMER, string);
		SendClientMessage(sellplayerid, HOMER, "Jei norite pirkti, rasykite /sutiktinama");
		return 1;
}
CMD:siulytiversla(playerid,params[])
{
		new price,name[128];
		if (sscanf(params, "s[24]d",name,price))
		{
			SendInfoMessage(playerid,"Naudojimas: /siulytiversla [vardas] [kaina]");
			return 1;
		}
		if(TradingWith[playerid] != -1) return SendInfoMessage(playerid,"Uzdaryk mainus!");
		new sellplayerid = GetPlayeridMid(name);

		if(sellplayerid == INVALID_PLAYER_ID || sellplayerid == playerid) return SendInfoMessage(playerid,"Tokio zaidejo nera.");

		if (price<50000)
		{
			SendInfoMessage(playerid,"Dovanosi versla? Kaina turi virsyti $50000.");
			return 1;
		}
		if (GetPlayerMoneyA(sellplayerid) < price)
		{
			SendInfoMessage(playerid,"Zaidejas neturi tiek pinigu.");
			return 1;
		}
		if(VerslaiCount(sellplayerid) >= 10) return SendInfoMessage(playerid,"Zaidejas jau turi 10 verslu.");

		new stata = GetPlayerState(sellplayerid);
		new vehicleid = GetPlayerVehicleID(sellplayerid);
		if(stata == PLAYER_STATE_DRIVER && (playerDB[sellplayerid][specialybe]==5 || playerDB[sellplayerid][specialybe]==55 || playerDB[sellplayerid][specialybe]==62 || vagia[sellplayerid] || vpakrauta[vehicleid]==1 || vbankomatams[vehicleid]==1) )
		{
			SendClientMessage(playerid,WHITE,"Pirkejas privalo islipti is automobilio.");
			return 1;
		}
		new bizid,string[128];
		//bizid = ArTuriBiz(sellplayerid);
		//if(bizid != -1 ) return SendInfoMessage(playerid,"Zaidejas jau turi Versla!");
		//bizid = ArTuriBiz(playerid);
		//if(bizid == -1) return SendInfoMessage(playerid,"Jus neturite verslo!");
		if(!IsInBiz(playerid)) return SendInfoMessage(playerid,"Jus neesate viduje!");
		bizid = GetPlayerVirtualWorld(playerid) - MAX_HOUSES*2;
		if(strcmp(BusinessInfo[bizid][bOwner],ReturnName(playerid),false) || !BusinessInfo[bizid][bOwned]) return SendInfoMessage(playerid,"Tai ne jusu verslas!");

		offerBiz[sellplayerid][0]=playerid;
		offerBiz[sellplayerid][1]=price;
		offerBiz[sellplayerid][2]=bizid;
		new playername[MAX_PLAYER_NAME];
		new sellplayername[MAX_PLAYER_NAME];
		GetPlayerName(playerid,playername,sizeof(playername));
		GetPlayerName(sellplayerid,sellplayername,sizeof(sellplayername));
		format(string,128,"Jus siulote %s savo versla (\"%s\") uz %i EUR!",sellplayername,BusinessInfo[bizid][bName],price);
		SendInfoMessage(playerid,string);
		SendClientMessage(playerid, HOMER, "Nutraukite pasiulyma su - /atsauktiversla.");
		format(string,128,"%s siulo savo versla (\"%s\") uz %i €.",playername,BusinessInfo[bizid][bName],price);
		SendClientMessage(sellplayerid, HOMER, string);
		SendClientMessage(sellplayerid, HOMER, "Jei norite pirkti, rasykite /sutiktiversla");

		SendClientMessage(sellplayerid, WHITE, "Verslas kuri jum siulo parodytas zemelapyje.");
		SetPlayerCheckpoint(sellplayerid,BusinessInfo[bizid][bEnterX],BusinessInfo[bizid][bEnterY],BusinessInfo[bizid][bEnterZ],5.0);
		return 1;
}

CMD:grizti(playerid,params[])
{
	if(PlayerEvent[playerid][pJoin] == 0 || !InEvent(playerid)) // 20 min
	{
		SendClientMessage(playerid,ORANGE, " * Jus nedalyvaujate evente arba praejo per daug laiko!");
	}
	else if(Server[EventON]) 
	{
		SendClientMessage(playerid,ORANGE, " * Vis dar vyksta evento teleport!");
	}
	else if(playerDB[playerid][ikalintas])
		return SendClientMessage(playerid, ORANGE, " * Ið kalëjimo gráþti negali!");
	else
	{
		LastEvent[playerid]=0;
		//ResetPlayerWeapons(playerid);
		ResetGunData(playerid);
		DisableRemoteVehicleCollisions(playerid,0);
		SetPlayerPosFade(playerid,30,PlayerEvent[playerid][pPos][0],PlayerEvent[playerid][pPos][1],PlayerEvent[playerid][pPos][2]+0.5,PlayerEvent[playerid][pInter],PlayerEvent[playerid][pVW]);
		PlayerEvent[playerid][pJoin]=0;
		LogA(playerid,"Grizta(event)");
		SetTimerEx("ReturnGuns", 1000, false, "i", playerid);
		SetCameraBehindPlayer(playerid);
		SetPlayerSkin(playerid,playerDB[playerid][spdata][24]);
	}
	return 1;
}
CMD:event(playerid,params[])
{
	if(!Server[EventON]) return SendInfoMessage(playerid,"Eventas nevyksta!");
	if(!Server[EventTime]) return SendInfoMessage(playerid,"Nebegalima prisijungti i eventa!");
	if(strval(params) != Server[EventNr]) return SendInfoMessage(playerid,"Neteisingas kodas!");
	if(playerDB[playerid][ikalintas]) return SendInfoMessage(playerid,"~r~Jus ikalintas!");
	if(playerDB[playerid][psratasvydis] > 0) return SendInfoMessage(playerid,"~r~Jus dazasvydyje!");
	if(playerDB[playerid][ant] || GetPlayerWantedLevel(playerid) >=5) return SendInfoMessage(playerid,"~r~Jus gaudomas policijos!");
	if(playerDB[playerid][suristas]) return SendInfoMessage(playerid,"~r~Jus surakintas!");
	if(playerDB[playerid][playingpoker]) return SendInfoMessage(playerid,"~r~Jus zaidziate!");
	if(IsPlayerInRangeOfPointEx(30,playerid,Server[EventCoo][0],Server[EventCoo][1],Server[EventCoo][2])) return SendInfoMessage(playerid,"~r~Jus jau evente!");
	if(playerDB[playerid][sotumas] < 30.0) playerDB[playerid][sotumas]=30.0;
	SendClientMessage(playerid, ORANGE, " * Norëdami gráþti ið evento raðykite: {FFFFFF}/grizti");
	ProcessAchievement(playerid, 125);
	GetPlayerPos(playerid,PlayerEvent[playerid][pPos][0],PlayerEvent[playerid][pPos][1],PlayerEvent[playerid][pPos][2]);
	PlayerEvent[playerid][pInter] = GetPlayerInterior(playerid);
	PlayerEvent[playerid][pVW] = GetPlayerVirtualWorld(playerid);
	PlayerEvent[playerid][pJoin]=GetTickCount();

	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		UpdateGunData(playerid);
	for(new slot=0; slot<12; slot++)
	{
		playerDB[playerid][spdata][slot] = GunData[ playerid ][ slot ][0];
		playerDB[playerid][spdata][12+slot] = GunData[ playerid ][ slot ][1];
	}
	playerDB[playerid][spdata][24]=GetPlayerSkin(playerid);
	//ResetPlayerWeapons(playerid);
	ResetGunData(playerid);

	if(Server[Dalyviai] != -1)
	{
		if(Server[Dalyviai])
		{
			Server[Dalyviai]--;
			if(LastEvent[playerid] == eventid-1) {
				EventCount[playerid]++;
			}
			else
				EventCount[playerid]=0;
			LastEvent[playerid]=eventid;
			if(EventCount[playerid] == 4)
				ProcessAchievement(playerid,74);
			//SetCameraBehindPlayer(playerid);
			SetPlayerPosFade(playerid,30,Server[EventCoo][0],Server[EventCoo][1],Server[EventCoo][2]+0.5,Server[EventInt],Server[EventVW]);
			if(!Server[Dalyviai])
			{
				SendClientMessageToAll(ORANGE," * Eventas pilnas dalyviu!");
				Server[EventON]=false;
			}
			return 1;
		}
		else SendInfoMessage(playerid,"Neber vietu!");
	}
	if(LastEvent[playerid] == eventid-1) {
		EventCount[playerid]++;
	}
	else
		EventCount[playerid]=0;
	LastEvent[playerid]=eventid;
	if(EventCount[playerid] == 4)
		ProcessAchievement(playerid,74);
	//SetCameraBehindPlayer(playerid);
	SetPlayerPosFade(playerid,30,Server[EventCoo][0],Server[EventCoo][1],Server[EventCoo][2]+0.5,Server[EventInt],Server[EventVW]);
	return 1;
}
CMD:atsauktinama(playerid,params[])
{
		#pragma unused params
		new string[128];
		foreach (Player, i)
		{
			if (offerHouse[i][0]==playerid)
			{
				offerHouse[i]={-1,0,-255};
				SendInfoMessage(playerid,"Jus nutraukete savo pasiulyma.");
				new playername[MAX_PLAYER_NAME];
				GetPlayerName(playerid,playername,sizeof(playername));
				format(string,128,"%s nutrauke pasiulyma.",playername);
				SendClientMessage(i, HOMER, string);
				return 1;
			}
		}
		SendInfoMessage(playerid,"Jus nesiulote savo namo!");
		return 1;
}
CMD:atsauktiversla(playerid,params[])
{
		#pragma unused params
		new string[128];
		foreach (Player, i)
		{
			if (offerBiz[i][0]==playerid)
			{
				offerBiz[i]={-1,0,-1};
				SendInfoMessage(playerid,"Jus nutraukete savo pasiulyma.");
				new playername[MAX_PLAYER_NAME];
				GetPlayerName(playerid,playername,sizeof(playername));
				format(string,128,"%s nutrauke pasiulyma.",playername);
				SendClientMessage(i, HOMER, string);
				return 1;
			}
		}
		SendInfoMessage(playerid,"Jus nesiulote savo verslo!");
		return 1;
}
CMD:sutiktiversla(playerid,params[])
{
    #pragma unused params
	if (offerBiz[playerid][0]!=-1)
	{
		if(IsPlayerConnected(offerBiz[playerid][0]))
		{
			if(TradingWith[offerBiz[playerid][0]] != -1) return SendInfoMessage(playerid,"Uzdaryk mainus!");
			new str[255],pname[24],parname[24];
			GetPlayerName(playerid, pname, 24);
			GetPlayerName(offerBiz[playerid][0], parname, 24);
			if(GetPlayerMoneyA(playerid) < offerBiz[playerid][1]) return SendClientMessage(playerid, c_r, "Neuztenka pinigu!");
			//if(ArTuriBiz(playerid) != -1 || ArTuriBiz(offerBiz[playerid][0]) == -1) return SendClientMessage(playerid, c_r, "Jus jau turite versla.");
			SendInfoMessage(playerid,"Jus nusipirkote versla!");
			format(str, sizeof(str), "%s Nusipirko versla!",pname);
			print(str);
			new sellerid=offerBiz[playerid][0];
			new price=offerBiz[playerid][1];
			new i=offerBiz[playerid][2];
			if(strcmp(BusinessInfo[i][bOwner],ReturnName(sellerid),false) != 0)
			{
				SendInfoMessage(playerid,"Zaidejas nebeturi verslo!");
				offerBiz[playerid]={-1,0,-1};
				return 1;
			}
			GivePlayerMoneyA(playerid, - price);
			GivePlayerMoneyA(sellerid, price);
			//new i=ArTuriBiz(sellerid);
			strmid(BusinessInfo[i][bOwner],pname,0,MAX_PLAYER_NAME,MAX_PLAYER_NAME);
			new string[128];
		    new idx=i;
		    
		    format(string, sizeof(string), VERSLAS_NEPARDUODAMAS, BusinessInfo[i][bName],BusinessInfo[i][bOwner],GetBussinessType(BusinessInfo[idx][bType]));
			DestroyDynamic3DTextLabel(businesstext[i]);
			businesstext[i] = CreateDynamic3DTextLabel(string,0x00BC00FF,BusinessInfo[i][bEnterX],BusinessInfo[i][bEnterY],BusinessInfo[i][bEnterZ],40.0, _,_, 1);
			offerBiz[playerid]={-1,0,-1};
			MLog(playerid,"Nusipirko versla is","is", i,parname);
			ProcessAchievement(playerid,45);
			return 1;
		}
		else
		{
			SendInfoMessage(playerid,"Pardavejas neprisijunges.");
		}
	}
	else
	{
		SendInfoMessage(playerid,"Nera jokio verslo, pardavejas jus bando apgauti.");
	}
	return 1;
}
CMD:sutiktinama(playerid,params[])
{
		#pragma unused params
		if (offerHouse[playerid][0]!=-1)
		{
			if (IsPlayerConnected(offerHouse[playerid][0]) )
			{
				new pname[24],parname[24];
				GetPlayerName(playerid, pname, 24);
				GetPlayerName(offerHouse[playerid][0], parname, 24);
				if(strcmp(hInfo[offerHouse[playerid][2]][Name],parname,false)) return 0;
				if(GetPlayerMoneyA(playerid) < offerHouse[playerid][1]) return SendInfoMessage(playerid,"Neuztenka pinigu!");
				if(playerDB[playerid][namu] >= GetNamuLimit(playerid)) return SendInfoMessage(playerid,"Jus jau turite 2 namus.");
				ProcessAchievement(offerHouse[playerid][0],71);
				SendInfoMessage(playerid,"Jus nusipirkote nama!");
				MLog(playerid,"Nusipirko nama is","is", offerHouse[playerid][2],ReturnName(offerHouse[playerid][0]));
				playerDB[playerid][namu]++;
				new sellerid=offerHouse[playerid][0];
				new price=offerHouse[playerid][1];
				GivePlayerMoneyA(playerid, - price);
				GivePlayerMoneyA(sellerid, price);
				playerDB[sellerid][namu]--;
				new housenumber=offerHouse[playerid][2];
				//hInfo[housenumber][zole] = 0;
				//hInfo[housenumber][nark] = 0;
				//hInfo[housenumber][pinigai] = 0;
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `Zole`=0,`Nark`=0,`Pinigai`=0 WHERE `ID`=%i",housenumber);
				mysql_query(query);
				for(new slot=0; slot<12; slot++)
				{
					hInfo[housenumber][gunas][slot]=0;
					hInfo[housenumber][kulkos][slot]=0;
					new kulkoz[50],gunz[50];
					format(kulkoz,sizeof(kulkoz),"Kulkos%i",slot);
					format(gunz,sizeof(gunz),"Ginklas%i",slot);

					format(query,sizeof(query),"UPDATE `Namai` SET `%s`=0,`%s`=0 WHERE `ID`=%i",kulkoz,gunz,housenumber);
					mysql_query(query);
				}
				format(query,sizeof(query),"UPDATE `Namai` SET `Name`='%s' WHERE `ID`=%i",pname,housenumber);
				mysql_query(query);
				hInfo[offerHouse[playerid][2]][Name]=pname;
				hInfo[offerHouse[playerid][2]][Locked] = 0;
				DestroyDynamic3DTextLabel(HouseText[housenumber]);
				new zinute[512];
				new vw;
				if(hInfo[housenumber][daugiabutis]) vw=(MAX_HOUSES*2+MAX_BUSINESSES+hInfo[housenumber][daugiabutis]-1);
				format(zinute,sizeof(zinute),"{FFFFFF}Namas Nr.: {FF0000}%i\n{FFFFFF}Savininkas: {FF0000}%s",housenumber,hInfo[housenumber][Name]);
				HouseText[housenumber] = CreateDynamic3DTextLabel(zinute, COLOR_WHITE, hInfo[housenumber][iconx], hInfo[housenumber][icony], hInfo[housenumber][iconz], 50, _,_, 1, vw);
				ProcessAchievement(playerid,19);
				offerHouse[playerid]={-1,0,-1};
				if(hInfo[housenumber][polyId] != -1)
				{
					ShowPlayerDialog(playerid, 9530, DIALOG_STYLE_MSGBOX, "Apartamentai", "Sveikiname ásigyjus vienà prestiþiðkiausiø Los Santos apartamentø!\n\nJuo galite naudotis visiðkai kaip ir kitais namais, iðskyrus kelias smulkmenas:\n\
					• Negalite daþyti namo sienø ir durø.\n\
					• Negalite namo remontuoti.\n\
					• Galite uþrakinti lifto duris uþlipæ ant ðio pickup.\n\
					• Privalote baldus statyti tvarkingai. Uþ per sienas/lubas/grindis iðlindusius baldus ið jûsø bus atimtas namas be jokio perspëjimo.\n\n\nLinkime jaukaus ir patogaus gyvenimo jûsø naujàjame name!", "Gerai","");
				}
				return 1;
			}
			else
			{
				SendInfoMessage(playerid,"Pardavejas neprisijunges.");
			}
		}
		else
		{
			SendInfoMessage(playerid,"Nera jokio namo, pardavejas jus bando apgauti.");
		}
		return 1;
}
CMD:policija(playerid,params[])
{
		#pragma unused params
		SendClientMessage(playerid,BLUE,"* Policijos komandos:");
		SendClientMessage(playerid,GREEN,"* /ita - itaria zaideja.");
		SendClientMessage(playerid,ORANGE,"* /paz - patikrina vairuotojo pazymejima. /tei - atima vairuotojo pazymejima.");
		SendClientMessage(playerid,ORANGE,"* /nark - patikrina ar turi nark. /kon - konfiskuoja nark.");
		SendClientMessage(playerid,ORANGE,"* /ant - surakina,atrakina nusikalteli.");
		SendClientMessage(playerid,ORANGE,"* /atristi - atrisa ikaita. /sekti - suseka zaideja. /nr - rodo automobilio buvimo vieta.");
		SendClientMessage(playerid,ORANGE,"* /bauda - paima is nusikaltelio bauda.");
		SendClientMessage(playerid,ORANGE,"* /alko - patikrina girtumo laipsni.");
		SendClientMessage(playerid,ORANGE,"* /matuoklis - ijungia,isjungia greicio matuokli");
		SendClientMessage(playerid,ORANGE,"* /kong - atimti zaidejo ginkla. /patruliavimas - patruliavimo komandos");
		SendClientMessage(playerid,ORANGE,"* /spygliai, /nspygliai - padeda ir nuima spyglius. /lauztis - isilauzia i zaidejo namus.");
		return 1;
}
CMD:mires(playerid,params[])
{
		#pragma unused params
		SendClientMessage(playerid,0xF50AF5FF,"* Mirusio miesto komandos:");
		SendClientMessage(playerid,0x9E5FA0FF,"* /lobis");
		return 1;
}

CMD:kviesti(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][suristas]) return SendInfoMessage(playerid,"Tu suristas! Naudokis /sms !");
	ShowPlayerDialog(playerid,505,DIALOG_STYLE_LIST,"Iskvietimai","Policija\nGaisrininkai\nMedikai\nTaksi\nDyleriai\nMechanikai\nSkelbejai\nAdvokatai\nLimuzinai\nNekilnojamo turto agentai\nBaikeriai\nGreitas maistas","Rinktis","Iseiti");
	if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_NONE && !playerDB[playerid][ant] && !playerDB[playerid][suristas]){SendClientMessage(playerid,COLOR,"* Kai baigsite rageli padekite su ( /bai )"); SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE); SetPlayerAttachedObject(playerid, TEL_SLOT, 330, 6);}
	return 1;
}

CMD:pokalbiai(playerid,params[])
{
		#pragma unused params
		SendClientMessage(playerid,0xF50AF5FF,"* Telefonas ir pokalbiai:");
		SendClientMessage(playerid,0x9E5FA0FF,"* /skamb /ans /den /bai /sms /kviesti /me /r /telon");
		return 1;
}
CMD:lytis(playerid,params[])
{
	#pragma unused params
	if(GetPlayerScore(playerid) < 1500) return SendInfoMessage(playerid,"Si komanda tik nuo 1500xp.");
	ShowPlayerDialog(playerid,9887,DIALOG_STYLE_MSGBOX,"Lytis","Prasome pasirinkti savo lyti.","Vyras","Moteris");
	return 1;
}

CMD:sleptis(playerid,params[])
{
		#pragma unused params
		SendClientMessage(playerid,0xF50AF5FF,"* Jusu statusas:");
		if(!playerDB[playerid][pasislepes])
		{
			SendClientMessage(playerid,0x9E5FA0FF,"* Pasislepes.");
			//SetPlayerColor(playerid,PLAYCOL_HIDDEN);
			TextDrawShowForPlayer(playerid, SleptisTD);
			playerDB[playerid][pasislepes]=true;
			BitFlag_On(PConfig[playerid],PCFG_PASISLEPES);
		}
		else
		{
			SendClientMessage(playerid,COLOR,"* Nepasislepes");
			TextDrawHideForPlayer(playerid, SleptisTD);
			playerDB[playerid][pasislepes]=false;
			BitFlag_Off(PConfig[playerid],PCFG_PASISLEPES);
		}
		return 1;
}

CMD:kreditai(playerid,params[])
{
		#pragma unused params
		new msg[128];
		format(msg,sizeof(msg),"Apie kreditus\nPirkti kreditus\nPirkti paslaugas (%i kred)",playerDB[playerid][kreditai]);
		ShowPlayerDialog(playerid, 1987, DIALOG_STYLE_LIST, "Kreditai",msg,"Taip","Ne");
	 	return 1;
}
CMD:kiti(playerid,params[])
{
		#pragma unused params
		SendClientMessage(playerid,0xF50AF5FF,"* Kitos komandos:");
		SendClientMessage(playerid,0x9E5FA0FF,"* /duoti /ginklas /kur /persirengti");
		return 1;
}

CMD:pagalba(playerid,params[])
{
		#pragma unused params
		SendClientMessage(playerid, TEXTCOL_GOLD,"* > Los Santos Gyvenimas <");
		SendClientMessage(playerid,TEXTCOL_SILVER,"* Pagalbos meniu:");
		SendClientMessage(playerid,TEXTCOL_WHITE,"* /kur /info /i /p /pokalbiai /admin /kviesti");
		SendClientMessage(playerid,TEXTCOL_WHITE,"* /darbai /masina /auto /pasiekimai ");
		SendClientMessage(playerid,TEXTCOL_WHITE,"* /kova /verslas /namai /dkomandos /narkotikai /rukyti /cigarete");
		SendClientMessage(playerid,TEXTCOL_WHITE,"* /veiksmai /duoti /ginklas /mainytis /sleptis ");
		SendClientMessage(playerid,TEXTCOL_WHITE,"* /bendradarbiai /gnariai /vinfo /kreditai /keybind");
		SendClientMessage(playerid, TEXTCOL_GOLD,"* Paraðæ daugumà komandø gausite iðsamesnæ informacijà. Iðkilus problemoms, raðykite /admin [problema].");
		return 1;
}
CMD:info(playerid,params[])
{
		#pragma unused params
		Stats(playerid,playerid);
		return 1;
}


CMD:veiksmai(playerid,params[])
{
		#pragma unused params
		SendClientMessage(playerid,0xF50AF5FF,"* Veiksmai:");
		SendClientMessage(playerid,0x9E5FA0FF,"* /sokti /sedet /gulet /yohyoh /sexy");
		SendClientMessage(playerid,0x9E5FA0FF,"* /verkt /ateik /spresti /aaa /gogogo /kungfu /wank");
		SendClientMessage(playerid,0x9E5FA0FF,"* /taip /ne /trenkt /mot /parkour /persirengti /selfie");
		SendClientMessage(playerid,0x9E5FA0FF,"* /veiksmai2 /veiksmai3 /baik - baigti veiksmus");
		return 1;
}

CMD:masina(playerid,params[])
{
	#pragma unused params
	SendClientMessage(playerid, GREEN,"Masinos pagalba:");
	SendClientMessage(playerid, GREEN,"Kasdienines komandos: /parkuoti /remontuoti /rakinti /kurmasina /mismesti /isspirti");
	SendClientMessage(playerid, GREEN,"Turgaus komandos: /parduoti /islipti");
	SendClientMessage(playerid, GREEN,"Masinos pardavimas zaidejams: /mainytis");
	return 1;
}

CMD:kova(playerid,params[])
{
		#pragma unused params
    	SendClientMessage(playerid,COLOR,"* Nauju kovos stiliu galite ismokti sporto saleje! /treniruotis");
		ShowPlayerDialog(playerid, 5010, DIALOG_STYLE_LIST, "Kovos stiliai", "Elbow\nBoxing\nGrabkick\nKneehead\nKungfu\nNormal", "Pasirinkti", "Cancel");
		return 1;
}
CMD:treniruotis(playerid,params[])
{
    	if (!IsPlayerInRangeOfPointEx(40, playerid,767.2731,14.1037,1000.7003) && !IsPlayerInRangeOfPointEx(40, playerid,762.1400,-29.5834,1000.5859) &&!IsPlayerInRangeOfPointEx(40, playerid,767.8558,-61.9425,1001.2811))//gym's checkpoint
		{
			SendInfoMessage(playerid,"Jus nesate sporto saleje!");
			return 1;
		}
		if(playerDB[playerid][treniruojasi]) return SendInfoMessage(playerid,"Jus jau treniruojates!");
		PlayerPlaySound(playerid, 4800, 0.0, 0.0, 0.0);
		SendClientMessage(playerid, COLOR_LIGHTBLUE, "|_______ Sporto klubas _______|");
		SendClientMessage(playerid, COLOR, "| 1: Box'as ($15000) | 2: Kung Fu ($10000) |");
		SendClientMessage(playerid, COLOR, "| 3: Grabkick ($13500) | 4: Kneehead ir Elbow ($50000) |");
		SendClientMessage(playerid, COLOR_GREY, "* Rasykite /kova Kad pasirinkt jau ismoktus smugius!");
		ShowPlayerDialog(playerid,12858,DIALOG_STYLE_LIST,"Sporto Klubas","Boksas  15000€\nKung Fu  10000€\nGrabkick  13500€\nKneehead ir Elbow  50000€","Gerai","Atsaukti");
		return 1;
}


CMD:sedet(playerid,params[])
{
	//LoopingAnim(playerid,animlib[],animname[], Float:Speed, looping, lockx, locky, lockz, lp,showtd=1)
	//ApplyAnimation(playerid,animlib,animname,fDelta,loop,lockx,locky,freeze,time,forcesync)
	//ApplyAnimation(playerid, animlib, animname, Speed, looping, lockx, locky, lockz, lp);
	if(CheckZone(playerid) != 0 || playerDB[playerid][ant] || playerDB[playerid][suristas]) return SendInfoMessage(playerid,"Cia sitos komandos naudoti negali!");
	new koks;
	if (sscanf(params, "d",koks)) return SendInfoMessage(playerid,"Atsisesti: /sedet [1-5] (skaicius)");
	if(koks == 1){
		//ApplyAnimation(playerid, "BEACH", "ParkSit_W_loop", 4.000000, 1, 0, 0, 1, 0,0); //Sedeti
		LoopingAnim(playerid,"BEACH", "ParkSit_W_loop",4.0,1,0,0,1,0);
	}else if(koks == 2){
		//ApplyAnimation(playerid, "BEACH", "SitnWait_loop_W", 4.000000, 1, 0, 0, 1, 0,0); //Sedeti
		LoopingAnim(playerid,"BEACH", "SitnWait_loop_W",4.0,1,0,0,1,0);
	}else if(koks == 3){
		//ApplyAnimation(playerid, "INT_HOUSE", "LOU_In", 4.000000, 0, 0, 0, 1, 0,0);
		LoopingAnim(playerid,"INT_HOUSE", "LOU_In",4.0,0,0,0,1,0);
	}else if(koks == 4){
		//ApplyAnimation(playerid, "INT_OFFICE", "FF_Dam_Fwd", 4.000000, 0, 0, 0, 1, 0, 0);
		LoopingAnim(playerid,"INT_OFFICE", "FF_Dam_Fwd",4.0,0,0,0,1,0);
	}else if(koks == 5){
		LoopingAnim(playerid,"PED","SEAT_IDLE",4.0,0,0,0,1,0);
	}
	return 1;
}
CMD:selfie(playerid,params[])
{
    if(GetPVarInt(playerid, "selfie") == 0)
    {
    	SetPVarInt(playerid, "selfie", 1);
    	new Float:Coo[6];
        GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
        SelfiePos[playerid][0]=Coo[0];
		SelfiePos[playerid][1]=Coo[1];
     	SelfiePos[playerid][2]=Coo[2];
        GetPlayerFacingAngle(playerid, Coo[3]);
        Coo[3]+=90;

        Coo[4] = Coo[0] + 1.4 * floatcos(Coo[3], degrees);
        Coo[5] = Coo[1] + 1.4 * floatsin(Coo[3], degrees);
        SetPlayerCameraPos(playerid, Coo[4],Coo[5],Coo[2] + 1.0);
        ApplyAnimation(playerid, "PED", "gang_gunstand", 4.1, 1, 1, 1, 1, 1, 1);
        SetPlayerCameraLookAt(playerid, Coo[0],Coo[1],Coo[2]+1);
        SendClientMessage(playerid, -1, " * Naudok /selfie norëdamas iðjungti ðá rëþimà. Naudok /headmove jei tavo þaidëjas judina galvà.");
        return 1;
    }
   	else
    {
        SetCameraBehindPlayer(playerid);
        SetPVarInt(playerid, "selfie", 0);
        ApplyAnimation(playerid, "PED", "ATM", 4.1, 0, 1, 1, 0, 1, 1);
        return 1;
    }
}

CMD:ujail(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==80 || playerDB[playerid][specialybe] == 81 || playerDB[playerid][specialybe] == 83  || playerDB[playerid][specialybe] == 84 || playerDB[playerid][admin])
	{
		RotateObject(iwaziavimas,0, 90 ,0);
	}
	return 1;
}
CMD:ajail(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==80 || playerDB[playerid][specialybe] == 81 || playerDB[playerid][specialybe] == 82 || playerDB[playerid][specialybe] == 83 || playerDB[playerid][specialybe] == 84 || playerDB[playerid][admin])
	{
		RotateObject(iwaziavimas,0,0,0);
		GameTextForPlayer(playerid,"~g~Vartai uzsidarys po 10sec.",5000,5);
		SetTimerEx("Varteliai",10000,0,"i",10);
	}
	else
		SendInfoMessage(playerid,"~r~Tu nepriklausai teisesaugos buriui!");
	return 1;
}
CMD:apolicija(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==80 || playerDB[playerid][specialybe] == 81 || playerDB[playerid][specialybe]== 82 || playerDB[playerid][specialybe] == 83  || playerDB[playerid][specialybe] == 84 || playerDB[playerid][admin])
	{
		RotateObject(policijaa,0,0,90);
		GameTextForPlayer(playerid,"~g~Vartai uzsidarys po 10sec.",5000,5);
		SetTimerEx("Varteliai",10000,0,"i",0);
	}
	else
		SendInfoMessage(playerid,"~r~Tu nepriklausai teisesaugos buriui!");
	return 1;
}
CMD:aspeeder(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][admin])
	{
		RotateObject(valtys,0,0,90);
		GameTextForPlayer(playerid,"~g~Vartai uzsidarys po 60 sec.",5000,5);
		SetTimerEx("Varteliai",60000,0,"i",13);
	}
	return 1;
}
CMD:amonster(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][admin])
	{
		MoveObject(angarovartai,-3.60795927,2472.71582031,11.98562927, 1.0001);
		GameTextForPlayer(playerid,"~g~Vartai uzsidarys po 120 sec.",5000,5);
		SetTimerEx("Varteliai",120000,0,"i",14);
	}
	return 1;
}
CMD:upolicija(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==80 || playerDB[playerid][specialybe] == 81 || playerDB[playerid][specialybe] == 83 || playerDB[playerid][specialybe] == 84 || playerDB[playerid][admin])
	{
		RotateObject(policijaa,0, 90 ,90);
	}
	return 1;
}
CMD:apolicijag(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==80 || playerDB[playerid][specialybe] == 81 || playerDB[playerid][specialybe] == 82 || playerDB[playerid][specialybe] == 83 || playerDB[playerid][specialybe] == 82 || playerDB[playerid][specialybe] == 84 || playerDB[playerid][admin])
	{
		garazostatus = 1;
		MoveObject(policijaaa,1589.252686, -1638.186401, 10.541596, 1.0001);
	}
	else
		SendInfoMessage(playerid,"~r~Tu nepriklausai teisesaugos buriui!");
	return 1;
}
CMD:adureles(playerid,params[])
{
	if(playerDB[playerid][plead]==80 || playerDB[playerid][admin])
	{
	    MoveObject(pddureles,1580.6054,-1637.9565,13.6169, 1.0001);
	    return 1;
	}
	return 0;
}
CMD:udureles(playerid,params[])
{
	if(playerDB[playerid][plead]==80 || playerDB[playerid][admin])
	{
	    MoveObject(pddureles,1582.6254,-1637.9903,13.7719, 1.0001);
	    return 1;
	}
	return 0;
}

CMD:laikrastis(playerid,params[])
{
	if(!playerDB[playerid][laikrastis]) return SendInfoMessage(playerid,"Neturi laikrascio! Ji gali nusipirkti spaudos kioske!"); // if !laikrastis
	ShowPlayerDialog(playerid,6431,DIALOG_STYLE_MSGBOX,"LSG Laikrastis","	  	{FF9900}LSG Laikrastis\n    {FFFFFF}Pirmas psl.: {00FF00}Paskutiniai banai\n    {FFFFFF}Antras psl.: {00FF00}Gaudomi policijos\n    {FFFFFF}Trecias psl: {00FF00}Rekordas\n    {FFFFFF}Ketvirtas psl.: {00FF00}Statistika\n    {FFFFFF}Penktas psl.: {00FF00}Paskutinis atnaujinimas","Uzversti","Kitas psl.");
	return 1;
}
CMD:upolicijag(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==80 || playerDB[playerid][specialybe] == 81 || playerDB[playerid][specialybe] == 83 || playerDB[playerid][specialybe] == 84 || playerDB[playerid][admin])
	{
		garazostatus = 0;
		MoveObject(policijaaa,1589.328613, -1638.230591, 14.832096, 1.0001);
	}
	return 1;
}
/*
CMD:astaff(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==80 || playerDB[playerid][specialybe] == 81 || playerDB[playerid][specialybe] == 82 || playerDB[playerid][specialybe] == 83 || playerDB[playerid][specialybe] == 84 || playerDB[playerid][admin])
	{
		MoveObject(apsauginiams,3219.03, -987.31, 293.62194824219, 1.0001);
		GameTextForPlayer(playerid,"~g~Vartai uzsidarys po 10sec.",5000,5);
		SetTimerEx("Varteliai",10000,0,"i",11);
	}
	return 1;
}
CMD:ustaff(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==80 || playerDB[playerid][specialybe] == 81 || playerDB[playerid][specialybe] == 83 || playerDB[playerid][specialybe] == 84 || playerDB[playerid][admin])
	{
		MoveObject(apsauginiams,3218.9348144531, -978.31512451172, 293.62194824219, 1.0001);
	}
	return 1;
}
*/
/*
CMD:azona(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==80 || playerDB[playerid][specialybe] == 81 || playerDB[playerid][specialybe] == 82 || playerDB[playerid][specialybe] == 83 || playerDB[playerid][specialybe] == 84|| playerDB[playerid][admin])
	{
	    if(!IsPlayerInRangeOfPointEx(10.0,playerid,3182.4892578125, -970.32940673828, 293.59725952148)) return SendInfoMessage(playerid,"Jus per toli nuo vartu!");
		MoveObject(iejimaz,3182.4892578125, -982.32940673828, 293.59725952148, 1.0001);
		GameTextForPlayer(playerid,"~g~Vartai uzsidarys po 10sec.",5000,5);
		SetTimerEx("Varteliai",10000,0,"i",12);
	}
	return 1;
}
CMD:uzona(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==80 || playerDB[playerid][specialybe] == 81 || playerDB[playerid][specialybe] == 83 || playerDB[playerid][specialybe] == 84 || playerDB[playerid][admin])
	{
		MoveObject(iejimaz,3182.4892578125, -970.32940673828, 293.59725952148, 1.0001);
	}
	return 1;
}
*/
CMD:aliftas(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==80 || playerDB[playerid][specialybe] == 81 || playerDB[playerid][specialybe] == 82 || playerDB[playerid][specialybe] == 83 || playerDB[playerid][specialybe] == 84 || playerDB[playerid][admin])
	{
		MoveObject(liftas,1569.856567, -1637.569091, 27.559857, 1.0001);
		GameTextForPlayer(playerid,"~g~Liftas nusileis po  20sec.",5000,5);
		SetTimerEx("Varteliai",20000,0,"i",1);
	}
	return 1;
}
CMD:uliftas(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==80 || playerDB[playerid][specialybe] == 81 || playerDB[playerid][specialybe] == 83 || playerDB[playerid][specialybe] == 84 || playerDB[playerid][admin])
	{
		MoveObject(liftas,1569.856567, -1637.569091, 12.859857, 1.0001);
	}
	return 1;
}
// pasienis
/*
CMD:upasienis(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==42 || playerDB[playerid][admin] || playerDB[playerid][prez])
	{
		MoveObject(pasienis,72.232567, -1533.768188, 6.978306, 1.0001);
	}
	return 1;
}*/
CMD:apasienis(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==42 || playerDB[playerid][admin] || playerDB[playerid][prez] || playerDB[playerid][specialybe] == 82)
	{
		//MoveObject(pasienis,72.348999, -1533.765503, 0.480380, 1.0001);
		RotateObject(pasienis,0,0,90);
		RotateObject(pasienis2,0,0,90);
		GameTextForPlayer(playerid,"~g~Vartai uzsidarys po 10sec.",5000,5);
		SetTimerEx("Varteliai",10000,0,"i",2);
		SetTimerEx("Varteliai",10000,0,"i",3);
	}
	return 1;
}


// BMX
/*
CMD:ubmx(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==36 || playerDB[playerid][admin] || playerDB[playerid][prez])
	{
		MoveDynamicObject(bmxx, 1861.897217, -1380.626831, 15.324156, 1.0001);
	}
	return 1;
}

CMD:abmx(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==36 || playerDB[playerid][admin] || playerDB[playerid][prez])
	{
		MoveDynamicObject(bmxx, 1861.906128, -1392.156128, 15.305244, 1.0001);
		GameTextForPlayer(playerid,"~g~Vartai uzsidarys po 10sec.",5000,5);
		SetTimerEx("Varteliai",10000,0,"i",3);
		return 1;
	}
	return 1;
}
*/


//Mechanikai
/*
CMD:umechanikai(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==6 || playerDB[playerid][admin] || playerDB[playerid][prez])
	{
		MoveDynamicObject(mechanikai, 1647.9857177734, -1540.3292236328, 15.339853286743, 1.0001);
	}
	return 1;
}
CMD:amechanikai(playerid,params[])
{
	#pragma unused params
	if(playerDB[playerid][specialybe]==6 || playerDB[playerid][admin] || playerDB[playerid][prez])
	{
		MoveDynamicObject(mechanikai, 1647.9857177734, -1540.3292236328, 9.339853286743, 1.0001);
		GameTextForPlayer(playerid,"~g~Vartai uzsidarys po 10sec.",5000,5);
		SetTimerEx("Varteliai",10000,0,"i",4);
		return 1;
	}
	return 1;
}
*/
//Vartu pabaiga

CMD:sokti(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	new sokis = random(3);
	if (sokis == 0){
		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE1);
	}else if (sokis == 1){
		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE2);
	}else{
		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE4);
	}

	return 1;
}
CMD:rankos(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	if(PFreezed[playerid] || playerDB[playerid][ant] || playerDB[playerid][suristas] || Bomzauja[playerid] || playerDB[playerid][mire]) return SendInfoMessage(playerid,"Tu negali pakelti ranku!");
	SetPlayerSpecialAction(playerid,SPECIAL_ACTION_HANDSUP);
	return 1;
}
CMD:sexy(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	ApplyAnimation(playerid, "PED", "WOMAN_walksexy",4.1,1,0,0,0,0);
	return 1;
}
CMD:gulet(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	//ApplyAnimation(playerid, "BEACH", "bather", 4.000000, 0, 0, 0, 0, 1); // Guleti
	LoopingAnim(playerid,"BEACH", "bather",4.0,1,1,1,1,1);
	return 1;
}
CMD:yohyoh(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	ApplyAnimation(playerid, "benchpress", "gym_bp_celebrate", 4.000000, 1, 0, 0, 0, 0); // Joh joh
	return 1;
}
CMD:ateik(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	ApplyAnimation(playerid, "CAMERA", "camstnd_cmon", 4.000000, 1, 0, 0, 0, 0); //ateikit
	return 1;
}
CMD:spresti(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	ApplyAnimation(playerid, "COP_AMBIENT", "Coplook_loop", 4.000000, 1, 0, 0, 0, 0); //rankos
	return 1;
}
CMD:aaa(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	if(CheckZone(playerid) != 0 || playerDB[playerid][ant] || playerDB[playerid][suristas]) return SendInfoMessage(playerid,"Cia sitos komandos naudoti negali!");
	ApplyAnimation(playerid, "DODGE", "Cover_Dive_01", 4.000000, 0, 1, 1, 0, 0); // Sok
	return 1;
}
CMD:pirmyn(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	ApplyAnimation(playerid, "POLICE", "CopTraf_Away", 4.000000, 1, 0, 0, 0, 0); //Pirmyn
	return 1;
}
CMD:kungfu(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	ApplyAnimation(playerid, "PARK", "Tai_Chi_Loop", 4.000000, 1, 0, 0, 0, 0); //kungFu
	return 1;
}
CMD:baik(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	if(GetPlayerSpecialAction(playerid) == 68) return SendInfoMessage(playerid,"Spausk Enter!");
	new anim = GetPlayerAnimationIndex(playerid);
	if(anim == 1130)
	{
		AC_Kick(playerid,"Bug");
		//Kick(playerid);
	}
	if(GetPVarInt(playerid, "selfie") == 1)
	{
		cmd_selfie(playerid,"");
	}
	if((GetTickCount () - CBugShot[playerid]) < 350)
	{
		CBugWarnings[playerid]++;
		if (CBugWarnings[playerid] > 12)
		{
			AC_Kick(playerid,"C-Bug",1);
			return 1;
		}
		if (CBugWarnings[playerid] > 10)
		{
			SendClientMessage (playerid, COLOR_GREEN, " * LSG Anti-Cheat: Prasome nenaudoti CBug, nes gausite kick/ban.");
		}
		ApplyAnimation( playerid, "PED", "XPRESSscratch", 0.0, 1, 0, 0, 0, 1000, 1 );
	}
	if(RocketManager == playerid)
	{
		RocketSet(playerid,false);
		new msg[256];
		format(msg,256,"Nustatyti pozicijà\nNustatyti laikmatá (%i min)\n{ff5733}Paleisti atominæ bombà", RocketDelay);
		ShowPlayerDialog(playerid, 7444, DIALOG_STYLE_LIST, "BOMBOS VALDYMO PUNKTAS", msg, "Gerai","Atsaukti");
		return 1;
	}
//	ClearAnimations(playerid);
	ApplyAnimation(playerid, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 0, 0);
	return 1;
}
CMD:veiksmai2(playerid,params[])
{
	SendClientMessage(playerid,0xF50AF5FF,"Veiksmai2:");
    SendClientMessage(playerid,0x9E5FA0FF,"/fall /fallback /injured /akick /push /handsup /lowbodypush /bomb /getarrested");
    SendClientMessage(playerid,0x9E5FA0FF,"/headbutt /spray /robman /lookout /kiss /crossarms /box /chant /finger /rap");
    SendClientMessage(playerid,0x9E5FA0FF,"/deal /crack /smoke /groundsit /fucku /hide /vomit /laugh /sup /lowthrow");
    SendClientMessage(playerid,0x9E5FA0FF,"/koface /kostomach /rollfall /bat /lightcig /tapcig /pee /lean");
    SendClientMessage(playerid,0x9E5FA0FF,"/lifejump /leftslap /hoodfrisked /highthrow /aim /walkold /dance");
    SendClientMessage(playerid,0x9E5FA0FF,"/shouting /knife /cop /elbow /kneekick /airkick /gpunch /fstance");
    return true;
}

CMD:veiksmai3(playerid, params[])
{
	SendClientMessage(playerid,COLOR_YELLOW,"Veiksmai3:");
    SendClientMessage(playerid,COLOR_WHITE,"/basket /medic /spray /taichi");
    SendClientMessage(playerid,COLOR_WHITE,"/hike /fuck");
    SendClientMessage(playerid,COLOR_WHITE,"/tired /scratch /eat /stance");
    SendClientMessage(playerid,COLOR_WHITE,"/flag /giver /look /show /endchat /face");
	return 1;
}		
CMD:face(playerid, params[])
{
	new choice[24];
   	if(GetPlayerVehicleID(playerid) != 0) SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	else
	{
	    if(sscanf(params, "s[24]", choice)) return SendClientMessage(playerid, COLOR_WHITE, "/face [1-6]");
		if(strcmp(choice, "1", true) == 0)
		{
			LoopingAnim(playerid,"PED","facanger",3.0,1,1,1,1,1);
			return 1;
		}
		else if(strcmp(choice, "2", true) == 0)
		{
			LoopingAnim(playerid,"PED","facgum",3.0,1,1,1,1,1);
			return 1;
		}
		else if(strcmp(choice, "3", true) == 0)
		{
			LoopingAnim(playerid,"PED","facsurp",3.0,1,1,1,1,1);
			return 1;
		}
		else if(strcmp(choice, "4", true) == 0)
		{
			LoopingAnim(playerid,"PED","facsurpm",3.0,1,1,1,1,1);
			return 1;
		}
		else if(strcmp(choice, "5", true) == 0)
		{
			LoopingAnim(playerid,"PED","factalk",3.0,1,1,1,1,1);
			return 1;
		}
		else if(strcmp(choice, "6", true) == 0)
		{
			LoopingAnim(playerid,"PED","facurios",3.0,1,1,1,1,1);
			return 1;
		}
	}
	return 1;
}
CMD:endchat(playerid, params[])
{
	new choice[24];
   	if(GetPlayerVehicleID(playerid) != 0) SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	else
	{
	    if(sscanf(params, "s[24]", choice)) return SendClientMessage(playerid, COLOR_WHITE, "/endchat [1-3]");
		if(strcmp(choice, "1", true) == 0)
		{
			OnePlayAnim(playerid,"PED","endchat_01",8.0,0,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "2", true) == 0)
		{
			OnePlayAnim(playerid,"PED","endchat_02",8.0,0,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "3", true) == 0)
		{
			OnePlayAnim(playerid,"PED","endchat_03",8.0,0,0,0,0,0);
			return 1;
		}
	}
	return 1;
}
CMD:show(playerid, params[])
{
   	if(GetPlayerVehicleID(playerid) != 0) SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	else
	{
		LoopingAnim(playerid,"ON_LOOKERS","point_loop",3.0,1,0,0,0,0);
		return 1;
	}	
	return 1;
}
CMD:look(playerid, params[])
{
	new choice[24];
   	if(GetPlayerVehicleID(playerid) != 0) SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	else
	{
	    if(sscanf(params, "s[24]", choice)) return SendClientMessage(playerid, COLOR_WHITE, "/look [1-4]");
		if(strcmp(choice, "1", true) == 0)
		{
			LoopingAnim(playerid,"ON_LOOKERS","lkup_loop",3.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "2", true) == 0)
		{
			LoopingAnim(playerid,"ON_LOOKERS","lkaround_loop",3.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "3", true) == 0)
		{
			LoopingAnim(playerid,"PED","flee_lkaround_01",3.0,1,1,1,1,1);
			return 1;
		}
		else if(strcmp(choice, "4", true) == 0)
		{
			OnePlayAnim(playerid,"BAR","Barserve_bottle",3.0,0,1,1,1,0);
			return 1;
		}
	}
	return 1;
}
CMD:giver(playerid, params[])
{
	new choice[24];
   	if(GetPlayerVehicleID(playerid) != 0) SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	else
	{
	    if(sscanf(params, "s[24]", choice)) return SendClientMessage(playerid, COLOR_WHITE, "/giver [1-2]");
		if(strcmp(choice, "1", true) == 0)
		{
			OnePlayAnim(playerid,"KISSING","gift_give",3.0,0,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "2", true) == 0)
		{
			OnePlayAnim(playerid,"BAR","Barserve_give",3.0,0,0,0,0,0);
			return 1;
		}
	}
	return 1;
}

CMD:flag(playerid, params[])
{
	if(GetPlayerVehicleID(playerid) != 0) SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	else
	{
		OnePlayAnim(playerid,"CAR","flag_drop",3.0,0,0,0,0,0);
		return 1;
	}	
	return 1;
}
CMD:stance(playerid, params[])
{
	new choice[24];
	if(GetPlayerVehicleID(playerid) != 0) SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	else
	{
	    if(sscanf(params, "s[24]", choice)) return SendClientMessage(playerid, COLOR_WHITE, "/stance [1-13]");
		if(strcmp(choice, "1", true) == 0)
		{
			LoopingAnim(playerid,"DEALER","DEALER_IDLE",4.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "2", true) == 0)
		{
			LoopingAnim(playerid,"PED","WOMAN_IDLESTANCE",4.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "3", true) == 0)
		{
			LoopingAnim(playerid,"PED","CAR_HOOKERTALK",4.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "4", true) == 0)
		{
			LoopingAnim(playerid,"FAT","FatIdle",4.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "5", true) == 0)
		{
			LoopingAnim(playerid,"WUZI","Wuzi_Stand_Loop",4.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "6", true) == 0)
		{
			LoopingAnim(playerid,"GRAVEYARD","mrnf_loop",4.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "7", true) == 0)
		{
			LoopingAnim(playerid,"GRAVEYARD","mrnm_loop",4.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "8", true) == 0)
		{
			LoopingAnim(playerid,"GRAVEYARD","prst_loopa",4.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "9", true) == 0)
		{
			LoopingAnim(playerid,"PED","idlestance_fat",4.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "10", true) == 0)
		{
			LoopingAnim(playerid,"PED","idlestance_old",4.0,1,0,0,0,0);
			return 1;
		}
		/*else if(strcmp(choice, "11" true) == 0)
		{
			LoopingAnim(playerid,"PED","turn_l",4.0,1,0,0,0,0);
			return 1;
		}*/
		else if(strcmp(choice, "11", true) == 0)
		{
			LoopingAnim(playerid,"PED","turn_l",4.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "12", true) == 0)
		{
			LoopingAnim(playerid,"BAR","Barcustom_loop",4.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "13", true) == 0)
		{
			LoopingAnim(playerid,"BAR","Barserve_loop",4.0,1,0,0,0,0);
			return 1;
		}
	}
	return 1;
}
CMD:eat(playerid, params[])
{
	if(GetPlayerVehicleID(playerid) != 0) SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	else	
	{
		OnePlayAnim(playerid, "FOOD", "EAT_Burger", 3.0, 0, 0, 0, 0, 0);
		return 1;
	}	
	return 1;
}
CMD:scratch(playerid, params[])
{
	if(GetPlayerVehicleID(playerid) != 0) SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	else	
	{
		LoopingAnim(playerid,"MISC","Scratchballs_01",3.0,1,0,0,0,0);
		return 1;
	}	
	return 1;
}
CMD:tired(playerid, params[])
{
	new choice[24];
	if(GetPlayerVehicleID(playerid) != 0) SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	else
	{
	    if(sscanf(params, "s[24]", choice)) return SendClientMessage(playerid, COLOR_WHITE, "/tired [1-2]");
		if(strcmp(choice, "1", true) == 0)
		{
			LoopingAnim(playerid,"PED","IDLE_tired",3.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "2", true) == 0)
		{
			OnePlayAnim(playerid,"FAT","Idle_Tired",3.0,1,0,0,0,0);
			return 1;
		}
	}
	return 1;
}
/*
CMD:caract(playerid, params[])
{
	new choice[24];
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendClientMessage(playerid, COLOR_GREY, " * Privalai vairuoti masina!");
	{
	    if(sscanf(params, "s[24]", choice)) return SendClientMessage(playerid, COLOR_WHITE, "/caract [1-6]");
		if(strcmp(choice, "1", true) == 0)
		{
			LoopingAnim(playerid,"PED","TAP_HAND",4.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "2", true) == 0)
		{
			LoopingAnim(playerid,"CAR", "sit_relaxed", 4.0, 1, 0, 0, 0, 0);
			return 1;
		}
		else if(strcmp(choice, "3", true) == 0)
		{
			LoopingAnim(playerid,"CAR", "tap_hand", 4.0, 1, 0, 0, 0, 0);
			return 1;
		}
		else if(strcmp(choice, "4", true) == 0)
		{
			LoopingAnim(playerid,"CAR_CHAT", "carfone_loopa", 4.0, 1, 0, 0, 0, 0);
			return 1;
		}
		else if(strcmp(choice, "5", true) == 0)
		{
			LoopingAnim(playerid,"CAR_CHAT", "carfone_loopb", 4.0, 1, 0, 0, 0, 0);
			return 1;
		}
		else if(strcmp(choice, "6", true) == 0)
		{
			OnePlayAnim(playerid,"DRIVEBYS","Gang_DrivebyLHS",3.0,0,0,0,0,0);
			return 1;
		}
	}
	return 1;
}	
*/
CMD:taichi(playerid, params[])
{
	if(GetPlayerVehicleID(playerid) != 0) SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	else
	{
		LoopingAnim(playerid,"PARK","Tai_Chi_Loop",4.0,1,0,0,0,0);
		return 1;
	}	
	return 1;
}

CMD:hike(playerid, params[])
{
	new choice[24];
	if(GetPlayerVehicleID(playerid) != 0) SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	else
	{
	    if(sscanf(params, "s[24]", choice)) return SendClientMessage(playerid, COLOR_WHITE, "/hike [1-3]");
		if(strcmp(choice, "1", true) == 0)
		{
			LoopingAnim(playerid,"MISC","hiker_pose",4.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "2", true) == 0)
		{
			LoopingAnim(playerid,"MISC","hiker_pose_l",4.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "3", true) == 0)
		{
			OnePlayAnim(playerid,"PED","idle_taxi",3.0,0,0,0,0,0);
			return 1;
		}
	}
	return 1;
}
CMD:fuck(playerid, params[])
{
	new choice[24];
	if(GetPlayerVehicleID(playerid) != 0) SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	else
	{
	    if(sscanf(params, "s[24]", choice)) return SendClientMessage(playerid, COLOR_WHITE, "/fuck [1-2]");
		if(strcmp(choice, "1", true) == 0)
		{
			OnePlayAnim(playerid,"PED","fucku",4.0,0,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "2", true) == 0)
		{
			OnePlayAnim(playerid,"RIOT","RIOT_FUKU",2.0,0,0,0,0,0);
			return 1;
		}
	}
	return 1;
}
	

CMD:basket(playerid, params[])
{
	new choice[24];
	if(GetPlayerVehicleID(playerid) != 0) SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	else
	{
	    if(sscanf(params, "s[24]", choice)) return SendClientMessage(playerid, COLOR_WHITE, "/basket [1-4]");
		if(strcmp(choice, "1", true) == 0)
		{
			LoopingAnim(playerid,"BSKTBALL","BBALL_idleloop",4.0,1,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "2", true) == 0)
		{
			OnePlayAnim(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
			return 1;
		}
		else if(strcmp(choice, "3", true) == 0)
		{
			LoopingAnim(playerid,"BSKTBALL","BBALL_run",4.1,1,1,1,1,1);
			return 1;
		}
		else if(strcmp(choice, "4", true) == 0)
		{
			LoopingAnim(playerid,"BSKTBALL","BBALL_def_loop",4.0,1,0,0,0,0);
			return 1;
		}
	}
	return 1;
}
CMD:medic(playerid, params[])
{
	if(GetPlayerVehicleID(playerid) != 0) SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	else
	{
		OnePlayAnim(playerid,"MEDIC","CPR",4.0,0,0,0,0,0);
		return 1;
	}	
	return 1;
}


CMD:mot(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	ApplyAnimation(playerid, "KISSING", "gfwave2", 4.000000, 0, 0, 0, 0, 0);
	return 1;
}
CMD:trenkt(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	ApplyAnimation(playerid, "SWEET", "sweet_ass_slap", 4.000000, 0, 0, 0, 0, 0);
	return 1;
}

CMD:wank(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	//ApplyAnimation(playerid, "PAULNMAC", "wank_loop", 4.000000, 1, 0, 0, 0, 0);
	LoopingAnim(playerid,"PAULNMAC", "wank_loop",4.0,1,0,0,0,0);
	return 1;
}


CMD:taip(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	ApplyAnimation(playerid, "GANGS", "Invite_Yes", 4.000000, 0, 0, 0, 0, 0);
	if(playerDB[playerid][textas])
		OnPlayerText(playerid, "taip");
	return 1;
}
CMD:ne(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	ApplyAnimation(playerid, "GANGS", "Invite_No", 4.000000, 0, 0, 0, 0, 0);
	if(playerDB[playerid][textas])
		OnPlayerText(playerid, "taip");
	return 1;
}
CMD:parkour(playerid,params[])
{
	#pragma unused params
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	ApplyAnimation(playerid, "DAM_JUMP", "DAM_Dive_Loop", 4.000000, 1, 0, 0, 0, 0);
	return 1;
}

CMD:r(playerid,params[])
{
		new textaz[128];
		if (sscanf(params, "s[128]",textaz)) return SendInfoMessage(playerid,"Noredami kalbeti per racija rasykite: /r [tekstas]");

		/*if(!(playerDB[playerid][specialybe] == 1 || playerDB[playerid][specialybe] == 3 || playerDB[playerid][specialybe] == 2 || playerDB[playerid][specialybe] == 10 || playerDB[playerid][specialybe] == 6 || playerDB[playerid][specialybe] == 66 ||
		playerDB[playerid][specialybe] == 7 || playerDB[playerid][specialybe] == 70 || playerDB[playerid][specialybe] == 71 || playerDB[playerid][specialybe] == 72 || playerDB[playerid][specialybe] == 73 || playerDB[playerid][specialybe] == 80 ||
		playerDB[playerid][specialybe] == 81 || playerDB[playerid][specialybe] == 82 || playerDB[playerid][specialybe] == 83 || playerDB[playerid][specialybe] == 67 || playerDB[playerid][specialybe] == 44 ||
		playerDB[playerid][specialybe] == 50 || playerDB[playerid][specialybe] == 58 || playerDB[playerid][specialybe] == 31 || playerDB[playerid][specialybe] == 32 || playerDB[playerid][specialybe] == 41 || playerDB[playerid][specialybe] == 39 || playerDB[playerid][specialybe] == 20 || playerDB[playerid][specialybe] == 28 || playerDB[playerid][specialybe] == 84))
*/
		if(!playerDB[playerid][specialybe])
		{
			SendInfoMessage(playerid,"Jus neturite darbines racijos.");
			return 1;
		}

		new msg[128],name[MAX_PLAYER_NAME];
		GetPlayerName(playerid,name,sizeof(name));
		format(msg,sizeof(msg),"[racija] %s: %s",name,textaz);
		if(playerDB[playerid][plead] > 0)
			format(msg,sizeof(msg),"[racija] Dir. %s: %s",name,textaz);


		if(playerDB[playerid][specialybe] == 80) SendMessageToTeisesauga(0xFFFFFF30,msg); // policija balta
		else if(playerDB[playerid][specialybe] == 81) SendMessageToTeisesauga(0x33CCFFAA,msg); // swat zydra
		
		else if( playerDB[playerid][specialybe] == 83) SendMessageToTeisesauga(0xC1762B30,msg); // kareivis ruda
		else if(playerDB[playerid][specialybe] == 84) SendMessageToTeisesauga(0xE3B92430,msg); // kobra 11 auksine
		
		else if(playerDB[playerid][specialybe] == 82) SendMessageToTeisesauga(PURPLE,msg); // VST
		
		else if(playerDB[playerid][specialybe] == 2) SendMessageToMedics(PURPLE,msg); // medikai
		else if(playerDB[playerid][specialybe] == 93) SendMessageToMedics(0xFFFFFF30,msg); // medikai


		else if(playerDB[playerid][specialybe] == 66) SendMessageToGaisras(0xFFFFFFFF,msg); // gaisrininkai
		else if(playerDB[playerid][specialybe] == 3) SendMessageToTransportas(0xFFFFFFFF,msg); // taxi balta


		else if(playerDB[playerid][specialybe] == 20) SendMessageToTransportas(0x33CCFFAA,msg); // trans melyna
		//else if(playerDB[playerid][specialybe] == 39) SendMessageToTransportas(0x98B13490,msg); // limuzin zalia

		else if(playerDB[playerid][specialybe] == 6) SendMessageToAutospecai(0x33CCFFAA,msg); // mech melyn

		else if(playerDB[playerid][specialybe] == 31) {SendMessageToKont(0x33CCFFAA,msg); SendMessageToDeal(0x33CCFFAA,msg);}// kont melyn
		else if(playerDB[playerid][specialybe] == 32) { SendMessageToKont(0xFFFFFF30,msg);  SendMessageToDeal(0xFFFFFF30,msg);}// deal balta



		else if(playerDB[playerid][specialybe] == 50) SendMessageToValstybe(0x98B13490,msg); // skelbejai

		else if(playerDB[playerid][specialybe] == 70 ) SendMessageToKlubai(0xE3B92430,msg); // automanai GOLD
		//else if(playerDB[playerid][specialybe] == 72 ) SendMessageToKlubai(0x33CCFFAA,msg); // JACHTOS ZYDRA
		else if(playerDB[playerid][specialybe] == 73 ) SendMessageToKlubai(0xFFFFFF30,msg); // motomanai melyna
		else if(playerDB[playerid][specialybe] == 71 ) SendMessageToBaikeriai(0xFFFFFF30,msg); // baikeriai
		
		else if(playerDB[playerid][specialybe] == 41 ) SendMessageToFuristai(0xFFFFFF30,msg); // furistai balta
		else if(playerDB[playerid][specialybe] == 44 ) SendMessageToFuristai(0x33CCFFAA,msg); // kurjeriai melyna
		
		
		else if(playerDB[playerid][specialybe] == 58 ) SendMessageToSunys(0xE3B92430,msg); // vagys
		else if(playerDB[playerid][specialybe] == 34 ) SendMessageToNTA(0xE3B92430,msg);
		else if(playerDB[playerid][specialybe] == 60 ) SendMessageToInka(0xE3B92430,msg);
		else
		{
		    foreach(Player, i)
		        if(playerDB[i][specialybe] == playerDB[playerid][specialybe])
		            SendClientMessage(i,0xFFFFFF30,msg);
		}
		return 1;

}


CMD:parduotinama(playerid,params[])
{
	#pragma unused params
	new pname[24],housenumber;

	housenumber = GetHouseID(playerid);
	GetPlayerName(playerid, pname, 24);
	if(housenumber < 0) return SendInfoMessage(playerid,"Jus neesate prie namo!");
	if(TradingWith[playerid] != -1) return SendInfoMessage(playerid,"Uzdaryk mainus!");
	if (strcmp(hInfo[housenumber][Name],pname,false)) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
	new msg[256];
	format(msg,sizeof(msg),"Ar tikrai norite parduoti savo nama?\nUz ji gautumete %i€ i rankas.",(hInfo[housenumber][Cost] /4));
	ShowPlayerDialog(playerid,3995,DIALOG_STYLE_MSGBOX,"Namas",msg,"Taip","Ne");
	return 1;
}

CMD:pirktinama(playerid,params[])
{
	#pragma unused params
	new str[255],pname[24], housenumber;
	housenumber = GetHouseID(playerid);
	if(housenumber < 0) return SendInfoMessage(playerid,"Jus neesate prie namo!");

	GetPlayerName(playerid, pname, 24);

	if (strcmp(hInfo[housenumber][Name],"Nera",true)) return SendInfoMessage(playerid,"Sis namas neparduodamas!");
	new kaina = hInfo[housenumber][Cost];
	if(playerDB[playerid][specialybe] ==34) 
	{
		kaina = kaina/2;
	}

	if(GetPlayerMoneyA(playerid)<kaina) return SendInfoMessage(playerid,"Neuztenka pinigu!");
	if(playerDB[playerid][namu] >= GetNamuLimit(playerid)) return SendInfoMessage(playerid,"Jus jau turite 2 namus.");
	SendInfoMessage(playerid,"Jus nusipirkote nama!");
	playerDB[playerid][namu]++;
	format(str, sizeof(str), "%s Nusipirko houseid 0",pname);
	print(str);
	GivePlayerMoneyA(playerid, -kaina);
	ProcessAchievement(playerid, 108);
	if(playerDB[playerid][specialybe] ==34) 
		Pelnas(playerid,33,floatround(kaina/4));
	new query[256];
	format(query,sizeof(query),"UPDATE `Namai` SET `Name`='%s',`Krumeliai`=0,`Locked`=0,`bMokesciai`=14 WHERE `ID`=%i",pname,housenumber);
	mysql_query(query);
	hInfo[housenumber][Name]=pname;
	hInfo[housenumber][hMokesciai]=14;
	hInfo[housenumber][Locked] = 0;
	MLog(playerid,"Nusipirko nama","i", housenumber);

	DestroyPickup(HousePickup[housenumber]);
	DestroyDynamic3DTextLabel(HouseText[housenumber]);
	new vw;
	if(hInfo[housenumber][daugiabutis]) vw=(MAX_HOUSES*2+MAX_BUSINESSES+hInfo[housenumber][daugiabutis]-1);
	HousePickup[housenumber] = CreatePickupA(1272, 23, hInfo[housenumber][iconx], hInfo[housenumber][icony], hInfo[housenumber][iconz],vw);
	new zinute[512];
	format(zinute,sizeof(zinute),"{FFFFFF}Namas Nr.: {FF0000}%i\n{FFFFFF}Savininkas: {FF0000}%s",housenumber,hInfo[housenumber][Name]);
	HouseText[housenumber] = CreateDynamic3DTextLabel(zinute, COLOR_WHITE, hInfo[housenumber][iconx], hInfo[housenumber][icony], hInfo[housenumber][iconz], 50, _,_, 1,vw);
	new querfr[240];
	format(querfr,sizeof(querfr),"UPDATE `Namai` SET `bMokesciai`=%i WHERE ID=%i",hInfo[housenumber][hMokesciai],housenumber);
	mysql_query(querfr);
	ProcessAchievement(playerid,19);
	SavePlayerData(playerid,true);
	if(hInfo[housenumber][polyId] != -1)
	{
		ShowPlayerDialog(playerid, 9530, DIALOG_STYLE_MSGBOX, "Apartamentai", "Sveikiname ásigyjus vienà prestiþiðkiausiø Los Santos apartamentø!\n\nJuo galite naudotis visiðkai kaip ir kitais namais, iðskyrus kelias smulkmenas:\n\
		• Negalite daþyti namo sienø ir durø.\n\
		• Negalite namo remontuoti.\n\
		• Galite uþrakinti lifto duris uþlipæ ant ðio pickup.\n\
		• Privalote baldus statyti tvarkingai. Uþ per sienas/lubas/grindis iðlindusius baldus ið jûsø bus atimtas namas be jokio perspëjimo.\n\n\nLinkime jaukaus ir patogaus gyvenimo jûsø naujàjame name!", "Gerai","");
	}
	return 1;
}






CMD:uzrakinti(playerid,params[])
{
	#pragma unused params
	return SendInfoMessage(playerid,"Naudokite /rakinti");
}

CMD:atrakinti(playerid,params[])
{
	#pragma unused params
	return SendInfoMessage(playerid,"Naudokite /rakinti");
}

CMD:nenuomoti(playerid,params[])
{
	new pname[24],housenumber;
	housenumber = GetHouseID(playerid);
	if(housenumber == -255) return SendInfoMessage(playerid,"Privalote stoveti prie namo!");
	GetPlayerName(playerid, pname, 24);

	if (strcmp(hInfo[housenumber][Name],pname,true)) return SendInfoMessage(playerid,"Sis namas ne jusu!");
	SendInfoMessage(playerid,"Jusu namas nebenuomojamas!");
	hInfo[housenumber][Rentable] = 0;
	hInfo[housenumber][Rentcost] = 0;
	format(hInfo[housenumber][Renter], 24, "ForRent");
	new query[128];
	format(query,sizeof(query),"UPDATE `Namai` SET `Rentable`=0,`Rentcost`=0,`Renter`='ForRent' WHERE `ID`=%i",housenumber);
	mysql_query(query);
	return 1;

}

CMD:nuomoti(playerid,params[])
{
	new pname[24],housenumber;
	housenumber = GetHouseID(playerid);
	if(housenumber == -255) return SendInfoMessage(playerid,"Privalote stoveti prie namo!");
	GetPlayerName(playerid, pname, 24);
	new rentcost;
	if(sscanf(params,"d",rentcost)) return SendInfoMessage(playerid,"/nuomuoti [kaina uz valanda]");
	if(rentcost < 10 || rentcost > 1000) return SendInfoMessage(playerid,"Nuomos kaina nuo 10 iki 1000EUR per valanda!");
	if (strcmp(hInfo[housenumber][Name],pname,true)) return SendInfoMessage(playerid,"Sis namas ne jusu!");

	SendInfoMessage(playerid,"Jusu namas nuomojamas!");
	ProcessAchievement(playerid,20);
	hInfo[housenumber][Rentable] = 1;
	hInfo[housenumber][Rentcost] = rentcost;
	new query[128];
	format(query,sizeof(query),"UPDATE `Namai` SET `Rentable`=1,`Rentcost`=%i WHERE `ID`=%i",rentcost,housenumber);
	mysql_query(query);
	return 1;
}

CMD:nuomotis(playerid,params[])
{
	#pragma unused params
	new pname[24],housenumber;
	housenumber = GetHouseID(playerid);
	if(housenumber == -255) return SendInfoMessage(playerid,"Privalote stoveti prie namo!");
	GetPlayerName(playerid, pname, 24);

	if (strcmp(hInfo[housenumber][Name],"Nera",true)==0) return SendInfoMessage(playerid,"Sis namas neturi savininko!");
	if(strcmp(hInfo[housenumber][Name],pname,true)==0) return SendInfoMessage(playerid,"Negalite nuomotis is saves!");
	if(hInfo[housenumber][Rentable]==0 || strcmp(hInfo[housenumber][Renter], "ForRent", true)) return SendInfoMessage(playerid,"Sis namas nenuomojamas!");
	if(GetPlayerMoneyA(playerid)<hInfo[housenumber][Rentcost]) return SendInfoMessage(playerid,"Neuztenka pinigu!");
	format(hInfo[housenumber][Renter], 24, pname);
	new query[128];
	format(query,sizeof(query),"UPDATE `Namai` SET `Renter`='%s',`RentPay`=0 WHERE `ID`=%i",hInfo[housenumber][Renter],housenumber);
	mysql_query(query);
	new str1[128];
	format(str1, sizeof(str1), "Jus nuomojates si nama, jums kainuos %i € per valanda!", hInfo[housenumber][Rentcost]);
	SendClientMessage(playerid, c_y, str1);
	return 1;
}

/*
// Gangster Walking

CMD:walkgangsta(playerid,params[])
{
    if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
    new dancestyle;
	if(sscanf(params,"d",dancestyle)) return SendInfoMessage(playerid,"Naudojimas: /walkgangsta [1-2]");
	switch (dancestyle)
	{
    	case 1: LoopingAnim(playerid,"PED","WALK_gang1",4.1,1,1,1,1,1);
     	case 2: LoopingAnim(playerid,"PED","WALK_gang2",4.1,1,1,1,1,1);
    	default: SendInfoMessage(playerid,"Naudojimas: /walkgangsta [1-2]");
	}
	return 1;
}

// Old Walking
CMD:walkold(playerid,params[])
{
	if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
    new dancestyle;
	if(sscanf(params,"d",dancestyle)) return SendInfoMessage(playerid,"Naudojimas: /walkold [1-2]");
	switch (dancestyle)
	{
    	case 1: LoopingAnim(playerid,"PED","WALK_old",4.1,1,1,1,1,1);
     	case 2: LoopingAnim(playerid,"PED","WALK_fatold",4.1,1,1,1,1,1);
    	default: SendInfoMessage(playerid,"Naudojimas: /walkold [1-2]");
	}
	return 1;
}

// Old Girl
CMD:walkgirl(playerid,params[])
{
    new dancestyle;
    if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	if(sscanf(params,"d",dancestyle)) return SendInfoMessage(playerid,"Naudojimas: /walkgirl [1-4]");
	switch (dancestyle)
	{
    	case 1: LoopingAnim(playerid,"PED","WOMAN_walknorm",4.1,1,1,1,1,1);
     	case 2: LoopingAnim(playerid,"PED","WOMAN_walkbusy",4.1,1,1,1,1,1);
     	case 3: LoopingAnim(playerid,"PED","WOMAN_walkpro",4.1,1,1,1,1,1);
     	case 4: LoopingAnim(playerid,"PED","WOMAN_walksexy",4.1,1,1,1,1,1);
    	default: SendInfoMessage(playerid,"Naudojimas: /walkgirl [1-4]");
	}
	return 1;
}
*/
// Smoking animations
CMD:smoke(playerid,params[])
{
    new dancestyle;
    if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	if(sscanf(params,"d",dancestyle)) return SendInfoMessage(playerid,"Naudojimas: /smoke [1-4]");
	switch (dancestyle)
	{
    	case 1: LoopingAnim(playerid,"SMOKING", "M_smklean_loop", 4.0, 1, 0, 0, 0, 0); // male
    	case 2: LoopingAnim(playerid,"SMOKING", "F_smklean_loop", 4.0, 1, 0, 0, 0, 0); //female
    	case 3: LoopingAnim(playerid,"SMOKING","M_smkstnd_loop", 4.0, 1, 0, 0, 0, 0); // standing-fucked
    	case 4: LoopingAnim(playerid,"SMOKING","M_smk_out", 4.0, 1, 0, 0, 0, 0); // standing
    	default: SendInfoMessage(playerid,"Naudojimas: /smoke [1-4]");
	}
	return 1;
}

// Homie animations
CMD:sup(playerid,params[])
{
    new dancestyle;
    if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	if(sscanf(params,"d",dancestyle)) return SendInfoMessage(playerid,"Naudojimas: /sup [1-3]");
	switch (dancestyle)
	{
    	case 1: OnePlayAnim(playerid,"GANGS","hndshkba",4.0,0,0,0,0,0);
     	case 2: OnePlayAnim(playerid,"GANGS","hndshkda",4.0,0,0,0,0,0);
     	case 3: OnePlayAnim(playerid,"GANGS","hndshkfa_swt",4.0,0,0,0,0,0);
    	default: SendInfoMessage(playerid,"Naudojimas: /sup [1-3]");
	}
	return 1;
}

// Rap animations
CMD:rap(playerid,params[])
{
    new dancestyle;
    if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	if(sscanf(params,"d",dancestyle)) return SendInfoMessage(playerid,"Naudojimas: /rap [1-4]");
	switch (dancestyle)
	{
	    case 1: LoopingAnim(playerid,"RAPPING","RAP_A_Loop",4.0,1,0,0,0,0);
    	case 2: LoopingAnim(playerid,"RAPPING","RAP_C_Loop",4.0,1,0,0,0,0);
    	case 3: LoopingAnim(playerid,"GANGS","prtial_gngtlkD",4.0,1,0,0,0,0);
    	case 4: LoopingAnim(playerid,"GANGS","prtial_gngtlkH",4.0,1,0,0,1,1);
    	default: SendInfoMessage(playerid,"Naudojimas: /rap [1-4]");
	}
	return 1;
}

// Knife animations
CMD:knife(playerid,params[])
{
    new dancestyle;
    if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	if(sscanf(params,"d",dancestyle)) return SendInfoMessage(playerid,"Naudojimas: /knife [1-4]");
	switch (dancestyle)
	{
	    case 1: LoopingAnim(playerid,"KNIFE","KILL_Knife_Ped_Damage",4.0,0,1,1,1,0);
    	case 2: LoopingAnim(playerid,"KNIFE","KILL_Knife_Ped_Die",4.0,0,1,1,1,0);
    	case 3: OnePlayAnim(playerid,"KNIFE","KILL_Knife_Player",4.0,0,0,0,0,0);
    	case 4: LoopingAnim(playerid,"KNIFE","KILL_Partial",4.0,0,1,1,1,1);
    	default: SendInfoMessage(playerid,"Naudojimas: /knife [1-4]");
	}
	return 1;
}

CMD:gwalk(playerid,params[])
{
    new dancestyle;
    if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	if(sscanf(params,"d",dancestyle)) return SendInfoMessage(playerid,"Naudojimas: /gwalk [1/2]");
    new style = dancestyle;
   	if (style == 1)
    {
		LoopingAnim(playerid,"PED","WALK_gang1",4.1,1,1,1,1,1);
    }
    else if (style == 2)
    {
		LoopingAnim(playerid,"PED","WALK_gang2",4.1,1,1,1,1,1);
    }
   	else SendInfoMessage(playerid,"Naudojimas: /gwalk [1/2]");
	return 1;
}

//Aiming animation
CMD:aim(playerid,params[])
{
    new dancestyle;
    if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	if(sscanf(params,"d",dancestyle)) return SendInfoMessage(playerid,"Naudojimas: /aim [1-.]");
	switch (dancestyle)
	{
    	case 1: LoopingAnim(playerid,"PED","gang_gunstand",4.0,1,1,1,1,1);
    	case 2: LoopingAnim(playerid,"PED","Driveby_L",4.0,0,1,1,1,1);
    	case 3: LoopingAnim(playerid,"PED","Driveby_R",4.0,0,1,1,1,1);
    	default: SendInfoMessage(playerid,"Naudojimas: /aim [1-3]");
	}
	return 1;
}


// Leaning animation
CMD:lean(playerid,params[])
{
    new dancestyle;
    if(GetPlayerVehicleID(playerid) != 0) return SendInfoMessage(playerid,"Komanda nenaudojama masinose!");
	if(sscanf(params,"d",dancestyle)) return SendInfoMessage(playerid,"Naudojimas: /lean [1-2]");
	switch (dancestyle)
	{
    	case 1: LoopingAnim(playerid,"GANGS","leanIDLE",4.0,0,1,1,1,0);
    	case 2: LoopingAnim(playerid,"MISC","Plyrlean_loop",4.0,0,1,1,1,0);
    	default: SendInfoMessage(playerid,"Naudojimas: /lean [1-2]");
	}
	return 1;
}

// START DANCING
CMD:dance(playerid,params[])
{
  		if(GetPlayerState(playerid) == PLAYER_STATE_PASSENGER || GetPlayerState(playerid) == PLAYER_STATE_DRIVER) return SendInfoMessage(playerid,"Is masinos galima islipti ir paprasciau!");
		new dancestyle;
		if(sscanf(params,"d",dancestyle)) {
			SendInfoMessage(playerid,"Naudojimas: /dance [1-4]");
			return 1;
		}
		if(dancestyle < 1 || dancestyle > 4) {
		    SendInfoMessage(playerid,"Naudojimas: /dance [1-4]");
		    return 1;
		}

		if(dancestyle == 1) {
		    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE1);
		} else if(dancestyle == 2) {
		    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE2);
		} else if(dancestyle == 3) {
		    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE3);
		} else if(dancestyle == 4) {
		    SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE4);
		}
  		return 1;
}


CMD:radijas(playerid,params[]) return cmd_radija(playerid,params);

CMD:radija(playerid,params[])
{
	#pragma unused params
	if(!IsPlayerInAnyVehicle(playerid)) return SendInfoMessage(playerid,"Komanda naudojama masinoje!");
	//if(!Audio_IsClientConnected(playerid)) return SendClientMessage(playerid,YELLOW,"* Jus neturite radijos plugino. Prasome ji atsisiusti is www.LSGyvenimas.€ Pagalbos skilties");
	//ShowPlayerDialog(playerid,9755,DIALOG_STYLE_LIST,"Radijos","Stabdyti\nKeisti garsa\nZip FM\nM-1\nEuropean Hit Radio\nPower Hit Radio\nHot Fm\nJpa FM\nRadio Centras","Rinktis","Isjungti");
	RadioList(playerid,false);
	return 1;
}

CMD:imtuvas(playerid,params[])
{
	#pragma unused params
	if(!playerDB[playerid][imtuvas]) return SendInfoMessage(playerid,"Jus neturite radijo imtuvo!");
	//if(!Audio_IsClientConnected(playerid)) return SendClientMessage(playerid,YELLOW,"* Jus neturite radijos plugino. Prasome ji atsisiusti is www.LSGyvenimas.€ Pagalbos skilties");
	//ShowPlayerDialog(playerid,9750,DIALOG_STYLE_LIST,"Radijos","Stabdyti\nKeisti garsa\nZip FM\nM-1\nEuropean Hit Radio\nPower Hit Radio\nHot Fm\nJpa FM\nRadio Centras","Rinktis","Isjungti");
	RadioList(playerid,true);
	return 1;
}
CMD:muzika(playerid,params[])
{
	if(!playerDB[playerid][admin]){SendInfoMessage(playerid,"Si komanda tik administratoriams");return 1;}
	//if(!Pareigos(playerid,"DJ")) return SendInfoMessage(playerid,"Jus neturite teises leisti muzikos!");
	new tmpz[128];
	if (sscanf(params, "s[128]", tmpz)) return SendInfoMessage(playerid,"Naudojimas: /muzika [adresas]");
	GetPlayerPos(playerid,g_RadioCord[0],g_RadioCord[1],g_RadioCord[2]);
	strcpy(g_RadioURL,tmpz,sizeof(tmpz));
	g_RadioON=true;

    /*foreach(Player,id) FIX DAT
	{
		//if(Audio_IsClientConnected(id))
		Audio_Stop(id,playerDB[id][klausoisadmin]);
		playerDB[id][klausoisadmin] = Audio_PlayStreamed(id,tmpz,false,false,true);
		Audio_Set3DPosition(id,playerDB[id][klausoisadmin],g_RadioCord[0],g_RadioCord[1],g_RadioCord[2],100);
	}*/
	SendInfoMessage(playerid,"Sekmingai uzleidai muzona!");
	return 1;
}


CMD:nesinuomoti(playerid,params[])
{
	#pragma unused params
	new pname[24],housenumber;
	housenumber = GetHouseID(playerid);
	if(housenumber < 0) return SendInfoMessage(playerid,"Jus neesate prie namo!");
	GetPlayerName(playerid, pname, 24);

	if(strcmp(hInfo[housenumber][Renter], pname, true)) return SendInfoMessage(playerid,"Jus nesinuomojat sito namo!");
    new query[128];
	format(query,sizeof(query),"UPDATE `Namai` SET `Renter`='ForRent' WHERE `ID`=%i",housenumber);
	mysql_query(query);

	format(hInfo[housenumber][Renter], 24, "ForRent");
	SendInfoMessage(playerid,"Jus atsauket namo nuoma!");
	return 1;
} 

CMD:namai(playerid,params[])
{
	#pragma unused params
	//SendClientMessage(playerid, c_y, "Nuomos funkcijos: /nuomoti, /gautinuoma, /moketinuoma, /nesinuomoti, /nuomotis");
	SendClientMessage(playerid, c_y, "Pirkimo, pardavimo funkcijos: /pirktinama, /parduotinama, /siulytinama");
	SendClientMessage(playerid, RED, "Demesio! Parduodami nama(/parduotinama) atgausite 1/4 sumos, uz kiek buvo pirktas namas.");
	SendClientMessage(playerid, RED,"Parduodami zmogui galite nustatyti savo kaina. (/siulytinama [vardas] [suma])");
	SendClientMessage(playerid,COLOR,"Nuomos funkcijos: /nuomoti /nenuomoti /nuomotis /moketinuoma /gautinuoma");
	
	//new pname[MAX_PLAYER_NAME];
	//GetPlayerName(playerid,pname,sizeof(pname));
	new x=0;
	if(playerDB[playerid][specialybe] == 34 || IsPlayerAdmin(playerid))
	{
		SendClientMessage(playerid,BLUE," * NTA komanda: /forsale -> pastato pardavimo zenkla prie namo.");
		new msg[4048];
		format(msg,4048, "Numeris\tTipas\tBûsena\tKaina\tVieta\n");
		foreach(Houses, i) if(x<90)
		{
			new line[128];
			new tipas[30];
			new busena[20];
			new cost;
			if (strcmp(hInfo[i][Name],"Nera",true) == 0)
			{
				busena="{f28c42}Apleistas";
				cost = hInfo[i][Cost];
			}
			else if(fsHouses[i][fobjid] != 0)
			{
				busena="{2495c1}ForSale";	
				cost = fsHouses[i][fcost];
				if(cost > 99 * 1000000)
				{
					continue;
				}
			}
			else 
			{
				continue;
			}

			if(hInfo[i][daugiabutis])
			{
				format(tipas,sizeof(tipas),"Butas (daug. %i)",hInfo[i][daugiabutis]);
			}
			else if(hInfo[i][polyId] != -1)
			{
				format(tipas,sizeof(tipas),"Apartamentas (%s)",JB_gSAZones[Get2DZoneEx(hInfo[i][iconx],hInfo[i][icony])][JB_SAZONE_NAME]);
			}
			else
			{
				format(tipas,sizeof(tipas),"Namas (%s)",JB_gSAZones[Get2DZoneEx(hInfo[i][iconx],hInfo[i][icony])][JB_SAZONE_NAME]);
			}

			format(line, sizeof(line),"%i\t%s\t%s\t%s€", i, tipas, busena, FormatNumber(cost));
			format(msg,sizeof(msg),"%s%s\n",msg,line);
			x++;
		}
		ShowPlayerDialog(playerid,5606,DIALOG_STYLE_TABLIST_HEADERS,"Parduodami namai",msg,"Rasti","Atsaukti");
	}
	return 1;
}


CMD:namostats(playerid,params[])
{
	#pragma unused params
	new str[60],housenumber;
	housenumber = GetHouseID(playerid);
	if(housenumber==-255) return 1;
	if(playerDB[playerid][specialybe] != 34) return SendInfoMessage(playerid," Si komanda skirta tik turto agentams!");
	format(str, sizeof(str), "Savininkas %s", hInfo[housenumber][Name]);
	SendClientMessage(playerid, c_y, str);
	format(str, sizeof(str), "Kaina $%d", hInfo[housenumber][Cost]);
	SendClientMessage(playerid, c_y, str);
	format(str, sizeof(str), "Nuomininkas %s", hInfo[housenumber][Renter]);
	SendClientMessage(playerid, c_y, str);
	format(str, sizeof(str), "Nuomos kaina %d €/ valanda", hInfo[housenumber][Rentcost]);
	SendClientMessage(playerid, c_y, str);
	format(str, sizeof(str), "Interjero lygis %i.", hInfo[housenumber][vidus]+1);
	SendClientMessage(playerid, c_y, str);
	return 1;
}

CMD:gautinuoma(playerid,params[])
{
	#pragma unused params
	new pname[24],housenumber;
	housenumber = GetHouseID(playerid);
	if(housenumber== -255) return 1;
	GetPlayerName(playerid, pname, 24);
	if(strcmp(hInfo[housenumber][Name],pname,false)==0)
	{
		SendInfoMessage(playerid,"Paemet pinigus is nuomininko!");
		new query[128];
		format(query,sizeof(query),"SELECT `RentGet` FROM `Namai` WHERE `ID`=%i",housenumber);
		mysql_function_query(SQL, query, true, "SQL_GautiN", "ii", playerid,housenumber);
		
	}
	else
	{
		SendInfoMessage(playerid,"Sis namas ne jusu!");
	}
	return 1;
}

CMD:moketinuoma(playerid,params[])
{
	#pragma unused params
	new pname[24],housenumber;
	housenumber = GetHouseID(playerid);
	if(housenumber==-255) return 0;
	GetPlayerName(playerid, pname, 24);
	if(strcmp(hInfo[housenumber][Renter],pname,false)==0)
	{
		new query[128];
		format(query,sizeof(query),"SELECT `RentPay` FROM `Namai` WHERE `ID`=%i",housenumber);
		mysql_function_query(SQL, query, true, "SQL_MoketiN", "ii", playerid,housenumber);
		
	}
	else
	{
		SendInfoMessage(playerid,"Jus nenuomojat sio namo!");
	}
	return 1;
}

/*
// Cop walking
CMD:walkregular(playerid,params[]) {

	LoopingAnim(playerid,"PED","WALK_player",4.1,1,1,1,1,1);
	//		(playerid, animlib[], animname[], Float:fDelta, loop, lockx, locky, freeze, time, forcesync)
    return 1;
}
// Cop walking
CMD:walkcop(playerid,params[]) {
	LoopingAnim(playerid,"PED","WALK_civi",4.1,1,1,1,1,1);
	
    return 1;
}

// Fat walking
CMD:walkfat(playerid,params[]) {
	LoopingAnim(playerid,"PED","WALK_fat",4.1,1,1,1,1,1);
    return 1;
}

// Woozie's walking
CMD:walkblind(playerid,params[]) {
	LoopingAnim(playerid,"PED","Walk_Wuzi",4.1,1,1,1,1,1);
    return 1;
}
*/
// carjacked
CMD:carjacked2(playerid,params[]) {
	 LoopingAnim(playerid,"PED","CAR_jackedRHS",4.0,0,1,1,1,0);
     return 1;
}

// HANDSUP
CMD:handsup(playerid,params[]) {
	//SetPlayerSpecialAction(playerid,SPECIAL_ACTION_HANDSUP);
	LoopingAnim(playerid, "ROB_BANK","SHP_HandsUp_Scr", 4.0, 0, 1, 1, 1, 0);
    return 1;
}

// Place a Bomb
CMD:bomb(playerid,params[]) {
	//ClearAnimations(playerid);
	LoopingAnim(playerid, "BOMBER","BOM_Plant_Loop",4.0,1,0,0,1,0); // Place Bomb
	return 1;
}
// Police Arrest
CMD:getarrested(playerid,params[]) {
      LoopingAnim(playerid,"ped", "ARRESTgun", 4.0, 0, 1, 1, 1, -1); // Gun Arrest
	  return 1;
}
// Laugh
CMD:laugh(playerid,params[]) {
      OnePlayAnim(playerid, "RAPPING", "Laugh_01", 4.0, 0, 0, 0, 0, 0); // Laugh
	  return 1;
}
// Rob Lookout
CMD:lookout(playerid,params[]) {
      OnePlayAnim(playerid, "SHOP", "ROB_Shifty", 4.0, 0, 0, 0, 0, 0); // Rob Lookout
	  return 1;
}
// Rob Threat
CMD:robman(playerid,params[]) {
      LoopingAnim(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 1, 0, 0, 0, 0); // Rob
	  return 1;
}
// Arms crossed
CMD:crossarms(playerid,params[]) {
      LoopingAnim(playerid, "COP_AMBIENT", "Coplook_loop", 4.0, 0, 1, 1, 1, -1); // Arms crossed
	  return 1;
}

// Take Cover
CMD:hide(playerid,params[]) {
      LoopingAnim(playerid, "ped", "cower", 3.0, 1, 0, 0, 0, 0); // Taking Cover
	  return 1;
}
// Vomit
CMD:vomit(playerid,params[]) {
      OnePlayAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); // Vomit BAH!
	  return 1;
}

// Wave
CMD:wave(playerid,params[]) {
      LoopingAnim(playerid, "ON_LOOKERS", "wave_loop", 4.0, 1, 0, 0, 0, 0); // Wave
	  return 1;
}

// Dealer
CMD:deal(playerid,params[]) {
      OnePlayAnim(playerid, "DEALER", "DEALER_DEAL", 4.0, 0, 0, 0, 0, 0); // Deal Drugs
	  return 1;
}
// Crack Dieing
CMD:crack(playerid,params[]) {
      LoopingAnim(playerid, "CRACK", "crckdeth2", 4.0, 1, 0, 0, 0, 0); // Dieing of Crack
	  return 1;
}

// Sit
CMD:groundsit(playerid,params[]) {
      LoopingAnim(playerid,"BEACH", "ParkSit_M_loop", 4.0, 1, 0, 0, 0, 0); // Sit
	  return 1;
}

// Fucku
CMD:fucku(playerid,params[]) {
	 OnePlayAnim(playerid,"PED","fucku",4.0,0,0,0,0,0);
     return 1;
}

// ChairSit
CMD:chairsit(playerid,params[]) {
	 LoopingAnim(playerid,"PED","SEAT_down",4.1,0,1,1,1,0);
     return 1;
}

// Fall on the ground
CMD:fall(playerid,params[]) {
	 LoopingAnim(playerid,"PED","KO_skid_front",4.1,0,1,1,1,0);
     return 1;
}

// Fall
CMD:fallback(playerid,params[]) {
	 LoopingAnim(playerid, "PED","FLOOR_hit_f", 4.0, 1, 0, 0, 0, 0);
     return 1;
}

// kiss
CMD:kiss(playerid,params[]) {
	 LoopingAnim(playerid, "KISSING", "Playa_Kiss_02", 3.0, 1, 1, 1, 1, 0);
     return 1;
}

// Injujred
CMD:injured(playerid,params[]) {
	 LoopingAnim(playerid, "SWEET", "Sweet_injuredloop", 4.0, 1, 0, 0, 0, 0);
     return 1;
}

// Violence animations
CMD:push(playerid,params[]) {
	 OnePlayAnim(playerid,"GANGS","shake_cara",4.0,0,0,0,0,0);
     return 1;
}

CMD:akick(playerid,params[]) {
	 OnePlayAnim(playerid,"POLICE","Door_Kick",4.0,0,0,0,0,0);
     return 1;
}

CMD:lowbodypush(playerid,params[]) {
	 OnePlayAnim(playerid,"GANGS","shake_carSH",4.0,0,0,0,0,0);
     return 1;
}

// Spray
CMD:spray(playerid,params[]) {
	 OnePlayAnim(playerid,"SPRAYCAN","spraycan_full",4.0,0,0,0,0,0);
     return 1;
}

// Headbutt
CMD:headbutt(playerid,params[]) {
	 OnePlayAnim(playerid,"WAYFARER","WF_Fwd",4.0,0,0,0,0,0);
     return 1;
}

// KO Face
CMD:koface(playerid,params[]) {
	 LoopingAnim(playerid,"PED","KO_shot_face",4.0,0,1,1,1,0);
     return 1;
}

// KO Stomach
CMD:kostomach(playerid,params[]) {
	 LoopingAnim(playerid,"PED","KO_shot_stom",4.0,0,1,1,1,0);
     return 1;
}

// Jump for your life!
CMD:lifejump(playerid,params[]) {
	 LoopingAnim(playerid,"PED","EV_dive",4.0,0,1,1,1,0);
     return 1;
}

// Left big slap
CMD:leftslap(playerid,params[]) {
	 OnePlayAnim(playerid,"PED","BIKE_elbowL",4.0,0,0,0,0,0);
     return 1;
}

// Big fall
CMD:rollfall(playerid,params[]) {
	 LoopingAnim(playerid,"PED","BIKE_fallR",4.0,0,1,1,1,0);
     return 1;
}

// carjack
CMD:rcarjack1(playerid,params[]) {
	 OnePlayAnim(playerid,"PED","CAR_pulloutL_LHS",4.0,0,0,0,0,0);
     return 1;
}

// carjack
CMD:lcarjack1(playerid,params[]) {
	 OnePlayAnim(playerid,"PED","CAR_pulloutL_RHS",4.0,0,0,0,0,0);
     return 1;
}

// carjack
CMD:rcarjack2(playerid,params[]) {
	 OnePlayAnim(playerid,"PED","CAR_pullout_LHS",4.0,0,0,0,0,0);
     return 1;
}

// carjack
CMD:lcarjack2(playerid,params[]) {
	 OnePlayAnim(playerid,"PED","CAR_pullout_RHS",4.0,0,0,0,0,0);
     return 1;
}

// Hood frisked
CMD:hoodfrisked(playerid,params[]) {
	 LoopingAnim(playerid,"POLICE","crm_drgbst_01",4.0,0,1,1,1,0);
     return 1;
}

// Lighting cigarette
CMD:lightcig(playerid,params[]) {
	 OnePlayAnim(playerid,"SMOKING","M_smk_in",3.0,0,0,0,0,0);
     return 1;
}
CMD:vehicle(playerid,params[]) {
	new msg[12];
	format(msg,12,"%i",GetPlayerVehicleID(playerid));
	SendClientMessage(playerid,RED,msg);
    return 1;
}


// Tap cigarette
CMD:tapcig(playerid,params[]) {
	 OnePlayAnim(playerid,"SMOKING","M_smk_tap",3.0,0,0,0,0,0);
     return 1;
}

// Bat stance
CMD:bat(playerid,params[]) {
	 LoopingAnim(playerid,"BASEBALL","Bat_IDLE",4.0,1,1,1,1,0);
     return 1;
}

// Boxing
CMD:box(playerid,params[]) {
	 LoopingAnim(playerid,"GYMNASIUM","GYMshadowbox",4.0,1,1,1,1,0);
     return 1;
}

// Gogogo
CMD:chant(playerid,params[]) {
	 LoopingAnim(playerid,"RIOT","RIOT_CHANT",4.0,1,1,1,1,0);
     return 1;
}

// Finger
CMD:finger(playerid,params[]) {
	 OnePlayAnim(playerid,"RIOT","RIOT_FUKU",2.0,0,0,0,0,0);
     return 1;
}

// Shouting
CMD:shouting(playerid,params[]) {
	 LoopingAnim(playerid,"RIOT","RIOT_shout",4.0,1,0,0,0,0);
     return 1;
}

// Cop stance
CMD:cop(playerid,params[]) {
	 OnePlayAnim(playerid,"SWORD","sword_block",50.0,0,1,1,1,1);
     return 1;
}

// Elbow
CMD:elbow(playerid,params[]) {
	 OnePlayAnim(playerid,"FIGHT_D","FightD_3",4.0,0,1,1,0,0);
     return 1;
}

// Knee kick
CMD:kneekick(playerid,params[]) {
	 OnePlayAnim(playerid,"FIGHT_D","FightD_2",4.0,0,1,1,0,0);
     return 1;
}

// Fight stance
CMD:fstance(playerid,params[]) {
	 LoopingAnim(playerid,"FIGHT_D","FightD_IDLE",4.0,1,1,1,1,0);
     return 1;
}

// Ground punch
CMD:gpunch(playerid,params[]) {
	 OnePlayAnim(playerid,"FIGHT_B","FightB_G",4.0,0,0,0,0,0);
     return 1;
}

// Air kick
CMD:airkick(playerid,params[]) {
	 OnePlayAnim(playerid,"FIGHT_C","FightC_M",4.0,0,1,1,0,0);
     return 1;
}

// Low throw
CMD:lowthrow(playerid,params[]) {
	 OnePlayAnim(playerid,"GRENADE","WEAPON_throwu",3.0,0,0,0,0,0);
     return 1;
}

// Ground kick
CMD:highthrow(playerid,params[]) {
	 OnePlayAnim(playerid,"GRENADE","WEAPON_throw",4.0,0,0,0,0,0);
     return 1;
}

// Deal stance
CMD:dealstance(playerid,params[]) {
	 LoopingAnim(playerid,"DEALER","DEALER_IDLE",4.0,1,0,0,0,0);
     return 1;
}

// Deal stance
CMD:pee(playerid,params[]) {
	new anim = GetPlayerAnimationIndex(playerid);
	if(anim == 1130)
	{
		AC_Kick(playerid,"Bug");
		//Kick(playerid);
	}
	
	SetPlayerSpecialAction(playerid, 68);
	return 1;
}


CMD:raides(playerid,params[])
{
	SendClientMessage(playerid, -1, " * Si nustatyma galite pakeisti VVP. Rasykite /p ir spauskite Nustatymai");
	return 1;
	/*
	if(sulietuvinti[playerid])
	{
		sulietuvinti[playerid]=false;
		SendClientMessage(playerid,COLOR," * Ájungei lietuviðkas raides.");
		return 1;
	}
	else
	{
		sulietuvinti[playerid]=true;
		SendClientMessage(playerid,COLOR," * Dabar lietuviskos raides viesajame chate bus keiciamos i ju atitikmeni (àèæëáðøûþ).");
		SendClientMessage(playerid,COLOR," * Noredami matyti sias raides taisyklingai, apsilankykite musu tinklapio (LSGYVENIMAS.€) pagalbos skiltyje.");
	
		return 1;
	}
	*/
}
/*
#define START_BENCH(%0); {new __a=%0,__b=0,__c,__d=GetTickCount(),__e=1;do{}\
    while(__d==GetTickCount());__c=GetTickCount();__d=__c;while(__c-__d<__a||\
    __e){if(__e){if(__c-__d>=__a){__e=0;__c=GetTickCount();do{}while(__c==\
    GetTickCount());__c=GetTickCount();__d=__c;__b=0;}}{
	
#define FINISH_BENCH(%0); }__b++;__c=GetTickCount();}printf(" Bench for "\
    %0": executes, by average, %.2f times/ms.",floatdiv(__b,__a));}

CMD:oputest(playerid,params[])
{
	//if(!IsPlayerAdmin(playerid)) return 0;
	new string[128];
	format(string,128,"adfighdsfguh23HJ@%$#Iji3o2frjoijfdsa:asd asdskifjoiew rj23j4JAKDSJASIOJ");
	START_BENCH(2000);
	{
		new var = small_hash(string);
		if(var == PaskutineCmd[playerid]) {}
	}
	FINISH_BENCH("small_hash");
	START_BENCH(2000);
	{
		if(strcmp(string,string,true)==0) {}
	}
	FINISH_BENCH("strcmp");

	return 1;
}
*/

/*
CMD:vehicletest(playerid,params[])
{
	START_BENCH(1000);
	{
		MasinuLoop();
	}
	FINISH_BENCH("DegalaiZvejyba");
	return 1;
}
*/
CMD:stunt(playerid,params[])
{
	if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 481) return SendInfoMessage(playerid,"Sia komanda gali naudotis tik BMX'eriai!");
	if(!galikeist[playerid]) return SendInfoMessage(playerid,"Dar nepraejo 5 minutes nuo praeito keitimo!");
	galikeist[playerid]=false;
	SetTimerEx("GaliKeist",300000,0,"i",playerid);
	if(bmx[playerid] != -1)
	{
		new cp=random(sizeof(BMXCP));
		if(cp == bmx[playerid]) cp=random(sizeof(BMXCP));
		bmx[playerid]=cp;
		SetPlayerCheckpoint(playerid,BMXCP[bmx[playerid]][0],BMXCP[bmx[playerid]][1],BMXCP[bmx[playerid]][2],2.0);
		SendInfoMessage(playerid,"Pakeitei stunta!");
	}
	return 1;
}

CMD:verslai(playerid,params[])
{
	SendClientMessage(playerid,BLUE," * Jusu verslai:");
	new pname[MAX_PLAYER_NAME],msg[128];
	GetPlayerName(playerid,pname,MAX_PLAYER_NAME);
    foreach(Businesses,i) if(BusinessInfo[i][bOwned] && 0==strcmp(BusinessInfo[i][bOwner],pname,false))
	{
		format(msg,sizeof(msg),"|Verslas: [%s(%s)] Sukaupta pinigu: [%i€]| %s",
		BusinessInfo[i][bName],GetBussinessType(BusinessInfo[i][bType]),BusinessInfo[i][bEarning],
		((BusinessInfo[i][bMokesciai] <= 0) ? ("{FF0000}Nesumoketi mokesciai!"):("{00FF00}Mokesciai sumoketi"))
		);
		SendClientMessage(playerid,COLOR,msg);
	}
	return 1;
}		


CMD:pirktiversla(playerid,params[])
{
	new bizid=-1;
    foreach(Businesses,i)
	{
		if(IsPlayerInRangeOfPointEx(2.0, playerid, BusinessInfo[i][bEnterX],BusinessInfo[i][bEnterY],BusinessInfo[i][bEnterZ]))
		{
		    bizid=i;
		    break;
		}
	}
	if(bizid == -1) return SendInfoMessage(playerid,"Jus neesate prie verslo!");
	if(BusinessInfo[bizid][bOwned]==1) return SendInfoMessage(playerid,"Sis verslas jau turi savininka!");
	//if(ArTuriBiz(playerid) != -1) return SendInfoMessage(playerid,"Jus jau turite versla!");
	if(GetPlayerMoneyA(playerid) < BusinessInfo[bizid][bPrice]) return SendInfoMessage(playerid,"Truksta pinigu!");
	if(GetPlayerScore(playerid) < 5000) return SendInfoMessage(playerid,"Jus permazai patyres, kad butumet verslininkas. Reikia XP > 5000");
	if(VerslaiCount(playerid) >= 10) return SendInfoMessage(playerid,"Jus jau turite 10 verslu.");

	GivePlayerMoneyA(playerid, - BusinessInfo[bizid][bPrice]);
	BusinessInfo[bizid][bOwned]=1;
	BusinessInfo[bizid][bMokesciai]=14;
	format(BusinessInfo[bizid][bOwner],MAX_PLAYER_NAME,ReturnName(playerid));
	//SetPlayerScore(playerid,GetPlayerScore(playerid)+250+random(250));
	SendClientMessage(playerid,COLOR," * Sveikiname! Nusipirkote versla!");
	SendClientMessage(playerid,COLOR," * Verslo komandos /verslas");
	PlayerPlaySound(playerid, 1149,-119.9460,23.1096,12.2238); // Muzika
	new msg[64];
	format(msg,sizeof(msg)," * Siuo metu versle sukaupta %iEUR.",BusinessInfo[bizid][bEarning]);
	SendInfoMessage(playerid,msg);
	new string[128];
    new idx =bizid;
    format(string, sizeof(string), VERSLAS_NEPARDUODAMAS, BusinessInfo[idx][bName],BusinessInfo[idx][bOwner],GetBussinessType(BusinessInfo[idx][bType]));
	DestroyDynamic3DTextLabel(businesstext[idx]);
	businesstext[idx] = CreateDynamic3DTextLabel(string,0x00BC00FF,BusinessInfo[idx][bEnterX],BusinessInfo[idx][bEnterY],BusinessInfo[idx][bEnterZ],40.0, _,_, 1);
	MLog(playerid,"Nusipirko versla","i", idx);
	ProcessAchievement(playerid,45);
	return 1;
}
CMD:verslas(playerid,params[])
{
	if(ArTuriBiz(playerid) != -1) SendClientMessage(playerid,COLOR," * Jus turite versla!");
	SendClientMessage(playerid,YELLOW," * Verslo komandos:");
	SendClientMessage(playerid,COLOR," /pirktiversla /apleisti /siulytiversla /verslai");
	SendClientMessage(playerid,COLOR," /perleisti");
	SendClientMessage(playerid,COLOR," /paimtipelna /pavadinimas");
	SendClientMessage(playerid,YELLOW," Naujiena: /radijav");
	return 1;
}

CMD:radijav(playerid,params[])
{
	//if(ArTuriBiz(playerid) == -1) return SendInfoMessage(playerid,"Jus neturite verslo!");
	if(!IsInBiz(playerid)) return SendInfoMessage(playerid,"Jus neesate viduje!");
	new i = GetPlayerVirtualWorld(playerid) - MAX_HOUSES*2;
	if(strcmp(BusinessInfo[i][bOwner],ReturnName(playerid),false) || !BusinessInfo[i][bOwned]) return SendInfoMessage(playerid,"Tai ne jusu verslas!");
	new string[500] = "Jokia";
	for(new ix, j = sizeof(RADIO_PLUGIN); ix < j; ix++)
	{
		format(string,sizeof(string),"%s\n%s",string,RADIO_PLUGIN[ix][RADIO_NAME]);
	}
	ShowPlayerDialog(playerid,9757,DIALOG_STYLE_LIST,"Radija",string,"Rinktis","Isjungti");
	return 1;
}
CMD:apleisti(playerid,params[])
{
   // if(ArTuriBiz(playerid) == -1 && !IsPlayerAdmin(playerid)) return SendInfoMessage(playerid,"Jus neturite verslo!");
	if(!IsInBiz(playerid)) return SendInfoMessage(playerid,"Jus neesate viduje!");
	new i = GetPlayerVirtualWorld(playerid) - MAX_HOUSES*2;
	if((strcmp(BusinessInfo[i][bOwner],ReturnName(playerid),false) != 0 || !BusinessInfo[i][bOwned]) && !IsPlayerAdmin(playerid)) return SendInfoMessage(playerid,"Tai ne jusu verslas!");
	if(TradingWith[playerid] != -1) return SendInfoMessage(playerid,"Uzdaryk mainus!");
	new string[128];
    new idx =i;
    format(BusinessInfo[i][bOwner],64,"Nera");
    BusinessInfo[i][bOwned]=0;
    format(BusinessInfo[i][bName],24,"-");
    format(string, sizeof(string), VERSLAS_PARDUODAMAS,GetBussinessType(BusinessInfo[idx][bType]),BusinessInfo[idx][bPrice]);
	DestroyDynamic3DTextLabel(businesstext[i]);
	businesstext[i] = CreateDynamic3DTextLabel(string,0x00BC00FF,BusinessInfo[i][bEnterX],BusinessInfo[i][bEnterY],BusinessInfo[i][bEnterZ],40.0, _,_, 1);
	SendInfoMessage(playerid,"Apleidote versla!");
	return 1;
}
CMD:pavadinimas(playerid,params[])
{
    //if(ArTuriBiz(playerid) == -1) return SendInfoMessage(playerid,"Jus neturite verslo!");
	if(!IsInBiz(playerid)) return SendInfoMessage(playerid,"Jus neesate viduje!");
	new i = GetPlayerVirtualWorld(playerid) - MAX_HOUSES*2;
	if(strcmp(BusinessInfo[i][bOwner],ReturnName(playerid),false) || !BusinessInfo[i][bOwned]) return SendInfoMessage(playerid,"Tai ne jusu verslas!");
	new agentas=-1;
	foreach(Player,pl)
	{
		new x = GetPlayerVirtualWorld(pl) - MAX_HOUSES*2;
		if(pl != playerid && x == i && playerDB[pl][specialybe]==34)
		{
			agentas=pl;
			break;
		}
	}
	if(agentas == -1) return SendInfoMessage(playerid,"Pasikvieskite i versla turto agenta!"); // €
	if(GetPlayerMoneyA(playerid) < COST_VERSLOCHANGE) return SendInfoMessage(playerid,"Verslo pavadinimo pakeitimas kainuoja "#COST_VERSLOCHANGE"EUR!");
	
	new Bpavadinimas[128];
	if(sscanf(params,"s[50]",Bpavadinimas)) return SendInfoMessage(playerid,"Naudojimas: /pavadinimas [Naujas Firmos Pavadinimas]");
	if(strlen(Bpavadinimas)> 20) return SendInfoMessage(playerid,"Per ilgas firmos pavadinimas!");
	if(strfind(Bpavadinimas,"{",false) != -1 || strfind(Bpavadinimas,"|",false) != -1 || strfind(Bpavadinimas,"'",false) != -1 || strfind(Bpavadinimas,"/",false) != -1 || strfind(Bpavadinimas,"=",false) != -1) return SendClientMessage(playerid,COLOR," * Pavadinima sudaro netinkami simboliai!");
	format(BusinessInfo[i][bName],64,Bpavadinimas);
	GivePlayerMoneyA(playerid, -COST_VERSLOCHANGE);
	GivePlayerMoneyA(agentas, COST_VERSLOCHANGE/2);

	if(GetTickCount()-LastForsale[playerid] > 1000*60*10)
	{
		Pelnas(agentas,33,COST_VERSLOCHANGE*10);
	}
	
	LastForsale[playerid]=GetTickCount();
	SendInfoMessage(playerid,"Pavadinimas pakeistas!");
	SendClientMessage(agentas,WHITE," * Gavote pinigu uz pavadinimo pakeitima!");
	new string[128];
    new idx =i;

    format(string, sizeof(string), VERSLAS_NEPARDUODAMAS, BusinessInfo[i][bName],BusinessInfo[i][bOwner],GetBussinessType(BusinessInfo[idx][bType]));
	DestroyDynamic3DTextLabel(businesstext[i]);
	businesstext[i] = CreateDynamic3DTextLabel(string,0x00BC00FF,BusinessInfo[i][bEnterX],BusinessInfo[i][bEnterY],BusinessInfo[i][bEnterZ],40.0, _,_, 1);
	return 1;
}
CMD:paimtipelna(playerid,params[])
{
	//if(ArTuriBiz(playerid) == -1) return SendInfoMessage(playerid,"Jus neturite verslo!");
	if(!IsInBiz(playerid)) return SendInfoMessage(playerid,"Jus neesate viduje!");
	new i = GetPlayerVirtualWorld(playerid) - MAX_HOUSES*2;
	if(strcmp(BusinessInfo[i][bOwner],ReturnName(playerid),false) || !BusinessInfo[i][bOwned]) return SendInfoMessage(playerid,"Tai ne jusu verslas!");
	new kiek;
	new lets = 10000000-BusinessInfo[i][bPaeme];
	if(sscanf(params,"i",kiek))
	{
		new msg[128];
		if(BusinessInfo[i][bEarning] < lets)
			kiek = BusinessInfo[i][bEarning];
		else
			kiek = lets;
		if(kiek < 0)
			return SendInfoMessage(playerid,"~r~Negali paimti firmos pelno!");
		format(msg,sizeof(msg)," * Is savo firmos paemete %i€. Per diena galite paimti iki 10000000€.",kiek);
		SendClientMessage(playerid,YELLOW,msg);
		SendClientMessage(playerid, COLOR, " * Rekomenduojame naudotis inkasatoriu paslaugomis. Uzsakyma galite padaryti ju ofise (/darbai)");
		GivePlayerMoneyA(playerid,kiek);
		BusinessInfo[i][bEarning]-=kiek;
		BusinessInfo[i][bPaeme]+=kiek;
	}
	else if(kiek <= 0) return SendInfoMessage(playerid,"~r~Netinkama suma!");
	else if(kiek >= BusinessInfo[i][bEarning]) return SendInfoMessage(playerid,"~r~Jusu pelne tiek nera! Rasykite /verslai");
	else if(kiek+BusinessInfo[i][bPaeme] > 10000000)
	{
		new dif = 10000000-BusinessInfo[i][bPaeme];
		new msg[128];
		format(msg,sizeof(msg)," * Per diena galite paimti tik iki 10000000€. Siandien galite paimti %i€.",dif);
		SendClientMessage(playerid, COLOR, msg);
		SendClientMessage(playerid, COLOR, " * Rekomenduojame naudotis inkasatoriu paslaugomis. Uzsakyma galite padaryti ju ofise (/darbai)");
		return SendInfoMessage(playerid,"~r~Per diena galite paimti iki 10000000EUR");
	}
	else
	{
		new msg[128];
		format(msg,sizeof(msg)," * Is savo firmos paemete %i€.",kiek);
		BusinessInfo[i][bPaeme]+=kiek;
		SendClientMessage(playerid,YELLOW,msg);
		GivePlayerMoneyA(playerid,kiek);
		BusinessInfo[i][bEarning]-=kiek;
	}
	return 1;
}
CMD:gaujos(playerid,params[])
{
	#pragma unused params
	new msg[256];
	for(new i;i<MAX_FAMILY;i++)
	{
		format(msg,sizeof(msg),"%d. \"%s\" Vadas: %s",i+1,FamilyInfo[i][FamilyName],FamilyInfo[i][FamilyLeader]);
		if(strcmp(FamilyInfo[i][FamilySubstitute],"Nera",false)!=0)
			format(msg,sizeof(msg),"%s, Pavaduotojas: %s",msg,FamilyInfo[i][FamilySubstitute]);
		if(FamilyInfo[i][FamilyIspejimai] == 1)
			format(msg,sizeof(msg),"%s, Áspëjimai: {fc8003}1/2", msg);
		else if(FamilyInfo[i][FamilyIspejimai] == 2)
			format(msg,sizeof(msg),"%s, Áspëjimai: {fc2803}2/2", msg);
		SendClientMessage(playerid,COLOR,msg);
	}
	return 1;
}

CMD:leidimas(playerid,params[])
{
	if(!playerDB[playerid][plead]) return SendInfoMessage(playerid,"Tai direktoriaus komandos.");
	new name[128],darbas[128];
	if(sscanf(params,"s[24]s[128]",name,darbas))
	{
		SendInfoMessage(playerid,"Noredami leisti zaidejui pakeisti darba rasykite: /leidimas [vardo dalis] [darbas]");
		return 1;
	}

	new id = GetPlayeridMid(name);
	if(id==INVALID_PLAYER_ID) return SendInfoMessage(playerid,"Tokio zaidejo nera!");

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
	else if(playerDB[playerid][plead] == 60){ lol = 60;} // inkasatorius
	new job;
	if(0==strcmp(darbas,"Transporteris",true)) job =20;
	else if(0==strcmp(darbas,"Dealeris",true)) job =32;
	else if(0==strcmp(darbas,"Limuzino vairuotojas",true)) job =39;
	else if(0==strcmp(darbas,"Furistas",true)) job =41;
    //else if(0==strcmp(darbas,"Jacht Klubo Narys",true)) job =72;
    else if(0==strcmp(darbas,"Motomanas",true)) job =73;
    else if(0==strcmp(darbas,"ARAS",true)) job =81;
    else if(0==strcmp(darbas,"Kareivis",true)) job =83;
    else if(0==strcmp(darbas,"Kobra",true)) job =84;
	else if(0==strcmp(darbas,"Policija",true)) job=80;
	else if(0==strcmp(darbas,"Privatus medikas",true)) job=93;
	else job=0;

	if(playerDB[id][specialybe] != lol && playerDB[id][specialybe] != lol2 && playerDB[id][specialybe] != lol3 && playerDB[id][specialybe] != lol4 && playerDB[id][specialybe] != lol5)
	    return SendInfoMessage(playerid,"Zaidejas nedirba pas jus!");
	    
	if(job != lol && job != lol2 && job != lol3 && job != lol4 && job != lol5)
	    return SendInfoMessage(playerid,"Jus neturite teises perleisti zmogu i ta darba. Rasykite /manodarbai");
	/*
	if(job == 32)
	{
		if(GetPlayerMoneyA(playerid) < COST_KYSIS) return SendInfoMessage(playerid,"Jums truksta pinigu. Kysis i mero fonda - "#COST_KYSIS"€/leidim.");
		Server[kysiufondas]+=COST_KYSIS;
		GivePlayerMoneyA(playerid,-COST_KYSIS);
		MLog(playerid,"Padejo i kfonda","is",COST_KYSIS,name);
		SendClientMessage(playerid,WHITE," * Padejai "#COST_KYSIS"€ i kysiu fonda!");
	}
	*/
	playerDB[id][leidimas]=job;
	new msg[128];
	format(msg,sizeof(msg)," * Jus gavote leidima is direktoriaus %s pereiti i \"%s\"",ReturnName(playerid),darbas);
	SendClientMessage(id,COLOR,msg);
	format(msg,sizeof(msg)," * Leidote %s pereiti i \"%s\"",ReturnName(id),darbas);
	SendClientMessage(playerid,COLOR,msg);
	ProcessAchievement(id, 134);
	MLog(playerid,"Paaukstino","ss",ReturnName(id),darbas);
	return 1;
}

CMD:manodarbai(playerid,params[])
{
	#pragma unused params
	if(!playerDB[playerid][plead]) return SendInfoMessage(playerid,"Tai direktoriaus komandos.");
	SendClientMessage(playerid,YELLOW," * Darbai, i kuriuos galite leisti pereit:");
	new lol=-1,lol2=-1,lol3=-1,lol4=-1,lol5=-1,darbas[100];
	if(playerDB[playerid][plead] == 2){ lol = 2; lol2=93; } // medikai
	else if(playerDB[playerid][plead] == 3){ lol = 3; lol2 = 20; lol3 = 39;} // transportas
	else if(playerDB[playerid][plead] == 5){ lol = 41; lol2 = 44;} // furistai
	else if(playerDB[playerid][plead] == 6){ lol = 6; lol2 = 28;} // autospeciai
	else if(playerDB[playerid][plead] == 66){ lol = 66; lol2 = 67;} // zudikai
	else if(playerDB[playerid][plead] == 70){ lol = 70; lol2 = 73; lol3 = 72;} // autoklubas
	else if(playerDB[playerid][plead] == 80){ lol = 80; lol2 = 81; lol3 = 83; lol4 = 84;}
	else if(playerDB[playerid][plead] == 50){ lol = 50;} // skelbejai
	else if(playerDB[playerid][plead] == 98){ lol = 71;} // baikeriai
	else if(playerDB[playerid][plead] == 58){ lol = 58;} // vagys
	else if(playerDB[playerid][plead] == 90){ lol = 31; lol2=32;} // dealeriai 
	else if(playerDB[playerid][plead] == 60){ lol = 60;} // vagys
	switch(lol)
    {
		case 20: darbas = "Transporteris";
		case 32: darbas = "Dealeris";
		case 39: darbas = "Limuzino vairuotojas";
		case 41: darbas = "Furistas";
		//case 72: darbas = "Jacht klubo narys";
		case 73: darbas = "Motomanas";
		case 81: darbas = "Aras";
		case 83: darbas = "Kareivis";
		case 84: darbas = "Kobra";
		case 80: darbas = "Policija";
		case 93: darbas = "Privatus medikas";
		default: darbas = "";
	}
	if(strlen(darbas))
	{
	    SendClientMessage(playerid,COLOR,darbas);
	}
	switch(lol2)
    {
		case 20: darbas = "Transporteris";
		case 32: darbas = "Dealeris";
		case 39: darbas = "Limuzino vairuotojas";
		case 41: darbas = "Furistas";
		//case 72: darbas = "Jacht klubo narys";
		case 73: darbas = "Motomanas";
		case 81: darbas = "Aras";
		case 83: darbas = "Kareivis";
		case 84: darbas = "Kobra";
		case 80: darbas = "Policija";
		case 93: darbas = "Privatus medikas";
		default: darbas = "";
	}
	if(strlen(darbas))
	{
	    SendClientMessage(playerid,COLOR,darbas);
	}
	switch(lol3)
    {
		case 20: darbas = "Transporteris";
		case 32: darbas = "Dealeris";
		case 39: darbas = "Limuzino vairuotojas";
		case 41: darbas = "Furistas";
		//case 72: darbas = "Jacht klubo narys";
		case 73: darbas = "Motomanas";
		case 81: darbas = "Aras";
		case 83: darbas = "Kareivis";
		case 84: darbas = "Kobra";
		case 80: darbas = "Policija";
		case 93: darbas = "Privatus medikas";
		default: darbas = "";
	}
	if(strlen(darbas))
	{
	    SendClientMessage(playerid,COLOR,darbas);
	}
	switch(lol4)
    {
		case 20: darbas = "Transporteris";
		case 32: darbas = "Dealeris";
		case 39: darbas = "Limuzino vairuotojas";
		case 41: darbas = "Furistas";
		//case 72: darbas = "Jacht klubo narys";
		case 73: darbas = "Motomanas";
		case 81: darbas = "Aras";
		case 83: darbas = "Kareivis";
		case 84: darbas = "Kobra";
		case 80: darbas = "Policija";
		case 93: darbas = "Privatus medikas";
		default: darbas = "";
	}
	if(strlen(darbas))
	{
	    SendClientMessage(playerid,COLOR,darbas);
	}
	switch(lol5)
	{
		case 20: darbas = "Transporteris";
		case 32: darbas = "Dealeris";
		case 39: darbas = "Limuzino vairuotojas";
		case 41: darbas = "Furistas";
		case 73: darbas = "Motomanas";
		case 81: darbas = "Aras";
		case 83: darbas = "Kareivis";
		case 84: darbas = "Kobra";
		case 80: darbas = "Policija";
		case 93: darbas = "Privatus medikas";
		default: darbas = "";
	
	}
	if(strlen(darbas))
	{
	    SendClientMessage(playerid,COLOR,darbas);
	}
	return 1;
}
CMD:lsd(playerid,params[])
{
	if(playerDB[playerid][lsd] < 1) return SendInfoMessage(playerid,"Neturi lsd!");
	new msg[128];
	new left = (NarkTaimas[playerid] - GetTickCount())/1000;	
	if(left > 0)
	{
		if(left >= 60)
			format(msg,128,"Tu jau apsineses! Palauk %dm%02ds",left/60, left % 60);
		else
			format(msg,128,"Tu jau apsineses! Palauk %is",left);
		return SendInfoMessage(playerid,msg); 
	}
	if(playerDB[playerid][psratasvydis]) return SendInfoMessage(playerid,"Cia negali vartot narkotiku!");
	new keys,lr,ud;
	GetPlayerKeys(playerid,keys,ud,lr);
	if(keys & KEY_HANDBRAKE || keys & KEY_FIRE || playerDB[playerid][ant] || playerDB[playerid][suristas])
		return SendInfoMessage(playerid,"Dabar narkotiku vartoti negali");
	new Float:Coo[3];
	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	//NarkoPickupas[playerid] = CreatePickupA(1241 ,2,Coo[0],Coo[1],Coo[2]+1.0);
	//SetTimerEx("RemoveNarkoPickup",2000,false,"i",playerid);
	if(random(2)==1) 
		StartGliucint(playerid);
	else 
		AddSniego(playerid); // else
	if(random(3)==1)
		SekiojantiKarve(playerid);
	SetPlayerDrunkLevel(playerid,GetPlayerDrunkLevel(playerid)+2000);
	OnePlayAnim(playerid, "CRACK", "Bbalbat_idle_01", 3.0, 0, 0, 0, 0, 0); //
	SendInfoMessage(playerid,"Nurijai ~r~L~p~S~y~D");
	ProcessAchievement(playerid, 126);
	new Float:Health;
	GetPlayerHealth(playerid,Health);
	if(Health+60.0 <= 140) 
		Health+=60.0;
	else 
		Health=140.0;
	SetPlayerHealth(playerid, Health);
	GetPlayerArmour(playerid,Health);
	if(Health+60.0 <= 150) 
		Health+=60.0;
	else 
		Health=140.0;
	SetPlayerArmour(playerid, Health);
	LogA(playerid,"LSD");
	playerDB[playerid][lsd]-=1;
	Invul[playerid]=true;
	MLog(playerid,"LSD","i",1);
	CheckNarkomanas(playerid,0,1);
	SetTimerEx("NoInvul",1000,false,"i",playerid);
	//playerDB[playerid][narkomanas]=true;
	NarkTaimas[playerid] = GetTickCount() + 105*1000;
	//SetTimerEx("NeNarkomanas", 105000, false, "i", playerid);
	return 1;
}
CMD:adrenalinas(playerid,params[])
{
	return cmd_adr(playerid,params);
}
CMD:adr(playerid,params[])
{
	if(playerDB[playerid][adr] < 1) return SendInfoMessage(playerid,"Neturi adrenalino!");
	new msg[128];
	new left = (NarkTaimas[playerid] - GetTickCount())/1000;	
	if(left > 0)
	{
		if(left >= 60)
			format(msg,128,"Tu jau apsineses! Palauk %dm%02ds",left/60, left % 60);
		else
			format(msg,128,"Tu jau apsineses! Palauk %is",left);
		return SendInfoMessage(playerid,msg); 
	}
	if(playerDB[playerid][psratasvydis]) return SendInfoMessage(playerid,"Cia negali vartot adrenalino!");
	new Float:Coo[3];
	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	//NarkoPickupas[playerid] = CreatePickupA(1241 ,2,Coo[0],Coo[1],Coo[2]+1.0);
	//SetTimerEx("RemoveNarkoPickup",2000,false,"i",playerid);
	AddSniego(playerid); // else
	//SetPlayerWeather(playerid, -84);
	//SetPlayerTime(playerid,4,00);
	SetPlayerTime(playerid,22,58);
	SetPlayerWeather(playerid, -145);

	OnePlayAnim(playerid, "CRACK", "Bbalbat_idle_02", 3.0, 0, 0, 0, 0, 0); //
	SetPlayerDrunkLevel(playerid,GetPlayerDrunkLevel(playerid)+1500);
	SetTimerEx("DrugEffectGone", 60000, false, "i", playerid);
	
	SendInfoMessage(playerid,"Susileidai ~r~ADRENALINO");
	
	new Float:Health;
	GetPlayerHealth(playerid,Health);
	if(Health+60.0 <= 140) 
		Health+=60.0;
	else 
		Health=140.0;
	SetPlayerHealth(playerid, Health);
	GetPlayerArmour(playerid,Health);
	if(Health+60.0 <= 150) 
		Health+=60.0;
	else 
		Health=150.0;
	SetPlayerArmour(playerid, Health);
	LogA(playerid,"ADR");
	playerDB[playerid][adr]-=1;
	Invul[playerid]=true;
	//MLog(playerid,"ADR","i",1);
	//CheckNarkomanas(playerid,0,1);
	SetTimerEx("NoInvul",1000,false,"i",playerid);
	//playerDB[playerid][narkomanas]=true;
	NarkTaimas[playerid] = GetTickCount() + 105*1000;
	//SetTimerEx("NeNarkomanas", 105000, false, "i", playerid);
	return 1;
}
CMD:ratai(playerid,params[])
{
	if(playerDB[playerid][ratai] < 1) return SendInfoMessage(playerid,"Neturi ekstazio!");
	new msg[128];
	new left = (NarkTaimas[playerid] - GetTickCount())/1000;	
	if(left > 0)
	{
		if(left >= 60)
			format(msg,128,"Tu jau apsineses! Palauk %dm%02ds",left/60, left % 60);
		else
			format(msg,128,"Tu jau apsineses! Palauk %is",left);
		return SendInfoMessage(playerid,msg); 
	}
	if(playerDB[playerid][psratasvydis]) return SendInfoMessage(playerid,"Cia negali vartot narkotiku!");
	new keys,lr,ud;
	GetPlayerKeys(playerid,keys,ud,lr);
	if(keys & KEY_HANDBRAKE || keys & KEY_FIRE || playerDB[playerid][ant] || playerDB[playerid][suristas])
		return SendInfoMessage(playerid,"Dabar narkotiku vartoti negali");
	new Float:Coo[3];
	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	//NarkoPickupas [playerid] = CreatePickupA(1241 ,2,Coo[0],Coo[1],Coo[2]+1.0);
	//SetPlayerWeather(playerid, -84);
	//SetPlayerTime(playerid,4,00);
	SetPlayerWeather(playerid, 32);
	SetPlayerTime(playerid,22,42);
	//playerDB[playerid][narkomanas]=true;
	//SetTimerEx("NeNarkomanas", 90000, false, "i", playerid);
	OnePlayAnim(playerid, "CRACK", "Bbalbat_idle_02", 3.0, 0, 0, 0, 0, 0); //
	SetPlayerDrunkLevel(playerid,GetPlayerDrunkLevel(playerid)+1000);
	SetTimerEx("DrugEffectGone", 60000, false, "i", playerid);
	//SetTimerEx("RemoveNarkoPickup",2000,false,"i",playerid);
	new Float:Health;
	GetPlayerHealth(playerid,Health);
	if(Health+45.0 <= 145.0) Health+=45.0;
	else Health=145.0;
	SetPlayerHealth(playerid, Health);
	GetPlayerArmour(playerid,Health);
	if(Health+45.0 <= 145.0) Health+=45.0;
	else Health=145.0;
	SetPlayerArmour(playerid, Health);
	LogA(playerid,"Ratai");
	MLog(playerid,"Ratai","i",1);
	SendInfoMessage(playerid,"Nurijai tablete ratu.");
	ProcessAchievement(playerid, 126);
	playerDB[playerid][ratai]-=1;
	CheckNarkomanas(playerid,1,1);
	Invul[playerid]=true;
	NarkTaimas[playerid] = GetTickCount() + 90*1000;
	SetTimerEx("NoInvul",1000,false,"i",playerid);
	return 1;
}
CMD:autop(playerid,params[])
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendInfoMessage(playerid,"Privalote vairuoti automobili!");
	new vid = GetPlayerVehicleID(playerid);
	if(!AutoPilotas[vid])
	{
		SendInfoMessage(playerid,"AutoPilotas: ~g~Ijungtas~w~~n~Jusu greitis bus ribojamas iki 90km/h.");
		AutoPilotas[vid]=1;
	}
	else
	{
		SendInfoMessage(playerid,"AutoPilotas: ~r~Isjungtas~w~~n~Jusu greitis nebus ribojamas.");
		AutoPilotas[vid]=0;
	}
	return 1;
}


CMD:spygliai(playerid,params[])
{
	if(playerDB[playerid][specialybe] != 81 && playerDB[playerid][specialybe] != 83 && playerDB[playerid][specialybe] != 84) return SendInfoMessage(playerid,"Si komanda teisesaugai(ARAS,Armija,Kobra 11)");
	new val;
	if(sscanf(params,"d",val)) return SendInfoMessage(playerid,"Naudojimas: /spygliai [1-2] (1-mazi, 2-dideli)");
	if(IsPlayerInAnyVehicle(playerid) || GetPlayerInterior(playerid) || GetPlayerVirtualWorld(playerid)) return SendInfoMessage(playerid,"Spyglius galite deti tik lauke!");
	if(YraSpygliu > 10) return SendInfoMessage(playerid,"Teisesauga nebeturi spygliu. Prasome nuimti kitus.");
	if(val == 1)
	{
		new Float:Xp, Float:Yp, Float:Zp, Float:Ap;
		GetPlayerPos(playerid, Xp, Yp, Zp);
		GetPlayerFacingAngle(playerid, Ap);
		CreateSmallStinger(playerid,Xp+(2.0*floatsin(-Ap, degrees)), Yp+(2.0*floatcos(-Ap, degrees)), Zp-0.825, Ap, GetPlayerVirtualWorld(playerid), 360000);
	}
	else if(val == 2)
	{
		new Float:Xp, Float:Yp, Float:Zp, Float:Ap;
		GetPlayerPos(playerid, Xp, Yp, Zp);
		GetPlayerFacingAngle(playerid, Ap);
		CreateLargeStinger(playerid,Xp+(4.0*floatsin(-Ap, degrees)), Yp+(4.0*floatcos(-Ap, degrees)), Zp-0.925, Ap, GetPlayerVirtualWorld(playerid), 360000);
	}
	else return SendInfoMessage(playerid,"Naudojimas: /spygliai [1-2] (1-mazi, 2-dideli)");
	return 1;

}
CMD:nspygliai(playerid,params[])
{
	new Float:Xp, Float:Yp, Float:Zp;
	for(new stingerid = 0; stingerid < sizeof(iPickups); stingerid++)
	{
		if(iPickups[stingerid][0] == -1)
			continue;
	   
		GetDynamicObjectPos(iPickups[stingerid][0], Xp, Yp, Zp);
		if(IsPlayerInRangeOfPointEx(6.0,playerid, Xp, Yp, Zp))
		{
			DestroyStinger(stingerid);
			break;
		}
	}
	return 1;
}
CMD:kurtikelione(playerid,params[])
{
	if(playerDB[playerid][plead]==70)
	{

		if(Keliones[Kuriama])
		{
			DisablePlayerRaceCheckpoint(playerid);
			Keliones[Kuriama]=false;
			Keliones[Kurejas]=-1;
			for(new i;i<CP;i++)
			{
				KelionesKurimas[i][koordx]=0.0;
				KelionesKurimas[i][koordy]=0.0;
				KelionesKurimas[i][koordz]=0.0;
			}
			CP=0;
			SendInfoMessage(playerid,"Nutraukei keliones kurima!");
			return 1;
		}
		SendClientMessage(playerid, COLOR_GREEN,"[Keliones] Deti CP galite parase /deticp, istrinti - /trinticp, issaugoti kelione - /saugotikelione.");
		SendClientMessage(playerid, COLOR_GREEN,"[Keliones] CP limitas: 10-65");
		SendClientMessage(playerid,COLOR_GREEN,"[Keliones] Noredami nebekurti keliones rasykite /kurtikelione");
		Keliones[Kuriama]=true;
		Keliones[Kurejas]=playerid;
		CP=0;
	}
	return 1;
}
CMD:deticp(playerid,params[])
{
	if(playerDB[playerid][plead]==70 && Keliones[Kuriama] && Keliones[Kurejas]==playerid)
	{
		if(CP<=65)
		{
			if(CP != 0 && IsPlayerInRangeOfPointEx(600.0,playerid,KelionesKurimas[CP-1][koordx],KelionesKurimas[CP-1][koordy],KelionesKurimas[CP-1][koordz]))
			{
				new msg[128];
				new Float:d = GetPlayerDistanceFromPoint(playerid,KelionesKurimas[CP-1][koordx],KelionesKurimas[CP-1][koordy],KelionesKurimas[CP-1][koordz]);
				format(msg,128,"Per arti dedate CP(min 600m). Truksta %im", 600 - floatround(d));
				return SendInfoMessage(playerid,msg);
			}	

			if(KiekFlood[playerid] > 1)
			{
				KiekFlood[playerid]-=2;
			}
			new Float:x, Float:y, Float:z;
			new Pranesimas[128];
			DisablePlayerRaceCheckpoint(playerid);
			GetPlayerPos(playerid,x,y,z);
			KelionesKurimas[CP][koordx]=x;
			KelionesKurimas[CP][koordy]=y;
			KelionesKurimas[CP][koordz]=z;
			SetPlayerRaceCheckpoint(playerid,1,x,y,z,0.0,0.0,0.0,10);
			format(Pranesimas,sizeof(Pranesimas),"Sukurtas %d CP.",CP+1);
			SendInfoMessage(playerid,Pranesimas);
			CP++;
			return 1;
		}
		else return SendInfoMessage(playerid,"Daugiau CP deti nebegalite, kadangi pasiekete limita.");
	}
	else if(playerDB[playerid][plead]!=70) return SendInfoMessage(playerid,"Jus nesate autoklubo direktorius");
	else if(!Keliones[Kuriama]) return SendInfoMessage(playerid,"Keliones kurimas nera pradetas");
	else if(Keliones[Kurejas]!=playerid) return SendInfoMessage(playerid,"Ne jus kuriat kelione!");
	return 1;
}
CMD:trinticp(playerid,params[])
{
	if(playerDB[playerid][plead]==70 && Keliones[Kuriama] && Keliones[Kurejas]==playerid)
	{
		if(CP>=1)
		{
			new Pranesimas[64];
			DisablePlayerRaceCheckpoint(playerid);
			format(Pranesimas,sizeof(Pranesimas),"Istrintas %d CP.",CP);
			SendInfoMessage(playerid,Pranesimas);
			KelionesKurimas[CP][koordx]=0;
			KelionesKurimas[CP][koordy]=0;
			KelionesKurimas[CP][koordy]=0;
			CP--;
			SetPlayerRaceCheckpoint(playerid,1,KelionesKurimas[CP][koordx],KelionesKurimas[CP][koordy],KelionesKurimas[CP][koordz],0.0,0.0,0.0,10);
			return 1;
		}
		else return SendInfoMessage(playerid,"Nera ka trinti.");
	}
	else if(playerDB[playerid][plead]!=70) return SendInfoMessage(playerid,"Jus nesate autoklubo direktorius");
	else if(!Keliones[Kuriama]) return SendInfoMessage(playerid,"Keliones kurimas nera pradetas");
	else if(Keliones[Kurejas]!=playerid) return SendInfoMessage(playerid,"Ne jus kuriat kelione!");
	return 1;
}
CMD:saugotikelione(playerid,params[])
{
	new kelpavadinimas[128];
	if(sscanf(params,"s[128]",kelpavadinimas)) return SendInfoMessage(playerid,"Naudojimas: /saugotikelione [pavadinimas]");
	mysql_real_escape_string(kelpavadinimas, kelpavadinimas);
	if(playerDB[playerid][plead]==70 && Keliones[Kuriama] && Keliones[Kurejas]==playerid)
	{
		if(CP>=10)
		{
			format(Keliones[KelionesPavadinimas],128,kelpavadinimas);
			DisablePlayerRaceCheckpoint(playerid);
			mysql_function_query(SQL, "SELECT DISTINCT id from Keliones ORDER BY id + 0 ASC", true, "SQL_SaveKelione", "i",playerid);
			return 1;
		}
		else return SendInfoMessage(playerid,"Nepakanakamas kiekis CP norint pabaigti keliones kurima.");
	}
	else if(playerDB[playerid][plead]!=70) return SendInfoMessage(playerid,"Jus nesate autoklubo direktorius");
	else if(!Keliones[Kuriama]) return SendInfoMessage(playerid,"Keliones kurimas nera pradetas");
	else if(Keliones[Kurejas]!=playerid) return SendInfoMessage(playerid,"Ne jus kuriat kelione!");
	return 1;
}
CMD:keliones(playerid,params[])
{
	SendClientMessage(playerid,YELLOW," * Autoklubo Kelioniu komandos:");
	SendClientMessage(playerid,COLOR," /kelione /istrintikelione");
	SendClientMessage(playerid,COLOR," /kurtikelione /deticp /trinticp /saugotikelione");
	SendClientMessage(playerid,GREEN," /prisijungti /palikti");
	return 1;
}
CMD:trintikelione(playerid,params[])
	return cmd_istrintikelione(playerid,params);
CMD:istrintikelione(playerid,params[])
{
	if(playerDB[playerid][plead]!=70) return SendInfoMessage(playerid,"Jus ne autoklubo direktorius!");
	if(Keliones[Kuriama]) return SendInfoMessage(playerid,"Kelione kuriama!");
	if(Keliones[Ijungta])
	{
		Keliones[Ijungta]=false;
		Keliones[DabartinisCP]=0;
		Keliones[Dalyviai]=0;
		foreach(Player, i) if(KDalyvis[i][Dalyvauja])
		{
			DisablePlayerRaceCheckpoint(i);
			KDalyvis[i][Dalyvauja]=false;
			KDalyvis[i][DabartinisCPs]=0;
		}
		SendMessageToKlubai(COLOR_WHITE,"[racija] Operatore: Direktorius nutrauke kelione!");
		return 1;
	}
	ShowPlayerKeliones(playerid, /*deleting=*/ 1);
	//ShowPlayerDialog(playerid,8583,DIALOG_STYLE_LIST,"Istrinti Keliones",string,"Gerai","Atsaukti");
	return 1;
}
CMD:kelione(playerid,params[])
{
	if(playerDB[playerid][plead]!=70) return SendInfoMessage(playerid,"Jus ne autoklubo direktorius!");
	if(Keliones[Kuriama]) return SendInfoMessage(playerid,"Kelione kuriama!");
	if(Keliones[Ijungta])
	{
		new msg[512];
		format(msg,512,"Kelione jau vyksta!\n\nDalyviai: %i\nCheckpoint %i/%i\n\n{FF0000}Ar norite nutraukti kelione?",Keliones[Dalyviai],Keliones[DabartinisCP],Keliones[Paskutinysis]);
		ShowPlayerDialog(playerid, 3433, DIALOG_STYLE_MSGBOX,"Kelione",msg,"Taip","Ne");
		return 1;
	}
	//new skaiciukas = (dini_Int("Keliones/number.txt","number")+1);
	//if(skaiciukas < 1) return SendInfoMessage(playerid,"Per mazai sukurtu kelioniu!");
	/*
	new AtsitiktinisSk = random(skaiciukas);
	new file[128];
	format(file,sizeof file,"Keliones/%i.txt",AtsitiktinisSk);
	if(LoadRace(file) == 0) return SendClientMessage(playerid,COLOR,"ERROR");
	*/
	ShowPlayerKeliones(playerid, /*deleting=*/ 0);
	/*new string[2024];
	new stringx[128];
	for(new i;i<50;i++)
	{
		new file[128];
		format(file,sizeof file,"Keliones/%i.txt",i);
		if(!fexist(file))
		{
			format(string,sizeof(string),"%s\n%i.<NERA>",string,i+1);
		
		}
		else
		{
			new File:failas = fopen(file, io_read); 
			if(fread(failas, stringx))
			{
				format(string,sizeof(string),"%s\n%i.%s",string,i+1,stringx);
			}
			fclose(failas);
		}
	}
	ShowPlayerDialog(playerid,8582,DIALOG_STYLE_LIST,"Keliones",string,"Gerai","Atsaukti");
	*/
	
	return 1;
}

CMD:prisijungti(playerid,params[])
{
	if(Keliones[Ijungta])
	{
		if(playerDB[playerid][specialybe] == 70 || playerDB[playerid][specialybe] == 72 || playerDB[playerid][specialybe] == 73 )
		{
			if(Keliones[DabartinisCP] != 0) return SendInfoMessage(playerid,"Kelione jau prasidejo!");
			if(KDalyvis[playerid][Dalyvauja]) return SendInfoMessage(playerid,"Jus jau prisijungete!");
			Keliones[Dalyviai]++;
			KDalyvis[playerid][Dalyvauja]=true;
			SetPlayerRaceCheckpoint(playerid, 0, KelionesKurimas[Keliones[DabartinisCP]][koordx], KelionesKurimas[Keliones[DabartinisCP]][koordy],KelionesKurimas[Keliones[DabartinisCP]][koordz],KelionesKurimas[Keliones[DabartinisCP]+1][koordx], KelionesKurimas[Keliones[DabartinisCP]+1][koordy],KelionesKurimas[Keliones[DabartinisCP]+1][koordz],18);
			SendClientMessage(playerid, COLOR_GREEN,"Jus prisijungete prie organizuojamos keliones, vaziuokite i CP.");
			SendClientMessage(playerid, COLOR_GREEN,"Noredami palikti kelione rasykite /palikti.");
			new msg[128];
			format(msg,sizeof(msg),"[racija] Operatore: %s prisijunge prie keliones!",ReturnName(playerid));
			SendMessageToKlubai(COLOR_YELLOW,msg);
			return 1;
		}
		else return SendInfoMessage(playerid,"Si komanda ne tau.");
	}
	else return SendInfoMessage(playerid,"Kelione nevyksta!");
}
CMD:palikti(playerid,params[])
{
	if(playerDB[playerid][specialybe] == 70 || playerDB[playerid][specialybe] == 72 || playerDB[playerid][specialybe] == 73)
	{
		if(!KDalyvis[playerid][Dalyvauja]) return SendInfoMessage(playerid,"Tu jau pasitraukei is keliones!");
		new Vardas[MAX_PLAYER_NAME], Pranesimas[64];
		DisablePlayerCheckpoint(playerid);
		DisablePlayerRaceCheckpoint(playerid);
		Keliones[Dalyviai]--;
		KDalyvis[playerid][Dalyvauja]=false;
		GetPlayerName(playerid, Vardas, sizeof(Vardas));
		HideCPS(playerid);	
		format(Pranesimas,sizeof(Pranesimas), "[Racija] %s pasitrauke is keliones.",Vardas);
		SendMessageToKlubai(0xFFFFFF30,Pranesimas);
		if(Keliones[Dalyviai] == 0)
		{
			Keliones[Ijungta]=false;
			Keliones[DabartinisCP]=0;
			SendMessageToKlubai(COLOR_WHITE,"[racija] Operatore: Visi dalyviai paliko kelione!");
		}
		return 1;
	}
	else return SendInfoMessage(playerid,"Si komanda ne tau.");
}
CMD:email(playerid,params[])
{
	ShowEmail(playerid);
	return 1;
}

CMD:garazas(playerid,params[])
{
	if(!galikast[playerid]) return 1;
	if(playerDB[playerid][hasmoney] || InkaUzsakymai[playerid][uamount] == 5)
		return 1;
	galikast[playerid]=false;
	SetTimerEx("GaliKast",2000,0,"i",playerid);
	new pname[MAX_PLAYER_NAME];
	GetPlayerName(playerid,pname,sizeof(pname));
	new pid;
	new vehicleid = GetPlayerVehicleID(playerid);

	if(GetPlace(playerid)!=PLACE_GARAGE)
	{
		foreach(Houses,i)
		{
			if(vehicleid)
			{
				if(vehicleid)
				{
					GetVehicleParamsEx(vehicleid,VehVars[0],VehVars[1],VehVars[2],VehVars[3],VehVars[4],VehVars[5],VehVars[6]);
					if(VehVars[0] == VEHICLE_PARAMS_OFF) return SendInfoMessage(playerid,"Jusu variklis isjungtas! Prasome ijungti ji.");
				}
				if(hInfo[i][Garazas] && IsPlayerInRangeOfPointEx(5.0,playerid,hInfo[i][GarazoX],hInfo[i][GarazoY],hInfo[i][GarazoZ]))
				{
					if(strcmp(hInfo[i][Name],pname,false) && strcmp(hInfo[i][Renter],pname,false) && !playerDB[playerid][admin] ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
					if(!GetPlayerFromCarlistID(vehicleid, pid)) return SendInfoMessage(playerid,"Darbinio automobilio ivezti cia negalite!");
	
					foreach(Player, pl)
					{
						if((GetPlayerSurfingVehicleID(pl) == vehicleid || IsPlayerInVehicle(pl,vehicleid)) && pl != playerid)
						{
							return SendInfoMessage(playerid,"Noredami ivaziuoti i garaza, islaipinkite keleivius.");
						}
					}
					SetVehiclePosFade(playerid,20,Garazai[hInfo[i][Garazas]-1][0],Garazai[hInfo[i][Garazas]-1][1],Garazai[hInfo[i][Garazas]-1][2],Garazai[hInfo[i][Garazas]-1][3],-1,(i+MAX_HOUSES));
				}
			}
			else
			{
				if(hInfo[i][Garazas] && IsPlayerInRangeOfPointEx(3.0,playerid,hInfo[i][GarazoX],hInfo[i][GarazoY],hInfo[i][GarazoZ]))
				{
					if(strcmp(hInfo[i][Name],pname,false) && strcmp(hInfo[i][Renter],pname,false) && !playerDB[playerid][admin]  ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");

					SetPlayerPosFade(playerid,20,Garazai[hInfo[i][Garazas]-1][0],Garazai[hInfo[i][Garazas]-1][1],Garazai[hInfo[i][Garazas]-1][2],-1,(i+MAX_HOUSES));
				}
			}
		}
	}
	else
	{
		new i = (GetPlayerVirtualWorld(playerid)-MAX_HOUSES);
		if(vehicleid)
		{
			if(hInfo[i][Garazas])
			{
			//	if(strcmp(hInfo[i][Name],pname,false) && strcmp(hInfo[i][Renter],pname,false) ) return SendClientMessage(playerid, c_r, "Sis namas nepriklauso jums!");
				foreach(Player, pl)
				{
					if((GetPlayerSurfingVehicleID(pl) == vehicleid || IsPlayerInVehicle(pl,vehicleid)) && pl != playerid)
					{
						//RemovePlayerFromVehicle(pl);
						return SendInfoMessage(playerid,"Noredami isvaziuoti is garazo, islaipinkite keleivius.");
					}
				}
				SetVehiclePosFade(playerid,20,hInfo[i][GarazoX],hInfo[i][GarazoY],hInfo[i][GarazoZ],hInfo[i][GarazoA],-1,0);
			}
		}
		else
		{
			if(hInfo[i][Garazas])
			{
			//	if(strcmp(hInfo[i][Name],pname,false) && strcmp(hInfo[i][Renter],pname,false) ) return SendClientMessage(playerid, c_r, "Sis namas nepriklauso jums!");

				
					SetPlayerPosFade(playerid,20,hInfo[i][GarazoX],hInfo[i][GarazoY],hInfo[i][GarazoZ],-1,0);
			}
		}
	}
	return 1;
}

CMD:pakrauti(playerid,params[])
{
	if(GetPlace(playerid) != PLACE_GARAGE) return SendInfoMessage(playerid,"Komanda naudojama tik garaze!");
	if(IsPlayerInAnyVehicle(playerid)) return SendInfoMessage(playerid,"Islipk is automobilio!");
	new vehicleid = GetClosestVehicleid(playerid,20.0);
	if (vehicleid == INVALID_VEHICLE_ID) return SendInfoMessage(playerid,"Salia taves nera automobilio!");
	if(GetPlayerFromCarlistCar(vehicleid) == -1 && GetPlayerFromCarlistCar2(vehicleid) == -1 && GetPlayerFromCarlistCar3(vehicleid) == -1) return SendInfoMessage(playerid,"Krauti gali tik savo automobili!");
	if(Kraunasi[vehicleid])
	{
		Kraunasi[vehicleid]=0;
		SendInfoMessage(playerid,"Nebekrauni savo automobilio!");
	}
	else 
	{
		if(vehicleDB[vehicleid][energy] > 99.0) return SendInfoMessage(playerid,"Tavo masinos nereikia krauti!");
		Kraunasi[vehicleid] = 1;
		new msg[128];
		new minutes = floatround((100.0-vehicleDB[vehicleid][energy]) / 1.8);
		format(msg,sizeof(msg)," * Pradejai krauti automobili. Siuo metu jo akumuliatorius %.1f%%. Visiskai jis pasikraus po %i min.",vehicleDB[vehicleid][energy],minutes);
		SendClientMessage(playerid,COLOR,msg);
	}
	return 1;
}

CMD:lauztis(playerid,params[])
{
	if(playerDB[playerid][specialybe]!=81 && playerDB[playerid][specialybe] != 83 && !playerDB[playerid][admin] && playerDB[playerid][specialybe] != 66){SendInfoMessage(playerid,"Si komanda tik Teisesaugai ir gaisrinei."); return 1;}
	new	housenumber = GetHouseID(playerid);

	if(housenumber == -255) return SendInfoMessage(playerid,"Noredamas islauzti duris, privalai stovet prie duru ir but atsisukes i jas.");
	Lauztis(playerid,housenumber);
	return 1;
}

CMD:p(playerid,params[])
{
	//new money[100];
	if(playerDB[playerid][authstate]==0) return 0;
	SendClientMessage(playerid,COLOR,"[VVP] Vartotojo valdymo panelæ ájungti galite paraðæ /p");
	AddDListItem(playerid,"Inventorius", PAN_INVENTORIUS);
	AddDListItem(playerid,"Veiksmai", PAN_VEIKSMAI);
    AddDListItem(playerid,"Paskyra", PAN_AKAUNTAS);
	AddDListItem(playerid,"Nustatymai", PAN_NUSTATYMAI);
	AddDListItem(playerid,"Kreditai", PAN_KREDITAI);
	AddDListItem(playerid,"Kovos stiliai", PAN_KOVOS);
	AddDListItem(playerid,"Vaikðèiojimo stiliai", PAN_STILIAI);
	
	if(playerDB[playerid][admin]) AddDListItem(playerid,"Administracijos panele", PAN_APANELE);
	if(playerDB[playerid][plead]==80) AddDListItem(playerid,"Teisesaugos ataskaitos", PAN_ATASKAITOS);
	if(playerDB[playerid][plead]==80 || playerDB[playerid][admin]) AddDListItem(playerid,"Teisesaugos elitiniai", PAN_ELITINIAI);
    ShowPlayerDList(playerid, 339, "Vartotojo panele", "Rinktis", "Iseiti");
	return 1;
}
CMD:stiliai(playerid,params[])
{
	new query[128];
	format(query,sizeof(query),"SELECT Stilius FROM Stiliai WHERE Vardas='%s'",ReturnName(playerid));
	mysql_function_query(SQL, query, true, "SQL_Stiliai", "i",playerid);
	return 1;
}

/*
CMD:keistis(playerid,params[])
{
	if(GetPlayerScore(playerid) < 100) return SendInfoMessage(playerid,"Dovanomis galima keistis tik nuo 100 xp!");
	new name[MAX_PLAYER_NAME];
	if(sscanf(params,"s[24]",name)) return SendInfoMessage(playerid,"Naudojimas: /keistis [vardo dalis]");
	new mid = GetPlayeridMid(name);
	if(mid==playerid || mid==INVALID_PLAYER_ID || !IsPlayerConnected(mid)) return SendInfoMessage(playerid,"Tokio zaidejo nera!");
	if(SiuloKeistis[mid] == playerid || SiuloKeistis[playerid] == mid) return SendInfoMessage(playerid,"Jus jau siulete keistis siam zaidejui!");
	SiuloKeistis[mid]=playerid;
	new msg[128];
	format(msg,sizeof(msg)," * Zaidejas %s jums siulo keistis dovanomis! Noredami sutikti, rasykite /ok",ReturnName(playerid));
	SendClientMessage(mid,PURPLE,msg);
	format(msg,sizeof(msg)," * Pasiulete zaidejui %s keistis dovanomis.",ReturnName(mid));
	SendClientMessage(playerid,PURPLE,msg);
	return 1;
}
*/

CMD:rukyti(playerid,params[])
{
	//if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT || GetPlayerInterior(playerid)) return SendInfoMessage(playerid,"Iseikite i lauka!");
	if(playerDB[playerid][parukes] || playerDB[playerid][ruko] || playerDB[playerid][narkomanas] || playerDB[playerid][ant] || playerDB[playerid][suristas]) return SendInfoMessage(playerid,"Tu neseniai rukei arba jau apsineses!");
	if(!playerDB[playerid][cigaretes]) return SendInfoMessage(playerid,"Neturi cigareciu. Ju gali nusipirkti spaudos kioske.");
	playerDB[playerid][cigaretes] -- ;
	if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) 
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
	playerDB[playerid][ruko]=1;
	LogA(playerid,"Ruko");
	SendInfoMessage(playerid,"~y~Prisidegei cigarete");
	SendClientMessage(playerid,COLOR,"Spauskite MOUSE1, kad Traukti arba ENTER, kad ismesti.");
	return 1;
}
CMD:cigarete(playerid,params[])
{
	new vardas[128];
	if(sscanf(params,"s[128]",vardas)) return SendInfoMessage(playerid,"Pavaisinti cigarete: /cigarete [Vardas_Pavarde]");
	new id = GetPlayeridMid(vardas);
	if (id == INVALID_PLAYER_ID){ SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	if (id == playerid){ SendInfoMessage(playerid,"Sau cigaretes duot negali"); return 1;}
	new Float:Coo[3];
	GetPlayerPos(id,Coo[0],Coo[1],Coo[2]);
	if(!IsPlayerInRangeOfPointEx(8, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(id)==PLAYER_STATE_SPECTATING){SendInfoMessage(playerid,"Zaidejas per toli, prieikite arciau."); return 1;}
	if(!playerDB[playerid][cigaretes]) return SendInfoMessage(playerid,"~r~Neturi cigaretes!");
	if(playerDB[id][cigaretes] < 20)
	{
		ProcessAchievement(playerid, 116);
		playerDB[playerid][cigaretes]--;
		playerDB[id][cigaretes]++;
		new msg[128];
		format(msg,sizeof(msg)," * %s jus pavaisino cigarete. Naudokite komanda /rukyti",ReturnName(playerid));
		SendClientMessage(id,WHITE,msg);
		SendInfoMessage(playerid,"Pavaisinai cigarete!");
	}
	else SendInfoMessage(playerid,"Zaidejas jau turi pilna pakeli!");
	return 1;
}
CMD:duk(playerid,params[])
{
	ShowPlayerDialog(playerid,2580,DIALOG_STYLE_LIST,"Dazniausiai uzduodami klausimai","1. Kodel musu serveris?\n2. Nuo ko pradeti?\n3. Ar serveryje yra autosave sistema?\n4. Negaunu kreditu. Ka daryti?\n5. Kaip palikti darba?","Gerai","Iseiti");
	return 1;
}
CMD:mainytis(playerid,params[])
{
	new string[128];
	if(sscanf(params,"s[24]",string)) return SendInfoMessage(playerid,"Naudojimas: /mainytis [Vardas_Pavarde]");
	foreach(Player,i)
	{
		if(NoriMainytis[i]==playerid)
		{
			SendInfoMessage(NoriMainytis[i],"Mainai atsaukti!");
			SendInfoMessage(NoriMainytis[i],"Atsaukete mainus!");
			NoriMainytis[i]=-1;
			return 1;
		}
	}
	foreach(Player, i)
	{
		if(offerCar[i][0] == playerid || offerCar2[i][0]==playerid || offerCar3[i][0]== playerid) return SendInfoMessage(playerid,"Tu dabar siulai automobili! Naudok /atsaukti");
		if(offerHouse[i][0] == playerid) return SendInfoMessage(playerid,"Tu dabar siulai nama! Daryk relog.");
		if(offerBiz[i][0] == playerid) return SendInfoMessage(playerid,"Tu dabar siulai versla! Daryk relog.");
	}
	if(TradingWith[playerid] != -1) return SendInfoMessage(playerid, "Tu jau mainaisi!");
	new tid = GetPlayeridMid(string);
	//TradingWith[playerid]=0;
	if(tid==INVALID_PLAYER_ID){SendInfoMessage(playerid,"Tokio vardo nera."); return 1;}
	if(tid==playerid){SendInfoMessage(playerid,"Su savim mainytis negali."); return 1;}
	
	if(TradingWith[tid] != -1) return SendInfoMessage(playerid, "Zaidejas jau mainosi!");
	if( GetPlayerScore(tid) < 100 || GetPlayerScore(playerid) < 100 ) return SendInfoMessage(playerid,"Zaidejas dar nepakankamai patyres.");

	new Float:narkx, Float:narky, Float:narkz;
	GetPlayerPos(tid, narkx, narky, narkz);
	if(!IsPlayerInRangeOfPointEx(10, playerid, narkx, narky, narkz) || GetPlayerState(tid)==PLAYER_STATE_SPECTATING)
	{
		SendInfoMessage(playerid,"Jus per toli nuo pirkejo (10 m)");
		return 1;
	}
	if(tid==playerid) return SendInfoMessage(playerid,"Su savim mainytis negali!");
	NoriMainytis[tid]=playerid;
	SendInfoMessage(playerid,"Pasiulete mainytis!");
	new msg[256];
	format(msg,sizeof(msg)," * %s siûlo jums mainytis! Sutikti galite paspaudæ ~k~~CONVERSATION_YES~, o atmesti paspaudæ ~k~~CONVERSATION_NO~",ReturnName(playerid));
	SendClientMessage(tid,BLUE,msg);
	return 1;
}

/*
CMD:dooropen(playerid,params[])
{
	if(IsPlayerInRangeOfPointEx(2.0, playerid,1849.32995605,-1714.31005859,3201.54003906))
	{
		MoveDynamicObject(door1,1849.32995605-1.25,-1714.31005859,3201.54003906,0.50);
		SendClientMessage(playerid, 0xFFFFFFFF, "SERVER: door 1 has been opened!");
		return 1;
	}
	else if(IsPlayerInRangeOfPointEx(2.0, playerid,1847.31994629,-1722.56994629,3201.54003906))
	{
		MoveDynamicObject(door2,1847.31994629,-1722.56994629-1.25,3201.54003906,0.50);
		SendClientMessage(playerid, 0xFFFFFFFF, "SERVER: door 2 has been opened!");
		return 1;
	}
	else if(IsPlayerInRangeOfPointEx(2.0, playerid,1854.01953125,-1726.27343750,3201.54003906))
	{
		MoveDynamicObject(door3,1854.01953125,-1726.27343750-1.25,3201.54003906,0.50);
		SendClientMessage(playerid, 0xFFFFFFFF, "SERVER: door 3 has been opened!");
		return 1;
	}
	else if(IsPlayerInRangeOfPointEx(2.0, playerid,1862.02246094,-1710.91992188,3201.54003906))
	{
		MoveDynamicObject(door4,1862.02246094-1.25,-1710.91992188,3201.54003906,0.50);
		SendClientMessage(playerid, 0xFFFFFFFF, "SERVER: door 4 has been opened!");
		return 1;
	}
	else SendClientMessage(playerid, 0xFFFFFFFF, "SERVER: You are not near any door!");
	return 1;
}
CMD:doorclose(playerid,params[])
{
	if(IsPlayerInRangeOfPointEx(2.0, playerid,1849.32995605,-1714.31005859,3201.54003906))
	{
		MoveDynamicObject(door1,1849.32995605,-1714.31005859,3201.54003906,0.50);
		SendClientMessage(playerid, 0xFFFFFFFF, "SERVER: door 1 has been closed!");
		return 1;
	}
	else if(IsPlayerInRangeOfPointEx(2.0, playerid,1847.31994629,-1722.56994629,3201.54003906))
	{
		MoveDynamicObject(door2,1847.31994629,-1722.56994629,3201.54003906,0.50);
		SendClientMessage(playerid, 0xFFFFFFFF, "SERVER: door 2 has been closed!");
		return 1;
	}
	else if(IsPlayerInRangeOfPointEx(2.0, playerid,1854.01953125,-1726.27343750,3201.54003906))
	{
		MoveDynamicObject(door3,1854.01953125,-1726.27343750,3201.54003906,0.50);
		SendClientMessage(playerid, 0xFFFFFFFF, "SERVER: door 3 has been closed!");
		return 1;
	}
	else if(IsPlayerInRangeOfPointEx(2.0, playerid,1862.02246094,-1710.91992188,3201.54003906))
	{
		MoveDynamicObject(door4,1862.02246094,-1710.91992188,3201.54003906,0.50);
		SendClientMessage(playerid, 0xFFFFFFFF, "SERVER: door 4 has been closed!");
		return 1;
	}
	else SendClientMessage(playerid, 0xFFFFFFFF, "SERVER: You are not near any door!");
	return 1;
}
*/

CMD:d(playerid,params[])
{
	if(!playerDB[playerid][plead] && !Pareigos(playerid,"Dyrikai")) return SendInfoMessage(playerid,"Si komanda tik direktoriams.");
	if(strlen(params) == 0 || params[0] == '\0') return SendInfoMessage(playerid,"Naudojimas: /d [tekstas]");
	if(GangJobLead(playerid) && !Pareigos(playerid,"Dyrikai")) return SendInfoMessage(playerid,"Nelegalus darbai neturi direktoriu chato");
	new msg[256];
	format(msg,sizeof(msg),"[dchat] %s: %s",ReturnName(playerid),params);
	foreach(Player,i)
	{
		if((playerDB[i][plead] && !GangJobLead(i)) || Pareigos(i,"Dyrikai"))
		{
			SendClientMessage(i,ORANGE,msg);
		}
	}
	return 1;
}

CMD:dpadeti(playerid,params[])
{
	if(!playerDB[playerid][plead]) return SendInfoMessage(playerid,"Si komanda tik direktoriams!");
	return SendInfoMessage(playerid,"Pinigai bus nuskaiciuoti duodant pakvietima i nelegalu darba!");
}

CMD:patruliavimas(playerid,params[])
{
	if(
		playerDB[playerid][specialybe]!=80 && 
		playerDB[playerid][specialybe]!=82 && 
		playerDB[playerid][specialybe]!=81 && 
		playerDB[playerid][specialybe]!=83 && 
		playerDB[playerid][specialybe]!=84 && 
		!playerDB[playerid][admin]
	)
	{SendInfoMessage(playerid,"Si komanda tik policininkams"); return 1;}
	
	if(Patruliavimas[playerid] != -1)
	{
		GangZoneHideForPlayer(playerid,Patruliai[Patruliavimas[playerid]][gangz]);
		Patruliai[Patruliavimas[playerid]][pplin]--;
		Patruliavimas[playerid]=-1;
		SendClientMessage(playerid,YELLOW," * Baigei patruliuoti!");
	}
	else
	{
		if(GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0) return SendInfoMessage(playerid,"Patruliuoti uzdaroje patalpoje negalima.");
		ShowPatruliavimoDialog(playerid);
	}
	return 1;
}

CMD:trintizona(playerid,params[])
{
	if(playerDB[playerid][plead]==80 || playerDB[playerid][admin])
	{
		if(Patruliavimas[playerid] == -1) return SendInfoMessage(playerid,"Pirmiausia turi patruliuoti!");
		new id = Patruliavimas[playerid];
		foreach(Player, i)
		{
			if(Patruliavimas[i] == id)
			{
				SendClientMessage(playerid,YELLOW," * Direktorius istryne sia patruliavimo zona.");
				Patruliavimas[i]=-1;
				GangZoneHideForPlayer(i,Patruliai[id][gangz]);
			}
		}
		GangZoneDestroy(Patruliai[id][gangz]);
		Patruliai[id][used]=0;
		DestroyDynamicArea(Patruliai[id][dynamicarea]);
		Patruliai[id][pplin]=0;
		Patruliai[id][pplmax]=0;
	}
	else return SendInfoMessage(playerid,"Si komanda ne tau!");
	return 1;
}
CMD:kurtizona(playerid,params[])
{
	if(playerDB[playerid][plead]==80 || playerDB[playerid][admin])
	{
		new name[24],Float:range,maxppl;
		if(sscanf(params,"fis[24]",range,maxppl,name)) return SendClientMessage(playerid,YELLOW, " * Naudojimas /kurtizona [atstumas] [max patruliu] [pavadinimas]");
		if(strlen(name) >= 12) return SendInfoMessage(playerid,"Per ilgas pavadinimas!");
		new Float:coo[3];
		GetPlayerPos(playerid,coo[0],coo[1],coo[2]);
		CreatePatruliavimoZone(playerid,name,maxppl,coo[0],coo[1],range);
		return 1;
	}
	else return SendInfoMessage(playerid,"Si komanda ne tau!");
}


CMD:ginklai(playerid,params[])
{
	if(playerDB[playerid][psratasvydis])
	{
		ShowPlayerDialog(playerid,4780,DIALOG_STYLE_LIST,"Pasirinkite pirma ginkla:","Colt\nSilenced Colt\nDesert Eagle\nShotgun","Gerai","");
	}
	return 1;
}
CMD:baldai(playerid,params[])
{
	if(GetPlace(playerid)==PLACE_HOUSE)
	{ 
		new housenumber,pname[MAX_PLAYER_NAME];
		housenumber = GetPlayerHouseID(playerid);
		GetPlayerName(playerid, pname, 24);
		if ( strcmp(hInfo[housenumber][Name],pname,false) != 0 && GetPVarInt(playerid,"irengineja") != housenumber && !IsPlayerAdmin(playerid))
		{
			if(playerDB[playerid][specialybe] == 34)
			{
				CheckNTAIrengimas(playerid,housenumber,1);
				return 1;
			}
			else
				return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
		} 
		/*
		if( GetPVarInt(playerid,"irengineja") == housenumber)
			ShowPlayerDialog(playerid,6871,DIALOG_STYLE_LIST,"Baldu sistema","Perstatyti, pasirinkti baldus","Gerai","Atsaukti");
		else
			ShowPlayerDialog(playerid,6871,DIALOG_STYLE_LIST,"Baldu sistema","Perstatyti, pasirinkti baldus\nIðmesti baldus\nPerveþti baldus á kità namà\nLeisti NTA árengti namà","Gerai","Atsaukti");
		*/
		mysql_function_query(SQL,"SELECT * From `baldai_cat` order by pav asc",true,"SQL_SelectMoveBaldai","ii",playerid,housenumber);
		return 1;
	}
	else
	{
		SendInfoMessage(playerid,"Si komanda naudojama namuose.");
	}
	return 1;
}	
CMD:tekstura(playerid,params[])
{
	new textureid;
	if(sscanf(params,"i",textureid))
		return SendInfoMessage(playerid, "Naudojimas: /tekstura [id]");
	if(!IsPlayerInWorld(playerid))
		return SendInfoMessage(playerid, "Komanda naudojama pasauliuose");
	if(textureid < 1 || textureid >= NUM_TEXTURES)
	{
		return SendInfoMessage(playerid, "Netinkama tekstura");
	}
	if(GetPVarInt(playerid, "dazymas"))
	{
		SetPVarInt(playerid, "dazymas", textureid);

		new str[24];
		format(str,24,"~g~%i",GetPVarInt(playerid, "dazymas"));
		GameTextForPlayer(playerid, str, 1000, 3);
		TexturizeWorldObject(playerid, GetPVarInt(playerid, "SelectedObj"), GetPVarInt(playerid, "matid"), GoodTextures[GetPVarInt(playerid, "dazymas")]);
	}	
	return 1;
}
CMD:dazyti(playerid,params[])
{

	if(GetPlace(playerid)==PLACE_HOUSE)
	{ 
		new housenumber,pname[MAX_PLAYER_NAME];
		housenumber = GetPlayerHouseID(playerid);
		if(hInfo[housenumber][polyId] != -1)
			return SendInfoMessage(playerid,"Sio namo dazyti negali!");
		GetPlayerName(playerid, pname, 24);
		if ( strcmp(hInfo[housenumber][Name],pname,false) != 0 && GetPVarInt(playerid,"irengineja") != housenumber)
		{
			if(playerDB[playerid][specialybe] == 34)
			{
				CheckNTAIrengimas(playerid,housenumber,1);
				return 1;
			}
			else
				return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
		} 
		if(GetPVarInt(playerid, "dazymas"))
		{
			if(strval(params) > 0 && strval(params) < NUM_TEXTURES)
			{


				SetPVarInt(playerid, "dazymas", strval(params));

				new str[24];
				format(str,24,"~g~%i",strval(params));
				GameTextForPlayer(playerid, str, 1000, 3);
				Texturize(GetPlayerHouseID(playerid),GetPVarInt(playerid, "isdoor"),GetPVarInt(playerid, "matid"),GoodTextures[GetPVarInt(playerid, "dazymas")]);
				SendClientMessage(playerid, -1, " * Pasirinkai ID!");
				return 1;
			}
			else
			{
				return SendClientMessage(playerid, -1, " * Tokios tekstûros nëra. Spausk ENTER noredamas uzbaigti dazyma.");
			}
		}

		ShowPlayerDialog(playerid,6900,DIALOG_STYLE_LIST,"Daþymas","Sienos\nDurys","Gerai","Atsaukti");
		return 1;
	}
	else
	{
		SendInfoMessage(playerid,"Si komanda naudojama namuose.");
	}
	return 1;
}	
/*
CMD:chasetest(playerid,params[])
{
	ChaseMeter[playerid]=500;
	return 1;
}*/

CMD:achievements(playerid,params[])
{
	if(GetPlayerScore(playerid) < 100) return SendInfoMessage(playerid,"Pasiekimus gali vykdyt tik nuo 100xp!");
	new namux[128];
	if(sscanf(params,"s[24]",namux)) 
		ShowAchievements(playerid);
	else
	{
		new pid = GetPlayeridMid(namux);
		if(pid == INVALID_PLAYER_ID || pid == playerid || !IsPlayerConnected(pid)) return SendInfoMessage(playerid,"Netinkamas zaidejas!");
		ShowAchievements(pid,playerid);
	}
	return 1;
}
CMD:pasiekimai(playerid,params[])
{
	
	return cmd_achievements(playerid,params);
}
CMD:duel(playerid,params[])
{
	if(playerDB[playerid][psratasvydis] != 1 && playerDB[playerid][psratasvydis] != 2)
	{
		return SendInfoMessage(playerid,"Komanda naudojama tik pirmame dazasvydydzio zemelapyje.");
	}
	if(DuelKova[playerid] != -1)
	{
		new msg[128];
		format(msg,sizeof(msg),"[DUEL] %s nutrauke kova!",ReturnName(playerid));
		SendClientMessage(playerid, YELLOW,msg);
		SendClientMessage(DuelKova[playerid],YELLOW,msg);
		SetPlayerHealth(DuelKova[playerid],0.0);
		SetPlayerHealth(playerid,0.0);
	}
	if(SiuloDuel[playerid] != -1)
	{
		if(!IsPlayerConnected(SiuloDuel[playerid]) || !playerDB[SiuloDuel[playerid]][psratasvydis]) 
		{
			SiuloDuel[playerid]=-1;
			SendClientMessage(playerid,YELLOW,"[DUEL] Zaidejas atsijunge arba jis nebe sratasvydyje.");
			return 1;
		}
		SendClientMessage(SiuloDuel[playerid],YELLOW,"[DUEL] Zaidejas prieme jusu issuki! Pasitraukti is kovos galite parase /duel");
		SendClientMessage(playerid,YELLOW,"[DUEL] Priemete issuki! Pasitraukti is kovos galite parase /duel");
		if(dazumap == 3)
		{
			SendClientMessage(SiuloDuel[playerid],COLOR_PINK,"[DUEL] CBug Ijungtas.");
			SendClientMessage(playerid,COLOR_PINK,"[DUEL] CBug Ijungtas.");
		}
		DuelKova[SiuloDuel[playerid]] = playerid;
		DuelKova[playerid]= SiuloDuel[playerid];
		ResetGunData(playerid);
		GivePlayerWeaponEx(playerid,24,100000);
		ResetGunData(DuelKova[playerid]);
		GivePlayerWeaponEx(DuelKova[playerid],24,100000);
		SetPlayerVirtualWorld(playerid, 10000+playerid);
		SetPlayerVirtualWorld(SiuloDuel[playerid], 10000+playerid);
		SetPlayerTeam(playerid,NO_TEAM);
		SetPlayerTeam(SiuloDuel[playerid],NO_TEAM);
		SetPlayerPoz(playerid, -973.9007,1081.6639,1347.9880, _, _, 0);
		SetPlayerFacingAngle(playerid,0.0);
		SetPlayerHealth(playerid,100.0); SetPlayerArmour(playerid,100.0);
		SetPlayerHealth(SiuloDuel[playerid],100.0); SetPlayerArmour(SiuloDuel[playerid],100.0);
		SetPlayerPoz(SiuloDuel[playerid], -973.9084,1073.1979,1347.9993, _, _, 0);
		SetPlayerFacingAngle(SiuloDuel[playerid],180.0);
		SetPlayerInterior(playerid, 10);
		SetPlayerInterior(SiuloDuel[playerid], 10);
		SiuloDuel[playerid]=-1;
		return 1;
	}
	new vardux[128];
	if(sscanf(params,"s[24]",vardux)) return SendInfoMessage(playerid,"Kviesti i dvikova: /duel [Vardas_Pavarde]");
	new tid = GetPlayeridMid(vardux);
	if(tid==INVALID_PLAYER_ID || tid == playerid){SendInfoMessage(playerid,"Tokio vardo nera"); return 1;}
	if(!playerDB[tid][psratasvydis]) return SendInfoMessage(playerid,"Zaidejas ne dazasvidyje!");
	new msg[120];
	format(msg,sizeof(msg),"[DUEL] %s Jus kviecia i dvikova! Rasykite /duel kad sutiktumete.",ReturnName(playerid));
	SendClientMessage(tid,YELLOW,msg);
	format(msg,sizeof(msg),"[DUEL] Pakvietei %s i dvikova!",ReturnName(tid));
	SendClientMessage(playerid,YELLOW,msg);
	SiuloDuel[tid]=playerid;
	return 1;
}
CMD:forsale(playerid,params[])
{
	if(playerDB[playerid][specialybe] != 34) return SendInfoMessage(playerid,"Si komanda tik NT agentams!");
	new cost,hid;
	if (sscanf(params, "ii",hid,cost))
	{
		SendClientMessage(playerid,-1," * NTA gali pastatyti parduodamo namo zenkla prie nuosavu namu. Kaina NT agentui: 10000€");
		SendClientMessage(playerid,-1," * Naudojimas: /forsale [namo nr] [kaina]");
		return 1;
	}
	if(cost < 0) return SendInfoMessage(playerid," Netinkama kaina!");
	if(GetPlayerMoneyA(playerid) < 10000) return SendClientMessage(playerid,-1," * Neturite pakankamai pinigu! Reikia: 10000€");

	new Float:R=99999.999;
	new closest=-1;
	foreach (Houses, i)
	{
		new Float:dist = GetPlayerDistanceFromPoint(playerid,hInfo[i][iconx], hInfo[i][icony], hInfo[i][iconz]);
		if(dist < R && dist < 100.0)
		{
			R= dist;
			closest = i;
		
		}
	}
	if(closest != hid)
	{
		new msg[128];
		format(msg,sizeof(msg)," * Jus stovite arciau namo nr. %i, negu %i, todel zenklo cia statyti negalite!",closest,hid);
		SendClientMessage(playerid,-1,msg);
		return 1;
	}
	if(R > 50.0) return SendClientMessage(playerid,-1," * Zenklas per toli nuo namo pickupo!");
	if(hInfo[hid][daugiabutis]) return SendClientMessage(playerid,-1," * Prie buto sio zenklo statyti negalite!");
	new ownerid = INVALID_PLAYER_ID;
	foreach(Player, i)
	{
		if (strcmp(hInfo[hid][Name],ReturnName(i),false) == 0) ownerid=i;
	}
	if(ownerid == INVALID_PLAYER_ID) return SendClientMessage(playerid,-1," * Sis namas neturi savininko arba jis neprisijunges!");
	new Float:Coo[3];
	GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
	if(!IsPlayerInRangeOfPointEx(20, ownerid, Coo[0],Coo[1],Coo[2])) return SendClientMessage(playerid,-1," * Namo savininkas turi stoveti arciau jusu!");
	if(fsHouses[hid][fobjid] != 0) return SendClientMessage(playerid,-1," * Sis namas jau turi for sale zenkla! Prieikite prie jo ir spauskite H.");
	CreateForSaleSign(playerid,hid,cost);
	GivePlayerMoneyA(playerid,-10000);
	//pelnas[33]+=10000;
	if(GetTickCount()-LastForsale[playerid] > 1000*60*60)
	{
		Pelnas(playerid,33,10000);
	}
	
	LastForsale[playerid]=GetTickCount();
	SendClientMessage(playerid, -1, " * Sekmingai pastatei for sale zenkla! I pelna uzdirbai 10000€");
	return 1;

}

/*
CMD:velykos(playerid,params[])
{
	new msgz[1024];
	format(msgz,1024,"Los Santos Gyvenimas administracija siuncia Jums silciausius linkejimus sv. Velyku proga!\n{ffd750}Kvieciame prisijungti prie Velykinio evento \"Easter egg hunt\".\nTikslas yra surasti 12 velykiniu kiausiniu, kurie yra paslepti visame San Andreas zemelapyje.\n");
	format(msgz,1024,"%sSurade viena kiausini, ji galesite pasideti savo name ar bute*, o surade visus gausite vienetini automobili*!\nSpauskite \"Dalyvauti\" kad pamatytumet uzuomenas. Uzuomenos parasytos anglu kalba, todel Jums gali tekti jas issiversti.\nSekmes!\n{ff0000}Kiausinio negalesite gauti jei neturite namo, o automobilio - jei jau turite 3 automobilius.",msgz);
	ShowPlayerDialog(playerid,1493,DIALOG_STYLE_MSGBOX,"Sv. Velykos",msgz,"Dalyvauti","Iseiti");
	return 1;
}*/
CMD:myversion(playerid,params[])
{
	new string[40];
    GetPlayerVersion(playerid, string, sizeof(string));
    format(string, sizeof(string), "Your version of SA-MP: %s", string);
    SendClientMessage(playerid, 0xFFFFFFFF, string);
    return 1;
}

/*
CMD:gimtadienis(playerid,params[])
{
	//PlayerPlaySound(playerid, strval(params) ,0,0,0);//17802
	new day,year,month;
	getdate(year,month,day);
	if(!(month == 5 && day == 15)) {
		return SendInfoMessage(playerid," Gimtadienio eventas baigesi!");
	}
	new query[128];
	format(query,128,"SELECT k1,k2,k3,k4,k5,prizas From `Easter18` WHERE `Vardas`='%s'",ReturnName(playerid));
	mysql_function_query(SQL, query, true, "SQL_kiausas", "i", playerid);
	return 1;
}*/
CMD:drift(playerid,params[])
{
    DriftPoints[playerid]=0;
    LastAngle[playerid]=0;
    DriftBonus[playerid]=0;
	g_DriftPlayers[playerid][driftState] = DRIFT_STATE_NONE;
    g_DriftPlayers[playerid][timeoutTicks] = 0;

    OnPlayerDriftEnd(playerid);
    if(Iter_Contains(PlayersDrifting, playerid))
    {
        Iter_Remove(PlayersDrifting, playerid);
        SendClientMessage(playerid, -1, "[DRIFT] Iðjungei drift skaièiuoklæ!");
    }
    else
    {
        Iter_Add(PlayersDrifting, playerid);
        SendClientMessage(playerid, -1, "[DRIFT] Ájungei drift skaièiuoklæ!");
    }
    return 1;
}

CMD:loto(playerid,params[])
{
	new msg[256];
	if(GetPVarInt(playerid, "LotoShown"))
	{
		if(GetPVarInt(playerid, "LotoRolling"))
			return SendClientMessage(playerid,RED," * Palauk kol pasibaigs sukimas!");
		HideLotoTextDraws(playerid);
		DestroyLotoTextDraws(playerid);
	}
	else
	{
		if(GetPlayerInterior(playerid) || GetPlayerVirtualWorld(playerid) || CheckZone(playerid))
			return SendInfoMessage(playerid,"Iseik i lauka!");
		CrateLotoTextDraws(playerid);
		ShowLotoTextDraws(playerid);
		if(!playerDB[playerid][loterijos])
			format(msg,sizeof(msg)," * Neturi loterijos bilietu! Nusipirk juos paraðæs /kreditai");
		else if(playerDB[playerid][loterijos] == 1)
			format(msg,sizeof(msg),"{FFFFFF} * Turi {335bff}%i {FFFFFF}loterijos bilietà.",1);
		else
			format(msg,sizeof(msg),"{FFFFFF} * Turi {335bff}%i {FFFFFF}loterijos bilietus.",playerDB[playerid][loterijos]);
		SendClientMessage(playerid, RED,msg);
		SendClientMessage(playerid, COLOR, " * Iðeiti ið loterijos gali paraðæs /loto");
	}
	return 1;
}


CMD:rida(playerid,params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if(!vehicleid)
		return SendInfoMessage(playerid,"Turite sedeti automobilyje");

	new pid;
	new ida = GetPlayerFromCarlistID(vehicleid,pid);
	new remontostr[256];
	if(ida)
	{
		new reparatur = 0;
		new carid = 0;
		switch(ida)
		{
			case 1: carid = Carlist[pid][Typ];
			case 2: carid = Carlist2[pid][Typ];
			case 3: carid = Carlist3[pid][Typ];
		}
		reparatur = floatround(aVehicleNames[carid][Repair]/AdjustByRida(vehicleid,RIDA_REMONTAS));	
		
		format(remontostr,256,"(%s€)",FormatNumber(reparatur));
	}
	new msg[3000];
	format(msg,sizeof(msg),"\
		{FFFFFF}Automobilio rida:{335bff} %.1fkm\n\n\n\
		{00EE00}Ridos bonusai:\n\n\
		{FFFFFF}Uþvedimo greitis:{9aaeff} %.1fx\n\
		{FFFFFF}Remonto kaina:{9aaeff} %.1f%% %s\n\
		{FFFFFF}Apdauþytos maðinos greitis:{9aaeff} %.1fx\n\
		{FFFFFF}Uþvedimo tikimybë:{9aaeff} %.1fx\n\
		{FFFFFF}Nitro atsistatymas:{9aaeff} %.1fsec.",\
		vehicleDB[vehicleid][rida],AdjustByRida(vehicleid,RIDA_UZVEDIMAS),100.0/AdjustByRida(vehicleid,RIDA_REMONTAS),remontostr,AdjustByRida(vehicleid,RIDA_SULETEJIMAS),\
		AdjustByRida(vehicleid,RIDA_UZVEDIMO_TIKIMYBE),AdjustByRida(vehicleid,RIDA_NITRO));
	new model = GetVehicleModel(vehicleid);
	if(model == BIKE || model == MTBIKE)
		format(msg,sizeof(msg),"%s\n{FFFFFF}Maksimalus greitis: {9aaeff} %.1fx",msg,AdjustByRida(vehicleid,RIDA_SULETEJIMAS));
	ShowPlayerDialog(playerid, 23323, DIALOG_STYLE_MSGBOX, "Rida", msg, "Gerai","");
	return 1;

}
/*
CMD:helovynas(playerid,params[])
{
	if(!helovynas)
		return SendInfoMessage(playerid,"Helovyno eventas nevyksta!");

	new stata = GetPlayerState(playerid);
	new vehicleid = GetPlayerVehicleID(playerid);
	if(stata == PLAYER_STATE_DRIVER && (playerDB[playerid][specialybe]==5 || playerDB[playerid][specialybe]==55 || playerDB[playerid][specialybe]==62 || vagia[playerid] || vpakrauta[vehicleid]==1 || vbankomatams[vehicleid]==1) )
	{
		SendInfoMessage(playerid,"Prasome islipti is automobilio.");
		return 1;
	}
	SetPlayerCheckpoint(playerid,2119.5464,-1740.5907,13.5664,6.0);
	SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten rasite helovyno eventa.");
	return 1;			
}
*/
/*
CMD:kaledos(playerid,params[])
{
	new day,month,year;
	getdate(year, month, day);
	if(month != 12 || day < 20)
	{
		printf("kaledos fail %i %i %i", year, month, day);
		return 0;
	}
	new stata = GetPlayerState(playerid);
	new vehicleid = GetPlayerVehicleID(playerid);
	if(stata == PLAYER_STATE_DRIVER && (playerDB[playerid][specialybe]==5 || playerDB[playerid][specialybe]==55 || playerDB[playerid][specialybe]==62 || vagia[playerid] || vpakrauta[vehicleid]==1 || vbankomatams[vehicleid]==1) )
	{
		SendInfoMessage(playerid,"Prasome islipti is automobilio.");
		return 1;
	}
	SetPlayerCheckpoint(playerid,834.2582,-1958.7120,12.9672,6.0);
	SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten rasite kaledu eventa.");
	return 1;			
}
*/

CMD:padetimoliuga(playerid,params[])
{
	if(GetPVarInt(playerid, "Moliugas") == 0)
		return SendInfoMessage(playerid,"~r~Neturi moliûgo!");
	new housenumber,pname[MAX_PLAYER_NAME];
	housenumber = GetPlayerHouseID(playerid);
	if(GetPlace(playerid) != PLACE_HOUSE)
		return SendInfoMessage(playerid,"Privalote buti namie!");
	GetPlayerName(playerid, pname, 24);
	if ( strcmp(hInfo[housenumber][Name],pname,false) ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");

	new hid = housenumber;
	for(new i;i<MAX_BALDAI;i++)
	{
		if(!BalduSistema[hid][i][b_used])
		{
			if(i > 9)
			{
				ProcessAchievement(playerid,29);
			}
			BalduSistema[hid][i][b_used]=1;
			BalduSistema[hid][i][b_obj]=19320;
			BalduSistema[hid][i][b_cat]=13;
			BalduSistema[hid][i][b_x]=0.0;
			BalduSistema[hid][i][b_y]=0.0;
			BalduSistema[hid][i][b_z]=-1000.0;
			BalduSistema[hid][i][b_rx]=0.0;
			BalduSistema[hid][i][b_ry]=0.0;
			BalduSistema[hid][i][b_rz]=0.0;
			//BalduSistema[hid][i][b_oid]=CreateDynamicObject(BalduSistema[hid][i][b_obj],BalduSistema[hid][i][b_x],BalduSistema[hid][i][b_y],BalduSistema[hid][i][b_z],BalduSistema[hid][i][b_rx],BalduSistema[hid][i][b_ry],BalduSistema[hid][i][b_rz],GetHouseVirtualWorld(hid), _, _, 50.0);
			CreateBaldas(hid,i);
			SendClientMessage(playerid,WHITE," * Pasidëjai moliûgà! Já gali perstatyti paraðæs /baldai -> Dovanos.");
			SaveBaldai(hid);
			ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
			SetPVarInt(playerid,"Moliugas",0);
			return 1;
		}
	}
	SendInfoMessage(playerid,"Nera vietos naujiems baldams!");
	return 1;
}

CMD:padetidovanas(playerid,params[])
	return cmd_padetidovana(playerid,params);
CMD:padetidovana(playerid, params[])
{
	if(GetPlayerHouseID(playerid) == 0)
		return SendInfoMessage(playerid,"Privalote buti namie!");

	//Kaledos(playerid, 3);
	return 1;
}

CMD:kontrabanda(playerid,params[])
{
	if(playerDB[playerid][admin] || playerDB[playerid][specialybe] == 31)
		ShowPlayerDialog(playerid,112,DIALOG_STYLE_LIST,"Darbai","Krauti Narkotikus\nKrauti Ginklus(Blueberry)\nKrauti Ginklus(Angel Pine)\nKrauti Ginklus(Bayside Marina)\nIskrauti","Rinktis","Iseiti");
	return 1;
}

CMD:keybind(playerid,params[])
{
	SendClientMessage(playerid, COLOR, " * Keybind nustatymas (/1 iki /9):");
	SendClientMessage(playerid, -1, " * /1 /varmour");
	SendClientMessage(playerid, -1, " * /2 Labas vakaras.");
	SendClientMessage(playerid, COLOR, " * Nustatæ keybind galite naudoti /1 - /9, kad greitai paraðytumëte komandas ar þinutes.");
	return 1;
}
CMD:1(playerid,params[])
{
	return KeyBind(playerid, 1, params);
}
CMD:2(playerid,params[])
{
	return KeyBind(playerid, 2, params);
}
CMD:3(playerid,params[])
{
	return KeyBind(playerid, 3, params);
}
CMD:4(playerid,params[])
{
	return KeyBind(playerid, 4, params);
}
CMD:5(playerid,params[])
{
	return KeyBind(playerid, 5, params);
}
CMD:6(playerid,params[])
{
	return KeyBind(playerid, 6, params);
}
CMD:7(playerid,params[])
{
	return KeyBind(playerid, 7, params);
}
CMD:8(playerid,params[])
{
	return KeyBind(playerid, 8, params);
}
CMD:9(playerid,params[])
{
	return KeyBind(playerid, 9, params);
}


CMD:atominebomba(playerid,params[])
{
	if(NuclearBlast[NukeInProgress] < 3)
		return 0;

	new progressTrash = floatround((NuclearBlast[TotalObjectsDestroyed]*100.0)/(NuclearBlast[TotalObjectsCreated]));
	new progressBuild = floatround((NuclearBlast[TotalObjectsRecovered]*100.0)/NuclearBlast[TotalObjectsNuked]);
	new totalProgress = (progressTrash + progressBuild)/2;
	new msg[2048];
	format(msg,sizeof(msg),"Los Santos valdþia siunèia nuoðirdþiausià uþuojautà tiems, kurie nukentëjo nuo atominës bombos sprogimo. Mûsû atominë bomba\nbuvo panaudota ne pagal paskirtá, ir visiems parodë savo negailestingà galià..\n\n\n\
		Kaip elgtis susprogus atominei bombai:\n\n\
		• Kiekvienas þaidëjas gali prisidëti prie miesto tvarkymo naudodamas statybininkø automobilius, ásidarbinti nereikia.\n\
	    • Naudoti statybininkø Dumper automobilá ir iðveþti visus griuvësius.\n\
	    • Naudoti statybininkø Cement Truck ir atstatyti sugriuvusius pastatus.\n\
	    • Jei nepasiekiate reikiamo objekto, galite iðlipti ið automobilio ir já paimti.\n\
	    • Jei objektas per aukðtai, kvieskite gaisrinæ/medikus/PD, kad jus uþkeltu su sraigtasparniu. Jûsø darbinë priemonë priemonë privalo iðlikti statybininkø maðina.\n\
	    • Jeigu nepasiekiate checkpointo net su sraigtasparniu (pvz.: jis sienoje), tuomet galite raðyti /admin.\n\
	    • Jei dirbate mechaniku praðome jûsø pataisyti ir papildyti degalø statybininkø automobiliams, nes jie netilps á paprastus á fixus. Laukite þmoniø statybininkø ir ðiukðliaveþiø bazëse.\n\
	    • Laikykites visø eismo taisykliø ir vaþinëkite lëtai. Uþ neatsakingà vairavimà bûsite baudþiami jailu.\n\
	    • Saugotis kelyje ir neuþkliûti uþ radioaktyviø griuvësiø.\n\n\n\n\
	    Los Santos miesto bûsena: {%s}%i%%\n\
	    {FFFFFF}• Iðveþti griuvësiai: {%s}%i%%\n\
	    {FFFFFF}• Atstatyti pastatai: {%s}%i%%\n\n\n\
	    {A9C4E4}Praðome visø Los Santos Gyventojø prisidëti prie miesto tvarkymo ir padëti mums kuo greièiau atsigauti po ðios tragedijos.",gradient(totalProgress,0,100),totalProgress,gradient(progressTrash,0,100),progressTrash,gradient(progressBuild,0,100),progressBuild);
	ShowPlayerDialog(playerid, 13354, DIALOG_STYLE_MSGBOX, "Atominës bombos protokolas", msg, "Gerai",""); //, button2[])
	return 1;
}
/*
CMD:dovanoti(playerid,params[])
	return cmd_dovana(playerid,params);
CMD:dovana(playerid,params[])
{
	new vardux[128];
	if(sscanf(params,"s[24]",vardux)) 
		return SendInfoMessage(playerid,"Padovanoti dovana /dovana [Vardas_Pavarde]");

	new tid = GetPlayeridMid(vardux);

	if(tid==INVALID_PLAYER_ID)
		return SendInfoMessage(playerid,"Tokio vardo nera");
	if(tid == playerid)
		return SendInfoMessage(playerid,"Pats sios dovanos atidaryti negali!");

	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
		return SendInfoMessage(playerid,"Islipk is automobilio!");

	

	new Float:Coo[3];
	GetPlayerPos(tid,Coo[0],Coo[1],Coo[2]);
	
	if(!IsPlayerInRangeOfPointEx(4, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(tid)==PLAYER_STATE_SPECTATING)
		return SendInfoMessage(playerid,"Zaidejas per toli, prieikite arciau.");

	SetPVarInt(playerid,"Dovanoja", tid);
	Kaledos(playerid,4);

	return 1;
}*/
