tagMenu: setDefaultSection
#
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Get key for tag that is to be added to record.
Set Variable [ $tag; Value:ruleSection::_Lgroup ]
Set Variable [ $tagName; Value:ruleSection::name ]
#
#Stop check spelling script as this script is triggered
#on section layout by record load trigger, and
#so before user can change the spelling.
Set Variable [ $$stopChangeSectionName; Value:1 ]
#
#Remove focus from field so can see
#conditional formatting.
Go to Field [ ]
#
#
#Select setup window.
Select Window [ Name: "Setup"; Current file ]
#
#Since sections are required, the deselect script
#steps are not needed. When the user clicks on
#a new record on the section layout this script
#is triggered and that section set as the default
#section.
Set Field [ tempSetup::ksection; $tag ]
Set Field [ tempSetup::sectionName; $tagName ]
Refresh Window
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#Allow duplicate tag check script to operate.
Set Variable [ $$stopChangeSectionName ]
#
#
#
#TURN INTO CHUNK!!!!!
#TURN INTO CHUNK!!!!!
#CHUNKaddReferenceNodesAndKeywords
#
#Check if nodes selected -- primary, other, and
#test subject -- are in the current section.
Select Window [ Name: "Setup"; Current file ]
Set Variable [ $nodePrimary; Value:tempSetup::kdefaultNodePrimary ]
Set Variable [ $nodeOther; Value:tempSetup::kdefaultNodeOther ]
Set Variable [ $nodeTestSubject; Value:tempSetup::kdefaultNodeTestSubject ]
#
#Find all nodes assigned to this section.
Go to Layout [ “defaultNode1” (tagMenus) ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; "node" ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
#
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
#Find the node to be added.
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; $nodePrimary ]
Perform Find [ ]
#
#Next, add the current section key to this node's
#group's keychain.
Set Variable [ $groupSectionKeychain; Value:ruleTagMenuGroups::ksection ]
Set Field [ ruleTagMenuGroups::ksection; TEMP::ksection & ¶ & $groupSectionKeychain ]
#
#Finally, refind all nodes, which now includes the
#node just added.
Enter Find Mode [ ]
Set Field [ tagMenus::match; "node" ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
End If
#
#TEST SUBJECT
#Loop thru records to find test subject node.
Go to Record/Request/Page
[ First ]
#
Loop
#
#If the key matches a lock or no locks exit the loop.
Exit Loop If [ $nodeTestSubject = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
January 7, 平成26 16:22:12 Imagination Quality Management.fp7 - setDefaultSection -1-tagMenu: setDefaultSection
#If the record the loop ended up on does not accept
#the test subject key being tested, then add its
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
If [ $nodeTestSubject ≠ tagMenus::_Ltag and $nodeTestSubject ≠ "" ]
#
#Find the node to be added.
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; $nodeTestSubject ]
Perform Find [ ]
#
#Next, add the current section key to this node's
#group's keychain.
Set Variable [ $groupSectionKeychain; Value:ruleTagMenuGroups::ksection ]
Set Field [ ruleTagMenuGroups::ksection; TEMP::ksection & ¶ & $groupSectionKeychain ]
#
#Finally, refind all nodes, which now includes the
#node just added.
Enter Find Mode [ ]
Set Field [ tagMenus::match; "node" ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
End If
#
#OTHER NODES
#Determine how many keys there are to find for
#on the other nodes' keychain.
Set Variable [ $numberOfNodes; Value:ValueCount ( $nodeOther ) ]
#
#Loop thru each node record, with every key
#in the keychain.
Loop
Go to Record/Request/Page
[ First ]
#
#Exit the loop when there are no more keys to check.
Exit Loop If [ $numberOfNodes = 0 ]
Loop
#
#If the key matches a lock or no locks exit the loop.
#( The get value calculation works by going to the
# key in the list specified by the numberOfNodes
# variable, set before entering the loops.
# The system starts with the last key and with each
# loop moves to the next key up, until there are
# no more keys to check. )
Exit Loop If [ GetValue ( $nodeOther ; $numberOfNodes ) = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#If the record the loop ended up on does not accept
#the other node key being tested, then add its
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
If [ GetValue ( $nodeOther ; $numberOfNodes ) ≠ tagMenus::_Ltag and $nodeOther ≠ "" ]
#
#Find this node to be added.
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; GetValue ( $nodeOther ; $numberOfNodes ) ]
Perform Find [ ]
#
#Next, add the current section key to this node's
#group's keychain.
Set Variable [ $groupSectionKeychain; Value:ruleTagMenuGroups::ksection ]
Set Field [ ruleTagMenuGroups::ksection; TEMP::ksection & ¶ & $groupSectionKeychain ]
#
#Finally, refind all nodes, which now includes the
#node just added.
Enter Find Mode [ ]
Set Field [ tagMenus::match; "node" ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
#
End If
#
#Go the next key up from the bottom of the list
#of keys on this section's keychain.
Set Variable [ $numberOfNodes; Value:$numberOfNodes - 1 ]
End Loop
Go to Layout [ “defaultSetup” (tempSetup) ]
#
#
#
#
January 7, 平成26 16:22:12 Imagination Quality Management.fp7 - setDefaultSection -2-
