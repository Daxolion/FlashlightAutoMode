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

modded class ActionTurnOnWeaponFlashlight
{
	void ActionTurnOnWeaponFlashlight()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_ITEM_ON;
		m_Text = "#switch_on";
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
		if (Class.CastTo(weapon, item))
		{
			if (weapon.FAM_IsWeaponFlashlightAutoMode())
			{
				return false;
			}
		}

		ItemBase flashlight = Weapon_Base.FAM_FindWeaponFlashlight(item);
		if (!flashlight)
		{
			return false;
		}
		if (!flashlight.HasEnergyManager())
		{
			return false;
		}
		ComponentEnergyManager em = flashlight.GetCompEM();
		if (!em)
		{
			return false;
		}
		if (!em.CanWork())
		{
			return false;
		}
		if (em.IsSwitchedOn())
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
		ItemBase flashlight = Weapon_Base.FAM_FindWeaponFlashlight(action_data.m_MainItem);
		if (!flashlight)
		{
			return;
		}

		if (!flashlight.HasEnergyManager())
		{
			return;
		}

		ComponentEnergyManager em = flashlight.GetCompEM();
		if (!em)
		{
			return;
		}

		if (!em.CanWork())
		{
			return;
		}

		if (em.IsSwitchedOn() == false && em.CanSwitchOn())
		{
			em.SwitchOn();
		}

		Weapon_Base weapon = Weapon_Base.Cast(action_data.m_MainItem);
		if (weapon)
		{
			if (weapon.FAM_IsWeaponFlashlightAutoMode())
			{
				weapon.FAM_SetWeaponFlashlightAutoMode(false);
			}
			weapon.FlashlightOn();
		}
	}

};
