forward ConnectMySQL();
public ConnectMySQL()
{
	//mysql_debug(false);
	//enable_mutex(false);
	SQL = mysql_connect_file();
	new errno = mysql_errno(SQL);
	if(SQL == MYSQL_INVALID_HANDLE || errno != 0)
	{
	    printf("[MYSQL]: [ERROR]: Connection to MYSQL failed! Error: %i", errno);
		return 0;
	}
	
	new test, Cache:result = mysql_queryworkaround(SQL, "SELECT 1 FROM Config LIMIT 1");
	cache_get_value_int(0, 0, test);
	cache_delete(result);
	#pragma unused result
	if(!test)
	{
		printf("[MYSQL]: [ERROR]: MySQL test failed!");
		return 0;
	}
	new cypher[256];
	result = mysql_queryworkaround(SQL, "SHOW SESSION STATUS LIKE 'Ssl_cipher'");
	cache_get_row(0, 1, cypher);
	cache_delete(result);
	printf("[MYSQL] SSL Cypher: '%s'",cypher);
	result = mysql_queryworkaround(SQL, "SHOW SESSION STATUS LIKE 'Ssl_version'");
	cache_get_row(0, 1, cypher);
	cache_delete(result);
	printf("[MYSQL] SSL Version: '%s'",cypher);

	mysql_query("SET NAMES `cp1257`");
	mysql_query("SET CHARACTER SET `cp1257`");
	mysql_query("SET COLLATION_CONNECTION = `cp1257_lithuanian_ci`");
	return 1;
}

main()
{
	print("GRPLT: Executing meta file. This is the last step of the loading process.");
	print("GRPLT: If you wish to view the log of startup, please look up.");
	print("\n\n\n\n\n\n\n\n\n");//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	print("                 ----------------------------------------------");
	print("                           Los Santos Gyvenimas ");
    print("                          Created by Benas benas@rayon.lt ");
	printf("                       Versija - %s %s (%s)",VERSIJA,KODUOTE,DATA);
	print("                 ----------------------------------------------");
	print("\n\n\n\n\n\n\n\n");//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
}
public OnGameModeInit()
{
	for(new i;i<sizeof(Verslu_CP);i++)
	{
		if(Verslu_CP[i][0] > -1544 && Verslu_CP[i][0] < -1543) // kioskas
				CreateDynamicCP(Verslu_CP[i][0], Verslu_CP[i][1], Verslu_CP[i][2], 1.0,-1,0);
		else if(i < 30)
		{
			CreateDynamicCP(Verslu_CP[i][0], Verslu_CP[i][1], Verslu_CP[i][2], 1.0,-1,NPCInt[i]);
		}
		else
		{
			for(new int=1;int<=18;int++)
				CreateDynamicCP(Verslu_CP[i][0], Verslu_CP[i][1], Verslu_CP[i][2], 1.0,-1,int);
		}
	}
	InitStars();
	drillid[0] = CreateDynamicCP(DRILL_CP[0][0],DRILL_CP[0][1],DRILL_CP[0][2], 1.0,-1,1); // pentagonas prie hotel
	drillid[1] = CreateDynamicCP(DRILL_CP[1][0],DRILL_CP[1][1],DRILL_CP[1][2], 1.0,-1,3); // savivaldybe prie poker
	drillid[2] = CreateDynamicCP(DRILL_CP[2][0],DRILL_CP[2][1],DRILL_CP[2][2], 1.0,-1,1); // bankas
	//InitPokerGame(0,1);
	AntiDeAMX();
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_STREAMED);
	strcat("", "", 0); // for getstrarg
	Streamer_VisibleItems(STREAMER_TYPE_OBJECT, 600);
	Streamer_TickRate(60);
	for(new i = 0; i < sizeof(iPickups); i++)
	{
		iPickups[i][0] = -1;
		iPickups[i][1] = -1;
		iPickups[i][2] = -1;
		iPickups[i][3] = -1;
		iPickups[i][4] = -1;
	}
	ManualVehicleEngineAndLights();
	ShowNameTags(1);
	print("LSG: Hello, and welcome to LSG Server Console.");
    AllignMaxPlayers();
	print("LSG: Connecting SQL");
	if(ConnectMySQL() == 0)
	{
		SendRconCommand("exit");
		return 1;
	}
	if(GetTickCount() < 0)
	{
		print("Tick count < 0");
		SendRconCommand("exit");
		return 1;
	}
	print("LSG: Loading MapAndreas");
	MapAndreas_Init(MAP_ANDREAS_MODE_FULL);
	print("LSG: Loading Master configuration settings.");
	LoadVars();
	printf("LSG: Success... current session id is: %i",Server[gSession]);
	
	if(IsProdEnvironment())
	{
		printf("LSG: Cleaning up stale logins");
		mysql_query("Update Login Set Logout = NOW(), `Time`=0 WHERE Logout IS NULL");
	}
	printf("Loading yrace");
	LoadYRace();
	new i;
	for(i=0; i<sizeof(aVehicleNames); i++) if(aVehicleNames[i][Autohaus])
	{
		aVehicleNames[i][Carid]=CreateVehicle(aVehicleNames[i][Modelid],aVehicleNames[i][X],aVehicleNames[i][Y],aVehicleNames[i][Z],aVehicleNames[i][Rotation],-1,-1,-1);
		new
		    tmpstr[ 60 ];
		format( tmpstr, 60, "%s\n%i€", aVehicleNames[i][Name],aVehicleNames[i][Price] );
        CreateDynamic3DTextLabel( tmpstr, COLOR_WHITE,aVehicleNames[i][X],aVehicleNames[i][Y],aVehicleNames[i][Z],25,_,_,true );
	}
	for (i=0 ; i < sizeof(siuksarray); i++ )
	{
		CreateDynamic3DTextLabel( "Ðiukðlës\nSpausk [ENTER], kad pavalgytum", COLOR_WHITE,siuksarray[i][X],siuksarray[i][Y],siuksarray[i][Z],7,_,_,true );
	}
	for(i=0; i<MAX_PLAYERS; i++)
	{
		Spectating[i][0]=-1;
	}
	//CreateDynamicMapIcon(1653.9268,-1661.9005,22.5156, 35, 0); // save
	CreateDynamicMapIcon(1315.3837,-898.9023,39.5781,23, 0,_,_,_,_,MAPICON_LOCAL); // dazasvydis
	CreateDynamicMapIcon(1178.0593,-1323.6637,14.1014, 22, 0,_,_,_,_,MAPICON_LOCAL); // ligonine
	CreateDynamicMapIcon(1550.4586,-1675.4597,15.4160, 30, 0,_,_,_,_,MAPICON_LOCAL); //pd
	CreateDynamicMapIcon(1798.6570,-1894.5203,13.4030, 36, 0,_,_,_,_,MAPICON_LOCAL); //VM
	CreateDynamicMapIcon(530.2449,-1291.5901,17.3530, 55, 0,_,_,_,_,MAPICON_LOCAL); //turgus 
	CreateDynamicMapIcon(1654.7229,-1098.2947,24.1436, 55, 0,_,_,_,_,MAPICON_LOCAL); //turgus
	CreateDynamicMapIcon(2128.6824,-1138.1835,25.4295, 55, 0,_,_,_,_,MAPICON_LOCAL); //turgus
	CreateDynamicMapIcon(2034.1698,-1402.0686,17.2948, 22, 0,_,_,_,_,MAPICON_LOCAL); // privati ligonine
	CreateDynamicMapIcon(981.8362,-1161.8503,25.0859, 25, 0,_,_,_,_,MAPICON_LOCAL); // pokeris
	CreateDynamicMapIcon(2019.4331,1007.7090,10.8203, 25, 0,_,_,_,_,MAPICON_LOCAL); // pokeris four dragons
	CreateDynamicMapIcon(386.7198,-1817.888,7.884, 9, 0,_,_,_,_,MAPICON_LOCAL); // zvejyba
	// car fixai
	CreateDynamicMapIcon(1017.7556,-917.3123,42.4931, 63, 0,_,_,_,_,MAPICON_LOCAL);
	CreateDynamicMapIcon(1911.2146,-1775.0718,13.5318, 63, 0,_,_,_,_,MAPICON_LOCAL);
	CreateDynamicMapIcon(666.1385,-616.0114,16.3396, 63, 0,_,_,_,_,MAPICON_LOCAL);
	CreateDynamicMapIcon(2066.8318,-2556.4392,19.3621, 63, 0,_,_,_,_,MAPICON_LOCAL);// malunsparniu.
	CreateDynamicMapIcon(2456.0039,-1460.7887,24.1489, 63, 0,_,_,_,_,MAPICON_LOCAL);
	// pay n spray

	for(i=0;i<sizeof(ac_PayNSpray);i++)
	{
		CreateDynamicMapIcon(ac_PayNSpray[i][0],ac_PayNSpray[i][1],ac_PayNSpray[i][2], 63, 0);

	}

    print("LSG: Applying pre-release configuration...");
	GlobalSystem();
	DisableInteriorEnterExits();
	//AllowAdminTeleport(1);
	print("LSG: Enabling treasure hunt script...");
	EnableLobiai();
	print("LSG: Creating vehicles and preparing gas system...");
	LoadVehicles();
	print("LSG: Preparing Skins and Classes...");
	LoadSpawns();
	print("LSG: Loading pickups");
	LoadPickups();
	print("LSG: Loading houses");
	LoadHouses();
	LoadForSaleSigns();
	print("LSG: Loading pelnai");
	LoadPelnai();
	print("LSG: Loading bussiness");
	LoadBusinesses();
	printf("LSG: Loading gangs");
	LoadFamily();
	printf("LSG: Loading Fades");
	FadeInit();
	printf("LSG: Loading Gang Tags");
	LoadGaujuTagai();
	printf("LSG: Loading Patruliai");
	LoadPatruliai();
	printf("LSG: Loading jobs");
	InitJobs();
	printf("LSG: Loading football");

	CreateBall();
	InitLab();
	InitWorlds();
	LoadCollisions();
	LoadTextDraws();
	// 
	print("LSG: Loading Entrances");
	for ( new ia = 0; ia < BENTRANCES_COUNT; ia++ )
    {
		new
		    tmpstr[ 128 ];
		    
		format( tmpstr, 128, "{00864b}%s\n\n{FFFFFF}Norëdami áeiti spauskite {00864b}[ENTER]", BEntrances[ ia ][ bStr1 ] );
        CreateDynamic3DTextLabel( tmpstr, COLOR_WHITE,BEntrances[ ia ][ bEnt_x ],BEntrances[ ia ][ bEnt_y ],BEntrances[ ia ][ bEnt_z ],75,_,_,true );
		CreatePickupA(19197,1,BEntrances[ ia ][ bEnt_x ],BEntrances[ ia ][ bEnt_y ],BEntrances[ ia ][ bEnt_z ]);
		format( tmpstr, 128, "{00864b}Iðëjimas\n\n{FFFFFF}Norëdami iðeiti spauskite {00864b}[ENTER]");
		CreateDynamic3DTextLabel( tmpstr, COLOR_WHITE,BEntrances[ ia ][ bExi_x ],BEntrances[ ia ][ bExi_y ],BEntrances[ ia ][ bExi_z ],25,_,_,true );
		CreatePickupA(19197,1,BEntrances[ ia ][ bExi_x ],BEntrances[ ia ][ bExi_y ],BEntrances[ ia ][ bExi_z ]);
	}
	for ( new ia = 0; ia < sizeof(SecEntrances); ia++ )
    {
        CreateDynamic3DTextLabel( "Tarnybinis Praëjimas", COLOR_PILKA, SecEntrances[ ia ][ se_x ],SecEntrances[ ia ][ se_y ],SecEntrances[ ia ][ se_z ],5,_,_,true );
		CreateDynamic3DTextLabel( "Tarnybinis Praëjimas", COLOR_PILKA, SecEntrances[ ia ][ se_x1 ],SecEntrances[ ia ][ se_y1 ],SecEntrances[ ia ][ se_z1 ],5,_,_,true );
	}
	for(new ia;ia < MAX_POKER_GAMES;ia++)
	{
		new
		    tmpstr[ 100 ];
		    
		format( tmpstr, 100, "Blinds %s/%s€\nBuy in %s-%s€\nSpauskite [H]", FormatNumber(PokerBlinds[ia][0]),FormatNumber(PokerBlinds[ia][1]),FormatNumber(PokerBlinds[ia][2]),FormatNumber(PokerBlinds[ia][3]) );
        PokerBlindsTD[ia] = CreateDynamic3DTextLabel( tmpstr, COLOR_PILKA,PokerTables[ia][0],PokerTables[ia][1],PokerTables[ia][2],25,_,_,true );
		for(new ix;ix<6;ix++)
		{
			Poker[ia][players][ix]=-1;
			
		}
	}
	LosimuTD = CreateDynamic3DTextLabel("{33CCFF}7 ið 42\n\n\n{FFFFFF}Iki kito loðimo liko {00864b}02:00", -1, 822.2601,2.1007,1005.1797,30.0);

	print("LSG: Loading objects and texts.");
	VisiObjektai();
	Textai();
	LoadFerris();
	LoadSiena();
	print("LSG: Loading Elevator");
	ResetElevatorQueue();
	InitPolygons();
	Elevator_Initialize();
	InitVartai();
	print("LSG: Loading Flat system");
	LoadDaugiabuciai();
	print("LSG: Loading Traffic Signs");
	LoadTrafficSigns();
   	print("LSG: Loading data completed. Starting the server...");
    print("LSG: Initialising timers...");
	DegalaiAkumas();
	SyncVehicles();
	for(new a;a<MAX_VEHICLES;a++)
	{
		if(GetVehicleModel(a))
		{
			SetVehicleToRespawn(a);
		}
	}
	for(new xz = 0; xz < sizeof(fs_balloon_kor); xz++)
	{
		SpawnBalloon(xz);
	}
	SetTimer("Zaidimas",59997,true); // ir pabegimas (minute)
	SetTimer("SendMSG",29999,true); // taimeris (30 sec).
	SetTimer("SecondTimer",3991, true); // 4sec
	SetTimer("SyncVehicles",3599985,true); // ir pelnai valanda
	SetTimer("GlobalUpdate",899998,true); // ir masinos parke 15min
	SetTimer("MedikaiTime", 6*60*1000, true); // 6 mins
	SetTimer("ZolesKokybe",3479991,true); // beveik valanda
	SetTimer("rentfee",3599990,true); // valanda
	SetTimer("Chekas",1000, 1); // 1min
	SetTimer("JailGates",599984, 1); // 10min
	SetTimer("GlobalUpdatez",239996, 1); // 4min
	SetTimer("DegalaiZvejyba",9999,1); // 10 sec
    // SOLO FEATURES
    SetTimer("SimulatedEconomy",  120000, true);  // every 2 min
    SetTimer("TerritoryUpdate",    60000, true);  // every 1 min
    SetTimer("SupplyChainUpdate",  60000, true);  // every 1 min
    SetTimer("FakeWorkerUpdate",   60000, true);  // every 1 min
    SetTimer("FakePlayerUpdate",  180000, true);  // every 3 min
    SetTimer("MortgagePayment",    60000, true);  // every 1 min
    SetTimer("DailyMarketShift",  300000, true);  // every 5 min
    InitSoloFeatures();


	Shamal1 =AddStaticVehicle(469,1781.66369629,-1925.78820801,13.49185181,0.00000000,16,16); //Sparrow
	Shamal2 =AddStaticVehicle(469,1798.97558594,-1925.74121094,13.49553299,0.00000000,16,16); //Sparrow

	Club1 = AddStaticVehicle(589,1777.66210938,-1914.00683594,13.10374451,269.74731445,16,16); //Club
	Club2 = AddStaticVehicle(589,1778.04394531,-1909.10058594,13.10480881,269.74731445,16,16); //Club
	Club3 = AddStaticVehicle(589,1777.80957031,-1903.37304688,13.10463333,269.74731445,16,16); //Club
	Moto1 = AddStaticVehicle(586,1804.55468750,-1904.04882812,12.99715614,86.74804688,16,16); //Wayfarer
	Moto2 = AddStaticVehicle(586,1804.17968750,-1908.50976562,12.99498177,88.74755859,16,16); //Wayfarer
	Moto3 = AddStaticVehicle(586,1804.28515625,-1913.35351562,12.99261475,91.49963379,16,16); //Wayfarer


	//LoadPool();
	print("LSG: Connecting BOT");
	ConnectNPC("Bus_Driver","mat_test");
	//ConnectNPC("Another_Driver","at400_ls");
	print("LSG: Loading actors");
	// kaledos
	//elfas = CreateActor(0,949.6525,-1652.1201,13.5422,79.8671);
	//CreateDynamicObject(19065, 949.582153, -1652.092773, 14.281448, 0.000, 35.5, -178.800); // kepure
	//CreateDynamicObject(18864,949.582153, -1652.092773, 0.0,5.0,5.0,31.0); // sniegas
	// inkasatoriai
	CreateActor(141,1555.2955,-1355.5699,226.4853, 78.0259);
	// casino
	CreateActor(11,2234.6082,1654.6954,1008.3594,272.9585); // kupje1
	CreateActor(171,2234.6221,1648.5309,1008.3594,265.2688); // kupje2
	CreateActor(172,2234.6460,1642.2800,1008.3594,268.9897); // kupje3
	CreateActor(171,2234.5042,1633.1887,1008.3594,269.9820); // kupje 4
	// casino four dragons
	CreateActor(91,1993.0685,1019.1484,994.8906,181.2626); // kupje
	CreateActor(214,2000.5251,1003.3713,994.4688,0.8067); // baras
	// lobiai
	CreateActor(159,-366.0555,2261.6736,42.4844,264.5); 
	// pd vidus
	pdactor1 = CreateActor(309,1261.6864,562.4147,1068.1515,79.6097); 
	ApplyActorAnimation(pdactor1, "INT_OFFICE", "FF_Dam_Fwd",4.0,0,0,0,1,0);
	// prie vartu pd,garaz ir jail
	CreateActor(310,1544.0226,-1631.7294,13.3828,87.9896); 
	pdactor2 = CreateActor(310,1580.8176,-1634.8824,13.5608,267.1951); 
	ApplyActorAnimation(pdactor2, "POLICE", "plc_drgbst_01",4.0, 1, 0,0,0,0);

	CreateActor(311,3072.2168,-765.4230,11.0300,181.1898); 
	// savivaldybe
	new aac = CreateActor(57,359.7138,173.5964,1008.3893,267.7668);
	ApplyActorAnimation(aac, "COP_AMBIENT", "Coplook_loop", 4.0, 0, 1, 1, 1, -1);
	// cezaris
	//cezarionpc = CreateActor(167,212.4125,1821.8938,6.4141,262.2883);
	//ApplyActorAnimation(cezarionpc, "POLICE", "plc_drgbst_01",4.0, 1, 0,0,0,0);

	print("LSG: Loading Achievements");
	LoadAchievementMax();
	print("LSG: Full starting procedure is completed, server is now ready to accept connections.");
	print("LSG: Have fun!");
	printf("%i",pickups[0][gunisk]);
	SetTimer("CheckNPC",1000,false);
	SetTimer("FixBot", 10000, true);
	//printf("LSG: Loading Vehicles");
	//LoadVehiclesEx();
	//printf("LSG: Done");
	//cmd_oputest(0,"");
	for(new a;a<sizeof(aVehicleNames);a++)
	{
		if(aVehicleNames[a][Price] == 0)
		{
			aVehicleNames[a][Price] = 100000;
		}
		if(aVehicleNames[a][Repair] == 0)
		{
			aVehicleNames[a][Repair] = 20000;
		}
	}
	AutokluboCars();
	InitRocketMarker();
	initChristmas();
	//TestLoterija();
	
	return 1;
} 
   //********************************************Skripto pabaiga

stock VisiObjektai()
{
	LoadObjektai();
	return 1;
}
forward CheckNPC();
public CheckNPC()
{
	new name[24];
	for(new i;i<MAX_PLAYERS;i++) if(IsPlayerConnected(i))
	{
		if(IsPlayerNPC(i))
		{
			GetPlayerName(i,name,24);
			if(!strcmp(name,"Bus_Driver",true)) return 1;
		}
	
	}
	ConnectNPC("Bus_Driver","mat_test");
	return 1;
}
new Text:MainuLine;
stock Textai()
{
	
	SleptisTD = TextDrawCreate(629.682739, 434.937347, "S");
	TextDrawLetterSize(SleptisTD, 0.335000, 1.029629);
	TextDrawAlignment(SleptisTD, 1);
	TextDrawColor(SleptisTD, -1694498580);
	TextDrawSetShadow(SleptisTD, 0);
	TextDrawBackgroundColor(SleptisTD, 255);
	TextDrawFont(SleptisTD, 0);
	TextDrawSetProportional(SleptisTD, 0);

	PassReminder = TextDrawCreate(587.000000, 313.000000, "Slaptazodzio priminimas");
	TextDrawAlignment(PassReminder, 2);
	TextDrawBackgroundColor(PassReminder, 255);
	TextDrawFont(PassReminder, 1);
	TextDrawLetterSize(PassReminder, 0.500000, 1.000000);
	TextDrawColor(PassReminder, -1);
	TextDrawSetOutline(PassReminder, 0);
	TextDrawSetProportional(PassReminder, 1);
	TextDrawSetShadow(PassReminder, 1);
	TextDrawUseBox(PassReminder, 1);
	TextDrawBoxColor(PassReminder, 255);
	TextDrawTextSize(PassReminder, 20.000000, 110.000000);
	TextDrawSetSelectable(PassReminder,true);
	// anim
    txtAnimHelper = TextDrawCreate(610.0, 400.0, "~p~~k~~PED_ANSWER_PHONE~ ~w~kad baigti veiksma");
	TextDrawUseBox(txtAnimHelper, 0);
	TextDrawFont(txtAnimHelper, 2);
	TextDrawSetShadow(txtAnimHelper,0); // no shadow
    TextDrawSetOutline(txtAnimHelper,1); // thickness 1
    TextDrawBackgroundColor(txtAnimHelper,0x000000FF);
    TextDrawColor(txtAnimHelper,0xFFFFFFFF);
    TextDrawAlignment(txtAnimHelper,3); // align right
	
	MainuLine = TextDrawCreate(322.000000, 150.000000, "~n~");
	TextDrawBackgroundColor(MainuLine, 255);
	TextDrawFont(MainuLine, 1);
	TextDrawLetterSize(MainuLine, 0.500000, 30.000001);
	TextDrawColor(MainuLine, -1);
	TextDrawSetOutline(MainuLine, 0);
	TextDrawSetProportional(MainuLine, 1);
	TextDrawSetShadow(MainuLine, 1);
	TextDrawUseBox(MainuLine, 1);
	TextDrawBoxColor(MainuLine, 255);
	TextDrawTextSize(MainuLine, 297.000000, 37.000000);
	
// laikrodis
	TextdrawTime = TextDrawCreate(546.0, 20.0,"--");
	TextDrawAlignment(TextdrawTime,0);
	TextDrawBackgroundColor(TextdrawTime,0x000000ff);
	TextDrawFont(TextdrawTime,3);
	TextDrawLetterSize(TextdrawTime,0.5, 1.9);
	TextDrawColor(TextdrawTime,0xffffffff);
	TextDrawSetOutline(TextdrawTime,1);
	TextDrawSetProportional(TextdrawTime,1);
	TextDrawSetShadow(TextdrawTime,1);

	// saugi zona
	SafeTD = TextDrawCreate(37.417060, 431.629730, "Saugi_zona");
	TextDrawLetterSize(SafeTD, 0.354166, 1.335556);
	TextDrawAlignment(SafeTD, 2);
	TextDrawColor(SafeTD, -1);
	TextDrawSetShadow(SafeTD, 1);
	TextDrawSetOutline(SafeTD, -256);
	TextDrawBackgroundColor(SafeTD, 39423);
	TextDrawFont(SafeTD, 3);
	TextDrawSetProportional(SafeTD, 1);
	TextDrawSetShadow(SafeTD, 1);

	WorldsTD = TextDrawCreate(37.417060, 431.629730, "_LSG_Pasauliai");
	TextDrawLetterSize(WorldsTD, 0.354166, 1.335556);
	TextDrawAlignment(WorldsTD, 2);
	TextDrawColor(WorldsTD, -1);
	TextDrawSetShadow(WorldsTD, 1);
	TextDrawSetOutline(WorldsTD, -256);
	TextDrawBackgroundColor(WorldsTD, 0x00630fFF);
	TextDrawFont(WorldsTD, 3);
	TextDrawSetProportional(WorldsTD, 1);
	TextDrawSetShadow(WorldsTD, 1);

	InvisTD = TextDrawCreate(70.417060, 310.629730, "INVISIBLE");
	TextDrawLetterSize(InvisTD, 0.354166, 1.335556);
	TextDrawAlignment(InvisTD, 2);
	TextDrawColor(InvisTD, -1);
	TextDrawSetShadow(InvisTD, 1);
	TextDrawSetOutline(InvisTD, -256);
	TextDrawBackgroundColor(InvisTD, 0xFF0000FF);
	TextDrawFont(InvisTD, 3);
	TextDrawSetProportional(InvisTD, 1);
	TextDrawSetShadow(InvisTD, 1);
	
	// speedo
	
	kmhTD = TextDrawCreate(572.000000, 399.000000, "km/h");
	TextDrawBackgroundColor(kmhTD, 255);
	TextDrawFont(kmhTD, 1);
	TextDrawLetterSize(kmhTD, 0.549998, 1.500000);
	TextDrawColor(kmhTD, -1);
	TextDrawSetOutline(kmhTD, 0);
	TextDrawSetProportional(kmhTD, 1);
	TextDrawSetShadow(kmhTD, 2);

	// degalai ir akumas textai

	// dazai
	//Global TextDraws: 

	
	{
		// rc laukai
		dazugui[0] = TextDrawCreate(300.833343, 10.074041, "203"); // red
		TextDrawLetterSize(dazugui[0], 0.400000, 1.600000);
		TextDrawTextSize(dazugui[0], 0.000000, 34.000000);
		TextDrawAlignment(dazugui[0], 2);
		TextDrawColor(dazugui[0], -16756737);
		TextDrawUseBox(dazugui[0], 1);
		TextDrawBoxColor(dazugui[0], 100);
		TextDrawSetShadow(dazugui[0], 0);
		TextDrawSetOutline(dazugui[0], -1);
		TextDrawBackgroundColor(dazugui[0], 255);
		TextDrawFont(dazugui[0], 2);
		TextDrawSetProportional(dazugui[0], 1);
		TextDrawSetShadow(dazugui[0], 0);

		dazugui[1] = TextDrawCreate(340.036987, 10.035160, "128"); // blu
		TextDrawLetterSize(dazugui[1], 0.400000, 1.600000);
		TextDrawTextSize(dazugui[1], 0.000000, 34.000000);
		TextDrawAlignment(dazugui[1], 2);
		TextDrawColor(dazugui[1], 1325465599);
		TextDrawUseBox(dazugui[1], 1);
		TextDrawBoxColor(dazugui[1], 100);
		TextDrawSetShadow(dazugui[1], 0);
		TextDrawSetOutline(dazugui[1], -1);
		TextDrawBackgroundColor(dazugui[1], 255);
		TextDrawFont(dazugui[1], 2);
		TextDrawSetProportional(dazugui[1], 1);
		TextDrawSetShadow(dazugui[1], 0);


		

		dazugui[2] = TextDrawCreate(297.267730, 27.703676, "59.34");
		TextDrawLetterSize(dazugui[2], 0.400000, 1.600000);
		TextDrawAlignment(dazugui[2], 1);
		TextDrawColor(dazugui[2], -1);
		TextDrawSetShadow(dazugui[2], 0);
		TextDrawSetOutline(dazugui[2], 0);
		TextDrawBackgroundColor(dazugui[2], 255);
		TextDrawFont(dazugui[2], 0);
		TextDrawSetProportional(dazugui[2], 1);
		TextDrawSetShadow(dazugui[2], 0);

		dazugui[3] = TextDrawCreate(279.166717, 10.005555, "||||||||red");
		TextDrawLetterSize(dazugui[3], 0.400000, 1.600000);
		TextDrawAlignment(dazugui[3], 3);
		TextDrawColor(dazugui[3], -16756737);
		TextDrawSetShadow(dazugui[3], 0);
		TextDrawSetOutline(dazugui[3], 1);
		TextDrawBackgroundColor(dazugui[3], 255);
		TextDrawFont(dazugui[3], 1);
		TextDrawSetProportional(dazugui[3], 1);
		TextDrawSetShadow(dazugui[3], 0);

		dazugui[4] = TextDrawCreate(361.666717, 10.079621, "||||||||blu");
		TextDrawLetterSize(dazugui[4], 0.400000, 1.600000);
		TextDrawAlignment(dazugui[4], 1);
		TextDrawColor(dazugui[4], 1325465599);
		TextDrawSetShadow(dazugui[4], 0);
		TextDrawSetOutline(dazugui[4], 1);
		TextDrawBackgroundColor(dazugui[4], 255);
		TextDrawFont(dazugui[4], 1);
		TextDrawSetProportional(dazugui[4], 1);
		TextDrawSetShadow(dazugui[4], 0);
	}

	CreateDynamic3DTextLabel("{00864b}Mokesèiai",COLOR_WHITE,361.8299,173.6071,1008.3828,10,_,_,1);
    //CreateDynamic3DTextLabel("Kalëdinë dovana", COLOR_WHITE, 393.0056,-1527.1067,32.2768, 10.0);
	//CreateDynamic3DTextLabel("Los Santos\n{e299ff}Kalëdø Eglutë",COLOR_WHITE,2302.3359,-1528.9720,26.9137,50,_,_,1);
	//CreateDynamic3DTextLabel("{00864b}Kalï¿½dï¿½ senelis",COLOR_WHITE,391.5240,-1560.5220,29.5992,10,_,_,1);
	CreateDynamic3DTextLabel("Inkasatorius", COLOR_WHITE, 1562.3695,-1341.8190,226.4853, 50, _, _, 1);
	//Total textdraws exported: 5 (5 global textdraws / 0 player textdraws) ~ 29/5/2017 ~ 14:46:21
	
//Darbu textai
	CreateDynamic3DTextLabel("Pinigø perveþimo uþsakymai",COLOR_WHITE,1553.1379,-1355.6760,226.4853,10,_,_,1);
  //Su pakvietimu
	CreateDynamic3DTextLabel("Daþasvydis",COLOR_WHITE,-974.3956,1061.0923,1345.6760,50,_,_,1);
	CreateDynamic3DTextLabel("Baikeriai\nSpauskite {00864b}[~k~~GROUP_CONTROL_BWD~]",COLOR_WHITE,BAIKER_LAUKAS, 50,_,_,1); 
	CreateDynamic3DTextLabel("Baikeriai\nSpauskite {00864b}[~k~~GROUP_CONTROL_BWD~]",COLOR_WHITE,BAIKER_VIDUS, 50,_,_,1); 
	
	CreateDynamic3DTextLabel("Vartai\nPareigûnai, spauskite {00864b}[~k~~GROUP_CONTROL_BWD~]",COLOR_LIGHTBLUE,1849.32995605,-1714.31005859,3201.54003906, 10,_,_,0); 
	CreateDynamic3DTextLabel("Vartai\nPareigûnai, spauskite {00864b}[~k~~GROUP_CONTROL_BWD~]",COLOR_LIGHTBLUE,1847.31994629,-1722.56994629,3201.54003906, 10,_,_,0); 
	CreateDynamic3DTextLabel("Vartai\nPareigûnai, spauskite {00864b}[~k~~GROUP_CONTROL_BWD~]",COLOR_LIGHTBLUE,1854.01953125,-1726.27343750,3201.54003906, 10,_,_,0); 
	CreateDynamic3DTextLabel("Vartai\nPareigûnai, spauskite {00864b}[~k~~GROUP_CONTROL_BWD~]",COLOR_LIGHTBLUE,1862.02246094,-1710.91992188,3201.54003906, 10,_,_,0); 



	//CreateDynamic3DTextLabel("Dovanos", COLOR_RED,  1479.5704,-1622.7815,14.0469, 50,_,_,1);
	CreateDynamic3DTextLabel("Mechanikai", COLOR_WHITE, 1615.9764, -1526.8292, 13.6237, 50,_,_, 1);
	//CreateDynamic3DTextLabel("Limuzino vairuotojas", COLOR_WHITE, 477.1216,-1496.3582,20.4286, 50,_,_, 1);
	CreateDynamic3DTextLabel("Gaisrininkai", COLOR_WHITE,1466.5741,-999.7215,675.6033, 50,_,_, 1);
	CreateDynamic3DTextLabel("Medikai", COLOR_WHITE, 1173.082397, -1327.809937, 15.021232, 50,_,_, 1);
	CreateDynamic3DTextLabel("Privatûs Medikai", COLOR_WHITE, 2025.3667,-1404.1603,17.2109, 50,_,_, 1);
	CreateDynamic3DTextLabel("Automanai", COLOR_WHITE, 2463.4329,2307.4607,91.7515, 50,_,_, 1);
	CreateDynamic3DTextLabel("Baikeriai", COLOR_WHITE, 2802.7490,-1416.8666,15.7901, 50,_,_, 1);
	CreateDynamic3DTextLabel("Motomanai", COLOR_WHITE, 1627.6857,-1002.4310,24.0646, 50,_,_, 1);
	CreateDynamic3DTextLabel("Skelbëjai", COLOR_WHITE, 800.3235,-1323.3992,710.2907, 50,_,_, 1);
	//CreateDynamic3DTextLabel("Jachtu Klubas", COLOR_WHITE, 723.1079, -1494.6093, 1.9343, 50,_,_, 1);
	CreateDynamic3DTextLabel("Policija", COLOR_WHITE, 524.914307,-1677.842773,5.210094, 50,_,_, 1);
	
	CreateDynamic3DTextLabel("ARAS", COLOR_WHITE, 915.6300,-1235.3546,17.2109, 50,_,_, 1);
	//CreateDynamic3DTextLabel("Taksistas", COLOR_WHITE, 1490.2881,1305.0903,1093.2964, 50,_,_, 1);
	CreateDynamic3DTextLabel("Taksistas", COLOR_WHITE,991.6368,-4.8654,2740.5122, 50,_,_, 1);
	CreateDynamic3DTextLabel("Transporteris", COLOR_WHITE, 895.9285,-1673.8705,13.5469, 50,_,_, 1);
	CreateDynamic3DTextLabel("VST", COLOR_WHITE, 1345.8868,521.9305,1067.7562, 10,_,_, 1);
	CreateDynamic3DTextLabel("Policija", COLOR_WHITE, 1345.7152,518.5157,1067.7562, 10,_,_, 1);
	CreateDynamic3DTextLabel("Kurjeriai", COLOR_WHITE, 1094.1445,2113.9644,15.3504, 10,_,_, 1);
	CreateDynamic3DTextLabel("Furistai", COLOR_WHITE,2474.5759,-2082.1638,13.6464, 10,_,_, 1);
	 //Be pakvietimo
	CreateDynamic3DTextLabel("Èia galite pasiimti laiðkø iðveþiojimui!", COLOR_WHITE, 616.8500,-1458.9423,14.4306, 50,_,_, 1);
	CreateDynamic3DTextLabel("Autobuso vairuotojai", COLOR_WHITE, 1451.3656,-2355.0891,13.5469, 50,_,_, 1);
	CreateDynamic3DTextLabel("Mikro autobusininkai", COLOR_WHITE, 1539.5917,-2299.0200,13.5469, 50,_,_, 1);
	CreateDynamic3DTextLabel("Picos iðveþiotojai", COLOR_WHITE, 2104.4744,-1820.8206,13.5547, 50,_,_, 1);
	CreateDynamic3DTextLabel("Ðiukðliaveþiai", COLOR_WHITE, 2201.2314,-1969.7465,13.7841, 50,_,_, 1);
	CreateDynamic3DTextLabel("Ðlavëjai", COLOR_WHITE, 1636.3925,-1905.2928,13.5504, 50,_,_, 1);
	CreateDynamic3DTextLabel("Statybininkai", COLOR_WHITE, 1241.8691,-1257.9651,17.190, 50,_,_, 1);
	CreateDynamic3DTextLabel("Traukinio vairuotojai", COLOR_WHITE, 1685.0159,-1944.7394,13.5469, 50,_,_, 1);
	CreateDynamic3DTextLabel("BMX'eriai", COLOR_WHITE, 1859.5493,-1392.1375,13.5625, 50,_,_, 1);
	CreateDynamic3DTextLabel("Lakûnai", COLOR_WHITE, 1596.6449,-2638.3730,13.5469, 50,_,_, 1);
	CreateDynamic3DTextLabel("Reporteriai", COLOR_WHITE, 784.2620,-1333.0282,13.5406, 50,_,_, 1);
	CreateDynamic3DTextLabel("Pakrantës Apsauga", COLOR_WHITE, 651.6191, -1871.2081, 5.4609, 50,_,_, 1);
	CreateDynamic3DTextLabel("Pasienis", COLOR_WHITE, 210.1804,-1434.0956,13.2025, 50,_,_, 1);
	CreateDynamic3DTextLabel("Kriminalistai", COLOR_WHITE, 783.6016,-1380.9467,13.6776, 50,_,_, 1);
	CreateDynamic3DTextLabel("Kunigai", COLOR_WHITE, 934.9195,-1085.8289,24.2891, 50,_,_, 1);
	CreateDynamic3DTextLabel("Nekilnojamo turto agentai", COLOR_WHITE, 1870.0470,2430.2769,20.8316, 50,_,_, 1);
	CreateDynamic3DTextLabel("Bankininkai", COLOR_WHITE, 1473.3879,-1771.9489,18.7958, 50,_,_, 1);
	CreateDynamic3DTextLabel("Advokatai", COLOR_WHITE, 1004.7285,-1125.1222,23.8984, 50,_,_, 1);
	CreateDynamic3DTextLabel("Inkasatorius", COLOR_WHITE, 1562.3695,-1341.8190,226.4853, 50, _, _, 1);
	//Kiti
	//CreateDynamic3DTextLabel("Isipirkti", COLOR_WHITE, 1463.4097, -1496.8733, 13.5469, 50,_,_, 1); //isejimas is mechaniku
	CreateDynamic3DTextLabel("Maðinø pridavimo punktas", COLOR_WHITE, 1523.8451,-1493.8091,13.5620, 50,_,_, 1); //mechaniku kofiskavimas
	CreateDynamic3DTextLabel("Teorijos testas", COLOR_WHITE, -2024.6622,-114.0485,1035.1719, 50,_,_, 1);
	CreateDynamic3DTextLabel("Ðautuvai", COLOR_WHITE, 2452.720459,-1963.575806,13.348365, 50,_,_, 1); //isejimas is mechaniku
	CreateDynamic3DTextLabel("Ûkines prekës", COLOR_WHITE, 2443.985352,-1963.212891,13.341334, 50,_,_, 1); //isejimas is mechaniku

	//Kiti
	CreateDynamic3DTextLabel("Kamera Ligoninë\nSpausk [ENTER]", COLOR_GREEN,1349.9720,516.3022,1067.7477, 20, _,_, 1); //isejimas is mechaniku
	CreateDynamic3DTextLabel("Kamera Bankas\nSpausk [ENTER]", COLOR_GREEN, 1348.7961,521.3548,1067.7477, 50,_,_, 1); //mechaniku kofiskavimas
	CreateDynamic3DTextLabel("Kamera PD\nSpausk [ENTER]", COLOR_GREEN, 1349.7361,518.8124,1067.7477, 20, _,_, 1); //mechaniku kofiskavimas
	//CreateDynamic3DTextLabel("Kamera Hotel\nSpausk [ENTER]", COLOR_GREEN, 230.5846,71.3593,1005.0391, 20, _,_, 1); //mechaniku kofiskavimas

	// Stotis
	CreateDynamic3DTextLabel("Visos komandos", COLOR_LIME, 1735.2341,-1944.4779,13.5618, 20,_,_, 1);
	CreateDynamic3DTextLabel("Kà daryti toliau?", COLOR_LIME, 1751.1981,-1944.4370,13.5618, 20,_,_, 1);
	//Masinu nuoma
	CreateDynamic3DTextLabel("Elegy - 1000€/val", COLOR_LIME, 1247.2047,-2010.6017,59.6685, 50,_,_, 1);
	CreateDynamic3DTextLabel("Sultan - 1000€/val", COLOR_LIME, 1253.4508,-2010.6760,59.4900, 50,_,_, 1);
	CreateDynamic3DTextLabel("Infernus - 2500€/val", COLOR_LIME, 1260.1593,-2010.6797,59.2983, 50,_,_, 1);
	CreateDynamic3DTextLabel("Turismo - 2000€/val", COLOR_LIME, 1266.8942,-2010.5802,59.1058, 50,_,_, 1);
	CreateDynamic3DTextLabel("Banshee - 1000€/val", COLOR_LIME, 1273.8087,-2010.5709,58.9082, 50,_,_, 1);
	CreateDynamic3DTextLabel("Cheetah - 1000€/val", COLOR_LIME,1276.9834,-2043.0852,58.9163, 50,_,_, 1);
	CreateDynamic3DTextLabel("Bullet - 1500€/val", COLOR_LIME, 1244.3783,-2041.9926,59.7561, 50,_,_, 1);
	CreateDynamic3DTextLabel("NRG - 2000€/val", COLOR_LIME, 1249.2036,-2042.0964,59.6158, 50,_,_, 1);
	// Regitra
	CreateDynamic3DTextLabel("Èia palikite savo automobilá", COLOR_LIME,1604.9871,-1468.1709,13.5717, 50,_,_, 1);
	CreateDynamic3DTextLabel("Èia galite uþregistruoti automobilá", COLOR_LIME,1563.8010,-1554.7915,13.6372,50,_,_,1);
	//CreateDynamic3DTextLabel("Cia galite sunaikinti arba pataisyti\ndarbini automobili",COLOR_LIME,1568.0664,-1478.3700,13.1723, 50,_,_,1);
	CreateDynamic3DTextLabel("Èia galite pataisyti savo\ndarbiná automobilá",COLOR_LIME,1017.7556,-917.3123,42.4931, 50,_,_,1);
	CreateDynamic3DTextLabel("Èia galite pataisyti savo\ndarbiná automobilá",COLOR_LIME,1911.2146,-1775.0718,13.5318, 50,_,_,1);
	CreateDynamic3DTextLabel("Èia galite pataisyti savo\ndarbiná automobilá",COLOR_LIME,2456.0039,-1460.7887,24.1489, 50,_,_,1);
	CreateDynamic3DTextLabel("Sëklø Sandelis",COLOR_WHITE,-366.4687,-1423.9979,25.7266,50,_,_,1);
	CreateDynamic3DTextLabel("LSD Sandelis",COLOR_WHITE,-60.0339,47.9782,3.1103,50,_,_,1);
	CreateDynamic3DTextLabel("Ekstazio Sandelis",COLOR_WHITE,2318.1348,38.3088,26.4844,50,_,_,1);
	CreateDynamic3DTextLabel("Ginklø Sandelis",COLOR_WHITE,213.9083,1866.8762,13.1406,50,_,_,1);
	CreateDynamic3DTextLabel("Pinigø Sandelis",COLOR_WHITE,2548.2683,-1293.5137,1044.1250,50,_,_,1);
	// Garazu isejimai
	CreateDynamic3DTextLabel("Norëdami iðeiti raðykite {FF0000}/garazas",COLOR_WHITE,2524.4707,-1673.2883,15.0045,5,_,_,1);
	CreateDynamic3DTextLabel("Norëdami iðeiti raðykite {FF0000}/garazas",COLOR_WHITE,1643.8168,-1516.3147,13.1684,5,_,_,1);
	CreateDynamic3DTextLabel("Norëdami iðeiti raðykite {FF0000}/garazas",COLOR_WHITE,-1688.5576,1036.3586,45.3536,5,_,_,1);
	// Pasienis:
	CreateDynamic3DTextLabel("Spauskite [H] Norëdami sumokëti. Kelio mokestis: 50€", COLOR_LIME, 34.5019,-1536.6483,5.4900, 50,_,_, 1);
	CreateDynamic3DTextLabel("Spauskite [H] Norëdami sumokëti. Kelio mokestis: 50€", COLOR_LIME, 62.7359,-1524.6807,5.4900, 50,_,_, 1);
	// a51 vartai
	Create3DTextLabel("{CCCCCC}[Ðiauriniai vartai]\n{CCCCCC}Spauskite '{FFFFFF}~k~~GROUP_CONTROL_BWD~{CCCCCC}' kad atidarytumëte arba uþdarytumëte vartus", 0xCCCCCCAA, 135.09, 1942.37, 19.82, 10.5, 0, 0);
	Create3DTextLabel("{CCCCCC}[Rytiniai vartai]\n{CCCCCC}Spauskite '{FFFFFF}~k~~GROUP_CONTROL_BWD~{CCCCCC}' kad atidarytumëte arba uþdarytumëte vartus", 0xCCCCCCAA, 287.12, 1821.51, 18.14, 10.5, 0, 0);

		// pd ir garazas
	CreateDynamic3DTextLabel("{CCCCCC}[PD vartai]\n{CCCCCC}Spauskite '{FFFFFF}~k~~GROUP_CONTROL_BWD~{CCCCCC}' kad atidarytumëte vartus", 0xCCCCCCAA,  1544.6888427734, -1630.8145751953, 13.2048397, 10.5);
	CreateDynamic3DTextLabel("{CCCCCC}[Garaþo vartai]\n{CCCCCC}Spauskite '{FFFFFF}~k~~GROUP_CONTROL_BWD~{CCCCCC}' kad atidarytumëte arba uþdarytumëte garaþà…", 0xCCCCCCAA, 1589.328613, -1638.230591, 14.832096, 10.5);
	CreateDynamic3DTextLabel("{CCCCCC}[Kalëjimo vartai]\n{CCCCCC}Spauskite '{FFFFFF}~k~~GROUP_CONTROL_BWD~{CCCCCC}' kad atidarytumëte arba uþdarytumëte vartus", 0xCCCCCCAA, 1353.473999, 524.417663, 1068.047607, 10.5);
	CreateDynamic3DTextLabel("{CCCCCC}[Kalëjimo vartai]\n{CCCCCC}Spauskite '{FFFFFF}~k~~GROUP_CONTROL_BWD~{CCCCCC}' kad atidarytumëte arba uþdarytumëte vartus", 0xCCCCCCAA, 1353.673950, 545.417663, 1068.047607, 10.5);
	

	// zvejyba
	CreateDynamic3DTextLabel("Þvejyba", COLOR_LIME, 386.7198,-1817.888,7.884, 50,_,_, 1);
	
	CreateDynamic3DTextLabel("Transporto saugykla", COLOR_LIME, 2726.7976,-2003.9595,13.5472, 30, _, _, 1);

	// jail
	CreateDynamic3DTextLabel("{CCCCCC}[Kalëjimo vartai]\n{CCCCCC}Spauskite '{FFFFFF}~k~~GROUP_CONTROL_BWD~{CCCCCC}' kad atidarytumëte vartus", 0xCCCCCCAA, 3072.91625977,-766.00115967,10.88475513, 10.5);

	// degalines
	CreateDynamic3DTextLabel("LSD Sandelis",COLOR_WHITE,-60.0339,47.9782,3.1103,50,_,_,1);
	for(new x=0;x<17;x++) 
	{
		new kof, angle;
		new tmp = pickups[0][degaline] + x;
		switch(x)
		{
			case 0: {kof=1; angle=40;} // SF
			case 1: {kof=2; angle=337;} //Kaime
			case 2: {kof=3; angle=90;} // netoli miesto
			case 3: {kof=3; angle=90;} //Prie vinewood
			case 4: {kof=3; angle=90;} //CJ degalai
			case 5: {kof=2; angle=90;} //LAIVAMS
			case 6: {kof=6; angle=320;} // mano namas
			case 7: {kof=1; angle=225;} //sf centras
			case 8: {kof=1; angle=90;} //prie lv
			case 9: {kof=1; angle=90;} //prie lv
			case 10: {kof=2; angle=90;} //ls apacia
			case 11: {kof=3; angle=90;} // dillimore
			case 12: {kof=3; angle=90;} //oro uostas virsuj
			case 13: {kof=3; angle=90;} //uoste // laivu
			case 14: {kof=3; angle=90;} // nta
			case 15: {kof=3; angle=225;} //nta
			case 16: {kof=3; angle=225;} // oro uostas
			default: {kof=4; angle=225;} //lv
		}
		if(angle == 3)
			angle = 3;
		new magas[50];
		format(magas,50,"Degalinë\n%i.0 €/L",kof);
		CreateDynamic3DTextLabel(magas,COLOR_WHITE,PickupIDs[tmp][0],PickupIDs[tmp][1],PickupIDs[tmp][2],15,_,_,1);

	}
	printf("Tick: %i",GetTickCount());

}


stock LoadPelnai()
{
		/*new failax[64];
		format(failax,sizeof(failax),"AAAAAAAApelnai.txt");
	    if (dini_Exists(failax))
		{
  			for(new i = 0; i < 100; i++)
 			{
				new zinutz[128];
				format(zinutz,128,"pelnas[%i]",i);
				pelnas[i] = dini_Int(failax,zinutz);
			}
		}
		*/
		mysql_function_query(SQL, "Select ID,Suma From Pelnai", true, "SQL_Pelnai", "");
		/*for(new i = 0; i < 100; i++)
		{
			new zinutz[128];
			format(zinutz,128,"SELECT Suma From Pelnai Where ID =%i",i);
			mysql_query(zinutz);
			mysql_store_result();
			pelnas[i]=mysql_fetch_int();
			mysql_free_result();
		}*/
		return 1;
}