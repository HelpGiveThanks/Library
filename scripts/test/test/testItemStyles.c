January 15, 2018 14:50:18 Library.fmp12 - testItemStyles -1-
test: test: testItemStyles
#
#
#If the node that created this group is locked
#prevent new items be created for it even by a
#node that is not locked.
If [ nodeLockTestTagItemGroup::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This group is locked. To format items, go the node that created this group — " &
nodeLockTestTagItemGroup::tag & " — in the setup tag window and enter the password."; Default Button: “OK”, Commit:
“Yes” ]
Exit Script [ ]
End If
#
#
#Apply style to text and note/flag style number.
If [ tagMenus::notesOrCopyright = "T"
 or
tagMenus::notesOrCopyright = "FT" ]
If [ tagMenus::textStyleOrCreatorNodeFlag = "" ]
Set Field [ tagMenus::textStyleOrCreatorNodeFlag; "1" ]
Set Field [ tagMenus::tag; Trim (tagMenus::tag) ]
Set Field [ tagMenus::tag; TextFont ( tagMenus::tag ; "Georgia" ) ]
Set Field [ tagMenus::tag; TextColor ( tagMenus::tag ; RGB ( 99 ; 99 ; 99 ) ) ]
Else If [ tagMenus::textStyleOrCreatorNodeFlag = "1" ]
Set Field [ tagMenus::textStyleOrCreatorNodeFlag; "2" ]
Set Field [ tagMenus::tag; Trim (tagMenus::tag) ]
Set Field [ tagMenus::tag; TextFont ( tagMenus::tag ; "Arial" ) ]
Set Field [ tagMenus::tag; TextColorRemove ( tagMenus::tag ; RGB ( 99 ; 99 ; 99 ) ) ]
Else If [ tagMenus::textStyleOrCreatorNodeFlag = "2" ]
Set Field [ tagMenus::textStyleOrCreatorNodeFlag; "3" ]
Set Field [ tagMenus::tag; Trim (tagMenus::tag) ]
Set Field [ tagMenus::tag; TextSize ( tagMenus::tag ; 20 ) ]
Set Field [ tagMenus::tag; TextFont ( tagMenus::tag ; "Arial" ) ]
Set Field [ tagMenus::tag; TextStyleAdd ( tagMenus::tag ; Bold ) ]
Set Field [ tagMenus::tag; TextColor ( tagMenus::tag ; RGB ( 99 ; 99 ; 99 ) ) ]
Else If [ tagMenus::textStyleOrCreatorNodeFlag = "3" ]
Set Field [ tagMenus::textStyleOrCreatorNodeFlag; "" ]
Set Field [ tagMenus::tag; Trim (tagMenus::tag) ]
Set Field [ tagMenus::tag; TextFontRemove ( tagMenus::tag ) ]
Set Field [ tagMenus::tag; TextSizeRemove ( tagMenus::tag ; 20 ) ]
Set Field [ tagMenus::tag; TextStyleRemove ( tagMenus::tag ; Bold ) ]
Set Field [ tagMenus::tag; TextColorRemove ( tagMenus::tag ; RGB ( 99 ; 99 ; 99 ) ) ]
Else
Set Field [ tagMenus::textStyleOrCreatorNodeFlag; "" ]
End If
Else
Show Custom Dialog [ Message: "Only text (T) and form (FT) items can be formatted as headers. To turn this item into a text
item, click on the check mark. (You may have to click it twice.)"; Default Button: “OK”, Commit: “Yes” ]
End If
#
