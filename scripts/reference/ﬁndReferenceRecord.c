July 20, 2018 21:52:25 Library.fmp12 - findReferenceRecord -1-
reference: findReferenceRecord
#
#
#!!! IMPORTANT !!! SAY WHAT !!! HERE YE, HERE YE !!!
#
#The find logic of this script is identical to the
#find logic in the findLearnRecord and the
#ActionLog's findSpecificAction script, as are
#their layouts where text and date field are
#concerned. Any changes made to this logic
#needs to also be made to those scripts to
#keep them identical.
#
#!!! IMPORTANT !!! SAY WHAT !!! HERE YE, HERE YE !!!
#
#
#If in find mode in the Tag Window, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Cancel find in Tag Menus window then click this button."; Default Button: “OK”, Commit:
“Yes” ]
Exit Script [ ]
End If
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current
#reference record will get deleted by the
#spelling check script.
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get ( ActiveFieldName ) ≠ "" ]
Show Custom Dialog [ Message: "You'll be able to perform a find once you exit the field you're in on the tag window."; Default
Button: “OK”, Commit: “Yes” ]
Select Window [ Name: "References"; Current file ]
Exit Script [ ]
End If
Select Window [ Name: "References"; Current file ]
#
#
#
#!!! IMPORTANT !!! SAY WHAT !!! HERE YE, HERE YE !!!
#
#BEGIN identical find logic
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#If the user has just clicked 'find' to perform
#a find and thus is not yet in find mode ...
If [ Get (WindowMode) ≠ 1 ]
#
#Capture the current layout name (to return user
#to it after find), enter find mode, go to the find
#layout, and await the user's find request.
Set Variable [ $$findReferenceLayout; Value:Get (LayoutName) ]
Enter Find Mode [ ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “ReferenceFIND” (reference) ]
Else
Go to Layout [ “ReferenceFINDstuff” (reference) ]
End If
Pause/Resume Script [ Indefinitely ]
#
End If
#
#
#
#If alread in find mode on the find layout ...
#
#FIRST check for find request errors,
#and copy current find request in case
#there are no errors but the find fails
#and the current find request needs
#to be re-entered by this script to
#allow the user to edit it for success.
If [ Get (WindowMode) = 1 ]
Perform Script [ “catchFindReferenceErrorMessages” ]
End If
#
#
#
#SECOND If there are no invalid find requests
#then perform the find.
If [ Get (WindowMode) = 1 ]
#
#Try to find the requested records.
Perform Find [ ]
#
#Get the error generated, which if successful
#will be zero.
Set Variable [ $error; Value:Get (LastError) ]
#
#Omit locked records, which are the copyright
#images used by default copyright tags.
Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::lock: “lock” ]
[ Restore ]
#
#If after removing the locked records, there are
#zero records, and the current error is not 508
#or 1 then set the error variable to 401 = no
#records found.
If [ Get (FoundCount) = 0 and $error ≠ 508 and $error ≠ 1 ]
Set Variable [ $error; Value:401 ]
End If
#
End If
#
#
#
#If the find was not successful...
#
#
#If the find attempt fails and generates a
#508 = invalid find request error or a 1 = user
#canceled action error.
If [ $error = 508 or $error = 1 ]
#
#Re-enter find mode to trigger the error capture
#portion of this script when it is restarted, which
#will tell the user what went wrong and how to
#fix it.
Enter Find Mode [ ]
#
#Start this script over.
Perform Script [ “findReferenceRecord” ]
#
End If
#
#
#If the find fails tell the user it failed and give them
#option to modify their request or cancel the find.
If [ $error = 401 or $error ≠ 0 and $error ≠ "" ]
#
#If currently not in find mode, then enter
#find mode.
If [ Get (WindowMode) ≠ 1 ]
Enter Find Mode [ ]
End If
#
#Replace user's last find requests so they can
#modify if they want to.
Set Variable [ $$putBackUserFindRequests; Value:1 ]
Perform Script [ “CHUNK_findReferenceRecordUserFindRequests” ]
Set Variable [ $$putBackUserFindRequests ]
#
#Inform the user that their find request found
#zero records.
Show Custom Dialog [ Message: "No records match this request."; Default Button: “cancel”, Commit: “No”; Button 2: “modify
find”, Commit: “No” ]
#
#
#If the user decides to modify their request
#then stay in find mode and await the user's
#new request.
If [ Get ( LastMessageChoice ) = 2 ]
Pause/Resume Script [ Indefinitely ]
#
#These next script steps only come into use
#if the user clicks the 'return' key on desktop
#computer's keyboard or the 'go' button on an
#iDevice. If instead, the user clicks the 'find'
#button again on the find layout, a duplicate
#copy of this script is started from the top to
#perform the find request.
#
#Start this script over. SEE NOTE ABOVE.
Perform Script [ “findReferenceRecord” ]
#
#
#If they cancel the find ...
Else If [ Get ( LastMessageChoice ) = 1 ]
#
#Return to main layout and
#enter browse mode.
Perform Script [ “cancelLearnAndRefFind” ]
#
End If
#
#
End If
#
#
#
#If the find is successful ...
#
#After a succesful find show the user
#the found records on the main layout.
If [ $$findReferenceLayout = "" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceStuff” (reference) ]
Else
Go to Layout [ “Reference” (reference) ]
End If
#
Else
Go to Layout [ $$findReferenceLayout ]
Set Variable [ $$findReferenceLayout ]
End If
Sort Records [ ]
[ No dialog ]
Scroll Window
[ Home ]
Go to Record/Request/Page
[ First ]
#
#
#Clear user find request variables.
Set Variable [ $$clearUserFindRequests; Value:1 ]
Perform Script [ “CHUNK_findReferenceRecordUserFindRequests” ]
Set Variable [ $$clearUserFindRequests ]
#
#Clear out all paused find scripts.
Halt Script
#
#
#!!! IMPORTANT !!! SAY WHAT !!! HERE YE, HERE YE !!!
#
#END identical find logic
#
