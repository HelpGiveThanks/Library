January 16, 2018 21:59:18 Library.fmp12 - findLearnRecord -1-
learn: findLearnRecord
#
#
#!!! IMPORTANT !!! SAY WHAT !!! HERE YE, HERE YE !!!
#
#The find logic of this script is identical to the
#find logic in the findReferenceRecord and the
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
Show Custom Dialog [ Message: "Exit find mode in the Tag Menus window, then click this button."; Default Button: “OK”,
Commit: “Yes” ]
Exit Script [ ]
End If
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current
#learn record will get deleted by the spelling
#check script.
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get ( ActiveFieldName ) ≠ "" ]
Show Custom Dialog [ Message: "You'll be able to perform a find once you exit the field you're in on the tag window."; Default
Button: “OK”, Commit: “No” ]
Select Window [ Name: "Learn"; Current file ]
Exit Script [ ]
End If
Select Window [ Name: "Learn"; Current file ]
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#If the user has just clicked 'find' to perform
#a find and thus is not yet in find mode ...
If [ Get (WindowMode) ≠ 1 ]
#
#
#First, see if the learn record is linked to other
#learn records, and find out if the user just
#wants to find these linked records.
#
#
#Check if the current Learn record
#references other Learn records or is
#referenced by other Learn records.
If [ Filter ( testlearn::kcreference ; "L" ) ≠ "" or $$LinkedLearnRecords ≠ "" ]
#
#If it does reference other Learn records, ask
#the user if they would like to find just those
#records, or continue to the find screen.
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "Find linked learn records (text areas highlighted purple)?" & ¶ & "OR" & ¶ & "Find
other?"; Default Button: “other”, Commit: “No”; Button 2: “linked”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "Find linked inventory records (text areas highlighted purple)?" & ¶ & "OR" & ¶ &
"Find other?"; Default Button: “other”, Commit: “No”; Button 2: “linked”, Commit: “No”; Button 3: “cancel”, Commit:
“No” ]
End If
#
#Exit script if user clicks cancel.
If [ Get ( LastMessageChoice ) = 3 ]
Exit Script [ ]
End If
#
If [ Get ( LastMessageChoice ) = 2 ]
#If the user wants to find just linked/
#referenced learn records...
#
#
#Determine if there are A) records it is linked to/
#referencing, and B) if other learn records link
#to it/referencing it.
If [ Filter ( testlearn::kcreference ; "L" ) ≠ ""
and
$$LinkedLearnRecords ≠ "" ]
#
#If both are found ask user if they want to see
#just the A records, or both A and B records.
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "This record 1) references and is 2) referenced by other Learn records.
Show 1 = Refs or 1 and 2 = Refs+?"; Default Button: “Ref+”, Commit: “Yes”; Button 2: “Ref”, Commit:
“No”; Button 3: “cancel”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "OPPS! A holder cannot be tagged with another holder tag. Return to
idea-library mode, where holder tags are labled as reference tags, and untag this record."; Default Button:
“OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "1) Remember the records that will now be found. 2) Click the 'back'
button. 3) Uncheck the 'inventory library' checkbox. 4) Click the 'Learn' button. 5) Go to the reference
tags menu, and 6) untag these records."; Default Button: “OK”, Commit: “Yes” ]
End If
If [ Get (LastMessageChoice) = 1 ]
Set Variable [ $showReferencesReferencingMe; Value:1 ]
End If
#
#If choice 2 is made go to the next section.
#
#Exit script if user clicks cancel (button 3).
If [ Get ( LastMessageChoice ) = 3 ]
Exit Script [ ]
End If
#
#
Else If [ $$LinkedLearnRecords ≠ "" ]
#If there are only records referencing this
#record, then find these records.
#
#Find original record first.
Set Variable [ $$stoploadCitation; Value:1 ]
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $$main ]
Perform Find [ ]
#
#Now find records referencing it.
Enter Find Mode [ ]
Set Field [ testlearn::kcreference; $$main ]
Extend Found Set [ ]
#
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
#
#Go to orignal record.
Loop
Exit Loop If [ testlearn::_Ltestlearn = $$main ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Stop the script.
Set Variable [ $$stoploadCitation ]
Set Variable [ $$findLearnLayout ]
Exit Script [ ]
#
#
Else If [ Filter ( testlearn::kcreference ; "L" ) ≠ "" ]
#If there are only records referenced by this record,
#then find these records in this next section.
#
#
End If
#
#
#Capture the current layout name to return
#user to it after find.
Set Variable [ $$findLearnLayout; Value:Get (LayoutName) ]
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Now find the record that the user was on
#when they clicked the 'find' button, and find
#the records that it references if there are any
#to find.
#
#Look thru the referenced learn records to
#create a value list of their keys. NOTE: This
#list will be used to find the final set of linked
#learn records including the original, so also
#caputre its key plus all the keys found in the
#portal of linked learn records.
Go to Layout [ “learn4EDIT” (testlearn) ]
Set Variable [ $findLinkedLearnRecords; Value:testlearn::_Ltestlearn ]
Loop
Go to Object [ Object Name: "ref2" ]
Exit Loop If [ Get (LastError) = 101 ]
Set Variable [ $findLinkedLearnRecords; Value:refTestLearn::_Ltestlearn & ¶ & $findLinkedLearnRecords ]
Go to Portal Row
[ Select; Next; Exit after last ]
End Loop
#
#Determine how many keys there are.
Set Variable [ $numberOfKeys; Value:ValueCount ($findLinkedLearnRecords ) ]
#
#Find 1st record.
Go to Layout [ $$findLearnLayout ]
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; GetValue ( $findLinkedLearnRecords ; $numberOfKeys ) ]
Perform Find [ ]
Set Variable [ $numberOfKeys; Value:$numberOfKeys - 1 ]
#
If [ $numberOfKeys ≠ 0 ]
#
#Loop thru each key to find next record in list until
#all linked records have been found.
Loop
#
#Exit the loop when there are no more keys to check.
Exit Loop If [ $numberOfKeys = 0 ]
#
#Find record.
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; GetValue ( $findLinkedLearnRecords ; $numberOfKeys ) ]
Extend Found Set [ ]
#
#Go the next key up from the bottom of the list
#of keys on this section's keychain.
Set Variable [ $numberOfKeys; Value:$numberOfKeys - 1 ]
End Loop
#
#Now find records referencing the original record
#if the user selected that option (button 1).
If [ $showReferencesReferencingMe ≠ "" ]
Enter Find Mode [ ]
Set Field [ testlearn::kcreference; $$main ]
Extend Found Set [ ]
End If
#
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
#
#Go to orignal record.
Loop
Exit Loop If [ testlearn::_Ltestlearn = $$main ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
End If
#
#Stop the script.
Set Variable [ $$stoploadCitation ]
Set Variable [ $$findLearnLayout ]
Exit Script [ ]
End If
#
End If
End If
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
Set Variable [ $$findLearnLayout; Value:Get (LayoutName) ]
Enter Find Mode [ ]
Go to Layout [ “learnFIND” (testlearn) ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
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
Perform Script [ “catchFindLearnErrorMessages (new)” ]
End If
#
#
#
#SECOND If there are no invalid find requests
#then perform the find.
If [ Get (WindowMode) = 1 ]
#
#Make sure to find only Learn records. Test
#discovery records are in the same table of
#records, but only Learn records have 'main'
#added to their FilterFind field when created.
Set Field [ testlearn::filterFind; "main" & ¶ ]
#
#Try to find the requested records.
Perform Find [ ]
#
#Get the error generated, which if successful
#will be zero.
Set Variable [ $error; Value:Get (LastError) ]
#
End If
#
#
#
#If the find was not successful...
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
Perform Script [ “findLearnRecord (update)” ]
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
#Replace user's last find requests so the can
#modify if they want to.
Set Field [ testlearn::note; $$note ]
Set Field [ testlearn::timestamp; $$timestamp ]
Set Field [ testlearn::brainstormCasePoint; $$brainstormCasePoint ]
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
Perform Script [ “findLearnRecord (update)” ]
#
#
#If they cancel the find ...
Else If [ Get ( LastMessageChoice ) = 1 ]
#
#Return to main layout and
#enter browse mode.
Perform Script [ “cancelLearnAndRefFind (update and name change)” ]
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
If [ $$findLearnLayout = "" ]
#
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnStuff3” (testlearn) ]
Else
Go to Layout [ “learn3” (testlearn) ]
End If
#
Else
Go to Layout [ $$findLearnLayout ]
Set Variable [ $$findLearnLayout ]
End If
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::note; ascending ]
[ Restore; No dialog ]
End If
Scroll Window
[ Home ]
Go to Record/Request/Page
[ First ]
#
#Clear user find request variables.
Set Variable [ $$note ]
Set Variable [ $$timestamp ]
Set Variable [ $$brainstormCasePoint ]
#
#Clear out all paused find scripts.
Halt Script
#
#
#!!! IMPORTANT !!! SAY WHAT !!! HERE YE, HERE YE !!!
#
#END identical find logic
#
