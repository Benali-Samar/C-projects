

#PIPE () usage: 

Using pipe for inter-process communication, with sending a PIN from the child process to the parent process using pipe.
Then read the PIN from the pipe in the parent process.

The child process creation using "fork()".

The token p is generated only once outside the loop using the getP() function. The same token is then sent from each child process to the parent process through the pipe. The parent process reads the token from the pipe and waits for all child processes to finish using a loop and wait().

After all child processes have completed, the parent process prints the received token.

After running the program u should see something like this:

	Hello from child process! child PID: 121662
	Sending p from child to parent ...
	Hello from child process! child PID: 121663
	Sending p from child to parent ...
	Hello from child process! child PID: 121664
	Sending p from child to parent ...
	Hello from the parent process! Parent PID: 121661
	Parent recieving p '4203'


