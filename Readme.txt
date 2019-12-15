GoIbibo Assignment.

Requirements:
1. Gcc compiler for C++ 11.

How to run the program:

It is a menu driven program. User would be shown various numerical options which he would have to select.

For the program to work as desired please follow the following steps:
1. Choose option 1 to add a new rule. User is asked to input hours (in integer only) and number of animals (integer only). 
	Output obtained is the rule id.
	Rule for the rule id is as follows:

	a. No two rules should contradict each other. For example if one rule say 5 hours => 6 animals and other says 6 hours => 3 animals, then its a violation.

2. Create a new dragon by choosing option 3. User is asked to input the name of the dragon only. Output obtained is the dragon id.

3. Choose option 4 to order the killing of animals. User is asked three parameters:
	
	a. DragonId (Obtained from step 2) (integer only).
	b. Number of animals (integer only).
	c. TimeStamp (YYYY-MM-DD-HH:MM). Please note for the timestamp year has to be greater than 1999 and lesser than 2011. This constraint 
	    was set because double type wasn't able to handle precision for year more tha 2010 when finding hours since 2000-01-01:00:00.

	Note: For a particular dragon, killing timeStamp must be greater than the last executed killing for that dragon.