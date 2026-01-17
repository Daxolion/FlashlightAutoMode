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

modded class DayZPlayerImplement
{
	protected bool m_FAM_LastRaised;
	protected bool m_FAM_LastOptics;
	protected bool m_FAM_StateInitialized;

	override bool ModCommandHandlerAfter(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
		super.ModCommandHandlerAfter(pDt, pCurrentCommandID, pCurrentCommandFinished);

		bool result = super.ModCommandHandlerAfter(pDt, pCurrentCommandID, pCurrentCommandFinished);
		PlayerBase player = PlayerBase.Cast(this);
		if (!player)
		{
			return result;
		}

		bool raisedNow = player.IsRaised();
		bool opticsNow = player.IsInOptics();

		if (!m_FAM_StateInitialized)
		{
			m_FAM_StateInitialized = true;
			m_FAM_LastRaised = raisedNow;
			m_FAM_LastOptics = opticsNow;
			Weapon_Base.FAM_ApplyWeaponFlashlightAuto(player, raisedNow, opticsNow);
			return result;
		}

		if (raisedNow == m_FAM_LastRaised)
		{
			if (opticsNow == m_FAM_LastOptics)
			{
				return result;
			}
		}

		m_FAM_LastRaised = raisedNow;
		m_FAM_LastOptics = opticsNow;
		Weapon_Base.FAM_ApplyWeaponFlashlightAuto(player, raisedNow, opticsNow);
		return result;
	}
};

