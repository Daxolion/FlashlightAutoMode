class CfgPatches
{
    class FlashlightAutoMode
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
    };
};

class CfgMods
{
	class FlashlightAutoMode
	{
		dir = "FlashlightAutoMode";
		name = "Flashlight Auto Mode";
		version = 1.0;
		credits = "Daxolion";
		creditsJson = "FlashlightAutoMode/credits.json";
		author = "Daxolion";
		authorID = "76561198056033505"; 
		action = "https://daxolion.de";
		hideName = 0;
		hidePicture = 0;
		type = "mod";
		picture = "FlashlightAutoMode/gui/logo.paa";
		logoSmall = "FlashlightAutoMode/gui/logosmall.paa";
		logo = "FlashlightAutoMode/gui/logo.paa";
		logoOver = "FlashlightAutoMode/gui/logosmall.paa";
		tooltip = "Flashlight Auto Mode";
		overview = "Flashlight Auto Mode";
		inputs = "";
		dependencies[] = { "Game", "World", "Mission" };
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"FlashlightAutoMode/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"FlashlightAutoMode/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"FlashlightAutoMode/scripts/5_Mission"};
			};
		};
	};
};