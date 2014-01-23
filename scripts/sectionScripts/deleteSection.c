sectionScripts: deleteSection
#
If [ nodeLockSection::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This record is currently locked. Select the node that created it and enter the password to unlock it, then you will able to start the delete process."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Set variables to conditionally format section to
#be deleted, and its record number so if the
#user cancels the delete, the system can return
#to this record.
Set Variable [ $delete; Value:ruleSection::_Lgroup ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
Set Variable [ $$addTagToCitation; Value:1 ]
Set Variable [ $$stopTest; Value:1 ]
#
#Because there may be no records found, stop
#the system from informing the user of this.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#See if section has any learn records tagged
#with it, and if so set the learnInUse variable to 1.
Set Variable [ $$stopLoadCitation; Value:1 ]
Go to Layout [ “learn1” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; $delete ]
Set Field [ testlearn::ﬁlterFind; "main" & ¶ ]
Perform Find [ ]
If [ Get (LastError) ≠ 401 ]
Set Variable [ $learnInUse; Value:1 ]
End If
#
#See if section has any reference records tagged
#with it, and if so set the refInUse variable to 1.
Go to Layout [ “Reference” (reference) ]
Enter Find Mode [ ]
Set Field [ reference::kcsection; $delete ]
Perform Find [ ]
If [ Get (LastError) ≠ 401 ]
Set Variable [ $referenceInUse; Value:1 ]
End If
Set Variable [ $$stopLoadCitation ]
#
#See if section has any tag records tagged
#with it, and if so set the refInUse variable to 1.
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ ruleLibrary 2::ksection; $delete ]
Perform Find [ ]
If [ Get (LastError) ≠ 401 ]
Set Variable [ $TagInUse; Value:1 ]
End If
#
#See if tags in question are only node tags.
Constrain Found Set [ Speciﬁed Find Requests: Omit Records; Criteria: tagTable::match: “node” ]
[ Restore ]
If [ Get (FoundCount) = 0 ]
Set Variable [ $OnlyNodes; Value:1 ]
End If
#
#See if section has any test records tagged
#with it, and if so set the testInUse variable to 1.
Set Variable [ $$ID; Value:"ignore" ]
Go to Layout [ “testSetup” (test) ]
Enter Find Mode [ ]
Set Field [ test::ksection; $delete ]
Perform Find [ ]
If [ Get (LastError) ≠ 401 ]
Set Variable [ $testInUse; Value:1 ]
End If
Set Variable [ $$ID ]
Set Variable [ $$stopTest ]
#
Perform Script [ “defaultSectionMenu” ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
If [ $learnInUse = 1 or $testInUse = 1 or $referenceInUse = 1 or $TagInUse = 1 ]
Set Variable [ $delete ]
Set Variable [ $$addTagToCitation ]
Refresh Window
Show Custom Dialog [ Message: Case ( $tagInUse = 1 and $OnlyNodes = 1 and $referenceInUse + $learnInUse + $testInUse = "" ; "Remove this section's node tags." ;
$tagInUse = 1 and $OnlyNodes ≠ 1 and $referenceInUse + $learnInUse + $testInUse = "" ; "Navigate to all the tag sections in the learn and reference modules and delete their tags before deleting their section." ;
$tagInUse = 1 and $OnlyNodes = 1 and $referenceInUse + $learnInUse + $testInUse = "" ; "Remove this section's node tags." ;
If ( $referenceInUse + $learnInUse + $testInUse > 1 ; "The following modules contain records and/or tags for this section: " ; "The following module contains records and/or tags for this section: " ) &
If ($testInUse = 1 ; "test" ; "" ) &
Case (
$learnInUse = 1 and $testInUse = 1; ", learn" ;
$learnInUse = 1 and $testInUse ≠ 1; "learn" ;
"" ) &
Case (
$referenceInUse = 1 and $learnInUse = 1; ", reference" ;
$referenceInUse = 1 and $testInUse = 1; ", reference" ;
$referenceInUse = 1 and $learnInUse ≠ 1 and $testInUse ≠ 1; " reference" ;
"" ) &
If ( $referenceInUse + $learnInUse + $testInUse > 1 ; ". These records must be deleted before this section can be deleted." ; ". These records must be deleted before this section can be deleted." ) ); Buttons: “OK” ]
Exit Script [ ]
End If
#
Set Variable [ $$addTagToCitation ]
#
#If the section being deleted has no records
#then make sure the user really wants to delete it.
Show Custom Dialog [ Message: "Delete " & ruleSection::name & "?"; Buttons: “cancel”, “delete” ]
#
#If the user cancels, stop the delete.
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Set Variable [ $delete ]
Refresh Window
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
#
#If the user conﬁrms, then delete the section.
Else If [ Get ( LastMessageChoice ) = 2 ]
Delete Record/Request
[ No dialog ]
January 7, 平成26 12:13:49 Imagination Quality Management.fp7 - deleteSection -1-sectionScripts: deleteSection
Delete Record/Request
[ No dialog ]
If [ TEMP::ksection = $delete ]
Set Field [ TEMP::ksection; "" ]
Set Field [ TEMP::sectionName; "" ]
Select Window [ Name: "Setup"; Current ﬁle ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
End If
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
End If
#
January 7, 平成26 12:13:49 Imagination Quality Management.fp7 - deleteSection -2-
