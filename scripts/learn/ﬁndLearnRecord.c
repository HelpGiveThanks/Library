learn: findLearnRecord
#Capture errors and tell user about them in custom
#dialogue box.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#If the user clicks the find button and the system is already
#in find mode, copy the user's current find request
#and then perform the requested find.
#If nothing is found the user is asked if they
#want to modify their copied request later in this script.
If [ Get (WindowMode) = 1 ]
Set Variable [ $caption; Value:testlearn::Caption ]
Set Variable [ $timestamp; Value:testlearn::timestamp ]
Perform Find [ ]
#
#
Else
#If the system is not in find mode when the user
#clicks the find button then do the following 2 things:
#
#1) Check if the current Learn record
#references other Learn records or is
#referenced by other Learn records.
If [ Filter ( testlearn::kcreference ; "L" ) ≠ "" or $$LinkedLearnRecords ≠ "" ]
#
#If it does reference other Learn records, ask the user
#if they would like to find just those records, or
#continue to the find screen.
Show Custom Dialog [ Message: "Find referenced records (purple highlight)?" & ¶ & "OR" & ¶ & "Find other?"; Buttons:
“other”, “purple”, “cancel” ]
#
#Exit script if user clicks cancel.
If [ Get ( LastMessageChoice ) = 3 ]
Exit Script [ ]
End If
#
If [ Get ( LastMessageChoice ) = 2 ]
#If the user wants to find just the referenced
#do 1 of 3 things:
#
#
#1.1) Determine if there are A) records it is referencing
#and B) records referencing it.
If [ Filter ( testlearn::kcreference ; "L" ) ≠ ""
and
$$LinkedLearnRecords ≠ "" ]
#
#If both are found ask user if they want to see
#A records or A and B records.
Show Custom Dialog [ Message: "Find referenced records only?" & ¶ & "OR" & ¶ & "Find referenced + records
referencing this record?"; Buttons: “Ref”, “Ref+”, “cancel” ]
#
#If button 2 is selected go to the next section
#after the End If below OR
#exit script if user clicks cancel (button 3).
If [ Get ( LastMessageChoice ) = 3 ]
Exit Script [ ]
End If
#
#
Else If [ $$LinkedLearnRecords ≠ "" ]
#1.2) If there are only records referencing this record,
#then find these records.
#
#Find original record first.
Set Variable [ $$stoploadCitation; Value:1 ]
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $$citation ]
Perform Find [ ]
#
#Now find records referencing it.
Enter Find Mode [ ]
Set Field [ testlearn::kcreference; $$citation ]
Extend Found Set [ ]
#
Sort Records [ Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
#
#Go to orignal record.
Loop
Exit Loop If [ testlearn::_Ltestlearn = $$citation ]
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
#1.3) If there are only records referenced by this record,
#then find these records in this next part of the script.
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
#Now find the original record and the records
#that it references if there are any to find.
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
#if the user selected that option (button 2).
If [ Get ( LastMessageChoice ) = 2 ]
Enter Find Mode [ ]
Set Field [ testlearn::kcreference; $$citation ]
Extend Found Set [ ]
End If
#
Sort Records [ Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
#
#Go to orignal record.
Loop
Exit Loop If [ testlearn::_Ltestlearn = $$citation ]
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
#
#
#2) If the system is not in find mode and the find button
#is clicked and there are no referenced records
#then capture the current layout name
#(to return user to it after find), enter find mode,
#go to the find layout, and await the user's find request.
Set Variable [ $$findLearnLayout; Value:Get (LayoutName) ]
#
Enter Find Mode [ ]
Go to Layout [ “learnFIND” (testlearn) ]
Show/Hide Status Area
[ Hide ]
Show/Hide Text Ruler
[ Hide ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Go to Field [ testlearn::Caption ]
Pause/Resume Script [ Indefinitely ]
#
Set Variable [ $caption; Value:testlearn::Caption ]
Set Variable [ $timestamp; Value:testlearn::timestamp ]
Perform Find [ ]
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
December 10, ଘ౮27 18:17:07 Library.fp7 - findLearnRecord -1-
