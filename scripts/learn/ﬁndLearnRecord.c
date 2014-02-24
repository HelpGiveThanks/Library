learn: ﬁndLearnRecord
#Capture errors and tell user about them in custom
#dialogue box.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#If the user clicks the ﬁnd button and the system is already
#in ﬁnd mode, capture the user's current ﬁnd request
#and then perform the requested ﬁnd.
#This capture is done in case nothing is found and the
#user is asked if they want to modify their request.
#The system puts in the captured request so that the
#user can see the failed request.
If [ Get (WindowMode) = 1 ]
Set Variable [ $caption; Value:testlearn::Caption ]
Set Variable [ $timestamp; Value:testlearn::timestamp ]
Perform Find [ ]
#
#If the system is not in ﬁnd mode when the user
#clicks the ﬁnd button do the following.
Else
#
#Check if the current Learn record references other
#Learn records.
If [ Filter ( testlearn::kcreference ; "L" ) ≠ "" ]
#
#If it does reference other Learn records, ask the user
#if they would like to ﬁnd just those records, or
#continue to the ﬁnd screen.
Show Custom Dialog [ Message: "Find all related (highlighted) LEARN records?" & ¶ & "OR" & ¶ & "Enter your own FIND request?"; Buttons: “ﬁnd”, “learn”, “cancel” ]
#
#Cancel selection, cancels the script.
If [ Get ( LastMessageChoice ) = 3 ]
Exit Script [ ]
#
#If the users selects the "learn" button, then ﬁnd just
#the referenced Learn records (in addition to the
#current Learn record).
Else If [ Get ( LastMessageChoice ) = 2 ]
#
Set Variable [ $$ﬁndLearnLayout; Value:Get (LayoutName) ]
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Look thru the referenced records to create a value
#list of their keys.
Go to Layout [ “learn4EDIT” (testlearn) ]
Set Variable [ $ﬁndLinkedLearnRecords; Value:testlearn::_Ltestlearn ]
Loop
Go to Object [ Object Name: "ref2" ]
Exit Loop If [ Get (LastError) = 101 ]
Set Variable [ $ﬁndLinkedLearnRecords; Value:refTestLearn::_Ltestlearn & ¶ & $ﬁndLinkedLearnRecords ]
Go to Portal Row
[ Select; Next; Exit after last ]
End Loop
#
#Determine how many keys there are.
Set Variable [ $numberOfKeys; Value:ValueCount ($ﬁndLinkedLearnRecords ) ]
#
#Find 1st record.
Go to Layout [ $$ﬁndLearnLayout ]
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; GetValue ( $ﬁndLinkedLearnRecords ; $numberOfKeys ) ]
Perform Find [ ]
Set Variable [ $numberOfKeys; Value:$numberOfKeys - 1 ]
#
If [ $numberOfKeys ≠ 0 ]
#
#Loop thru each key to ﬁnd next record in list until
#all linked records have been found.
Loop
#
#Exit the loop when there are no more keys to check.
Exit Loop If [ $numberOfKeys = 0 ]
#
#Find record.
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; GetValue ( $ﬁndLinkedLearnRecords ; $numberOfKeys ) ]
Extend Found Set [ ]
#
#Go the next key up from the bottom of the list
#of keys on this section's keychain.
Set Variable [ $numberOfKeys; Value:$numberOfKeys - 1 ]
End Loop
#
Sort Records [ Speciﬁed Sort Order: testlearn::date; descending
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
Set Variable [ $$ﬁndLearnLayout ]
Exit Script [ ]
End If
#
End If
#
#
#If the system is not in ﬁnd mode and the ﬁnd button
#is clicked then capture the current layout name
#(to return user to it after ﬁnd), enter ﬁnd mode,
#go to the ﬁnd layout, and await the user's ﬁnd request.
Set Variable [ $$ﬁndLearnLayout; Value:Get (LayoutName) ]
Enter Find Mode [ ]
Go to Layout [ “learnFIND” (testlearn) ]
Show/Hide Status Area
[ Hide ]
Show/Hide Text Ruler
[ Hide ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Go to Field [ testlearn::Caption ]
Pause/Resume Script [ Indeﬁnitely ]
Set Variable [ $caption; Value:testlearn::Caption ]
Set Variable [ $timestamp; Value:testlearn::timestamp ]
Perform Find [ ]
February 24, 平成26 10:31:20 Imagination Quality Management.fp7 - ﬁndLearnRecord -1-learn: ﬁndLearnRecord
End If
#
#If the ﬁnd fails tell the user it failed and give them
#option to modify their request or cancel the ﬁnd.
Loop
If [ Get (LastError) = 401 ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::Caption; $caption ]
Set Field [ testlearn::timestamp; $timestamp ]
Go to Field [ testlearn::Caption ]
Show Custom Dialog [ Message: "No records match this request."; Buttons: “cancel”, “modify ﬁnd” ]
#
#If the user decides to modify their request then stay
#in ﬁnd mode and await the users new request.
If [ Get ( LastMessageChoice ) = 2 ]
Pause/Resume Script [ Indeﬁnitely ]
Set Variable [ $caption; Value:testlearn::Caption ]
Set Variable [ $timestamp; Value:testlearn::timestamp ]
#
#If the user decides to cancel their the ﬁnd, then return
#to the main record window and show all records.
Else If [ Get ( LastMessageChoice ) = 1 ]
Go to Layout [ $$ﬁndLearnLayout ]
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
Set Variable [ $$ﬁndLearnLayout ]
Exit Script [ ]
End If
Perform Find [ ]
End If
#
#If the ﬁnd is successful then show the user the found
#records on the main records layout.
Exit Loop If [ Get (LastError) = 0 ]
End Loop
Go to Layout [ $$ﬁndLearnLayout ]
Set Variable [ $$ﬁndLearnLayout ]
Sort Records [ ]
[ No dialog ]
Go to Record/Request/Page
[ First ]
February 24, 平成26 10:31:20 Imagination Quality Management.fp7 - ﬁndLearnRecord -2-