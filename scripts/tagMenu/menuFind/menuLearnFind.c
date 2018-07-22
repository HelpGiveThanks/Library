July 21, 2018 14:44:30 Library.fmp12 - menuLearnFind -1-
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
#Go to layout with no pictures.
Go to Layout [ “learnMenu4NoPicRefCiteFindTL” (testlearn) ]
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
#Go to correct layout.
If [ TEMP::InventoryLibraryYN = "" ]
#Idea Mode
#
If [ TEMP::layoutLtagLFIND = "" ]
#If no layout preference is set, then on iDevices
#go the layout with no pictures, and to the
#layout with pictures on desktop computers.
If [ Get (SystemPlatform) = 3 ]
Go to Layout [ “learnMenu4NoPicRefCiteFindTL” (testlearn) ]
Set Field [ TEMP::layoutLtagLFIND; "more" & Get (LayoutName) ]
Else
Go to Layout [ “learnMenu4RefCiteFindTL” (testlearn) ]
Set Field [ TEMP::layoutLtagLFIND; "less" & Get (LayoutName) ]
End If
Else
#
#Go the layout the user has selected.
Go to Layout [ Middle ( TEMP::layoutLtagLFIND ; 5 ; 42 ) ]
End If
#
Else
#Inventory Mode
#
#Go the layout the user has selected.
Go to Layout [ “learnMenu4RefStuffCiteFindTL” (testlearn) ]
End If
#
#Sort records.
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
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
