#include <Arduino.h>
#include "TestRunner.h"

extern HardwareSerial Serial;

// Test callback returns -1 if in progress, 0 if failed, 1 if passed
void runTest(const char *name, long timeout, char (*test)(char))
{
   int result = -1;
   Serial.print("{ name: \"");
   Serial.print(name);
   Serial.print("\", ");

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
   Serial.print("\"result\": ");
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
   Serial.println(" }");
}