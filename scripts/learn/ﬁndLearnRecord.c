learn: findLearnRecord
#Capture errors and tell user about them in custom
#dialogue box.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#If the user clicks the find button and the system is already
#in find mode, capture the user's current find request
#and then perform the requested find.
#This capture is done in case nothing is found and the
#user is asked if they want to modify their request.
#The system puts in the captured request so that the
#user can see the failed request.
If [ Get (WindowMode) = 1 ]
Set Variable [ $caption; Value:testlearn::Caption ]
Set Variable [ $timestamp; Value:testlearn::timestamp ]
Perform Find [ ]
#
#If the system is not in find mode when the user
#clicks the find button do the following.
Else
#
#Check if the current Learn record references other
#Learn records.
If [ Filter ( testlearn::kcreference ; "L" ) ≠ "" ]
#
#If it does reference other Learn records, ask the user
#if they would like to find just those records, or
#continue to the find screen.
Show Custom Dialog [ Message: "Find all related (highlighted) LEARN records?" & ¶ & "OR" & ¶ & "Enter your own FIND request?"; Buttons: “find”, “learn”, “cancel” ]
#
#Cancel selection, cancels the script.
If [ Get ( LastMessageChoice ) = 3 ]
Exit Script [ ]
#
#If the users selects the "learn" button, then find just
#the referenced Learn records (in addition to the
#current Learn record).
Else If [ Get ( LastMessageChoice ) = 2 ]
#
Set Variable [ $$findLearnLayout; Value:Get (LayoutName) ]
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Look thru the referenced records to create a value
#list of their keys.
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
Sort Records [ Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Sort Records [ ]
[ No dialog ]
Go to Record/Request/Page
[ First ]
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
#
#
#If the system is not in find mode and the find button
#is clicked then capture the current layout name
#(to return user to it after find), enter find mode,
#go to the find layout, and await the user's find request.
Set Variable [ $$findLearnLayout; Value:Get (LayoutName) ]
Enter Find Mode [ ]
Go to Layout [ “learnFIND” (testlearn) ]
Show/Hide Status Area
[ Hide ]
Show/Hide Text Ruler
[ Hide ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Go to Field [ testlearn::Caption ]
Pause/Resume Script [ Indefinitely ]
Set Variable [ $caption; Value:testlearn::Caption ]
Set Variable [ $timestamp; Value:testlearn::timestamp ]
Perform Find [ ]
May 10, 平成27 11:50:03 Library.fp7 - findLearnRecord -1-
learn: findLearnRecord
End If
#
#If the find fails tell the user it failed and give them
#option to modify their request or cancel the find.
Loop
If [ Get (LastError) = 401 ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::Caption; $caption ]
Set Field [ testlearn::timestamp; $timestamp ]
Go to Field [ testlearn::Caption ]
Show Custom Dialog [ Message: "No records match this request."; Buttons: “cancel”, “modify find” ]
#
#If the user decides to modify their request then stay
#in find mode and await the users new request.
If [ Get ( LastMessageChoice ) = 2 ]
Pause/Resume Script [ Indefinitely ]
Set Variable [ $caption; Value:testlearn::Caption ]
Set Variable [ $timestamp; Value:testlearn::timestamp ]
#
#If the user decides to cancel their the find, then return
#to the main record window and show all records.
Else If [ Get ( LastMessageChoice ) = 1 ]
Go to Layout [ $$findLearnLayout ]
Show/Hide Status Area
[ Hide ]
Show/Hide Text Ruler
[ Hide ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Perform Find [ ]
Sort Records [ ]
[ No dialog ]
Go to Record/Request/Page
[ First ]
Set Variable [ $$findLearnLayout ]
Exit Script [ ]
End If
Perform Find [ ]
End If
#
#If the find is successful then show the user the found
#records on the main records layout.
Exit Loop If [ Get (LastError) = 0 ]
End Loop
Go to Layout [ $$findLearnLayout ]
Set Variable [ $$findLearnLayout ]
Sort Records [ ]
[ No dialog ]
Go to Record/Request/Page
[ First ]
May 10, 平成27 11:50:03 Library.fp7 - findLearnRecord -2-
