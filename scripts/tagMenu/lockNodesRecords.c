January 20, 2018 18:21:20 Library.fmp12 - lockNodesRecords -1-
tagMenu: lockNodesRecords
#
#
#Capture the password for comparrison and to return
#the password field back to if the user fails to get the
#password right.
Set Variable [ $password; Value:tagMenus::orderOrLock[2] ]
Set Variable [ $tagKey; Value:tagMenus::_Ltag ]
Set Field [ TEMP::passwordCheck; "" ]
Go to Field [ ]
#
#Use the halt instead of exit script step as the
#user can sometimes click the lock button
#twice. The halt stops the second click's
#calling up of this script.
#
#If there is a password, ask user to enter it.
If [ tagMenus::orderOrLock[2] ≠ "" ]
Loop
Show Custom Dialog [ Message: "Enter the password to unlock " & tagMenus::tag & " records."; Default Button: “enter”,
Commit: “Yes”; Button 2: “cancel”, Commit: “No”; Input #1: TEMP::passwordCheck, Password ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ TEMP::passwordCheck; "" ]
Halt Script
End If
#
#Unlock node if password is correct.
If [ $password = TEMP::passwordCheck ]
Show Custom Dialog [ Message: "unlocked"; Default Button: “OK”, Commit: “Yes” ]
Set Field [ TEMP::passwordCheck; "" ]
Set Field [ tagMenus::orderOrLock; "" ]
Set Field [ tagMenus::orderOrLock[2]; "" ]
#
#Allow creation of new records by this node if
#it is the primary default node.
If [ tagMenus::_Ltag = TEMP::kdefaultNodePrimary ]
Set Field [ tempSetup::primaryNodeIsLocked; "" ]
End If
#
#Allow new records to be created by the
#primary node if it was created by this node.
If [ tagMenus::_Ltag = TEMP::kdefaultNodePrimaryCreator ]
Set Field [ tempSetup::primaryNodesCreatorNodeIsLocked; "" ]
End If
#
#Allow new records to be created for this
#node if it is the default test subject.
If [ tagMenus::_Ltag = TEMP::kdefaultNodeTestSubject ]
Set Variable [ $$testSubjectIsLocked ]
Set Field [ tempSetup::testSubjectNodeIsLocked; "" ]
End If
#
#
#Check if node created a setup reference
#record, and if so and if locked, let user
#know this unlocking will not affect this
#setup reference.
#
#Prevent tagLoad script from running and
#open a new window to go to the setup
#reference table layout.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize:
“Yes” ]
Go to Layout [ “tableSetupReference” (librarySetupReferenceMain) ]
#
#Find any records created by this node.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ librarySetupReferenceMain::kcreatorNode; $tagKey ]
Set Field [ librarySetupReferenceMain::password; 0 ]
Perform Find [ ]
#
#If there are locked setup references, tell the
#user that they the must be locked separately.
If [ librarySetupReferenceMain::password ≠ "" ]
Set Variable [ $setupReference; Value:Case ( Length ( librarySetupReferenceMain::name & " by " &
librarySetupReferenceMain::creatorName ) < 56 ;
 Left ( librarySetupReferenceMain::name & " by " & librarySetupReferenceMain::creatorName ; 55 )
& "...." ;
 librarySetupReferenceMain::name & " by " & librarySetupReferenceMain::creatorName & "." ) ]
Set Variable [ $foundCount; Value:Get (FoundCount) ]
Close Window [ Current Window ]
If [ $foundCount = 1 ]
Show Custom Dialog [ Message: "NOTE: Setup references must locked separately. The following setup
reference created by this node remains locked until you unlock it in the Setup window: " &
$setupReference; Default Button: “OK”, Commit: “Yes” ]
Else If [ $foundCount = 2 ]
Show Custom Dialog [ Message: "NOTE: Setup references must locked separately. The following setup
reference, and 1 other, created by this node remain locked until you unlock them in the Setup window: " &
$setupReference; Default Button: “OK”, Commit: “Yes” ]
Else If [ $foundCount > 2 ]
Show Custom Dialog [ Message: "NOTE: Setup references must locked separately. The following setup
reference, and " & $foundCount & " others, created by this node remain locked until you unlock them in
the Setup window: " & $setupReference; Default Button: “OK”, Commit: “Yes” ]
End If
Else
Close Window [ Current Window ]
End If
Set Variable [ $$stopLoadTagRecord ]
#
#
Halt Script
End If
End Loop
#
#If there is no password, ask user to create one.
Else If [ tagMenus::orderOrLock[2] = "" ]
Set Field [ TEMP::passwordCheck; "" ]
Show Custom Dialog [ Message: "Enter a password to lock " & tagMenus::tag & "'s records. WARNING: If you can't remember
this password, your records will remain locked."; Default Button: “enter”, Commit: “Yes”; Button 2: “cancel”, Commit: “No”;
Input #1: tagMenus::orderOrLock, Password, "password"; Input #2: TEMP::passwordCheck, Password, "confirm password" ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ tagMenus::orderOrLock; "" ]
Exit Script [ ]
End If
#
#Check validity of password entered.
#
#If they don't match, ask user to try again.
Loop
If [ tagMenus::orderOrLock ≠ TEMP::passwordCheck ]
Show Custom Dialog [ Message: "Passwords did not match."; Default Button: “enter”, Commit: “Yes”; Button 2:
“cancel”, Commit: “No”; Input #1: tagMenus::orderOrLock, Password, "password"; Input #2: TEMP::
passwordCheck, Password, "confirm password" ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ tagMenus::orderOrLock; "" ]
Halt Script
End If
End If
#
#If the user picks 0, then make them choose
#another and explain why the must do so.
If [ TEMP::passwordCheck = 0 ]
Show Custom Dialog [ Message: "Zero is not allowed. Try again."; Default Button: “enter”, Commit: “Yes”; Button 2:
“cancel”, Commit: “No”; Input #1: tagMenus::orderOrLock, Password, "password"; Input #2: TEMP::
passwordCheck, Password, "confirm password" ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ tagMenus::orderOrLock; "" ]
Halt Script
End If
End If
#
#If the password is valid exit the
#password check loop.
Exit Loop If [ tagMenus::orderOrLock = TEMP::passwordCheck and TEMP::passwordCheck ≠ 0 ]
End Loop
#
#Move the user entered password into the
#second field, and replace it with 0, which will
#tell the system that this node is locked, but
#will not reveal to any user what the actual
#password is, as the second field appears on
#zero layouts.
Set Field [ tagMenus::orderOrLock[2]; TEMP::passwordCheck ]
If [ TEMP::passwordCheck ≠ "" ]
Set Field [ tagMenus::orderOrLock; 0 ]
End If
#
#Prevent creation of new records by this node
#if it is the primary default node.
If [ tagMenus::_Ltag = TEMP::kdefaultNodePrimary ]
Set Field [ tempSetup::primaryNodeIsLocked; 0 ]
End If
#
#Prevent new records being created by the
#primary node if it was created by this node.
If [ tagMenus::_Ltag = TEMP::kdefaultNodePrimaryCreator ]
Set Field [ tempSetup::primaryNodesCreatorNodeIsLocked; tagMenus::tag ]
End If
#
#Prevent new records being created by the
#node if it is the default test subject.
If [ tagMenus::_Ltag = TEMP::kdefaultNodeTestSubject ]
Set Variable [ $$testSubjectIsLocked; Value:tagMenus::tag ]
Set Field [ tempSetup::testSubjectNodeIsLocked; 1 ]
End If
#
#Turn on show locked records if the box is
#not already checked.
Set Field [ tempSetup::nodeLockedShow; "1" ]
#
#
#Check if node created a setup reference
#record, and if so and if locked, let user
#know this unlocking will not affect this
#setup reference.
#
#Prevent tagLoad script from running and
#open a new window to go to the setup
#reference table layout.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “tableSetupReference” (librarySetupReferenceMain) ]
#
#Find any records created by this node.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ librarySetupReferenceMain::kcreatorNode; $tagKey ]
Set Field [ librarySetupReferenceMain::password; "=" ]
Perform Find [ ]
#
#
#If there are any unlocked, tell the user that
#they the must be locked separately.
If [ librarySetupReferenceMain::password = "" ]
Set Variable [ $setupReference; Value:Case ( Length ( librarySetupReferenceMain::name & " by " &
librarySetupReferenceMain::creatorName ) < 56 ;
 Left ( librarySetupReferenceMain::name & " by " & librarySetupReferenceMain::creatorName ; 55 ) & "... |" ;
 librarySetupReferenceMain::name & " by " & librarySetupReferenceMain::creatorName & " |" ) ]
Set Variable [ $foundCount; Value:Get (FoundCount) ]
Close Window [ Current Window ]
If [ $foundCount = 1 ]
Show Custom Dialog [ Message: "NOTE: Setup references must locked separately. The following setup reference
created by this node remain unlocked in the Setup window: " & $setupReference; Default Button: “OK”, Commit:
“Yes” ]
Else If [ $foundCount = 2 ]
Show Custom Dialog [ Message: "NOTE: Setup references must locked separately. The following setup reference,
and 1 other, created by this node remain unlocked in the Setup window: " & $setupReference; Default Button: “OK”,
Commit: “Yes” ]
Else If [ $foundCount > 2 ]
Show Custom Dialog [ Message: "NOTE: Setup references must locked separately. The following setup reference,
and " & $foundCount & " others, created by this node remain unlocked in the Setup window: " & $setupReference;
Default Button: “OK”, Commit: “Yes” ]
End If
Else
Close Window [ Current Window ]
End If
Set Variable [ $$stopLoadTagRecord ]
#
#
End If
Halt Script
#
#
