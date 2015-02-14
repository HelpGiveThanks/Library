tagMenu: addBackSectionCreatorNode
#
Allow User Abort [ Off ]
Set Error Capture [ On ]
If [ $$stopAddBack = 1 ]
Exit Script [ ]
End If
#
#Make section creator key.
Go to Layout [ “tableGroupTag” (groupTest) ]
Enter Find Mode [ ]
Set Field [ groupTest::_Lgroup; TEMP::ksection ]
Perform Find [ ]
#
#Check if nodes selected -- primary, other, and
#test subject -- are in the current section.
Set Variable [ $nodePrimary; Value:groupTest::kRecordCreatorNode ]
Set Variable [ $nodeCreator; Value:groupTest::kSectionCreatorNodesCreator ]
Set Variable [ $groupName; Value:groupTest::defaultSectionInfo ]
Set Variable [ $nodeName; Value:groupTest::CaptionORinuseCheck ]
#
#If node record has been deleted then create a new one.
Go to Layout [ “defaultNode1” (tagMenus) ]
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; $nodePrimary ]
Set Field [ tagMenus::match; "node" ]
Perform Find [ ]
If [ Get (FoundCount) = 0 ]
#
#Find all node records.
Go to Layout [ “defaultNode1” (tagMenus) ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; "node" ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
#
#Create a new node group.
Go to Layout [ “tableGroupTag” (groupTest) ]
#
New Record/Request
Set Field [ groupTest::ksection; TEMP::ksection ]
Set Field [ groupTest::kRecordCreatorNode; $nodePrimary ]
#
Set Field [ groupTest::match; "node" ]
Set Field [ groupTest::name; $groupName ]
Set Field [ groupTest::nameSpelling; $groupName ]
Set Variable [ $group; Value:groupTest::_Lgroup ]
#
#Re-create section's creator node.
Go to Layout [ “defaultNode1” (tagMenus) ]
New Record/Request
Set Field [ tagMenus::kGroupOrTest; $group ]
Set Field [ tagMenus::ksection; TEMP::ksection ]
Set Field [ tagMenus::kRecordCreatorNode; $nodeCreator ]
Set Field [ tagMenus::_Ltag; $nodePrimary ]
Set Field [ tagMenus::tag; $nodeName ]
Set Field [ tagMenus::tagSpelling; $nodeName ]
Set Field [ tagMenus::match; "node" ]
#
#Return to defaultSection layout.
Go to Layout [ original layout ]
#
#Inform user node was added back.
Show Custom Dialog [ Message: "The creator node for this default section was added back. If you want to keep it deleted, you will have to delete the section it created right after you delete the section's creator node."; Buttons: “OK” ]
#
Exit Script [ ]
End If
#
#Find all nodes assigned to this section.
Enter Find Mode [ ]
Set Field [ tagMenus::match; "node" ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
#PRIMARY NODE
#Loop thru records to find primary node.
Go to Record/Request/Page
[ First ]
#
Loop
#
#If the key matches a lock or no locks exit the loop.
Exit Loop If [ $nodePrimary = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#If the record the loop ended up on does not accept
#the primary key being tested, then add its
#group to the current section. ( Node groups are
# are assigned to sections, not individual nodes.
# So if the user wants one node to be assigned
# to a new section, its group and all nodes in
# its group must be assigned to the new section.
# The reason for this is because the display of
# nodes by catergory requires that each group
# have a unique name and that each node belong
# to a group. For the node to be the same node
# The group key it holds has to be the same as
# well, which means the group has to appear
# with the node, and with the group comes
# all the nodes assigned to it. )
If [ $nodePrimary ≠ tagMenus::_Ltag and $nodePrimary ≠ "" ]
#
#Set variable to trigger Message to user.
Set Variable [ $nodeAddedBack; Value:1 ]
#
#Find the node to be added.
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; $nodePrimary ]
Perform Find [ ]
#
#Next, add the current section key to this node's
#group's keychain.
Set Variable [ $groupSectionKeychain; Value:ruleTagMenuGroups::ksection ]
Set Field [ ruleTagMenuGroups::ksection; TEMP::ksection & ¶ & $groupSectionKeychain ]
January 7, 平成26 16:22:44 Imagination Quality Management.fp7 - addBackSectionCreatorNode -1-tagMenu: addBackSectionCreatorNode
#
#Finally, refind all nodes, which now includes the
#node just added.
Enter Find Mode [ ]
Set Field [ tagMenus::match; "node" ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
End If
#
#Return to defaultSection layout.
Go to Layout [ original layout ]
#
#Inform user node was added back.
If [ $nodeAddedBack = 1 ]
Show Custom Dialog [ Message: "The creator node for this default section was added back. If you want to keep it deleted, you will have to delete the section it created right after you delete the section's creator node."; Buttons: “OK” ]
End If
#
January 7, 平成26 16:22:44 Imagination Quality Management.fp7 - addBackSectionCreatorNode -2-
