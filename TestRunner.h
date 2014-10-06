#define SETUP 0
#define RUN 1
#define TEARDOWN 2

#define SECONDS(x) (x * 1000)
#define MINUTES(x) (x * 60000)

// Test callback returns -1 if in progress, 0 if failed, 1 if passed
void runTest(const char *name, long timeout, char (*test)(char));