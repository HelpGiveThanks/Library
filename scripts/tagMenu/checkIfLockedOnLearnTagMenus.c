January 15, 2018 17:11:57 Library.fmp12 - checkIfLockedOnLearnTagMenus -1-
tagMenu: checkIfLockedOnLearnTagMenus
#
If [ $$stopLockCheck = 1
or $$citationMatch = "key"
//or $$citationMatch = "node"
or $$citationMatch = "copyright"
or $$citationMatch = "medium"
or $$citationMatch = "path" ]
Exit Script [ ]
End If
#Used on learn tag menus to keep user out of any
#locked fields.
If [ tagCreatorLock::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" ]
Set Field [ tagMenus::tag; tagMenus::tagSpelling ]
Go to Field [ ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it — " & tagCreatorLock::tag & " — and enter
the password to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
If [ nodeLockTagGroupCreatorLock::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "name" ]
// Set Variable [ $$stopChangeSpellingOfTagCategory; Value:1 ]
Set Field [ tagMenuGroup::name; tagMenuGroup::nameSpellingEXCEPTForTestItemGroup ]
Go to Field [ ]
Show Custom Dialog [ Message: "This group name is locked. Go the node that created it — " & nodeLockTestTagItemGroup::
tag & " — and enter the password to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
