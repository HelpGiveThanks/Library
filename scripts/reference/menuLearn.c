July 21, 2018 12:41:21 Library.fmp12 - menuLearn -1-
reference: menuLearn
#
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
Select Window [ Name: "Tag Menus"; Current file ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"learn" ]
#
#Set testlearn internal reference field conditional
#formatting to green if there are any.
Set Variable [ $$internal; Value:1 ]
#
#Speed up script.
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Show all internal reference possibilities.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnMenu4noPicRefCite” (testlearn) ]
Else
Go to Layout [ “learnMenu4noPicRefCite” (testlearn) ]
End If
#
#Find learn records that can be referenced.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Field [ testlearn::brainstormCasePoint; "1" ]
End If
Set Field [ testlearn::filterFind; "main" ]
Perform Find [ ]
#
#If the user has yet to create any Learn or internal records
#let them know, and return user to outside reference records.
If [ Get (FoundCount) = 0 ]
#
Show Custom Dialog [ Message: "No Learn records have been created."; Default Button: “OK”, Commit: “Yes” ]
#
#Turn back on essential variable.
Set Variable [ $$stoploadCitation ]
Exit Script [ ]
#
End If
#
#Continue with show all internal reference possibilities...
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
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
#
#If the current learn record references another
#learn record, find it.
If [ Filter ( $$ref ; "L" ) ≠ "" ]
Loop
Exit Loop If [ testlearn::_Ltestlearn & "L¶" = FilterValues ( $$ref ; testlearn::_Ltestlearn & "L¶" ) and $$citationMatch = "ref" ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#If no records are used as a cite or ref, go to first record.
If [ Get (LastError) = 101 ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
End If
#
End If
#
#Goto correct layout.
If [ TEMP::InventoryLibraryYN = "" ]
#Idea Mode
#
If [ TEMP::layoutLtagL = "" ]
#If no layout preference is set, then on iDevices
#go the layout with no pictures, and to the
#layout with pictures on desktop computers.
If [ Get (SystemPlatform) = 3 ]
Go to Layout [ “learnMenu4noPicRefCite” (testlearn) ]
Set Field [ TEMP::layoutLtagL; "more" & Get (LayoutName) ]
Else
Go to Layout [ “learnMenu4RefCite” (testlearn) ]
Set Field [ TEMP::layoutLtagL; "less" & Get (LayoutName) ]
End If
Else
#
#Go the layout the user has selected.
Go to Layout [ Middle ( TEMP::layoutLtagL ; 5 ; 42 ) ]
End If
#
Else
#
#Inventory Mode
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnMenu4STUFFRefCite” (testlearn) ]
// Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderInventoryGroupNumber; ascending
testlearn::note; ascending ]
[ Restore; No dialog ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
End If
#
#
End If
#
#Update conditional formatting in main window.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Go to Field [ ]
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
#
#Turn back on essential variable.
Set Variable [ $$stoploadCitation ]
#
