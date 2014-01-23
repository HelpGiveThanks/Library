learn: newLearn
#
#If node is currenlty locked then stop script, inform user.
If [ TEMP::nodeLock ≠ "" ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to create new records assigned to this node."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If in ﬁnd mode, exit script.
If [ $$ﬁndMode ≠ "" ]
Show Custom Dialog [ Message: "Exit ﬁnd mode, then click this button."; Buttons: “OK” ]
Exit Script [ ]
End If
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Field [ ]
Freeze Window
New Record/Request
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::kNodePrimary; TEMP::kdefaultNodePrimary ]
Set Field [ testlearn::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ testlearn::RecordModifyDate; Get ( CurrentTimeStamp ) ]
Set Field [ testlearn::kNodeOther; TEMP::kdefaultNodeOther ]
Set Field [ testlearn::NodeOthers; TEMP::DEFAULTNodeOtherNames ]
Set Field [ testlearn::kHealth; TEMP::kdefaultHealth ]
Set Field [ testlearn::incomplete; "incomplete" & ¶ ]
Set Field [ testlearn::ﬁlterFind; "main" & ¶ ]
If [ Right ( Get ( LayoutName ) ; 4 ) = "EDIT" ]
Set Field [ testlearn::ﬁlterFind; "main" & ¶ ]
Set Variable [ $$stoploadCitation ]
#
#Note that citation is for either the node or keyword depending on the citation match.
Else If [ Right ( Get ( LayoutName ) ; 3 ) = "TAG" ]
Set Field [ testlearn::ﬁlterFind; "main" & ¶ ]
End If
Sort Records [ ]
[ No dialog ]
Set Variable [ $record; Value:Get (RecordNumber) ]
Go to Record/Request/Page [ $record ]
[ No dialog ]
Set Variable [ $$stoploadCitation ]
// Perform Script [ “loadCitation” ]
Set Variable [ $$citation; Value:testlearn::_Ltestlearn ]
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
Set Variable [ $$medium; Value:testlearn::kmedium ]
Set Variable [ $$health; Value:testlearn::kHealth ]
Set Variable [ $$Path; Value:testlearn::kfolderPath ]
Set Variable [ $$cite; Value:testlearn::kcitation ]
Set Variable [ $$ref; Value:testlearn::kcreference ]
Set Variable [ $$PrimaryKey; Value:testlearn::kKeywordPrimary ]
Set Variable [ $$Key; Value:testlearn::kcKeywordOther ]
Set Variable [ $$OtherKey; Value:testlearn::kcKeywordOther ]
Set Variable [ $$Section; Value:testlearn::kcsection ]
Set Variable [ $$test; Value:testlearn::kctest ]
Set Variable [ $$sample; Value:testlearn::kcsample ]
Set Variable [ $$RecordID; Value:Get (RecordID) ]
Set Variable [ $$stopOpenNewTextWindow ]
Set Variable [ $$stopLoadCitation; Value:1 ]
Set Variable [ $$citationItem ]
If [ $$citationMatch = "node" ]
Set Variable [ $$citationItem; Value:TEMP::kdefaultNodePrimary ]
End If
#
#Clear conditional formatting in Tag Menus window.
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Refresh Window
Select Window [ Name: "Learn"; Current ﬁle ]
#
#Open new window to edit new record in.
New Window [ ]
Go to Layout [ “LearnTextWindow” (testlearn) ]
Go to Field [ testlearn::Caption ]
Set Variable [ $$stopLoadCitation ]
Pause/Resume Script [ Indeﬁnitely ]
// Go to Object [ Object Name: "text" ]
January 7, 平成26 17:28:42 Imagination Quality Management.fp7 - newLearn -1-
