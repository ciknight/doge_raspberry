#include <Python.h>

static PyObject* wrap_read(PyObject* self, PyObject* args)
{
    int iPin;
    int piHumidity = -1;
    int piTemp = -1;
    int result[2] = {piHumidity, piTemp};
    if (!PyArg_ParseTuple(args, "i:read_dht22_dat", &iPin))
        return NULL;
    read_dht22_dat(iPin, &piHumidity, &piTemp);
    return Py_BuildValue("0&", result);
}

static PyMethodDef pydht22Methods[] = {
    {"read", wrap_read, METH_VARARGS, "read dht22 humidity and temp"},
    {NULL, NULL}
};

void initPydht22()
{
    PyObject* m;
    m = Py_InitModule("pydht22", pydht22Methods);
}
