#include <ctime>
#include <chrono>
#include <vector>
#include "token.h"
#include "include/callables.h"
#include "include/interpreter.h"
#include "include/allstmt.h"
#include "include/util.h"

using std::vector;

Object Clock::__call__(Interpreter* runtime, vector<Object>* arguments) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // std::tm local_tm = *std::localtime(&now_time);
    return std::ctime(&now_time);
} 

Object Clock::__arity__() {
    return 0.0f;
}

Object Clock::__repr__() {
    return "<built-in function clock >";
}

// =================================================================================================

ViFunction::ViFunction(Function* declaration, Environment* closure) {
    this->declaration = declaration;
    this->closure = closure;
}

Object ViFunction::__call__(Interpreter* runtime, vector<Object>* arguments) {
    // std::cout << "[ViFunction::call] ENTER (this=" << this 
    //           << ") runtime globals=" << runtime->getGlobals()
    //           << " args count=" << arguments->size() << std::endl;
    Environment* previous = runtime->getGlobals();
    Environment* functionScope = new Environment(closure);
    runtime->setEnvironment(functionScope);
    
    for (int i = 0; i < declaration->parameters.size(); i++) {
        functionScope->define(declaration->parameters[i]->lexeme, (*arguments)[i]);
    }

    // std::cout << runtime->getGlobals() << " address " << std::endl;
    try {
        runtime->execute(declaration->body);
    } catch (ReturnV& returnVal) {
        runtime->setEnvironment(previous);
        // delete functionScope;   write a garbage collector
        return std::move(returnVal.value);
    }
    
    return nullptr;
}

Object ViFunction::__arity__() {
    return (float)declaration->parameters.size();
}

Object ViFunction::__repr__() {
    return "<function " + declaration->name->lexeme + " >";
}

// =================================================================================================

Object Range::__call__(Interpreter* runtime, vector<Object>* arguments) {
    // int start = isFloat((*arguments)[0]) ? getFloat((*arguments)[0]) : 0;
    // int end = isFloat((*arguments)[1]) ? getFloat((*arguments)[1]) : 0;
    // int skip = isFloat((*arguments)[2]) ? getFloat((*arguments)[2]) : 1;
    

    // vector<Object>* buffer = new vector<Object>();
    // for (start; start < end; start += skip+1) buffer->push_back((float)start);
    // return buffer;
    return nullptr;
} 

Object Range::__arity__() {
    return 3.0f;
}

Object Range::__repr__() {
    return "<built-in function range >";
}