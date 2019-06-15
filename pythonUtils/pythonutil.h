#ifndef PYTHONUTIL_H
#define PYTHONUTIL_H
#include<qlist.h>
#include <qdebug.h>
#include<Python.h>


class PythonUtil
{
public:
    PythonUtil();
    static void     init();
    static PyObject *open(char * moduleName,char * funName);
    static PyObject *open(char * moduleName,char * funName,const QList<QString> & params);
    static PyObject *open(char * moduleName,char * funName,const QList<int> & params);
    static PyObject *open(char * moduleName,char* funName,const QString & param);
    static PyObject *open(char * moduleName,char * funName,const QString  &arg1,const QString & arg2);
    static PyObject *open(char * moduleName,char * funName,const QString &param1,const int param2);
    static PyObject *open(char * moduleName, char * funName,const int & param);
    static void      close();
    static PyObject * IntToPyObject(int val);
    static PyObject * StringToPyObject(QString param);
};

#endif // PYTHONUTIL_H
