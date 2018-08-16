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
PluginCallbacks* vcmpCallbacks;
py::module* moduleCallbacks = nullptr;

// TODO: MOVE LATER
bool haveNewFunctions = false;
bool haveNewCallbacks = false;

void PythonExceptionHandler()
{
	try
	{
		throw;
	}
	catch (py::error_already_set e)
	{
		bool shutdown = false;
		if (e.matches(PyExc_KeyboardInterrupt) || e.matches(PyExc_SystemExit))
			shutdown = true;

		{
			auto sys = py::module::import("sys");
			PyObject *pstderr = sys.attr("stderr").ptr();

			auto f = py::module::import("io").attr("StringIO")();

			sys.attr("stderr") = f;

			e.restore();
			PyErr_Print();

			sys.attr("stderr") = pstderr;

			std::string str(py::str(f.attr("getvalue")()));
			vcmpFunctions->LogMessage("%s", str.c_str());
		}

		if (shutdown)
			vcmpFunctions->ShutdownServer();
	}
	catch (std::exception e)
	{
		vcmpFunctions->LogMessage("Exception: %s", e.what());
	}
}
