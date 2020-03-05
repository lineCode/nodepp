#include "World.h"
#include <stdlib.h>
#include <time.h>

#include "WorldSession.h"

volatile bool World::m_stopEvent = false;

World::World() {
}

World::~World() {
	//Empty the kicked session set

	//clear clicommand holder

	//clear queued session

	//VMap clear
	//MMap clear
}

void World::ClearupsBeforeStop() {
	//KickAll();
	//UpdateSessions(1);
	//sBattleGroundMgr.DeleteAllBattleGrounds();
}

WorldSession* World::FindSession(uint32_t id) const
{
	return nullptr;
}

bool World::RemoveSession(uint32_t id)
{
	return true;
}

void World::AddSession(WorldSession* s) {
	//addSessQueue.add(s);
}

void World::AddSession_(WorldSession* s) {
}

void World::AddQueuedSession(WorldSession* sess) {
}

bool World::RemoveQueuedSession(WorldSession* sess) {
	return true;
}

void World::LoadConfigSettings(bool reload) {
}

void World::SetInitialWorldSettings() {
	srand((unsigned int)time(nullptr));

	LoadConfigSettings();

	//load from db
}

void World::Update(uint32_t diff) {
	//Update the different timers

	//- Update the game time and check for shutdown time
	_UpdateGameTime();

	//Handle session updates
	UpdateSessions(diff);

	//Handle all other objects
	//update objects (maps, transport, creatures, ...)

	//sMapMgr.Update(diff);
	//BattleGroundMgr.Update(diff);

	// execute callbacks from sql queries that were queued recently
	//UpdateResultQueue();

	//Erase corpses once every 20 minuts
	//Process game events when necessary

	// and last, but not least handle ths issued cli commands
	ProcessCliCommands();

	//clearup unused GridMap objects as well as VMaps
}

void World::KickAll() {
}

void World::UpdateSessions(uint32_t idff) {
}

void World::ProcessCliCommands() {
}

void World::_UpdateGameTime() {
}
