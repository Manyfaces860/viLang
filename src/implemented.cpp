#include <vector>
#include "token.h"
#include "include/implemented.h"
#include "include/interpreter.h"
#include "include/allstmt.h"
#include "include/util.h"

using std::vector;

// =================================================================================================

ViFunction::ViFunction(Function* declaration, Environment* closure, bool method) {
    this->declaration = declaration;
    this->closure = closure;
    this->method = method;
}

Object ViFunction::__call__(Interpreter* runtime, vector<Object>* arguments) {
    // std::cout << "[ViFunction::call] ENTER (this=" << this 
    //           << ") runtime globals=" << runtime->getGlobals()
    //           << " args count=" << arguments->size() << std::endl;
    Environment* previous = runtime->getGlobals();
    Environment* functionScope = new Environment(closure);
    runtime->setEnvironment(functionScope);
    
    for (int i = method ? 1 : 0; i < declaration->parameters.size(); i++) {
        functionScope->define(declaration->parameters[i]->lexeme, (*arguments)[method ? i-1 :i]);
    }

    // std::cout << runtime->getGlobals() << " address " << std::endl;
    try {
        runtime->execute(declaration->body);
    } catch (ReturnV& returnVal) {
        runtime->setEnvironment(previous);
        // delete functionScope;   write a garbage collector
        return std::move(returnVal.value);
    }
    runtime->setEnvironment(previous);
    return nullptr;
}

Object ViFunction::__arity__() {
    return (float)declaration->parameters.size();
}

Object ViFunction::__repr__() {
    return "<function '" + declaration->name->lexeme + "'>";
}

// =================================================================================================

ViClass::ViClass(string name, std::unordered_map<string, Object> methods) {
    this->name = name;
    this->methods = methods;
}

Object ViClass::__call__(Interpreter* runtime, vector<Object>* arguments) {
    std::shared_ptr<ViInstance> instance = std::make_shared<ViInstance>(this);
    Object initMethod = this->__find_method__("__init__");
    if (!isNull(initMethod)) instance->__bind__(initMethod)->__call__(runtime, arguments);
    else throw RuntimeError("No __init__ method was found in the class", instance->klass->name);
    return instance;
}

Object ViClass::__arity__() {
    return 0.0f;
}

Object ViClass::__repr__() {
    return "<class '" + this->name + "'>";
}

Object ViClass::__find_method__(const string& name) {
    if (this->methods.find(name) == this->methods.end()) return nullptr;
    return this->methods[name];
}

// =================================================================================================

ViInstance::ViInstance(ViClass* klass) {
    this->klass = klass;
}

Object ViInstance::__repr__() {
    return "<class Instance '" + this->klass->name + "'>";
}

Object ViInstance::__get__(Token* name) {
    if (this->fields.find(name->lexeme) != this->fields.end()) {
        return this->fields[name->lexeme];
    }

    Object method = this->klass->__find_method__(name->lexeme);
    if (isNull(method)) throw RuntimeError("property doesn't exit on instance", *name);

    return std::static_pointer_cast<ViCallable>(this->__bind__(method));
}

void ViInstance::__set__(string& name, Object value) {
    this->fields[name] = value;
}

std::shared_ptr<ViFunction> ViInstance::__bind__(Object methodPtr) {
    std::shared_ptr<ViFunction> method = std::static_pointer_cast<ViFunction>(getCallable(methodPtr));
    Environment* newClosure = new Environment(method->closure);
    if (method->declaration->parameters.size() == 0) throw RuntimeError("self or atleast one parameter is required in class methods", this->klass->name);
    newClosure->define(method->declaration->parameters[0]->lexeme, std::static_pointer_cast<Karanodak>(std::shared_ptr<ViInstance>(this)));
    method->closure = newClosure;
    return method;
}