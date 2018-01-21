January 10, 2018 15:45:46 Library.fmp12 - CHUNK_checkCreatorNodeAndPrimaryNode -1-
startclose: CHUNK_checkCreatorNodeAndPrimaryNode
#
#PURPOSE: Restores library's creator node If
#accidently deleted while in admin mode, and
#checks to see if primary node's creator is locked.
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Get creator node information from
#library record.
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Perform Find [ Specified Find Requests: Find Records; Criteria: testSubsectionGroup::match: “"library"” ]
[ Restore ]
If [ Get (FoundCount) = 0 ]
Show Custom Dialog [ Message: "This library's library ID record has been deleted. It will no longer work. If it has records, then
import them into a new library. "; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "If you can, check the creator node key fields for records in this library, and make sure there is
a creator node for them, and if not, re-create one."; Default Button: “OK”, Commit: “Yes” ]
Close Window [ Current Window ]
Set Field [ TEMP::kdefaultNodeOther; "" ]
Set Field [ TEMP::kdefaultCopyright; "" ]
Halt Script
End If
Set Variable [ $node; Value:testSubsectionGroup::kRecordCreatorNode ]
Set Variable [ $nodeName; Value:testSubsectionGroup::ReportCaptionORLibraryCreatorName ]
Set Variable [ $group; Value:testSubsectionGroup::orderOrLibraryType ]
Set Variable [ $groupName; Value:testSubsectionGroup::nameSpellingFORTestItemGroup ]
#
#Make sure the creator node's group exists.
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::_Lgroup; $group ]
Perform Find [ ]
#
#If not, recreate this group.
If [ Get (FoundCount) = 0 ]
New Record/Request
Set Field [ testSubsectionGroup::match; "node" ]
Set Field [ testSubsectionGroup::kRecordCreatorNode; $node ]
Set Field [ testSubsectionGroup::_Lgroup; $group ]
Set Field [ testSubsectionGroup::nameSpellingEXCEPTForTestItemGroup; $groupName ]
Set Field [ testSubsectionGroup::nameSpellingFORTestItemGroup; $groupName ]
End If
#
#Make sure the creator node exists.
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::_Ltag; $node ]
Perform Find [ ]
#
#If not, recreate this node.
If [ Get (FoundCount) = 0 ]
New Record/Request
Set Field [ tagTable::_Ltag; $node ]
Set Field [ tagTable::match; "node" ]
Set Field [ tagTable::kGroupOrTest; $group ]
Set Field [ tagTable::tag; $nodeName ]
Set Field [ tagTable::tagSpelling; $nodeName ]
Set Field [ tagTable::kRecordCreatorNode; $node ]
End If
#
#
#
#
#See primary node's creator is locked.
#
If [ tempSetup::DEFAULTNodePrimaryName ≠ "" ]
#Do not load tag records until the end of script
#to prevent flashing of window and to speed up
#script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Find the pimary node if there is one.
Go to Layout [ “defaultNode1” (tagMenus) ]
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; tempSetup::kdefaultNodePrimary ]
Perform Find [ ]
#
#Note primary node's creator if it is locked,
#and clear it if not locked.
If [ primaryNodesCreatorLock::orderOrLock ≠ "" ]
Set Field [ tempSetup::primaryNodesCreatorNodeIsLocked; primaryNodesCreatorLock::tag ]
Set Field [ tempSetup::kdefaultNodePrimaryCreator; primaryNodesCreatorLock::_Ltag ]
Else
Set Field [ tempSetup::primaryNodesCreatorNodeIsLocked; "" ]
Set Field [ tempSetup::kdefaultNodePrimaryCreator; "" ]
End If
End If
#
Set Variable [ $$stopLoadTagRecord ]
#
#
