January 18, 2018 16:07:16 Library.fmp12 - closeWindow -1-
sharedLayoutScripts: closeWindow
#
#
#In copyright tag review window, check
#changes to any locked group names.
If [ $$citationMatch = "copyright" ]
Perform Script [ “checkTagGroupNamesEXCEPTtestItemGroups (update)” ]
End If
#
#
#Close window and clear unneeded variables.
Show/Hide Text Ruler
[ Hide ]
Close Window [ Current Window ]
Set Variable [ $$PictureOnReportLayout ]
Set Variable [ $$userInCopyrightWindow ]
Set Variable [ $$showCopyrightLockMessage ]
#
#Scroll window to selected record if
#it has been changed in a stuff/inventory
#library.
If [ TEMP::InventoryLibraryYN ≠ "" and Get (WindowName) = "Tag Menus" ]
If [ reference::Title[1] ≠ reference::Title[2]
 or
reference::thoughtsNotesEtc[1] ≠ reference::thoughtsNotesEtc[2]
 or
reference::publicationYearOrStuffOrderNumber[1] ≠ reference::publicationYearOrStuffOrderNumber[2]
 or
reference::kkeywordPrimary ≠ $$locationKeyword ]
Scroll Window
[ End ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list:
“order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::publicationYearOrStuffOrderNumber; based on value list: “order Pulldown List”
reference::Title; ascending ]
[ Restore; No dialog ]
Set Variable [ $$locationKeyword ]
End If
End If
#
