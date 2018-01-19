January 18, 2018 14:45:33 Library.fmp12 - sortEditedStuffModeReference -1-
reference: sortEditedStuffModeReference
#
#If the user cannot change the order number,
#then do not re-sort the window.
If [ TEMP::InventoryLibraryYN ≠ "" ]
If [ refCreatorNode::orderOrLock ≠ "" ]
Exit Script [ ]
End If
End If
#
#If user elected to delete the order number
#then delete it.
If [ reference::publicationYearOrStuffOrderNumber = "delete number" ]
Set Field [ reference::publicationYearOrStuffOrderNumber; "" ]
End If
#
#Resort and go to edited record.
Scroll Window
[ End ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list:
“testPulldownListANDsortOrderList”
tagKeywordPrimary::tag; ascending
reference::publicationYearOrStuffOrderNumber; based on value list: “testPulldownListANDsortOrderList”
reference::Title; ascending
reference::thoughtsNotesEtc; ascending ]
[ Restore; No dialog ]
#
