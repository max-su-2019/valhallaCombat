#pragma once
#include "lib/robin_hood.h"
#include <mutex>
/*Handling block stamina damage and perfect blocking.*/
class blockHandler {
public:

	/*Mapping of all actors in perfect blocking state =>> effective time of their perfect blocks.*/
	robin_hood::unordered_map <RE::Actor*, float> actorsPerfectBlocking;

	/*Mapping of all actors in perfect blocking cool down =>> remaining time of the cool down.*/
	robin_hood::unordered_map <RE::Actor*, float> actorsInBlockingCoolDown;

	/*Set of all actors who have successfully perfect blocked an attack.*/
	robin_hood::unordered_set <RE::Actor*> actorsPerfectblockSuccessful;

	static blockHandler* GetSingleton()
	{
		static blockHandler singleton;
		return  std::addressof(singleton);
	}

	void update();

	/*Register a perfect block when an actor tries to block. Put the blocker into the active perfect blocker set and start timing.
	@param actor actor whose block is registered as a perfect block.*/
	void registerPerfectBlock(RE::Actor* actor);

	/*Process a single block.
	@param blocker: Actor who blocks.
	@param aggressor: Actor whose attack gets blocked.
	@param iHitflag: hitflag of the blocked hit, in integer.
	@param hitData: hitdata of the blocked hit.
	@param realDamage: real damage of this blocked hit.
	@return if the block is a perfect block.*/
	bool processBlock(RE::Actor* blocker, RE::Actor* aggressor, int iHitflag, RE::HitData& hitData, float realDamage);

private:
	static inline std::mutex mtx;
	/*Process a stamina block.
	Actor with enough stamina can negate all incoming health damage with stamina. 
	Actor without enough stamina will triggerStagger and receive partial damage.*/
	void processStaminaBlock(RE::Actor* blocker, RE::Actor* aggressor, int iHitflag, RE::HitData& hitData, float realDamage);

	/*Process perfect block does not take in real damage, as parry damage is re-adjusted.*/
	void processPerfectBlock(RE::Actor* blocker, RE::Actor* aggressor, int iHitflag, RE::HitData& hitData);

	/*Play VFX, SFX and screenShake for successful perfect block.*/
	inline void playPerfectBlockVFX(RE::Actor* blocker, RE::Actor* aggressor, int iHitFlag, bool blockBrokeGuard);
	inline void playPerfectBlockSFX(RE::Actor* blocker, int iHitFlag, bool blockBrokeGuard);
	inline void playPerfectBlockScreenShake(RE::Actor* blocker, int iHitFlag, bool blockBrokeGuard);
};

namespace Utils
{
	namespace sound
	{

	}
}