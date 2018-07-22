July 21, 2018 14:44:55 Library.fmp12 - menuReferenceFind -1-
tagMenu: menuFind: menuReferenceFind
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"ref" ]
#
#Set testlearn internal reference field conditional
#formatting to transparent.
Set Variable [ $$internal ]
#
#
#Goto correct layout.
If [ TEMP::InventoryLibraryYN = "" ]
#Idea Mode
#
#If no layout preference is set, then on iDevices
#go the layout with no pictures, and to the
#layout with pictures on desktop computers.
If [ TEMP::layoutLtagRFIND = "" ]
If [ Get (SystemPlatform) = 3 ]
Go to Layout [ “learnFindCiteS” (reference) ]
Set Field [ TEMP::layoutLtagRFIND; "more" & Get (LayoutName) ]
Else
Go to Layout [ “learnFindCite” (reference) ]
Set Field [ TEMP::layoutLtagRFIND; "less" & Get (LayoutName) ]
End If
Else
#
#Go the layout the user has selected.
Go to Layout [ Middle ( TEMP::layoutLtagRFIND ; 5 ; 42 ) ]
End If
#
Else
#Inventory Mode
#
#Go the location tag layout.
Go to Layout [ “learnFindStuffCite” (reference) ]
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
Enter Find Mode [ ]
Set Field [ tagInventoryLocation::match; "location" ]
Perform Find [ ]
#
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
