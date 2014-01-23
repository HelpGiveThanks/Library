tagMenu: menuReference
#
#Clear sample and test tags so there conditional
#formatting in the Learn window is removed.
If [ $$citationMatch = "sample" or $$citationMatch = "test" ]
Select Window [ Name: "Learn"; Current ﬁle ]
Go to Field [ ]
Set Variable [ $$tagSample ]
Set Variable [ $$tagtest ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
End If
Sort Records [ Speciﬁed Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
Select Window [ Name: "Tag Menus"; Current ﬁle ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"ref" ]
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Set testlearn internal reference ﬁeld conditional
#formatting to transparent.
Set Variable [ $$internal ]
#
#Goto correct layout.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnMenu3Cite” (reference) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenu3Cite” (reference) ]
End If
#
#Find References for this section.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ reference::kcsection; TEMP::ksection ]
Set Field [ reference::ﬁlterFind; "main" ]
Set Field [ reference::show; "show in learn" ]
// Set Field [ reference::ktest; TEMP::ktest ]
Perform Find [ ]
// Constrain Found Set [ Speciﬁed Find Requests: Omit Records; Criteria: reference::knodePrimary: “=” ]
[ Restore ]
// Extend Found Set [ Speciﬁed Find Requests: Find Records; Criteria: reference::referenceNodes: “*” ]
[ Restore ]
// Constrain Found Set [ Speciﬁed Find Requests: Omit Records; Criteria: reference::Title: “=” ]
[ Restore ]
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
Sort Records [ Speciﬁed Sort Order: tagKeywordPrimary::orderOrLock; ascending
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
#
#Go to citation record's current selection or to ﬁrst record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ FilterValues ( $$ref ; reference::_Lreference ) = reference::_Lreference & ¶ ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
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
Select Window [ Name: "References"; Current ﬁle ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current ﬁle ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Go to Field [ ]
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
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
#Just in case user was in nonTag ﬁeld on this
#window when user clicked a menu button on
#the other window, exit all ﬁelds.
Select Window [ Name: "References"; Current ﬁle ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current ﬁle ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Go to Field [ ]
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
January 7, 平成26 16:01:01 Imagination Quality Management.fp7 - menuReference -1-
