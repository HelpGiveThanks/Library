July 20, 2018 17:17:38 Library.fmp12 - catchFindLearnErrorMessages -1-
learn: catchFindLearnErrorMessages
#
#This script is used by the findLearnRecord script.
#
#!!! IMPORTANT !!! SAY WHAT !!! HERE YE, HERE YE !!!
#
#The error check logic of this script is identical
#to the logic in the ActionLog's catch error
#message script and the catchFindReferenceErrorMessage
#script. Any changes made to this logic needs
#to also be made to those scripts to keep
#them all identical.
#
#!!! IMPORTANT !!! SAY WHAT !!! HERE YE, HERE YE !!!
#
#
#BEGIN identical catch error logic
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#
#Copy the user's current find request.
Set Variable [ $$note; Value:testlearn::note ]
Set Variable [ $$timestamp; Value:testlearn::timestamp ]
Set Variable [ $$brainstormCasePoint; Value:testlearn::brainstormCasePoint ]
#
#
#Enter the text field and exit it to see if a "user
#cancelled action" = 1 error is generated or the
#508 = "invalid find request" variable is generated.
If [ $$note ≠ "" ]
Set Field [ testlearn::note; $$note ]
#
#BUG: The 1 error is a bug because the script,
#not the user, is generating the error. If the user
#actually click's into another field causing the
#error that this script will now look for, FileMaker
#fails to pass along this error code. The only
#way to know if it is happening is to have a
#script generate this "user" caused 1 error.
# Now in the test of a text field, FileMaker
#will not allow an invalid find request to be
#entered by the script, generating a 508 error
#when the attempt is made. In contrast, an
#invalid find request is allowed to be put into
#a date field by FileMaker = 500 error,
#however, FileMaker will not allow the script to
#leave the bad date in the field and generates
#the "user cancelled action" = 1 error when
#the script moves on.
#
#If an error is produced...
If [ Get (LastError) = 1 or Get (LastError) = 508 ]
#
#Check the text field to see if an error is being
#caused by question marks.
If [ Left ( Filter ( $$note ; "?" ) ; 1 ) = "?" and Left ( $$note ; 2 ) ≠ "*\"" and Right ( $$note ; 1 ) ≠ "\""
or
Left ( Filter ( $$note ; "?" ) ; 1 ) = "?" and Left ( $$note ; 1 ) ≠ "\"" and Right ( $$note ; 1 ) ≠ "\"" ]
#
#Make find request valid.
Set Field [ testlearn::note; "*" & Quote ( $$note ) ]
#
#Explain problem with question marks in the
#find request.
Show Custom Dialog [ Message: "Find requests that include a question mark with a space between it and another
character, or find requests with two or more question marks in a row \"like this ???\" must be put in quotes."; Default
Button: “OK”, Commit: “No” ]
Show Custom Dialog [ Message: "This is now done. The astrix before the first quote is to find what you've typed
starting from anywhere including the beginning of phase, or the middle of a word."; Default Button: “OK”, Commit:
“No” ]
#
#Return to the text field and allow the user to
#edit their find request.
Go to Field [ testlearn::note ]
Pause/Resume Script [ Indefinitely ]
#
#If this script was activated by the user, which
#would turn on the GoToField variable...
If [ $$GoToField ≠ "" ]
#
#Reset this go to field variable for future use.
Set Variable [ $$GoToField ]
Exit Script [ ]
#
#If this script was activated by find script...
Else If [ $$GoToField = "" ]
#
#Start this script over.
# NOTE: The user can leave a text box with
#an invalid find, and if they do by hitting the
#return key on a desktop computer, or the go
#key on an iDevice keyboard, this script will
#exit, which is bad. This relaunch of
#this script below is exactly what happens
#when the user clicks the 'find' button on the
#layout.
# A copy of this script needs to be running
#during a find request session to catch any
#textbox invalid find requests, and inform the
#user about how to deal with them.
# The result being that many copies of the
#script will be running if the user makes many
#invalid find requests in a row. No problem.
# Once the user finally makes a valid find
#request, or cancels their find session, this
#script or the cancel find script will halt all
#copies of the script launched during the
#sesion.
Perform Script [ “findLearnRecord (update)” ]
Exit Script [ ]
End If
End If
End If
End If
#
#
#Check the timestamp field to see if it is
#improperly formatted.
If [ $$timestamp ≠ "" ]
#
#Enter the timestamp field and exit it to see if
#a "user cancelled action" = 1 error is generated.
#SEE ABOVE BUG.
Set Field [ testlearn::timestamp; $$timestamp ]
Go to Field [ testlearn::timestamp ]
Go to Field [ ]
#
#If an error is produced...
If [ Get (LastError) = 1 ]
Set Field [ testlearn::timestamp; $$timestamp ]
#
#Explain problems with enter date and time
#and how this problem can be addressed.
Show Custom Dialog [ Message: "Date searches must include both date and time entered like this" & ¶ & "1/5/2018
12:25:30."; Default Button: “OK”, Commit: “No” ]
Show Custom Dialog [ Message: "You can replace the M/D/2018 H:M:S numbers with asterisks to, for example, search by
year = */*/2018 *:*:*"; Default Button: “OK”, Commit: “No” ]
Show Custom Dialog [ Message: "Click the 'less than' (or search before this date), 'more than' (or search after this date), or
between dates search strategy buttons, and a properly formatted date search will be inserted for you to edit."; Default
Button: “OK”, Commit: “No” ]
#
#Return to the timestamp field and allow the
#user to edit their find request.
Go to Field [ testlearn::timestamp ]
Pause/Resume Script [ Indefinitely ]
#
#If this script was activated by the user, which
#would turn on the GoToField variable...
If [ $$GoToField ≠ "" ]
#
#Reset this go to field variable for future use.
Set Variable [ $$GoToField ]
Exit Script [ ]
#
#If this script was activated by find script...
Else If [ $$GoToField = "" ]
#
#Start this script over. SEE ABOVE NOTE.
Perform Script [ “findLearnRecord (update)” ]
Exit Script [ ]
End If
End If
End If
#
#
#Peform one last invalid find error check just to
#catch any that do not involve the quesion mark.
If [ $$caption ≠ "" ]
Set Field [ testlearn::note; $$note ]
#
#If an error is produced...
If [ Get (LastError) = 1 or Get (LastError) = 508 ]
#
#Make find request valid.
Set Field [ testlearn::note; "*" & Quote ( $$note ) ]
#
#Explain unknown invalid find request error
#and its remedy.
Show Custom Dialog [ Message: "Find request is producing an \"invalid find request\" error. Putting it in quotes should make
FileMaker happy."; Default Button: “OK”, Commit: “No” ]
Show Custom Dialog [ Message: "This is now done. The astrix before the first quote is to find what you've typed starting
from anywhere including the beginning of phase, or the middle of a word."; Default Button: “OK”, Commit: “No” ]
Show Custom Dialog [ Message: "If you continue to get this error message, you'll need to change your find request.";
Default Button: “OK”, Commit: “No” ]
#
#Return to the text field and allow the user to
#edit their find request.
Go to Field [ testlearn::note ]
Pause/Resume Script [ Indefinitely ]
#
#
#If this script was activated by the user, which
#would turn on the GoToField variable...
If [ $$GoToField ≠ "" ]
#
#Reset this go to field variable for future use.
Set Variable [ $$GoToField ]
Exit Script [ ]
#
#If this script was activated by find script...
Else If [ $$GoToField = "" ]
#
#Start this script over. SEE ABOVE NOTE.
Perform Script [ “findLearnRecord (update)” ]
Exit Script [ ]
End If
End If
End If
#
#
#In order to generate an invalid find request
#custom error message, I had to turn the
#layouts fields into buttons, which run scripts
#that all turn on this script and generate the
#error 1. If no error is actually found, these
#next steps actually enter the field the user
#wanted to enter. End result for the user is
#looks like they are entering a field instead of
#pressing a button. OH IF ONLY FileMaker
#would pass along the invalid find request
#variable!!! Well, until it does, this work around
#does the job (except when the user just hits
#the return key on a desktop computer).
If [ $$GoToField = "note" ]
Go to Field [ testlearn::note ]
#
Else If [ $$GoToField = "Timestamp" ]
Go to Field [ testlearn::timestamp ]
#
Else If [ $$GoToField = "brainstormCasePoint" ]
#
If [ testlearn::brainstormCasePoint = "" ]
Set Field [ testlearn::brainstormCasePoint; 1 ]
Go to Field [ ]
Else
Set Field [ testlearn::brainstormCasePoint; "" ]
Go to Field [ ]
End If
#
End If
#
#Reset this go to field variable for future use.
Set Variable [ $$GoToField ]
#
#
#END identical catch error logic
#
#
