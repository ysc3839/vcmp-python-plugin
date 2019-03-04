# pylint: disable=missing-docstring

from typing import Callable, Union, NewType, Dict
VcmpDisconnectReason = NewType('VcmpDisconnectReason', int)
VcmpBodyPart = NewType('VcmpBodyPart', int)
VcmpPlayerUpdate = NewType('VcmpPlayerUpdate', int)
VcmpPlayerState = NewType('VcmpPlayerState', int)
VcmpVehicleUpdate = NewType('VcmpVehicleUpdate', int)
VcmpEntityPool = NewType('VcmpEntityPool', int)

struct_size: int = 0

on_server_initialise: Callable[[], bool] = None
on_server_shutdown: Callable[[], None] = None
on_server_frame: Callable[[float], None] = None

on_plugin_command: Callable[[int, str], bool] = None
on_incoming_connection: Callable[[str, int, str, str], Union[bool, str]] = None
on_client_script_data: Callable[[int, bytes], None] = None

on_player_connect: Callable[[int], None] = None
on_player_disconnect: Callable[[int, VcmpDisconnectReason], None] = None

on_player_request_class: Callable[[int, int], bool] = None
on_player_request_spawn: Callable[[int], bool] = None
on_player_spawn: Callable[[int], None] = None
on_player_death: Callable[[int, int, int, VcmpBodyPart], None] = None
on_player_update: Callable[[int, VcmpPlayerUpdate], None] = None

on_player_request_enter_vehicle: Callable[[int, int, int], bool] = None
on_player_enter_vehicle: Callable[[int, int, int], None] = None
on_player_exit_vehicle: Callable[[int, int], None] = None

on_player_name_change: Callable[[int, str, str], None] = None
on_player_state_change: Callable[[int, VcmpPlayerState, VcmpPlayerState], None] = None
on_player_action_change: Callable[[int, int, int], None] = None
on_player_on_fire_change: Callable[[int, bool], None] = None
on_player_crouch_change: Callable[[int, bool], None] = None
on_player_game_keys_change: Callable[[int, int, int], None] = None
on_player_begin_typing: Callable[[int], None] = None
on_player_end_typing: Callable[[int], None] = None
on_player_away_change: Callable[[int, bool], None] = None

on_player_message: Callable[[int, str], bool] = None
on_player_command: Callable[[int, str], bool] = None
on_player_private_message: Callable[[int, int, str], bool] = None

on_player_key_bind_down: Callable[[int, int], None] = None
on_player_key_bind_up: Callable[[int, int], None] = None
on_player_spectate: Callable[[int, int], None] = None
on_player_crash_report: Callable[[int, str], None] = None

on_vehicle_update: Callable[[int, VcmpVehicleUpdate], None] = None
on_vehicle_explode: Callable[[int], None] = None
on_vehicle_respawn: Callable[[int], None] = None

on_object_shot: Callable[[int, int, int], None] = None
on_object_touched: Callable[[int, int], None] = None

on_pickup_pick_attempt: Callable[[int, int], bool] = None
on_pickup_picked: Callable[[int, int], None] = None
on_pickup_respawn: Callable[[int], None] = None

on_checkpoint_entered: Callable[[int, int], None] = None
on_checkpoint_exited: Callable[[int, int], None] = None

on_entity_pool_change: Callable[[VcmpEntityPool, int, bool], None] = None
on_server_performance_report: Callable[[Dict[str, int]], None] = None

# TODO: MOVE LATER
on_player_module_list: Callable[[int, str], None] = None
