# Arduino Test Runner

## Installation

## Usage

## Protocol
The test runner uses a simple, JSON protocol for communicating with the host.

### Run Tests
Tells the Arduino to run the test suite.  An optional mode (integer) may be provided which can be used to test different variants.

```
{ "cmd": "run", "mode": OPTIONAL_MODE }
```

### Acknowledge
Tells the host that the command has been accepted.

```
{ "action": "ack" }
```

### Error
Tells the host that an error has occurred.

```
{ "error": "ERROR_MESSAGE" }
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
