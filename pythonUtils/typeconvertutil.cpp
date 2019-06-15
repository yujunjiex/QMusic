#include "typeconvertutil.h"

TypeConvertUtil::TypeConvertUtil()
{

}

int TypeConvertUtil::toInt(PyObject *object)
{
      int i;
      if(object)
      {
          PyArg_Parse(object,"i",&i);
      }

      return i;

}

char *TypeConvertUtil::toString(PyObject *  object)
{
    char * str=NULL;
    if(object)
    {
         PyArg_Parse(object,"s",&str);
    }

    return str;
}




QList<QString> TypeConvertUtil::toList(PyObject *object)
{
         QList<QString> list;
         if(object)
         {
             //检查是否为List
             if(PyList_Check(object))
             {
                 int size=PyList_Size(object);
                 for(int i=0;i<size;i++)
                 {
                      // 得到每个列表项
                      PyObject *ListItem = PyList_GetItem(object, i);
                      if(ListItem)
                      {

                          char * str=toString(ListItem);
                          list.append(str);

                      }

                 }
             }
         }

         return list;
}

QJsonObject TypeConvertUtil::toJsonObject(PyObject *object)
{
    QJsonObject json;
    if(object)
    {
         if(PyDict_Check(object))
         {
             PyObject * keys= PyDict_Keys(object);
             if(PyList_Check(keys))
             {
                  int size=PyList_Size(keys);

                  for(int i=0;i<size;i++)
                  {
                        PyObject * listItem=PyList_GetItem(keys,i);
                        char * key=toString(listItem);
                        PyObject * value=  PyDict_GetItemString(object,key);
                        int  t =toInt(value);
                        json.insert(key,t);
                  }
                  return json;
             }
        }
    }

    return json;
}

QJsonArray TypeConvertUtil::toJsonArray(PyObject *object)
{
    QJsonArray array;

    if(object)
    {
        if(PyList_Check(object))
        {
            for(int i=0;i<PyList_Size(object);i++)
            {
                PyObject * listItem=PyList_GetItem(object,i);
                QJsonObject json=toJsonObject(listItem);
                array.append(json);
            }
        }
    }

   return array;

}
