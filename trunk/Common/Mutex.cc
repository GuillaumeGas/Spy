#include "Mutex.hh"

Mutex::Mutex() {
}

void Mutex::lock() {
    m_mutex.lock();
}

void Mutex::unlock() {
    m_mutex.unlock();
}

Mutex::~Mutex() {
}
