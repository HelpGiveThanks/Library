January 20, 2018 19:15:28 Library.fmp12 - menuLearnFind -1-
tagMenu: menuFind: menuLearnFind
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"learn" ]
#
#Set testlearn internal reference field conditional
#formatting to transparent.
Set Variable [ $$internal ]
#
#
#Go to correct layout.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnMenu4RefStuffCiteFindTL” (testlearn) ]
Else
Go to Layout [ “learnMenu4RefCiteFindTL” (testlearn) ]
End If
#
#
#Find learn records that can be referenced.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Field [ testlearn::brainstormCasePoint; "1" ]
Else
Set Field [ testlearn::filterFind; "main" ]
End If
Perform Find [ ]
#
#
#Sort records.
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list: “order
Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::concatenateSTUFFcontainer; ascending ]
[ Restore; No dialog ]
End If
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
#
