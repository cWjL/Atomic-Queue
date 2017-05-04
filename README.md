# Atomic-Queue
Test semaphore atomicity in multi-threaded execution
/*
*
*	Author:				  Jacob Loden
*
*	Description:		Program to test semaphore atomicity in multi-threaded execution.
*
*						      Program accepts command line integer parameter and runs the number
*						      of threads corresponding to this parameter.
*
*						      Program first starts parent thread, followed by N child threads.
*						      Parent waits for children to finish execution, then prints contents
*						      of global array of child threads.  Child threads increment the ith
*						      array elements and returns.
*
*						      Program will run until user enters <CTRL+C>
*
*
*/
