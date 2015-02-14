tagMenu: menuCitation
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Go to Field [ ]
#
#Clear sample and test tags so there conditional
#formatting in the Learn window is removed.
If [ $$citationMatch = "sample" or $$citationMatch = "test" ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Set Variable [ $$tagSample ]
Set Variable [ $$tagtest ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
End If
#
#Set testlearn internal reference field conditional
#formatting to tan.
Set Variable [ $$internal ]
Sort Records [ Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
Select Window [ Name: "Tag Menus"; Current file ]
#
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"cite" ]
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Freeze Window
#
#Goto correct layout.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnMenu3Cite” (reference) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenu3Cite” (reference) ]
End If
#
#Find Citations for this library.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
If [ Left (Get (LayoutName) ; 9 ) ≠ "reference" ]
Set Field [ reference::kcsection; TEMP::ksection ]
Set Field [ reference::show; "show in learn" ]
Else
Set Field [ reference::kcsection; TEMP::ksection ]
End If
// Set Field [ reference::filterFind; "main" & ¶ ]
// Set Field [ reference::ktest; TEMP::ktest ]
Perform Find [ ]
// Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::knodePrimary: “=” ]
[ Restore ]
// Extend Found Set [ Specified Find Requests: Find Records; Criteria: reference::referenceNodes: “*” AND reference::filterFind: “"main"” ]
[ Restore ]
// Extend Found Set [ Specified Find Requests: Find Records; Criteria: reference::referenceNodes: “*” ]
[ Restore ]
// Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::Title: “=” ]
[ Restore ]
Sort Records [ Specified Sort Order: tagKeywordPrimary::tag; ascending ]
[ Restore; No dialog ]
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
// If [ TEMP::sortCite = "cat" ]
// Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
// Else If [ TEMP::sortCite = "abc" ]
// Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
// End If
Sort Records [ Specified Sort Order: tagKeywordPrimary::orderOrLock; ascending
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
#
#Go to citation record's current selection or to first record.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Exit Loop If [ $$cite = reference::_Lreference ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ $$cite ≠ reference::_Lreference ]
#
#Decided below was too much help. User can look
#on main screen to see where cite or reference is located.
// #Clear reference location variable that conditionally
// #formatts buttons to tell user where reference is located.
// Set Variable [ $$refIsRefRecord ]
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Go to Field [ ]
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Exit Script [ ]
End If
#
#Decided below was too much help. User can look
#on main screen to see where cite or reference is located.
// #Turn on reference location variable that conditionally
// #formatts buttons to tell user where reference is located.
// Set Variable [ $$refIsRefRecord; Value:1 ]
#
January 7, 平成26 16:00:31 Imagination Quality Management.fp7 - menuCitation -1-tagMenu: menuCitation
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
January 7, 平成26 16:00:31 Imagination Quality Management.fp7 - menuCitation -2-
