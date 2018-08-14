#include "main.h"
#include "EventHandler.h"
#include "PythonModule.h"

extern "C" EXPORT unsigned int VcmpPluginInit(PluginFuncs* pluginFunctions, PluginCallbacks* pluginCallbacks, PluginInfo* pluginInfo)
{
	pluginInfo->pluginVersion = 0x102;
	pluginInfo->apiMajorVersion = PLUGIN_API_MAJOR;
	pluginInfo->apiMinorVersion = PLUGIN_API_MINOR;
	strcpy(pluginInfo->name, "vcmp-python-plugin");

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
