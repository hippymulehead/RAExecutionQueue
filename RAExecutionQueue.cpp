#include <Arduino.h>
#include <RAExecutionQueue.h>

RAExecutionQueue::RAExecutionQueue() {
    m_counter = 0;
}

RAExecutionQueue::~RAExecutionQueue() {
}

void RAExecutionQueue::addProcess(int index, void (*userFunc)(void),unsigned long millisTime) {
    m_queue.push_back(RAQueueItem());
    m_queue[index].setID(index);
    m_queue[index].setDuration(millisTime);
    m_queue[index].attachCallBack(userFunc);
    m_counter++;
}

void RAExecutionQueue::addHardwareInterrupt(uint8_t pinNumber, void (*userFunc)(void), int mode) {
    attachInterrupt(digitalPinToInterrupt(pinNumber),userFunc, mode);
}

void RAExecutionQueue::processQueue() {
    for (int i = 0; i < m_counter; i++) {
        if (m_queue[i].isRunning()) {
            m_queue[i].run();
        }
    }
}

void RAExecutionQueue::start() {
    m_queueStartTime = millis();
    for (int i = 0; i < m_counter; i++) {
        m_queue[i].start(m_queueStartTime);
    }
}

void RAExecutionQueue::stop() {
    m_queueStartTime = 0;
    for (int i = 0; i < m_counter; i++) {
        m_queue[i].stop();
    }
}

void RAExecutionQueue::reset() {
    if (m_queueStartTime != 0) {
        m_queueStartTime = millis();
    }
}

void RAExecutionQueue::startQueueItem(int index) {
    m_queue[index].start(m_queueStartTime);
}

void RAExecutionQueue::stopQueueItem(int index) {
    m_queue[index].stop();
}

int RAExecutionQueue::queueItemRunning(int index) {
    return m_queue[index].isRunning();
}

void RAExecutionQueue::stopInterrupts() {
    noInterrupts();
}

void RAExecutionQueue::restartInterrupts() {
    interrupts();
}

void RAExecutionQueue::invertQueueItemRunning(int index) {
    if (m_queue[index].isRunning()) {
        m_queue[index].stop();
    } else {
        m_queue[index].start(m_queueStartTime);
    }
}
