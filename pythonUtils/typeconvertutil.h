#ifndef TYPECONVERTUTIL_H
#define TYPECONVERTUTIL_H
#include<qlist.h>
#include<QJsonObject>
#include<QJsonArray>
#include<Python.h>



class TypeConvertUtil
{
public:
    TypeConvertUtil();
    static int  toInt(PyObject * object);
    static char * toString(PyObject * object);
    static QList<QString> toList(PyObject * object);
    static QJsonObject  toJsonObject(PyObject * object);
    static QJsonArray   toJsonArray(PyObject * object);
};

#endif // TYPECONVERTUTIL_H
