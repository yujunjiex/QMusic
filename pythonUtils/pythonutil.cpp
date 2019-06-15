#include "pythonutil.h"
#include <QTextCodec>


PythonUtil::PythonUtil()
{
}

void PythonUtil::init()
{



       if(!Py_IsInitialized())
       {
//           qDebug()<<"failed";
           Py_Initialize();

       }
       else{
           qDebug()<<"已初始化";
       }

}

PyObject *PythonUtil::open(char *moduleName, char *funName)
{


   //引入模块
   PyObject * module=PyImport_ImportModule(moduleName);
   if(!module)
   {
       qDebug()<<"can not find files";
       return NULL;
   }
   //加载模块和要执行的方法
   PyObject * pf=PyObject_GetAttrString(module,funName);
   if(!pf)
   {
       qDebug()<<"Can not open python files";
         return NULL;
   }
    PyObject * res =NULL;
           qDebug()<<"不带参数";
           //执行不带参数的方法并得到返回值
           res=PyEval_CallObject(pf,NULL);

           return res;
}

PyObject *PythonUtil::open(char *moduleName, char *funName, const QList<QString> & params)
{
        //初始化
//                Py_Initialize();

//               if(!Py_IsInitialized())
//               {
//                   qDebug()<<"failed";
//                   return NULL;
//               }
               //引入模块
               PyObject * module=PyImport_ImportModule(moduleName);
               if(!module)
               {
                   qDebug()<<"can not find files";
                   return NULL;
               }
               //加载模块和要执行的方法
               PyObject * pf=PyObject_GetAttrString(module,funName);
               if(!pf)
               {
                   qDebug()<<"Can not open python files";
                     return NULL;
               }
                PyObject * res =NULL;
                PyObject * args = PyTuple_New(1);
                PyObject *  pList=PyList_New(params.size());
                for(int i=0;i<params.size();i++)
                {

                    PyList_SetItem(pList,i,StringToPyObject(params.at(i)));
                }
                   PyTuple_SetItem(args,0,pList);
                   //执行带参数的方法
                   res=PyEval_CallObject(pf,args);

          return res;
}

PyObject *PythonUtil::open(char *moduleName, char *funName, const QList<int> & params)
{
//                Py_Initialize();

//               if(!Py_IsInitialized())
//               {
//                   qDebug()<<"failed";
//                   return NULL;
//               }
               //引入模块
               PyObject * module=PyImport_ImportModule(moduleName);
               if(!module)
               {
                   qDebug()<<"can not find files";
                   return NULL;
               }
               //加载模块和要执行的方法
               PyObject * pf=PyObject_GetAttrString(module,funName);
               if(!pf)
               {
                   qDebug()<<"Can not open python files";
                     return NULL;
               }
                PyObject * res =NULL;
              PyObject * args = PyTuple_New(1);
              PyObject *  pList=PyList_New(params.size());
            for(int i=0;i<params.size();i++)
            {

                PyList_SetItem(pList,i,IntToPyObject(params.at(i)));
            }
               PyTuple_SetItem(args,0,pList);
               //执行带参数的方法
               res=PyEval_CallObject(pf,args);

         return res;
}

PyObject *PythonUtil::open(char *moduleName, char *funName, const QString & param)
{
//            Py_Initialize();

//           if(!Py_IsInitialized())
//           {
//               qDebug()<<"failed";
//               return NULL;
//           }
           //引入模块
           PyObject * module=PyImport_ImportModule(moduleName);
           if(!module)
           {
               qDebug()<<"can not find files";
               return NULL;
           }
           //加载模块和要执行的方法
           PyObject * pf=PyObject_GetAttrString(module,funName);
           if(!pf)
           {
               qDebug()<<"Can not open python files";
                 return NULL;
           }
             PyObject * res =NULL;
             PyObject * args = PyTuple_New(1);
             PyObject * arg= StringToPyObject(param);

             PyTuple_SetItem(args,0,arg);
             res=PyEval_CallObject(pf,args);

             return res;


}

PyObject *PythonUtil::open(char *moduleName, char *funName, const QString &param1, const QString &param2)
{
//                Py_Initialize();

//               if(!Py_IsInitialized())
//               {
//                   qDebug()<<"failed";
//                   return NULL;
//               }
               //引入模块
               PyObject * module=PyImport_ImportModule(moduleName);
               if(!module)
               {
                   qDebug()<<"can not find files";
                   return NULL;
               }
               //加载模块和要执行的方法
               PyObject * pf=PyObject_GetAttrString(module,funName);
               if(!pf)
               {
                   qDebug()<<"Can not open python files";
                     return NULL;
               }
                 PyObject * res =NULL;
                 PyObject * args = PyTuple_New(2);
                 PyObject * arg1= StringToPyObject(param1);
                 PyObject * arg2=StringToPyObject(param2);
                 PyTuple_SetItem(args,0,arg1);
                 PyTuple_SetItem(args,1,arg2);
                 res=PyEval_CallObject(pf,args);

                 return res;

}

PyObject *PythonUtil::open(char *moduleName, char *funName, const QString &param1, const int param2)
{
    PyObject * module=PyImport_ImportModule(moduleName);
    if(!module)
    {
        qDebug()<<"can not find files";
        return NULL;
    }
    //加载模块和要执行的方法
    PyObject * pf=PyObject_GetAttrString(module,funName);
    if(!pf)
    {
        qDebug()<<"Can not open python files";
          return NULL;
    }
      PyObject * res =NULL;
      PyObject * args = PyTuple_New(2);
      PyObject * arg1= StringToPyObject(param1);
      PyObject * arg2=IntToPyObject(param2);
      PyTuple_SetItem(args,0,arg1);
      PyTuple_SetItem(args,1,arg2);
      res=PyEval_CallObject(pf,args);

      return res;

}

PyObject *PythonUtil::open(char *moduleName, char *funName, const int &param)
{
//    Py_Initialize();

//   if(!Py_IsInitialized())
//   {
//       qDebug()<<"failed";
//       return NULL;
//   }

   qDebug()<<moduleName;
   qDebug()<<funName;
   qDebug()<<param;

   //引入模块
   PyObject * module=PyImport_ImportModule(moduleName);
   if(!module)
   {
      qDebug()<<"can not find files";
      return NULL;
   }
   //加载模块和要执行的方法

   PyObject * pf=PyObject_GetAttrString(module,funName);
   if(!pf)
   {
       qDebug()<<"Can not open python files";
         return NULL;
   }
     PyObject * res =NULL;
     PyObject * args = PyTuple_New(1);
     PyObject * arg= IntToPyObject(param);

     PyTuple_SetItem(args,0,arg);
     res=PyEval_CallObject(pf,args);

     return res;
}

void PythonUtil::close()
{
    Py_Finalize();
}

PyObject *PythonUtil::IntToPyObject(int val)
{
      PyObject * obj=Py_BuildValue("i",val);
      return obj;
}

PyObject *PythonUtil::StringToPyObject(QString param)
{
        const char * str;

        str = param.toStdString().data();

        PyObject * obj=Py_BuildValue("s",str);

      return obj;
}
