#define MOD_MINIGAME_COUNT 10
#define LAB_COMPUTERS 3

#define TYRIMAI_LOOP_MINS 5
#define CRASH_TIME 30 // change to 30

#define TYRIMAI_CRASH_CHANCE (CRASH_TIME/TYRIMAI_LOOP_MINS) // 30 mins / loop mins

new ModsNumbers[MAX_PLAYERS][MOD_MINIGAME_COUNT][3];
new ModsResponses[MAX_PLAYERS][MOD_MINIGAME_COUNT];

new LabPickups[LAB_COMPUTERS] = {-1,-1,-1};


// do not reorder
enum TyrStatusEnum
{
    TYR_NOT_STARTED = 0,
    TYR_IN_PROGRESS = 1,
    TYR_DONE = 2,
    TYR_COMPLETED = 3, // reward redeemed
    TYR_CANCELLED = 4 // sandeliai or failure
}

new const BukleList[TyrStatusEnum][] = {"{f7746a}NEPRADËTAS", "{dff76a}VYKDOMAS", "{6af771}BAIGTAS", "{078a0d}UÞDARYTAS", "{ad036f}NUTRAUKTAS"};

// do not reorder
enum TyrTypes
{
    LAB_SATCHEL = 0,
    LAB_RPG = 1,
    LAB_BOMB = 2,
    LAB_NUKE = 3
}

enum TyrEnum
{
    TyrName[50],
    TyrUnits,
    TyrHours,
    TyrStatusEnum:TyrStatus,
    TyrTicksDone,
    TyrTicksRequired // precomputed
}

new TyrimaiConfig[TyrTypes][TyrEnum] = {
    {"Satchel Charges", 10, 4, TYR_NOT_STARTED, 0, 0},
    {"RPG", 3, 6, TYR_NOT_STARTED, 0, 0},
    {"Bomba", 1, 12, TYR_NOT_STARTED, 0, 0},
    {"Atominë bomba", 1, 12, TYR_NOT_STARTED, 0, 0}
};

enum LabEnum 
{
    Text3D:LabText,
    Text3D:ComputerText[LAB_COMPUTERS],
    ComputerStatus[LAB_COMPUTERS],
    ResearchStatus
}

new LabStatus[LabEnum];

new const Float:LabComputerPositions[LAB_COMPUTERS][3] = {
    {213.6712,1818.5769,4.5241},
    {212.4147,1822.8461,4.5141},
    {213.0116,1825.7637,4.5141}
};

/*
new const Float:KaleduKompiuteriai[][3] = {
    {-2471.3298,1536.5732,31.3344},
    {1279.3804,1503.9314,8.9203},
    {415.2677,2537.1306,17.2484},
    {-225.5418,1406.8932,68.0375},
    {-2535.0540,-688.6632,137.4203}
};

new KaleduKompiuterMapIcons[MAX_PLAYERS][sizeof(KaleduKompiuteriai)];
new KaleduPcStatus[MAX_PLAYERS][sizeof(KaleduKompiuteriai)];
*/


forward TyrimaiLoop();
public TyrimaiLoop()
{
	if(IsSandeliai())
    {
        WipeTyrimai();
        return;
    }

    if(LabStatus[ResearchStatus] == -1)
        return;

    new TyrTypes:type = TyrTypes:LabStatus[ResearchStatus];

    new computersAlive = 0;
    for(new i=0;i<LAB_COMPUTERS;i++)
    {
        if(LabStatus[ComputerStatus][i] == 1)
            computersAlive ++;
    }

    if(computersAlive == 0)
    {
        // failed!
        EndTyrimas(type, TyrStatusEnum:TYR_CANCELLED);
        return;
    }

    if(random(TYRIMAI_CRASH_CHANCE) == 0)
    {
        // computer crash!
        new computers[LAB_COMPUTERS];
        new count =0;
        for(new i;i<LAB_COMPUTERS;i++)
        {
            if(LabStatus[ComputerStatus][i] == 1)
            {
                computers[count] = i;
                count ++;
            }
        }
        new crashedComputer = computers[random(count)];
        CreateExplosion(LabComputerPositions[crashedComputer][0], LabComputerPositions[crashedComputer][1], LabComputerPositions[crashedComputer][2], 12, 2.0);
        LabStatus[ComputerStatus][crashedComputer] = 0;
        ResetLabPickups();
        if(count == 1)
        {
            new gang = PlaceOwnedBy[3];
            if(gang != -1)
            {
                new msg[128];
                format(msg,128,"[gauja] Laboratorijoje sugedo visi %i kompiuteriai! Turite %i minutes juos pataisyti.",LAB_COMPUTERS, TYRIMAI_LOOP_MINS);
                SendMessageToFamily(gang,ORANGE,msg);
            }
        }
    }

    TyrimaiConfig[type][TyrTicksDone] += computersAlive;
    if(TyrimaiConfig[type][TyrTicksDone] >= TyrimaiConfig[type][TyrTicksRequired])
    {
        TyrimaiConfig[type][TyrTicksDone] = TyrimaiConfig[type][TyrTicksRequired]; // remove overflow
        // finished!
        EndTyrimas(type, TyrStatusEnum:TYR_DONE);
    }
    else
    {
        SaveTyrimas(type, TyrStatusEnum:TYR_IN_PROGRESS);
        UpdateLabText(type);
    }
}

stock SaveTyrimas(TyrTypes:type, TyrStatusEnum:oldStatus)
{
    new query[512];
    format(query,512,"UPDATE Tyrimai SET `status`=%i, `ticks_done`=%i WHERE `type`=%i AND `status`=%i", _:TyrimaiConfig[type][TyrStatus], TyrimaiConfig[type][TyrTicksDone], _:type, _:oldStatus);
    mysql_query(query);
}

stock RedeemTyrimas(TyrTypes:type)
{
    TyrimaiConfig[type][TyrStatus] = TyrStatusEnum:TYR_COMPLETED;
    //ResetLabPickups();
    new query[256];
    format(query,sizeof(query),"UPDATE Tyrimai set `status`=%i WHERE `status` = %i AND `type` = %i",  _:TYR_COMPLETED, _:TYR_DONE, _:type);
    mysql_query(query);
}

stock EndTyrimas(TyrTypes:type, TyrStatusEnum:status)
{   
    LabStatus[ResearchStatus] = -1; // not started
    //TyrimaiConfig[type][TyrTicksDone] = 0;
    TyrimaiConfig[type][TyrStatus] = status;
    ResetLabPickups();
    new query[256];
    format(query,sizeof(query),"UPDATE Tyrimai set `status`=%i,`ticks_done`=%i WHERE `status` = 1 AND `type` = %i", _:status, TyrimaiConfig[type][TyrTicksDone], _:type);
    mysql_query(query);
    new gang = PlaceOwnedBy[3];
    if(gang != -1)
    {
        new msg[128];
        if(status == TyrStatusEnum:TYR_DONE)
            format(msg,128,"[gauja] Laboratorijoje sëkmingai pabaigtas tyrimas \"%s\"!",TyrimaiConfig[type][TyrName]);
        else
            format(msg,128,"[gauja] Laboratorijoje þlugo tyrimas \"%s\"!",TyrimaiConfig[type][TyrName]);
        SendMessageToFamily(gang,ORANGE,msg);
    }
    if(status == TyrStatusEnum:TYR_DONE && type == TyrTypes:LAB_NUKE)
    {
        CreateRocketObj();
    }
    UpdateLabText(type);
}
stock CreateRocketObj()
{
    if(NuclearBlast[RocketObj] != -1)
        DestroyObject(NuclearBlast[RocketObj]);
    NuclearBlast[RocketObj] = CreateObject(17050,268.78613281,1883.78320312,-31.09375000,0.00000000,0.00000000,0.00000000); //foguete
}

stock InitLab()
{
    LabStatus[LabText] = CreateDynamic3DTextLabel("Laboratorija", COLOR_WHITE, 222.2627,1822.9048,6.4141, 10,_,_, 1);
    for(new i;i<LAB_COMPUTERS;i++)
    {
        LabStatus[ComputerStatus][i] = 0;
        LabStatus[ComputerText][i] = Text3D:-1;
    }
    LabStatus[ResearchStatus] = -1; // not started
    NuclearBlast[RocketObj] = -1;
    for(new i;i<sizeof(TyrimaiConfig); i++)
    {
        TyrimaiConfig[TyrTypes:i][TyrTicksRequired] = TyrimaiConfig[TyrTypes:i][TyrHours] * LAB_COMPUTERS * (60 / TYRIMAI_LOOP_MINS); // 3 computers
    }
    ResetLabPickups();
    LoadLabTyrimai();
    
	SetTimer("TyrimaiLoop",TYRIMAI_LOOP_MINS*60*1000 - 5, 1);
}

stock LoadLabTyrimai()
{
    mysql_function_query(SQL, "SELECT `type`, `status`, `ticks_done` From Tyrimai where `status` IN (1, 2)", true, "SQL_LoadTyrimai", "");
}

stock PreloadTyrimas(TyrTypes:type, TyrStatusEnum:status, ticksDone)
{
    TyrimaiConfig[type][TyrStatus] = status;
    TyrimaiConfig[type][TyrTicksDone] = ticksDone;
    if(status == TyrStatusEnum:TYR_IN_PROGRESS)
    {
        LabStatus[ResearchStatus] = _:type;
        for(new i;i<LAB_COMPUTERS;i++)
        {
            LabStatus[ComputerStatus][i] = 1;
        }
        UpdateLabText(type);
    }
    if(status == TyrStatusEnum:TYR_DONE && type == TyrTypes:LAB_NUKE)
    {
        CreateRocketObj();
    }
    ResetLabPickups();
}

stock UpdateLabText(TyrTypes:type)
{
    new msg[256];
    if(LabStatus[ResearchStatus] == -1)
    {
        format(msg,256, "Laboratorija");
    }
    else
    {
        new completedBars = floatround((TyrimaiConfig[type][TyrTicksDone] * 10.0) / TyrimaiConfig[type][TyrTicksRequired], floatround_floor); // out of 10
        format(msg,sizeof(msg),"Laboratorija\nTyrimas: {54ff54}%s{1b521b}%s{FFFFFF}",str_repeat("|",completedBars), str_repeat("|",10-completedBars));
    }
    DestroyDynamic3DTextLabel(LabStatus[LabText]);
    LabStatus[LabText] = CreateDynamic3DTextLabel(msg, COLOR_WHITE, 222.2627,1822.9048,6.4141, 10,_,_, 1);
}

stock WipeTyrimai()
{
    LabStatus[ResearchStatus] = -1;
    new bool:changed = false;
    for(new i;i<sizeof(TyrimaiConfig);i++) 
    {
        if(TyrimaiConfig[TyrTypes:i][TyrStatus] == TyrStatusEnum:TYR_IN_PROGRESS || TyrimaiConfig[TyrTypes:i][TyrStatus] == TyrStatusEnum:TYR_DONE)
        {
            changed = true;
            TyrimaiConfig[TyrTypes:i][TyrStatus] = TyrStatusEnum:TYR_CANCELLED;
        }
    }
    if(NuclearBlast[RocketObj] != -1 && !DelayedNukeLaunched)
    {
        DestroyObject(NuclearBlast[RocketObj]);
        NuclearBlast[RocketObj] = -1;
    }

    if(changed)
        mysql_query("UPDATE Tyrimai set `status`=4 WHERE `status` IN (1,2)");
}


stock DestroyLabPickups() 
{
    for(new i;i<LAB_COMPUTERS;i++)
    {
        if(LabPickups[i] != -1) 
        {
            DestroyPickup(LabPickups[i]);
            LabPickups[i] = -1;
        }
        if(LabStatus[ComputerText][i] != Text3D:-1)
        {
            DestroyDynamic3DTextLabel(LabStatus[ComputerText][i]);
            LabStatus[ComputerText][i] = Text3D:-1;
        }
    }
}
stock CheckLabPickups(playerid)
{
    new computer = GetLabComputerId(playerid);
    /*new christmasComputer = GetChristmasComputerId(playerid);
    if(christmasComputer != -1)
    {
        if(KaleduPcStatus[playerid][christmasComputer] == 0)
        {
            SendInfoMessage(playerid,"~r~Tu nevykdai Kaledu misijos!");
        }
        else if(KaleduPcStatus[playerid][christmasComputer] == 2)
        {
            SendInfoMessage(playerid,"~g~Sis kompiuteris jau sukalibruotas!");
        }
        else
        {
            StartModsMinigame(playerid);
            Stop(playerid);
        }
        return true;
    }*/
    if(computer == -1)
    {
        return false;
    }
    if(LabStatus[ResearchStatus] == -1)
    {
        SendInfoMessage(playerid,"~r~Tyrimas nevyksta");
    }
    else if(LabStatus[ComputerStatus][computer] == 1) 
    {
        SendInfoMessage(playerid,"Kompiuteris dirba...");
    }
    else
    {
        new KasOwnina = PlaceOwnedBy[3]; // gun sandelis
        if(KasOwnina == -1 || KasOwnina != playerDB[playerid][pgang])
        {
            SendInfoMessage(playerid, "Jums nepriklauso ginklu sandelis!");
        }
        else
        {
            StartModsMinigame(playerid);
            Stop(playerid);
        }
    }

    return true;
}

stock FixComputer(computer)
{
    LabStatus[ComputerStatus][computer] = 1;
    ResetLabPickups();
}

stock GetLabComputerId(playerid)
{
    for(new i=0;i<LAB_COMPUTERS;i++)
    {
        if(IsPlayerInRangeOfPointEx(1.2, playerid, LabComputerPositions[i][0], LabComputerPositions[i][1], LabComputerPositions[i][2]+1.0))
        {
           return i;
        }
    }
    return -1;
}
/*
stock GetChristmasComputerId(playerid)
{
    for(new i;i<sizeof(KaleduKompiuteriai);i++)
    {
        if(IsPlayerInRangeOfPointEx(2, playerid, KaleduKompiuteriai[i][0], KaleduKompiuteriai[i][1], KaleduKompiuteriai[i][2]+1.0))
        {
           return i;
        }
    }
    return -1;
}

new kaleduPickupsCreated = 0;

stock InitKaleduKompiuteriai()
{
    if(kaleduPickupsCreated == 1)
        return;
    kaleduPickupsCreated = 1;
    for(new i;i<sizeof(KaleduKompiuteriai);i++)
    {
        CreatePickupA(19605, 14, KaleduKompiuteriai[i][0], KaleduKompiuteriai[i][1], KaleduKompiuteriai[i][2], 0);
    }
}
*/
stock ShowKaleduKompiuteriai(playerid)
{
    for(new i;i<sizeof(KaleduKompiuteriai);i++)
    {
        KaleduPcStatus[playerid][i] = 1;
        KaleduKompiuterMapIcons[playerid][i] = CreateDynamicMapIcon(KaleduKompiuteriai[i][0], KaleduKompiuteriai[i][1], KaleduKompiuteriai[i][2], 56, 0, -1, -1, playerid, 5000.0, MAPICON_GLOBAL);
    }
    Streamer_Update(playerid);
}
/*
stock CleanupKaledos(playerid)
{
    for(new i;i<sizeof(KaleduKompiuteriai);i++)
    {
        KaleduPcStatus[playerid][i] = 0;
        if(IsValidDynamicMapIcon(KaleduKompiuterMapIcons[playerid][i]))
        {
            DestroyDynamicMapIcon(KaleduKompiuterMapIcons[playerid][i]);
            KaleduKompiuterMapIcons[playerid][i] = -1;
        }
    }
}
*/
stock ResetLabPickups()
{
    DestroyLabPickups();
    for(new i;i<LAB_COMPUTERS;i++)
    {
        if(LabPickups[i] == -1) 
        {
            new type = LabStatus[ComputerStatus][i] == 1 ? 19606 : 19605;
            LabPickups[i] = CreatePickupA(type, 14, LabComputerPositions[i][0], LabComputerPositions[i][1], LabComputerPositions[i][2], 0);
        }
        new text[24];
        if(LabStatus[ResearchStatus] == -1)
        {
            format(text,24,"...");
        }
        else
        {
            if(LabStatus[ComputerStatus][i] == 1)
            {
                format(text,24,"Dirba...");
            }
            else
            {
                format(text,24,"x_x");
            }
        }
        LabStatus[ComputerText][i] = CreateDynamic3DTextLabel(text, COLOR_WHITE, LabComputerPositions[i][0], LabComputerPositions[i][1], LabComputerPositions[i][2]+1.0, 5,_,_, 1);
    }
}

stock GenerateModsNumbers(playerid) 
{
    for(new i=0;i<MOD_MINIGAME_COUNT;i++)
    {
        ModsNumbers[playerid][i][0] = random(10);
        ModsNumbers[playerid][i][1] = random(2);
        ModsNumbers[playerid][i][2] = random(10);

        ModsResponses[playerid][i] = -1;
    }
}

stock ModNumsToString(nums[], response)
{
    new str[50];
    new sign = nums[1] == 1 ? '+' : '-';
    format(str,50,"{00b303}MOD(|{b3b300}%i%c%i{00b303}|){FFFFFF} = ", nums[0], sign, nums[2]);
    if(response != -1)
        format(str,50,"%s%i", str, response);
    return str;
}

stock GetModsResult(nums[])
{
    if(nums[1] == 1)
        return absex(nums[0] + nums[2]) % 10;
    else
       return absex(nums[0] - nums[2]) % 10;
}

stock absex(num)
{
    return num > 0 ? num : -num;
}

stock CheckModsResponses(playerid) 
{
    for(new i;i<MOD_MINIGAME_COUNT; i++)
    {
        if(ModsResponses[playerid][i] != GetModsResult(ModsNumbers[playerid][i]))
            return false;
    }
    return true;
}

stock ShowModsDialog(playerid)
{
    new str[2048];
    format(str,sizeof(str),"Instrukcijos\n");
    new bool:selector = false;
    for(new i;i<MOD_MINIGAME_COUNT;i++)
    {
        format(str,sizeof(str), "%s%s\n", str, ModNumsToString(ModsNumbers[playerid][i], ModsResponses[playerid][i]));
        if(ModsResponses[playerid][i] == -1 && !selector)
        {
            selector = true;
            for(new opts;opts<10;opts++)
            {
                format(str,sizeof(str),"%s{c702b3}%i\n",str, opts);
            }
        }
    }
    ShowPlayerDialog(playerid, 14305, DIALOG_STYLE_LIST, "Kalibravimas", str, "Gerai", "Atsaukti");
}
stock HandleValdymoPunktas(playerid)
{
	if(IsSandeliai())
    {
        return SendInfoMessage(playerid, "~r~Laboratorija nedirba!");
    }

    new KasOwnina = PlaceOwnedBy[3]; // gun sandelis
    if(KasOwnina == -1)
    {
        return SendInfoMessage(playerid,"Sveikiname teisesauga issaugojus ginklu sandeli!");
    }

    if(KasOwnina != playerDB[playerid][pgang])
    {
        return SendInfoMessage(playerid, "Jums nepriklauso ginklu sandelis!");
    }

    ShowPlayerDialog(playerid, 16733, DIALOG_STYLE_LIST, "Laboratorija", "Informacija\nPradëti tyrimà\nTyrimø progresas\nAtsiimti ginklus", "Gerai", "Atsaukti");

    return 1;
}

stock HandleValdymoPunktoDialog(playerid, listitem)
{
    new KasOwnina = PlaceOwnedBy[3]; // gun sandelis
    if(KasOwnina == -1)
    {
        return SendInfoMessage(playerid,"Sveikiname teisesauga issaugojus ginklu sandeli!");
    }
    /*if(KasOwnina != playerDB[playerid][pgang])
    {
        return SendInfoMessage(playerid, "Jums nepriklauso ginklu sandelis!");
    }*/

    if(listitem == 0)
    {
        ShowPlayerDialog(playerid, 16734, DIALOG_STYLE_MSGBOX, "Laboratorija", "{FFFFFF}Ðioje laboratorijoje jûs galite atlikti tyrimus ir iðrasti naujus ginklus.\n\n\n\
        Tyrimà pradëti gali tik gaujos vadas, bet prisidëti prie tyrimo gali kiekvienas gaujos narys.\n\
        Prasidëjus tyrimui turësite priþiûrëti tris kompiuterius. Sugedus vienam ið kompiuteriø suletës tyrimo progresas, o sugedus visiems trims, tyrimo duomenys bus prarasti.\n\n\
        Tyrimo pabaigoje gaujos vadas galës atsiimti ginklus. Tyrimø duomenys bus automatiðkai iðtrinti prasidëjus kitiems sandëliams.", "Atgal", "");
    }
    if(listitem == 1)
    {
        new tyrimai[4096];
        format(tyrimai,sizeof(tyrimai),"Tyrimas\tKiekis\tBûklë\tTrukmë\n");
        for(new i;i<sizeof(TyrimaiConfig);i++)
        {
            new TyrTypes:type = TyrTypes:i;
            new TyrStatusEnum:status = TyrimaiConfig[type][TyrStatus];
            format(tyrimai,sizeof(tyrimai),"%s%s\t%i vnt\t%s\t%i val\n",tyrimai, TyrimaiConfig[type][TyrName], TyrimaiConfig[type][TyrUnits], BukleList[status], TyrimaiConfig[type][TyrHours]);
        }
        ShowPlayerDialog(playerid,16736, DIALOG_STYLE_TABLIST_HEADERS, "Tyrimai", tyrimai, "Pradëti", "Atgal");
    }
    if(listitem == 2)
    {
        // show all statuses, why not
        new tyrimai[4096];
        for(new i;i<sizeof(TyrimaiConfig);i++)
        {
            new TyrTypes:type = TyrTypes:i;
            new TyrStatusEnum:status = TyrimaiConfig[type][TyrStatus];
            new done = TyrimaiConfig[type][TyrTicksDone];
            new required = TyrimaiConfig[type][TyrTicksRequired];
            new Float:completed = (done * 1.0) / required;
            new Float:likoVal = TyrimaiConfig[type][TyrHours] * (1-completed);
            new likoh = floatround(likoVal, floatround_floor);
            new likom = floatround((likoVal - likoh)*60, floatround_floor);
            format(tyrimai,sizeof(tyrimai),"%s\n\
            {FFFFFF}Tyrimas:\t{95d7f0}%s\n\
            {FFFFFF}Bûklë:\t\t%s\n\
            {FFFFFF}Progresas:\t%i/%i (%.1f%%)\nLikæs laikas:\t%i val %i min\n\n", tyrimai, TyrimaiConfig[type][TyrName],BukleList[status], done, required, completed * 100.0, likoh, likom);

        }
        ShowPlayerDialog(playerid,16735, DIALOG_STYLE_MSGBOX, "Tyrimai", tyrimai, "Atnaujinti", "Atgal");

    }
    if(listitem == 3)
    {
        new tyrimai[4096];
        format(tyrimai,sizeof(tyrimai),"Tyrimas\tKiekis\tBûklë\tTrukmë\n");
        for(new i;i<sizeof(TyrimaiConfig);i++)
        {
            new TyrTypes:type = TyrTypes:i;
            new TyrStatusEnum:status = TyrimaiConfig[type][TyrStatus];
            format(tyrimai,sizeof(tyrimai),"%s%s\t%i vnt\t%s\t%i val\n",tyrimai, TyrimaiConfig[type][TyrName], TyrimaiConfig[type][TyrUnits], BukleList[status], TyrimaiConfig[type][TyrHours]);
        }
        ShowPlayerDialog(playerid,16737, DIALOG_STYLE_TABLIST_HEADERS, "Tyrimai", tyrimai, "Paimti", "Atgal");
    }

    return 1;
}
stock TakeTyrimoItem(playerid, tyrimoid)
{
    new KasOwnina = PlaceOwnedBy[3]; // gun sandelis
    if(KasOwnina == -1 || KasOwnina != playerDB[playerid][pgang] || IsSandeliai())
    {
        SendInfoMessage(playerid,"~r~Negali paimti ginklo!");
        HandleValdymoPunktas(playerid);
        return;
    }
            
    if(strcmp(FamilyInfo[KasOwnina][FamilyLeader],ReturnName(playerid),true) != 0 && strcmp(FamilyInfo[KasOwnina][FamilySubstitute],ReturnName(playerid),true) != 0)
    {
        SendInfoMessage(playerid, "Ginklus paimti gali tik gaujos vadas!");
        HandleValdymoPunktas(playerid);
        return;
    }
    new TyrTypes:type = TyrTypes:tyrimoid;

    if(TyrimaiConfig[type][TyrStatus] != TyrStatusEnum:TYR_DONE)
    {
        SendInfoMessage(playerid,"~r~Sis tyrimas nepabaigtas!");
        HandleValdymoPunktas(playerid);
        return;
    }

    if(type == TyrTypes:LAB_SATCHEL)
    {
        GivePlayerWeaponEx(playerid,39,TyrimaiConfig[type][TyrUnits]); // Satelite
        RedeemTyrimas(type);
    }
    else if(type == TyrTypes:LAB_RPG)
    {
        GivePlayerWeaponEx(playerid,35,TyrimaiConfig[type][TyrUnits]); // RPG
        RedeemTyrimas(type);
    }
    else if(type == TyrTypes:LAB_BOMB)
    {
        SendInfoMessage(playerid,"Pasiemei bomba! Pakrauk ja i automobilio bagazine.");
        SetPlayerAttachedObject( playerid, SLOT_KROVINYS, 1575, 1, -0.064613, 0.520760, 0.000000, 0.000000, 84.217391, 0.000000, 1.000000, 1.000000, 1.000000 );
        SetPVarInt(playerid,"Bomba",1);
        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 1, 1, 1, 1, 1);
        RedeemTyrimas(type);
    }
    else if(type == TyrTypes:LAB_NUKE)
    {
        new msg[256];
        format(msg,256,"Nustatyti pozicijà\nNustatyti laikmatá (%i min)\n{ff5733}Paleisti atominæ bombà", RocketDelay);
        ShowPlayerDialog(playerid, 7444, DIALOG_STYLE_LIST, "BOMBOS VALDYMO PUNKTAS", msg, "Gerai","Atsaukti");
    }
    else
    {
        SendInfoMessage(playerid,"~r~Ivyko klaida!");
    }

}
stock IsNukeThere()
{
	/*new year,month,day;
	getdate(year, month, day);
	if(month == 5 && day <= 15 && NuclearBlast[NukeInProgress] == 0)
		return true;*/
	return TyrimaiConfig[LAB_NUKE][TyrStatus] == TyrStatusEnum:TYR_DONE;
}


stock IsSandeliai()
{
    new hour,minute,second;
    gettime(hour,minute,second);
    new WeekDay = GetWeekDay();
    new bool:WedSat = (WeekDay == 2 || WeekDay == 6);
    return (WedSat && (hour == 14 && minute > 0));
}
stock StartTyrimas(playerid, tyrimoid)
{
    new KasOwnina = PlaceOwnedBy[3]; // gun sandelis
    if(KasOwnina == -1 || KasOwnina != playerDB[playerid][pgang] || IsSandeliai())
    {
        SendInfoMessage(playerid,"~r~Negali pradeti tyrimo!");
        HandleValdymoPunktas(playerid);
        return;
    }
            
    if(strcmp(FamilyInfo[KasOwnina][FamilyLeader],ReturnName(playerid),true) != 0 && strcmp(FamilyInfo[KasOwnina][FamilySubstitute],ReturnName(playerid),true) != 0)
    {
        SendInfoMessage(playerid, "Tyrima pradeti gali tik gaujos vadas!");
        HandleValdymoPunktas(playerid);
        return;
    }
    if(LabStatus[ResearchStatus] != -1)
    {
        SendInfoMessage(playerid,"~r~Tyrimas jau vyksta!");
        HandleValdymoPunktas(playerid);
        return;
    }
    new TyrTypes:type = TyrTypes:tyrimoid;

    if(TyrimaiConfig[type][TyrStatus] == TyrStatusEnum:TYR_DONE)
    {
        SendInfoMessage(playerid,"~r~Sis tyrimas jau pabaigtas!");
        HandleValdymoPunktas(playerid);
        return;
    }

    LabStatus[ResearchStatus] = tyrimoid;
    for(new i;i<LAB_COMPUTERS;i++)
    {
        LabStatus[ComputerStatus][i] = 1;
    }
    TyrimaiConfig[type][TyrTicksDone] = 0;
    TyrimaiConfig[type][TyrStatus] = TyrStatusEnum:TYR_IN_PROGRESS;
    ResetLabPickups();
    SendInfoMessage(playerid,"~g~Pradejai tyrima!");
    new query[512];
    format(query,512,"INSERT INTO Tyrimai (`type`,`status`,`ticks_done`,`ticks_total`,`started_by`,`start_time`) VALUES (%i, %i, %i, %i, '%s', NOW())",
        _:type, _:TyrimaiConfig[type][TyrStatus], TyrimaiConfig[type][TyrTicksDone], TyrimaiConfig[type][TyrTicksRequired], ReturnName(playerid));
    mysql_query(query);
    new gang = PlaceOwnedBy[3];
    if(gang != -1)
    {
        new msg[128];
        format(msg,128,"[gauja] Laboratorijoje pradëtas tyrimas \"%s\"! Planuojama trukmë: %i valandos.",TyrimaiConfig[type][TyrName], TyrimaiConfig[type][TyrHours]);
        SendMessageToFamily(gang,ORANGE,msg);
    }
}

stock HandleModsResponse(playerid, listitem)
{
    if(listitem == 0) 
    {
        ShowPlayerDialog(playerid, 14306, DIALOG_STYLE_MSGBOX, "Instrukcijos", "Tavo uþduotis - sukalibruoti sugædusi kompiuterá.\n\n\
        Tam turësi pasitelkti savo matematinius sugebëjimus ir apskaièiuoti MOD funkcijos rezultatà. Ði funkcija turi gràþinti paskutiná rezultato skaitmená.\n\n\
        Pavyzdþiai:\n\
        {00b303}MOD(|{b3b300}7+8{00b303}|){FFFFFF} = 1{c702b3}5{FFFFFF} = {c702b3}5\n\
        {00b303}MOD(|{b3b300}1-4{00b303}|){FFFFFF} = -{c702b3}3{FFFFFF} = {c702b3}3\n\
        {00b303}MOD(|{b3b300}2+4{00b303}|){FFFFFF} = {c702b3}6\n", "Atgal", "");
    }
    else
    {
        new completed = 0;
        for(new i; i < MOD_MINIGAME_COUNT; i++)
        {
            if(ModsResponses[playerid][i] == -1)
                break;
            
            completed ++;
        }
        if(completed == 10)
        {
            SendInfoMessage(playerid, "Klaida!");
            return;
        }
        // valid options start after all completed ids, limited to 9
        // Pagalba, MOD(..) = 1, MOD(..) = 2, MOD(..) =, 0, 1, 2, 3, ..., 9, MOD(..)=, MOD(..)=
        new firstValidOption = 2 + completed;
        new lastValidOption = firstValidOption + 9;
        if(listitem < firstValidOption || listitem > lastValidOption)
        {
            SendInfoMessage(playerid,"~r~Netinkamas pasirinkimas");
            ShowModsDialog(playerid);
            return;
        }
        new selected = listitem - firstValidOption;
        ModsResponses[playerid][completed] = selected;
        completed ++;
        if(completed == 10)
        {
            OnModsFinished(playerid);
        }
        else
        {
            ShowModsDialog(playerid);
        }
    }
}

stock OnModsFinished(playerid)
{
    if(CheckModsResponses(playerid))
    {
        new computer = GetLabComputerId(playerid);
        /* new christmasComputer = GetChristmasComputerId(playerid);
        if(christmasComputer != -1)
        {
            KaleduPcStatus[playerid][christmasComputer] = 2;
            new count = 0;
            for(new i;i<sizeof(KaleduKompiuteriai);i++)
            {
                if( KaleduPcStatus[playerid][i] == 2)
                    count++;
            }
            if(count == sizeof(KaleduKompiuteriai))
                SendInfoMessage(playerid,"~g~Sukalibruoti visi radarai!");
            else
                SendInfoMessage(playerid,"~g~Sukalibruota!");
            return;
        }*/
        if(computer == -1)
        {
            SendInfoMessage(playerid, "~r~Nuejai per toli!");
        }
        else if(LabStatus[ComputerStatus][computer] == 1)
        {
            SendInfoMessage(playerid,"Kompiuteris jau sukalibruotas!");
        }
        else
        {
            FixComputer(computer);
            SendInfoMessage(playerid,"~g~Sukalibruota!");
        }
    }
    else
    {
        SendInfoMessage(playerid,"~r~Kalibravimo klaida!");
    }
}

stock StartModsMinigame(playerid)
{
    GenerateModsNumbers(playerid);
    ShowModsDialog(playerid);
}

