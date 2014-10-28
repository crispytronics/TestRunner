#include "TestRunner.h"

/*-------------------------------------
 * TESTS
 *------------------------------------*/
int i = 0;

// Tests are defined like this
char test1(char state) {
   // Setup the test here
   if(state == SETUP) {
      i = 0;
      return -1;
   }
   
   /* The actual test goes here.  TestRunner will continue calling this until one of the 
      following happens:  test returns 0 (test failed), test returns 1 (test passed), or the 
      test has timed out.  Returning -1 will tell the test runner that the test is still in 
      progress and to call it again if the test hasn't timed out.  It's encouraged to make 
      your tests as simple as possible and let the test runner do the work! */
   if(state == RUN) {
      // The current value can be reported like this
      currentValue(i++, "V");
      delay(1000);
      
      if(i < 3) {
         // Test isn't finished yet
         return -1;
      }
      
      // Test passed
      return 1; 
   }
   
   // Teardown the test here
   if(state == TEARDOWN) {
      return -1;
   }
}

char test2(char state) {
   // Setup the test here
   if(state == SETUP) {
      i = 0;
      return -1;
   }
   
   /* The actual test goes here.  TestRunner will continue calling this until one of the 
      following happens:  test returns 0 (test failed), test returns 1 (test passed), or the 
      test has timed out.  Returning -1 will tell the test runner that the test is still in 
      progress and to call it again if the test hasn't timed out.  It's encouraged to make 
      your tests as simple as possible and let the test runner do the work! */
   if(state == RUN) {
      // The current value can be reported like this
      currentValue(i++, "V");
      delay(1000);
      
      if(i < 3) {
         // Test isn't finished yet
         return -1;
      }
      
      // Test passed
      return 0; 
   }
   
   // Teardown the test here
   if(state == TEARDOWN) {
      return -1;
   }
}

// Test suites are defined like this
void testSuite(int mode) {
   // Include a test in a test suite like this
   runTest("Test 1", SECONDS(4), test1);
   runTest("Test 2", SECONDS(4), test2);
}

/*-------------------------------------
 * SETUP
 *------------------------------------*/
void setup() {
  // Serial is needed by TestRunner, initialize it here 
  Serial.begin(9600);
}


/*-------------------------------------
 * LOOP
 *------------------------------------*/
void loop() {
   // Run returns -1 on error or the mode on success.  If no mode is provided, then 0 will be returned.
   int mode = run();

   // Validate mode here if needed
   if(mode >= 0) {
      // Test suites are run like this
      runSuite("My Test Suite", testSuite, mode);
   }  
}

