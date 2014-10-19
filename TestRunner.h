/*
TestRunner.h - Main header file for TestRunner library

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

#define SETUP 0
#define RUN 1
#define TEARDOWN 2

#define SECONDS(x) (x * 1000)
#define MINUTES(x) (x * 60000)

// Test callback returns -1 if in progress, 0 if failed, 1 if passed
void runSuite(void (*suite)(void));
void runTest(const char *name, long timeout, char (*test)(char));
void currentValue(float value);
int start();
