//
// Created by shea on 12/31/21.
//
#include <Python.h>
int main(int argc, char *argv[]) {
    Py_SetProgramName(reinterpret_cast<const wchar_t *>(argv[0])); /* optional but recommended */
    Py_Initialize();
    PyRun_SimpleString("from time import time,ctime\n"
                       "print (\"Today is\",ctime(time()))\n");
    Py_Finalize();
    return 0;
}
