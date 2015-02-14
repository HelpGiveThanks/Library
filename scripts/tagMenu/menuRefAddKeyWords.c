tagMenu: menuRefAddKeyWords
#
#Ask user if OK to replace keywords.
Show Custom Dialog [ Message: "Add reference's keywords to current Learn record -- " &
//KEYWORDS
tagKeywordPrimary::tag & ", " &
reference::OtherKeyWords &
" -- ? (This will replace all keywords for this record, if there are any.)"; Buttons: “no”, “yes” ]
#
#Copy tag's keywords and go to Learn window and
#replace current record's keywords with them.
If [ Get ( LastMessageChoice ) = 2 ]
Set Variable [ $citekeywordOther; Value:reference::kkeywordOther ]
Set Variable [ $citekeywordOtherWords; Value:reference::OtherKeyWords ]
Set Variable [ $citekeywordPrimary; Value:reference::kkeywordPrimary ]
Select Window [ Name: "Learn"; Current file ]
Set Field [ testlearn::kKeywordPrimary; $citekeywordPrimary ]
Set Field [ testlearn::kcKeywordOther; $citekeywordOther ]
Set Field [ testlearn::OtherKeyWords; $citekeywordOtherWords ]
End If
#
#Return to Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
January 7, 平成26 16:05:16 Imagination Quality Management.fp7 - menuRefAddKeyWords -1-
