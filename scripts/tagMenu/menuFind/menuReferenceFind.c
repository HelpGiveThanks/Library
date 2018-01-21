January 20, 2018 19:14:40 Library.fmp12 - menuReferenceFind -1-
tagMenu: menuFind: menuReferenceFind
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"ref" ]
#
#Set testlearn internal reference field conditional
#formatting to transparent.
Set Variable [ $$internal ]
#
#Goto correct layout.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnFindCite” (reference) ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnFindStuffCite” (reference) ]
End If
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “learnFindCite” (reference) ]
End If
#
#
#Find References for the Learn module.
If [ TEMP::InventoryLibraryYN = "" ]
#
#If in idea mode then show only references user
#has selected to show in the Learn module.
Enter Find Mode [ ]
Set Field [ reference::showInLearn; "show in learn" ]
Perform Find [ ]
#
Else
#
#If in inventory mode then show all references
#(except the locked references).
Show All Records
#
#Omit locked records, which are the copyright
#images used by default copyright tags.
Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::lock: “lock” ]
[ Restore ]
End If
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
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list: “order
Pulldown List”
tagKeywordPrimary::tag; ascending
reference::publicationYearOrStuffOrderNumber; based on value list: “order Pulldown List”
reference::Title; ascending ]
[ Restore; No dialog ]
End If
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
