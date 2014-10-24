/*
TestRunner.cpp - Main source file for TestRunner library

Copyright (C) 2014 Kris Barrett

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
USA
 */

#include <Arduino.h>
#include "TestRunner.h"

float _testRunnerValue;
bool _testRunnerValueSet;

extern HardwareSerial Serial;

void runSuite(const char *name, void (*suite)(int), int mode) {
   Serial.print("{ \"action\": \"suite-started\", \"name\": \"");
   Serial.print(name);
   Serial.println("\" }");

   suite(mode);

   Serial.print("{ \"action\": \"suite-finished\" }");
}

// Test callback returns -1 if in progress, 0 if failed, 1 if passed
void runTest(const char *name, long timeout, char (*test)(char))
{
   int result = -1;
   Serial.print("{ \"action\": \"test-started\", \"name\": \"");
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
   Serial.print("{ \"action\": \"test-finished\", \"result\": ");
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

// returns -1 on error, mode on success, 0 if no mode provided
int run() {
   Serial.print("$ ");   

   String cmd = String();
   unsigned int index = 0;
   while(true) {
      char c;
      if(Serial.available()) {
         c = Serial.read();
         if(c == 0x0d) {
            Serial.println();
            break;
         }
         else if(c == 0x7f) {
            // do nothing
         }
         else {
            Serial.print(c);
            cmd += c;
         }
      }
   }
   Serial.println(cmd);
   if(cmd.startsWith("run")) {
      return cmd.substring(4).toInt();
   }
   return -1;
}
