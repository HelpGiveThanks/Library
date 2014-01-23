reference(citation): editCitation
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
If [ TEMP::ksection = "" ]
Show Custom Dialog [ Message: "Select a section from the Tag Menus window for records that you create to be placed into."; Buttons: “OK” ]
Halt Script
Else If [ tempSetup::kdefaultHealth = "" ]
Show Custom Dialog [ Message: "Select a health/copyright type from the health section."; Buttons: “OK” ]
Halt Script
Else If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible) from Tag Menus window."; Buttons: “OK” ]
Halt Script
End If
#
#Make sure creator node's group is part of section group.
Perform Script [ “addBackSectionCreatorNode” ]
#
#Determine if user wants to edit an external citation.
If [ Get (LayoutTableName) = "reference" ]
#
#Capture record ID so system can return user
#after editing is complete.
Set Variable [ $$tagEdit; Value:reference::_Lreference ]
Set Variable [ $$learnTagLayout; Value:Get (LayoutName) ]
Set Variable [ $$citeORref; Value:$$citationMatch ]
#
#Go to reference tag menu so load citation script
#below will work properly.
Set Variable [ $$stoploadTagRecord; Value:1 ]
Go to Layout [ “ReferenceMenu2keywordOrNode1” (tagMenus) ]
Set Variable [ $$stoploadTagRecord ]
#
#Capture record ID so system can return user
#after editing is complete.
Select Window [ Name: "Learn"; Current ﬁle ]
Set Variable [ $$LearnEdit; Value:testlearn::_Ltestlearn ]
#
#Take user to citation edit layout.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Layout [ “Reference” (reference) ]
Set Window Title [ Current Window; New Title: "References" ]
#
#Find main records.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ reference::kcsection; TEMP::ksection ]
// Set Field [ reference::ﬁlterFind; "main" ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: tagKeywordPrimary::tag; ascending
reference::referenceForReferenceWindow; ascending ]
[ Restore; No dialog ]
#
#Loop to record to be edited.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$tagEdit = reference::_Lreference ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$stoploadCitation ]
Perform Script [ “menuKey” ]
Perform Script [ “loadCitation” ]
Sort Records [ Speciﬁed Sort Order: tagKeywordPrimary::tag; ascending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Set Variable [ $refRecordNumber; Value:Get ( RecordNumber ) ]
Scroll Window
[ Home ]
Go to Record/Request/Page
[ Last ]
Go to Record/Request/Page [ $refRecordNumber ]
[ No dialog ]
#
Else If [ Left ( Get (LayoutName) ; 1 ) = "d" ]
#
#
#Capture record ID so system can return user
#after editing is complete.
Set Variable [ $$defaultRecordNumber; Value:Get (RecordNumber) ]
Set Variable [ $$defaultTagLayout; Value:Get (LayoutName) ]
#
#Go to reference tag menu so load citation script
#below will work properly.
Set Variable [ $$stoploadTagRecord; Value:1 ]
Go to Layout [ “ReferenceMenu2keywordOrNode1” (tagMenus) ]
Set Variable [ $$stoploadTagRecord ]
#
#Capture record ID so system can return user
#after editing is complete.
Select Window [ Name: "Setup"; Current ﬁle ]
#
#Take user to citation edit layout.
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Layout [ “Reference” (reference) ]
Set Window Title [ Current Window; New Title: "References" ]
#
#Find main records.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ reference::kcsection; TEMP::ksection ]
// Set Field [ reference::ﬁlterFind; "main" ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: tagKeywordPrimary::tag; ascending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
#
#Loop to record to be edited.
Go to Record/Request/Page
[ First ]
Set Variable [ $$stoploadCitation ]
Go to Field [ reference::knodePrimary ]
Perform Script [ “menuKey” ]
Perform Script [ “loadCitation” ]
Sort Records [ Speciﬁed Sort Order: tagKeywordPrimary::tag; ascending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
January 7, 平成26 17:50:36 Imagination Quality Management.fp7 - editCitation -1-reference(citation): editCitation
Scroll Window
[ Home ]
#
#
End If
January 7, 平成26 17:50:36 Imagination Quality Management.fp7 - editCitation -2-
