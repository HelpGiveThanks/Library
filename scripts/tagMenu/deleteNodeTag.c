January 20, 2018 17:56:40 Library.fmp12 - deleteNodeTag -1-
tagMenu: deleteNodeTag
#
#
#If user is looking at keyword switch to that script.
If [ $$citationMatch = "key" ]
Perform Script [ “deleteKeywordTag (update)” ]
Exit Script [ ]
End If
#
#Exit field so user can see red delete
#formatting later on.
Go to Field [ ]
#
#Prevent all record load scripts (they slow down
#this script and are uneccessary).
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Set variables to conditionally format section to
#be deleted, and its record number so if the
#user cancels the delete, the system can return
#to this record.
Set Variable [ $delete; Value:tagMenus::_Ltag ]
Set Variable [ $deleteName; Value:tagMenus::tag ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
Set Variable [ $$addTagToCitation; Value:1 ]
Set Variable [ $group; Value:tagMenus::kGroupOrTest ]
Set Variable [ $groupName; Value:tagMenuGroup::name ]
#
#The check variable duplicates the $delete
#variable, and when there is time I'll remove it.
Set Variable [ $check; Value:tagMenus::_Ltag ]
#
#Because there may be no records found, stop
#the system from informing the user of this.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Open a new window and look for tag in both
#primary and other node fields.
New Window [ Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom
Control Area: “Yes”; Resize: “Yes” ]
// New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
#
#See if this node is this library's creator.
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::match; "library" ]
Perform Find [ ]
#
#If the current node is the library's creator
#note this.
If [ testSubsectionGroup::kRecordCreatorNode = $delete ]
Set Variable [ $lastSectionCreatorNode; Value:1 ]
Set Field [ testSubsectionGroup::ReportCaptionORLibraryCreatorName; $deleteName ]
Set Field [ testSubsectionGroup::nameSpellingFORTestItemGroup; $groupName ]
End If
#
#
#
#
#SETUP REFERENCE
#See if node is used by any setup
#reference records.
Go to Layout [ “tableSetupReference” (librarySetupReferenceMain) ]
Enter Find Mode [ ]
Set Field [ librarySetupReferenceMain::kcreatorNode; $check ]
Perform Find [ ]
If [ Get (FoundCount) ≠ 0 ]
Set Variable [ $setupReference; Value:Case ( Length ( librarySetupReferenceMain::name & " by " & librarySetupReferenceMain::
creatorName ) < 56 ;
 Left ( librarySetupReferenceMain::name & " by " & librarySetupReferenceMain::creatorName ; 55 ) & "... |" ;
 librarySetupReferenceMain::name & " by " & librarySetupReferenceMain::creatorName & " |" ) ]
Set Variable [ $foundCount; Value:Get (FoundCount) ]
End If
#
#
#
#
#LEARN
#See if node is used by any learn records.
#Look in main kprimary...
Go to Layout [ “tableTestLearn” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kNodePrimary; $check ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Perform Find [ ]
#
#Look in main kother...
Enter Find Mode [ ]
Set Field [ testlearn::kNodeOther; $check & ¶ ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Extend Found Set [ ]
If [ Get (FoundCount) ≠ 0 ]
Set Variable [ $inUse; Value:"Learn " & Get (FoundCount) ]
End If
#
#
#
#
#REFERENCE
#See if node is used by any reference records.
#Check in primary...
Go to Layout [ “Reference” (reference) ]
Enter Find Mode [ ]
Set Field [ reference::knodePrimary; $check ]
Perform Find [ ]
#
#Check in other...
Enter Find Mode [ ]
Set Field [ reference::knodeOther; $check ]
Extend Found Set [ ]
If [ Get (FoundCount) ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:$addToInUse & "; Reference " & Get (FoundCount) ]
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:"Reference " & Get (FoundCount) ]
End If
End If
#
#
#
#
#
#TAG BRAINSTORM
#See if node is used by any test result records.
#Check in primary...
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kRecordCreatorNode; $check ]
Set Field [ tagTable::match; "brainstorm" ]
Perform Find [ ]
#
If [ Get (FoundCount) ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:$addToInUse & "; Tags — brainstorm " & Get (FoundCount) ]
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:"Tags — brainstorm " & Get (FoundCount) ]
End If
Set Variable [ $TagsHeader; Value:1 ]
End If
#
#
#
#
#
#TAG COPYRIGHT
#See if node is used by any test result records.
#Check in primary...
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kRecordCreatorNode; $check ]
Set Field [ tagTable::match; "copyright" ]
Perform Find [ ]
#
If [ Get (FoundCount) ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
If [ $TagsHeader ≠ "" ]
Set Variable [ $inUse; Value:$addToInUse & ", copyright " & Get (FoundCount) ]
Else
Set Variable [ $inUse; Value:$addToInUse & "; Tags — copyright " & Get (FoundCount) ]
End If
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:"Tags — copyright " & Get (FoundCount) ]
End If
Set Variable [ $TagsHeader; Value:1 ]
End If
#
#
#
#
#
#TAG KEYWORD
#See if node is used by any test result records.
#Check in primary...
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kRecordCreatorNode; $check ]
Set Field [ tagTable::match; "key" ]
Perform Find [ ]
#
If [ Get (FoundCount) ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
If [ $TagsHeader ≠ "" ]
Set Variable [ $inUse; Value:$addToInUse & ", key " & Get (FoundCount) ]
Else
Set Variable [ $inUse; Value:$addToInUse & "Tags — key " & Get (FoundCount) ]
End If
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:"Tags — key " & Get (FoundCount) ]
End If
Set Variable [ $TagsHeader; Value:1 ]
End If
#
#
#
#
#
#TAG NODE
#See if node is used by any test result records.
#Check in primary...
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kRecordCreatorNode; $check ]
Set Field [ tagTable::match; "node" ]
#Omit creator nodes.
Set Field [ tagTable::textStyleOrCreatorNodeFlag; "=" ]
Perform Find [ ]
#
If [ Get (FoundCount) ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
If [ $TagsHeader ≠ "" ]
Set Variable [ $inUse; Value:$addToInUse & ", node " & Get (FoundCount) ]
Else
Set Variable [ $inUse; Value:$addToInUse & ": Tags — node " & Get (FoundCount) ]
End If
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:"Tags — node " & Get (FoundCount) ]
End If
Set Variable [ $TagsHeader; Value:1 ]
End If
#
#
#
#
#
#TAG PATH
#See if node is used by any test result records.
#Check in primary...
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kRecordCreatorNode; $check ]
Set Field [ tagTable::match; "path" ]
Perform Find [ ]
#
If [ Get (FoundCount) ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
If [ $TagsHeader ≠ "" ]
Set Variable [ $inUse; Value:$addToInUse & ", path " & Get (FoundCount) ]
Else
Set Variable [ $inUse; Value:$addToInUse & "; Tags — path " & Get (FoundCount) ]
End If
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:"Tags — path " & Get (FoundCount) ]
End If
Set Variable [ $TagsHeader; Value:1 ]
End If
#
#
#
#
#
#TAG PUBLICATION
#See if node is used by any test result records.
#Check in primary...
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kRecordCreatorNode; $check ]
Set Field [ tagTable::match; "publication" ]
Perform Find [ ]
#
If [ Get (FoundCount) ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
If [ $TagsHeader ≠ "" ]
Set Variable [ $inUse; Value:$addToInUse & ", publication " & Get (FoundCount) ]
Else
Set Variable [ $inUse; Value:$addToInUse & "; Tags — publication " & Get (FoundCount) ]
End If
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:"Tags — publication " & Get (FoundCount) ]
End If
Set Variable [ $TagsHeader; Value:1 ]
End If
#
#
#
#
#
#TAG PUBLISHER
#See if node is used by any test result records.
#Check in primary...
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kRecordCreatorNode; $check ]
Set Field [ tagTable::match; "publisher" ]
Perform Find [ ]
#
If [ Get (FoundCount) ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
If [ $TagsHeader ≠ "" ]
Set Variable [ $inUse; Value:$addToInUse & ", publisher " & Get (FoundCount) ]
Else
Set Variable [ $inUse; Value:$addToInUse & "; Tags — publisher " & Get (FoundCount) ]
End If
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:"Tags — publisher " & Get (FoundCount) ]
End If
End If
#
#
#
#
#
#TEST SUBJECT — SECTION
#See if node is the creator of any
#test section records.
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::kcreatorNode; $check ]
Perform Find [ ]
#
If [ Get (FoundCount) ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:$addToInUse & "; Setup Test " & Get (FoundCount) ]
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:"Setup Test " & Get (FoundCount) ]
End If
End If
#
#
#
#
#TEST SUBJECT — RESULT
#See if node is the creator of any
#test result records.
Go to Layout [ “tableTestLearn” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kRecordCreatorNode; $check ]
Set Field [ testlearn::filterFind; "=" ]
Perform Find [ ]
#
If [ Get (FoundCount) ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:$addToInUse & "; Test Result " & Get (FoundCount) ]
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:"Test Result " & Get (FoundCount) ]
End If
End If
#
#
#
#
#TEST SUBJECT — REPORT
#See if node is the test subject in any
#report records.
#NOT NECESSARY to check on report, as
#Report records are deleted when all test
#results for a report section are deleted.
#
#
#
#
#TEST TEMPLATE — SECTION
#See if node is used by any test result records.
#Check in primary...
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kRecordCreatorNode; $check ]
Set Field [ tagTable::match; "testSection" ]
Perform Find [ ]
#
If [ Get (FoundCount) ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:$addToInUse & "; Test Templates — section " & Get (FoundCount) ]
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:"testtemplate-section " & Get (FoundCount) ]
End If
Set Variable [ $TestTemplateHeader; Value:1 ]
End If
#
#
#
#
#TEST TEMPLATE — SUBSECTION
#See if node is used by any test result records.
#Check in primary...
Go to Layout [ “tableTestSubsectionTemplates” (testSubsectionTemplate) ]
Enter Find Mode [ ]
Set Field [ testSubsectionTemplate::kcreatorNode; $check ]
Perform Find [ ]
#
If [ Get (FoundCount) ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
If [ $TestTemplateHeader ≠ "" ]
Set Variable [ $inUse; Value:$addToInUse & ", subsection " & Get (FoundCount) ]
Else
Set Variable [ $inUse; Value:$addToInUse & "; Test Template — subsection " & Get (FoundCount) ]
End If
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:"Test Template — subsection " & Get (FoundCount) ]
End If
Set Variable [ $TestTemplateHeader; Value:1 ]
End If
#
#
#
#
#TEST TEMPLATE — ITEM
#See if node is used by any test result records.
#Check in primary...
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kRecordCreatorNode; $check ]
Set Field [ tagTable::match; "testItem" ]
Perform Find [ ]
#
If [ Get (FoundCount) ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
If [ $TestTemplateHeader ≠ "" ]
Set Variable [ $inUse; Value:$addToInUse & ", item " & Get (FoundCount) ]
Else
Set Variable [ $inUse; Value:$addToInUse & "; Test Template — item " & Get (FoundCount) ]
End If
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:"Test Template — item " & Get (FoundCount) ]
End If
End If
#
#
#
#
#TEST SUBJECT — SECTION
#See if node is the test subject for any
#test section records created to test it.
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::ktestSubjectNode; $check ]
Perform Find [ ]
If [ Get (FoundCount) ≠ 0 ]
Set Variable [ $inUseTestSubject; Value:"Setup Test " & Get (FoundCount) ]
End If
#
#
#
#
#TEST SUBJECT — RESULT
#See if node is the test subject in any
#test result records.
Go to Layout [ “tableTestLearn” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $check ]
Perform Find [ ]
If [ Get (FoundCount) ≠ 0 ]
If [ $inUseTestSubject ≠ "" ]
Set Variable [ $addToInUseTestSubject; Value:$inUseTestSubject ]
Set Variable [ $inUseTestSubject; Value:$addToInUseTestSubject & ", Test Result " & Get (FoundCount) ]
Else If [ $inUseTestSubject = "" ]
Set Variable [ $inUseTestSubject; Value:"Test Result " & Get (FoundCount) ]
End If
End If
#
#
#
#
#TEST SUBJECT — REPORT
#See if node is the test subject in any
#report records.
#NOT NECESSARY to check on report, as
#Report records are deleted when all test
#results for a report section are deleted.
// Go to Layout [ “tableReport” (report) ]
// Enter Find Mode [ ]
// Set Field [ report::ktestSubject; $check ]
// Perform Find [ ]
// If [ Get (FoundCount) ≠ 0 ]
// If [ $inUseTestSubject ≠ "" ]
// Set Variable [ $addToInUseTestSubject; Value:$inUseTestSubject ]
// Set Variable [ $inUseTestSubject; Value:$addToInUseTestSubject & ", Report " & Get (FoundCount) ]
// Else If [ $inUseTestSubject = "" ]
// Set Variable [ $inUseTestSubject; Value:"Report " & Get (FoundCount) ]
// End If
// End If
#
#
#
#
#Report on findings and if none delete node.
Close Window [ Current Window ]
#
#
#
#
#If the node being checked for deletion is in use
#as a default node then stop the script and inform
#the user of this fact.
If [ TEMP::kdefaultNodePrimary = tagMenus::_Ltag ]
Show Custom Dialog [ Message: "This node is currently selected as the default node (creator of all new records in this library )
and cannot be deleted."; Default Button: “OK”, Commit: “No” ]
#In use as the primary node.
Set Variable [ $primaryOtherOrTestSubjectNode; Value:1 ]
Else If [ FilterValues ( TEMP::kdefaultNodeOther ; tagMenus::_Ltag & "¶" ) ]
Show Custom Dialog [ Message: "This node is currently selected as a default other node (a co-creator of all new records in this
library ) and cannot be deleted."; Default Button: “OK”, Commit: “No” ]
#In use as an other node.
Set Variable [ $primaryOtherOrTestSubjectNode; Value:1 ]
Else If [ TEMP::kdefaultNodeTestSubject = tagMenus::_Ltag ]
Show Custom Dialog [ Message: "This node is currently selected as the default test subject and cannot be deleted."; Default
Button: “OK”, Commit: “No” ]
#In use as the test subject node.
Set Variable [ $primaryOtherOrTestSubjectNode; Value:1 ]
End If
#
#
#If the node is locked, tell the user, and include
#all the other reasons the node might not be
#able to be deleted, rather than making the user
#fulfill one delete requirement only to learn of
#another, and then another. Show all the
#delete requirements at once!
#
#Check creator nodes, to see if they are
#locked. NOTE: Creator nodes are created
#themselves only on Setup Tag Menus
#Node layouts.
If [ tagMenus::orderOrLock[2] ≠ "" ]
If [ $primaryOtherOrTestSubjectNode = "" ]
#
#NOT in use as a P, O, or TS node.
Show Custom Dialog [ Message: "This node is locked. Click the lock button above, and enter its password to unlock it.";
Default Button: “OK”, Commit: “No” ]
Else
#
#IN USE as a P, O, or TS node.
Show Custom Dialog [ Message: "And, this node cannot be deleted because it is locked. Click the lock button above, and
enter its password to unlock it."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#This node is locked.
Set Variable [ $locked; Value:1 ]
#
#Check nodes created by creator nodes
#to see if their creator node is locked.
Else If [ tagCreatorLock::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it — " & tagCreatorLock::tag & " — in the
setup tag window and enter the password to unlock it."; Default Button: “OK”, Commit: “No” ]
#
#This node is locked because its creator node
#is locked. NOTE: This locked variable just
#tells the script below that the user has
#already seen a locked message and so the
#next message they see needs to begin with,
#"Also, ...."
Set Variable [ $locked; Value:1 ]
End If
#
#
#
#If the node is found to have created records,
#tell the user where they are, and that this
#node cannot be deleted while records it
#created remain in the library.
If [ $inUse ≠ "" or $inUseTestSubject ≠ "" or $setupReference ≠ "" ]
#
#
#Conditionally format the node record the
#user is trying to delete to highlight which
#node the following messages apply to.
Set Variable [ $delete; Value:tagMenus::_Ltag ]
Set Variable [ $group ]
Refresh Window
#
#
#
#
#NOT locked.
#NOT in use as a P, O, or TS node.
#So this will be the first "you cannot delete..."
#message the user since this script started.
If [ $primaryOtherOrTestSubjectNode = "" and $locked = "" ]
#
#
#Node created library records.
If [ $inUse ≠ "" ]
Show Custom Dialog [ Message: "The records created by this node must be deteted before it can be deleted: " &
$inUse & "."; Default Button: “OK”, Commit: “Yes” ]
#
#AND test subject records where created
#for this node.
If [ $inUseTestSubject ≠ "" ]
Show Custom Dialog [ Message: "And, test subject records created for this node must also be deleted: " &
$inUseTestSubject & "."; Default Button: “OK”, Commit: “Yes” ]
End If
End If
#
#
#ONLY test subject records where created
#for this node.
If [ $inUse = "" and $inUseTestSubject ≠ "" ]
Show Custom Dialog [ Message: "Test subject records created for this node must be deleted before it can be deleted: "
& $inUseTestSubject & "."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#
End If
#
#
#
#
#Locked, AND/OR,
#IN USE as a P, O, or TS node.
#So this will NOT be the first "you cannot
#delete..." message the user since this
#script started.
If [ $primaryOtherOrTestSubjectNode ≠ "" or $locked ≠ "" ]
#
#
#Node created library records.
If [ $inUse ≠ "" ]
Show Custom Dialog [ Message: "Also, the records created by this node must be deteted before it can be deleted: " &
$inUse & "."; Default Button: “OK”, Commit: “Yes” ]
#
#AND test subject records where created
#for this node.
If [ $inUseTestSubject ≠ "" ]
Show Custom Dialog [ Message: "And, test subject records created for this node must also be deleted: " &
$inUseTestSubject & "."; Default Button: “OK”, Commit: “Yes” ]
End If
End If
#
#
#ONLY test subject records where created
#for this node.
If [ $inUse = "" and $inUseTestSubject ≠ "" ]
Show Custom Dialog [ Message: "Also, test subject records created for this node must be deleted before it can be
deleted: " & $inUseTestSubject & "."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#
End If
#
#
#
#
#If the node was used to create one or
#more library setup reference records
#tell the user this:
If [ $setupReference ≠ "" ]
#
#
#NOT locked.
#NOT in use as a P, O, or TS node.
#Creator of ZERO records.
#This will be the first "you cannot delete..."
#message the user since this script started.
If [ $primaryOtherOrTestSubjectNode = "" and $locked = "" and $inUse = "" and $inUseTestSubject = "" ]
If [ $foundCount = 1 ]
Show Custom Dialog [ Message: "This node has been used to create the following library setup reference in the
Setup window, which must deleted before deleting this node: " & $setupReference; Default Button: “OK”,
Commit: “Yes” ]
Show Custom Dialog [ Message: "This reference giving it credit for setting up this library should definitially be
deleted since this node hasn't created any records in this library."; Default Button: “OK”, Commit: “Yes” ]
Else If [ $foundCount = 2 ]
Show Custom Dialog [ Message: "This node has been used to create the following library setup reference, and 1
other, in the Setup window. Both must deleted before deleting this node: " & $setupReference; Default Button:
“OK”, Commit: “No” ]
Show Custom Dialog [ Message: "This reference giving it credit for setting up this library should definitially be
deleted since this node hasn't created any records in this library."; Default Button: “OK”, Commit: “Yes” ]
Else If [ $foundCount > 2 ]
Show Custom Dialog [ Message: "This node has been used to create the following library setup reference, and " &
$foundCount & " others, in the Setup window. They must deleted before deleting this node: " &
$setupReference; Default Button: “OK”, Commit: “No” ]
Show Custom Dialog [ Message: "This reference giving it credit for setting up this library should definitially be
deleted since this node hasn't created any records in this library."; Default Button: “OK”, Commit: “Yes” ]
End If
End If
#
#
#Locked, AND/OR,
#IN USE as a P, O, or TS node, AND/OR,
#Creator of SOME library records.
#So this will NOT be the first "you cannot
#delete..." message the user since this
#script started.
If [ $primaryOtherOrTestSubjectNode ≠ "" or $locked ≠ "" or $inUse ≠ "" or $inUseTestSubject ≠ "" ]
If [ $foundCount = 1 ]
#
#
Show Custom Dialog [ Message: "And finally, this node has been used to create the following library setup
reference in the Setup window, which must deleted before deleting this node: " & $setupReference; Default
Button: “OK”, Commit: “Yes” ]
#Creator of ZERO records (so node is locked
#and/or a P, 0, or TS node).
If [ $inUse = "" and $inUseTestSubject = "" ]
Show Custom Dialog [ Message: "This reference giving it credit for setting up this library should definitially be
deleted since this node hasn't created any records in this library."; Default Button: “OK”, Commit: “No” ]
End If
#
#
Else If [ $foundCount = 2 ]
#
#
Show Custom Dialog [ Message: "And finally, this node has been used to create the following library setup
reference, and 1 other, in the Setup window. Both must deleted before deleting this node: " &
$setupReference; Default Button: “OK”, Commit: “Yes” ]
#Creator of ZERO records (so node is locked
#and/or a P, 0, or TS node).
If [ $inUse = "" and $inUseTestSubject = "" ]
Show Custom Dialog [ Message: "This reference giving it credit for setting up this library should definitially be
deleted since this node hasn't created any records in this library."; Default Button: “OK”, Commit: “No” ]
End If
#
#
Else If [ $foundCount > 2 ]
#
#
Show Custom Dialog [ Message: "And finally, this node has been used to create the following library setup
reference, and " & $foundCount & " others, in the Setup window. They must deleted before deleting this node:
" & $setupReference; Default Button: “OK”, Commit: “Yes” ]
#Creator of ZERO records (so node is locked
#and/or a P, 0, or TS node).
If [ $inUse = "" and $inUseTestSubject = "" ]
Show Custom Dialog [ Message: "This reference giving it credit for setting up this library should definitially be
deleted since this node hasn't created any records in this library."; Default Button: “OK”, Commit: “No” ]
End If
#
#
End If
End If
#
#
End If
#
#
#
#
#Remove conditional formatting highlight of
#the node record the user was trying to delete.
Set Variable [ $delete ]
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Refresh Window
#
#
End If
#
#
#
If [ $primaryOtherOrTestSubjectNode ≠ "" or $locked ≠ "" or $inUse ≠ "" or $inUseTestSubject ≠ "" or $setupReference ≠ "" ]
Halt Script
End If
#
#
#If the node being deleted was not found in
#use then make sure the user really wants
#it deleted.
If [ $inUse = "" ]
#
#If node is this library's creator
#tell user this and exit the script.
If [ $lastSectionCreatorNode = 1 ]
Show Custom Dialog [ Message: "This node is the creator of this library. It cannot be deleted."; Default Button: “OK”,
Commit: “Yes” ]
Exit Script [ ]
End If
#
#If the node being deleted was not found in
#use in any sections of the database then before
#deleting it make sure the user really wants it deleted.
Set Variable [ $group ]
Refresh Window
Show Custom Dialog [ Message: "Delete current node?"; Default Button: “cancel”, Commit: “No”; Button 2: “delete”, Commit:
“No” ]
Set Variable [ $group; Value:tagMenus::kGroupOrTest ]
Set Variable [ $deleteGroup; Value:tagMenuGroup::name ]
#
#If the user cancels, stop the delete.
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Set Variable [ $delete ]
Set Variable [ $group ]
Refresh Window
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
#
#If the user says yes, first make sure the record
#is not the last record in a group. If it is and
#the system deleted the record without deleting
#the group too, this group would become
#an orphan as only categories that have records
#attached to them show up for the user to add
#more records uner them. So the group
#record must also be deleted if this is the last
#record under it.
Else If [ Get ( LastMessageChoice ) = 2 ]
New Window [ Name: "delete tag"; Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize:
“Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kGroupOrTest; $group ]
Perform Find [ ]
#
#If there are more records under this cateogry
#then the system deletes the current record without
#any more user input.
If [ Get (FoundCount) ≠ 1 ]
Close Window [ Name: "Delete Tag"; Current file ]
Delete Record/Request
[ No dialog ]
Set Variable [ $delete ]
Set Variable [ $group ]
#
#Capture recordID to conditionally format current record.
Set Variable [ $$tagRecordID; Value:Get (RecordID) ]
#
#Get reference groups and references order
#number in case user changes it.
Set Variable [ $$refGroupOrderNumber; Value:tagKeywordPrimary::orderOrLock ]
Set Variable [ $$refOrderNumber; Value:reference::publicationYearOrStuffOrderNumber ]
#
#Get tag's copyright key for 'select' button
#in case this node is locked, and the copyright
#has to be put back to the orginal after the
#user is informed they cannot change a locked
#record's copyright.
Set Variable [ $$oldCopyright; Value:tagMenus::notesOrCopyright ]
#
Refresh Window
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
#
#BUT if only one record is found user is asked
#if they want to delete the group too.
Else If [ Get (FoundCount) = 1 ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#The records are sorted by group to show
#the user which group is going to be deleted.
If [ TEMP::sortKey ≠ "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on
value list: “order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
Show Custom Dialog [ Message: "Deleting " & $deleteName & " will also delete its group — " & $deleteGroup & " — as
it is the last tag in this group."; Default Button: “Cancel”, Commit: “Yes”; Button 2: “Delete”, Commit: “No” ]
#
#If the user says yes, then delete both the tag and
#the group record.
If [ Get ( LastMessageChoice ) = 2 ]
#
#Delete tag.
Delete Record/Request
[ No dialog ]
#
#Delete group.
Select Window [ Name: "delete tag"; Current file ]
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::_Lgroup; $group ]
Perform Find [ ]
Delete Record/Request
[ No dialog ]
End If
End If
End If
Close Window [ Name: "Delete Tag"; Current file ]
Set Variable [ $delete ]
Set Variable [ $group ]
#
#Capture recordID to conditionally format current record.
Set Variable [ $$tagRecordID; Value:Get (RecordID) ]
#
#Get group ID for 'move' button script.
Set Variable [ $$groupOLD; Value:tagMenus::kGroupOrTest ]
#
#Get reference groups and references order
#number in case user changes it.
Set Variable [ $$refGroupOrderNumber; Value:tagKeywordPrimary::orderOrLock ]
Set Variable [ $$refOrderNumber; Value:reference::publicationYearOrStuffOrderNumber ]
#
#Get tag's copyright key for 'select' button
#in case this node is locked, and the copyright
#has to be put back to the orginal after the
#user is informed they cannot change a locked
#record's copyright.
Set Variable [ $$oldCopyright; Value:tagMenus::notesOrCopyright ]
#
Refresh Window
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
End If
#
#
