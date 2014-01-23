tagMenu: menuFind: menuCitationFind
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"cite" ]
#
#Set testlearn internal reference ﬁeld conditional
#formatting to transparent.
Set Variable [ $$internal ]
#
#Goto correct layout.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnFindCite” (reference) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “learnFindCite” (reference) ]
End If
#
#Find Citations for this library.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ reference::kcsection; TEMP::ksection ]
// Set Field [ reference::ﬁlterFind; "main" ]
// Set Field [ reference::ktest; TEMP::ktest ]
Perform Find [ ]
Constrain Found Set [ Speciﬁed Find Requests: Omit Records; Criteria: reference::knodePrimary: “=” ]
[ Restore ]
Extend Found Set [ Speciﬁed Find Requests: Find Records; Criteria: reference::referenceNodes: “*” ]
[ Restore ]
// Constrain Found Set [ Speciﬁed Find Requests: Omit Records; Criteria: reference::Title: “=” ]
[ Restore ]
Sort Records [ Speciﬁed Sort Order: tagKeywordPrimary::orderOrLock; ascending
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
If [ TEMP::sortCite = "cat" or TEMP::sortCite = "" ]
Sort Records [ Speciﬁed Sort Order: tagKeywordPrimary::orderOrLock; ascending
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
// Sort Records [ Speciﬁed Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortCite = "abc" ]
Sort Records [ Speciﬁed Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
January 7, 平成26 16:53:37 Imagination Quality Management.fp7 - menuCitationFind -1-
