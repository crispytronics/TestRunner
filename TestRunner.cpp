#include <Arduino.h>
#include "TestRunner.h"

float _testRunnerValue;
bool _testRunnerValueSet;

extern HardwareSerial Serial;

// Test callback returns -1 if in progress, 0 if failed, 1 if passed
void runTest(const char *name, long timeout, char (*test)(char))
{
   int result = -1;
   Serial.print("{ \"action\": \"test-started\", name: \"");
   Serial.print(name);
   Serial.println("\" }");

   // setup current val
   _testRunnerValueSet = false;

   // setup test
   test(SETUP);

   // run test
   unsigned long start = millis();
   while((result = test(RUN)) == -1) {
      if(millis() - start > timeout)
      {
         break;
      }
   }

   unsigned long done = millis();

   // teardown test
   test(TEARDOWN);

   // result
   Serial.print("{ \"action\": \"test-finished\" \"result\": ");
   if(done - start > timeout || result == 0)
   {
      Serial.print("\"fail\", ");
   }
   else 
   {
      Serial.print("\"pass\", ");
   }
   Serial.print("\"duration\": ");
   Serial.print(done - start);
   if(_testRunnerValueSet) {
      Serial.print(", \"value\": ");
      Serial.print(_testRunnerValue);
   }
   Serial.println(" }");
}

void currentValue(float value) {
   _testRunnerValueSet = true;
   _testRunnerValue = value;
   Serial.print("{ \"action\": \"current-value\", \"value\": ");
   Serial.print(_testRunnerValue);
   Serial.println(" }");
   Serial.flush();
}
