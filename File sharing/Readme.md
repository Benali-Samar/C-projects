
	In here you find the locks of file sharing demo using flocks
	on a file containing a value 100 and than process A read that value
	and minus -20 of it and B reads that file and it find that the value
	is still 100 because of retarding updating so flocks just reserve the 
	file untill it ends its processing and than liberating it for other 
	processes.


*A producer should gain an exclusive lock on the file before writing to the file. An exclusive lock can be held by one process at most, which rules out a race condition because no other process can access the file until the lock is released.

*A consumer should gain at least a shared lock on the file before reading from the file. Multiple readers can hold a shared lock at the same time, but no writer can access a file when even a single reader holds a shared lock.



The standard I/O library includes a utility function named fcntl that can be used to inspect and manipulate both exclusive and shared locks on a file. 
For file locking, Linux provides the library function flock, which is a thin wrapper around fcntl. The first example uses the fcntl function to expose API details.

