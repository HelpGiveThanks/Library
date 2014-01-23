tagMenu: noCommasAllowed
If [ Filter ( tagMenus::tag ; "," ) = "," and $$citationMatch = "key" ]
Set Variable [ $tag; Value:tagMenus::tag ]
Show Custom Dialog [ Message: "commas prevent system from keeping track of this item"; Buttons: “OK” ]
Set Field [ tagMenus::tag; Substitute ( $tag ; "," ; "" ) ]
Else If [ Filter ( tagMenus::tag ; ";" ) = ";" and $$citationMatch = "node" ]
Set Variable [ $tag; Value:tagMenus::tag ]
Show Custom Dialog [ Message: "semicolons prevent system from keeping track of this item"; Buttons: “OK” ]
Set Field [ tagMenus::tag; Substitute ( $tag ; ";" ; "" ) ]
End If
If [ $$changeSpelling = 1 ]
Set Variable [ $$changeSpelling; Value:2 ]
Perform Script [ “changeSpellingOfKeywordOrNodeTag” ]
End If
January 7, 平成26 16:32:09 Imagination Quality Management.fp7 - noCommasAllowed -1-
