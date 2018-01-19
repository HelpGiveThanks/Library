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
#Find Citations for this library.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
If [ Left (Get (LayoutName) ; 9 ) ≠ "reference" ]
Set Field [ reference::kcsection; TEMP::ksection ]
Set Field [ reference::showInLearn; "show in learn" ]
Else
Set Field [ reference::kcsection; TEMP::ksection ]
End If
Perform Find [ ]
Sort Records [ Specified Sort Order: tagKeywordPrimary::tag; ascending ]
[ Restore; No dialog ]
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
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
August 19, ଘ౮28 23:30:11 Library.fp7 - menuCitationFind -1-
