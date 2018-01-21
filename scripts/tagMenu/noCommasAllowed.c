January 21, 2018 11:50:07 Library.fmp12 - noCommasAllowed -1-
tagMenu: noCommasAllowed
If [ Filter ( tagMenus::tag ; "," ) = "," and $$citationMatch = "key" ]
Set Variable [ $tag; Value:tagMenus::tag ]
Show Custom Dialog [ Message: "commas prevent system from keeping track of this item"; Default Button: “OK”, Commit: “Yes” ]
Set Field [ tagMenus::tag; Substitute ( $tag ; "," ; "" ) ]
Else If [ Filter ( tagMenus::tag ; ";" ) = ";" and $$citationMatch = "node" ]
Set Variable [ $tag; Value:tagMenus::tag ]
Show Custom Dialog [ Message: "semicolons prevent system from keeping track of this item"; Default Button: “OK”, Commit:
“Yes” ]
Set Field [ tagMenus::tag; Substitute ( $tag ; ";" ; "" ) ]
End If
If [ $$changeSpelling = 1 ]
Set Variable [ $$changeSpelling; Value:2 ]
Perform Script [ “checkKeyANDNodeTagNames” ]
End If
