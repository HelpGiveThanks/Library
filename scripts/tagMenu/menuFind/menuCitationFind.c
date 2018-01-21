January 20, 2018 19:13:45 Library.fmp12 - menuCitationFind -1-
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
#Goto correct layout.
Go to Layout [ “ReferenceMenu3CiteFind” (reference) ]
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
