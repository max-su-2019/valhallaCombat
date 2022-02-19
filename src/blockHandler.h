#pragma once
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
/*Handling block stamina damage and perfect blocking.*/
class blockHandler {
public:

	/*Mapping of all actors in perfect blocking state =>> effective time of their perfect blocks.*/
	boost::unordered_map <RE::Actor*, float> actorsPerfectBlocking;

	/*Mapping of all actors in perfect blocking cool down =>> remaining time of the cool down.*/
	boost::unordered_map <RE::Actor*, float> actorsInBlockingCoolDown;

	/*Set of all actors who have successfully perfect blocked an attack.*/
	boost::unordered_set <RE::Actor*> actorsPerfectblockSuccessful;
	
	static blockHandler* GetSingleton()
	{
		static blockHandler singleton;
		return  std::addressof(singleton);
	}

	void update();

	void registerPerfectBlock(RE::Actor* actor);

	/*Process a single block.
	@param blocker: Actor who blocks.
	@param aggressor: Actor whose attack gets blocked.
	@param iHitflag: hitflag of the blocked hit, in int.
	@param hitData: hitdata of the blocked hit.
	@return if the block is a perfect block.*/
	bool processBlock(RE::Actor* blocker, RE::Actor* aggressor, int iHitflag, RE::HitData& hitData);

private:
	inline void guardBreak(RE::Actor* actor);

	inline void processStaminaBlock(RE::Actor* blocker, RE::Actor* aggressor, int iHitflag, RE::HitData& hitData);

	inline void processPerfectBlock(RE::Actor* blocker, RE::Actor* aggressor, int iHitflag, RE::HitData& hitData);

};