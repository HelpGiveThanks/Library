January 18, 2018 15:57:46 Library.fmp12 - stopNewRecordsBeingCreatedByLockedNode -1-
sharedLayoutScripts: stopNewRecordsBeingCreatedByLockedNode
#
#
#Scripts that use this script —
#duplicateLearnRecord,
#duplicateReferenceRecord,
#duplicateSectionFromTemplate,
#duplicateBrainstorm, itemNA, newLearn,
#learnOpenTextNewWindow,
#newReference, newRowOfPhotos, newSection,
#newSectionFromTemplate, newTag,
#newTagMenuTag. newTagMenuTagGroup,
#newTest, newTestGroup, newTestItem,
#newTestItemGroup, newTestResult,
#newTestSection, newTestSubsection,
#reportNewTestResult.
#CHECK THE DDR! To get the most uptodate
#list of scripts currently using this one!
#
#
#If the PRIMARY node is currenlty locked then
#stop ALL scripts, and inform the user.
#(By ALL scripts, I mean the script that used this
#one to see if running it was OK.)
If [ TEMP::primaryNodeIsLocked ≠ "" ]
If [ Left ( Get (LayoutName) ; 11 ) = "defaultNode" ]
Show Custom Dialog [ Message: "The default primary node — " & TEMP::DEFAULTNodePrimaryName & " — is locked. A)
Click 'lock' to unlock it, B) select an unlocked node for the primary node, or C) create a new primary node."; Default
Button: “OK”, Commit: “Yes”; Button 2: “new primary”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "The default primary node — " & TEMP::DEFAULTNodePrimaryName & " — is locked.
Go to the Default Node Tag Menu and A) click 'lock' to unlock it, B) select an unlocked node for the primary node, or C)
create a new primary node."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#If the user decides to create a new primary
#record then proceed to do so.
If [ Get (LastMessageChoice) = 2 ]
Show Custom Dialog [ Message: "A new node to assign to yourself will now be created, allowing you to make new records,
tags, etc. If you lock it, all its creations will also be locked."; Default Button: “OK”, Commit: “Yes”; Button 2: “Cancel”,
Commit: “No” ]
If [ Get (LastMessageChoice) = 2 ]
Halt Script
End If
#
#This variable tells the create new node script to
#create a new user node, which is a node that is
#its own creator, and thus can only be locked
#directly, versus locked by also locking its creator.
Set Variable [ $$createNewPrimary; Value:1 ]
#
#If user doesn't elect to create a new user node,
#then halt the script.
Else
Halt Script
End If
#
#If the primary node's CREATOR node is
#currenlty locked then stop ALL scripts, and
#inform the user.
#(By ALL scripts, I mean the script that used this
#one to see if running it was OK.)
Else If [ TEMP::primaryNodesCreatorNodeIsLocked ≠ "" ]
If [ Left ( Get (LayoutName) ; 11 ) = "defaultNode" ]
Show Custom Dialog [ Message: "The creator — " & TEMP::primaryNodesCreatorNodeIsLocked & " — of the default
primary node — " & TEMP::DEFAULTNodePrimaryName & " — is locked. A) Click 'lock' to unlock it, B) select an
unlocked node for the primary node, or C) create a new primary node."; Default Button: “OK”, Commit: “Yes”; Button 2:
“new primary”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "The creator — " & TEMP::primaryNodesCreatorNodeIsLocked & " — of the default
primary node — " & TEMP::DEFAULTNodePrimaryName & " — is locked. Go to the Default Node Tag Menu and A)
click 'lock' to unlock it, B) select an unlocked node for the primary node, or C) create a new primary node."; Default
Button: “OK”, Commit: “Yes” ]
End If
#
#If the user decides to create a new primary
#record then proceed to do so.
If [ Get (LastMessageChoice) = 2 ]
Show Custom Dialog [ Message: "A new node to assign to yourself will now be created, allowing you to make new records,
tags, etc. If you lock it, all its creations will also be locked."; Default Button: “OK”, Commit: “No”; Button 2: “Cancel”,
Commit: “No” ]
If [ Get (LastMessageChoice) = 2 ]
Halt Script
End If
#
#This variable tells the create new node script to
#create a new user node, which is a node that is
#its own creator, and thus can only be locked
#directly, versus locked by also locking its creator.
Set Variable [ $$createNewPrimary; Value:1 ]
#
#If user doesn't elect to create a new user node,
#then halt the script.
Else
Halt Script
End If
#
#If the TEST SUBJECT node is locked then stop
#ALL scripts, and inform the user.
#(By ALL scripts, I mean the script that used this
#one to see if running it was OK.)
Else If [ testSubsectionTestSubjectLock::orderOrLock = "0"
 or
ReportResultTestSubject::orderOrLock ≠ ""
 or
reportTestSubjectLock::orderOrLock = "0"
 or
TEMP::testSubjectNodeIsLocked ≠ "" and Left ( Get ( LayoutName ) ; 7 ) = "default" and Get ( LayoutName ) ≠ "defaultTest" and
Get ( LayoutName ) ≠ "defaultSetup" ]
#
#Get the current test subject's name.
Set Variable [ $testSubjectName; Value:Case ( testSubsectionTestSubjectLock::orderOrLock = "0" ;
testSubsectionTestSubjectLock::tag ;
ReportResultTestSubject::orderOrLock ≠ "" ; ReportResultTestSubject::tag ;
reportTestSubjectLock::orderOrLock = "0" ; reportTestSubjectLock::tag ;
TEMP::testSubjectNodeIsLocked ≠ "" ; TEMP::DEFAULTNodeTestSubjectName ) ]
#
#If the script that used this script was started
#by the user on a different layout or window,
#return to it before informing the user about
#the locked status of the test subject.
If [ Get (LayoutName) = "testResult" ]
Perform Script [ “returnToSubsections (update and name change returnToStep3)” ]
Else If [ $$checkORaddTestItem = 1 and Get ( WindowName ) = "Test"
 or
$$checkORaddTestItem = 1 and Get ( WindowName ) = "Report" ]
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$checkORaddTestItem ]
End If
Show Custom Dialog [ Message: "The test subject — " & $testSubjectName & " — is locked. To unlock, A) go back to the setup
node tag menu. B) Select this test subject. C) Click 'lock' and enter the password."; Default Button: “OK”, Commit: “Yes” ]
#
Halt Script
#
#If the LEARN record's node is locked then stop
#ALL scripts, and inform the user.
#(By ALL scripts, I mean the script that used this
#one to see if running it was OK.)
Else If [ tagTLNodePrimary::orderOrLock = "0"
 or
tagTLReportNodePrimary::orderOrLock = "0" ]
#
#Figure out what layout the user is on to
#retrieve the correct user name to show.
If [ tagTLNodePrimary::orderOrLock = "0" ]
Show Custom Dialog [ Message: "This Learn record's creator — " & tagTLNodePrimary::tag & " — is locked. To unlock, A)
go back to the setup node tag menu. B) Select this test subject. C) Click 'lock' and enter the password."; Default Button:
“OK”, Commit: “Yes” ]
Else If [ tagTLReportNodePrimary::orderOrLock = "0" ]
Show Custom Dialog [ Message: "This Learn record's creator — " & tagTLReportNodePrimary::tag & " — is locked. To
unlock, A) go back to the setup node tag menu. B) Select this test subject. C) Click 'lock' and enter the password.";
Default Button: “OK”, Commit: “Yes” ]
End If
#
Halt Script
End If
#
#
