#define RAQueueItem_h
#ifdef RAQueueItem_h

class RAQueueItem {
    public:
        RAQueueItem();
        void setID(int ID);
        void attachCallBack(void (*userFunc)(void));
        void setDuration(unsigned long duration);
        void start(unsigned long startTime);
        void stop();
        void reset(unsigned long startTime);
        void run();
        int counterValue();
        int isRunning();
    private:
        int             m_ID;
        unsigned long   m_duration;
        unsigned long   m_nowTime = 0;
        unsigned long   m_lastTime = 0;
        unsigned long   m_startTime = 0;
        unsigned long   m_counter = 0;
        unsigned long   m_lastCounter = 99;
        int             m_running = 0;
        void            (*m_userFunc)(void);
};
#endif
