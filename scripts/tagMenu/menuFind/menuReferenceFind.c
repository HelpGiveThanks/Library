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
If [ TEMP::InventoryLibaryYN ≠ "" ]
Go to Layout [ “learnFindStuffCite” (reference) ]
End If
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “learnFindCite” (reference) ]
End If
#
#Find References for this library.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ reference::kcsection; TEMP::ksection ]
If [ TEMP::InventoryLibaryYN ≠ "" ]
Set Field [ reference::filterFind; "main" ]
Set Field [ reference::show; "show in learn" ]
End If
// Set Field [ reference::filterFind; "main" ]
// Set Field [ reference::ktest; TEMP::ktest ]
Perform Find [ ]
If [ TEMP::InventoryLibaryYN = "" ]
Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::knodePrimary: “=” ]
[ Restore ]
Extend Found Set [ Specified Find Requests: Find Records; Criteria: reference::referenceNodes: “*” ]
[ Restore ]
Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::Title: “=” ]
[ Restore ]
End If
Sort Records [ Specified Sort Order: tagKeywordPrimary::orderOrLock; ascending
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
If [ TEMP::sortRef = "cat" or TEMP::sortRef = "" ]
Sort Records [ Specified Sort Order: tagKeywordPrimary::orderOrLock; ascending
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortRef = "abc" ]
Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
May 10, 平成27 10:58:24 Library.fp7 - menuReferenceFind -1-
