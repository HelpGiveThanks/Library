January 17, 2018 13:00:41 Library.fmp12 - gotoReference -1-
reference: gotoReference
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
If [ tempSetup::kdefaultCopyright = "" ]
Show Custom Dialog [ Message: "Select the default copyright for any new records that you create by clicking the copyright button
(you can always change your mind)."; Default Button: “OK”, Commit: “Yes” ]
Halt Script
Else If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible for creating new records) by clicking the node button.";
Default Button: “OK”, Commit: “No” ]
Halt Script
End If
#
#Set in copyAndpastTags script.
Set Variable [ $$copyAndpastTagsRECORD ]
#
#Determine if user wants to edit an external citation.
If [ Get (LayoutTableName) = "reference" ]
#
#Capture record ID so system can return user
#after editing is complete.
Set Variable [ $$tagEdit; Value:reference::_Lreference ]
Set Variable [ $$learnTagLayout; Value:Get (LayoutName) ]
Set Variable [ $$module; Value:"ref" ]
#
#Go to reference tag menu so load citation script
#below will work properly.
Set Variable [ $$stoploadTagRecord; Value:1 ]
Go to Layout [ “ReferenceMenu2keywordOrNode2” (tagMenus) ]
Set Variable [ $$stoploadTagRecord ]
#
#Capture record ID so system can return user
#after editing is complete.
Select Window [ Name: "Learn"; Current file ]
Set Variable [ $$LearnEdit; Value:testlearn::_Ltestlearn ]
#
#Take user to reference layout without pictures
#for faster looping thru records.
Set Variable [ $$stoploadCitation; Value:1 ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceStuffScriptLoops” (reference) ]
Else
Go to Layout [ “ReferenceStuffScriptLoops” (reference) ]
End If
Set Window Title [ Current Window; New Title: "References" ]
#
#Find main records.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Show All Records
#
#Omit locked records, which are the copyright
#images used by default copyright tags.
Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::lock: “lock” ]
[ Restore ]
#
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list:
“order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list:
“order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
End If
#
#Loop to record to be edited.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Exit Loop If [ $$tagEdit = reference::_Lreference ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Load selected records keys and the menu 'key'.
Set Variable [ $$stoploadCitation ]
Perform Script [ “menuKey (update)” ]
Perform Script [ “loadLearnOrRefMainRecord (update name change loadCitation)” ]
#
#Take user to reference edit layout with pictures.
Set Variable [ $$stoploadCitation; Value:1 ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceStuff” (reference) ]
Else
Go to Layout [ “Reference” (reference) ]
End If
Set Variable [ $$stoploadCitation ]
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
Go to Layout [ “ReferenceMenu2keywordOrNode2” (tagMenus) ]
Set Variable [ $$stoploadTagRecord ]
#
#Capture record ID so system can return user
#after editing is complete.
Select Window [ Name: "Setup"; Current file ]
#
#Take user to citation edit layout.
Set Variable [ $$stoploadCitation; Value:1 ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceStuff” (reference) ]
Else
Go to Layout [ “Reference” (reference) ]
End If
Set Window Title [ Current Window; New Title: "References" ]
#
#Find main records.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Show All Records
#
#Omit locked records, which are the copyright
#images used by default copyright tags.
Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::lock: “lock” ]
[ Restore ]
#
If [ TEMP::InventoryLibraryYN ≠ "" ]
#
Go to Layout [ “ReferenceStuff” (reference) ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list:
“testPulldownListANDsortOrderList”
tagKeywordPrimary::tag; ascending
reference::publicationYearOrStuffOrderNumber; based on value list: “testPulldownListANDsortOrderList”
reference::Title; ascending
reference::thoughtsNotesEtc; ascending ]
[ Restore; No dialog ]
#
Else
#
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list:
“order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
#
End If
#
#Go to first record.
Go to Record/Request/Page
[ First ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “menuKey (update)” ]
Perform Script [ “loadLearnOrRefMainRecord (update name change loadCitation)” ]
Scroll Window
[ Home ]
#
#
End If
