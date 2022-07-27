July 27, 2022 11:31:52 Library.fmp12 - duplicateLearnRecord -1-
learn: duplicateLearnRecord
#
#
#IMPORTANT: Exit the text field just in case the
#user is in this field and has just been using the
#mic to dictate text. If this script does not
#exit the field first, then all text in the
#field will be erased!!!
Go to Field [ ]
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Currently in find mode. Click done in the tag menus window to exit find mode, and then click
this button."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode” ]
#
#Give user duplicate record options.
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "Duplicate this record to continue capturing ideas, thoughts, etc. that link to the current record
MINUS its tagged references?"; Default Button: “yes”, Commit: “Yes”; Button 2: “no”, Commit: “No”; Button 3: “cancel”,
Commit: “No” ]
#
#If user wants to reference current record, note
#this and then ask if the want to also duplicate
#previous record's reference tags.
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $referenceCurrentRecord; Value:1 ]
End If
#
#If user cancels, then exit script.
If [ Get ( LastMessageChoice ) = 3 ]
Exit Script [ ]
End If
End If
#
#Close edit window if user clicked "d" button
#from this window.
If [ Get (WindowName) = "Edit" ]
Go to Field [ ]
Show/Hide Text Ruler
[ Hide ]
Close Window [ Current Window ]
Set Variable [ $$DuplicateDontGoToTagMenuWindow; Value:1 ]
Set Variable [ $$PictureOnReportLayout ]
End If
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Exit find mode, then click this button."; Default Button: “OK”, Commit: “No” ]
Exit Script [ ]
End If
#
#If user selects option 1 or 2 gather orignal record's info.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $getRecordNumberInCaseUserCancles; Value:Get ( RecordNumber ) ]
Go to Field [ ]
Set Variable [ $note; Value:testlearn::note ]
Set Variable [ $point; Value:testlearn::brainstormCasePoint ]
Set Variable [ $P; Value:testlearn::kKeywordPrimary ]
Set Variable [ $O; Value:testlearn::kcKeywordOther ]
Set Variable [ $Owords; Value:testlearn::OtherKeyWords ]
Set Field [ TEMP::duplicateOtherKeywords; testlearn::kcKeywordOther ]
Set Variable [ $reference; Value:testlearn::kcreference ]
Set Variable [ $showReferencedMedia; Value:testlearn::kshowReferencedMedia ]
Set Variable [ $picture; Value:testlearn::picture ]
#The 'L' is added to all Tag Menu to conditional format
#the Learn menu button.
Set Variable [ $referenceOriginal; Value:testlearn::_Ltestlearn & "L" ]
New Record/Request
Set Field [ testlearn::kNodePrimary; TEMP::kdefaultNodePrimary ]
Set Field [ testlearn::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ testlearn::dateModify; Get ( CurrentTimestamp ) ]
Set Field [ testlearn::kNodeOther; TEMP::kdefaultNodeOther ]
Set Field [ testlearn::NodeOthers; TEMP::DEFAULTNodeOtherNames ]
Set Field [ testlearn::kcopyright; TEMP::kdefaultCopyright ]
Set Field [ testlearn::incomplete; "incomplete" & ¶ ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Set Field [ testlearn::kKeywordPrimary; $P ]
Set Field [ testlearn::OtherKeyWords; $Owords ]
Set Field [ testlearn::picture; $picture ]
#
#Filemaker has a bug that is stripping out the paragraphs
#if the script puts the Other variable keys directly into the
#other word field. But put them into the note field and then
#from note into the otherword key field and everything
#is fine.
Set Field [ testlearn::note; $O ]
Set Field [ testlearn::kcKeywordOther; testlearn::note ]
Set Field [ testlearn::note; $note ]
Set Field [ testlearn::brainstormCasePoint; $point ]
Set Variable [ $$stoploadCitation ]
#
#If the user does not want to keep tagged
#references then remove them.
If [ $referenceCurrentRecord = 1 ]
Set Field [ testlearn::kcreference; $referenceOriginal & ¶ & $reference ]
Set Field [ testlearn::kshowReferencedMedia; $showReferencedMedia ]
#
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $count; Value:ValueCount ( testlearn::kcreference ) ]
Loop
If [ Filter ( GetValue ( testlearn::kcreference ; $count ) ; "L" ) ≠ "L" ]
Set Field [ testlearn::kcreference; //last item in list has no paragraph mark, so a valuecount test needs to be done and if
item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( testlearn::kcreference) ≠ ValueCount ( Substitute ( testlearn::kcreference ; GetValue ( testlearn::
kcreference ; $count ) & "¶" ; "" ) ) ;
Substitute ( testlearn::kcreference ; GetValue ( testlearn::kcreference ; $count ) & "¶" ; "" ) ;
Substitute ( testlearn::kcreference ; GetValue ( testlearn::kcreference ; $count ); "" )
) ]
End If
Set Variable [ $count; Value:$count - 1 ]
Exit Loop If [ $count = 0 ]
End Loop
Set Variable [ $$stoploadCitation ]
#
#If the user wants to keep tagged references
#then do not remove them.
Else If [ Get ( LastMessageChoice ) = 2 or
TEMP::InventoryLibraryYN ≠ "" ]
Set Field [ testlearn::kcreference; $referenceOriginal & ¶ & $reference ]
Set Field [ testlearn::kshowReferencedMedia; $showReferencedMedia ]
#
End If
#
#
#Sort the new record to the top of window, and
#go to this new record, run the loadCition script,
#and open up the text edit window for the new record.
Sort Records [ ]
[ No dialog ]
Set Variable [ $record; Value:Get (RecordNumber) ]
Go to Record/Request/Page [ $record ]
[ No dialog ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadLearnOrRefMainRecord” ]
Set Variable [ $$stopOpenNewTextWindow ]
#
#Note that the new record is a duplicate so its
#text area should be highlighted when opened
#in the follow on script, which makes it easy
#for the user to replace the deleted text while
#keeping all the duplcated tags.
Set Variable [ $$duplicateRecord; Value:1 ]
#
#Open duplicate record in text window so
#user can now edit it.
Perform Script [ “learnOpenTextNewWindow” ]
#
#
