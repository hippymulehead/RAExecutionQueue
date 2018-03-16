RAExecutionQueue by Michael Romans of Romans Audio

A pseudo RTOS execution queue for the Arduino platform.  By pseudo I mean that the times
are not guaranteed but should be pretty close.  The lower the ID the higher priority in
the queue the process has if two things have to happen at the same time.

This is handy for things like the DHT sensors where you can't hit them every time
through loop but you don't want to block loop by using a delay call.  Or for creating
a clocking system in your code where the clock variable only needs to update every n
millis.  I hope you find it useful.

Things I'm looking at adding...
1) Dynamic Queue Size
    This would allow you to add and remove queue items at runtime and not have to define
    a queue size.  Not sure How useful that would be but it sounds like fun.
2) Queue items tied to digital input pins
    Think queue item that only runs when triggered from a rising pin value on a digital pin.
    Like a pseudo interrupt.

RAExecutionQueue(int numberOfQueueItems);
	Create a Execution Queue of a set size.

virtual ~RAExecutionQueue();
	Release the execution queue.

void addProcess(int ID, void (*userFunc)(void),unsigned long millisTime);
	Add a process (your code) to the execution queue.
		ID is the array pos.  (First at 0)
		*userFunc is a pointer to your function.  No returns, no params.
		How often in millis to execute the function

void addHardwareInterrupt(uint8_t pinNumber, void (*userFunc)(void), int mode);
	Convenience function to allow adding interrupts through the queue
		See docs for attachInterrupt()

void stopInterrupts()
	Convenience function to allow adding interrupts through the queue
		See docs for nointerrupts()

void restartInterrupts()
	Convenience function to allow adding interrupts through the queue
		See docs for interrupt()

void processQueue();
	run through the queue and see what needs done.  This goes in loop();

void start();
	Start the queue running.  All processes are initialized with the same base time.

void stop();
	Stop the queue from running.
		This DOES NOT set the items running state so if you start it again things that
		were not running will still not be running.

void reset();
	Reset the queue start time to now.

void startQueueItem(int ID);
	Start an individual queue item.
		ID is an array pos you assigned when you created the process.

void stopQueueItem(int ID);
	Stop an individule queue item.
		ID is an array pos you assigned when you created the process.

void invertQueueItemRunning(int ID);
	Invert the running status of a queue item

int queueItemRunning(int ID);
	Check to see the running status of the queue item and invert it.
