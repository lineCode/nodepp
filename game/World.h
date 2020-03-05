#pragma once
#include <cstdint>

class WorldSession;

const int WORLD_SLEEP_CONST = 50;

class World
{
private:
	World();
	~World();
	World(const World&) = delete;
	World& operator=(const World&) = delete;
public:
	static World& Instance() {
		//thread safe
		static World world;
		return world;
	}

public:
	void ClearupsBeforeStop();

	WorldSession* FindSession(uint32_t id) const;
	bool RemoveSession(uint32_t id);
	void AddSession(WorldSession* s);
	void AddSession_(WorldSession* s);
	void AddQueuedSession(WorldSession* sess);
	bool RemoveQueuedSession(WorldSession* sess);
	void LoadConfigSettings(bool reload = false);
	void SetInitialWorldSettings();

	void Update(uint32_t diff);
	void UpdateSessions(uint32_t diff);

	void KickAll();

	void _UpdateGameTime();
	void ProcessCliCommands();

	static bool IsStopped() { return m_stopEvent; }


	static volatile bool m_stopEvent;
};

#define sWorld World::Instance()
