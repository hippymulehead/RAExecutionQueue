#ifndef RAEXECUTIONQUEUE_H
#define RAEXECUTIONQUEUE_H
#include "RAQueueItem.h"
#include "RAMiniVector.h"

class RAExecutionQueue {
    public:
        RAExecutionQueue();
        virtual ~RAExecutionQueue();
        void addProcess(int index, void (*userFunc)(void),unsigned long millisTime);
        void addHardwareInterrupt(uint8_t pinNumber, void (*userFunc)(void), int mode);
        void processQueue();
        void start();
        void stop();
        void reset();
        void startQueueItem(int index);
        void stopQueueItem(int index);
        void invertQueueItemRunning(int index);
        void stopInterrupts();
        void restartInterrupts();
        int queueItemRunning(int index);

    protected:
        RAMiniVector <RAQueueItem>  m_queue;
        unsigned long               m_queueStartTime = 0;
        int                         m_counter;

    private:
};

#endif // RAEXECUTIONQUEUE_H
