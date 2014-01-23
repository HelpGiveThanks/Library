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
#If the system is not in ﬁnd mode and the ﬁnd button
#is clicked then capture the current layout name
#(to return user to it after ﬁnd), enter ﬁnd mode,
#go to the ﬁnd layout, and await the user's ﬁnd request.
Else
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
January 7, 平成26 17:27:11 Imagination Quality Management.fp7 - ﬁndLearnRecord -1-
