# Arduino Test Runner
[![wercker status](https://app.wercker.com/status/7ad473da876df82c915605888d7c96c2/s "wercker status")](https://app.wercker.com/project/bykey/7ad473da876df82c915605888d7c96c2)

A library for running test cases on Arduino.

## Installation
Download the library [here](https://github.com/crispytronics/TestRunner/releases/download/v1.0.1/TestRunner.zip) and follow the instructions [here](http://arduino.cc/en/Guide/Libraries) to install the library in the Arduino IDE.

## Usage
See [boilerplate.pde](https://github.com/crispytronics/TestRunner/blob/master/examples/boilerplate/boilerplate.pde) for example usage.

## Protocol
The test runner uses a simple, JSON protocol for communicating with the host. 

### Run Tests
Tells the Arduino to run the test suite.  An optional mode (integer) may be provided which can be used to test different variants. The command is terminated with a single newline character (i.e. 0x0d).

```
run OPTIONAL_MODE
```

### Test Suite Started
Tells the host that the test suite is running.

```
{ "action": "test-suite-started" }
```

### Test Suite Finished
Tells the host that the test suite has finished running.

```
{ "action": "test-suite-finished" }
```

### Test Started
Tells the host that a test case has started.

```
{ "action": "test-started", "name": "TEST_NAME" }
```

### Current Value
Tells the host the current value (float) of the test.  This message is optional, but it's useful for giving insight into long running tests. This value is stored internally, so it can be sent at the end of the test.

```
{ "action": "current-value", "value": TEST_VALUE }
```

### Test Finished
Tells the host that the test has finished.  If a current value was sent at any point during the test, the final value will be included in this message.

```
{ "action": "test-finished", "result": "PASS/FAIL", "duration": DURATION_IN_MILLISECONDS, "value": OPTIONAL_FINAL_VALUE }
 ```
 
### Error
Tells the host that an error has occurred.

```
{ "error": "ERROR_MESSAGE" }
```
