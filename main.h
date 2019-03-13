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
FILE* logFile = nullptr;

// TODO: MOVE LATER
bool haveNewFunctions = false;
bool haveNewCallbacks = false;

void PrintStdErrAndLogFile(const char* str)
{
	fputs(str, stderr);
	if (logFile)
		fputs(str, logFile);
}

void PythonExceptionHandler()
{
	try
	{
		throw;
	}
	catch (py::error_already_set &e)
	{
		bool shutdown = false;
		if (e.matches(PyExc_KeyboardInterrupt) || e.matches(PyExc_SystemExit))
			shutdown = true;

		{
			auto sys = py::module::import("sys");
			py::object pystderr = sys.attr("stderr");

			auto f = py::module::import("io").attr("StringIO")();

			sys.attr("stderr") = f;

			e.restore();
			PyErr_Print();

			sys.attr("stderr") = pystderr;

			std::string str(py::str(f.attr("getvalue")()));
			PrintStdErrAndLogFile(str.c_str());
		}

		if (shutdown)
			vcmpFunctions->ShutdownServer();
	}
	catch (const std::exception &e)
	{
		vcmpFunctions->LogMessage("Exception: %s", e.what());
	}
}

bool ReadServerConfig(const char *filename, std::string &moduleName)
{
	std::ifstream f(filename, std::ios::binary);

	std::string prefix("pymodule ");
	for (std::string line; std::getline(f, line);)
	{
		if (line.compare(0, prefix.size(), prefix) == 0)
		{
			moduleName = line.substr(prefix.size());
			return true;
		}
	}
	return false;
}

#if defined(__x86_64__) || defined(_M_X64)
#define CONFIG_FILENAME_ARCH "server64.cfg"
#else
#define CONFIG_FILENAME_ARCH "server32.cfg"
#endif
