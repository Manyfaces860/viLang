#include <ctime>
#include <chrono>
#include "include/token.h"
#include "include/library.h"

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