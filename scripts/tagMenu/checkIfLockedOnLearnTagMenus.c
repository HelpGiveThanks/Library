tagMenu: checkIfLockedOnLearnTagMenus
#
If [ $$citationMatch = "key"
//or $$citationMatch = "node"
or $$citationMatch = "health"
or $$citationMatch = "medium"
or $$citationMatch = "path" ]
Exit Script [ ]
End If
#Used on learn tag menus to keep user out of any
#locked fields.
If [ nodeLockTagMenus::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "tag" ]
Set Field [ tagMenus::tag; tagMenus::tagSpelling ]
Go to Field [ ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it -- " & nodeLockTagMenus::tag & " -- and enter the password to unlock it."; Buttons: “OK” ]
Exit Script [ ]
End If
If [ nodeLockTagGroup::orderOrLock ≠ "" and Get ( ActiveFieldName ) = "name" ]
// Set Variable [ $$stopChangeSpellingOfTagCategory; Value:1 ]
Set Field [ ruleTagMenuGroups::name; ruleTagMenuGroups::nameSpelling ]
Go to Field [ ]
Show Custom Dialog [ Message: "This group name is locked. Go the node that created it -- " & nodeLockTestTagGroup::tag & " -- and enter the password to unlock it."; Buttons: “OK” ]
Exit Script [ ]
End If
January 7, 平成26 16:18:02 Imagination Quality Management.fp7 - checkIfLockedOnLearnTagMenus -1-
