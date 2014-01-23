reference(citation): RemoveTextFormattingAndCommas
Commit Records/Requests
Set Field [ tagMenus::tag; TextFontRemove ( tagMenus::tag ) ]
Set Field [ tagMenus::tag; TextFormatRemove ( tagMenus::tag ) ]
Set Field [ tagMenus::tag; TextSizeRemove ( tagMenus::tag ) ]
Set Variable [ $tag; Value:tagMenus::tag ]
If [ Filter ( tagMenus::tag ; "," ) = "," and $$citationMatch = "key" ]
Show Custom Dialog [ Message: "commas prevent system from keeping track of this item and have been removed"; Buttons: “OK” ]
Set Field [ tagMenus::tag; Substitute ( $tag ; "," ; "" ) ]
Else If [ Filter ( tagMenus::tag ; ";" ) = ";" and $$citationMatch = "node" ]
Show Custom Dialog [ Message: "semicolons prevent system from keeping track of this item and have been removed"; Buttons: “OK” ]
Set Field [ tagMenus::tag; Substitute ( $tag ; ";" ; "" ) ]
End If
Set Field [ tagMenus::tag; Trim ( tagMenus::tag ) ]
If [ $$citationmatch = "health"
 or
$$citationmatch = "sample" ]
Perform Script [ “insureEqualityOfSpellFields” ]
End If
January 7, 平成26 17:55:06 Imagination Quality Management.fp7 - RemoveTextFormattingAndCommas -1-
