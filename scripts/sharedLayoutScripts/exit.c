January 18, 2018 16:09:49 Library.fmp12 - exit -1-
sharedLayoutScripts: exit
#
// #Follow the record whose order number was
// #changed on the reportTestResult layout.
// If [ Get ( WindowName ) = "References" ]
// Scroll Window
[ Home ]
// Sort Records [ ]
[ No dialog ]
// End If
#
#If there are no editors on the referenceEDIT
#layout than delete any abbreviations.
If [ reference::compilationEditors = "" and Get ( ActiveFieldName ) = "compilationAbbr" ]
Set Field [ reference::compilationAbbr; "" ]
Set Field [ reference::compilationNumberOfEditors; "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "Type in the editor, compiler, or translators' names before checking the box to indicate what
they are."; Default Button: “OK”, Commit: “No” ]
Else If [ reference::compilationEditors = "" and Get ( ActiveFieldName ) = "compilationNumberOfEditors" ]
Set Field [ reference::compilationNumberOfEditors; "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "Type in the editor, compiler, or translators' names before checking the 'plural' box to indicate
that there is more than one."; Default Button: “OK”, Commit: “No” ]
End If
#
If [ Get ( WindowName ) = "References" ]
Go to Field [ ]
If [ Get (LayoutTableName) and tagKeywordPrimary::orderOrLock = "delete number" ]
Set Field [ tagKeywordPrimary::orderOrLock; "" ]
End If
#
#Follow the record whose order number was
#changed on the reference layout.
If [ Get (LayoutTableName) = "reference" and $$refGroupOrderNumber ≠ tagKeywordPrimary::orderOrLock
or
Get (LayoutTableName) = "reference" and $$refOrderNumber ≠ reference::publicationYearOrStuffOrderNumber ]
Scroll Window
[ Home ]
Sort Records [ ]
[ No dialog ]
#
#Get reference groups and references order
#number in case user changes it.
Set Variable [ $$refGroupOrderNumber; Value:tagKeywordPrimary::orderOrLock ]
Set Variable [ $$refOrderNumber; Value:reference::publicationYearOrStuffOrderNumber ]
End If
Exit Script [ ]
End If
#
#TEST ITEM ORDER NUMBER
#If this is a test item and it is locked replace
#revert the order number change and exit
# the script.
If [ Get (LayoutName) = "setupTestItem" and tagMenus::match = "testItem" and nodeLockTestTagItemGroup::orderOrLock ≠ "" ]
If [ tagMenus::orderOrLock ≠ tagMenus::orderOrLock[2] ]
Set Field [ tagMenus::orderOrLock; tagMenus::orderOrLock[2] ]
End If
If [ tagMenuTestItemGroup::orderOrLibraryType ≠ tagMenuTestItemGroup::orderOrLibraryType[2] ]
Set Field [ tagMenuTestItemGroup::orderOrLibraryType; tagMenuTestItemGroup::orderOrLibraryType[2] ]
End If
#
#If this is a test item and it is not locked replace
#the backup order number with the new
#change, and continue the script to sort the test
#items based on this change.
Else If [ Get (LayoutName) = "setupTestItem" and tagMenus::match = "testItem" and nodeLockTestTagItemGroup::orderOrLock = "" ]
If [ tagMenus::orderOrLock ≠ tagMenus::orderOrLock[2] or tagMenuTestItemGroup::orderOrLibraryType ≠
tagMenuTestItemGroup::orderOrLibraryType[2] ]
Set Variable [ $sortTestItems; Value:1 ]
End If
Set Field [ tagMenus::orderOrLock[2]; tagMenus::orderOrLock[1] ]
Set Field [ tagMenuTestItemGroup::orderOrLibraryType[2]; tagMenuTestItemGroup::orderOrLibraryType[1] ]
End If
#
#SUBSECTION ORDER NUMBER
#If this is a test item and it is locked replace
#revert the order number change and exit
# the script.
If [ Get (LayoutName) = "setupTestSubsection" and testSectionCreatorLock::orderOrLock ≠ "" ]
Set Field [ testSubsectionTemplate::order; testSubsectionTemplate::order[2] ]
End If
If [ Get (LayoutName) = "setupTestSubsection" and testSubsectionGroupNodeLock::orderOrLock ≠ "" ]
Set Field [ testSubsectionGroup::orderOrLibraryType; testSubsectionGroup::orderOrLibraryType[2] ]
End If
#
#If this is a test item and it is not locked replace
#the backup order number with the new
#change, and continue the script to sort the test
#items based on this change.
If [ Get (LayoutName) = "setupTestSubsection" and testSectionCreatorLock::orderOrLock = "" ]
If [ testSubsectionTemplate::order ≠ testSubsectionTemplate::order[2] ]
Set Field [ testSubsectionTemplate::order[2]; testSubsectionTemplate::order[1] ]
Set Variable [ $sortTestItems; Value:1 ]
End If
End If
If [ Get (LayoutName) = "setupTestSubsection" and testSubsectionGroupNodeLock::orderOrLock = "" ]
If [ testSubsectionGroup::orderOrLibraryType ≠ testSubsectionGroup::orderOrLibraryType[2] ]
Set Field [ testSubsectionGroup::orderOrLibraryType[2]; testSubsectionGroup::orderOrLibraryType[1] ]
Set Variable [ $sortTestItems; Value:1 ]
End If
End If
#
#Delete tag group order number if user selects
#delete order number option.
If [ $$citationMatch = "key" and tagMenuGroup::orderOrLibraryType = "delete number"
 or
$$citationMatch = "node" and tagMenuGroup::orderOrLibraryType = "delete number" ]
Set Field [ tagMenuGroup::orderOrLibraryType; "" ]
End If
#
#Delete tag order number if user selects
#delete order number option.
If [ $$citationMatch = "key" and tagMenus::orderOrLock = "delete number"
 or
$$citationMatch = "testItem" and tagMenus::orderOrLock = "delete number"
 or
Get (LayoutTableName) and tagKeywordPrimary::orderOrLock = "delete number" ]
If [ Get (LayoutTableName) and tagKeywordPrimary::orderOrLock = "delete number" ]
Set Field [ tagKeywordPrimary::orderOrLock; "" ]
Else
Set Field [ tagMenus::orderOrLock; "" ]
End If
End If
#
#Delete test result order number if user selects
#delete order number option.
If [ //testlearnReportTags::orderDiscovery = "delete number"
Get ( ActiveFieldContents ) = "delete number" ]
// Set Field [ testlearnReportTags::orderTestResult; "" ]
Set Field [ "" ]
End If
#
#
#If node is currenlty locked then stop script, inform user.
If [ tagTLNodePrimary::orderOrLock ≠ "" ]
If [ testlearn::brainstormCasePoint = 1 ]
Set Field [ testlearn::brainstormCasePoint; "" ]
Else
Set Field [ testlearn::brainstormCasePoint; "1" ]
End If
Go to Field [ ]
Show Custom Dialog [ Message: "The node — " & tagTLNodePrimary::tag & " — is locked. Go to the Default Node Tag Menu
and A) click 'lock' to unlock it."; Default Button: “OK”, Commit: “No” ]
Exit Script [ ]
End If
#
#If node doesn't have a password delete any
#order number, but if the node does have
#password then put in a zero.
If [ $$citationMatch = "node" and tagMenus::orderOrLock[2] = "" and Get (LayoutName) ≠ "defaultSections" and Get (LayoutName) ≠
"defaultTestNewSection" ]
Set Field [ tagMenus::orderOrLock; "" ]
Set Field [ tagMenus::orderOrLock[2]; "" ]
Else If [ $$citationMatch = "node" and tagMenus::orderOrLock[2] ≠ "" and Get (LayoutName) ≠ "defaultSections" ]
Set Field [ tagMenus::orderOrLock; 0 ]
End If
#
#If user changed copyright of a locked node,
#on the Node menu change it back and inform user.
If [ tagMenus::notesOrCopyright ≠ $$oldCopyright and tagCreatorLock::orderOrLock ≠ "" and tagMenus::match = "node"
or
tagMenus::notesOrCopyright ≠ $$oldCopyright and tagMenus::orderOrLock = "0" and tagMenus::match = "node" ]
Set Field [ tagMenus::notesOrCopyright; $$oldCopyright ]
Go to Field [ ]
If [ tagMenus::orderOrLock[2] = "" ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it — " & tagCreatorLock::tag & " — enter
the password to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "This node is locked. Click the lock button above, and enter its password to unlock it.";
Default Button: “OK”, Commit: “No” ]
End If
End If
#
#If user changed copyright of a locked node,
#on the brainstorm menu change it back
#and inform user.
If [ tagCreatorLock::orderOrLock ≠ "" and tagMenus::orderOrLock ≠ "lock" and tagMenus::match = "brainstorm" or
tagCreatorLock::orderOrLock ≠ "" and tagMenus::orderOrLock ≠ "lock" and tagMenus::match = "copyright" or
tagCreatorLock::orderOrLock ≠ "" and tagMenus::orderOrLock ≠ "lock" and tagMenus::match = "test" ]
Set Field [ tagMenus::notesOrCopyright; $$oldCopyright ]
Go to Field [ ]
Show Custom Dialog [ Message: "The node that created this brainstorm — " & tagCreatorLock::tag & " — is locked. Go to the
setup tag window and enter its password to unlock it."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#
#If this is the primary node on a default layout,
#and if the default copyright is blank or is
#different from primary's copyright, then update
#the default copyright to match this node's copyright.
If [ $$citationMatch = "node" and tempSetup::kdefaultCopyright ≠ tagMenus::notesOrCopyright and tagMenus::_Ltag = tempSetup::
kdefaultNodePrimary ]
Set Variable [ $$copyright; Value:tagMenus::notesOrCopyright ]
Set Field [ tempSetup::kdefaultCopyright; tagMenus::notesOrCopyright ]
Show Custom Dialog [ Message: "The library's default copyright has been updated to match the default node's copyright.";
Default Button: “OK”, Commit: “Yes” ]
End If
#
#
#Exit field.
Go to Field [ ]
#
#Follow the record whose order number was
#changed on the reportTestResult layout.
If [ $$citationMatch = "testResult"
 or
$$citationMatch = "testItem" and $sortTestItems = 1
or
Get (LayoutName) = "setupTestSubsection" and $sortTestItems = 1 ]
Scroll Window
[ Home ]
Sort Records [ ]
[ No dialog ]
End If
#
#Follow the record whose order number was
#changed on the reference layout.
If [ Get (LayoutTableName) = "reference" and $$refGroupOrderNumber ≠ tagKeywordPrimary::orderOrLock
or
Get (LayoutTableName) = "reference" and $$refOrderNumber ≠ reference::publicationYearOrStuffOrderNumber ]
Scroll Window
[ Home ]
Sort Records [ ]
[ No dialog ]
#
#Get reference groups and references order
#number in case user changes it.
Set Variable [ $$refGroupOrderNumber; Value:tagKeywordPrimary::orderOrLock ]
Set Variable [ $$refOrderNumber; Value:reference::publicationYearOrStuffOrderNumber ]
#
#One more sort seems needed sometimes
#to get FM to focus on selected record.
Sort Records [ ]
[ No dialog ]
End If
#
#If this is the reference section and user is
#looking at either author/node or keyword/
#subject ordered records, check to see if this
#order has changed as a result of re-ordering
#the author/node or keyword/subject tags.
If [ $$citationMatch = "key" and $$referenceSort = "" and Get ( WindowName ) = "Tag Menus"
 or
$$citationMatch = "node" and $$referenceSort = "author" and Get ( WindowName ) = "Tag Menus" ]
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) ≠ 112 ]
Commit Records/Requests
#
#See if the edited record changed position in
#the main reference window as a result of
#alphabetical or order number changing edits.
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $currentrecord; Value:Get (RecordNumber) ]
New Window [ Name: "CheckDuplicateRecordPosition"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”;
Zoom Control Area: “Yes”; Resize: “Yes” ]
If [ $$citationMatch = "key" and $$referenceSort = "" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on
value list: “testPulldownListANDsortOrderList”
tagKeywordPrimary::tag; ascending
reference::publicationYearOrStuffOrderNumber; based on value list: “testPulldownListANDsortOrderList”
reference::Title; ascending
reference::thoughtsNotesEtc; ascending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on
value list: “order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceForReferenceWindow; ascending ]
[ Restore; No dialog ]
End If
Else If [ $$citationMatch = "node" and $$referenceSort = "author" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::sortByAuthor; ascending
reference::referenceForReferenceWindow; ascending ]
[ Restore; No dialog ]
End If
#
#If the edited record moved then note this.
If [ $currentrecord ≠ Get (RecordNumber) ]
Set Variable [ $recordMoved; Value:Get (RecordNumber) ]
End If
Close Window [ Name: "CheckDuplicateRecordPosition"; Current file ]
#
#Re-sort to view edited record if it
#was moved.
If [ $recordMoved ≠ "" ]
If [ $$citationMatch = "key" and $$referenceSort = "" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based
on value list: “testPulldownListANDsortOrderList”
tagKeywordPrimary::tag; ascending
reference::publicationYearOrStuffOrderNumber; based on value list: “testPulldownListANDsortOrderList”
reference::Title; ascending
reference::thoughtsNotesEtc; ascending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based
on value list: “order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceForReferenceWindow; ascending ]
[ Restore; No dialog ]
End If
Else If [ $$citationMatch = "node" and $$referenceSort = "author" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::sortByAuthor; ascending
reference::referenceForReferenceWindow; ascending ]
[ Restore; No dialog ]
End If
Go to Record/Request/Page [ $recordMoved ]
[ No dialog ]
End If
End If
#
#Return to the Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
End If
#
#
#This prevents the system trademark tag (not
#user created) being used improperly.
If [ tagsCopyrightGroup::_Lgroup = "92020171119521809" and Left ( Get ( LayoutName ) ; 9 ) = "learnMenu" ]
Show Custom Dialog [ Message: "Trademark tags can only be added to reference records, and then only if if the reference is for
a trademark, logo, brand, etc."; Default Button: “OK”, Commit: “Yes” ]
#
#Set default copyright for tag.
Set Field [ tagMenus::notesOrCopyright; TEMP::kdefaultCopyright ]
#
Show Custom Dialog [ Message: "The copyright has been reset to the current default. Please choose again if this not what you
want."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#
#
#
