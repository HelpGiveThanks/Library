January 20, 2018 18:18:00 Library.fmp12 - checkActiveFieldForChangesAndTellUserIfItIsLocked -1-
tagMenu: checkActiveFieldForChangesAndTellUserIfItIsLocked
#
#
#Exit script if user is clicked V button to view a form.
If [ $$userClickedVButton ≠ "" ]
Exit Script [ ]
End If
#
#
#Used on test setup layouts to revert any locked fields
#back to the original text.
If [ //Test setup window
testSectionCreatorLock::orderOrLock ≠ "" or testSubsectionGroupNodeLock::orderOrLock ≠ "" and Get ( ActiveFieldName ) =
"name" ]
If [ Get ( ActiveFieldTableName ) = "testSubsectionGroup" ]
Set Variable [ $lockedGroupName; Value:1 ]
End If
#
#If locked, show the locked message
#one time per session.
If [ testSectionCreatorLock::orderOrLock ≠ "" ]
If [ $$stopShowingTestItemLockMessage ≠ 1 ]
Show Custom Dialog [ Message: "Changes made to records locked by the node — " & testSectionCreatorLock::tag & "
— like this one, will be reverted upon exiting. This message appears once per session. Restart library to see it
again."; Default Button: “OK”, Commit: “Yes” ]
Set Variable [ $$stopShowingTestItemLockMessage; Value:1 ]
End If
Exit Script [ ]
End If
#
If [ $lockedGroupName = 1 ]
Show Custom Dialog [ Message: "This group name is locked. Go the node that created it — " &
testSubsectionGroupNodeLock::tag & " — and enter the password to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
Else If [ //Tag menus window
tagMenuGroup::orderOrLibraryType ≠ "" and tagMenuGroup::match = "copyright"
or
tagMenus::orderOrLock = "lock" ]
#
#If record is locked by system...
If [ tagMenuGroup::orderOrLibraryType ≠ "" and tagMenuGroup::match = "copyright" and Get ( ActiveFieldName ) = "name"
or
tagMenus::orderOrLock = "lock" ]
Show Custom Dialog [ Message: "Record is locked by the system. So you can look and copy text but any changes will be
undone by the system."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
Else If [ //Tag menus window
nodeLockTestTagItemGroup::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "name" and $$citationMatch ≠ "path"
//or nodeLockTagMenus::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" and $$citationMatch = "copyright"
or tagCreatorLock::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" and $$citationMatch = "node"
or tagCreatorLock::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" and $$citationMatch = "publisher"
or tagCreatorLock::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" and $$citationMatch = "brainstorm"
or tagCreatorLock::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" and $$citationMatch = "publication"
or tagCreatorLock::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" and $$citationMatch = "testItem"
or tagCreatorLock::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" and $$citationMatch = "key" ]
Set Variable [ $lockedGroupName; Value:1 ]
#
#If locked, show the locked message
#one time per session.
If [ tagCreatorLock::orderOrLock ≠ "" ]
If [ $$stopShowingTestItemLockMessage ≠ 1 ]
Show Custom Dialog [ Message: "Changes made to records locked by the node — " & tagCreatorLock::tag & " like this
one, will be reverted upon exiting. This message appears once per session. Restart library to see it again. ";
Default Button: “OK”, Commit: “Yes” ]
Set Variable [ $$stopShowingTestItemLockMessage; Value:1 ]
End If
Exit Script [ ]
End If
#
If [ $lockedGroupName = 1 ]
Show Custom Dialog [ Message: "This group name is locked. Go the node that created it -- " &
nodeLockTestTagItemGroup::tag & " -- and enter the password to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
Go to Field [ ]
End If
Refresh Window
