public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(DEBUG==true) printf("OnDialogResponse: playerid:%i,dialogid:%i,response:%i,inputtext:%s",playerid,dialogid,response,inputtext);
	replaceChar(inputtext, '%', '#');
	#define if(dialogid==%0) case %0:
	if(playerid == -2000) return 1;
	if(dialogid != gPlayerDialog[playerid] && gPlayerDialog[playerid] != -1) dialogid=gPlayerDialog[playerid];
	if(gPlayerDialog[playerid]== -1) return 1;
	gPlayerDialog[playerid]=-1;
	if(response == 1) 	PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0); // Confirmation sound
	else 				PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0); // Cancelation sound
	switch(dialogid)
	{
		if(dialogid==15536)
		{
			if(response)
			{
				Kaledos(playerid, 1);
			}
			return 1;
		}
		if(dialogid==15532)
		{
			if(response)
			{
				Kaledos(playerid, 2);
			}
			return 1;
		}
		/*
		if(dialogid==15533)
		{
			if(response)
			{
				Kaledos(playerid, 2);
			}
		}*/
		if(dialogid==15534)
		{
			if(response)
			{
				ShowSaugykla(playerid);
			}
			else
			{
				SendInfoMessage(playerid,"~g~Viso gero!");
			}
			return 1;
		}
		if(dialogid==15535)
		{
			if(response)
			{
				SaugyklaSelection(playerid,listitem);
			}
			else
			{
				SendInfoMessage(playerid,"~g~Viso gero!");
			}
			return 1;
		}
		if(dialogid==15537)
		{
			if(response)
			{
				MakePurchase(playerid,PURCHASE_CARSLOT);
			}
			else
			{
				ShowSaugykla(playerid);
			}
			return 1;
		}
		if(dialogid==15538)
		{
			if(response)
			{
				PadetiMasina(playerid,DLItemID);
				ShowSaugykla(playerid);
			}
			else
			{
				ShowSaugykla(playerid);
			}
			return 1;
		}
		if(dialogid==15539)
		{
			if(response)
			{
				new CarArray[ahCar];
				if(listitem == 0)
					CarArray = Carlist[playerid];
				else if(listitem == 1)
					CarArray = Carlist2[playerid];
				else if(listitem == 2)
					CarArray = Carlist3[playerid];

				if(CarArray[Carid] == -1)
				{
					SendInfoMessage(playerid,"Sprogusio automobilio padeti negali!");
					ShowSaugykla(playerid);
					return 1;
				}	
				if(TradingWith[playerid] != -1) return SendInfoMessage(playerid, "Uzdaryk mainus");
				new query[128];
				format(query,128,"SELECT * From CarSaugykla WHERE `Vardas` = '%s' AND Id=%i",ReturnName(playerid),GetPVarInt(playerid, "SaugyklosId"));
				mysql_function_query(SQL, query, true, "SQL_GetSaugykla2", "ii",playerid,DLItemID);
			}
			else
			{
				ShowSaugykla(playerid);
			}
			return 1;
		}
		if(dialogid==7444)
		{
			if(response)
			{
				if(listitem == 0)
				{
					if(RocketManager != INVALID_PLAYER_ID)
					{
						SendClientMessage(playerid, COLOR_RED, " * Bombos pozicijà jau nustatinëja kitas þaidëjas.");
						new msg[256];
						format(msg,256,"Nustatyti pozicijà\nNustatyti laikmatá (%i min)\n{ff5733}Paleisti atominæ bombà", RocketDelay);
						ShowPlayerDialog(playerid, 7444, DIALOG_STYLE_LIST, "BOMBOS VALDYMO PUNKTAS", msg, "Gerai","Atsaukti");
						return 1;
					}
					SendClientMessage(playerid, -1, " * Naudokite rodykles nustatyti raketos pozicijà. Nustaèius pozicijà, raðykite /baik");
					RocketSet(playerid,true);
				}
				else if(listitem == 1)
				{
					ShowPlayerDialog(playerid, 7446, DIALOG_STYLE_LIST, "Laikmatis", "Paleisti po 0 minuèiø\nPaleisti po 5 minuèiø\nPaleisti po 10 minuèiø\nPaleisti po 15 minuèiø\nPaleisti po 20 minuèiø\nPaleisti po 25 minuèiø\nPaleisti po 30 minuèiø", "Gerai", "Atgal");
				}
				else if(listitem == 2)
				{
					/*if(rocketries == 0)
					{
						SendClientMessage(playerid, COLOR_RED, " * Buvo iðnaudotas bandymu skaièius. Valdymo pultas atsirakins po 15 minuèiø.");
						return 1;
					}
					new msg[512];
					format(msg,sizeof(msg),"Atominës bombos valdymo punktas.\n{FFFFFF}Áveskite 9-þenklá atominës bombos detonacijos kodà. Suklydus tris kartus valdymo punktas bus uþblokuotas.\nLiko bandymø: {ff5733}%i\n\
						Dëmesio!{FFFFFF} Ávedus teisingà kodà raketos laikmatis bus paleistas ir jo sustabdyti jûs nebegalësite.",rocketries);
					ShowPlayerDialog(playerid, 7445, DIALOG_STYLE_PASSWORD, "Atominës bombos paleidimas", msg, "Gerai","Atgal");*/
					if(!IsNukeThere())
					{
						return SendInfoMessage(playerid, "~r~Bombos nebera!");
					}
					SendClientMessage(playerid, RED, " * Paleidai atominæ bombà. Ðaunuolis...");
					RedeemTyrimas(TyrTypes:LAB_NUKE);
					StartNuke();
				}
			}
			else
			{
				//SendClientMessage(playerid, -1, " * Geros dienos, jûsø Ekselencija.");
				HandleValdymoPunktas(playerid);
			}
		}
		if(dialogid == 7446)
		{
			new msg[256];
			if(response)
			{
				if(listitem > 6) // in case of cheats
					return 1;
				RocketDelay = listitem * 5;
				format(msg,256,"Bombos paleidimas bus atidetas ~g~%i~w~ minuciu po to, kai paleisite bomba.",RocketDelay);
				SendInfoMessage(playerid,msg);
			}
			format(msg,256,"Nustatyti pozicijà\nNustatyti laikmatá (%i min)\n{ff5733}Paleisti atominæ bombà", RocketDelay);
			ShowPlayerDialog(playerid, 7444, DIALOG_STYLE_LIST, "BOMBOS VALDYMO PUNKTAS", msg, "Gerai","Atsaukti");
			return 1;
		}
		if(dialogid == 7445)
		{
			if(!response)
			{
				new msg[256];
				format(msg,256,"Nustatyti pozicijà\nNustatyti laikmatá (%i min)\n{ff5733}Paleisti atominæ bombà", RocketDelay);
				ShowPlayerDialog(playerid, 7444, DIALOG_STYLE_LIST, "BOMBOS VALDYMO PUNKTAS", msg, "Gerai","Atsaukti");
				return 1;
			}
			else
			{
				if(rocketries == 0)
				{
					SendClientMessage(playerid, COLOR_RED, " * Buvo iðnaudotas bandymu skaièius. Valdymo pultas atsirakins po 15 minuèiø.");
					return 1;
				}
				new msg[512];
				if(strlen(inputtext) != 9)
				{
					format(msg,sizeof(msg),"Atominës bombos valdymo punktas.\n{FFFFFF}Áveskite 9-þenklá atominës bombos detonacijos kodà. Suklydus tris kartus valdymo punktas bus uþblokuotas.\nLiko bandymø: {ff5733}%i\n\
							Dëmesio!{FFFFFF} Ávedus teisingà kodà raketos laikmatis bus paleistas ir jo sustabdyti jûs nebegalësite.\n{FF0000}Kodà turi sudaryti 9 simboliai.",rocketries);
					ShowPlayerDialog(playerid, 7445, DIALOG_STYLE_PASSWORD, "Atominës bombos paleidimas", msg, "Gerai","Atgal");
					return 1;
				}
				if(!IsNumeric(inputtext))
				{
					format(msg,sizeof(msg),"Atominës bombos valdymo punktas.\n{FFFFFF}Áveskite 9-þenklá atominës bombos detonacijos kodà. Suklydus tris kartus valdymo punktas bus uþblokuotas.\nLiko bandymø: {ff5733}%i\n\
							Dëmesio!{FFFFFF} Ávedus teisingà kodà raketos laikmatis bus paleistas ir jo sustabdyti jûs nebegalësite.\n{FF0000}Kodà turi sudaryti tik skaièiai.",rocketries);
					ShowPlayerDialog(playerid, 7445, DIALOG_STYLE_PASSWORD, "Atominës bombos paleidimas", msg, "Gerai","Atgal");
					return 1;
				}
				rocketries--;
				if(rocketries == 0)
				{
					SendClientMessage(playerid, COLOR_RED, " * Neteisingas kodas! Buvo iðnaudotas bandymu skaièius, todël valdymo pultas uþrakinamas 15 minuèiø.");
					SetTimer("UnblockRocket", 15 * 60 * 1000, false);
					return 1;
				}
				format(msg,sizeof(msg),"Atominës bombos valdymo punktas.\n{FFFFFF}Áveskite 9-þenklá atominës bombos detonacijos kodà. Suklydus tris kartus valdymo punktas bus uþblokuotas.\nLiko bandymø: {ff5733}%i\n\
						Dëmesio!{FFFFFF} Ávedus teisingà kodà raketos laikmatis bus paleistas ir jo sustabdyti jûs nebegalësite.\n{FF0000}Neteisingas kodas!!!",rocketries);
				ShowPlayerDialog(playerid, 7445, DIALOG_STYLE_PASSWORD, "Atominës bombos paleidimas", msg, "Gerai","Atgal");
				return 1;
			}
		}
		if(dialogid==6900)
		{
			if(GetPlace(playerid) != PLACE_HOUSE)
				return 1;
			if(response)
			{
				SetPVarInt(playerid, "isdoor", listitem);
				SetPVarInt(playerid, "choosingmat", 1);
				SetPVarInt(playerid, "matid", 0);

				SendClientMessage(playerid, ORANGE, " * Sienas gali keisti gali paspaudæs Y ir N klaviðus. Iðsirinkæs spausk ENTER");
				SendClientMessage(playerid, RED, " * Pasirinkta siena arba durys bus paþymëtos raudonai.");
				SendClientMessage(playerid, -1, " * Namø interjerai turi daug skirtingø tekstûrø, ir jûsø name gali nebûti visø 16.");
				Texturize(GetPlayerHouseID(playerid),GetPVarInt(playerid, "isdoor"),GetPVarInt(playerid, "matid"),8932);
			}
		}
		/*if(dialogid==6901)
		{
			if(response)
			{
				SetPVarInt(playerid, "matid", listitem);
				ShowPlayerDialog(playerid,6902,DIALOG_STYLE_LIST,"Pasirinkite veiksmà","Daþyti\nAtstatyti originalià tekstûrà","Gerai","Atsaukti");
			}
			else
			{
				ShowPlayerDialog(playerid,6900,DIALOG_STYLE_LIST,"Daþymas","Durys\nSienos","Gerai","Atsaukti");
			}
		}*/
		if(dialogid==6902)
		{
			if(GetPlace(playerid) != PLACE_HOUSE)
				return 1;
			if(response)
			{
				if(listitem == 0)
				{
					new dazymoid = 1;
					new hid = GetPlayerHouseID(playerid);
					if(!GetPVarInt(playerid, "isdoor"))
					{

						if(hInfo[hid][intobjid][GetPVarInt(playerid, "matid")] > 0) 
						{
							new temp = hInfo[hid][intobjid][GetPVarInt(playerid, "matid")];
							for(new i=1;i<NUM_TEXTURES;i++)
							{
								if(GoodTextures[i] == temp)
								{
									dazymoid = i;
									break;
								}
							}
						}



					}	
					SetPVarInt(playerid, "dazymas", dazymoid);
					Texturize(GetPlayerHouseID(playerid),GetPVarInt(playerid, "isdoor"),GetPVarInt(playerid, "matid"),GoodTextures[dazymoid]);
					SendClientMessage(playerid, ORANGE, " * Daþus keisti gali paspaudæs Y ir N klaviðus. Iðsaugoti gali paspaudæs ENTER");
					SendClientMessage(playerid, ORANGE, " * Jei þinai daþø ID gali ávesti /dazyti [id]");
				}
				else
				{
					new hid = GetPlayerHouseID(playerid);

					if(!GetPVarInt(playerid, "isdoor"))
					{

						if(hInfo[hid][intobjid][GetPVarInt(playerid, "matid")] > 0) 
						{
							hInfo[hid][intobjid][GetPVarInt(playerid, "matid")] = 0;
						}
					}	
					
					SetPVarInt(playerid, "dazymas", 0);
					TogglePlayerControllable(playerid, false);
					ResetTextures(GetPlayerHouseID(playerid),GetPVarInt(playerid, "isdoor"),GetPVarInt(playerid, "matid"), 1);
					//Streamer_Update(playerid);
					SendClientMessage(playerid, ORANGE, " * Atstatei originalià spalvà!");

					if(!playerDB[playerid][ant] && !playerDB[playerid][suristas])
						SetTimerEx("Atfreezint",1000,false,"i",playerid);
					ShowPlayerDialog(playerid,6900,DIALOG_STYLE_LIST,"Daþymas","Sienos\nDurys","Gerai","Atsaukti");

				}
			}
			else
			{
				ResetTextures(GetPlayerHouseID(playerid),GetPVarInt(playerid, "isdoor"),GetPVarInt(playerid, "matid"));
				ShowPlayerDialog(playerid,6900,DIALOG_STYLE_LIST,"Daþymas","Sienos\nDurys","Gerai","Atsaukti");
			}
		}
		if(dialogid==5284)
		{
			if(response)
			{
				if(30 <= dazutime <= 60)
				{
					dazuvotes[listitem]++;
					//new msg[256];
					new votemenu[256];
					format(votemenu,256,#TEXT_GREEN"[DAÞASVYDIS] {FFFFFF}Balsai: ");
					for(new i;i<NUM_ARENOS;i++) 
					{
						format(votemenu,256,"%s%s [%i] | ",votemenu,dazuarenos[i],dazuvotes[i]);
					}	
					SendMessageToDazaiThird(-1,votemenu);
				}
			}
			return 1;
		}
		if(dialogid==15454)
		{
			if(response) 
			{
				SendClientMessage(playerid, -1, " * Sekmingai anuliavai minutes!");
				mysql_query("DELETE FROM Logs WHERE Veiksmas='Praleido'");
				return 1;
			}
		}
		if(dialogid==3433)
		{
			if(response)
			{
				Keliones[Ijungta]=false;
				Keliones[DabartinisCP]=0;
				Keliones[Dalyviai]=0;
				foreach(Player, i) if(KDalyvis[i][Dalyvauja])
				{
					DisablePlayerRaceCheckpoint(i);
					KDalyvis[i][Dalyvauja]=false;
					KDalyvis[i][DabartinisCPs]=0;
					HideCPS(i);
				}
				SendMessageToKlubai(COLOR_WHITE,"[racija] Operatore: Direktorius nutrauke kelione!");
				return 1;
			}
		}
		if(dialogid==30103)
		{
			if(!response)
				LosimuGui(playerid,0);
			else
			{
				VerifyStatymas(playerid,GetPVarInt(playerid,"statymo_id"),inputtext);
			}
		}
		if(dialogid==30104)
		{
			if(!response)
				LosimuGui(playerid,0);
			else
				MakeStatymas(playerid);
		}
		if(dialogid==30100)
		{
			if(!response)
			{
				LosimuGui(playerid,0);
			}
			else
			{
				new suma = strval(inputtext);
				if(!IsNumeric(inputtext))
				{
					return ShowPlayerDialog(playerid, 30100, DIALOG_STYLE_INPUT, "Statymo suma", "Praðome ávesti kokià sumà norite statyti.\nSuma turi bûti bent 100€ ir nedidesnë uþ 100.000€\n{FF0000}Praðome ávesti tik skaièius.", "Gerai","Atðaukti");
				}
				if(suma < 100 || suma > 100000)
				{
					return ShowPlayerDialog(playerid, 30100, DIALOG_STYLE_INPUT, "Statymo suma", "Praðome ávesti kokià sumà norite statyti.\n{FF0000}Suma turi bûti bent 100€ ir nedidesnë uþ 100.000€", "Gerai","Atðaukti");
				}
				if(GetPlayerMoneyA(playerid) < suma)
					return ShowPlayerDialog(playerid, 30100, DIALOG_STYLE_INPUT, "Statymo suma", "Praðome ávesti kokià sumà norite statyti.\nSuma turi bûti bent 100€ ir nedidesnë uþ 100.000€\n{FF0000}Tu neturi tiek pinigu!", "Gerai","Atðaukti");
				SetPVarInt(playerid,"statymo_suma",suma);
				LosimuGui(playerid,0);
			}
		}
		if(dialogid==30101)
		{
			if(response)
			{
				if(listitem == 0)
				{
					return ShowPlayerDialog(playerid, 30100, DIALOG_STYLE_INPUT, "Statymo suma", "Praðome ávesti kokià sumà norite statyti.\nSuma turi bûti bent 100€ ir nedidesnë uþ 100.000€", "Gerai","Atðaukti");
				}
				LosimuGui(playerid,listitem);
			}
		}
		if(dialogid==30102)
		{
			if(!response)
			{
				LosimuGui(playerid,0);
			}
			else
			{
				new statymoid = DLItemID;
				LoadStatymas(playerid,statymoid);
			}
		}
		if(dialogid==10400)
		{
			if(response)
			{
				if(listitem == 0)
				{
					ShowPlayerDialog(playerid, 10401, DIALOG_STYLE_MSGBOX, "Ðaudykla", #TEXT_BLUE"LOS SANTOS ÐAUDYKLOS IÐÐUKIS\n\n\n"#TEXT_WHITE"Kvieèiame sudalyvauti LSG Ðaudykloje ir pagerinti laiko rekordus!\nJûsø uþduotis: suðaudyti visus taikinius per kuo trumpesná laikà.\n\
						"#TEXT_RED"Galite naudoti betkuri ginkla, taciau uþduoties metu jo keisti negalite.\nTurite atsineðti savo ginklà.\n\n"#TEXT_WHITE"Ar norite dalyvauti?","Taip","Ne");
				}
				else
				{
					new query[256];
					format(query,256,"SELECT DISTINCT Ginklas from Saudykla Where Saudykla=%i",GetPVarInt(playerid,"Saudykla"));
					mysql_function_query(SQL, query, true, "SQL_SaudyklosGun", "ii",playerid,GetPVarInt(playerid,"Saudykla"));
				}

			}
		}
		if(dialogid==10401)
		{
			if(response)
				LoadSaudykla(playerid,GetPVarInt(playerid, "Saudykla"));
			else
				ShowPlayerDialog(playerid, 10400, DIALOG_STYLE_LIST, "Ðaudykla", "Dalyvauti\nTOP 10","Gerai","Atsaukti");
			return 1;
		}
		if(dialogid==10402)
		{
			if(response)
			{
				new query[256];
				format(query,256,"SELECT * From Saudykla Where Saudykla=%i AND Ginklas=%i ORDER BY Laikas ASC LIMIT 10",GetPVarInt(playerid,"Saudykla"),DLItemID);
				mysql_function_query(SQL, query, true, "SQL_SaudyklosTOP", "ii",playerid,GetPVarInt(playerid,"Saudykla"));
				return 1;
			}
			else
			{
				ShowPlayerDialog(playerid, 10400, DIALOG_STYLE_LIST, "Ðaudykla", "Dalyvauti\nTOP 10","Gerai","Atsaukti");
				return 1;
			}
		}
		if(dialogid==10403)
		{
			return ShowPlayerDialog(playerid, 10400, DIALOG_STYLE_LIST, "Ðaudykla", "Dalyvauti\nTOP 10","Gerai","Atsaukti");
		}
		if(dialogid==5990)
		{
			if(response)
			{
				if(listitem == 0) // apie event
				{
					ShowPlayerDialog(playerid, 5991, DIALOG_STYLE_MSGBOX, "LSG Gimtadienis", "\n\nSveikiname su 8-uoju LSG Gimtadieniu!!\n\n\
						Ðiemet jums dovanojame atsiminimus is sandeliø gyvenimo! \nAplanke visus sandelius galite susirinkti 5 prizus ir juos pasideti namuose!", "Dalyvauti","Atgal");
				}
				else if(listitem == 1)
				{
					ShowPlayerKiausai(playerid);
				}
				/*else if(listitem == 2)
				{
					GetPresent(playerid);
				}*/

			}
			return 1;
		}
		if(dialogid==5991)
		{
			if(response)
			{
				//SetPlayerCheckpoint(playerid,1315.3837,-898.9023,39.5781,6.0);
				//SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten rasite dazasvydi.");
				return 1;
			}
			else
			{
				//cmd_kiausinis(playerid,"");
				return 1;
			}

		}
		if(dialogid == 15397)
		{
			if(response)
			{
				playerDB[playerid][kepure] = 14 + listitem;
				if(!AttachKepure(playerid,GetPlayerSkin(playerid)))
					return SendInfoMessage(playerid,"Ant sio skino negali detis kaukes!");
				SetPlayerPos(playerid,2117.1992,-1746.1838,13.5547);
				SavePlayerData(playerid,false);
				SendClientMessage(playerid, ORANGE, "[HELOVYNO EVENTAS] Aèiû uþ dalyvavimà! Kaukæ gali pasikeisti kol vyksta eventas.");
				SendClientMessage(playerid, ORANGE, "[HELOVYNO EVENTAS] Kaukë iðsisaugos vietoje kepurës, jà gali nusiimti paraðæs /i");
				return 1;
			}
		}
		if(dialogid==5992)
		{
			if(response)
			{
				PadetiKiausini(playerid,listitem);
			}
			else
			{
				//cmd_kiausinis(playerid,"");
				return 1;
			}
			
		}
		if(dialogid==5993)
		{
			if(response)
			{
				if(listitem == 0)
				{
					new skinid=167;
					SetPlayerSkin(playerid,skinid);
					playerDB[playerid][drabuziai]=skinid;

					SendInfoMessage(playerid,"Sveikiname gavus naujaji skina!");
					new uzrasas[256];
					//SendClientMessage(playerid,RED," * Butinai issaugokite zaidima, antraip dings jusu skinas.");
					format(uzrasas,sizeof(uzrasas),"INSERT INTO `Spinta`(`Vardas`,`Skin`,`LastUsed`) VALUES ('%s',%i,NOW())",ReturnName(playerid),skinid);
					mysql_query(uzrasas);
					ProcessAchievement(playerid,48);
					// set prizas
					format(uzrasas,sizeof(uzrasas),"UPDATE `Easter18` SET `prizas`=1 WHERE Vardas='%s'",ReturnName(playerid));
					mysql_tquery(SQL,uzrasas);
					return 1;
				}
				new caridas = 549;
				new autohaus=random(sizeof(Carspawns2));
				new string[256];
				if(Carlist[playerid][Typ]==-1)
				{
					Carlist[playerid][Typ]=caridas-400; Carlist[playerid][X]=Carspawns2[autohaus][X]; Carlist[playerid][Y]=Carspawns2[autohaus][Y]; Carlist[playerid][Z]=Carspawns2[autohaus][Z]; Carlist[playerid][Rotation]=Carspawns2[autohaus][Rotation];Carlist[playerid][Status]=1; Carlist[playerid][Lock]=0;
					
					Carlist[playerid][Carid]=CreateVehicle(Carlist[playerid][Typ]+400,Carlist[playerid][X],Carlist[playerid][Y],Carlist[playerid][Z],Carlist[playerid][Rotation],-1,-1,-1);
					SetVehicleNumberPlate(Carlist[playerid][Carid],"{FF0000}NERA");
					Carlist[playerid][Lock]=1;
					SetVehicleParamsForAll(Carlist[playerid][Carid],0,1);
					SetVehicleParamsForPlayerEx(Carlist[playerid][Carid],playerid,0,0);
					new vehicleid = Carlist[playerid][Carid];
					format(vehicleDB[vehicleid][nuomuoja],24,"no");
					format(vehicleDB[vehicleid][lastuser],MAX_PLAYER_NAME,"");
					vehicleDB[vehicleid][energy]=50;
					vehicleDB[vehicleid][OldHP]=1000;
					vehicleDB[vehicleid][gas]=50;
					RemovePlayerFromVehicle(playerid);
					SavePlayerData(playerid,true);
					new name[24];
					GetPlayerName(playerid,name,24);
					format(string,128,"Sveikiname! Jus gavote %s dovanu! Tai pirmoji jusu masina!",aVehicleNames[Carlist[playerid][Typ]][Name]);
					printf("%s %s",name,string);
					SendInfoMessage(playerid,string);
					SendClientMessage(playerid, GREEN, "Maðinos komandas rasite paraðæ /masina.");
					SendClientMessage(playerid, HOMER, "Savo automobili rasite paraðæ /kurmasina");
					ProcessAchievement(playerid,3);
				}
				else if(Carlist2[playerid][Typ]==-1)
				{
					Carlist2[playerid][Typ]=caridas-400; Carlist2[playerid][X]=Carspawns2[autohaus][X]; Carlist2[playerid][Y]=Carspawns2[autohaus][Y]; Carlist2[playerid][Z]=Carspawns2[autohaus][Z]; Carlist2[playerid][Rotation]=Carspawns2[autohaus][Rotation];Carlist2[playerid][Status]=1; Carlist2[playerid][Lock]=0;
					
					Carlist2[playerid][Carid]=CreateVehicle(Carlist2[playerid][Typ]+400,Carlist2[playerid][X],Carlist2[playerid][Y],Carlist2[playerid][Z],Carlist2[playerid][Rotation],-1,-1,-1);
					SetVehicleNumberPlate(Carlist2[playerid][Carid],"{FF0000}NERA");
					Carlist2[playerid][Lock]=1;
					SetVehicleParamsForAll(Carlist2[playerid][Carid],0,1);
					SetVehicleParamsForPlayerEx(Carlist2[playerid][Carid],playerid,0,0);

					new vehicleid = Carlist2[playerid][Carid];
					format(vehicleDB[vehicleid][nuomuoja],24,"no");
					format(vehicleDB[vehicleid][lastuser],MAX_PLAYER_NAME,"");
					vehicleDB[vehicleid][energy]=50;
					vehicleDB[vehicleid][OldHP]=1000;
					vehicleDB[vehicleid][gas]=50;
					RemovePlayerFromVehicle(playerid);
					SavePlayerData(playerid,true);
					new name[24];
					GetPlayerName(playerid,name,24);
					format(string,128,"Sveikiname! Jus gavote %s dovanu! Tai antroji jusu masina!",aVehicleNames[Carlist2[playerid][Typ]][Name]);
					printf("%s %s",name,string);
					SendInfoMessage(playerid,string);
					SendClientMessage(playerid, GREEN, "Masinos komandas rasite paraðæ /masina.");
					SendClientMessage(playerid, HOMER, "Savo automobilá rasite paraðæ /kurmasina");
					ProcessAchievement(playerid,3);
				}
				else if(Carlist3[playerid][Typ]==-1)
				{
					Carlist3[playerid][Typ]=caridas-400; Carlist3[playerid][X]=Carspawns2[autohaus][X]; Carlist3[playerid][Y]=Carspawns2[autohaus][Y]; Carlist3[playerid][Z]=Carspawns2[autohaus][Z]; Carlist3[playerid][Rotation]=Carspawns2[autohaus][Rotation];Carlist3[playerid][Status]=1; Carlist3[playerid][Lock]=0;
					
					Carlist3[playerid][Carid]=CreateVehicle(Carlist3[playerid][Typ]+400,Carlist3[playerid][X],Carlist3[playerid][Y],Carlist3[playerid][Z],Carlist3[playerid][Rotation],-1,-1,-1);
					SetVehicleNumberPlate(Carlist3[playerid][Carid],"{FF0000}NERA");
					Carlist3[playerid][Lock]=1;
					SetVehicleParamsForAll(Carlist3[playerid][Carid],0,1);
					SetVehicleParamsForPlayerEx(Carlist3[playerid][Carid],playerid,0,0);

					new vehicleid = Carlist3[playerid][Carid];
					format(vehicleDB[vehicleid][nuomuoja],24,"no");
					format(vehicleDB[vehicleid][lastuser],MAX_PLAYER_NAME,"");
					vehicleDB[vehicleid][energy]=50;
					vehicleDB[vehicleid][OldHP]=1000;
					vehicleDB[vehicleid][gas]=50;
					RemovePlayerFromVehicle(playerid);
					SavePlayerData(playerid,true);
					new name[24];
					GetPlayerName(playerid,name,24);
					format(string,128,"Sveikiname! Jus gavote %s dovanu! Tai trecioji jusu masina!",aVehicleNames[Carlist3[playerid][Typ]][Name]);
					printf("%s %s",name,string);
					SendInfoMessage(playerid,string);
					SendClientMessage(playerid, GREEN, "Masinos komandas rasite paraðæ /masina.");
					SendClientMessage(playerid, HOMER, "Savo automobilá rasite paraðæ /kurmasina");
					ProcessAchievement(playerid,3);
				}
				else
					return SendClientMessage(playerid,-1,"Tu jau turi tris automobilius!");
				// set prizas
				new uzrasas[256];
				format(uzrasas,sizeof(uzrasas),"UPDATE `Easter18` SET `prizas`=2 WHERE Vardas='%s'",ReturnName(playerid));
				mysql_tquery(SQL,uzrasas);
			}
			else
			{
				//cmd_kiausinis(playerid,"");
			}
			return 1;
		}
		if(dialogid==17000)
		{
			if(response)
			{
				if(listitem == 0)
				{
					Uzsakymai[playerid][utype] = 0;
					Uzsakymai[playerid][uforid] = 0;
					Uzsakymai[playerid][uamount] = 0;
					new businesses = 0;
					new pname[MAX_PLAYER_NAME],msg[4048];
					GetPlayerName(playerid,pname,MAX_PLAYER_NAME);
					foreach(Businesses,i) if(BusinessInfo[i][bOwned] && 0==strcmp(BusinessInfo[i][bOwner],pname,false))
					{
						format(msg,sizeof(msg),"{FFFFFF}%s(%s) [pelnas {008000}%i{FFFFFF}€]",BusinessInfo[i][bName],GetBussinessType(BusinessInfo[i][bType]),BusinessInfo[i][bEarning]);
						AddDListItem(playerid, msg, i);
						businesses++;
					}
					if(!businesses)
						return SendInfoMessage(playerid, "~r~Jus neturite nei vieno verslo!");
					ShowPlayerDList(playerid, 17002, "Pasirinkite versla", "Rinktis", "Atsaukti");
				}
				if(playerDB[playerid][specialybe] == 60 && listitem == 1)
					ShowUzsakymai(playerid,0);
			}
			return 1;
		}
		if(dialogid==17002)
		{
			if(response)
			{
				new bizid = DLItemID;
				Uzsakymai[playerid][uforid] = bizid;
				new pinigu = BusinessInfo[bizid][bEarning];
				if(pinigu < 2000) {
					if(playerDB[playerid][specialybe] == 60)
					{
						ShowPlayerDialog(playerid,17000,DIALOG_STYLE_LIST,"Inkasatoriai","Padaryti uþsakymà\nPriimti uþsakymà","Gerai","Atsaukti");
					}
					else
					{
						ShowPlayerDialog(playerid,17000,DIALOG_STYLE_LIST,"Inkasatoriai","Padaryti uþsakymà","Gerai","Atsaukti");
					}
					return SendInfoMessage(playerid,"~r~Uzsakymus priimame tik nuo 2000 EUR");
				}
				new const saibos[] = {2000,3000,4000,5000,6000,7000,8000,9000,10000,15000,20000,50000,100000};
				new sumos[1024];
				new cur = 0;
				while(cur < sizeof(saibos) && saibos[cur] <= pinigu)
				{
					format(sumos,1024,"%s%s{008000}%i{FFFFFF}€\n",sumos,((cur == 0)?(""):("\n")),saibos[cur]);
					cur++;
				}
				ShowPlayerDialog(playerid, 17003, DIALOG_STYLE_LIST, "Pasirinkite pinigu suma", sumos, "Gerai", "Atsaukti");
			}
			return 1;
		}
		if(dialogid==17003)
		{
			if(response)
			{
				new bizid =	Uzsakymai[playerid][uforid];
				new const saibos[] = {2000,3000,4000,5000,6000,7000,8000,9000,10000,15000,20000,50000,100000,200000,500000};
				if(listitem >= sizeof(saibos) || saibos[listitem] > BusinessInfo[bizid][bEarning])
					return SendInfoMessage(playerid,"~r~Tiek pelno nera!");
				Uzsakymai[playerid][uamount]=saibos[listitem];
				NewUzsakymas(playerid,Uzsakymai[playerid][utype],Uzsakymai[playerid][uforid],Uzsakymai[playerid][uamount]);
			}
			return 1;
		}
		if(dialogid==17001)
		{
			if(response)
			{
				if(playerDB[playerid][specialybe] == 60)
				{
					StartUzsakymas(playerid,listitem/2); // 0,1 /2 = 0, 2,3 / 2 = 1, ....
				}
			}
			else
			{
				if(playerDB[playerid][specialybe] == 60)
				{
					ShowPlayerDialog(playerid,17000,DIALOG_STYLE_LIST,"Inkasatoriai","Padaryti uþsakymà\nPriimti uþsakymà","Gerai","Atsaukti");
				}
				else
				{
					ShowPlayerDialog(playerid,17000,DIALOG_STYLE_LIST,"Inkasatoriai","Padaryti uþsakymà","Gerai","Atsaukti");
				}
			}
			return 1;
		}
		if(dialogid==6557)
		{
			if(response)
			{
			
				if(listitem==0) // pakeisti komanda
				{
					new red,blue;
					foreach(Player, i)
					{
						if(playerDB[i][psratasvydis]==2) red++;
						else if(playerDB[i][psratasvydis]==1) blue++;	
					}
					if(playerDB[playerid][psratasvydis] == 1)
					{
						if(red > blue)
							return SendClientMessage(playerid,YELLOW," * Ðiuo metu negalite pakeisti komandos, nes jûsø komandoje per maþai þmoniø.");
						else
							playerDB[playerid][psratasvydis]=2;
					}
					else if(playerDB[playerid][psratasvydis] == 2)
					{
						if(blue > red)
							return SendClientMessage(playerid,YELLOW," * Ðiuo metu negalite pakeisti komandos, nes jûsø komandoje per maþai þmoniø.");
						else
							playerDB[playerid][psratasvydis]=1;
					}
					for(new y=0;y<5;y++)
						TextDrawHideForPlayer(playerid,dazugui[y]);
					Sratasvydziosetup(playerid);
				}
				else if(listitem == 1)
				{
					return cmd_ginklai(playerid,"");
				}
				else if(listitem == 2)
				{
					for(new y=0;y<5;y++)
							TextDrawHideForPlayer(playerid,dazugui[y]);
					SetPlayerPoz(playerid,-978.7211,1052.6761,1344.9857);
					SetCameraBehindPlayer(playerid);
					SetPlayerVirtualWorld(playerid,0);
					//ResetPlayerWeapons(playerid);
					ResetGunData(playerid);
					playerDB[playerid][psratasvydis]=0;
					SetPlayerTeam(playerid,NO_TEAM);
					for(new slot=0; slot<12; slot++) if(playerDB[playerid][spdata][slot])
						GivePlayerWeaponEx(playerid,playerDB[playerid][spdata][slot],playerDB[playerid][spdata][12+slot]);
					SetPlayerHealth(playerid,playerDB[playerid][shealth][0]);
					SetPlayerArmour(playerid,playerDB[playerid][shealth][1]);
					SetPlayerWantedLevel(playerid,playerDB[playerid][spdata][25]);
					SetPlayerSkin(playerid,playerDB[playerid][spdata][24]);
					//Stop(playerid);
					SendInfoMessage(playerid,"Lauksime sugriztant!");
					SetPlayerInterior(playerid,10);
					for(new i; i< 20; i++)
					{
						SendDeathMessage(6000,5005, 255);
					}
				}
			}
			return 1;
		}
		if(dialogid==1555)
		{
			if(!playerDB[playerid][ant] && !playerDB[playerid][suristas])
				TogglePlayerControllable(playerid,true);
			if(response)
			{
				if(GetPlayerMoneyA(playerid) < 1000)
				{
					SendInfoMessage(playerid,"~r~Neturi tiek pinigu!");
					SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE);
					new Float:coo[3];
					GetPlayerPos(playerid,coo[0],coo[1],coo[2]);
					SetPlayerPos(playerid,coo[0]+2.0,coo[1],coo[2]);
					ClearAnimations(playerid);
					DestroyBalloon(fs_balloon_pl[playerid][1]);
					SpawnBalloon(fs_balloon_pl[playerid][1]);
					fs_balloon_pl[playerid][0]=0;
					Iter_Remove(PlayersFading,playerid);
					/*FPS[playerid] = false;// You can use 0 if you don't want to false. 
					StopFPS(playerid);//Called Stock StopFPS 
					SendInfoMessage(playerid,"~r~Isjungei FPS mod.");*/

					return 1;
				}
				GivePlayerMoneyA(playerid,-1000);
				SendClientMessage(playerid,-1," * Smagaus skraidymo!");

				//GivePlayerWeaponEx(playerid,46,1);
				//SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USEJETPACK);
				ApplyAnimation(playerid, "ped", "DRIVE_BOAT", 4.0, 1, 0, 0, 0, 0);
				SetTimerEx("NuomaBaliono",60*60*1000,0,"ii",playerid,fs_balloon_pl[playerid][1]);
				return 1;
			}
			else
			{
				/*FPS[playerid] = false;// You can use 0 if you don't want to false. 
				StopFPS(playerid);//Called Stock StopFPS 
				SendInfoMessage(playerid,"~r~Isjungei FPS mod.");*/
				SetPlayerSpecialAction(playerid,SPECIAL_ACTION_NONE);
				ClearAnimations(playerid);
				fs_balloon_pl[playerid][0]=0;
				new Float:coo[3];
				GetPlayerPos(playerid,coo[0],coo[1],coo[2]);
				SetPlayerPos(playerid,coo[0]+2.0,coo[1],coo[2]);
				DestroyBalloon(fs_balloon_pl[playerid][1]);
				SpawnBalloon(fs_balloon_pl[playerid][1]);
				Iter_Remove(PlayersFading,playerid);
				return 1;
			}
		}
		/*if(dialogid==4646)
		{
			new Float:pos[3];
			GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
			if(pos[1] < -1301.4 && pos[1] > -1303.2417 && pos[0] < 1786.2131 && pos[0] > 1784.1555) ShowElevatorDialog(playerid);
			else if(pos[1] > -1301.4 && pos[1] < -1299.1447 && pos[0] < 1785.6147 && pos[0] > 1781.9902)
			{
				// He is most likely using it, check floor:
				new i=20;
				while(pos[2] < GetDoorsZCoordForFloor(i) + 3.5 && i > 0)
					i --;

				if(i == 0 && pos[2] < GetDoorsZCoordForFloor(0) + 2.0)
					i = -1;

				if(i <= 19)
				{
					if(response)
					{
						CallElevator(playerid, i + 1);
						GameTextForPlayer(playerid, "~r~Liftas iskviestas", 3500, 4);
					}
					return 1;
				}
			}
		}*/
		if(dialogid==2525)
		{
			new const cars[3] =
			{
				555,
				559,
				549
			};
			new autohaus=random(sizeof(Carspawns2));
			new string[256];
			if(Carlist[playerid][Typ]==-1)
			{
				Carlist[playerid][Typ]=cars[listitem]-400; Carlist[playerid][X]=Carspawns2[autohaus][X]; Carlist[playerid][Y]=Carspawns2[autohaus][Y]; Carlist[playerid][Z]=Carspawns2[autohaus][Z]; Carlist[playerid][Rotation]=Carspawns2[autohaus][Rotation];Carlist[playerid][Status]=1; Carlist[playerid][Lock]=0;
				
				Carlist[playerid][Carid]=CreateVehicle(Carlist[playerid][Typ]+400,Carlist[playerid][X],Carlist[playerid][Y],Carlist[playerid][Z],Carlist[playerid][Rotation],-1,-1,-1);
				SetVehicleNumberPlate(Carlist[playerid][Carid],"{FF0000}NERA");
				Carlist[playerid][Lock]=1;
				SetVehicleParamsForAll(Carlist[playerid][Carid],0,1);
				SetVehicleParamsForPlayerEx(Carlist[playerid][Carid],playerid,0,0);
				new vehicleid = Carlist[playerid][Carid];
				format(vehicleDB[vehicleid][nuomuoja],24,"no");
				format(vehicleDB[vehicleid][lastuser],MAX_PLAYER_NAME,"");
				vehicleDB[vehicleid][energy]=50;
				vehicleDB[vehicleid][OldHP]=1000;
				vehicleDB[vehicleid][gas]=50;
				RemovePlayerFromVehicle(playerid);
				SavePlayerData(playerid,true);
				new name[24];
				GetPlayerName(playerid,name,24);
				format(string,128,"Sveikiname! Jus gavote %s dovanu! Tai pirmoji jusu masina!",aVehicleNames[Carlist[playerid][Typ]][Name]);
				printf("%s %s",name,string);
				SendInfoMessage(playerid,string);
				SendClientMessage(playerid, GREEN, "Maðinos komandas rasite paraðæ /masina.");
				SendClientMessage(playerid, HOMER, "Savo automobili rasite paraðæ /kurmasina");
				ProcessAchievement(playerid,3);
				return 1;
			}
			else if(Carlist2[playerid][Typ]==-1)
			{
				Carlist2[playerid][Typ]=cars[listitem]-400; Carlist2[playerid][X]=Carspawns2[autohaus][X]; Carlist2[playerid][Y]=Carspawns2[autohaus][Y]; Carlist2[playerid][Z]=Carspawns2[autohaus][Z]; Carlist2[playerid][Rotation]=Carspawns2[autohaus][Rotation];Carlist2[playerid][Status]=1; Carlist2[playerid][Lock]=0;
				
				Carlist2[playerid][Carid]=CreateVehicle(Carlist2[playerid][Typ]+400,Carlist2[playerid][X],Carlist2[playerid][Y],Carlist2[playerid][Z],Carlist2[playerid][Rotation],-1,-1,-1);
				SetVehicleNumberPlate(Carlist2[playerid][Carid],"{FF0000}NERA");
				Carlist2[playerid][Lock]=1;
				SetVehicleParamsForAll(Carlist2[playerid][Carid],0,1);
				SetVehicleParamsForPlayerEx(Carlist2[playerid][Carid],playerid,0,0);

				new vehicleid = Carlist2[playerid][Carid];
				format(vehicleDB[vehicleid][nuomuoja],24,"no");
				format(vehicleDB[vehicleid][lastuser],MAX_PLAYER_NAME,"");
				vehicleDB[vehicleid][energy]=50;
				vehicleDB[vehicleid][OldHP]=1000;
				vehicleDB[vehicleid][gas]=50;
				RemovePlayerFromVehicle(playerid);
				SavePlayerData(playerid,true);
				new name[24];
				GetPlayerName(playerid,name,24);
				format(string,128,"Sveikiname! Jus gavote %s dovanu! Tai antroji jusu masina!",aVehicleNames[Carlist2[playerid][Typ]][Name]);
				printf("%s %s",name,string);
				SendInfoMessage(playerid,string);
				SendClientMessage(playerid, GREEN, "Masinos komandas rasite paraðæ /masina.");
				SendClientMessage(playerid, HOMER, "Savo automobilá rasite paraðæ /kurmasina");
				ProcessAchievement(playerid,3);
			}
			else if(Carlist3[playerid][Typ]==-1)
			{
				Carlist3[playerid][Typ]=cars[listitem]-400; Carlist3[playerid][X]=Carspawns2[autohaus][X]; Carlist3[playerid][Y]=Carspawns2[autohaus][Y]; Carlist3[playerid][Z]=Carspawns2[autohaus][Z]; Carlist3[playerid][Rotation]=Carspawns2[autohaus][Rotation];Carlist3[playerid][Status]=1; Carlist3[playerid][Lock]=0;
				
				Carlist3[playerid][Carid]=CreateVehicle(Carlist3[playerid][Typ]+400,Carlist3[playerid][X],Carlist3[playerid][Y],Carlist3[playerid][Z],Carlist3[playerid][Rotation],-1,-1,-1);
				SetVehicleNumberPlate(Carlist3[playerid][Carid],"{FF0000}NERA");
				Carlist3[playerid][Lock]=1;
				SetVehicleParamsForAll(Carlist3[playerid][Carid],0,1);
				SetVehicleParamsForPlayerEx(Carlist3[playerid][Carid],playerid,0,0);

				new vehicleid = Carlist3[playerid][Carid];
				format(vehicleDB[vehicleid][nuomuoja],24,"no");
				format(vehicleDB[vehicleid][lastuser],MAX_PLAYER_NAME,"");
				vehicleDB[vehicleid][energy]=50;
				vehicleDB[vehicleid][OldHP]=1000;
				vehicleDB[vehicleid][gas]=50;
				RemovePlayerFromVehicle(playerid);
				SavePlayerData(playerid,true);
				new name[24];
				GetPlayerName(playerid,name,24);
				format(string,128,"Sveikiname! Jus gavote %s dovanu! Tai pirmoji jusu masina!",aVehicleNames[Carlist3[playerid][Typ]][Name]);
				printf("%s %s",name,string);
				SendInfoMessage(playerid,string);
				SendClientMessage(playerid, GREEN, "Masinos komandas rasite paraðæ /masina.");
				SendClientMessage(playerid, HOMER, "Savo automobilá rasite paraðæ /kurmasina");
				ProcessAchievement(playerid,3);
			}
			else
				return SendClientMessage(playerid,-1,"Tu jau turi tris automobilius!");
		}
		if(dialogid==1493)
		{	
			if(!response)
				return 1;
			new msgz[1024];
			new const Texts[][] =
			{
				"There are no easter eggs up here",
				"This one's for Jesus",
				"I might need a bike for this one",
				"Aesthetic egg",
				"Didn't think eggs float on water",
				"Nuclear egg launch in 3...2...",
				"I'll have to dig deep for this one",
				"Hopefully trains don't go at this hour",
				"Mount Everest egg",
				"Los Santos Eye",
				"They sell eggs here?!",
				"Dunkin' eggs"
			};
			for(new i;i<12;i++)
			{
				if(EggFound[playerid][i])
					format(msgz,sizeof(msgz),"%s{5079ff}%i. %s\n",msgz,i+1,Texts[i]);
				else
					format(msgz,sizeof(msgz),"%s{ffffff}%i. %s\n",msgz,i+1,Texts[i]);
			}
			ShowPlayerDialog(playerid,1494,DIALOG_STYLE_LIST,"Uzuomenos",msgz,"Gerai","");
			return 1;
		}
		if(dialogid==4780)
		{
			SratsvydzioGuns[playerid][0]=22+listitem;
			ShowPlayerDialog(playerid,4781,DIALOG_STYLE_LIST,"Pasirinkite pagrindini ginkla:","MP5\nAk-47\nM4\nTec-9","Gerai","");
		}
		if(dialogid==4781)
		{
			SratsvydzioGuns[playerid][1]=29+listitem;
			ShowPlayerDialog(playerid,4782,DIALOG_STYLE_LIST,"Pasirinkite snaiperi:","Country Rifle\nSniper Rifle","Gerai","");
		}
		if(dialogid==4782)
		{
			SratsvydzioGuns[playerid][2]=33+listitem;
			ResetGunData(playerid);
			GivePlayerWeaponEx(playerid,SratsvydzioGuns[playerid][0],100000); // dgl-sg
			GivePlayerWeaponEx(playerid,SratsvydzioGuns[playerid][1],100000); // mp5-ak47
			GivePlayerWeaponEx(playerid,SratsvydzioGuns[playerid][2],100000); // rifle-awp
		}
		if(dialogid==4522)
		{
			if(response)
			{
				if(GetPlayerMoneyA(playerid) < 10000) return SendInfoMessage(playerid,"Neturite pakankamai pinigu!");
				
				new file[128], vardasx[24]; // Susikuriam string kintamuosius.
				GetPlayerName(playerid, vardasx, 24); // Gaunam zaidejo varda.
				
				format(file,128,"UPDATE `Account` SET `PLigonine`= 15 WHERE `Name` = '%s'",vardasx);
				mysql_query(file);
				GivePlayerMoneyA(playerid,-10000);
				playerDB[playerid][pligonis]=15;
				SendInfoMessage(playerid,"Sekmingai nusipirkote privacios ligonines abonimenta!");
			}
		}
		if(dialogid==4578)
		{
			if(!response) // nta edit
			{
				if(playerDB[playerid][specialybe] != 34 && !playerDB[playerid][admin]) return 1;
				new hid=-1;
				for(new i; i < MAX_HOUSES; i++)
				{
					if(fsHouses[i][fobjid] != 0)
					{
						if(IsPlayerInRangeOfPointEx(5, playerid, fsHouses[i][fspos][0],fsHouses[i][fspos][1],fsHouses[i][fspos][2]))
						{
							hid=i;
							break;
						}
					}
				}
				if(hid==-1) return 1;
				new ownerid = INVALID_PLAYER_ID;
				foreach(Player, i)
				{
					if (strcmp(hInfo[hid][Name],ReturnName(i),false) == 0) ownerid=i;
				}
				if(ownerid == INVALID_PLAYER_ID && !playerDB[playerid][admin] && playerDB[playerid][plead] != 34) return SendClientMessage(playerid,-1," * Ðis namas neturi savininko arba jis neprisijunges!");
				new Float:Coo[3];
				GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
				if(!IsPlayerInRangeOfPointEx(20, ownerid, Coo[0],Coo[1],Coo[2]) && !playerDB[playerid][admin] && playerDB[playerid][plead] != 34) return SendClientMessage(playerid,-1," * Namo savininkas turi stovëti arèiau jûsø!");
				
				ShowPlayerDialog(playerid,4579,DIALOG_STYLE_LIST,"NTA edit","Iðtrinti þenklà\nPakeisti kaina","Gerai","Atðaukti");
				
			}
		}
		if(dialogid==4579)
		{
			if(response)
			{
				new hid=-1;
				for(new i; i < MAX_HOUSES; i++)
				{
					if(fsHouses[i][fobjid] != 0)
					{
						if(IsPlayerInRangeOfPointEx(5, playerid, fsHouses[i][fspos][0],fsHouses[i][fspos][1],fsHouses[i][fspos][2]))
						{
							hid=i;
							break;
						}
					}
				}
				if(hid==-1) return 1;
				if(listitem==0)
				{
					DestroyDynamicObject(fsHouses[hid][fobjid]); fsHouses[hid][fobjid]=0;
					DestroyDynamic3DTextLabel(fsHouses[hid][ftextid]);
					fsHouses[hid][fcost]=0;
					SendClientMessage(playerid, -1, " * Iðemei ðá þenkla!");
					new msg[128];
					format(msg,sizeof(msg),"DELETE From HouseSale Where houseid=%i",hid);
					mysql_query(msg);
				}
				else
				{
					ShowPlayerDialog(playerid,4580,DIALOG_STYLE_INPUT,"Kaina","Iveskite nauja pardavimo kaina:","Gerai","Atsaukti");
					
				}
			}
			return 1;
		}
		if(dialogid==4580)
		{
			if(response)
			{
				new hid=-1;
				for(new i; i < MAX_HOUSES; i++)
				{
					if(fsHouses[i][fobjid] != 0)
					{
						if(IsPlayerInRangeOfPointEx(5, playerid, fsHouses[i][fspos][0],fsHouses[i][fspos][1],fsHouses[i][fspos][2]))
						{
							hid=i;
							break;
						}
					}
				}
				if(hid==-1) return 1;
				if(!IsNumeric(inputtext)) return SendInfoMessage(playerid,"Skaiciais!");
				new amount = strval(inputtext);
				if(amount < 0) return SendInfoMessage(playerid,"Skaiciais!");
				fsHouses[hid][fcost]=amount;
				SendClientMessage(playerid, -1, " * Pakeitei kainà!");
				DestroyDynamic3DTextLabel(fsHouses[hid][ftextid]);
				new tmp[128];
				format(tmp,128,"Kaina: {33CC00}%s{FFFFFF} €\nDaugiau informacijos - spauskite {33CC00}'~k~~GROUP_CONTROL_BWD~'",FormatNumber(fsHouses[hid][fcost]));
				fsHouses[hid][ftextid] = CreateDynamic3DTextLabel( tmp, 0xFFFFFFFF,fsHouses[hid][fspos][0],fsHouses[hid][fspos][1],fsHouses[hid][fspos][2]+1.0,5.0 );
				new msg[128];
				format(msg,sizeof(msg),"Update HouseSale Set price=%i Where houseid=%i",amount,hid);
				mysql_query(msg);
				
			}
		}
		if(dialogid==4523)
		{
			if(response)
			{
				if(listitem == 0)
				{
					new row[128];
					format(row,sizeof(row),"SELECT Item,Count From Bagazine Where Vardas='%s' AND Masina=4",ReturnName(playerid));
					mysql_function_query(SQL, row, true, "SQL_Bagazas", "ii",playerid,4);
					return 1;					
				}
				else if(listitem == 1)
				{
					if(playerDB[playerid][pgang]==-1) return SendInfoMessage(playerid,"~n~Nepriklausote jokiai gaujai!");
					else
					{
						return ShowPlayerDialog(playerid, 5256, DIALOG_STYLE_LIST, "Skinai","Pirmas(Vyr.)\nAntras(Vyr.)\nTrecias(Vyr.)\nKetvirtas(Mot.)","Taip","Ne");
					}
				}
			
			
			}
		}
		if(dialogid==7842)
		{
			if(!response)
			{
				if(playerDB[playerid][baikeruzd]!= -1)
				{
					if(GetTickCount() - LastPjovimas[playerid] > 5*60*1000)
					{
						SendClientMessage(playerid,COLOR," * Nenori pinigø - nereik. Gali eit deðrainius pardavinët :)");
						playerDB[playerid][baikeruzd]=-1;
					}
				}
			}
			return 1;
		}
		if(dialogid==565)
		{
			if(response)
			{
				new red,blue;
				foreach(Player, i)
				{
					if(playerDB[i][psratasvydis]==2) red++;
					else if(playerDB[i][psratasvydis]==1) blue++;	
				}
				if(listitem == 4) // red
				{
					if(red > blue)
					{
						SendInfoMessage(playerid,"Sioje komandoje per daug zmoniu!");
						DazuLentele(playerid);
						return 1;
					}
					playerDB[playerid][psratasvydis]=2;
				}
				else if(listitem == 5) // blue
				{
					if(blue > red)
					{
						SendInfoMessage(playerid,"Sioje komandoje per daug zmoniu!");
						DazuLentele(playerid);
						return 1;
					}
					playerDB[playerid][psratasvydis]=1;

				}
				else
				{
					DazuLentele(playerid);
					return 1;
				}
				PTotal[playerid] = 0;
				//SendClientMessage(playerid, -1, " * Daþasvydyje bendrauti galite naudodami "#TEXT_GREEN"/dazai");
				UpdateGunData(playerid);
				for(new slot=0; slot<12; slot++)
				{
					playerDB[playerid][spdata][slot] = GunData[playerid][slot][0];
					playerDB[playerid][spdata][12+slot] = GunData[playerid][slot][1];
				}
				playerDB[playerid][spdata][24]=GetPlayerSkin(playerid);
				SratsvydzioGuns[playerid][0]=0;
				SratsvydzioGuns[playerid][1]=0;
				SratsvydzioGuns[playerid][2]=0;
				playerDB[playerid][spdata][25]=GetPlayerWantedLevel(playerid);
				GetPlayerHealth(playerid,playerDB[playerid][shealth][0]);
				GetPlayerArmour(playerid,playerDB[playerid][shealth][1]);
				//GivePlayerMoneyA(playerid, -500);

				Sratasvydziosetup(playerid);
				return 1;
			}
		}
		if(dialogid==3995)
		{
			if(response)
			{
				new str[50],pname[24],housenumber;

				housenumber = GetHouseID(playerid);
				GetPlayerName(playerid, pname, 24);
				if(housenumber < 0) return SendInfoMessage(playerid,"Jus neesate prie namo!");
				if(TradingWith[playerid] != -1) return SendInfoMessage(playerid,"Uzdaryk mainus!");
				if (strcmp(hInfo[housenumber][Name],pname,false)) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
				SendInfoMessage(playerid,"Jus pardavete savo nama!");
				format(str, sizeof(str), "%s pardave houseid %i",pname,housenumber);
				print(str);
				GivePlayerMoneyA(playerid, (hInfo[housenumber][Cost] /4));
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `Name`='Nera',`Zole`=0,`Locked`=1,`Nark`=0,`Pinigai`=0,`Renter`='ForRent' WHERE `ID`=%i",housenumber);
				mysql_query(query);

				playerDB[playerid][namu]--;
				hInfo[housenumber][Locked] = 1;
				hInfo[housenumber][zole] = 0;
				hInfo[housenumber][nark] = 0;
				hInfo[housenumber][pinigai] = 0;
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
				format(hInfo[housenumber][Name],255,"Nera");
				hInfo[housenumber][Rentable] = 0;
				hInfo[housenumber][Rentcost] = 0;
				hInfo[housenumber][hMokesciai] = 14;
				format(hInfo[housenumber][Renter], 24, "ForRent");
				DestroyPickup(HousePickup[housenumber]);
				new vw;
				if(hInfo[housenumber][daugiabutis]) vw=(MAX_HOUSES*2+MAX_BUSINESSES+hInfo[housenumber][daugiabutis]-1);
				HousePickup[housenumber] = CreatePickupA(1273, 23, hInfo[housenumber][iconx], hInfo[housenumber][icony], hInfo[housenumber][iconz],vw);
				new zinute[512];
				DestroyDynamic3DTextLabel(HouseText[housenumber]);
				format(zinute,sizeof(zinute),"Namas Nr.: {FF0000}%i",housenumber);
				HouseText[housenumber] = CreateDynamic3DTextLabel(zinute, COLOR_WHITE, hInfo[housenumber][iconx], hInfo[housenumber][icony], hInfo[housenumber][iconz], 50, _,_, 1,vw);
				new querfr[240];
				format(querfr,sizeof(querfr),"UPDATE `Namai` SET `bMokesciai`=%i WHERE ID=%i",hInfo[housenumber][hMokesciai],housenumber);
				mysql_query(querfr); 
				return 1;
			}
		}
		if(dialogid==7801)
		{
			if(response)
			{
				new query[512];
				format(query,sizeof(query),"SELECT * From `gangcars` WHERE `gang`=%i LIMIT %i,1",playerDB[playerid][pgang],listitem);
				mysql_function_query(SQL,query,true,"SQL_ChosenCar","iii",playerid,playerDB[playerid][pgang],listitem);
			}
			else
			{
				return ShowGangDialog(playerid);
			}
		}
		if(dialogid==6385)
		{
			if(response)
			{
				if(listitem == 100)
				{
					ShowAchievements(playerid,-1,1);
				}
				else
				{
					new page = GetPVarInt(playerid, "PageId");
					new idas = 100 * page + listitem;
					new query[256];
					format(query,sizeof(query),"SELECT * From AchInfo Where id=%i LIMIT 1",idas);
					mysql_function_query(SQL, query, true, "SQL_ShowAchInfo", "ii", playerid,idas);
				}
			}
		}
		if(dialogid==6387)
		{
			if(response)
			{
				if(listitem == 100)
				{
					new player = GetPVarInt(playerid, "AchForPlayer");
					ShowAchievements(player,playerid,1);
				}
			}
		}
		if(dialogid==6386)
		{
			ShowAchievements(playerid);
		}
		if(dialogid==5604)
		{
			if(response)
			{
				new job=PlayerLastJob[playerid][0];
				for(new i;i<MAX_DARBINES_CAR;i++)
				{
					DarbinesCar[job][i][DCevent]=1;
				}
				SetTimerEx("StopEvent",30*60*1000,false,"i",job);
			}
		}
		if(dialogid==5600)
		{
			if(response)
			{
				new job=PlayerLastJob[playerid][0];
				new car=PlayerLastJob[playerid][1];
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
				vehicleDB[PlayerCar[playerid]][gas]=40.0;
				vehicleDB[PlayerCar[playerid]][energy]=50.0;
				vehicleDB[PlayerCar[playerid]][OldHP]=1000.0;
				FadeColorForPlayer(playerid,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,10,5);
				TogglePlayerControllable(playerid,false);
				Stop(playerid);
				SendClientMessage(playerid,GREEN," * Gavote darbiná automobilá.");
			}
		}
		if(dialogid==5605)
		{
			if(response)
			{
				if(GetPlayerMoneyA(playerid) < COST_DCEVENT)
					return SendInfoMessage(playerid,"Neuztenka pinigu!");
				GivePlayerMoney(playerid,-COST_DCEVENT);
				new job=PlayerLastJob[playerid][0];
				new car=PlayerLastJob[playerid][1];
				DestroyOldCar(playerid);
				_PlayerTeleporting[playerid]=6;
				PlayerCar[playerid] = CreateVehicle(DarbinesCar[job][car][DCmodel],0.0,0.0,0.0,DarbinesCar[job][car][DCR],DarbinesCar[job][car][DCcolor1],DarbinesCar[job][car][DCcolor2],-1,DarbinesCar[job][car][DCsirens]);
				OnVehicleSpawn(PlayerCar[playerid]);
				SetVehicleToRespawn(PlayerCar[playerid]);
				vehicleDB[PlayerCar[playerid]][gas]=40.0;
				vehicleDB[PlayerCar[playerid]][energy]=50.0;
				vehicleDB[PlayerCar[playerid]][OldHP]=1000.0;
				FadeColorForPlayer(playerid,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,10,5);
				TogglePlayerControllable(playerid,false);
				Stop(playerid);
				SendClientMessage(playerid,GREEN," * Gavote event automobilá.");
			}
		}
		if(dialogid==5601)
		{
			if(response)
			{
				DestroyOldCar(playerid);
				new job = PlayerLastJob[playerid][0];
				new car = PlayerLastJob[playerid][1];
//				new msg[128];
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
				if(GetPlayerMoneyA(playerid) < cost)
					return SendInfoMessage(playerid,"Neturi tiek pinigu!");
				GivePlayerMoneyA(playerid,-cost);
				/*
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
				_PlayerTeleporting[playerid]=6;
				FadeColorForPlayer(playerid,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,10,5);
				TogglePlayerControllable(playerid,false);
				Stop(playerid);
				SendClientMessage(playerid,GREEN," * Gavote darbini automobili. Susprogdinus ji teks mok?ti "#COST_DCMINI"-"#COST_DCSUPAKV"€");
				*/
				SendInfoMessage(playerid,"Sutaisei automobili!");
				new query[512];
				if(listitem == 0)
					format(query,512,"UPDATE `Darbines` Set `Status`=1,`Degalai`=40,`Health`=1000 WHERE `Job`=%i AND `Cartype`=%i AND `Vardas`='%s'",job,car,ReturnName(playerid));
				else
					format(query,512,"UPDATE `Darbines` Set `mod1`=0,`Health`=1000,`mod2`=0,`mod3`=0,`mod4`=0,`mod5`=0,`mod6`=0,`mod7`=0,`mod8`=0,`mod9`=0,`mod10`=0,\
						`mod11`=0,`mod12`=0,`mod13`=0,`mod14`=0,`mod15`=0,`mod16`=0,`mod17`=0,`Status`=1,`Degalai`=40 WHERE `Job`=%i AND `Cartype`=%i AND `Vardas`='%s'",job,car,ReturnName(playerid));

				mysql_function_query(SQL, query, true, "SQL_LoadDarbineDelay", "iii", playerid,job,car);
			}
		}
		if(dialogid==5602)
		{
			if(response)
			{
				DestroyOldCar(playerid);
				new job = PlayerLastJob[playerid][0];
				new car = PlayerLastJob[playerid][1];
//				new msg[128];
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
				if(GetPlayerMoneyA(playerid) < cost)
					return SendInfoMessage(playerid,"Neturi tiek pinigu!");
				GivePlayerMoneyA(playerid,-cost);
				/*
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
				_PlayerTeleporting[playerid]=6;
				FadeColorForPlayer(playerid,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,10,5);
				TogglePlayerControllable(playerid,false);
				Stop(playerid);
				SendClientMessage(playerid,GREEN," * Gavote darbini automobili. Susprogdinus ji teks mok?ti "#COST_DCMINI"-"#COST_DCSUPAKV"€");
				*/
				new health = 1000;
				new modelis = DarbinesCar[job][car][DCmodel];
				if(modelis == 432)
					health = 3000;
				if(modelis == 428 || modelis == 427)
					health = 2000;
				SendInfoMessage(playerid,"Sutaisei automobili!");
				new query[512];
				if(listitem == 0)
					format(query,512,"UPDATE `Darbines` Set `Status`=1,`Degalai`=40,`Health`=%i WHERE `Job`=%i AND `Cartype`=%i AND `Vardas`='%s'",health,job,car,ReturnName(playerid));
				else
					format(query,512,"UPDATE `Darbines` Set `mod1`=0,`mod2`=0,`mod3`=0,`mod4`=0,`mod5`=0,`mod6`=0,`mod7`=0,`mod8`=0,`mod9`=0,`mod10`=0,\
						`mod11`=0,`mod12`=0,`mod13`=0,`mod14`=0,`mod15`=0,`mod16`=0,`mod17`=0,`Status`=1,`Degalai`=40,`Health`=%i WHERE `Job`=%i AND `Cartype`=%i AND `Vardas`='%s'",health,job,car,ReturnName(playerid));
				mysql_query(query);
				//mysql_function_query(SQL, query, true, "SQL_LoadDarbineDelay", "iii", playerid,job,car);
			}
		}
		if(dialogid==755)
		{
			//ShowPlayerDialog(playerid,756,DIALOG_STYLE_MSGBOX,"Apmokymai","Jusu pinigai yra saugesni banke, nei jusu rankose.\n{0066CC}Banka ir kitas svarbias vietas rasite parase /kur","Gerai","");
			
			return 1;
		}
		/*if(dialogid==756)
		{
			ShowPlayerDialog(playerid,757,DIALOG_STYLE_MSGBOX,"Apmokymai","Serveryje alki galite numalsinti apsilanke restorane arba pasirause siuksliadezeje.","Gerai",""); //\n{0066CC}Banka ir kitas svarbias vietas rasite parase /kur"
			return 1;
		}
		if(dialogid==757)
		{
			ShowPlayerDialog(playerid,758,DIALOG_STYLE_MSGBOX,"Apmokymai","Noredami issilaikyti serveryje, turite dirbti.\n{0066CC}Darbus rasite parase /darbai","Gerai","");
			return 1;
		}
		if(dialogid==758)
		{
			ShowPlayerDialog(playerid,759,DIALOG_STYLE_MSGBOX,"Apmokymai","Kita reikalinga informacija rasite parase /pagalba\n{00FF00}Serveryje veikia griezta anti-cheat sistema. Bet koks bandymas sukciaut prives prie bano.\n{FF0000}Serveryje nera sa-mp pasauliui iprasto LAG SHOT bugo. Saudyti reikia tiesiai i zmogu.","Gerai","");
			return 1;
		}*/
		if(dialogid==5606)
		{
			if(response)
			{
				new hid = strval(inputtext);
				if(hid < 1 || hid > MAX_HOUSES)
					return 1;
				new y = hInfo[hid][daugiabutis]-1;
				if(!hInfo[hid][daugiabutis]) 
					SetPlayerCheckpoint(playerid,hInfo[hid][iconx],hInfo[hid][icony],hInfo[hid][iconz],2);
				else 			
					SetPlayerCheckpoint(playerid,Daugiabuciai[y][dX],Daugiabuciai[y][dY],Daugiabuciai[y][dZ],5.0);
				SendClientMessage(playerid,COLOR," * Namo pozicija paþymeta þemelapyje");
			}
		}
		if(dialogid==6881)
		{
			if(response)
			{
				new houseid=GetPlayerHouseID(playerid);
				if(!houseid) return 1;
				new i = PlayerLastBaldai[playerid];
				if(BalduSistema[houseid][i][b_used])
				{
					BalduSistema[houseid][i][b_used]=0;
					DestroyDynamicObject(BalduSistema[houseid][i][b_oid]);
					BalduSistema[houseid][i][b_oid]=-1;
				}
				SendClientMessage(playerid,WHITE," * Iðmetei baldus!");
			}
			else
			{
				PlayerLastBaldai[playerid]=0;
				SelectObject(playerid);
			}
		}
		if(dialogid==6871)
		{
			if(response)
			{
				new houseid,pname[MAX_PLAYER_NAME];
				houseid = GetPlayerHouseID(playerid);
				GetPlayerName(playerid, pname, 24);
				if ( strcmp(hInfo[houseid][Name],pname,false) != 0 && GetPVarInt(playerid,"irengineja") != houseid && !IsPlayerAdmin(playerid)) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");

				if(listitem==0)
				{
					mysql_function_query(SQL,"SELECT * From `baldai_cat` order by pav asc",true,"SQL_SelectMoveBaldai","ii",playerid,houseid);
					return 1;			
				}
				if(listitem==1) // ismesti
				{
					if ( strcmp(hInfo[houseid][Name],pname,false) != 0) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
					ShowPlayerDialog(playerid,6874,DIALOG_STYLE_LIST,"Pasirinkite buda","Pazymeti\nPagal sarasa","Gerai","Atsaukti");
					return 1;			
				}
				if(listitem==2) // pervezti
				{
					if ( strcmp(hInfo[houseid][Name],pname,false) != 0) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
					PlayerLastBaldai[playerid]=-1;
					SetTimerEx("Selectint",750,false,"i",playerid);
					//SelectObject(playerid);
					SendClientMessage(playerid, 0xFFFFFFFF, " * Naudokites pele ir pasirinkite kurá baldà norite perveþti!");
					SendClientMessage(playerid, 0xFFFFFFFF, " * Iðjungti ðá rëþimà galite paspaudæ ESC.");
				}
				if(listitem == 3)
				{
					ShowPlayerDialog(playerid, 6952, DIALOG_STYLE_INPUT, "Irengimas", "Áveskite NTA agento vardà, kuriam norite leisti árengti jûsø namà.\nTai jums kainuos 25.000€ + iðlaidos uþ baldus susitarus su NTA.\nJis/ji turës 24 valandas per kurias galës perstatyti ir pirkti naujus baldus jûsø namui.", "Gerai", "Atðaukti");
				}
			}
		}
		if(dialogid == 6952)
		{
			if(response)
			{
				new id = GetPlayeridMid(inputtext);
				if( id == playerid) return SendInfoMessage(playerid,"~r~Sau leisti negali.");
				if(id == INVALID_PLAYER_ID) return SendInfoMessage(playerid,"~r~Tokio zaidejo nera.");
				if(playerDB[id][specialybe] != 34)
					return SendInfoMessage(playerid,"~r~Sis zaidejas nedirba NTA.");
				if(GetPlayerMoneyA(playerid) < 25000)
					return SendInfoMessage(playerid,"Neturi pakankamai pinigu.");
				new houseid = GetPlayerHouseID(playerid);
				if(!houseid)
					return 1;
				new pname[MAX_PLAYER_NAME];
				GetPlayerName(playerid, pname, 24);
				if (strcmp(hInfo[houseid][Name],pname,false) != 0 ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
				TryIrengti(playerid,id,houseid);
			}
		}
		if(dialogid==6951)
		{
			if(response)
			{
				new input = strval(inputtext);
				if(input < 1 || input > Iter_Count(Houses))
				{
					return SendInfoMessage(playerid,"~r~Netinkamas namas!");
				}
				new houseid = GetPlayerHouseID(playerid);
				if(!houseid)
					return 1;

				new hid = input;
				if(strcmp(hInfo[hid][Name],"Nera",true) == 0)
					return SendInfoMessage(playerid,"~r~Namas nepriklauso niekam!");
				if(hid == GetPlayerHouseID(playerid))
					return SendInfoMessage(playerid,"~r~Negali pervezti baldu i ta pati nama!");

				new pname[MAX_PLAYER_NAME];
				GetPlayerName(playerid, pname, 24);
				if (strcmp(hInfo[houseid][Name],pname,false) != 0) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");

				new id2 = -1;
				new id1 = GetPVarInt(playerid, "selected_baldas");
				if(BalduSistema[houseid][id1][b_used]==0)
				{
					return SendInfoMessage(playerid,"Tokio baldo nera!");
				}
				for(new b;b<MAX_BALDAI;b++)
				{
					if(!BalduSistema[hid][b][b_used])
					{
						id2=b;
						break;
					}
				}
				if(id2==-1) return SendInfoMessage(playerid," Kitam name nebera vietos baldams!");
				BalduSistema[hid][id2][b_used]=1;
				BalduSistema[houseid][id1][b_used]=0;
				DestroyDynamicObject(BalduSistema[houseid][id1][b_oid]);
				BalduSistema[hid][id2][b_obj]=BalduSistema[houseid][id1][b_obj];
				BalduSistema[hid][id2][b_cat]=BalduSistema[houseid][id1][b_cat];
				//BalduSistema[hid][id2][b_oid]=CreateDynamicObject(BalduSistema[hid][id2][b_obj],BalduSistema[hid][id2][b_x],BalduSistema[hid][id2][b_y],BalduSistema[hid][id2][b_z],BalduSistema[hid][id2][b_rx],BalduSistema[hid][id2][b_ry],BalduSistema[hid][id2][b_rz],GetHouseVirtualWorld(hid), _, _, 50.0);
				//FixBalduObj(BalduSistema[hid][id2][b_oid]);
				CreateBaldas(hid,id2);
				new msgas[128];
				format(msgas,128," * Pervezei baldus á namà Nr. %i",input);
				SendClientMessage(playerid,WHITE,msgas);
				SaveBaldai(houseid);
				SaveBaldai(hid);

			}
			else
			{
				PlayerLastBaldai[playerid]=-1;
				SetTimerEx("Selectint",750,false,"i",playerid);
				//SelectObject(playerid);
				SendClientMessage(playerid, 0xFFFFFFFF, " * Naudokites pele ir pasirinkite kurá baldà norite perveþti!");
				SendClientMessage(playerid, 0xFFFFFFFF, " * Iðjungti ðá rëþimà galite paspaudæ ESC.");
			}
		}
		if(dialogid==6874)
		{
			if(response)
			{
				if(listitem==0)
				{
					new houseid,pname[MAX_PLAYER_NAME];
					houseid = GetPlayerHouseID(playerid);
					GetPlayerName(playerid, pname, 24);
					if ( strcmp(hInfo[houseid][Name],pname,false)) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
					SetTimerEx("Selectint",750,false,"i",playerid);
					//SelectObject(playerid);
					SendClientMessage(playerid, 0xFFFFFFFF, " * Naudokites pele ir pasirinkite kurá baldà norite iðmesti!");
					SendClientMessage(playerid, 0xFFFFFFFF, " * Iðjungti ðá rëþimà galite paspaudæ ESC.");
					PlayerLastBaldai[playerid]=0;
				}
				else
				{
					new query[256];
					new houseid,pname[MAX_PLAYER_NAME];
					houseid = GetPlayerHouseID(playerid);
					GetPlayerName(playerid, pname, 24);
					if ( strcmp(hInfo[houseid][Name],pname,false)) return SendInfoMessage(playerid,"Ðis namas nepriklauso jums!");
					format(query,sizeof(query),"SELECT * From `baldai_cat` order by id asc");
					mysql_function_query(SQL,query,true,"SQL_SelectDeleteBaldai","ii",playerid,houseid);
				}
			}
			return 1;
		}
		if(dialogid==6872)
		{
			if(response)
			{
				if(GetPlace(playerid) != PLACE_HOUSE)
					return SendInfoMessage(playerid,"Privalote buti namie!");
				new houseid=GetPlayerHouseID(playerid);
				PlayerLastCat[playerid]=DLItemID; //listitem;
				new x;
				new Float:dist;
				new Float:Coo[3];
				GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
				format(G_DialogList,sizeof(G_DialogList),"Objektas\tAtstumas{FFFFFF}\n");
				for(new i;i<MAX_BALDAI;i++)
				{
					if(x >= 75 || strlen(G_DialogList) >= 3800)
					{
						break;
					}
					if(BalduSistema[houseid][i][b_used] && BalduSistema[houseid][i][b_cat]==DLItemID) // listitem
					{

						x++;
						new objectid = BalduSistema[houseid][i][b_obj];
						dist = floatsqroot((Coo[0]-BalduSistema[houseid][i][b_x])*(Coo[0]-BalduSistema[houseid][i][b_x])+(Coo[1]-BalduSistema[houseid][i][b_y])*(Coo[1]-BalduSistema[houseid][i][b_y])+(Coo[2]-BalduSistema[houseid][i][b_z])*(Coo[2]-BalduSistema[houseid][i][b_z]));
						if(dist < 200)
						{
							format(G_DialogList,sizeof(G_DialogList),"%s%i.%s (%i)\t{00FF00}Padëtas uþ %.1fm{FFFFFF}\n",G_DialogList,x,smartSearch(objectid),objectid,dist);
						}
						else
						{
							format(G_DialogList,sizeof(G_DialogList),"%s%i.%s (%i)\t{FF0000}Nepadëtas{FFFFFF}\n",G_DialogList,x,smartSearch(objectid),objectid);
						}
					}
				}
				if(!x) return SendInfoMessage(playerid,"~r~Neturi baldu sioje kategorijoje!");
				format(G_DialogList,sizeof(G_DialogList),"%sPasirinkti pagal nuotrauka...",G_DialogList);
				ShowPlayerDialog(playerid,6873,DIALOG_STYLE_TABLIST_HEADERS,"Pasirinkite baldus",G_DialogList,"Gerai","Atsaukti");
				return 1;
				/*new query[256];
				format(query,sizeof(query),"SELECT * From baldai Where houseid=%i AND cat=%i",GetPlayerVirtualWorld(playerid),listitem);
				mysql_function_query(SQL,query,true,"SQL_ViewCategory","iii",playerid,GetPlayerVirtualWorld(playerid),listitem);
				return 1;*/
			}
			
		}
		if(dialogid==6875)
		{
			if(response)
			{
				
				new houseid=GetPlayerHouseID(playerid);
				PlayerLastCat[playerid]=DLItemID;//listitem;
				new x;
				new Float:dist;
				new Float:Coo[3];
				GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
				format(G_DialogList,sizeof(G_DialogList),"{FFFFFF}");
				for(new i;i<MAX_BALDAI;i++)
				{
					if(BalduSistema[houseid][i][b_used] && BalduSistema[houseid][i][b_cat]==DLItemID) //listitem
					{
					
						x++;
						dist = floatsqroot((Coo[0]-BalduSistema[houseid][i][b_x])*(Coo[0]-BalduSistema[houseid][i][b_x])+(Coo[1]-BalduSistema[houseid][i][b_y])*(Coo[1]-BalduSistema[houseid][i][b_y])+(Coo[2]-BalduSistema[houseid][i][b_z])*(Coo[2]-BalduSistema[houseid][i][b_z]));
						if(dist < 200)
						{
							format(G_DialogList,sizeof(G_DialogList),"%s%i.Objektas id.%i[{00FF00}Padetas uz %.1fm{FFFFFF}]\n",G_DialogList,x,BalduSistema[houseid][i][b_obj],dist);
						}
						else
						{
							format(G_DialogList,sizeof(G_DialogList),"%s%i.Objektas id.%i[{FF0000}Nepadetas{FFFFFF}]\n",G_DialogList,x,BalduSistema[houseid][i][b_obj]);
						}
						
					}
				}
				if(!x) return SendInfoMessage(playerid,"~r~Neturi baldu sioje kategorijoje!");
				ShowPlayerDialog(playerid,6876,DIALOG_STYLE_LIST,"Pasirinkite baldus",G_DialogList,"Gerai","Atsaukti");
				/*new query[256];
				format(query,sizeof(query),"SELECT * From baldai Where houseid=%i AND cat=%i",GetPlayerVirtualWorld(playerid),listitem);
				mysql_function_query(SQL,query,true,"SQL_ViewCategory","iii",playerid,GetPlayerVirtualWorld(playerid),listitem);
				return 1;*/
			}
		}
		if(dialogid==6876)
		{
			if(response)
			{
				//ew list[MAX_BALDAI];
				new items;
				new houseid=GetPlayerHouseID(playerid);
				new x;
				//new msg[1524];
				for(new i;i<MAX_BALDAI;i++)
				{
					if(BalduSistema[houseid][i][b_used] && BalduSistema[houseid][i][b_cat]==PlayerLastCat[playerid])
					{
						//list[items]=BalduSistema[houseid][i][b_oid];
						if(items==listitem)
							x=i;
						items++;
					}
				}
				//new objektoid=list[listitem];
				//for(new i;i<
				new query[256];
				format(query,sizeof(query),"SELECT `pav` FROM `baldai_cat` WHERE id=%i LIMIT 1",BalduSistema[houseid][x][b_cat]);
				CancelEdit(playerid);
				mysql_function_query(SQL,query, true,"SQL_IsmestiBaldus","iii",playerid,houseid,x);
				return 1;
			}
		}
		if(dialogid==6873)
		{
			if(response)
			{
				if(GetPlace(playerid) != PLACE_HOUSE)
					return SendInfoMessage(playerid,"Privalote buti namie!");

				//new list[MAX_BALDAI];
				new items;
				new houseid=GetPlayerHouseID(playerid);
				if ( strcmp(hInfo[houseid][Name],ReturnName(playerid),false) != 0 && GetPVarInt(playerid,"irengineja") != houseid && !IsPlayerAdmin(playerid))
				{
					return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
				} 
				new cat = PlayerLastCat[playerid]; //listitem;
				new baldai[MAX_BALDAI];
				//new msg[1524];
				for(new i;i<MAX_BALDAI;i++)
				{
					if(BalduSistema[houseid][i][b_used] && BalduSistema[houseid][i][b_cat]==PlayerLastCat[playerid])
					{
						//list[items]=BalduSistema[houseid][i][b_oid];
						new objectid = BalduSistema[houseid][i][b_obj];
						baldai[items] = objectid;
						if(items == listitem)
						{
							SetPVarInt(playerid, "EditingBaldas", i);
						}
						items++;
					}
				}
				if(listitem == items || listitem >= 75)
				{
					if(items) 
						ShowModelSelectionMenuEx(playerid, baldai, items, "Pasirinkite baldus", GUI_BALDAI2+cat, 340.0, 0.0, 180.0, 1.5,0xF2FEBFBB,0xE6FE8099,0x88888899);
					return 1;
				}
				if( GetPVarInt(playerid,"irengineja") == houseid)
					ShowPlayerDialog(playerid, 6883, DIALOG_STYLE_LIST, "Baldai", "Perstatyti","Gerai","Atsaukti");
				else
					ShowPlayerDialog(playerid, 6883, DIALOG_STYLE_LIST, "Baldai", "Perstatyti\nIðmesti\nPerveþti á kità namà","Gerai","Atsaukti");
				return 1;
			}
			else
			{
				new houseid=GetPlayerHouseID(playerid);
				mysql_function_query(SQL,"SELECT * From `baldai_cat` order by pav asc",true,"SQL_SelectMoveBaldai","ii",playerid,houseid);
				return 1;
			}

		}
		if(dialogid==6883)
		{
			if(response)
			{
				if(GetPlace(playerid) != PLACE_HOUSE)
					return SendInfoMessage(playerid,"Privalote buti namie!");
				new houseid=GetPlayerHouseID(playerid);
				if ( strcmp(hInfo[houseid][Name],ReturnName(playerid),false) != 0 && GetPVarInt(playerid,"irengineja") != houseid && !IsPlayerAdmin(playerid))
				{
					return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
				} 
				new i = GetPVarInt(playerid, "EditingBaldas");
				new obj = BalduSistema[houseid][i][b_oid];
				if(listitem == 0)
				{
					new Float:Coo[3];
					new Float:Xoo[3];

					GetDynamicObjectPos(obj,Xoo[0],Xoo[1],Xoo[2]);
					
					GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
					GetXYInFrontOfPlayer(playerid, Coo[0],Coo[1], 1.9); //1221
					new Float:Dist = GetDistanceBetweenPoints(Coo[0],Coo[1],Coo[2],Xoo[0],Xoo[1],Xoo[2]);

					//Coo[2]+=1.0;
					if(Dist > 15.0)
						SetDynamicObjectPos(obj, Coo[0]+0.5,Coo[1],Coo[2]-0.5);
					SetTimerEx("EditBaldas",1000,false,"ii",playerid,obj);
					//EditPlayerObject(playerid, list[listitem]);
					EditDynamicObject(playerid, obj);
					SetPVarInt(playerid, "EditingID", obj);
					SetPVarInt(playerid, "PlayerPoly", GetPlayerPoly(playerid));
					SendClientMessage(playerid,WHITE," * Naudokites rodyklëmis, kad judintumët objektà ir paspauskite diskà arba ESC mygtukà kai norësite baigti!");
					SendClientMessage(playerid,WHITE," * Objektà pasukti galite ájungæ sukiojimo rëþimà (mygtukas apaèioje)");
					SendClientMessage(playerid,WHITE," * Vaizdà sukiot gali laikydamas SPACE");
				}
				else if(listitem == 1)
				{
					new query[256];
					format(query,sizeof(query),"SELECT `pav` FROM `baldai_cat` WHERE id=%i LIMIT 1",BalduSistema[houseid][i][b_cat]);
					CancelEdit(playerid);
					mysql_function_query(SQL,query, true,"SQL_IsmestiBaldus","iii",playerid,houseid,i);
				}
				else if(listitem == 2)
				{
					SetPVarInt(playerid, "selected_baldas", i);
					new msg[256];
					format(msg,256,"Iveskite namo numerá, á kurá norite perveþti ðá baldà %s (%i).\nNamas turi bûti nupirktas.",smartSearch(obj),obj);
					ShowPlayerDialog(playerid, 6951, DIALOG_STYLE_INPUT, "Perveþimas", msg, "Gerai", "Atðaukti");

				}
				return 1;
			}
			else
			{
				new houseid=GetPlayerHouseID(playerid);
				mysql_function_query(SQL,"SELECT * From `baldai_cat` order by pav asc",true,"SQL_SelectMoveBaldai","ii",playerid,houseid);
				return 1;
			}
		}
		if(dialogid==6870)
		{
			new hid1=-1,
				hid2=-1,
				name[MAX_PLAYER_NAME];
			GetPlayerName(playerid,name,sizeof(name));
			foreach(Houses,i)
			{
				if(0==strcmp(name,hInfo[i][Name],false))
				{
					if(hid1==-1)
					{
						hid1=i;
						continue;
					}
					else
					{
						hid2=i;
						break;
					}
				}
			}
			if(hid1 == -1) return 0;
			new valid[5];
			new totalh;
			for(new i;i<MAX_BALDAI;i++)
			{
				if(!BalduSistema[hid1][i][b_used])
				{
					valid[totalh]=hid1;
					totalh++;
					break;
				}
			}
			if(hid2 != -1)
			{
				for(new i;i<MAX_BALDAI;i++)
				{
					if(!BalduSistema[hid2][i][b_used])
					{
						valid[totalh]=hid2;
						totalh++;
						break;
					}
				}
			}
			if(GetPVarInt(playerid,"irengineja") != 0)
			{
				valid[totalh] = GetPVarInt(playerid,"irengineja");
				totalh++;
			}
			if(!totalh) return 0;
			if(!valid[listitem]) return 0;
			
			new hid=valid[listitem];
			for(new i;i<MAX_BALDAI;i++)
			{
				if(!BalduSistema[hid][i][b_used])
				{
					if(i > 9)
					{
						ProcessAchievement(playerid,29);
					}
					BalduSistema[hid][i][b_used]=1;
					BalduSistema[hid][i][b_obj]=PlayerLastBaldai[playerid];
					BalduSistema[hid][i][b_cat]=PlayerLastCat[playerid];
					BalduSistema[hid][i][b_x]=0.0;
					BalduSistema[hid][i][b_y]=0.0;
					BalduSistema[hid][i][b_z]=-1000.0;
					BalduSistema[hid][i][b_rx]=0.0;
					BalduSistema[hid][i][b_ry]=0.0;
					BalduSistema[hid][i][b_rz]=0.0;
					//BalduSistema[hid][i][b_oid]=CreateDynamicObject(BalduSistema[hid][i][b_obj],BalduSistema[hid][i][b_x],BalduSistema[hid][i][b_y],BalduSistema[hid][i][b_z],BalduSistema[hid][i][b_rx],BalduSistema[hid][i][b_ry],BalduSistema[hid][i][b_rz],GetHouseVirtualWorld(hid), _, _, 50.0);
					CreateBaldas(hid,i);
					SendClientMessage(playerid,WHITE," * Baldai pristatyti á namus! Juos perstatyti galite paraðæ /baldai");
					ShowBaldaiCat(playerid);
					SaveBaldai(hid);
					break;
				}
			}
		}
		if(dialogid==6879)
		{
			if(response)
			{
				new query[256];
				format(query,sizeof(query),"SELECT `id` FROM `baldai_cat` WHERE rusis='%i' LIMIT %i,1",GetBaldaiType(playerid),listitem);
				mysql_function_query(SQL,query,true,"SQL_LoadCat","i",playerid);
				//format(query,sizeof(query),"SELECT `id` FROM `baldai_cat` WHERE rusis='%i' LIMIT %i,1",GetBaldaiType(playerid),listitem);
			}
		}
		if(dialogid==6878)
		{
			if(response)
			{
				if(!PlayerLastKaina[playerid]) return 0;
				if(GetPlayerMoneyA(playerid) < PlayerLastKaina[playerid])
					return SendInfoMessage(playerid,"~r~Neturi tiek pinigu!");
				if(!DeliverBaldai(playerid,PlayerLastBaldai[playerid]))
				{
					SendClientMessage(playerid,WHITE," * Neturite namø, kuriuose tilptø daugiau baldø!");
					PlayerLastBaldai[playerid]=0;
					return 1;
				}
				GivePlayerMoneyA(playerid, -PlayerLastKaina[playerid]);
				ProcessAchievement(playerid, 122);
				BusinessMoney(PlayerLastKaina[playerid]);
				ActorServe(playerid);
				return 1;
			}
			else
			{
				ShowBaldaiShope(playerid,PlayerLastCat[playerid]);
			}
		}
		/*
		if(dialogid==7540)
		{
			if(!response) return 1;
			if(listitem==0)
			{
				ShowPlayerDialog(playerid,7541,DIALOG_STYLE_INPUT,"Baldai","Iveskite kategorijos, kuria norite sukurti, pavadinima.","Gerai","Atgal");
				return 1;
			}
			if(listitem==1)
			{
				mysql_function_query(SQL, "SELECT pav FROM `baldai_cat`", true, "SQL_SelectCat", "i",playerid);
				return 1;
			}
			if(listitem==2)
			{
				ShowPlayerDialog(playerid,7543,DIALOG_STYLE_INPUT,"Prideti balda","Noredami prideti daikta, rasykite siuo formatu:\n{00FF00}Objektoid;Kategorija;Pavadinimas\n{FFFFFF}PVZ:18515;1;Televizorius LG 100cm","Gerai","Atgal");
				return 1;
			}
		}
		if(dialogid==7541)
		{
			if(!response) BaldaiEdit(playerid);
			if(!strlen(inputtext)) return 0;
			new query[512];
			format(query,sizeof(query),"INSERT INTO `baldai_cat`(`pav`) VALUES('%s')",inputtext);
			mysql_query(query);
			SendClientMessage(playerid,WHITE," * Kategorija sukurta!");
			return 1;
		}
		if(dialogid==7542) // delete cat
		{
			if(!response) BaldaiEdit(playerid);
			new query[512];
			format(query,sizeof(query),"DELETE FROM `baldai_cat` LIMIT %i,1",listitem);
			mysql_query(query);
			SendClientMessage(playerid,WHITE," * Kategorija istrinta!");
			return 1;
		}
		if(dialogid==7543)
		{
			if(!response) BaldaiEdit(playerid);
			new objectid,cat,name[30];
			if(sscanf(inputtext,"p<;>iis[30]",objectid,cat,name)) return SendClientMessage(playerid,WHITE," * Netinkamas formatas!");
			new query[512];
			mysql_real_escape_string(name,name);
			format(query,sizeof(query),"INSERT INTO `baldai_id`(`cat`,`pav`,`obj`) VALUES ('%i','%s','%i')",cat,name,objectid);
			mysql_query(query);
			SendClientMessage(playerid,WHITE," * Objektas pridetas!");
			ShowPlayerDialog(playerid,7543,DIALOG_STYLE_INPUT,"Prideti balda","Noredami prideti daikta, rasykite siuo formatu:\n{00FF00}Objektoid;Kategorija;Pavadinimas\n{FFFFFF}PVZ:18515;1;Televizorius LG 100cm","Gerai","Atgal");
			return 1;
		}
		*/
		if(dialogid==1122)
		{
			if(response)
			{
				new count = 0;
				for(new i;i<MAX_PATRULIU;i++)
				{
					if(Patruliai[i][used])
					{
						if(listitem == count)
						{
							if(playerDB[playerid][plead]==80 || playerDB[playerid][admin])
							{
								LoadPatruliavimas(playerid,i);
								SendClientMessage(playerid,YELLOW," * Norëdami iðtrinti ðià patruliavimo zonà, raðykite /trintizona");
							}
							else
							{
								LoadPatruliavimas(playerid,i);
							}
							return 1;
						}
						count++;
					}
				}
				if(playerDB[playerid][plead]==80 || playerDB[playerid][admin])
				{
					SendClientMessage(playerid,YELLOW," * Norëdami ðioje vietoje sukurt patruliavimo zonà, raðykite /kurtizona [atstumas] [max patruliu] [pavadinimas]");
					return 1;
				}
			}
		}
		if(dialogid==9989)
		{
			if(response)
			{
				new res = SendSMSConfirmation(playerid, inputtext);
				SetPVarString(playerid,"telnr",inputtext);
				if(!res)
				{
					ShowPlayerDialog(playerid,9989,DIALOG_STYLE_INPUT,"Iveskite telefono numeri","{FF0000}Neteisingas telefono numeris!\n\n\
					{ffffff}Iveskite savo mob. telefono numeri, kad patvirtumete savo registracija.\n\n\
					Galimi formatai:\n\
					{f55d42}86*******\n\
					{f55d42}3706*******\n\
					{f55d42}+3706*******\n\
					\n\n\n\
					{ffffff}Jeigu neturite lietuvisko numerio, sukurkite tema musu forumo Pagalbos skiltyje ir jusu akaunta perziuresime rankiniu budu.","Gerai","Atsaukti");
				}
			}
			else
			{
				KickEx(playerid);
			}
			return 1;
		}
		if(dialogid==9799)
		{
			if(response)
			{			
				new thecode = GetPVarInt(playerid,"ConfirmationCode");
				new input = strval(inputtext);
				if(!IsNumeric(inputtext) || strlen(inputtext) != 5 || input != thecode)
				{
					new retries = GetPVarInt(playerid, "Retries");
					SetPVarInt(playerid,"Retries", retries + 1);
					if(retries == 3)
					{
						return Kick(playerid);
					}
					ShowPlayerDialog(playerid,9799,DIALOG_STYLE_INPUT,"Iveskite patvirtinimo koda","{ff0000}Neteisingai ivestas patvirtinimo kodas!\n\
					{ffffff}Iveskite savo patvirtinimo koda, kad uzbaigtumete registracija.","Gerai","Atsaukti");
					return 1;
				}
				new query[128];
				format(query,128,"Update Phones Set Patvirtinta=1, Data=NOW() WHERE Vardas='%s'",ReturnName(playerid));
				mysql_query(query);
				SendClientMessage(playerid, -1, " * Sekmingai patvirtinote savo telefono numeri!");
				LetPlayerSpawn(playerid, GetPVarInt(playerid, "loginvar"));
			}
			else
			{
				Kick(playerid);
			}
			return 1;
		}
		if(dialogid==9990)
		{
			if(!response)
				return Kick(playerid);
			if(listitem == 0)
			{
				ShowPlayerDialog(playerid,9799,DIALOG_STYLE_INPUT,"Iveskite patvirtinimo koda","{ffffff}Iveskite savo patvirtinimo koda, kad uzbaigtumete registracija.","Gerai","Atsaukti");
			}
			else
			{
				TryNumberConfirm(playerid);
			}
			return 1;
		}
		if(dialogid==9988)
		{
			if(GetPlayerInterior(playerid))
			{
				for(new i;i<MAX_POKER_GAMES;i++)
				{
					if(IsPlayerInRangeOfPointEx(3.0,playerid,PokerTables[i][0],PokerTables[i][1],PokerTables[i][2]))
					{
						if(!playerDB[playerid][playingpoker])
						{
							if(!IsNumeric(inputtext)) return SendInfoMessage(playerid,"Skaiciais!");
							new suma = strval(inputtext);
							if(suma < PokerBlinds[i][2] || suma > PokerBlinds[i][3]) return SendInfoMessage(playerid,"Netinkama suma!");
							if(GetPlayerMoneyA(playerid) < suma)
							{
								return SendInfoMessage(playerid,"Jus tiek neturite! Bankomata rasite kazino gale.");
							}
							if(Poker[i][GameUsed])
							{
								new found=-1;
								//new y;
								for(new x;x<6;x++) // 3 FOR TESTING ONLY
								{
									if(Poker[i][players][x] == -1)
									{
										found = x;
										break;
									}
								}
								if(found == -1)
								{
									new queId = AddToPokerWaitQue(playerid, i, suma);
									if(!queId)
									{
										return SendInfoMessage(playerid, "Pokerio eile pilna!");
									}
									new msg[256];
									format(msg,256,"Jusu vieta pokerio eileje: ~r~%i~n~~w~Noredami iseiti spauskite [H]",queId);
									SendInfoMessage(playerid, msg);

									return 1;
								}
								GivePlayerMoneyA(playerid, -suma);
								Poker[i][PFondas][found]=suma;
								Poker[i][players][found]=playerid;
								Poker[i][Playing][found]=0;
								SetPlayerPos(playerid,SeatCoords[i][found][0],SeatCoords[i][found][1],SeatCoords[i][found][2]);
								SetPlayerFacingAngle(playerid,SeatCoords[i][found][3]);
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
								SendClientMessage(playerid,-1,"Norëdami iðeiti spauskite ESC!");
								SelectTextDraw(playerid, 0xACCBF1FF);
							}
							else
							{
								AddToPokerQue(playerid,i,suma);
							}
							return 1;
						}	
					}
				}
			}
		}
		if(dialogid==6000)
		{
			if(response)
			{
				switch(DLItemID)
				{
					case 1: ShowPlayerDialog(playerid,6001,DIALOG_STYLE_INPUT,"Prideti pinigu","Irasykite kiek pinigu norite prideti.","Gerai","Atsaukti");
					case 2: ShowPlayerDialog(playerid,6002,DIALOG_STYLE_INPUT,"Prideti kreditu","Irasykite kiek kreditu norite prideti.","Gerai","Atsaukti");
					case 3:
					{
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
					        AddDListItem(playerid, msg, 1);
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
					        AddDListItem(playerid, msg, 2);
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
					        AddDListItem(playerid, msg, 3);
						}
						ShowPlayerDList(playerid, 6003, "Prideti automobili", "Rinktis", "Atsaukti");
					}
					case 4:
					{
						new pname[MAX_PLAYER_NAME],msg[512];
						GetPlayerName(playerid,pname,MAX_PLAYER_NAME);
						foreach(Businesses,i) if(BusinessInfo[i][bOwned] && 0==strcmp(BusinessInfo[i][bOwner],pname,false))
						{
							format(msg,sizeof(msg),"%s(%s)",BusinessInfo[i][bName],GetBussinessType(BusinessInfo[i][bType]));
							AddDListItem(playerid, msg, i);
						}
						ShowPlayerDList(playerid, 6004, "Prideti versla", "Rinktis", "Atsaukti");
					}
					case 5:
					{
						new hid1=-1,
							hid2=-1,
							name[MAX_PLAYER_NAME];
						new msg[128];
						GetPlayerName(playerid,name,sizeof(name));
						foreach(Houses,i)
						{
							if(0==strcmp(name,hInfo[i][Name],false))
							{
								if(hid1==-1)
								{
									hid1=i;
									format(msg,sizeof(msg),"Namas Nr.%i",hid1);
									AddDListItem(playerid, msg, i);
									continue;
								}
								else
								{
									hid2=i;
									format(msg,sizeof(msg),"Namas Nr.%i",hid2);
									AddDListItem(playerid, msg, i);
									break;
								}
							}
						}
						ShowPlayerDList(playerid, 6005, "Prideti nama", "Rinktis", "Atsaukti");
						return 1;
					}
					case 6: ClearOffer(playerid);
				}
			}
		}
		case 6001:
		{
			if(response)
			{
				new kiek = strval(inputtext);
				if(!IsNumeric(inputtext) || !kiek) return SendInfoMessage(playerid,"Netinkama suma!");
				if(GetPlayerMoneyA(playerid) < kiek) return SendInfoMessage(playerid,"Jus tiek neturite!");
				//GivePlayerMoneyA(playerid, -kiek);
				new x;
				x = AddItemToMainai(playerid,1,kiek);
				if(!x) return SendInfoMessage(playerid,"Nebera vietos!");
				return 1;
			}
		}
		case 6002:
		{
			if(response)
			{
				new kiek = strval(inputtext);
				if(!IsNumeric(inputtext) || !kiek) return SendInfoMessage(playerid,"Netinkama suma!");
				if(playerDB[playerid][kreditai] < kiek) return SendInfoMessage(playerid,"Jus tiek neturite!");
				/*playerDB[playerid][kreditai]-=kiek;
				new uzrasas[128];
				format(uzrasas,128,"UPDATE `Account` SET Kreditai =%i WHERE `Name` = '%s'",playerDB[playerid][kreditai],ReturnName(playerid));
				mysql_query(uzrasas); */
				new x;
				x = AddItemToMainai(playerid,2,kiek);
				if(!x) return SendInfoMessage(playerid,"Nebera vietos!");
				return 1;
			}
		}
		case 6003,6004,6005:
		{
			if(response)
			{
				new x;
				x = AddItemToMainai(playerid,dialogid-6000,DLItemID);
				if(!x) return SendInfoMessage(playerid,"~r~Nebera vietos!");
				if(x==2) return SendInfoMessage(playerid,"~r~Sia preke jus jau pridejote!");
				return 1;
			}
		}
		if(dialogid==9352)
		{
			if(response)
			{
				if(listitem==0)
				{
					new name[MAX_PLAYER_NAME];
					new msg[2048];
					GetPlayerName(playerid,name,sizeof(name));
					new x = 0;
					foreach(Businesses,i)
					{
						if(0==strcmp(BusinessInfo[i][bOwner],name,false) && x < 10)
						{
							new sumas;
							if(BusinessInfo[i][bMokesciai] > 0) 
								sumas=1000;
							else
								sumas = ((-BusinessInfo[i][bMokesciai])*100+1000);
							//new dienos = ((-14-BusinessInfo[i][bMokesciai])*-1);
							
							format(msg,sizeof(msg),"%s%s - %i€ %s\n",msg,BusinessInfo[i][bName],sumas,((BusinessInfo[i][bMokesciai] <= 2) ? ("Reikia moketi") : ("Nereikia moketi")));
							x++;
						}
					}
					if(strlen(msg))
						ShowPlayerDialog(playerid,9353,DIALOG_STYLE_LIST,"Mokesciai",msg,"Moketi","Atgal");
					else 
						SendInfoMessage(playerid,"Neturi verslo!");
					return 1;
				}
				else
				{
					new name[MAX_PLAYER_NAME];
					new msg[2048];
					GetPlayerName(playerid,name,sizeof(name));
					foreach(Houses,i)
					{
						if(0==strcmp(hInfo[i][Name],name,false))
						{
							new sumas;
							if(hInfo[i][hMokesciai] > 0) 
								sumas=100;
							else
								sumas = (((-hInfo[i][hMokesciai])+1)*100);

							format(msg,sizeof(msg),"%sNamas Nr.%i - %i€ %s\n",msg,i,sumas,((hInfo[i][hMokesciai] <= 2) ? ("Reikia moketi") : ("Nereikia moketi")));
						}
					}
					if(strlen(msg))
						ShowPlayerDialog(playerid,9354,DIALOG_STYLE_LIST,"Mokesciai",msg,"Moketi","Atgal");
					else 
						SendInfoMessage(playerid,"Neturi namo!");
					return 1;
				}
			}
		}
		if(dialogid==9353)
		{
			if(response)
			{	
				new name[MAX_PLAYER_NAME];
				GetPlayerName(playerid,name,sizeof(name));
				new sumas;
				new x,idx;
				foreach(Businesses,i)
				{
					if(0==strcmp(BusinessInfo[i][bOwner],name,false))
					{
						if(listitem==x)
						{
							idx=i;
							break;
						}
						x++;
					}
				}
				if(BusinessInfo[idx][bMokesciai] > 0) 
					sumas=1000;
				else
					sumas = ((-BusinessInfo[idx][bMokesciai])*100+1000);
				if(GetPlayerMoneyA(playerid) < sumas) return SendInfoMessage(playerid,"Jus tiek neturite!");
				GivePlayerMoneyA(playerid, -sumas);
				if(BusinessInfo[idx][bMokesciai] != 14)
					ProcessAchievement(playerid,96);
				BusinessInfo[idx][bMokesciai]=14;
				SendInfoMessage(playerid,"Mokesciai sumoketi.~n~Vel moketi reikes po 14 dienu~n~Apie tai pranesime el. pastu");
				ShowPlayerDialog(playerid,9352,DIALOG_STYLE_LIST,"Mokesciai","Mokesèiai uþ verslus\nMokesèiai uþ namus","Rinktis","Atsaukti");
				return 1;
			}
		}
		if(dialogid==9354)
		{
			if(response)
			{	
				new name[MAX_PLAYER_NAME];
				GetPlayerName(playerid,name,sizeof(name));
				new sumas;
				new x,idx;
				foreach(Houses,i)
				{
					if(0==strcmp(name,hInfo[i][Name],false))
					{
						if(listitem==x)
						{
							idx=i;
							break;
						}
						x++;
					}
				}
				if(hInfo[idx][hMokesciai] > 0) 
					sumas=100;
				else
					sumas = (((-hInfo[idx][hMokesciai])+1)*100);
				if(GetPlayerMoneyA(playerid) < sumas) return SendInfoMessage(playerid,"Jus tiek neturite!");
				GivePlayerMoneyA(playerid, -sumas);
				if(hInfo[idx][hMokesciai] != 14)
					ProcessAchievement(playerid,96);
				hInfo[idx][hMokesciai]=14;	
				new querfr[240];
				format(querfr,sizeof(querfr),"UPDATE `Namai` SET `bMokesciai`=%i WHERE ID=%i",hInfo[idx][hMokesciai],idx);
				mysql_query(querfr);
				SendInfoMessage(playerid,"Mokesciai sumoketi.~n~Vel moketi reikes po 14 dienu~n~Apie tai pranesime el. pastu");
				ShowPlayerDialog(playerid,9352,DIALOG_STYLE_LIST,"Mokesciai","Mokesèiai uþ verslus\nMokesèiai uþ namus","Rinktis","Atsaukti");
				return 1;
			}
		}
		if(dialogid==8252)
		{
			if(response)
			{
				if(listitem==0)
				{
					if(GetPlayerMoneyA(playerid) < COST_BAIKERIUGUN)
					{
						SendInfoMessage(playerid,"Jus neturite pakankamai pinigu !");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_BAIKERIUGUN);
					SendInfoMessage(playerid,"Nesaudyk nekaltu zmoniu.");
					GivePlayerWeaponEx(playerid,1,1); // kastetas
					GivePlayerWeaponEx(playerid,5,1); // beisbolke
					//GivePlayerWeaponEx(playerid,18,5); // molotovas
					GivePlayerWeaponEx(playerid,22,30); // pistule
					GivePlayerWeaponEx(playerid,25,20); // SG
					GivePlayerWeaponEx(playerid,33,10); // Rifle
					//GivePlayerWeaponEx(playerid,37,500); // Flame Thrower
					
					//GivePlayerWeaponEx(playerid,41,100); // Nitruha
				}
				else if(listitem==1)
				{
					if(GetPlayerMoneyA(playerid) < COST_BAIKERIUBOMBOS)
					{
						SendInfoMessage(playerid,"Jus neturite pakankamai pinigu !");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_BAIKERIUBOMBOS);
					DeletePlayerWeapon(playerid,39);
					GivePlayerWeaponEx(playerid,39,3); // Satelite
				}
				else if(listitem == 2)
					playerDB[playerid][virve]=true,SendInfoMessage(playerid,"Gavai virve!");

				ShowPlayerDialog(playerid,8252,DIALOG_STYLE_LIST,"Ginklai","Ginklai "#COST_BAIKERIUGUN"€\nBombos "#COST_BAIKERIUBOMBOS"€\nVirve","Gerai","Iseiti");
				return 1;
			}
		}
		if(dialogid==9535)
		{
			if(response) return 1;
			new querystring[512];
			//printf("1");
			GetPVarString(playerid,"Ataskaitos",querystring,512);
			new temp[128];
			//printf("2");
			format(temp,sizeof(temp),") ORDER BY `Data` DESC LIMIT %i,40",40*(GetPVarInt(playerid,"Ataskaitosnr")+1));
			//printf("1");
			SetPVarInt(playerid,"Ataskaitosnr",GetPVarInt(playerid,"Ataskaitosnr")+1);
			//printf("2");
			strcat(querystring,temp);
			//printf("1");
			//mysql_query(querystring);
			mysql_function_query(SQL, querystring, true, "SQL_Ataskaitos", "i", playerid);
			
		}
		if(dialogid==467)
		{
			if(response)
			{
				playerDB[playerid][wstyle]=DLItemID;
				new msg[128];
				format(msg,sizeof(msg),"Vaiksciojimo stilius: ~y~%s",inputtext);
				SendInfoMessage(playerid,msg);
			}
		}
		if(dialogid==1499) // full bagazine
		{
			if(response)
			{
				if(listitem == 0)
					return ShowBagazine(playerid);
				new Item=BagazinesItems[playerid][listitem-1];
				if(Item < 50)
				{
					if(GetPlayerWeapon(playerid) != Item)
						return SendInfoMessage(playerid,"~r~Privalote laikyti ta pati ginkla");
					playerDB[playerid][daiktas]=0;
				}
				else
				{
					playerDB[playerid][daiktas]=Item-49; // Item nuo 50 tai daiktas nuo 1
				}
				ShowPlayerDialog(playerid,1502,DIALOG_STYLE_INPUT,"Padeti","Iveskite skaiciu, kiek norite padeti.","Rinktis","Iseiti");
				
			}
			else ShowBagazine(playerid);
		}
		if(dialogid==1501)
		{
			if(response)
			{
				playerDB[playerid][daiktas]=listitem;
				ShowPlayerDialog(playerid,1502,DIALOG_STYLE_INPUT,"Padeti","Iveskite skaiciu, kiek norite padeti.","Rinktis","Iseiti");
				
			}
			else ShowBagazine(playerid);
		}
		
		if(dialogid==1502)
		{
			if(response)
			{
				new vehicleid = GetClosestVehicleid(playerid,10.0);
				new exas;
				new mid;
				if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
					return 0;
				if(!vehicleid || vehicleid == INVALID_VEHICLE_ID)
				{
					if(GetPlayerInterior(playerid) == 3)
					{
						mid=4;
						exas=playerid;
					}
					else return 0;
				}
				else
				{
					GetVehicleParamsEx(vehicleid,VehVars[0],VehVars[1],VehVars[2],VehVars[3],VehVars[4],VehVars[5],VehVars[6]);
					if(VehVars[5] != VEHICLE_PARAMS_ON) return 1;
					mid = GetPlayerFromCarlistID(vehicleid, exas);
					if(!mid) return 0;
				}
				if(mid != 4 && GetPVarInt(playerid,"PlayerBagazine") != mid)
					return 0;
				new kiek = strval(inputtext);
				if(!IsNumeric(inputtext) || !kiek) return ShowBagazine(playerid),SendInfoMessage(playerid,"Skaiciais!");
				// ShowPlayerDialog(playerid,1501,DIALOG_STYLE_LIST,"Padeti","Ginklas\nSeklos\nZole\nAmfetaminas\nLSD\nRatai\nPinigai","Rinktis","Iseiti");
				if(playerDB[playerid][daiktas] == 0)
				{
					new
							weaponid = GetPlayerWeapon(playerid),
							weaponidas,
							slot = GetWeaponsSlot(weaponid),
							kiekkulku = strval(inputtext),
							kiekturi;
					GetPlayerWeaponData(playerid,slot,weaponidas,kiekturi);
					if(weaponid != 22 && weaponid != 24 && weaponid != 25 && weaponid != 27 && weaponid != 29 && weaponid != 30 && weaponidas != 31 && weaponid != 33 && weaponid != 43 && weaponid != 34 && weaponid !=42) return SendInfoMessage(playerid,"Sio ginklo pasideti negali, nes jis yra darbinis, arba neturi kulku.");
					//if(weaponid < 16 || weaponid == 40 || weaponid > 43 || ((weaponid == 29 || weaponid == 24 || weaponid == 34) && playerDB[playerid][specialybe] >=80 && playerDB[playerid][specialybe] <= 84)) return SendInfoMessage(playerid,"~r~Sio ginklo padeti negalima!");
					if(kiekturi == -100 || kiekturi > 10000) return SendInfoMessage(playerid,"~r~Sio ginklo pasideti negali, nes jo kulkos neribotos!");
					
					if(kiekturi < kiekkulku) return SendInfoMessage(playerid,"~r~Tu tiek neturi!");
					

					if(GunData[playerid][slot][0] != weaponid)
					{
						AC_Kick(playerid,"Ginklai 3");
						return 1;
					}
					if(GunData[playerid][slot][1] < kiekturi)
					{
						AC_Kick(playerid,"Ginklai 4");
						return 1;
					}

					AddToBagazine(playerid,mid,weaponid,kiekkulku);
					

					GivePlayerWeaponEx(playerid,weaponid,-kiekkulku);
					/*
					new
						weponzai[13],
						ammozai[13];
						
					for(new i; i < 13; ++i)
					{
						GetPlayerWeaponData(playerid, i, weponzai[i], ammozai[i]);
						if(ammozai[i] > playerDB[playerid][ammok][weponzai[i]]) 
						{
							ammozai[i]=0;
							continue;
						}
						//ammozai[i] = ((ammozai[i] < 0) ? (-ammozai[i]) : (ammozai[i]));
						//if(ammozai[i] > playerDB[playerid][ammok][weponzai[i]]) ammozai[i]=playerDB[playerid][ammok][weponzai[i]];
						if(ammozai[i] == -100 && playerDB[playerid][ammok][weponzai[i]] != -100) ammozai[i]=playerDB[playerid][ammok][weponzai[i]];
						if(ammozai[i] > playerDB[playerid][ammok][weponzai[i]]) ammozai[i]=playerDB[playerid][ammok][weponzai[i]];
					}
					ResetPlayerWeapons(playerid);

					
					for(new i; i < 13; ++i)
					{
						if(weponzai[i] != weaponid)
						{
							GivePlayerWeaponEx(playerid, weponzai[i], ammozai[i]);
						}
						else
						{
							if(weponzai[i] && ammozai[i] > kiekkulku)
							{
								ammozai[i]-=kiekkulku;
								GivePlayerWeaponEx(playerid, weponzai[i], ammozai[i]);
							}
						}
					}
					*/
					ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
					SendInfoMessage(playerid,"Sekmingai pasidejai ginkla.");
					//UpdateWeaps(playerid,weaponid,-kiekkulku);
					
				}
				else if(playerDB[playerid][daiktas]==1)
				{
					if(kiek > playerDB[playerid][seklos]) return SendInfoMessage(playerid,"Tu tiek neturi");
					playerDB[playerid][seklos]-=kiek;
					AddToBagazine(playerid,mid,50,kiek);
				}
				else if(playerDB[playerid][daiktas]==2)
				{
					if(kiek > playerDB[playerid][zole]) return SendInfoMessage(playerid,"Tu tiek neturi");
					playerDB[playerid][zole]-=kiek;
					AddToBagazine(playerid,mid,51,kiek);
				}
				else if(playerDB[playerid][daiktas]==3)
				{
					if(kiek > playerDB[playerid][amfetaminas]) return SendInfoMessage(playerid,"Tu tiek neturi");
					playerDB[playerid][amfetaminas]-=kiek;
					AddToBagazine(playerid,mid,52,kiek);
				}	
				else if(playerDB[playerid][daiktas]==4)
				{
					if(kiek > playerDB[playerid][lsd]) return SendInfoMessage(playerid,"Tu tiek neturi");
					playerDB[playerid][lsd]-=kiek;
					AddToBagazine(playerid,mid,53,kiek);
				}	
				else if(playerDB[playerid][daiktas]==5)
				{
					if(kiek > playerDB[playerid][ratai]) return SendInfoMessage(playerid,"Tu tiek neturi");
					playerDB[playerid][ratai]-=kiek;
					AddToBagazine(playerid,mid,54,kiek);
				}				
				else if(playerDB[playerid][daiktas]==6)
				{
					if(kiek > playerDB[playerid][pinigai]) return SendInfoMessage(playerid,"Tu tiek neturi");
					if(GetPlayerScore(playerid) < 100)
						return SendInfoMessage(playerid,"Pinigus gali padeti nuo 100 xp");
					GivePlayerMoneyA(playerid,-kiek);
					AddToBagazine(playerid,mid,55,kiek);
				}
				else if(playerDB[playerid][daiktas]==7)
				{
					if(kiek > playerDB[playerid][masalas]) return SendInfoMessage(playerid,"Tu tiek neturi");
					playerDB[playerid][masalas]-=kiek;
					AddToBagazine(playerid,mid,56,kiek);
				}
				else if(playerDB[playerid][daiktas]==8)
				{
					if(kiek > playerDB[playerid][zuvis]) return SendInfoMessage(playerid,"Tu tiek neturi");
					playerDB[playerid][zuvis]-=kiek;
					AddToBagazine(playerid,mid,57,kiek);
				}
			}
			

			playerDB[playerid][daiktas]=0;
		}
		if(dialogid==1500) if(response)
		{
			new vehicleid = GetClosestVehicleid(playerid,10.0);
			if(!vehicleid || vehicleid == INVALID_VEHICLE_ID)
			{
				if(GetPlayerInterior(playerid)==3)
				{
					new row[128];
					format(row,sizeof(row),"SELECT Item,Count From Bagazine Where Vardas='%s' AND Masina=4",ReturnName(playerid));
					//mysql_query(row);
					mysql_function_query(SQL, row, true, "SQL_Bagazine", "iii", playerid,4,listitem);
				}
				else return 0;
			}
			GetVehicleParamsEx(vehicleid,VehVars[0],VehVars[1],VehVars[2],VehVars[3],VehVars[4],VehVars[5],VehVars[6]);
			if(VehVars[5] == VEHICLE_PARAMS_ON)
			{
				new exas;
				new mid = GetPlayerFromCarlistID(vehicleid, exas);
				if(exas != playerid) return SendInfoMessage(playerid,"Tai ne jusu automobilis!");
				if(!mid) return 0;
				new row[128];
				format(row,sizeof(row),"SELECT Item,Count From Bagazine Where Vardas='%s' AND Masina=%i",ReturnName(exas),mid);
				//mysql_query(row);
				mysql_function_query(SQL, row, true, "SQL_Bagazine", "iii", playerid,mid,listitem);
				SetPVarInt(playerid,"PlayerBagazine",mid);
			}
			return 1;
		}
		if(dialogid==1510)
		{
			if(response)
			{
				if(!IsNumeric(inputtext) || !strval(inputtext)) return ShowBagazine(playerid),SendInfoMessage(playerid,"Skaiciais!");
				new kiek = strval(inputtext);
				new vehicleid = GetClosestVehicleid(playerid,10.0);
				if(!vehicleid || vehicleid == INVALID_VEHICLE_ID)
				{
					if(GetPlayerInterior(playerid)==3)
					{
						new row[128];
						format(row,sizeof(row),"SELECT Item,Count From Bagazine Where Vardas='%s' AND Masina=4",ReturnName(playerid));
						//mysql_query(row);
						mysql_function_query(SQL, row, true, "SQL_Bagazine3", "iii", playerid,4,kiek);
					}
					else return 0;
				}
				GetVehicleParamsEx(vehicleid,VehVars[0],VehVars[1],VehVars[2],VehVars[3],VehVars[4],VehVars[5],VehVars[6]);
				if(VehVars[5] == VEHICLE_PARAMS_ON)
				{
					new exas;
					new mid = GetPlayerFromCarlistID(vehicleid, exas);
					if(!mid) return 0;
					new row[128];
					format(row,sizeof(row),"SELECT Item,Count From Bagazine Where Vardas='%s' AND Masina=%i",ReturnName(playerid),mid);
					//mysql_query(row);
					mysql_function_query(SQL, row, true, "SQL_Bagazine3", "iii", playerid,mid,kiek);

					
				}
			}
			else ShowBagazine(playerid);
			return 1;
		}
		if(dialogid==7531){ ServerStats(playerid,response); return 1;}
		if(dialogid==9654) { if(response) LeaveJob(playerid,1); return 1;}
		if(dialogid==2897)
		{
			strcpy(g_RadioURL,inputtext,512);
			g_RadioON=true;

			/*foreach(Player,id) FIX_DIS
			{
				if(Audio_IsClientConnected(id))
				{
					Audio_Stop(id,playerDB[id][klausoisadmin]);
					playerDB[id][klausoisadmin] = Audio_PlayStreamed(id,g_RadioURL,false,false,true);
					Audio_Set3DPosition(id,playerDB[id][klausoisadmin],g_RadioCord[0],g_RadioCord[1],g_RadioCord[2],100);
				}
			}*/
		}
		if(dialogid==9757)
		{
			if(response)
			{
				if(IsInBiz(playerid))
				{
					if(listitem==0)
					{
						new i = GetPlayerVirtualWorld(playerid) - MAX_HOUSES*2;
						BusinessInfo[i][bRadio]=0;
						SendInfoMessage(playerid,"~r~Isjungei~w~ radija!");
						foreach(Player, id)
						{
							if(i+MAX_HOUSES*2==GetPlayerVirtualWorld(id))
							{
								StopAudioStreamForPlayer(id);
								/*Audio_Stop(id,playerDB[id][radija]);
								playerDB[id][radija] = -1;
								playerDB[id][klausosi] = 0;	*/
							}						
						}
						return 1;
					}
					else
					{
						new i = GetPlayerVirtualWorld(playerid) - MAX_HOUSES*2;
						BusinessInfo[i][bRadio]=listitem;
						SendInfoMessage(playerid,"~g~Ijungei~w~ radija!");
						foreach(Player, id)
						{
							if(i+MAX_HOUSES*2==GetPlayerVirtualWorld(id))
							{
								StopAudioStreamForPlayer(id);
								PlayAudioStreamForPlayer(id,RADIO_PLUGIN[BusinessInfo[i][bRadio]-1][RADIO_URL],BusinessInfo[i][bExitX],BusinessInfo[i][bExitY],BusinessInfo[i][bExitZ],200.0,true);
								
								/*
								playerDB[id][radija] = Audio_PlayStreamed(id,RADIO_PLUGIN[BusinessInfo[i][bRadio]-1][RADIO_URL],false,false,false); // zip
								playerDB[id][stotis] = BusinessInfo[i][bRadio]-1;
								playerDB[id][klausosi] = 0;		
								Audio_Set3DPosition(id,playerDB[id][radija],BusinessInfo[i][bExitX],BusinessInfo[i][bExitY],BusinessInfo[i][bExitZ],200);
								*/
							}						
						}
						return 1;
					}
				}
			}
		}
		if(dialogid==9758)
		{
			if(response)
			{
				if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");
				if(listitem==0)
				{
					new i = GetPlayerHouseID(playerid);
					hInfo[i][hRadio]=0;
					SendInfoMessage(playerid,"~r~Isjungei~w~ radija!");
					foreach(Player, id)
					{
						if(i==GetPlayerHouseID(id))
						{
							StopAudioStreamForPlayer(id);
							/*Audio_Stop(id,playerDB[id][radija]);
							playerDB[id][radija] = -1;
							playerDB[id][klausosi] = 0;	*/	
						}
					}
					new query[256];
					format(query,sizeof(query),"UPDATE `Namai` SET `Radio`=%i WHERE `ID`=%i",hInfo[i][hRadio],i);
					mysql_query(query);
					return 1;
				}
				else
				{
					new i = GetPlayerHouseID(playerid);
					hInfo[i][hRadio]=listitem;
					SendInfoMessage(playerid,"~g~Ijungei~w~ radija!");
					foreach(Player, id)
					{
						if(i==GetPlayerHouseID(id))
						{
							StopAudioStreamForPlayer(id);
							if(hInfo[i][polyId] == -1)
								PlayAudioStreamForPlayer(id,RADIO_PLUGIN[hInfo[i][hRadio]-1][RADIO_URL],Inter[ hInfo[i][vidus] ][ IntX ],Inter[ hInfo[i][vidus] ][ IntY ],Inter[ hInfo[i][vidus] ][ IntZ ],200.0,true);
							else
								PlayAudioStreamForPlayer(id,RADIO_PLUGIN[hInfo[i][hRadio]-1][RADIO_URL],hInfo[i][iconx],hInfo[i][icony],hInfo[i][iconz],50.0,true);
							/*Audio_Stop(id,playerDB[id][radija]);
							playerDB[id][radija] = Audio_PlayStreamed(id,RADIO_PLUGIN[hInfo[i][hRadio]-1][RADIO_URL],false,false,false); // zip
							playerDB[id][stotis] = hInfo[i][hRadio]-1;
							playerDB[id][klausosi] = 0;		
							Audio_Set3DPosition(id,playerDB[id][radija],Inter[ hInfo[i][vidus] ][ IntX ],Inter[ hInfo[i][vidus] ][ IntY ],Inter[ hInfo[i][vidus] ][ IntZ ],200);
							*/
						}
					}
					new query[256];
					format(query,sizeof(query),"UPDATE `Namai` SET `Radio`=%i WHERE `ID`=%i",hInfo[i][hRadio],i);
					mysql_query(query);
					return 1;
				}
			}
		}
		if(dialogid==9756)
		{
			if(response)
			{
				SendInfoMessage(playerid,"~r~Garsa gali nustatyti GTA nustatymuose!");
				/*
				if(listitem == 0)
				{
					foreach(Player, i)
					{
						if(playerDB[i][klausosi] == GetPlayerVehicleID(playerid) || GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid) )
						{
							Audio_SetVolume(i,playerDB[i][radija],0);
						}
					}
					return 1;
				}
				if(listitem == 1)
				{
					foreach(Player, i)
					{
						if(playerDB[i][klausosi] == GetPlayerVehicleID(playerid) || GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid) )
						{
							Audio_SetVolume(i,playerDB[i][radija],25);
						}
					}
					return 1;
				}
				if(listitem == 2)
				{
					foreach(Player, i)
					{
						if(playerDB[i][klausosi] == GetPlayerVehicleID(playerid) || GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid) )
						{
							Audio_SetVolume(i,playerDB[i][radija],50);
						}
					}
					return 1;
				}
				if(listitem == 3)
				{
					foreach(Player, i)
					{
						if(playerDB[i][klausosi] == GetPlayerVehicleID(playerid) || GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid) )
						{
							Audio_SetVolume(i,playerDB[i][radija],75);
						}
					}
					return 1;
				}
				if(listitem == 4)
				{
					foreach(Player, i)
					{
						if(playerDB[i][klausosi] == GetPlayerVehicleID(playerid) || GetPlayerVehicleID(i) == GetPlayerVehicleID(playerid) )
						{
							Audio_SetVolume(i,playerDB[i][radija],100);
						}
					}
					return 1;
				}
				*/
			}
			else
			{
				RadioList(playerid,false);
			}

		}
		if(dialogid==9755)
		{
			if(response)
			{
				if(listitem == 0)
				{
					new veh = GetPlayerVehicleID(playerid);
					if(!veh) return 1;
					VehicleRadio[veh]=0;
					foreach(Player,i)
					{
						if(GetPlayerVehicleID(i) == veh && !playerDB[i][klausoimtuvo]) {
							playerDB[i][stotis]=0;
							
							playerDB[i][klausosi] = 0;
							StopAudioStreamForPlayer(i);
						}
						/*
						if(playerDB[i][klausosi] == veh || GetPlayerVehicleID(i) == veh )
						{
							StopAudioStreamForPlayer(i);
							
							playerDB[i][stotis]=0;
							
							playerDB[i][klausosi] = 0;
						}*/
					}
					return 1;
				}
				if(listitem == 1)
				{
					ShowPlayerDialog(playerid,9756,DIALOG_STYLE_LIST,"Garsas","Mute\nTyliai\nVidutiniskai\nGarsiai\nLabai garsiai","Gerai","Atsaukti");
					return 1;
				}
				if(listitem >= 2)
				{
					listitem-=2;

					new veh = GetPlayerVehicleID(playerid);
					if(!veh) return 1;
					VehicleRadio[veh] = listitem+1;
					foreach(Player, i)
					{
						if(GetPlayerVehicleID(i) == veh )
						{
							/*
							Audio_Stop(i,playerDB[i][radija]);
							playerDB[i][radija] = Audio_PlayStreamed(i,RADIO_PLUGIN[listitem][RADIO_URL],false,false,false); // zip
							*/
							playerDB[i][klausoimtuvo] = 0;
							StopAudioStreamForPlayer(i);
							PlayAudioStreamForPlayer(i,RADIO_PLUGIN[listitem][RADIO_URL]);
							playerDB[i][stotis] = listitem+1;
							playerDB[i][klausosi] = veh;
						}
					}
					return 1;
				}
			}

		}
		if(dialogid==9750)
		{
			if(response)
			{
				if(listitem == 0)
				{
					StopAudioStreamForPlayer(playerid);
					playerDB[playerid][klausoimtuvo] = 0;
					/*
					Audio_Stop(playerid,playerDB[playerid][radija]);
					playerDB[playerid][radija]=-1;
					*/
					return 1;
				}
				if(listitem == 1)
				{
					ShowPlayerDialog(playerid,9751,DIALOG_STYLE_LIST,"Garsas","Mute\nTyliai\nVidutiniskai\nGarsiai\nLabai garsiai","Gerai","Atsaukti");
					return 1;
				}
				if(listitem >= 2)
				{
					listitem-=2;
					/*
					Audio_Stop(playerid,playerDB[playerid][radija]);
					playerDB[playerid][radija] = Audio_PlayStreamed(playerid,RADIO_PLUGIN[listitem][RADIO_URL],false,false,false); // zip
					*/
					StopAudioStreamForPlayer(playerid);
					PlayAudioStreamForPlayer(playerid,RADIO_PLUGIN[listitem][RADIO_URL]);
					playerDB[playerid][stotis] = listitem+1;
					playerDB[playerid][klausoimtuvo] = 1;
					return 1;
				}
			}
		}

		if(dialogid==9751)
		{
			if(response)
			{
				SendInfoMessage(playerid,"~r~Garsa gali nustatyti GTA nustatymuose!");
				/*
				if(listitem == 0)
				{
					Audio_SetVolume(playerid,playerDB[playerid][radija],0);
					return 1;
				}
				if(listitem == 1)
				{
					Audio_SetVolume(playerid,playerDB[playerid][radija],25);
					return 1;
				}
				if(listitem == 2)
				{
					Audio_SetVolume(playerid,playerDB[playerid][radija],50);
					return 1;
				}
				if(listitem == 3)
				{
					Audio_SetVolume(playerid,playerDB[playerid][radija],75);
					return 1;
				}
				if(listitem == 4)
				{
					Audio_SetVolume(playerid,playerDB[playerid][radija],100);
					return 1;
				}
				*/
			}
			else
			{
				//ShowPlayerDialog(playerid,9750,DIALOG_STYLE_LIST,"Radijos","Stabdyti\nKeisti garsa\nZip FM\nM-1\nEuropean Hit Radio\nPower Hit Radio\nHot FM\nJpa FM\nRadio Centras","Rinktis","Isjungti");
				RadioList(playerid,true);
			}

		}
		if(dialogid==499)
		{
			if(response)
			{
				if(listitem==0)
				{
					if(GetPlayerMoneyA(playerid) < COST_TRUMPAS_DILDO) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					GivePlayerMoneyA(playerid, -COST_TRUMPAS_DILDO);
					BusinessMoney(COST_TRUMPAS_DILDO);
					ActorServe(playerid);

					ProcessAchievement(playerid, 84);
					GivePlayerWeaponEx(playerid, 13, 1);
				}
				if(listitem==1)
				{
					if(GetPlayerMoneyA(playerid) < COST_TRUMPAS_VIBRATORIUS) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					GivePlayerMoneyA(playerid, -COST_TRUMPAS_VIBRATORIUS);
					ActorServe(playerid);
					BusinessMoney(COST_TRUMPAS_VIBRATORIUS);
					GivePlayerWeaponEx(playerid, 11, 1);
					ProcessAchievement(playerid, 84);
				}
				if(listitem==2)
				{
					if(GetPlayerMoneyA(playerid) < 2500) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					GivePlayerMoneyA(playerid, -COST_ILGAS_DILDO);
					ActorServe(playerid); BusinessMoney(COST_ILGAS_DILDO);
					ProcessAchievement(playerid, 84);
					GivePlayerWeaponEx(playerid, 10, 1);
				}
				if(listitem==3)
				{
					if(GetPlayerMoneyA(playerid) < COST_ILGAS_VIBRATORIUS) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					GivePlayerMoneyA(playerid, -COST_ILGAS_VIBRATORIUS);
					ActorServe(playerid); BusinessMoney(COST_ILGAS_VIBRATORIUS);
					ProcessAchievement(playerid, 84);
					GivePlayerWeaponEx(playerid, 12, 1);
				}
				SendInfoMessage(playerid,"Gero naudojimo!");
			}
		}
		if(dialogid==836)
		{
			if(!playerDB[playerid][ant] && !playerDB[playerid][suristas]) TogglePlayerControllable(playerid,true);
			new v = GetPlayerVehicleID(playerid);
			if(!v) return 0;
			new playeridx;
			if(GetPlayerFromCarlistID(v,playeridx) || IsVagiuCar(v) || IsVairavimoMokyklosCar(v)) return SendInfoMessage(playerid,"Cia taisome tik DARBINIUS automobilius.");
			if(response)
			{
				if(listitem==0)
				{
					if(GetPlayerScore(playerid) > 200)
					{
						if(GetPlayerMoneyA(playerid) < COST_FIXAS)
						{
							if(playerDB[playerid][banke] < COST_FIXAS)
								return SendInfoMessage(playerid,"Truksta pinigu!");
							else
							{
								SendInfoMessage(playerid,"Sumokejote kortele!");
								playerDB[playerid][banke]-=COST_FIXAS;
							}
						}
						else 
						{
							/*if(COST_FIXAS ! 0)
							{
								SendInfoMessage(playerid,"Sumokejote grynais!");
								GivePlayerMoneyA(playerid,-COST_FIXAS);
							}*/
						}
					}
					RepairVehicle(v);
					if(GetVehicleModel(v) == 432)
						SetVehicleHealth(v,3000.0);
					else if(GetVehicleModel(v) == 428 || GetVehicleModel(v) == 427)
						SetVehicleHealth(v, 2000.0);
					//SetVehicleHealth(v,1000);
					if(vehicleDB[v][gas] < 40.0)
						vehicleDB[v][gas]=40.0;
					if(vehicleDB[v][energy] < 50.0)
						vehicleDB[v][energy]=50.0;
				}
				else
				{
					Stop(playerid);
					DestroyOldCar(playerid);
				}
			}
			
		}
		if(dialogid==498)
		{
			if(response)
			{
				if(listitem==0)
				{
					if(GetPlayerMoneyA(playerid) < COST_STAR_DREAM) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					GivePlayerMoneyA(playerid,-COST_STAR_DREAM);
					ActorServe(playerid); BusinessMoney(COST_STAR_DREAM);
				}
				if(listitem==1)
				{
					if(GetPlayerMoneyA(playerid) < COST_DYNAMITE) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					GivePlayerMoneyA(playerid,-COST_DYNAMITE);
					ActorServe(playerid); BusinessMoney(COST_DYNAMITE);
				}
				if(listitem==2)
				{
					if(GetPlayerMoneyA(playerid) < COST_SATURN) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					GivePlayerMoneyA(playerid,-COST_SATURN);
					ActorServe(playerid); BusinessMoney(COST_SATURN);
				}
				if(listitem==3)
				{
					if(GetPlayerMoneyA(playerid) < COST_THUNDER) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					GivePlayerMoneyA(playerid,-COST_THUNDER);
					ActorServe(playerid); BusinessMoney(COST_THUNDER);
				}
				if(listitem==4)
				{
					if(GetPlayerMoneyA(playerid) < COST_RISING) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					GivePlayerMoneyA(playerid,-COST_RISING);
					ActorServe(playerid); BusinessMoney(COST_RISING);
				}
				if(listitem==5)
				{
					if(GetPlayerMoneyA(playerid) < COST_OCEAN) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					GivePlayerMoneyA(playerid,-COST_OCEAN);
					ActorServe(playerid); BusinessMoney(COST_OCEAN);
				}
				if(listitem==6)
				{
					if(GetPlayerMoneyA(playerid) < COST_VIXEN) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					GivePlayerMoneyA(playerid,-COST_VIXEN);
					ActorServe(playerid); BusinessMoney(COST_VIXEN);
				}
				if(listitem==7)
				{
					if(GetPlayerMoneyA(playerid) < COST_MIDNIGHT) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					GivePlayerMoneyA(playerid,-COST_MIDNIGHT);
					ActorServe(playerid); BusinessMoney(COST_MIDNIGHT);
				}

				SendInfoMessage(playerid,"Nusipirkai fejerverka! Ji panaudoti gali parases /fw");
				ShowPlayerDialog(playerid, 498, DIALOG_STYLE_TABLIST, "Fejerverkai","Star Dream\t{33FF33}"#COST_STAR_DREAM"€\n{FFFFFF}Dinamitas\t{33FF33}"#COST_DYNAMITE"€\n{FFFFFF}Raketa Saturn\t{33FF33}"#COST_SATURN"€\n{FFFFFF}Raketa Thunder\t{33FF33}"#COST_THUNDER"€\n{FFFFFF}Fontanas Rising Sun\t{33FF33}"#COST_RISING"€\n{FFFFFF}Fontanas Ocean Wave\t{33FF33}"#COST_OCEAN"€\n{FFFFFF}Volkanas Vixen\t{33FF33}"#COST_VIXEN"€\n{FFFFFF}Baterija Midnight Episode\t{33FF33}"#COST_MIDNIGHT"€", "Pirkti", "Nepirkti");
				playerDB[playerid][fejerverkai][listitem]=true;
				
				return 1;
			}
		}
	//	ShowPlayerDialog(playerid, 9623, DIALOG_STYLE_LIST, "Regitra", "{FFFFFF}Paprastas numeris\t{33FF33} 1000€\n{FFFFFF}Vardinis numeris {33FF33}10000€", "Pirkti", "Nepirkti");
		if(dialogid==9999)
		{
			if(response)
			{
				SetPlayerCheckpoint(playerid,1604.9871,-1468.1709,13.5717,10);
				SendInfoMessage(playerid,"Vieta kurioje galite uzregistruoti automobili rodoma radare.");
				return 1;
			}
		}
		if(dialogid==9998)
		{
			if(response)
			{
				new kiekRaise = 0;
				if(IsNumeric(inputtext))
				{
					kiekRaise = strval(inputtext);
				}
				else
				{
					kiekRaise = GetPokerNumber(inputtext);
					if(kiekRaise == 0)
						 return SendInfoMessage(playerid,"Skaiciais!");
				}
				if(!Raising(playerid,kiekRaise)) 
					return SendInfoMessage(playerid,"Zaidimas nerastas!");
			}
		}
		if(dialogid==6431)
		{
			if(response) return 1;
			else
			{
				mysql_function_query(SQL, "SELECT 0 FROM `BANS`", true, "SQL_Laikrastis", "i", playerid);


			}
			return 1;
		}
		
		if(dialogid==6432)
		{
			if(response)
			{
				ShowPlayerDialog(playerid,6431,DIALOG_STYLE_MSGBOX,"LSG Laikrastis","	  	{FF9900}LSG Laikrastis\n    {FFFFFF}Pirmas psl.: {00FF00}Paskutiniai banai\n    {FFFFFF}Antras psl.: {00FF00}Gaudomi policijos\n    {FFFFFF}Trecias psl: {00FF00}Rekordas\n    {FFFFFF}Ketvirtas psl: {00FF00}Statistika","Uzversti","Kitas psl.");
			}
			else
			{
				new string[1024];
				format(string,sizeof(string),"	   {FF9900}LSG Laikrastis\n    {FFFFFF}Sunkus nusikalteliai:\n");
				foreach(Player,i)
				{
					if(GetPlayerWantedLevel(i) > 2)
					{
						format(string,sizeof(string),"%s\no %s(%i star)",string,ReturnName(i),GetPlayerWantedLevel(i));
					}
				}
				ShowPlayerDialog(playerid,6433,DIALOG_STYLE_MSGBOX,"LSG Laikrastis",string,"Praeitas psl.","Kitas psl.");
			}
			return 1;
		}
		if(dialogid==6433)
		{
			if(response)
			{
				mysql_function_query(SQL, "SELECT 0 FROM `BANS`", true, "SQL_Laikrastis", "i", playerid);
			}
			else
			{
				//mysql_query("SELECT * FROM `Rekordas` ORDER BY `Rekordas` DESC LIMIT 1");
				mysql_function_query(SQL, "SELECT * FROM `Rekordas` ORDER BY `Rekordas` DESC LIMIT 1", true, "SQL_Laikrastis3", "i", playerid);

				
			}
			return 1;
		}
		if(dialogid==6434)
		{
			if(response)
			{
				new string[1024],skaic;
				format(string,sizeof(string),"	   {FF9900}LSG Laikrastis\n    {FFFFFF}Sunkus nusikalteliai:\n");
				foreach(Player,i)
				{
					skaic++;
					if(skaic >=10) break;
					if(GetPlayerWantedLevel(i) > 2)
					{
						format(string,sizeof(string),"%s\no %s(%i star)",string,ReturnName(i),GetPlayerWantedLevel(i));
					}
				}
				ShowPlayerDialog(playerid,6433,DIALOG_STYLE_MSGBOX,"LSG Laikrastis",string,"Praeitas psl.","Kitas psl.");
			}
			else
			{
				mysql_function_query(SQL, "SELECT COUNT(Name) FROM `Account` UNION SELECT COUNT(Vardas) FROM `BANS` UNION SELECT COUNT(Name) FROM `Account` WHERE `Namu`=1 UNION ALL SELECT COUNT(Name) FROM `Account` WHERE `Namu`=2 UNION ALL SELECT COUNT(Owner) FROM `Bizniai` UNION ALL SELECT COUNT(Owner) FROM `Bizniai` WHERE `Owned`=1  UNION ALL SELECT COUNT(Owner) FROM `Cars` WHERE `AH_Typ`!= -1 AND `AH2_Typ` != -1 AND `AH3_Typ` != -1", true, "SQL_Laikrastis4", "i", playerid);
			}
			return 1;
		}
		if(dialogid==6435)
		{
			if(response)
			{
				mysql_function_query(SQL, "SELECT * FROM `Rekordas` ORDER BY `Rekordas` DESC LIMIT 1", true, "SQL_Laikrastis3", "i", playerid);

			}
			else
			{
				mysql_function_query(SQL, "SELECT Atnaujinimas FROM `Updates` ORDER BY `Versija` DESC LIMIT 1;", true, "SQL_Laikrastis5", "i", playerid);

				return 1;
			}
		}
		if(dialogid==6436)
		{
			if(response)
			{
				mysql_function_query(SQL, "SELECT COUNT(Name) FROM `Account` UNION SELECT COUNT(Vardas) FROM `BANS` UNION SELECT COUNT(Name) FROM `Account` WHERE `Namu`=1 UNION ALL SELECT COUNT(Name) FROM `Account` WHERE `Namu`=2 UNION ALL SELECT COUNT(Owner) FROM `Bizniai` UNION ALL SELECT COUNT(Owner) FROM `Bizniai` WHERE `Owned`=1  UNION ALL SELECT COUNT(Owner) FROM `Cars` WHERE `AH_Typ`!= -1 AND `AH2_Typ` != -1 AND `AH3_Typ` != -1", true, "SQL_Laikrastis4", "i", playerid);
			}
			return 1;
		}
		if(dialogid==5379)
		{
			if(response)
			{
				new did = GetPlayerVirtualWorld(playerid)-(MAX_HOUSES*2+MAX_BUSINESSES);
				if(did < 0) return 0;
				if(Daugiabuciai[did][dLiftU]) return SendInfoMessage(playerid,"~r~Liftas jau naudojamas!");
				new aukstas = -1;
				for(new i;i<sizeof(VLiftoDurys);i++)
				{
					if(IsPlayerInRangeOfPointEx(3.5,playerid,VLiftoDurys[i][0],VLiftoDurys[i][1],VLiftoDurys[i][2])) aukstas = i;
				}
				if(Daugiabuciai[did][dLift] != aukstas) return SendInfoMessage(playerid,"~r~Liftas jau nuvaziavo i kita auksta!");
				if(aukstas == listitem) return MenuLift(playerid,did,aukstas);
				Daugiabuciai[did][dLiftU]=true;
				_PlayerTeleporting[playerid]=5;
				new vari = abs(aukstas-listitem)*20;
				FadeColorForPlayer(playerid,0,0,0,0,_TELEPORTFADECOLORR,_TELEPORTFADECOLORG,_TELEPORTFADECOLORB,_TELEPORTFADECOLORA,vari,10);
				SetTimerEx("FixLiftas",(vari+1)*_UPDATERATE,false,"i",did);
				Daugiabuciai[did][dLift]=listitem;
				TogglePlayerControllable(playerid,false);
			}
		}
		if(dialogid==8582)
		{
			if(response)
			{
				LoadPlayerKelione(playerid, listitem, /*deleting=*/ 0);
				/*new file[128];
				format(file,sizeof file,"Keliones/%i.txt",listitem);
				if(!fexist(file)) return 1;
				if(LoadAutokluboRace(file) == 0) return SendClientMessage(playerid,COLOR,"ERROR");
				new Pranesimas[128];
				format(Pranesimas,sizeof(Pranesimas), "[racija] Operatore: Direktorius visus kviecia prisijungti prie keliones: %s",Keliones[KelionesPavadinimas]);
				SendMessageToKlubai(0xFFFFFF30,Pranesimas);
				SendMessageToKlubai(0xFFFFFF30,"[racija] Operatore: Tai padarysite parase /prisijungti");
				Keliones[Ijungta]=true;
				Keliones[Kuriama]=false;
				Keliones[paskutinisCP]=false;
				Keliones[Dalyviai]=0;
				Keliones[Atlygis]=0;
				SendInfoMessage(playerid,"Noredami isjungti kelione rasykite /kelione");*/
				return 1;
			}
		}
		if(dialogid==8583)
		{
			if(response)
			{
				LoadPlayerKelione(playerid, listitem, /* deleting= */ 1);
				return 1;
			}
		}
		if(dialogid==8543)
		{
			if(response)
			{
				if(GetPlace(playerid) != PLACE_BIZ) return 1;
				new vw = GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2;
				if(listitem == 3) listitem+=random(2);
				//ShowPlayerDialog(playerid,8543,DIALOG_STYLE_LIST,"Banko operacijos","Kasa 1: Moketi algas\nKasa 2: Pervedimai\nKasa 3: Pasiimti kortele\nKasa 4,5: Pasiimti/Padeti pinigus","Gerai","Atsaukti");
				/*new 
					biggest_numb = BankuSystem[vw][listitem];
				foreach(Player, i)
				{
					if(i != playerid &&GetPlayerVirtualWorld(i) == vw && playerDB[i][cekis])
					{
						if(playerDB[i][cekis] <((listitem*100)+100) && playerDB[i][cekis] >(listitem*100))
						{
							if(playerDB[i][cekis] > biggest_numb)
								biggest_numb=playerDB[i][cekis];
						}
					}
				}*/
				if(AddToBankArray(playerid,vw,listitem)==0)
				{
					new msg[128];
					format(msg,sizeof(msg),"~y~Kasa ~r~%i ~n~~y~Numeris eileje ~r~%i",listitem+1,playerDB[playerid][cekis]);
					GameTextForPlayer(playerid,msg,12000,1);
					return 1;
				}
				playerDB[playerid][cekis]=GetCekioNr(vw,listitem);
				/*biggest_numb++;
				if(biggest_numb >= (100+(listitem*100))) biggest_numb=(1+(listitem*100)); 
				playerDB[playerid][cekis] = biggest_numb;*/
				new msg[128];
				format(msg,sizeof(msg),"~y~Kasa ~r~%i ~n~~y~Numeris eileje ~r~%i",listitem+1,playerDB[playerid][cekis]);
				GameTextForPlayer(playerid,msg,12000,1);
			}
			return 1;
		}
		if(dialogid==623)
		{
			if(response)
			{
				new bauda = GetPlayerWantedLevel(playerid)*800;
				if(!bauda) return 1;
				if(GetPlayerMoneyA(playerid) < bauda) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
				Pelnas(-1,79,bauda/2);//pelnas[79]+=(bauda/2);
				SetPlayerWantedLevel(playerid, 0);
				SendInfoMessage(playerid,"Susimokejote bauda!");
				GivePlayerMoneyA(playerid, - bauda);
				return 1;
			}
			return 1;
		}
		if(dialogid==7474)
		{
			SetPlayerKVS(playerid,"AutoSaved","accepted");
		}
		if(dialogid==7475)
		{
			// DIALOGID_NOOP
			return 1;
		}
		if(dialogid==9534)
		{
			if(response)
			{
				if(GetPlace(playerid) != PLACE_BIZ)
					return 1;
				if(GetPlayerMoneyA(playerid) >= COST_SAVE)
				{
					BusinessMoney(COST_SAVE);
					SendInfoMessage(playerid,"Sumokejote grynais!");
					GivePlayerMoneyA(playerid, -COST_SAVE);
					SavePlayerData(playerid,false);
					ProcessAchievement(playerid, 129);
					return 1;
				}
				else
				{
					if(playerDB[playerid][banke] >= COST_SAVE)
					{
						BusinessMoney(COST_SAVE);
						SendInfoMessage(playerid,"Sumokejote kortele!");
						playerDB[playerid][banke]-=COST_SAVE;
						SavePlayerData(playerid,false);
						ProcessAchievement(playerid, 129);
						return 1;
					}
					SendInfoMessage(playerid,"~r~Neturi pinigu! :(");
					return 1;
				}
			}
		}
		if(dialogid==7563)
		{
			if(response)
			{
				IsmoketiAlga(playerid, listitem);
				return 1;
			}
			else
			{
				//playerDB[playerid][cekis]=0;
				SendInfoMessage(playerid,"Geros dienos!");
				return 1;
			}// ids:605,616,410,610,610
		}
		if(dialogid==339)
		{
			if(response)
			{
				switch(DLItemID)
				{
					case PAN_AKAUNTAS: ShowPlayerDialog(playerid,340,DIALOG_STYLE_LIST,"Akauntas","Keisti slaptaþodá","Gerai","Atgal");
					case PAN_INVENTORIUS: cmd_i(playerid,"");
					case PAN_VEIKSMAI: cmd_veiksmai(playerid,"");
					case PAN_KREDITAI: cmd_kreditai(playerid,""); 
					case PAN_KOVOS: cmd_kova(playerid,"");
					case PAN_STILIAI: cmd_stiliai(playerid,"");
					case PAN_NUSTATYMAI:
					{
						new money[1536];
						format(money,sizeof(money),"VVP greitieji klaviðai [%s]\nGaujos pokalbiai [%s]\nVIP skelbimai [%s]\nVIP pokalbiai [%s]\nÞaidëjø vardai [%s]\nSpidometras [%s]\nAnimacijos tekstas [%s]\nAlkio rodiklis [%s]\nLietuviðkø raidþiø konvertavimas [%s]\nPataikymo garsas [%s]\nMonetos pasiûlymai [%s]",
						((!BitFlag_Get(PConfig[playerid],PCFG_SPARTIEJI)) ? ("{FF0033}Iðjungti{FFFFFF}"):("{33FF00}Ájungti{FFFFFF}")),
						((!BitFlag_Get(PConfig[playerid],PCFG_SHOWGCHAT)) ? ("{FF0033}Iðjungti{FFFFFF}"):("{33FF00}Ájungti{FFFFFF}")),
						((!BitFlag_Get(PConfig[playerid],PCFG_SHOWVCHAT)) ? ("{FF0033}Iðjungti{FFFFFF}"):("{33FF00}Ájungti{FFFFFF}")),
						((!BitFlag_Get(PConfig[playerid],PCFG_SHOWVIPCHAT)) ? ("{FF0033}Iðjungti{FFFFFF}"):("{33FF00}Ájungti{FFFFFF}")),
						((!BitFlag_Get(PConfig[playerid],PCFG_SHOWNAMES)) ? ("{FF0033}Iðjungti{FFFFFF}"):("{33FF00}Ájungti{FFFFFF}")),
						((!BitFlag_Get(PConfig[playerid],PCFG_SHOWSPEEDO)) ? ("{FF0033}Iðjungti{FFFFFF}"):("{33FF00}Ájungti{FFFFFF}")),
						((!BitFlag_Get(PConfig[playerid],PCFG_SHOWANIMATIONS)) ? ("{FF0033}Iðjungti{FFFFFF}"):("{33FF00}Ájungti{FFFFFF}")),
						((!BitFlag_Get(PConfig[playerid],PCFG_SHOWALKIS)) ? ("{FF0033}Iðjungtas{FFFFFF}"):("{33FF00}Ájungtas{FFFFFF}")),
						((!BitFlag_Get(PConfig[playerid],PCFG_RAIDES)) ? ("{FF0033}Iðjungtas{FFFFFF}"):("{33FF00}Ájungtas{FFFFFF}")),
						((!BitFlag_Get(PConfig[playerid],PCFG_HITSOUND)) ? ("{FF0033}Iðjungtas{FFFFFF}"):("{33FF00}Ájungtas{FFFFFF}")),
						((!BitFlag_Get(PConfig[playerid],PCFG_MONETA)) ? ("{FF0033}Iðjungti{FFFFFF}"):("{33FF00}Ájungti{FFFFFF}"))
						);
						if(playerDB[playerid][admin])
							format(money,sizeof(money),"%s\nAdministratoriø pokalbiai [%s]",money,((!BitFlag_Get(PConfig[playerid],PCFG_SHOWACHAT)) ? ("{FF0033}Iðjungti{FFFFFF}"):("{33FF00}Ájungti{FFFFFF}")));
						ShowPlayerDialog(playerid,350,DIALOG_STYLE_LIST,"Nustatymai",money,"Gerai","Atgal");
					}
					case PAN_APANELE:
					{
						new query[128];
						format(query,sizeof(query),"SELECT variable from Config where value='%s'",ReturnName(playerid));
						mysql_function_query(SQL, query, true, "SQL_Apanele", "i", playerid);
					}
					case PAN_ATASKAITOS:
					{
						Ataskaita(playerid,"Dave star","Isteisino");
					}
					case PAN_ELITINIAI:
					{
						ShowTeisesaugaElitiniai(playerid);
					}
					case PAN_ELPASTAS:
					{
						
					}
				}
			}
		}
		if(dialogid==341)
		{
			if(response)
			{
				switch(DLItemID)
				{
					case 0: Ataskaita(playerid,"Pavoge Masina","Pridave Masina");
					case 1: Ataskaita(playerid,"Emigravo");
					case 2: Ataskaita(playerid,"Pass Keitimas");
					case 3: Ataskaita(playerid,"Nupyzdino is afondo","Padejo i afonda");
					case 4: Ataskaita(playerid,"Nusipirko nama","Nusipirko nama is");
					case 5: Ataskaita(playerid,"Jailino","Nukilino");
					case 6: Ataskaita(playerid,"Atsibanino","Uzbanino","Iskickino");
					case 7: Ataskaita(playerid,"Nusipirko versla is","Nusipirko versla");
					case 8: 
					{
						for(new i;i<MAX_PLAYERS;i++) if(IsPlayerConnected(i) && IsPlayerNPC(i)) return SendClientMessage(playerid,RED," * Botas jau yra, idësim á busikà!"),PutPlayerInVehicle(i,Busikas,0);
						ConnectNPC("Bus_Driver","mat_test");
						SendClientMessage(playerid,GREEN," * Botas sëkmingai prijungtas.");
						//1911.81774902,-1408.98840332,4166.76562500
					}
					case 9: Ataskaita(playerid,"Prieme","Ismete","Paaukstino");
					case 10: Ataskaita(playerid,"Paeme ginkla","Padejo ginkla","Itariamas kulku gamyba");
					case 11: Ataskaita(playerid,"Vardo keitimas is","Vardo keitimas i");
					case 12: Ataskaita(playerid,"Nuzude","Mire");
					case 13: Ataskaita(playerid,"Relog","Save");
					case 15: Ataskaita(playerid,"Range");
					case 16: Ataskaita(playerid,"Dave star","Isteisino");
					case 17: Ataskaita(playerid,"WarnCheat","AC_Ban","AC_Kick");
					case 18: Ataskaita(playerid,"Sprogimai");
					case 20: Ataskaita(playerid,"Padejo i kfonda","Paeme is kfondo"); 
					case 21: Ataskaita(playerid,"N");//AddDListItem(playerid, "Padejo/paeme is kfondo", 20);
					case 22: Ataskaita(playerid,"Paeme is pelno","Padejo i pelna"); //MLog(playerid,"Paeme is pelno","ii",id,kiekis);
					case 23: Ataskaita(playerid,"Ismokejo alga");
					case 24: Ataskaita(playerid,"Uzdejo ispejima","Nueme ispejimus");
					case 25: Ataskaita(playerid,"Kviecia", "Prieme iskvietima");
					//case 14: ShowPlayerDialog(playerid,8581,DIALOG_STYLE_INPUT,"Login song","{FFFFFF}Irasykite dainos koda is youtube:\nhttp://www.youtube.com/watch?v={FF0000}LoQYw49saqc{FFFFFF}&ob=av2e","Gerai","Atsaukti");
				}
			}
			else cmd_p(playerid,"");
		}
		if(dialogid==340)
		{
			if(response) 
			{
				if(listitem ==0)
					cmd_cpass(playerid,"");
				else if(listitem == 1)
					ShowPlayerDialog(playerid,9889,DIALOG_STYLE_INPUT,"El. paðtas","Áveskite el. paðto adresà, kurá norite susieti su ðia paskyra.\nPamirðus slaptaþodá, naujas bus atsiøstas ðiuo adresu. {FF6666}Bûtinai naudokite tik savo el paðto adresà, nes kitaip jûsø akauntas gali bûti pavogtas.","Gerai","Atsaukti");
				else
					AtsauktiKeitima(playerid);
			}
			else cmd_p(playerid,"");
		}
		if(dialogid==8581)
		{
			if(response && !isnull(inputtext))
			{
				cmd_radiostart(playerid,inputtext);
				SendInfoMessage(playerid,"Nustatyta!");
			}	
		}	
		if(dialogid==350)
		{
			if(response)
			{
				switch(listitem)
				{	
					case 0:
					{
						new msg[128];
						format(msg,sizeof(msg),"Greitieji klavisai: %s",((BitFlag_Get(PConfig[playerid],PCFG_SPARTIEJI)) ? ("~r~Isjungei"):("~g~Ijungei")));
						SendInfoMessage(playerid,msg);
						BitFlag_Toggle(PConfig[playerid],PCFG_SPARTIEJI);
						//OPOS(PConfig[playerid][spart]);
					}
					case 1:
					{
						new msg[128];
						format(msg,sizeof(msg),"Gaujos chatas: %s",((BitFlag_Get(PConfig[playerid],PCFG_SHOWGCHAT)) ? ("~r~Isjungei"):("~g~Ijungei")));
						SendInfoMessage(playerid,msg);
						//OPOS(PConfig[playerid][showgchat]);
						BitFlag_Toggle(PConfig[playerid],PCFG_SHOWGCHAT);
					}
					case 2:
					{
						new msg[128];
						format(msg,sizeof(msg),"VIP skelbimai: %s",((BitFlag_Get(PConfig[playerid],PCFG_SHOWVCHAT)) ? ("~r~Isjungei"):("~g~Ijungei")));
						SendInfoMessage(playerid,msg);
						BitFlag_Toggle(PConfig[playerid],PCFG_SHOWVCHAT);
					}
					case 3:
					{
						new msg[128];
						format(msg,sizeof(msg),"VIP chatas: %s",((BitFlag_Get(PConfig[playerid],PCFG_SHOWVIPCHAT)) ? ("~r~Isjungei"):("~g~Ijungei")));
						SendInfoMessage(playerid,msg);
						BitFlag_Toggle(PConfig[playerid],PCFG_SHOWVIPCHAT);
					}
					case 4:
					{
						new msg[128];
						format(msg,sizeof(msg),"Zaideju vardu rodymas : %s",((BitFlag_Get(PConfig[playerid],PCFG_SHOWNAMES)) ? ("~r~Isjungei"):("~g~Ijungei")));
						SendInfoMessage(playerid,msg);
						BitFlag_Toggle(PConfig[playerid],PCFG_SHOWNAMES);
						new Float:Coo[3];
						GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
						if(!!BitFlag_Get(PConfig[playerid],PCFG_SHOWNAMES)) 
						{
							for(new p;p<StreamedPlayers[playerid][sCount];p++) 
							{
								new pid = StreamedPlayers[playerid][sList][p];

								new Float:dists = GetPlayerDistanceFromPoint(pid,Coo[0],Coo[1],Coo[2]);
								if(dists <= 25.0) 
								{
									ShowPlayerNameTagForPlayer(playerid, pid, true);
								}
								else
								{
									ShowPlayerNameTagForPlayer(playerid, pid, false);
								}

							}
						}
						else
						{
							foreach(Player, i) 
								ShowPlayerNameTagForPlayer(playerid,i,false);
						}
					}
					case 5:
					{
						new msg[128];
						format(msg,sizeof(msg),"Spidometras : %s",((BitFlag_Get(PConfig[playerid],PCFG_SHOWSPEEDO)) ? ("~r~Isjungei"):("~g~Ijungei")));
						SendInfoMessage(playerid,msg);
						BitFlag_Toggle(PConfig[playerid],PCFG_SHOWSPEEDO);
						if(!BitFlag_Get(PConfig[playerid],PCFG_SHOWSPEEDO))
						{
							PlayerTextDrawHide(playerid,Speedo[playerid]);
							TextDrawHideForPlayer(playerid, kmhTD);
							//PlayerTextDrawShow(playerid, Speedo[playerid]);
							HideProgressBarForPlayer(playerid,Degalai);
							HideProgressBarForPlayer(playerid,Akumas);
							PlayerTextDrawHide(playerid, DegalasTD[playerid]);
							PlayerTextDrawHide(playerid, AkumasTD[playerid]);
							PlayerTextDrawHide(playerid, VehicleHP[playerid]);
						}
						else if(IsPlayerInAnyVehicle(playerid))
						{
							PlayerTextDrawShow(playerid,Speedo[playerid]);
							TextDrawShowForPlayer(playerid, kmhTD);
							//PlayerTextDrawShow(playerid, Speedo[playerid]);
							ShowProgressBarForPlayer(playerid,Degalai);
							ShowProgressBarForPlayer(playerid,Akumas);
							PlayerTextDrawShow(playerid, DegalasTD[playerid]);
							PlayerTextDrawShow(playerid, AkumasTD[playerid]);
							PlayerTextDrawShow(playerid, VehicleHP[playerid]);
						}
						//foreach(Player, i) ShowPlayerNameTagForPlayer(playerid,i,!!BitFlag_Get(PConfig[playerid],PCFG_SHOWSPEE));
					}
					case 6:
					{
						new msg[128];
						format(msg,sizeof(msg),"Animacijos tekstas : %s",((BitFlag_Get(PConfig[playerid],PCFG_SHOWANIMATIONS)) ? ("~r~Isjungei"):("~g~Ijungei")));
						SendInfoMessage(playerid,msg);
						BitFlag_Toggle(PConfig[playerid],PCFG_SHOWANIMATIONS);
						TextDrawHideForPlayer(playerid,txtAnimHelper);
						//foreach(Player, i) ShowPlayerNameTagForPlayer(playerid,i,!!BitFlag_Get(PConfig[playerid],PCFG_SHOWNAMES));
					}
					case 7:
					{
						new msg[128];
						format(msg,sizeof(msg),"Alkanumo rodiklis : %s",((BitFlag_Get(PConfig[playerid],PCFG_SHOWALKIS)) ? ("~r~Isjungei"):("~g~Ijungei")));
						SendInfoMessage(playerid,msg);
						BitFlag_Toggle(PConfig[playerid],PCFG_SHOWALKIS);
						if(!BitFlag_Get(PConfig[playerid],PCFG_SHOWALKIS))
						{
							HideProgressBarForPlayer(playerid,Alkis);
						}
						else
						{
							SetProgressBarValue(Alkis, playerDB[playerid][sotumas]+10.0);
							ShowProgressBarForPlayer(playerid,Alkis);
						}
					}
					case 8:
					{
						if(!BitFlag_Get(PConfig[playerid],PCFG_RAIDES))
						{
							BitFlag_Toggle(PConfig[playerid],PCFG_RAIDES);
							SendClientMessage(playerid,COLOR," * Dabar lietuviskos raides viesajame chate bus keiciamos i ju atitikmeni (àèæëáðøûþ).");
							SendClientMessage(playerid,COLOR," * Noredami matyti sias raides taisyklingai, apsilankykite musu tinklapio (LSGYVENIMAS.LT) pagalbos skiltyje.");
						}
						else
						{
							BitFlag_Toggle(PConfig[playerid],PCFG_RAIDES);
							SendClientMessage(playerid,COLOR," * Dabar matysi lietuviðkas raides.");
						}
						RenderTexts(playerid);
					}
					case 9:
					{
						if(!BitFlag_Get(PConfig[playerid],PCFG_HITSOUND))
						{
							SendClientMessage(playerid,COLOR," * Ájungei pataikymo garsus. Pataikes kulka i kita zmogu isgirsi garso efekta.");
						}
						else
						{
							SendClientMessage(playerid,COLOR," * Isjungei pataikymo garsus.");
						}
						BitFlag_Toggle(PConfig[playerid],PCFG_HITSOUND);
					}
					case 10:
					{
						if(!BitFlag_Get(PConfig[playerid],PCFG_MONETA))
						{
							SendClientMessage(playerid,COLOR," * Ájungei monetos pasiûlymus.");
						}
						else
						{
							SendClientMessage(playerid,COLOR," * Iðjungei monetos pasiûlymus.");
						}
						BitFlag_Toggle(PConfig[playerid],PCFG_MONETA);
					}
					case 11:
					{
						new msg[128];
						format(msg,sizeof(msg),"Admin chatas: %s",((BitFlag_Get(PConfig[playerid],PCFG_SHOWACHAT)) ? ("~r~Isjungei"):("~g~Ijungei")));
						SendInfoMessage(playerid,msg);
						BitFlag_Toggle(PConfig[playerid],PCFG_SHOWACHAT);
					}
				}
				return cmd_p(playerid,"");
			}
			else return cmd_p(playerid,"");
		
		}
		if(dialogid==88) // vardo keitimas
		{
			if(!strlen(inputtext)) return ShowPlayerDialog(playerid,88,DIALOG_STYLE_INPUT,"Vardo keitimas","Demesio! Jusu vardas musu serveryje netinkamas.\nJusu Vardas turi buti Vardas_Pavarde formatu.\nIveskite pageidaujama varda savo veikejui.\nVardas gali buti lietuviskas arba angliskas.{FF0000}\nJusu vardas netinkamas.","Gerai","Ok");
			if(strlen(inputtext) > 22)  return ShowPlayerDialog(playerid,88,DIALOG_STYLE_INPUT,"Vardo keitimas","Toks vardas per ilgas!","Gerai","Ok");
			mysql_real_escape_string(inputtext,inputtext,_,256);
			new query[512];
			format(query,sizeof(query),"SELECT 0 FROM `Account` WHERE `Name`='%s'",inputtext);
			mysql_function_query(SQL, query, true, "SQL_NameChange", "is", playerid,inputtext);
			
		}
		if(dialogid==89)
		{
			if(response)
			{
				if(!strlen(inputtext)) return ShowPlayerDialog(playerid,89,DIALOG_STYLE_INPUT,"Vardo keitimas","Jusu Vardas turi buti Vardas_Pavarde formatu.\nIveskite pageidaujama varda savo veikejui.\nVardas gali buti lietuviskas arba angliskas.","Gerai","Atgal");
				if(strlen(inputtext) > 22)  return ShowPlayerDialog(playerid,89,DIALOG_STYLE_INPUT,"Vardo keitimas","Toks vardas per ilgas!","Gerai","Atgal");
				mysql_real_escape_string(inputtext,inputtext,_,256);
				new query[512];
				format(query,sizeof(query),"SELECT 0 FROM `Account` WHERE `Name`='%s'",inputtext);
				mysql_function_query(SQL, query, true, "SQL_NameChange2", "is", playerid,inputtext);
			}
			else
			{
				new kredita[30];
				format(kredita,sizeof(kredita),"Turite %i kreditø",playerDB[playerid][kreditai]);
				return ShowPlayerDialog(playerid, 1989, DIALOG_STYLE_TABLIST, kredita , PASLAUGU_DIALOG, "Pirkti", "Atsaukti");
			}
				
		}
		if(dialogid==8563) // gaujos ismetimas
		{
			if(response)
			{
				new query[128];
				format(query,sizeof(query),"SELECT `Name` FROM `Account` WHERE `Gangas` = %i AND `Name`!='%s'",playerDB[playerid][pgang],ReturnName(playerid));
				//mysql_query(query);
				mysql_function_query(SQL, query, true, "SQL_GIsmesti", "ii", playerid,listitem);

			}
			else
			{
				return ShowGangDialog(playerid);
			}
		}
		
		if(dialogid==7600)
		{
			if(response)
			{
				if(!IsNumeric(inputtext)) return SendInfoMessage(playerid,"~r~Netinkamas formatas!");
				new kiek = strval(inputtext);
				if(GetPlayerMoneyA(playerid) < kiek*COST_SEKLOS) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
				if(KiekYra[0] < kiek) return SendInfoMessage(playerid,"~r~Tiek neturime!");
				
				new file[256];
				format(file,sizeof(file),"SELECT SUM(`Variable`) from `Logs` WHERE Zaidejas='%s' AND Veiksmas='Nusipirko Seklu' AND Data > SUBDATE(NOW(), 1)",ReturnName(playerid));
				mysql_function_query(SQL, file, true, "SQL_LimitSandeliai", "iii", playerid, 0, kiek);
			}
			else
			{
				if(strcmp(FamilyInfo[PlaceOwnedBy[0]][FamilyLeader],ReturnName(playerid),true) == 0 || strcmp(FamilyInfo[PlaceOwnedBy[0]][FamilySubstitute],ReturnName(playerid),true) == 0)
				{
					Ataskaita(playerid, "Nusipirko Seklu");
				}
			}
		}
		if(dialogid==7601)
		{
			if(response)
			{
				if(!IsNumeric(inputtext)) return SendInfoMessage(playerid,"~r~Netinkamas formatas!");
				new kiek = strval(inputtext);
				if(GetPlayerMoneyA(playerid) < kiek*COST_LSD) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
				if(KiekYra[1] < kiek) return SendInfoMessage(playerid,"~r~Tiek neturime!");

				new file[256];
				format(file,sizeof(file),"SELECT SUM(`Variable`) from `Logs` WHERE Zaidejas='%s' AND Veiksmas='Nusipirko LSD' AND Data > SUBDATE(NOW(), 1)",ReturnName(playerid));
				mysql_function_query(SQL, file, true, "SQL_LimitSandeliai", "iii", playerid, 1, kiek);
			}
			else
			{
				if(strcmp(FamilyInfo[PlaceOwnedBy[1]][FamilyLeader],ReturnName(playerid),true) == 0 || strcmp(FamilyInfo[PlaceOwnedBy[1]][FamilySubstitute],ReturnName(playerid),true) == 0)
				{
					Ataskaita(playerid, "Nusipirko LSD");
				}
			}			
		}
		if(dialogid==7602)
		{
			if(response)
			{
				if(!IsNumeric(inputtext)) return SendInfoMessage(playerid,"~r~Netinkamas formatas!");
				new kiek = strval(inputtext);
				if(GetPlayerMoneyA(playerid) < kiek*COST_RATAI) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
				if(KiekYra[2] < kiek) return SendInfoMessage(playerid,"~r~Tiek neturime!");

				new file[256];
				format(file,sizeof(file),"SELECT SUM(`Variable`) from `Logs` WHERE Zaidejas='%s' AND Veiksmas='Nusipirko Ratu' AND Data > SUBDATE(NOW(), 1)",ReturnName(playerid));
				mysql_function_query(SQL, file, true, "SQL_LimitSandeliai", "iii", playerid, 2, kiek);
			}	
			else
			{
				if(strcmp(FamilyInfo[PlaceOwnedBy[2]][FamilyLeader],ReturnName(playerid),true) == 0 || strcmp(FamilyInfo[PlaceOwnedBy[2]][FamilySubstitute],ReturnName(playerid),true) == 0)
				{
					Ataskaita(playerid, "Nusipirko Ratu");
				}
			}
		}
		if(dialogid==7704)
		{
			if(response)
			{
				if(listitem==1)
				{
					if(KiekYra[4] < 100000)
						return SendInfoMessage(playerid,"~r~Sandelyje nepakankamai pinigu.");
					KiekYra[4]=0;
					SendClientMessage(playerid,YELLOW," * Sekmingai paemei pinigus, dabar padek juos i inkasatoriaus automobili, kad sis juos praplautu."); 
					SetPlayerAttachedObject(playerid, MESKERE_SLOT, 1550, 1, 0.1, -0.3, 0, 0, 40, 0, 1, 1, 1);
					playerDB[playerid][dirtymoney]=true;
				}
			}
		}
		if(dialogid==7604)
		{
			if(response)
			{
				new string[256];
				if(listitem==0)
				{
					format(string,sizeof(string),"Turime %i apkabu combat sg.\nKiek norite pirkti?\nVieneto kaina: "#COST_COMBAT"€",KiekYra[3]);
					ShowPlayerDialog(playerid,7603,DIALOG_STYLE_INPUT,"Combat SG",string,"Gerai","Iki");
				}
				else
				{
					if(!BombaYra[3])
					{
						return SendInfoMessage(playerid,"Bombos nebera!");
					}
					new vehicle = playerDB[playerid][masina];
					new vehicle2 = GetClosestVehicleid(playerid,10.0);
					if(vehicle != vehicle2) 
						return SendInfoMessage(playerid,"Privezk arciau automobili!");
					new model = GetVehicleModel(vehicle);
					new exas;
					new mid = GetPlayerFromCarlistID(vehicle, exas);
					if(!mid) return SendInfoMessage(playerid,"Tai ne tavo automobilis!");
					if(vehicle == INVALID_VEHICLE_ID || model == 509 || model == 510)
						return SendInfoMessage(playerid,"Sis automobilis neturi bagazines!");
					GetVehicleParamsEx(vehicle,VehVars[0],VehVars[1],VehVars[2],VehVars[3],VehVars[4],VehVars[5],VehVars[6]);
					if(VehVars[5] != VEHICLE_PARAMS_ON)
						return SendInfoMessage(playerid,"~y~Atidaryk bagazine! Jei ilipsi i automobili su bomba rankose - sprogsi!");
					BombaYra[3]=0;
					SendInfoMessage(playerid,"Pasiemei bomba! Pakrauk ja i automobilio bagazine.");
					SetPlayerAttachedObject( playerid, SLOT_KROVINYS, 1575, 1, -0.064613, 0.520760, 0.000000, 0.000000, 84.217391, 0.000000, 1.000000, 1.000000, 1.000000 );
					SetPVarInt(playerid,"Bomba",1);
					ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 1, 1, 1, 1, 1);
				}
			}
		}
		if(dialogid==7605)
		{
			if(response)
			{
				new string[256];
				if(listitem==0)
				{
					format(string,sizeof(string),"Turime %i apkabu M4.\nKiek norite pirkti?\nVieneto kaina: "#COST_M4"€",KiekYra[5]);
					ShowPlayerDialog(playerid,7606,DIALOG_STYLE_INPUT,"M4",string,"Gerai","Iki");
				}
			}
		}
		if(dialogid==7606)
		{
			if(response)
			{
				if(!IsNumeric(inputtext)) return SendInfoMessage(playerid,"~r~Netinkamas formatas!");
				new kiek = strval(inputtext);
				if(GetPlayerMoneyA(playerid) < kiek*COST_COMBAT) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
				if(KiekYra[5] < kiek) return SendInfoMessage(playerid,"~r~Tiek neturime!");
				KiekYra[5]-=kiek;
				//playerDB[playerid][ratai]+=kiek;
				GivePlayerWeaponEx(playerid,31,kiek*50);
				GivePlayerMoneyA(playerid,-kiek*COST_M4);
				if(kiek) MLog(playerid,"Nusipirko M4","i", kiek);
				SendInfoMessage(playerid,"M4 nupirkti!");
			}	
			else
			{
				if(strcmp(FamilyInfo[PlaceOwnedBy[5]][FamilyLeader],ReturnName(playerid),true) == 0 || strcmp(FamilyInfo[PlaceOwnedBy[5]][FamilySubstitute],ReturnName(playerid),true) == 0)
				{
					Ataskaita(playerid, "Nusipirko M4");
				}
			}
		}
		if(dialogid==7603)
		{
			if(response)
			{
				if(!IsNumeric(inputtext)) return SendInfoMessage(playerid,"~r~Netinkamas formatas!");
				new kiek = strval(inputtext);
				if(GetPlayerMoneyA(playerid) < kiek*COST_COMBAT) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
				if(KiekYra[3] < kiek) return SendInfoMessage(playerid,"~r~Tiek neturime!");
				KiekYra[3]-=kiek;
				//playerDB[playerid][ratai]+=kiek;
				GivePlayerWeaponEx(playerid,27,kiek*7);
				GivePlayerMoneyA(playerid,-kiek*COST_COMBAT);
				if(kiek) MLog(playerid,"Nusipirko Combat","i", kiek);
				SendInfoMessage(playerid,"Combat SG nupirkti!");
			}	
			else
			{
				if(strcmp(FamilyInfo[PlaceOwnedBy[3]][FamilyLeader],ReturnName(playerid),true) == 0 || strcmp(FamilyInfo[PlaceOwnedBy[3]][FamilySubstitute],ReturnName(playerid),true) == 0)
				{
					Ataskaita(playerid, "Nusipirko Combat");
				}
			}
		}
		if(dialogid==12858)
		{
			if(response)
			{
				if (listitem == 0)
				{
					if(GetPlayerMoneyA(playerid) < COST_BOKSAS) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					GivePlayerMoneyA(playerid, -COST_BOKSAS);
					playerDB[playerid][treniruojasi]=true;
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					BusinessMoney(COST_BOKSAS);
					SetPlayerFightingStyle (playerid, FIGHT_STYLE_BOXING);
					SetTimerEx("BoxTrain", 1000, false, "i", playerid);
				}
				else if (listitem == 1)
				{
					if(GetPlayerMoneyA(playerid) < COST_KUNGFU) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					GivePlayerMoneyA(playerid, -COST_KUNGFU);
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					playerDB[playerid][treniruojasi]=true;
					SetPlayerFightingStyle (playerid, FIGHT_STYLE_KUNGFU);
					BusinessMoney(COST_KUNGFU);
					SetTimerEx("KungTrain", 1000, false, "i", playerid);
				}
				else if (listitem == 2)
				{
					if(GetPlayerMoneyA(playerid) < COST_GRABKICK) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, -COST_GRABKICK);
					playerDB[playerid][treniruojasi]=true;
					SetPlayerFightingStyle (playerid, FIGHT_STYLE_GRABKICK);
					BusinessMoney(COST_GRABKICK);
					SetTimerEx("GrabTrain", 1000, false, "i", playerid);
				}
				else if (listitem == 3)
				{
					if(GetPlayerMoneyA(playerid) < COST_KNEEHEAD_ELBOW) return SendInfoMessage(playerid,"~r~Truksta pinigu!");
					PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, -COST_KNEEHEAD_ELBOW);
					playerDB[playerid][treniruojasi]=true;
					SetPlayerFightingStyle (playerid, FIGHT_STYLE_KNEEHEAD);
					BusinessMoney(COST_KNEEHEAD_ELBOW);
					SetTimerEx("KneeTrain", 1000, false, "i", playerid);
				}
			}
		}
		if(dialogid==458)
		{
			if(response)
			{
				if(listitem == 0)
				{
					playerDB[playerid][aksesuaras]=1;
					TogglePlayerControllable(playerid,false);
					SetPlayerPosFade(playerid,20,-201.1304,-42.5132,1002.2734);
					SetPlayerFacingAngle(playerid,90.6467);
					SetPlayerCameraPos(playerid,-204.0696,-42.8246,1003.1270);
					SetPlayerCameraLookAt(playerid,-201.1304,-42.5132,1002.2734);
					playerDB[playerid][issirinkoak]=1;
					new skin=GetPlayerSkin(playerid);
					SetPlayerAttachedObject(playerid, AKINIU_SLOT, CommonRed+playerDB[playerid][issirinkoak]-1, 2, AkiniuOffSet[skin][0], AkiniuOffSet[skin][1], AkiniuOffSet[skin][2], AkiniuOffSet[skin][3], AkiniuOffSet[skin][4], AkiniuOffSet[skin][5],AkiniuOffSet[skin][6],AkiniuOffSet[skin][6]);

					GameTextForPlayer(playerid,"~y~Akinius rinkites ~k~~PED_FIREWEAPON~ arba ~k~~PED_LOCK_TARGET~ ~n~ ~g~Kai issirinksit spauskit ~k~~PED_SPRINT~ ~n~ ~r~Noredami iseit spauskit ~k~~VEHICLE_ENTER_EXIT~",60000,3);
					SendInfoMessage(playerid,"Jei norite kad zaidejas nepasuktu galvos rasykite /headmove");
					return 1;
				}
				if(listitem == 1)
				{
					playerDB[playerid][aksesuaras]=2;
					TogglePlayerControllable(playerid,false);
					//SetPlayerPoz(playerid,-202.8164,-42.8761,1002.2734);
					SetPlayerPosFade(playerid,20,-202.8164,-42.8761,1002.2734);
					SetPlayerFacingAngle(playerid,0.6467);
					SetPlayerCameraPos(playerid,-204.0696,-42.8246,1003.1270);
					SetPlayerCameraLookAt(playerid,-201.1304,-42.5132,1002.2734);
					playerDB[playerid][issirinkoak]=1;
					UzdetiSalma(playerid,Salmai[playerDB[playerid][issirinkoak]-1]);
					GameTextForPlayer(playerid,"~y~Akinius rinkites ~k~~PED_FIREWEAPON~ arba ~k~~PED_LOCK_TARGET~ ~n~ ~g~Kai issirinksit spauskit ~k~~PED_SPRINT~ ~n~ ~r~Noredami iseit spauskit ~k~~VEHICLE_ENTER_EXIT~",60000,3);
					SendInfoMessage(playerid,"Jei norite kad zaidejas nepasuktu galvos rasykite /headmove");
					return 1;
				}
				if(listitem == 2)
				{
					new skinid=GetPlayerSkin(playerid);
					
					if(InvalidCapSkin(skinid))
						return SendClientMessage(playerid,COLOR," * Negali uþsidëti kepurës ant ðio skino!");
					playerDB[playerid][issirinkoak]=1;
					SetPlayerAttachedObject(playerid, CAP_SLOT, Kepures[playerDB[playerid][issirinkoak]-1], 2, SkinCapsSet[skinid][0], SkinCapsSet[skinid][1],SkinCapsSet[skinid][2], SkinCapsSet[skinid][3], SkinCapsSet[skinid][4], SkinCapsSet[skinid][5]);
					
					playerDB[playerid][aksesuaras]=3;
					TogglePlayerControllable(playerid,false);
					//SetPlayerPoz(playerid,-202.8164,-42.8761,1002.2734);
					SetPlayerPosFade(playerid,20,-202.8164,-42.8761,1002.2734);
					SetPlayerFacingAngle(playerid,0.6467);
					SetPlayerCameraPos(playerid,-204.0696,-42.8246,1003.1270);
					SetPlayerCameraLookAt(playerid,-201.1304,-42.5132,1002.2734);
					playerDB[playerid][issirinkoak]=1;
					
					GameTextForPlayer(playerid,"~y~Kepure rinkites ~k~~PED_FIREWEAPON~ arba ~k~~PED_LOCK_TARGET~ ~n~ ~g~Kai issirinksit spauskit ~k~~PED_SPRINT~ ~n~ ~r~Noredami iseit spauskit ~k~~VEHICLE_ENTER_EXIT~",60000,3);
					SendInfoMessage(playerid,"Jei norite kad zaidejas nepasuktu galvos rasykite /headmove");
					return 1;
				}
				
			}
		
		}
		if(dialogid==549)
		{
			if(response)
			{
				new rs = random(Lovu);
				SetPlayerPoz(playerid,Lova[rs][Xl],Lova[rs][Yl],Lova[rs][Zl], _, _, 0);
				SetCameraBehindPlayer(playerid);
				//SetPlayerPosFade(playerid,20,Lova[rs][Xl],Lova[rs][Yl],Lova[rs][Zl]);
				SetPlayerFacingAngle(playerid,Lova[rs][Al]);
				ApplyAnimation(playerid, "CRACK", "crckdeth2", 4.0, 1, 0, 0, 0, 0, 1);
				TogglePlayerControllable(playerid,false);
				ApplyAnimation(playerid, "CRACK", "crckdeth2", 4.0, 1, 0, 0, 0, 0, 1);
				Gydosi[playerid] = SetTimerEx("Gydimas",5000,false,"i",playerid);
				SetTimerEx("AnimFreeze",300,false,"i",playerid);
				playerDB[playerid][mire]=true;
				SendInfoMessage(playerid,"Atsigulei pasigydyt.~n~ Kai pasijusi sveikas - rasyk ~r~/eiti");
				return 1;
			}
			return 1;
		}
		
		if(dialogid==12312)
		{
			if(response)
			{
				new name[MAX_PLAYER_NAME],file[128];
				GetPlayerName(playerid,name,sizeof(name));
				format(file,128,"SELECT `Slaptazodis` FROM `Account` WHERE `Name` = '%s' LIMIT 1",name);
				
				//mysql_query(file);
				mysql_function_query(SQL, file, true, "SQL_Cpass", "is", playerid,inputtext);

			}
		}
		if(dialogid==1111)
		{
			if(!response) return 1;
			switch(DLItemID)
			{
				case 0:
				{
					if(playerDB[playerid][treniruojasi]) return SendInfoMessage(playerid,"~r~Jus jau treniruojates!");
					SendClientMessage(playerid, COLOR_LIGHTBLUE, "|_______ Sporto klubas _______|");
					SendClientMessage(playerid, COLOR, "| 1: Box'as ("#COST_BOKSAS"€) | 2: Kung Fu ("#COST_KUNGFU"€) |");
					SendClientMessage(playerid, COLOR, "| 3: Grabkick ("#COST_GRABKICK"€) | 4: Kneehead ir Elbow ("#COST_KNEEHEAD_ELBOW") |");
					SendClientMessage(playerid, COLOR_GREY, "* Raðykite /kova, kad pasirinkt jau iðmoktus smûgius!");
					ShowPlayerDialog(playerid,12858,DIALOG_STYLE_TABLIST,"Sporto Klubas","Boksas\t"#COST_BOKSAS"€\nKung Fu\t"#COST_KUNGFU"€\nGrabkick\t"#COST_GRABKICK"€\nKneehead ir Elbow\t"#COST_KNEEHEAD_ELBOW"€","Gerai","Atsaukti");
					return 1;
				}
				case 1:
				{
					ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, "Ukines prekes", UKINES_PREKES, "Pirkti", "Nepirkti");
					return 1;
				}
				case 2:
				{
					if(GetPlayerMoneyA(playerid) < COST_SKINAS) return SendInfoMessage(playerid,"~r~Skinai kainuoja "#COST_SKINAS"EUR.");
					if(playerDB[playerid][uniformd]) return SendInfoMessage(playerid,"~r~Jus esate su darbine uniforma. Rasykite /persirengti");
					playerDB[playerid][aksesuaras]=4;
					TogglePlayerControllable(playerid,false);
					//SetPlayerPoz(playerid,-201.1304,-42.5132,1002.2734);
					new Float:Coo[3];
					GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
					GetXYInFrontOfPlayer(playerid, Coo[0],Coo[1], 1);
					Coo[2]+=1.0;
					SetPlayerCameraPos(playerid,Coo[0],Coo[1],Coo[2]);
					GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
					SetPlayerCameraLookAt(playerid,Coo[0],Coo[1],Coo[2]);
					playerDB[playerid][issirinkoak]=1;
					playerDB[playerid][paskutinisrubas]=GetPlayerSkin(playerid);
					SetPlayerSkin(playerid,Shopas[playerDB[playerid][issirinkoak]-1]);
					GameTextForPlayer(playerid,"~y~Rubus rinkites ~k~~PED_FIREWEAPON~ arba ~k~~PED_LOCK_TARGET~ ~n~ ~g~Kai issirinksit spauskit ~k~~PED_SPRINT~ ~n~ ~r~Noredami iseit spauskit ~k~~VEHICLE_ENTER_EXIT~",60000,3);
					SendInfoMessage(playerid,"Jei norite kad zaidejas nepasuktu galvos rasykite /headmove");

				}
				case 25:
				{
					new uni[2][5]; // 0 moteris 1 vyras
					switch(playerDB[playerid][specialybe])
					{
						case 2: {uni[0][0]=308; uni[1][0]=274; uni[1][1]=275; uni[1][2]=276; }
						case 3: {uni[0][0]=195; uni[1][0]=255;}
						case 6: {uni[0][0]=131; uni[1][0]=50;}
						case 20: {uni[0][0]=211; uni[1][0]=124;}
						case 31: {uni[0][0]=198; uni[1][0]=15;}
						case 32: {uni[0][0]=225; uni[1][0]=30;}
						case 39: {uni[0][0]=148; uni[1][0]=227;}
						case 41: {uni[0][0]=201; uni[1][0]=112;}
						case 44: {uni[0][0]=193; uni[1][0]=261;}
						case 50: {uni[0][0]=263; uni[1][0]=126;}
						case 66: {uni[0][0]=219; uni[1][0]=277;uni[1][1]=278;uni[1][2]=279;}
						case 70: {uni[0][0]=192; uni[1][0]=43;}
						case 71: {uni[0][0]=64; uni[1][0]=247;}
						case 72: {uni[0][0]=141; uni[1][0]=223;}
						case 73: {uni[0][0]=169; uni[1][0]=248;}
						case 80: {uni[0][0]=306;uni[1][0]=265;uni[1][1]=266;uni[1][2]=267;uni[1][3]=280;uni[1][4]=281;}
						case 81: {uni[0][0]=285; uni[1][0]=285;}
						case 82: {uni[0][0]=219; uni[1][0]=71;}
						case 83: {uni[0][0]=191; uni[1][0]=287;}
						case 84: {uni[0][0]=298; uni[1][0]=120;}
						case 34: {uni[0][0]=76; uni[1][0]=113;}
						case 93: {uni[0][0]=308; uni[1][0]=119;}
						case 60: {uni[0][0]=309; uni[1][0]=163; uni[1][1]=164;}
						default: return SendInfoMessage(playerid,"~r~Jusu darbui nereikalinga uniforma pagal uzsakyma!");
					}
					new x,y;
					if(playerDB[playerid][lytis]==2) y = 0;
					else y=1;
					if(GetPlayerMoneyA(playerid) < COST_UNIFORMA) return SendInfoMessage(playerid,"~r~Uniformos kainuoja "#COST_UNIFORMA" EUR!");
					GivePlayerMoneyA(playerid , -COST_UNIFORMA);
					ActorServe(playerid); BusinessMoney(COST_UNIFORMA);
					for(new i;i<5;i++)
						if(uni[y][i]) x++;
					new uniformax = uni[y][random(x)];
					playerDB[playerid][uniforma]= uniformax;
					SetPlayerSkin(playerid,uniformax);
					ApplyAnimation(playerid,"PLAYIDLES","stretch",4.1,0,0,0,0,0);
					playerDB[playerid][uniformd]=true;
					SendInfoMessage(playerid,"Sekmingai nusipirkote uniforma!");
				}
				case 3:
				{
					ShowPlayerDialog(playerid, 2, DIALOG_STYLE_LIST, "Gerimu parduotuve", "Coca cola\t{33FF33}"#COST_COLA"€\nSprite\t{33FF33}"#COST_SPRITE"€\nSampanas\t{33FF33}"#COST_SAMPANAS"€\nVynas\t{33FF33}"#COST_VYNAS"€\nAlus\t{33FF33}"#COST_ALUS"€\nVodka\t{33FF33}"#COST_VODKA"€\nBrendis\t{33FF33}"#COST_BRENDIS"€", "Pirkti", "Nepirkti");
					return 1;
				}
				case 4:
				{
					if(GetPlayerMoneyA(playerid) < COST_MAZA_PICA) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_MAZA_PICA);
					ActorServe(playerid); BusinessMoney(COST_MAZA_PICA);
					new Float:HP;
					GetPlayerHealth(playerid,HP);
					if(HP+20 < 200)
					{
						ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
						SetPlayerHealth(playerid,HP+20);
						Valgymas(playerid,20.0); ProcessAchievement(playerid,16);
						if(GetPlayerVisibleDynamicCP(playerid))
							SetTimerEx("OnPlayerEnterDynamicCP",1000,false,"ii",playerid,GetPlayerVisibleDynamicCP(playerid));
						return 1;
					}
					OnePlayAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); // Vomit BAH!
					SetPlayerHealth(playerid,20);
					
				}
				case 5:
				{
					if(GetPlayerMoneyA(playerid) < COST_VIDUTINE_PICA) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_VIDUTINE_PICA);
					ActorServe(playerid); BusinessMoney(COST_VIDUTINE_PICA);
					new Float:HP;
					GetPlayerHealth(playerid,HP);
					if(HP+40 < 200)
					{
						ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
						SetPlayerHealth(playerid,HP+40);
						Valgymas(playerid,40.0);ProcessAchievement(playerid,16);
						if(GetPlayerVisibleDynamicCP(playerid))
							SetTimerEx("OnPlayerEnterDynamicCP",1000,false,"ii",playerid,GetPlayerVisibleDynamicCP(playerid));
						return 1;
					}
					OnePlayAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); // Vomit BAH!
					SetPlayerHealth(playerid,20);

				}
				case 6:
				{
					if(GetPlayerMoneyA(playerid) < COST_DIDELE_PICA) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_DIDELE_PICA);
					ActorServe(playerid); BusinessMoney(COST_DIDELE_PICA);
					new Float:HP;
					GetPlayerHealth(playerid,HP);
					if(HP+60 < 200)
					{
						ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
						SetPlayerHealth(playerid,HP+60);
						Valgymas(playerid,60.0);ProcessAchievement(playerid,16);
						if(GetPlayerVisibleDynamicCP(playerid))
							SetTimerEx("OnPlayerEnterDynamicCP",1000,false,"ii",playerid,GetPlayerVisibleDynamicCP(playerid));
						return 1;
					}
					OnePlayAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); // Vomit BAH!
					SetPlayerHealth(playerid,20);
				}
				case 7:
				{
					if(GetPlayerMoneyA(playerid) < COST_SALOTOS) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_SALOTOS);
					ActorServe(playerid); BusinessMoney(COST_SALOTOS);
					new Float:HP;
					GetPlayerHealth(playerid,HP);
					if(HP+50 < 200)
					{
						//ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
						ApplyAnimation(playerid, "FOOD", "EAT_Burger", 3.0, 0, 0, 0, 0, 0);
						SetPlayerHealth(playerid,HP+50);
						Valgymas(playerid,50.0);ProcessAchievement(playerid,16);
						if(GetPlayerVisibleDynamicCP(playerid))
							SetTimerEx("OnPlayerEnterDynamicCP",1000,false,"ii",playerid,GetPlayerVisibleDynamicCP(playerid));
						return 1;
					}
					OnePlayAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); // Vomit BAH!
					SetPlayerHealth(playerid,20);
				}
				case 8:
				{
					//ShowPlayerDialog(playerid, 4, DIALOG_STYLE_LIST, "Saunamieji ginklai", "{FFFFFF}Rifle(50)\t{33FF33}"#COST_RIFLE"€\n{FFFFFF}Shotgun(20)\t{33FF33}"#COST_SHOTGUN"€\n{FFFFFF}9mm Pistol(100)\t{33FF33}"#COST_PISTOL"€\n{FFFFFF}Brass knuckles\t{33FF33}"#COST_KNUCKLES"€", "Pirkti", "Nepirkti");
					ShowPlayerDialog(playerid, 4, DIALOG_STYLE_TABLIST, "Saunamieji ginklai", SAUNAMIEJI_TEXT, "Pirkti", "Nepirkti");
					return 1;
					
				}
				case 9:
				{
					if(GetPlayerMoneyA(playerid) < COST_ARMOUR) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_ARMOUR);
					ActorServe(playerid); BusinessMoney(COST_ARMOUR);
					new Float:Armour;
					if(Armour+100 < 201) SetPlayerArmour(playerid,Armour+100);
					else SetPlayerArmour(playerid, 200);
					SendInfoMessage(playerid,"Nusipirkote sarvus!");
					if(boughtgun[playerid] == 1) 
						ProcessAchievement(playerid,78);
					boughtgun[playerid]=2;
					return 1;
				}
				case 10:
				{
					ShowPlayerDialog(playerid, 498, DIALOG_STYLE_TABLIST, "Fejerverkai","Star Dream\t{33FF33}"#COST_STAR_DREAM"€\n{FFFFFF}Dinamitas\t{33FF33}"#COST_DYNAMITE"€\n{FFFFFF}Raketa Saturn\t{33FF33}"#COST_SATURN"€\n{FFFFFF}Raketa Thunder\t{33FF33}"#COST_THUNDER"€\n{FFFFFF}Fontanas Rising Sun\t{33FF33}"#COST_RISING"€\n{FFFFFF}Fontanas Ocean Wave\t{33FF33}"#COST_OCEAN"€\n{FFFFFF}Volkanas Vixen\t{33FF33}"#COST_VIXEN"€\n{FFFFFF}Baterija Midnight Episode\t{33FF33}"#COST_MIDNIGHT"€", "Pirkti", "Nepirkti");					return 1;
				}
				case 11:
				{
					ShowPlayerDialog(playerid, 499, DIALOG_STYLE_LIST, "Sex Shop", "{FFFFFF}Trumpas Dildo \t{33FF33} "#COST_TRUMPAS_DILDO"€\n{FFFFFF}Trumpas Vibratorius \t{33FF33} "#COST_TRUMPAS_VIBRATORIUS"€\n{FFFFFF}Ilgas Dildo \t{33FF33} "#COST_ILGAS_DILDO"€\n{FFFFFF}Ilgas Vibratorius \t{33FF33} "#COST_ILGAS_VIBRATORIUS"€", "Pirkti", "Nepirkti");
					return 1;
				}
				case 12:
				{
					if(GetPlayerMoneyA(playerid) < COST_MESAINIS) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_MESAINIS);
					ActorServe(playerid); BusinessMoney(COST_MESAINIS);
					new Float:HP;
					GetPlayerHealth(playerid,HP);
					if(HP+5 < 200)
					{
						ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
						SetPlayerHealth(playerid,HP+5);
						Valgymas(playerid,5.0);ProcessAchievement(playerid,16);
						if(GetPlayerVisibleDynamicCP(playerid))
							SetTimerEx("OnPlayerEnterDynamicCP",500,false,"ii",playerid,GetPlayerVisibleDynamicCP(playerid));
						return 1;
					}
					OnePlayAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); // Vomit BAH!
					SetPlayerHealth(playerid,20);
				}
				case 13:
				{
					if(GetPlayerMoneyA(playerid) < COST_SURAINIS) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_SURAINIS);
					ActorServe(playerid); BusinessMoney(COST_SURAINIS);
					new Float:HP;
					GetPlayerHealth(playerid,HP);
					if(HP+10 < 200)
					{
						ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
						SetPlayerHealth(playerid,HP+10);
						Valgymas(playerid,10.0);ProcessAchievement(playerid,16);
						if(GetPlayerVisibleDynamicCP(playerid))
							SetTimerEx("OnPlayerEnterDynamicCP",500,false,"ii",playerid,GetPlayerVisibleDynamicCP(playerid));
						return 1;
					}
					OnePlayAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); // Vomit BAH!
					SetPlayerHealth(playerid,20);
				}
				case 14:
				{
					if(GetPlayerMoneyA(playerid) < COST_DVIGUBAS_MESAINIS) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_DVIGUBAS_MESAINIS);
					ActorServe(playerid); BusinessMoney(COST_DVIGUBAS_MESAINIS);
					new Float:HP;
					GetPlayerHealth(playerid,HP);
					if(HP+20 < 200)
					{
						ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
						SetPlayerHealth(playerid,HP+20);
						Valgymas(playerid,20.0);ProcessAchievement(playerid,16);
						if(GetPlayerVisibleDynamicCP(playerid))
							SetTimerEx("OnPlayerEnterDynamicCP",500,false,"ii",playerid,GetPlayerVisibleDynamicCP(playerid));
						return 1;
					}
					OnePlayAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); // Vomit BAH!
					SetPlayerHealth(playerid,20);
				}
				case 15:
				{
					if(GetPlayerMoneyA(playerid) < COST_BIGMAC) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_BIGMAC);
					ActorServe(playerid); BusinessMoney(COST_BIGMAC);
					new Float:HP;
					GetPlayerHealth(playerid,HP);
					if(HP+50 < 200)
					{
						//ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
						ApplyAnimation(playerid, "FOOD", "EAT_Burger", 3.0, 0, 0, 0, 0, 0);
						SetPlayerHealth(playerid,HP+50);
						Valgymas(playerid,50.0);ProcessAchievement(playerid,16);
						if(GetPlayerVisibleDynamicCP(playerid))
							SetTimerEx("OnPlayerEnterDynamicCP",500,false,"ii",playerid,GetPlayerVisibleDynamicCP(playerid));
						return 1;
					}
					OnePlayAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); // Vomit BAH!
					SetPlayerHealth(playerid,20);
				}
				case 16:
				{
					if(GetPlayerMoneyA(playerid) < COST_KEKSAS) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_KEKSAS);
					ActorServe(playerid); BusinessMoney(COST_KEKSAS);
					new Float:HP;
					GetPlayerHealth(playerid,HP);
					if(HP+5 < 200)
					{
						ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
						SetPlayerHealth(playerid,HP+5);
						Valgymas(playerid,5.0);ProcessAchievement(playerid,16);
						if(GetPlayerVisibleDynamicCP(playerid))
							SetTimerEx("OnPlayerEnterDynamicCP",500,false,"ii",playerid,GetPlayerVisibleDynamicCP(playerid));
						return 1;
					}
					OnePlayAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); // Vomit BAH!
					SetPlayerHealth(playerid,20);
				}
				case 17:
				{
					if(GetPlayerMoneyA(playerid) < COST_SPURGA) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_SPURGA);
					ActorServe(playerid); BusinessMoney(COST_SPURGA);
					new Float:HP;
					GetPlayerHealth(playerid,HP);
					if(HP+10 < 200)
					{
						ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
						SetPlayerHealth(playerid,HP+10);
						Valgymas(playerid,10.0);ProcessAchievement(playerid,16);
						if(GetPlayerVisibleDynamicCP(playerid))
							SetTimerEx("OnPlayerEnterDynamicCP",500,false,"ii",playerid,GetPlayerVisibleDynamicCP(playerid));
						return 1;
					}
					OnePlayAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); // Vomit BAH!
					SetPlayerHealth(playerid,20);
				}
				case 18:
				{
					if(GetPlayerMoneyA(playerid) < COST_DIDELE_SPURGA) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_DIDELE_SPURGA);
					ActorServe(playerid); BusinessMoney(COST_DIDELE_SPURGA);
					new Float:HP;
					GetPlayerHealth(playerid,HP);
					if(HP+50 < 200)
					{
						//ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
						ApplyAnimation(playerid, "FOOD", "EAT_Burger", 3.0, 0, 0, 0, 0, 0);
						SetPlayerHealth(playerid,HP+50);
						Valgymas(playerid,50.0);ProcessAchievement(playerid,16);
						if(GetPlayerVisibleDynamicCP(playerid))
							SetTimerEx("OnPlayerEnterDynamicCP",500,false,"ii",playerid,GetPlayerVisibleDynamicCP(playerid));
						return 1;
						
					}
					OnePlayAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); // Vomit BAH!
					SetPlayerHealth(playerid,20);
				}
				case 19:
				{
					//ShowPlayerDialog(playerid, 458, DIALOG_STYLE_MSGBOX, "Akiniai", "Ar norite nusipirkti akinius?\nKaina 1000€.", "Pirkti", "Nepirkti");
					
					ShowPlayerDialog(playerid, 458, DIALOG_STYLE_TABLIST, "Aksesuarai", "Akiniai\t"#COST_AKINIAI"€\nÐalmai\t"#COST_SALMAI"€\nKepurës\t"#COST_KEPURES"€","Pasirinkti", "Nesirinkti");
					return 1;
				}
				case 20:
				{
					ShowPlayerDialog(playerid, 5131, DIALOG_STYLE_INPUT, "Draudimas", "Iveskite suma, kuria norite apsidrausti.\nDidziausia suma: 250€.\nDraudimas galios 7 dienas.","Drausti","Atsaukti");
					return 1;
				}
				case 24:
				{
					new msg[512];
					if(Carlist[playerid][Typ]!=-1)
					{
						format(msg,sizeof(msg),"Pirmas automobilis(%s)",aVehicleNames[Carlist[playerid][Typ]][Name]);
						AddDListItem(playerid, msg, 0);
					}
					if(Carlist2[playerid][Typ]!=-1)
					{
						format(msg,sizeof(msg),"Antras automobilis(%s)",aVehicleNames[Carlist2[playerid][Typ]][Name]);
						AddDListItem(playerid, msg, 1);
					}
					if(Carlist3[playerid][Typ]!=-1)
					{
						format(msg,sizeof(msg),"Trecias automobilis(%s)",aVehicleNames[Carlist3[playerid][Typ]][Name]);
						AddDListItem(playerid, msg, 2);
					}
					ShowPlayerDList(playerid, 5132, "Draudimas", "Rinktis", "Iseiti");
					return 1;
				}
				case 21:
				{
					if(GetPlayerMoneyA(playerid) < COST_MAISTAS_NAMO) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_MAISTAS_NAMO);
					ActorServe(playerid); BusinessMoney(COST_MAISTAS_NAMO);
					playerDB[playerid][maistas]=1000;
					SendInfoMessage(playerid,"Nusipirkote maisto! Pasidekite ji namie ir rasykite /pavalgyti.",200);
					return 1;
				}
				case 22:
				{
					if(GetPlayerMoneyA(playerid) < COST_MAISTAS) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_MAISTAS);
					ActorServe(playerid); BusinessMoney(COST_MAISTAS);
					playerDB[playerid][maistaslauk]=1;
					SendInfoMessage(playerid,"Nusipirkote maisto! Galite suvalgyti ji parase /pavalgyti",200);
					return 1;
				}
				case 23:
				{	
					ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");
					return 1;
				}
				case 27:
				{
					ShowPlayerDialog(playerid,580,DIALOG_STYLE_TABLIST,"Maisto prekes",VARTOJIMO_TEXT,"Taip","Ne");
					return 1;
				}
				case 26:
				{
					ShowPlayerDialog(playerid,581,DIALOG_STYLE_TABLIST,"Automobiliu prekes",AUTOMOBILIU_TEXT,"Taip","Ne");
					return 1;
				}
				case 28:
				{
					if(GetPlayerMoneyA(playerid) < COST_SKINAS) return SendInfoMessage(playerid,"~r~Skinai kainuoja "#COST_SKINAS"EUR.");
					if(playerDB[playerid][uniformd]) return SendInfoMessage(playerid,"~r~Jus esate su darbine uniforma. Rasykite /persirengti");
					playerDB[playerid][aksesuaras]=5;
					TogglePlayerControllable(playerid,false);
					//SetPlayerPoz(playerid,-201.1304,-42.5132,1002.2734);
					new Float:Coo[3];
					GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
					GetXYInFrontOfPlayer(playerid, Coo[0],Coo[1], 1);
					Coo[2]+=1.0;
					SetPlayerCameraPos(playerid,Coo[0],Coo[1],Coo[2]);
					GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
					SetPlayerCameraLookAt(playerid,Coo[0],Coo[1],Coo[2]);
					playerDB[playerid][issirinkoak]=1;
					playerDB[playerid][paskutinisrubas]=GetPlayerSkin(playerid);
					SetPlayerSkin(playerid,Shopassex[playerDB[playerid][issirinkoak]-1]);
					GameTextForPlayer(playerid,"~y~Rubus rinkites ~k~~PED_FIREWEAPON~ arba ~k~~PED_LOCK_TARGET~ ~n~ ~g~Kai issirinksit spauskit ~k~~PED_SPRINT~ ~n~ ~r~Noredami iseit spauskit ~k~~VEHICLE_ENTER_EXIT~",60000,3);
					SendInfoMessage(playerid,"Jei norite kad zaidejas nepasuktu galvos rasykite /headmove");
					return 1;
				}
				case 29:
				{
					if(GetPlayerScore(playerid) < 100)
						return SendInfoMessage(playerid,"Sugrizk kai turesi 100xp!");
					// pirkti nark
					new idx=(GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2);
					new query[128];
					format(query,sizeof(query),"SELECT * From NarkTrade WHERE `busid`=%i ORDER BY price",idx);
					mysql_function_query(SQL, query, true, "SQL_PirktiNark", "ii", playerid,idx);
				}
				case 30:
				{
					// parduoti nark
					ShowPlayerDialog(playerid,582,DIALOG_STYLE_LIST,"Narkotiku pardavimas","Zole\nLSD\nRatai\nAmfetaminas","Gerai","Atsaukti");
				}
			}
		}
		if(dialogid==582)
		{
			if(response)
			{
				new textaz[128];
				new narkas[24];
				new countas = 0;
				
				if(listitem == 0) 
				{
					if(playerDB[playerid][zole] == 0)
						return SendInfoMessage(playerid,"~r~Neturi zoles!");
					SetPVarInt(playerid,"NarkType",0);
					narkas = "zoles";
					countas = playerDB[playerid][zole];
				}
				else if(listitem == 1) 
				{
					if(playerDB[playerid][lsd] == 0)
						return SendInfoMessage(playerid,"~r~Neturi LSD!");
					SetPVarInt(playerid,"NarkType",1);
					narkas = "LSD";
					countas = playerDB[playerid][lsd];
				}
				else if(listitem == 2) 
				{
					if(playerDB[playerid][ratai] == 0)
						return SendInfoMessage(playerid,"~r~Neturi ratu!");
					SetPVarInt(playerid,"NarkType",2);
					narkas = "ratu";
					countas = playerDB[playerid][ratai];
				}
				else if(listitem == 3) 
				{
					if(playerDB[playerid][amfetaminas] == 0)
						return SendInfoMessage(playerid,"~r~Neturi amfetamino!");
					SetPVarInt(playerid,"NarkType",3);
					narkas = "amfetamino";
					countas = playerDB[playerid][amfetaminas];
				}
				format(textaz,128,"Puiku! Kiek nori parduoti %s? Daugiausiai: %i",narkas,countas);
				ShowPlayerDialog(playerid, 583, DIALOG_STYLE_INPUT, "Narkotiku pardavimas", textaz, "Gerai", "Atsaukti");
			}
		}
		if(dialogid==583)
		{
			if(response) 
			{
				new kiekx = strval(inputtext);
				if(kiekx <= 0)
					return SendInfoMessage(playerid,"~r~Netinkamas kiekis!");
				new narkas = GetPVarInt(playerid, "NarkType");
				if(narkas == 0 && playerDB[playerid][zole] < kiekx)
					return SendInfoMessage(playerid,"~r~Tu tiek neturi!");
				if(narkas == 1 && playerDB[playerid][lsd] < kiekx)
					return SendInfoMessage(playerid,"~r~Tu tiek neturi!");
				if(narkas == 2 && playerDB[playerid][ratai] < kiekx)
					return SendInfoMessage(playerid,"~r~Tu tiek neturi!");
				if(narkas == 3 && playerDB[playerid][amfetaminas] < kiekx)
					return SendInfoMessage(playerid,"~r~Tu tiek neturi!");
				SetPVarInt(playerid,"NarkCount",kiekx);
				ShowPlayerDialog(playerid, 584, DIALOG_STYLE_INPUT, "Narkotiku pardavimas", "Kiek nori gauti uz viena vieneta? Daugiausiai: 5000€", "Gerai", "Atsaukti");
				return 1;
			}
		}
		if(dialogid==584)
		{
			if(response)
			{
				new kiekx=strval(inputtext);
				if(kiekx > 5000 || kiekx <=0)
					return SendInfoMessage(playerid,"~r~Netinkama kaina!");
				new type = GetPVarInt(playerid,"NarkType");
				new kiekis = GetPVarInt(playerid,"NarkCount");
				new price = kiekx;
				SellNark(playerid, type, kiekis, price);
			}
		}
		if(dialogid==585)
		{
			if(response)
			{
				SetPVarInt(playerid,"nark_id",listitem);
				new msg[128];
				new temp[24];
				format(temp,24,"nark_count_%i",listitem);
				format(msg,sizeof(msg),"Iveskite narkotiku kieki. Daugiausiai: %i vnt.",GetPVarInt(playerid,temp));
				ShowPlayerDialog(playerid,586,DIALOG_STYLE_INPUT,"Narkotiku pirkimas",msg,"Gerai","Atsaukti");
			}
		}
		if(dialogid==586)
		{
			if(response)
			{
				new kiek = strval(inputtext);
				new temp[24]; format(temp,24,"nark_count_%i",GetPVarInt(playerid, "nark_id"));
				if(kiek <= 0 || kiek > GetPVarInt(playerid, temp))
					return SendInfoMessage(playerid,"~r~Netinkamas kiekis!");
				format(temp,24,"nark_type_%i",GetPVarInt(playerid, "nark_id"));
				new type = GetPVarInt(playerid,temp);
				format(temp,24,"nark_price_%i",GetPVarInt(playerid, "nark_id"));
				new price = GetPVarInt(playerid,temp);
				BuyNark(playerid, type, kiek, price);
			}
		}
		if(dialogid==580)
		{
			if(response)
			{
				if(listitem==0) // kava
				{
					if(GetPlayerMoneyA(playerid) < COST_KAVA) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_KAVA);
					ActorServe(playerid); BusinessMoney(COST_KAVA);
					new Float:HP;
					GetPlayerHealth(playerid,HP);
					if(HP+20 < 200)
					{
						//ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
						ApplyAnimation(playerid, "FOOD", "EAT_Burger", 3.0, 0, 0, 0, 0, 0);
						SetPlayerHealth(playerid,HP+20);
						Valgymas(playerid,20.0);ProcessAchievement(playerid,16);
						if(GetPlayerVisibleDynamicCP(playerid))
							SetTimerEx("OnPlayerEnterDynamicCP",500,false,"ii",playerid,GetPlayerVisibleDynamicCP(playerid));
						return 1;
						
					}
					OnePlayAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); // Vomit BAH!
					SetPlayerHealth(playerid,20);
				}
				else if(listitem == 1) // submarinas
				{
					if(GetPlayerMoneyA(playerid) < COST_SUBMARINAS) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					GivePlayerMoneyA(playerid, -COST_SUBMARINAS);
					ActorServe(playerid); BusinessMoney(COST_SUBMARINAS);
					new Float:HP;
					GetPlayerHealth(playerid,HP);
					if(HP+40 < 200)
					{
						//ApplyAnimation(playerid,"VENDING","vend_eat1_P",4.1,0,0,0,0,0);
						ApplyAnimation(playerid, "FOOD", "EAT_Burger", 3.0, 0, 0, 0, 0, 0);
						SetPlayerHealth(playerid,HP+40);
						Valgymas(playerid,40.0);ProcessAchievement(playerid,16);
						if(GetPlayerVisibleDynamicCP(playerid))
							SetTimerEx("OnPlayerEnterDynamicCP",500,false,"ii",playerid,GetPlayerVisibleDynamicCP(playerid));
						return 1;
						
					}
					OnePlayAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0); // Vomit BAH!
					SetPlayerHealth(playerid,20);
				}
				else if(listitem == 2) // tekila
				{
					if(GetPlayerMoneyA(playerid) < COST_TEKILA)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_TEKILA);
					ActorServe(playerid); BusinessMoney(COST_TEKILA);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
					SendInfoMessage(playerid,"Nusipirkote tekilos.");
					//ApplyAnimation(playerid, "GANGS", "DEALER_DEAL", 4.000000, 0, 0, 0, 0, -1);
				}
				else if(listitem == 3) // cigaretes
				{
					if(GetPlayerMoneyA(playerid) < COST_CIGARETES)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_CIGARETES);
					ActorServe(playerid); BusinessMoney(COST_CIGARETES);
					playerDB[playerid][cigaretes]=20;
					//if(!Audio_IsClientConnected(playerid)) SendClientMessage(playerid,RED,"* Demesio! Neturite audio plugin'o. Tik turedami ji, galesite klausytis lietuviskos radijos. Prasome atsisiusti is www.LSGyvenimas.lt Pagalbos skilties.");
					SendInfoMessage(playerid,"Nusipirkote cigareciu.~n~Rasykite /rukyti, kad parukytumet.",150);
					//ApplyAnimation(playerid, "GANGS", "DEALER_DEAL", 4.000000, 0, 0, 0, 0, -1);				
				}
			}
		}
		if(dialogid==581)
		{
			if(response)
			{
				if(listitem==0) // bakelis
				{
					if(GetPlayerMoneyA(playerid) < COST_BAKELIS) return SendInfoMessage(playerid,"~r~Nepakanka pinigu!");
					GivePlayerMoneyA(playerid,-COST_BAKELIS);
					ActorServe(playerid); BusinessMoney(COST_BAKELIS);
					SendInfoMessage(playerid,"Nusipirkai kuro bakeli. Ji panaudoti gali parases /bakelis");
					playerDB[playerid][bakelis]=true;
				}
				else if(listitem == 1) // pakrovimas
				{
					if(GetPlayerMoneyA(playerid) < COST_PAKROVIMAS) return SendInfoMessage(playerid,"~r~Nepakanka pinigu!");
					
					new world = GetPlayerVirtualWorld(playerid);
					world-=MAX_HOUSES*2;
					if(world < 0) return 0;
					if(playerDB[playerid][masina] == -1) return SendInfoMessage(playerid,"O kur tavo masina?");
					if(!IsVehicleInRangeOfPoint(playerDB[playerid][masina],100.0,BusinessInfo[world][bEnterX],BusinessInfo[world][bEnterY],BusinessInfo[world][bEnterZ]))
					{
						SendInfoMessage(playerid,"Laidas nesiekia iki tavo masinos! Pastatyk ja arciau");
						return 1;
					}
				    GivePlayerMoneyA(playerid,-COST_PAKROVIMAS);
					ActorServe(playerid); BusinessMoney(COST_PAKROVIMAS);
					SendInfoMessage(playerid,"Mes pakroveme tavo automobili iki 20%");
					vehicleDB[playerDB[playerid][masina]][energy]=20;
				}
			}
		}
		if(dialogid==5131)
		{
			if(response)
			{
				if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, 5131, DIALOG_STYLE_INPUT, "Draudimas", "Iveskite suma, kuria norite apsidrausti.\nDidziausia suma: 250€.\nSkaiciais!","Drausti","Atsaukti");
				new val=strval(inputtext);
				if(val < 0 || val > 250) return ShowPlayerDialog(playerid, 5131, DIALOG_STYLE_INPUT, "Draudimas", "Iveskite suma, kuria norite apsidrausti.\nDidziausia suma: 250€.","Drausti","Atsaukti");
				if(val > GetPlayerMoneyA(playerid))
				{
					SendInfoMessage(playerid,"Suma per didele!~n~ Neturite tiek pinigu!");
					return 1;
				}

				GivePlayerMoneyA(playerid,-val); 
				playerDB[playerid][draudimas]=val;
				playerDB[playerid][draudimasg]=true;
				new query[128];
				format(query,sizeof(query),"UPDATE `Account` SET `Draudimasg` = 7 WHERE `Name`='%s'",ReturnName(playerid));
				mysql_query(query);
				//BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning]+=val;
				ActorServe(playerid); BusinessMoney(val);
				new msg[128];
				format(msg,sizeof(msg),"Lietuvos Gyvybes Draudimas: Apsidraudete ~r~%i~w~ EUR suma.",val);
				SendInfoMessage(playerid,msg);
				return 1;
			}
		}
		if(dialogid==5132)
		{
			if(response)
			{
				switch(DLItemID) // lolha
				{
					case 0:
					{
						if(!Carlist[playerid][Status]) return SendInfoMessage(playerid,"~r~Jusu automobilis sproges!");
						playerDB[playerid][paskutinisrubas]=1;
						new cost = floatround(aVehicleNames[Carlist[playerid][Typ]][Repair]/AdjustByRida(0,RIDA_REMONTAS,Carlist[playerid][Rida])/4); // AdjustByRida(vehicleid,RIDA_REMONTAS)
						new msg[256];
						format(msg,sizeof(msg)," Jusu automobilio draudimas kainuos %i€.\nJis galios 15 dienu.\nJusu automobiliui sprogus jums bus ismoketa %i€ suma.\nAr norite ji apdrausti?",cost, cost*2); //,(aVehicleNames[Carlist[playerid][Typ]][Repair]/2));
						ShowPlayerDialog(playerid,5133,DIALOG_STYLE_MSGBOX,"Draudimas",msg,"Gerai","Atsaukti");
					}
					case 1:
					{
						if(!Carlist2[playerid][Status]) return SendInfoMessage(playerid,"~r~Jusu automobilis sproges!");
						playerDB[playerid][paskutinisrubas]=2;
						new msg[256];
						new cost = floatround(aVehicleNames[Carlist2[playerid][Typ]][Repair]/AdjustByRida(0,RIDA_REMONTAS,Carlist2[playerid][Rida])/4);
						format(msg,sizeof(msg)," Jusu automobilio draudimas kainuos %i€.\nJis galios 15 dienu.\nJusu automobiliui sprogus jums bus ismoketa %i€ suma.\nAr norite ji apdrausti?",cost, cost*2);
						ShowPlayerDialog(playerid,5133,DIALOG_STYLE_MSGBOX,"Draudimas",msg,"Gerai","Atsaukti");
					}
					case 2:
					{
						if(!Carlist3[playerid][Status]) return SendInfoMessage(playerid,"~r~Jusu automobilis sproges!");
						playerDB[playerid][paskutinisrubas]=3;
						new cost = floatround(aVehicleNames[Carlist3[playerid][Typ]][Repair]/AdjustByRida(0,RIDA_REMONTAS,Carlist3[playerid][Rida])/4);
						new msg[256];
						format(msg,sizeof(msg)," Jusu automobilio draudimas kainuos %i€.\nJis galios 15 dienu.\nJusu automobiliui sprogus jums bus ismoketa %i€ suma.\nAr norite ji apdrausti?",cost, cost*2);
						ShowPlayerDialog(playerid,5133,DIALOG_STYLE_MSGBOX,"Draudimas",msg,"Gerai","Atsaukti");
					}
				}
			
			}
		}
		if(dialogid==5133)
		{
			if(response)
			{
				switch(playerDB[playerid][paskutinisrubas])
				{
					case 1:
					{
						new cost = floatround((aVehicleNames[Carlist[playerid][Typ]][Repair]/4)/AdjustByRida(0,RIDA_REMONTAS,Carlist[playerid][Rida])/4);
						if(GetPlayerMoneyA(playerid) < cost) return SendInfoMessage(playerid,"~r~Neturi tiek pinigu!");
						GivePlayerMoneyA(playerid, -cost);
						//BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning]+=((cost/3)*2);
						ActorServe(playerid); BusinessMoney(cost);
						SendInfoMessage(playerid,"Sveikiname! Jus apdraudete savo automobili 15 dienu!");
						Carlist[playerid][CDraud]=15;
					}
					case 2:
					{
						new cost = floatround((aVehicleNames[Carlist2[playerid][Typ]][Repair]/4)/AdjustByRida(0,RIDA_REMONTAS,Carlist2[playerid][Rida])/4);
						if(GetPlayerMoneyA(playerid) < cost) return SendInfoMessage(playerid,"~r~Neturi tiek pinigu!");
						GivePlayerMoneyA(playerid, -cost);
						//BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning]+=((cost/3)*2);
						ActorServe(playerid); BusinessMoney(cost);
						SendInfoMessage(playerid,"Sveikiname! Jus apdraudete savo automobili 15 dienu!");
						Carlist2[playerid][CDraud]=15;
					}
					case 3:
					{
						new cost = floatround((aVehicleNames[Carlist3[playerid][Typ]][Repair]/4)/AdjustByRida(0,RIDA_REMONTAS,Carlist3[playerid][Rida])/4);
						if(GetPlayerMoneyA(playerid) < cost) return SendInfoMessage(playerid,"~r~Neturi tiek pinigu!");
						GivePlayerMoneyA(playerid, -cost);
						//BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning]+=((cost/3)*2);
						ActorServe(playerid); BusinessMoney(cost);
						SendInfoMessage(playerid,"Sveikiname! Jus apdraudete savo automobili 15 dienu!");
						Carlist3[playerid][CDraud]=15;					
					}
				}
				ProcessAchievement(playerid, 124);
			}
			
			playerDB[playerid][paskutinisrubas]=0;
		}
		if(dialogid==12313)
		{
			if(response)
			{
				new file[128],name[MAX_PLAYER_NAME];
				if(strlen(inputtext) > 15)
				{
					ShowPlayerDialog(playerid,12313,DIALOG_STYLE_INPUT,"Cpass","Iveskite nauja slaptazodi\nSlaptazodis per ilgas.","Gerai","Atsaukti");
					return SendInfoMessage(playerid,"~r~SLAPTAZODIS PER ILGAS!"); 
				}
				else if(strlen(inputtext) <= 3)
				{
					ShowPlayerDialog(playerid,12313,DIALOG_STYLE_INPUT,"Cpass","Iveskite nauja slaptazodi\nSlaptazodis per trumpas.","Gerai","Atsaukti");
					return SendInfoMessage(playerid,"~r~SLAPTAZODIS PER TRUMPAS!"); 
				}
				GetPlayerName(playerid,name,MAX_PLAYER_NAME);
				format(file,256,"UPDATE `Account` SET `Slaptazodis` = '%s' WHERE `Name` = '%s'",sha256_hash(inputtext),name);
				mysql_query(file);
				format(file,sizeof(file),"LSG:\nSlaptazodis pakeistas i:\n{CC0033}%s",inputtext);
				printf(" [PASS] %s Pakeite password (naujas)",name);
				MLog(playerid,"Pass Keitimas", "s", name);
				ShowPlayerDialog(playerid,12314,DIALOG_STYLE_MSGBOX,"Cpass",file,"Gerai","");
				return 1;
			}
		}
		if(dialogid==1231)
		{
			if(!response)
			{
				if (Spectating[playerid][0]!=-1)
				{
					TogglePlayerControllable(playerid,1);
					SetVehicleParamsForAll(aVehicleNames[Spectating[playerid][0]][Carid],0,0);
					Spectating[playerid][0]=-1;
					//new masinx = GetPlayerVehicleID(playerid);
					Stop(playerid);
					//SetVehicleToRespawn(masinx);
					//vehicleDB[masinx][lastpos][0]=0;
					//vehicleDB[masinx][lastpos][1]=0;
					//vehicleDB[masinx][lastpos][2]=0;
				}
			}
			else
			{
				new string[128];
				if (Spectating[playerid][0]!=-1)
				{
					new price = aVehicleNames[Spectating[playerid][0]][Price];
					if (price <= GetPlayerMoneyA(playerid))
					{
						new autohaus;
						if (Carlist[playerid][Typ]==-1)
						{
							GivePlayerMoneyA(playerid, - price);
							switch(aVehicleNames[Spectating[playerid][0]][Autohaus])
							{
								case 1:
								{
									autohaus=random(sizeof(Carspawns));
									Carlist[playerid][Typ]=Spectating[playerid][0]; Carlist[playerid][X]=Carspawns[autohaus][X]; Carlist[playerid][Y]=Carspawns[autohaus][Y]; Carlist[playerid][Z]=Carspawns[autohaus][Z]; Carlist[playerid][Rotation]=Carspawns[autohaus][Rotation];Carlist[playerid][Status]=1; Carlist[playerid][Lock]=0;
								}
								case 2:
								{
									autohaus=random(sizeof(Carspawns2));
									Carlist[playerid][Typ]=Spectating[playerid][0]; Carlist[playerid][X]=Carspawns2[autohaus][X]; Carlist[playerid][Y]=Carspawns2[autohaus][Y]; Carlist[playerid][Z]=Carspawns2[autohaus][Z]; Carlist[playerid][Rotation]=Carspawns2[autohaus][Rotation];Carlist[playerid][Status]=1; Carlist[playerid][Lock]=0;
								}
								case 3:
								{
									autohaus=random(sizeof(Carspawns3));
									Carlist[playerid][Typ]=Spectating[playerid][0]; Carlist[playerid][X]=Carspawns3[autohaus][X]; Carlist[playerid][Y]=Carspawns3[autohaus][Y]; Carlist[playerid][Z]=Carspawns3[autohaus][Z]; Carlist[playerid][Rotation]=Carspawns3[autohaus][Rotation];Carlist[playerid][Status]=1; Carlist[playerid][Lock]=0;
								}
								case 4:
								{
									autohaus=random(sizeof(Carspawns4));
									ProcessAchievement(playerid, 83);
									Carlist[playerid][Typ]=Spectating[playerid][0]; Carlist[playerid][X]=Carspawns4[autohaus][X]; Carlist[playerid][Y]=Carspawns4[autohaus][Y]; Carlist[playerid][Z]=Carspawns4[autohaus][Z]; Carlist[playerid][Rotation]=Carspawns4[autohaus][Rotation];Carlist[playerid][Status]=1; Carlist[playerid][Lock]=0;
								}
							}
							
							Carlist[playerid][Carid]=CreateVehicle(aVehicleNames[Spectating[playerid][0]][Modelid],Carlist[playerid][X],Carlist[playerid][Y],Carlist[playerid][Z],Carlist[playerid][Rotation],-1,-1,-1);
							SetVehicleNumberPlate(Carlist[playerid][Carid],"{FF0000}NERA");
							SetVehicleParamsForAll(aVehicleNames[Spectating[playerid][0]][Carid],0,0);
							TogglePlayerControllable(playerid,1);
							Spectating[playerid][0]=-1;
							new vehicleid = Carlist[playerid][Carid];
							format(vehicleDB[vehicleid][nuomuoja],24,"no");
							format(vehicleDB[vehicleid][lastuser],MAX_PLAYER_NAME,"");
							vehicleDB[vehicleid][energy]=50;
							vehicleDB[vehicleid][OldHP]=1000;
							vehicleDB[vehicleid][gas]=50;
							vehicleDB[vehicleid][rida]=0.0;
							RemovePlayerFromVehicle(playerid);
							SavePlayerData(playerid,true);
							new name[24];
							GetPlayerName(playerid,name,24);
							format(string,128,"Sveikiname! Jus nusipirkote %s uz %iEUR! Tai pirmoji jusu masina!",aVehicleNames[Carlist[playerid][Typ]][Name],price);
							printf("%s %s",name,string);
							SendInfoMessage(playerid,string);
							SendClientMessage(playerid, GREEN, "Maðinos komandas rasite paraðæ /masina.");
							SendClientMessage(playerid, HOMER, "Jûsø maðina jau laukia jûsø kitoje gatvës puseje esanèioje aikðtelëje. Sëkmës!");
							SendClientMessage(playerid, HOMER, "Ðtai jums gesintuvas dovanø. Jei maðina uþsidegs kviesk gaisrine arba gesink pats.");
							SendClientMessage(playerid, ORANGE, "Gaisrininkai automobilá uþgesins DAUG greièiau, nei jûs gesintuvu.");
							GivePlayerWeaponEx(playerid,42,500);
							if(!IsAPBike(vehicleid))
								ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "Regitra", "Demesio! Privalote uþregistruoti savo maðinà!\nAr norite ten vaþiuoti dabar?", "Taip", "Ne");
							ProcessAchievement(playerid,3);
							return 1;
						}
						else if(Carlist2[playerid][Typ]==-1)
						{
							GivePlayerMoneyA(playerid, - price);
							//Carlist2[playerid][Typ]=Spectating[playerid][0]; Carlist2[playerid][X]=Carspawns[autohaus][X]; Carlist2[playerid][Y]=Carspawns[autohaus][Y]; Carlist2[playerid][Z]=Carspawns[autohaus][Z]; Carlist2[playerid][Rotation]=Carspawns[autohaus][Rotation]; Carlist2[playerid][Status]=1; Carlist2[playerid][Lock]=0;
							switch(aVehicleNames[Spectating[playerid][0]][Autohaus])
							{
								case 1:
								{
									autohaus=random(sizeof(Carspawns));
									Carlist2[playerid][Typ]=Spectating[playerid][0]; Carlist2[playerid][X]=Carspawns[autohaus][X]; Carlist2[playerid][Y]=Carspawns[autohaus][Y]; Carlist2[playerid][Z]=Carspawns[autohaus][Z]; Carlist2[playerid][Rotation]=Carspawns[autohaus][Rotation];Carlist2[playerid][Status]=1; Carlist2[playerid][Lock]=0;
								}
								case 2:
								{
									autohaus=random(sizeof(Carspawns2));
									Carlist2[playerid][Typ]=Spectating[playerid][0]; Carlist2[playerid][X]=Carspawns2[autohaus][X]; Carlist2[playerid][Y]=Carspawns2[autohaus][Y]; Carlist2[playerid][Z]=Carspawns2[autohaus][Z]; Carlist2[playerid][Rotation]=Carspawns2[autohaus][Rotation];Carlist2[playerid][Status]=1; Carlist2[playerid][Lock]=0;
								}
								case 3:
								{
									autohaus=random(sizeof(Carspawns3));
									Carlist2[playerid][Typ]=Spectating[playerid][0]; Carlist2[playerid][X]=Carspawns3[autohaus][X]; Carlist2[playerid][Y]=Carspawns3[autohaus][Y]; Carlist2[playerid][Z]=Carspawns3[autohaus][Z]; Carlist2[playerid][Rotation]=Carspawns3[autohaus][Rotation];Carlist2[playerid][Status]=1; Carlist2[playerid][Lock]=0;
								}
								case 4:
								{
									autohaus=random(sizeof(Carspawns4));
									ProcessAchievement(playerid, 83);
									Carlist2[playerid][Typ]=Spectating[playerid][0]; Carlist2[playerid][X]=Carspawns4[autohaus][X]; Carlist2[playerid][Y]=Carspawns4[autohaus][Y]; Carlist2[playerid][Z]=Carspawns4[autohaus][Z]; Carlist2[playerid][Rotation]=Carspawns4[autohaus][Rotation];Carlist2[playerid][Status]=1; Carlist2[playerid][Lock]=0;
								}
							}
							Carlist2[playerid][Carid]=CreateVehicle(aVehicleNames[Spectating[playerid][0]][Modelid],Carlist2[playerid][X],Carlist2[playerid][Y],Carlist2[playerid][Z],Carlist2[playerid][Rotation],-1,-1,-1);
							SetVehicleNumberPlate(Carlist2[playerid][Carid],"{FF0000}NERA");
							SetVehicleParamsForAll(aVehicleNames[Spectating[playerid][0]][Carid],0,0);
							TogglePlayerControllable(playerid,1);
							Spectating[playerid][0]=-1;
							new vehicleid = Carlist2[playerid][Carid];
							format(vehicleDB[vehicleid][nuomuoja],24,"no");
							format(vehicleDB[vehicleid][lastuser],MAX_PLAYER_NAME,"");
							vehicleDB[vehicleid][energy]=50;
							vehicleDB[vehicleid][OldHP]=1000;
							vehicleDB[vehicleid][gas]=50;
							vehicleDB[vehicleid][rida]=0.0;
							RemovePlayerFromVehicle(playerid);
							SavePlayerData(playerid,true);
							new name[24];
							GetPlayerName(playerid,name,24);
							format(string,128,"Sveikiname! Jus nusipirkote %s uz %iEUR! Tai antroji jusu masina",aVehicleNames[Carlist2[playerid][Typ]][Name],price);
							SendInfoMessage(playerid,string);
							printf("%s %s",name,string);
							SendClientMessage(playerid, GREEN, "Maðinos komandas rasite paraðæ /masina.");
							SendClientMessage(playerid, HOMER, "Jûsø maðina jau laukia jûsø kitoje gatvës puseje esanèioje aikðtelëje. Sëkmës!");
							SendClientMessage(playerid, HOMER, "Ðtai jums gesintuvas dovanø. Jei maðina uþsidegs kviesk gaisrine arba gesink pats.");
							SendClientMessage(playerid, ORANGE, "Gaisrininkai automobilá uþgesins DAUG greièiau, nei jûs gesintuvu.");
							GivePlayerWeaponEx(playerid,42,500);
							if(!IsAPBike(vehicleid))
								ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "Regitra", "Demesio! Privalote uþregistruoti savo maðinà!\nAr norite ten vaþiuoti dabar?", "Taip", "Ne");
							ProcessAchievement(playerid,3);
							return 1;
						}
						else if(Carlist3[playerid][Typ]==-1)
						{
							GivePlayerMoneyA(playerid, - price);
							//Carlist3[playerid][Typ]=Spectating[playerid][0]; Carlist3[playerid][X]=Carspawns[autohaus][X]; Carlist3[playerid][Y]=Carspawns[autohaus][Y]; Carlist3[playerid][Z]=Carspawns[autohaus][Z]; Carlist3[playerid][Rotation]=Carspawns[autohaus][Rotation]; Carlist3[playerid][Status]=1; Carlist3[playerid][Lock]=0;
							switch(aVehicleNames[Spectating[playerid][0]][Autohaus])
							{
								case 1:
								{
									autohaus=random(sizeof(Carspawns));
									Carlist3[playerid][Typ]=Spectating[playerid][0]; Carlist3[playerid][X]=Carspawns[autohaus][X]; Carlist3[playerid][Y]=Carspawns[autohaus][Y]; Carlist3[playerid][Z]=Carspawns[autohaus][Z]; Carlist3[playerid][Rotation]=Carspawns[autohaus][Rotation];Carlist3[playerid][Status]=1; Carlist3[playerid][Lock]=0;
								}
								case 2:
								{
									autohaus=random(sizeof(Carspawns2));
									Carlist3[playerid][Typ]=Spectating[playerid][0]; Carlist3[playerid][X]=Carspawns2[autohaus][X]; Carlist3[playerid][Y]=Carspawns2[autohaus][Y]; Carlist3[playerid][Z]=Carspawns2[autohaus][Z]; Carlist3[playerid][Rotation]=Carspawns2[autohaus][Rotation];Carlist3[playerid][Status]=1; Carlist3[playerid][Lock]=0;
								}
								case 3:
								{
									autohaus=random(sizeof(Carspawns3));
									Carlist3[playerid][Typ]=Spectating[playerid][0]; Carlist3[playerid][X]=Carspawns3[autohaus][X]; Carlist3[playerid][Y]=Carspawns3[autohaus][Y]; Carlist3[playerid][Z]=Carspawns3[autohaus][Z]; Carlist3[playerid][Rotation]=Carspawns3[autohaus][Rotation];Carlist3[playerid][Status]=1; Carlist3[playerid][Lock]=0;
								}
								case 4:
								{
									autohaus=random(sizeof(Carspawns4));
									ProcessAchievement(playerid, 83);
									Carlist3[playerid][Typ]=Spectating[playerid][0]; Carlist3[playerid][X]=Carspawns4[autohaus][X]; Carlist3[playerid][Y]=Carspawns4[autohaus][Y]; Carlist3[playerid][Z]=Carspawns4[autohaus][Z]; Carlist3[playerid][Rotation]=Carspawns4[autohaus][Rotation];Carlist3[playerid][Status]=1; Carlist3[playerid][Lock]=0;
								}
							}
							Carlist3[playerid][Carid]=CreateVehicle(aVehicleNames[Spectating[playerid][0]][Modelid],Carlist3[playerid][X],Carlist3[playerid][Y],Carlist3[playerid][Z],Carlist3[playerid][Rotation],-1,-1,-1);
							SetVehicleNumberPlate(Carlist3[playerid][Carid],"{FF0000}NERA");
							SetVehicleParamsForAll(aVehicleNames[Spectating[playerid][0]][Carid],0,0);
							TogglePlayerControllable(playerid,1);
							Spectating[playerid][0]=-1;
							new vehicleid = Carlist3[playerid][Carid];
							format(vehicleDB[vehicleid][nuomuoja],24,"no");
							format(vehicleDB[vehicleid][lastuser],MAX_PLAYER_NAME,"");
							vehicleDB[vehicleid][energy]=50;
							vehicleDB[vehicleid][OldHP]=1000;
							vehicleDB[vehicleid][gas]=50;
							vehicleDB[vehicleid][rida]=0.0;
							RemovePlayerFromVehicle(playerid);
							SavePlayerData(playerid,true);
							new name[24];
							GetPlayerName(playerid,name,24);
							format(string,128,"Sveikiname! Jus nusipirkote %s uz %iEUR! Tai trecioji jusu masina!",aVehicleNames[Carlist3[playerid][Typ]][Name],price);
							SendInfoMessage(playerid,string);
							printf("%s %s",name,string);
							SendClientMessage(playerid, GREEN, "Maðinos komandas rasite paraðæ /masina.");
							SendClientMessage(playerid, HOMER, "Jûsø maðina jau laukia jûsø kitoje gatvës puseje esanèioje aikðtelëje. Sëkmës!");
							SendClientMessage(playerid, HOMER, "Ðtai jums gesintuvas dovanø. Jei maðina uþsidegs kviesk gaisrine arba gesink pats.");
							SendClientMessage(playerid, ORANGE, "Gaisrininkai automobilá uþgesins DAUG greièiau, nei jûs gesintuvu.");
							GivePlayerWeaponEx(playerid,42,500);
							if(!IsAPBike(vehicleid))
								ShowPlayerDialog(playerid, 9999, DIALOG_STYLE_MSGBOX, "Regitra", "Demesio! Privalote uþregistruoti savo maðinà!\nAr norite ten vaþiuoti dabar?", "Taip", "Ne");
							ProcessAchievement(playerid,3);
							return 1;
						}
						else
						{
							if (Spectating[playerid][0]!=-1)
							{
								TogglePlayerControllable(playerid,1);
								SetVehicleParamsForAll(aVehicleNames[Spectating[playerid][0]][Carid],0,0);
								Spectating[playerid][0]=-1;
								new masinx = GetPlayerVehicleID(playerid);
								Stop(playerid);
								if(IsAutohausCar(masinx))
                                {
                                    SetVehicleToRespawn(masinx);
                                    vehicleDB[masinx][lastpos][0]=0;
                                    vehicleDB[masinx][lastpos][1]=0;
                                    vehicleDB[masinx][lastpos][2]=0;
                                }
							}
							SendInfoMessage(playerid,"~r~Jus jau turite tris automobilius!");
							return 1;
						}
					}
					else
					{
						if (Spectating[playerid][0]!=-1)
						{
							TogglePlayerControllable(playerid,1);
							SetVehicleParamsForAll(aVehicleNames[Spectating[playerid][0]][Carid],0,0);
							Spectating[playerid][0]=-1;
							new masinx = GetPlayerVehicleID(playerid);
							Stop(playerid);
							if(IsAutohausCar(masinx))
							{
								SetVehicleToRespawn(masinx);
								vehicleDB[masinx][lastpos][0]=0;
								vehicleDB[masinx][lastpos][1]=0;
								vehicleDB[masinx][lastpos][2]=0;
							}
						}
						format(string, 128, "~r~Nepakanka pinigu, isigyti sia masina (reikia: %iEUR)!", price);
						SendInfoMessage(playerid,string);
						return 1;
					}
					
				}
				else
				{
					SendInfoMessage(playerid,"Jus nesate parduodamoje masinoje.");
					return 1;
				}
			}
		
		}
/*		if(dialogid==8423)
		{
			if(!response) return 1;
		   // "Drabuziai\nGerimai\nFejerverkai\nKioskai\nMaisto produktai\nCigaretes\nZaislai"
			new pickupid;
			switch(listitem)
			{
				case 0: pickupid=pickups[0][kur_rubai];
				case 1: pickupid=pickups[0][kur_gerimai];
				case 2: pickupid=pickups[0][kur_fejerverkai];
				case 3: pickupid=pickups[0][kur_kioskai];
				case 4: pickupid=pickups[0][kur_maistas];
				case 5: pickupid=pickups[0][kur_cig];
				case 6: pickupid=pickups[0][kur_sexs];
			}
			SetPlayerCheckpoint(playerid,PickupIDs[pickupid][0],PickupIDs[pickupid][1],PickupIDs[pickupid][2],10.0);
			SendInfoMessage(playerid,"Jusu pasirinkta vieta rodoma radare!");
			return 1;
		}*/
		if(dialogid==874)
		{
			if(!response)
				return 0;
			ElevatorDialogResponse(playerid,listitem);
			return 1;
		}
		if(dialogid==1687)
		{
			if(response)
			{
			//	ShowPlayerDialog(playerid,1687,DIALOG_STYLE_LIST,"Automobilis","Lempos\nKapotas\nBagazine","Gerai","Iseit");
				//SetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
				new vehicleid=GetPlayerVehicleID(playerid);
				GetVehicleParamsEx(vehicleid,VehVars[0],VehVars[1],VehVars[2],VehVars[3],VehVars[4],VehVars[5],VehVars[6]);
				if(listitem == 0)
				{
					if(!VehVars[0])
					{
						if(vehicleDB[vehicleid][uzvedineja]) return 1;
						if(JobCars[vehicleid][0]) return 1;
						if(playerDB[playerid][ant] || playerDB[playerid][suristas]) return 1;
						if(vehicleDB[vehicleid][rankinis]) return SendInfoMessage(playerid,"Rankinis stabdis uztrauktas! Spausk [SPACE], kad ji atleistum!");
						SetTimerEx("Uzvedimas",floatround((2000+random(5000))/AdjustByRida(vehicleid,RIDA_UZVEDIMAS)),false,"ii",vehicleid,playerid);
						SendInfoMessage(playerid,"Uzvedineji masinos varikli");
						vehicleDB[vehicleid][uzvedineja]=true;
						return 1;
					}
					else
					{
						if(vehicleDB[vehicleid][uzvedineja]) return 1;
						if(playerDB[playerid][ant] || playerDB[playerid][suristas]) return 1;
						SetTimerEx("Isjungimas",random(1000),false,"ii",vehicleid,playerid);
						SendInfoMessage(playerid,"Isjungineji masinos varikli");
						vehicleDB[vehicleid][uzvedineja]=true;
					}
				}
				if(listitem==1)
				{
					if(VehVars[1])
					{
						SendInfoMessage(playerid,"~r~Isjungei~w~ automobilio lempas!");
						SetVehicleParamsEx(vehicleid,VehVars[0],false,VehVars[2],-1,VehVars[4],VehVars[5],VehVars[6]);
					}
					else
					{
						SendInfoMessage(playerid,"~g~Ijungei~w~ automobilio lempas!");
						SetVehicleParamsEx(vehicleid,VehVars[0],true,VehVars[2],-1,VehVars[4],VehVars[5],VehVars[6]);
					}
				}
				if(listitem==2)
				{
					if(VehVars[4])
					{
						SendInfoMessage(playerid,"~r~Uzdarei~w~ automobilio kapota!");
						SetVehicleParamsEx(vehicleid,VehVars[0],VehVars[1],false,-1,false,VehVars[5],VehVars[6]);
					}
					else
					{
						SendInfoMessage(playerid,"~g~Atidarei~w~ automobilio kapota!");
						SetVehicleParamsEx(vehicleid,VehVars[0],VehVars[1],false,-1,true,VehVars[5],VehVars[6]);
					}
				}
				if(listitem==3)
				{
					if(VehVars[5])
					{
						SendInfoMessage(playerid,"~r~Uzdarei~w~ automobilio bagazine!");
						SetVehicleParamsEx(vehicleid,VehVars[0],VehVars[1],false,-1,VehVars[4],false,VehVars[6]);
					}
					else
					{
						SendInfoMessage(playerid,"~g~Atidarei~w~ automobilio bagazine!");
						SetVehicleParamsEx(vehicleid,VehVars[0],VehVars[1],false,-1,VehVars[4],true,VehVars[6]);
						SendClientMessage(playerid,-1," * Norëdami naudotis bagaþine prieikite prie jos ir spauskite ~k~~GROUP_CONTROL_BWD~");
					}
				}
				if(listitem==4)
				{
					RadioList(playerid,false);
				}
			}
		
		}
		if(dialogid==9623)
		{
			if(response)
			{
				if(listitem==0)
				{
					if(GetPlayerMoneyA(playerid) < COST_NUMERIS) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
					if(playerDB[playerid][paskutinisrubas]==0) return SendInfoMessage(playerid,"O kur tavo masina?");
					GivePlayerMoneyA(playerid,-COST_NUMERIS);
					if(playerDB[playerid][paskutinisrubas]==1)
					{
						GetVehiclePos(Carlist[playerid][Carid],Carlist[playerid][X],Carlist[playerid][Y],Carlist[playerid][Z]);
						GetVehicleZAngle(Carlist[playerid][Carid],Carlist[playerid][Rotation]);
						Carlist[playerid][VirtualW] = GetVehicleVirtualWorld(Carlist[playerid][Carid]);
						new carid = Carlist[playerid][Carid];
						Carlist[playerid][Gas]=floatround(vehicleDB[carid][gas]);
						Carlist[playerid][Energy]=floatround(vehicleDB[carid][energy]);
						Carlist[playerid][Rida] = vehicleDB[carid][rida];
						SetVehicleParamsForAll(Carlist[playerid][Carid],0,0);
						DestroyVehicle(Carlist[playerid][Carid]);
						Carlist[playerid][Carid]=-1;
						Carlist[playerid][Carid]=CreateTunedCar(playerid);
						
						new stringas[50];
						new msg[128];
						format(stringas,sizeof(stringas),"%c%c%c %i%i%i",(65+random(26)),(65+random(26)),(65+random(26)),random(10),random(10),random(10));
						format(msg,sizeof(msg),"Aciu, kad naudojates musu paslaugomis! Jusu naujas numeris: %s",stringas);
						SendInfoMessage(playerid,msg);
						format(stringas,sizeof(stringas),"{000000}%s",stringas);
						SetVehicleNumberPlate(Carlist[playerid][Carid],stringas);
						Carlist[playerid][NumPlate]=stringas;
						playerDB[playerid][paskutinisrubas]=0;
						return 1;
					}
					if(playerDB[playerid][paskutinisrubas]==2)
					{
						GetVehiclePos(Carlist2[playerid][Carid],Carlist2[playerid][X],Carlist2[playerid][Y],Carlist2[playerid][Z]);
						GetVehicleZAngle(Carlist2[playerid][Carid],Carlist2[playerid][Rotation]);
						Carlist2[playerid][VirtualW] = GetVehicleVirtualWorld(Carlist2[playerid][Carid]);
						new carid = Carlist2[playerid][Carid];
						Carlist2[playerid][Gas]=floatround(vehicleDB[carid][gas]);
						Carlist2[playerid][Energy]=floatround(vehicleDB[carid][energy]);
						Carlist2[playerid][Rida] = vehicleDB[carid][rida];
						SetVehicleParamsForAll(Carlist2[playerid][Carid],0,0);
						DestroyVehicle(Carlist2[playerid][Carid]);
						Carlist2[playerid][Carid]=-1;
						Carlist2[playerid][Carid]=CreateTunedCar2(playerid);
						new stringas[50];
						new msg[128];
						format(stringas,sizeof(stringas),"%c%c%c %i%i%i",(65+random(26)),(65+random(26)),(65+random(26)),random(10),random(10),random(10));
						format(msg,sizeof(msg),"Aciu, kad naudojates musu paslaugomis! Jusu naujas numeris: %s",stringas);
						SendInfoMessage(playerid,msg);
						format(stringas,sizeof(stringas),"{000000}%s",stringas);
						SetVehicleNumberPlate(Carlist2[playerid][Carid],stringas);
						Carlist2[playerid][NumPlate]=stringas;
						playerDB[playerid][paskutinisrubas]=0;
						return 1;
					}
					if(playerDB[playerid][paskutinisrubas]==3)
					{
						GetVehiclePos(Carlist3[playerid][Carid],Carlist3[playerid][X],Carlist3[playerid][Y],Carlist3[playerid][Z]);
						GetVehicleZAngle(Carlist3[playerid][Carid],Carlist3[playerid][Rotation]);
						Carlist3[playerid][VirtualW] = GetVehicleVirtualWorld(Carlist3[playerid][Carid]);
						new carid = Carlist3[playerid][Carid];
						Carlist3[playerid][Gas]=floatround(vehicleDB[carid][gas]);
						Carlist3[playerid][Energy]=floatround(vehicleDB[carid][energy]);
						Carlist3[playerid][Rida] = vehicleDB[carid][rida];
						SetVehicleParamsForAll(Carlist3[playerid][Carid],0,0);
						DestroyVehicle(Carlist3[playerid][Carid]);
						Carlist3[playerid][Carid]=-1;
						Carlist3[playerid][Carid]=CreateTunedCar3(playerid);
						new stringas[50];
						new msg[128];
						format(stringas,sizeof(stringas),"%c%c%c %i%i%i",(65+random(26)),(65+random(26)),(65+random(26)),random(10),random(10),random(10));
						format(msg,sizeof(msg),"Aciu, kad naudojates musu paslaugomis! Jusu naujas numeris: %s",stringas);
						SendInfoMessage(playerid,msg);
						format(stringas,sizeof(stringas),"{000000}%s",stringas);
						SetVehicleNumberPlate(Carlist3[playerid][Carid],stringas);
						Carlist3[playerid][NumPlate]=stringas;
						playerDB[playerid][paskutinisrubas]=0;
						return 1;
					}
				}
				else
				{
					if(playerDB[playerid][kreditai]<10) return SendInfoMessage(playerid,"~r~Neuztenka kreditu! Rasykite /kreditai");
					ShowPlayerDialog(playerid,9624,DIALOG_STYLE_INPUT,"Numeris","Irasykite savo pasirinkta numeri.\nNumeris negali buti ilgesnis nei 9 simboliai ir trumpesnis nei 3.\nKaina 10 kreditu.","Gerai","Atsaukti");
					return 1;
				}
			}
		}
		if(dialogid==9624)
		{
			if(response)
			{
				if(strlen(inputtext) > 9 || strlen(inputtext) < 3 || strfind(inputtext,"{",false) != -1 || strfind(inputtext,"|",false) != -1 || strfind(inputtext,"'",false) != -1) return ShowPlayerDialog(playerid,9624,DIALOG_STYLE_INPUT,"Numeris","Irasykite savo pasirinkta numeri.\nNumeris negali buti ilgesnis nei 9 simboliai ir trumpesnis nei 3.\nKaina 10 kreditu.","Gerai","Atsaukti");
				SetPVarString(playerid,"MasinosNr", inputtext);
				MakePurchase(playerid, PURCHASE_NUMERIAI);
			}
		}
		if(dialogid==5250)
		{
			if(response)
			{
				new id = GetPlayeridMid(inputtext);
				if( id == playerid) return SendInfoMessage(playerid,"~r~Sau perleisti negali.");
				if(id == INVALID_PLAYER_ID) return SendInfoMessage(playerid,"~r~Tokio zaidejo nera.");
				if(playerDB[id][pgang] != playerDB[playerid][pgang]) return SendInfoMessage(playerid,"~r~Zaidejas ne jusu gaujoje.");
				format(FamilyInfo[playerDB[playerid][pgang]][FamilyLeader],MAX_PLAYER_NAME,"%s",ReturnName(id));
				format(FamilyInfo[playerDB[playerid][pgang]][FamilySubstitute],24,"Nera");
				new msg[128];
				format(msg,128," * %s Perleido tau savo gaujà '%s'.",ReturnName(playerid),FamilyInfo[playerDB[id][pgang]][FamilyName]);
				ProcessAchievement(id, 114);
				SendClientMessage(id,GANG_COLOR,msg);
				format(msg,128," * Jus perleidote %s savo gaujà '%s'.",ReturnName(id),FamilyInfo[playerDB[id][pgang]][FamilyName]);
				SendClientMessage(playerid,GANG_COLOR,msg);
				return 1;
			}
		
		}
		if(dialogid==7687)
		{
			if(response)
			{
				if(listitem==0)
				{
					if(IsPlayerAttachedObjectSlotUsed(playerid,MESKERE_SLOT))
					{
						RemovePlayerAttachedObject(playerid,MESKERE_SLOT);
						SendInfoMessage(playerid,"Pardavei meskere!");
						GivePlayerMoneyA(playerid, COST_MESKERE/2);
						ShowPlayerDialog(playerid, 7687, DIALOG_STYLE_TABLIST, "Zvejyba", ZVEJYBA_TEXT, "Pirkti", "Nepirkti");
						return 1;
					}
					if(GetPlayerMoneyA(playerid) < COST_MESKERE) return SendInfoMessage(playerid,"~r~Truksta pinigu!"),ShowPlayerDialog(playerid, 7687, DIALOG_STYLE_TABLIST, "Zvejyba", ZVEJYBA_TEXT, "Pirkti", "Nepirkti");
					SetPlayerAttachedObject(playerid, MESKERE_SLOT, 18632, 6, 0.091037, 0.019389, -0.053716, 184.678207, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000 );
					SendInfoMessage(playerid,"Nusipirkai meskere! Dabar issinuomuok valti ir rasyk /zvejoti");
					GivePlayerMoneyA(playerid, -COST_MESKERE);
					ShowPlayerDialog(playerid, 7687, DIALOG_STYLE_TABLIST, "Zvejyba", ZVEJYBA_TEXT, "Pirkti", "Nepirkti");
					return 1;
				}
				if(listitem==1)
				{
					if(GetPlayerMoneyA(playerid) < COST_MASALAS) return SendInfoMessage(playerid,"~r~Neuztenka pinigu!"),ShowPlayerDialog(playerid, 7687, DIALOG_STYLE_TABLIST, "Zvejyba", ZVEJYBA_TEXT, "Pirkti", "Nepirkti");
					if(playerDB[playerid][masalas] > 200) return SendInfoMessage(playerid,"~r~Nebepatempsi!"),ShowPlayerDialog(playerid, 7687, DIALOG_STYLE_TABLIST, "Zvejyba", ZVEJYBA_TEXT, "Pirkti", "Nepirkti");
					SendInfoMessage(playerid,"Nusipirkai 10 gramu masalo!");
					playerDB[playerid][masalas]+=10;
					GivePlayerMoneyA(playerid, -COST_MASALAS);
					ShowPlayerDialog(playerid, 7687, DIALOG_STYLE_TABLIST, "Zvejyba", ZVEJYBA_TEXT, "Pirkti", "Nepirkti");
					return 1;
				}
				if(listitem==2)
				{
					if(playerDB[playerid][zuvis] < 1) return SendInfoMessage(playerid,"~r~Neturi zuvies!");
					new msg[128];
					format(msg,sizeof(msg),"Pardavei %i vnt. zuvies uz %i EUR.",playerDB[playerid][zuvis],playerDB[playerid][zuvis]*COST_ZUVIS);
					SendInfoMessage(playerid,msg);
					GivePlayerMoneyA(playerid,playerDB[playerid][zuvis]*COST_ZUVIS);
					playerDB[playerid][zuvis]=0;
					ShowPlayerDialog(playerid, 7687, DIALOG_STYLE_TABLIST, "Zvejyba", ZVEJYBA_TEXT, "Pirkti", "Nepirkti");
					return 1;
				}
			}
		
		}
		// Apie kreditus\nPirkti kreditus\nPirkti paslaugas(%i kred.)
		
		if(dialogid==1987)
		{
			if(response)
			{
				if(listitem == 0)
				{
					SendClientMessage(playerid,COLOR ," * Kas yra kreditai?");
					SendClientMessage(playerid,YELLOW," Kreditai - virtualûs serverio pinigai, uþ kuriuos galite pirkti serverio paslaugas.");
					SendClientMessage(playerid,YELLOW," Pirkdami kreditus jûs paremiate serverá ir taip leidþiate jam gyvuoti.");
					return 1;
				}
				if(listitem == 1)
				{
					
					new msg[2048],name[24];
					GetPlayerName(playerid,name,24);
					format(msg,sizeof(msg),"{FFFFFF}Norëdami pirkti kreditus mûsø serveryje, apsilankykite mûsø puslapyje: {33FF33}lsgyvenimas.lt/kreditai\n\
					{FFFFFF}Nusipirkæ kreditus palaukite porà minuèiø ir spauskite Patvirtinti.");
					ShowPlayerDialog(playerid, 1988, DIALOG_STYLE_MSGBOX,"Kreditai", msg, "Patvirtinti", "Atsaukti");
					return 1;
				}
				if(listitem == 2)
				{
					new kredita[30];
					format(kredita,sizeof(kredita),"Turite %i kreditø",playerDB[playerid][kreditai]);
					ShowPlayerDialog(playerid, 1989, DIALOG_STYLE_TABLIST, kredita , PASLAUGU_DIALOG, "Pirkti", "Atsaukti");
					return 1;
				}
			}
		}
		
		if(dialogid==1989)
		{
			if(response)
			{   // Unban(10krd)\nVip 30d(20krd)\nPaleisti is jail(2krd)\nNuimti viena star(1krd)\nNorimas skinas(10krd)
				if(listitem == 0)
				{
					if(playerDB[playerid][kreditai] < 20)
					{
						SendInfoMessage(playerid,"~r~Neuztenka kreditu!");
						new kredita[30];
						format(kredita,sizeof(kredita),"Turite %i kreditø",playerDB[playerid][kreditai]);
						ShowPlayerDialog(playerid, 1989, DIALOG_STYLE_TABLIST, kredita , PASLAUGU_DIALOG, "Pirkti", "Atsaukti");
						return 1;
					}
					new query[256];
					format(query,sizeof(query),"SELECT * FROM `BANS` WHERE `Vardas`='%s' LIMIT 1",ReturnName(playerid));
					//mysql_query(query);
					mysql_function_query(SQL, query, true, "SQL_CheckUnban", "i", playerid);

				}
				if(listitem == 1)
				{
					MakePurchase(playerid, PURCHASE_VIP);
					return 1;
				}
				if(listitem == 2)
				{
					MakePurchase(playerid, PURCHASE_UNJAIL);
					return 1;
				}
				if(listitem == 3)
				{
					MakePurchase(playerid, PURCHASE_IST);
					return 1;
				}
				if(listitem == 4)
				{
					if(playerDB[playerid][uniformd]) return SendInfoMessage(playerid,"~r~Nusiimkite darbine apranga!");
					//ShowPlayerDialog(playerid, 1991, DIALOG_STYLE_INPUT, "Kreditai","Prasome irasyti skino numeri.\nDraudziami skinai: 0,74\nSkinu paveiksliukus rasite tinklapyje.","Taip","Ne");
					new rubai[320];
					new x = 0;
					for(new i;i<312;i++) if(i != 0 && i != 74)
					{
						rubai[x] = i;
						x++;
					}
					if(x) 
						ShowModelSelectionMenuEx(playerid, rubai, x, "Pasirinkite skina", GUI_BUYSKINS, 0.0, 0.0, 0.0, 1.0);//, Float:mZoom = 1.0, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899 , tdSelectionColor = 0xFFFF00AA);

					SendInfoMessage(playerid,"Prasome issirinkti norima skina!");
					return 1;
				}
				if(listitem == 5)
				{
					MakePurchase(playerid, PURCHASE_TEISES);
					return 1;
				}
				if(listitem == 6)
				{
					MakePurchase(playerid, PURCHASE_SPAZ);
					return 1;
				}
				if(listitem == 7)
				{
					ShowPlayerDialog(playerid,89,DIALOG_STYLE_INPUT,"Vardo keitimas","Jusu Vardas turi buti Vardas_Pavarde formatu.\nIveskite pageidaujama varda savo veikejui.\nVardas gali buti lietuviskas arba angliskas.","Gerai","Atgal");
					return 1;
				}
				if(listitem == 8)
				{
					AddDListItem(playerid,"Gangsteris", WALK_GANGSTA);
					AddDListItem(playerid,"Gangsteris 2", WALK_GANGSTA2);
					AddDListItem(playerid,"Senis", WALK_OLD);
					AddDListItem(playerid,"Storas senis", WALK_FAT_OLD);
					AddDListItem(playerid,"Storulis", WALK_FAT);
					AddDListItem(playerid,"Panele", WALK_LADY);
					AddDListItem(playerid,"Panele 2", WALK_LADY2);
					AddDListItem(playerid,"Kekse", WALK_WHORE);
					AddDListItem(playerid,"Kekse 2", WALK_WHORE2);
					AddDListItem(playerid,"Girtuoklis", WALK_DRUNK);
					AddDListItem(playerid,"Aklasis", WALK_BLIND);
					//ShowPlayerDialog(playerid,90,DIALOG_STYLE_LIST,"Vaiksciojimo stiliai",
					ShowPlayerDList(playerid,90,"Vaiksciojimo stiliai","Rinktis","Atsaukti");
					return 1;
				}
				if(listitem == 9)
				{
					ShowPlayerDialog(playerid,2001,DIALOG_STYLE_LIST,"Spalvos","Balta\nPilka\nZalia\nMelyna\nZydra\nRozine\nOranzine\nRaudona\nGeltona\n{FFCCCC}Sviesiai rozine\n{33FFCC}Electric\n{003300}Tamsiai zalia\n{660000}Tamsiai raudona\n{CCFFFF}Sviesiai melyna\n{6600CC}Violetine","Gerai","Atsaukti");
					return 1;
				}
				if(listitem == 10) // gesintuvas
				{
					MakePurchase(playerid, PURCHASE_GESINTUVAS);
					return 1;
				}
				if(listitem == 11) // pataisyt automobili
				{
					MakePurchase(playerid, PURCHASE_FIX);
					return 1;
				}
				if(listitem == 12) // pakelti sotuma
				{
					MakePurchase(playerid, PURCHASE_SOTUMAS);
					return 1;
				}
				if(listitem == 13) // pakelti sotuma
				{
					CrateLotoTextDraws(playerid);
					ShowLotoTextDraws(playerid,0);
					ShowPlayerDialog(playerid, 2332, DIALOG_STYLE_MSGBOX, "Vienetiniu automobiliu loterija", "Ar norite pirkti vienetiniø automobiliø loterijos bilietà?\n\n\
						Nusipirkæ ðá bilietà laimësite vienà ið 8 matomø vienetiniø automobiliø.\nAutomobiliai biliete keièiasi kasdien.\n\nKaina: {00CC00}100 kreditø","Pirkti","Nepirkti");
				}
				if(listitem == 14)
				{
					SendInfoMessage(playerid,"~r~Noredami nusipirkti papildoma vieta apsilankykite Transporto Saugykloje (/kur)");
				}
			}
			else
			{
				new msg[128];
				format(msg,sizeof(msg),"Apie kreditus\nPirkti kreditus\nPirkti paslaugas(%i kred.)",playerDB[playerid][kreditai]);
				ShowPlayerDialog(playerid, 1987, DIALOG_STYLE_LIST, "Kreditai",msg,"Taip","Ne");
			}
			return 1;
		}
		if(dialogid==2332)
		{
			HideLotoTextDraws(playerid);
			DestroyLotoTextDraws(playerid);
			if(response)
			{
				MakePurchase(playerid, PURCHASE_LOTO);
				return 1;
			}
			else
			{
				new kredita[30];
				format(kredita,sizeof(kredita),"Turite %i kreditø",playerDB[playerid][kreditai]);
				ShowPlayerDialog(playerid, 1989, DIALOG_STYLE_TABLIST, kredita , PASLAUGU_DIALOG, "Pirkti", "Atsaukti");
				return 1;
			}
		}
		if(dialogid==2002)
		{
			if(response)
			{
				SendInfoMessage(playerid,"Sveikiname nusipirkus naujaja spalva!");
				SendClientMessage(playerid,YELLOW," * Spalvà galite pasirinkti inventoriuje paraðæ /i");
				//ShowPlayerDialog(playerid,2001,DIALOG_STYLE_LIST,"Spalvos","Balta\nPilka\nZalia\nMelyna\nZydra\nRozine\nOranzine\nRaudona\nGeltona","Gerai","Atsaukti");
				new string[128];
				switch(listitem)
				{
					case 0: format(string,sizeof(string),"0xFFFFFFFF"),SetPlayerColor(playerid,0xFFFFFFFF);
					case 1: format(string,sizeof(string),"0xCCCCCCFF"),SetPlayerColor(playerid,0xA8A8A8FF);//SetPlayerColor(playerid,0xCCCCCCFF);
					case 2: format(string,sizeof(string),"0x00FF00FF"),SetPlayerColor(playerid,0x00FF00FF);
					case 3: format(string,sizeof(string),"0x0033FFFF"),SetPlayerColor(playerid,0x0033FFFF);
					case 4: format(string,sizeof(string),"0x33FFFFFF"),SetPlayerColor(playerid,0x33FFFFFF);
					case 5: format(string,sizeof(string),"0xFF00FFFF"),SetPlayerColor(playerid,0xFF00FFFF);
					case 6: format(string,sizeof(string),"0xFF6600FF"),SetPlayerColor(playerid,0xFF6600FF);
					case 7: format(string,sizeof(string),"0xFF0000FF"),SetPlayerColor(playerid,0xFF0000FF);
					case 8: format(string,sizeof(string),"0xFFFF00FF"),SetPlayerColor(playerid,0xFFFF00FF);
					// naujos spalvos comming up:
					//{FFCCCC}Sviesiai rozine\n{33FFCC}Electric\n{003300}Tamsiai zalia\n{660000}Tamsiai raudona\n{CCFFFF}Sviesiai melyna\n{6600CC}Violetine
					case 9: format(string,sizeof(string),"0xFFCCCCFF"),SetPlayerColor(playerid,0xFFCCCCFF);
					case 10: format(string,sizeof(string),"0x33FFCCFF"),SetPlayerColor(playerid,0x33FFCCFF);
					case 11: format(string,sizeof(string),"0x003300FF"),SetPlayerColor(playerid,0x003300FF);
					case 12: format(string,sizeof(string),"0x660000FF"),SetPlayerColor(playerid,0x660000FF);
					case 13: format(string,sizeof(string),"0xCCFFFFFF"),SetPlayerColor(playerid,0xCCFFFFFF);
					case 14: format(string,sizeof(string),"0x6600CCFF"),SetPlayerColor(playerid,0x6600CCFF);
				}
				new query[150];
				format(query,sizeof(query),"UPDATE Spalvos Set `Set`=0 WHERE Vardas='%s'",ReturnName(playerid));
				mysql_query(query);
				format(query,sizeof(query),"INSERT INTO Spalvos (Vardas,Color,`Set`) VALUES ('%s','%s',1)",ReturnName(playerid),string);
				mysql_query(query);
				ChristmasQuery(playerid);
				return 1;
			}
		}
		if(dialogid==2001)
		{
			
			if(response)
			{
				MakePurchase(playerid, PURCHASE_SPALVA, listitem);
				return 1;
			}
			else
			{
				new kredita[128];
				format(kredita,sizeof(kredita),"Turite %i kreditø",playerDB[playerid][kreditai]);
				ShowPlayerDialog(playerid, 1989, DIALOG_STYLE_TABLIST, kredita , PASLAUGU_DIALOG, "Pirkti", "Atsaukti");
				return 1;
			}
		}
		if(dialogid==91)
		{
			if(response)
			{
				SendInfoMessage(playerid,"Sveikiname gavus naujaji stiliu!");
				playerDB[playerid][wstyle]=DLItemID;
				new uzrasas[128];
				format(uzrasas,sizeof(uzrasas),"INSERT INTO `Stiliai`(`Vardas`,`Stilius`) VALUES ('%s',%i)",ReturnName(playerid),DLItemID);
				mysql_query(uzrasas);
				ChristmasQuery(playerid);
			}
		}
		if(dialogid==90)
		{
			
			if(response)
			{
				if(playerDB[playerid][kreditai] < 10)
				{
					SendInfoMessage(playerid,"~r~Neuztenka kreditu!");
					new kredita[30];
					format(kredita,sizeof(kredita),"Turite %i kreditø",playerDB[playerid][kreditai]);
					ShowPlayerDialog(playerid, 1989, DIALOG_STYLE_TABLIST, kredita , PASLAUGU_DIALOG, "Pirkti", "Atsaukti");
					return 1;
				}
				new query[128];
				format(query,sizeof(query),"SELECT Stilius FROM Stiliai WHERE Vardas='%s' AND Stilius=%i",ReturnName(playerid),DLItemID);
				//mysql_query(query);
				mysql_function_query(SQL, query, true, "SQL_CheckStilius", "ii", playerid,DLItemID);

			}
			else
			{
				new kredita[30];
				format(kredita,sizeof(kredita),"Turite %i kreditø",playerDB[playerid][kreditai]);
				ShowPlayerDialog(playerid, 1989, DIALOG_STYLE_TABLIST, kredita , PASLAUGU_DIALOG, "Pirkti", "Atsaukti");
				return 1;
			}
		}
		if(dialogid==1991)
		{
			
			if(response)
			{
				new skinid = GetPVarInt(playerid, "perkaskin");
				MakePurchase(playerid, PURCHASE_SKIN, skinid);
			}
			else
			{
				new rubai[320];
				new x = 0;
				for(new i;i<312;i++) if(i != 0 && i != 74)
				{
					rubai[x] = i;
					x++;
				}
				//galikast[playerid]=false;
				//SetTimerEx("GaliKast",1000,0,"i",playerid);
				if(x) 
					ShowModelSelectionMenuEx(playerid, rubai, x, "Pasirinkite skina", GUI_BUYSKINS, 0.0, 0.0, 0.0, 1.0);//, Float:mZoom = 1.0, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x88888899 , tdSelectionColor = 0xFFFF00AA);


			}
		}
		if(dialogid==1999)
		{
			new cost=PlayerUnbanCost[playerid];
			if(!response)
			{
				new msz[128];
				format(msz,128,"Pirkti kreditus(turite %i)\nGauti unban(%i kreditu)",playerDB[playerid][kreditai],cost);
				ShowPlayerDialog(playerid, 1990, DIALOG_STYLE_LIST, "Kreditai",msz,"Taip","Ne");
				return 1;
			}
			else
			{
				MakePurchase(playerid, PURCHASE_UNBAN, cost);
				return 1;
			}
		
		}
		if(dialogid==1990)
		{
			
			if(!response) Kick(playerid);
			else if(response)
			{
				if(listitem == 0)
				{
					
					new msg[2048],name[24];
					GetPlayerName(playerid,name,24);
					format(msg,sizeof(msg),"{FFFFFF}Norëdami pirkti kreditus mûsø serveryje, apsilankykite mûsø puslapyje: {33FF33}lsgyvenimas.lt/kreditai\n\
					{FFFFFF}Nusipirkæ kreditus palaukite porà minuèiø ir spauskite Patvirtinti.");
					ShowPlayerDialog(playerid, 1993, DIALOG_STYLE_MSGBOX,"Kreditai", msg, "Patvirtinti", "Atsaukti");
					
					return 0;
					
				}
				if(listitem == 1)
				{
					new query[128];
					new ip[24];
					GetPlayerIp(playerid,ip,24);
					format(query,sizeof(query),"SELECT * From Logs Where Veiksmas='Atsibanino' AND (Zaidejas='%s' OR Variable=' %s')",ReturnName(playerid),ip);
					mysql_function_query(SQL, query, true, "SQL_UnbanCost", "i", playerid);

				}
				return 1;
			}
		}
		
		if(dialogid==1993)
		{
			if(response)
			{
				new query[128];
				format(query,sizeof(query),"SELECT `Kreditai` FROM `Account` WHERE `Name`='%s' LIMIT 1",ReturnName(playerid));
				mysql_function_query(SQL, query, true, "SQL_UpdateKred", "i", playerid);
				
			}
			else Kick(playerid);
		}

			
			
			
		if(dialogid==1988)
		{
			if(!response) return 0;
			if(!IsPlayerConnected(playerid)) return 0;
			new query[128];
			format(query,sizeof(query),"SELECT * From `Account` WHERE `Name`='%s' LIMIT 1",ReturnName(playerid));
			mysql_function_query(SQL, query, true, "SQL_UpdateKred2", "i", playerid);

			return 1;
		}
		if(dialogid==5251)
		{
			if(response)
			{
				new id = GetPlayeridMid(inputtext);
				if(id == INVALID_PLAYER_ID) return SendInfoMessage(playerid,"~r~Tokio zaidejo nera.");
				if(playerDB[id][pgang]!= -1) return SendInfoMessage(playerid,"~r~Zaidejas jau turi gauja.");
				if(GetPlayerScore(id) < 100) return SendInfoMessage(playerid,"~r~Zaidejas dar neturi 100 xp!");
				new msg[128];
				format(msg,128," * %s Jus kvieèia á savo gaujà %s.",ReturnName(playerid),FamilyInfo[playerDB[playerid][pgang]][FamilyName]);
				SendClientMessage(id,GANG_COLOR,msg);
				format(msg,128," * Kvieèiate %s á savo gaujà %s.",ReturnName(id),FamilyInfo[playerDB[playerid][pgang]][FamilyName]);
				SendClientMessage(playerid,GANG_COLOR,msg);
				playerDB[id][ginvited][playerDB[playerid][pgang]]=true;
				return ShowGangDialog(playerid);
			}
			else
			{
				return ShowGangDialog(playerid);
			}

		}
		if(dialogid==5249)
		{
			if(response)
			{
				new id = GetIdForAlgos(inputtext);
				if( id == playerid) return SendInfoMessage(playerid,"~r~Saves ismesti negali.");
				if(id == INVALID_PLAYER_ID || playerDB[id][authstate]!=4)
				{
					new escname[128];
					mysql_real_escape_string(inputtext,escname,_,256);
					new query[128];
					format(query,sizeof(query),"SELECT `Gangas` FROM `Account` WHERE `Name`='%s'",escname);
					mysql_function_query(SQL, query, true, "SQL_GIsmesti2", "is", playerid,escname);

				}
				if(playerDB[id][pgang]!= playerDB[playerid][pgang]) return SendInfoMessage(playerid,"~r~Zaidejas ne jusu gaujoje.");

				new msg[128];
				format(msg,128," * %s Jus iðmete ið gaujos '%s'.",ReturnName(playerid),FamilyInfo[playerDB[playerid][pgang]][FamilyName]);
				SendClientMessage(id,GANG_COLOR,msg);
				format(msg,128," * Iðmetëte %s ið savo gaujos '%s'.",ReturnName(id),FamilyInfo[playerDB[playerid][pgang]][FamilyName]);
				SendClientMessage(playerid,GANG_COLOR,msg);
				playerDB[id][pgang]=-1;
				SetPlayerSkin(id,playerDB[id][drabuziai]);
				return ShowGangDialog(playerid);
			}
		
		}
		if(dialogid==5248)
		{
			if(response)
			{
					foreach (Player, i)
					{
						if(playerDB[i][pgang]==playerDB[playerid][pgang] && i != playerid)
						{
							playerDB[i][pgang]=-1;
							SendClientMessage(i,GANG_COLOR," * Jûsø gauja subyrëjo!");
						}
					}
					format(FamilyInfo[playerDB[playerid][pgang]][FamilyLeader],MAX_PLAYER_NAME,"Nera");
					format(FamilyInfo[playerDB[playerid][pgang]][FamilySubstitute],MAX_PLAYER_NAME,"Nera");
					SendInfoMessage(playerid,"~g~Apleidai gauja!");
					playerDB[playerid][pgang]=-1;
			}
			return 1;
		}
		if(dialogid==5253)
		{
			if(response)
			{
				if(listitem == 0)
				{
					new query[60];
					format(query,sizeof(query),"SELECT 0 FROM Account WHERE `Gangas`=%i",playerDB[playerid][pgang]);
					//mysql_query(query);
					mysql_function_query(SQL, query, true, "SQL_GangLimit", "i", playerid);

				}
				if(listitem == 1)
				{
					ShowGNarius(playerid);
				   // ShowPlayerDialog(playerid,5249,DIALOG_STYLE_INPUT,"Ismesti","Iveskite zaidejo varda, kuri norite ismesti.\nGalite ismesti ir atsijungusi zaideja.","Gerai","Blogai");
					return 1;
				}
				if(listitem == 2)
				{
					ShowGangNarioDialog(playerid);
					return 1;
				}
				if(listitem==3)
				{
					new query[256];
					format(query,sizeof(query),"SELECT * From `gangcars` WHERE `gang`=%i",playerDB[playerid][pgang]);
					mysql_function_query(SQL, query, true, "SQL_LoadGaujosVadui", "ii", playerid,playerDB[playerid][pgang]);
				
				}
				if(listitem==4)
				{
					new query[128];
					format(query,sizeof(query),"SELECT `Name` From `Account` WHERE `Gangas`=%i",playerDB[playerid][pgang]);
					mysql_function_query(SQL, query, true, "SQL_GangNariai", "i", playerid);
				}
				if(listitem==5)
				{
					ShowPlayerDialog(playerid, 5255, DIALOG_STYLE_LIST, "Limitai", "Sandeliai\nSaugykla", "Gerai", "Atgal");
				}
				if(listitem == 6)
				{
					new gangid = playerDB[playerid][pgang];
					if(FamilyInfo[gangid][FamilyIspejimai] == 2)
					{
						return SendInfoMessage(playerid, "Negali perleisti sios gaujos.");
					}
					ShowPlayerDialog(playerid,5250,DIALOG_STYLE_INPUT,"Perleisti","Iveskite zaidejo varda, kuriam norite perleisti.","Gerai","Blogai");
					return 1;
				}
				if(listitem==7)
				{
					new gangid = playerDB[playerid][pgang];
					if(FamilyInfo[gangid][FamilyIspejimai] == 2)
					{
						return SendInfoMessage(playerid, "Negali apleisti sios gaujos.");
					}
					ShowPlayerDialog(playerid,5248,DIALOG_STYLE_MSGBOX,"Apleisti","Ar tikrai norite apleisti savo gauja?\nPinigai grazinti nebus.","Apleisti","Atsaukti");
					return 1;
				}
				if(listitem==8)
				{
					new gangid = playerDB[playerid][pgang];
					if(FamilyInfo[gangid][FamilyIspejimai] == 2)
					{
						return SendInfoMessage(playerid, "Negali skirti pavaduotojo.");
					}
					ShowPlayerDialog(playerid,5243,DIALOG_STYLE_INPUT,"Pavaduotojas","Irasykite pavaduotojo varda(jis turi buti gaujos narys).\nJei norite nuimti pavaduotoja, irasykite \"Nera\"(be kabuciu)","Gerai","Atsaukti");
				}
			}
		
		}
		if(dialogid==5265)
		{
			new gang = playerDB[playerid][pgang];
			if(gang == -1)
				return SendInfoMessage(playerid,"Tu nepriklausai jokiai gaujai!");
			if(response)
			{
				SetPVarInt(playerid,"SelectedLimit",listitem);
				new const names[][] =
				{
					"Seklu",
					"LSD",
					"Ratu"
				};
				new msg[256];
				format(msg,256,"Iveskite nauja limita %s sandeliui.\n\n\
				Dabartinis limitas: %i vnt per 24h.\n\
				Limitai negalioja gaujos vadui bei pavaduotojui.\n\n\
				{FF0000}Leidziami limitai: 1-100",names[listitem],FamilyInfo[gang][SandelioLimitai][listitem]);
				ShowPlayerDialog(playerid,5267,DIALOG_STYLE_INPUT,"Limitai",msg,"Gerai","Atgal");
			}
			else
			{
				return ShowGangDialog(playerid);
			}
		}
		if(dialogid==5267)
		{
			new gang = playerDB[playerid][pgang];
			if(gang == -1)
				return SendInfoMessage(playerid,"Tu nepriklausai jokiai gaujai!");
			if(response)
			{
				if(!IsNumeric(inputtext)) 
				{
					SendInfoMessage(playerid,"~r~Skaiciais!");
					return ShowGangDialog(playerid);
				}
				new kiek = strval(inputtext);
				if(kiek < 1 || kiek > 100) 
				{
					SendInfoMessage(playerid,"~r~Netinkama suma!");
					return ShowGangDialog(playerid);
				}
				SendInfoMessage(playerid,"~g~Limitas sekmingai nustatytas!");
				FamilyInfo[gang][SandelioLimitai][GetPVarInt(playerid,"SelectedLimit")] = kiek;
				new msgas[1024];
				format(msgas,1024,"Nark\tVieta\tLimitas (24h)\n\
					Seklos\tSandelis\t{FF0000}%i\n\
					LSD\tSandelis\t{FF0000}%i\n\
					Ratai\tSandelis\t{FF0000}%i",
					FamilyInfo[gang][SandelioLimitai][0],
					FamilyInfo[gang][SandelioLimitai][1],
					FamilyInfo[gang][SandelioLimitai][2]);
				ShowPlayerDialog(playerid, 5265, DIALOG_STYLE_TABLIST_HEADERS, "Limitai", msgas, "Gerai", "Atgal");
				return 1;
			}
			else
			{
				return ShowGangDialog(playerid);
			}
		}
		if(dialogid==5266)
		{
			new gang = playerDB[playerid][pgang];
			if(gang == -1)
				return SendInfoMessage(playerid,"Tu nepriklausai jokiai gaujai!");
			if(response)
			{
				SetPVarInt(playerid,"SelectedLimit",listitem);
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
				new msg[256];
				format(msg,256,"Iveskite nauja limita %s saugyklai.\n\n\
				Dabartinis limitas: %i vnt per 24h.\n\
				Limitai negalioja gaujos vadui bei pavaduotojui.\n\n\
				{FF0000}Leidziami limitai: 1-10000",names[listitem],FamilyInfo[gang][SaugyklosLimitai][listitem]);
				ShowPlayerDialog(playerid,5268,DIALOG_STYLE_INPUT,"Limitai",msg,"Gerai","Atgal");
			}
			else
			{
				return ShowGangDialog(playerid);
			}
		}
		if(dialogid==5268)
		{
			new gang = playerDB[playerid][pgang];
			if(gang == -1)
				return SendInfoMessage(playerid,"Tu nepriklausai jokiai gaujai!");
			if(response)
			{
				if(!IsNumeric(inputtext)) 
				{
					SendInfoMessage(playerid,"~r~Skaiciais!");
					return ShowGangDialog(playerid);
				}
				new kiek = strval(inputtext);
				if(kiek < 1 || kiek > 10000) 
				{
					SendInfoMessage(playerid,"~r~Netinkama suma!");
					return ShowGangDialog(playerid);
				}
				SendInfoMessage(playerid,"~g~Limitas sekmingai nustatytas!");
				FamilyInfo[gang][SaugyklosLimitai][GetPVarInt(playerid,"SelectedLimit")] = kiek;
				new msgas[1024];
					
				format(msgas,1024,"Item\tVieta\tPadeta\tLimitas (24h)\n\
					LSD\tSaugykla\t%i\t{FF0000}%i\n\
					Ratai\tSaugykla\t%i\t{FF0000}%i\n\
					Seklos\tSaugykla\t%i\t{FF0000}%i\n\
					Zole\tSaugykla\t%i\t{FF0000}%i\n\
					Amfetaminas\tSaugykla\t%i\t{FF0000}%i\n\
					Deagle\tSaugykla\t%i\t{FF0000}%i\n\
					Sniper Rifle\tSaugykla\t%i\t{FF0000}%i\n\
					Combat Shotgun\tSaugykla\t%i\t{FF0000}%i\n\
					AK-47\tSaugykla\t%i\t{FF0000}%i\n\
					MP5\tSaugykla\t%i\t{FF0000}%i",
					FamilyInfo[gang][FamilySaugykla][0],
					FamilyInfo[gang][SaugyklosLimitai][0],
					FamilyInfo[gang][FamilySaugykla][1],
					FamilyInfo[gang][SaugyklosLimitai][1],
					FamilyInfo[gang][FamilySaugykla][2],
					FamilyInfo[gang][SaugyklosLimitai][2],
					FamilyInfo[gang][FamilySaugykla][3],
					FamilyInfo[gang][SaugyklosLimitai][3],
					FamilyInfo[gang][FamilySaugykla][4],
					FamilyInfo[gang][SaugyklosLimitai][4],
					FamilyInfo[gang][FamilySaugykla][5],
					FamilyInfo[gang][SaugyklosLimitai][5],
					FamilyInfo[gang][FamilySaugykla][6],
					FamilyInfo[gang][SaugyklosLimitai][6],
					FamilyInfo[gang][FamilySaugykla][7],
					FamilyInfo[gang][SaugyklosLimitai][7],
					FamilyInfo[gang][FamilySaugykla][8],
					FamilyInfo[gang][SaugyklosLimitai][8],
					FamilyInfo[gang][FamilySaugykla][9],
					FamilyInfo[gang][SaugyklosLimitai][9]);
				ShowPlayerDialog(playerid, 5266, DIALOG_STYLE_TABLIST_HEADERS, "Limitai", msgas, "Gerai", "Atgal");
				return 1;
			}
			else
			{
				return ShowGangDialog(playerid);
			}
		}
		if(dialogid==5255)
		{
			if(response)
			{
				new gang = playerDB[playerid][pgang];
				if(gang == -1)
					return SendInfoMessage(playerid,"Tu nepriklausai jokiai gaujai!");
				if(listitem == 0) // sandeliai
				{
					new msgas[1024];
					
					format(msgas,1024,"Nark\tVieta\tLimitas (24h)\n\
						Seklos\tSandelis\t{FF0000}%i\n\
						LSD\tSandelis\t{FF0000}%i\n\
						Ratai\tSandelis\t{FF0000}%i",
						FamilyInfo[gang][SandelioLimitai][0],
						FamilyInfo[gang][SandelioLimitai][1],
						FamilyInfo[gang][SandelioLimitai][2]);
					ShowPlayerDialog(playerid, 5265, DIALOG_STYLE_TABLIST_HEADERS, "Limitai", msgas, "Gerai", "Atgal");
				}
				else
				{
					new msgas[1024];
					
					format(msgas,1024,"Item\tVieta\tPadeta\tLimitas (24h)\n\
						LSD\tSaugykla\t%i\t{FF0000}%i\n\
						Ratai\tSaugykla\t%i\t{FF0000}%i\n\
						Seklos\tSaugykla\t%i\t{FF0000}%i\n\
						Zole\tSaugykla\t%i\t{FF0000}%i\n\
						Amfetaminas\tSaugykla\t%i\t{FF0000}%i\n\
						Deagle\tSaugykla\t%i\t{FF0000}%i\n\
						Sniper Rifle\tSaugykla\t%i\t{FF0000}%i\n\
						Combat Shotgun\tSaugykla\t%i\t{FF0000}%i\n\
						AK-47\tSaugykla\t%i\t{FF0000}%i\n\
						MP5\tSaugykla\t%i\t{FF0000}%i",
						FamilyInfo[gang][FamilySaugykla][0],
						FamilyInfo[gang][SaugyklosLimitai][0],
						FamilyInfo[gang][FamilySaugykla][1],
						FamilyInfo[gang][SaugyklosLimitai][1],
						FamilyInfo[gang][FamilySaugykla][2],
						FamilyInfo[gang][SaugyklosLimitai][2],
						FamilyInfo[gang][FamilySaugykla][3],
						FamilyInfo[gang][SaugyklosLimitai][3],
						FamilyInfo[gang][FamilySaugykla][4],
						FamilyInfo[gang][SaugyklosLimitai][4],
						FamilyInfo[gang][FamilySaugykla][5],
						FamilyInfo[gang][SaugyklosLimitai][5],
						FamilyInfo[gang][FamilySaugykla][6],
						FamilyInfo[gang][SaugyklosLimitai][6],
						FamilyInfo[gang][FamilySaugykla][7],
						FamilyInfo[gang][SaugyklosLimitai][7],
						FamilyInfo[gang][FamilySaugykla][8],
						FamilyInfo[gang][SaugyklosLimitai][8],
						FamilyInfo[gang][FamilySaugykla][9],
						FamilyInfo[gang][SaugyklosLimitai][9]);
					ShowPlayerDialog(playerid, 5266, DIALOG_STYLE_TABLIST_HEADERS, "Limitai", msgas, "Gerai", "Atgal");
				}
			}
			else
			{
				return ShowGangDialog(playerid);
			}
		}
		if(dialogid==5243)
		{
			if(response)
			{
				toupper(inputtext[0]);
				if(0==strcmp(inputtext,"Nera",false))
				{
					format(FamilyInfo[playerDB[playerid][pgang]][FamilySubstitute],24,"Nera");
					SendInfoMessage(playerid,"Sekmingai nuemei pavaduotojo statusa!");
				}
				else
				{
					new id = GetIdForAlgos(inputtext);
					if( id == playerid)
					{
						SendInfoMessage(playerid,"~r~Saves paversti pavaduotoju negali.");
					}
					else if(id == INVALID_PLAYER_ID)
						SendInfoMessage(playerid,"Zaidejas neprisijunges");
					else
					{
						if(playerDB[id][pgang] != playerDB[playerid][pgang]) return SendInfoMessage(playerid,"~r~Zaidejas ne jusu gaujoje.");
						format(FamilyInfo[playerDB[playerid][pgang]][FamilySubstitute],24,ReturnName(id));
						SendInfoMessage(playerid,"Pavaduotojas paskirtas!");
						ProcessAchievement(id, 114);
					}
				}
			}
			return ShowGangDialog(playerid);
		}
		if(dialogid==5254)
		{
			if(response)
			{
				if(listitem == 0) return ShowPlayerDialog(playerid, 5256, DIALOG_STYLE_LIST, "Skinai","Pirmas(Vyr.)\nAntras(Vyr.)\nTrecias(Vyr.)\nKetvirtas(Mot.)","Taip","Ne");
				if(listitem == 1)
				{
					new gangas = playerDB[playerid][pgang];
					if(gangas == -1) return 1;
					if(IsPlayerInDynamicArea(playerid,FamilyInfo[gangas][FamilyZone][2]))
					SavePlayerData(playerid, false);

					ShowGangNarioDialog(playerid);
					return 1;
				}
				if(listitem == 2)
				{
					if(GetPlayerMoneyA(playerid) < COST_GINKLAI_GAUJA)
					{
						SendInfoMessage(playerid,"~r~Jus neturite ["#COST_GINKLAI_GAUJA"EUR]");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_GINKLAI_GAUJA);
					SendInfoMessage(playerid,"Nusipirkai ginklus!");
					//ResetPlayerWeapons(playerid);
					GivePlayerWeaponEx(playerid,25,100);		
					GivePlayerWeaponEx(playerid,22,100);
					GivePlayerWeaponEx(playerid,33,50);
					GivePlayerWeaponEx(playerid,1,1);
					ShowGangNarioDialog(playerid);
				}
				if(listitem == 3)
				{
					new title[50];
					new id=playerDB[playerid][pgang];
					new tagai = 0;
					for(new i;i<sizeof(GaujuTagai);i++)
					{
						if(TagOwnedBy[i] == id)
						{
							tagai++;
						}
					}

					format(title,sizeof(title),"Gaujos fonde: %i€ (%i tagai)",FamilyInfo[id][FamilyFunds],tagai);
				//	new msg[256];
					if(0==strcmp(FamilyInfo[playerDB[playerid][pgang]][FamilySubstitute],ReturnName(playerid),true) || 0==strcmp(FamilyInfo[playerDB[playerid][pgang]][FamilyLeader],ReturnName(playerid),true))
					{
						ShowPlayerDialog(playerid,5257,DIALOG_STYLE_LIST,title,"Padëti á fondà\nAtaskaitos\nPaimti ið fondo\n{FF0000}Nustatyti limità","Gerai","Atgal");
					}
					else
					{
						ShowPlayerDialog(playerid,5257,DIALOG_STYLE_LIST,title,"Padëti á fondà\nAtaskaitos\nPaimti ið fondo","Gerai","Atgal");
					}
				
				}
				if(listitem == 4) // saugykla
				{
					ShowGangNarioDialog(playerid,1);
				}
				if(listitem == 5)
				{
					new query[256];
					format(query,sizeof(query),"SELECT * From `gangcars` WHERE `gang`=%i",playerDB[playerid][pgang]);
					mysql_function_query(SQL, query, true, "SQL_LoadGaujosVadui", "ii", playerid,playerDB[playerid][pgang]);
					return 1;
				}
				if(listitem == 6)
				{
					if(playerDB[playerid][pgang]==-1) return 1;
					new pi = playerDB[playerid][pgang];
					if(0==strcmp(FamilyInfo[pi][FamilyLeader],ReturnName(playerid),true)) return SendInfoMessage(playerid,"Vadas negali palikti gaujos!");


					new msg[128];
					format(msg,128,"[gauja] %s paliko mus!",ReturnName(playerid));

					SetPVarInt(playerid,"LeftGang",1);
					SendMessageToFamily(playerDB[playerid][pgang],COLOR,msg);
					if(0==strcmp(FamilyInfo[playerDB[playerid][pgang]][FamilySubstitute],ReturnName(playerid),true)) format(FamilyInfo[playerDB[playerid][pgang]][FamilySubstitute],24,"Nera");
					playerDB[playerid][pgang]=-1;
					SetPlayerSkin(playerid,playerDB[playerid][drabuziai]);
					SavePlayerData(playerid,true);
					return 1;
				}
			}
		
		}
		if(dialogid==5277)
		{
			if(playerDB[playerid][pgang]==-1) return 1;
			new gang = playerDB[playerid][pgang];
			new msgas[512];
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
			SetPVarInt(playerid,"SaugyklosId",listitem);

			if(response) // paimti
			{
				if(listitem >= 10 || FamilyInfo[gang][FamilySaugykla][listitem] < 1)
				{
					SendInfoMessage(playerid,"~r~Saugykloje siuo metu to neturime!");
					return ShowGangNarioDialog(playerid);
				}
				
				format(msgas,512, "Iveskite %s kieki, kuri norite paimti.\n\nSiuo metu turime: %i vnt.\n{FF0000}Dienos limitas: %i vnt.",
					names[listitem],
					FamilyInfo[gang][FamilySaugykla][listitem],
					FamilyInfo[gang][SaugyklosLimitai][listitem]);
				ShowPlayerDialog(playerid, 5278, DIALOG_STYLE_INPUT, "Paimti", msgas, "Gerai", "Atgal");
			}
			else // padeti
			{
				format(msgas,512, "Iveskite %s kieki, kuri norite padeti.\n\nSiuo metu turime: %i vnt.",
					names[listitem],
					FamilyInfo[gang][FamilySaugykla][listitem]);
				ShowPlayerDialog(playerid, 5279, DIALOG_STYLE_INPUT, "Padeti", msgas, "Gerai", "Atgal");
			
			}
		}
		if(dialogid==5278)
		{
			if(response)
			{
				new gang = playerDB[playerid][pgang];
				if(gang == -1)
					return 1;
				new idas = GetPVarInt(playerid,"SaugyklosId");
				if(!IsNumeric(inputtext))
				{
					SendInfoMessage(playerid,"Skaiciais!");
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
				new kiek = strval(inputtext);
				if(!kiek)
				{
					SendInfoMessage(playerid,"Skaiciais!");
					return ShowGangNarioDialog(playerid, 1);
				}
				new file[256];
				format(file,sizeof(file),"SELECT SUM(`Variable`) from `Logs` WHERE Zaidejas='%s' AND Veiksmas='Paeme is saugyklos(%s)' AND Data > SUBDATE(NOW(), INTERVAL 23 HOUR)",ReturnName(playerid),names[idas]);
				mysql_function_query(SQL, file, true, "SQL_LimitSaugykla", "iii", playerid, idas, kiek);
			}
			else
			{
				return ShowGangNarioDialog(playerid);
			}
		}
		if(dialogid==5279)
		{
			if(response)
			{
				new gang = playerDB[playerid][pgang];
				if(gang == -1)
					return 1;
				new idas = GetPVarInt(playerid,"SaugyklosId");
				if(!IsNumeric(inputtext))
				{
					SendInfoMessage(playerid,"Skaiciais!");
					return ShowGangNarioDialog(playerid, 1);
				}
				new kiek = strval(inputtext);
				if(!kiek)
				{
					SendInfoMessage(playerid,"Skaiciais!");
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
						if(playerDB[playerid][lsd] < kiek)
						{
							SendInfoMessage(playerid,"~r~Tu tiek neturi!");
							ShowGangNarioDialog(playerid,1);
							return 1;
						}
						playerDB[playerid][lsd] -= kiek;
					}
					case 1:
					{
						if(playerDB[playerid][ratai] < kiek)
						{
							SendInfoMessage(playerid,"~r~Tu tiek neturi!");
							ShowGangNarioDialog(playerid,1);
							return 1;
						}
						playerDB[playerid][ratai] -= kiek;
					}
					case 2:
					{
						if(playerDB[playerid][seklos] < kiek)
						{
							SendInfoMessage(playerid,"~r~Tu tiek neturi!");
							ShowGangNarioDialog(playerid,1);
							return 1;
						}
						playerDB[playerid][seklos] -= kiek;
					}
					case 3:
					{
						if(playerDB[playerid][zole] < kiek)
						{
							SendInfoMessage(playerid,"~r~Tu tiek neturi!");
							ShowGangNarioDialog(playerid,1);
							return 1;
						}
						playerDB[playerid][zole] -= kiek;
					}
					case 4:
					{
						if(playerDB[playerid][amfetaminas] < kiek)
						{
							SendInfoMessage(playerid,"~r~Tu tiek neturi!");
							ShowGangNarioDialog(playerid,1);
							return 1;
						}
						playerDB[playerid][amfetaminas] -= kiek;
					}
					case 5,6,7,8,9:
					{
						new const gunai[] = {24,34,27,30,29};
						new weap = gunai[idas-5];

						new slot = GetWeaponsSlot(weap);
						new weaponidas, kiekturi;

						GetPlayerWeaponData(playerid,slot,weaponidas,kiekturi);
						
						if(weaponidas != weap || kiekturi < kiek)
						{
							SendInfoMessage(playerid, "Tu tiek neturi!");
							ShowGangNarioDialog(playerid,1);
							return 1;
						}

						if(GunData[playerid][slot][0] != weap)
						{
							AC_Kick(playerid,"Ginklai 3");
							return 1;
						}
						if(GunData[playerid][slot][1] < kiekturi)
						{
							AC_Kick(playerid,"Ginklai 4");
							return 1;
						}

						GivePlayerWeaponEx(playerid,weap,-kiek);

					}
					default:
					{
						return SendInfoMessage(playerid,"~r~Ivyko klaida!");
					}
				}

				FamilyInfo[gang][FamilySaugykla][idas] += kiek;
				SendInfoMessage(playerid,"~g~Sekmingai padejai i saugykla!");
				new msg1[50];
				format(msg1,sizeof(msg1),"Padejo i saugykla(%s)",names[idas]);
				MLog(playerid,msg1,"i", kiek);
				return ShowGangNarioDialog(playerid,1);
			}
			else
			{
				return ShowGangNarioDialog(playerid);
			}
		}
		if(dialogid==5257)
		{
			if(response)
			{
				if(listitem==0)
				{
					if(GetPlayerScore(playerid) < 100) return SendInfoMessage(playerid,"Padeti i fonda galite tik nuo 100xp!");
					ShowPlayerDialog(playerid,5258,DIALOG_STYLE_INPUT,"Padeti i fonda","Iveskite pinigu suma, kuria norite paaukoti gaujai.","Gerai","Atsaukti");
				}
				else if(listitem==1)
				{
					new msg1[50],msg2[50];
					format(msg1,sizeof(msg1),"Padejo i fonda(%i)",playerDB[playerid][pgang]);
					format(msg2,sizeof(msg2),"Paeme is fondo(%i)",playerDB[playerid][pgang]);
					Ataskaita(playerid, msg1,msg2);
				}
				else if(listitem==2)
				{
					new msg[127];
					format(msg,127,"Iveskite pinigu suma, kuria norite paimti is fondo.\n{FFFFFF}Gaujos nariai gali paimti iki {FF0000}%i€{FFFFFF} per dienà.",FamilyInfo[playerDB[playerid][pgang]][FamilyLimit]);
					ShowPlayerDialog(playerid,5259,DIALOG_STYLE_INPUT,"Paimti is fondo",msg,"Gerai","Atsaukti");
				}
				else if(listitem == 3)
				{
					ShowPlayerDialog(playerid,5260,DIALOG_STYLE_INPUT,"Padeti i fonda","Iveskite pinigu suma, kuria gaujos nariai gales paimti per diena. Tinkamos reiksmes 0-100.000€","Gerai","Atsaukti");
				}
				return 1;
			}
			else
			{
				return ShowGangNarioDialog(playerid);
			}
		}
		if(dialogid==5260)
		{
			if(response)
			{
				if(!IsNumeric(inputtext)) return SendInfoMessage(playerid,"~r~Skaiciais!");
				new kiek = strval(inputtext);
				if(kiek < 0 || kiek > 100000) return SendInfoMessage(playerid,"~r~Netinkama suma!");
				FamilyInfo[playerDB[playerid][pgang]][FamilyLimit]= kiek;
				SendInfoMessage(playerid,"Sekmingai nustatei fondo limita!");
				SaveFamily(playerDB[playerid][pgang]);
			}
			return 1;
		}
		if(dialogid==5258)
		{
			if(response)
			{
				if(!IsNumeric(inputtext)) return SendInfoMessage(playerid,"~r~Skaiciais!");
				new kiek = strval(inputtext);
				if(kiek <=0) return SendInfoMessage(playerid,"~r~Skaiciais!");
				if(kiek > GetPlayerMoneyA(playerid)) return SendInfoMessage(playerid,"~r~Tu tiek neturi!");
				
				GivePlayerMoneyA(playerid,-kiek);
				FamilyInfo[playerDB[playerid][pgang]][FamilyFunds]+=kiek;
				new msg1[50];
				format(msg1,sizeof(msg1),"Padejo i fonda(%i)",playerDB[playerid][pgang]);
				MLog(playerid,msg1,"i", kiek);
				SendInfoMessage(playerid,"Sekmingai paaukojai gaujos fondui!");
				SaveFamily(playerDB[playerid][pgang]);
				return ShowGangNarioDialog(playerid);
			}
			else
			{
				return ShowGangNarioDialog(playerid);

			}
		}
		if(dialogid==5259)
		{
			if(response)
			{
				if(!IsNumeric(inputtext)) return SendInfoMessage(playerid,"~r~Skaiciais!");
				new kiek = strval(inputtext);
				if(kiek <=0) return SendInfoMessage(playerid,"~r~Skaiciais!");
				if(kiek > FamilyInfo[playerDB[playerid][pgang]][FamilyFunds]) return SendInfoMessage(playerid,"~r~Gaujos fonde tiek nera!");
				
				if(0==strcmp(FamilyInfo[playerDB[playerid][pgang]][FamilySubstitute],ReturnName(playerid),true) || 0==strcmp(FamilyInfo[playerDB[playerid][pgang]][FamilyLeader],ReturnName(playerid),true))
				{

					GivePlayerMoneyA(playerid,kiek);
					FamilyInfo[playerDB[playerid][pgang]][FamilyFunds]-=kiek;
					new msg1[50];
					format(msg1,sizeof(msg1),"Paeme is fondo(%i)",playerDB[playerid][pgang]);
					MLog(playerid,msg1,"i", kiek);
					SendInfoMessage(playerid,"Sekmingai paemei pinigus is gaujos fondo!");
					SaveFamily(playerDB[playerid][pgang]);

				}
				else
				{
					new file[256];
					format(file,sizeof(file),"SELECT SUM(`Variable`) from `Logs` WHERE Zaidejas='%s' AND Veiksmas='Paeme is fondo(%i)' AND Data > SUBDATE(NOW(), 1)",ReturnName(playerid),playerDB[playerid][pgang]);
					mysql_function_query(SQL, file, true, "SQL_LimitGangMoney", "ii", playerid,kiek);

				}
			}
		}
		if(dialogid==5256)
		{
			if(response) {
				SetPlayerSkin(playerid,FamilySkins[playerDB[playerid][pgang]][listitem]);
				playerDB[playerid][drabuziai] = FamilySkins[playerDB[playerid][pgang]][listitem];
				playerDB[playerid][uniformd] = false;
			} 
			else
			{
				return 1;
			}
		}

		if(dialogid==5252)
		{
			if(response)
			{
				if(listitem == 0)
				{
					for(new pi;pi<MAX_FAMILY;pi++)
					{
						if(FamilyInfo[pi][FamilyPickup] == playerDB[playerid][rid][6])
						{
							if(0==strcmp(FamilyInfo[pi][FamilyLeader],"Nera",true))
							{
								new msg[128];
								format(msg,128,"%s\nPirkti Gauja ("#COST_GANG" €)",FamilyInfo[pi][FamilyName]);
								return ShowPlayerDialog(playerid, 5252, DIALOG_STYLE_LIST, "Gauja",msg,"Taip","Ne");
							}
						}
					}
				}
				if(listitem == 1)
				{
					for(new pi;pi<MAX_FAMILY;pi++)
					{
						if(FamilyInfo[pi][FamilyPickup] == playerDB[playerid][rid][6])
						{
							if(GetPlayerMoneyA(playerid) < COST_GANG) return SendInfoMessage(playerid,"~r~Nepakanka pinigu!");
							if(playerDB[playerid][pgang]!= -1) return SendInfoMessage(playerid,"~r~Tu jau turi gauja!");
							if(strcmp(FamilyInfo[pi][FamilyLeader],"Nera",true)) return SendInfoMessage(playerid,"~r~Si gauja jau nupirkta!");
							GivePlayerMoneyA(playerid, -COST_GANG);
							new msg[128];
							format(msg,128," * Sekmingai nusipirkai gauja %s uz "#COST_GANG"EUR!",FamilyInfo[pi][FamilyName]);
							SendInfoMessage(playerid,msg);
							playerDB[playerid][pgang]=pi;
							ProcessAchievement(playerid, 114);
							format(FamilyInfo[pi][FamilyLeader],MAX_PLAYER_NAME,"%s",ReturnName(playerid));
							return 1;
						}
					}
				
				}
			}
		
		}
		if(dialogid==610)
		{
			if(response)
			{
				ShowPlayerDialog(playerid,611,DIALOG_STYLE_LIST,"Bankas","Paiimti pinigus\nPadeti pinigus","Rinktis","Atgal");
				return 1;
			}
			else
			{
				//playerDB[playerid][cekis]=0;
				SendInfoMessage(playerid,"Geros dienos!");
				return 1;
			}// ids:605,616,410,610,610
		}
		if(dialogid==605)
		{
			if(response)
			{
				ShowDarbuotojus(playerid);
			}
			else
			{
				//playerDB[playerid][cekis]=0;
				SendInfoMessage(playerid,"Geros dienos!");
				return 1;
			}// ids:605,616,410,610,610
		}

		if(dialogid==611)
		{
			if(!response)
			{
				new msg[128];
				format(msg,sizeof(msg)," Jusu saskaitos balansas {33FF33} %i€.\n{FFFFFF} Norite testi?",playerDB[playerid][banke]);
				ShowPlayerDialog(playerid, 610, DIALOG_STYLE_MSGBOX,"Bankas", msg, "Testi", "Atsaukti");
				return 1;
			}
			else if(response)
			{
				if(listitem == 0)
				{
					ShowPlayerDialog(playerid, 612, DIALOG_STYLE_INPUT,"Bankas", "Iveskite pinigu suma, kuria norite paimti.", "Testi", "Atsaukti");
					return 1;
				}
				else if(listitem == 1)
				{
					ShowPlayerDialog(playerid, 613, DIALOG_STYLE_INPUT,"Bankas", "Iveskite pinigu suma, kuria norite padeti.", "Testi", "Atsaukti");
					return 1;
				}
			}
		}

		if(dialogid==612)
		{
			if(!response)
			{
				new msg[128];
				format(msg,sizeof(msg)," Jusu saskaitos balansas {33FF33} %i€.\n{FFFFFF} Norite testi?",playerDB[playerid][banke]);
				ShowPlayerDialog(playerid, 610, DIALOG_STYLE_MSGBOX,"Bankas", msg, "Testi", "Atsaukti");
				return 1;
			}
			else
			{
				
				new kiek = StringToInt(inputtext);
				if(!IsNumeric(inputtext))
				{
					new msg[128];
					format(msg,sizeof(msg)," Jusu saskaitos balansas {33FF33} %i€.\n{FFFFFF} Norite testi?",playerDB[playerid][banke]);
					ShowPlayerDialog(playerid, 610, DIALOG_STYLE_MSGBOX,"Bankas", msg, "Testi", "Atsaukti");
					return SendInfoMessage(playerid,"~r~Skaiciais!");
				}
				if(kiek == 0)
				{
					new msg[128];
					format(msg,sizeof(msg)," Jusu saskaitos balansas {33FF33} %i€.\n{FFFFFF} Norite testi?",playerDB[playerid][banke]);
					ShowPlayerDialog(playerid, 610, DIALOG_STYLE_MSGBOX,"Bankas", msg, "Testi", "Atsaukti");
					return SendInfoMessage(playerid,"~r~0 €?");
				}
				if(playerDB[playerid][banke] < kiek) return SendInfoMessage(playerid,"~r~Jus tiek neturite");
				playerDB[playerid][banke]-=kiek;
				GivePlayerMoneyA(playerid, kiek);
				new msg[128];
				format(msg,sizeof(msg)," Jusu saskaitos balansas {33FF33} %i€.\n{FFFFFF} Norite testi?",playerDB[playerid][banke]);
				ShowPlayerDialog(playerid, 610, DIALOG_STYLE_MSGBOX,"Bankas", msg, "Testi", "Atsaukti");
				return 1;
			}

		}
		if(dialogid==613)
		{
			if(!response)
			{
				new msg[128];
				format(msg,sizeof(msg)," Jusu saskaitos balansas {33FF33} %i€.\n{FFFFFF} Norite testi?",playerDB[playerid][banke]);
				ShowPlayerDialog(playerid, 610, DIALOG_STYLE_MSGBOX,"Bankas", msg, "Testi", "Atsaukti");
				return 1;
			}
			else
			{
				new kiek = StringToInt(inputtext);
				if(!IsNumeric(inputtext))
				{
					new msg[128];
					format(msg,sizeof(msg)," Jusu saskaitos balansas {33FF33} %i€.\n{FFFFFF} Norite testi?",playerDB[playerid][banke]);
					ShowPlayerDialog(playerid, 610, DIALOG_STYLE_MSGBOX,"Bankas", msg, "Testi", "Atsaukti");
					return SendInfoMessage(playerid,"~r~Skaiciais!");
				}
				if(kiek == 0)
				{
					new msg[128];
					format(msg,sizeof(msg)," Jusu saskaitos balansas {33FF33} %i€.\n{FFFFFF} Norite testi?",playerDB[playerid][banke]);
					ShowPlayerDialog(playerid, 610, DIALOG_STYLE_MSGBOX,"Bankas", msg, "Testi", "Atsaukti");
					return SendInfoMessage(playerid,"~r~0 EUR?");
				}
				if(playerDB[playerid][pinigai] < kiek) return SendInfoMessage(playerid,"~r~Jus tiek neturite");
				playerDB[playerid][banke]+=kiek;
				GivePlayerMoneyA(playerid, -kiek);
				new msg[128];
				format(msg,sizeof(msg)," Jusu saskaitos balansas {33FF33} %i€.\n{FFFFFF} Norite testi?",playerDB[playerid][banke]);
				ShowPlayerDialog(playerid, 610, DIALOG_STYLE_MSGBOX,"Bankas", msg, "Testi", "Atsaukti");
				return 1;
			}

		}
		if(dialogid==614)
		{
			if(!response)
			{
				new msg[256];
				if(!playerDB[playerid][kortele]) return SendInfoMessage(playerid,"Jus neturite banko saskaitos.~n~Pasiimkite ja kitoje kasoje.");
				format(msg,sizeof(msg),"{FFFFFF}Pervesti pinigus. Balansas: {33FF33}%i€\n{FFFFFF}Pervesti kreditus. Balansas: {33FF33}%i kred",playerDB[playerid][banke],playerDB[playerid][kreditai]);
				ShowPlayerDialog(playerid, 616, DIALOG_STYLE_MSGBOX,"Bankas", msg, "Taip", "Ne");
				return 1;
			}
			else
			{
				if(GetPlayerScore(playerid) < 100) return SendInfoMessage(playerid,"~r~Turi per mazai XP!");
				new kiek = StringToInt(inputtext);
				if(!IsNumeric(inputtext))
				{	
					SendInfoMessage(playerid,"~r~Skaiciais!");
					new msg[256];
					if(!playerDB[playerid][kortele]) return SendInfoMessage(playerid,"Jus neturite banko saskaitos.~n~Pasiimkite ja kitoje kasoje.");
					format(msg,sizeof(msg),"{FFFFFF}Pervesti pinigus. Balansas: {33FF33}%i€\n{FFFFFF}Pervesti kreditus. Balansas: {33FF33}%i kred",playerDB[playerid][banke],playerDB[playerid][kreditai]);
					ShowPlayerDialog(playerid, 616, DIALOG_STYLE_MSGBOX,"Bankas", msg, "Taip", "Ne");
					return 1;
				}
				if(kiek == 0) return SendInfoMessage(playerid,"~r~0 EUR ?");
				if(playerDB[playerid][banke] < kiek) return SendInfoMessage(playerid,"~r~Banke Jus tiek neturite.");
				playerDB[playerid][perveda]=kiek;
				new msg[128];
				format(msg,sizeof(msg)," Norite pervesti %i€.\n Iveskite PILNA Zmogaus kuriam norite pervesti varda.\nOperacijos mokestis : 1%%.",playerDB[playerid][perveda]);
				ShowPlayerDialog(playerid, 615, DIALOG_STYLE_INPUT,"Bankas", msg, "Testi", "Atsaukti");
				return 1;
			}

		}

		if(dialogid==4443)
		{
			if(response)
			{
				if(playerDB[playerid][pinigai] < 20) return SendInfoMessage(playerid,"~r~Jus neturite 20EUR.");

				new tname[MAX_PLAYER_NAME];
				new tid = GetPlayeridMid(inputtext);

				if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_NONE)
				{
					SendClientMessage(playerid,COLOR,"* Kai baigsite ragelá padëkite su ( /bai ).");
					SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
					SetPlayerAttachedObject(playerid, TEL_SLOT, 330, 6); // 4 = attachment slot, 330 = cellphone model, 6 = right hand
				}

				if(tid==INVALID_PLAYER_ID)
				{
					SendInfoMessage(playerid,"Operatorius: Tokio vardo nera.");
					return 1;
				}


				if(tid==playerid)
				{
					SendInfoMessage(playerid,"Operatorius: Linija uzmita.");
					return 1;
				}
				if(!playerDB[tid][telon]) return SendInfoMessage(playerid,"~r~Telefonas yra isjungtas.");
				if(playerDB[tid][ikalintas]) return SendInfoMessage(playerid,"~r~Telefonas yra uz rysio zonos ribu.");
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
		}
		if(dialogid==616)
		{
			if(response)
			{
				if(listitem==0)
					ShowPlayerDialog(playerid, 614, DIALOG_STYLE_INPUT,"Bankas", "Áveskite pinigø sumà, kurià norite pervesti.\nDëmesio! Pinigus galite pervesti ir atsijungusiam þaidëjui.\nOperacijos mokestis: 1% nuo pervedamos sumos.", "Testi", "Atsaukti");
				else
				{
					if(GetPlayerMoneyA(playerid) < 1000) return SendInfoMessage(playerid,"Kreditu pervedimas kainuoja 1000EUR.");
					ShowPlayerDialog(playerid, 617, DIALOG_STYLE_INPUT,"Bankas", "Áveskite skaièiø kreditø, kurá norite pervesti.\nDëmesio! Kreditus galite pervesti ir atsijungusiam þaidëjui.\nOperacijos mokestis: 1000€", "Testi", "Atsaukti");

				}
				return 1;
			}
			else
			{
				//playerDB[playerid][cekis]=0;
				SendInfoMessage(playerid,"Geros dienos!");
				return 1;
			}// ids:605,616,410,610,610
		}
		if(dialogid==617)
		{
			if(!response)
				return SendInfoMessage(playerid,"Geros dienos!");
			if(GetPlayerScore(playerid) < 100) return SendInfoMessage(playerid,"~r~Tu turi per mazai XP!");
			new kiek = StringToInt(inputtext);
			if(!IsNumeric(inputtext))
			{	
				SendInfoMessage(playerid,"~r~Skaiciais!");
				new msg[256];
				if(!playerDB[playerid][kortele]) return SendInfoMessage(playerid,"Jus neturite banko saskaitos.~n~Pasiimkite ja kitoje kasoje.");
				format(msg,sizeof(msg),"{FFFFFF}Pervesti pinigus. Balansas: {33FF33}%i€\n{FFFFFF}Pervesti kreditus. Balansas: {33FF33}%i kred",playerDB[playerid][banke],playerDB[playerid][kreditai]);
				ShowPlayerDialog(playerid, 616, DIALOG_STYLE_LIST,"Bankas", msg, "Taip", "Ne");
				return 1;
			}
			if(kiek == 0) return SendInfoMessage(playerid,"~r~0 kreditu?");
			if(playerDB[playerid][kreditai] < kiek) return SendInfoMessage(playerid,"~r~Jus tiek neturite.");
			playerDB[playerid][perveda]=kiek;
			new msg[128];
			format(msg,sizeof(msg)," Norite pervesti %i kreditu.\n Iveskite PILNA Zmogaus kuriam norite pervesti varda.\nOperacijos mokestis : 1000€.",playerDB[playerid][perveda]);
			ShowPlayerDialog(playerid, 618, DIALOG_STYLE_INPUT,"Bankas", msg, "Testi", "Atsaukti");
			return 1;
		}
		if(dialogid==618)
		{
			if(!response)
			{
				new msg[256];
				if(!playerDB[playerid][kortele]) return SendInfoMessage(playerid,"Jus neturite banko saskaitos.~n~Pasiimkite ja kitoje kasoje.");
				format(msg,sizeof(msg),"{FFFFFF}Pervesti pinigus. Balansas: {33FF33}%i€\n{FFFFFF}Pervesti kreditus. Balansas: {33FF33}%i kred",playerDB[playerid][banke],playerDB[playerid][kreditai]);
				ShowPlayerDialog(playerid, 616, DIALOG_STYLE_LIST,"Bankas", msg, "Taip", "Ne");
				playerDB[playerid][perveda]=0;
				return 1;
			}
			else
			{
				new id = GetIdForAlgos(inputtext);
				if( id == playerid)
				{
					SendInfoMessage(playerid,"~r~Sau pervesti negali :)");
					playerDB[playerid][perveda]=0;
					return 1;
				}
				if(id == INVALID_PLAYER_ID || playerDB[id][authstate]!=4)
				{
					new query[128];
					mysql_real_escape_string(inputtext,inputtext,_,256);
					format(query,128,"SELECT `Xp` FROM `Account` WHERE `Name` = '%s' LIMIT 1",inputtext);
					mysql_function_query(SQL, query, true, "SQL_PervestiKred", "iis", playerid,id,inputtext);
					return 1;
				}
				if(GetPlayerMoneyA(playerid) < 1000) return SendInfoMessage(playerid,"Neturi 1000EUR mokesciui");
				if(!GiveKreditai(playerid, -playerDB[playerid][perveda]))
				{
 					return SendInfoMessage(playerid,"~r~Jus neturite tiek kreditu.");
				}
				GivePlayerMoneyA(playerid, - 1000);
				MLog(playerid,"Pervede kred","is",playerDB[playerid][perveda],ReturnName(id));
				ActorServe(playerid); BusinessMoney(1000);
				GiveKreditai(id, playerDB[playerid][perveda]);
		
				SendInfoMessage(playerid,"Pervedimas sekmingas.");
				ProcessAchievement(playerid, 109);
				new msg[160];
				format(msg,sizeof(msg),"%s Jums pervede %i kreditus.",ReturnName(playerid),playerDB[playerid][perveda]);
				EAtaskaita("Bankas",inputtext,"Pervedimo ataskaita",msg);
				format(msg,sizeof(msg),"Zaidejui %s Jus pervedete %i kreditu.",inputtext,playerDB[playerid][perveda]);
				EAtaskaita("Bankas",ReturnName(playerid),"Pervedimo ataskaita",msg);
				if(!playerDB[playerid][kortele]) return SendInfoMessage(playerid,"Jus neturite banko saskaitos.~n~Pasiimkite ja kitoje kasoje.");
				format(msg,sizeof(msg),"{FFFFFF}Pervesti pinigus. Balansas: {33FF33}%i€\n{FFFFFF}Pervesti kreditus. Balansas: {33FF33}%i kred",playerDB[playerid][banke],playerDB[playerid][kreditai]);
				ShowPlayerDialog(playerid, 616, DIALOG_STYLE_LIST,"Bankas", msg, "Taip", "Ne");
				playerDB[playerid][perveda]=0;
				return 1;
			}

		}
		if(dialogid==615)
		{
			if(!response)
			{
				new msg[256];
				if(!playerDB[playerid][kortele]) return SendInfoMessage(playerid,"Jus neturite banko saskaitos.~n~Pasiimkite ja kitoje kasoje.");
				format(msg,sizeof(msg),"{FFFFFF}Pervesti pinigus. Balansas: {33FF33}%i€\n{FFFFFF}Pervesti kreditus. Balansas: {33FF33}%i kred",playerDB[playerid][banke],playerDB[playerid][kreditai]);
				ShowPlayerDialog(playerid, 616, DIALOG_STYLE_LIST,"Bankas", msg, "Taip", "Ne");
				playerDB[playerid][perveda]=0;
				return 1;
			}
			else
			{
				new id = GetIdForAlgos(inputtext);
				if( id == playerid)
				{
					SendInfoMessage(playerid,"~r~Sau pervesti negali :)");
					playerDB[playerid][perveda]=0;
					return 1;
				}
				if(playerDB[playerid][banke] < playerDB[playerid][perveda]) return SendInfoMessage(playerid,"~r~Jus neturite tiek pinigu.");
				if(id == INVALID_PLAYER_ID || playerDB[id][authstate]!=4)
				{
					new query[128];
					mysql_real_escape_string(inputtext,inputtext,_,256);
					format(query,128,"SELECT `Xp` FROM `Account` WHERE `Name` = '%s' LIMIT 1",inputtext);
					mysql_function_query(SQL, query, true, "SQL_Pervesti", "iis", playerid,id,inputtext);
					return 1;
				}
				MLog(playerid,"Pervede","is",playerDB[playerid][perveda],ReturnName(id));
				new procentas = playerDB[playerid][perveda]/100;
				//BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning]+=procentas;
				ActorServe(playerid); BusinessMoney(procentas*3/2);
				playerDB[playerid][perveda]-=procentas;
				playerDB[playerid][banke]-=(playerDB[playerid][perveda]+procentas);
				playerDB[id][banke]+=playerDB[playerid][perveda];
				
				ProcessAchievement(playerid, 109);
				SendInfoMessage(playerid,"Pervedimas sekmingas.");
				new msg[160];
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

		}

		if(dialogid==506)
		{
			if(response)
			{
				if(listitem == 0)
				{
					new turi[128];
					format(turi,sizeof(turi),"Siuo metu turite %ig. Zoles\nKiek norite pasideti?",playerDB[playerid][zole]);
					ShowPlayerDialog(playerid,516,DIALOG_STYLE_INPUT,"Padeti Zole",turi,"Padeti","Iseiti");
					return 1;
				}
				if(listitem == 1)
				{
					new turi[128];
					format(turi,sizeof(turi),"Siuo metu turite %ipak. Amfetamino\nKiek norite pasideti?",playerDB[playerid][amfetaminas]);
					ShowPlayerDialog(playerid,526,DIALOG_STYLE_INPUT,"Padeti",turi,"Padeti","Iseiti");
					return 1;
				}
				if(listitem == 2) // seklos
				{
					new turi[128];
					format(turi,sizeof(turi),"Siuo metu turite %ivnt. Seklu\nKiek norite pasideti?",playerDB[playerid][seklos]);
					ShowPlayerDialog(playerid,556,DIALOG_STYLE_INPUT,"Padeti",turi,"Padeti","Iseiti");
					return 1;
				}
				if(listitem == 3) // lsd
				{
					new turi[128];
					format(turi,sizeof(turi),"Siuo metu turite %ivnt. LSD\nKiek norite pasideti?",playerDB[playerid][lsd]);
					ShowPlayerDialog(playerid,566,DIALOG_STYLE_INPUT,"Padeti",turi,"Padeti","Iseiti");
					return 1;
				}
				if(listitem == 4) // ratai
				{
					new turi[128];
					format(turi,sizeof(turi),"Siuo metu turite %ivnt. Ratu\nKiek norite pasideti?",playerDB[playerid][ratai]);
					ShowPlayerDialog(playerid,576,DIALOG_STYLE_INPUT,"Padeti",turi,"Padeti","Iseiti");
					return 1;
				}
				if(listitem == 5)
				{
					new turi[128];
					format(turi,sizeof(turi),"Siuo metu turite %i€ Pinigu.\nKiek norite pasideti?",GetPlayerMoneyA(playerid));
					ShowPlayerDialog(playerid,536,DIALOG_STYLE_INPUT,"Padeti pinigus",turi,"Padeti","Iseiti");
					return 1;
				}
				if(listitem == 6)
				{
					new weaponid = GetPlayerWeapon(playerid);
					if(weaponid < 16 || weaponid == 40 || weaponid > 43) return SendInfoMessage(playerid,"~r~Sio ginklo padeti negalima!");
					if(GetPlayerAmmo(playerid) == -100) return SendInfoMessage(playerid,"Sio ginklo pasideti negali!");
					new string[128];

					playerDB[playerid][imaginkla]=weaponid;
					format(string,sizeof(string),"Irasykite kulku skaiciu, kiek norite padeti.\nDaugiausiai galite padeti: %i",GetPlayerAmmo(playerid));
					ShowPlayerDialog(playerid,504, DIALOG_STYLE_INPUT,"Ginklas",string,"Padeti","Atsaukti");
					return 1;
				}
				if(listitem == 7)
				{
					if(!playerDB[playerid][maistas]) return SendInfoMessage(playerid,"Neturi maisto!~n~ Nusipirk jo 24/7 parduotuveje!");
					new houseid = GetPlayerHouseID(playerid);
					if((hInfo[houseid][hmaistas]+playerDB[playerid][maistas]) < 2000) hInfo[houseid][hmaistas]+=playerDB[playerid][maistas];
					else hInfo[houseid][hmaistas]=2000;
					playerDB[playerid][maistas]=0;
					ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
					SendInfoMessage(playerid,"Sekmingai pasidejai maista.");
					return 1;
				} 
			}
		}
		if(dialogid==504)
		{
			if(response)
			{
				if(!IsNumeric(inputtext)) return SendInfoMessage(playerid,"Skaiciais!");
				new kulkoz[50],
					gunz[50],
					weaponidas,
					slot,
					houseid = GetPlayerHouseID(playerid),
					kiekkulku = strval(inputtext),
					kiekturi;
				slot = GetWeaponsSlot(GetPlayerWeapon(playerid));
				GetPlayerWeaponData(playerid,slot,weaponidas,kiekturi);
				if(weaponidas != 22 && weaponidas != 24 && weaponidas != 25 && weaponidas != 27 && weaponidas != 29 && weaponidas != 30 && weaponidas != 33 && weaponidas != 31 && weaponidas != 41 && weaponidas != 42 && weaponidas != 43 && weaponidas != 34) return SendInfoMessage(playerid,"Sio ginklo pasideti negali, nes jis yra darbinis, arba neturi kulku.");
				if(kiekturi == -100 || kiekturi > 10000) return SendInfoMessage(playerid,"~r~Sio ginklo pasideti negali, nes jo kulkos neribotos!");
				
			
				if(kiekturi < kiekkulku) return SendInfoMessage(playerid,"~r~Tu tiek neturi!");
				new pname[MAX_PLAYER_NAME];
				GetPlayerName(playerid, pname, 24);

				if (!houseid || strcmp(hInfo[houseid][Name],pname,false) != 0 ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");

				if(GunData[playerid][slot][0] != weaponidas)
				{
					AC_Kick(playerid,"Ginklai 3");
					return 1;
				}
				if(GunData[playerid][slot][1] < kiekturi)
				{
					AC_Kick(playerid,"Ginklai 4");
					return 1;
				}
				
				if(hInfo[houseid][gunas][slot] == weaponidas || !hInfo[houseid][gunas][slot]) 
					hInfo[houseid][kulkos][slot]+=kiekkulku;
				else 
					hInfo[houseid][kulkos][slot]=kiekkulku;
				hInfo[houseid][gunas][slot]=weaponidas;
				
				format(kulkoz,sizeof(kulkoz),"Kulkos%i",slot);
				format(gunz,sizeof(gunz),"Ginklas%i",slot);
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `%s`=%i,`%s`=%i WHERE `ID`=%i",kulkoz,hInfo[houseid][kulkos][slot],gunz,hInfo[houseid][gunas][slot],houseid);
				mysql_query(query);
				
				GivePlayerWeaponEx(playerid, weaponidas, -kiekkulku);


				ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
				SendInfoMessage(playerid,"Sekmingai pasidejai ginkla.");
				//UpdateWeaps(playerid,weaponid,-kiekkulku);
				MLog(playerid,"Padejo ginkla","ii",weaponidas,kiekkulku);
				return 1;
			}
		}
		if(dialogid==507)
		{
			if(response)
			{
				new housenumber,pname[MAX_PLAYER_NAME];
				housenumber = GetPlayerHouseID(playerid);
				GetPlayerName(playerid, pname, 24);
				if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");

				if ( strcmp(hInfo[housenumber][Name],pname,false) ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
				if(listitem == 0)
				{
					new turi[128];
					format(turi,sizeof(turi),"Siuo metu namuose yra %ig. Zoles\nKiek norite pasiimti?",hInfo[GetPlayerHouseID(playerid)][zole]);
					ShowPlayerDialog(playerid,517,DIALOG_STYLE_INPUT,"Paimti Zole",turi,"Paimti","Iseiti");
					return 1;
				}
				if(listitem == 1)
				{
					new turi[128];
					format(turi,sizeof(turi),"Siuo metu namuose yra %ipak. Amfetamino\nKiek norite pasiimti?",hInfo[GetPlayerHouseID(playerid)][nark]);
					ShowPlayerDialog(playerid,527,DIALOG_STYLE_INPUT,"Paimti",turi,"Paimti","Iseiti");
					return 1;
				}
				if(listitem == 2) // seklos
				{
					new turi[128];
					format(turi,sizeof(turi),"Siuo metu namuose yra %ivnt. Seklu\nKiek norite pasiimti?",hInfo[GetPlayerHouseID(playerid)][seklos]);
					ShowPlayerDialog(playerid,557,DIALOG_STYLE_INPUT,"Paimti",turi,"Paimti","Iseiti");
					return 1;
				}
				if(listitem == 3) // lsd
				{
					new turi[128];
					format(turi,sizeof(turi),"Siuo metu namuose yra %ivnt. LSD\nKiek norite pasiimti?",hInfo[GetPlayerHouseID(playerid)][lsd]);
					ShowPlayerDialog(playerid,567,DIALOG_STYLE_INPUT,"Paimti",turi,"Paimti","Iseiti");
					return 1;
				}
				if(listitem == 4) // ratai
				{
					new turi[128];
					format(turi,sizeof(turi),"Siuo metu namuose yra %ivnt. Ratu\nKiek norite pasiimti?",hInfo[GetPlayerHouseID(playerid)][ratai]);
					ShowPlayerDialog(playerid,577,DIALOG_STYLE_INPUT,"Paimti",turi,"Paimti","Iseiti");
					return 1;
				}
				if(listitem == 5)
				{
					new turi[128];
					format(turi,sizeof(turi),"Siuo metu namuose yra %i€ Pinigu.\nKiek norite pasiimti?",hInfo[GetPlayerHouseID(playerid)][pinigai]);
					ShowPlayerDialog(playerid,537,DIALOG_STYLE_INPUT,"Paimti Pinigus",turi,"Paimti","Iseiti");
					return 1;
				}
				if(listitem == 6)
				{
					new msg[512],wepname[30],houseid = GetPlayerHouseID(playerid);
					new x;
					for(new slot=0; slot<12; slot++)
					{
						if(hInfo[houseid][gunas][slot] != 0 && hInfo[houseid][kulkos][slot] > 0)
						{
							GetWeaponName(hInfo[houseid][gunas][slot],wepname,sizeof(wepname));
							format(msg,sizeof(msg),"%s(%i)",wepname,hInfo[houseid][kulkos][slot]);
							AddDListItem(playerid, msg, slot);
							x++;
						}
					}
					if(!x) return SendInfoMessage(playerid,"~r~Neturi ginklu!");
					ShowPlayerDList(playerid, 828, "Ginklas", "Paimti","Atsaukti");
					return 1;
				}
				return 1;
			}
			return 1;
		}
		if(dialogid==828)
		{
			if(response)
			{
				new housenumber,pname[MAX_PLAYER_NAME];
				housenumber = GetPlayerHouseID(playerid);
				GetPlayerName(playerid, pname, 24);

				if ( strcmp(hInfo[housenumber][Name],pname,false) ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
				
				playerDB[playerid][imaginkla]=DLItemID;
				ShowPlayerDialog(playerid,829,DIALOG_STYLE_INPUT,"Iveskite skaiciu","Iveskite kulku skaiciu, kiek norite paimti.","Paimti","Atsaukti");
				return 1;
			}
		
		}
		if(dialogid==829)
		{
			if(response)
			{
				new kulkoz[10],gunz[10];
				if(!IsNumeric(inputtext)) return SendInfoMessage(playerid,"~r~Skaiciais!");
				new kiekkulku = strval(inputtext);
				new slot = playerDB[playerid][imaginkla];
				new houseid = GetPlayerHouseID(playerid);
				if(!houseid) return 1;
				new pname[MAX_PLAYER_NAME];
				GetPlayerName(playerid, pname, 24);

				if (strcmp(hInfo[houseid][Name],pname,false) != 0 ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
				if(kiekkulku > hInfo[houseid][kulkos][slot])
					return SendInfoMessage(playerid,"~r~Tiek kulku nera!");

				new
					slotas = GetWeaponsSlot(hInfo[houseid][gunas][slot]),
					weaponidas, kiekturi;
				
				GetPlayerWeaponData(playerid,slotas,weaponidas,kiekturi);
				if(weaponidas != hInfo[houseid][gunas][slot])
					kiekturi = 0;
				
				if(kiekturi + kiekkulku >= 10000)
				{
					return SendInfoMessage(playerid,"~r~Negali paimti daugiau nei 10.000 kulku!");
				}


				GivePlayerWeaponEx(playerid,hInfo[houseid][gunas][slot],kiekkulku);
				MLog(playerid,"Paeme ginkla","ii",hInfo[houseid][gunas][slot],kiekkulku);
				hInfo[houseid][kulkos][slot]-=kiekkulku;
				if(hInfo[houseid][kulkos][slot] < 1)
				{
					hInfo[houseid][gunas][slot]=0;
					hInfo[houseid][kulkos][slot]=0;
				}
				format(kulkoz,sizeof(kulkoz),"Kulkos%i",slot);
				format(gunz,sizeof(gunz),"Ginklas%i",slot);
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `%s`=%i,`%s`=%i WHERE `ID`=%i",kulkoz,hInfo[houseid][kulkos][slot],gunz,hInfo[houseid][gunas][slot],houseid);
				mysql_query(query);
				ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
				SendInfoMessage(playerid,"Sekmingai pasiemei ginkla.");
				return 1;
			}
		}
		if(dialogid==527)
		{
			if(response)
			{
				new kiek = StringToInt(inputtext);
				if(!IsNumeric(inputtext)) return 1;
				new houseid = GetPlayerHouseID(playerid);
				if(!houseid) return 1;
				new housenumber,pname[MAX_PLAYER_NAME];
				housenumber = GetPlayerHouseID(playerid);
				GetPlayerName(playerid, pname, 24);

				if ( strcmp(hInfo[housenumber][Name],pname,false) ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
				if(hInfo[houseid][nark] < kiek)
				{
					SendInfoMessage(playerid,"~r~Jus tiek neturite.");
					new turi[128];
					format(turi,sizeof(turi),"Jus tiek neturite.\nSiuo metu turite %ipak. Amfetamino.\nKiek norite pasiimti?",hInfo[GetPlayerHouseID(playerid)][nark]);
					ShowPlayerDialog(playerid,527,DIALOG_STYLE_INPUT,"Paimti",turi,"Padeti","Iseiti");
					return 1;
				}
				//if(playerDB[playerid][amfetaminas]+kiek > 10) return SendInfoMessage(playerid,"~r~ Nepatempsi tiek!");
				new house[20];
				format(house, sizeof(house), "Houses/houseid%d",GetPlayerHouseID(playerid));
				playerDB[playerid][amfetaminas]+=kiek;
				hInfo[houseid][nark]-=kiek;
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `Nark`=%i WHERE `ID`=%i",hInfo[houseid][nark],houseid);
				mysql_query(query);
				ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
				return 1;
			}
		}
		if(dialogid==537)
		{
			if(response)
			{
				new kiek = StringToInt(inputtext);
				if(!IsNumeric(inputtext)) return 1;
				new houseid = GetPlayerHouseID(playerid);
				if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");

				new housenumber,pname[MAX_PLAYER_NAME];
				housenumber = GetPlayerHouseID(playerid);
				GetPlayerName(playerid, pname, 24);

				if ( strcmp(hInfo[housenumber][Name],pname,false) != 0 || strlen(hInfo[housenumber][Name]) < 3 ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
				if(hInfo[houseid][pinigai] < kiek)
				{
					SendInfoMessage(playerid,"~r~Jus tiek neturite.");
					new turi[128];
					format(turi,sizeof(turi),"Jus tiek neturite.\nSiuo metu turite %i€ Pinigu.\nKiek norite pasiimti?",hInfo[GetPlayerHouseID(playerid)][pinigai]);
					ShowPlayerDialog(playerid,537,DIALOG_STYLE_INPUT,"Paimti pinigus",turi,"Padeti","Iseiti");
					return 1;
				}
				GivePlayerMoneyA(playerid, kiek);
				hInfo[houseid][pinigai]-=kiek;
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `Pinigai`=%i WHERE `ID`=%i",hInfo[houseid][pinigai],houseid);
				mysql_query(query);
				SavePlayerData(playerid,true);
				ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
				return 1;
			}
		}
		if(dialogid==557)
		{
			if(response)
			{
				new kiek = StringToInt(inputtext);
				if(!IsNumeric(inputtext)) return 1;
				new houseid = GetPlayerHouseID(playerid);
				new housenumber,pname[MAX_PLAYER_NAME];
				housenumber = GetPlayerHouseID(playerid);
				GetPlayerName(playerid, pname, 24);

				if ( strcmp(hInfo[housenumber][Name],pname,false) ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
				if(hInfo[houseid][seklos] < kiek)
				{
					SendInfoMessage(playerid,"~r~Jus tiek neturite.");
					return 1;
				}
				//if(playerDB[playerid][seklos]+kiek > 10) return SendInfoMessage(playerid,"~r~Nepatempsi tiek!");
				playerDB[playerid][seklos]+=kiek;
				hInfo[houseid][seklos]-=kiek;
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `Seklos`=%i WHERE `ID`=%i",hInfo[houseid][seklos],houseid);
				mysql_query(query);
				ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
				return 1;
			}
		}
		if(dialogid==567)
		{
			if(response)
			{
				new kiek = StringToInt(inputtext);
				if(!IsNumeric(inputtext)) return 1;
				new houseid = GetPlayerHouseID(playerid);
				new housenumber,pname[MAX_PLAYER_NAME];
				housenumber = GetPlayerHouseID(playerid);
				GetPlayerName(playerid, pname, 24);

				if ( strcmp(hInfo[housenumber][Name],pname,false) ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
				if(hInfo[houseid][lsd] < kiek)
				{
					SendInfoMessage(playerid,"~r~Jus tiek neturite.");
					return 1;
				}
				//if(playerDB[playerid][lsd]+kiek > 10) return SendInfoMessage(playerid,"~r~Nepatempsi tiek!");
				playerDB[playerid][lsd]+=kiek;
				hInfo[houseid][lsd]-=kiek;
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `LSD`=%i WHERE `ID`=%i",hInfo[houseid][lsd],houseid);
				mysql_query(query);
				ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
				return 1;
			}
		}
		if(dialogid==577)
		{
			if(response)
			{
				new kiek = StringToInt(inputtext);
				if(!IsNumeric(inputtext)) return 1;
				new houseid = GetPlayerHouseID(playerid);
				new housenumber,pname[MAX_PLAYER_NAME];
				housenumber = GetPlayerHouseID(playerid);
				GetPlayerName(playerid, pname, 24);

				if ( strcmp(hInfo[housenumber][Name],pname,false) ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
				if(hInfo[houseid][ratai] < kiek)
				{
					SendInfoMessage(playerid,"~r~Jus tiek neturite.");
					return 1;
				}
				playerDB[playerid][ratai]+=kiek;
				hInfo[houseid][ratai]-=kiek;
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `Ratai`=%i WHERE `ID`=%i",hInfo[houseid][ratai],houseid);
				mysql_query(query);
				ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
				return 1;
			}
		}
		if(dialogid==517)
		{
			if(response)
			{
				new kiek = StringToInt(inputtext);
				if(!IsNumeric(inputtext)) return 1;
				new houseid = GetPlayerHouseID(playerid);
				new housenumber,pname[MAX_PLAYER_NAME];
				housenumber = GetPlayerHouseID(playerid);
				GetPlayerName(playerid, pname, 24);

				if ( strcmp(hInfo[housenumber][Name],pname,false) ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
				if(hInfo[GetPlayerHouseID(playerid)][zole] < kiek)
				{
					SendInfoMessage(playerid,"~r~Jus tiek neturite.");
					new turi[128];
					format(turi,sizeof(turi),"Jus tiek neturite.\nSiuo metu turite %ig. Zoles.\nKiek norite pasiimti?",hInfo[GetPlayerHouseID(playerid)][zole]);
					ShowPlayerDialog(playerid,517,DIALOG_STYLE_INPUT,"Paimti Zole",turi,"Padeti","Iseiti");
					return 1;
				}
				new house[20];
				format(house, sizeof(house), "Houses/houseid%d",GetPlayerHouseID(playerid));
				playerDB[playerid][zole]+=kiek;
				hInfo[GetPlayerHouseID(playerid)][zole]-=kiek;
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `Zole`=%i WHERE `ID`=%i",hInfo[houseid][zole],houseid);
				mysql_query(query);
				ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
				return 1;
			}
		}
		if(dialogid==526)
		{
			if(response)
			{
				new kiek = StringToInt(inputtext);
				if(!IsNumeric(inputtext)) return 1;
				new houseid = GetPlayerHouseID(playerid);
				if(playerDB[playerid][amfetaminas] < kiek)
				{
					SendInfoMessage(playerid,"~r~Jus tiek neturite.");
					new turi[128];
					format(turi,sizeof(turi),"Jus tiek neturite.\nSiuo metu turite %ipak. Amfetamino.\nKiek norite pasideti?",playerDB[playerid][amfetaminas]);
					ShowPlayerDialog(playerid,526,DIALOG_STYLE_INPUT,"Padeti",turi,"Padeti","Iseiti");
					return 1;
				}
				new house[20];
				format(house, sizeof(house), "Houses/houseid%d",GetPlayerHouseID(playerid));
				playerDB[playerid][amfetaminas]-=kiek;
				hInfo[houseid][nark]+=kiek;
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `Nark`=%i WHERE `ID`=%i",hInfo[houseid][nark],houseid);
				mysql_query(query);
				ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
				return 1;
			}
		}
		if(dialogid==536)
		{
			if(response)
			{
				new kiek = StringToInt(inputtext);
				if(!IsNumeric(inputtext)) return 1;
				new houseid = GetPlayerHouseID(playerid);
				if(GetPlace(playerid)!=PLACE_HOUSE) return SendInfoMessage(playerid,"Si komanda naudojama name!");
				new housenumber,pname[MAX_PLAYER_NAME];
				housenumber = GetPlayerHouseID(playerid);
				GetPlayerName(playerid, pname, 24);

				if ( strcmp(hInfo[housenumber][Name],pname,false) != 0 || strlen(hInfo[housenumber][Name]) < 3 ) return SendInfoMessage(playerid,"Sis namas nepriklauso jums!");
				if(GetPlayerMoneyA(playerid) < kiek)
				{
					SendInfoMessage(playerid,"~r~Jus tiek neturite.");
					new turi[128];
					format(turi,sizeof(turi),"Jus tiek neturite.\nSiuo metu turite %i€ Pinigu.\nKiek norite pasideti?",GetPlayerMoneyA(playerid));
					ShowPlayerDialog(playerid,536,DIALOG_STYLE_INPUT,"Padeti Pinigus",turi,"Padeti","Iseiti");
					return 1;
				}
				GivePlayerMoneyA(playerid,-kiek);
				hInfo[houseid][pinigai]+=kiek;
				if(kiek >= 10000)
					ProcessAchievement(playerid,43);
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `Pinigai`=%i WHERE `ID`=%i",hInfo[houseid][pinigai],houseid);
				mysql_query(query);
				SavePlayerData(playerid,true);
				ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
				return 1;
			}
		}
		if(dialogid==556)
		{
			if(response)
			{
				new kiek = StringToInt(inputtext);
				if(!IsNumeric(inputtext)) return 1;
				new houseid = GetPlayerHouseID(playerid);
				if(playerDB[playerid][seklos] < kiek)
				{
					SendInfoMessage(playerid,"~r~Jus tiek neturite.");
					return 1;
				}
				if(hInfo[houseid][seklos]+kiek > 100) return SendInfoMessage(playerid,"Namie galite laikyti tik iki 100 vnt!");
				playerDB[playerid][seklos]-=kiek;
				hInfo[houseid][seklos]+=kiek;
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `Seklos`=%i WHERE `ID`=%i",hInfo[houseid][seklos],houseid);
				mysql_query(query);
				ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
				return 1;
			}
		}
		if(dialogid==566)
		{
			if(response)
			{
				new kiek = StringToInt(inputtext);
				if(!IsNumeric(inputtext)) return 1;
				new houseid = GetPlayerHouseID(playerid);
				if(playerDB[playerid][lsd] < kiek)
				{
					SendInfoMessage(playerid,"~r~Jus tiek neturite.");
					return 1;
				}
				if(hInfo[houseid][lsd]+kiek > 100) return SendInfoMessage(playerid,"Namie galite laikyti tik iki 100 vnt!");
				playerDB[playerid][lsd]-=kiek;
				hInfo[houseid][lsd]+=kiek;
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `LSD`=%i WHERE `ID`=%i",hInfo[houseid][lsd],houseid);
				mysql_query(query);
				ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
				return 1;
			}
		}
		if(dialogid==576)
		{
			if(response)
			{
				new kiek = StringToInt(inputtext);
				if(!IsNumeric(inputtext)) return 1;
				new houseid = GetPlayerHouseID(playerid);
				if(playerDB[playerid][ratai] < kiek)
				{
					SendInfoMessage(playerid,"~r~Jus tiek neturite.");
					return 1;
				}
				if(hInfo[houseid][ratai]+kiek > 100) return SendInfoMessage(playerid,"Namie galite laikyti tik iki 100 vnt!");
				playerDB[playerid][ratai]-=kiek;
				hInfo[houseid][ratai]+=kiek;
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `Ratai`=%i WHERE `ID`=%i",hInfo[houseid][ratai],houseid);
				mysql_query(query);
				ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
				return 1;
			}
		}
		if(dialogid==516)
		{
			if(response)
			{
				new kiek = StringToInt(inputtext);
				if(!IsNumeric(inputtext)) return 1;
				new houseid = GetPlayerHouseID(playerid);
				if(playerDB[playerid][zole] < kiek)
				{
					SendInfoMessage(playerid,"~r~Jus tiek neturite.");
					new turi[128];
					format(turi,sizeof(turi),"Jus tiek neturite.\nSiuo metu turite %ig. Zoles.\nKiek norite pasideti?",playerDB[playerid][zole]);
					ShowPlayerDialog(playerid,516,DIALOG_STYLE_INPUT,"Padeti Zole",turi,"Padeti","Iseiti");
					return 1;
				}
				if(hInfo[houseid][zole]+kiek > 100) return SendInfoMessage(playerid,"Namie galite laikyti tik iki 100 vnt!");
				playerDB[playerid][zole]-=kiek;
				hInfo[houseid][zole]+=kiek;
				new query[128];
				format(query,sizeof(query),"UPDATE `Namai` SET `Zole`=%i WHERE `ID`=%i",hInfo[houseid][zole],houseid);
				mysql_query(query);
				ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
				return 1;
			}
		}
		if(dialogid==505)
		{
			if(response)
			{
				
				new const tarnybos[][] = {"Policija", "Gaisrine", "Medikai", "Taksi", "Dyleriai", "Mechanikai", "Skelbejai", "Advokatai", "Limuzinai", "NTA", "Baikeriai", "Maistas"};
				if(listitem < sizeof(tarnybos))
					MLog(playerid,"Kviecia", "s", tarnybos[listitem]);

				if(listitem == 0)
				{
					new msg[128],name[MAX_PLAYER_NAME];
					GetPlayerName(playerid,name,sizeof(name));
					SendInfoMessage(playerid,"~b~Policija iskviesta.");
					kvieciapd=playerid;
					GetPlayerPos(playerid,kvieciapdcord[0],kvieciapdcord[1],kvieciapdcord[2]);
					format(msg,sizeof(msg),"[racija] Operatore: %s kviecia policija(%s)! Rasykite /imti !",name,JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
					SendMessageToTeisesauga(COLOR,msg);
					if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USECELLPHONE)
					{
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid,TEL_SLOT);
					}
					return 1;
				}
				if(listitem == 1)
				{
					new x=0;
					foreach (Player, i)
					{
							if(playerDB[i][specialybe]==66) x++;
					}
					if(x==0) return SendInfoMessage(playerid,"~r~Siuo metu prisijungusiu gaisrininku nera.");
					new msg[128],name[MAX_PLAYER_NAME];
					GetPlayerName(playerid,name,sizeof(name));
					format(msg,sizeof(msg),"[racija] Operatore: %s kviecia gaisrininkus(%s)! Rasykite /imti !",name,JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
					SendInfoMessage(playerid,"~w~Gaisrininkai iskviesti.");
					kvieciagais=playerid;
					SendMessageToGaisras(COLOR,msg);
					if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USECELLPHONE)
					{
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid,TEL_SLOT);
					}
					return 1;
				}
				if(listitem == 2)
				{
					new x=0;
					foreach (Player, i)
					{
							if(playerDB[i][specialybe]==2 || playerDB[i][specialybe]==93) x++;
					}
					if(x==0) return SendInfoMessage(playerid,"~r~Siuo metu prisijungusiu mediku nera.");
					new msg[128],name[MAX_PLAYER_NAME];
					GetPlayerName(playerid,name,sizeof(name));
					format(msg,sizeof(msg),"[racija] Operatore: %s kviecia medikus(%s)! Rasykite /imti !",name,JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
					SendInfoMessage(playerid,"~r~Medikai iskviesti.");
					kvieciamedikus=playerid;
					SendMessageToMedics(COLOR,msg);
					if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USECELLPHONE)
					{
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid,TEL_SLOT);
					}
					return 1;
				}
				if(listitem == 3)
				{
					new x=0;
					foreach (Player, i)
					{
							if(playerDB[i][specialybe]==3) x++;
							if(playerDB[i][specialybe]==20) x++;
					}
					if(x==0) return SendInfoMessage(playerid,"~r~Siuo metu prisijungusiu taksistu nera.");
					new msg[128],name[MAX_PLAYER_NAME];
					GetPlayerName(playerid,name,sizeof(name));
					format(msg,sizeof(msg),"[racija] Operatore: %s kviecia taksi(%s)! Rasykite /imti !",name,JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
					SendInfoMessage(playerid,"~y~Taksi iskviesta.");
					kvieciataxi=playerid;
					SendMessageToTransportas(COLOR,msg);
					if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USECELLPHONE)
					{
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid,TEL_SLOT);
					}
					return 1;
				}
				if(listitem == 4)
				{
					new x=0;
					foreach (Player, i)
					{
							if(playerDB[i][specialybe]==32) x++;
					}
					if(x==0) return SendInfoMessage(playerid,"~r~Siuo metu prisijungusiu dyleriu nera.");
					new msg[128],name[MAX_PLAYER_NAME];
					GetPlayerName(playerid,name,sizeof(name));
					format(msg,sizeof(msg),"[racija] Operatore: %s kviecia Dylerius(%s)! Rasykite /imti !",name,JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
					SendInfoMessage(playerid,"~w~Dyleriai iskviesti.");
					kvieciadyl=playerid;
					SendMessageToDeal(COLOR,msg);
					if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USECELLPHONE)
					{
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid,TEL_SLOT);
					}
					return 1;
				}
				if(listitem == 5)
				{
					new x=0;
					foreach (Player, i)
					{
							if(playerDB[i][specialybe]==6) x++;
					}
					if(x==0) return SendInfoMessage(playerid,"~r~Siuo metu prisijungusiu mechaniku nera.");
					new msg[128],name[MAX_PLAYER_NAME];
					GetPlayerName(playerid,name,sizeof(name));
					format(msg,sizeof(msg),"[racija] Operatore: %s kviecia Mechanikus(%s)! Rasykite /imti !",name,JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
					SendInfoMessage(playerid,"~b~Mechanikas iskviestas.");
					kvieciamech=playerid;
					SendMessageToAutospecai(COLOR,msg);
					if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USECELLPHONE)
					{
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid,TEL_SLOT);
					}
					return 1;
				}
				if(listitem == 6)
				{
					new x=0;
					foreach (Player, i)
					{
							if(playerDB[i][specialybe]==50) x++;
					}
					if(x==0) return SendInfoMessage(playerid,"~r~Siuo metu prisijungusiu skelbeju nera.");
					new msg[128],name[MAX_PLAYER_NAME];
					GetPlayerName(playerid,name,sizeof(name));
					format(msg,sizeof(msg),"[racija] Operatore: %s kviecia Skelbejus(%s)! Rasykite /imti !",name,JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
					SendInfoMessage(playerid,"~p~Skelbejas iskviestas.");
					kvieciaskelb=playerid;
					SendMessageToValstybe(YELLOW,msg);
					if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USECELLPHONE)
					{
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid,TEL_SLOT);
					}
					return 1;
				}
				if(listitem == 7)
				{
					new x=0;
					foreach (Player, i)
					{
							if(playerDB[i][specialybe]==15) x++;
					}
					if(x==0) return SendInfoMessage(playerid,"~r~Siuo metu prisijungusiu advokatu nera.");
					kvieciaadv=playerid;
					new msg[128],name[MAX_PLAYER_NAME];
					GetPlayerName(playerid,name,sizeof(name));
					format(msg,sizeof(msg),"[racija] Operatore: %s kvieèia advokatà! Raðykite /imti",name);
					foreach (Player, i)
					{
							if(playerDB[i][specialybe]==15) SendClientMessage(i,YELLOW,msg);
					}
					SendInfoMessage(playerid,"~w~Advokatas iskviestas.");
					if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USECELLPHONE)
					{
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid,TEL_SLOT);
					}
					return 1;
				}
				if(listitem == 8)
				{
					new x=0;
					foreach (Player, i)
							if(playerDB[i][specialybe]==20) x++;
					if(x==0) return SendInfoMessage(playerid,"~r~Siuo metu prisijungusiu limuzino vairuotoju.");
					new msg[128],name[MAX_PLAYER_NAME];
					GetPlayerName(playerid,name,sizeof(name));
					format(msg,sizeof(msg),"[racija] Operatore: %s kviecia limuzina(%s)! Rasykite /imti !",name,JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
					SendInfoMessage(playerid,"~p~Limuzinas iskviestas.");
					kviecialimo=playerid;
					SendMessageToTransportas(COLOR,msg);
					if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USECELLPHONE)
					{
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid,TEL_SLOT);
					}
					return 1;

				}// 39
				if(listitem == 9)
				{
					new x=0;
					foreach (Player, i)
					{
							if(playerDB[i][specialybe]==34) x++;
					}
					if(x==0) return SendInfoMessage(playerid,"~r~Siuo metu prisijungusiu turto agentu nera.");
					kviecianta=playerid;
					new msg[128],name[MAX_PLAYER_NAME];
					GetPlayerName(playerid,name,sizeof(name));
					format(msg,sizeof(msg),"[racija] Operatore: %s kviecia NTA(%s)! Rasykite /imti !",name,JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
					SendInfoMessage(playerid,"~b~Nekilnojamo turto agentas iskviestas.");
					kviecianta=playerid;
					SendMessageToNTA(0xE3B92430,msg);
					if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USECELLPHONE)
					{
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid,TEL_SLOT);
					}
					return 1;
				}
				if(listitem == 10)
				{
					new x=0;
					foreach (Player, i)
					{
							if(playerDB[i][specialybe]==71) x++;
					}
					if(x==0) return SendInfoMessage(playerid,"~r~Siuo metu prisijungusiu baikeriu nera.");
					new msg[128],name[MAX_PLAYER_NAME];
					GetPlayerName(playerid,name,sizeof(name));
					format(msg,sizeof(msg),"[racija] Operatore: %s kviecia baikerius(%s)! Rasykite /imti !",name,JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
					SendInfoMessage(playerid,"~b~Baikeris iskviestas.");
					kvieciabaikerius=playerid;
					SendMessageToBaikeriai(0xE3B92430,msg);
					if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USECELLPHONE)
					{
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid,TEL_SLOT);
					}
				}
				if(listitem == 11)
				{
					new x=0;
					new msg[128],name[MAX_PLAYER_NAME];
					GetPlayerName(playerid,name,sizeof(name));
					format(msg,sizeof(msg),"[racija] Operatore: %s kvieèia maisto iðveþiotojus(%s)! Raðykite /imti !",name,JB_gSAZones[Get2DZone(playerid)][JB_SAZONE_NAME]);
					foreach (Player, i)
					{
						if(GetPlayerState(i)==PLAYER_STATE_DRIVER)
						{
							new moddel = GetVehicleModel(GetPlayerVehicleID(i));
							switch(moddel)
							{
								case HOTDOG,423,478,448:
								{
									x++;
									SendClientMessage(i,0xE3B92430,msg);
								}
							}
						}
					}
					if(x==0) return SendInfoMessage(playerid,"~r~Siuo metu prisijungusiu maisto isveziotoju nera.");
					kvieciafood=playerid;
					SendInfoMessage(playerid,"~b~Greitas maistas iskviestas.");
					//SendMessageToNTA(0xE3B92430,msg);
					if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USECELLPHONE)
					{
						SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
						RemovePlayerAttachedObject(playerid,TEL_SLOT);
					}
					return 1;
				}
			}
			
		}
		if(dialogid==1339)
		{
			if(response)
			{
				if(listitem==0)
				{
					if(playerDB[playerid][daiktas] == INV_DOVANA)
					{
						if(IsPlayerAttachedObjectSlotUsed(playerid, DOVANOS_SLOT))
						{
							SendInfoMessage(playerid,"~r~Nusiemei~w~ dovana!");
							RemovePlayerAttachedObject(playerid, DOVANOS_SLOT);
						}
						else
						{
							new query[128];
							format(query,sizeof(query),"SELECT Itemid From `Kaledos11` WHERE Vardas='%s'",ReturnName(playerid));
							mysql_function_query(SQL, query, true, "SQL_PutOnGift", "i", playerid);
							
						}
						return 1;
					}
					if(playerDB[playerid][daiktas] == INV_AKINIAI)
					{
						if(IsPlayerAttachedObjectSlotUsed(playerid, AKINIU_SLOT))
						{
							SendInfoMessage(playerid,"~r~Nusiemei~w~ akinius!");
							RemovePlayerAttachedObject(playerid, AKINIU_SLOT);
						}
						else
						{
							SendInfoMessage(playerid,"~g~Uzsidejai~w~ akinius!");
							new skin=GetPlayerSkin(playerid);
							SetPlayerAttachedObject(playerid, AKINIU_SLOT, CommonRed+playerDB[playerid][akiniai]-1, 2, AkiniuOffSet[skin][0], AkiniuOffSet[skin][1], AkiniuOffSet[skin][2], AkiniuOffSet[skin][3], AkiniuOffSet[skin][4], AkiniuOffSet[skin][5],AkiniuOffSet[skin][6]);
						}
						return 1;
						//playerDB[playerid][akiniai]=0;
					}
					else if(playerDB[playerid][daiktas] == INV_KEPURE)
					{
						if(IsPlayerAttachedObjectSlotUsed(playerid, CAP_SLOT))
						{
							BitFlag_Off(PConfig[playerid],PCFG_KEPURE);
							SendInfoMessage(playerid,"~r~Nusiemei~w~ kepure!");
							RemovePlayerAttachedObject(playerid, CAP_SLOT);
						}
						else
						{
							new skinid = GetPlayerSkin(playerid);
							if(playerDB[playerid][kepure])
							{
								if(!AttachKepure(playerid,skinid)) return SendInfoMessage(playerid,"~r~Negali uzsideti kepures ant sito skino!");
							}
							SendInfoMessage(playerid,"~g~Uzsidejai~w~ kepure!");
							BitFlag_On(PConfig[playerid],PCFG_KEPURE);
						}
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_SALMAS)
					{
						if(IsPlayerAttachedObjectSlotUsed(playerid, SALMO_SLOT))
						{
							SendInfoMessage(playerid,"~r~Nusiemei~w~ salma!");
							RemovePlayerAttachedObject(playerid, SALMO_SLOT);
							BitFlag_Off(PConfig[playerid],PCFG_SALMAS);
						}
						else
						{
							SendInfoMessage(playerid,"~r~Uzsidejai~w~ salma!");
							UzdetiSalma(playerid,Salmai[playerDB[playerid][salmas]-1]);
							BitFlag_On(PConfig[playerid],PCFG_SALMAS);
						}
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_CIGARETES)
					{
						cmd_rukyti(playerid,"");
						return 1;
					}
					
					else if(playerDB[playerid][daiktas] == INV_NARK)
					{
						cmd_amfa(playerid,"");
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_RATAI)
					{
						cmd_ratai(playerid,"");
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_LSD)
					{
						cmd_lsd(playerid,"");
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_ADR)
					{
						cmd_adr(playerid,"");
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_LAIKRODIS)
					{
						BitFlag_Toggle(PConfig[playerid],PCFG_SHOWTIME);
						if(!BitFlag_Get(PConfig[playerid],PCFG_SHOWTIME))
						{
							SendInfoMessage(playerid,"Nusiemei laikrodi!");
							//PConfig[playerid][showtime]=false;
							TextDrawHideForPlayer(playerid, TextdrawTime);
						}
						else
						{
							SendInfoMessage(playerid,"Uzsidejai laikrodi!");
							TextDrawShowForPlayer(playerid, TextdrawTime);
							//PConfig[playerid][showtime]=true;
						}
					}
					else if(playerDB[playerid][daiktas] == INV_ZOLE)
					{
						cmd_pusti(playerid,"");
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_MAISTASLAUK)
					{
						cmd_pavalgyti(playerid,"");
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_RAKTAS)
					{
						cmd_fix(playerid,"");
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_BAKELIS)
					{
						cmd_bakelis(playerid,"");
						return 1;
					}
					else return SendInfoMessage(playerid,"~r~Sio daikto naudoti negalima!");
				
				}
				else
				{
					if(playerDB[playerid][daiktas] == INV_DOVANA)
					{
						SendInfoMessage(playerid,"~r~Niekas dovanu neismeta :O!");
					}
					if(playerDB[playerid][daiktas] == INV_AKINIAI)
					{
						BitFlag_Off(PConfig[playerid],PCFG_AKINIAI);
						SendInfoMessage(playerid,"~r~Ismetei akinius!");
						if(IsPlayerAttachedObjectSlotUsed(playerid, AKINIU_SLOT))
						{
							RemovePlayerAttachedObject(playerid, AKINIU_SLOT);
						}
						playerDB[playerid][akiniai]=0;
						return 1;
						//playerDB[playerid][akiniai]=0;
					}
					else if(playerDB[playerid][daiktas] == INV_KEPURE)
					{
						SendInfoMessage(playerid,"~r~Ismetei kepure!");
						BitFlag_Off(PConfig[playerid],PCFG_KEPURE);
						if(IsPlayerAttachedObjectSlotUsed(playerid, CAP_SLOT))
						{
							
							RemovePlayerAttachedObject(playerid, CAP_SLOT);
						}
						playerDB[playerid][kepure]=0;
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_SALMAS)
					{
						SendInfoMessage(playerid,"~r~Ismetei salma!");
						BitFlag_Off(PConfig[playerid],PCFG_SALMAS);
						if(IsPlayerAttachedObjectSlotUsed(playerid, SALMO_SLOT))
						{
							RemovePlayerAttachedObject(playerid, SALMO_SLOT);
						}
						playerDB[playerid][salmas]=0;
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_NARK)
					{
						SendInfoMessage(playerid,"~r~Ismetei Amfetamina!");
						playerDB[playerid][amfetaminas]=0;
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_RATAI)
					{
						SendInfoMessage(playerid,"~r~Ismetei Ekstazi!");
						playerDB[playerid][ratai]=0;
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_CIGARETES)
					{
						SendInfoMessage(playerid,"~r~Ismetei Cigaretes!");
						playerDB[playerid][cigaretes]=0;
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_LAISKAI)
					{
						if(IsPlayerAttachedObjectSlotUsed(playerid, SLOT_LAGAMINAS))
						{
							RemovePlayerAttachedObject(playerid, SLOT_LAGAMINAS);
						}
						for(new i;i<10;i++)
						{
							playerDB[playerid][pastas][i]=0;
						}
						SendInfoMessage(playerid,"Ismetei laiskus!");
						//SetPlayerAttachedObject(playerid,SLOT_LAGAMINAS,1210, 5, 0.300000, 0.079999, 0.029999, 0.000000, 258.750000, 0.470031 );
	
					
					}
					else if(playerDB[playerid][daiktas] == INV_TAZERIS)
					{
						SendInfoMessage(playerid,"~r~Ismetei tazeri!");
						RemovePlayerAttachedObject(playerid, TAZER_SLOT);
					}
					else if(playerDB[playerid][daiktas] == INV_LSD)
					{
						SendInfoMessage(playerid,"~r~Ismetei LSD!");
						playerDB[playerid][lsd]=0;
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_ADR)
					{
						SendInfoMessage(playerid,"~r~Ismetei Adrenalina!");
						playerDB[playerid][adr]=0;
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_LAIKRODIS)
					{
						SendInfoMessage(playerid,"~r~Ismetei laikrodi!");
						playerDB[playerid][laikrodis]=false;
						BitFlag_Off(PConfig[playerid],PCFG_SHOWTIME);

						TextDrawHideForPlayer(playerid, TextdrawTime);
					}
					else if(playerDB[playerid][daiktas] == INV_ZOLE)
					{
						SendInfoMessage(playerid,"~r~Ismetei Zole!");
						playerDB[playerid][zole]=0;
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_MAISTASLAUK)
					{
						SendInfoMessage(playerid,"~r~Ismetei Maista!");
						playerDB[playerid][maistaslauk]=0;
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_RAKTAS)
					{
						SendInfoMessage(playerid,"~r~Ismetei Rakta!");
						playerDB[playerid][raktas]=0;
						return 1;
					}
					else if(playerDB[playerid][daiktas] == INV_BAKELIS)
					{
						SendInfoMessage(playerid,"~r~Ismetei Bakeli!");
						playerDB[playerid][bakelis]=false;
						return 1;
					}
					else return SendInfoMessage(playerid,"~r~Sio daikto ismesti negalima!");
				}
				/*INV_TELEFONAS,
				INV_MONEY,
				INV_KREDITINE,
				INV_NARK,
				INV_ZOLE,
				INV_SEKLOS,
				INV_GUN,
				INV_GERIMAS,
				INV_RAKTAS, 
				INV_TEISES,
				INV_TEISESM,
				INV_TEISESS,
				INV_SPAZ,
				INV_AKINIAI,
				INV_ZUVIS,
				INV_MASALAS,
				INV_BAKELIS,
				INV_MAISTAS,
				INV_MAISTASLAUK,
				INV_LSD,
				INV_RATAI,
				INV_KEPURE,
				INV_SALMAS */
			}
			else cmd_i(playerid,"");
		}
		if(dialogid==1338)
		{
			if(response)
			{
				if(DLItemID == INV_RUBAI)
				{
					if(playerDB[playerid][psratasvydis]) return SendInfoMessage(playerid,"Cia keist skino negali!");
					if(InEvent(playerid)) return SendInfoMessage(playerid,"Evente skino keisti negali!");
					if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return SendInfoMessage(playerid,"Islipk is masinos!"); 
					ShowRubai(playerid);
					return 1;
				}
				if(DLItemID == INV_SPALVOS)
				{
					//if(playerDB[playerid][psratasvydis]) return SendInfoMessage(playerid,"Cia keist skino negali!");
					//ShowRubai(playerid);
					ShowSpalvos(playerid);
					return 1;
				}
				playerDB[playerid][daiktas]=DLItemID;
				ShowPlayerDialog(playerid,1339,DIALOG_STYLE_LIST,"Daiktai","Naudoti\nIsmesti","Gerai","Atsaukti");
			}
			return 1;
		}
		
		if(dialogid==304)
		{
			if(response)
			{
				
				if(DLItemID == 0)
				{
					if (Carlist[playerid][Typ]!=-1)
					{

						new price = (aVehicleNames[Carlist[playerid][Typ]][Price]/5)*2;
						if(Carlist[playerid][Typ]==149)
							price = 100;
						new msg[256];
						format(msg,sizeof(msg),"Ar tikrai norite parduoti savo antraji automobili?\nUz ji gautumete %i€ i rankas.",price);
						ShowPlayerDialog(playerid,3996,DIALOG_STYLE_MSGBOX,"Namas",msg,"Taip","Ne");

					}
					else { SendInfoMessage(playerid,"~r~Jus neturite masinos!"); }
					return 1;
				}
				if(DLItemID == 1)
				{
					if (Carlist2[playerid][Typ]!=-1)
					{
						new price = (aVehicleNames[Carlist2[playerid][Typ]][Price]/5)*2;
						if(Carlist2[playerid][Typ]==149)
							price = 100;
						new msg[256];
						format(msg,sizeof(msg),"Ar tikrai norite parduoti savo antraji automobili?\nUz ji gautumete %i€ i rankas.",price);
						ShowPlayerDialog(playerid,3997,DIALOG_STYLE_MSGBOX,"Automobilis",msg,"Taip","Ne");
						
					}
					else { SendInfoMessage(playerid,"~r~Jus neturite masinos!"); }
					return 1;
				}
				if(DLItemID == 2)
				{
					if (Carlist3[playerid][Typ]!=-1)
					{
						new price = (aVehicleNames[Carlist3[playerid][Typ]][Price]/5)*2;
						if(Carlist3[playerid][Typ]==149)
							price = 100;
						new msg[256];
						format(msg,sizeof(msg),"Ar tikrai norite parduoti savo treciaji automobili?\nUz ji gautumete %i€ i rankas.",price);
						ShowPlayerDialog(playerid,3998,DIALOG_STYLE_MSGBOX,"Automobilis",msg,"Taip","Ne");
						
					}
					else { SendInfoMessage(playerid,"~r~Jus neturite masinos!"); }
					return 1;
				}
			}
		}
		/*
		if(dialogid==305)
		{
			if(response)
			{
				SetPVarInt(playerid, "SiuloCarID", DLItemID);
				if(DLItemID == 0)
					SetPVarInt(playerid, "SiuloCarModel", Carlist[playerid][Typ]);
				else if(DLItemID == 1)
					SetPVarInt(playerid, "SiuloCarModel", Carlist2[playerid][Typ]);
				else if(DLItemID == 2)
					SetPVarInt(playerid, "SiuloCarModel", Carlist3[playerid][Typ]);
				new msg[256];
				new model = GetPVarInt(playerid, "SiuloCarModel");
				if(model == -1)
					return 1;
				format(msg,256,"{FFFFFF}Norite parduoti savo automobilá "#TEXT_BLUE"%s{FFFFFF}.\n\nÁveskite þaidëjo vardà, kuriam já norite parduoti.",aVehicleNames[model])
				ShowPlayerDialog(playerid, 306, DIALOG_STYLE_INPUT, "Siulyti?", msg, "Gerai", "Atsaukti");
			}
		}
		if(dialogid==306)
		{
			if(response)
			{
				if(TradingWith[playerid] != -1) return SendInfoMessage(playerid,"Uzdaryk mainus!");
				new sellplayerid = GetPlayeridMid(inputtext);

				if (!IsPlayerConnected(sellplayerid))
				{
					SendInfoMessage(playerid,"Zaidejas nera prisijunges.");
					return 1;
				}
				new Float:Coo[3];
				GetPlayerPos(sellplayerid,Coo[0],Coo[1],Coo[2]);
				if(!IsPlayerInRangeOfPointEx(100, playerid, Coo[0],Coo[1],Coo[2]) || GetPlayerState(sellplayerid) == PLAYER_STATE_SPECTATING){SendInfoMessage(playerid,"Zaidejas per toli!"); return 1;}
				if(playerid == sellplayerid) return SendInfoMessage(playerid,"Sau parduoti masinos negali");
				if(offerCar[sellplayerid][0]==playerid) return SendInfoMessage(playerid,"Jau siulote savo masina siam zaidejui!");
				if(GetPlayerScore(sellplayerid) < 200) return SendInfoMessage(playerid,"Zaidejo XP per mazas! XP < 200");
		        if(GetPlayerScore(playerid) < 200) return SendInfoMessage(playerid,"Jusu XP per mazas! XP < 200");

		        new msg[256];
				new model = GetPVarInt(playerid, "SiuloCarModel");
				if(model == -1)
					return 1;
				format(msg,256,"{FFFFFF}Norite parduoti savo automobilá "#TEXT_BLUE"%s{FFFFFF}.\nÞaidëjui: "#TEXT_BLUE"%s{FFFFFF}.\n\nÁveskite kainà:",aVehicleNames[model])
				ShowPlayerDialog(playerid, 306, DIALOG_STYLE_INPUT, "Siulyti?", msg, "Gerai", "Atsaukti");

				return 1;
			}
			else
			{
				return cmd_siulyti(playerid,"");
			}
		}
		*/
		if(dialogid==303)
		{
			if(response)
			{
				if(DLItemID == 0)
				{
					if (Carlist[playerid][Typ]!=-1)
					{
						if (Carlist[playerid][Carid]!=-1)
						{
							if((GetPlayerState(playerid) == PLAYER_STATE_DRIVER && playerDB[playerid][specialybe]==5) || (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && playerDB[playerid][specialybe]==55) || (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && playerDB[playerid][specialybe]==62) || vagia[playerid] || (IsPlayerInAnyVehicle(playerid) &&
							(vpakrauta[GetPlayerVehicleID(playerid)]==1 || vbankomatams[GetPlayerVehicleID(playerid)]==1)))
							{
								SendInfoMessage(playerid,"Prasome islipti is automobilio.");
								return 1;
							}
							new Float:sx,Float:sy,Float:sz;
							GetVehiclePos(Carlist[playerid][Carid],sx,sy,sz);
							/*if(sy < -1483.6194 && sy > -1507.2380 && sx < 1546.4885 && sx > 1464.6373)
							{
								SendInfoMessage(playerid,"Jusu masina konfiskuota!");
							}*/
							if(GetVehicleVirtualWorld(Carlist[playerid][Carid]))
							{
								new vw = GetVehicleVirtualWorld(Carlist[playerid][Carid]);
								new msg[128];
								format(msg,sizeof(msg),"Jûsø maðina garaze nr.%i",vw-MAX_HOUSES);
								SendInfoMessage(playerid,msg);
								//SendClientMessage(playerid,YELLOW,msg);
								return 1;
							}
							new msg[128],Float:coo[6];
							GetVehiclePos(Carlist[playerid][Carid],coo[0],coo[1],coo[2]);
							GetPlayerPos(playerid,coo[3],coo[4],coo[5]);
							new Float:atstumas = ((floatabs(coo[0]-coo[3])+floatabs(coo[1]-coo[4])+floatabs(coo[2]-coo[5]))/3)/100;
							SetPlayerCheckpoint(playerid,coo[0],coo[1],coo[2],2);
							new salis1[10],salis2[10];if(coo[0]-coo[3]>0) salis1="rytus";
							else salis1="vakarus";
							if(coo[1]-coo[4]>0) salis2="siaures";
							else salis2="pietu";
							format(msg,sizeof(msg),"Dabartine jusu automobilio vieta rodoma GPS. Jis yra %.1f KM i %s %s nuo jusu.",atstumas,salis2,salis1);
							SendInfoMessage(playerid,msg,150);
						}
						else { SendInfoMessage(playerid,"Jusu masina yra sunaikinta. Susiremontuokite ja."); }
					}
					else { SendInfoMessage(playerid,"Ka? Jus neturite masinos!"); }
					return 1;
				}
				if(DLItemID == 1)
				{
					if (Carlist2[playerid][Typ]!=-1)
					{
						if (Carlist2[playerid][Carid]!=-1)
						{
							if((GetPlayerState(playerid) == PLAYER_STATE_DRIVER && playerDB[playerid][specialybe]==5) || (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && playerDB[playerid][specialybe]==55) || (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && playerDB[playerid][specialybe]==62) || vagia[playerid] ||
							(IsPlayerInAnyVehicle(playerid) && (vpakrauta[GetPlayerVehicleID(playerid)]==1 || vbankomatams[GetPlayerVehicleID(playerid)]==1 )) )
							{
								SendInfoMessage(playerid,"Prasome islipti is automobilio.");
								return 1;
							}
							new Float:sx,Float:sy,Float:sz;
							GetVehiclePos(Carlist2[playerid][Carid],sx,sy,sz);
							/*if(sy < -1483.6194 && sy > -1507.2380 && sx < 1546.4885 && sx > 1464.6373)
							{
								SendInfoMessage(playerid,"Jusu masina konfiskuota!");
							}*/
							if(GetVehicleVirtualWorld(Carlist2[playerid][Carid]))
							{
								new vw = GetVehicleVirtualWorld(Carlist2[playerid][Carid]);
								new msg[128];
								format(msg,sizeof(msg),"Jusu masina garaze nr.%i",vw-MAX_HOUSES);
								SendInfoMessage(playerid,msg);
								return 1;
							}
							
							new msg[128],Float:coo[6];
							GetVehiclePos(Carlist2[playerid][Carid],coo[0],coo[1],coo[2]);
							GetPlayerPos(playerid,coo[3],coo[4],coo[5]);
							new Float:atstumas = ((floatabs(coo[0]-coo[3])+floatabs(coo[1]-coo[4])+floatabs(coo[2]-coo[5]))/3)/100;
							SetPlayerCheckpoint(playerid,coo[0],coo[1],coo[2],2);
							new salis1[10],salis2[10];if(coo[0]-coo[3]>0) salis1="rytus";
							else salis1="vakarus";
							if(coo[1]-coo[4]>0) salis2="siaures";
							else salis2="pietu";
							format(msg,sizeof(msg),"Dabartine jusu automobilio vieta rodoma GPS. Jis yra %.1f KM i %s %s nuo jusu.",atstumas,salis2,salis1);
							SendInfoMessage(playerid,msg,150);
					
						}
						else { SendInfoMessage(playerid,"Jusu masina yra sunaikinta. Susiremontuokite ja."); }
					}
					else { SendInfoMessage(playerid,"Ka? Jus neturite masinos!"); }
					return 1;
				}
				if(DLItemID == 2)
				{
					if (Carlist3[playerid][Typ]!=-1)
					{
						if (Carlist3[playerid][Carid]!=-1)
						{
							if((GetPlayerState(playerid) == PLAYER_STATE_DRIVER && playerDB[playerid][specialybe]==5) || (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && playerDB[playerid][specialybe]==55) || (GetPlayerState(playerid) == PLAYER_STATE_DRIVER && playerDB[playerid][specialybe]==62) || vagia[playerid] ||
							(IsPlayerInAnyVehicle(playerid) && (vpakrauta[GetPlayerVehicleID(playerid)]==1 || vbankomatams[GetPlayerVehicleID(playerid)]==1 )))
							{
								SendInfoMessage(playerid,"Prasome islipti is automobilio.");
								return 1;
							}
							new Float:sx,Float:sy,Float:sz;
							GetVehiclePos(Carlist3[playerid][Carid],sx,sy,sz);
							/*if(sy < -1483.6194 && sy > -1507.2380 && sx < 1546.4885 && sx > 1464.6373)
							{
								SendInfoMessage(playerid,"Jusu masina konfiskuota!");
							}*/
							if(GetVehicleVirtualWorld(Carlist3[playerid][Carid]))
							{
								new vw = GetVehicleVirtualWorld(Carlist3[playerid][Carid]);
								new msg[128];
								format(msg,sizeof(msg),"Jusu masina garaze nr.%i",vw-MAX_HOUSES);
								SendInfoMessage(playerid,msg);
								return 1;
							}
							new msg[128],Float:coo[6];
							GetVehiclePos(Carlist3[playerid][Carid],coo[0],coo[1],coo[2]);
							GetPlayerPos(playerid,coo[3],coo[4],coo[5]);
							new Float:atstumas = ((floatabs(coo[0]-coo[3])+floatabs(coo[1]-coo[4])+floatabs(coo[2]-coo[5]))/3)/100;
							SetPlayerCheckpoint(playerid,coo[0],coo[1],coo[2],2);
							new salis1[10],salis2[10];if(coo[0]-coo[3]>0) salis1="rytus";
							else salis1="vakarus";
							if(coo[1]-coo[4]>0) salis2="siaures";
							else salis2="pietu";
							format(msg,sizeof(msg),"Dabartine jusu automobilio vieta rodoma GPS. Jis yra %.1f KM i %s %s nuo jusu.",atstumas,salis2,salis1);
							SendInfoMessage(playerid,msg);
						}
						else { SendInfoMessage(playerid,"Jusu masina yra sunaikinta. Susiremontuokite ja."); }
					}
					else { SendInfoMessage(playerid,"Ka? Jus neturite masinos!"); }
					return 1;
				}
			}
		}
		if(dialogid==8685)
		{
			if(response)
			{
				new Float:pos[3];
				GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
				if((pos[1] < -1301.4 && pos[1] > -1303.2417 && pos[0] < 1786.2131 && pos[0] > 1784.1555) || (pos[1] > -1301.4 && pos[1] < -1299.1447 && pos[0] < 1785.6147 && pos[0] > 1781.9902))
					return SendInfoMessage(playerid,"Islisk i lauka!");    
				if(((1110.9355 < pos[0] < 1216.6061) && (-1211.0791 < pos[1] < -1152.7689)) || (  ( 247.5167 < pos[0] < 320.7534) && (-1640.1964 < pos[1] < -1569.4169)  )) // ligonines aps & beachside aps
					return SendInfoMessage(playerid,"Cia fejerverku deti negali.");
				if(pos[2] > 500.0 || pos[2] < -1.0)
					return SendInfoMessage(playerid,"Cia fejerverku deti negali.");
				if(DLItemID > 1 && IsPlayerInDynamicArea(playerid,GangArea[5])) // laivas
				{
					return SendInfoMessage(playerid,"Cia fejerverku deti negali.");
				}

				if(SafeArea(playerid) && !playerDB[playerid][admin])
					return SendInfoMessage(playerid,"Saugioje zonoje fejerverku deti negali.");
				new Float:xla,Float:yla,Float:zla;
				if(playerDB[playerid][fejerverkai][DLItemID]==false) return SendInfoMessage(playerid,"Neturi fejerverko!");
				if(GetPlayerInterior(playerid)!=0 || GetPlayerVehicleID(playerid) != 0 || GetPlayerHouseID(playerid) != 0 ) return SendInfoMessage(playerid,"Islisk i lauka!");

				if(playerDB[playerid][ant] || playerDB[playerid][suristas] || playerDB[playerid][pila])
					return SendInfoMessage(playerid,"Dabar deti fejerverku negali.");
				new Float:Coo[3];
				GetPlayerPos(playerid,Coo[0],Coo[1],Coo[2]);
				if(IsPlayerInRangeOfPointExXY(50.0,playerid,-60.7811,48.0869,3.1103)) // lsd
				{
					if(Coo[2] < 2.6) // lsd po zeme
					{
						AC_Warn(playerid,"FW po zeme");
						HideProgressBarForPlayer(playerid,Veiksmai);
						return 1;
					}
				}
				else if(IsPlayerInRangeOfPointExXY(50.0,playerid,2318.0364,38.2342,26.4844)) // ratai
				{
					if(Coo[2] < 26.0)
					{
						AC_Warn(playerid,"FW po zeme");
						return 1;
					}
				}
				else if(IsPlayerInRangeOfPointExXY(50.0,playerid,-365.9257,-1423.4869,25.7266)) // seklos
				{
					if(Coo[2] < 25.0)
					{
						AC_Warn(playerid,"FW po zeme");
						return 1;
					}
				}
				else if(IsPlayerInRangeOfPointExXY(50.0,playerid,213.6279,1867.3140,13.1406)) // ginklai
				{
					if(Coo[2] < 12.5)
					{
						SendInfoMessage(playerid,"Cia fw deti negali!");
						return 1;
					}
				}
				else if(IsPlayerInRangeOfPointExXY(50.0,playerid,2541.9163,-1296.3842,1044.1250)) // pinigai
				{
					if(Coo[2] < 1043.0)
					{
						AC_Warn(playerid,"FW po zeme");
						return 1;
					}
				}
				if(DLItemID == 0)
				{
					if(firecrackertime[playerid] == 0)
					{
						LogA(playerid,"FW(mazas)");
						firecrackertime[playerid] = 1;
						new string[128];
						new sendername[MAX_PLAYER_NAME];
						GetPlayerName(playerid, sendername, sizeof(sendername));
						format(string, sizeof(string), "<> %s ismeta maza fejerverka.", sendername);
						ProxDetector(15.0, playerid, string, WHITE,WHITE,WHITE,WHITE,WHITE);
						GetPlayerPos(playerid,xla,yla,zla);
						GetXYInFrontOfPlayer(playerid, xla,yla, 1);
						Firecracker[playerid] = CreateDynamicObject(1672, xla,yla,(zla-0.9), 0, 0, 0);
						SetTimerEx("FirecrackerTime", (2000+(random(3000))), 0, "i", playerid);
						playerDB[playerid][fejerverkai][DLItemID]=false;
						ProcessAchievement(playerid,101);
						UpdateStreamerFW(xla,yla,zla);
						return 1;
					}
					else return SendInfoMessage(playerid,"Tu jau paleidai fejerverka!");
				}
				else if(DLItemID == 1)
				{
					if(firecrackerroll[playerid] == 0)
					{
						LogA(playerid,"FW(dinamitas)");
						firecrackerroll[playerid] = 1;
						new string[128];
						new sendername[MAX_PLAYER_NAME];
						GetPlayerName(playerid, sendername, sizeof(sendername));
						format(string, sizeof(string), "<> %s ismeta dinamita.", sendername);
						ProxDetector(15.0, playerid, string, WHITE,WHITE,WHITE,WHITE,WHITE);
						GetPlayerPos(playerid,xla,yla,zla);
						GetXYInFrontOfPlayer(playerid, xla,yla, 1);
						CreateRoll(playerid,xla,yla,(zla-1.00));
						RollStartX[playerid] = xla;
						RollStartY[playerid] = yla;
						RollStartZ[playerid] = (zla-1.00);
						CrackerRollSmoke[playerid] = CreateDynamicObject(2780, xla,yla,(zla-5.00), 0, 0, 0);
						SetTimerEx("CrackerRollTime", (2000+(random(3000))), 0, "i", playerid);
						playerDB[playerid][fejerverkai][DLItemID]=false;
						ProcessAchievement(playerid,101);
						UpdateStreamerFW(xla,yla,zla);
						return 1;
					}
					else return SendInfoMessage(playerid,"Tu jau paleidai fejerverka!");
				}
				else if(DLItemID == 2)
				{
					if(firerockettime[playerid] == 0)
					{
						LogA(playerid,"FW(raketa)");
						firerockettime[playerid] = 1;
						new string[128];
						new sendername[MAX_PLAYER_NAME];
						GetPlayerName(playerid, sendername, sizeof(sendername));
						format(string, sizeof(string), "<> %s pastato raketos formos fejerverka.", sendername);
						ProxDetector(15.0, playerid, string, WHITE,WHITE,WHITE,WHITE,WHITE);
						GetPlayerPos(playerid,xla,yla,zla);
						GetXYInFrontOfPlayer(playerid, xla,yla, 2);
						Firerocket[playerid] = CreateDynamicObject(354, xla,yla,zla-1, 0, 0, 0);
						rocketsmoke[playerid] = CreateDynamicObject(2780, xla,yla,zla-1, 0, 0, 0);
						SetTimerEx("Raketos",3000,false,"iifff",playerid,1,xla,yla,zla);
						SetTimerEx("FirerocketTime", 6000, 0, "i", playerid);
						playerDB[playerid][fejerverkai][DLItemID]=false;
						ProcessAchievement(playerid,101);
						UpdateStreamerFW(xla,yla,zla);
						return 1;
					}
					else return SendInfoMessage(playerid,"Tu jau paleidai fejerverka!");
				}
				else if(DLItemID == 3)
				{
					if(firerockettime[playerid] == 0)
					{
						LogA(playerid,"FW(raketa)");
						firerockettime[playerid] = 2;
						new string[128];
						new sendername[MAX_PLAYER_NAME];
						GetPlayerName(playerid, sendername, sizeof(sendername));
						format(string, sizeof(string), "<> %s pastato raketos formos fejerverka.", sendername);
						ProxDetector(15.0, playerid, string, WHITE,WHITE,WHITE,WHITE,WHITE);
						GetPlayerPos(playerid,xla,yla,zla);
						GetXYInFrontOfPlayer(playerid, xla,yla, 2);
						Firerocket[playerid] = CreateDynamicObject(354, xla,yla,zla-1, 0, 0, 0);
						rocketsmoke[playerid] = CreateDynamicObject(2780, xla,yla,zla-1, 0, 0, 0);
						SetTimerEx("Raketos",3000,false,"iifff",playerid,2,xla,yla,zla);
						SetTimerEx("FirerocketTime", 6000, 0, "i", playerid);
						playerDB[playerid][fejerverkai][DLItemID]=false;
						ProcessAchievement(playerid,101);
						UpdateStreamerFW(xla,yla,zla);
						return 1;
					}
					else return SendInfoMessage(playerid,"Tu jau paleidai fejerverka!");
				}
				else if(DLItemID == 4)
				{
					if(Fountain1Time[playerid] == 0 && Fountain2Time[playerid] == 0 && Fountain3Time[playerid] == 0)
					{
						LogA(playerid,"FW(fontanas)");
						Fountain1Time[playerid] = 1;
						new string[128];
						new sendername[MAX_PLAYER_NAME];
						GetPlayerName(playerid, sendername, sizeof(sendername));
						format(string, sizeof(string), "<> %s padeda fontanini fejerverka.", sendername);
						ProxDetector(15.0, playerid, string, WHITE,WHITE,WHITE,WHITE,WHITE);
						GetPlayerPos(playerid,xla,yla,zla);
						GetXYInFrontOfPlayer(playerid, xla,yla, 2);
						FTX[playerid] = xla;
						FTY[playerid] = yla;
						FTZ[playerid] = (zla-1.0);
						Fountain[playerid] = CreateDynamicObject(354, xla,yla,(zla-1.0), 0, 0, 0);
						FountainSmoke[playerid] = CreateDynamicObject(2780, xla,yla,(zla-1.0), 0, 0, 0);
						SetTimerEx("FountainTimer", 3000, 0, "i", playerid);
						playerDB[playerid][fejerverkai][DLItemID]=false;
						ProcessAchievement(playerid,101);
						UpdateStreamerFW(xla,yla,zla);
						return 1;
					}
					else return SendInfoMessage(playerid,"Tu jau paleidai fejerverka!");
				}
				else if(DLItemID == 5)
				{
					if(Fountain1Time[playerid] == 0 && Fountain2Time[playerid] == 0 && Fountain3Time[playerid] == 0)
					{
						LogA(playerid,"FW(fontanas)");
						Fountain2Time[playerid] = 1;
						new string[128];
						new sendername[MAX_PLAYER_NAME];
						GetPlayerName(playerid, sendername, sizeof(sendername));
						format(string, sizeof(string), "<> %s padeda fontanini fejerverka.", sendername);
						ProxDetector(15.0, playerid, string, WHITE,WHITE,WHITE,WHITE,WHITE);
						GetPlayerPos(playerid,xla,yla,zla);
						GetXYInFrontOfPlayer(playerid, xla,yla, 2);
						FTX[playerid] = xla;
						FTY[playerid] = yla;
						FTZ[playerid] = (zla-1.0);
						Fountain[playerid] = CreateDynamicObject(354,xla,yla,(zla-1.0), 0, 0, 0);
						FountainSmoke[playerid] = CreateDynamicObject(2780, xla,yla,(zla-1.0), 0, 0, 0);
						SetTimerEx("FountainTimer", 3000, 0, "i", playerid);
						playerDB[playerid][fejerverkai][DLItemID]=false;
						ProcessAchievement(playerid,101);
						UpdateStreamerFW(xla,yla,zla);
						return 1;
					}
					else return SendInfoMessage(playerid,"Tu jau paleidai fejerverka!");
				}
				else if(DLItemID == 6)
				{
					if(Fountain1Time[playerid] == 0 && Fountain2Time[playerid] == 0 && Fountain3Time[playerid] == 0)
					{
						LogA(playerid,"FW(fontanas)");
						Fountain3Time[playerid] = 1;
						new string[128];
						new sendername[MAX_PLAYER_NAME];
						GetPlayerName(playerid, sendername, sizeof(sendername));
						format(string, sizeof(string), "<> %s padeda fontanini fejerverka.", sendername);
						ProxDetector(15.0, playerid, string, WHITE,WHITE,WHITE,WHITE,WHITE);
						GetPlayerPos(playerid,xla,yla,zla);
						GetXYInFrontOfPlayer(playerid, xla,yla, 2);
						FTX[playerid] = xla;
						FTY[playerid] = yla;
						FTZ[playerid] = (zla-1.0);
						Fountain[playerid] = CreateDynamicObject(354, xla,yla,(zla-1.0), 0, 0, 0);
						FountainSmoke[playerid] = CreateDynamicObject(2780, xla,yla,(zla-1.0), 0, 0, 0);
						SetTimerEx("FountainTimer", 3000, 0, "i", playerid);
						playerDB[playerid][fejerverkai][DLItemID]=false;
						ProcessAchievement(playerid,101);
						UpdateStreamerFW(xla,yla,zla);
						return 1;
					}
					else return SendInfoMessage(playerid,"Tu jau paleidai fejerverka!");
				}
				else if(DLItemID == 7)
				{
					if(RocketBoxTime[playerid] == 0)
					{
						LogA(playerid,"FW(baterija)");
						RocketBoxTime[playerid] = 1;
						new string[128];
						new sendername[MAX_PLAYER_NAME];
						GetPlayerName(playerid, sendername, sizeof(sendername));
						format(string, sizeof(string), "<> %s pastato baterija ant zemes.", sendername);
						ProxDetector(15.0, playerid, string, WHITE,WHITE,WHITE,WHITE,WHITE);
						GetPlayerPos(playerid,xla,yla,zla);
						GetXYInFrontOfPlayer(playerid, xla,yla, 2);
						RBX[playerid] = xla;
						RBY[playerid] = yla;
						RBZ[playerid] = (zla-1.0);
						RocketBox[playerid] = CreateDynamicObject(354, xla,yla,(zla-1.0), 0, 0, 0);
						RocketBoxSmoke[playerid] = CreateDynamicObject(2780, xla,yla,(zla-1.0), 0, 0, 0);
						SetTimerEx("RocketBoxTimer", 3000, 0, "i", playerid);
						playerDB[playerid][fejerverkai][DLItemID]=false;
						ProcessAchievement(playerid,101);
						UpdateStreamerFW(xla,yla,zla);
						return 1;
					}
					else return SendInfoMessage(playerid,"Tu jau paleidai fejerverka!");
				}
				else return SendInfoMessage(playerid,"Tokios rusies nera!");
			}
		}
		if(dialogid == 3996) if(response)
		{
			new string[128];
			new price = (aVehicleNames[Carlist[playerid][Typ]][Price]/5)*2;
			if(Carlist[playerid][Typ]==149)
				price = 100;
			if (IsPlayerInVehicle(playerid,Carlist[playerid][Carid])) { RemovePlayerFromVehicle(playerid); }
			GivePlayerMoneyA(playerid, price);
			DestroyVehicle(Carlist[playerid][Carid]);
			Carlist[playerid][Typ]=-1; Carlist[playerid][X]=0.0; Carlist[playerid][Y]=0.0; Carlist[playerid][Z]=0.0;
			Carlist[playerid][Rotation]=0.0; Carlist[playerid][Status]=0; Carlist[playerid][Lock]=0; Carlist[playerid][Carid]=-1;
			Carlist[playerid][Color1]=-1; Carlist[playerid][Color2]=-1; Carlist[playerid][mod1]=-1; Carlist[playerid][mod2]=-1;
			Carlist[playerid][mod3]=-1; Carlist[playerid][mod4]=-1; Carlist[playerid][mod5]=-1; Carlist[playerid][mod6]=-1;
			Carlist[playerid][mod7]=-1; Carlist[playerid][mod8]=-1; Carlist[playerid][mod9]=-1; Carlist[playerid][mod10]=-1;
			Carlist[playerid][mod11]=-1; Carlist[playerid][mod12]=-1; Carlist[playerid][mod13]=-1; Carlist[playerid][mod14]=-1;
			Carlist[playerid][mod15]=-1; Carlist[playerid][mod16]=-1; Carlist[playerid][mod17]=-1; Carlist[playerid][Paintjob]=-1;
			Carlist[playerid][CDraud]=0; Carlist[playerid][Gas]=-1; Carlist[playerid][Sirena]=0; Carlist[playerid][Energy]=-1; Carlist[playerid][VirtualW]=0;
			format(Carlist[playerid][NumPlate],40,"{FF0000}NERA");
			format(string,128,"Jus pardavete savo masina uz %iEUR!",price);
			SendInfoMessage(playerid,string);
		}
		if(dialogid == 3997) if(response)
		{

			new string[128];
			new price = (aVehicleNames[Carlist2[playerid][Typ]][Price]/5)*2;
			if(Carlist2[playerid][Typ]==149)
				price = 100;
			if (IsPlayerInVehicle(playerid,Carlist2[playerid][Carid])) { RemovePlayerFromVehicle(playerid); }
			GivePlayerMoneyA(playerid, price);
			DestroyVehicle(Carlist2[playerid][Carid]);
			Carlist2[playerid][Typ]=-1; Carlist2[playerid][X]=0.0; Carlist2[playerid][Y]=0.0; Carlist2[playerid][Z]=0.0;
			Carlist2[playerid][Rotation]=0.0; Carlist2[playerid][Status]=0; Carlist2[playerid][Lock]=0; Carlist2[playerid][Carid]=-1;
			Carlist2[playerid][Color1]=-1; Carlist2[playerid][Color2]=-1; Carlist2[playerid][mod1]=-1; Carlist2[playerid][mod2]=-1;
			Carlist2[playerid][mod3]=-1; Carlist2[playerid][mod4]=-1; Carlist2[playerid][mod5]=-1; Carlist2[playerid][mod6]=-1;
			Carlist2[playerid][mod7]=-1; Carlist2[playerid][mod8]=-1; Carlist2[playerid][mod9]=-1; Carlist2[playerid][mod10]=-1;
			Carlist2[playerid][mod11]=-1; Carlist2[playerid][mod12]=-1; Carlist2[playerid][mod13]=-1; Carlist2[playerid][mod14]=-1;
			Carlist2[playerid][mod15]=-1; Carlist2[playerid][mod16]=-1; Carlist2[playerid][mod17]=-1; Carlist2[playerid][Paintjob]=-1;
			Carlist2[playerid][CDraud]=0;  Carlist2[playerid][Gas]=-1; Carlist2[playerid][Sirena]=0; Carlist2[playerid][Energy]=-1; Carlist2[playerid][VirtualW]=0;
			format(Carlist2[playerid][NumPlate],40,"{FF0000}NERA");
			format(string,128,"Jus pardavete savo masina uz %iEUR!",price);
			SendInfoMessage(playerid,string);
		}
		if(dialogid == 3998) if(response)
		{
			new string[128];
			new price = (aVehicleNames[Carlist3[playerid][Typ]][Price]/5)*2;
			if(Carlist3[playerid][Typ]==149)
				price = 100;
			if (IsPlayerInVehicle(playerid,Carlist3[playerid][Carid])) { RemovePlayerFromVehicle(playerid); }
			GivePlayerMoneyA(playerid, price);
			DestroyVehicle(Carlist3[playerid][Carid]);
			Carlist3[playerid][Typ]=-1; Carlist3[playerid][X]=0.0; Carlist3[playerid][Y]=0.0; Carlist3[playerid][Z]=0.0;
			Carlist3[playerid][Rotation]=0.0; Carlist3[playerid][Status]=0; Carlist3[playerid][Lock]=0; Carlist3[playerid][Carid]=-1;
			Carlist3[playerid][Color1]=-1; Carlist3[playerid][Color2]=-1; Carlist3[playerid][mod1]=-1; Carlist3[playerid][mod2]=-1;
			Carlist3[playerid][mod3]=-1; Carlist3[playerid][mod4]=-1; Carlist3[playerid][mod5]=-1; Carlist3[playerid][mod6]=-1;
			Carlist3[playerid][mod7]=-1; Carlist3[playerid][mod8]=-1; Carlist3[playerid][mod9]=-1; Carlist3[playerid][mod10]=-1;
			Carlist3[playerid][mod11]=-1; Carlist3[playerid][mod12]=-1; Carlist3[playerid][mod13]=-1; Carlist3[playerid][mod14]=-1;
			Carlist3[playerid][mod15]=-1; Carlist3[playerid][mod16]=-1; Carlist3[playerid][mod17]=-1; Carlist3[playerid][Paintjob]=-1;
			Carlist3[playerid][CDraud]=0; Carlist3[playerid][Gas]=-1; Carlist3[playerid][Sirena]=0; Carlist3[playerid][Energy]=-1; Carlist3[playerid][VirtualW]=0;
			
			format(Carlist3[playerid][NumPlate],40,"{FF0000}NERA");
			format(string,128,"Jus pardavete savo masina uz %iEUR!",price);
			SendInfoMessage(playerid,string);
		}
		if(dialogid==302)
		{
			if(response)
			{
				new string[128];
				if(DLItemID == 0)
				{
					if (Carlist[playerid][Typ]!=-1)
					{
						if (Carlist[playerid][Status]==0)
						{
							new reparatur = floatround(aVehicleNames[Carlist[playerid][Typ]][Repair]/AdjustByRida(0,RIDA_REMONTAS,Carlist[playerid][Rida]));
							if (reparatur <= GetPlayerMoneyA(playerid))
							{
								Carlist[playerid][VeHP]=1000;
								Carlist[playerid][Status]=1;
								Carlist[playerid][Carid]=CreateTunedCar(playerid);
								GivePlayerMoneyA(playerid, - reparatur);
								format(string, 128, "Jus susiremontavote savo masina uz %iEUR~n~ Ji atsirado ten kur ja priparkavote.", reparatur);
								SendInfoMessage(playerid,string);
							}
								else { format(string, 128, "Nepakanka pinigu remontui~n~reikia: %iEUR", reparatur); SendInfoMessage(playerid,string); }
						}
						else { SendInfoMessage(playerid,"Jusu masinai nereikia remonto!"); }
					}
					else { SendInfoMessage(playerid,"Jus pirmos neturite masinos!"); }
					return 1;
				}
				if(DLItemID == 1)
				{
					if (Carlist2[playerid][Typ]!=-1)
					{
						if (Carlist2[playerid][Status]==0)
						{
							new reparatur = floatround(aVehicleNames[Carlist2[playerid][Typ]][Repair]/AdjustByRida(0,RIDA_REMONTAS,Carlist2[playerid][Rida]));
							if (reparatur <= GetPlayerMoneyA(playerid))
							{
								Carlist2[playerid][VeHP]=1000;
								Carlist2[playerid][Status]=1;
								Carlist2[playerid][Carid]=CreateTunedCar2(playerid);
								GivePlayerMoneyA(playerid, - reparatur);
								format(string, 128, "Jus susiremontavote savo masina uz %iEUR!~n~ Ji atsirado ten kur ja priparkavote.", reparatur);
								SendInfoMessage(playerid,string);
							}
								else { format(string, 128, "Nepakanka pinigu remontui~n~reikia: %iEUR!", reparatur); SendInfoMessage(playerid,string); }
						}
						else { SendInfoMessage(playerid,"Jusu masinai nereikia remonto!"); }
					}
					else { SendInfoMessage(playerid,"Jus antros neturite masinos!"); }
					return 1;
				}
				if(DLItemID == 2)
				{
					if (Carlist3[playerid][Typ]!=-1)
					{
						if (Carlist3[playerid][Status]==0)
						{
							new reparatur = floatround(aVehicleNames[Carlist3[playerid][Typ]][Repair]/AdjustByRida(0,RIDA_REMONTAS,Carlist3[playerid][Rida]));
							if (reparatur <= GetPlayerMoneyA(playerid))
							{
								Carlist3[playerid][VeHP]=1000;
								Carlist3[playerid][Status]=1;
								Carlist3[playerid][Carid]=CreateTunedCar3(playerid);
								GivePlayerMoneyA(playerid, - reparatur);
								format(string, 128, "Jus susiremontavote savo masina uz %iEUR!~n~ Ji atsirado ten kur ja priparkavote.", reparatur);
								SendInfoMessage(playerid,string);
							}
								else { format(string, 128, "Nepakanka pinigu remontui~n~reikia: %iEUR!", reparatur); SendInfoMessage(playerid, string); }
						}
						else { SendInfoMessage(playerid,"Jusu masinai nereikia remonto!"); }
					}
					else { SendInfoMessage(playerid,"Jus neturite masinos!"); }
					return 1;
				}
			}
		}
		if(dialogid==301)
		{
			if(response)
			{
				if(DLItemID == 0)
				{
					if (Carlist[playerid][Typ]!=-1)
					{
						if (Carlist[playerid][Carid]!=-1)
						{
							new name[24];
							GetPlayerName(playerid,name,24);
							new Float:sx,Float:sy,Float:sz;
							GetVehiclePos(Carlist[playerid][Carid],sx,sy,sz);
							if(sy < -1483.6194 && sy > -1507.2380 && sx < 1546.4885 && sx > 1464.6373)
							{
								SendInfoMessage(playerid,"Jus negalite atrakinti konfiskuotos masinos!");
							}
							else
							{
								if (Carlist[playerid][Lock]==0)
								{
									Carlist[playerid][Lock]=1;
									SetVehicleParamsForAll(Carlist[playerid][Carid],0,1);
									SetVehicleParamsForPlayerEx(Carlist[playerid][Carid],playerid,0,0);
									SendInfoMessage(playerid,"~r~Jus uzrakinote savo masina.");
								}
								else
								{
									Carlist[playerid][Lock]=0;
									SetVehicleParamsForAll(Carlist[playerid][Carid],0,0);
									SendInfoMessage(playerid,"~g~Jus atrakinote savo masina.");
								}
							}
						}
						else { SendInfoMessage(playerid,"Jusu masina yra sunaikinta. Susiremontuokite ja."); }
					}
					else
					{
						SendInfoMessage(playerid,"Ka? Jus neturite masinos!");
					}
					return 1;
				}
				if(DLItemID == 1)
				{
					if (Carlist2[playerid][Typ]!=-1)
					{
						if (Carlist2[playerid][Carid]!=-1)
						{
							new name[24];
							GetPlayerName(playerid,name,24);
							new Float:sx,Float:sy,Float:sz;
							GetVehiclePos(Carlist2[playerid][Carid],sx,sy,sz);
							if(sy < -1483.6194 && sy > -1507.2380 && sx < 1546.4885 && sx > 1464.6373)
							{
								SendInfoMessage(playerid,"Jus negalite atrakinti konfiskuotos masinos!");
							}
							else
							{
								if (Carlist2[playerid][Lock]==0)
								{
									Carlist2[playerid][Lock]=1;
									SetVehicleParamsForAll(Carlist2[playerid][Carid],0,1);
									SetVehicleParamsForPlayerEx(Carlist2[playerid][Carid],playerid,0,0);
									SendInfoMessage(playerid,"~r~Jus uzrakinote savo masina.");
								}
								else
								{
									Carlist2[playerid][Lock]=0;
									SetVehicleParamsForAll(Carlist2[playerid][Carid],0,0);
									SendInfoMessage(playerid,"~g~Jus atrakinote savo masina.");
								}
							}
						}
						else { SendInfoMessage(playerid,"Jusu masina yra sunaikinta. Susiremontuokite ja."); }
					}
					else
					{
						SendInfoMessage(playerid,"Ka? Jus neturite masinos!");
					}
					return 1;
				}
				if(DLItemID == 2)
				{
					if (Carlist3[playerid][Typ]!=-1)
					{
						if (Carlist3[playerid][Carid]!=-1)
						{
							new name[24];
							GetPlayerName(playerid,name,24);
							new Float:sx,Float:sy,Float:sz;
							GetVehiclePos(Carlist3[playerid][Carid],sx,sy,sz);
							if(sy < -1483.6194 && sy > -1507.2380 && sx < 1546.4885 && sx > 1464.6373)
							{
								SendInfoMessage(playerid,"Jus negalite atrakinti konfiskuotos masinos!");
							}
							else
							{
								if (Carlist3[playerid][Lock]==0)
								{
									Carlist3[playerid][Lock]=1;
									SetVehicleParamsForAll(Carlist3[playerid][Carid],0,1);
									SetVehicleParamsForPlayerEx(Carlist3[playerid][Carid],playerid,0,0);
									SendInfoMessage(playerid,"~r~Jus uzrakinote savo masina.");
								}
								else
								{
									Carlist3[playerid][Lock]=0;
									SetVehicleParamsForAll(Carlist3[playerid][Carid],0,0);
									SendInfoMessage(playerid,"~g~Jus atrakinote savo masina.");
								}
							}
						}
						else { SendInfoMessage(playerid,"Jusu masina yra sunaikinta. Susiremontuokite ja."); }
					}
					else
					{
						SendInfoMessage(playerid,"Ka? Jus neturite masinos!");
					}
					return 1;
				}
			}
		}
		if(dialogid==410)
		{
			if(response)
			{
				//if(GetPlayerMoneyA(playerid) < 250) return SendClientMessage(playerid, RED, " * Truksta pinigu!!");
				//GivePlayerMoneyA(playerid,-250);
				SendInfoMessage(playerid,"Sekmingai pasiemete kortele");
				//BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning]+=150;
				//BusinessMoney(250);
				playerDB[playerid][kortele]=true;
				ApplyAnimation(playerid, "GANGS", "DEALER_DEAL", 4.000000, 0, 0, 0, 0, -1);
				playerDB[playerid][cekis]=0;
				return 1;
			}
			else
			{
				//playerDB[playerid][cekis]=0;
				SendInfoMessage(playerid,"Geros dienos!");
				return 1;
			}// ids:605,616,410,610,610

		}
		/*if(dialogid==1010)
		{
			if(response)
			{
				if(GetPlayerMoneyA(playerid) < 1000) return SendClientMessage(playerid,RED,"* Skinai kainuoja 1000€.");
				if(playerDB[playerid][uniformd]) return SendClientMessage(playerid,RED,"* Jus esate su darbine uniforma. Rasykite /persirengti");
				new skinz = Shopas[listitem][skinas];
				playerDB[playerid][paskutinisrubas]=GetPlayerSkin(playerid);
				SetPlayerSkin(playerid,skinz);
				Stop(playerid);
				ApplyAnimation(playerid,"PLAYIDLES","stretch",4.1,0,0,0,0,0);
				ShowPlayerDialog(playerid,1011,DIALOG_STYLE_MSGBOX,"Parduotuve","Pirkti rubus?\nKaina: 1000€.\nRubai liks visam laikui.","Taip","Ne");
	//GivePlayerMoneyA(playerid, -1000);
				return 1;
			}
		}
		if(dialogid==1011)
		{
			if(response)
			{
				if(GetPlayerMoneyA(playerid) < 1000) return SendClientMessage(playerid,RED,"* Skinai kainuoja 1000€.");
				if(playerDB[playerid][uniformd]) return SendClientMessage(playerid,RED,"* Jus esate su darbine uniforma. Rasykite /persirengti");
				GivePlayerMoneyA(playerid, -1000);
				playerDB[playerid][drabuziai]=GetPlayerSkin(playerid);
				playerDB[playerid][paskutinisrubas]=-1;
				Stop(playerid);
				BusinessInfo[GetPlayerVirtualWorld(playerid)-500][bEarning]+=900;
				new listas[1024];
				for(new i;i<Skinu;i++)
				{
					format(listas,sizeof(listas),"%s\n%s",listas,Shopas[ i ][ pavadinimas ]);
				}
				ShowPlayerDialog(playerid,1010,DIALOG_STYLE_LIST,"Aprangos",listas,"Rinktis","Iseiti");
				return 1;
			}
			else if(!response)
			{
				SetPlayerSkin(playerid,playerDB[playerid][paskutinisrubas]);
				playerDB[playerid][paskutinisrubas]=-1;
				Stop(playerid);
				return 1;
			}
		}*/
		if(dialogid==1011)
		{
			if(response)
			{
				if(playerDB[playerid][uniformd]) return SendInfoMessage(playerid,"Nusirenkite darbine uniforma.");
				new query[128];
				format(query,sizeof(query),"SELECT Skin FROM Spinta Where Vardas='%s' ORDER BY LastUsed DESC",ReturnName(playerid));
				mysql_function_query(SQL, query, true, "SQL_Skinas", "ii", playerid,listitem);

			} 
		}
		if(dialogid==1012)
		{
			if(response)
			{
//				new id=listitem;
				new query[128];
				format(query,sizeof(query),"SELECT Color FROM Spalvos Where Vardas='%s'",ReturnName(playerid));
				mysql_function_query(SQL, query, true, "SQL_SpalvaSet", "ii", playerid,listitem);
				//for(new 
				//new query[128];
				//format(query,sizeof(query),"SELECT Color FROM Spalvos Where Vardas='%s'",ReturnName(playerid));
				//mysql_function_query(SQL, query, true, "SQL_Spalvos", "i",playerid);
			
			}
		}
		if(dialogid==102)
		{
			if(response)
			{
				if(listitem == 0) // piltikura
				{
					SetPlayerCheckpoint(playerid,-986.79,-710.74,32.01,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
				if(listitem == 1) // ispilti kura
				{
					ShowPlayerDialog(playerid,101,DIALOG_STYLE_LIST,"Vietos","1\n2\n3\n4\n5\n6\n7\n8\n9\n10","Rinktis","Iseiti");
					return 1;
				}
				if(listitem == 2) // krauti paletes
				{
					SetPlayerCheckpoint(playerid,-1866.5500,-1715.6100,22.7000,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite paletes.");
					return 1;
				}
				if(listitem == 3) // iskrauti paletes
				{
					ShowPlayerDialog(playerid,103,DIALOG_STYLE_LIST,"Vietos","1\n2","Rinktis","Iseiti");
					return 1;
				}
				if(listitem == 4) // krauti tv
				{
					SetPlayerCheckpoint(playerid,-18.8600,-270.5700,5.4300,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite paletes.");
					return 1;
				}
				if(listitem == 5) // iskrauti tv
				{
					ShowPlayerDialog(playerid,104,DIALOG_STYLE_LIST,"Vietos","1\n2\n3","Rinktis","Iseiti");
					return 1;
				}
			}
			if(!response) return 1;
		}
		if(dialogid==103) // iskrauti paletes
		{
			if(response)
			{
				if(listitem == 0)
				{
					SetPlayerCheckpoint(playerid,-2457.4172,790.4736,35.1719,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite paleciu iskrovima.");
					return 1;
				}
				if(listitem == 1)
				{
					SetPlayerCheckpoint(playerid,-2540.2522,-52.6456,16.5594,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite paleciu iskrovima.");
					return 1;
				}
			}
			if(!response) return 1;
		}
		if(dialogid==104) // iskrauti tv
		{
			if(response)
			{
				if(listitem == 0)
				{
					SetPlayerCheckpoint(playerid,2876.0300,920.5000,10.7500,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite tv iskrovima.");
					return 1;
				}
				if(listitem == 1)
				{
					SetPlayerCheckpoint(playerid,1682.4900,2326.8700,10.8200,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite tv iskrovima.");
					return 1;
				}
				if(listitem == 2)
				{
					SetPlayerCheckpoint(playerid,1438.2200,975.6000,10.8100,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite tv iskrovima.");
					return 1;
				}
			}
			if(!response) return 1;
		}




		if(dialogid==101) // ispilti kura.
		{
			if(response)
			{
				if(listitem == 0)
				{
					SetPlayerCheckpoint(playerid,2478.93,-2078.63,13.55,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
				if(listitem == 1)
				{
					SetPlayerCheckpoint(playerid,-2414.9436,995.9910,45.3016,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
				if(listitem == 2)
				{
					SetPlayerCheckpoint(playerid,-2038.6443,141.0242,28.8429,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite paletes.");
					return 1;
				}
				if(listitem == 3)
				{
					SetPlayerCheckpoint(playerid,-1700.5726,415.7048,7.1797,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
				if(listitem == 4)
				{
					SetPlayerCheckpoint(playerid,1609.4260,2240.9463,10.8203,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
				if(listitem == 5)
				{
					SetPlayerCheckpoint(playerid,2188.0750,2464.7031,11.2422,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
				if(listitem == 6)
				{
					SetPlayerCheckpoint(playerid,2877.2361,920.4135,10.7500,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
				if(listitem == 7)
				{
					SetPlayerCheckpoint(playerid,-72.2638,-1163.2455,1.8936,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
				if(listitem == 8)
				{
					SetPlayerCheckpoint(playerid,638.3459,1683.8516,6.9922,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
				if(listitem == 9)
				{
					SetPlayerCheckpoint(playerid,-1739.3656,177.4001,3.5547,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
			}
			if(!response) return 1;
		}


		if(dialogid==588)
		{
			if(response)
			{
				ShowPlayerDialog(playerid,589,DIALOG_STYLE_INPUT,"Bankomatas","Iveskite suma pinigu, kiek norite paimti.","Paimti","Iseiti");
				return 1;
			}
			if(!response) return 1;
		}
		if(dialogid==8)
		{
			if(response)
			{
				if(GetPlayerMoneyA(playerid) < COST_TEORIJA) return SendInfoMessage(playerid,"~r~Jus neuztenka pinigu.");
				GivePlayerMoneyA(playerid, -COST_TEORIJA);
				new string[2024];
				format(string,sizeof(string),"Privaloma vaþiuoti tik keliu ir tik deðine eismo juosta.\n Á prieðprieðinæ eismo juostà galima trumpam iðlásti siekiant aplenkti kliûtá.\nJeigu jums dega þalias ðviesoforo signalas, galite dràsiai vaþiuoti á visas puses.\n Jeigu dega raudonas ðviesoforo signalas, privalote sustoti ir palaukti þalio,nebent sukate á deðinæ.\n ");
				format(string,sizeof(string),"%sGeltonà signalà kirsti galima tik tada, jeigu manote, kad vaþiuojate per greitai, kad laiku sustotumëte.\n Nuo nakties 1h iki ryto 6h ðviesoforai dël nedidelio eismo iðjungiami, taigi ðiuo paros metu galima jø nepaisyti.\n",string);
				format(string,sizeof(string),"%sJeigu jûsø kelio puse vaþiuoja spec. transportas su ájungtais ðvyturëliais, privalote pristabdyti ir pasitraukti á ðalikelæ.\nDidþiausias leistinas greitis mieste 100km/h (kai kur 110km/h).\nKonfliktus su kitais eismo dalyviais bei policininkais spræskite taikiai, neskubëdami.\n",string);
				format(string,sizeof(string),"%sNetaikus konfliktø sprendimo bûdas jums gali atsieiti bauda arba kalëjimu.\nDraudþiama uþvaziuoti ant zmogaus ir laukti, kol sis numirs, uþ tai gresia BAN.\nNorëdami pradëti testà - spauskite Pradëti",string);
				ShowPlayerDialog(playerid,990,DIALOG_STYLE_MSGBOX,"Keliu Eismo Taisykles",string,"Pradëti","Iseiti");
				playerDB[playerid][balas]=0;
				return 1;
			}

		}
		if(dialogid==990)
		{
			if(response)
			{
				ShowPlayerDialog(playerid,991,DIALOG_STYLE_MSGBOX,"Testas","Vaþiuojate keliu tiesiai ir uþsidega raudonas ðviesoforo signalas.\n1. Sustojate arba sukate á deðinæ\n2. Toliau vaþiuojate tiesiai arba sukate á kairæ","1.","2.");
				//GerasAts1;
			}
		}
		if(dialogid==991)
		{
			ShowPlayerDialog(playerid,992,DIALOG_STYLE_MSGBOX,"Testas","Kokiu paros metu iðjungiami ðviesoforai, taigi galima nepaisyti jø signalø?\n1. Nëra tokio meto\n2. 01:00AM - 06:00AM","1.","2.");
			GerasAts1;
		}
		if(dialogid==992)
		{
			ShowPlayerDialog(playerid,993,DIALOG_STYLE_MSGBOX,"Testas","Kuria kelio puse leidþiama vaþiuoti?\n1. Deðine\n2. Kaire","1.","2.");
			GerasAts2;
		}
		if(dialogid==993)
		{
			ShowPlayerDialog(playerid,994,DIALOG_STYLE_MSGBOX,"Testas","Susidarë automobiliø spûstis.\n1. Sustojate ir laukiate, kol ji sumaþës\n2. Apvaþiuojate jà prieðprieðine eismo juosta arba per ðaligatvá","1.","2.");
			GerasAts1;
		}
		if(dialogid==994)
		{
			ShowPlayerDialog(playerid,995,DIALOG_STYLE_MSGBOX,"Testas","Matote, kad neiðvengsite gulinèio policininko.\n1. Pristabdote ir lëtai pravaþiuojate\n2. Apvaþiuojate per ðaligatvá","1.","2.");
			GerasAts1;
		}
		if(dialogid==995)
		{
			ShowPlayerDialog(playerid,996,DIALOG_STYLE_MSGBOX,"Testas","Koks didþiausias leistinas greitis mieste ir uþ jo?\n1. Mieste 100km/h, uþmiestyje 120km/h\n2. Mieste 100km/h, uþmiestyje neribojamas","1.","2.");
			GerasAts1;
		}
		if(dialogid==996)
		{
			ShowPlayerDialog(playerid,997,DIALOG_STYLE_MSGBOX,"Testas","Jûsø kelio puse vaþiuoja spec. transportas, ájungæs sirenas/ðvyturëlius.\n1. Skubiai pristabdote ir pasitraukiate á ðalikelæ\n2. Nekreipdami dëmesio vaþiuojate toliau","1.","2.");
			GerasAts2;
		}
		if(dialogid==997)
		{
			ShowPlayerDialog(playerid,998,DIALOG_STYLE_MSGBOX,"Testas","Jus surakina policininkas.\n1. Nedelsdami raðote adminams, kad jûs nekaltas.\n2. Palaukiate, kol jis pasakys paþeidimà","1.","2.");
			GerasAts1;
		}
		if(dialogid==998)
		{
			ShowPlayerDialog(playerid,999,DIALOG_STYLE_MSGBOX,"Testas","Á jus atsitrenkia kita maðina.\n1. Iðlipæs suðaudote vairuotojà ir raðote adminams, kad sutaisytø maðinà\n2. Susitariate su kaltininku arba kvieèiate policijà","1.","2.");
			GerasAts2;
		}
		if(dialogid==999)
		{
			ShowPlayerDialog(playerid,1000,DIALOG_STYLE_MSGBOX,"Testas","Partenkiate þmogø.\n1. Uþvaþiuojate ant jo ir laukiate, kol ðis numirs\n2. Jeigu suþeistas nesmarkiai, atsipraðote ir vaþiuojate toliau","1.","2.");
			GerasAts2;
		}
		if(dialogid==1000)
		{
			new msg[128];
			GerasAts2;
			if(playerDB[playerid][balas] >= 9)
			{
				format(msg,128," Surinkote:\n %i/10 balø!\nTeorinis Testas iðlaikytas. Dabar eikite laikyti praktinio testo.",playerDB[playerid][balas]);
				playerDB[playerid][teor]=true;
			}
			else
			{
				format(msg,128," Surinkote:\n %i/10 balø!\nTeorinis Testas neiðlaikytas. Bandykite dar karta.",playerDB[playerid][balas]);
			}
			playerDB[playerid][balas] = 0;
			ShowPlayerDialog(playerid,1001,DIALOG_STYLE_MSGBOX,"Testas",msg,"Gerai","");
		}
		if(dialogid==887) // narkotikai
		{
			NarkResponse(playerid, response);
			return 1;
		}
		if(dialogid==886)
		{
			KreditaiResponse(playerid, response);
			return 1;
		}


		if(dialogid==888)
		{
			new bauda = playerDB[playerid][rkaina][1];
			new mentas = playerDB[playerid][rid][1];

			new mzzg[128];
			new vardas[MAX_PLAYER_NAME],police[MAX_PLAYER_NAME];
			if(response)
			{
				if(bauda < GetPlayerWantedLevel(playerid)*1000)
				{
					SendClientMessage(playerid,RED,"* Jûsø bauda pakilo nes gavote daugiau þvaigþduèiø.");
					SendClientMessage(mentas,RED,"* Þaidëjas gavo daugiau þvaigþduèiø. Pasiûlykite baudà ið naujo.");
					return 1;
				}
				GetPlayerName(mentas,police,sizeof(police));
				GetPlayerName(playerid,vardas,sizeof(vardas));
				if(GetPlayerMoneyA(playerid) < bauda)
				{
					SendClientMessage(playerid,RED,"* Kiðeneje neturite tiek pinigø, gal mokësite kreditine kortele?");
					SendClientMessage(mentas,RED,"* Þaidejas tiek pinigø kiðenëje neturi, gal mokës kreditine kortele?");
					if(!playerDB[playerid][kortele])
					{
						SendClientMessage(playerid,GREEN,"* Jûs neturite banko kortelës!");
						SendClientMessage(mentas,GREEN,"* Þaidëjas neturi banko kortelës!");
						RemovePlayerFromVehicle(playerid);
						return 1;
					}
					if(playerDB[playerid][banke]<bauda)
					{
						SendClientMessage(playerid,RED,"* Jûs tiek neturite");
						SendClientMessage(mentas,RED,"* Þaidëjas banke tiek pinigø neturi");
						RemovePlayerFromVehicle(playerid);
					}
					else
					{
						playerDB[playerid][banke]-=bauda;
						//GivePlayerMoneyA(mentas,bauda);
						Pelnas(mentas,79,bauda);//pelnas[79]+=floatround(bauda);
						GivePlayerMoneyA(mentas,floatround(bauda*0.4));
						SendClientMessage(playerid,RED,"* Bauda sumokëta, jûs iðteisintas!");
						SendClientMessage(mentas,RED,"* Bauda sumokëta, þaidejas iðteisintas!");
						SetPlayerWantedLevel(playerid,0);
						playerDB[mentas][jobpts]++;
						format(mzzg,sizeof(mzzg),"[racija] %s: %s sumokejo bauda ir buvo isteisintas!",police,vardas);
						SendMessageToTeisesauga(RED,mzzg);
					}
				}
				else
				{
					GivePlayerMoneyA(playerid,-bauda);
					//GivePlayerMoneyA(mentas,bauda);
					GivePlayerMoneyA(mentas,floatround(bauda*0.4));
					Pelnas(mentas,79,bauda);//elnas[79]+=floatround(bauda);
					SendClientMessage(playerid,GREEN,"* Bauda sumokëta, jûs iðteisintas!");
					SendClientMessage(mentas,BLUE,"* Bauda sumokëta, þaidejas iðteisintas!");
					SetPlayerWantedLevel(playerid,0);
					playerDB[mentas][jobpts]++;
					format(mzzg,sizeof(mzzg),"[racija] %s: %s sumokëjo baudà ir buvo iðteisintas!",police,vardas);
					SendMessageToTeisesauga(BLUE,mzzg);
					return 1;
				}
			}
			else
			{

				SendClientMessage(playerid,BLUE,"* Bauda nesumokëta, sësite á kalëjima");
				SendClientMessage(mentas,BLUE,"* Bauda nesumokëta, veþkite á kalëjimà");
				RemovePlayerFromVehicle(playerid);
			}
		}



		if(dialogid==222)
		{
			if(response)
			{
				ShowPlayerDialog(playerid,223,DIALOG_STYLE_INPUT,"Narkasas","Kiek reikia? Vnt kaina: 100 €","Pirkti","Iseiti");
				return 1;
			}
			if(!response) return 1;
		}

		if(dialogid==589)
		{
			if(response)
			{
				new kiek = StringToInt(inputtext);

				if(playerDB[playerid][banke] < kiek)
				{
					ShowPlayerDialog(playerid,589, DIALOG_STYLE_INPUT,"Nuimti pinigus","Banke jus tiek neturite\nIveskite suma pinigu, kiek norite paimti.","Paimti","Iseiti");
					return 1;
				}
				if(!IsNumeric(inputtext))
				{
					ShowPlayerDialog(playerid,589, DIALOG_STYLE_INPUT,"Nuimti pinigus","Simbolis turi buti skaicius\nIveskite suma pinigu, kiek norite paimti.","Paimti","Iseiti");
					return 1;
				}
				playerDB[playerid][banke]-=kiek;
				GivePlayerMoneyA(playerid,kiek);
				ApplyAnimation(playerid, "MISC", "pickup_box", 4.000000, 0, 0, 0, 0, -1);
				SendInfoMessage(playerid,"Sekmingai paemete pinigus.~n~ Aciu, kad naudojates musu paslaugomis!");
				return 1;
			}
			if(!response) return 1;
		}
		if(dialogid==1199)
		{
			if(response)
			{
				if(GetPlayerMoneyA(playerid) < DRIVING_LICENSE_PRICE)
				{
					SendInfoMessage(playerid,"~r~Jums neuztenka pinigu.");
					new masinaa = GetPlayerVehicleID(playerid);
					RemovePlayerFromVehicle(playerid);
					SetVehicleToRespawn(masinaa);
				}
				else if(GetPlayerMoneyA(playerid) >= DRIVING_LICENSE_PRICE)
				{
					GivePlayerMoneyA(playerid,-DRIVING_LICENSE_PRICE);
					gPlayerDrivingCheckpoints[playerid]=1;
					new i = gPlayerDrivingCheckpoints[playerid]-1;
					SetPlayerRaceCheckpoint(playerid,0,VAIRAVIMO_CP[i][0],VAIRAVIMO_CP[i][1],VAIRAVIMO_CP[i][2],VAIRAVIMO_CP[i+1][0],VAIRAVIMO_CP[i+1][1],VAIRAVIMO_CP[i+1][2],4.0);
					GameTextForPlayer(playerid," ~y~ Sekite ~r~ Checkpointus~n~~y~ Nesudauzykit Automobilio.",4000,4);
					SetPlayerVirtualWorld(playerid,20002+playerid);
					SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),20002+playerid);
					playerDB[playerid][DrivingTest] = 1;
					TogglePlayerControllable(playerid,true);
				}
			}
			else
			{
				new masinaa = GetPlayerVehicleID(playerid);
				RemovePlayerFromVehicle(playerid);
				SetVehicleToRespawn(masinaa);
			}
		}
		if(dialogid==1299)
		{
			if(response)
			{
				if(GetPlayerMoneyA(playerid) < MOTO_LICENSE_PRICE)
				{
					SendInfoMessage(playerid,"~r~Jums neuztenka pinigu.");
					new masinaa = GetPlayerVehicleID(playerid);
					RemovePlayerFromVehicle(playerid);
					SetVehicleToRespawn(masinaa);
				}
				else if(GetPlayerMoneyA(playerid) >= MOTO_LICENSE_PRICE)
				{
					GivePlayerMoneyA(playerid,-MOTO_LICENSE_PRICE);
					playerDB[playerid][MotoTest] = 1;
					gPlayerDrivingCheckpoints[playerid]=1;
					new i = gPlayerDrivingCheckpoints[playerid]-1;
					SetPlayerRaceCheckpoint(playerid,0,VAIRAVIMO_CP[i][0],VAIRAVIMO_CP[i][1],VAIRAVIMO_CP[i][2],VAIRAVIMO_CP[i+1][0],VAIRAVIMO_CP[i+1][1],VAIRAVIMO_CP[i+1][2],4.0);
					GameTextForPlayer(playerid," ~y~ Sekit ~r~ Checkpointus.~n~~y~ nesudauzykit ~r~ Motociklo.",4000,4);
					SetPlayerVirtualWorld(playerid,20002+playerid);
					SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),20002+playerid);
					TogglePlayerControllable(playerid,true);
				}
			}
			else
			{
				new masinaa = GetPlayerVehicleID(playerid);
				RemovePlayerFromVehicle(playerid);
				SetVehicleToRespawn(masinaa);
			}
		}
		if(dialogid==1399)
		{
			if(response)
			{
				if(GetPlayerMoneyA(playerid) < FLYING_LICENSE_PRICE)
				{
					SendInfoMessage(playerid,"~r~Jums neuztenka pinigu.");
					new masinaa = GetPlayerVehicleID(playerid);
					RemovePlayerFromVehicle(playerid);
					SetVehicleToRespawn(masinaa);
				}
				else if(GetPlayerMoneyA(playerid) >= FLYING_LICENSE_PRICE)
				{
					GivePlayerMoneyA(playerid,-FLYING_LICENSE_PRICE);
					gPlayerFlyingCheckpoints[playerid]=1;
					new i = gPlayerFlyingCheckpoints[playerid]-1;
					SetPlayerRaceCheckpoint(playerid,3,SKRAIDYMO_CP[i][0],SKRAIDYMO_CP[i][1],SKRAIDYMO_CP[i][2],SKRAIDYMO_CP[i+1][0],SKRAIDYMO_CP[i+1][1],SKRAIDYMO_CP[i+1][2],4.0);
					GameTextForPlayer(playerid," ~y~ Sekit ~r~ Checkpointus.~n~~y~ nesudauzykit ~r~ Lektuvo.",4000,4);
					SetPlayerVirtualWorld(playerid,20002+playerid);
					SetVehicleVirtualWorld(GetPlayerVehicleID(playerid),20002+playerid);
					playerDB[playerid][FlyingTest] = 1;
					TogglePlayerControllable(playerid,true);
				}
			}
			else
			{
				new masinaa = GetPlayerVehicleID(playerid);
				RemovePlayerFromVehicle(playerid);
				SetVehicleToRespawn(masinaa);
			}
		}
		/*
		//Vieta Eventu dialogam
		if(dialogid==1399) //Team DM dialogas
		{
			if(response)
			{
				switch(listitem)
				case 0:
				{
					ShowPlayerDialog(playerid,9003,DIALOG_STYLE_INPUT,"Komandu skaicius","Nustatykite komandu skaiciu(Max - 4)","Pasirinkti","Nekeisti");
					return 1;
				}
				case 1:
				{
					ShowPlayerDialog(playerid,9003,DIALOG_STYLE_INPUT,"Komandu skaicius","Pasirinkite zaideju komandoje skaiciu(Max - 6)","Pasirinkti","Nekeisti");
					return 1;
				}
				case 2:
				{
					new i=1,
						KomanduList[128];

					format(KomanduList,128,"\n%i komanda",i);
					for(i;i<=TeamDMVars[KomanduSk];i++)
						format(KomanduList,128,"%s\n%i komanda",KomanduList[sizeof(KomanduList)],i);
					ShowPlayerDialog(playerid,9003,DIALOG_STYLE_LIST,"Komandu sarasas",KomanduList[sizeof(KomanduList)],"Pasirinkti","Nekeisti");

					return 1;
				}
				case 3: //Skinu meniu
				{
					new i=1,
						KomanduList[128];

					format(KomanduList,128,"\n%i komanda",i);
					for(i;i<=TeamDMVars[KomanduSk];i++)
						format(KomanduList,128,"%s\n%i komanda",KomanduList[sizeof(KomanduList)],i);
					ShowPlayerDialog(playerid,9003,DIALOG_STYLE_LIST,"Komandu sarasas",KomanduList[sizeof(KomanduList)],"Pasirinkti","Nekeisti");

					return 1;
				}
				case 4: //Ginklu meniu
				{
					#define MAX_EVENT_GUNS 12
					new GinklaiEventam[MAX_EVENT_GUNS][2];
					new msg[512];
					for(new i=0;i<MAX_EVENT_GUNS;i++)
					{
						if(GinklaiEventam[i][0] != 0) // nepamirsk resetint po evento
						{
							new temp[24];
							GetWeaponName(GinklaiEventam[i][0],temp,sizeof(temp));GetSpeedEx(veh);
							format(msg,sizeof(msg),"%s%i. %s(%i ammo)\n",msg,i+1,temp,GinklaiEventam[i][1]);
						
						}
					}
					format(msg,sizeof(msg),"%s{FF0000}Prideti ginklu",msg);
					//format(EventGinkluMeniu,128,"Ak47 - %i\nM4a1 - %i\nDeagle - %i\nSniper - %i\nRifle - %i\nColt - %i\nChainsaw\nShotgun - %i\nGrande - %i",GinklaiEventam[0][Kiekis],GinklaiEventam[1][Kiekis],
					//GinklaiEventam[2][Kiekis],GinklaiEventam[3][SniperKiekis],GinklaiEventam[4][Kiekis],GinklaiEventam[5][Kiekis],GinklaiEventam[7][Kiekis],GinklaiEventam[8][Kiekis]);
					ShowPlayerDialog(playerid,9003,DIALOG_STYLE_LIST,EventGinkluSarasas,EventGinkluMeniu,"Pasirinkti","Nekeisti");
					return 1;
				}
				case 5:
				{
					ShowPlayerDialog(playerid,546,DIALOG_STYLE_MSGBOX,"Friendly Fire","","Ijungta","Isjungta");
					return 1;
				}
				case 6:
				{
					ShowPlayerDialog(playerid,546,DIALOG_STYLE_MSGBOX,"Komandu naudojimas","","Ijungta","Isjungta");
					return 1;
				}
				case 7:
				{
					//PRADEDAM
				}									
			}
			else
			{
				new masinaa = GetPlayerVehicleID(playerid);
				RemovePlayerFromVehicle(playerid);
				SetVehicleToRespawn(masinaa);
			}
		}
		if(dialogid==1399) //Last Man Standing dialogas
		{
			if(response)
			{
				switch(listitem)
				case 0:
				{
					SetPlayerCheckpoint(playerid,2478.93,-2078.63,13.55,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
				case 1:
				{
					SetPlayerCheckpoint(playerid,-2414.9436,995.9910,45.3016,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
			}
			else
			{
				new masinaa = GetPlayerVehicleID(playerid);
				RemovePlayerFromVehicle(playerid);
				SetVehicleToRespawn(masinaa);
			}
		if(dialogid==1399) //One x One DM dialogas
		{
			if(response)
			{
				switch(listitem)
				case 0:
				{
					SetPlayerCheckpoint(playerid,2478.93,-2078.63,13.55,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
				case 1:
				{
					SetPlayerCheckpoint(playerid,-2414.9436,995.9910,45.3016,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
			}
			else
			{
				new masinaa = GetPlayerVehicleID(playerid);
				RemovePlayerFromVehicle(playerid);
				SetVehicleToRespawn(masinaa);
			}
		if(dialogid==1399) //Race dialogas
		{
			if(response)
			{
				switch(listitem)
				case 0:
				{
					SetPlayerCheckpoint(playerid,2478.93,-2078.63,13.55,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
				case 1:
				{
					SetPlayerCheckpoint(playerid,-2414.9436,995.9910,45.3016,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
			}
			else
			{
				new masinaa = GetPlayerVehicleID(playerid);
				RemovePlayerFromVehicle(playerid);
				SetVehicleToRespawn(masinaa);
			}
		if(dialogid==1399) //Hunger Games dialogas
		{
			if(response)
			{
				switch(listitem)
				case 0:
				{
					SetPlayerCheckpoint(playerid,2478.93,-2078.63,13.55,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
				case 1:
				{
					SetPlayerCheckpoint(playerid,-2414.9436,995.9910,45.3016,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
			}
			else
			{
				new masinaa = GetPlayerVehicleID(playerid);
				RemovePlayerFromVehicle(playerid);
				SetVehicleToRespawn(masinaa);
			}
		if(dialogid==1399) //Stunt dialogas
		{
			if(response)
			{
				switch(listitem)
				case 0:
				{
					SetPlayerCheckpoint(playerid,2478.93,-2078.63,13.55,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
				case 1:
				{
					SetPlayerCheckpoint(playerid,-2414.9436,995.9910,45.3016,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
			}
			else
			{
				new masinaa = GetPlayerVehicleID(playerid);
				RemovePlayerFromVehicle(playerid);
				SetVehicleToRespawn(masinaa);
			}
		if(dialogid==1399) //Find dialogas
		{
			if(response)
			{
				switch(listitem)
				case 0:
				{
					SetPlayerCheckpoint(playerid,2478.93,-2078.63,13.55,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
				case 1:
				{
					SetPlayerCheckpoint(playerid,-2414.9436,995.9910,45.3016,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite backine.");
					return 1;
				}
			}
			else
			{
				new masinaa = GetPlayerVehicleID(playerid);
				RemovePlayerFromVehicle(playerid);
				SetVehicleToRespawn(masinaa);
			}
		}


		*/











		if(dialogid==546) // jai dialog id lygus 9876.
		{
			if(response) // Mygtukas "Registruotis"
			{
				ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");
				return 1;
			}
			if(!response) return 1;
		}

		if(dialogid==547) // jai dialog id lygus 9876.
		{
			if(response) // Mygtukas "Registruotis"
			{
				if(listitem == 0)
				{
					ShowPlayerDialog(playerid,548,DIALOG_STYLE_LIST,"Papildymai:","10€\n30€\n50€\n100€\n500€","Pirkti","Iseiti");
					return 1;
				}
				if(listitem == 1)
				{
					if(GetPlayerMoneyA(playerid) < COST_LAIKRASTIS)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_LAIKRASTIS);
					ActorServe(playerid); BusinessMoney(COST_LAIKRASTIS);
					playerDB[playerid][laikrastis]=true;
					SendInfoMessage(playerid,"Laikrasti gali skaityti parases /laikrastis",150);
					//ApplyAnimation(playerid, "GANGS", "DEALER_DEAL", 4.000000, 0, 0, 0, 0, -1);
					ShowPlayerDialog(playerid,546,DIALOG_STYLE_MSGBOX,"Spaudos Kioskas","Ar noresite kanors pirkti?","Taip","Ne");
					return 1;
				}
				if(listitem == 2)
				{
					if(GetPlayerMoneyA(playerid) < COST_FOTOAPARATAS)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_FOTOAPARATAS);
					ActorServe(playerid); BusinessMoney(COST_FOTOAPARATAS);
					GivePlayerWeaponEx(playerid,43,50);
					//ApplyAnimation(playerid, "GANGS", "DEALER_DEAL", 4.000000, 0, 0, 0, 0, -1);
					ShowPlayerDialog(playerid,546,DIALOG_STYLE_MSGBOX,"Spaudos Kioskas","Ar noresite kanors pirkti?","Taip","Ne");
					return 1;
				}
				if(listitem == 3)
				{
					if(GetPlayerMoneyA(playerid) < COST_GELES)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_GELES);
					ActorServe(playerid); BusinessMoney(COST_GELES);
					GivePlayerWeaponEx(playerid,14,3);
					//ApplyAnimation(playerid, "GANGS", "DEALER_DEAL", 4.000000, 0, 0, 0, 0, -1);
					ShowPlayerDialog(playerid,546,DIALOG_STYLE_MSGBOX,"Spaudos Kioskas","Ar noresite kanors pirkti?","Taip","Ne");
					return 1;
				}
				if(listitem == 4)
				{
					if(GetPlayerMoneyA(playerid) < COST_SPRITE)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_SPRITE);
					ActorServe(playerid); BusinessMoney(COST_SPRITE);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
					SendInfoMessage(playerid,"Nusipirkote sprite.");
					//ApplyAnimation(playerid, "GANGS", "DEALER_DEAL", 4.000000, 0, 0, 0, 0, -1);
					ShowPlayerDialog(playerid,546,DIALOG_STYLE_MSGBOX,"Spaudos Kioskas","Ar noresite kanors pirkti?","Taip","Ne");
					return 1;
				}
				if(listitem == 5)
				{
					if(GetPlayerMoneyA(playerid) < COST_ALUS)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_ALUS);
					ActorServe(playerid); BusinessMoney(COST_ALUS);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
					SendInfoMessage(playerid,"Nusipirkote alaus.");
					//ApplyAnimation(playerid, "GANGS", "DEALER_DEAL", 4.000000, 0, 0, 0, 0, -1);
					ShowPlayerDialog(playerid,546,DIALOG_STYLE_MSGBOX,"Spaudos Kioskas","Ar noresite kanors pirkti?","Taip","Ne");
					return 1;
				}
				if(listitem == 6)
				{
					if(GetPlayerMoneyA(playerid) < COST_VODKA)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_VODKA);
					ActorServe(playerid); BusinessMoney(COST_VODKA);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
					SendInfoMessage(playerid,"Nusipirkote degtines.");
					//ApplyAnimation(playerid, "GANGS", "DEALER_DEAL", 4.000000, 0, 0, 0, 0, -1);
					ShowPlayerDialog(playerid,546,DIALOG_STYLE_MSGBOX,"Spaudos Kioskas","Ar noresite kanors pirkti?","Taip","Ne");
					return 1;
				}
				if(listitem == 7)
				{
					if(GetPlayerMoneyA(playerid) < COST_LAIKRODIS)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_LAIKRODIS);
					ActorServe(playerid); BusinessMoney(COST_LAIKRODIS);
					playerDB[playerid][laikrodis]=true;
					SendInfoMessage(playerid,"Nusipirkote laikrodi.");
					TextDrawShowForPlayer(playerid, TextdrawTime);//Time
					//ApplyAnimation(playerid, "GANGS", "DEALER_DEAL", 4.000000, 0, 0, 0, 0, -1);
					ShowPlayerDialog(playerid,546,DIALOG_STYLE_MSGBOX,"Spaudos Kioskas","Ar noresite kanors pirkti?","Taip","Ne");
					return 1;
				}
				if(listitem == 8)
				{
					if(GetPlayerMoneyA(playerid) < COST_IMTUVAS)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_IMTUVAS);
					ActorServe(playerid); BusinessMoney(COST_IMTUVAS);
					playerDB[playerid][imtuvas]=true;
					//if(!Audio_IsClientConnected(playerid)) SendClientMessage(playerid,RED,"* Demesio! Neturite audio plugin'o. Tik turedami ji, galesite klausytis lietuviskos radijos. Prasome atsisiusti is www.LSGyvenimas.lt Pagalbos skilties.");
					SendInfoMessage(playerid,"Nusipirkote radijo imtuva.~n~ Naudokite /imtuvas noredami juo naudotis.",150);
					//ApplyAnimation(playerid, "GANGS", "DEALER_DEAL", 4.000000, 0, 0, 0, 0, -1);
					ShowPlayerDialog(playerid,546,DIALOG_STYLE_MSGBOX,"Spaudos Kioskas","Ar noresite kanors pirkti?","Taip","Ne");
					return 1;
				}
				if(listitem==9)
				{	
					if(GetPlayerMoneyA(playerid) < COST_CIGARETES)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_CIGARETES);
					ActorServe(playerid); BusinessMoney(COST_CIGARETES);
					playerDB[playerid][cigaretes]=20;
					//if(!Audio_IsClientConnected(playerid)) SendClientMessage(playerid,RED,"* Demesio! Neturite audio plugin'o. Tik turedami ji, galesite klausytis lietuviskos radijos. Prasome atsisiusti is www.LSGyvenimas.lt Pagalbos skilties.");
					SendInfoMessage(playerid,"Nusipirkote cigareciu.~n~Rasykite /rukyti, kad parukytumet.",150);
					//ApplyAnimation(playerid, "GANGS", "DEALER_DEAL", 4.000000, 0, 0, 0, 0, -1);
					ShowPlayerDialog(playerid,546,DIALOG_STYLE_MSGBOX,"Spaudos Kioskas","Ar noresite kanors pirkti?","Taip","Ne");
					
					return 1;
				}
			}

		}

		if(dialogid==548)
		{
			if(response)
			{
				if(playerDB[playerid][mobsas] >= 10000)
					ProcessAchievement(playerid, 112);
				if(listitem == 0)
				{
					if(GetPlayerMoneyA(playerid) < 10)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						ShowPlayerDialog(playerid,548,DIALOG_STYLE_LIST,"Papildymai:","10€\n30€\n50€\n100€\n500€","Pirkti","Iseiti");
						return 1;
					}
					GivePlayerMoneyA(playerid, -10);
					ActorServe(playerid); BusinessMoney(10);
					//BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning]+=7;
					SendInfoMessage(playerid,"Saskaita papildyta!");
					playerDB[playerid][mobsas]+=10;

					ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");
				}
				if(listitem == 1)
				{
					if(GetPlayerMoneyA(playerid) < 30)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						ShowPlayerDialog(playerid,548,DIALOG_STYLE_LIST,"Papildymai:","10€\n30€\n50€\n100€\n500€","Pirkti","Iseiti");
						return 1;
					}
					GivePlayerMoneyA(playerid, -30);
					//BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning]+=21;
					ActorServe(playerid); BusinessMoney(30);
					SendInfoMessage(playerid,"Saskaita papildyta!");
					playerDB[playerid][mobsas]+=30;
					ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");

				}
				if(listitem == 2)
				{
					if(GetPlayerMoneyA(playerid) < 50)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						ShowPlayerDialog(playerid,548,DIALOG_STYLE_LIST,"Papildymai:","10€\n30€\n50€\n100€\n500€","Pirkti","Iseiti");
						return 1;
					}
					GivePlayerMoneyA(playerid, -50);
					//BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning]+=35;
					ActorServe(playerid); BusinessMoney(50);
					SendInfoMessage(playerid,"Saskaita papildyta!");
					playerDB[playerid][mobsas]+=50;
					ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");

				}
				if(listitem == 3)
				{
					if(GetPlayerMoneyA(playerid) < 100)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						ShowPlayerDialog(playerid,548,DIALOG_STYLE_LIST,"Papildymai:","10€\n30€\n50€\n100€\n500€","Pirkti","Iseiti");
						return 1;
					}
					GivePlayerMoneyA(playerid, -100);
					//BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning]+=70;
					ActorServe(playerid); BusinessMoney(100);
					SendInfoMessage(playerid,"Saskaita papildyta!");
					playerDB[playerid][mobsas]+=100;
					ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");

				}
				if(listitem == 4)
				{
					if(GetPlayerMoneyA(playerid) < 500)
					{
						SendInfoMessage(playerid,"~r~Truksta pinigu.");
						ShowPlayerDialog(playerid,548,DIALOG_STYLE_LIST,"Papildymai:","10€\n30€\n50€\n100€\n500€","Pirkti","Iseiti");
						return 1;
					}
					GivePlayerMoneyA(playerid, -500);
					//BusinessInfo[GetPlayerVirtualWorld(playerid)-MAX_HOUSES*2][bEarning]+=400;
					ActorServe(playerid); BusinessMoney(500);
					SendInfoMessage(playerid,"Saskaita papildyta!");
					playerDB[playerid][mobsas]+=500;
					ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");
				}
			}
			if(!response)
			{
				ShowPlayerDialog(playerid,547,DIALOG_STYLE_TABLIST,"Prekes:",KIOSKO_TEXT,"Pirkti","Iseiti");
			}
		}

		if(dialogid==9876) // jai dialog id lygus 9876.
		{
			if(response) // Mygtukas "Registruotis"
			{
				new userquery[256];
				if(strlen(inputtext) > 15)
				{
					new girismsg[128];
					format(girismsg,128,"{FFFFFF}Labas, {CC0033}%s{FFFFFF} !\n\nIvesk slaptazodi, kuri naudosi veliau.\n{CC0033}Slaptazodis per ilgas.",ReturnName(playerid));
					ShowPlayerDialog(playerid,9876,DIALOG_STYLE_PASSWORD,"Registracija",girismsg,"Regintis","Iseiti"); 
					return SendInfoMessage(playerid,"~r~SLAPTAZODIS PER ILGAS!"); 
				}
				else if(strlen(inputtext) <= 3)
				{
					new girismsg[128];
					format(girismsg,128,"{FFFFFF}Labas, {CC0033}%s{FFFFFF} !\n\nIvesk slaptazodi, kuri naudosi veliau.\n{CC0033}Slaptazodis per trumpas.",ReturnName(playerid));
					ShowPlayerDialog(playerid,9876,DIALOG_STYLE_PASSWORD,"Registracija",girismsg,"Regintis","Iseiti"); 
					return SendInfoMessage(playerid,"~r~SLAPTAZODIS PER TRUMPAS!"); 
				}
				format(userquery,sizeof(userquery),"INSERT INTO `Account` (`Name`,`Slaptazodis`) VALUES ('%s','%s')",ReturnName(playerid),sha256_hash(inputtext));
				mysql_query(userquery);
				OnPlayerRegister(playerid);

				playerDB[playerid][vip]=false;
				SendInfoMessage(playerid,"Registracija sekminga, prie serverio jus prijungtas automatiskai");
				ShowPlayerDialog(playerid,9888,DIALOG_STYLE_MSGBOX,"Lytis","Prasome pasirinkti savo lyti.","Vyras","Moteris");
			}
			else if(!response) // Jai zaidejas paspaude mygtuka Iseiti
			{
				SendClientMessage(playerid,-1," * Viso gero!");
				Kick(playerid); // Ismetam zaideja is serverio
			}
			return 1;
		}
		if(dialogid==9888)
		{
			if(response){
			playerDB[playerid][lytis]=1; }
			if(!response){ playerDB[playerid][lytis]=2; }
			CheckEmailStatus(playerid);
		}
		if(dialogid==9887)
		{
			if(response){
			playerDB[playerid][lytis]=1; }
			if(!response){ playerDB[playerid][lytis]=2; }
		}
		if(dialogid==9889)
		{
			if(playerDB[playerid][authstate]==0)
			{
				if(response)
				{
					if(!IsValidEmail(inputtext)) return ShowPlayerDialog(playerid,9889,DIALOG_STYLE_INPUT,"Iveskite el.pasto adresa","Netinkamas el.pasto adresas!\nIveskite el.pasto adresa, kuri norite susieti su siuo akauntu.\nPamirsus slaptazodi, naujas bus atsiustas siuo adresu.","Gerai","Atsaukti");
					mysql_real_escape_string(inputtext,inputtext,_,256);
					new query[350];
					format(query,sizeof(query),"SELECT * From Pastas Where REPLACE(Email,'.','')=REPLACE('%s','.','')",inputtext);
					mysql_function_query(SQL, query, true, "SQL_IsEmailUsed", "is", playerid,inputtext);
				}
				else Kick(playerid);
				return 1;
			}
			else
			{
				if(!IsValidEmail(inputtext)) return SendClientMessage(playerid,WHITE," * Netinkamas el.paðto adresas.");

				new query[350];
				format(query,sizeof(query),"SELECT Email From Pastas Where Vardas='%s'",ReturnName(playerid));
				mysql_function_query(SQL, query, true, "SQL_EmailNotification", "is", playerid,inputtext);

			}
			return 1;
		}
		if(dialogid==1996)
		{
			if(response)
			{
				BitFlag_Off(PConfig[playerid],PCFG_RAIDES);
			}
			else
			{
				BitFlag_On(PConfig[playerid],PCFG_RAIDES);
			}
			CheckEmailStatus(playerid,GetPVarInt(playerid,"loginvar"));
		}
		if(dialogid==1998)
		{
			if(!response)
				Kick(playerid);
			else
			{
				new query[350];
				mysql_real_escape_string(inputtext,inputtext,_,256);
				format(query,sizeof(query),"Select Confirmation From Pastas Where Vardas='%s'",ReturnName(playerid));
				mysql_function_query(SQL, query, true, "SQL_Confirmationas", "is", playerid,inputtext);
			}
		}
		if(dialogid==1997)
		{
			if(!response) Kick(playerid);
			else
			{
				if(listitem==0)
				{
					ShowPlayerDialog(playerid,1998,DIALOG_STYLE_INPUT,"Patvirtinimo kodas","I jusu el.pasto adresa issiunteme patvirtinimo koda. Turetumete ji gauti 10 min. begyje, taciau dazniausiai gausite ji is karto.\nPasitikrinkite ir SPAM kataloga.\nIveskite koda cia:","Gerai","Atsaukti");
				}
				else if(listitem == 1)
				{
					new query[128];
					format(query,sizeof(query),"SELECT Email,Confirmation FROM Pastas Where Vardas='%s'",ReturnName(playerid));
					mysql_function_query(SQL, query, true, "SQL_ResendConfirmation", "i", playerid);
				}
				else if(listitem == 2)
				{
					new query[128];
					format(query,sizeof(query),"DELETE FROM Pastas Where Vardas='%s'",ReturnName(playerid));
					mysql_query(query);
					ShowPlayerDialog(playerid,9889,DIALOG_STYLE_INPUT,"Iveskite el.pasto adresa","Iveskite el.pasto adresa, kuri norite susieti su siuo akauntu.\nPamirsus slaptazodi, naujas bus atsiustas siuo adresu.","Gerai","Atsaukti");
					return 1;
				}
			}
		}
		if(dialogid==9001) // jai dialog id lygus 9876.
		{
			if(response) // Mygtukas "Imti"
			{
				if(!IsNumeric(inputtext)){SendInfoMessage(playerid,"~b~Prasome teisingai ivesti suma."); return 1;}
				if(Server[atveztan] < strval(inputtext)) return SendInfoMessage(playerid,"~b~Sakyta buvo, siuo metu tiek neturim!!");
				if(strval(inputtext) > 10) return SendInfoMessage(playerid,"~b~Nepatempsi tiek ");
				//if(playerDB[playerid][amfetaminas]+strval(inputtext) > 10) return SendInfoMessage(playerid,"~b~Nepatempsi tiek ");
				new kaina = strval(inputtext)*COST_AMFA;
				if(GetPlayerMoneyA(playerid) < kaina) return SendInfoMessage(playerid,"Tu gal pirma babkiu uzsikalk? 1 pak. kainuoja 500EUR!");
				new file[256];
				format(file,sizeof(file),"SELECT SUM(`Variable`) from `Logs` WHERE Zaidejas='%s' AND Veiksmas='Paeme Amfetamina' AND Data > SUBDATE(NOW(), 1)",ReturnName(playerid));
				mysql_function_query(SQL, file, true, "SQL_LimitAmfa", "isi", playerid,inputtext,kaina);
			}
			return 1;
		}
		if(dialogid==9002) // jai dialog id lygus 9876.
		{
			new girismsg[128];
			if(response) // Mygtukas "Rinktis"
			{
				if(listitem == 0) // dgl
				{
				format(girismsg,128,"Siuo metu turime %i apkabas.",Server[adgl]);
				ShowPlayerDialog(playerid,9003,DIALOG_STYLE_INPUT,"Deagle",girismsg,"Imti","Iseiti");
				}
				if(listitem == 1) // mp5
				{
				format(girismsg,128,"Siuo metu turime %i apkabas.",Server[amp]);
				ShowPlayerDialog(playerid,9004,DIALOG_STYLE_INPUT,"Mp5",girismsg,"Imti","Iseiti");
				}
				if(listitem == 2) // ak
				{
				format(girismsg,128,"Siuo metu turime %i apkabas.",Server[aak]);
				ShowPlayerDialog(playerid,9005,DIALOG_STYLE_INPUT,"AK45",girismsg,"Imti","Iseiti");
				}
				if(listitem==3)
				{
					format(girismsg,128,"Siuo metu turime %i apkabas.",Server[aawp]);
					ShowPlayerDialog(playerid,9006,DIALOG_STYLE_INPUT,"AWP",girismsg,"Imti","Iseiti");
				}
				if(listitem == 4) // ataskaita
				{
					Ataskaita(playerid, "Paeme Deagle","Paeme MP5","Paeme AK-47","Paeme AWP","Paeme Amfetamina");
				}
				if(listitem == 5)
				{
					Ataskaita(playerid, "Iskrove nark","Iskrove dgl mp ak awp");
				}
			}
			return 1;
		}
		if(dialogid==9003) // jai dialog id lygus 9876.
		{
			if(response) // Mygtukas "Imti"
			{
				if(!IsNumeric(inputtext) || !strval(inputtext)){SendInfoMessage(playerid,"~b~Prasome teisingai ivesti suma."); return 1;}
				if(Server[adgl]< strval(inputtext)) return SendInfoMessage(playerid,"~b~Sakyta buvo, siuo metu tiek neturim!!");
				if(strval(inputtext) > 200) return SendInfoMessage(playerid,"~b~Nepatempsi tiek ");
				new kaina = strval(inputtext)*COST_DEAGLE;
				if(GetPlayerMoneyA(playerid) < kaina) return SendInfoMessage(playerid,"~b~Tu gal pirma babkiu uzsikalk?");
				new file[256];
				format(file,sizeof(file),"SELECT SUM(`Variable`) from `Logs` WHERE Zaidejas='%s' AND Veiksmas='Paeme Deagle' AND Data > SUBDATE(NOW(), 1)",ReturnName(playerid));
				mysql_function_query(SQL, file, true, "SQL_LimitDeagle", "isi", playerid,inputtext,kaina);
				
			}
			else if(!response) // Jai zaidejas paspaude mygtuka Iseiti
			{
				ShowPlayerDialog(playerid, 9002, DIALOG_STYLE_LIST, "Ginklai", "Desert eagle\nMp5\nAk47\nAWP", "Rinktis", "Iseiti");
			}
			return 1;
		}
		if(dialogid==9004) // jai dialog id lygus 9876.
		{
			if(response) // Mygtukas "Imti"
			{
				if(!IsNumeric(inputtext) || !strval(inputtext)){SendInfoMessage(playerid,"~b~Prasome teisingai ivesti suma."); return 1;}
				if(Server[amp]< strval(inputtext)) return SendInfoMessage(playerid,"~b~Sakyta buvo, siuo metu tiek neturim!!");
				if(strval(inputtext) > 200) return SendInfoMessage(playerid,"~b~Nepatempsi tiek ");
				new kaina = strval(inputtext)*COST_MP5;
				if(GetPlayerMoneyA(playerid) < kaina) return SendInfoMessage(playerid,"~b~Tu gal pirma babkiu uzsikalk?");
				new file[256];
				format(file,sizeof(file),"SELECT SUM(`Variable`) from `Logs` WHERE Zaidejas='%s' AND Veiksmas='Paeme MP5' AND Data > SUBDATE(NOW(), 1)",ReturnName(playerid));
				mysql_function_query(SQL, file, true, "SQL_LimitMP", "isi", playerid,inputtext,kaina);
			}
			else if(!response) // Jai zaidejas paspaude mygtuka Iseiti
			{
				ShowPlayerDialog(playerid, 9002, DIALOG_STYLE_LIST, "Ginklai", "Desert eagle\nMp5\nAk47\nAWP", "Rinktis", "Iseiti");
			}
			return 1;
		}
		if(dialogid==9005) // jai dialog id lygus 9876.
		{
			if(response) // Mygtukas "Imti"
			{
				if(!IsNumeric(inputtext) || !strval(inputtext)){SendInfoMessage(playerid,"~b~Prasome teisingai ivesti suma."); return 1;}
				if(Server[aak]< strval(inputtext)) return SendInfoMessage(playerid,"~b~Sakyta buvo, siuo metu tiek neturim!!");
				if(strval(inputtext) > 200) return SendInfoMessage(playerid,"~b~Nepatempsi tiek ");
				new kaina = strval(inputtext)*COST_AK47;
				if(GetPlayerMoneyA(playerid) < kaina) return SendInfoMessage(playerid,"~b~Tu gal pirma babkiu uzsikalk?");
				new file[256];
				format(file,sizeof(file),"SELECT SUM(`Variable`) from `Logs` WHERE Zaidejas='%s' AND Veiksmas='Paeme AK-47' AND Data > SUBDATE(NOW(), 1)",ReturnName(playerid));
				mysql_function_query(SQL, file, true, "SQL_LimitAK", "isi", playerid,inputtext,kaina);

			}
			else if(!response) // Jai zaidejas paspaude mygtuka Iseiti
			{
				ShowPlayerDialog(playerid, 9002, DIALOG_STYLE_LIST, "Ginklai", "Desert eagle\nMp5\nAk47\nAWP", "Rinktis", "Iseiti");
			}
			return 1;
		}
		if(dialogid==9006) // jai dialog id lygus 9876.
		{
			if(response) // Mygtukas "Imti"
			{
				if(!IsNumeric(inputtext) || !strval(inputtext)){SendInfoMessage(playerid,"~b~Prasome teisingai ivesti suma."); return 1;}
				if(Server[aawp]< strval(inputtext)) return SendInfoMessage(playerid,"~b~Sakyta buvo, siuo metu tiek neturim!!");
				if(strval(inputtext) > 200) return SendInfoMessage(playerid,"~b~Nepatempsi tiek ");
				new kaina = strval(inputtext)*COST_AK47;
				if(GetPlayerMoneyA(playerid) < kaina) return SendInfoMessage(playerid,"~b~Tu gal pirma babkiu uzsikalk?");
				new file[256];
				format(file,sizeof(file),"SELECT SUM(`Variable`) from `Logs` WHERE Zaidejas='%s' AND Veiksmas='Paeme AWP' AND Data > SUBDATE(NOW(), 1)",ReturnName(playerid));
				mysql_function_query(SQL, file, true, "SQL_LimitSniper", "isi", playerid,inputtext,kaina);

			}
			else if(!response) // Jai zaidejas paspaude mygtuka Iseiti
			{
				ShowPlayerDialog(playerid, 9002, DIALOG_STYLE_LIST, "Ginklai", "Desert eagle\nMp5\nAk47\nAWP", "Rinktis", "Iseiti");
			}
			return 1;
		}

		if(dialogid==9008) // jai dialog id lygus 9876.
		{
			if(response) // Mygtukas "Rinktis"
			{
				if(GetPlayerVirtualWorld(playerid) != 0) return AC_Warn(playerid,"Pasikrove kitam pasaulyje");
				new ginklas[24];
				new kaina;
				if(listitem == 0) // dgl
				{
					if(Server[adgl] > LIMIT_VEZIMO) 
					{
						SendInfoMessage(playerid,"~r~Bazeje pasiektas 10,000 Deagle apkabu limitas.");
						SDDI(playerid);
						return 1;
					}
					kaina=COST_VDGL;
					ginklas="Deagle";
					//ShowPlayerDialog(playerid,9009,DIALOG_STYLE_INPUT,"Deagle","Kiek reikes apkabu?","Krauti","Iseiti");
				}
				if(listitem == 1) // mp5
				{
					if(Server[amp] > LIMIT_VEZIMO) 
					{
						SendInfoMessage(playerid,"~r~Bazeje pasiektas 10,000 MP5 apkabu limitas.");
						SDDI(playerid);
						return 1;
					}
					kaina=COST_VMP5;
					ginklas="Mp5";
					//ShowPlayerDialog(playerid,9010,DIALOG_STYLE_INPUT,"Mp5","Kiek reikes apkabu?","Krauti","Iseiti");
				}
				if(listitem == 2) // ak
				{
					if(Server[aak] > LIMIT_VEZIMO) 
					{
						SendInfoMessage(playerid,"~r~Bazeje pasiektas 10,000 AK47 apkabu limitas.");
						SDDI(playerid);
						return 1;
					}
					kaina=COST_VAK47;
					ginklas="AK47";
					//ShowPlayerDialog(playerid,9011,DIALOG_STYLE_INPUT,"AK45","Kiek reikes apkabu?","Krauti","Iseiti");
				}
				if(listitem== 3)
				{
					if(Server[aawp] > LIMIT_VEZIMO) 
					{
						SendInfoMessage(playerid,"~r~Bazeje pasiektas 10,000 AWP apkabu limitas.");
						SDDI(playerid);
						return 1;
					}
					kaina=COST_VAWP;
					ginklas="AWP";
					//ShowPlayerDialog(playerid,9012,DIALOG_STYLE_INPUT,"AWP","Kiek reikes apkabu?","Krauti","Iseiti");
				}
				new modelis = GetVehicleModel(playerDB[playerid][masina]);
				new kiekis;
				switch(modelis)
				{
					case 609: kiekis=22; // boxvile
					case 600: kiekis=11; // picador
					case 422: kiekis=14; // bobcat
				}
				new msg[128];
				format(msg,sizeof(msg),"Kiek reikes apkabu?\nI automobili galite krauti iki %i apkabu.\nVienos apkabos kaina: %i€.",kiekis,kaina);
				ShowPlayerDialog(playerid,(9009+listitem),DIALOG_STYLE_INPUT,ginklas,msg,"Krauti","Iseiti");
			}
			else if(!response) // Jai zaidejas paspaude mygtuka Iseiti
			{
				//SendClientMessage(playerid,COLOR,"Eik jau net pinigu neturi ");
				/*if(IsPlayerInRangeOfPointEx(10.0,playerid,PickupIDs[pickups[0][gunkraut]][0],PickupIDs[pickups[0][gunkraut]][1],PickupIDs[pickups[0][gunkraut]][2]))
					ShowPlayerDialog(playerid, 9008, DIALOG_STYLE_LIST, "Ka krausim?", "Desert eagle\nMp5", "Rinktis", "Iseiti");
				else if(IsPlayerInRangeOfPointEx(10.0,playerid,PickupIDs[pickups[0][gunkraut2]][0],PickupIDs[pickups[0][gunkraut2]][1],PickupIDs[pickups[0][gunkraut2]][2]))
					ShowPlayerDialog(playerid, 9008, DIALOG_STYLE_LIST, "Ka krausim?", "Desert eagle\nMp5\nAk-47", "Rinktis", "Iseiti");
				else if(IsPlayerInRangeOfPointEx(10.0,playerid,PickupIDs[pickups[0][gunkraut3]][0],PickupIDs[pickups[0][gunkraut3]][1],PickupIDs[pickups[0][gunkraut3]][2]))
					ShowPlayerDialog(playerid, 9008, DIALOG_STYLE_LIST, "Ka krausim?", "Desert eagle\nMp5\nAk-47", "Rinktis", "Iseiti"); */
			}
			return 1;
		}
		if(dialogid==9009) // jai dialog id lygus 9876.
		{
			if(response) // Mygtukas "Krauti"
			{
				if(!IsNearPakrovimas(playerid))
					return SendInfoMessage(playerid, "Tu per toli nuo pakrovimo!");
				new Float:cpo[3];
				GetVehiclePos(playerDB[playerid][masina],cpo[0],cpo[1],cpo[2]);

				if(!IsPlayerInRangeOfPointEx(10,playerid,cpo[0],cpo[1],cpo[2]))
				{
					SendInfoMessage(playerid,"~r~Kaip as tau krausiu, kai taip toli pastatei?");
					return 1;
				}
				if(playerDB[playerid][masina] != PlayerCar[playerid])
					return SendInfoMessage(playerid,"Tai ne tavo automobilis!");
				SDDI(playerid);
				if(!IsNumeric(inputtext)){SendInfoMessage(playerid,"~b~Prasome teisingai ivesti suma."); return 1;}

				//if(strval(inputtext) > 10) return SendInfoMessage(playerid,"~b~Nebuk godus.");
				new modelis = GetVehicleModel(playerDB[playerid][masina]);

				if(modelis == 609 && krovinys[playerDB[playerid][masina]]+strval(inputtext) > 22) return SendInfoMessage(playerid,"~r~Jusu masina jau ir taip pilna.");
				if(modelis == 600 && krovinys[playerDB[playerid][masina]]+strval(inputtext) > 11) return SendInfoMessage(playerid,"~r~Jusu masina jau ir taip pilna.");
				if(modelis == 422 && krovinys[playerDB[playerid][masina]]+strval(inputtext) > 14) return SendInfoMessage(playerid,"~r~Jusu masina jau ir taip pilna.");
				if(modelis != 609 && modelis != 600 && modelis != 422)
					return SendInfoMessage(playerid,"Tai ne darbinis automobilis!");
				new kaina = strval(inputtext)*COST_VDGL;

				if(GetPlayerMoneyA(playerid) < kaina) return SendInfoMessage(playerid,"~b~Tu gal pirma babkiu uzsikalk?");
				SendInfoMessage(playerid,"Sekmingai pakrovei ginklus!");
				ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 4.000000, 0, 0, 0, 0, -1);
				GivePlayerMoneyA(playerid,-kaina);
				vdgl[playerDB[playerid][masina]]+=strval(inputtext);
				krovinys[playerDB[playerid][masina]]+=strval(inputtext);
				return 1;
			}
			else if(!response) // Jai zaidejas paspaude mygtuka Iseiti
			{
				SDDI(playerid);
			}
			return 1;
		}
		if(dialogid==9010) // jai dialog id lygus 9876.
		{
			if(response) // Mygtukas "Krauti"
			{
				if(!IsNearPakrovimas(playerid))
					return SendInfoMessage(playerid, "Tu per toli nuo pakrovimo!");
				new Float:cpo[3];
				GetVehiclePos(playerDB[playerid][masina],cpo[0],cpo[1],cpo[2]);

				if(!IsPlayerInRangeOfPointEx(10,playerid,cpo[0],cpo[1],cpo[2]))
				{
					SendInfoMessage(playerid,"~r~Kaip as tau krausiu, kai taip toli pastatei?");
					return 1;
				}
				if(playerDB[playerid][masina] != PlayerCar[playerid])
					return SendInfoMessage(playerid,"Tai ne tavo automobilis!");
				SDDI(playerid);
				if(!IsNumeric(inputtext)){SendInfoMessage(playerid,"~b~Prasome teisingai ivesti suma."); return 1;}
				//if(strval(inputtext) > 10) return SendInfoMessage(playerid,"~b~Nebuk godus.");
				new modelis = GetVehicleModel(playerDB[playerid][masina]);

				if(modelis == 609 && krovinys[playerDB[playerid][masina]]+strval(inputtext) > 22) return SendInfoMessage(playerid,"~r~Jusu masina jau ir taip pilna.");
				if(modelis == 600 && krovinys[playerDB[playerid][masina]]+strval(inputtext) > 11) return SendInfoMessage(playerid,"~r~Jusu masina jau ir taip pilna.");
				if(modelis == 422 && krovinys[playerDB[playerid][masina]]+strval(inputtext) > 14) return SendInfoMessage(playerid,"~r~Jusu masina jau ir taip pilna.");
				if(modelis != 609 && modelis != 600 && modelis != 422)
					return SendInfoMessage(playerid,"Tai ne darbinis automobilis!");
				new kaina = strval(inputtext)*COST_VMP5;
				if(GetPlayerMoneyA(playerid) < kaina) return SendInfoMessage(playerid,"~b~Tu gal pirma babkiu uzsikalk?");
				SendInfoMessage(playerid,"Sekmingai pakrovei ginklus!");
				ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 4.000000, 0, 0, 0, 0, -1);
				GivePlayerMoneyA(playerid,-kaina);
				vmp[playerDB[playerid][masina]]+=strval(inputtext);
				krovinys[playerDB[playerid][masina]]+=strval(inputtext);
				return 1;
			}
			else if(!response) // Jai zaidejas paspaude mygtuka Iseiti
			{
				SDDI(playerid);
			}
			return 1;
		}
		if(dialogid==9011) // jai dialog id lygus 9876.
		{
			if(response) // Mygtukas "Krauti"
			{
				if(!IsNearPakrovimas(playerid))
					return SendInfoMessage(playerid, "Tu per toli nuo pakrovimo!");
				new Float:cpo[3];
				GetVehiclePos(playerDB[playerid][masina],cpo[0],cpo[1],cpo[2]);

				if(!IsPlayerInRangeOfPointEx(10,playerid,cpo[0],cpo[1],cpo[2]))
				{
					SendInfoMessage(playerid,"~r~Kaip as tau krausiu, kai taip toli pastatei?");
					return 1;
				}
				if(playerDB[playerid][masina] != PlayerCar[playerid])
					return SendInfoMessage(playerid,"Tai ne tavo automobilis!");
				SDDI(playerid);
				if(!IsNumeric(inputtext)){SendInfoMessage(playerid,"~b~Prasome teisingai ivesti suma."); return 1;}
				//if(strval(inputtext) > 10) return SendInfoMessage(playerid,"~b~Nebuk godus.");
				new modelis = GetVehicleModel(playerDB[playerid][masina]);

				if(modelis == 609 && krovinys[playerDB[playerid][masina]]+strval(inputtext) > 22) return SendInfoMessage(playerid,"~r~Jusu masina jau ir taip pilna. ");
				if(modelis == 600 && krovinys[playerDB[playerid][masina]]+strval(inputtext) > 11) return SendInfoMessage(playerid,"~r~Jusu masina jau ir taip pilna.");
				if(modelis == 422 && krovinys[playerDB[playerid][masina]]+strval(inputtext) > 14) return SendInfoMessage(playerid,"~r~Jusu masina jau ir taip pilna.");
				if(modelis != 609 && modelis != 600 && modelis != 422)
					return SendInfoMessage(playerid,"Tai ne darbinis automobilis!");
				new kaina = strval(inputtext)*COST_VAK47;
				if(GetPlayerMoneyA(playerid) < kaina) return SendInfoMessage(playerid,"~b~Tu gal pirma babkiu uzsikalk?");
				SendInfoMessage(playerid,"Sekmingai pakrovei ginklus!");
				ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 4.000000, 0, 0, 0, 0, -1);
				GivePlayerMoneyA(playerid,-kaina);
				vak[playerDB[playerid][masina]]+=strval(inputtext);
				krovinys[playerDB[playerid][masina]]+=strval(inputtext);
				return 1;
			}
			else if(!response) // Jai zaidejas paspaude mygtuka Iseiti
			{
				SDDI(playerid);
			}
			return 1;
		}
		if(dialogid==9012)
		{
			if(response) // Mygtukas "Krauti"
			{
				if(!IsNearPakrovimas(playerid))
					return SendInfoMessage(playerid, "Tu per toli nuo pakrovimo!");
				new Float:cpo[3];
				GetVehiclePos(playerDB[playerid][masina],cpo[0],cpo[1],cpo[2]);

				if(!IsPlayerInRangeOfPointEx(10,playerid,cpo[0],cpo[1],cpo[2]))
				{
					SendInfoMessage(playerid,"~r~Kaip as tau krausiu, kai taip toli pastatei?");
					return 1;
				}
				if(playerDB[playerid][masina] != PlayerCar[playerid])
					return SendInfoMessage(playerid,"Tai ne tavo automobilis!");
				SDDI(playerid);
				if(!IsNumeric(inputtext)){SendInfoMessage(playerid,"~b~Prasome teisingai ivesti suma."); return 1;}
				//if(strval(inputtext) > 10) return SendInfoMessage(playerid,"~b~Nebuk godus.");
				new modelis = GetVehicleModel(playerDB[playerid][masina]);

				if(modelis == 609 && krovinys[playerDB[playerid][masina]]+strval(inputtext) > 22) return SendInfoMessage(playerid,"~r~Jusu masina jau ir taip pilna. ");
				if(modelis == 600 && krovinys[playerDB[playerid][masina]]+strval(inputtext) > 11) return SendInfoMessage(playerid,"~r~Jusu masina jau ir taip pilna.");
				if(modelis == 422 && krovinys[playerDB[playerid][masina]]+strval(inputtext) > 14) return SendInfoMessage(playerid,"~r~Jusu masina jau ir taip pilna.");
				if(modelis != 609 && modelis != 600 && modelis != 422)
					return SendInfoMessage(playerid,"Tai ne darbinis automobilis!");
				new kaina = strval(inputtext)*COST_VAWP;
				if(GetPlayerMoneyA(playerid) < kaina) return SendInfoMessage(playerid,"~b~Tu gal pirma babkiu uzsikalk?");
				SendInfoMessage(playerid,"Sekmingai pakrovei ginklus!");
				ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 4.000000, 0, 0, 0, 0, -1);
				GivePlayerMoneyA(playerid,-kaina);
				vawp[playerDB[playerid][masina]]+=strval(inputtext);
				krovinys[playerDB[playerid][masina]]+=strval(inputtext);
				return 1;
			}
			else if(!response) // Jai zaidejas paspaude mygtuka Iseiti
			{
				SDDI(playerid);
			}
			return 1;
		
		}



		if(dialogid==9877) // jai dialog id lygus 9877.
		{
			if(response) // jai paspaude prisijungti.
			{
				new query[128];
				format(query,sizeof(query),"SELECT Slaptazodis FROM `Account` WHERE Name='%s' LIMIT 1",ReturnName(playerid));
				mysql_function_query(SQL, query, true, "SQL_Login", "is", playerid,inputtext);

			}
			else if(!response) // Jai paspaude iseiti
			{
				SendInfoMessage(playerid,"~w~Viso Gero!");
				KickEx(playerid); // Ismes is serverio.
			}
			return 1;
		}
		if(dialogid==551)
		{
			if(response)
			{
				if(GetPlayerMoneyA(playerid) < 10000)
				{
					SendInfoMessage(playerid,"Jus neturite pakankamai pinigu !");
					return 1;
				}
				GivePlayerMoneyA(playerid,-10000);
				SendInfoMessage(playerid,"Kardo prekeivio biznis yra labai geras!");
				GivePlayerWeaponEx(playerid,8,50);
			}
		}
		if(dialogid==007) //mechaniku dialogas
		{
			if(response)
			{
				if(listitem == 0) //Jei pirmas pasirinkimas
				{
					//if(GetSpeed(playerid) > 5) return SendClientMessage(playerid, RED," * Masina privalo sustoti!");
					if(IsPlayerInAnyVehicle(playerid)) return SendInfoMessage(playerid,"Privalote islipti is automobilio!");
					if(GetPlayerMoneyA(playerid) < COST_TAISYMAS) return SendInfoMessage(playerid,"Truksta pinigu.");
					if(playerDB[playerid][ant] || playerDB[playerid][suristas]) return 1;
					/*SetVehicleHealth(GetPlayerVehicleID(playerid),1000); */
					if(Taisymas(playerid,0)==1)
					{
						Pelnas(playerid,5,(COST_TAISYMAS*2));//pelnas[5]+=(COST_TAISYMAS*3);
						GivePlayerMoneyA(playerid, - COST_TAISYMAS);
						SendInfoMessage(playerid,"Jus pataisete masinos varikli!");
						ProcessAchievement(playerid,34);
						playerDB[playerid][jobpts]++;
					}
				}
				else if(listitem == 1) //Jei antras pasirinkimas
				{
					new vehicleid = GetPlayerVehicleID(playerid);
					if(!vehicleid)
					{
						vehicleid = GetClosestVehicleid(playerid,10.0);
						if(!vehicleid || vehicleid == INVALID_VEHICLE_ID)
							return SendInfoMessage(playerid,"Prie jusu nera automobilio!");
					}
					if(GetPlayerMoneyA(playerid) < COST_DEGALAI) return SendInfoMessage(playerid,"Truksta pinigu.");
					SendInfoMessage(playerid,"Jus pripylete masinai degalu!");
					vehicleDB[vehicleid][gas]=40;
					//pelnas[5]+=100;
					GivePlayerMoneyA(playerid, - COST_DEGALAI);
					Pelnas(playerid,5,(COST_DEGALAI*2));
					playerDB[playerid][jobpts]++;
					/*new vairuotojas = GetDriver(GetPlayerVehicleID(playerid));
					if(!playerDB[vairuotojas][ant])
					{
						TogglePlayerControllable(vairuotojas,true);
					}*/
				}
				else if(listitem == 2) 
				{
					//if(GetSpeed(playerid) > 5) return SendClientMessage(playerid, RED," * Masina privalo sustoti!");
					if(IsPlayerInAnyVehicle(playerid)) return SendInfoMessage(playerid,"Privalote islipti is automobilio!");
					if(GetPlayerMoneyA(playerid) < COST_RESTAURAVIMAS) return SendInfoMessage(playerid,"Truksta pinigu.");
					/*SetVehicleHealth(GetPlayerVehicleID(playerid),1000);
					RepairVehicle(GetPlayerVehicleID(playerid));
					*/
					if(playerDB[playerid][ant] || playerDB[playerid][suristas]) return 1;
					if(Taisymas(playerid,1)==1)
					{
						//pelnas[5]+=100;
						GivePlayerMoneyA(playerid, - COST_RESTAURAVIMAS);
						Pelnas(playerid,5,(COST_RESTAURAVIMAS*2));
						SendInfoMessage(playerid,"Jus atrestauravote masina!");
						ProcessAchievement(playerid,34);
						playerDB[playerid][jobpts]++;
					}
					
				}
				else if(listitem == 3) //Jei ketvirtas pasirinkimas
				{
					if(!IsPlayerInAnyVehicle(playerid)) return SendInfoMessage(playerid,"Privalote sedeti automobilyje!");
					if(GetPlayerMoneyA(playerid) < 2000) return SendInfoMessage(playerid,"Truksta pinigu.");
					SendInfoMessage(playerid,"Idejote i masina signalizacija!");
					ProcessAchievement(playerid,34);
					alarmed[GetPlayerVehicleID(playerid)]=1;
					GetVehicleParamsEx(GetPlayerVehicleID(playerid),VehVars[0],VehVars[1],VehVars[2],VehVars[3],VehVars[4],VehVars[5],VehVars[6]);
					SetVehicleParamsEx(GetPlayerVehicleID(playerid),VehVars[0],VehVars[1],false,-1,VehVars[4],VehVars[5],VehVars[6]);
					Pelnas(playerid,5,4000);
					GivePlayerMoneyA(playerid, - 2000);
					playerDB[playerid][jobpts]++;
				}
				else if(listitem == 4) //spalva
				{
					if(!IsPlayerInAnyVehicle(playerid)) return SendInfoMessage(playerid,"Privalote sedeti automobilyje!");
					ShowPlayerDialog(playerid, 552, DIALOG_STYLE_LIST, "Spalvos", "Juoda \nBalta \nTamsiai melyna \nZydra \nZalia \nRaudona \nGeltona \nRozine\nMelyna\nRuda\nKita", "Dazyti!", "Gryzti");
				}
				else if(listitem == 5) //nos
				{
					if(!IsPlayerInAnyVehicle(playerid)) return SendInfoMessage(playerid,"Privalote sedeti automobilyje!");
					if(GetPlayerMoneyA(playerid) < 1000) return SendInfoMessage(playerid,"Truksta pinigu. Reikia 1000EUR.");
					if(IsABike(GetPlayerVehicleID(playerid)))
						return SendInfoMessage(playerid, "Negali uzdeti nitro siam transportui!");
					GivePlayerMoneyA(playerid, -1000);
					SendInfoMessage(playerid,"Idejote i masina nitro!");
					AddVehicleComponent(GetPlayerVehicleID(playerid),1010);
					Pelnas(playerid,5,2000);
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod2]=1010;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod2]=1010;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod2]=1010;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),1010);
					ProcessAchievement(playerid,34);
					playerDB[playerid][jobpts]++;
					
				}
				else if(listitem == 6) //hydraulika
				{
					if(!IsPlayerInAnyVehicle(playerid)) return SendInfoMessage(playerid,"Privalote sedeti automobilyje!");
					if(GetPlayerMoneyA(playerid) < 1500) return SendInfoMessage(playerid,"Truksta pinigu. Reikia 1500EUR.");
					if(IsABike(GetPlayerVehicleID(playerid)))
						return SendInfoMessage(playerid, "Negali uzdeti hidraulikos siam transportui!");
					SendInfoMessage(playerid,"Idejote i masina hydraulika!");
					GivePlayerMoneyA(playerid, -1500);
					AddVehicleComponent(GetPlayerVehicleID(playerid),1087);
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod12]=1087;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod12]=1087;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod12]=1087;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),1087);
					ProcessAchievement(playerid,34);
					Pelnas(playerid,5,3000);
					playerDB[playerid][jobpts]++;
				}
				else if(listitem == 7) // ratai
				{
					if(!IsPlayerInAnyVehicle(playerid)) return SendInfoMessage(playerid,"Privalote sedeti automobilyje!");
					if(IsABike(GetPlayerVehicleID(playerid)))
						return SendInfoMessage(playerid, "Negali uzdeti ratu siam transportui!");
					ShowPlayerDialog(playerid, 5051, DIALOG_STYLE_LIST, "Ratlankiai", "Switch\nMega\nCutter\nOffroad\nShadow\nRimshine\nWires\nClassic\nTwist\nGrove\nImport\nDollar\nTrance\nAtomic\nAhab\nVirtual\nAccess\n", "Rinktis", "Atgal");
					return 1;
				}
				else if(listitem == 8) // akumas
				{
					new vehicleid = GetPlayerVehicleID(playerid);
					if(!vehicleid)
					{
						vehicleid = GetClosestVehicleid(playerid,10.0);
						if(!vehicleid || vehicleid == INVALID_VEHICLE_ID)
							return SendInfoMessage(playerid,"Prie jusu nera automobilio!");
					}
					if(GetPlayerMoneyA(playerid) < COST_AKUMAS) return SendInfoMessage(playerid,"Truksta pinigu. Reikia "#COST_AKUMAS"EUR.");
					GivePlayerMoneyA(playerid, - COST_AKUMAS);
					Pelnas(playerid,5,COST_AKUMAS*2);
					vehicleDB[vehicleid][energy]=50.0;
					playerDB[playerid][jobpts]++;
					SendInfoMessage(playerid,"Pakrovei akumuliatoriu!");
					//if(IsABike(vehicleid) || IsAPlane(GetVehicleModel(vehicleid)) || IsABoat(GetVehicleModel(vehicleid))) return SendClientMessage(playerid,RED," * Ant sios transporto priemones neonu deti negalima!");
					//ShowPlayerDialog(playerid, 5052, DIALOG_STYLE_LIST, "Neonai", "Melyni\nRaudoni\nZali\nBalti\nRoziniai\nGeltoni", "Rinktis", "Atgal");
					return 1;
				}
				else if(listitem == 9)
				{
					new vehicleid=GetPlayerVehicleID(playerid);
					if(vehicleid == 0) return SendInfoMessage(playerid,"Privalote sedeti automobilyje!");
					if(GetPlayerMoneyA(playerid) < COST_PAINTJOB) return SendInfoMessage(playerid,"Truksta pinigu. Reikia "#COST_PAINTJOB"EUR.");
					GivePlayerMoneyA(playerid, - COST_PAINTJOB);
					Pelnas(playerid,5,COST_PAINTJOB*2);
					ProcessAchievement(playerid,34);
					playerDB[playerid][jobpts]++;
					ChangeVehiclePaintjob(vehicleid,3);
					SendInfoMessage(playerid,"Nuemei paintjob!");
					MaybeApplyAutokluboPaintjob(vehicleid, -1);
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][Paintjob]=-1;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][Paintjob]=-1;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][Paintjob]=-1;
					}
					//if(IsABike(vehicleid) || IsAPlane(GetVehicleModel(vehicleid)) || IsABoat(GetVehicleModel(vehicleid))) return SendClientMessage(playerid,RED," * Ant sios transporto priemones neonu deti negalima!");
					//ShowPlayerDialog(playerid, 5052, DIALOG_STYLE_LIST, "Neonai", "Melyni\nRaudoni\nZali\nBalti\nRoziniai\nGeltoni", "Rinktis", "Atgal");
					return 1;
				}
				if(listitem == 10)
				{
					new vehicleid=GetPlayerVehicleID(playerid);
					if(vehicleid == 0) 
						return SendInfoMessage(playerid,"Privalote sedeti automobilyje!");
					if(GetPlayerFromCarlistCar(vehicleid)==-1 && GetPlayerFromCarlistCar2(vehicleid)==-1 && GetPlayerFromCarlistCar3(vehicleid) == -1)
						return SendInfoMessage(playerid,"Tai ne nuosavas automobilis!");
					if(GetPlayerMoneyA(playerid) < COST_NUIMTI_TUNE) return SendInfoMessage(playerid,"Truksta pinigu. Reikia "#COST_NUIMTI_TUNE"EUR.");
					GivePlayerMoneyA(playerid, - COST_NUIMTI_TUNE);
					Pelnas(playerid,5,(COST_NUIMTI_TUNE*2));
					ProcessAchievement(playerid,34);
					playerDB[playerid][jobpts]++;
					SendInfoMessage(playerid,"Nuemei tune!");
					VehicleNitro[vehicleid]=0;
					if(GetPlayerFromCarlistCar(vehicleid)!=-1)
					{
						new pid = GetPlayerFromCarlistCar(vehicleid);
						if(Carlist[pid][mod1]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod1]); Carlist[pid][mod1]=-1; }
						if(Carlist[pid][mod2]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod2]); Carlist[pid][mod2]=-1;}
						if(Carlist[pid][mod3]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod3]); Carlist[pid][mod3]=-1;}
						if(Carlist[pid][mod4]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod4]); Carlist[pid][mod4]=-1;}
						if(Carlist[pid][mod5]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod5]); Carlist[pid][mod5]=-1;}
						if(Carlist[pid][mod6]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod6]); Carlist[pid][mod6]=-1;}
						if(Carlist[pid][mod7]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod7]); Carlist[pid][mod7]=-1;}
						if(Carlist[pid][mod8]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod8]); Carlist[pid][mod8]=-1;}
						if(Carlist[pid][mod9]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod9]); Carlist[pid][mod9]=-1;}
						if(Carlist[pid][mod10]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod10]); Carlist[pid][mod10]=-1;}
						if(Carlist[pid][mod11]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod11]); Carlist[pid][mod11]=-1;}
						if(Carlist[pid][mod12]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod12]); Carlist[pid][mod12]=-1;}
						if(Carlist[pid][mod13]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod13]); Carlist[pid][mod13]=-1;}
						if(Carlist[pid][mod14]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod14]); Carlist[pid][mod14]=-1;}
						if(Carlist[pid][mod15]!=-1) {  RemoveVehicleComponent(vehicleid,Carlist[pid][mod15]); Carlist[pid][mod15]=-1; }
						if(Carlist[pid][mod16]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod16]); Carlist[pid][mod16]=-1; }
						if(Carlist[pid][mod17]!=-1) { RemoveVehicleComponent(vehicleid,Carlist[pid][mod17]); Carlist[pid][mod17]=-1;}

					}
					else if(GetPlayerFromCarlistCar2(vehicleid)!=-1)
					{
						new pid = GetPlayerFromCarlistCar2(vehicleid);
						if(Carlist2[pid][mod1]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod1]); Carlist2[pid][mod1]=-1; }
						if(Carlist2[pid][mod2]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod2]); Carlist2[pid][mod2]=-1;}
						if(Carlist2[pid][mod3]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod3]); Carlist2[pid][mod3]=-1;}
						if(Carlist2[pid][mod4]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod4]); Carlist2[pid][mod4]=-1;}
						if(Carlist2[pid][mod5]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod5]); Carlist2[pid][mod5]=-1;}
						if(Carlist2[pid][mod6]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod6]); Carlist2[pid][mod6]=-1;}
						if(Carlist2[pid][mod7]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod7]); Carlist2[pid][mod7]=-1;}
						if(Carlist2[pid][mod8]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod8]); Carlist2[pid][mod8]=-1;}
						if(Carlist2[pid][mod9]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod9]); Carlist2[pid][mod9]=-1;}
						if(Carlist2[pid][mod10]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod10]); Carlist2[pid][mod10]=-1;}
						if(Carlist2[pid][mod11]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod11]); Carlist2[pid][mod11]=-1;}
						if(Carlist2[pid][mod12]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod12]); Carlist2[pid][mod12]=-1;}
						if(Carlist2[pid][mod13]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod13]); Carlist2[pid][mod13]=-1;}
						if(Carlist2[pid][mod14]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod14]); Carlist2[pid][mod14]=-1;}
						if(Carlist2[pid][mod15]!=-1) {  RemoveVehicleComponent(vehicleid,Carlist2[pid][mod15]); Carlist2[pid][mod15]=-1; }
						if(Carlist2[pid][mod16]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod16]); Carlist2[pid][mod16]=-1; }
						if(Carlist2[pid][mod17]!=-1) { RemoveVehicleComponent(vehicleid,Carlist2[pid][mod17]); Carlist2[pid][mod17]=-1;}
					}
					else if(GetPlayerFromCarlistCar3(vehicleid)!=-1)
					{
						new pid = GetPlayerFromCarlistCar3(vehicleid);
						if(Carlist3[pid][mod1]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod1]); Carlist3[pid][mod1]=-1; }
						if(Carlist3[pid][mod2]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod2]); Carlist3[pid][mod2]=-1;}
						if(Carlist3[pid][mod3]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod3]); Carlist3[pid][mod3]=-1;}
						if(Carlist3[pid][mod4]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod4]); Carlist3[pid][mod4]=-1;}
						if(Carlist3[pid][mod5]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod5]); Carlist3[pid][mod5]=-1;}
						if(Carlist3[pid][mod6]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod6]); Carlist3[pid][mod6]=-1;}
						if(Carlist3[pid][mod7]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod7]); Carlist3[pid][mod7]=-1;}
						if(Carlist3[pid][mod8]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod8]); Carlist3[pid][mod8]=-1;}
						if(Carlist3[pid][mod9]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod9]); Carlist3[pid][mod9]=-1;}
						if(Carlist3[pid][mod10]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod10]); Carlist3[pid][mod10]=-1;}
						if(Carlist3[pid][mod11]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod11]); Carlist3[pid][mod11]=-1;}
						if(Carlist3[pid][mod12]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod12]); Carlist3[pid][mod12]=-1;}
						if(Carlist3[pid][mod13]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod13]); Carlist3[pid][mod13]=-1;}
						if(Carlist3[pid][mod14]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod14]); Carlist3[pid][mod14]=-1;}
						if(Carlist3[pid][mod15]!=-1) {  RemoveVehicleComponent(vehicleid,Carlist3[pid][mod15]); Carlist3[pid][mod15]=-1; }
						if(Carlist3[pid][mod16]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod16]); Carlist3[pid][mod16]=-1; }
						if(Carlist3[pid][mod17]!=-1) { RemoveVehicleComponent(vehicleid,Carlist3[pid][mod17]); Carlist3[pid][mod17]=-1;}
					}
					else
					{
					}
				}
				if(listitem == 11)
				{
					//if(GetSpeed(playerid) > 5) return SendClientMessage(playerid, RED," * Masina privalo sustoti!");
					if(IsPlayerInAnyVehicle(playerid)) return SendInfoMessage(playerid,"Privalote islipti is automobilio!");
					if(GetPlayerMoneyA(playerid) < COST_RESTAURAVIMAS) return SendInfoMessage(playerid,"Truksta pinigu.");

					/*SetVehicleHealth(GetPlayerVehicleID(playerid),1000);
					RepairVehicle(GetPlayerVehicleID(playerid));
					*/
					if(playerDB[playerid][ant] || playerDB[playerid][suristas]) return 1;
					if(Taisymas(playerid,2)==1)
					{
						//pelnas[5]+=100;
						GivePlayerMoneyA(playerid, - 500);
						Pelnas(playerid,5,400);
						SendInfoMessage(playerid,"Jus atrestauravote masina ir sutvirtinote kebula!");
						ProcessAchievement(playerid,34);
						playerDB[playerid][jobpts]++;
					}
					
				}
			}
			return 1;
		}
	/*	if(dialogid==5052)
		{
			if(!response) return ShowPlayerDialog(playerid,007,DIALOG_STYLE_LIST,"Mechaniku meniu","Sutaisyti varikli(100€)\nPripilti degalu(100€)\nRestauruoti masina(150€)\nIdeti signalizacija(2000€)\nUzdeti spalva\nIdeti Nitro\nIdeti hydraulika\nRatai(1000€)\nPakrauti Akumuliatoriu(200€)","Rinktis","Iseiti");
			new obj;
			new vehicleid=GetPlayerVehicleID(playerid);
			switch(listitem)
			{
				case 0: obj=18648; // blue
				case 1: obj=18647; // red
				case 2: obj=18649; // green
				case 3: obj=18652; // white
				case 4: obj=18651; // pink
				case 5: obj=18650; // yellow
			}
			if(Neon[0][vehicleid]) { DestroyDynamicObject(Neon[0][vehicleid]); Neon[0][vehicleid]=0; }
			if(Neon[1][vehicleid]) { DestroyDynamicObject(Neon[1][vehicleid]); Neon[1][vehicleid]=0; }
			new Float:Coo[3]; GetPlayerPos(playerid, Coo[0],Coo[1],Coo[2]);
			Neon[0][vehicleid]= CreateDynamicObject(obj,Coo[0],Coo[1],Coo[2],0,0,0);
			Neon[1][vehicleid]= CreateDynamicObject(obj,Coo[0],Coo[1],Coo[2],0,0,0);
			AttachObjectToVehicle(Neon[0][vehicleid], vehicleid, -0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
			AttachObjectToVehicle(Neon[1][vehicleid], vehicleid, 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);
			SendClientMessage(playerid,GREEN," * Neonai ideti!");
		} */
		if(dialogid==5051)
		{
			if(!response) return ShowPlayerDialog(playerid,007,DIALOG_STYLE_LIST,"Mechaniku meniu","Sutaisyti varikli("#COST_TAISYMAS"€)\nPripilti degalu("#COST_DEGALAI"€)\nRestauruoti masina("#COST_RESTAURAVIMAS"€)\nIdeti signalizacija(2000€)\nUzdeti spalva\nIdeti Nitro\nIdeti hydraulika\nRatai(1000€)\nPakrauti Akumuliatoriu("#COST_AKUMAS"€)","Rinktis","Iseiti");
			if(response)
			{
				if(GetPlayerMoneyA(playerid) < 1000) return SendInfoMessage(playerid,"Neuztenka pinigu!");
				if(IsABike(GetPlayerVehicleID(playerid)))
					return SendInfoMessage(playerid, "Negali uzdeti ratu siam transportui!");
				if(listitem == 0)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1080); //Switch
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1080;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}

				if(listitem == 1)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1074); //Mega
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1074;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
				if(listitem == 2)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1079); //Cutter
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1079;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
				if(listitem == 3)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1025); //Offroad
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1025;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
				if(listitem == 4)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1073); //Shadow
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1073;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
				if(listitem == 5)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1075); //Rimshine
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1075;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
				if(listitem == 6)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1076); //Wires
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1076;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
				if(listitem == 7)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1077); //Classic
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1077;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
				if(listitem == 8)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1078); //Twist
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1078;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
				if(listitem == 9)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1081); //Grove
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1081;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
				if(listitem == 10)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1082); //Import
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1082;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
				if(listitem == 11)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1083); //Dollar
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1083;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
				
				if(listitem == 12)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1084); //Trance
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1084;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
				if(listitem == 13)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1085); //Atomic
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1085;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
				if(listitem == 14)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1096); //Ahab
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1096;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
				if(listitem == 15)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1097); //Virtual
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1097;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
				if(listitem == 16)
				{
					AddVehicleComponent(GetPlayerVehicleID(playerid), 1098); //Access
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					GivePlayerMoneyA(playerid, - 1000);
					Pelnas(playerid,5,200);
					new const id = 1098;
					if(GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist[GetPlayerFromCarlistCar(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist2[GetPlayerFromCarlistCar2(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					if(GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))!=-1)
					{
						Carlist3[GetPlayerFromCarlistCar3(GetPlayerVehicleID(playerid))][mod16]=id;
					}
					OnVehicleModEx(GetPlayerVehicleID(playerid),id);
				}
			}
			return 1;
		}
		if(dialogid==552) // Colors
		{
			if(response)
			{
				if(GetPlayerMoneyA(playerid) < 100) return SendInfoMessage(playerid,"Tau neuztenka pinigu.");
				new vehicleid = GetPlayerVehicleID(playerid);
				if(!vehicleid || GetDriver(vehicleid) == INVALID_PLAYER_ID) return SendInfoMessage(playerid,"Automobilyje turi sedeti vairuotojas!");
				new const spalvos[] = {0,1,79,240,16,3,6,126,152,174};
				if(listitem >= sizeof(spalvos))	
					return ShowPlayerDialog(playerid,553,DIALOG_STYLE_INPUT,"Pasirinkite spalva","Irasykite spalvos numeri, kuria norite uzdeti.\nTinkami numeriai: 0-255","Gerai","Atsaukti");

				new spalva = spalvos[listitem];
				SetPVarInt(playerid, "MechSpalva", spalva);

				ChangeVehicleColor(vehicleid,spalva,spalva);
				GivePlayerMoneyA(playerid, - 100);
				MaybeApplyAutokluboRespray(vehicleid, spalva, spalva);
				if(GetPlayerFromCarlistCar(vehicleid)!=-1)
				{
					Carlist[GetPlayerFromCarlistCar(vehicleid)][Color1]=spalva;
					Carlist[GetPlayerFromCarlistCar(vehicleid)][Color2]=spalva;
				}
				if(GetPlayerFromCarlistCar2(vehicleid)!=-1)
				{
					Carlist2[GetPlayerFromCarlistCar2(vehicleid)][Color1]=spalva;
					Carlist2[GetPlayerFromCarlistCar2(vehicleid)][Color2]=spalva;
				}
				if(GetPlayerFromCarlistCar3(vehicleid)!=-1)
				{
					Carlist3[GetPlayerFromCarlistCar3(vehicleid)][Color1]=spalva;
					Carlist3[GetPlayerFromCarlistCar3(vehicleid)][Color2]=spalva;
				}
				ShowPlayerDialog(playerid, 542, DIALOG_STYLE_LIST, "Antra spalva", "Juoda \nBalta \nTamsiai melyna \nZydra \nZalia \nRaudona \nGeltona \nRozine\nMelyna\nRuda\nKita", "Dazyti!", "Gryzti");
				Pelnas(playerid,5,200);

			}
			return 1;
		}
		if(dialogid==553)
		{
			if(response)
			{
				new vehicleid = GetPlayerVehicleID(playerid);
				new id = strval(inputtext);
				if(id < 0 || id > 255) return ShowPlayerDialog(playerid,553,DIALOG_STYLE_INPUT,"Pasirinkite spalva","Irasykite spalvos numeri, kuria norite uzdeti.\nTinkami numeriai: 0-255","Gerai","Atsaukti");
				ChangeVehicleColor(vehicleid,id,id);
				GivePlayerMoneyA(playerid, - 100);
				if(GetPlayerFromCarlistCar(vehicleid)!=-1)
				{
					Carlist[GetPlayerFromCarlistCar(vehicleid)][Color1]=id;
					Carlist[GetPlayerFromCarlistCar(vehicleid)][Color2]=id;
				}
				if(GetPlayerFromCarlistCar2(vehicleid)!=-1)
				{
					Carlist2[GetPlayerFromCarlistCar2(vehicleid)][Color1]=id;
					Carlist2[GetPlayerFromCarlistCar2(vehicleid)][Color2]=id;
				}
				if(GetPlayerFromCarlistCar3(vehicleid)!=-1)
				{
					Carlist3[GetPlayerFromCarlistCar3(vehicleid)][Color1]=id;
					Carlist3[GetPlayerFromCarlistCar3(vehicleid)][Color2]=id;
				}
				SetPVarInt(playerid, "MechSpalva", id);
				ShowPlayerDialog(playerid, 542, DIALOG_STYLE_LIST, "Antra spalva", "Juoda \nBalta \nTamsiai melyna \nZydra \nZalia \nRaudona \nGeltona \nRozine\nMelyna\nRuda\nKita", "Dazyti!", "Gryzti");
				Pelnas(playerid,5,200);
			}
		}
		if(dialogid==543)
		{
			if(response)
			{
				new vehicleid = GetPlayerVehicleID(playerid);
				new id = strval(inputtext);
				if(id < 0 || id > 255) return ShowPlayerDialog(playerid,543,DIALOG_STYLE_INPUT,"Pasirinkite spalva","Irasykite spalvos numeri, kuria norite uzdeti.\nTinkami numeriai: 0-255","Gerai","Atsaukti");
				
				GivePlayerMoneyA(playerid, - 100);
				ChangeVehicleColor(vehicleid,GetPVarInt(playerid, "MechSpalva"),id);
				if(GetPlayerFromCarlistCar(vehicleid)!=-1)
				{
					Carlist[GetPlayerFromCarlistCar(vehicleid)][Color2]=id;
				}
				if(GetPlayerFromCarlistCar2(vehicleid)!=-1)
				{
					Carlist2[GetPlayerFromCarlistCar2(vehicleid)][Color2]=id;
				}
				if(GetPlayerFromCarlistCar3(vehicleid)!=-1)
				{
					Carlist3[GetPlayerFromCarlistCar3(vehicleid)][Color2]=id;
				}
				Pelnas(playerid,5,200);
			}
			
		}
		if(dialogid==542) // Colors2
		{
			if(response)
			{
				if(GetPlayerMoneyA(playerid) < 100) return SendInfoMessage(playerid,"Tau neuztenka pinigu.");
				new vehicleid = GetPlayerVehicleID(playerid);
				if(!vehicleid || GetDriver(vehicleid) == INVALID_PLAYER_ID) return SendInfoMessage(playerid,"Automobilyje turi sedeti vairuotojas!");
				GivePlayerMoneyA(playerid, - 100);
				playerDB[playerid][jobpts]++;
				new const spalvos[] = {0,1,79,240,16,3,6,126,152,174};
				if(listitem >= sizeof(spalvos))	
					return ShowPlayerDialog(playerid,543,DIALOG_STYLE_INPUT,"Pasirinkite spalva","Irasykite spalvos numeri, kuria norite uzdeti.\nTinkami numeriai: 0-255","Gerai","Atsaukti");

				new spalva = spalvos[listitem];
				ChangeVehicleColor(vehicleid,GetPVarInt(playerid, "MechSpalva"),spalva);
				GivePlayerMoneyA(playerid, - 100);
				MaybeApplyAutokluboRespray(vehicleid, GetPVarInt(playerid, "MechSpalva"), spalva);
				if(GetPlayerFromCarlistCar(vehicleid)!=-1)
				{
					Carlist[GetPlayerFromCarlistCar(vehicleid)][Color2]=spalva;
				}
				if(GetPlayerFromCarlistCar2(vehicleid)!=-1)
				{
					Carlist2[GetPlayerFromCarlistCar2(vehicleid)][Color2]=spalva;
				}
				if(GetPlayerFromCarlistCar3(vehicleid)!=-1)
				{
					Carlist3[GetPlayerFromCarlistCar3(vehicleid)][Color2]=spalva;
				}
				Pelnas(playerid,5,200);
			}
			return 1;
		}
		if(dialogid==687)
		{
			if(!IsPlayerConnected(Pasisveikino[playerid]))return 1;
			if(response) // kick
			{	
				new msg[128],vardas[MAX_PLAYER_NAME],adminname[MAX_PLAYER_NAME];
				GetPlayerName(Pasisveikino[playerid],vardas,sizeof(vardas));
				GetPlayerName(playerid,adminname,sizeof(adminname));

				format(msg,sizeof(msg),"[kick] %s iðmetë %s ið serverio (Vardas_Pavarde).",adminname,vardas);
				SendClientMessageToAll(0xD9E916FF,msg);
				KickEx(Pasisveikino[playerid]);
			
			}
			else
			{
				new msg[128],pname[24],cname[24];
				new clickedplayerid=Pasisveikino[playerid];
				GetPlayerName(playerid,pname,24);
				GetPlayerName(clickedplayerid,cname,24);
				format(msg, 128, "* Pasisveikinote su %s ID %i!", cname, clickedplayerid);
				SendClientMessage(playerid, 0xFFFFFFFF, msg);
				if(Pasisveikino[playerid]==clickedplayerid) return 1;
				format(msg, 128, "* Su jumis pasisveikino %s ID %i!", pname, playerid);
				SendClientMessage(clickedplayerid, 0xFFFFFFFF, msg);
			
			}
		}
		if(dialogid==5010)
		{
			if(response)
			{
				if(listitem == 0)
				{
					if(playerDB[playerid][pKneeSkill] == 0) return SendInfoMessage(playerid,"Tu nemoki sito kovos stiliaus. Ji gali ismokt sporto saleje. /treniruotis");
					playerDB[playerid][pFS] = 5;
					SetPlayerSkills(playerid);
				}
				if(listitem == 1)
				{
					if(playerDB[playerid][pBoxiSkill] == 0) return SendInfoMessage(playerid,"Tu nemoki sito kovos stiliaus. Ji gali ismokt sporto saleje. /treniruotis");
					playerDB[playerid][pFS] = 1;
					SetPlayerSkills(playerid);
				}
				if(listitem == 2)
				{
					if(playerDB[playerid][pGrabSkill] == 0) return SendInfoMessage(playerid,"Tu nemoki sito kovos stiliaus. Ji gali ismokt sporto saleje. /treniruotis");
					playerDB[playerid][pFS] = 3;
					SetPlayerSkills(playerid);
				}
				if(listitem == 3)
				{
					if(playerDB[playerid][pKneeSkill] == 0) return SendInfoMessage(playerid,"Tu nemoki sito kovos stiliaus. Ji gali ismokt sporto saleje. /treniruotis");
					playerDB[playerid][pFS] = 4;
					SetPlayerSkills(playerid);
				}
				if(listitem == 4)
				{
					if(playerDB[playerid][pKungSkill] == 0) return SendInfoMessage(playerid,"Tu nemoki sito kovos stiliaus. Ji gali ismokt sporto saleje. /treniruotis");
					playerDB[playerid][pFS] = 2;
					SetPlayerSkills(playerid);
				}
				if(listitem == 5)
				{
					playerDB[playerid][pFS] = 0;
					SetPlayerSkills(playerid);
				}
			}
		}

		if(dialogid==012) //darbu izanga
		{
			if(response)
			{
				if(listitem == 0) //Jei pirmas pasirinkimas
				{
					ShowPlayerDialog(playerid,013,DIALOG_STYLE_TABLIST,"Mini darbai",DARBAI_MINI,"Rinktis","Atgal");
					return 1;
				}
				else if(listitem == 1) //Jei antras pasirinkimas
				{
					ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
					return 1;
				}
				else if(listitem == 2) 
				{
					ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
					return 1;
				}
				else if(listitem == 3) 
				{
					ShowPlayerDialog(playerid,115,DIALOG_STYLE_TABLIST,"Nelegalûs darbai",DARBAI_NELEGALUS,"Rinktis","Atgal");
					return 1;
				}
				else if(listitem==4)
				{
					ShowPlayerDialog(playerid,012,DIALOG_STYLE_LIST,"Darbai",#TEXT_GREEN"• "#TEXT_WHITE"Mini darbai\n"#TEXT_GREEN"• "#TEXT_WHITE"Darbai be pakvietimo\n"#TEXT_GREEN"• "#TEXT_WHITE"Darbai su pakvietimu\n"#TEXT_GREEN"• "#TEXT_WHITE"Nelegalûs darbai\n \n"#TEXT_GREEN"• "#TEXT_WHITE"Apie darbus","Rinktis","Iseiti");					return 1;
				}
				else if(listitem==5)
				{
					ShowPlayerDialog(playerid,5995,DIALOG_STYLE_MSGBOX,"Darbai","Pats lengviausias bûdas uþsidirbti pinigø yra dirbti viename ið Los Santos darbø. Serveryje yra keturios darbø rûðis:\n\
						\n\n"#TEXT_GREEN"• Mini darbai"#TEXT_WHITE"\nÐie darbai nereikalauja patirties taðkø(XP), jiems nereikia teisiø ir á juos nereikia ásidarbinti. Tai puikus variantas, kai reikia greitai uþsidirbti pinigø.\n\
						\n\n"#TEXT_GREEN"• Darbai be pakvietimo"#TEXT_WHITE"\nÐie darbai tinkami naujokams, nes jiems nereikia daug XP. Á juos ásidarbinti labai paprasta: tereikia uþlipti ant marðkinëliø darbo bazëje.\n\
						Darbai be pakvietimo yra paprasti, todël jie moka nedaug pinigø, bet jie puikiai tinka susipaþinti su Los Santos miestu.\nVisi darbai moka algà tiesiai á jûsø banko sàskaità, o uþ papildomà veiklà gaunate pinigø á rankas.\n\
						\n\n"#TEXT_GREEN"• Darbai su pakvietimu"#TEXT_WHITE"\nNorint dirbti darbe su pakvietimu pirmiausiai reikës sudalyvauti atrankoje ir patekti á darbà. Atrankos áprastai vyksta treèiadieniais ir ðeðtadieniais 19:00,\n\
						taèiau esant darbuotojø trûkumui direktoriai gali padaryti atrankas ir kitomis dienomis. Norint gauti algà ðiuose darbuose reikia pradirbti bent 100 minuèiø\niki algø, kurios vyksta treèiadieniais ir ðeðtadieniais 17:00.\n\
						Darbams su pakvietimu reikalingos teisës bei sveikatos paþymëjimas, o jø XP reikalavimas prasideda nuo 3.000XP.\n\
						\n\n"#TEXT_GREEN"• Nelegalûs darbai"#TEXT_WHITE"\nÐie darbai priklauso gaujoms kurios uþima ir iðlaiko narkotikø sandëlius. Atrankos á juos nevyksta, o norint á juos patekti, jûms reikës sumokëti kyðá darbo direktoriui.\n\n\nPrisijungusius darbø direktorius galite rasti paraðæ "#TEXT_BLUE"/direktoriai","Gerai","Atgal");
				}
			}
			return 1;
		}
		if(dialogid == 5995)
		{
			if(!response)
			{
				ShowPlayerDialog(playerid,012,DIALOG_STYLE_LIST,"Darbai",#TEXT_GREEN"• "#TEXT_WHITE"Mini darbai\n"#TEXT_GREEN"• "#TEXT_WHITE"Darbai be pakvietimo\n"#TEXT_GREEN"• "#TEXT_WHITE"Darbai su pakvietimu\n"#TEXT_GREEN"• "#TEXT_WHITE"Nelegalûs darbai\n \n"#TEXT_GREEN"• "#TEXT_WHITE"Apie darbus","Rinktis","Iseiti");
				return 1;
			}
		}
		if(dialogid==013) //darbai >>>> info
		{
			if(response)
			{// #define DARBAI_BE_PAKVIETIMO "BMX???eris\nSlavejas\nTraukinistas\nSokeja\nSiuksliavezys\nStatybininkas\nPicu isveziotojas\nAutobuso vairuotojas\nPakrantes apsauga\nKunigas\nPilotas\nReporteris\nKriminalistas\nMikro autobuso vairuotojas\nPasienietis\nNekilnojamo turto agentas\nBankininkas"
				if(listitem == 0) //Jei antras pasirinkimas
				{
					ShowPlayerDialog(playerid,017,DIALOG_STYLE_MSGBOX,"Ledu pardavejas","Reikalauja xp: 0\n\nUzdarbis: "#MONEY_LEDAI"€/min\n\nAutomobilis: Mr Whoopee\n\nPareigos: Pardavineti ledus.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 1) 
				{
					ShowPlayerDialog(playerid,018,DIALOG_STYLE_MSGBOX,"Zvejys","Reikalauja xp: 0\n\nUzdarbis: "#MONEY_ZVEJYS"€/min\n\nAutomobilis: Walton\n\nLaivas: Reefer\n\nPareigos: Pardavineti zuvi.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 2) 
				{
					ShowPlayerDialog(playerid,019,DIALOG_STYLE_MSGBOX,"Desrainiu pardavejas","Reikalauja xp: 0\n\nUzdarbis: "#MONEY_HOTDOG"€/min\n\nAutomobilis: Hotdog\n\nPareigos: Pardavineti desrainius.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 3)
				{
					ShowPlayerDialog(playerid,011,DIALOG_STYLE_MSGBOX,"Pieno isveziotojas","Reikalauja xp: 0\n\nUzdarbis: "#MONEY_PIENAS"€/min\n\nAutomobilis: Sadler\n\nPareigos: Pardavineti piena.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 4)
				{
					ShowPlayerDialog(playerid,010,DIALOG_STYLE_MSGBOX,"Pastininkas","Reikalauja xp: 0\n\nUzdarbis: "#MONEY_PASTAS"€ uz laiska\n\nAutomobilis: nuosavas\n\nPareigos: Pasiimti laisku ir juos isvezioti.","Kur jis?","Atgal");
					return 1;
				}
			}
			else if(!response) 	ShowPlayerDialog(playerid,012,DIALOG_STYLE_LIST,"Darbai",#TEXT_GREEN"• "#TEXT_WHITE"Mini darbai\n"#TEXT_GREEN"• "#TEXT_WHITE"Darbai be pakvietimo\n"#TEXT_GREEN"• "#TEXT_WHITE"Darbai su pakvietimu\n"#TEXT_GREEN"• "#TEXT_WHITE"Nelegalûs darbai\n \n"#TEXT_GREEN"• "#TEXT_WHITE"Apie darbus","Rinktis","Iseiti");			return 1;
		}
		if(dialogid==010)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,616.8500,-1458.9423,14.4306,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response)  ShowPlayerDialog(playerid,013,DIALOG_STYLE_TABLIST,"Mini darbai",DARBAI_MINI,"Rinktis","Atgal");
		}
		if(dialogid==014) //darbai >>>> info
		{
			if(response)
			{
				if(listitem == 0) 
				{
					ShowPlayerDialog(playerid,024,DIALOG_STYLE_MSGBOX,"BMX'eris","Reikalauja xp: "#XP_BMX"\n\nUzdarbis: "#MONEY_BMX"€/min + "#MONEYP_BMX"€ uz stuntus\n\nDviratis: BMX\n\nPareigos: Rodyti zmonems savo triukus","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 1)
				{
					ShowPlayerDialog(playerid,016,DIALOG_STYLE_MSGBOX,"Slavejas","Reikalauja xp: "#XP_SLAVEJAS"\n\nUzdarbis: "#MONEY_SLAVEJAS"€/min + "#MONEYP_SLAVEJAS"€ uz marsruta\n\nAutomobilis: Sweeper\n\nPareigos: Valyti gatves ir saligatvius.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 2) 
				{
					ShowPlayerDialog(playerid,023,DIALOG_STYLE_MSGBOX,"Traukinistas","Reikalauja xp: "#XP_TRAUKINISTAS"\n\nUzdarbis: "#MONEY_TRAUKINISTAS"€/min + "#MONEYP_TRAUKINISTAS"€ uz sustojimus.\n\nTraukinys: Freight, Brownstreak\n\nPareigos: Vezioti zmones is miesto i miesta.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 3) 
				{
					ShowPlayerDialog(playerid,824,DIALOG_STYLE_MSGBOX,"Sokeja","Reikalauja xp: "#XP_SOKEJA"\n\nUzdarbis: "#MONEY_SOKEJA"€/min\n\nAutomobilis: Intruder\n\nPareigos: Gundyti vyrus ir sokti klubuose.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 4) 
				{
					ShowPlayerDialog(playerid,022,DIALOG_STYLE_MSGBOX,"Siuksliavezis","Reikalauja xp: "#XP_SIUKSLIAVEZIS"\n\nUzdarbis: "#MONEY_SIUKSLIAVEZIS"€/min + "#MONEYP_SIUKSLIAVEZIS"€ Uz iskrautas siuksles.\n\nAutomobilis: Siuksliavezys\n\nPareigos: Isvezioti siuksles.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 5) 
				{
					ShowPlayerDialog(playerid,923,DIALOG_STYLE_MSGBOX,"Statybininkas","Reikalauja xp: "#XP_STATYBININKAS"\n\nUzdarbis: "#MONEY_STATYBININKAS"€/min + "#MONEYP_STATYBININKAS"€ uz atvezta cementa.\n\nAutomobilis: Cement Truck\n\nPareigos: Vezioti Cementa.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 6) //Jei antras pasirinkimas
				{
					ShowPlayerDialog(playerid,021,DIALOG_STYLE_MSGBOX,"Picos isveziotojas","Reikalauja xp: "#XP_PICU_ISVEZIOTOJAS"\n\nUzdarbis: "#MONEY_PICU_ISVEZIOTOJAS"€/min + "#MONEYP_PICU_ISVEZIOTOJAS"€ uz picos atvezima.\n\nAutomobilis: Pizzaboy\n\nPareigos: Pardaveineti zmonems picas ir isvezioti jas po namus.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 7) //Jei pirmas pasirinkimas
				{
					ShowPlayerDialog(playerid,020,DIALOG_STYLE_MSGBOX,"Autobuso vairuotojas","Reikalauja xp: "#XP_AUTOBUSO_VAIRUOTOJAS"\n\nUzdarbis: "#MONEY_AUTOBUSO_VAIRUOTOJAS"€/min + "#MONEYP_AUTOBUSO_VAIRUOTOJAS"€ uz stotele.\n\nAutomobilis: Bus\n\nPareigos: Vezioti zmones po stoteles.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 8) 
				{
					ShowPlayerDialog(playerid,027,DIALOG_STYLE_MSGBOX,"Pakrantes apsauga","Reikalauja xp: "#XP_PAKRANTES_APSAUGA"\n\nUzdarbis: "#MONEY_PAKRANTES_APSAUGA"€/min + "#MONEYP_PAKRANTES_APSAUGA"€ uz priziureta kranta.\n\nAutomobilis: BF Injection, Kateris: Squallo\n\nPareigos: Priziureti tvarka papludimyje.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 9) 
				{
					ShowPlayerDialog(playerid,030,DIALOG_STYLE_MSGBOX,"Kunigas","Reikalauja xp: "#XP_KUNIGAS"\n\nUzdarbis: "#MONEY_KUNIGAS"€/min + Pinigai uz vestuves\n\nAutomobilis: Romero\n\nPareigos: Sutuokineti zmones bei rengti misias.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 10) 
				{
					ShowPlayerDialog(playerid,025,DIALOG_STYLE_MSGBOX,"Pilotas","Reikalauja xp: "#XP_PILOTAS"\n\nUzdarbis: "#MONEY_PILOTAS"€/min + "#MONEYP_PILOTAS"€ uz skrydi i kita miesta.\n\nLektuvas: Shamal\n\nPareigos: Skraidinti zmones is vieno miesto i kita.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 11) 
				{
					ShowPlayerDialog(playerid,026,DIALOG_STYLE_MSGBOX,"Reporteris","Reikalauja xp: "#XP_REPORTERIS"\n\nUzdarbis: "#MONEY_REPORTERIS"€/min\n\nAutomobilis: Newsvan, Sraigtasparnis: SAN News Maverick\n\nPareigos: Dometis serverio aktualijomis bei jas pranesti kitiems.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 12) 
				{
					ShowPlayerDialog(playerid,029,DIALOG_STYLE_MSGBOX,"Kriminalistas","Reikalauja xp: "#XP_KRIMINALISTAS"\n\nUzdarbis: "#MONEY_KRIMINALISTAS"€/min + "#MONEYP_KRIMINALISTAS"€ uz istirta zmogzudyste.\n\nAutomobilis: Stallion\n\nPareigos: Tirti nusikaltimus mieste.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 13) //Jei antras pasirinkimas
				{
					ShowPlayerDialog(playerid,121,DIALOG_STYLE_MSGBOX,"Mikro autobuso vairuotojas","Reikalauja xp: "#XP_MIKRO_VAIRUOTOJAS"\n\nUzdarbis: "#MONEY_MIKRO_VAIRUOTOJAS"€/min + "#MONEYP_MIKRO_VAIRUOTOJAS"€ uz bilieta.\n\nAutomobilis: Mikro autobusas\n\nPareigos: Vezioti zmones savais marsrutais.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 14) 
				{
					ShowPlayerDialog(playerid,028,DIALOG_STYLE_MSGBOX,"Pasienietis","Reikalauja xp: "#XP_PASIENIETIS"\n\nUzdarbis: "#MONEY_PASIENIETIS"€/min + pinigai uz vartu atidaryma\n\nAutomobilis: Landstalker\n\nPareigos: Praleisti zmones pro pasieni.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 15)
				{
					ShowPlayerDialog(playerid,134,DIALOG_STYLE_MSGBOX,"Bankininkas","Reikalauja xp: "#XP_BANKININKAS"\n\nUzdarbis: "#MONEY_BANKININKAS"€/min + "#MONEYP_BANKININKAS"€ uz pakrautus bankomatus.\n\nAutomobilis: Securicar, \n\nPareigos: Teikti zmonem banko paslaugas, vezioti pinigus i bankomatus.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 16)
				{
					ShowPlayerDialog(playerid,135,DIALOG_STYLE_MSGBOX,"Ukininkas","Reikalauja xp: "#XP_UKININKAS"\n\nUzdarbis: "#MONEY_UKININKAS"€/min + "#MONEYP_UKININKAS"€ uz nupjauta veja ar kultivuotus laukus.\n\nAutomobiliai: Mower,Tractor, \n\nPareigos: Pjauti zole, bei kultivuoti laukus.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 17)
				{
					ShowPlayerDialog(playerid,052,DIALOG_STYLE_MSGBOX,"Advokatas","Reikalauja xp: "#XP_ADVOKATAS"\n\nUzdarbis: "#MONEY_ADVOKATAS"€/min + pinigai uz isteisinima\n\nAutomobilis: Elegant\n\nPareigos: Eiti i vykstancius teismus ir ginti savo uzsakova teisme, isteisinti zmones kalejime.","Kur jis?","Atgal");
					return 1;
				}
			}
			else if(!response) 	ShowPlayerDialog(playerid,012,DIALOG_STYLE_LIST,"Darbai",#TEXT_GREEN"• "#TEXT_WHITE"Mini darbai\n"#TEXT_GREEN"• "#TEXT_WHITE"Darbai be pakvietimo\n"#TEXT_GREEN"• "#TEXT_WHITE"Darbai su pakvietimu\n"#TEXT_GREEN"• "#TEXT_WHITE"Nelegalûs darbai\n \n"#TEXT_GREEN"• "#TEXT_WHITE"Apie darbus","Rinktis","Iseiti");			return 1;
		}
		
		if(dialogid==015) //darbai >>>> info
		{
			if(response)
			{// #define DARBAI_SU_PAKVIETIMU "Automanas\nTaksistas\nMedikas\nKurjeris\nLimuzino Vairuotojas\nViesojo Saugumo Tarnyba\nMechanikas\nBaikeris\nSkelbejas\nGaisrininkas\nTransporteris\nMotomanas\nFuristas\nPolicininkas\nKontrabandininkas\nKobra 11\nDealeris\nARAS\nVagis\nKareivis"
				if(listitem == 0) 
				{
					ShowPlayerDialog(playerid,037,DIALOG_STYLE_MSGBOX,"Automanas","Reikalauja xp: "#XP_AUTOMANAI"\n\nUzdarbis: "#MONEY_AUTOMANAI"€/min (á pelnà) + Keliones\n\nAutomobiliai: Hotknife, Oceanic, Hermes, Broadway \n\nPareigos: Vazineti po miesta, eksponuoti senovinius automobilius.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 1) 
				{
					ShowPlayerDialog(playerid,040,DIALOG_STYLE_MSGBOX,"Taksistas","Reikalauja xp: "#XP_TAKSISTAI"\n\nUzdarbis: "#MONEY_TAKSISTAI"€/min (á pelnà) + pinigai uz nuvezima\n\nAutomobilis: Taksi\n\nPareigos: Vezioti zmones, pagal uzsakyma.","Kur jis?","Atgal");
					return 1;
				}
				if(listitem == 2) //Jei antras pasirinkimas
				{
					ShowPlayerDialog(playerid,036,DIALOG_STYLE_MSGBOX,"Medikas","Reikalauja xp: "#XP_MEDIKAI"\n\nUzdarbis: "#MONEY_MEDIKAI"€/min (á pelnà) + Sveikatos pazymejimai\n\nAutomobiliai: Ambulance, Raindance\n\nPareigos: Gydyti suzeistuosius bei aprupinti juos sveikatos pazymejimais.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 3) 
				{
					ShowPlayerDialog(playerid,046,DIALOG_STYLE_MSGBOX,"Kurjeris","Reikalauja xp: "#XP_KURJERIAI"\n\nUzdarbis: "#MONEY_KURJERIAI"€/min (á pelnà) + Iskrovimai\n\nAutomobiliai: Mule, Yankee, Benson\n\nPareigos: Isvezioti krovinius i nurodytas vietas.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 4)
				{
					ShowPlayerDialog(playerid,047,DIALOG_STYLE_MSGBOX,"Viesojo Saugumo Tarnyba","Reikalauja xp: "#XP_VST"\n\nUzdarbis: "#MONEY_VST"€/min (á pelnà) + Baudos\n\nAutomobilis: Fbi truck\n\nPareigos: Saugoti, Gelbeti, Padeti.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 5) 
				{
					ShowPlayerDialog(playerid,039,DIALOG_STYLE_MSGBOX,"Mechanikas","Reikalauja xp: "#XP_MECHANIKAI"\n\nUzdarbis: "#MONEY_MECHANIKAI"€/min (á pelnà) + Masinu nutempimai, automobiliu taisymas\n\nAutomobilis: Towtruck\n\nPareigos: Taisyti automobilius zmonems iskvietus, nutempti ant gatves paliktas masinas.","Kur jis?","Atgal");
					return 1;
				}
				
				else if(listitem == 6)
				{
					ShowPlayerDialog(playerid,050,DIALOG_STYLE_MSGBOX,"Skelbejas","Reikalauja xp: "#XP_SKELBEJAI"\n\nUzdarbis: "#MONEY_SKELBEJAI"€/min (á pelnà) + 500€ uz viena skelbima\n\nAutomobilis: Washington\n\nPareigos: Rasyti skelbimus, pagal zaideju uzsakymus.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 7)
				{
					ShowPlayerDialog(playerid,032,DIALOG_STYLE_MSGBOX,"Gaisrininkas","Reikalauja xp: "#XP_GAISRININKAI"\n\nUzdarbis: "#MONEY_GAISRININKAI"€/min (á pelnà) + Pinigai uz uzgesintus automobilius ir gaisrus.\n\nAutomobilis: Firetruck, \n\nPareigos: Gesinti uzdegtas masinas pagal iskvietimus!","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 8)
				{
					ShowPlayerDialog(playerid,044,DIALOG_STYLE_MSGBOX,"Transporteris","Reikalauja xp: "#XP_TRANSPORTERIAI"\n\nUzdarbis: "#MONEY_TRANSPORTERIAI"€/min (á pelnà) + Pinigai uz nuvezima\n\nAutomobilis: ZR-350\n\nPareigos: Skubiai pervezineti klientus.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 9)
				{
					ShowPlayerDialog(playerid,048,DIALOG_STYLE_MSGBOX,"Motomanas","Reikalauja xp: "#XP_MOTOMANAS"\n\nUzdarbis: "#MONEY_MOTOMANAS"€/min (á pelnà) + Keliones\n\nMotociklai: PCJ-600, BF-400\n\nPareigos: Exponuoti savo britvas, daryti keliones po miestus.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 10)
				{
					ShowPlayerDialog(playerid,045,DIALOG_STYLE_MSGBOX,"Furistas","Reikalauja xp: "#XP_FURISTAI"\n\nUzdarbis: "#MONEY_FURISTAI"€/min (á pelnà) + Pinigai uz pasiektus taskus\n\nAutomobiliai: Tanker, Roadtrain\n\nPareigos: Isvezioti krovinius i nurodytas vietas.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 11) 
				{
					ShowPlayerDialog(playerid,041,DIALOG_STYLE_MSGBOX,"Policininkas","Reikalauja xp: "#XP_POLICININKAI"\n\nUzdarbis: "#MONEY_POLICININKAI"€/min (á pelnà) + pinigai uz bauda.\n\nAutomobiliai: Police Ranger, Police Car (LSPD)  Motociklas: HPV1000 Sraigtasparnis: Police Maverick\n\nPareigos: Priziureti eisma kelyje.","Kur jis?","Atgal");
					return 1;
				}
								

				else if(listitem == 12)
				{
					ShowPlayerDialog(playerid,043,DIALOG_STYLE_MSGBOX,"ARAS","Reikalauja xp: "#XP_ARAS"\n\nUzdarbis: "#MONEY_ARAS"€/min (á pelnà) + Baudos\n\nAutomobilis: Enforcer, S.W.A.T.\n\nPareigos: Vykdyti antiteroristines ir ikaitu islaisvinimo operacijas.\nVykdyti ginkluotu ir pavojingu nusikalteliu sulaikymus.\nDalyvauti vykdant operatyvinius veiksmus, sulaikant asmenis, itariamus padarius arba besirengiancius daryti nusikaltimus...","Kur jis?","Atgal");
					return 1;
				}

				else if(listitem == 13)
				{
					ShowPlayerDialog(playerid,053,DIALOG_STYLE_MSGBOX,"Kobra 11","Reikalauja xp: "#XP_KOBRA"\n\nUzdarbis: "#MONEY_KOBRA"€/min (á pelnà) + Baudos\n\nAutomobilis: Cheetah\n\nPareigos: Gaudyt vagis, padet teisesaugai gaudyt beglius.","Kur jis?","Atgal");
					return 1;
				}

				
				else if(listitem == 14)
				{
					ShowPlayerDialog(playerid,051,DIALOG_STYLE_MSGBOX,"Kareivis","Reikalauja xp: "#XP_KAREIVIS"\n\nUzdarbis: "#MONEY_KAREIVIS"€/min (á pelnà) + Baudos\n\nAutomobiliai: Patriot, Hydra, Hunter, Cargobob \n\nPareigos: Padeti policijai gaudyti stambius nusikaltelius/teroristus.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 15)
				{
					ShowPlayerDialog(playerid,031,DIALOG_STYLE_MSGBOX,"Nekilnojamo turto agentas","Reikalauja xp: "#XP_TURTO_AGENTAS"\n\nUzdarbis: "#MONEY_TURTO_AGENTAS"€/min (á pelnà) + Pinigai uz sandorius\n\nAutomobilis: Euros\n\nPareigos: Padeti zmonems isirinkti namus/verslus, tvarkyti nekilnojama turta.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 16)
				{
					ShowPlayerDialog(playerid,034,DIALOG_STYLE_MSGBOX,"Privatus Medikas","Reikalauja xp: "#XP_PRIVATUS"\n\nUzdarbis: "#MONEY_PMEDIKAI"€/min (á pelnà) + Pinigai uz suteiktas paslaugas\n\nAutomobilis: Blista,Rancher,Sparrow\n\nPareigos: Gydyti zmones ir suteikti jiem sveikatos pazymejimus.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 17) // inkasatorius
				{
					ShowPlayerDialog(playerid,451,DIALOG_STYLE_MSGBOX,"Inkasatorius","Reikalauja xp: "#XP_INKASATORIUS"\n\nUzdarbis: "#MONEY_INKASATORIUS"€/min (á pelnà) + Pinigai uz pervezimo paslaugas\n\nAutomobilis: Securicar\n\nPareigos: Pervezti pinigus pagal uzsakymus.","Kur jis?","Atgal");
					return 1;
				}
			}
			else if(!response) 	ShowPlayerDialog(playerid,012,DIALOG_STYLE_LIST,"Darbai",#TEXT_GREEN"• "#TEXT_WHITE"Mini darbai\n"#TEXT_GREEN"• "#TEXT_WHITE"Darbai be pakvietimo\n"#TEXT_GREEN"• "#TEXT_WHITE"Darbai su pakvietimu\n"#TEXT_GREEN"• "#TEXT_WHITE"Nelegalûs darbai\n \n"#TEXT_GREEN"• "#TEXT_WHITE"Apie darbus","Rinktis","Iseiti");			return 1;
		}
		if(dialogid==115)
		{
			if(response)
			{
				if(listitem == 0) 
				{
					ShowPlayerDialog(playerid,038,DIALOG_STYLE_MSGBOX,"Baikeris","Reikalauja xp: "#XP_BAIKERIAI"\n\nUzdarbis: "#MONEY_BAIKERIAI"€/min (á pelnà)\n\nMotociklas: Freeway\n\nPareigos: Exponuoti savo motocikus bei siek tiek nepaklusti teisesaugai :)","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 1) 
				{
					ShowPlayerDialog(playerid,141,DIALOG_STYLE_MSGBOX,"Kontrabandininkas","Reikalauja xp: "#XP_KONTRABANDA"\n\nUzdarbis: "#MONEY_KONTRABANDA"€/min (á pelnà) + Pinigai uz iskrovima.\n\nAutomobiliai: Bobcat, Picador, Boxvile: \n\nPareigos: Vezioti ginklus ir narkotikus.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 2)
				{
					ShowPlayerDialog(playerid,148,DIALOG_STYLE_MSGBOX,"Dyleris","Reikalauja xp: "#XP_DEALERIS"\n\nUzdarbis: "#MONEY_DEALERIS"€/min (á pelnà) + Pardavimai\n\nAutomobilis: Esperanto\n\nPareigos:Pardavineti ginklus ir narkotikus.","Kur jis?","Atgal");
					return 1;
				}
				else if(listitem == 3)
				{
					ShowPlayerDialog(playerid,449,DIALOG_STYLE_MSGBOX,"Vagis","Reikalauja xp: "#XP_VAGIS"\n\nPlatesne informacija neskelbiama.","Kur jis?","Atgal");
					return 1;
				}
			}
			else if(!response) 	ShowPlayerDialog(playerid,012,DIALOG_STYLE_LIST,"Darbai",#TEXT_GREEN"• "#TEXT_WHITE"Mini darbai\n"#TEXT_GREEN"• "#TEXT_WHITE"Darbai be pakvietimo\n"#TEXT_GREEN"• "#TEXT_WHITE"Darbai su pakvietimu\n"#TEXT_GREEN"• "#TEXT_WHITE"Nelegalûs darbai\n \n"#TEXT_GREEN"• "#TEXT_WHITE"Apie darbus","Rinktis","Iseiti");			return 1;
		}
		if(dialogid==451) //inkasatorius
		{
			if(response)
			{
				SetPlayerCheckpoint(playerid,1658.5502,-1343.3350,17.4382,6.0);
				SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==449) // vagis
		{
			if(response)
			{
				SendInfoMessage(playerid,"Susirask ji pats!!");
			}
			else if(!response) ShowPlayerDialog(playerid,115,DIALOG_STYLE_TABLIST,"Nelegalûs darbai",DARBAI_NELEGALUS,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==450) //slaveju dialogas
		{
			if(response)
			{
				SetPlayerCheckpoint(playerid,2591.7954,-2175.8123,0.9734,6.0);
				SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==34) //slaveju dialogas
		{
			if(response)
			{
				SetPlayerCheckpoint(playerid,2025.3667,-1404.1603,17.2109,6.0);
				SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==016) //slaveju dialogas
		{
			if(response)
			{
				SetPlayerCheckpoint(playerid,1621.2847,-1887.3850,13.5480,6.0);
				SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}

		if(dialogid==112) //kontrabanda
		{
			if(response)
			{
				if(listitem == 0) //krauti nark
				{
					SetPlayerCheckpoint(playerid,-1117.0293,-1621.2343,76.3739,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
					return 1;
				}
				if(listitem == 1) // krauti gun
				{
					SetPlayerCheckpoint(playerid,255.2211,-158.0174,1.5703,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
					return 1;
				}
				if(listitem == 2) // krauti gun
				{
					SetPlayerCheckpoint(playerid,-2107.7827,-2401.7698,31.3832,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
					return 1;
				}
				if(listitem == 3) // krauti gun
				{
					SetPlayerCheckpoint(playerid,-2430.1716,2314.5378,4.9844,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
					return 1;
				}
				if(listitem == 4) // iskrauti
				{
					SetPlayerCheckpoint(playerid,1410.7506,-1304.8969,9.0368,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
					return 1;
				}
			}
			return 1;
		}


		if(dialogid==017) //ledu dialogas
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1946.2386,-2141.5417,13.5485,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response)  ShowPlayerDialog(playerid,013,DIALOG_STYLE_TABLIST,"Mini darbai",DARBAI_MINI,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==011)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,807.8798,-606.0580,16.3432,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response)  ShowPlayerDialog(playerid,013,DIALOG_STYLE_TABLIST,"Mini darbai",DARBAI_MINI,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==018) //zveju dialogas
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,167.2650,-1802.2814,4.1839,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response)  ShowPlayerDialog(playerid,013,DIALOG_STYLE_TABLIST,"Mini darbai",DARBAI_MINI,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==019) //desrainiu dialogas
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,2495.4219,-1744.5090,13.4757,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response)  ShowPlayerDialog(playerid,013,DIALOG_STYLE_TABLIST,"Mini darbai",DARBAI_MINI,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==020)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1432.5295,-2352.9258,13.5391,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==021)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,2100.1340,-1805.5992,13.5547,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==121)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1547.6846,-2320.7195,13.5547,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==022)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,2188.4175,-1984.3630,13.5510,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==023)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1689.3116,-1946.4226,13.5469,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==923)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1261.0067,-1250.2216,14.1399,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==024)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1859.6653,-1385.9291,13.5625,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==824) // sokeja
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,2421.4531,-1220.8494,25.4582,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==025)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1605.8281,-2631.4814,13.5469,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==026)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,771.8616,-1337.2327,13.5344,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==027)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,648.6686,-1871.8862,5.4609,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==028)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,210.1804,-1434.0956,13.2025,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==029)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,775.1966,-1377.3323,13.6187,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==030)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,928.5887,-1085.5601,24.2891,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==031)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,2485.6653,-1537.3223,23.9968,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==032)  // gaisrininkai
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1810.9818,-2021.2864,13.5456,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==033)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1245.5969,-2035.1282,59.8378,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}

		if(dialogid==134)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1473.3879,-1771.9489,18.7958,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==135)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1090.9701,-306.0299,73.9922,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==035)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1813.7799,-1880.6448,13.5781,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==036)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1184.7361,-1325.3058,13.5742,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==037)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1632.8000,-1037.7870,23.8984,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}

		if(dialogid==141) // KONTRABANDA
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1630.4290,-1845.7972,13.8913,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,115,DIALOG_STYLE_TABLIST,"Nelegalûs darbai",DARBAI_NELEGALUS,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==148) // DEALER
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1407.3196,-1300.3998,13.5503,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,115,DIALOG_STYLE_TABLIST,"Nelegalûs darbai",DARBAI_NELEGALUS,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==038)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,2802.7490,-1416.8666,15.7901,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,115,DIALOG_STYLE_TABLIST,"Nelegalûs darbai",DARBAI_NELEGALUS,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==039)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1628.1111,-1550.1956,13.6542,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==040)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,2155.8867,-1146.3519,24.5752,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==041)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1552.9650,-1627.8453,13.3828,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==042)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,480.3601,-1499.4764,20.0518,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==043)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,903.0731,-1233.8431,16.6222,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==044)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,904.9814,-1663.0570,13.5469,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==045)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,2441.6934,-2132.2241,17.2712,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==046)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,2281.1057,-2365.0566,13.5469,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==047)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1552.9650,-1627.8453,13.3828,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==048)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1624.9597,-1017.2007,23.4699,6.0);//904.9814,-1663.0570,13.5469,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==049)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,2066.7559,-1912.2290,13.5469,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==050)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,2850.5522,-1526.2449,10.6804,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==051)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,2730.0996,-2408.9104,13.4520,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==053)
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1786.6602,-1293.5505,13.1938,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,015,DIALOG_STYLE_TABLIST,"Darbai su pakvietimu",DARBAI_SU_PAKVIETIMU,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==052) //advokatas
		{
			if(response)
			{
				{
					SetPlayerCheckpoint(playerid,1016.2076,-1127.9236,23.8580,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite savo darba.");
				}
			}
			else if(!response) ShowPlayerDialog(playerid,014,DIALOG_STYLE_TABLIST,"Darbai be pakvietimo",DARBAI_BE_PAKVIETIMO,"Rinktis","Atgal");
			return 1;
		}
		if(dialogid==555) //mechaniku dialogas
		{
			if(response)
			{
				if(GetPlayerMoneyA(playerid) < COST_ISPIRKIMAS) return SendInfoMessage(playerid,"Mazai slamanciu~n~reik "#COST_ISPIRKIMAS"EUR");
				new Float:sx,Float:sy,Float:sz;
				GetVehiclePos(Carlist[playerid][Carid],sx,sy,sz);
				if(sy < -1483.6194 && sy > -1507.2380 && sx < 1546.4885 && sx > 1464.6373)
				{
					GivePlayerMoneyA(playerid, - COST_ISPIRKIMAS);
					SetVehiclePos(Carlist[playerid][Carid],1460.5974,-1498.4716,13.5469);
					SetVehicleVirtualWorld(Carlist[playerid][Carid],0);
					SendInfoMessage(playerid,"Jus issipirkote masina, ji turejo atsirasti salia jusu.");
					return 1;
				}

				new Float:zx,Float:zy,Float:zz;
				GetVehiclePos(Carlist2[playerid][Carid],zx,zy,zz);
				if(zy < -1483.6194 && zy > -1507.2380 && zx < 1546.4885 && zx > 1464.6373)
				{
					GivePlayerMoneyA(playerid, - COST_ISPIRKIMAS);
					SetVehiclePos(Carlist2[playerid][Carid],1460.5974,-1498.4716,13.5469);
					SetVehicleVirtualWorld(Carlist2[playerid][Carid],0);
					SendInfoMessage(playerid,"Jus issipirkote masina, ji turejo atsirasti salia jusu.");
					return 1;
				}
				new Float:xx,Float:xy,Float:xz;
				GetVehiclePos(Carlist3[playerid][Carid],xx,xy,xz);
				if(xy < -1483.6194 && xy > -1507.2380 && xx < 1546.4885 && xx > 1464.6373)
				{
					GivePlayerMoneyA(playerid, - COST_ISPIRKIMAS);
					SetVehiclePos(Carlist3[playerid][Carid],1460.5974,-1498.4716,13.5469);
					SetVehicleVirtualWorld(Carlist3[playerid][Carid],0);
					SendInfoMessage(playerid,"Jus issipirkote masina, ji turejo atsirasti salia jusu.");
					return 1;
				}
			}
			else if(!response) SendInfoMessage(playerid,"Nu ir gerai, jusu masina liks rudyti aiksteleje.^^");
			return 1;
		}







		if(dialogid==666) //VIETOS
		{
			if(response)
			{
				KurMenu(playerid,DLItemID);
				/*
				if(listitem == 0)
				{
					ShowPlayerDialog(playerid,012,DIALOG_STYLE_LIST,"Darbai","Mini darbai\nDarbai be pakvietimo\nDarbai su pakvietimu","Rinktis","Iseiti");
					return 1;
				}
				if(listitem == 1)
				{
					ShowPlayerDialog(playerid,667,DIALOG_STYLE_INPUT,"Rasti zmogu"," Noredami surasti zmogu, irasykite jo varda.","Rasti","Iseiti");
					return 1;
				}
				if(listitem == 2)
				{
					ShowPlayerDialog(playerid,668,DIALOG_STYLE_INPUT,"Rasti nama"," Noredami surasti nama, irasykite jo numeri.","Rasti","Iseiti");
					return 1;
				}
				if(listitem == 3)
				{
					SetPlayerCheckpoint(playerid,1483.3174,-1748.2933,15.4453,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite banka.");
					return 1;
				}
				if(listitem == 4)
				{
					SetPlayerCheckpoint(playerid,1798.6570,-1894.5203,13.4030,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite VM.");
					return 1;
				}
				if(listitem == 5)
				{
					SetPlayerCheckpoint(playerid,1178.5485,-1324.4526,14.1255,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite Ligonine.");
					return 1;
				}
				if(listitem == 6)
				{
					SetPlayerCheckpoint(playerid,1546.7813,-1673.4042,13.5626,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite Policija.");
					return 1;
				}
				if(listitem == 7)
				{
					SetPlayerCheckpoint(playerid,1653.6010,-1668.1217,21.4375,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite Hoteli.");
					return 1;
				}
				if(listitem == 8)
				{
					//SetPlayerCheckpoint(playerid,1399.6960,-2234.6807,13.5391,6.0);
					ShowPlayerDialog(playerid,669,DIALOG_STYLE_LIST,"Automobiliu turgus","Pigus automobiliai\nLowRiders\nSportiniai automobiliai\nLaivai","Gerai","Atsaukti");
					//SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite Turgu.");
					return 1;
				}
				if(listitem == 9)
				{
					SetPlayerCheckpoint(playerid,1641.1680,-2328.5908,13.5469,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite Oro Uosta.");
					return 1;
				}
				if(listitem == 10)
				{
					SetPlayerCheckpoint(playerid,1831.6837,-1682.0695,13.5466,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite Kluba.");
					return 1;
				}
				if(listitem == 11)
				{
					SetPlayerCheckpoint(playerid,1604.9871,-1468.1709,13.5717,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite Regitra.");
					return 1;
				}
				if(listitem == 12)
				{
					SetPlayerCheckpoint(playerid,1245.5969,-2035.1282,59.8378,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite Auto nuoma.");
					return 1;
				}
				if(listitem == 13)
				{
					SetPlayerCheckpoint(playerid,386.719,-1817.888,7.884,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite Zvejybos punkta.");
					return 1;
				}
				if(listitem == 14)
				{
					ShowPlayerDialog(playerid,670,DIALOG_STYLE_LIST,"Taisyklos","1\n2\n3","Rinktis","Atsaukti");
					return 1;
				}
				if(listitem == 15)
				{
					SetPlayerCheckpoint(playerid,1022.5022,-1121.6348,23.8720,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite Savivaldybe.");
					return 1;
				}
				if(listitem == 16)
				{
					SetPlayerCheckpoint(playerid,1315.3837,-898.9023,39.5781,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten rasite dazasvydi.");
					return 1;
				}
				*/
			}
			return 1;
		}
		if(dialogid==670)
		{
			if(response)
			{
				if(listitem == 0) SetPlayerCheckpoint(playerid,1017.7556,-917.3123,42.4931,6.0);
				if(listitem == 1) SetPlayerCheckpoint(playerid,1911.2146,-1775.0718,13.5318,6.0);
				if(listitem == 2) SetPlayerCheckpoint(playerid,2456.0039,-1460.7887,24.1489,6.0);
				SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite taisykla.");
			}
			return 1;
		}
		if(dialogid==667) //Rasti zmogu
		{
			if(response)
			{
				return cmd_kur(playerid,inputtext);
			}
		}
		if(dialogid==668) //Rasti nama
		{
			if(response)
			{
				new id = strval(inputtext);
				if(!IsNumeric(inputtext)){SendInfoMessage(playerid,"Prasome teisingai ivesti numeri."); return 1;}
				if(id >= MAX_HOUSES || id < 0 || (strval(hInfo[id][Name]) == 0 && strlen(hInfo[id][Name]) < 3)) return SendInfoMessage(playerid,"Tokio namo nera.");
				new x = hInfo[id][daugiabutis]-1;
				if(!hInfo[id][daugiabutis]) 
					SetPlayerCheckpoint(playerid,hInfo[id][iconx],hInfo[id][icony],hInfo[id][iconz],2);
				else 			
					SetPlayerCheckpoint(playerid,Daugiabuciai[x][dX],Daugiabuciai[x][dY],Daugiabuciai[x][dZ],5.0);
				SendInfoMessage(playerid,"Namo pozicija rodoma Radare!");
				return 1;
			}
		}
		if(dialogid==669)
		{
			if(response)
			{
				if(listitem==0)
				{
					SetPlayerCheckpoint(playerid,530.2449,-1291.5901,17.3530,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite Turgu.");
					return 1;			
				}
				if(listitem==1)
				{
					SetPlayerCheckpoint(playerid,2128.6824,-1138.1835,25.4295,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite Turgu.");
					return 1;
				} 
				if(listitem==2)
				{

					SetPlayerCheckpoint(playerid,1654.7229,-1098.2947,24.1436,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite Turgu.");
					return 1;
				}
				if(listitem == 3)
				{
					SetPlayerCheckpoint(playerid,723.4328,-1493.3035,1.9343,6.0);
					SendInfoMessage(playerid,"Mini mape matote raudona taskeli, vazuokite link jo, ten ir rasite Turgu.");
					return 1;
				}
			}
		}
		if(dialogid==4)
		{
			if(response)
			{
				if(listitem == 0)
				{//ShowPlayerDialog(playerid, 4, DIALOG_STYLE_LIST, "Saunamieji ginklai", "{FFFFFF}Rifle(50)  {33FF33}"#COST_RIFLE"€\n{FFFFFF}Shotgun(20)  {33FF33}"#COST_SHOTGUN"€\n{FFFFFF}9mm Pistol(100)  {33FF33}"#COST_PISTOL"€\n{FFFFFF}Brass knuckles {33FF33} "#COST_KNUCKLES"€", "Pirkti", "Nepirkti");
					if(GetPlayerMoneyA(playerid) < COST_RIFLE)
					{
						SendInfoMessage(playerid,"Truksta babkiu.");
						ShowPlayerDialog(playerid, 4, DIALOG_STYLE_TABLIST, "Saunamieji ginklai", SAUNAMIEJI_TEXT, "Pirkti", "Nepirkti");
						return 1;
					}
					if(boughtgun[playerid] == 2) 
						ProcessAchievement(playerid,78);
					boughtgun[playerid]=1;
					GivePlayerMoneyA(playerid,-COST_RIFLE);
					ActorServe(playerid); BusinessMoney(COST_RIFLE);
					GivePlayerWeaponEx(playerid,33,50);
					ShowPlayerDialog(playerid, 4, DIALOG_STYLE_TABLIST, "Saunamieji ginklai", SAUNAMIEJI_TEXT, "Pirkti", "Nepirkti");
					return 1;
				}
				if(listitem == 1)
				{
					if(GetPlayerMoneyA(playerid) < COST_SHOTGUN)
					{
						SendInfoMessage(playerid,"Truksta babkiu.");
						ShowPlayerDialog(playerid, 4, DIALOG_STYLE_TABLIST, "Saunamieji ginklai", SAUNAMIEJI_TEXT, "Pirkti", "Nepirkti");
						return 1;
					}
					if(boughtgun[playerid] == 2) 
						ProcessAchievement(playerid,78);
					boughtgun[playerid]=1;
					GivePlayerMoneyA(playerid,-COST_SHOTGUN);
					ActorServe(playerid); BusinessMoney(COST_SHOTGUN);
					GivePlayerWeaponEx(playerid,25,20);
					ShowPlayerDialog(playerid, 4, DIALOG_STYLE_TABLIST, "Saunamieji ginklai", SAUNAMIEJI_TEXT, "Pirkti", "Nepirkti");
					return 1;
				}
				if(listitem == 2)
				{
					if(GetPlayerMoneyA(playerid) < COST_PISTOL)
					{
						SendInfoMessage(playerid,"Truksta babkiu.");
						ShowPlayerDialog(playerid, 4, DIALOG_STYLE_TABLIST, "Saunamieji ginklai", SAUNAMIEJI_TEXT, "Pirkti", "Nepirkti");
						return 1;
					}
					if(boughtgun[playerid] == 2) 
						ProcessAchievement(playerid,78);
					boughtgun[playerid]=1;
					GivePlayerMoneyA(playerid,-COST_PISTOL);
					ActorServe(playerid); BusinessMoney(COST_PISTOL);
					GivePlayerWeaponEx(playerid,22,100);
					ShowPlayerDialog(playerid, 4, DIALOG_STYLE_TABLIST, "Saunamieji ginklai", SAUNAMIEJI_TEXT, "Pirkti", "Nepirkti");
					return 1;
				}
				if(listitem == 3)
				{
					if(GetPlayerMoneyA(playerid) < COST_KNUCKLES)
					{
						SendInfoMessage(playerid,"Truksta babkiu.");
						ShowPlayerDialog(playerid, 4, DIALOG_STYLE_TABLIST, "Saunamieji ginklai", SAUNAMIEJI_TEXT, "Pirkti", "Nepirkti");
						return 1;
					}

					GivePlayerMoneyA(playerid,-COST_KNUCKLES);
					ActorServe(playerid); BusinessMoney(COST_KNUCKLES);
					GivePlayerWeaponEx(playerid,1,1);
					ShowPlayerDialog(playerid, 4, DIALOG_STYLE_TABLIST, "Saunamieji ginklai", SAUNAMIEJI_TEXT, "Pirkti", "Nepirkti");
					return 1;
				}

			}
		}




		if(dialogid==3)
		{
			if(response)
			{
				if(listitem == 0)
				{ // #define UKINES_PREKES "{FFFFFF}Purskiamieji dazai(80){33FF33}  "#COST_PURSKIAMIEJI_DAZAI"€\n{FFFFFF}Kastuvas {33FF33}  "#COST_KASTUVAS"€\n{FFFFFF}Lazdele {33FF33}  "#COST_LAZDELE"€\n{FFFFFF}Golfo lazda {33FF33} "#COST_GOLFO_LAZDA"€\n{FFFFFF}Beisbolo lazda {33FF33} "#COST_BEISBOLO_LAZDA"€\n{FFFFFF}Geles {33FF33} "#COST_GELES"€\n{FFFFFF}Kiseninis peilis{33FF33}  "#COST_KISENINIS_PEILIS"€"
					if(GetPlayerMoneyA(playerid) < COST_PURSKIAMIEJI_DAZAI)
					{
						SendInfoMessage(playerid,"Truksta babkiu.");//{FFFFFF}{33FF33}
						ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, "Ukines prekes", UKINES_PREKES, "Pirkti", "Nepirkti");
						return 1;
					}
					if(GetPlayerWeapon(playerid) == 41 && GetPlayerAmmo(playerid) >= 9000)
						return SendInfoMessage(playerid,"Daugiau nepatempsi!");

					GivePlayerMoneyA(playerid,-COST_PURSKIAMIEJI_DAZAI);
					ActorServe(playerid); BusinessMoney(COST_PURSKIAMIEJI_DAZAI);
					GivePlayerWeaponEx(playerid,41,1000);
					ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, "Ukines prekes", UKINES_PREKES, "Pirkti", "Nepirkti");
					return 1;
				}
				if(listitem == 1)
				{
					if(GetPlayerMoneyA(playerid) < COST_KASTUVAS)
					{
						SendInfoMessage(playerid,"Truksta babkiu.");//{FFFFFF}{33FF33}
						ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, "Ukines prekes", UKINES_PREKES, "Pirkti", "Nepirkti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_KASTUVAS);
					ActorServe(playerid); BusinessMoney(COST_KASTUVAS);
					GivePlayerWeaponEx(playerid,6,1);
					ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, "Ukines prekes", UKINES_PREKES, "Pirkti", "Nepirkti");
					return 1;
				}
				if(listitem == 2)
				{
					if(GetPlayerMoneyA(playerid) < COST_LAZDELE)
					{
						SendInfoMessage(playerid,"Truksta babkiu.");//{FFFFFF}{33FF33}
						ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, "Ukines prekes", UKINES_PREKES, "Pirkti", "Nepirkti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_LAZDELE);
					ActorServe(playerid); BusinessMoney(COST_LAZDELE);
					GivePlayerWeaponEx(playerid,15,1);
					ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, "Ukines prekes", UKINES_PREKES, "Pirkti", "Nepirkti");
					return 1;
				}
				if(listitem == 3)
				{
					if(GetPlayerMoneyA(playerid) < COST_GOLFO_LAZDA)
					{
						SendInfoMessage(playerid,"Truksta babkiu.");//{FFFFFF}{33FF33}
						ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, "Ukines prekes", UKINES_PREKES, "Pirkti", "Nepirkti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_GOLFO_LAZDA);
					ActorServe(playerid); BusinessMoney(COST_GOLFO_LAZDA);
					GivePlayerWeaponEx(playerid,2,1);
					ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, "Ukines prekes", UKINES_PREKES, "Pirkti", "Nepirkti");
					return 1;
				}
				if(listitem == 4)
				{
					if(GetPlayerMoneyA(playerid) < COST_BEISBOLO_LAZDA)
					{
						SendInfoMessage(playerid,"Truksta babkiu.");//{FFFFFF}{33FF33}
						ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, "Ukines prekes", UKINES_PREKES, "Pirkti", "Nepirkti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_BEISBOLO_LAZDA);
					ActorServe(playerid); BusinessMoney(COST_BEISBOLO_LAZDA);
					GivePlayerWeaponEx(playerid,5,1);

					ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, "Ukines prekes", UKINES_PREKES, "Pirkti", "Nepirkti");
					return 1;
				}
				if(listitem == 5)
				{
					if(GetPlayerMoneyA(playerid) < COST_GELES)
					{
						SendInfoMessage(playerid,"Truksta babkiu.");//{FFFFFF}{33FF33}
						ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, "Ukines prekes", UKINES_PREKES, "Pirkti", "Nepirkti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_GELES);
					ActorServe(playerid); BusinessMoney(COST_GELES);
					GivePlayerWeaponEx(playerid,14,1);
					ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, "Ukines prekes", UKINES_PREKES, "Pirkti", "Nepirkti");
					return 1;
				}
				if(listitem == 6)
				{
					if(GetPlayerMoneyA(playerid) < COST_KISENINIS_PEILIS)
					{
						SendInfoMessage(playerid,"Truksta babkiu.");//{FFFFFF}{33FF33}
						ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, "Ukines prekes", UKINES_PREKES, "Pirkti", "Nepirkti");
						return 1;
					}
					GivePlayerMoneyA(playerid,-COST_KISENINIS_PEILIS);
					ActorServe(playerid); BusinessMoney(COST_KISENINIS_PEILIS);
					GivePlayerWeaponEx(playerid,4,1);
					ShowPlayerDialog(playerid, 3, DIALOG_STYLE_TABLIST, "Ukines prekes", UKINES_PREKES, "Pirkti", "Nepirkti");
					return 1;
				
				}
			}
		}




		// ShowPlayerDialog(playerid,2580,DIALOG_STYLE_LIST,"Dazniausiai uzduodami klausimai","1. Kodel musu serveris?\n2. Nuo ko pradeti?\n3. Ar serveryje yra autosave sistema?\n4. Negaunu kreditu. Ka daryti?\n5. Kaip palikti darba?","Gerai","Iseiti");

		if(dialogid==2580)
		{
			if(response)
			{
				if(listitem==0)
				{
					ShowPlayerDialog(playerid,2581,DIALOG_STYLE_MSGBOX,"Dazniausiai uzduodami klausimai","{FF0000}Kodel musu serveris?\n{FFFFFF}Galime pasigirti, kad musu serveris islaiko originaluma ir skiriasi nuo kitu serveriu.\n Tik cia zaidimas prasideda nuo 0. Tik cia galima pajusti kazk? panasaus i tikra gyvenima.\n Serveris pasizymi paprastumu - nieko nera per daug. Viskas tobulai subalansuota.","Gerai","Iseiti");
				}
				if(listitem==1)
				{
					new msg[512];
					format(msg,sizeof(msg),"{FF0000}Nuo ko pradeti?\n{FFFFFF}Zaidimas prasideda nuo visiskai apvalaus nulio, Los Santos traukiniu stotyje. Pradedant zaidima, zaidejai gauna 3,000 €, kad galetu pragyventi.\n");
					format(msg,sizeof(msg),"%sJeigu norite, kad sektusi, reiktu atlikti veiksmus protingai. Taip patariame mes: Kitoje traukiniu stoties puseje yra vairavimo mokykla. Issilaikykite teorini ir praktini testus.\nVeliau galite pradeti dirbti. Rasykite /darbai, spauskite darbai be pakvietimo > BMX'eris > Kur jis.",msg);
					ShowPlayerDialog(playerid,2581,DIALOG_STYLE_MSGBOX,"Dazniausiai uzduodami klausimai",msg,"Gerai","Iseiti");
				}
				if(listitem==2) 
				{
					ShowPlayerDialog(playerid,2581,DIALOG_STYLE_MSGBOX,"Dazniausiai uzduodami klausimai","{FF0000}Ar serveryje yra autosave sistema?\n{FFFFFF}Ne. Nor?dami neprarasti patirties ta?ku?, privalote saugoti ?aidim? hotelyje.","Gerai","Iseiti");
				}
				if(listitem==3)
				{
					ShowPlayerDialog(playerid,2581,DIALOG_STYLE_MSGBOX,"Dazniausiai uzduodami klausimai","{FF0000}Negaunu kreditu. Ka daryti?\n{FFFFFF}I?siunte SMS zinute ir negave atsako per 10min. nepulkite kabinti aki?? administracijai ar kurti temu forume.\n Bukite kantrus. Palaukite siek tiek ilgiau - keleta valandu.\n Jeigu vistiek jokios ?inios, tada prasome kreiptis i administracija. Patogiau butu, kad pagalbos kreiptumetes forume, pagalbos skyriuje.","Gerai","Iseiti");
				}
				if(listitem==4)
				{
					ShowPlayerDialog(playerid,2581,DIALOG_STYLE_MSGBOX,"Dazniausiai uzduodami klausimai","{FF0000}Kaip palikti darba?\n{FFFFFF}Pirmiausia, jums reikia uzeiti i uzdara patalpa(pvz.: i hotel?) ir viduje parasyti komanda /persirengti.\n Kai persirengsite i kasdienius drabuzius, Jums reikia uzlipti ant marskin?li?? paveikslelio, ten pat kur isidarbinote.","Gerai","Iseiti");
				}
			}
		}
		if(dialogid==2581)
		{
			if(!response) ShowPlayerDialog(playerid,2580,DIALOG_STYLE_LIST,"Dazniausiai uzduodami klausimai","1. Kodel musu serveris?\n2. Nuo ko pradeti?\n3. Ar serveryje yra autosave sistema?\n4. Negaunu kreditu. Ka daryti?\n5. Kaip palikti darba?","Gerai","Iseiti");
		}
		if(dialogid==2582)
		{
			if(response)
			{
				if(IsPlayerInAnyVehicle(playerid))
				{
					SetPlayerVirtualWorld(playerid,0);
					new vehicleid=GetPlayerVehicleID(playerid);
					SetVehicleVirtualWorld(vehicleid,0);
					if(listitem == 0)
					{
						SetPlayerInterior(playerid,0);
						LinkVehicleToInterior(vehicleid,GetPlayerInterior(playerid));
						SetVehiclePoz(vehicleid,1636.7281,-1687.4882,13.5242+2);
						PutPlayerInVehicle(playerid,vehicleid,0);
					}
					if(listitem == 1)
					{
						SetPlayerInterior(playerid,0);
						LinkVehicleToInterior(vehicleid,GetPlayerInterior(playerid));
						SetVehiclePoz(vehicleid,1537.8330,-1656.0118,13.5469+2);
						PutPlayerInVehicle(playerid,vehicleid,0);
					}
					if(listitem == 2)
					{
						SetPlayerInterior(playerid,0);
						LinkVehicleToInterior(vehicleid,GetPlayerInterior(playerid));
						SetVehiclePoz(vehicleid,1188.0259,-1330.4771,13.5607+2);
						PutPlayerInVehicle(playerid,vehicleid,0);
					}
					if(listitem == 3)
					{
						SetPlayerInterior(playerid,0);
						LinkVehicleToInterior(vehicleid,GetPlayerInterior(playerid));
						SetVehiclePoz(vehicleid,631.0367,-543.6788,16.3491+2);
						PutPlayerInVehicle(playerid,vehicleid,0);
					}
					if(listitem == 4)
					{
						SetPlayerInterior(playerid,0);
						LinkVehicleToInterior(vehicleid,GetPlayerInterior(playerid));
						SetVehiclePoz(vehicleid,2912.5159,-793.6180,11.0389);
						PutPlayerInVehicle(playerid,vehicleid,0);
					}
					if(listitem == 5)
					{
						SetPlayerInterior(playerid,0);
						LinkVehicleToInterior(vehicleid,GetPlayerInterior(playerid));
						SetVehiclePoz(vehicleid,1812.3293,-1882.6591,13.5781);
						PutPlayerInVehicle(playerid,vehicleid,0);
					}
				}
				else
				{
					SetPlayerVirtualWorld(playerid,0);
					if(listitem == 0)
					{
						SetPlayerInterior(playerid,0);
						SetPlayerPoz(playerid,1636.7281,-1687.4882,13.5242);
					}
					if(listitem == 1)
					{
						SetPlayerInterior(playerid,0);
						SetPlayerPoz(playerid,1537.8330,-1656.0118,13.5469);
					}
					if(listitem == 2)
					{
						SetPlayerInterior(playerid,0);
						SetPlayerPoz(playerid,1188.0259,-1330.4771,13.5607);
					}
					if(listitem == 3)
					{
						SetPlayerInterior(playerid,0);
						SetPlayerPoz(playerid,631.0367,-543.6788,16.3491);
					}
					if(listitem == 4)
					{
						SetPlayerInterior(playerid,0);
						SetPlayerPoz(playerid,2912.5159,-793.6180,11.0389);
					}
					if(listitem == 5)
					{
						SetPlayerInterior(playerid,0);
						SetPlayerPoz(playerid,1812.3293,-1882.6591,13.5781);
					}
					if(listitem == 6)
					{
						SetPlayerInterior(playerid,9);
						SetPlayerPoz(playerid,315.7553,1021.1771,1950.5634);
					}
					if(listitem == 7)
					{
						SetPlayerInterior(playerid,7);
						SetPlayerPoz(playerid,-1400.2383,-256.5094,1043.6348);
					}
					if(listitem == 8)
					{
						SetPlayerInterior(playerid,1);
						SetPlayerPoz(playerid,-838.3227,509.7492,1358.2678);
					}
					if(listitem == 9)
					{
						SetPlayerInterior(playerid,1);
						SetPlayerPoz(playerid,-1401.2244,106.6356,1032.2734);
					 }
					if(listitem == 10)
					{
						SetPlayerInterior(playerid,14);
						SetPlayerPoz(playerid,-1421.8290,1590.2783,1052.5313);
					}
					if(listitem == 11)
					{
						SetPlayerInterior(playerid,1);
						SetPlayerPoz(playerid,1.7759,28.9136,1199.5938);
					}
					if(listitem == 12)
					{
						SetPlayerInterior(playerid,3);
						SetPlayerPoz(playerid,973.7828,-9.7713,1001.1484);
					}
					if(listitem == 13)
					{
						SetPlayerInterior(playerid,3);
						SetPlayerPoz(playerid,1212.1489,-28.5388,1000.9531);
					}
					if(listitem == 14)
					{
						SetPlayerInterior(playerid,3);
						SetPlayerPoz(playerid,285.4655,174.7658,1007.1719);
					}
					if(listitem == 15)
					{
						SetPlayerInterior(playerid,3);
						SetPlayerPoz(playerid,-2638.2166,1406.7994,906.4609);
					}
					if(listitem == 16)
					{
						SetPlayerInterior(playerid,0);
						SetPlayerPoz(playerid,-1921.6140,3451.7737,22.3520);
					}
					if(listitem == 17)
					{
						SetPlayerInterior(playerid,0);
						SetPlayerPoz(playerid,824.9877,69.0823,1205.6963);
					}
					if(listitem == 18)
					{
						SetPlayerInterior(playerid,0);
						SetPlayerPoz(playerid,1477.9417,-2985.3330,4.4279);
					}
					if(listitem == 19)
					{
						SetPlayerInterior(playerid,1);
						SetPlayerPoz(playerid,1675.117,2812.955,-44.808);
					}
					if(listitem == 20)
					{
						SetPlayerInterior(playerid,1);
						SetPlayerPoz(playerid,1707.4130,-2521.1953,1025.5825);
					}
					if(listitem==21) {
						SetPlayerVirtualWorld(playerid, 20000);
						SetPlayerInterior(playerid,0);
						SetPlayerPoz(playerid,-173.4125,1119.1212,27.7546);
					}
					if(listitem==22) {
						SetPlayerInterior(playerid,5);
						SetPlayerPoz(playerid,1263.1504,-785.5751,1091.9063);
					}
					if(listitem==23)
					{
						SetPlayerInterior(playerid, 4);
						SetPlayerPoz(playerid,-1444.645507,-664.526000,1053.572998);
					}
					if(listitem==24)
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerPoz(playerid,1059.895996,2081.685791,10.820312);
					}
					if(listitem==25)
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerPoz(playerid,2230.8215,-13379.9551,6.0298);
					}
					if(listitem==26)
					{
						SetPlayerInterior(playerid, 10);
						SetPlayerPoz(playerid,2016.2699,1017.7790,996.8750 );
					}
					if(listitem==27)
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerPoz(playerid,957.4894,-3201.6340,13.4630);
					}
					if(listitem==28)
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerPoz(playerid,-3522.9160,1628.6731,13.9800+0.5);
					}
					if(listitem == 29)
					{
						SetPlayerInterior(playerid, 0);
						SetPlayerVirtualWorld(playerid, 20000);
						SetPlayerPoz(playerid,-1440.1460,-3509.1777,19.7825);
					}
					SetCameraBehindPlayer(playerid);
				}
			}
			return 1;
		}
		if(dialogid==7800)
		{
			if(response)
			{
				new query[256];
				format(query,sizeof(query),"SELECT * From `gangcars` WHERE `gang`=%i LIMIT %i,1",playerDB[playerid][pgang],listitem);
				mysql_function_query(SQL, query, true, "SQL_LoadGCar", "ii", playerid,playerDB[playerid][pgang]);
			}
		}
		if(dialogid==4858) // kaledu event
		{
			if(!response)
				return SendInfoMessage(playerid,"~r~Nejaugi LSG vel liks be Kaledu?");
			else
			{	
				ShowPlayerDialog(playerid,4859,DIALOG_STYLE_MSGBOX,"Kalëdø Senelis","{10A112}Kalëdø eventas 2017\n{FFFFFF}Keliauk á oro uostà ir áveik Senelio trasà!","Gerai!","");
				SetPlayerCheckpoint(playerid, 1976.8904,-2553.4766,13.5469,10.0);
				//LoadChristmasEvent(playerid,0);
			}
		}
		if(dialogid==4860)
		{
			if(!response)
				SendClientMessage(playerid, WHITE, " * Sugráþk kai apsispresi!");
			else
			{
				if(listitem < 3)
					return ShowPlayerDialog(playerid,4860,DIALOG_STYLE_LIST,"Kalëdø Senelis","Oho! Panaðu, kad Senelio rogës tau nesukëlë jokiø problemø!\nÐirdingai dëkoju tau uþ pagalbà, o dabar noriu atsidëkoti tau:\nIðsirink vienà ið ðiø dovanø:\n{FFFF99}Kalëdø Senelio saldainiø deþutë\n{0099FF}Rimti þaisliukai\n{FF0000}Senelio iðmintis(1000 XP)","Taip","Ne");
				else if(listitem == 3) // saldainiu dezute
				{
					if(GetPlayerScore(playerid) < 2000)
						return SendInfoMessage(playerid,"~r~Si priza gali atsiimti tik nuo 2000XP.");
					PlayerPlaySound(playerid,4201,0,0,0);
					playerDB[playerid][lsd]+=10;
					playerDB[playerid][amfetaminas]+=10;
					playerDB[playerid][ratai]+=10;
					ChristmasQuery(playerid,0);
					ShowPlayerDialog(playerid,4859,DIALOG_STYLE_MSGBOX,"Kalëdø Senelis","{10A112}Kalëdø eventas 2017\nTu gavai:\n{FF0000}o 10vnt. LSD\no 10vnt. Ratu\no 10vnt. Amfetamino\n{FFFFFF}Aèiû tau uþ dalyvavimà! LSG Administracija linki paèiø jaukiausiø ir smagiausiø ðvenèiø!","Aèiû!","");
				}
				else if(listitem == 4) // rimti zaisliukai
				{
					if(GetPlayerScore(playerid) < 2000)
						return SendInfoMessage(playerid,"~r~Si priza gali atsiimti tik nuo 2000XP.");
					GivePlayerWeaponEx(playerid,24,1000);
					GivePlayerWeaponEx(playerid,27,500);
					GivePlayerWeaponEx(playerid,34,100);
					PlayerPlaySound(playerid,4201,0,0,0);
					ChristmasQuery(playerid,1);
					ShowPlayerDialog(playerid,4859,DIALOG_STYLE_MSGBOX,"Kalëdø Senelis","{10A112}Kalëdø eventas 2017\nTu gavai:\n{FF0000}o 1000 kulkø Desert Eagle\no 500 kulkø CSG\no 100 kulkø AWP\n{FFFFFF}Aèiû tau uþ dalyvavimà! LSG Administracija linki paèiø jaukiausiø ir smagiausiø ðvenèiø!","Aèiû!","");
				}
				else if(listitem == 5) //1000 xp
				{
					if(GetPlayerScore(playerid) < 200)
						return SendInfoMessage(playerid,"~r~Si priza gali atsiimti tik nuo 200XP.");
					SetPlayerScore(playerid, GetPlayerScore(playerid)+1000);

					ShowPlayerDialog(playerid,4859,DIALOG_STYLE_MSGBOX,"Kalëdø Senelis","{10A112}Kalëdø eventas 2017\nTu gavai:\n{FF0000}o 1000 XP taðkø\n{FFFFFF}Aèiû tau uþ dalyvavimà! LSG Administracija linki paèiø jaukiausiø ir smagiausiø ðvenèiø!","Aèiû!","");
					ChristmasQuery(playerid,2);
					SavePlayerData(playerid,false);
				}
			}
			return 1;
		}
		if(dialogid==2) //Jei dialogid bus lygus 2
		{
			if(response) //Jei paspaude mygtuka taip
			{
				if(listitem == 0)
				{
					if(GetPlayerMoneyA(playerid)<COST_COLA){ // cola
					SendInfoMessage(playerid,"Neturite tiek pinigu");return 1;}
					GivePlayerMoneyA(playerid, -COST_COLA);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
					SendInfoMessage(playerid,"Nusipirkote kolos.");
					if(IsInBiz(playerid))
					{	
						ActorServe(playerid);
						BusinessMoney(COST_COLA);
					}
				}
				if(listitem == 1)
				{
					if(GetPlayerMoneyA(playerid)<COST_SPRITE){ // spraitas
					SendInfoMessage(playerid,"Neturite tiek pinigu");return 1;}
					GivePlayerMoneyA(playerid, -COST_SPRITE);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
					SendInfoMessage(playerid,"Nusipirkote spraito.");
					if(IsInBiz(playerid))
					{	
						ActorServe(playerid);
						BusinessMoney(COST_SPRITE);
					}
				}
				if(listitem == 2)
				{
					if(GetPlayerMoneyA(playerid)<COST_SAMPANAS){ // Sampanas
					SendInfoMessage(playerid,"Neturite tiek pinigu");return 1;}
					GivePlayerMoneyA(playerid, -COST_SAMPANAS);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
					SendInfoMessage(playerid,"Nusipirkote sampano.");
					if(IsInBiz(playerid))
					{	
						ActorServe(playerid);
						BusinessMoney(COST_SAMPANAS);
					}
				}
				if(listitem == 3)
				{
					if(GetPlayerMoneyA(playerid)<COST_VYNAS){ // vynas
					SendInfoMessage(playerid,"Neturite tiek pinigu");return 1;}
					GivePlayerMoneyA(playerid, -COST_VYNAS);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
					SendInfoMessage(playerid,"Nusipirkote vyno.");
					if(IsInBiz(playerid))
					{	
						ActorServe(playerid);
						BusinessMoney(COST_VYNAS);
					}
				}
				if(listitem == 4)
				{
					if(GetPlayerMoneyA(playerid)<COST_ALUS){ // alus
					SendInfoMessage(playerid,"Neturite tiek pinigu");return 1;}
					GivePlayerMoneyA(playerid, -COST_ALUS);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
					SendInfoMessage(playerid,"Nusipirkote alaus.");
					if(IsInBiz(playerid))
					{	
						ActorServe(playerid);
						BusinessMoney(COST_ALUS);
					}
				}
				if(listitem == 5)
				{

					if(GetPlayerMoneyA(playerid)<COST_VODKA){ // vodka
					SendInfoMessage(playerid,"Neturite tiek pinigu");return 1;}
					GivePlayerMoneyA(playerid, -COST_VODKA);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
					SendInfoMessage(playerid,"Nusipirkote vodkos.");
					if(IsInBiz(playerid))
					{	
						ActorServe(playerid);
						BusinessMoney(COST_VODKA);
					}
				}
				if(listitem == 6)
				{
					if(GetPlayerMoneyA(playerid)<COST_BRENDIS){ // brendis
					SendInfoMessage(playerid,"Neturite tiek pinigu.");return 1;}
					GivePlayerMoneyA(playerid, -COST_BRENDIS);
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
					SendInfoMessage(playerid,"Nusipirkote brendzio.");
					if(IsInBiz(playerid))
					{	
						ActorServe(playerid);
						BusinessMoney(COST_BRENDIS);
					}

				}
			}
			return 1;
		}
		case DIALOGID-3:
		{
			if(response)
			{
				if(listitem == 0)
				{
					ShowPlayerDialog(playerid,DIALOGID+31,DIALOG_STYLE_INPUT,"Rasyti","Irasykite tema.\nDaugiausia simboliu: 100.","Gerai","Atgal");
					return 1;
				}
				else
				{
					//mysql_real_escape_string(inputtext,inputtext);
					new query[128];
					format(query,sizeof(query),"DELETE FROM `Emails` WHERE `ID`=%i AND UPPER(`Reciever`)=UPPER('%s') LIMIT 1",MkP[playerid],ReturnName(playerid));
					mysql_query(query);
					SendInfoMessage(playerid,"Zinute istrinta!");
					ShowEmail(playerid);
					return 1;
				}
			}
			else ShowEmail(playerid);
			return 1;
		}
		case DIALOGID-1: // reply/delete
		{
			if(response)
			{
				ShowPlayerDialog(playerid,DIALOGID-3,DIALOG_STYLE_LIST,"Veiksmai","Atsakyti\nIstrinti","Gerai","Atgal");
				return 1;
			}
			else
			{
				ShowEmail(playerid);
				return 1;
			}
		}
		case DIALOGID-2:
		{
			ShowEmail(playerid);
			return 1;
		}
		case DIALOGID+1: // inbox
		{
			if(response)
			{
				//mysql_real_escape_string(inputtext,inputtext);
				new result[1024],
					name[MAX_PLAYER_NAME];

				GetPlayerName(playerid,name,MAX_PLAYER_NAME);
				format(result,sizeof(result),"SELECT `ID`,`Sender`,`Subject`,`Time`,`Date`,`New`,`MK`,`Text` FROM `Emails` WHERE UPPER(`Reciever`)=UPPER('%s') ORDER BY `DateTime` DESC LIMIT %i,1",name,listitem);
				
				mysql_function_query(SQL, result, true, "SQL_Inbox", "i", playerid);
			}
			else ShowEmail(playerid);
			return 1;
		}
		case DIALOGID+2: // outbox
		{
			if(response)
			{
				//mysql_real_escape_string(inputtext,inputtext);
				new result[1024],
					name[MAX_PLAYER_NAME];

				GetPlayerName(playerid,name,MAX_PLAYER_NAME);
				format(result,sizeof(result),"SELECT `Reciever`,`Subject`,`Time`,`Date`,`Text` FROM `Emails` WHERE `Sender`='%s' ORDER BY `DateTime` DESC LIMIT %i,1",name,listitem);
				//mysql_query(result);
				mysql_function_query(SQL, result, true, "SQL_Outbox", "i", playerid);

			}
			else ShowEmail(playerid);
			return 1;
		}
		case DIALOGID: // main dialog
		{
			if(response)
			{
				switch(listitem)
				{
					case 0: // inbox
					{
					//	mysql_real_escape_string(inputtext,inputtext);
						new 
							name[MAX_PLAYER_NAME],
							QR[256];
						GetPlayerName(playerid,name,MAX_PLAYER_NAME);
						format(QR,sizeof(QR),"SELECT `Sender`,`Subject`,`DateTime`,`New` FROM `Emails` WHERE UPPER(`Reciever`)=UPPER('%s') ORDER BY `DateTime` DESC LIMIT 20",name);
						mysql_function_query(SQL, QR, true, "SQL_Gautieji", "i", playerid);

					}
					case 1: // outbox
					{
						//mysql_real_escape_string(inputtext,inputtext);
						new 
							name[MAX_PLAYER_NAME],
							QR[256];

						GetPlayerName(playerid,name,MAX_PLAYER_NAME);
						format(QR,sizeof(QR),"SELECT `Reciever`,`Subject`,`DateTime`,`New` FROM `Emails` WHERE `Sender`='%s' ORDER BY `DateTime` DESC LIMIT 20",name);
						//mysql_query(QR);
						mysql_function_query(SQL, QR, true, "SQL_Issiustieji", "i", playerid);
						
					}
					case 2: // compose
					{
						if(GetTickCount() - LastEmail[playerid] < 30*1000)
							return SendInfoMessage(playerid,"~r~Emailus gali siusti tik kas 30 sekundziu");
						ShowPlayerDialog(playerid,DIALOGID+30,DIALOG_STYLE_INPUT,"Sukurti","Áraðykite gavëjo vardà (formatas - Vardas_Pavarde).\nJei norite siøsti masinæ þinutæ, naudokite:\n\r@g - gaujos nariams (gali naudoti tik gaujos savininkas)\n\r@d - darbuotojams (gali naudoti tik direktorius)\n\r@a - administratoriams (gali naudoti visi)","Gerai","Atsaukti");
						return 1;
					}
				}
			}
		}
		case DIALOGID+30: // compose 1
		{
			if(response)
			{
				mysql_real_escape_string(inputtext,inputtext,_,256);
				if(strlen(inputtext) > 50 || strlen(inputtext) < 2 || strfind(inputtext,"\n",true) != -1 || strfind(inputtext,"{",true) != -1 || strfind(inputtext,"}",true) != -1 || strfind(inputtext,"|",true) != -1 ) return ShowPlayerDialog(playerid,DIALOGID+30,DIALOG_STYLE_INPUT,"Kurti","Irasykite gavejo varda.\nFormatas - Vardas_Pavarde\nMasine zinute:\n\r@g - gaujos nariams(gali naudoti tik gaujos savininkas)\n\r@d - darbuotojams(gali naudoti tik direktorius)\nNetinkamas formatas!","Gerai","Atgal");
				format(RecieverP[playerid],50,"%s", inputtext);
				ShowPlayerDialog(playerid,DIALOGID+31,DIALOG_STYLE_INPUT,"Kurti","Irasykite tema.\nSimboliu limitas: 100.","Gerai","Atgal");
				return 1;
			}
			else
			{
			   ShowEmail(playerid);
			   return 1;
			}
		}
		case DIALOGID+31: // compose 2
		{
			
			if(response)
			{
				mysql_real_escape_string(inputtext,inputtext,_,256);
				if(strlen(inputtext) > 98 || strlen(inputtext) < 2 || strfind(inputtext,"\n",true) != -1 || strfind(inputtext,"{",true) != -1 || strfind(inputtext,"}",true) != -1 || strfind(inputtext,"|",true) != -1) return ShowPlayerDialog(playerid,DIALOGID+31,DIALOG_STYLE_INPUT,"Kurti","Irasykite tema.\nSimboliu limitas: 100.\nNetinkamas formatas!","Gerai","Atgal");
				format(SubjectP[playerid],100,"%s", inputtext);
				SetPVarInt(playerid, "MsgLines", 0);
				SetPVarString(playerid, "MsgText", "");
				ShowPlayerDialog(playerid,DIALOGID+32,DIALOG_STYLE_INPUT,"Kurti","Èia galite raðyti þinutæ.\nEiluèiø limitas: 10.\nParaðæ þinutæ turësite progà dar kartà jà perþiûrëti prieð iðsiunèiant.","Enter","Atgal");
				return 1;
			}
			else
			{
			   ShowEmail(playerid);
			   return 1;
			}
		}
		case DIALOGID+32: // compose 3
		{
			if(response)
			{
				mysql_real_escape_string(inputtext,inputtext,_,256);
				new msg[4096];
				format(msg,sizeof(msg),"Èia galite raðyti þinutæ.\nEiluèiø limitas: 10.\nParaðæ þinutæ turësite progà dar kartà jà perþiûrëti prieð iðsiunèiant.");
				new textaz[2600];
				GetPVarString(playerid, "MsgText", textaz, 2600);
				if(strlen(inputtext) > 255)
				{
					format(msg,sizeof(msg),"%s\n{FF0000}Ði eilutë per ilga!\n\n{FFFFFF}%s\n",msg,textaz);
					return ShowPlayerDialog(playerid,DIALOGID+32,DIALOG_STYLE_INPUT,"Kurti",msg,"Enter","Baigti");
				}
				/*else if(strlen(inputtext) < 3)
				{
					format(msg,sizeof(msg),"%s\n{FF0000}Ði eilutë per trumpa!\n\n{FFFFFF}%s",msg,textaz);
					return ShowPlayerDialog(playerid,DIALOGID+32,DIALOG_STYLE_INPUT,"Kurti",msg,"Enter","Baigti");
				}*/
				if(strfind(inputtext,"\n",true) != -1 ||strfind(inputtext,"~",true) != -1 || strfind(inputtext,"{",true) != -1 || strfind(inputtext,"}",true) != -1 || strfind(inputtext,"|",true) != -1)
				{
					format(msg,sizeof(msg),"%s\n{FF0000}Þinutëje yra netinkamø simboliø!\n\n{FFFFFF}%s\n",msg,textaz);
					return ShowPlayerDialog(playerid,DIALOGID+32,DIALOG_STYLE_INPUT,"Kurti",msg,"Enter","Baigti");
				}
				new lines = GetPVarInt(playerid, "MsgLines");
				if( lines >= 10)
				{
					format(msg,sizeof(msg),"%s\n{FF0000}Þinutëje pasiektas eiluèiø limitas!\n\n{FFFFFF}%s\n",msg,textaz);
					return ShowPlayerDialog(playerid,DIALOGID+32,DIALOG_STYLE_INPUT,"Kurti",msg,"Enter","Baigti");
				}
				SetPVarInt(playerid, "MsgLines", lines+1);

				format(textaz,sizeof(textaz),"%s\n%s",textaz,inputtext);
				SetPVarString(playerid, "MsgText", textaz);

				format(msg,sizeof(msg),"%s\n\n{FFFFFF}%s\n",msg,textaz);
				return ShowPlayerDialog(playerid,DIALOGID+32,DIALOG_STYLE_INPUT,"Kurti",msg,"Enter","Baigti");

				
			}
			else
			{
				if(GetPVarInt(playerid, "MsgLines") == 0)
				{
					ShowEmail(playerid);
		  			return 1;
				}
				new result[4096];
				new textaz[2600];
				GetPVarString(playerid, "MsgText", textaz, 2600);


				new day,year,month;
				getdate(year,month, day);
				new hour,minute;
				gettime(hour, minute);
				format(result,sizeof(result),"{FFFFFF}Data:{FF9933} %i-%i-%i{FFFF33} %02d:%02d\n{FFFFFF}Gavëjas:{FFFF33} %s\n{FFFFFF}Tema: %s\n\n\n%s",day,month,year,hour,minute,RecieverP[playerid],SubjectP[playerid],textaz);

				ShowPlayerDialog(playerid, DIALOGID+34, DIALOG_STYLE_MSGBOX, "Perþiûra", result, "Siøsti", "Atðaukti");

			}

		}
		case DIALOGID+34:
		{
			if(response)
			{
				new
					query[2048],
					name[MAX_PLAYER_NAME];

				GetPlayerName(playerid,name,MAX_PLAYER_NAME);
				if(RecieverP[playerid][0] == '@')
				{
					if(RecieverP[playerid][1] == 'd' || RecieverP[playerid][1] == 'D') 
					{
						new lol=-1,
							lol2=-1,
							lol3=-1,
							lol4=-1,
							lol5=-1;
						if(playerDB[playerid][plead] == 2){ lol = 2; lol2=93; } // medikai
						else if(playerDB[playerid][plead] == 3){ lol = 3; lol2 = 20; lol3 = 39;} // transportas
						else if(playerDB[playerid][plead] == 5){ lol = 41; lol2 = 44;} // furistai
						else if(playerDB[playerid][plead] == 6){ lol = 6; lol2 = 28;} // autospeciai
						else if(playerDB[playerid][plead] == 66){ lol = 66;} // gaisrininkai
						else if(playerDB[playerid][plead] == 70){ lol = 70; lol2 = 73; lol3 = 72;} // autoklubas
						else if(playerDB[playerid][plead] == 80){ lol = 80; lol2 = 81; lol3 = 83; lol4 = 84; lol5=82;} // teisesauga
						else if(playerDB[playerid][plead] == 50){ lol = 50;} // skelbejai
						else if(playerDB[playerid][plead] == 98){ lol = 71;} // baikeriai
						else if(playerDB[playerid][plead] == 58){ lol = 58;} // vagys
						else if(playerDB[playerid][plead] == 90){ lol = 31; lol2=32;} // dealeriai 
						else if(playerDB[playerid][plead] == 34){ lol = 34; }
						else if(playerDB[playerid][plead] == 60){ lol = 60; }
						else return SendInfoMessage(playerid,"Tu ne direktorius!");
						format(query,150,"SELECT `Name` From `Account` WHERE (`Job`=%d or `Job`=%d or `Job`=%d or `Job`=%d or `Job`=%d) and `Name` != '%s'",lol,lol2,lol3,lol4,lol5,name);
						//mysql_query(query);
						mysql_function_query(SQL, query, true, "SQL_SendMass", "i", playerid);
						
						return 1;
					}
					else if(RecieverP[playerid][1] == 'g' || RecieverP[playerid][1] == 'G') 
					{
						new bolas=0;
						for(new i; i<MAX_FAMILY;i++)
						{
							if(0==strcmp(FamilyInfo[i][FamilyLeader],name,false) || 0==strcmp(FamilyInfo[i][FamilySubstitute],name,false) )
								bolas=1;
						}	
						if(!bolas) return SendInfoMessage(playerid,"Jus ne gaujos vadas!");
						
						format(query,150,"SELECT `Name` From `Account` WHERE `Gangas`=%i and `Name` != '%s'",playerDB[playerid][pgang],name);
						mysql_function_query(SQL, query, true, "SQL_SendMass", "i", playerid);
						return 1;

					}
					else if(RecieverP[playerid][1] == 'a' || RecieverP[playerid][1] == 'A') 
					{			
						format(query,150,"SELECT `Name` From `Account` WHERE `Adminas`=1 and `Name` != '%s'",name);
						mysql_function_query(SQL, query, true, "SQL_SendMass", "i", playerid);
						return 1;
					}
					else
						return SendInfoMessage(playerid,"Neteisingas gavejo kodas!");
				}


				format(query,sizeof(query),"SELECT `Name` FROM `Account` WHERE `Name`='%s'",RecieverP[playerid]);
				mysql_function_query(SQL, query, true, "SQL_MailCheck", "i", playerid);
				return 1;
			}
			else
			{
				SetPVarInt(playerid, "MsgLines", 0);
				SetPVarString(playerid, "MsgText", "");
				ShowPlayerDialog(playerid,DIALOGID+32,DIALOG_STYLE_INPUT,"Kurti","Èia galite raðyti þinutæ.\nEiluèiø limitas: 10.\nParaðæ þinutæ turësite progà dar kartà jà perþiûrëti prieð iðsiunèiant.","Enter","Atgail");
			}
		}
		if(dialogid==16733)
		{
			if(response)
			{
				HandleValdymoPunktoDialog(playerid, listitem);
			}
		}
		if(dialogid==16734)
		{
			HandleValdymoPunktas(playerid);
		}
		if(dialogid==16735)
		{
			if(response)
			{
				HandleValdymoPunktoDialog(playerid, 2);
			}
			else
			{
				HandleValdymoPunktas(playerid);
			}
		}
		if(dialogid==16736)
		{
			if(response)
			{
				StartTyrimas(playerid, listitem);
			}
			else
			{
				HandleValdymoPunktas(playerid);
			}
		}
		if(dialogid==16737)
		{
			if(response)
			{
				TakeTyrimoItem(playerid, listitem);
			}
			else
			{
				HandleValdymoPunktas(playerid);
			}
		}
		if(dialogid==14305)
		{
			if(response) 
			{
				HandleModsResponse(playerid, listitem);
			}
			else 
			{
				SendInfoMessage(playerid,"~r~Kalibravimas atsauktas");
			}
			return 1;
		}
		if(dialogid==14306)
		{
			ShowModsDialog(playerid);
			return 1;
		}
		if(dialogid==2790) 
		{
			if(response) 
			{
				if(DLItemID == 0) 
				{
					OpenWorldsMenu(playerid);
				}
				else if(DLItemID == 1)
				{
					cmd_saugoti(playerid, "");
				}
				else if(DLItemID == 2)
				{
					cmd_spyna(playerid, "");
				}
				else if(DLItemID == 3)
				{
					cmd_pavalgyti(playerid, "");
				}
				else if(DLItemID == 4)
				{
					cmd_paimti(playerid, "");
				}
				else if(DLItemID == 5)
				{
					cmd_padeti(playerid, "");
				}
				else if(DLItemID == 6)
				{
					cmd_baldai(playerid, "");
				}
				else if(DLItemID == 7)
				{
					cmd_radijan(playerid, "");
				}
				else if(DLItemID == 8)
				{
					ShowPlayerDialog(playerid, 2791, DIALOG_STYLE_LIST, "Remontas", "Kelti namo lygá\nMaþinti namo lygá", "Gerai", "Atgal");
				}
				else if(DLItemID == 9)
				{
					cmd_dazyti(playerid, "");
				}
				else if(DLItemID == 10)
				{
					cmd_leistirengti(playerid, "");
				}
				else if(DLItemID == 11)
				{
					ShowPlayerDialog(playerid, 2792, DIALOG_STYLE_LIST, "Augalai", "Sodinti kanapes\nLaistyti\nNuimti derliø", "Gerai", "Atgal");
				}
			}
		}
		if(dialogid == 2791) 
		{
			if(response)
			{
				if(listitem == 0)
				{
					cmd_remontas(playerid, "");
				}
				else
				{
					cmd_lvl(playerid, "");
				}
			}
			else
			{
				OpenHouseMenu(playerid);
			}
		}
		if(dialogid == 2792)
		{
			if(response)
			{
				if(listitem == 0)
				{
					cmd_sodinti(playerid, "");
				}
				if(listitem == 1)
				{
					cmd_laistyti(playerid, "");
				}
				if(listitem == 2)
				{
					cmd_derlius(playerid, "");
				}
			}
			else
			{
				OpenHouseMenu(playerid);
			}
		}
		if(dialogid == 2793)
		{
			if(response)
			{
				HandleInHouseDialog(playerid, DLItemID);
			}
			else
			{
				OpenHouseMenu(playerid);
			}
		}
		if(dialogid == 2974)
		{
			if(response)
			{
				HandleInWorldDialog(playerid, 2974, DLItemID);
			}
		}
		if(dialogid == 2795)
		{
			if(response)
			{
				HandleInWorldDialog(playerid, 2795, listitem);
			}
			else 
			{
				OpenInWorldMenu(playerid);
			}
		}
		if(dialogid == 2796)
		{
			if(response)
			{
				HandleWorldNameChange(playerid, inputtext);
			}
			else
			{
				OpenInWorldMenu(playerid);
			}
		}
		if(dialogid == 2797)
		{
			if(response)
			{
				HandleInWorldDialog(playerid, 2797, listitem);
			}
			else
			{
				OpenInWorldMenu(playerid);
			}
		}
		if(dialogid == 2798)
		{
			if(response)
			{
				HandleInWorldDialog(playerid, 2798, listitem);
			}
			else
			{
				OpenInWorldMenu(playerid);
			}
		}
		if(dialogid == 2799)
		{
			if(response)
			{
				HandleInWorldDialog(playerid, 2799, listitem);
			}
			else
			{
				OpenInWorldMenu(playerid);
			}
		}
		if(dialogid == 2800)
		{
			if(response)
			{
				HandleInWorldDialog(playerid, 2800, listitem);
			}
			else
			{
				HandleInWorldDialog(playerid, 2974, 2); // statybos
			}
		}
		if(dialogid == 2801)
		{
			if(response)
			{
				HandlePlaceObject(playerid, strval(inputtext));
			}
			else
			{
				HandleInWorldDialog(playerid, 2974, 2); // statybos
			}
		}
		if(dialogid == 2802)
		{
			if(response)
			{
				ShowItemCatalog(playerid, inputtext);
			}
			else
			{
				HandleInWorldDialog(playerid, 2974, 2); // statybos
			}
		}
		if(dialogid == 2803)
		{
			if(response)
			{
				HandleInWorldDialog(playerid, 2803, listitem);
			}
			else
			{
				HandleInWorldDialog(playerid, 2974, 2); // statybos
			}
		}
		if(dialogid == 2804) // pagal id
		{
			if(response)
			{
				HandleObjectSelectionById(playerid, inputtext);
			}
			else
			{
				HandleInWorldDialog(playerid, 2974, 2); // statybos
			}
		}
		if(dialogid == 2805)
		{
			if(response)
			{
				SetStatybuLeidimas(playerid,inputtext);
			}
			else
			{
				HandleInWorldDialog(playerid, 2974, 3); // nustatymai
			}
		}
		if(dialogid == 2806)
		{
			if(response)
			{
				HandleInWorldDialog(playerid, 2806, listitem); // cars
			}
			else
			{
				OpenInWorldMenu(playerid);
			}
		}
		if(dialogid == 2807)
		{
			if(response)
			{
				HandleInWorldDialog(playerid, 2807, listitem);
			}
			else
			{
				OpenInWorldMenu(playerid);
			}
		}
		if(dialogid == 2808)
		{
			if(response)
			{
				HandleNewParam(playerid, inputtext);
			}
			else
			{
				OpenInWorldMenu(playerid);
			}
		}
		if(dialogid == 2975)
		{
			if(response)
			{
				HandleInWorldDialog(playerid, 2975, DLItemID);
			}
			else
			{
				OpenInWorldMenu(playerid);
			}
		}
		if(dialogid == 2976)
		{
			if(response)
			{
				HandleInWorldDialog(playerid, 2976, listitem);
			}
			else
			{
				OpenInWorldMenu(playerid);
			}
		}
		if(dialogid == 2977)
		{
			if(response)
			{
				HandleWorldTextDialog(playerid, 2977, inputtext);
			}
			else
			{
				OpenInWorldMenu(playerid);
			}
		}
		if(dialogid == 2978)
		{
			if(response)
			{
				HandleWorldTextDialog(playerid, 2978, inputtext);
			}
			else
			{
				OpenInWorldMenu(playerid);
			}
		}
		if(dialogid == 2979)
		{
			if(response)
			{
				HandleWorldTextDialog(playerid, 2979, inputtext);
			}
			else
			{
				OpenInWorldMenu(playerid);
			}
		}

	// ============================================================
	// SOLO FEATURES â€” DIALOG HANDLERS
	// ============================================================

	if(dialogid == DIALOG_MORTGAGE)
	{
		if(!response) { DeletePVar(playerid,"MortgageBizID"); return 1; }
		new bizid = GetPVarInt(playerid,"MortgageBizID");
		DeletePVar(playerid,"MortgageBizID");
		if(bizid < 0 || bizid >= MAX_BUSINESSES) return 1;
		if(BusinessInfo[bizid][bOwned]) return SendInfoMessage(playerid,"Verslas jau parduotas!");
		new price       = BusinessInfo[bizid][bPrice];
		new downPayment = price / 5;
		new mortgage    = price - downPayment;
		if(GetPlayerMoneyA(playerid) < downPayment)
			return SendInfoMessage(playerid,"~r~Neuztenka pinigu pradinei imokai!");
		GivePlayerMoneyA(playerid, -downPayment);
		BusinessInfo[bizid][bOwned]      = 1;
		BusinessInfo[bizid][bMokesciai]  = 14;
		format(BusinessInfo[bizid][bOwner], MAX_PLAYER_NAME, ReturnName(playerid));
		g_HasMortgage[bizid]       = true;
		g_MortgageRemaining[bizid] = mortgage;
		new string[128];
		format(string,sizeof(string),VERSLAS_NEPARDUODAMAS,
			BusinessInfo[bizid][bName],BusinessInfo[bizid][bOwner],
			GetBussinessType(BusinessInfo[bizid][bType]));
		DestroyDynamic3DTextLabel(businesstext[bizid]);
		businesstext[bizid] = CreateDynamic3DTextLabel(string,0x00BC00FF,
			BusinessInfo[bizid][bEnterX],BusinessInfo[bizid][bEnterY],
			BusinessInfo[bizid][bEnterZ],40.0,_,_,1);
		new msg[128];
		format(msg,sizeof(msg)," * Isigiojote versla su paskola! Liko grazinti: %d EUR (automatiskai is pelno).",mortgage);
		SendClientMessage(playerid,0x00FF00FF,msg);
		ProcessAchievement(playerid,45);
		return 1;
	}
	if(dialogid == DIALOG_KAZINO_MAIN)
	{
		if(!response) return 1;
		if(listitem == 0)
			ShowPlayerDialog(playerid, DIALOG_KAZINO_BET, DIALOG_STYLE_LIST,
				"Slot Machine - Statymas",
				"100 EUR\n500 EUR\n1,000 EUR\n5,000 EUR\n10,000 EUR",
				"Losit","Atgal");
		else
			ShowPlayerDialog(playerid, DIALOG_DICE_BET, DIALOG_STYLE_LIST,
				"Kauliukai - Pasirinkite",
				"100 EUR - Didelis (7-12)\n100 EUR - Mazas (2-6)\n500 EUR - Didelis (7-12)\n500 EUR - Mazas (2-6)\n1000 EUR - Didelis (7-12)\n1000 EUR - Mazas (2-6)",
				"Mesti","Atgal");
		return 1;
	}
	if(dialogid == DIALOG_KAZINO_BET)
	{
		if(!response) { cmd_kazino(playerid,""); return 1; }
		static const SlotBets[] = {100,500,1000,5000,10000};
		new bet = SlotBets[listitem];
		if(GetPlayerMoneyA(playerid) < bet)
			return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
		new s1=SlotReel(), s2=SlotReel(), s3=SlotReel();
		new mult = SlotMultiplier(s1,s2,s3);
		new msg[512];
		format(msg,sizeof(msg),
			"%s%s%s  |  %s%s%s  |  %s%s%s\n\n",
			g_SlotColors[s1],g_SlotSymbols[s1],"{FFFFFF}",
			g_SlotColors[s2],g_SlotSymbols[s2],"{FFFFFF}",
			g_SlotColors[s3],g_SlotSymbols[s3],"{FFFFFF}");
		if(mult > 0)
		{
			new winnings = bet * mult;
			GivePlayerMoneyA(playerid, winnings - bet);
			if(mult >= 100)
				format(msg,sizeof(msg),"%s{FFD700}*** DZEKPOTAS! x%d ***\n{FFFFFF}Laimejote: {00FF00}%d EUR",
					msg,mult,winnings);
			else
				format(msg,sizeof(msg),"%s{00FF00}LAIMEJOTE! x%d\n{FFFFFF}Gavote: {00FF00}%d EUR",
					msg,mult,winnings);
		}
		else
		{
			GivePlayerMoneyA(playerid,-bet);
			format(msg,sizeof(msg),"%s{FF0000}Nepasiseke.\n{FFFFFF}Praradote: {FF0000}%d EUR",msg,bet);
		}
		ShowPlayerDialog(playerid, DIALOG_KAZINO_RESULT, DIALOG_STYLE_MSGBOX,"Slot Machine",msg,"Dar karta","Baigti");
		return 1;
	}
	if(dialogid == DIALOG_KAZINO_RESULT)
	{
		if(response)
			ShowPlayerDialog(playerid, DIALOG_KAZINO_BET, DIALOG_STYLE_LIST,
				"Slot Machine - Statymas",
				"100 EUR\n500 EUR\n1,000 EUR\n5,000 EUR\n10,000 EUR",
				"Losit","Baigti");
		return 1;
	}
	if(dialogid == DIALOG_DICE_BET)
	{
		if(!response) { cmd_kazino(playerid,""); return 1; }
		static const DiceBets[] = {100,100,500,500,1000,1000};
		new bet     = DiceBets[listitem];
		new betHigh = ((listitem % 2) == 0);
		if(GetPlayerMoneyA(playerid) < bet)
			return SendInfoMessage(playerid,"~r~Neuztenka pinigu!");
		new roll1 = 1+random(6), roll2 = 1+random(6), total = roll1+roll2;
		new won = (betHigh && total >= 7) || (!betHigh && total <= 6);
		new msg[256];
		format(msg,sizeof(msg),
			"Kauliukai: {FFFF00}[%d] + [%d]{FFFFFF} = {FFFF00}%d{FFFFFF}\n\nJus lazinotes: {FFFF00}%s{FFFFFF}\n\n",
			roll1, roll2, total, betHigh ? "Didelis (7-12)" : "Mazas (2-6)");
		if(won)
		{
			GivePlayerMoneyA(playerid, bet);
			format(msg,sizeof(msg),"%s{00FF00}LAIMEJOTE! +%d EUR",msg,bet);
		}
		else
		{
			GivePlayerMoneyA(playerid,-bet);
			format(msg,sizeof(msg),"%s{FF0000}Pralaimejote. -%d EUR",msg,bet);
		}
		ShowPlayerDialog(playerid, DIALOG_DICE_RESULT, DIALOG_STYLE_MSGBOX,"Kauliukai",msg,"Dar karta","Baigti");
		return 1;
	}
	if(dialogid == DIALOG_DICE_RESULT)
	{
		if(response)
			ShowPlayerDialog(playerid, DIALOG_DICE_BET, DIALOG_STYLE_LIST,
				"Kauliukai - Pasirinkite",
				"100 EUR - Didelis (7-12)\n100 EUR - Mazas (2-6)\n500 EUR - Didelis (7-12)\n500 EUR - Mazas (2-6)\n1000 EUR - Didelis (7-12)\n1000 EUR - Mazas (2-6)",
				"Mesti","Baigti");
		return 1;
	}

	}	return 1;
}

