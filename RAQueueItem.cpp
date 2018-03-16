#include <RAQueueItem.h>
#include <Arduino.h>

RAQueueItem::RAQueueItem() {
}

void RAQueueItem::setID(int ID) {
    m_ID = ID;
}

void RAQueueItem::attachCallBack(void (*userFunc)(void)) {
    m_userFunc = userFunc;
}

void RAQueueItem::start(unsigned long startTime) {
    m_startTime = startTime;
    m_running = 1;
}

void RAQueueItem::stop() {
    m_startTime = 0;
    m_running = 0;
}

void RAQueueItem::reset(unsigned long startTime) {
    m_startTime = millis();
    m_counter = 0;
}

void RAQueueItem::setDuration(unsigned long duration) {
    m_duration = duration;
}

void RAQueueItem::run() {
    m_nowTime = (millis() - m_startTime);
	if (m_nowTime >= (m_lastTime + m_duration)) {
		m_counter++;
		m_lastTime = m_lastTime + m_duration;
        m_userFunc();
	}
	if (m_counter != m_lastCounter) {
		m_lastCounter = m_counter;
	}
}

int RAQueueItem::counterValue() {
    return m_counter;
}

int RAQueueItem::isRunning() {
    return m_running;
}
