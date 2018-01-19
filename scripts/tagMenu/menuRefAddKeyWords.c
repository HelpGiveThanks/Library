January 15, 2018 16:47:03 Library.fmp12 - addRefsKeywordsToMainRecord -1-
tagMenu: addRefsKeywordsToMainRecord
#
#Ask user if OK to replace keywords.
Show Custom Dialog [ Message: "Add reference's keywords to current Learn record — " &
//KEYWORDS
tagKeywordPrimary::tag & ", " &
reference::OtherKeyWords &
" — ? (This will replace all keywords for this record, if there are any.)"; Default Button: “no”, Commit: “Yes”; Button 2: “yes”,
Commit: “No” ]
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
