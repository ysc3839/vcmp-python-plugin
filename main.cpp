#include "main.h"
#include "EventHandler.h"
#include "PythonModule.h"

extern "C" EXPORT uint32_t VcmpPluginInit(PluginFuncs* pluginFunctions, PluginCallbacks* pluginCallbacks, PluginInfo* pluginInfo)
{
	pluginInfo->pluginVersion = 0x105;
	pluginInfo->apiMajorVersion = PLUGIN_API_MAJOR;
	pluginInfo->apiMinorVersion = PLUGIN_API_MINOR;
	strcpy(pluginInfo->name, "vcmp-python-plugin");

	logFile = fopen("server_log.txt", "a");

	vcmpFunctions = pluginFunctions;
	if (pluginFunctions->structSize == sizeof(PluginFuncsNew))
		haveNewFunctions = true;
	vcmpCallbacks = pluginCallbacks;
	if (pluginCallbacks->structSize == sizeof(PluginCallbacksNew))
		haveNewCallbacks = true;
	RegisterCallbacks(pluginCallbacks);

	py::initialize_interpreter();

	return 1;
}
