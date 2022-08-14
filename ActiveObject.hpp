#ifndef ACTIVE_OBJECT_HPP
#define ACTIVE_OBJECT_HPP
#pragma once

#include "TsQueue.hpp"

template<typename T> class ActiveObject{
private:
TsQueue<T> safeQueue;

public:
ActiveObject() {

}

virtual ~ActiveObject() {

}
ActiveObject(const ActiveObject&) = delete;
ActiveObject(const ActiveObject&&) = delete;
ActiveObject& operator=(const ActiveObject&) = delete;


};


#endif // ACTIVE_OBJECT_HPP