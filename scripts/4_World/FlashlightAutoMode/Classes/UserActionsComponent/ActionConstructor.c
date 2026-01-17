/*
	* Name:			Flashlight Auto Mode
	*
	* Description:	Adds an automatic mode for weapon-mounted flashlights.
	*				When Auto Mode is active, the light turns on when the weapon is raised
	*				(or when aiming down sights / using optics), and turns off when lowered.
	*
	* Author:		Daxolion
	* Site:			https://daxolion.de/
	*
	* License:		DayZ Public License (DPL)
	* License URL:	https://www.bohemia.net/community/licenses/dayz-public-license-dpl/
	*
	* DayZ and Bohemia Interactive are trademarks of their respective owners.
	* This project is community-made and is not affiliated with or endorsed by Bohemia Interactive.
*/

modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(ActionSetWeaponFlashlightAuto);
		actions.Insert(ActionSetWeaponFlashlightManual);
	}
};
