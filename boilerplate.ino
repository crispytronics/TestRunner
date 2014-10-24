#include "TestRunner.h"

/*-------------------------------------
 * TESTS
 *------------------------------------*/
int i = 0;
char test1(char state) {
   if(state == SETUP) {
      // setup the test here
   }
   if(state == RUN) {
      currentValue(i++);
      delay(250);
      if(i < 3) {
         return -1;
      }
      return 1; 
   }
   if(state == TEARDOWN) {
      // teardown the test here
   }
}

void testSuite(int mode) {
   runTest("Test 1", SECONDS(1), test1);
}

/*-------------------------------------
 * SETUP
 *------------------------------------*/
void setup() {
  // Serial is needed by TestRunner, initialize it here... 
  Serial.begin(9600);
}


/*-------------------------------------
 * LOOP
 *------------------------------------*/
void loop() {
   int mode = run();

   // validate mode here if needed
   if(mode >= 0) {
      runSuite("My Test Suite", testSuite, mode);
   }  
}

