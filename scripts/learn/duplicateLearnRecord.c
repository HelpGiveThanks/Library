learn: duplicateLearnRecord
#
#If node is currenlty locked then stop script, inform user.
If [ TEMP::nodeLock ≠ "" ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to create new records assigned to this node."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Exit find mode, then click this button."; Buttons: “OK” ]
Exit Script [ ]
End If
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Field [ ]
Set Variable [ $caption; Value:testlearn::Caption ]
Set Variable [ $P; Value:testlearn::kKeywordPrimary ]
Set Variable [ $O; Value:testlearn::kcKeywordOther ]
Set Variable [ $Owords; Value:testlearn::OtherKeyWords ]
Set Field [ TEMP::duplicateOtherKeywords; testlearn::kcKeywordOther ]
Set Variable [ $citation; Value:testlearn::kcitation ]
Set Variable [ $reference; Value:testlearn::kcreference ]
#The 'L' is added to all Tag Menu to conditional format
#the Learn menu button.
Set Variable [ $referenceOriginal; Value:testlearn::_Ltestlearn & "L" ]
New Record/Request
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::kNodePrimary; TEMP::kdefaultNodePrimary ]
Set Field [ testlearn::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ testlearn::RecordModifyDate; Get ( CurrentTimeStamp ) ]
Set Field [ testlearn::kNodeOther; TEMP::kdefaultNodeOther ]
Set Field [ testlearn::NodeOthers; TEMP::DEFAULTNodeOtherNames ]
Set Field [ testlearn::kHealth; TEMP::kdefaultHealth ]
Set Field [ testlearn::incomplete; "incomplete" & ¶ ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Set Field [ testlearn::kKeywordPrimary; $P ]
Set Field [ testlearn::OtherKeyWords; $Owords ]
Set Field [ testlearn::kcitation; $citation ]
Set Field [ testlearn::Caption; $O ]
#
#Filemaker has a bug that is stripping out the paragraphs
#if the script puts the O variable keys directly into the
#other word field. But put them into caption and then
#from caption into the otherword key field and everything
#is fine.
Set Field [ testlearn::kcKeywordOther; testlearn::Caption ]
Set Field [ testlearn::Caption; $caption ]
Set Variable [ $$stoploadCitation ]
If [ testlearn::kcitation = "" ]
Show Custom Dialog [ Message: "Reference the duplicated record (the one with the green bar)? If yes, adds the dupliated record to the referene section of its duplicate (the record below the one with green bar)."; Buttons: “no”, “yes” ]
If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ testlearn::kcreference; $referenceOriginal & ¶ & $reference ]
Else
Set Field [ testlearn::kcreference; $reference ]
End If
Else
Set Field [ testlearn::kcreference; $reference ]
End If
Sort Records [ ]
[ No dialog ]
Set Variable [ $record; Value:Get (RecordNumber) ]
Go to Record/Request/Page [ $record ]
[ No dialog ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadCitation” ]
Set Variable [ $$stopOpenNewTextWindow ]
Perform Script [ “LearnOpenTextNewWindow” ]
January 7, 平成26 17:25:29 Imagination Quality Management.fp7 - duplicateLearnRecord -1-
