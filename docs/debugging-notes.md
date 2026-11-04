# Student Management System Debugging Checklist

## Understanding Existing Code

- [ ] What behavior is expected, and what happens instead?
- [ ] Which classes and functions handle the affected student or management operation?
- [ ] How does data flow between `main`, the manager, and the student model?
- [ ] Can the issue be reproduced with a small, specific sequence of inputs?
- [ ] What changed recently, and does the issue occur before that change?

## Compiler and Linker Errors

- [ ] What is the first diagnostic, and does it identify the root error or a follow-on error?
- [ ] Do the source definitions match their declarations in headers?
- [ ] Are required headers included, and are declarations visible where used?
- [ ] Are all required source files compiled and linked exactly once?
- [ ] Is the project being built with the expected C++17 settings?

## Runtime Crashes

- [ ] What exact input and operation trigger the crash?
- [ ] Which line and call stack were active when it occurred?
- [ ] Could an object be null, uninitialized, or already destroyed?
- [ ] Are indexes and iterators valid for the container being accessed?
- [ ] Does the crash still occur with a minimal reproducible input?

## Undefined Behavior

- [ ] Is any variable read before it is initialized?
- [ ] Could code access an object outside its lifetime or an array/container out of bounds?
- [ ] Are integer operations, conversions, and input parsing within valid ranges?
- [ ] Are references, pointers, and iterators still valid after modifying a container?
- [ ] Can the issue be reproduced under compiler warnings or runtime sanitizers?

## Memory Leaks and Dangling Pointers

- [ ] Who owns each dynamically allocated object, and where is that ownership released?
- [ ] Can RAII or a smart pointer express ownership more safely?
- [ ] Does any pointer or reference outlive the object it refers to?
- [ ] Can container changes invalidate stored pointers, references, or iterators?
- [ ] Are resources released correctly on early returns and error paths?

## Multi-file Dependency Problems

- [ ] Do headers declare the same interfaces that source files define?
- [ ] Are include guards or `#pragma once` preventing repeated inclusion?
- [ ] Are definitions placed in the correct namespace and linked from the expected files?
- [ ] Are there duplicate definitions or missing source files in the build configuration?
- [ ] Do dependent files need rebuilding after a header or interface change?

## Static Analysis

- [ ] What compiler warnings or static-analysis diagnostics apply to the affected code?
- [ ] Are there warnings about conversions, uninitialized values, ownership, or unreachable code?
- [ ] Does analysis identify unsafe input handling or unchecked return values?
- [ ] Have relevant diagnostics been resolved rather than suppressed?

## Testing After Applying a Fix

- [ ] Does the project compile and link successfully using its C++17 configuration?
- [ ] Does the original reproducing case now behave as expected?
- [ ] Do normal student-management operations still work?
- [ ] Have relevant boundary cases and invalid inputs been tested?
- [ ] Have regression tests or a manual execution check confirmed existing functionality is preserved?