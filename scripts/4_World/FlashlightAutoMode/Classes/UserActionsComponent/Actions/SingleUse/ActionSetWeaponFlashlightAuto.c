/*
	* Name:			Flashlight Auto Mode
	*
	* Description:	Adds an automatic mode for weapon-mounted flashlights.
	*				When Auto Mode is active, the light turns on when the weapon is raised
	*				(or when aiming down sights / using optics), and turns off when lowered.
	*
	* Author:		Daxolion
	*
	* License:		DayZ Public License (DPL)
	* License URL:	https://www.bohemia.net/community/licenses/dayz-public-license-dpl/
	*
	* DayZ and Bohemia Interactive are trademarks of their respective owners.
	* This project is community-made and is not affiliated with or endorsed by Bohemia Interactive.
*/

class ActionSetWeaponFlashlightAuto : ActionSingleUseBase
{
	ItemBase m_FAM_Flashlight;

	void ActionSetWeaponFlashlightAuto()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ITEM_ON;
		m_Text = "Flashlight: Auto";
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override bool HasTarget()
	{
		return false;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		Weapon_Base weapon;
		if (!Class.CastTo(weapon, item))
		{
			return false;
		}
		if (weapon.FAM_IsWeaponFlashlightAutoMode())
		{
			return false;
		}
		m_FAM_Flashlight = Weapon_Base.FAM_FindWeaponFlashlight(item);
		if (!m_FAM_Flashlight)
		{
			return false;
		}
		if (!m_FAM_Flashlight.HasEnergyManager())
		{
			return false;
		}
		ComponentEnergyManager em = m_FAM_Flashlight.GetCompEM();
		if (!em)
		{
			return false;
		}
		if (!em.CanWork())
		{
			return false;
		}
		if (!em.CanSwitchOn())
		{
			return false;
		}
		return true;
	}

	override void OnExecuteServer(ActionData action_data)
	{
		Weapon_Base weapon;
		if (!Class.CastTo(weapon, action_data.m_MainItem))
		{
			return;
		}
		weapon.FAM_SetWeaponFlashlightAutoMode(true);
	}

};
