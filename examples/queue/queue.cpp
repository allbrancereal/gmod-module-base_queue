#include "GarrysMod/Lua/Interface.h"
#include "Python.h"
using namespace GarrysMod::Lua;

PyObject* get_python_function(const char* script_name, const char* function_name) {
    PyObject* pName = PyUnicode_DecodeFSDefault(script_name);
    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule == NULL) {
        PyErr_Print();
        return NULL;
    }

    PyObject* pFunc = PyObject_GetAttrString(pModule, function_name);
    Py_DECREF(pModule);

    if (pFunc == NULL || !PyCallable_Check(pFunc)) {
        Py_XDECREF(pFunc);
        PyErr_Print();
        return NULL;
    }

    return pFunc;
}

LUA_FUNCTION(RunPythonScript)
{
    const char* script_name = LUA->CheckString(1);

    PyObject* pFunc = get_python_function(script_name, "main");
    if (pFunc == NULL) {
        LUA->PushNil();
        LUA->PushString("Failed to get Python function");
        return 2;  // Return nil and error message
    }

    PyObject* pValue = PyObject_CallObject(pFunc, NULL);
    Py_DECREF(pFunc);

    if (pValue == NULL) {
        PyErr_Print();
        LUA->PushNil();
        LUA->PushString("Python function call failed");
        return 2;  // Return nil and error message
    }

    LUA->PushNumber(PyFloat_AsDouble(pValue));
    Py_DECREF(pValue);

    return 1;  // Return the result
}

GMOD_MODULE_OPEN()
{
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./GarrysMod/lua/bin/python')");

    LUA->PushSpecial(SPECIAL_GLOB);  // Get the global table
    LUA->PushCFunction(RunPythonScript);
    LUA->SetField(-2, "RunPythonScript");  // global.RunPythonScript = RunPythonScript
    LUA->Pop();

    return 0;
}

GMOD_MODULE_CLOSE()
{
    Py_Finalize();
    return 0;
}
