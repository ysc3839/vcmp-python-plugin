#include <fstream>

#include <pybind11/embed.h>
namespace py = pybind11;

#include "plugin.h"

#ifdef _WIN32
#define EXPORT __declspec(dllexport)

#define strcpy strcpy_s
#else
#define EXPORT
#endif

PluginFuncs* vcmpFunctions;
py::module* moduleCallbacks = nullptr;

void PythonExceptionHandler()
{
	try
	{
		throw;
	}
	catch (py::error_already_set e)
	{
		e.restore();
		PyErr_Print();
		if (e.matches(PyExc_KeyboardInterrupt) || e.matches(PyExc_SystemExit))
			vcmpFunctions->ShutdownServer();
	}
}
