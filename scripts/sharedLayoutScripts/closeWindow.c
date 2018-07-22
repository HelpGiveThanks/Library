July 21, 2018 12:41:56 Library.fmp12 - closeWindow -1-
sharedLayoutScripts: closeWindow
#
#
#In copyright tag review window, check
#changes to any locked group names.
If [ $$citationMatch = "copyright" ]
Perform Script [ “checkTagGroupNamesEXCEPTtestItemGroups” ]
End If
#
#
#Close window and clear unneeded variables.
Show/Hide Text Ruler
[ Hide ]
Set Variable [ $mediaWindowName; Value:Case ( Get ( WindowName ) = "Media" ; 1 ; "" ) ]
Close Window [ Current Window ]
Set Variable [ $$PictureOnReportLayout ]
Set Variable [ $$userInCopyrightWindow ]
Set Variable [ $$showCopyrightLockMessage ]
#
#Scroll window to selected record if
#it has been changed in a stuff/inventory
#library.
If [ $$copyNoteForSortCheck ≠ testlearn::note ]
If [ TEMP::InventoryLibraryYN ≠ "" and Get (WindowName) = "Tag Menus"
 or
TEMP::InventoryLibraryYN ≠ "" and Get (WindowName) = "Learn" ]
If [ reference::Title[1] ≠ reference::Title[2]
 or
reference::thoughtsNotesEtc[1] ≠ reference::thoughtsNotesEtc[2]
 or
reference::publicationYearOrStuffOrderNumber[1] ≠ reference::publicationYearOrStuffOrderNumber[2]
 or
reference::kkeywordPrimary ≠ $$locationKeyword ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value
list: “order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::publicationYearOrStuffOrderNumber; based on value list: “order Pulldown List”
reference::Title; ascending ]
[ Restore; No dialog ]
Set Variable [ $$locationKeyword ]
End If
If [ Get (WindowName) = "Learn" and $mediaWindowName ≠ 1 and Get ( LayoutName ) ≠ "learn4EDITstuff" ]
Scroll Window
[ End ]
Sort Records [ ]
[ No dialog ]
End If
End If
Set Variable [ $$copyNoteForSortCheck ]
End If
#
