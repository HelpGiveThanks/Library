July 21, 2018 14:44:15 Library.fmp12 - menuCitationFind -1-
tagMenu: menuFind: menuCitationFind
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"cite" ]
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Freeze Window
#
#Set testlearn internal reference field conditional
#formatting to transparent.
Set Variable [ $$internal ]
#
#
#If no layout preference is set, then on iDevices
#go the layout with no pictures, and to the
#layout with pictures on desktop computers.
If [ TEMP::layoutRtagCiteFIND = "" ]
If [ Get (SystemPlatform) = 3 ]
Go to Layout [ “ReferenceMenu3CiteFindS” (reference) ]
Set Field [ TEMP::layoutRtagCiteFIND; "more" & Get (LayoutName) ]
Else
Go to Layout [ “ReferenceMenu3CiteFind” (reference) ]
Set Field [ TEMP::layoutRtagCiteFIND; "less" & Get (LayoutName) ]
End If
Else
#
#Go the layout the user has selected.
Go to Layout [ Middle ( TEMP::layoutRtagCiteFIND ; 5 ; 42 ) ]
End If
#
#
#Find references for reference module.
Show All Records
#
#Omit locked records, which are the copyright
#images used by default copyright tags.
Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::lock: “lock” ]
[ Restore ]
#
#Sort and go to the first record. Due to bugs,
#two sorts are required to get to the
#first record.
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list: “order
Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else
#There is no cite menu for inventory libraries,
#so no need to perform a sort.
End If
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stoploadCitation ]
#
#Go to citation record's current selection or to first record.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
#
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
