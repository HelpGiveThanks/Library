January 17, 2018 11:33:46 Library.fmp12 - newLearn -1-
learn: newLearn
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode” ]
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Exit find mode, then click this button."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Field [ ]
Freeze Window
New Record/Request
Set Field [ testlearn::kNodePrimary; TEMP::kdefaultNodePrimary ]
Set Field [ testlearn::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ testlearn::dateModify; Get ( CurrentTimeStamp ) ]
Set Field [ testlearn::kNodeOther; TEMP::kdefaultNodeOther ]
Set Field [ testlearn::NodeOthers; TEMP::DEFAULTNodeOtherNames ]
Set Field [ testlearn::kcopyright; TEMP::kdefaultCopyright ]
Set Field [ testlearn::incomplete; "incomplete" & ¶ ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
If [ Right ( Get ( LayoutName ) ; 4 ) = "EDIT" ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Set Variable [ $$stoploadCitation ]
#
#Note that citation is for either the node or keyword depending on the citation match.
Else If [ Right ( Get ( LayoutName ) ; 3 ) = "TAG" ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
End If
Sort Records [ ]
[ No dialog ]
Set Variable [ $record; Value:Get (RecordNumber) ]
Go to Record/Request/Page [ $record ]
[ No dialog ]
Set Variable [ $$stoploadCitation ]
// Perform Script [ “loadLearnOrRefMainRecord” ]
Set Variable [ $$main; Value:testlearn::_Ltestlearn ]
#
#capture keys of related tag menu items to
#to allow the citationMenu scripts to loop to the
#primary record of interest when the user navigates
#to a item on the Tag Menu window
#whose list of tags like node, keyword, medium, etc.
#might contain an item related to the current
#citation record, but which one, which is why all
#the keys have to be readied. Mmm... now that
#I write this out, I'm thinking I could have the
#citationMenu scripts select the citation window
#to grab the key if any in the current current
#record that applies to the menu item.
Set Variable [ $$citationRecord; Value:testlearn::_Ltestlearn ]
Set Variable [ $$node; Value:testlearn::kNodeOther ]
Set Variable [ $$primaryNode; Value:testlearn::kNodePrimary ]
Set Variable [ $$copyright; Value:testlearn::kcopyright ]
Set Variable [ $$ref; Value:testlearn::kcreference ]
Set Variable [ $$PrimaryKey; Value:testlearn::kKeywordPrimary ]
Set Variable [ $$Key; Value:testlearn::kcKeywordOther ]
Set Variable [ $$OtherKey; Value:testlearn::kcKeywordOther ]
Set Variable [ $$test; Value:testlearn::kctestSubsectionInfo ]
Set Variable [ $$brainstorm; Value:testlearn::kcbrainstorm ]
Set Variable [ $$RecordID; Value:Get (RecordID) ]
Set Variable [ $$stopOpenNewTextWindow ]
Set Variable [ $$stopLoadCitation; Value:1 ]
Set Variable [ $$citationItem ]
If [ $$citationMatch = "node" ]
Set Variable [ $$citationItem; Value:TEMP::kdefaultNodePrimary ]
End If
#
#Clear conditional formatting in Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
Select Window [ Name: "Learn"; Current file ]
Set Variable [ $$stopLoadCitation ]
#
#Open new record in text window so
#user can now edit it.
Perform Script [ “learnOpenTextNewWindow” ]
#
