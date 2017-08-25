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

PYBIND11_EMBEDDED_MODULE(_vcmp, m)
{
	py::module functions = m.def_submodule("functions");
	py::module callbacks = m.def_submodule("callbacks");

	for (auto &name : callbackNames)
	{
		callbacks.attr(name) = py::none();
	}

	moduleCallbacks = new py::module(callbacks);
}
