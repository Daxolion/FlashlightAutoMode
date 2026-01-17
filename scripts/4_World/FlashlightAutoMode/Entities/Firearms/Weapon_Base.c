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

modded class Weapon_Base
{
	protected bool m_FAM_WeaponFlashlightAutoMode;

	void Weapon_Base()
	{
		RegisterNetSyncVariableBool("m_FAM_WeaponFlashlightAutoMode");
	}

	bool FAM_IsWeaponFlashlightAutoMode()
	{
		return m_FAM_WeaponFlashlightAutoMode;
	}

	void FAM_SetWeaponFlashlightAutoMode(bool enabled)
	{
		if (m_FAM_WeaponFlashlightAutoMode == enabled)
		{
			return;
		}
		m_FAM_WeaponFlashlightAutoMode = enabled;
		SetSynchDirty();
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		int version = 1;
		ctx.Write(version);
		ctx.Write(m_FAM_WeaponFlashlightAutoMode);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
		{
			return false;
		}

		int storedVersion;
		if (!ctx.Read(storedVersion))
		{
			return true;
		}

		if (storedVersion >= 1)
		{
			if (!ctx.Read(m_FAM_WeaponFlashlightAutoMode))
			{
				m_FAM_WeaponFlashlightAutoMode = false;
				return true;
			}
		}

		return true;
	}

	static ItemBase FAM_FindWeaponFlashlight(ItemBase weaponItem)
	{
		if (!weaponItem)
		{
			return null;
		}

		ItemBase flashlight = ItemBase.Cast(weaponItem.FindAttachmentBySlotName("weaponFlashlight"));
		if (flashlight)
		{
			return flashlight;
		}

		flashlight = ItemBase.Cast(weaponItem.FindAttachmentBySlotName("pistolFlashlight"));
		if (flashlight)
		{
			return flashlight;
		}

		return null;
	}

	static void FAM_ApplyWeaponFlashlightAuto(PlayerBase player, bool weaponRaised, bool opticsActive)
	{
		if (!player)
		{
			return;
		}

		Weapon_Base weapon = Weapon_Base.Cast(player.GetItemInHands());
		if (!weapon)
		{
			return;
		}

		if (!weapon.FAM_IsWeaponFlashlightAutoMode())
		{
			return;
		}

		ItemBase flashlight = FAM_FindWeaponFlashlight(weapon);
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

		bool shouldBeOn = false;
		if (weaponRaised)
		{
			shouldBeOn = true;
		}
		if (opticsActive)
		{
			shouldBeOn = true;
		}

		if (shouldBeOn)
		{
			if (em.IsSwitchedOn() == false && em.CanSwitchOn())
			{
				em.SwitchOn();
			}
			return;
		}

		if (em.IsSwitchedOn() && em.CanSwitchOff())
		{
			em.SwitchOff();
		}
	}

	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionSetWeaponFlashlightAuto);
		AddAction(ActionSetWeaponFlashlightManual);
	}
};
