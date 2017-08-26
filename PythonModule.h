#pragma once

const char *callbackNames[] = {
	"on_server_initialise",
	"on_server_shutdown",
	"on_server_frame",
	"on_plugin_command",
	"on_incoming_connection",
	"on_client_script_data",
	"on_player_connect",
	"on_player_disconnect",
	"on_player_request_class",
	"on_player_request_spawn",
	"on_player_spawn",
	"on_player_death",
	"on_player_update",
	"on_player_request_enter_vehicle",
	"on_player_enter_vehicle",
	"on_player_exit_vehicle",
	"on_player_name_change",
	"on_player_state_change",
	"on_player_action_change",
	"on_player_on_fire_change",
	"on_player_crouch_change",
	"on_player_game_keys_change",
	"on_player_begin_typing",
	"on_player_end_typing",
	"on_player_away_change",
	"on_player_message",
	"on_player_command",
	"on_player_private_message",
	"on_player_key_bind_down",
	"on_player_key_bind_up",
	"on_player_spectate",
	"on_player_crash_report",
	"on_vehicle_update",
	"on_vehicle_explode",
	"on_vehicle_respawn",
	"on_object_shot",
	"on_object_touched",
	"on_pickup_pick_attempt",
	"on_pickup_picked",
	"on_pickup_respawn",
	"on_checkpoint_entered",
	"on_checkpoint_exited",
	"on_entity_pool_change",
	"on_server_performance_report"
};

void RegisterFunctions(py::module functions)
{
	/**
	 * Plugin system
	 */

	functions.def("get_server_version", []() {
		return vcmpFunctions->GetServerVersion();
	});
	functions.def("get_server_settings", []() -> py::object {
		ServerSettings settings;
		if (vcmpFunctions->GetServerSettings(&settings) == vcmpErrorNone)
			return py::make_tuple(settings.serverName, settings.maxPlayers, settings.port, settings.flags);
		return py::none();
	});
	/*functions.def("export_functions", [](int32_t pluginId, const void** functionList, size_t size) {
		return vcmpFunctions->ExportFunctions(pluginId, functionList, size);
	});*/
	functions.def("get_number_of_plugins", []() {
		return vcmpFunctions->GetNumberOfPlugins();
	});
	functions.def("get_plugin_info", [](int32_t pluginId) -> py::object {
		PluginInfo pluginInfo;
		if (vcmpFunctions->GetPluginInfo(pluginId, &pluginInfo) == vcmpErrorNone)
			return py::make_tuple(pluginInfo.name, pluginInfo.pluginVersion, pluginInfo.apiMajorVersion, pluginInfo.apiMinorVersion);
		return py::none();
	});
	functions.def("find_plugin", [](const char* pluginName) {
		return vcmpFunctions->FindPlugin(pluginName);
	});
	functions.def("send_plugin_command", [](uint32_t commandIdentifier, const char* command) {
		return vcmpFunctions->SendPluginCommand(commandIdentifier, "%s", command);
	});
	functions.def("get_time", []() {
		return vcmpFunctions->GetTime();
	});
	functions.def("log_message", [](const char* message) {
		return vcmpFunctions->LogMessage("%s", message);
	});
	functions.def("get_last_error", []() {
		return vcmpFunctions->GetLastError();
	});

	/**
	 * Client messages
	 */

	functions.def("send_client_script_data", [](int32_t playerId, py::bytes bytes) {
		std::string data = bytes;
		return vcmpFunctions->SendClientScriptData(playerId, data.c_str(), data.size());
	});
	functions.def("send_client_message", [](int32_t playerId, uint32_t colour, const char* message) {
		return vcmpFunctions->SendClientMessage(playerId, colour, "%s", message);
	});
	functions.def("send_game_message", [](int32_t playerId, int32_t type, const char* message) {
		return vcmpFunctions->SendGameMessage(playerId, type, "%s", message);
	});

	/*
	 * Server settings
	 */

	functions.def("set_server_name", [](const char* text) {
		return vcmpFunctions->SetServerName(text);
	});
	functions.def("get_server_name", []() -> py::object {
		char buffer[128];
		if (vcmpFunctions->GetServerName(buffer, sizeof(buffer)) == vcmpErrorNone)
			return py::str(buffer);
		return py::none();
	});
	functions.def("set_max_players", [](uint32_t maxPlayers) {
		return vcmpFunctions->SetMaxPlayers(maxPlayers);
	});
	functions.def("get_max_players", []() {
		return vcmpFunctions->GetMaxPlayers();
	});
	functions.def("set_server_password", [](const char* password) {
		return vcmpFunctions->SetServerPassword(password);
	});
	functions.def("get_server_password", []() -> py::object {
		char buffer[128];
		if (vcmpFunctions->GetServerPassword(buffer, sizeof(buffer)) == vcmpErrorNone)
			return py::str(buffer);
		return py::none();
	});
	functions.def("set_game_mode_text", [](const char* gameMode) {
		return vcmpFunctions->SetGameModeText(gameMode);
	});
	functions.def("get_game_mode_text", []() -> py::object {
		char buffer[128];
		if (vcmpFunctions->GetGameModeText(buffer, sizeof(buffer)) == vcmpErrorNone)
			return py::str(buffer);
		return py::none();
	});
	functions.def("shutdown_server", []() {
		vcmpFunctions->ShutdownServer();
	});

	/*
	 * Game environment settings
	 */

	functions.def("set_server_option", [](vcmpServerOption option, bool toggle) {
		return vcmpFunctions->SetServerOption(option, toggle);
	});
	functions.def("get_server_option", [](vcmpServerOption option) {
		return py::bool_(vcmpFunctions->GetServerOption(option) != 0);
	});
	functions.def("set_world_bounds", [](float maxX, float minX, float maxY, float minY) {
		vcmpFunctions->SetWorldBounds(maxX, minX, maxY, minY);
	});
	functions.def("get_world_bounds", []() {
		float maxXOut, minXOut, maxYOut, minYOut;
		vcmpFunctions->GetWorldBounds(&maxXOut, &minXOut, &maxYOut, &minYOut);
		return py::make_tuple(maxXOut, minXOut, maxYOut, minYOut);
	});
	functions.def("set_wasted_settings", [](uint32_t deathTimer, uint32_t fadeTimer, float fadeInSpeed, float fadeOutSpeed, uint32_t fadeColour, uint32_t corpseFadeStart, uint32_t corpseFadeTime) {
		vcmpFunctions->SetWastedSettings(deathTimer, fadeTimer, fadeInSpeed, fadeOutSpeed, fadeColour, corpseFadeStart, corpseFadeTime);
	});
	functions.def("get_wasted_settings", []() {
		uint32_t deathTimerOut, fadeTimerOut, fadeColourOut, corpseFadeStartOut, corpseFadeTimeOut;
		float fadeInSpeedOut, fadeOutSpeedOut;
		vcmpFunctions->GetWastedSettings(&deathTimerOut, &fadeTimerOut, &fadeInSpeedOut, &fadeOutSpeedOut, &fadeColourOut, &corpseFadeStartOut, &corpseFadeTimeOut);
		return py::make_tuple(deathTimerOut, fadeTimerOut, fadeInSpeedOut, fadeOutSpeedOut, fadeColourOut, corpseFadeStartOut, corpseFadeTimeOut);
	});
	functions.def("set_time_rate", [](int32_t timeRate) {
		vcmpFunctions->SetTimeRate(timeRate);
	});
	functions.def("get_time_rate", []() {
		return vcmpFunctions->GetTimeRate();
	});
	functions.def("set_hour", [](int32_t hour) {
		vcmpFunctions->SetHour(hour);
	});
	functions.def("get_hour", []() {
		return vcmpFunctions->GetHour();
	});
	functions.def("set_minute", [](int32_t minute) {
		vcmpFunctions->SetMinute(minute);
	});
	functions.def("get_minute", []() {
		return vcmpFunctions->GetMinute();
	});
	functions.def("set_weather", [](int32_t weather) {
		vcmpFunctions->SetWeather(weather);
	});
	functions.def("get_weather", []() {
		return vcmpFunctions->GetWeather();
	});
	functions.def("set_gravity", [](float gravity) {
		vcmpFunctions->SetGravity(gravity);
	});
	functions.def("get_gravity", []() {
		return vcmpFunctions->GetGravity();
	});
	functions.def("set_game_speed", [](float gameSpeed) {
		vcmpFunctions->SetGameSpeed(gameSpeed);
	});
	functions.def("get_game_speed", []() {
		return vcmpFunctions->GetGameSpeed();
	});
	functions.def("set_water_level", [](float waterLevel) {
		vcmpFunctions->SetWaterLevel(waterLevel);
	});
	functions.def("get_water_level", []() {
		return vcmpFunctions->GetWaterLevel();
	});
	functions.def("set_maximum_flight_altitude", [](float height) {
		vcmpFunctions->SetMaximumFlightAltitude(height);
	});
	functions.def("get_maximum_flight_altitude", []() {
		return vcmpFunctions->GetMaximumFlightAltitude();
	});
	functions.def("set_kill_command_delay", [](int32_t delay) {
		vcmpFunctions->SetKillCommandDelay(delay);
	});
	functions.def("get_kill_command_delay", []() {
		return vcmpFunctions->GetKillCommandDelay();
	});
	functions.def("set_vehicles_forced_respawn_height", [](float height) {
		vcmpFunctions->SetVehiclesForcedRespawnHeight(height);
	});
	functions.def("get_vehicles_forced_respawn_height", []() {
		return vcmpFunctions->GetVehiclesForcedRespawnHeight();
	});

	/*
	 * Miscellaneous things
	 */

	functions.def("create_explosion", [](int32_t worldId, int32_t type, float x, float y, float z, int32_t responsiblePlayerId, bool atGroundLevel) {
		return vcmpFunctions->CreateExplosion(worldId, type, x, y, z, responsiblePlayerId, atGroundLevel);
	});
	functions.def("play_sound", [](int32_t worldId, int32_t soundId, float x, float y, float z) {
		return vcmpFunctions->PlaySound(worldId, soundId, x, y, z);
	});
	functions.def("hide_map_object", [](int32_t modelId, int16_t tenthX, int16_t tenthY, int16_t tenthZ) {
		vcmpFunctions->HideMapObject(modelId, tenthX, tenthY, tenthZ);
	});
	functions.def("show_map_object", [](int32_t modelId, int16_t tenthX, int16_t tenthY, int16_t tenthZ) {
		vcmpFunctions->ShowMapObject(modelId, tenthX, tenthY, tenthZ);
	});
	functions.def("show_all_map_objects", []() {
		vcmpFunctions->ShowAllMapObjects();
	});

	/*
	 * Weapon settings
	 */

	functions.def("set_weapon_data_value", [](int32_t weaponId, int32_t fieldId, double value) {
		return vcmpFunctions->SetWeaponDataValue(weaponId, fieldId, value);
	});
	functions.def("get_weapon_data_value", [](int32_t weaponId, int32_t fieldId) {
		return vcmpFunctions->GetWeaponDataValue(weaponId, fieldId);
	});
	functions.def("reset_weapon_data_value", [](int32_t weaponId, int32_t fieldId) {
		return vcmpFunctions->ResetWeaponDataValue(weaponId, fieldId);
	});
	functions.def("is_weapon_data_value_modified", [](int32_t weaponId, int32_t fieldId) {
		return py::bool_(vcmpFunctions->IsWeaponDataValueModified(weaponId, fieldId) != 0);
	});
	functions.def("reset_weapon_data", [](int32_t weaponId) {
		return vcmpFunctions->ResetWeaponData(weaponId);
	});
	functions.def("reset_all_weapon_data", []() {
		vcmpFunctions->ResetAllWeaponData();
	});

	/*
	 * Key binds
	 */

	functions.def("get_key_bind_unused_slot", []() {
		return vcmpFunctions->GetKeyBindUnusedSlot();
	});
	functions.def("get_key_bind_data", [](int32_t bindId) -> py::object {
		uint8_t isCalledOnReleaseOut;
		int32_t keyOneOut, keyTwoOut, keyThreeOut;
		if (vcmpFunctions->GetKeyBindData(bindId, &isCalledOnReleaseOut, &keyOneOut, &keyTwoOut, &keyThreeOut) == vcmpErrorNone)
			return py::make_tuple(py::bool_(isCalledOnReleaseOut != 0), keyOneOut, keyTwoOut, keyThreeOut);
		return py::none();
	});
	functions.def("register_key_bind", [](int32_t bindId, bool isCalledOnRelease, int32_t keyOne, int32_t keyTwo, int32_t keyThree) {
		return vcmpFunctions->RegisterKeyBind(bindId, isCalledOnRelease, keyOne, keyTwo, keyThree);
	});
	functions.def("remove_key_bind", [](int32_t bindId) {
		return vcmpFunctions->RemoveKeyBind(bindId);
	});
	functions.def("remove_all_key_binds", []() {
		vcmpFunctions->RemoveAllKeyBinds();
	});

	/*
	 * Coordinate blips
	 */

	functions.def("create_coord_blip", [](int32_t index, int32_t world, float x, float y, float z, int32_t scale, uint32_t colour, int32_t sprite) {
		return vcmpFunctions->CreateCoordBlip(index, world, x, y, z, scale, colour, sprite);
	});
	functions.def("destroy_coord_blip", [](int32_t index) {
		return vcmpFunctions->DestroyCoordBlip(index);
	});
	functions.def("get_coord_blip_info", [](int32_t index) -> py::object {
		int32_t worldOut, scaleOut, spriteOut;
		float xOut, yOut, zOut;
		uint32_t colourOut;
		if (vcmpFunctions->GetCoordBlipInfo(index, &worldOut, &xOut, &yOut, &zOut, &scaleOut, &colourOut, &spriteOut) == vcmpErrorNone)
			return py::make_tuple(worldOut, xOut, yOut, zOut, scaleOut, colourOut, spriteOut);
		return py::none();
	});

	/*
	 * Radios
	 */

	functions.def("add_radio_stream", [](int32_t radioId, const char* radioName, const char* radioUrl, bool isListed) {
		return vcmpFunctions->AddRadioStream(radioId, radioName, radioUrl, isListed);
	});
	functions.def("remove_radio_stream", [](int32_t radioId) {
		return vcmpFunctions->RemoveRadioStream(radioId);
	});

	/*
	 * Spawning and classes
	 */

	functions.def("add_player_class", [](int32_t teamId, uint32_t colour, int32_t modelIndex, float x, float y, float z, float angle, int32_t weaponOne, int32_t weaponOneAmmo, int32_t weaponTwo, int32_t weaponTwoAmmo, int32_t weaponThree, int32_t weaponThreeAmmo) {
		return vcmpFunctions->AddPlayerClass(teamId, colour, modelIndex, x, y, z, angle, weaponOne, weaponOneAmmo, weaponTwo, weaponTwoAmmo, weaponThree, weaponThreeAmmo);
	});
	functions.def("set_spawn_player_position", [](float x, float y, float z) {
		vcmpFunctions->SetSpawnPlayerPosition(x, y, z);
	});
	functions.def("set_spawn_camera_position", [](float x, float y, float z) {
		vcmpFunctions->SetSpawnCameraPosition(x, y, z);
	});
	functions.def("set_spawn_camera_look_at", [](float x, float y, float z) {
		vcmpFunctions->SetSpawnCameraLookAt(x, y, z);
	});

	/*
	 * Administration
	 */

	functions.def("is_player_admin", [](int32_t playerId) {
		return py::bool_(vcmpFunctions->IsPlayerAdmin(playerId) != 0);
	});
	functions.def("set_player_admin", [](int32_t playerId, bool toggle) {
		return vcmpFunctions->SetPlayerAdmin(playerId, toggle);
	});
	functions.def("get_player_ip", [](int32_t playerId) -> py::object {
		char buffer[64];
		if (vcmpFunctions->GetPlayerIP(playerId, buffer, sizeof(buffer)) == vcmpErrorNone)
			return py::str(buffer);
		return py::none();
	});
	functions.def("get_player_uid", [](int32_t playerId) -> py::object {
		char buffer[64];
		if (vcmpFunctions->GetPlayerUID(playerId, buffer, sizeof(buffer)) == vcmpErrorNone)
			return py::str(buffer);
		return py::none();
	});
	functions.def("get_player_uid2", [](int32_t playerId) -> py::object {
		char buffer[64];
		if (vcmpFunctions->GetPlayerUID2(playerId, buffer, sizeof(buffer)) == vcmpErrorNone)
			return py::str(buffer);
		return py::none();
	});
	functions.def("kick_player", [](int32_t playerId) {
		return vcmpFunctions->KickPlayer(playerId);
	});
	functions.def("ban_player", [](int32_t playerId) {
		return vcmpFunctions->BanPlayer(playerId);
	});
	functions.def("ban_ip", [](char* ipAddress) {
		vcmpFunctions->BanIP(ipAddress);
	});
	functions.def("unban_ip", [](char* ipAddress) {
		return py::bool_(vcmpFunctions->UnbanIP(ipAddress) != 0);
	});
	functions.def("is_ip_banned", [](char* ipAddress) {
		return py::bool_(vcmpFunctions->IsIPBanned(ipAddress) != 0);
	});

	/*
	 * Player access and basic info
	 */

	functions.def("get_player_id_from_name", [](const char* name) {
		return vcmpFunctions->GetPlayerIdFromName(name);
	});
	functions.def("is_player_connected", [](int32_t playerId) {
		return py::bool_(vcmpFunctions->IsPlayerConnected(playerId) != 0);
	});
	functions.def("is_player_streamed_for_player", [](int32_t checkedPlayerId, int32_t playerId) {
		return py::bool_(vcmpFunctions->IsPlayerStreamedForPlayer(checkedPlayerId, playerId) != 0);
	});
	functions.def("get_player_key", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerKey(playerId);
	});
	functions.def("get_player_name", [](int32_t playerId) -> py::object {
		char buffer[64];
		if (vcmpFunctions->GetPlayerName(playerId, buffer, sizeof(buffer)) == vcmpErrorNone)
			return py::str(buffer);
		return py::none();
	});
	functions.def("set_player_name", [](int32_t playerId, const char* name) {
		return vcmpFunctions->SetPlayerName(playerId, name);
	});
	functions.def("get_player_state", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerState(playerId);
	});
	functions.def("set_player_option", [](int32_t playerId, vcmpPlayerOption option, bool toggle) {
		return vcmpFunctions->SetPlayerOption(playerId, option, toggle);
	});
	functions.def("get_player_option", [](int32_t playerId, vcmpPlayerOption option) {
		return py::bool_(vcmpFunctions->GetPlayerOption(playerId, option) != 0);
	});

	/*
	 * Player world
	 */

	functions.def("set_player_world", [](int32_t playerId, int32_t world) {
		return vcmpFunctions->SetPlayerWorld(playerId, world);
	});
	functions.def("get_player_world", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerWorld(playerId);
	});
	functions.def("set_player_secondary_world", [](int32_t playerId, int32_t secondaryWorld) {
		return vcmpFunctions->SetPlayerSecondaryWorld(playerId, secondaryWorld);
	});
	functions.def("get_player_secondary_world", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerSecondaryWorld(playerId);
	});
	functions.def("get_player_unique_world", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerUniqueWorld(playerId);
	});
	functions.def("is_player_world_compatible", [](int32_t playerId, int32_t world) {
		return py::bool_(vcmpFunctions->IsPlayerWorldCompatible(playerId, world) != 0);
	});

	/*
	 * Player class, team, skin, colour
	 */

	functions.def("get_player_class", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerClass(playerId);
	});
	functions.def("set_player_team", [](int32_t playerId, int32_t teamId) {
		return vcmpFunctions->SetPlayerTeam(playerId, teamId);
	});
	functions.def("get_player_team", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerTeam(playerId);
	});
	functions.def("set_player_skin", [](int32_t playerId, int32_t skinId) {
		return vcmpFunctions->SetPlayerSkin(playerId, skinId);
	});
	functions.def("get_player_skin", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerSkin(playerId);
	});
	functions.def("set_player_colour", [](int32_t playerId, uint32_t colour) {
		return vcmpFunctions->SetPlayerColour(playerId, colour);
	});
	functions.def("get_player_colour", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerColour(playerId);
	});

	/*
	 * Player spawn cycle
	 */

	functions.def("is_player_spawned", [](int32_t playerId) {
		return py::bool_(vcmpFunctions->IsPlayerSpawned(playerId) != 0);
	});
	functions.def("force_player_spawn", [](int32_t playerId) {
		return vcmpFunctions->ForcePlayerSpawn(playerId);
	});
	functions.def("force_player_select", [](int32_t playerId) {
		return vcmpFunctions->ForcePlayerSelect(playerId);
	});
	functions.def("force_all_select", []() {
		vcmpFunctions->ForceAllSelect();
	});
	functions.def("is_player_typing", [](int32_t playerId) {
		return py::bool_(vcmpFunctions->IsPlayerTyping(playerId) != 0);
	});

	/*
	 * Player money, score, wanted level
	 */

	functions.def("give_player_money", [](int32_t playerId, int32_t amount) {
		return vcmpFunctions->GivePlayerMoney(playerId, amount);
	});
	functions.def("set_player_money", [](int32_t playerId, int32_t amount) {
		return vcmpFunctions->SetPlayerMoney(playerId, amount);
	});
	functions.def("get_player_money", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerMoney(playerId);
	});
	functions.def("set_player_score", [](int32_t playerId, int32_t score) {
		return vcmpFunctions->SetPlayerScore(playerId, score);
	});
	functions.def("get_player_score", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerScore(playerId);
	});
	functions.def("set_player_wanted_level", [](int32_t playerId, int32_t level) {
		return vcmpFunctions->SetPlayerWantedLevel(playerId, level);
	});
	functions.def("get_player_wanted_level", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerWantedLevel(playerId);
	});
	functions.def("get_player_ping", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerPing(playerId);
	});
	functions.def("get_player_fps", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerFPS(playerId);
	});

	/*
	 * Player health and immunity
	 */

	functions.def("set_player_health", [](int32_t playerId, float health) {
		return vcmpFunctions->SetPlayerHealth(playerId, health);
	});
	functions.def("get_player_health", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerHealth(playerId);
	});
	functions.def("set_player_armour", [](int32_t playerId, float armour) {
		return vcmpFunctions->SetPlayerArmour(playerId, armour);
	});
	functions.def("get_player_armour", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerArmour(playerId);
	});
	functions.def("set_player_immunity_flags", [](int32_t playerId, uint32_t flags) {
		return vcmpFunctions->SetPlayerImmunityFlags(playerId, flags);
	});
	functions.def("get_player_immunity_flags", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerImmunityFlags(playerId);
	});

	/*
	 * Player position and rotation
	 */

	functions.def("set_player_position", [](int32_t playerId, float x, float y, float z) {
		return vcmpFunctions->SetPlayerPosition(playerId, x, y, z);
	});
	functions.def("get_player_position", [](int32_t playerId) -> py::object {
		float xOut, yOut, zOut;
		if (vcmpFunctions->GetPlayerPosition(playerId, &xOut, &yOut, &zOut) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut);
		return py::none();
	});
	functions.def("set_player_speed", [](int32_t playerId, float x, float y, float z) {
		return vcmpFunctions->SetPlayerSpeed(playerId, x, y, z);
	});
	functions.def("get_player_speed", [](int32_t playerId) -> py::object {
		float xOut, yOut, zOut;
		if (vcmpFunctions->GetPlayerSpeed(playerId, &xOut, &yOut, &zOut) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut);
		return py::none();
	});
	functions.def("add_player_speed", [](int32_t playerId, float x, float y, float z) {
		return vcmpFunctions->AddPlayerSpeed(playerId, x, y, z);
	});
	functions.def("set_player_heading", [](int32_t playerId, float angle) {
		return vcmpFunctions->SetPlayerHeading(playerId, angle);
	});
	functions.def("get_player_heading", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerHeading(playerId);
	});
	functions.def("set_player_alpha", [](int32_t playerId, int32_t alpha, uint32_t fadeTime) {
		return vcmpFunctions->SetPlayerAlpha(playerId, alpha, fadeTime);
	});
	functions.def("get_player_alpha", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerAlpha(playerId);
	});
	functions.def("get_player_aim_position", [](int32_t playerId) -> py::object {
		float xOut, yOut, zOut;
		if (vcmpFunctions->GetPlayerAimPosition(playerId, &xOut, &yOut, &zOut) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut);
		return py::none();
	});
	functions.def("get_player_aim_direction", [](int32_t playerId) -> py::object {
		float xOut, yOut, zOut;
		if (vcmpFunctions->GetPlayerAimDirection(playerId, &xOut, &yOut, &zOut) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut);
		return py::none();
	});

	/*
	 * Player actions and keys
	 */

	functions.def("is_player_on_fire", [](int32_t playerId) {
		return py::bool_(vcmpFunctions->IsPlayerOnFire(playerId) != 0);
	});
	functions.def("is_player_crouching", [](int32_t playerId) {
		return py::bool_(vcmpFunctions->IsPlayerCrouching(playerId) != 0);
	});
	functions.def("get_player_action", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerAction(playerId);
	});
	functions.def("get_player_game_keys", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerGameKeys(playerId);
	});

	/*
	 * Player vehicle
	 */

	functions.def("put_player_in_vehicle", [](int32_t playerId, int32_t vehicleId, int32_t slotIndex, bool makeRoom, bool warp) {
		return vcmpFunctions->PutPlayerInVehicle(playerId, vehicleId, slotIndex, makeRoom, warp);
	});
	functions.def("remove_player_from_vehicle", [](int32_t playerId) {
		return vcmpFunctions->RemovePlayerFromVehicle(playerId);
	});
	functions.def("get_player_in_vehicle_status", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerInVehicleStatus(playerId);
	});
	functions.def("get_player_in_vehicle_slot", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerInVehicleSlot(playerId);
	});
	functions.def("get_player_vehicle_id", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerVehicleId(playerId);
	});

	/*
	 * Player weapons
	 */

	functions.def("give_player_weapon", [](int32_t playerId, int32_t weaponId, int32_t ammo) {
		return vcmpFunctions->GivePlayerWeapon(playerId, weaponId, ammo);
	});
	functions.def("set_player_weapon", [](int32_t playerId, int32_t weaponId, int32_t ammo) {
		return vcmpFunctions->SetPlayerWeapon(playerId, weaponId, ammo);
	});
	functions.def("get_player_weapon", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerWeapon(playerId);
	});
	functions.def("get_player_weapon_ammo", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerWeaponAmmo(playerId);
	});
	functions.def("set_player_weapon_slot", [](int32_t playerId, int32_t slot) {
		return vcmpFunctions->SetPlayerWeaponSlot(playerId, slot);
	});
	functions.def("get_player_weapon_slot", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerWeaponSlot(playerId);
	});
	functions.def("get_player_weapon_at_slot", [](int32_t playerId, int32_t slot) {
		return vcmpFunctions->GetPlayerWeaponAtSlot(playerId, slot);
	});
	functions.def("get_player_ammo_at_slot", [](int32_t playerId, int32_t slot) {
		return vcmpFunctions->GetPlayerAmmoAtSlot(playerId, slot);
	});
	functions.def("remove_player_weapon", [](int32_t playerId, int32_t weaponId) {
		return vcmpFunctions->RemovePlayerWeapon(playerId, weaponId);
	});
	functions.def("remove_all_weapons", [](int32_t playerId) {
		return vcmpFunctions->RemoveAllWeapons(playerId);
	});

	/*
	 * Player camera
	 */

	functions.def("set_camera_position", [](int32_t playerId, float posX, float posY, float posZ, float lookX, float lookY, float lookZ) {
		return vcmpFunctions->SetCameraPosition(playerId, posX, posY, posZ, lookX, lookY, lookZ);
	});
	functions.def("restore_camera", [](int32_t playerId) {
		return vcmpFunctions->RestoreCamera(playerId);
	});
	functions.def("is_camera_locked", [](int32_t playerId) {
		return py::bool_(vcmpFunctions->IsCameraLocked(playerId) != 0);
	});

	/*
	 * Player miscellaneous stuff
	 */

	functions.def("set_player_animation", [](int32_t playerId, int32_t groupId, int32_t animationId) {
		return vcmpFunctions->SetPlayerAnimation(playerId, groupId, animationId);
	});
	functions.def("get_player_standing_on_vehicle", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerStandingOnVehicle(playerId);
	});
	functions.def("get_player_standing_on_object", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerStandingOnObject(playerId);
	});
	functions.def("is_player_away", [](int32_t playerId) {
		return py::bool_(vcmpFunctions->IsPlayerAway(playerId) != 0);
	});
	functions.def("get_player_spectate_target", [](int32_t playerId) {
		return vcmpFunctions->GetPlayerSpectateTarget(playerId);
	});
	functions.def("set_player_spectate_target", [](int32_t playerId, int32_t targetId) {
		return vcmpFunctions->SetPlayerSpectateTarget(playerId, targetId);
	});
	functions.def("redirect_player_to_server", [](int32_t playerId, const char* ip, uint32_t port, const char* nick, const char* serverPassword, const char* userPassword) {
		return vcmpFunctions->RedirectPlayerToServer(playerId, ip, port, nick, serverPassword, userPassword);
	});

	/*
	 * All entities
	 */

	functions.def("check_entity_exists", [](vcmpEntityPool entityPool, int32_t index) {
		return py::bool_(vcmpFunctions->CheckEntityExists(entityPool, index) != 0);
	});

	/*
	 * Vehicles
	 */

	functions.def("create_vehicle", [](int32_t modelIndex, int32_t world, float x, float y, float z, float angle, int32_t primaryColour, int32_t secondaryColour) {
		return vcmpFunctions->CreateVehicle(modelIndex, world, x, y, z, angle, primaryColour, secondaryColour);
	});
	functions.def("delete_vehicle", [](int32_t vehicleId) {
		return vcmpFunctions->DeleteVehicle(vehicleId);
	});
	functions.def("set_vehicle_option", [](int32_t vehicleId, vcmpVehicleOption option, bool toggle) {
		return vcmpFunctions->SetVehicleOption(vehicleId, option, toggle);
	});
	functions.def("get_vehicle_option", [](int32_t vehicleId, vcmpVehicleOption option) {
		return py::bool_(vcmpFunctions->GetVehicleOption(vehicleId, option) != 0);
	});
	functions.def("get_vehicle_sync_source", [](int32_t vehicleId) {
		return vcmpFunctions->GetVehicleSyncSource(vehicleId);
	});
	functions.def("get_vehicle_sync_type", [](int32_t vehicleId) {
		return vcmpFunctions->GetVehicleSyncType(vehicleId);
	});
	functions.def("is_vehicle_streamed_for_player", [](int32_t vehicleId, int32_t playerId) {
		return py::bool_(vcmpFunctions->IsVehicleStreamedForPlayer(vehicleId, playerId) != 0);
	});
	functions.def("set_vehicle_world", [](int32_t vehicleId, int32_t world) {
		return vcmpFunctions->SetVehicleWorld(vehicleId, world);
	});
	functions.def("get_vehicle_world", [](int32_t vehicleId) {
		return vcmpFunctions->GetVehicleWorld(vehicleId);
	});
	functions.def("get_vehicle_model", [](int32_t vehicleId) {
		return vcmpFunctions->GetVehicleModel(vehicleId);
	});
	functions.def("get_vehicle_occupant", [](int32_t vehicleId, int32_t slotIndex) {
		return vcmpFunctions->GetVehicleOccupant(vehicleId, slotIndex);
	});
	functions.def("respawn_vehicle", [](int32_t vehicleId) {
		return vcmpFunctions->RespawnVehicle(vehicleId);
	});
	functions.def("set_vehicle_immunity_flags", [](int32_t vehicleId, uint32_t immunityFlags) {
		return vcmpFunctions->SetVehicleImmunityFlags(vehicleId, immunityFlags);
	});
	functions.def("get_vehicle_immunity_flags", [](int32_t vehicleId) {
		return vcmpFunctions->GetVehicleImmunityFlags(vehicleId);
	});
	functions.def("explode_vehicle", [](int32_t vehicleId) {
		return vcmpFunctions->ExplodeVehicle(vehicleId);
	});
	functions.def("is_vehicle_wrecked", [](int32_t vehicleId) {
		return py::bool_(vcmpFunctions->IsVehicleWrecked(vehicleId) != 0);
	});
	functions.def("set_vehicle_position", [](int32_t vehicleId, float x, float y, float z, bool removeOccupants) {
		return vcmpFunctions->SetVehiclePosition(vehicleId, x, y, z, removeOccupants);
	});
	functions.def("get_vehicle_position", [](int32_t vehicleId) -> py::object {
		float xOut, yOut, zOut;
		if (vcmpFunctions->GetVehiclePosition(vehicleId, &xOut, &yOut, &zOut) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut);
		return py::none();
	});
	functions.def("set_vehicle_rotation", [](int32_t vehicleId, float x, float y, float z, float w) {
		return vcmpFunctions->SetVehicleRotation(vehicleId, x, y, z, w);
	});
	functions.def("set_vehicle_rotation_euler", [](int32_t vehicleId, float x, float y, float z) {
		return vcmpFunctions->SetVehicleRotationEuler(vehicleId, x, y, z);
	});
	functions.def("get_vehicle_rotation", [](int32_t vehicleId) -> py::object {
		float xOut, yOut, zOut, wOut;
		if (vcmpFunctions->GetVehicleRotation(vehicleId, &xOut, &yOut, &zOut, &wOut) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut, wOut);
		return py::none();
	});
	functions.def("get_vehicle_rotation_euler", [](int32_t vehicleId) -> py::object {
		float xOut, yOut, zOut;
		if (vcmpFunctions->GetVehicleRotationEuler(vehicleId, &xOut, &yOut, &zOut) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut);
		return py::none();
	});
	functions.def("set_vehicle_speed", [](int32_t vehicleId, float x, float y, float z, bool add, bool relative) {
		return vcmpFunctions->SetVehicleSpeed(vehicleId, x, y, z, add, relative);
	});
	functions.def("get_vehicle_speed", [](int32_t vehicleId, bool relative) -> py::object {
		float xOut, yOut, zOut;
		if (vcmpFunctions->GetVehicleSpeed(vehicleId, &xOut, &yOut, &zOut, relative) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut);
		return py::none();
	});
	functions.def("set_vehicle_turn_speed", [](int32_t vehicleId, float x, float y, float z, bool add, bool relative) {
		return vcmpFunctions->SetVehicleTurnSpeed(vehicleId, x, y, z, add, relative);
	});
	functions.def("get_vehicle_turn_speed", [](int32_t vehicleId, bool relative) -> py::object {
		float xOut, yOut, zOut;
		if (vcmpFunctions->GetVehicleTurnSpeed(vehicleId, &xOut, &yOut, &zOut, relative) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut);
		return py::none();
	});
	functions.def("set_vehicle_spawn_position", [](int32_t vehicleId, float x, float y, float z) {
		return vcmpFunctions->SetVehicleSpawnPosition(vehicleId, x, y, z);
	});
	functions.def("get_vehicle_spawn_position", [](int32_t vehicleId) -> py::object {
		float xOut, yOut, zOut;
		if (vcmpFunctions->GetVehicleSpawnPosition(vehicleId, &xOut, &yOut, &zOut) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut);
		return py::none();
	});
	functions.def("set_vehicle_spawn_rotation", [](int32_t vehicleId, float x, float y, float z, float w) {
		return vcmpFunctions->SetVehicleSpawnRotation(vehicleId, x, y, z, w);
	});
	functions.def("set_vehicle_spawn_rotation_euler", [](int32_t vehicleId, float x, float y, float z) {
		return vcmpFunctions->SetVehicleSpawnRotationEuler(vehicleId, x, y, z);
	});
	functions.def("get_vehicle_spawn_rotation", [](int32_t vehicleId) -> py::object {
		float xOut, yOut, zOut, wOut;
		if (vcmpFunctions->GetVehicleSpawnRotation(vehicleId, &xOut, &yOut, &zOut, &wOut) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut, wOut);
		return py::none();
	});
	functions.def("get_vehicle_spawn_rotation_euler", [](int32_t vehicleId) -> py::object {
		float xOut, yOut, zOut;
		if (vcmpFunctions->GetVehicleSpawnRotationEuler(vehicleId, &xOut, &yOut, &zOut) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut);
		return py::none();
	});
	functions.def("set_vehicle_idle_respawn_timer", [](int32_t vehicleId, uint32_t millis) {
		return vcmpFunctions->SetVehicleIdleRespawnTimer(vehicleId, millis);
	});
	functions.def("get_vehicle_idle_respawn_timer", [](int32_t vehicleId) {
		return vcmpFunctions->GetVehicleIdleRespawnTimer(vehicleId);
	});
	functions.def("set_vehicle_health", [](int32_t vehicleId, float health) {
		return vcmpFunctions->SetVehicleHealth(vehicleId, health);
	});
	functions.def("get_vehicle_health", [](int32_t vehicleId) {
		return vcmpFunctions->GetVehicleHealth(vehicleId);
	});
	functions.def("set_vehicle_colour", [](int32_t vehicleId, int32_t primaryColour, int32_t secondaryColour) {
		return vcmpFunctions->SetVehicleColour(vehicleId, primaryColour, secondaryColour);
	});
	functions.def("get_vehicle_colour", [](int32_t vehicleId) -> py::object {
		int32_t primaryColourOut, secondaryColourOut;
		if (vcmpFunctions->GetVehicleColour(vehicleId, &primaryColourOut, &secondaryColourOut) == vcmpErrorNone)
			return py::make_tuple(primaryColourOut, secondaryColourOut);
		return py::none();
	});
	functions.def("set_vehicle_part_status", [](int32_t vehicleId, int32_t partId, int32_t status) {
		return vcmpFunctions->SetVehiclePartStatus(vehicleId, partId, status);
	});
	functions.def("get_vehicle_part_status", [](int32_t vehicleId, int32_t partId) {
		return vcmpFunctions->GetVehiclePartStatus(vehicleId, partId);
	});
	functions.def("set_vehicle_tyre_status", [](int32_t vehicleId, int32_t tyreId, int32_t status) {
		return vcmpFunctions->SetVehicleTyreStatus(vehicleId, tyreId, status);
	});
	functions.def("get_vehicle_tyre_status", [](int32_t vehicleId, int32_t tyreId) {
		return vcmpFunctions->GetVehicleTyreStatus(vehicleId, tyreId);
	});
	functions.def("set_vehicle_damage_data", [](int32_t vehicleId, uint32_t damageData) {
		return vcmpFunctions->SetVehicleDamageData(vehicleId, damageData);
	});
	functions.def("get_vehicle_damage_data", [](int32_t vehicleId) {
		return vcmpFunctions->GetVehicleDamageData(vehicleId);
	});
	functions.def("set_vehicle_radio", [](int32_t vehicleId, int32_t radioId) {
		return vcmpFunctions->SetVehicleRadio(vehicleId, radioId);
	});
	functions.def("get_vehicle_radio", [](int32_t vehicleId) {
		return vcmpFunctions->GetVehicleRadio(vehicleId);
	});
	functions.def("get_vehicle_turret_rotation", [](int32_t vehicleId) -> py::object {
		float horizontalOut, verticalOut;
		if (vcmpFunctions->GetVehicleTurretRotation(vehicleId, &horizontalOut, &verticalOut) == vcmpErrorNone)
			return py::make_tuple(horizontalOut, verticalOut);
		return py::none();
	});

	/*
	 * Vehicle handling
	 */

	functions.def("reset_all_vehicle_handlings", []() {
		vcmpFunctions->ResetAllVehicleHandlings();
	});
	functions.def("exists_handling_rule", [](int32_t modelIndex, int32_t ruleIndex) {
		return py::bool_(vcmpFunctions->ExistsHandlingRule(modelIndex, ruleIndex) != 0);
	});
	functions.def("set_handling_rule", [](int32_t modelIndex, int32_t ruleIndex, double value) {
		return vcmpFunctions->SetHandlingRule(modelIndex, ruleIndex, value);
	});
	functions.def("get_handling_rule", [](int32_t modelIndex, int32_t ruleIndex) {
		return vcmpFunctions->GetHandlingRule(modelIndex, ruleIndex);
	});
	functions.def("reset_handling_rule", [](int32_t modelIndex, int32_t ruleIndex) {
		return vcmpFunctions->ResetHandlingRule(modelIndex, ruleIndex);
	});
	functions.def("reset_handling", [](int32_t modelIndex) {
		return vcmpFunctions->ResetHandling(modelIndex);
	});
	functions.def("exists_inst_handling_rule", [](int32_t vehicleId, int32_t ruleIndex) {
		return py::bool_(vcmpFunctions->ExistsInstHandlingRule(vehicleId, ruleIndex) != 0);
	});
	functions.def("set_inst_handling_rule", [](int32_t vehicleId, int32_t ruleIndex, double value) {
		return vcmpFunctions->SetInstHandlingRule(vehicleId, ruleIndex, value);
	});
	functions.def("get_inst_handling_rule", [](int32_t vehicleId, int32_t ruleIndex) {
		return vcmpFunctions->GetInstHandlingRule(vehicleId, ruleIndex);
	});
	functions.def("reset_inst_handling_rule", [](int32_t vehicleId, int32_t ruleIndex) {
		return vcmpFunctions->ResetInstHandlingRule(vehicleId, ruleIndex);
	});
	functions.def("reset_inst_handling", [](int32_t vehicleId) {
		return vcmpFunctions->ResetInstHandling(vehicleId);
	});

	/*
	 * Pickups
	 */

	functions.def("create_pickup", [](int32_t modelIndex, int32_t world, int32_t quantity, float x, float y, float z, int32_t alpha, bool isAutomatic) {
		return vcmpFunctions->CreatePickup(modelIndex, world, quantity, x, y, z, alpha, isAutomatic);
	});
	functions.def("delete_pickup", [](int32_t pickupId) {
		return vcmpFunctions->DeletePickup(pickupId);
	});
	functions.def("is_pickup_streamed_for_player", [](int32_t pickupId, int32_t playerId) {
		return py::bool_(vcmpFunctions->IsPickupStreamedForPlayer(pickupId, playerId) != 0);
	});
	functions.def("set_pickup_world", [](int32_t pickupId, int32_t world) {
		return vcmpFunctions->SetPickupWorld(pickupId, world);
	});
	functions.def("get_pickup_world", [](int32_t pickupId) {
		return vcmpFunctions->GetPickupWorld(pickupId);
	});
	functions.def("set_pickup_alpha", [](int32_t pickupId, int32_t alpha) {
		return vcmpFunctions->SetPickupAlpha(pickupId, alpha);
	});
	functions.def("get_pickup_alpha", [](int32_t pickupId) {
		return vcmpFunctions->GetPickupAlpha(pickupId);
	});
	functions.def("set_pickup_is_automatic", [](int32_t pickupId, bool toggle) {
		return vcmpFunctions->SetPickupIsAutomatic(pickupId, toggle);
	});
	functions.def("is_pickup_automatic", [](int32_t pickupId) {
		return py::bool_(vcmpFunctions->IsPickupAutomatic(pickupId) != 0);
	});
	functions.def("set_pickup_auto_timer", [](int32_t pickupId, uint32_t durationMillis) {
		return vcmpFunctions->SetPickupAutoTimer(pickupId, durationMillis);
	});
	functions.def("get_pickup_auto_timer", [](int32_t pickupId) {
		return vcmpFunctions->GetPickupAutoTimer(pickupId);
	});
	functions.def("refresh_pickup", [](int32_t pickupId) {
		return vcmpFunctions->RefreshPickup(pickupId);
	});
	functions.def("set_pickup_position", [](int32_t pickupId, float x, float y, float z) {
		return vcmpFunctions->SetPickupPosition(pickupId, x, y, z);
	});
	functions.def("get_pickup_position", [](int32_t pickupId) -> py::object {
		float xOut, yOut, zOut;
		if (vcmpFunctions->GetPickupPosition(pickupId, &xOut, &yOut, &zOut) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut);
		return py::none();
	});
	functions.def("get_pickup_model", [](int32_t pickupId) {
		return vcmpFunctions->GetPickupModel(pickupId);
	});
	functions.def("get_pickup_quantity", [](int32_t pickupId) {
		return vcmpFunctions->GetPickupQuantity(pickupId);
	});

	/*
	 * Checkpoints
	 */

	functions.def("create_check_point", [](int32_t playerId, int32_t world, bool isSphere, float x, float y, float z, int32_t red, int32_t green, int32_t blue, int32_t alpha, float radius) {
		return vcmpFunctions->CreateCheckPoint(playerId, world, isSphere, x, y, z, red, green, blue, alpha, radius);
	});
	functions.def("delete_check_point", [](int32_t checkPointId) {
		return vcmpFunctions->DeleteCheckPoint(checkPointId);
	});
	functions.def("is_check_point_streamed_for_player", [](int32_t checkPointId, int32_t playerId) {
		return py::bool_(vcmpFunctions->IsCheckPointStreamedForPlayer(checkPointId, playerId) != 0);
	});
	functions.def("is_check_point_sphere", [](int32_t checkPointId) {
		return py::bool_(vcmpFunctions->IsCheckPointSphere(checkPointId) != 0);
	});
	functions.def("set_check_point_world", [](int32_t checkPointId, int32_t world) {
		return vcmpFunctions->SetCheckPointWorld(checkPointId, world);
	});
	functions.def("get_check_point_world", [](int32_t checkPointId) {
		return vcmpFunctions->GetCheckPointWorld(checkPointId);
	});
	functions.def("set_check_point_colour", [](int32_t checkPointId, int32_t red, int32_t green, int32_t blue, int32_t alpha) {
		return vcmpFunctions->SetCheckPointColour(checkPointId, red, green, blue, alpha);
	});
	functions.def("get_check_point_colour", [](int32_t checkPointId) -> py::object {
		int32_t redOut, greenOut, blueOut, alphaOut;
		if (vcmpFunctions->GetCheckPointColour(checkPointId, &redOut, &greenOut, &blueOut, &alphaOut) == vcmpErrorNone)
			return py::make_tuple(redOut, greenOut, blueOut, alphaOut);
		return py::none();
	});
	functions.def("set_check_point_position", [](int32_t checkPointId, float x, float y, float z) {
		return vcmpFunctions->SetCheckPointPosition(checkPointId, x, y, z);
	});
	functions.def("get_check_point_position", [](int32_t checkPointId) -> py::object {
		float xOut, yOut, zOut;
		if (vcmpFunctions->GetCheckPointPosition(checkPointId, &xOut, &yOut, &zOut) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut);
		return py::none();
	});
	functions.def("set_check_point_radius", [](int32_t checkPointId, float radius) {
		return vcmpFunctions->SetCheckPointRadius(checkPointId, radius);
	});
	functions.def("get_check_point_radius", [](int32_t checkPointId) {
		return vcmpFunctions->GetCheckPointRadius(checkPointId);
	});
	functions.def("get_check_point_owner", [](int32_t checkPointId) {
		return vcmpFunctions->GetCheckPointOwner(checkPointId);
	});

	/*
	 * Objects
	 */

	functions.def("create_object", [](int32_t modelIndex, int32_t world, float x, float y, float z, int32_t alpha) {
		return vcmpFunctions->CreateObject(modelIndex, world, x, y, z, alpha);
	});
	functions.def("delete_object", [](int32_t objectId) {
		return vcmpFunctions->DeleteObject(objectId);
	});
	functions.def("is_object_streamed_for_player", [](int32_t objectId, int32_t playerId) {
		return py::bool_(vcmpFunctions->IsObjectStreamedForPlayer(objectId, playerId) != 0);
	});
	functions.def("get_object_model", [](int32_t objectId) {
		return vcmpFunctions->GetObjectModel(objectId);
	});
	functions.def("set_object_world", [](int32_t objectId, int32_t world) {
		return vcmpFunctions->SetObjectWorld(objectId, world);
	});
	functions.def("get_object_world", [](int32_t objectId) {
		return vcmpFunctions->GetObjectWorld(objectId);
	});
	functions.def("set_object_alpha", [](int32_t objectId, int32_t alpha, uint32_t duration) {
		return vcmpFunctions->SetObjectAlpha(objectId, alpha, duration);
	});
	functions.def("get_object_alpha", [](int32_t objectId) {
		return vcmpFunctions->GetObjectAlpha(objectId);
	});
	functions.def("move_object_to", [](int32_t objectId, float x, float y, float z, uint32_t duration) {
		return vcmpFunctions->MoveObjectTo(objectId, x, y, z, duration);
	});
	functions.def("move_object_by", [](int32_t objectId, float x, float y, float z, uint32_t duration) {
		return vcmpFunctions->MoveObjectBy(objectId, x, y, z, duration);
	});
	functions.def("set_object_position", [](int32_t objectId, float x, float y, float z) {
		return vcmpFunctions->SetObjectPosition(objectId, x, y, z);
	});
	functions.def("get_object_position", [](int32_t objectId) -> py::object {
		float xOut, yOut, zOut;
		if (vcmpFunctions->GetObjectPosition(objectId, &xOut, &yOut, &zOut) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut);
		return py::none();
	});
	functions.def("rotate_object_to", [](int32_t objectId, float x, float y, float z, float w, uint32_t duration) {
		return vcmpFunctions->RotateObjectTo(objectId, x, y, z, w, duration);
	});
	functions.def("rotate_object_to_euler", [](int32_t objectId, float x, float y, float z, uint32_t duration) {
		return vcmpFunctions->RotateObjectToEuler(objectId, x, y, z, duration);
	});
	functions.def("rotate_object_by", [](int32_t objectId, float x, float y, float z, float w, uint32_t duration) {
		return vcmpFunctions->RotateObjectBy(objectId, x, y, z, w, duration);
	});
	functions.def("rotate_object_by_euler", [](int32_t objectId, float x, float y, float z, uint32_t duration) {
		return vcmpFunctions->RotateObjectByEuler(objectId, x, y, z, duration);
	});
	functions.def("get_object_rotation", [](int32_t objectId) -> py::object {
		float xOut, yOut, zOut, wOut;
		if (vcmpFunctions->GetObjectRotation(objectId, &xOut, &yOut, &zOut, &wOut) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut, wOut);
		return py::none();
	});
	functions.def("get_object_rotation_euler", [](int32_t objectId) -> py::object {
		float xOut, yOut, zOut;
		if (vcmpFunctions->GetObjectRotationEuler(objectId, &xOut, &yOut, &zOut) == vcmpErrorNone)
			return py::make_tuple(xOut, yOut, zOut);
		return py::none();
	});
	functions.def("set_object_shot_report_enabled", [](int32_t objectId, bool toggle) {
		return vcmpFunctions->SetObjectShotReportEnabled(objectId, toggle);
	});
	functions.def("is_object_shot_report_enabled", [](int32_t objectId) {
		return py::bool_(vcmpFunctions->IsObjectShotReportEnabled(objectId) != 0);
	});
	functions.def("set_object_touched_report_enabled", [](int32_t objectId, bool toggle) {
		return vcmpFunctions->SetObjectTouchedReportEnabled(objectId, toggle);
	});
	functions.def("is_object_touched_report_enabled", [](int32_t objectId) {
		return py::bool_(vcmpFunctions->IsObjectTouchedReportEnabled(objectId) != 0);
	});
}

PYBIND11_EMBEDDED_MODULE(_vcmp, m)
{
	py::module functions = m.def_submodule("functions");
	py::module callbacks = m.def_submodule("callbacks");

	RegisterFunctions(functions);

	for (auto name : callbackNames)
	{
		callbacks.attr(name) = py::none();
	}

	moduleCallbacks = new py::module(callbacks);
}
