July 20, 2018 21:33:26 Library.fmp12 - catchFindReferenceErrorMessages -1-
reference: catchFindReferenceErrorMessages
#
#This script is used by the findReference
#Record script.
#
#!!! IMPORTANT !!! SAY WHAT !!! HERE YE, HERE YE !!!
#
#The error check logic of this script is identical
#to the logic in the ActionLog's catch error
#message script and the catchFindLearnErrorMessage
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
Set Variable [ $$captureUserFindRequests; Value:1 ]
Perform Script [ “CHUNK_findReferenceRecordUserFindRequests (update)” ]
Set Variable [ $$captureUserFindRequests ]
#
#
#Enter the text field and exit it to see if a "user
#cancelled action" = 1 error is generated or the
#508 = "invalid find request" variable is generated.
If [ $$r4 ≠ "" ]
Set Field [ reference::referenceForReferenceFINDWindow; $$r4 ]
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
If [ Left ( Filter ( $$r4 ; "?" ) ; 1 ) = "?" and Left ( $$r4 ; 2 ) ≠ "*\"" and Right ( $$r4 ; 1 ) ≠ "\""
or
Left ( Filter ( $$r4 ; "?" ) ; 1 ) = "?" and Left ( $$r4 ; 1 ) ≠ "\"" and Right ( $$r4 ; 1 ) ≠ "\"" ]
#
#Make find request valid.
Set Field [ reference::referenceForReferenceFINDWindow; "*" & Quote ( $$r4 ) ]
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
Go to Field [ reference::referenceForReferenceFINDWindow ]
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
Perform Script [ “findReferenceRecord (update)” ]
Exit Script [ ]
End If
End If
End If
End If
#
#
#Check the create date field to see if it is
#improperly formatted.
If [ $$r0 ≠ "" ]
#
#Enter the create date field and exit it to see if a
#"user cancelled action" = 1 error is generated.
#SEE ABOVE BUG.
Set Field [ reference::createDate; $$r0 ]
Go to Field [ reference::createDate ]
Go to Field [ ]
#
#If an error is produced...
If [ Get (LastError) = 1 ]
Set Field [ reference::createDate; $$r0 ]
#
#Explain problems with enter date and time
#and how this problem can be addressed.
Show Custom Dialog [ Message: "Date searches must include both date and time entered like this" & ¶ & "1/5/2016
12:25:30."; Default Button: “OK”, Commit: “No” ]
Show Custom Dialog [ Message: "You can replace the M/D/2016 H:M:S numbers with asterisks to, for example, search by
year = */*/2016 *:*:*"; Default Button: “OK”, Commit: “No” ]
Show Custom Dialog [ Message: "Click the 'less than' (or search before this date), 'more than' (or search after this date), or
between dates search strategy buttons, and a properly formatted date search will be inserted for you to edit."; Default
Button: “OK”, Commit: “No” ]
#
#Return to the create date field and allow the
#user to edit their find request.
Go to Field [ reference::createDate ]
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
Perform Script [ “findReferenceRecord (update)” ]
Exit Script [ ]
End If
End If
End If
#
#
#Check the modify date field to see if it is
#improperly formatted.
If [ $$r1 ≠ "" ]
#
#Enter the modify date field and exit it to see if
#a "user cancelled action" = 1 error is generated.
#SEE ABOVE BUG.
Set Field [ reference::modifyDate; $$r1 ]
Go to Field [ reference::modifyDate ]
Go to Field [ ]
#
#If an error is produced...
If [ Get (LastError) = 1 ]
Set Field [ reference::modifyDate; $$r1 ]
#
#Explain problems with enter date and time
#and how this problem can be addressed.
Show Custom Dialog [ Message: "Date searches must include both date and time entered like this" & ¶ & "1/5/2016
12:25:30."; Default Button: “OK”, Commit: “No” ]
Show Custom Dialog [ Message: "You can replace the M/D/2016 H:M:S numbers with asterisks to, for example, search by
year = */*/2016 *:*:*"; Default Button: “OK”, Commit: “No” ]
Show Custom Dialog [ Message: "Click the 'less than' (or search before this date), 'more than' (or search after this date), or
between dates search strategy buttons, and a properly formatted date search will be inserted for you to edit."; Default
Button: “OK”, Commit: “No” ]
#
#Return to the modify date field and allow the
#user to edit their find request.
Go to Field [ reference::modifyDate ]
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
Perform Script [ “findReferenceRecord (update)” ]
Exit Script [ ]
End If
End If
End If
#
#
#Peform one last invalid find error check just to
#catch any that do not involve the quesion mark.
If [ $$r4 ≠ "" ]
Set Field [ reference::referenceForReferenceFINDWindow; $$r4 ]
#
#If an error is produced...
If [ Get (LastError) = 1 or Get (LastError) = 508 ]
#
#Make find request valid.
Set Field [ reference::referenceForReferenceFINDWindow; "*" & Quote ( $$r4 ) ]
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
Go to Field [ reference::referenceForReferenceFINDWindow ]
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
Perform Script [ “findReferenceRecord (update)” ]
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
If [ $$GoToField = "reference" ]
Go to Field [ reference::referenceForReferenceFINDWindow ]
#
Else If [ $$GoToField = "createDate" ]
Go to Field [ reference::createDate ]
#
Else If [ $$GoToField = "modifyDate" ]
Go to Field [ reference::modifyDate ]
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
