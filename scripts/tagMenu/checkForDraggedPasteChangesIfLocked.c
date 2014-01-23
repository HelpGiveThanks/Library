tagMenu: checkForDraggedPasteChangesIfLocked
#
#Used on test setup layouts to revert any locked ﬁelds
#back to the original text.
If [ //Test setup window
nodeLockTest::orderOrLock ≠ "" or nodeLockTestGroup::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "name" ]
Set Variable [ $lockedGroupName; Value:1 ]
Perform Script [ “insureEqualityOfSpellFields” ]
If [ nodeLockTest::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it -- " & nodeLockTest::tag & " -- and enter the password to unlock it."; Buttons: “OK” ]
Exit Script [ ]
End If
If [ $lockedGroupName = 1 ]
Show Custom Dialog [ Message: "This group name is locked. Go the node that created it -- " & nodeLockTestGroup::tag & " -- and enter the password to unlock it."; Buttons: “OK” ]
Exit Script [ ]
End If
Go to Field [ ]
Else If [ //Tag menus window
ruleTagMenuGroups::order ≠ "" and ruleTagMenuGroups::match = "health"
or
tagMenus::orderOrLock = "lock" ]
#
#If record is locked by system...
If [ ruleTagMenuGroups::order ≠ "" and ruleTagMenuGroups::match = "health" and Get ( ActiveFieldName ) = "name"
or
tagMenus::orderOrLock = "lock" ]
Show Custom Dialog [ Message: "Record is locked by the system. So you can look and copy text but any changes will be undone by the system."; Buttons: “OK” ]
Exit Script [ ]
End If
Else If [ //Tag menus window
nodeLockTestTagGroup::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "name" and $$citationMatch ≠ "path"
//or nodeLockTagMenus::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" and $$citationMatch = "health"
or nodeLockTagMenus::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" and $$citationMatch = "node"
or nodeLockTagMenus::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" and $$citationMatch = "copyist"
or nodeLockTagMenus::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" and $$citationMatch = "sample"
or nodeLockTagMenus::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" and $$citationMatch = "organ"
or nodeLockTagMenus::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" and $$citationMatch = "testItem"
or nodeLockTagMenus::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" and $$citationMatch = "key" ]
Set Variable [ $lockedGroupName; Value:1 ]
Perform Script [ “insureEqualityOfSpellFields” ]
If [ nodeLockTagMenus::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it -- " & nodeLockTagMenus::tag & " -- and enter the password to unlock it."; Buttons: “OK” ]
Exit Script [ ]
End If
If [ $lockedGroupName = 1 ]
Show Custom Dialog [ Message: "This group name is locked. Go the node that created it -- " & nodeLockTestTagGroup::tag & " -- and enter the password to unlock it."; Buttons: “OK” ]
Exit Script [ ]
End If
Go to Field [ ]
End If
January 7, 平成26 16:45:57 Imagination Quality Management.fp7 - checkForDraggedPasteChangesIfLocked -1-
