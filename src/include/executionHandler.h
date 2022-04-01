#pragma once
#include "lib/robin_hood.h"
/*Class handling all executions*/
class executionHandler {
public:

	bool playerCanExecute;
	/*Mapping of all active executors -> people being executed.*/
	robin_hood::unordered_set<RE::Actor*> activeExecutor;
	static executionHandler* GetSingleton()
	{
		static executionHandler singleton;
		return  std::addressof(singleton);
	}

	/*Play an execution idle animation.
	@param executor: the actor the execute.
	@param victim: the actor to be executed.
	@param executionIdle: the execution idle to be played.*/
	void playExecutionIdle(RE::Actor* executor, RE::Actor* victim, RE::TESIdleForm* executionIdle);
	void playExecutionIdle(RE::Actor* executor, RE::Actor* victim, std::vector<RE::TESIdleForm*> executionIdleV);
	/*Attempt an execution. Help aggressor decide which killmove to use
	based on aggressor/victim's relative position, rotation, and victim's race.
	Also performs a check on whether the aggressor can execute victim.
	@param executor: actor to perform killmove.
	@param victim: actor to be executed.*/
	void attemptExecute(RE::Actor* executor, RE::Actor* victim);

	/*Conclude an execution, cancle executor and victim's ghost state. Optionally apply buff onto executor.*/
	void concludeExecution(RE::Actor* executor);

private:
	void executeHumanoid(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeDraugr(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeFalmer(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeSpider(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeGargoyle(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeGiant(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeBear(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeSabreCat(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeWolf(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeTroll(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeHagraven(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeSpriggan(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeBoar(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeRiekling(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeAshHopper(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeSteamCenturion(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeDwarvenBallista(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeChaurusFlyer(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeLurker(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);
	void executeDragon(RE::Actor* executer, RE::Actor* victim, RE::WEAPON_TYPE weaponType);

};

namespace Utils
{
	inline void sendConsoleCommand(std::string a_command)
	{
		const auto scriptFactory = RE::IFormFactory::GetConcreteFormFactoryByType<RE::Script>();
		const auto script = scriptFactory ? scriptFactory->Create() : nullptr;
		if (script) {
			const auto selectedRef = RE::Console::GetSelectedRef();
			script->SetCommand(a_command);
			script->CompileAndRun(selectedRef.get());
			delete script;
		}
	}

	/*Whether the actor's back is facing the other actor's front.
	@param actor1: actor whose facing will be returned
	@param actor2: actor whose relative location to actor1 will be calculated.*/
	inline bool isBackFacing(RE::Actor* actor1, RE::Actor* actor2) {
		auto angle = actor1->GetHeadingAngle(actor2->GetPosition(), false);
		if (90 < angle || angle < -90) {
			return true;
		}
		else {
			return false;
		}
	}
	/*Get a random element from this vector.
	@param in the vector containing strings.
	@return a random element from the vector.*/
	inline std::string getRandomStr(std::vector<std::string> in) {
		return in[rand() % in.size()];
	}

	/*Get a random element from this vector.
	@param in the vector containing strings.
	@return a random element from the vector.*/
	inline RE::TESIdleForm* getRandomIdle(std::vector<RE::TESIdleForm*> in) {
		DEBUG("getting random idle");
		DEBUG("in size: {}", in.size());
		return in[rand() % in.size()];
	}



	typedef void(_fastcall* _setIsGhost)(RE::Actor* actor, bool isGhost);
	static REL::Relocation<_setIsGhost> setIsGhost{ REL::ID(36287) };

	inline bool playPairedIdle(RE::AIProcess* proc, RE::Actor* attacker, RE::DEFAULT_OBJECT smth, RE::TESIdleForm* idle, bool a5, bool a6, RE::TESObjectREFR* target)
	{
		using func_t = decltype(&playPairedIdle);
		REL::Relocation<func_t> func{ REL::ID(38290) };
		return func(proc, attacker, smth, idle, a5, a6, target);
	}
}
