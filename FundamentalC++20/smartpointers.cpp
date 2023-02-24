/*
Old design pattern
+ allocate dynamic memory --> assign the address of that memory to a pointer
--> use the pointer to manipulate the memory --> deallocate the memory when it's no longer needed
If an exception occurs before deallocation --> memory leak

Solution:
RAII - Resource Acquitision Is Initilization
+ create local object and acquire the resource during construction
+ use the object
+ when the object goes out of scope, destructor called automatically to release the resource

*/