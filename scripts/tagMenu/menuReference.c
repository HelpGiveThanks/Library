July 21, 2018 14:16:44 Library.fmp12 - menuReference -1-
tagMenu: menuReference
#
#
#Prevent halting of script.
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Go to Field [ ]
#
#Clear brainstorm and test tags so there conditional
#formatting in the Learn window is removed.
If [ $$citationMatch = "brainstorm" or $$citationMatch = "test" ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Set Variable [ $$tagBrainstorm ]
Set Variable [ $$tagtest ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
#
#Sort the records by date field, if current sort is
#by order number.
If [ TEMP::TLTestSort = 1 or TEMP::TLBrainstormSort = 1 ]
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderInventoryGroupNumber; ascending
testlearn::note; ascending ]
[ Restore; No dialog ]
End If
#
#Set the sort preference field to date.
If [ $$citationMatch = "brainstorm" ]
Set Field [ TEMP::TLBrainstormSort; "" ]
Else If [ $$citationMatch = "test" ]
Set Field [ TEMP::TLTestSort; "" ]
End If
End If
#
End If
#
#Admin tasks.
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
Select Window [ Name: "Tag Menus"; Current file ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"ref" ]
#
Set Variable [ $$doNotHaltOtherScripts ]
#
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Set testlearn internal reference field conditional
#formatting to transparent.
Set Variable [ $$internal ]
#
#Speed up script by going to layout with no
#pictures to load.
If [ Left (Get (LayoutName) ; 1) = "l" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “learnMenu3CiteS” (reference) ]
Else
Go to Layout [ “learnMenu3CiteS” (reference) ]
// Go to Layout [ “learnMenuRefStuff” (reference) ]
End If
Else
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “ReferenceMenu3Cite” (reference) ]
Else
End If
End If
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
#Go to citation record's current selection or to first record.
Go to Record/Request/Page
[ First ]
#
#If current learn record is tagged with a
#reference, find it.
If [ Length ( Filter ( $$ref ; "L" ) ) ≠ ValueCount ( $$ref ) ]
Loop
Exit Loop If [ FilterValues ( $$ref ; reference::_Lreference ) = reference::_Lreference & ¶ ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#Clear these variables and then load them.
Set Variable [ $$refIDForMainLearnRecord ]
Set Variable [ $$learnIDForMainLearnRecord; Value:reference::_Lreference ]
Set Variable [ $$refIDForMainLearnRecord; Value:reference::_Lreference ]
#
#Goto correct layout.
If [ TEMP::InventoryLibraryYN = "" ]
#Idea Mode
#
#If no layout preference is set, then on iDevices
#go the layout with no pictures, and to the
#layout with pictures on desktop computers.
If [ TEMP::layoutLtagR = "" ]
If [ Get (SystemPlatform) = 3 ]
Go to Layout [ “learnMenu3CiteS” (reference) ]
Set Field [ TEMP::layoutLtagR; "more" & Get (LayoutName) ]
Else
Go to Layout [ “learnMenu3Cite” (reference) ]
Set Field [ TEMP::layoutLtagR; "less" & Get (LayoutName) ]
End If
Else
#
#Go the layout the user has selected.
Go to Layout [ Middle ( TEMP::layoutLtagR ; 5 ; 42 ) ]
End If
#
Else
#Inventory Mode
#
#Go the location tag layout.
Go to Layout [ “learnMenuRefStuff” (reference) ]
Set Variable [ $$editLocation; Value:reference::_Lreference ]
End If
#
If [ FilterValues ( $$ref ; reference::_Lreference ) ≠ reference::_Lreference & ¶ ]
#
#Decided below was too much help. User can look
#on main screen to see where cite or reference is located.
// #Clear reference location variable that conditionally
// #formatts buttons to tell user where reference is located.
// Set Variable [ $$refIsRefRecord ]
#
Scroll Window
[ Home ]
Go to Record/Request/Page
[ First ]
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
#
#In inventory mode prevent the showing of
#hidden edit fields.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Perform Script [ “loadTagRecord (update)” ]
Exit Script [ ]
End If
#
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Go to Field [ ]
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $stopref ]
Exit Script [ ]
End If
#
#
#
#
#
#Decided below was too much help. User can look
#on main screen to see where cite or reference is located.
#
#
#
#
#
// #Turn on reference location variable that conditionally
// #formatts buttons to tell user where reference is located.
// Set Variable [ $$refIsRefRecord; Value:1 ]
#
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
#Inform user of items use on both screens.
Set Variable [ $$citationItem; Value:reference::_Lreference ]
Refresh Window
#Just in case user was in nonTag field on this
#window when user clicked a menu button on
#the other window, exit all fields.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Go to Field [ ]
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
