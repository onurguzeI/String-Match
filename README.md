# String-Matching-Algorithm

This algorithm uses brute force string matching technique solve the challanges shared below; 

#### FIB

This algorithm is used for filling in the blanks, given the statements and the original script.

#### Q&A

This algorithm is used for providing answers to the question statements given the original script

## How to Use 

- Add the original script and the statements file to the code block shown below;

```c#
vector<string> statements = splitStatements("[Statements_File_Name]");
vector<string> sentences = splitSentences("[Input_File_Name]");
```
- Open a new terminal 

- Use the command ```make``` to compile the code 

- Use ```./StringMatch``` command to run the code 

### Example Output 



- #### FIB
```
looks up into the sky but there is no ___ in sight
He looks up into the sky but there is no plane in sight 
----------------------------------------------
----------------------------------------------
Truman regards his companion in a new ___ He comes
" Truman regards his companion in a new light 
----------------------------------------------
----------------------------------------------
God, Truman almost hit ___!
God, Truman almost hit Marilyn! 
----------------------------------------------
----------------------------------------------
Truman notices that the traffic jam in the street and the ___ crowd of pedestrians
As he departs, Truman notices that the traffic jam in the street and the mysterious crowd of pedestrians has dissolved 
----------------------------------------------
----------------------------------------------
```
 - #### Q&A
```
Who is suddenly aware that the hundreds of other beachgoers have stopped their activities to stare at him
TRUMAN 
With an apathetic shrug, what does Truman replace
RECEIVER 
He picks up the framed picture of his wife from where
DESK 
The sound of the children triggers what in his head
MEMORY 
What does Truman exit to investigate
OLDSMOBILE 
How many girls look up, surprised by the interruption
3 
What time is read on a clock on the wall
4:12PM 
What color is the cardigan she is already removing from the drycleaning bag on the back seat as Truman pulls away from the curb
LAVENDER 

```
