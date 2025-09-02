#pragma once
#include <unordered_map>
#include "objects.h"

class Function;
class Environment;

class ViFunction : public ViCallable {

    public:
        Function* declaration;
        Environment* closure;
        bool method;

        ViFunction(Function* declaration, Environment* closure, bool method);
        Object __call__(Interpreter* runtime, vector<Object>* arguments) override;
        Object __arity__() override;
        Object __repr__() override;
};

class ViClass : public ViCallable {
    
    public:
        string name;
        std::unordered_map<string, Object> methods;

        ViClass(string name, std::unordered_map<string, Object> methods);
        Object __call__(Interpreter* runtime, vector<Object>* arguments) override;
        Object __arity__() override;
        Object __repr__() override;
        Object __find_method__(const string& name);
};

class ViInstance : public Karanodak {

    public:
        ViClass* klass;
        std::unordered_map<string, Object> fields;

        ViInstance(ViClass* kclass);
        Object __repr__() override;
        Object __get__(Token* name);
        void __set__(string& name, Object value);
        std::shared_ptr<ViFunction> __bind__(Object methodPtr);
};